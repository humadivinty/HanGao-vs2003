#ifndef _HVDEVICECOMMDEF_H__
#define _HVDEVICECOMMDEF_H__

/* ͼƬ���� */
#define IMAGE_TYPE_UNKNOWN          0xffff0100	/**< δ֪ */
#define IMAGE_TYPE_JPEG_NORMAL      0xffff0101	/**< Jpeg��ͨͼ */
#define IMAGE_TYPE_JPEG_CAPTURE     0xffff0102	/**< Jpegץ��ͼ */
#define IMAGE_TYPE_JPEG_LPR         0xffff0103	/**< Jpeg�������� */

/* ��Ƶ���� */
#define VIDEO_TYPE_UNKNOWN          0xffff0200	/**< δ֪ */
#define VIDEO_TYPE_H264_NORMAL_I    0xffff0201	/**< H.264ʵʱ��Ƶ��I֡ */
#define VIDEO_TYPE_H264_NORMAL_P    0xffff0202	/**< H.264ʵʱ��Ƶ��P֡ */
#define VIDEO_TYPE_H264_HISTORY_I   0xffff0203	/**< H.264Ӳ��¼����Ƶ��I֡ */
#define VIDEO_TYPE_H264_HISTORY_P   0xffff0205	/**< H.264Ӳ��¼����Ƶ��I֡ */
#define VIDEO_TYPE_JPEG_HISTORY     0xffff0204	/**< JPEGӲ��¼����Ƶ�� */

/* ʶ�������� */
#define RECORD_TYPE_UNKNOWN         0xffff0300	/**< δ֪ */
#define RECORD_TYPE_NORMAL          0xffff0301	/**< ʵʱ��� */
#define RECORD_TYPE_HISTORY         0xffff0302	/**< ��ʷ��� */
#define RECORD_TYPE_STRING          0xffff0303	/**< �¼������Ϣ */
#define RECORD_TYPE_INLEFT          0xffff0304	/**< ���Ƶ����뿪��ʶ */

/* ����״̬ */
#define CONN_STATUS_UNKNOWN         0xffff0400	/**< δ֪ */
#define CONN_STATUS_NORMAL          0xffff0401	/**< ���� */
#define CONN_STATUS_DISCONN         0xffff0402	/**< �Ͽ� */
#define CONN_STATUS_RECONN          0xffff0403	/**< ������ */
#define CONN_STATUS_RECVDONE        0xffff0404	/**< ��ʷ���ݽ������ */
//��������״̬Ϊ������������
#define CONN_STATUS_CONNFIRST           0xffff0405	/**< ��ʼ����*/
#define CONN_STATUS_CONNOVERTIME        0xffff0406	/**< ���ӳ�ʱ*/

/* ����������*/
#define RESULT_RECV_FLAG_REALTIME					0xffff0500  /**< ����ʵʱ��� */
#define RESULT_RECV_FLAG_HISTORY					0xffff0501  /**< ������ʷ��� */
#define RESULT_RECV_FLAG_HISTROY_ONLY_PECCANCY		0xffff0502  /**< ������ʷΥ�½�� */

/* �����־*/
#define RESULT_FLAG_INVAIL			0xffff0600  /**< ��Ч������� */
#define RESULT_FLAG_VAIL			0xffff0601  /**< ��Ч������� */
#define RESULT_FLAG_HISTROY_END		0xffff0602  /**< ��ʷ���������־ */

/* ����H264����*/
#define H264_RECV_FLAG_REALTIME				0xffff0700  /**< ����ʵʱ��Ƶ */
#define H264_RECV_FLAG_HISTORY				0xffff0701  /**< ������ʷ��Ƶ */

/* H264��־*/
#define H264_FLAG_INVAIL			0xffff0800  /**< ��Ч��Ƶ���� */
#define H264_FLAG_VAIL				0xffff0801  /**< ��Ч��Ƶ���� */
#define H264_FLAG_HISTROY_END		0xffff0802  /**< ��ʷ���������־ */


/* ����MJPEG����*/
#define MJPEG_RECV_FLAG_DEBUG				0xffff0900  /**< ���յ������� */
#define MJPEG_RECV_FLAG_REALTIME			0xffff0901  /**< ����ʵʱJPEG��*/

/* MJPEG��־*/
#define MJPEG_FLAG_INVAIL			0xffff0A00  /**< ��ЧMJPEG */
#define MJPEG_FLAG_VAIL				0xffff0A01  /**< ��ЧMJPEG֡ */
/* �豸���� */
#define DEV_TYPE_UNKNOWN		0x00000000 /**< δ֪�豸 */
#define DEV_TYPE_HVCAM_200W		0x00000001 /**< 200��һ��� */
#define DEV_TYPE_HVCAM_500W		0x00000002 /**< 500��һ��� */
#define DEV_TYPE_HVSIGLE		0x00000004 /**< ����2.0ʶ���� */
#define DEV_TYPE_HVCAM_SINGLE	0x00000008 /**< �򻯰�һ��� */
#define DEV_TYPE_HVCAMERA       0x00000010 /**< ����� */
#define DEV_TYPE_HVMERCURY		0x00000020  /**< ˮ���豸 */
#define DEV_TYPE_HVEARTH		0x00000040  /**< �����豸 */
#define DEV_TYPE_HVVENUS		0x00000080  /**< �����豸 */
#define DEV_TYPE_HVJUPITER		0x00000100  /**< ľ���豸 */
#define DEV_TYPE_ITTS	        0x00000200  /**< ITTS�豸 */
#define DEV_TYPE_SATURN	        0x00000400  /**< �����豸 */
#define DEV_TYPE_VFR	        0x00000800  /**< ���ͷ����豸 */
#define DEV_TYPE_SATURN2        0x00001000  /**< ����2�豸 */
#define DEV_TYPE_ALL            0x0000ffff	/**< �����豸 */


/* �ص��������� */
#define CALLBACK_TYPE_RECORD_PLATE			0xFFFF0001
#define CALLBACK_TYPE_RECORD_BIGIMAGE		0xFFFF0002
#define CALLBACK_TYPE_RECORD_SMALLIMAGE		0xFFFF0003
#define CALLBACK_TYPE_RECORD_BINARYIMAGE	0xFFFF0004
#define CALLBACK_TYPE_RECORD_INFOBEGIN		0xFFFF0005
#define CALLBACK_TYPE_RECORD_INFOEND		0xFFFF0006
#define CALLBACK_TYPE_STRING				0xFFFF0007
#define CALLBACK_TYPE_JPEG_FRAME			0xFFFF0008
#define CALLBACK_TYPE_H264_VIDEO			0xFFFF0009
#define CALLBACK_TYPE_HISTORY_VIDEO			0xFFFF0010
#define CALLBACK_TYPE_TFD_STRING			0xFFFF0011
#define CALLBACK_TYPE_ADV_VIDEO			    0xFFFF0012
#define CALLBACK_TYPE_ADV_HISTORY_VIDEO		0xFFFF0013
#define CALLBACK_TYPE_ADV_MJPEG				0xFFFF0014
#define CALLBACK_TYPE_ADV_RECORD_RESULT		0xFFFF0015
#define CALLBACK_TYPE_ADV_HISTORY_RECORD_RESULT		0xFFFF0016
#define CALLBACK_TYPE_REDEVELOP_RESULT      0xFFFF0017
#define CALLBACK_TYPE_RECORD_ILLEGALVIDEO	0xFFFF0018
#define CALLBACK_TYPE_RADAR_DATA            0xFFFF0019 

/* ʶ������ͼ���Ͷ��� */
#define RECORD_BIGIMG_BEST_SNAPSHOT			0x0001	/**< ������ʶ��ͼ */
#define RECORD_BIGIMG_LAST_SNAPSHOT			0x0002	/**< ���ʶ��ͼ */
#define RECORD_BIGIMG_BEGIN_CAPTURE			0x0003	/**< ��ʼץ��ͼ */
#define RECORD_BIGIMG_BEST_CAPTURE			0x0004	/**< ������ץ��ͼ */
#define RECORD_BIGIMG_LAST_CAPTURE			0x0005	/**<  ���ץ��ͼ */
#define RECORD_BIGIMG_PLATE					0x0006  /**< ����Сͼ */
#define RECORD_BIGIMG_PLATE_BIN				0x0007  /**< ���ƶ�ֵͼ */


/* �������Ͷ��� */
#define CONN_TYPE_UNKNOWN         0xffff0000	/**< δ֪ */
#define CONN_TYPE_IMAGE           0xffff0001	/**< ͼƬ */
#define CONN_TYPE_VIDEO           0xffff0002	/**< ��Ƶ */
#define CONN_TYPE_RECORD          0xffff0003	/**< ʶ���� */
#define CONN_TYPE_RADAR           0xffff0004    /**< �״���Ϣ */

/* ��չ�������� */
#define PLATE_RECT_BEST_SNAPSHOT           0x0001        /**< ������ʶ��ͼ�������� */
#define PLATE_RECT_LAST_SNAPSHOT           0x0002        /**< ���ʶ��ͼ�������� */
#define PLATE_RECT_BEGIN_CAPTURE           0x0003        /**< ��ʼץ��ͼ�������� */
#define PLATE_RECT_BEST_CAPTURE            0x0004        /**< ������ץ��ͼ�������� */
#define PLATE_RECT_LAST_CAPTURE            0x0005        /**< ���ץ��ͼ�������� */

#define FACE_RECT_BEST_SNAPSHOT            0x0006        /**< ������ʶ��ͼ������Ϣ */
#define FACE_RECT_LAST_SNAPSHOT            0x0007        /**< ���ʶ��ͼ������Ϣ */
#define FACE_RECT_BEGIN_CAPTURE            0x0008        /**< ��ʼץ��ͼ������Ϣ */
#define FACE_RECT_BEST_CAPTURE             0x0009        /**< ������ץ��ͼ������Ϣ */
#define FACE_RECT_LAST_CAPTURE             0x000A        /**< ���ץ��ͼ������Ϣ */

#define STACK_SIZE 128*1024 // �����߳�ջΪ128K

//������ʻ��������
#define ROADTYPE_RRT_FORWARD	0x001 /** ֱ��*/
#define ROADTYPE_RRT_LEFT		0x002 /** ��ת*/
#define	ROADTYPE_RRT_RIGHT		0x004	 /**��ת*/
#define	ROADTYPE_RRT_TURN		0x008  /**��ͷ*/
#define ROADTYPE_RRT_ESTOP		0x010  /**�ǻ�����*/
/* ���������ص��������� */
#define CALLBACK_TYPE_LISTEN_XML_DATE			0x00001  /** �ص���������*/

/* ͨѶЭ��汾�� */
typedef enum
{
	PROTOCOL_VERSION_1,
	PROTOCOL_VERSION_2,
	PROTOCOL_VERSION_MERCURY,
	PROTOCOL_VERSION_EARTH,
	PROTOCOL_UNKNOWN
} PROTOCOL_VERSION;
 
typedef struct _CDevBasicInfo
{
	CHAR szIP[64];
	CHAR szMask[64];
	CHAR szGateway[64];
	CHAR szMac[128];
	CHAR szModelVersion[128];
	CHAR szSN[128];
	CHAR szWorkMode[128];
	CHAR szDevType[128];
	CHAR szDevVersion[128];
	CHAR szMode[128];
	CHAR szRemark[128];
	CHAR szBackupVersion[128];//����
	CHAR szFPGAVersion[128];//����
	CHAR szKernelVersion[128];//����
	CHAR szUbootVersion[128];//����
	CHAR szUBLVersion[128];//����
	CHAR szFirmwareVersion[128];//����
	CHAR szNetPackageVersion[128];//����

	_CDevBasicInfo()
	{
		szIP[0]='\0';
		szMask[0]='\0';
		szGateway[0]='\0';
		szMac[0]='\0';
		szModelVersion[0]='\0';
		szSN[0]='\0';
		szWorkMode[0]='\0';
		szDevType[0]='\0';
		szDevVersion[0]='\0';
		szMode[0]='\0';
		szRemark[0]='\0';
		szBackupVersion[0]='\0';
		szFPGAVersion[0]='\0';
		szKernelVersion[0]='\0';
		szUbootVersion[0]='\0';
		szUBLVersion[0]='\0';
		szFirmwareVersion[0]='\0';
		szNetPackageVersion[0]='\0';
	}

}CDevBasicInfo;



typedef struct _CCameraInfo
{
	INT  iChnnnelID;
	CHAR szIP[64];
	CHAR szMask[64];
	CHAR szGateway[64];
	CHAR szMac[128];
	CHAR szSN[128];
	CHAR szWorkMode[128];
	CHAR szDevType[128];
	CHAR szDevName[128];

	_CCameraInfo()
	{
		iChnnnelID = 0;
		szIP[0]='\0';
		szMask[0]='\0';
		szGateway[0]='\0';
		szMac[0]='\0';
		szSN[0]='\0';
		szWorkMode[0]='\0';
		szDevType[0]='\0';
		szDevName[0]='\0';
	}

}CCameraInfo;


typedef struct _AIOAddDevice
{
	INT  iChannelID;
	CHAR szIP[20];
	CHAR szMask[20];
	CHAR szGateway[20];
	CHAR szMac[256];
	CHAR szSn[256];
	CHAR szDeviceType[256];
	CHAR szDeviceWorkMode[256];
	CHAR szDevName[128];
	//NBR
	INT iRateControl;	//ǰ�����H.264���ʿ��Ʒ�ʽ 0:VBR 1:CBR
    INT iTargetBitrate;	//ǰ�����H.264Ŀ������
    INT iIframeIntervel;	//ǰ�����H.264��I֡���
    INT iVbrDuration;	//ǰ�����H.264 VBR����ʱ��
    INT iVbrSensitivity;	//ǰ�����H.264 VBR������

	_AIOAddDevice()
	{
		szDevName[0]='\0';
	}
}AIOAddDevice;


typedef struct _ResultList
{
	INT iStartIndex;
	INT iEndIndex;
	CHAR szPlate[128];
	CHAR szPlateColor[20];
	CHAR szVehicleType[64];
	INT iSpeed;
	INT iIllegalType;
	INT iLaneNo;
	CHAR szResultTime[20];
	INT iCarId;
	_ResultList()
	{
		iStartIndex = 0;
		iEndIndex = 0;
		szPlate[0] = '\0';
		szPlateColor[0] = '\0';
		szVehicleType[0] = '\0';
		iSpeed = 0;
		iIllegalType = 0;
		iLaneNo = 0;
		szResultTime[0] = '\0';
		iCarId = 0;
	}
	
}ResultList;

typedef struct _ResultListEx
{
	INT iStartIndex;
	INT iEndIndex;
	CHAR szPlate[128];
	CHAR szPlateColor[20];
	CHAR szVehicleType[64];
	INT iSpeed;
	INT iIllegalType;
	INT iLaneNo;
	CHAR szResultTime[20];
	INT iCarId;
	CHAR szCarFace[24];
	PVOID pOutExtInfo;
	INT iChannelID;
	_ResultListEx()
	{
		iStartIndex = 0;
		iEndIndex = 0;
		szPlate[0] = '\0';
		szPlateColor[0] = '\0';
		szVehicleType[0] = '\0';
		iSpeed = 0;
		iIllegalType = 0;
		iLaneNo = 0;
		szResultTime[0] = '\0';
		iCarId = 0;
		szCarFace[0] = '\0';
		pOutExtInfo = NULL;
		iChannelID = -1;
	}
	
}ResultListEx;


typedef struct _VideoList
{
	char szBTime[32];
	char szETime[32];

	_VideoList()
	{
		szBTime[0] ='\0';
		szETime[0] ='\0';
	}
	
}VideoList;











typedef struct _CDevState
{
	INT nTemperature;		//�¶�    ����50 �� 50���϶�
	INT nCpuUsage;			//CPUʹ���� ����50 �� 50%
	INT nMemUsage;			//�ڴ�ʹ���� ����50 �� 50%
	INT nHddState;			//Ӳ��ʹ��״̬ 0��������1���쳣
	BOOL fOCGateEnable;		//OC��ʹ��״̬
	BOOL fRTSPMulticastEnable;	//RTSP�㲥����
	INT nTraceRank;

	CHAR szRecordLinkIP[512];
	CHAR szVideoLinkIP[512];
	CHAR szImageLinkIP[512];
	
	BOOL fNTPEnable;
	CHAR szNTPServerIP[64];
	INT nNTPServerUpdateInterval;
	//ʱ��
	INT nTimeZone;
	//ʱ��
	INT nYear;
	INT nMon;
	INT nDay;
	INT nHour;
	INT nMin;
	INT nSec;
	INT nMSec;

	_CDevState()
	{
		nTemperature=0;
		nCpuUsage=0;
		nMemUsage=0;
		nHddState=0;
		fOCGateEnable=0;
		fRTSPMulticastEnable=0;
		nTraceRank=0;
		szRecordLinkIP[0]='\0';
		szVideoLinkIP[0]='\0';
		szImageLinkIP[0]='\0';
		fNTPEnable=0;
		szNTPServerIP[0]='\0';
		nNTPServerUpdateInterval=0;
		nTimeZone=0;
		nYear=0;
		nMon=0;
		nDay=0;
		nHour=0;
		nMin=0;
		nSec=0;
		nMSec=0;
	}
}CDevState;

typedef struct _CCameraState
{
	BOOL fAGCEnable;
	INT nShutter;
	INT nGain;

	BOOL fAWBEnable;
	INT nGainR;
	INT nGainG;
	INT nGainB;


	_CCameraState()
	{
		fAGCEnable=0;
		nShutter=0;
		nGain=0;
		fAWBEnable=0;
		nGainR=0;
		nGainG=0;
		nGainB=0;

	}
}CCameraState;


typedef struct _CVideoState
{
	INT nCVBSDisplayMode;	     //CVBSģʽ  0:PAL,1:NTSL
	INT nH264FPS;
	INT nH264BitRateControl;
	INT nH264BitRate;
	INT nJpegFPS;
	INT nJpegCompressRate;

	//auto jpeg compress
	BOOL fAutoJpegCompressEnable;
	INT nJpegFileSize;
	
	INT nJpegCompressMaxRate;
	INT nJpegCompressMinRate;

	INT nDebugJpegStatus;

	_CVideoState()
	{
		nCVBSDisplayMode=0; 
		nH264FPS=0;
		nH264BitRateControl=0;
		nH264BitRate=0;
		nJpegFPS=0;
		nJpegCompressRate=0;
		fAutoJpegCompressEnable=0;
		nJpegFileSize=0;
		nJpegCompressMaxRate=0;
		nJpegCompressMinRate=0;
		nDebugJpegStatus=0;
	}
}CVideoState;


#define  MAX_ZONE_NUM 16
typedef struct _CCameraBasicInfo
{
	INT nBrightness;

	BOOL fImageEnhancementEnable;
	INT nContrast;
	INT nSaturation;
	
	BOOL fSharpnessEnable;
	INT nSharpness;

	//��̬
	BOOL fWDREnable;
	INT nWDRLevel;

	//����
	BOOL fDeNoiseTNFEnable;
	BOOL fDeNoiseSNFEnable;
	INT nDeNoiseMode;
	INT nDeNoiseLevel;

	//2DDenoise
	BOOL f2DDeNoiseEnable;
	INT n2DeNoiseStrength;

	//Gamma 
	BOOL fGammaEnable;
	INT nGammaStrength;

	//color
	INT nColor;		// ɫ��

	//Manual
	INT nManualShutter;
	INT nManualGain;
	INT nManualGainR;
	INT nManualGainG;
	INT nManualGainB;
	
	//AWB
	BOOL fAWBEnable;
	//AGC
	BOOL fAGCEnable;
	INT nAGCLightBaseLine;
	INT nAGCShutterMin;
	INT nAGCShutterMax;
	INT nAGCGainMin;
	INT nAGCGainMax;
	//ACSync
	INT nACSyncMode;
	INT nACSyncDelay;
	
	INT nFilterMode;
	BOOL fDCEnable;

	BOOL fGrayImageEnable;//�Ҷ�ͼ����
	INT nEnRedLightThreshold;//��ƼӺ���ֵ
	INT nEdgeEnhance;//��Ե��ǿ

	_CCameraBasicInfo()
	{
		nBrightness=0;
		fImageEnhancementEnable=0;
		nContrast=0;
		nSaturation=0;
		fSharpnessEnable=0;
		nSharpness=0;
		fWDREnable=0;
		nWDRLevel=0;
		fDeNoiseTNFEnable=0;
		fDeNoiseSNFEnable=0;
		nDeNoiseMode=0;
		nDeNoiseLevel=0;
		f2DDeNoiseEnable=0;
		n2DeNoiseStrength=0;
		fGammaEnable=0;
		nGammaStrength=0;
		nColor=0;		
		nManualShutter=0;
		nManualGain=0;
		nManualGainR=0;
		nManualGainG=0;
		nManualGainB=0;
		fAWBEnable=0;
		fAGCEnable=0;
		nAGCLightBaseLine=0;
		nAGCShutterMin=0;
		nAGCShutterMax=0;
		nAGCGainMin=0;
		nAGCGainMax=0;
		nACSyncMode=0;
		nACSyncDelay=0;
		nFilterMode=0;
		fDCEnable=0;
		fGrayImageEnable=0;
		nEnRedLightThreshold=0;
		nEdgeEnhance=0;
	}
}CCameraBasicInfo;

typedef struct _COSDInfo
{
	BOOL fEnable;
	BOOL fPlateEnable;
	BOOL fTimeStampEnable;
	INT nPosX;
	INT nPosY;

	INT nFontSize;
	INT nFontColorR;
	INT nFontColorG;
	INT nFontColorB;

	CHAR szText[256];

	_COSDInfo()
	{
		fEnable=0;
		fPlateEnable=0;
		fTimeStampEnable=0;
		nPosX=0;
		nPosY=0;
		nFontSize=0;
		nFontColorR=0;
		nFontColorG=0;
		nFontColorB=0;
		szText[0]='\0';
	}

}COSDInfo;

typedef struct _CUserInfo
{
	CHAR szUserName[128];
	INT nAuthority;
}CUserInfo;

typedef struct _CHvPoint
{
	INT nX;
	INT nY;
}CHvPoint;

//ͼƬ��Ϣ
typedef struct _CImageInfo
{
	DWORD wSize;			//�ṹ���С
	DWORD wImgType;			//ͼƬ����
	DWORD wWidth;			//ͼƬ��
	DWORD wHeight;			//ͼƬ�߶�
	PBYTE pbData;		    //ͼƬ����ָ��
	DWORD dwDataLen;		//ͼƬ���ݳ���
	DWORD64 dw64TimeMS;		//ͼƬʱ��
	DWORD fHasData;			//ͼƬ�����Ƿ���Ч
}CImageInfo;
#endif

