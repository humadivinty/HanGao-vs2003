#include "stdafx.h"
#include "Camera6467.h"
//#include "HvDevice/HvDeviceBaseType.h"
//#include "HvDevice/HvDeviceCommDef.h"
//#include "HvDevice/HvDeviceNew.h"
#include "tinyxml/tinyxml.h"
#include<math.h>
#include<shellapi.h>
//#pragma comment(lib, "./lib/hvdevice/HvDevice.lib")

#include "HvDevice/HvDeviceBaseType.h"
#include "HvDevice/HvDeviceCommDef.h"
#include "HvDevice/HvDeviceNew.h"
#pragma comment(lib, "HvDevice/HvDevice.lib")

Camera6467::Camera6467()
{
	m_CameraResult = NULL;
	m_BufferResult = NULL;
	m_hHvHandle = NULL;
	m_hWnd = NULL;
	m_strIP = std::string("");	
	m_iCompressQuality = 20;
	m_bResultComplete = false;
	m_dwLastCarID = -1;
	m_bSaveToBuffer = false;
	//合成图片初始化
	GetEncoderClsid(L"image/jpeg", &m_jpgClsid);
	GetEncoderClsid(L"image/bmp", &m_bmpClsid);

	ReadConfig();
	InitializeCriticalSection(&m_csLog);
	InitializeCriticalSection(&m_csResult);
}

Camera6467::Camera6467( const char* chIP, HWND*  hWnd, int Msg)
{
	m_strIP = std::string(chIP);
	m_hWnd = hWnd;
	m_iMsg = Msg;

	m_hHvHandle = NULL;
	m_iCompressQuality = 20;
	m_CameraResult = NULL;
	m_BufferResult = NULL;
	m_bResultComplete = false;
	m_bSaveToBuffer = false;
	m_dwLastCarID = -1;
	//合成图片初始化
	GetEncoderClsid(L"image/jpeg", &m_jpgClsid);
	GetEncoderClsid(L"image/bmp", &m_bmpClsid);

	ReadConfig();
	InitializeCriticalSection(&m_csLog);
	InitializeCriticalSection(&m_csResult);
}

Camera6467::~Camera6467()
{
	InterruptionConnection();
	if(NULL != m_hHvHandle)
	{
		HVAPI_CloseEx((HVAPI_HANDLE_EX)m_hHvHandle);
		m_hHvHandle = NULL;
	}
	if(NULL != m_CameraResult)
	{
		delete m_CameraResult;
		m_CameraResult = NULL;
	}
	if (NULL != m_BufferResult)
	{
		delete m_BufferResult;
		m_BufferResult = NULL;
	}
	m_bResultComplete = false;
	//m_strIP.clear();
	ClearAllResult();
	m_hWnd = NULL;
	DeleteCriticalSection(&m_csLog);
	DeleteCriticalSection(&m_csResult);
}

void Camera6467::ReadHistoryInfo()
{
	char FileName[MAX_PATH];
	GetModuleFileNameA(NULL, FileName, MAX_PATH-1);

	PathRemoveFileSpecA(FileName);
	char iniFileName[MAX_PATH] = {0};
	char iniDeviceInfoName[MAX_PATH] = {0};
	strcat(iniFileName, FileName);
	strcat(iniFileName,"\\SafeModeConfig.ini");

	//读取可靠性配置文件
	m_SaveModelInfo.iSafeModeEnable = GetPrivateProfileIntA(m_strIP.c_str(), "SafeModeEnable", 0, iniFileName);
	GetPrivateProfileStringA(m_strIP.c_str(),"BeginTime", "0", m_SaveModelInfo.chBeginTime, 256, iniFileName);
	GetPrivateProfileStringA(m_strIP.c_str(), "EndTime", "0", m_SaveModelInfo.chEndTime, 256, iniFileName);
	m_SaveModelInfo.iIndex = GetPrivateProfileIntA(m_strIP.c_str(), "Index", 0, iniFileName);
	m_SaveModelInfo.iDataType = GetPrivateProfileIntA(m_strIP.c_str(), "DataType", 0, iniFileName);
}

void Camera6467::WriteHistoryInfo( SaveModeInfo& SaveInfo )
{
	char fileName[MAX_PATH];
	GetModuleFileNameA(NULL, fileName, MAX_PATH-1);

	PathRemoveFileSpecA(fileName);
	char iniFileName[MAX_PATH] = {0};
	char iniDeviceInfoName[MAX_PATH] = {0};
	strcat(iniFileName, fileName);
	strcat(iniFileName, "\\SafeModeConfig.ini");

	//读取配置文件
	char chTemp[256] = {0};
	sprintf(chTemp, "%d", m_SaveModelInfo.iSafeModeEnable);

	//if(m_SaveModelInfo.iSafeModeEnable == 0)
	//{
	//	SYSTEMTIME st;	
	//	GetLocalTime(&st);
	//	sprintf(m_SaveModelInfo.chBeginTime, "%d.%d.%d_%d", st.wYear, st.wMonth, st.wDay, st.wHour);
	//}
	WritePrivateProfileStringA(m_strIP.c_str(), "SafeModeEnable", chTemp, iniFileName);
	WritePrivateProfileStringA(m_strIP.c_str(), "BeginTime", SaveInfo.chBeginTime, iniFileName);
	WritePrivateProfileStringA(m_strIP.c_str(), "EndTime", SaveInfo.chEndTime, iniFileName);
	memset(chTemp, 0, sizeof(chTemp));
	sprintf(chTemp, "%d", SaveInfo.iIndex);
	WritePrivateProfileStringA(m_strIP.c_str(), "Index", chTemp, iniFileName);
}

bool Camera6467::SaveImgToDisk( char* chImgPath, BYTE* pImgData, DWORD dwImgSize )
{
	WriteLog("begin SaveImgToDisk");
	if(NULL == pImgData)
	{
		WriteLog("end1 SaveImgToDisk");
		return false;
	}
	bool bRet = false;
	size_t iWritedSpecialSize = 0;	
	std::string tempFile(chImgPath);
	size_t iPosition = tempFile.rfind("\\");
	std::string tempDir = tempFile.substr(0, iPosition+1);
	if (MakeSureDirectoryPathExists(tempDir.c_str()))
	{
		FILE* fp = NULL;
		fp = fopen(chImgPath, "wb+");
		if(fp)
		{
			//iWritedSpecialSize = fwrite(pImgData, dwImgSize , 1, fp);
			iWritedSpecialSize = fwrite(pImgData, 1 , dwImgSize, fp);
			fclose(fp);
			fp = NULL;
			bRet = true;
		}
		if (iWritedSpecialSize == dwImgSize)
		{
			char chLogBuff[MAX_PATH] = {0};
			sprintf(chLogBuff, "%s save success", chImgPath);
			WriteLog(chLogBuff);
		}
	}
	else
	{
		char chLogBuff[MAX_PATH] = {0};
		sprintf(chLogBuff, "%s save failed", chImgPath);
		WriteLog(chLogBuff);
		bRet = false;
	}
	WriteLog("end SaveImgToDisk");
	return bRet;
}

bool Camera6467::SaveImgToDisk( char* chImgPath, BYTE* pImgData, DWORD dwImgSize, int iWidth, int iHeight, int iType /*= 0*/ )
{
	//iType 为0时压缩图像，1时不压缩
	if (pImgData == NULL || dwImgSize < 0 || iWidth < 0 || iHeight < 0)
	{
		return false;
	}	
	IStream* pStream = NULL;
	CreateStreamOnHGlobal(NULL, TRUE, &pStream);
	if (NULL == pStream)
	{
		WriteLog("SaveImgToDisk:: Stream 流创建失败. reture false");
		return false;		//流创建失败
	}
	LARGE_INTEGER LiTemp = {0};
	ULARGE_INTEGER ULiZero = {0};
	ULONG ulRealSize = 0;
	pStream->Seek(LiTemp, STREAM_SEEK_SET, NULL);
	pStream->SetSize(ULiZero);

	//将图片写入流中
	pStream->Write(pImgData, dwImgSize, &ulRealSize);
	//创建位图
	Bitmap bmpSrc(pStream);

	Bitmap bmpDest(iWidth, iHeight);
	Graphics grCompress(&bmpDest);
	Rect RCompress(0, 0 , iWidth, iHeight);
	Status statuDraw = grCompress.DrawImage(&bmpSrc, RCompress,0, 0, bmpSrc.GetWidth(), bmpSrc.GetHeight(), UnitPixel);
	if (statuDraw != Ok)
	{
		char chLog[260] = {0};
		sprintf(chLog, "SaveImgToDisk:: DrawImage failed, the error code = %d", statuDraw);
		WriteLog(chLog);

		if (pStream) 
		{
			pStream->Release();
			pStream = NULL;
		}
		return false;
	}
	Status statusDest;
	bool bRet = false;
	if (iType == 0)
	{
		ULONG quality = 50;
		EncoderParameters encoderParameters;
		encoderParameters.Count = 1;
		encoderParameters.Parameter[0].Guid = EncoderQuality;
		encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
		encoderParameters.Parameter[0].NumberOfValues = 1;

		pStream->Seek(LiTemp, STREAM_SEEK_SET, NULL);
		pStream->SetSize(ULiZero);
		encoderParameters.Parameter[0].Value = &quality;
		statusDest = bmpDest.Save(pStream, &m_jpgClsid, &encoderParameters);
		if (statusDest != Ok)
		{
			char chLog[260] = {0};
			sprintf(chLog, "SaveImgToDisk:: failed, the error code = %d", statusDest);
			WriteLog(chLog);

			if (pStream) 
			{
				pStream->Release();
				pStream = NULL;
			}
			return false;
		}

		ULARGE_INTEGER uiLength;
		ULONG iLastSize = 0;
		if (GetStreamLength(pStream, &uiLength))
		{
			iLastSize = (int)uiLength.QuadPart;
		}
		BYTE* pDestImg = NULL;
		if (iLastSize > 0)
		{
			pDestImg = new BYTE[iLastSize];
		}
		pStream->Seek(LiTemp, STREAM_SEEK_SET, NULL);
		if(S_OK != pStream->Read(pDestImg, iLastSize, &iLastSize))
		{
			WriteLog("压缩图片保存失败");

			if (NULL != pDestImg)
			{
				delete[] pDestImg;
				pDestImg = NULL;
			}			
			return false;
		}
		bRet = SaveImgToDisk(chImgPath, pDestImg, iLastSize);
		if (NULL != pDestImg)
		{
			delete[] pDestImg;
			pDestImg = NULL;
		}

		if (pStream) 
		{
			pStream->Release();
			pStream = NULL;
		}
		return bRet;
	}
	else
	{
		wchar_t tempPath[260];
		MultiByteToWideChar(CP_ACP, NULL, chImgPath, 260, tempPath, 260); 
		statusDest = bmpDest.Save(tempPath, &m_bmpClsid);
		if (statusDest ==  Ok)
		{
			bRet = true;
		}
		else
		{
			char chLog[260] = {0};
			sprintf(chLog, "SaveImgToDisk:: Save failed, the error code = %d", statusDest);
			WriteLog(chLog);
		}

		if (pStream) 
		{
			pStream->Release();
			pStream = NULL;
		}
	}
	return bRet;
}

bool Camera6467::SetCameraInfo( CameraInfo& camInfo )
{
	m_strIP = std::string(camInfo.chIP);
	m_strDeviceID = std::string(camInfo.chDeviceID);
	sprintf(m_chDeviceID, "%s", camInfo.chDeviceID);
	sprintf(m_chLaneID, "%s", camInfo.chLaneID);
	sprintf(m_chStationID, "%s", camInfo.chStationID);
	m_bLogEnable = camInfo.bLogEnable;
	m_bSynTime = camInfo.bSynTimeEnable;
	m_iDirection = camInfo.iDirection;

	return true;
}

int Camera6467::GetCamStatus()
{
	if(NULL == m_hHvHandle)
		return 1;
	DWORD dwStatus = 1;

	if ( HVAPI_GetConnStatusEx((HVAPI_HANDLE_EX)m_hHvHandle, CONN_TYPE_RECORD, &dwStatus) == S_OK )
	{
		if (dwStatus == CONN_STATUS_NORMAL
			/*|| dwStatus == CONN_STATUS_RECVDONE*/)
		{
			m_iConnectStatus = 0;
		}
		else if (dwStatus == CONN_STATUS_RECONN)
		{
			m_iConnectStatus = 1;
		}
		else
		{
			m_iConnectStatus = 1;
		}
	}
	else
	{
		m_iConnectStatus = 1;
	}
	return m_iConnectStatus;
}

char* Camera6467::GetStationID()
{
	return m_chStationID;
}

char* Camera6467::GetDeviceID()
{
	return m_chDeviceID;
}

char* Camera6467::GetLaneID()
{
	return m_chLaneID;
}

const char* Camera6467::GetCameraIP()
{
	return m_strIP.c_str();
}

CameraResult* Camera6467::GetOneResult()
{
	CameraResult* tempResult = NULL;
	//EnterCriticalSection(&m_csResult);	
	//if (m_ResultList.size() > 0)
	//{
	//	tempResult = m_ResultList.front();
	//	//m_ResultList.pop_front();
	//}
	//LeaveCriticalSection(&m_csResult);
	//if (NULL != tempResult)
	//{
	//	CTime tm(tempResult->dw64TimeMS/1000);
	//	SaveModeInfo TempSaveModeInfo;
	//	sprintf(TempSaveModeInfo.chBeginTime, "%d.%02d.%02d_%02d", tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour());
	//	WriteHistoryInfo(TempSaveModeInfo);
	//}
	//return tempResult;
	
	EnterCriticalSection(&m_csResult);
	if (NULL != m_BufferResult && m_bResultComplete)
	{
		tempResult = new CameraResult(*m_BufferResult);
		m_bResultComplete = false;
	}
	LeaveCriticalSection(&m_csResult);
	return tempResult;
}

bool Camera6467::ConnectToCamera()
{
	if(m_strIP.empty())
	{
		WriteLog("ConnectToCamera:: please finish the camera ip address");
		return false;
	}
	if(NULL != m_hHvHandle)
	{
		HVAPI_CloseEx((HVAPI_HANDLE_EX)m_hHvHandle);
		m_hHvHandle = NULL;
	}
	m_hHvHandle = HVAPI_OpenEx(m_strIP.c_str(), NULL);
	//m_hHvHandle = HVAPI_OpenChannel(m_strIP.c_str(), NULL, 0);
	if(NULL == m_hHvHandle)
	{
		WriteLog("ConnectToCamera:: Open CameraHandle failed!");
		return false;
	}

	ReadHistoryInfo();
	char chCommand[1024] = {0};
	sprintf(chCommand, "DownloadRecord,BeginTime[%s],Index[%d],Enable[%d],EndTime[%s],DataInfo[%d]", m_SaveModelInfo.chBeginTime, m_SaveModelInfo.iIndex, m_SaveModelInfo.iSafeModeEnable, m_SaveModelInfo.chEndTime, m_SaveModelInfo.iDataType);
	
	WriteLog(chCommand);

	if ( (HVAPI_SetCallBackEx(m_hHvHandle, (PVOID)RecordInfoBeginCallBack, this, 0, CALLBACK_TYPE_RECORD_INFOBEGIN, /*NULL*/chCommand) != S_OK) ||
		(HVAPI_SetCallBackEx(m_hHvHandle, (PVOID)RecordInfoPlateCallBack, this, 0, CALLBACK_TYPE_RECORD_PLATE, /*NULL*/chCommand) != S_OK) ||
		(HVAPI_SetCallBackEx(m_hHvHandle, (PVOID)RecordInfoBigImageCallBack, this, 0, CALLBACK_TYPE_RECORD_BIGIMAGE, /*NULL*/chCommand) != S_OK) ||
		(HVAPI_SetCallBackEx(m_hHvHandle, (PVOID)RecordInfoSmallImageCallBack, this, 0, CALLBACK_TYPE_RECORD_SMALLIMAGE, /*NULL*/chCommand) != S_OK) ||
		(HVAPI_SetCallBackEx(m_hHvHandle, (PVOID)RecordInfoBinaryImageCallBack, this, 0, CALLBACK_TYPE_RECORD_BINARYIMAGE, /*NULL*/chCommand) != S_OK) ||
		(HVAPI_SetCallBackEx(m_hHvHandle, (PVOID)RecordInfoEndCallBack, this, 0, CALLBACK_TYPE_RECORD_INFOEND, /*NULL*/chCommand) != S_OK)
		)
	{		
		WriteLog("ConnectToCamera:: SetCallBack failed.");
		HVAPI_CloseEx(m_hHvHandle);
		m_hHvHandle = NULL;
		m_dwConnectStatus = -1;
		return false;
	}
	else
	{
		m_dwConnectStatus = 0;
		WriteLog("ConnectToCamera:: SetCallBack success.");
	}

	return true;
}

void Camera6467::ReadConfig()
{
	char FileName[MAX_PATH];
	GetModuleFileNameA(NULL, FileName, MAX_PATH-1);

	PathRemoveFileSpecA(FileName);
	char iniFileName[MAX_PATH] = {0};
	char iniDeviceInfoName[MAX_PATH] = {0};
	strcat(iniFileName, FileName);
	strcat(iniFileName,"\\FouthHWYDll_XLW.ini");

	//读取可靠性配置文件
	int iLog =  GetPrivateProfileIntA("Log", "Enable", 1, iniFileName);
	m_bLogEnable = (iLog==1 ) ? true : false;	

	int iSaveBuffer =  GetPrivateProfileIntA("SaveBuffer", "Enable", 0, iniFileName);
	m_bSaveToBuffer = (iSaveBuffer==1 ) ? true : false;	

	char chTemp[256] = {0};
	sprintf(chTemp, "%d", iLog);

	WritePrivateProfileStringA("Log", "Enable", chTemp, iniFileName);
}

bool Camera6467::WriteLog( const char* chlog )
{
	if(!m_bLogEnable || NULL == chlog)
		return false;

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
	sprintf(chLogPath, "%s\\XLWLog\\%04d-%02d-%02d\\%s\\",  szFileName, pTM->tm_year + 1900, pTM->tm_mon+1, pTM->tm_mday, m_strIP.c_str());
	MakeSureDirectoryPathExists(chLogPath);

	//每次只保留10天以内的日志文件
	CTime tmCurrentTime = CTime::GetCurrentTime();
	CTime tmLastMonthTime = tmCurrentTime - CTimeSpan(10, 0, 0, 0);
	int Last_Year = tmLastMonthTime.GetYear() ;
	int Last_Month = tmLastMonthTime.GetMonth();
	int Last_Day = tmLastMonthTime.GetDay();

	char chOldLogFileName[MAXPATH] = {0};
	sprintf(chOldLogFileName, "%s\\XLWLog\\%04d-%02d-%02d\\",szFileName, Last_Year, Last_Month, Last_Day);
	if (PathFileExists(chOldLogFileName))
	{
		char chCommand[512] = {0};
		sprintf(chCommand, "/c rd /s/q %s", chOldLogFileName);
		ExcuteCMD(chCommand);
	}

	char chLogFileName[512] = {0};
	sprintf(chLogFileName, "%s\\CameraLog-%d-%02d_%02d.log",chLogPath, pTM->tm_year + 1900, pTM->tm_mon+1, pTM->tm_mday);

	EnterCriticalSection(&m_csLog);

	FILE *file = NULL;
	file = fopen(chLogFileName, "a+");
	if (file)
	{
		fprintf(file,"%04d-%02d-%02d %02d:%02d:%02d:%03d : %s\n",  pTM->tm_year + 1900, pTM->tm_mon+1, pTM->tm_mday,
			pTM->tm_hour, pTM->tm_min, pTM->tm_sec, dwMS, chlog);
		fclose(file);
		file = NULL;
	}

	LeaveCriticalSection(&m_csLog);


	return true;
}

bool Camera6467::TakeCapture()
{
	if (NULL == m_hHvHandle)
		return false;

	bool bRet = true;
	char chRetBuf[1024] = {0};
	int nRetLen = 0;

	if (HVAPI_ExecCmdEx(m_hHvHandle, "SoftTriggerCapture", chRetBuf, 1024, &nRetLen) != S_OK)
	{
		bRet = false;
		char chCaptureLog3[MAX_PATH] = {0};
		sprintf(chCaptureLog3, "Camera: %s SoftTriggerCapture failed", m_strIP.c_str());
		WriteLog(chCaptureLog3);
	}
	else
	{
		char chCaptureLog4[MAX_PATH] = {0};
		sprintf(chCaptureLog4, "Camera: %s SoftTriggerCapture success", m_strIP.c_str());
		WriteLog(chCaptureLog4);
	}
	m_bResultComplete = false;
	return bRet;
}

bool Camera6467::SynTime()
{
	if (NULL == m_hHvHandle || m_dwConnectStatus != 0)
		return false;
	if (!m_bSynTime)
	{
		return false;
	}
	WriteLog("SynTime begin");

	static time_t starttime = time(NULL);
	static DWORD starttick = GetTickCount(); 
	DWORD dwNowTick = GetTickCount() - starttick;
	time_t nowtime = starttime + (time_t)(dwNowTick / 1000);
	struct tm *pTM = localtime(&nowtime);
	DWORD dwMS = dwNowTick % 1000;

	char chTemp[256]={ 0 };
	sprintf(chTemp, "SetTime,Date[%d.%02d.%02d],Time[%02d:%02d:%02d]",
		pTM->tm_year + 1900,  pTM->tm_mon, pTM->tm_mday,
		pTM->tm_hour, pTM->tm_min, pTM->tm_sec);
	WriteLog(chTemp);
	char szRetBuf[1024] = {0};
	int nRetLen = 0;
	if (m_hHvHandle != NULL)
	{
		try
		{
			if (HVAPI_ExecCmdEx(m_hHvHandle, chTemp, szRetBuf, 1024, &nRetLen) != S_OK)
			{
				char chSynTimeLogBuf1[MAX_PATH] = {0};
				sprintf(chSynTimeLogBuf1, "Camera: %s SynTime failed", m_strIP.c_str());
				WriteLog(chSynTimeLogBuf1);
				return false;
			}
			else
			{
				char chSynTimeLogBuf2[MAX_PATH] = {0};
				sprintf(chSynTimeLogBuf2, "Camera: %s SynTime success", m_strIP.c_str());
				WriteLog(chSynTimeLogBuf2);
			}
		} catch (...)
		{
			char chSynTimeLogBuf3[MAX_PATH] = {0};
			sprintf(chSynTimeLogBuf3, "Camera: %s SynTime take exception", m_strIP.c_str());
			WriteLog(chSynTimeLogBuf3);
		}
	}
	WriteLog("SynTime end");
	return 0;
}

bool Camera6467::SynTime( int Year, int Month, int Day, int Hour, int Minute, int Second, int MilientSecond )
{
	if (NULL == m_hHvHandle || m_dwConnectStatus != 0)
		return false;
	if (!m_bSynTime)
	{
		return false;
	}
	if (abs(Month) > 12 || abs(Day) > 31 || abs(Hour) > 24 || abs(Minute) > 60 || abs(Second) > 60)
	{
		WriteLog("SynTime  failed: time value is invalid.");
		return false;
	}
	WriteLog("SynTime begin");

	
	char chTemp[256]={ 0 };
	sprintf(chTemp, "SetTime,Date[%d.%02d.%02d],Time[%02d:%02d:%02d]",
		abs(Year),  abs(Month), abs(Day),
		abs(Hour), abs(Minute), abs(Second));
	WriteLog(chTemp);
	char szRetBuf[1024] = {0};
	int nRetLen = 0;
	if (m_hHvHandle != NULL)
	{
		try
		{
			if (HVAPI_ExecCmdEx(m_hHvHandle, chTemp, szRetBuf, 1024, &nRetLen) != S_OK)
			{
				char chSynTimeLogBuf1[MAX_PATH] = {0};
				sprintf(chSynTimeLogBuf1, "Camera: %s SynTime failed", m_strIP.c_str());
				WriteLog(chSynTimeLogBuf1);
				return false;
			}
			else
			{
				char chSynTimeLogBuf2[MAX_PATH] = {0};
				sprintf(chSynTimeLogBuf2, "Camera: %s SynTime success", m_strIP.c_str());
				WriteLog(chSynTimeLogBuf2);
			}
		} catch (...)
		{
			char chSynTimeLogBuf3[MAX_PATH] = {0};
			sprintf(chSynTimeLogBuf3, "Camera: %s SynTime take exception", m_strIP.c_str());
			WriteLog(chSynTimeLogBuf3);
		}
	}
	WriteLog("SynTime end");
	return true;
}

void Camera6467::AnalysisAppendInfo( CameraResult* record )
{
	if (strstr(record->chPlateNO, "无车牌"))
	{
		record->iPlateColor = 0;
		record->iPlateTypeNo=0;
	}
	else
	{
		char tmpPlateColor[20] = {0};
		strncpy(tmpPlateColor, record->chPlateNO,2);
		strncpy(record->chPlateColor, record->chPlateNO,2);
		if (strstr(tmpPlateColor, "蓝"))
		{
			record->iPlateColor = 3;
			record->iPlateTypeNo=2;
		}
		else if (strstr(tmpPlateColor, "黄"))
		{
			record->iPlateColor = 2;
			record->iPlateTypeNo=1;
		}
		else if (strstr(tmpPlateColor, "黑"))
		{
			record->iPlateColor = 4;
			record->iPlateTypeNo=3;
		}
		else if (strstr(tmpPlateColor, "白"))
		{
			record->iPlateColor = 1;
			record->iPlateTypeNo=6;
		}
        else if (strstr(tmpPlateColor, "绿"))
        {
            record->iPlateColor = 5;
            record->iPlateTypeNo=6;
            memset(record->chPlateColor, '\0', sizeof(record->chPlateColor));
            char tmpPlate[32] = {0};
            strcpy(tmpPlate, record->chPlateNO);
            int len = 0;
            len = strlen(tmpPlate);
            if(tmpPlate[len - 1] == 'D' || tmpPlate[len - 1] == 'F')
            {                
                strcpy(record->chPlateColor,"黄绿");
                //sprintf(pCtrl->m_Result.pchPlate, "%s%s", "黄绿双拼", tmpPlate);
            }
            else
            {
                strcpy(record->chPlateColor,"白绿");
                //sprintf(pCtrl->m_Result.pchPlate, "%s%s", "渐变绿", tmpPlate);
            }
        }
		else
		{
			record->iPlateColor = 0;
			record->iPlateTypeNo=0;
		}
		//获取车牌号
		char sztempPlate[20] = {0};
		sprintf(sztempPlate, "%s", record->chPlateNO + 2);
		//sprintf(sztempPlate, "%s", record->chPlateNO);
		if (strlen(sztempPlate) > 0)
		{
			memset(record->chPlateNO, 0, sizeof(record->chPlateNO));
			sprintf(record->chPlateNO,"%s",sztempPlate);
		}
	}
	char * pchObj = NULL;
	pchObj = (char *)strstr(record->pcAppendInfo, "车道");
	if (pchObj)
	{
		sscanf(pchObj, "车道:%d", &(record->iLaneNo));
	}
	else
	{
		record->iLaneNo = 0;
	}
	pchObj = (char *)strstr(record->pcAppendInfo, "路口方向");
	if (pchObj)
	{
		sscanf(pchObj, "路口方向:%d", &(record->iDirection));
	}
	else
	{
		record->iDirection = 0;
	}
	if (0 != record->dw64TimeMS)
	{
		CTime tm(record->dw64TimeMS/1000);
		sprintf(record->chPlateTime, "%04d%02d%02d%02d%02d%02d%03d", tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond(), record->dw64TimeMS%1000);
	}
	else
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		sprintf(record->chPlateTime, "%04d%02d%02d%02d%02d%02d%03d", st.wYear, st.wMonth, st.wDay	,st.wHour, st.wMinute,st.wSecond, st.wMilliseconds);
	}

	//------------车道
	pchObj = (char*)strstr(record->pcAppendInfo, "车辆类型");
	if(pchObj)
	{
		char szCarType[20] = {0};
		sscanf(pchObj, "车辆类型:%s", szCarType);
		if (strstr(szCarType,"大"))
		{
			record->iVehTypeNo=2;
		}
		if (strstr(szCarType,"中"))
		{
			record->iVehTypeNo=2;
		}
		if (strstr(szCarType,"小"))
		{
			record->iVehTypeNo=1;
		}
		if(strstr(szCarType,"客车"))
		{
			record->iVehTypeNo=1;
		}
		if(strstr(szCarType,"货车"))
		{
			record->iVehTypeNo=2;
		}
		if(strstr(szCarType,"牵引车"))
		{
			record->iVehTypeNo=3;
		}
		if(strstr(szCarType,"专项作业车"))
		{
			record->iVehTypeNo=4;
		}
		if(strstr(szCarType,"电车"))
		{
			record->iVehTypeNo=5;
		}
		if(strstr(szCarType,"摩托车"))
		{
			record->iVehTypeNo=6;
		}
		if(strstr(szCarType,"三轮汽车"))
		{
			record->iVehTypeNo=7;
		}
		if(strstr(szCarType,"拖拉机"))
		{
			record->iVehTypeNo=8;
		}
		if(strstr(szCarType,"轮式机械"))
		{
			record->iVehTypeNo=9;
		}
		if(strstr(szCarType,"全挂车"))
		{
			record->iVehTypeNo=10;
		}
		if(strstr(szCarType,"半挂车"))
		{
			record->iVehTypeNo=11;
		}
		if(strstr(szCarType,"其他"))
		{
			record->iVehTypeNo=12;
		}
	}	

	//---------------车身颜色
	pchObj= (char*)strstr(record->pcAppendInfo,"车身颜色:");

	record->iVehBodyColorNo=0;
	if(pchObj)
	{
		char szBodyColour[256]={0};
		sscanf(pchObj,"车身颜色:%s",szBodyColour);
		if(strstr(szBodyColour,"白"))
			record->iVehBodyColorNo=1;

		if(strstr(szBodyColour,"灰"))
			record->iVehBodyColorNo=2;

		if(strstr(szBodyColour,"黄"))
			record->iVehBodyColorNo=3;

		if(strstr(szBodyColour,"粉"))
			record->iVehBodyColorNo=4;

		if(strstr(szBodyColour,"红"))
			record->iVehBodyColorNo=5;

		if(strstr(szBodyColour,"紫"))
			record->iVehBodyColorNo=6;

		if(strstr(szBodyColour,"绿"))
			record->iVehBodyColorNo=7;

		if(strstr(szBodyColour,"蓝"))
			record->iVehBodyColorNo=8;

		if(strstr(szBodyColour,"棕"))
			record->iVehBodyColorNo=9;

		if(strstr(szBodyColour,"黑"))
			record->iVehBodyColorNo=10;
	}

	//---------车身深浅度
	pchObj = (char*)(strstr(record->pcAppendInfo,"深浅度:"));
	if(pchObj)
	{
		char szBodyColourDeep[256]={0};
		sscanf(pchObj,"深浅度:%s",szBodyColourDeep);

		if(strstr(szBodyColourDeep,"深"))
			record->iVehBodyDeepNo=1;

		if(strstr(szBodyColourDeep,"浅"))
			record->iVehBodyDeepNo=0;
	}
	//--------------------测速
	pchObj = (char*)(strstr(record->pcAppendInfo,"测速:"));
	if(pchObj)
	{
		int iCarSpeed = 0;
		sscanf(pchObj,"测速:%d Km/h",&iCarSpeed);
		record->iSpeed = iCarSpeed;
	}
	//--------------车型----------------------------
	pchObj = (char*)(strstr(record->pcAppendInfo,"车型:"));
	if(pchObj)
	{
		char chTemp[128] = {0};
		sscanf(pchObj,"车型:%s",chTemp);
		if (strstr(chTemp, "客1"))
		{
			record->iVehTypeNo = 1;
		}
		else if (strstr(chTemp, "客2"))
		{
			record->iVehTypeNo = 2;
		}
		else if (strstr(chTemp, "客3"))
		{
			record->iVehTypeNo = 3;
		}
		else if (strstr(chTemp, "客4"))
		{
			record->iVehTypeNo = 4;
		}
		else if (strstr(chTemp, "货1"))
		{
			record->iVehTypeNo = 5;
		}
		else if (strstr(chTemp, "货2"))
		{
			record->iVehTypeNo = 6;
		}
		else if (strstr(chTemp, "货3"))
		{
			record->iVehTypeNo = 7;
		}
		else if (strstr(chTemp, "货4"))
		{
			record->iVehTypeNo = 8;
		}
		char chLog[260] = {0};
		sprintf(chLog, "iVehTypeNo= %d", record->iVehTypeNo);
		WriteLog(chLog);
	}
	//--------------轮数----------------------------
	pchObj = (char*)(strstr(record->pcAppendInfo,"轮数:"));
	if(pchObj)
	{
		int iTemp = 0;
		sscanf(pchObj, "轮数:%d", &iTemp);
		record->iWheelCount = iTemp;

		char chLog[260] = {0};
		sprintf(chLog, "iWheelCount= %d", record->iWheelCount);
		WriteLog(chLog);
	}
	//--------------轴数----------------------------
	pchObj = (char*)(strstr(record->pcAppendInfo,"轴数:"));
	if(pchObj)
	{
		int iTemp = 0;
		sscanf(pchObj, "轴数:%d", &iTemp);
		record->iAxletreeCount = iTemp;

		char chLog[260] = {0};
		sprintf(chLog, "iAxletreeCount= %d", record->iAxletreeCount);
		WriteLog(chLog);
	}
	//--------------轴距----------------------------
	pchObj = (char*)(strstr(record->pcAppendInfo,"轴距:"));
	if(pchObj)
	{
		float fTemp = 0.0;
		sscanf(pchObj, "轴距:%f", &fTemp);
		record->fDistanceBetweenAxles = fTemp;

		char chLog[260] = {0};
		sprintf(chLog, "fDistanceBetweenAxles= %f", record->fDistanceBetweenAxles);
		WriteLog(chLog);
	}
	//--------------车长----------------------------
	pchObj = (char*)(strstr(record->pcAppendInfo,"车长:"));
	if(pchObj)
	{
		float fTemp = 0.0;
		sscanf(pchObj, "车长:%f", &fTemp);
		record->fVehLenth = fTemp;

		char chLog[260] = {0};
		sprintf(chLog, "fVehLenth= %f", record->fVehLenth);
		WriteLog(chLog);
	}
	//--------------车高----------------------------
	pchObj = (char*)(strstr(record->pcAppendInfo,"车高:"));
	if(pchObj)
	{
		float fTemp = 0.0;
		sscanf(pchObj, "车高:%f", &fTemp);
		record->fVehHeight = fTemp;

		char chLog[260] = {0};
		sprintf(chLog, "fVehHeight= %f", record->fVehHeight);
		WriteLog(chLog);
	}

}

int Camera6467::RecordInfoBegin( DWORD dwCarID )
{
	char chlogInfo[260] = {0};
	sprintf(chlogInfo, "RecordInfoBegin -begin- dwCarID = %d", dwCarID);
	WriteLog(chlogInfo);
	if (dwCarID == m_dwLastCarID)
	{
		WriteLog("相同carID,丢弃该结果");
		return 0;
	}
	EnterCriticalSection(&m_csResult);
	m_bResultComplete = false;
	LeaveCriticalSection(&m_csResult);
	if(NULL != m_CameraResult)
	{
		delete m_CameraResult;
		m_CameraResult = NULL;
	}
	m_CameraResult = new CameraResult();
	sprintf(m_CameraResult->chDeviceIp, "%s", m_strIP.c_str());
	m_CameraResult->dwCarID = dwCarID;
	char chlogInfo2[260] = {0};
	sprintf(chlogInfo2, "RecordInfoBegin -end- dwCarID = %d", dwCarID);
	WriteLog(chlogInfo2);
	return 0;
}

int Camera6467::RecordInfoEnd( DWORD dwCarID )
{
	char chLog[260] = {0};
	sprintf(chLog, "RecordInfoEnd begin, dwCarID = %d", dwCarID);
	WriteLog(chLog);
	if (dwCarID != m_dwLastCarID)
	{
		m_dwLastCarID = dwCarID;
	}
	else
	{
		WriteLog("相同CarID, 丢弃该结果");
		return 0;
	}

	if (NULL == m_CameraResult)
	{
		return 0;
	}

	CTime tm(m_CameraResult->dw64TimeMS/1000);
	SaveModeInfo TempSaveModeInfo;
	sprintf(TempSaveModeInfo.chBeginTime, "%d.%02d.%02d_%02d", tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour());
	WriteHistoryInfo(TempSaveModeInfo);

	if (m_bSaveToBuffer)
	{
		SaveResultToBuffer(m_CameraResult);
	}
	
	//EnterCriticalSection(&m_csResult);	
	//if (m_ResultList.size() < 100)
	//{
	//	char chLogList[260] = {0};
	//	sprintf(chLogList, "now the size is %d, put one result in list.", m_ResultList.size());
	//	WriteLog(chLogList);
	//	m_ResultList.push_back(m_CameraResult);
	//	LeaveCriticalSection(&m_csResult);
	//}
	//else
	//{
	//	LeaveCriticalSection(&m_csResult);
	//	//todo 将结果缓存的本地缓存目录
	//	//SaveResultToBuffer(m_CameraResult);

	//	delete m_CameraResult;
	//	//WriteLog("The list is full , save the result to buffer path.");
	//	WriteLog("The list is full , delete the result.");
	//}
	//m_CameraResult = NULL;

	EnterCriticalSection(&m_csResult);
	if (NULL != m_BufferResult)
	{
		delete m_BufferResult;
		m_BufferResult = NULL;
	}
	m_BufferResult = new CameraResult(*m_CameraResult);

	m_bResultComplete = true;
	LeaveCriticalSection(&m_csResult);

	if (NULL != m_hWnd)
	{
		WriteLog("PostMessage");
		::PostMessage(*((HWND*)m_hWnd),m_iMsg, 1,(LPARAM)m_hHvHandle);
	}

	char chLog2[260] = {0};
	sprintf(chLog2, "RecordInfoEnd end, dwCarID = %d", dwCarID);
	WriteLog(chLog2);
	return 0;
}

int Camera6467::RecordInfoPlate( DWORD dwCarID, LPCSTR pcPlateNo, LPCSTR pcAppendInfo, DWORD dwRecordType, DWORD64 dw64TimeMS )
{
	//m_bResultComplete = false;

	if (NULL == m_CameraResult)
	{
		return -1;
	}
	char chlogInfo[260] = {0};
	sprintf(chlogInfo, "RecordInfoPlate -begin- dwCarID = %d", dwCarID);
	WriteLog(chlogInfo);
	if (dwCarID == m_dwLastCarID)
	{
		WriteLog("相同carID,丢弃该结果");
		return 0;
	}

	if (m_CameraResult->dwCarID == dwCarID)
	{
		m_CameraResult->dw64TimeMS = dw64TimeMS;
		sprintf(m_CameraResult->chPlateNO, "%s",pcPlateNo);
		//sprintf(m_CameraResult->chPlateNO, "%s",pcPlateNo+3);
		memset(m_CameraResult->pcAppendInfo, 0, sizeof(m_CameraResult->pcAppendInfo));
		HVAPIUTILS_ParsePlateXmlStringEx(pcAppendInfo, m_CameraResult->pcAppendInfo, 2048);
		WriteLog(m_CameraResult->chPlateNO);
		WriteLog(m_CameraResult->pcAppendInfo);
		AnalysisAppendInfo(m_CameraResult);

		char qstrPlateTime[260] = {0};
		sprintf(qstrPlateTime, "the plate time is %s, %lld", m_CameraResult->chPlateTime, dw64TimeMS);
		WriteLog(qstrPlateTime);
	}
	char chlogInfo2[260] = {0};
	sprintf(chlogInfo2, "RecordInfoPlate -end- dwCarID = %d", dwCarID);
	WriteLog(chlogInfo2);
	return 0;
}

int Camera6467::RecordInfoBigImage( DWORD dwCarID, WORD wImgType, WORD wWidth, WORD wHeight, PBYTE pbPicData, DWORD dwImgDataLen, DWORD dwRecordType, DWORD64 dw64TimeMS )
{
	//m_bResultComplete = false;

	if (NULL == m_CameraResult)
	{
		return -1;
	}
	char chlogInfo[260] = {0};
	sprintf(chlogInfo, "RecordInfoBigImage -begin- dwCarID = %ld, dwRecordType = %#x， ImgType=%d", dwCarID,  dwRecordType, wImgType);
	WriteLog(chlogInfo);
	if (dwCarID == m_dwLastCarID)
	{
		WriteLog("相同carID,丢弃该结果");
		return 0;
	}
	if (m_CameraResult->dwCarID == dwCarID)
	{
		if (wImgType == RECORD_BIGIMG_BEST_SNAPSHOT)
		{
			WriteLog("RecordInfoBigImage BEST_SNAPSHO  ");

			CopyDataToIMG(m_CameraResult->CIMG_BestSnapshot, pbPicData, wWidth, wHeight, dwImgDataLen, wImgType);
		}
		else if (wImgType == RECORD_BIGIMG_LAST_SNAPSHOT)
		{
			WriteLog("RecordInfoBigImage LAST_SNAPSHOT  ");

			CopyDataToIMG(m_CameraResult->CIMG_LastSnapshot, pbPicData, wWidth, wHeight, dwImgDataLen, wImgType);
		}
		else if (wImgType == RECORD_BIGIMG_BEGIN_CAPTURE)
		{
			WriteLog("RecordInfoBigImage BEGIN_CAPTURE  ");

			CopyDataToIMG(m_CameraResult->CIMG_BeginCapture, pbPicData, wWidth, wHeight, dwImgDataLen, wImgType);
		}
		else if (wImgType == RECORD_BIGIMG_BEST_CAPTURE)
		{
			WriteLog("RecordInfoBigImage BEST_CAPTURE  ");

			CopyDataToIMG(m_CameraResult->CIMG_BestCapture, pbPicData, wWidth, wHeight, dwImgDataLen, wImgType);
		}
		else if (wImgType == RECORD_BIGIMG_LAST_CAPTURE)
		{
			WriteLog("RecordInfoBigImage LAST_CAPTURE  ");

			CopyDataToIMG(m_CameraResult->CIMG_LastCapture, pbPicData, wWidth, wHeight, dwImgDataLen, wImgType);
		}
		else
		{
			WriteLog("RecordInfoBigImage other Img, put it to  LAST_CAPTURE .");
			CopyDataToIMG(m_CameraResult->CIMG_LastCapture, pbPicData, wWidth, wHeight, dwImgDataLen, wImgType);
		}
	}
	char chlogInfo2[260] = {0};
	sprintf(chlogInfo2, "RecordInfoBigImage -end- dwCarID = %d",dwCarID);
	WriteLog(chlogInfo2);
	return 0;
}

int Camera6467::RecordInfoSmallImage( DWORD dwCarID, WORD wWidth, WORD wHeight, PBYTE pbPicData, DWORD dwImgDataLen, DWORD dwRecordType, DWORD64 dw64TimeMS )
{
	//m_bResultComplete = false;
	if (NULL == m_CameraResult)
	{
		return -1;
	}
	char chlogInfo[260] = {0};
	sprintf(chlogInfo, "RecordInfoSmallImage  -begin- dwCarID = %d", dwCarID);
	WriteLog(chlogInfo);
	if (dwCarID == m_dwLastCarID)
	{
		WriteLog("相同carID,丢弃该结果");
		return 0;
	}

	int iBuffLen = 1024 * 1024;
	if (m_CameraResult->dwCarID == dwCarID)
	{
		if (NULL != m_CameraResult->CIMG_PlateImage.pbImgData)
		{
			delete[] m_CameraResult->CIMG_PlateImage.pbImgData;
			m_CameraResult->CIMG_PlateImage.pbImgData = NULL;
		}
		m_CameraResult->CIMG_PlateImage.pbImgData = new BYTE[iBuffLen];
		WriteLog("RecordInfoSmallImage 内存申请.");
		if (m_CameraResult->CIMG_PlateImage.pbImgData != NULL)
		{
			WriteLog("RecordInfoSmallImage 内存申请成功.");
			memset(m_CameraResult->CIMG_PlateImage.pbImgData, 0 ,iBuffLen);
			HRESULT Hr = HVAPIUTILS_SmallImageToBitmapEx(pbPicData,
				wWidth,
				wHeight,
				m_CameraResult->CIMG_PlateImage.pbImgData,
				&iBuffLen);
			if ( Hr == S_OK)
			{
				m_CameraResult->CIMG_PlateImage.wImgWidth = wWidth;
				m_CameraResult->CIMG_PlateImage.wImgHeight = wHeight;
				m_CameraResult->CIMG_PlateImage.dwImgSize = iBuffLen;
			}
			else
			{
				WriteLog("HVAPIUTILS_SmallImageToBitmapEx 失败.");
			}
		}
		else
		{
			WriteLog("RecordInfoSmallImage 内存申请失败.");
		}
	}
	char chlogInfo2[260] = {0};
	sprintf(chlogInfo2, "RecordInfoSmallImage  -end- dwCarID = %d", dwCarID);	
	WriteLog(chlogInfo2);
	return 0;
}

int Camera6467::RecordInfoBinaryImage( DWORD dwCarID, WORD wWidth, WORD wHeight, PBYTE pbPicData, DWORD dwImgDataLen, DWORD dwRecordType, DWORD64 dw64TimeMS )
{
	//m_bResultComplete = false;

	if (NULL == m_CameraResult)
	{
		return -1;
	}
	char chlogInfo[260] = {0};
	sprintf(chlogInfo, "RecordInfoBinaryImage -begin- dwCarID = %d", dwCarID);
	WriteLog(chlogInfo);

	if (dwCarID == m_dwLastCarID)
	{
		WriteLog("相同carID,丢弃该结果");
		return 0;
	}

	if (m_CameraResult->dwCarID == dwCarID)
	{
		unsigned char pbSourceBinImage[BIN_BYTE_COUNT] = {0};
		unsigned char pbByteBinImage[BIN_BYTE_COUNT] = {0};
		if (dwImgDataLen <= BIN_BYTE_COUNT)
		{
			WriteLog("针对汉高的要求，转换二值图");
			memcpy(pbSourceBinImage, pbPicData, dwImgDataLen);
			RgbBin2ByteBin(pbSourceBinImage, pbByteBinImage);

			CopyDataToIMG(m_CameraResult->CIMG_BinImage, pbByteBinImage, wWidth, wHeight, dwImgDataLen, 0);
		}
		else
		{
			WriteLog("长度不符合二值图要求，不转换，直接给原图");
			CopyDataToIMG(m_CameraResult->CIMG_BinImage, pbPicData, wWidth, wHeight, dwImgDataLen, 0);
		}		
	}
	char chlogInfo2[260] = {0};
	sprintf(chlogInfo2, "RecordInfoBinaryImage -end- dwCarID = %d", dwCarID);
	WriteLog(chlogInfo2);
	return 0;
}

void Camera6467::SetResultToUnready()
{
	m_bResultComplete = false;
}

bool Camera6467::GetDeviceTime( DeviceTime& deviceTime )
{
	if (NULL == m_hHvHandle)
		return false;
	
	char chRetBuf[1024] = {0};
	int nRetLen = 0;

	if (HVAPI_ExecCmdEx(m_hHvHandle, "DateTime", chRetBuf, 1024, &nRetLen) != S_OK)
	{
		WriteLog("GetDeviceTime:: failed.");
		return false;
	}
	WriteLog(chRetBuf);
	bool bRet = false;
	const char* chFileName = "./DateTime.xml";
	DeleteFileA(chFileName);

	FILE* file_L = fopen(chFileName, "wb");
	if(file_L)
	{
		size_t size_Read =  fwrite(chRetBuf, 1, nRetLen, file_L);		
		fclose(file_L);
		file_L = NULL;
		char chFileLog[260] = {0};
		sprintf(chFileLog, "GetDeviceTime:: DateTime.xml create success, size =%d ", size_Read);
		WriteLog(chFileLog);
		bRet = true;
	}
	if (!bRet)
	{
		WriteLog("GetDeviceTime:: DateTime.xml create failed.");
		return false;
	}

	const char* pDate = NULL;
	const char* pTime = NULL;
	TiXmlDocument cXmlDoc;
	//    if(cXmlDoc.Parse(chRetBuf))
	if(cXmlDoc.LoadFile(chFileName))
	{
		TiXmlElement* pSectionElement = cXmlDoc.RootElement();
		if(pSectionElement)
		{
			TiXmlElement* pChileElement = pSectionElement->FirstChildElement();
			pDate = pChileElement->Attribute("Date");
			pTime = pChileElement->Attribute("Time");
		}
		else
		{
			WriteLog("find Root element failed.");
		}
	}
	else
	{
		WriteLog("parse failed");
	}
	int iYear = 0, iMonth = 0, iDay = 0, iHour = 0, iMinute = 0, iSecond = 0, iMiliSecond = 0;
	sscanf(pDate, "%04d.%02d.%02d", &iYear, &iMonth, &iDay);
	sscanf(pTime, "%02d:%02d:%02d %03d", &iHour, &iMinute, &iSecond, &iMiliSecond);

	deviceTime.iYear =iYear;
	deviceTime.iMonth =iMonth;
	deviceTime.iDay =iDay;
	deviceTime.iHour =iHour;
	deviceTime.iMinutes =iMinute;
	deviceTime.iSecond =iSecond;
	deviceTime.iMilisecond =iMiliSecond;

	return true;
}

int Camera6467::GetEncoderClsid( const WCHAR* format, CLSID* pClsid )
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if(size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}    
	}
	free(pImageCodecInfo);
	return -1;  // Failure
}

bool Camera6467::GetStreamLength( IStream* pStream, ULARGE_INTEGER* puliLenth )
{
	if (pStream == NULL)
		return false;

	LARGE_INTEGER liMov;
	liMov.QuadPart = 0;

	ULARGE_INTEGER uliEnd, uliBegin;

	HRESULT hr = S_FALSE;

	hr = pStream->Seek(liMov, STREAM_SEEK_END, &uliEnd);
	if (FAILED(hr))
		return false;

	hr = pStream->Seek(liMov, STREAM_SEEK_SET, &uliBegin);
	if (FAILED(hr))
		return false;

	// 差值即是流的长度
	puliLenth->QuadPart = uliEnd.QuadPart - uliBegin.QuadPart;

	return TRUE;
}

void Camera6467::SaveResultToBuffer( CameraResult* pResult )
{
	if (NULL == pResult)
	{
		return;
	}
	//将图片缓存到缓存目录
	long dwPlateTime = 0;
	//char chBigImgFileName[260] = {0};
	//char chBinImgFileName[260] = {0};
	char chPlateColor[32] = {0};

	dwPlateTime = pResult->dw64TimeMS/1000;
	if (strstr(pResult->chPlateNO, "无"))
	{
		sprintf(chPlateColor, "无");
	}
	else
	{
		sprintf(chPlateColor, "%s", pResult->chPlateColor);
	}

	TCHAR szFileName[260] = {0};
	GetModuleFileName(NULL, szFileName, 260);	//取得包括程序名的全路径
	PathRemoveFileSpec(szFileName);				//去掉程序名	
	
	//构造文件名称，格式： Unix时间-车牌号-车牌颜色
	//二值图
	sprintf(pResult->CIMG_BinImage.chSavePath,"%s\\Buffer\\%s\\%d-%s-%s-%s-车型%d-车轴%d-%d-bin.bin", szFileName, m_strIP.c_str(), dwPlateTime, pResult->chPlateNO, chPlateColor, pResult->chPlateTime, pResult->iVehTypeNo, pResult->iAxletreeCount, pResult->dwCarID);
	//车牌图
	sprintf(pResult->CIMG_PlateImage.chSavePath,"%s\\Buffer\\%s\\%d-%s-%s-%s-车型%d-车轴%d-%d-Plate.jpg", szFileName, m_strIP.c_str(), dwPlateTime, pResult->chPlateNO, chPlateColor, pResult->chPlateTime, pResult->iVehTypeNo, pResult->iAxletreeCount, pResult->dwCarID);
	//bestCapture
	sprintf(pResult->CIMG_BestCapture.chSavePath, "%s\\Buffer\\%s\\%d-%s-%s-%s-车型%d-车轴%d-%d-BestCapture.jpg", szFileName, m_strIP.c_str(), dwPlateTime, pResult->chPlateNO, chPlateColor, pResult->chPlateTime, pResult->iVehTypeNo, pResult->iAxletreeCount, pResult->dwCarID);
	//lastCapture
	sprintf(pResult->CIMG_LastCapture.chSavePath,"%s\\Buffer\\%s\\%d-%s-%s-%s-车型%d-车轴%d-%d-LastCapture.jpg", szFileName, m_strIP.c_str(), dwPlateTime, pResult->chPlateNO, chPlateColor, pResult->chPlateTime, pResult->iVehTypeNo, pResult->iAxletreeCount, pResult->dwCarID);
	//BEGIN_CAPTURE
	sprintf(pResult->CIMG_BeginCapture.chSavePath,"%s\\Buffer\\%s\\%d-%s-%s-%s-车型%d-车轴%d-%d-BeginCapture.jpg", szFileName, m_strIP.c_str(), dwPlateTime, pResult->chPlateNO, chPlateColor, pResult->chPlateTime, pResult->iVehTypeNo, pResult->iAxletreeCount, pResult->dwCarID);
	//BEST_SNAPSHOT
	sprintf(pResult->CIMG_BestSnapshot.chSavePath,"%s\\Buffer\\%s\\%d-%s-%s-%s-车型%d-车轴%d-%d-BestSnapshot.jpg", szFileName, m_strIP.c_str(), dwPlateTime, pResult->chPlateNO, chPlateColor, pResult->chPlateTime, pResult->iVehTypeNo, pResult->iAxletreeCount, pResult->dwCarID);
	//LAST_SNAPSHOT
	sprintf(pResult->CIMG_LastSnapshot.chSavePath,"%s\\Buffer\\%s\\%d-%s-%s-%s-车型%d-车轴%d-%d-LastSnapshot.jpg", szFileName, m_strIP.c_str(), dwPlateTime, pResult->chPlateNO, chPlateColor, pResult->chPlateTime, pResult->iVehTypeNo, pResult->iAxletreeCount, pResult->dwCarID);

	if (pResult->CIMG_BinImage.pbImgData)
	{
		bool bSave = SaveImgToDisk(pResult->CIMG_BinImage.chSavePath, pResult->CIMG_BinImage.pbImgData, pResult->CIMG_BinImage.dwImgSize);
	}

	if (pResult->CIMG_PlateImage.pbImgData)
	{
		bool bSave = SaveImgToDisk(pResult->CIMG_PlateImage.chSavePath, pResult->CIMG_PlateImage.pbImgData, pResult->CIMG_PlateImage.dwImgSize);
	}

	if (pResult->CIMG_BeginCapture.pbImgData)
	{
		bool bSave = SaveImgToDisk(pResult->CIMG_BeginCapture.chSavePath, pResult->CIMG_BeginCapture.pbImgData, pResult->CIMG_BeginCapture.dwImgSize);
	}

	if (pResult->CIMG_BestCapture.pbImgData)
	{
		bool bSave = SaveImgToDisk(pResult->CIMG_BestCapture.chSavePath, pResult->CIMG_BestCapture.pbImgData, pResult->CIMG_BestCapture.dwImgSize);
		//bool bSave  = SaveImgToDisk(pResult->CIMG_BestCapture.chSavePath, pResult->CIMG_BestCapture.pbImgData, pResult->CIMG_BestCapture.dwImgSize, 768, 576, 1); 
	}

	if (pResult->CIMG_LastCapture.pbImgData)
	{
		bool bSave = SaveImgToDisk(pResult->CIMG_LastCapture.chSavePath, pResult->CIMG_LastCapture.pbImgData, pResult->CIMG_LastCapture.dwImgSize);
	}

	if (pResult->CIMG_BestSnapshot.pbImgData)
	{
		bool bSave = SaveImgToDisk(pResult->CIMG_BestSnapshot.chSavePath, pResult->CIMG_BestSnapshot.pbImgData, pResult->CIMG_BestSnapshot.dwImgSize);
	}

	if (pResult->CIMG_LastSnapshot.pbImgData)
	{
		bool bSave = SaveImgToDisk(pResult->CIMG_LastSnapshot.chSavePath, pResult->CIMG_BestSnapshot.pbImgData, pResult->CIMG_LastSnapshot.dwImgSize);
		//bool bSave  = SaveImgToDisk(pResult->CIMG_LastSnapshot.chSavePath, pResult->CIMG_LastSnapshot.pbImgData, pResult->CIMG_LastSnapshot.dwImgSize, 768, 576, 0); 
	}
}

void Camera6467::ExcuteCMD( char* pChCommand )
{
	if (NULL == pChCommand)
	{
		return;
	}
	ShellExecute(NULL, "open", "C:\\WINDOWS\\system32\\cmd.exe", pChCommand, "", SW_HIDE);
}

bool Camera6467::IsFileExist( const char* FilePath )
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

bool Camera6467::MyMakeDir( const char* chImgPath)
{
	if(NULL == chImgPath)
	{
		WriteLog("the path is null ,Create Dir failed.");
		return false;
	}
	std::string tempFile(chImgPath);
	size_t iPosition = tempFile.rfind("\\");
	std::string tempDir = tempFile.substr(0, iPosition+1);
	if (MakeSureDirectoryPathExists(tempDir.c_str()))
	{
		return true;
	}
	else
	{
		WriteLog("Create Dir failed.");
		return false;
	}
}

CameraResult* Camera6467::GetOneResultByIndex( int iIndex )
{
	CameraResult* tempResult = NULL;
	if (iIndex < 0 || iIndex > 100)
	{
		return tempResult;
	}
	EnterCriticalSection(&m_csResult);	
	if (m_ResultList.size() > iIndex)
	{
		int idex = 0;
		for (std::list<CameraResult*>::iterator it = m_ResultList.begin(); it != m_ResultList.end(); it++)
		{
			if (idex == iIndex)
			{
				tempResult = *it;
				break;
			}
			idex++;
		}		
	}
	LeaveCriticalSection(&m_csResult);

	return tempResult;
}

void Camera6467::DeleteOneResult()
{
	CameraResult* tempResult = NULL;

	EnterCriticalSection(&m_csResult);	
	if (m_ResultList.size() > 0)
	{
		tempResult = m_ResultList.front();
		m_ResultList.pop_front();
	}
	LeaveCriticalSection(&m_csResult);
	if (tempResult != NULL)
	{
		delete tempResult;
		tempResult = NULL;
	}
}

void Camera6467::InterruptionConnection()
{
	if(NULL == m_hHvHandle)
	{
		return;
	}

	char chCommand[1024] = {0};


	if ( (HVAPI_SetCallBackEx(m_hHvHandle, NULL, this, 0, CALLBACK_TYPE_RECORD_INFOBEGIN, /*NULL*/chCommand) != S_OK) ||
		(HVAPI_SetCallBackEx(m_hHvHandle, NULL, this, 0, CALLBACK_TYPE_RECORD_PLATE, /*NULL*/chCommand) != S_OK) ||
		(HVAPI_SetCallBackEx(m_hHvHandle, NULL, this, 0, CALLBACK_TYPE_RECORD_BIGIMAGE, /*NULL*/chCommand) != S_OK) ||
		(HVAPI_SetCallBackEx(m_hHvHandle, NULL, this, 0, CALLBACK_TYPE_RECORD_SMALLIMAGE, /*NULL*/chCommand) != S_OK)||
		(HVAPI_SetCallBackEx(m_hHvHandle, NULL, this, 0, CALLBACK_TYPE_RECORD_BINARYIMAGE, /*NULL*/chCommand) != S_OK)||
		(HVAPI_SetCallBackEx(m_hHvHandle, NULL, this, 0, CALLBACK_TYPE_RECORD_INFOEND, /*NULL*/chCommand) != S_OK)
		)
	{		
		WriteLog("DisConnectToCamera:: SetCallBack failed.");
		//return false;
	}
	else
	{
		WriteLog("DisConnectToCamera:: SetCallBack success.");
	}
}

int Camera6467::GetResultCount()
{
	int iCount = 0;
	EnterCriticalSection(&m_csResult);
	iCount = m_ResultList.size();
	LeaveCriticalSection(&m_csResult);
	return iCount;
}

void Camera6467::ClearAllResult()
{
	EnterCriticalSection(&m_csResult);
	CameraResult * ptempResult = NULL;
	while(m_ResultList.size() > 0)
	{
		ptempResult = m_ResultList.front();
		m_ResultList.pop_front();
		if (ptempResult != NULL)
		{
			delete ptempResult;
			ptempResult = NULL;
		}
	}
	LeaveCriticalSection(&m_csResult);
}

void RgbBin2ByteBin( PBYTE m_rgbBinImage, PBYTE pbByteBinImage )
{

	/*********用汉高的测试软件，“显示二值化”按钮显示正确，但“获取识别结果”上下颠倒****/
	//BYTE *pSrc = &m_rgbBinImage[(BIN_HEIGHT - 1) * BIN_STRIDE];
	//BYTE *pDest = pbByteBinImage;
	//for (int y = 0; y < BIN_HEIGHT; y++)
	//{
	//	memcpy(pDest, pSrc, BIN_STRIDE);
	//	pSrc -= BIN_STRIDE;
	//	pDest += BIN_STRIDE;
	//}


	/*********用汉高的测试软件，“显示二值化”按钮显示上下颠倒，但“获取识别结果”显示正确****/
	BYTE *pSrc = &m_rgbBinImage[0];
	BYTE *pDest = pbByteBinImage;
	for (int y = 0; y < BIN_HEIGHT; y++)
	{
		memcpy(pDest, pSrc, BIN_STRIDE);
		pSrc += BIN_STRIDE;
		pDest += BIN_STRIDE;
	}

	//字节中前后bit位互换
	for (int i = 0; i < BIN_BYTE_COUNT; i++)
	{
		BYTE bTemp = pbByteBinImage[i];
		BYTE bTemp2 = 0;
		bTemp2 |= (bTemp & 0x80) >> 7;
		bTemp2 |= (bTemp & 0x40) >> 5;
		bTemp2 |= (bTemp & 0x20) >> 3;
		bTemp2 |= (bTemp & 0x10) >> 1;
		bTemp2 |= (bTemp & 0x08) << 1;
		bTemp2 |= (bTemp & 0x04) << 3;
		bTemp2 |= (bTemp & 0x02) << 5;
		bTemp2 |= (bTemp & 0x01) << 7;
		pbByteBinImage[i] = bTemp2;
	}
}
