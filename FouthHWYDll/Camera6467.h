#ifndef CAMERA6467_H
#define CAMERA6467_H
#include <string>
#include <list>
#include "CameraResult.h"

const int BIN_BIT_COUNT = 8;
const int BIN_WIDTH = 112;
const int BIN_HEIGHT = 20;
const int BIN_STRIDE = BIN_WIDTH / BIN_BIT_COUNT;
const int BIN_BYTE_COUNT = BIN_HEIGHT * BIN_STRIDE;

void RgbBin2ByteBin(PBYTE m_rgbBinImage, PBYTE pbByteBinImage);

struct CameraInfo
{
	char chIP[20];                          //deviceIP
	char chDeviceID[3];
	char chStationID[7];
	char chLaneID[3];
	bool bLogEnable;
	bool bSynTimeEnable;
	bool bIsInit;
	int iDirection;
	CameraInfo()
	{
		memset(chIP, 0, 20);
		memset(chDeviceID, 0, 3);
		memset(chStationID, 0, 7);
		memset(chLaneID, 0, 3);
		bLogEnable = true;
		bSynTimeEnable = false;
		bIsInit = false;
		iDirection = 0;
	}
};

struct SaveModeInfo
{
	int iSafeModeEnable;
	char chBeginTime[260];
	char chEndTime[260];
	int iIndex;
	int iDataType;
	SaveModeInfo()
	{
		iSafeModeEnable = 0;
		iIndex = 0;
		iDataType = 0;
		memset(chBeginTime, 0, 260);
		memset(chEndTime, 0, 260);
	}
};

struct DeviceTime
{
	int iYear;
	int iMonth;
	int iDay;
	int iHour;
	int iMinutes;
	int iSecond;
	int iMilisecond;
	
	DeviceTime()
	{
		iYear = 0;
		iMonth = 0;
		iDay = 0;
		iHour = 0;
		iMinutes = 0;
		iSecond = 0;
		iMilisecond = 0;
	}
};

class Camera6467
{
public:
	Camera6467();
	Camera6467(const char* chIP, HWND*  hWnd,int Msg);
	~Camera6467();

	//void SetList(Result_lister* ResultList);
	bool SetCameraInfo(CameraInfo& camInfo);

	int GetCamStatus();
	char* GetStationID();
	char* GetDeviceID();
	char*  GetLaneID();
	const char* GetCameraIP();
	CameraResult* GetOneResult();
	CameraResult* GetOneResultByIndex(int iIndex);
	int GetResultCount();
	void DeleteOneResult();
	bool GetDeviceTime(DeviceTime& deviceTime);
	void ClearAllResult();

	bool ConnectToCamera();
	
	void ReadConfig();
	bool WriteLog(const char* chlog);
	bool TakeCapture();
	bool SynTime();
	bool SynTime(int Year, int Month, int Day, int Hour, int Minute, int Second, int MilientSecond);
	bool SaveImgToDisk( char* chImgPath, BYTE* pImgData, DWORD dwImgSize);
	bool SaveImgToDisk( char* chImgPath, BYTE* pImgData, DWORD dwImgSize, int iWidth, int iHeight, int iType = 0);
	void SetResultToUnready();
	void SaveResultToBuffer(CameraResult* pResult);
//	bool GetFileNameAndPathFromDisk(char* pChFileName, char* pChFilePath);
	void ExcuteCMD(char* pChCommand);
	bool IsFileExist(const char* FilePath);
	bool MyMakeDir(const char*);
	
private:
	void* m_hHvHandle;
	void* m_hWnd;
	int m_iMsg;
	std::string m_strIP;
	std::string m_strDeviceID;
	int m_iConnectStatus;

	char m_chDeviceID[3];
	char m_chStationID[7];
	char m_chLaneID[3];
	bool m_bLogEnable;
	bool m_bSynTime;
	bool m_bResultComplete;
	bool m_bSaveToBuffer;
	unsigned long m_dwConnectStatus;
	int m_iCompressQuality;
	int m_iDirection;
	DWORD m_dwLastCarID;

	char m_qstrBackupPath[260];
	char m_qstrRootPath[260];

	CLSID m_jpgClsid;
	CLSID m_bmpClsid;
	
	SaveModeInfo m_SaveModelInfo;

	CameraResult* m_CameraResult;
	CameraResult* m_BufferResult;
	std::list<CameraResult*>  m_ResultList;
	CRITICAL_SECTION m_csLog;
	CRITICAL_SECTION m_csResult;

	void ReadHistoryInfo();
	void WriteHistoryInfo(SaveModeInfo& SaveInfo);	
	void AnalysisAppendInfo(CameraResult* CamResult);
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	bool GetStreamLength( IStream* pStream, ULARGE_INTEGER* puliLenth );
	//bool SaveImgToDiskByQt( CameraIMG& camImageStruct);
	//void SetImgPath(CameraResult* camResult);
	void	InterruptionConnection();

	inline void CopyDataToIMG(CameraIMG& DestImg, PBYTE pImgData, unsigned long width, unsigned long height, unsigned long dataLenth, WORD wImgType)
	{
		if(NULL != DestImg.pbImgData)
		{
			delete[] DestImg.pbImgData;
			DestImg.pbImgData = NULL;
		}

		DestImg.pbImgData = new(std::nothrow) BYTE[dataLenth];
		DestImg.dwImgSize = 0;
		if (  NULL != DestImg.pbImgData)
		{
			memcpy(DestImg.pbImgData, pImgData, dataLenth);
			DestImg.wImgWidth = width;
			DestImg.wImgHeight = height;
			DestImg.dwImgSize = dataLenth;
			DestImg.wImgType = wImgType;
		}
	}


public:
	static int  RecordInfoBeginCallBack(PVOID pUserData, DWORD dwCarID)
	{
		if ( pUserData == NULL )
			return 0;

		Camera6467* pThis = (Camera6467*)pUserData;
		return pThis->RecordInfoBegin(dwCarID);
	};
	int RecordInfoBegin(DWORD dwCarID);


	static int  RecordInfoEndCallBack(PVOID pUserData, DWORD dwCarID)
	{
		if ( pUserData == NULL )
			return 0;

		Camera6467* pThis = (Camera6467*)pUserData;
		return pThis->RecordInfoEnd(dwCarID);
	};
	int RecordInfoEnd(DWORD dwCarID);


	static int  RecordInfoPlateCallBack(PVOID pUserData,
		DWORD dwCarID,
		LPCSTR pcPlateNo,
		LPCSTR pcAppendInfo,
		DWORD dwRecordType,
		DWORD64 dw64TimeMS)
	{
		if (pUserData == NULL)
			return 0;

		Camera6467* pThis = (Camera6467*)pUserData;
		return pThis->RecordInfoPlate(dwCarID, pcPlateNo, pcAppendInfo, dwRecordType, dw64TimeMS);
	}
	int RecordInfoPlate(DWORD dwCarID,
		LPCSTR pcPlateNo,
		LPCSTR pcAppendInfo,
		DWORD dwRecordType,
		DWORD64 dw64TimeMS);


	static int  RecordInfoBigImageCallBack(PVOID pUserData,
		DWORD dwCarID,
		WORD  wImgType,
		WORD  wWidth,
		WORD  wHeight,
		PBYTE pbPicData,
		DWORD dwImgDataLen,
		DWORD dwRecordType,
		DWORD64 dw64TimeMS)
	{
		if (pUserData == NULL)
			return 0;

		Camera6467* pThis = (Camera6467*)pUserData;
		return pThis->RecordInfoBigImage(dwCarID, wImgType, wWidth, wHeight, pbPicData, dwImgDataLen, dwRecordType, dw64TimeMS);
	}
	int RecordInfoBigImage(DWORD dwCarID,
		WORD  wImgType,
		WORD  wWidth,
		WORD  wHeight,
		PBYTE pbPicData,
		DWORD dwImgDataLen,
		DWORD dwRecordType,
		DWORD64 dw64TimeMS);



	static int  RecordInfoSmallImageCallBack(PVOID pUserData,
		DWORD dwCarID,
		WORD wWidth,
		WORD wHeight,
		PBYTE pbPicData,
		DWORD dwImgDataLen,
		DWORD dwRecordType,
		DWORD64 dw64TimeMS)
	{
		if (pUserData == NULL)
			return 0;

		Camera6467* pThis = (Camera6467*)pUserData;
		return pThis->RecordInfoSmallImage(dwCarID, wWidth, wHeight, pbPicData, dwImgDataLen, dwRecordType, dw64TimeMS);
	}
	int RecordInfoSmallImage(DWORD dwCarID,
		WORD wWidth,
		WORD wHeight,
		PBYTE pbPicData,
		DWORD dwImgDataLen,
		DWORD dwRecordType,
		DWORD64 dw64TimeMS);


	static int  RecordInfoBinaryImageCallBack(PVOID pUserData,
		DWORD dwCarID,
		WORD wWidth,
		WORD wHeight,
		PBYTE pbPicData,
		DWORD dwImgDataLen,
		DWORD dwRecordType,
		DWORD64 dw64TimeMS)
	{
		if (pUserData == NULL)
			return 0;

		Camera6467* pThis = (Camera6467*)pUserData;
		return pThis->RecordInfoBinaryImage(dwCarID, wWidth, wHeight, pbPicData, dwImgDataLen, dwRecordType, dw64TimeMS);
	}
	int RecordInfoBinaryImage(DWORD dwCarID,
		WORD wWidth,
		WORD wHeight,
		PBYTE pbPicData,
		DWORD dwImgDataLen,
		DWORD dwRecordType,
		DWORD64 dw64TimeMS);

};

#endif