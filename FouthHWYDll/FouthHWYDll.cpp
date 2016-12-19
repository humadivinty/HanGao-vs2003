// FouthHWYDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "FouthHWYDll.h"


extern void g_WriteLog(const char*);
extern BOOL MyGetPrivateProfileString(char* pchNodeName, char* chPropertyName, char* pchValue);

extern CallbackNETStatusFuc g_NetStatusFuc;
extern Camera6467* g_pCamera6467;
extern CRITICAL_SECTION g_csLock;



FOUTHHWYDLL_API void  __stdcall SetServerPort( UINT nPort )
{
	char chLog[260] = {0};
	sprintf(chLog, "开始调用 SetServerPort, nPort = %d", nPort);
	g_WriteLog(chLog);



	g_WriteLog("结束调用 SetServerPort ,返回 true");
}

FOUTHHWYDLL_API  BOOL  __stdcall StartServer()
{
	char chIP[32]= {0};
	MyGetPrivateProfileString("Device", "IP", chIP);

	char chLog[260] = {0};
	sprintf(chLog, "开始调用 StartServer, IP = %s", chIP);
	g_WriteLog(chLog);
	EnterCriticalSection(&g_csLock);
	if (g_pCamera6467)
	{
		delete g_pCamera6467;
		g_pCamera6467 = NULL;
	}
	g_pCamera6467 = new Camera6467(chIP, NULL, 0);
	bool bRet = g_pCamera6467->ConnectToCamera();
	LeaveCriticalSection(&g_csLock);
	if (bRet)
	{
		g_WriteLog("结束调用 StartServer ,返回 true");
	}
	else
	{
		//delete g_pCamera6467;
		//g_pCamera6467 = NULL;
		g_WriteLog("结束调用 StartServer ,返回 false");
	}
	
	return bRet;
}

FOUTHHWYDLL_API BOOL __stdcall Trigger( char *chIP )
{
	char chLog[260] = {0};
	sprintf(chLog, "开始调用 Trigger, IP = %s", chIP);
	g_WriteLog(chLog);
	BOOL bRet = FALSE;
	EnterCriticalSection(&g_csLock);
	if (g_pCamera6467 && (0 == strcmp(chIP, g_pCamera6467->GetCameraIP() ) ))
	{
		bRet = g_pCamera6467->TakeCapture();
	}
	LeaveCriticalSection(&g_csLock);
	if (bRet)
	{
		g_WriteLog("结束调用 Trigger ,返回 TRUE");
	}
	else
	{
		g_WriteLog("结束调用 Trigger ,返回 FALSE");
	}
	return bRet;
}

FOUTHHWYDLL_API void __stdcall RegisterNETStatusEvent( CallbackNETStatusFuc NETFuc )
{
	char chLog[260] = {0};
	sprintf(chLog, "调用 RegisterNETStatusEvent");
	g_WriteLog(chLog);

	g_NetStatusFuc = NETFuc;
	
}

FOUTHHWYDLL_API BOOL __stdcall StopServer()
{
	char chLog[260] = {0};
	sprintf(chLog, "开始调用 StopServer");
	g_WriteLog(chLog);
	EnterCriticalSection(&g_csLock);
	if (g_pCamera6467)
	{
		delete g_pCamera6467;
		g_pCamera6467 = NULL;
	}
	LeaveCriticalSection(&g_csLock);

	g_WriteLog("结束调用 StopServer ,返回 TURE");
	return TRUE;
}

FOUTHHWYDLL_API BOOL __stdcall GetPlateInfo( char* lpPlate,unsigned char* lpTwoImg,char* strIP, int nDelayTime )
{
	char chLog[260] = {0};
	sprintf(chLog, "开始调用 GetPlateInfo, IP = %s, nDelayTime = %d", strIP, nDelayTime);
	g_WriteLog(chLog);

	EnterCriticalSection(&g_csLock);
	if (!g_pCamera6467)
	{
		LeaveCriticalSection(&g_csLock);
		g_WriteLog("结束调用 GetPlateInfo, 设备未连接，返回FALSE");
		return FALSE;
	}
	LeaveCriticalSection(&g_csLock);

	DWORD dwFirstTime = GetTickCount();
	DWORD dwCurrentTime = 0;
	CameraResult* pTempResult = NULL;
	BOOL bRet = FALSE;

	while(!pTempResult)
	{
		EnterCriticalSection(&g_csLock);
		pTempResult = g_pCamera6467->GetOneResult();
		LeaveCriticalSection(&g_csLock);
		dwCurrentTime = GetTickCount();
		if (dwCurrentTime - dwFirstTime > nDelayTime)
		{
			break;
		}
		Sleep(50);
	}
	if (pTempResult)
	{
		EnterCriticalSection(&g_csLock);
		g_pCamera6467->SetResultToUnready();
		LeaveCriticalSection(&g_csLock);

		sprintf(lpPlate, "%s%s", pTempResult->chPlateColor, pTempResult->chPlateNO);
		if (pTempResult->CIMG_BinImage.dwImgSize > 0 && pTempResult->CIMG_BinImage.dwImgSize <= 280)
		{
			memcpy(lpTwoImg, pTempResult->CIMG_BinImage.pbImgData, pTempResult->CIMG_BinImage.dwImgSize);
			g_WriteLog("填充二值图数据");
		}
		if (0 == strcmp(strIP, pTempResult->chDeviceIp))
		{
			bRet = TRUE;		//当结果的IP与传进来的IP相等时才返回TURE
		}
		else
		{
			g_WriteLog("结束调用 GetPlateInfo， 传入的IP与结果IP不符，返回FALSE");
		}
	}
	else
	{
		g_WriteLog("结果等待超时，结束调用 GetPlateInfo, 返回False");
	}

	if (pTempResult)
	{
		delete pTempResult;
		pTempResult = NULL;
	}

	if (bRet)
	{
		memset(chLog, 0 , sizeof(chLog));
		sprintf(chLog, "结束调用 GetPlateInfo, IP = %s, lpPlate = %s",strIP, lpPlate);
		g_WriteLog(chLog);
	}
	return bRet;
}
