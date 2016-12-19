// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"



bool g_ReadConfig();
void g_WriteConfig();
bool g_IsFileExist( const char* FilePath );
long g_GetFileSize(const char *FileName);
void g_WriteLog(const char*);
BOOL MyGetPrivateProfileString(char* pchNodeName, char* chPropertyName, char* pchValue);
static unsigned __stdcall CheckCameraStatus(void* pParam);

typedef int (_stdcall  *CallbackNETStatusFuc  )(char* pszIP);

HANDLE g_hThread = NULL;
bool g_bThreadExit = false;
bool  g_bLogEnable = false;
Camera6467* g_pCamera6467 = NULL;
CallbackNETStatusFuc g_NetStatusFuc= NULL;
CRITICAL_SECTION g_csLock;

BOOL APIENTRY DllMain( HMODULE hModule,
					  DWORD  ul_reason_for_call,
					  LPVOID lpReserved
					  )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_ReadConfig();
		g_pCamera6467 = NULL;
		InitializeCriticalSection(&g_csLock);
		g_hThread = (HANDLE)_beginthreadex( NULL, 0, &CheckCameraStatus, NULL, 0, NULL );
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		g_bThreadExit = true;
		if (g_pCamera6467)
		{
			delete g_pCamera6467;
			g_pCamera6467 = NULL;
		}
		//g_WriteConfig();
		if (g_hThread)
		{
			ResumeThread( g_hThread );  
			WaitForSingleObject( g_hThread, INFINITE ); 

			CloseHandle( g_hThread );
			g_hThread = NULL;
		}
		DeleteCriticalSection(&g_csLock);
		break;
	}
	return TRUE;
}


long g_GetFileSize(const char *FileName)
{
	FILE* tmpFile = fopen(FileName, "rb");
	if(tmpFile)
	{
		fseek(tmpFile, 0, SEEK_END);
		long fileSize = ftell(tmpFile);
		fclose(tmpFile);
		tmpFile = NULL;
		return fileSize;
	}
	else
	{
		//"open file failed.";
		return 0;
	}
}

bool g_IsFileExist( const char* FilePath )
{
	if (FilePath == NULL)
	{
		return false;
	}
	FILE* tempFile = NULL;
	bool bRet = false;
	tempFile = fopen(FilePath, "r");
	if (tempFile)
	{
		bRet = true;
		fclose(tempFile);
		tempFile = NULL;
	}
	return bRet;
}

void g_WriteLog(const char* chLog)
{
	if (!g_bLogEnable)
	{
		return;
	}
	//取得当前的精确毫秒的时间
	static time_t starttime = time(NULL);
	static DWORD starttick = GetTickCount(); 
	DWORD dwNowTick = GetTickCount() - starttick;
	time_t nowtime = starttime + (time_t)(dwNowTick / 1000);
	struct tm *pTM = localtime(&nowtime);
	DWORD dwMS = dwNowTick % 1000;

	const int MAXPATH = 260;

	TCHAR szFileName[ MAXPATH] = {0};
	GetModuleFileName(NULL, szFileName, MAXPATH);	//取得包括程序名的全路径
	PathRemoveFileSpec(szFileName);				//去掉程序名

	char chLogPath[512] = {0};
	sprintf(chLogPath, "%s\\XLWLog\\%04d-%02d-%02d\\Sw.log",  szFileName, pTM->tm_year + 1900, pTM->tm_mon+1, pTM->tm_mday);
	MakeSureDirectoryPathExists(chLogPath);	

	FILE *file = NULL;
	file = fopen(chLogPath, "a+");
	if (file)
	{
		fprintf(file,"%04d-%02d-%02d %02d:%02d:%02d:%03d : %s\n",  pTM->tm_year + 1900, pTM->tm_mon+1, pTM->tm_mday,
			pTM->tm_hour, pTM->tm_min, pTM->tm_sec, dwMS, chLog);
		fclose(file);
		file = NULL;
	}
}

bool g_ReadConfig()
{
	char FileName[MAX_PATH];
	GetModuleFileNameA(NULL, FileName, MAX_PATH-1);

	PathRemoveFileSpecA(FileName);
	char iniFileName[MAX_PATH] = {0};
	char iniDeviceInfoName[MAX_PATH] = {0};
	strcat(iniFileName, FileName);
	strcat(iniFileName,"\\FouthHWYDll_XLW.ini");

	//读取可靠性配置文件
	int iLogEnable =  GetPrivateProfileIntA("Log", "Enable", 0, iniFileName);
	if (iLogEnable == 0 )
	{
		g_bLogEnable = false;
	}
	else
	{
		g_bLogEnable = true;
	}
	return true;
}

/**
@name    WritePrivateProfileInt
@brief   获取配置文件中指定的属性值
@param[in]        char* pchNodeName     节名
@param[in]        char* chPropertyName     键名
@param[in]        char* pchValue             键值
@return           成功TRUE，失败FALSE
*/
BOOL MyGetPrivateProfileString(char* pchNodeName, char* chPropertyName, char* pchValue)
{
	char FileName[MAX_PATH];
	GetModuleFileNameA(NULL, FileName, MAX_PATH-1);

	PathRemoveFileSpecA(FileName);
	char iniFileName[MAX_PATH] = {0};
	char iniDeviceInfoName[MAX_PATH] = {0};
	strcat(iniFileName, FileName);
	strcat(iniFileName,"\\FouthHWYDll_XLW.ini");

	GetPrivateProfileString(pchNodeName, chPropertyName, "127.0.0.1", pchValue,128, iniFileName);
	return TRUE;
}

static unsigned __stdcall CheckCameraStatus(void* pParam)
{
	int iCameraStatus = 1;
	char chDeviceIp[32] = {0};
	while (!g_bThreadExit)
	{
		EnterCriticalSection(&g_csLock);
		if (g_pCamera6467)
		{
			//当获取到的状态不为0时，相机处于断开状态
			iCameraStatus = g_pCamera6467->GetCamStatus();
			sprintf(chDeviceIp, "%s", g_pCamera6467->GetCameraIP());
			OutputDebugStringA(" Thread CameraStatus get camera status. \n");
		}
		else
		{
			memset(chDeviceIp, 0, sizeof(chDeviceIp));
		}
		LeaveCriticalSection(&g_csLock);
		if (g_NetStatusFuc)
		{
			if (strlen(chDeviceIp) > 0 && iCameraStatus )
			{
				g_NetStatusFuc(chDeviceIp);
				OutputDebugStringA(" Thread CameraStatus call NetStatusFuc. \n");
			}			
		}
		OutputDebugStringA(" Thread CameraStatus is runing. \n");
		Sleep(5*1000);		
	}
	OutputDebugStringA(" Thread CameraStatus stop runing. \n");
	return 0;
}