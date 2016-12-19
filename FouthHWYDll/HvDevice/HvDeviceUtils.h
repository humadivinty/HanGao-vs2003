#ifndef _HVDEVICEUTILS_H_
#define _HVDEVICEUTILS_H_

#include "HvDeviceDLL.h"
#include "HvDeviceCommDef.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)							\
	if ( p )									\
	{											\
		delete p;								\
		p = NULL;								\
	}
#endif

#define IVN_MAX_SIZE 128

#ifndef SAFE_DELETE_ARG
#define SAFE_DELETE_ARG(p)						\
	if(p)										\
	{											\
		delete[] p;								\
		p = NULL;								\
	}
#endif

//���ͼƬ��Ϣ�ṹ��
typedef struct _RECORD_IMAGE_INFO_EX
{
	RECT rcPlate;
	RECT rcFacePos[20];                     //��������
	int nFaceCount;                         //������
	DWORD32 dwCarID;
	DWORD32 dwWidth;
	DWORD32 dwHeight;
	DWORD64 dw64TimeMS;
}RECORD_IMAGE_INFO_EX;

//���ͼƬ�ṹ��
typedef struct _RECORD_IMAGE_EX
{
	RECORD_IMAGE_INFO_EX	cImgInfo;
	PBYTE pbImgInfo;
	PBYTE pbImgData;
	DWORD dwImgInfoLen;
	DWORD dwImgDataLen;
}RECORD_IMAGE_EX;
//��Ƶ�ṹ��
typedef struct _RECORD_VIDEO_ILLEGAL
{
	PBYTE pbVideoInfo;
	PBYTE pbVideoData;
	DWORD dwVideoInfoLen;
	DWORD dwVideoDataLen;
	DWORD dwCarID;
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD64 dw64TimeMS;
	DWORD dwChannelID;
}RECORD_VIDEO_ILLEGAL;

//���ͼƬ���ṹ��
typedef struct _RECORD_IMAGE_GROUP_EX
{
	RECORD_IMAGE_EX	cBestSnapshot;
	RECORD_IMAGE_EX	cLastSnapshot;
	RECORD_IMAGE_EX	cBeginCapture;
	RECORD_IMAGE_EX	cBestCapture;
	RECORD_IMAGE_EX	cLastCapture;
	RECORD_IMAGE_EX	cPlatePicture;
	RECORD_IMAGE_EX	cPlateBinary;
	RECORD_IMAGE_EX cComposePicture;  //ITTS �ϳ�ͼ
	RECORD_VIDEO_ILLEGAL cIllegalVideo;
}RECORD_IMAGE_GROUP_EX;

typedef struct _PACK_RESUME_HEADER
{
	DWORD32 dwType;
	DWORD32 dwInfoLen;
	DWORD32 dwDataLen;

}PACK_RESUME_HEADER;


#define MAX_INFOR_LEN 3*1024*1024
#define MAX_DATA_LEN 10*1024*1024

#define DEFAULT_INFOR_LEN 1024*1024
#define DEFAULT_DATA_LEN  3*1024*1024

#define PROTOCOL_MERCURY	1
#define PROTOCOL_EARTH	2

typedef enum
{
	PACK_TYPE_HEADER 
	, PACK_TYPE_INFO
	, PACK_TYPE_DATA

}PACK_TYPE;

//�ϵ�������¼������������������¼��
typedef struct _PACK_RESUME_CACHE
{
	PACK_RESUME_HEADER header;
	BOOL fVailHeader;			

	CHAR* pInfor;
	INT nMaxInforLen;
	INT nInforLen;
	BOOL fVailInfor;

	CHAR* pData;
	INT nMaxDataLen;
	INT nDataLen;
	BOOL fVailData;

	INT nDataOffset;
	INT nInfoOffset;

	_PACK_RESUME_CACHE()
		: nInforLen(0)
		, nDataLen(0)
		, fVailData(FALSE)
		, fVailInfor(FALSE)
		, fVailHeader(FALSE)
		, pInfor(NULL)
		, nMaxInforLen(0)
		, pData(NULL)
		, nMaxDataLen(0)
		, nDataOffset(0)
		, nInfoOffset(0)
	{
		ZeroMemory((void*)&header , sizeof(header));

	}

}PACK_RESUME_CACHE;

// ˮ��Э����������/���������
typedef enum {
	XML_CMD_TYPE_NULL,       // �������Ҳ�޳���
	XML_CMD_TYPE_CUSTOM,     // �ɴ������ж��������ʽ
	XML_CMD_TYPE_INT,
	XML_CMD_TYPE_DOUBLE,
	XML_CMD_TYPE_FLOAT,
	XML_CMD_TYPE_BOOL,
	XML_CMD_TYPE_DWORD,
	XML_CMD_TYPE_STRING,
	XML_CMD_TYPE_BIN,
	XML_CMD_TYPE_INTARRAY1D,
	XML_CMD_TYPE_INTARRAY2D
} XML_CMD_TYPE;

#define KEYNAME_MAX_SIZE	128
#define KEYVALUE_MAX_SIZE	512

typedef struct _CXmlParseInfo
{
	CHAR		szKeyName[KEYNAME_MAX_SIZE];
	CHAR		szKeyValue[KEYVALUE_MAX_SIZE];
	INT			nKeyValueLen;
	XML_CMD_TYPE eKeyType; 
	_CXmlParseInfo()
	{
		szKeyName[0]='\0';
		szKeyValue[0]='\0';
		nKeyValueLen = KEYVALUE_MAX_SIZE;
		eKeyType = XML_CMD_TYPE_NULL;
	}
}CXmlParseInfo;

#define HX_TYPE		    "TYPE"
#define HX_TYPE_INT     "INT"
#define HX_TYPE_STRING  "STRING"
#define HX_TYPE_BIN     "BIN"
#define HX_TYPE_FLOAT   "FLOAT"
#define HX_CMDNAME		"CmdName"
#define HX_VALUE		"Value"
#define HX_RECODE		"Value"
#define HX_RETMSG		"RetMsg"

const INT E_SendCmdHeadFail = 0;
const INT E_SendCmdDataFail = 1;
const INT E_RecCmdHeadFail = 2;
const INT E_RecCmdDataFail = 3;
const INT S_RecCmdHead_CmdIDNotMatch_OR_CmdRespondResultNotSuccess = 4;
const INT E_NullPoint = 5;
const INT S_ArrRoomNotEnough = 6;
const INT E_NewMemoryFail = 7;
const INT S_CanNotConnectDevice = 8;
const INT UNKNOWN = 0xFFFFFFFF;

// ��ʼ��WSA
bool InitWSA();

// ����ʼ��WSA
bool UnInitWSA();

// ����SOCKET
SOCKET HvCreateSocket(int af=AF_INET, int type=SOCK_STREAM, int protocol=0);

// ���ý��ճ�ʱ
HRESULT HvSetRecvTimeOut(const SOCKET& hSocket, int iMS);

// ���÷��ͳ�ʱ
HRESULT HvSetSendTimeOut(const SOCKET& hSocket, int iMS);

// ����һ�������
HRESULT HvListen(const SOCKET& hSocket, int nPort, int backlog);

// �ȴ�һ�������
HRESULT HvAccept(const SOCKET& hSocket, SOCKET& hNewSocket, int iTimeout/*=-1*/);



//��ʼ��GDI
void GdiInitialized(void);

void LoadIniConfig(void);

// ����һ���
bool ConnectCamera(char* szIp, WORD wPort, SOCKET& hSocket, int iTryTimes = 8, int iReciveTimeOutMS = 6000 );

// ǿ�ƹر�socket
int ForceCloseSocket(SOCKET &s);

// д��־
void HV_WriteLog(const char *pszLog);

// ��ȫ�ر��߳�
void HvSafeCloseThread(HANDLE& hThread);

// ��������socket�ϵ�����
int RecvAll(SOCKET socket, char *pBuffer, int iRecvLen);

// ��������socket�ϵ�����,�����������ӵ��ĳ���
int RecvAll(SOCKET socket, char *pBuffer, int iRecvLen , int& iRealRecvLen) ;

// ����ִ��xmlЭ������
bool ExecXmlExtCmd(char* szIP, char* szXmlCmd, char* szRetBuf, int& nBufLen, WORD wAddPort);

//����ִ��XMLЭ������
bool ExecXmlExtCmd(char* szXmlCmd, char* szRetBuf,
				   int& iBufLen, SOCKET sktSend, WORD wAddPort);


//��ȡЭ��汾
PROTOCOL_VERSION GetProtocolVersion(char* szIP, WORD wAddPort);

//��ȡXMLЭ������
//HRESULT HvGetXmlProtocolVersion(char* szIP, DWORD* pdwVersionType);

//��ȡ�豸��չ��Ϣ
HRESULT HvGetDeviceExteInfo(int iIndex, LPSTR lpExtInfo, int iBufLen);
// ����Xml����
int BuildHvCmdXml(
			char* pXmlBuf,
			char* pCmdName,
			int iArgCount,
			const char rgszName[][IVN_MAX_SIZE],
			const char rgszValue[][IVN_MAX_SIZE]
				  );
 // ��HvXmlЭ����Ϣ�� ��ȡָ�������� Vaule(String)
HRESULT GetParamStringFromXml(
			const TiXmlElement* pCmdArgElement,
			const char *pszParamName,
			char *pszParamValue,
			int nParamValueSize
			);

// ��HvXmlЭ����Ϣ�� ��ȡָ�������� Vaule(int) 
HRESULT GetParamIntFromXml(
			const TiXmlElement* pCmdArgElement,
			const char *pszParamName,
			int *pnParamValue
			);

// ��XML�н��� ָ������
HRESULT	HvXmlParse( CHAR* szXmlCmdName , CHAR* szXml , INT nXmlLen, CXmlParseInfo* prgXmlParseInfo , INT nXmlParseInfoCount );
// ��XML�н��� ָ������
HRESULT	HvXmlParseMercury( const CHAR* szXmlCmdName , CHAR* szXml , INT nXmlLen, CXmlParseInfo* prgXmlParseInfo , INT nXmlParseInfoCount );

HRESULT HvGetNonGreedyMatchBetweenBeginLabelAndEndLabel(const CHAR* szBeginLabel,const  CHAR* szEndLabel,const  CHAR* pszRetMsg, INT nRetMsgLen, CHAR* szJieQuReslut, INT nJieQuReslutLen );

// ��XML�н��� ָ������  onlyfor 
HRESULT	HvXmlParseMercuryMulti( CHAR* szXmlCmdName , CHAR* szXml , INT nXmlLen, CXmlParseInfo* prgXmlParseInfo , INT nXmlParseInfoCount );

// �жϼ�����Xml��Xml�ַ������������Xml���ݣ�szOutXmlBuf�������㹻�Ŀռ�
HRESULT HvMakeXmlCmdByString(
	PROTOCOL_VERSION emProtocolVersion,
	const char* inXmlOrStrBuf, 
	int nInlen, 
	char* szOutXmlBuf, 
	int& nOutlen
);

// �жϼ�����Xml��Xml�ַ������������Xml���ݣ�szOutXmlBuf�������㹻�Ŀռ�
HRESULT HvMakeXmlCmdByString1(
	const char* inXmlOrStrBuf, 
	int nInlen, 
	char* szOutXmlBuf, 
	int& nOutlen
);

// �жϼ�����Xml��Xml�ַ�����Ϣ��������Xml���ݣ�szOutXmlBuf�������㹻�Ŀռ�
HRESULT HvMakeXmlCmdByString2(
	const char* inXmlOrStrBuf,
	int nInlen, 
	char* szOutXmlBuf, 
	int& nOutlen);

// ˮ��Э�飬�жϼ�����Xml��Xml�ַ�����Ϣ��������Xml���ݣ�szOutXmlBuf�������㹻�Ŀռ�
HRESULT HvMakeXmlCmdByString3(
	const char* inXmlOrStrBuf, 
	int nInlen, 
	char* szOutXmlBuf, 
	int& nOutlen);

// �жϼ�����Xml��Xml�ַ�����Ϣ��������Xml���ݣ�szOutXmlBuf�������㹻�Ŀռ�
HRESULT HvMakeXmlInfoByString(
    PROTOCOL_VERSION emProtocolVersion,
	const char* inXmlOrStrBuf, 
	int nInlen, 
	char* szOutXmlBuf, 
	int& nOutlen
);

// ��HvXmlЭ������ִ�з��صĽ���н�����������
HRESULT HvParseXmlCmdRespRetcode(char* szXmlBuf, char* szCommand);

// ��HvXmlЭ������ִ�з��صĽ���н����������ı���Ϣ
HRESULT HvParseXmlCmdRespMsg(char* szXmlBuf, char* szMsgID, char* szMsgOut);

//��XML2.0Э����Ϣ����ִ�з��صĽ���н�����ָ����Ϣ
HRESULT HvParseXmlCmdRespRetcode2(char* szXmlBuf, char* szCmdName, char* szCmdValueName, char* szCmdValueText);

//��XML2.0Э����Ϣ����ִ�з��صĽ���н�����ָ����Ϣ
HRESULT HvParseXmlCmdRespRetcode2Adv(char* szXmlBuf, const char* szCmdName, char* szCmdValueName, char* szCmdValueText, int* pnCmdValueTextLen);

//��XML3.0Э����Ϣ����ִ�з��صĽ���н�����ָ����Ϣ
HRESULT HvParseXmlCmdRespRetcode3(char* szXmlBuf, char* szCmdName, char* szCmdValueName, char* szCmdValueText);

//����connectIP�ַ���
HRESULT ParseConnectIP(const CHAR* szIn, const CHAR* szPre, CHAR* szOut, INT *pnszOut);

// ��HvXmlЭ����Ϣ��ȡִ�з��صĽ���н�����ָ����Ϣ
HRESULT HvParseXmlInfoRespValue(
	char* szXmlBuf,
	char* szInfoName, 
	char* nInfoValueName,
	char* szInfoValueText
);

// ����:	ת��YUV���ݳ�BMP��ʽ
// ����:	pbDest			���BMP���ݵĻ�����ָ��;
//			iDestBufLen		�����������С
//			piDestLen		ʵ��������ݴ�С
//			pbSrc			����YUV���ݵĻ�����ָ��;
//			iSrcWidth		ͼ����;
//			iSrcHeight		ͼ��߶�;
// ����ֵ:  ����S_OK, ��ʾ�����ɹ�,
//          ����E_POINTER, �����а����зǷ���ָ��;
//          ����E_FAIL, ��ʾδ֪�Ĵ����²���ʧ��;
HRESULT Yuv2BMP(
	BYTE* pbDest,
	int iDestBufLen,
	int* piDestLen,
	BYTE* pbSrc,
	int iSrcWidth,
	int iSrcHeight
);

// ��ֵͼ����ת��ΪBMP��ʽ
void Bin2BMP(PBYTE pbBinData, PBYTE pbBmpData, INT& nBmpLen);

// ���������������е���Ƶ�����豸�������豸��Ŀ
HRESULT SearchHVDeviceCount(DWORD32 *pdwCount);

// ����������ѯ�豸ip��ַ
HRESULT GetHVDeviceAddr(
	int iIndex,
	DWORD64 *pdw64MacAddr,
	DWORD32 *pdwIP,
	DWORD32 *pdwMask,
	DWORD32 *pdwGateway
);

// ͨ���豸MAC��ַ�޸��豸��IP��ַ
HRESULT SetIPFromMac(DWORD64 dw64MacAddr, DWORD32 dwIP, DWORD32 dwMask, DWORD32 dwGateway);

// ��IP��ַ�ɶ�����ת��Ϊ���ʮ�����ַ�����ʽ
BOOL MyGetIpString(DWORD dwIP, LPSTR lpszIP);

// ��MAC��ַ�ɶ�����ת��Ϊ'-'��ʮ�������ַ�����ʽ
BOOL MyGetMacString(DWORD64 dwMac, LPSTR lpszMac, DWORD dwDevType);

//��������
HRESULT HvSendXmlCmd(LPCSTR szCmd, LPSTR szRetBuf, INT iBufLen, INT* piRetLen, DWORD dwXmlVersion, SOCKET sktSend, WORD wAddPort);

//ͨ��ָ����SOCKET����Xml����
HRESULT HvSendXmlCmd(char* szIP, LPCSTR szCmd, LPSTR szRetBuf,
					 INT iBufLen, INT* piRetLen, SOCKET sktSend, WORD wAddPort);
//ͨ��ָ����SOCKETִ��Xml����
bool ExecXmlExtCmdEx(char* szIP, char* szXmlCmd, char* szRetBuf,
					 int& iBufLen, SOCKET sktSend, WORD wAddPort);

//ͨ��ָ����SOCKETִ��Xml���ˮ��Э�飩
bool ExecXmlExtCmdMercury(char* szIP, char* szXmlCmd, char* szRetBuf,
					 int& iBufLen, SOCKET sktSend, WORD wAddPort);

HRESULT HvGetRecordImage_Mercury(const char* szAppendInfo, PBYTE pbRecordData, DWORD dwRecordDataLen, RECORD_IMAGE_GROUP_EX* pcRecordImage);
HRESULT HvGetRecordImage(PBYTE pbRecordData, DWORD dwRecordDataLen, RECORD_IMAGE_GROUP_EX* pcRecordImage);

HRESULT HvEnhanceTrafficLight(PBYTE pbSrcImg, DWORD dwiSrcImgDataLen, int iRedLightCount,
							  PBYTE pbRedLightPos, PBYTE pbDestImgBuf, DWORD& dwDestImgBufLen,
							  INT iBrightness, INT iHueThreshold, INT iCompressRate);

HRESULT ZBase64Encode( unsigned char* pSrcData, int nSrcByte ,  char* pDestData ,int* pnDestByte );
HRESULT ZBase64Decode( unsigned char* pSrcData, int nSrcByte ,  char* pDestData ,int* pnDestByte );

HRESULT ExecuteCmd( CHAR* pIP , CAMERA_COMMAND_TYPE eCmdId 
				   , CHAR* pCmdData , INT nCmdByte
				   , CHAR* pRetData , INT* pnRetByte , WORD wAddPort);
HRESULT SearchDeviceEx( CDevBasicInfo* rgDevInfo , INT* pnDevCount );

HRESULT HvGetFirstParamNameFromXmlCmdAppendInfoMap(const CHAR* szCmdName, CHAR * szParamName, INT nParamNameLen);

HRESULT HvGetParamNameFromXmlCmdAppendInfoMap(const CHAR* szCmdName,  CXmlParseInfo* pXmlParseInfo, INT nXmlParseInfoNum);

int HvGetXmlForSetNameList( const CHAR* szValue, INT iValueLen, CHAR *szXmlBuff, INT iBuffLen);
bool HvGetNamListFromXML(const CHAR* szXmlBuff, CHAR* szWhiteNameList, CHAR* szBlackNameList);
int HvGetXmlForTriggerPlate( const CHAR* szValue, INT iValueLen, CHAR *szXmlBuff, INT iBuffLen);
bool HvGetRetMsgFromXml(const CHAR* szXmlBuff, CHAR* szRetMsg);
int HvGetXmlOfStringType(const CHAR* szCMD, const CHAR* szClass, const CHAR* szValue, CHAR *szXmlBuff);
HRESULT HvGetDeviceType(LPCSTR szDeviceIp, WORD wPort, PROTOCOL_VERSION sProtocol, CHAR* szDeviceType);

#endif // _HVDEVICEUTILS_H_
