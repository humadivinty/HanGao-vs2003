// FouthHWYDll.cpp : ���� DLL Ӧ�ó���ĵ���������
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
	sprintf(chLog, "��ʼ���� SetServerPort, nPort = %d", nPort);
	g_WriteLog(chLog);



	g_WriteLog("�������� SetServerPort ,���� true");
}

FOUTHHWYDLL_API  BOOL  __stdcall StartServer()
{
	char chIP[32]= {0};
	MyGetPrivateProfileString("Device", "IP", chIP);

	char chLog[260] = {0};
	sprintf(chLog, "��ʼ���� StartServer, IP = %s", chIP);
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
		g_WriteLog("�������� StartServer ,���� true");
	}
	else
	{
		//delete g_pCamera6467;
		//g_pCamera6467 = NULL;
		g_WriteLog("�������� StartServer ,���� false");
	}
	
	return bRet;
}

FOUTHHWYDLL_API BOOL __stdcall Trigger( char *chIP )
{
	char chLog[260] = {0};
	sprintf(chLog, "��ʼ���� Trigger, IP = %s", chIP);
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
		g_WriteLog("�������� Trigger ,���� TRUE");
	}
	else
	{
		g_WriteLog("�������� Trigger ,���� FALSE");
	}
	return bRet;
}

FOUTHHWYDLL_API void __stdcall RegisterNETStatusEvent( CallbackNETStatusFuc NETFuc )
{
	char chLog[260] = {0};
	sprintf(chLog, "���� RegisterNETStatusEvent");
	g_WriteLog(chLog);

	g_NetStatusFuc = NETFuc;
	
}

FOUTHHWYDLL_API BOOL __stdcall StopServer()
{
	char chLog[260] = {0};
	sprintf(chLog, "��ʼ���� StopServer");
	g_WriteLog(chLog);
	EnterCriticalSection(&g_csLock);
	if (g_pCamera6467)
	{
		delete g_pCamera6467;
		g_pCamera6467 = NULL;
	}
	LeaveCriticalSection(&g_csLock);

	g_WriteLog("�������� StopServer ,���� TURE");
	return TRUE;
}

FOUTHHWYDLL_API BOOL __stdcall GetPlateInfo( char* lpPlate,unsigned char* lpTwoImg,char* strIP, int nDelayTime )
{
	char chLog[260] = {0};
	sprintf(chLog, "��ʼ���� GetPlateInfo, IP = %s, nDelayTime = %d", strIP, nDelayTime);
	g_WriteLog(chLog);

	EnterCriticalSection(&g_csLock);
	if (!g_pCamera6467)
	{
		LeaveCriticalSection(&g_csLock);
		g_WriteLog("�������� GetPlateInfo, �豸δ���ӣ�����FALSE");
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
			g_WriteLog("����ֵͼ����");
		}
		if (0 == strcmp(strIP, pTempResult->chDeviceIp))
		{
			bRet = TRUE;		//�������IP�봫������IP���ʱ�ŷ���TURE
		}
		else
		{
			g_WriteLog("�������� GetPlateInfo�� �����IP����IP����������FALSE");
		}
	}
	else
	{
		g_WriteLog("����ȴ���ʱ���������� GetPlateInfo, ����False");
	}

	if (pTempResult)
	{
		delete pTempResult;
		pTempResult = NULL;
	}

	if (bRet)
	{
		memset(chLog, 0 , sizeof(chLog));
		sprintf(chLog, "�������� GetPlateInfo, IP = %s, lpPlate = %s",strIP, lpPlate);
		g_WriteLog(chLog);
	}
	return bRet;
}
