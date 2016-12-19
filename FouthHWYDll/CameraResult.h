#ifndef CAMERRESULT
#define CAMERRESULT

/* ʶ������ͼ���Ͷ��� */
#define RECORD_BIGIMG_BEST_SNAPSHOT			0x0001	/**< ������ʶ��ͼ */
#define RECORD_BIGIMG_LAST_SNAPSHOT			0x0002	/**< ���ʶ��ͼ */
#define RECORD_BIGIMG_BEGIN_CAPTURE			0x0003	/**< ��ʼץ��ͼ */
#define RECORD_BIGIMG_BEST_CAPTURE			0x0004	/**< ������ץ��ͼ */
#define RECORD_BIGIMG_LAST_CAPTURE			0x0005	/**<  ���ץ��ͼ */

class CameraIMG
{
public:
	CameraIMG();
	CameraIMG(const CameraIMG& CaIMG);
	~CameraIMG();
	WORD wImgWidth;
	WORD wImgHeight;
	DWORD dwImgSize;
	WORD  wImgType;
	char chSavePath[256];
	PBYTE pbImgData;

	CameraIMG& operator = (const CameraIMG& CaIMG);
};

class CameraResult
{
public:

	CameraResult();
	CameraResult(const CameraResult& CaRESULT);
	~CameraResult();

	DWORD dwCarID;
	int iDeviceID;
	int iPlateColor;
	int iPlateTypeNo;
	DWORD64 dw64TimeMS;
	int iSpeed;
	int iResultNo;
	int iVehTypeNo;		//���ʹ���: ��1--1 ��������4--4�� ��1--5  ��������4--8
	int iVehBodyColorNo;	
	int iVehBodyDeepNo;	
	int iAreaNo;
	int iRoadNo;
	int iLaneNo;
	int iDirection;
	int iWheelCount;		//����
	int iAxletreeCount;		//����
	float fVehLenth;			//����
	float fDistanceBetweenAxles;		//���
	float fVehHeight;		//����


	char chDeviceIp[32];
	char chPlateNO[32];
	char chPlateColor[10];
	char chListNo[256];
	char chPlateTime[256];
	char chSignStationID[50];
	char chSignStationName[50];
	char pcAppendInfo[2048];

	char chDeviceID[3];
	char chLaneID[3];

	CameraIMG CIMG_BestSnapshot;	/**< ������ʶ��ͼ */
	CameraIMG CIMG_LastSnapshot;	/**< ���ʶ��ͼ */
	CameraIMG CIMG_BeginCapture;	/**< ��ʼץ��ͼ */
	CameraIMG CIMG_BestCapture;		/**< ������ץ��ͼ */
	CameraIMG CIMG_LastCapture;		/**< ���ץ��ͼ */
	CameraIMG CIMG_PlateImage;		/**< ����Сͼ */
	CameraIMG CIMG_BinImage;			/**< ���ƶ�ֵͼ */

	CameraResult& operator = (const CameraResult& CaRESULT);

	friend bool SerializationResultToDisk(const char* chFilePath, const CameraResult& CaResult);
	friend bool SerializationFromDisk(const char* chFilePath, CameraResult& CaResult);

	friend bool SerializationAsConfigToDisk(const char* chFilePath, const CameraResult& CaResult);
	friend bool SerializationAsConfigFromDisk(const char* chFilePath, CameraResult& CaResult);
};

typedef struct _tagSafeModeInfo
{
	int iEableSafeMode;
	char chBeginTime[256];
	char chEndTime[256];
	int index;
	int DataInfo;
	_tagSafeModeInfo()
	{
		iEableSafeMode = 0;
		memset(chBeginTime, 0, sizeof(chBeginTime));
		memset(chEndTime, 0, sizeof(chEndTime));
		index = 0;
		DataInfo = 0;
	}
}_tagSafeModeInfo;

#endif