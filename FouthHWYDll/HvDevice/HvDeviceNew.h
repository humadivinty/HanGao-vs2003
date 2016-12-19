#ifndef _HVDEVICENEW_H__
#define _HVDEVICENEW_H__

#include "HvDeviceBaseType.h"
#include "HvDeviceCommDef.h"
#include <vector>
using namespace std;

#ifdef HVDEVICE_EXPORTS
#define HV_API_EX extern "C" __declspec(dllexport)
#elif HVDEVICE_LIB
#define HV_API_EX
#else
#define HV_API_EX extern "C" __declspec(dllimport)
#endif

#define HVAPI_API_VERSION_EX	"2.0"
typedef PVOID HVAPI_HANDLE_EX;         /**< HvAPI������� */


/**
* @brief			ʶ������ʼ�ص�����
* @param[out]		pUserData		��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		dwCarID			����ID
* @return			0
*/
typedef INT (CDECL* HVAPI_CALLBACK_RECORD_INFOBEGIN)(PVOID pUserData, DWORD dwCarID);

/**
* @brief			ʶ���������ص�����
* @param[out]		pUserData		��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		dwCarID			����ID
* @return			0
*/
typedef INT (CDECL* HVAPI_CALLBACK_RECORD_INFOEND)(PVOID pUserData, DWORD dwCarID);

/**
* @brief			���ƻص�����
* @param[out]		pUserData		��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		dwCarID			����ID
* @param[out]		pcPlateNo		�����ַ���
* @param[out]		pcAppendInfo	���Ƹ�����Ϣ
* @param[out]		dw64TimeMS		ʶ��ʱ��
* @return			0
*/
typedef INT (CDECL* HVAPI_CALLBACK_RECORD_PLATE)(PVOID pUserData,
												 DWORD dwCarID,
												 LPCSTR pcPlateNo,
												 LPCSTR pcAppendInfo,
												 DWORD dwRecordType,
												 DWORD64 dw64TimeMS);

/**
* @brief			ʶ������ͼ�ص�����
* @param[out]		pUserData		��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		dwCarID			����ID
* @param[out]		wImgType		��ͼ����
* @param[out]		wWidth			��ͼ��
* @param[out]		wHeight			��ͼ��
* @param[out]		pbPicData		��ͼ����
* @param[out]		dwImgDataLen	��ͼ���ݳ���
* @param[out]		dw64TimeMS		ʶ��ʱ��
* @return			0
*/
typedef INT (CDECL* HVAPI_CALLBACK_RECORD_BIGIMAGE)(PVOID pUserData,
													DWORD dwCarID, 
													WORD  wImgType,
													WORD  wWidth,
													WORD  wHeight,
													PBYTE pbPicData,
													DWORD dwImgDataLen,
													DWORD dwRecordType,
													DWORD64 dw64TimeMS);



/**
* @brief			ʶ��������Сͼ�ص�����
* @param[out]		pUserData		��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		dwCarID			����ID
* @param[out]		wWidth			Сͼ��
* @param[out]		wHeight			Сͼ��
* @param[out]		pbPicData		Сͼ����
* @param[out]		dwImgDataLen	Сͼ���ݳ���
* @param[out]		dw64TimeMS		ʶ��ʱ��
* @return			0
*/
typedef INT (CDECL* HVAPI_CALLBACK_RECORD_SMALLIMAGE)(PVOID pUserData,
													  DWORD dwCarID,
													  WORD wWidth,
													  WORD wHeight,
													  PBYTE pbPicData,
													  DWORD dwImgDataLen,
													  DWORD dwRecordType,
													  DWORD64 dw64TimeMS);

/**
* @brief			ʶ�������ƶ�ֵͼ�ص�����
* @param[out]		pUserData		��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		dwCarID			����ID
* @param[out]		wWidth			��ֵͼ��
* @param[out]		wHeight			��ֵͼ��
* @param[out]		pbPicData		��ֵͼ����
* @param[out]		dwImgDataLen	��ֵͼ���ݳ���
* @param[out]		dw64TimeMS		ʶ��ʱ��
* @return			0
*/
typedef INT (CDECL* HVAPI_CALLBACK_RECORD_BINARYIMAGE)(PVOID pUserData,
													   DWORD dwCarID,
													   WORD wWidth,
													   WORD wHeight,
													   PBYTE pbPicData,
													   DWORD dwImgDataLen,
													   DWORD dwRecordType,
													   DWORD64 dw64TimeMS);

/**
* @brief			Υ����Ƶ�ص�����
* @param[out]		pUserData			��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		dwCarID				����ID
* @param[out]		dwVideoType			��Ƶ֡����
* @param[out]		dwVideoWidth		��Ƶ�Ŀ�
* @param[out]		dwVideoHeight		��Ƶ�ĸ�
* @param[out]		dw64TimeMS			��Ƶʱ��
* @param[out]		pbVideoData			��Ƶ֡����
* @param[out]		dwVideoDataLen		��Ƶ֡���ݳ���
* @param[out]		szVideoExtInfo		��Ƶ֡��Ϣ
* @return			0
*/
typedef INT (CDECL* HVAPI_CALLBACK_RECORD_ILLEGALVideo)(PVOID pUserData,
													   DWORD dwCarID,													   
													   DWORD dwVideoType,
													   DWORD dwVideoWidth,
													   DWORD dwVideoHeight,
													   DWORD64 dw64TimeMS,
													   PBYTE pbVideoData,
													   DWORD dwVideoDataLen,
													   LPCSTR szVideoExtInfo);

/**
* @brief			ʶ������Ϣ�ص�����
* @param[out]		pUserData		��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		pString			��Ϣ�ַ���
* @param[out]		dwStrLen		��Ϣ�ַ�������
* @return			0
*/
typedef INT (CDECL* HVAPI_CALLBACK_STRING)(PVOID pUserData, LPCSTR pString, DWORD dwStrLen);

/**
* @brief			�״���Ϣ�ص�����
* @param[out]		pUserData		��HVAPI_StartRecvRadarData���õĴ���ص��������û�����ָ��
* @param[out]		pRadarData		�״�����
* @param[out]		dwRadarDataLen	�״����ݳ���
* @return			0
*/
typedef  INT (CDECL* HVAPI_CALLBACK_RADAR)(PVOID pUserData, PBYTE pRadarData, DWORD dwRadarDataLen);

/**
* @brief			ʶ������Ϣ�ص�����
* @param[out]		pUserData		��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		pString			��Ϣ�ַ���
* @param[out]		dwStrLen		��Ϣ�ַ�������
* @param[out]		dwType			��Ϣ�ַ������� ��ʷ��ʵʱ
* @return			0
*/
typedef INT (CDECL* HVAPI_CALLBACK_TFD_STRING)(PVOID pUserData, LPCSTR pString, DWORD dwStrLen, DWORD dwType);


/**
* @brief			ͼƬ�ص�����
* @param[out]		pUserData			��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		pbImageData			ͼƬ����
* @param[out]		dwImageDataLen		ͼƬ���ݳ���
* @param[out]		dwImageType			ͼƬ����
* @param[out]		szImageExtInfo		ͼƬ��Ϣ
* @return			0
*/
typedef INT (CDECL* HVAPI_CALLBACK_JPEG)(PVOID pUserData,
										 PBYTE pbImageData,
										 DWORD dwImageDataLen,
										 DWORD dwImageType,
										 LPCSTR szImageExtInfo);

/**
* @brief			��Ƶ�ص�����
* @param[out]		pUserData			��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		pbVideoData			��Ƶ֡����
* @param[out]		dwVideoDataLen		��Ƶ֡���ݳ���
* @param[out]		dwVideoType			��Ƶ֡����
* @param[out]		szVideoExtInfo		��Ƶ֡��Ϣ
* @return			0
*/
typedef INT (CDECL* HVAPI_CALLBACK_H264)(PVOID pUserData,
										 PBYTE pbVideoData,
										 DWORD dwVideoDataLen,
										 DWORD dwVideoType,
										 LPCSTR szVideoExtInfo);

/**
* @brief			��ʷ��Ƶ�ص�����
* @param[out]		pUserData			��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		pbVideoData			��Ƶ֡����
* @param[out]		dwVideoDataLen		��Ƶ֡���ݳ���
* @param[out]		dwVideoType			��Ƶ֡����
* @param[out]		szVideoExtInfo		��Ƶ֡��Ϣ
* @return			�ɹ�S_OK ʧ�� E_FAILE
*/
typedef INT (CDECL* HVAPI_CALLBACK_HISTORY_VIDEO)(PVOID pUserData,
												  PBYTE pbVideoData,
												  DWORD dwVideoDataLen,
												  DWORD dwVideoType,
												  LPCSTR szVideoExtInfo);


//�ص������Ķ���

/**
* @brief               ��Ƶ�ص�����
* @param[out]          pUserData          ��HVAPI_StartRecvH264Video���õĴ���ص��������û�����ָ��
* @param[out]          dwVedioFlag        ��Ƶ��� ����Ч���ݱ�ǡ���Ч���ݱ�ǡ���ʷ�������
* @param[out]          dwVideoType        ��Ƶ���� ����ʷ��Ƶ��ʵʱ��Ƶ
* @param[out]          dwWidth            ���
* @param[out]          dwHeight			  �߶�
* @param[out]          dw64TimeMS         ��Ƶʱ��
* @param[out]          pbVideoData        ��Ƶ֡����
* @param[out]          dwVideoDataLen     ��Ƶ֡����
* @param[out]          szVideoExtInfo     ��Ƶ������Ϣ
* @return              �ɹ�S_OK ʧ�� E_FAILE
*/
typedef INT (CDECL* HVAPI_CALLBACK_H264_EX)(
												PVOID pUserData,  
												DWORD dwVedioFlag,
												DWORD dwVideoType, 
												DWORD dwWidth,
												DWORD dwHeight,
												DWORD64 dw64TimeMS,
												PBYTE pbVideoData, 
												DWORD dwVideoDataLen,
												LPCSTR szVideoExtInfo
												);

/**
* @brief               jpeg���ص�����
* @param[out]          pUserData          ��HVAPI_StartRecvH264Video���õĴ���ص��������û�����ָ��
* @param[out]          dwImageFlag        ͼƬ��� ����ЧͼƬ���ݡ���ЧͼƬ����
* @param[out]          dwImageType        ͼƬ���� ��������������������
* @param[out]          dwWidth            ���
* @param[out]          dwHeight			  �߶�
* @param[out]          dw64TimeMS         JPEGʱ��
* @param[out]          pbImageData        ͼƬ֡����
* @param[out]          dwImageDataLen     ͼƬ֡����
* @param[out]          szImageExtInfo     JPEG������Ϣ
* @return              �ɹ�S_OK ʧ�� E_FAILE
*/

typedef INT (CDECL* HVAPI_CALLBACK_JPEG_EX)(
											PVOID pUserData,  
											DWORD dwImageFlag,
											DWORD dwImageType, 
											DWORD dwWidth,
											DWORD dwHeight,
											DWORD64 dw64TimeMS,
											PBYTE pbImageData, 
											DWORD dwImageDataLen,
											LPCSTR szImageExtInfo
											);

/**
* @brief               ʶ�����ص�����
* @param[out]          pUserData          ��HVAPI_StartRecvResult���õĴ���ص��������û�����ָ��
* @param[out]          dwResultFlag		  �����־����Ч�����ǡ���Ч�����ǡ�������ʷ�������
* @param[out]          dwResultType		  ������ͣ�ʵʱ�������ʷ���
* @param[out]          dwCarID            ���ID
* @param[out]          pcPlateNo          �����ַ���
* @param[out]          dw64TimeMS		  ���ʱ��
* @param[out]          pPlate			  ����Сͼ
* @param[out]          pPlateBin          ���ƶ�ֵͼ
* @param[out]          pBestSnapshot      ��������ͼ
* @param[out]          pLastSnapshot      ����ͼ
* @param[out]          pBeginCapture      ��һ��ץ��ͼ
* @param[out]          pBestCapture       �ڶ���ץ��ͼ
* @param[out]          pLastCapture       ������ץ��ͼ
* @return              �ɹ�S_OK ʧ�� E_FAILE
*/
//ע�� plate ��ͼ Сͼ ��άͼ �ش���dwCardID��Ϣ��_string �� _tfd_string��dwCardID��Ϣ
typedef INT (CDECL* HVAPI_CALLBACK_RESULT)(
	PVOID pUserData, 
	DWORD dwResultFlag,			
	DWORD dwResultType,		
	DWORD dwCarID,
	LPCSTR pcPlateNo,
	LPCSTR pcAppendInfo,
	DWORD64 dw64TimeMS,
	CImageInfo   Plate,
	CImageInfo   PlateBin,
	CImageInfo   BestSnapshot,
	CImageInfo   LastSnapshot,
	CImageInfo   BeginCapture,
	CImageInfo   BestCapture,
	CImageInfo   LastCapture
	);

/**
* @brief               ���ο�������ص�����
* @param[out]          pUserData          ��HVAPI_StartRecvReDevelopResult���õĴ���ص��������û�����ָ��
* @param[out]          pbInfo        ����
* @param[out]          dwInfoLen     ����
* @param[out]          pbData        ͼƬ����
* @param[out]          dwDataLen     ͼƬ����
* @param[out]          nWidth     ͼƬ���
* @param[out]          nHeight    ͼƬ�߶ȶ�
* @return              �ɹ�S_OK ʧ�� E_FAILE
*/
typedef INT (CDECL* HVAPI_CALLBACK_REDEVELOP_RESULT)(
	PVOID pUserData, 
	PBYTE pbInfo,
	DWORD dwInfoLen,
	PBYTE pbData,
	DWORD dwDataLen,
	INT nWidth,
	INT nHeight
	);


/**
* @brief			�����źŴ����ص�����
* @param[in]		pUserData		��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[in]		dwTime			����ʱ��
* @param[in]		dwRoadID		��·ͨ��ID
* @param[in]		dwTrigerID		����ID
* @return			0
*/
typedef INT (CDECL* HVAPI_CALLBACK_LISTEN_CMD)(PVOID pUserData,DWORD64 dwTime,DWORD dwRoadID,DWORD dwTrigerID);

/**
* @brief			�����źŴ����ص�������չ
* @param[in]		pUserData		��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[in]		pXMLData		XML��Ϣ
* @param[in]		iLen			XML���ݳ���
* @return			0
*/

typedef INT (CDECL* HVAPI_CALLBACK_LISTEN_CMDEX)(PVOID pUserData,LPCSTR pXMLData,INT iLen);


/**
* @brief		�����豸
* @param[out]	pdwDeviceCount		  �豸��
* @return		�ɹ�S_OK ʧ�� E_FAILE
*/
HV_API_EX HRESULT HVAPI_SearchDeviceCount(DWORD32* pdwDeviceCount);

/**
* @brief		��ȡ�豸IP
* @param[in]	dwIndex			����ʱ���������λ��
* @param[out]	dw64MacAddr		�豸MAC��ַ
* @param[out]	dwIP			�豸IP
* @param[out]	dwMask			����
* @param[out]	dwGateWay		����
* @return		�ɹ�S_OK ʧ�� E_FAILE
*/
HV_API_EX HRESULT HVAPI_GetDeviceAddr(DWORD32 dwIndex, DWORD64* dw64MacAddr, DWORD32* dwIP,
								   DWORD32* dwMask, DWORD32* dwGateWay);

/**
* @brief		    �����½ӿ� ע�ʹ�����
* @param[in,out]	rgDevInfo	���������豸��Ϣ�ṹ������
* @param[in,out]	pnDevCount	���������豸����
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL, ����ṹ������̫�٣�S_FALSE 
*/
HV_API_EX HRESULT CDECL HVAPI_SearchDeviceEx( CDevBasicInfo* rgDevInfo , INT* pnDevCount );

/**
* @brief		ͨ��MAC��ַ�����豸IP
* @param[in]	dw64MacAddr		�豸MAC��ַ
* @param[in]	dwIP			�豸IP
* @param[in]	dwMask			����
* @param[in]	dwGateWay		����
* @return		�ɹ�S_OK ʧ�� E_FAILE
*/
HV_API_EX HRESULT CDECL HVAPI_SetIPByMacAddr(DWORD64 dw64MacAddr, DWORD32 dwIP, DWORD32 dwMask, DWORD32 dwGateway);

/**
* @brief		������������Ϣ���ȡ�豸������Ϣ
* @param[in]	dwIndex			����ʱ���������λ��
* @param[out]	lpExtInfo		�豸������Ϣ����
* @param[in]	iBufLen			�豸������Ϣ���泤��
* @return		�ɹ�S_OK ʧ�� E_FAILE
*/
HV_API_EX HRESULT HVAPI_GetDeviceInfoEx(int iIndex, LPSTR lpExtInfo, int iBufLen);

/**
* @brief		��ȡ�豸����
* @param[in]	pcIP		�豸IP
* @param[out]	iDeviceType	�豸����
* @return		�ɹ�S_OK ʧ�� E_FAILE
*/
HV_API_EX HRESULT CDECL HVAPI_GetDevTypeEx(PSTR pcIP, int* iDeviceType);

/**
* @brief			���豸���
* @param[in]		szIp			�豸��IP��ַ
* @param[in]		szApiVer		��Ӧ�豸��API�汾��ע��ΪNULL��Ĭ��HVAPI_API_VERSION
* @return			�ɹ����豸�����ʧ�ܣ�NULL
*/
HV_API_EX HVAPI_HANDLE_EX CDECL HVAPI_OpenEx(LPCSTR szIp, LPCSTR szApiVer);

/**
* @brief			�ر��豸���
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_CloseEx(HVAPI_HANDLE_EX hHandle);


/**
* @brief			��ȡ�����豸ʹ�õ�XMLЭ��汾
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[out]		pemProtocolVersion	������ʹ�õ�XMLЭ��汾
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetXmlVersionEx(HVAPI_HANDLE_EX hHandle, PROTOCOL_VERSION* pemProtocolVersion);


/**
* @brief			��ȡ�����豸ʹ�õ�Э��汾
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[out]		pemProtocolVersion	������ʹ�õ�Э��汾
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetProtocolVersionEx(HVAPI_HANDLE_EX hHandle, PROTOCOL_VERSION* pemProtocolVersion);


/**
* @brief			��ȡ����״̬
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		nStreamType		���������ͣ������������ͣ�
* @param[out]		pdwConnStatus	�����ӵĵ�ǰ״̬
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetConnStatusEx(HVAPI_HANDLE_EX hHandle, INT nStreamType, DWORD* pdwConnStatus);


/**
* @brief			��ȡ��������
* @param[in]		hHandle				��Ӧ�豸����Ч���
* @param[in]		nStreamType			���������ͣ������������ͣ�
* @param[out]		pdwReConnectTimes	�����ӵĵ�ǰ��������
* @param[in]		fIsReset			��ȡ����Ƿ񽫸����ӵ�������������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetReConnectTimesEx(HVAPI_HANDLE_EX hHandle, INT nStreamType, DWORD* pdwReConnectTimes, BOOL fIsReset);


/**
* @brief			ִ������
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szCmd			�������豸����ĳ��������ַ���
* @param[in]		szRetBuf		���ص�ִ�н��(XML��ʽ)
* @param[in]		nBufLen			szRetBuf�������ĳ���
* @param[out]		pnRetLen		ʵ�ʷ��ص�ִ�н�����ȡ�ע��ΪNULL����Ըò�����
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_ExecCmdEx(HVAPI_HANDLE_EX hHandle,
								   LPCSTR szCmd,
								   LPSTR szRetBuf,
								   INT nBufLen,
								   INT* pnRetLen);

/**
* @brief			��ȡ�豸����
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szParamDoc		��ȡ���Ĳ�����XML��ʽ��
* @param[in]		nBufLen			szParam�������ĳ���
* @param[out]		pnRetLen		ʵ�ʷ��صĲ������ȡ�ע��ΪNULL����Ըò�����
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetParamEx(HVAPI_HANDLE_EX hHandle,
									LPSTR szParamDoc,
									INT nBufLen,
									INT* pnRetLen);

/**
* @brief			�����豸����
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szParamDoc		Ҫ���浽�豸�Ĳ�����XML��ʽ��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
* @warning			���Ĺ��Ĳ���Ҫ���豸�´�������Ż���Ч
*/
HV_API_EX HRESULT CDECL HVAPI_SetParamEx(HVAPI_HANDLE_EX hHandle, LPCSTR szParamDoc);

/**
* @brief			�ϴ����ذ���ư������ļ���һ���
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szParamDoc		Ҫ���浽�豸�Ĳ�����XML��ʽ��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
* @warning			���Ĺ��Ĳ���Ҫ���豸�´�������Ż���Ч
*/
HV_API_EX HRESULT CDECL HVAPI_SendControllPannelUpdateFileEx(HVAPI_HANDLE_EX hHandle,
														PBYTE pUpdateFileBuffer,
														DWORD dwFileSize);

/**
* @brief			�������������ջص�����
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		pFunc			�ص�����ָ�롣ע��ΪNULLʱ��ʾ�ر�nStreamType���͵���������
* @param[in]		pUserData		����ص��������û�����ָ��
* @param[in]		iVideoID		��Ƶͨ����Ŀǰֻʹ��0
* @param[in]		nStreamType		�ص�����������
* @param[in]		szConnCmd		��������������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetCallBackEx(HVAPI_HANDLE_EX hHandle, PVOID pFunc, PVOID pUserData,
									   INT iVideoID, INT iCallBackType, LPCSTR szConnCmd);

/**
* @brief              �״���Ϣ����
* @param[in]          hHandle				 �豸���
* @param[in]          pFunc					 �ص�����ָ��
* @param[in]          pUserData				 �û�����
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL  HVAPI_StartRecvRadarData
(
	HVAPI_HANDLE_EX  hHandle,
	PVOID  pFunc,
	PVOID  pUserData
 );

/**
* @brief              ֹͣ�״���Ϣ����
* @param[in]          hHandle			�豸���
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL  HVAPI_StopRecvRadarData
(
	HVAPI_HANDLE_EX  hHandle
 );

/**
* @brief              �����״���Ϣ
* @param[in]          hHandle				 �豸���
* @param[in]          pRadarInfo			 Ҫ���õ��״���Ϣ
* @param[in]          dwRadarInfoLen		 �״���Ϣ�ĳ���
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL  HVAPI_SetRadarInfo(HVAPI_HANDLE_EX hHandle,PBYTE  pRadarInfo, DWORD  dwRadarInfoLen);


/**
* @brief              ����H264����
* @param[in]          hHandle				�豸���
* @param[in]          pFunc				    �ص�����ָ��
* @param[in]          pUserData			    �û�����
* @param[in]          iVideoID				��Ƶͨ����Ŀǰֻʹ��0
* @param[in]          dw64BeginTimeMS       ��ʼʱ��
* @param[in]          dw64EndTimeMS         ����ʱ�� 
* @param[in]          dwRecvFlag            ���ձ�־ :ʵʱ��Ƶ����ʷ��Ƶ
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_StartRecvH264Video(
	HVAPI_HANDLE_EX hHandle,
	PVOID pFunc,
	PVOID pUserData,
	INT iVideoID ,       
	DWORD64 dw64BeginTimeMS,
	DWORD64 dw64EndTimeMS,
	DWORD dwRecvFlag
);
/**
* @brief              ֹͣH264����
* @param[in]          hHandle          �豸���
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_StopRecvH264Video(HVAPI_HANDLE_EX hHandle);


/**
* @brief              ����MJPEG����
* @param[in]          hHandle				 �豸���
* @param[in]          pFunc					 �ص�����ָ��
* @param[in]          pUserData				 �û�����
* @param[in]          iVideoID				 ��Ƶͨ����Ŀǰֻʹ��0
* @param[in]          dwRecvFlag			 ���ձ�־��������������������
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_StartRecvMJPEG(
					 HVAPI_HANDLE_EX hHandle,
					 PVOID pFunc,
					 PVOID pUserData,
					 INT iVideoID ,
					 DWORD dwRecvFlag
					 );
/**
* @brief              ֹͣMJPEG����
* @param[in]          hHandle          �豸���
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL  HVAPI_StopRecvMJPEG(HVAPI_HANDLE_EX hHandle);
/**
* @brief              ���ĵ���������״̬
* @param[in]          hHandle          �豸���
* @param[in]          fEnable          �Ƿ�򿪵�������
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetDebugJpegStatus(HVAPI_HANDLE_EX hHandle, BOOL fEnable);

/**
* @brief              �������ս��
* @param[in]          hHandle			�豸���
* @param[in]          pFunc				�ص�����ָ��
* @param[in]          pUserData			�û�����
* @param[in]          iVideoID          ��Ƶͨ����Ŀǰֻʹ��0
* @param[in]          dw64BeginTimeMS       ��ʼʱ��
* @param[in]          dw64EndTimeMS         ����ʱ��
* @param[in]          dwStartIndex			��ʼ֡��
* @param[in]          dwRecvFlag			���ձ�־
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_StartRecvResult(
						HVAPI_HANDLE_EX hHandle,
						PVOID pFunc,
						PVOID pUserData,
						INT iVideoID,
						DWORD64 dw64BeginTimeMS,
						DWORD64 dw64EndTimeMS,
						DWORD dwStartIndex,
						DWORD dwRecvFlag
					 );
/**
* @brief              ֹͣ�������
* @param[in]          hHandle          �豸���
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_StopRecvResult(HVAPI_HANDLE_EX hHandle);


/**
* @brief              ����״̬��Ϣ����
* @param[in]          hHandle				 �豸���
* @param[in]          pFunc					 �ص�����ָ��
* @param[in]          pUserData				 �û�����
* @param[in]          iVideoID				 ��Ƶͨ����Ŀǰֻʹ��
* @param[in]          dwRecvFlag			 ���ձ�־������
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_StartRecvMsg(
	HVAPI_HANDLE_EX hHandle,
	PVOID pFunc,
	PVOID pUserData,
	INT iVideoID ,
	DWORD dwRecvFlag
	);

/**
* @brief		�������ο����������
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL  HVAPI_StartRecvRedevelopResult
(
	HVAPI_HANDLE_EX hHandle,
	PVOID pFunc,
	PVOID pUserData
 );

/**
* @brief		ֹͣ���ο����������
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL  HVAPI_StopRecvRedevelopResult
(
	HVAPI_HANDLE_EX hHandle
);

/**
* @brief		�����źţ����ڿ�բ��
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
*@param[in]   iVideo		   ��Ƶ���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_TriggerSignal(HVAPI_HANDLE_EX hHandle, INT iVideoID);

/**
* @brief		���������źţ� ���ڿ��Ʊ����豸
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
������Ϊ�� SendAlarmTriggerOut
*/
HV_API_EX HRESULT CDECL HVAPI_TriggerAlarmSignal(HVAPI_HANDLE_EX hHandle);


/**
* @brief		����ڰ�����
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	szWhileNameList	 �������б�,������(����-��Ч��)��$������������:��A11111-2013010101$��A2222-2013010202$��A33333-2013020202   ���ָ��ΪNULL,��ʾ�����á�
* @param[in]	iWhileListLen		�������ַ�����
* @param[in]	szBlackNameList		�����ַ����� ������(����-��Ч��)��$������������:��A11111-2013010101$��A2222-2013010202$��A33333-2013020202   ���ָ���ʾ������
* @param[in]	iListLen		�����ַ������� 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_InportNameList(HVAPI_HANDLE_EX hHandle, CHAR* szWhileNaneList, INT iWhileListLen, CHAR* szBlackNameList, INT iBlackListLen);


/**
* @brief		��ȡ�ڰ�����
* @param[in]	hHandle	        ��Ӧ�豸����Ч��� 
* @param[out]	szWhileNameList		�������ַ����������� ������(����-��Ч��)��$������������:��A11111-2013010101$��A2222-2013010202$��A33333-2013020202   
* @param[in/out]	iWhileListLen		����������ָ�룬 ��������ͷ��� 
@param[out]	szBlackNameList		�������ַ����������� ������(����-��Ч��)��$������������:��A11111-2013010101$��A2222-2013010202$��A33333-2013020202   
* @param[in/out]	iBlackListLen		����������ָ�룬 ��������ͷ��� 

* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/

HV_API_EX HRESULT CDECL HVAPI_GetNameList(HVAPI_HANDLE_EX hHandle, CHAR* szWhileNameList, INT *iWhileListLen, CHAR* szBlackNameList, INT *iBlackListLen);


/**
* @brief              ֹͣ״̬��Ϣ����
* @param[in]          hHandle          �豸���
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL  HVAPI_StopRecvMsg(HVAPI_HANDLE_EX hHandle);

/**
* @brief			�����ַ�����
* @param[in]		hHandle					��Ӧ�豸����Ч���
* @param[in]		szCharacterDataBuff		��������
* @param[in]		nBuffLen				�������ݳ���
* @param[in]		nTopLeftX				�����ַ����Ͻ�����Xֵ
* @param[in]		nTopLeftY				�����ַ����Ͻ�����Yֵ
* @param[in]		nDateType				��������
* @param[in]		nSize					�����С�����أ�
* @param[in]		nR						RGB��Rֵ
* @param[in]		nG						RGB��Gֵ
* @param[in]		nB						RGB��Bֵ
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPIUTILS_SetCharacterValue(HVAPI_HANDLE_EX hHandle, const char* szCharacterDataBuff, 
												  INT nTopLeftX, INT nTopLeftY, INT nDateType, INT nSize, INT nR, INT nG, INT nB);

/**
* @brief			�����ͼ��ƼӺ�����
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		dwEnhanceStyle	�Ӻ촦��ģʽ 0���Ӻ� 1ֻ�Ӻ�Υ�½�� 2ȫ�Ӻ� 3ֻ�Ӻ�ץ��ͼ
* @param[in]		iBrightness		�Ӻ��ͼƬ������ǿ����
* @param[in]		iHubThreshold	���ɫ�ȷ�ֵ
* @param[in]		iCompressRate	�Ӻ촦���ͼƬѹ��Ʒ��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetEnhanceRedLightFlagEx(HVAPI_HANDLE_EX hHandle, DWORD dwEnhanceStyle, INT iBrightness, INT iHubThreshold, INT iCompressRate);

/**
* @brief			��ʷ���JPEGͼƬ֡��ƼӺ�����
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		dwEnhanceStyle	�Ӻ촦��ģʽ 0���Ӻ� 1�Ӻ�
* @param[in]		iBrightness		�Ӻ��ͼƬ������ǿ����
* @param[in]		iHubThreshold	���ɫ�ȷ�ֵ
* @param[in]		iCompressRate	�Ӻ촦���ͼƬѹ��Ʒ��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetHistoryVideoEnhanceRedLightFlagEx(HVAPI_HANDLE_EX hHandle, DWORD dwEnhanceStyle, INT iBrightness, INT iHubThreshold, INT iCompressRate);

/**
* @brief			Ԥ���ӿڣ������豸��չ�¹��ܺ��ȡ��ص���չ��Ϣ
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		dwType			��Ϣ����
* @param[in]		iBrightness		������Ϣ�Ļ����ַ
* @param[in/out]	iBrightness		������Ϣ�Ļ����ַ���Ⱥ�ʵ�ʷ�����Ϣ����
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetExtensionInfoEx(HVAPI_HANDLE_EX hHandle, DWORD dwType, LPVOID pRetData, INT* iBufLen);

/**
* @brief			�ӽ��������Ϣ�л�ȡĳ����Ϣ
* @param[in]		szAppened			���������Ϣ
* @param[in]		szInfoName			��ȡ����
* @param[out]		szRetInfo			����ִ�
* @param[in]		iRetInfoBufLen		����ִ����滺������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPIUTILS_GetRecordInfoFromAppenedStringEx(LPCSTR szAppened, LPCSTR szInfoName, LPSTR szRetInfo, INT iRetInfoBufLen);

/**
* @brief			�ӽ��������Ϣ����ȡȫ����Ϣÿ��Ŀ��Ϣʹ�ûس�������
* @param[in]		pszXmlPlateInfo			���������Ϣ
* @param[out]		pszPlateInfoBuf			����ִ�������
* @param[in]		iPlateInfoBufLen		����ִ�����������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPIUTILS_ParsePlateXmlStringEx(LPCSTR pszXmlPlateInfo, LPSTR pszPlateInfoBuf, INT iPlateInfoBufLen);

/**
* @brief			�������Сͼ����ת����BMP��ʽ
* @param[in]		pbSmallImageData		����Сͼ����
* @param[in]		nSmallImageWidth		����Сͼ��
* @param[in]		nSmallImageHeight		����Сͼ��
* @param[out]		pbBitmapData			ת�����BMP����
* @param[out]		pnBitmapDataLen			ת�����BMP���ݳ���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPIUTILS_SmallImageToBitmapEx(PBYTE pbSmallImageData, INT nSmallImageWidth, INT nSmallImageHeight, PBYTE pbBitmapData, INT* pnBitmapDataLen);

/**
* @brief			��ʶ������ֵͼת��ΪBMPλͼ
* @param[in]		pbBinImageData		ʶ������ֵͼ
* @param[in]		pbBitmapData		BMPλͼ���ݴ�Ż�����
* @param[in,out]	pnBitmapDataLen		BMPλͼ���ݴ�Ż��������ȡ��������غ���Ϊ��BMPλͼ����ʵ�ʳ���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPIUTILS_BinImageToBitmapEx(PBYTE pbBinImageData,
												 PBYTE pbBitmapData,
												 INT* pnBitmapDataLen);

/**
* @brief		������ִ�н��XML�ַ����л�ȡ��Ӧ��Ϣ
* @param[in]	fIsNewXmlProtocol	XMLЭ������
* @param[in]	pszRetXmlStr		ִ������ʱ���ص�ִ�н��XML�ַ���
* @param[in]	pszCmdName			��������
* @param[in]	pszInfoName			��ȡ��Ϣ����
* @param[out]	pszInfoValue		��ȡ��Ϣ����ִ�
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPIUTILS_GetExeCmdRetInfoEx(BOOL fIsNewXmlProtocol, LPCSTR pszRetXmlStr, LPCSTR pszCmdName, 
													  LPCSTR pszInfoName, LPSTR pszInfoValue);


HV_API_EX HRESULT CDECL HVAPI_Capture(HVAPI_HANDLE_EX hHandle, char* szValue);

/**
* @brief              ��185������ʹ�������
* @param[in]          hHandle          �豸���
* @param[in]          dw64CaptureTime    DWORD64�ͣ���ǰϵͳʱ��,Ϊ��1970-01-01 00:00:00��ʼ��Ŀǰ�������ĺ�������Ϊ����ץ��ʱ�䣬���Ϊ�� (NULL)�����Զ���ȡ��ǰʱ��
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SendCaptureCmd(HVAPI_HANDLE_EX hHandle, DWORD64 dw64CaptureTime);

/**
* @brief			���������źż�������
@param[in]			nNum	��������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_OpenListenCMDSever(int nNum);

/**
* @brief			�رմ����źż�������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_CloseListenCMDSever();

/**
* @brief			���ü����ص�����
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[in]		pFunc			�ص�����ָ��
* @param[in]		pUserData		����ص��������û�����ָ��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetCallBackListen(HVAPI_HANDLE_EX hHandle,PVOID pFunc, PVOID pUserData);

/**
* @brief			���ü����ص�������չ
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[in]		iCallBackType	����ص�����
* @param[in]		pFunc			�ص�����ָ��
* @param[in]		pUserData		����ص��������û�����ָ��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetCallBackListenEx(HVAPI_HANDLE_EX hHandle,INT iCallBackType,PVOID pFunc, PVOID pUserData);


/**
* @brief			���Ӽ����豸���
* @param[in]		szIp			�豸��IP��ַ
* @return			�ɹ����豸�����ʧ�ܣ�NULL
*/
HV_API_EX HVAPI_HANDLE_EX CDECL HVAPI_OpenListenClientEx(LPCSTR szIp);

/**
* @brief			�رռ����豸���
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_CloseListenClientEx(HVAPI_HANDLE_EX hHandle);


/**
* @brief              ȡ���˿���������(���ֻ��ȡһ��������)
* @param[in]          hHandle          �豸���
* @param[in]          dw64StartTime    ��Ӧ��ȡ��������Ϣ����ʼʱ��,Ϊ��1970-01-01 00:00:00��ʼ��Ŀǰ�������ĺ�����
* @param[in]          dw64EndTime      ��Ӧ��ȡ��������Ϣ�Ľ���ʱ��,Ϊ��1970-01-01 00:00:00��ʼ��Ŀǰ�������ĺ�����
* @param[out]         szRetInfo		   ��Ӧʹ����������ڴ����򣬺������óɹ����������Ϣ�����ڴ�
* @param[in,out]      iLen		       szRetInfo���������ȣ��������غ�Ϊ�ַ���ʵ�ʳ���
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetPCSFlow(HVAPI_HANDLE_EX hHandle, DWORD64 dw64StartTime, DWORD64 dw64EndTime, CHAR* szRetInfo, INT* iLen);



/**
* @brief              ץ��¼��
* @param[in]          hHandle          �豸���
* @param[in]          iFlag   ץ��¼��ʼ�������ǣ�0Ϊ����ץ�ģ�1Ϊ��ʼץ��
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_CaptureVideo(HVAPI_HANDLE_EX hHandle, INT iFlag);

/**
* @brief				����ƿ���
* @param[in]          hHandle          �豸���
* @param[in]          iFlag   ���ر�ǣ�0Ϊ�رգ�1Ϊ��
* @return             �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_OBCLightSwitch(HVAPI_HANDLE_EX hHandle, INT iFlag);



//=====================================ITTS�����ӿ�=========================================

/**
* @brief			���豸���
* @param[in]		szIp			�豸��IP��ַ
* @param[in]		szApiVer		��Ӧ�豸��API�汾��ע��ΪNULL��Ĭ��HVAPI_API_VERSION
* @param[in]		nChannelNum		ͨ���ţ���Χ0~6   0Ϊ��ͨ��ͨ�����ʣ�  1-6����ͨ��1��ͨ��6
* @return			�ɹ����豸�����ʧ�ܣ�NULL
*/
HV_API_EX HVAPI_HANDLE_EX CDECL HVAPI_OpenChannel(LPCSTR szIp, LPCSTR szApiVer, INT iChannelNum = 0);

/**
* @brief		    ����ǰ��һ����豸
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[in,out]	pCameraInfo	    ���������豸��Ϣ�ṹ������
* @param[in,out]	pnCameraCount	���������豸����
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL, ����ṹ������̫�٣�S_FALSE 
*/
HV_API_EX HRESULT CDECL HVAPI_SearchCameraEx(HVAPI_HANDLE_EX hHandle, CCameraInfo* pCameraInfo,INT* pnCameraCount);




/**
* @brief		    ��ȡ�豸��IP��ַ/����/����
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[out]		szIP			IP��ַ
* @param[in,out]	szIPLen			ִ�к󷵻ص�ʵ�ʳ���
* @param[out]		szMask			����
* @param[in,out]	szMaskLen		���볤��
* @param[out]		szGateWay		����
* @param[in,out]	szGateWayLen		���س���
* @param[out]		szMac			Mac��ַ
* @param[in,out]	szMacLen		Mac��ַ����
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetIPInfo(HVAPI_HANDLE_EX hHandle,CHAR* szIP,INT*szIPLen,CHAR* szMask ,INT*szMaskLen ,CHAR* szGateWay,INT*szGateWayLen,CHAR* szMac,INT*szMacLen );



/**
* @brief		    ��ѯNTP�������Ƿ�ʹ��
* @param[in]		hHandle			    ��Ӧ�豸��������Ч���
* @param[in,out]	fEnable				IP��ַ
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetNTPEnable(HVAPI_HANDLE_EX hHandle, BOOL*fEnable );



/**
* @brief		    ����NTP������IP/�˿�/ʱ����
* @param[in]		hHandle			    ��Ӧ�豸��������Ч���
* @param[in]		szIP				IP��ַ
* @param[in]		Port				�˿�
* @param[in]		UpdateIntervalMS	ʱ����
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetNTPServerIPPort(HVAPI_HANDLE_EX hHandle, CHAR* szIP,INT Port, DWORD UpdateIntervalMS);




/**
* @brief		    ��ȡNTP������IP/�˿�/ʱ����
* @param[in]		hHandle			    ��Ӧ�豸��������Ч���
* @param[in,out]	szIP				IP��ַ
* @param[in,out]	szIPLen		    ִ�к󷵻ص�ʵ�ʳ���
* @param[in,out]	nPort				�˿�
* @param[in]		UpdateIntervalMS	ʱ����
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetNTPServerIPPort(HVAPI_HANDLE_EX hHandle,CHAR* szIP,INT*szIPLen,INT*nPort,DWORD*UpdateIntervalMS);




/**
* @brief		    ��ȡ�豸ʱ��
* @param[in]		hHandle			    ��Ӧ�豸��������Ч���
* @param[in,out]	iZoneNum			ʱ��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetTimeZone(HVAPI_HANDLE_EX hHandle, INT*iZoneNum);





/**
* @brief		    ��ȡ�豸ʱ��
* @param[in]		hHandle			    ��Ӧ�豸��������Ч���
* @param[in,out]	iYear				��
* @param[in,out]	iMon				��
* @param[in,out]	iDay				��
* @param[in,out]	iHour				ʱ
* @param[in,out]	iMin				��
* @param[in,out]	iSec				��
* @param[in,out]	iMSec				����
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetTime(HVAPI_HANDLE_EX hHandle,INT*iYear,INT*iMon,INT*iDay,INT*iHour ,INT*iMin,INT*iSec,INT*iMSec);




/**
* @brief		    ��ʽ��Ӳ��
* @param[in]		hHandle			    ��Ӧ�豸��������Ч���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_FormatHdd(HVAPI_HANDLE_EX hHandle);






/**
* @brief		    ע��
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_LoginOut(HVAPI_HANDLE_EX hHandle);



/**
* @brief		    �ָ�Ĭ������
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_RestoreDefaultPass(HVAPI_HANDLE_EX hHandle);




/**
* @brief		    ��������ͨ��
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[in]		AddDevice		�豸��Ϣ
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_AddCameraToChannel(HVAPI_HANDLE_EX hHandle,AIOAddDevice AddDevice);



/**
* @brief		    ���ģ�������ͨ��
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[in]		AddDevice		�豸��Ϣ
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_AddCameraToChannelTest(HVAPI_HANDLE_EX hHandle,AIOAddDevice AddDevice);


/**
* @brief		    ɾ��ͨ��
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[in]		nChannel		ͨ��	
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_RemoveCamaraFromChannel(HVAPI_HANDLE_EX hHandle,INT iChannelID);


/**
* @brief		    ɾ��ģ��ͨ��
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[in]		nChannel		ͨ��	
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_RemoveCamaraFromChannelTest(HVAPI_HANDLE_EX hHandle,INT iChannelID);


/**
* @brief		    ���úϳ�ͼ��ʽ���������ϳ�ͼ��С�����������ʽ����С����ɫ��λ��
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[in]		iTwoEnable		2��ͼ�ϳɿ���	
* @param[in]		iTwoMode		2��ͼ�ϳɷ�ʽ	
* @param[in]		iThreeMode	    3��ͼ�ϳɷ�ʽ	
* @param[in]		iSixMode	    6��ͼ�ϳɷ�ʽ	
* @param[in]		iQuality		�ϳ�ͼ����	
* @param[in]		iOutPutSize		�ϳ�ͼ��С һ����౶
* @param[in]		iFontEnable		�������ʹ��
* @param[in]		iFontSize		�����С
* @param[in]		iFontAddPos		�������λ��
* @param[in]		iFontColor		������ɫ a r g b ÿ������ռһ���ֽ�
* @param[in]		iFormat			���Ӹ�ʽ
* @param[in]		szContent		�Զ����������
* @param[in]		iChannelID		ͨ��	
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetComposeInfoByChannel(HVAPI_HANDLE_EX hHandle,INT iTwoEnable,INT iTwoMode,INT iThreeMode,INT iSixMode,INT iQuality,INT iOutPutSize,INT iFontEnable
													  ,INT iFontSize,INT iFontAddPos,INT iFontColor,INT iFormat ,CHAR*szContent,INT iChannelID);


/**
* @brief		    ���úϳ�ͼ��ʽ���������ϳ�ͼ��С�����������ʽ����С����ɫ��λ��
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[in]		iTwoEnable		2��ͼ�ϳɿ���	
* @param[in]		iTwoMode		2��ͼ�ϳɷ�ʽ	
* @param[in]		iThreeEnable	3��ͼ�ϳɿ���	
* @param[in]		iThreeMode		3��ͼ�ϳɷ�ʽ	
* @param[in]		iFourEnable	    4��ͼ�ϳɿ���	
* @param[in]		iFourMode		4��ͼ�ϳɷ�ʽ	
* @param[in]		iSixEnable	    6��ͼ�ϳɿ���	
* @param[in]		iSixMode	    6��ͼ�ϳɷ�ʽ	
* @param[in]		iQuality		�ϳ�ͼ����	
* @param[in]		iOutPutSize		�ϳ�ͼ��С һ����౶
* @param[in]		iFontEnable		�������ʹ��
* @param[in]		iFontSize		�����С
* @param[in]		iFontAddPos		�������λ��
* @param[in]		iFontColor		������ɫ a r g b ÿ������ռһ���ֽ�
* @param[in]		iFormat			���Ӹ�ʽ
* @param[in]		szContent		�Զ����������
* @param[in]		iChannelID		ͨ��	
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetComposeInfoByChannelEx(HVAPI_HANDLE_EX hHandle,INT iTwoEnable,INT iTwoMode,INT iThreeEnable,INT iThreeMode,INT iFourEnable,INT iFourMode,INT iSixEnable,INT iSixMode,INT iQuality,INT iOutPutSize,INT iFontEnable
													  ,INT iFontSize,INT iFontAddPos,INT iFontColor,INT iFormat ,CHAR*szContent,INT iChannelID);



/**
* @brief			��ѯ�ϳ�ͼ��ʽ���������ϳ�ͼ��С�����������ʽ����С����ɫ��λ��
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[out]		iTwoMode		2��ͼ�ϳɷ�ʽ
* @param[out]		iTwoEnable	2��ͼ�ϳɷ�ʽʹ��
* @param[out]		iThreeMode	    3��ͼ�ϳɷ�ʽ	
* @param[out]		iSixMode	    6��ͼ�ϳɷ�ʽ
* @param[out]		iQuality		�ϳ�ͼ����	
* @param[out]		iOutPutSize		�ϳ�ͼ��С һ����౶
* @param[out]		iFontEnable		�������ʹ��
* @param[out]		iFontSize		�����С
* @param[out]		iFontAddPos		�������λ��
* @param[out]		iFontColor		������ɫ a r g b ÿ������ռһ���ֽ�
* @param[out]		iFormat			���Ӹ�ʽ
* @param[out]		szContent		�Զ����������
* @param[in,out]	iContentLen    ʵ�ʽ��ճ���
* @param[in]		iChannelID		ͨ��	
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetComposeInfoByChannel(HVAPI_HANDLE_EX hHandle,INT*iTwoMode,INT *iTwoEnable,INT*iThreeMode,INT*iSixMode,INT*iQuality,INT*iOutPutSize,INT*iFontEnable
													  ,INT*iFontSize,INT*iFontAddPos,INT*iFontColor,INT*iFormat ,CHAR*szContent,INT *iContentLen,INT iChannelID);



/**
* @brief			��ѯ�ϳ�ͼ��ʽ���������ϳ�ͼ��С�����������ʽ����С����ɫ��λ��
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[out]		iTwoEnable		2��ͼ�ϳɿ���
* @param[out]		iTwoMode		2��ͼ�ϳɷ�ʽ
* @param[out]		iThreeEnable	3��ͼ�ϳɿ���	
* @param[out]		iThreeMode	    3��ͼ�ϳɷ�ʽ	
* @param[out]		iFourEnable	    4��ͼ�ϳɿ���	
* @param[out]		iFourMode		4��ͼ�ϳɷ�ʽ	
* @param[out]		iSixEnable	    6��ͼ�ϳɿ���	
* @param[out]		iSixMode	    6��ͼ�ϳɷ�ʽ	
* @param[out]		iQuality		�ϳ�ͼ����	
* @param[out]		iOutPutSize		�ϳ�ͼ��С һ����౶
* @param[out]		iFontEnable		�������ʹ��
* @param[out]		iFontSize		�����С
* @param[out]		iFontAddPos		�������λ��
* @param[out]		iFontColor		������ɫ a r g b ÿ������ռһ���ֽ�
* @param[out]		iFormat			���Ӹ�ʽ
* @param[out]		szContent		�Զ����������
* @param[in,out]	iContentLen    ʵ�ʽ��ճ���
* @param[in]		iChannelID		ͨ��	
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/																
HV_API_EX HRESULT CDECL HVAPI_GetComposeInfoByChannelEx(HVAPI_HANDLE_EX hHandle,INT *iTwoEnable,INT*iTwoMode,INT *iThreeEnable,INT *iThreeMode, INT *iFourEnable,INT *iFourMode,INT *iSixEnable,INT*iSixMode,INT*iQuality,INT*iOutPutSize,INT*iFontEnable
													  ,INT*iFontSize,INT*iFontAddPos,INT*iFontColor,INT*iFormat ,CHAR*szContent,INT*iContentLen,INT iChannelID);



/**
* @brief			�����豸
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[in]		UpGradeFile		�����ļ���·��	
* @param[in]		UpGradeType		�������ͣ�1��Upgrade Kernel	2��Upgrade Rootfs 3��Upgrade the whole package
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_UpGrade(HVAPI_HANDLE_EX hHandle, CHAR* UpGradeFile,INT UpGradeType);



/**
* @brief			��ȡ����״̬
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[in]		pvOutBuf		����״̬��Ϣ���ջ���	
* @param[in,out]	BufLen			ʵ�ʽ������ݳ���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetUpGradeStatus(HVAPI_HANDLE_EX hHandle,CHAR*pvOutBuf,INT*BufLen);



/**
* @brief			�����豸����
* @param[in]		hHandle		��Ӧ�豸��������Ч���
* @param[in]		szDevName		�豸����	
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetDevName(HVAPI_HANDLE_EX hHandle,CHAR* szDevName);



/**
* @brief			��ѯ�豸���ơ���ź�ϵͳ�汾��
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[in]		szDevName			�豸����	
* @param[in]		iDevNameLen		�豸���Ƴ���	
* @param[in]		szSno				�豸���
* @param[in]		iSnoLen			�豸��ų���		
* @param[in]		szBuildNo			ϵͳ�汾��
* @param[in]		iBuildNoLen		ϵͳ�汾�ų���	
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetDevNameInfo(HVAPI_HANDLE_EX hHandle,CHAR* szDevName,INT* iDevNameLen,CHAR* szSno,INT* iSnoLen,CHAR* szBuildNo,INT* iBuildNoLen);



/**
* @brief			��ȡӲ��״̬
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[out]		iInsert			Ӳ���Ƿ����
* @param[out]		iInit			Ӳ���Ƿ��ʼ��
* @param[out]		iH264Recording	Ӳ���Ƿ����ڱ���¼��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetHddState(HVAPI_HANDLE_EX hHandle,INT*iInsert,INT*iInit, INT* iH264Recording);






/**
* @brief			��ȡӲ�̵Ĵ洢״̬
* @param[in]		hHandle						��Ӧ�豸��������Ч���	
* @param[out]		iHddRate					Ӳ��ʹ����	
* @param[out]		iResultRate					���ʹ����	
* @param[out]		iH264Rate					��Ƶʹ����	
* @param[out]		iResultCnt					�����	
* @param[out]		iImageCnt					ͼƬ��		
* @param[out]		iHddSize					Ӳ������ ��λM
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL 
*/
HV_API_EX HRESULT CDECL HVAPI_GetHddUsage(HVAPI_HANDLE_EX hHandle,INT*iHddRate ,INT* iResultRate,INT* iH264Rate,INT* iResultCnt,INT*iImageCnt, INT* iHddSize);


/**
* @brief		��ȡ��Ƶ���ÿ�ʼ����ʱ��
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[out]	szBeginTime		��ʼʱ��
* @param[out]	szEndTime		����ʱ��
* @param[in]	iChannelID	    ͨ��
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetVedioTimeList(HVAPI_HANDLE_EX hHandle, CHAR *szBeginTime ,INT *iBeginTimeLen,CHAR *szEndTime,INT *iEndTimeLen,INT iChannelID);




/**
* @brief		��ȡ������ÿ�ʼ����ʱ��
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[out]	szBeginTime		��ʼʱ��
* @param[out]	szEndTime		����ʱ��
* @param[in]	iChannelID	    ͨ��
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetResultTimeList(HVAPI_HANDLE_EX hHandle, CHAR *szBeginTime ,INT *iBeginTimeLen,CHAR *szEndTime,INT *iEndTimeLen,INT iChannelID);



/**
* @brief		��ѯͨ��������״̬
* @param[in]	hHandle					��Ӧ�豸����Ч���
* @param[out]	iChannelConnStatus		ͨ��
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetChannelConnStatus(HVAPI_HANDLE_EX hHandle,  INT* iChannelConnStatus );



/**
* @brief			��ȡĳ��ʱ���ڵĿ��ý���б�
* @param[in]		hHandle	        ��Ӧ�豸����Ч���
* @param[in]		ChannelID		ͨ��
* @param[in]		szBeginTime		��ʼʱ��,��ʽ2014-12-11 20:30:56
* @param[in]		szBeginTime		����ʱ��
* @param[in]		iPageNum		��ǰҪ���ҳ��Ĭ�ϵ�һ���ǵ�1ҳ��
* @param[in]		iPageSize		ÿҳ��С
* @param[in]		szVehicleType	��������
* @param[in]		iResultType		���� or ���Ӿ�������
* @param[in]		iIllegalType		Υ������
* @param[in,out]	iTotalCount		��ѯ�������� 1��ѯ������-1��������
* @param[out]		iListCount		��ǰ���ص��б���
* @param[out]		pResultList		����б�
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_QueryResultIndex(HVAPI_HANDLE_EX hHandle,INT iChannelID,CHAR *szBeginTime,CHAR *szEndTime,INT iPageNum,
	INT iPageSize,CHAR *szVehicleType,INT iResultType,INT iIllegalType,INT *iTotalCount,INT *iListCount,ResultList *pResultList);




/**
* @brief			��ȡ��Ƶĳʱ����ڵĿ���ʱ�����
* @param[in]		hHandle	        ��Ӧ�豸����Ч���
* @param[in]		iChannelID		ͨ��
* @param[in]		szBeginTime		��ʼʱ��,��ʽ2014-12-11 20:30:56
* @param[in]		szBeginTime		����ʱ��
* @param[in]		iPageNum		��ǰҪ���ҳ��Ĭ�ϵ�һ���ǵ�1ҳ��
* @param[in]		iPageSize		ÿҳ��С
* @param[out]		iTotalCount		��ѯ��������   1��ѯ������-1��������
* @param[out]		iListCount		��ǰ���ص��б���
* @param[out]		pVideoList		����б�
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_QueryVideoIndex(HVAPI_HANDLE_EX hHandle,INT iChannelID,CHAR *szBeginTime,CHAR *szEndTime,INT iPageNum,
	INT iPageSize,INT *iTotalCount,INT *iListCount,VideoList *pVideoList);

// ����:	ͼƬ���۸ı�ʶֲ��ӿ�
// ����:	
//			char* pcDstFileName,				ֲ����۸ı�ʶ������ļ����ļ�������������·����
//			char* pcSrcFileName,				��ֲ����۸ı�ʶ��ԭʼ�ļ����ļ�������������·����
//			PBYTE pbPublicKey,					�������۸ı�ʶ��Կ�����ݿ�
//			WORD wKeyLen						��Կ���ݿ鳤��
// ����ֵ:  ����S_OK, ��ʾ�����ɹ�,
//          ����E_POINTER, �����а����зǷ���ָ��;
//          ����E_FAIL, ��ʾδ֪�Ĵ����²���ʧ��;
//ע�⣺	�������ڳɹ�ִ�к�Ὣ������������ͼƬ��ƴ�ӽ��д���Ӧ�������
HV_API_EX HRESULT _cdecl HV_AntiTamper_Embed(
										char* pcDstFileName,				//ֲ����۸ı�ʶ������ļ����ļ�������������·����
										char* pcSrcFileName,				//��ֲ����۸ı�ʶ��ԭʼ�ļ����ļ�������������·����
										PBYTE pbPublicKey,					//�������۸ı�ʶ��Կ�����ݿ�
										WORD wKeyLen						//��Կ���ݿ鳤��
										);

// ����:	ͼƬ���۸ı�ʶУ��ӿ�
// ����:	
//			BOOL &fIsOriginal,					У����������TRUEΪУ��ͨ����FALSEΪУ��ʧ�ܣ����۸ģ�
//			char* pcSrcFileName,				��У���ԭʼ�ļ����ļ�������������·����
//			PBYTE pbPublicKey,					�������۸ı�ʶ��Կ�����ݿ�
//			WORD wKeyLen						��Կ���ݿ鳤��
// ����ֵ:  ����S_OK, ��ʾ�����ɹ�,
//          ����E_POINTER, �����а����зǷ���ָ��;
//          ����E_FAIL, ��ʾδ֪�Ĵ����²���ʧ��;
//ע�⣺	�������ڳɹ�ִ�к�Ὣ������������ͼƬ��ƴ�ӽ��д���Ӧ�������
HV_API_EX HRESULT _cdecl HV_AntiTamper_Examine(
											BOOL &fIsOriginal,					//У����������TRUEΪУ��ͨ����FALSEΪУ��ʧ�ܣ����۸ģ�
											char* pcSrcFileName,				//��У���ԭʼ�ļ����ļ�������������·����
											PBYTE pbPublicKey,					//�������۸ı�ʶ��Կ�����ݿ�
											WORD wKeyLen						//��Կ���ݿ鳤��
											);

/**
* @brief			��ȡĳ��ʱ���ڵĿ��ý���б�
* @param[in]		hHandle	        ��Ӧ�豸����Ч���
* @param[in]		ChannelID		ͨ��
* @param[in]		szBeginTime		��ʼʱ��,��ʽ2014-12-11 20:30:56
* @param[in]		szBeginTime		����ʱ��
* @param[in]		iPageNum		��ǰҪ���ҳ��Ĭ�ϵ�һ���ǵ�1ҳ��
* @param[in]		iPageSize		ÿҳ��С
* @param[in]		szVehicleType	��������
* @param[in]		iResultType		���� or ���Ӿ�������
* @param[in]		iIllegalType		Υ������
* @param[in]		szPlate		    ����
* @param[in]		szCarFace		����
* @param[in]		pExtInInfo		���Ӳ�ѯ����ָ��
* @param[in,out]	iTotalCount		��ѯ�������� 1��ѯ������-1��������
* @param[out]		iListCount		��ǰ���ص��б���
* @param[out]		pResultList		����б�
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_QueryResultIndexEx(HVAPI_HANDLE_EX hHandle,
												 INT iChannelID,
												 CHAR* szBeginTime,
												 CHAR* szEndTime,
												 INT iPageNum,
												 INT iPageSize,
												 CHAR* szVehicleType,
												 INT iResultType,
												 INT iIllegalType,
												 CHAR* szPlate,
												 CHAR* szCarFace,
												 PVOID* pInExtInfo,
												 INT* iTotalCount,
												 INT* iListCount,
												 ResultListEx* pResultList);

/**
* @brief		    ��ȡFTPʱ��
* @param[in]		hHandle			    ��Ӧ�豸��������Ч���
* @param[in,out]	nFtpServerNo		FTP���������
* @param[in,out]	iYear				��
* @param[in,out]	iMon				��
* @param[in,out]	iDay				��
* @param[in,out]	iHour				ʱ
* @param[in,out]	iMin				��
* @param[in,out]	iSec				��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetFtpSaveTime(HVAPI_HANDLE_EX hHandle, INT nFtpServerNo, INT*iYear,INT*iMon,INT*iDay,INT*iHour ,INT*iMin,INT*iSec);

/**
* @brief		    ��ѯʱ������Ƿ��н��
* @param[in]		hHandle			    ��Ӧ�豸��������Ч���
* @param[in]	ChannelID				ͨ����
* @param[in]	BeginTime				��ʼʱ��
* @param[in]	EndTime					����ʱ��
* @param[int,out]	pnExsitResultDataCount  ���ݸ���
* @param[int,out]	rgExsitResultData       ��������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_ExsitResultData(HVAPI_HANDLE_EX hHandle,INT iChannelID,CHAR *szBeginTime,CHAR *szEndTime, INT *pnExsitResultDataCount,CHAR *rgExsitResultData);

/**
* @brief		    ��ѯʱ������Ƿ�����Ƶ
* @param[in]		hHandle			    ��Ӧ�豸��������Ч���
* @param[in]	ChannelID				ͨ����
* @param[in]	nInterval				��ѯ�ļ��
* @param[in]	BeginTime				��ʼʱ��
* @param[in]	EndTime					����ʱ��
* @param[int,out]	pnExsitVideoDataCount  ���ݸ���
* @param[int,out]	rgExsitVideoData       ��������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_ExsitVideoData(HVAPI_HANDLE_EX hHandle,INT iChannelID, INT nInterval, CHAR *szBeginTime,CHAR *szEndTime,INT *pnExsitVideoDataCount,CHAR *rgExsitVideoData);

/**
* @brief		    ���ʹ�õ����ݿ�汾��
* @param[in]		hHandle			    ��Ӧ�豸��������Ч���
* @param[in]	    nMode				����ģʽ�� 0:��õ�ǰ�豸�����ݿ�İ汾��  1:�������֧�ֵ����ݿ�汾��
* @param[out]	    pnDbVersion				���ݿ�汾��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetHddDbVersion(HVAPI_HANDLE_EX hHandle, INT nMode, INT* pnDbVersion );


/**
* @brief		    ��ѯʱ������Ƿ�����Ƶ
* @param[in]		hHandle			    ��Ӧ�豸��������Ч���
* @param[in]	   nMode				����ģʽ��  0:��ʼ�������ݿ�  1:ֹͣ�������ݿ�
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_HddUpDateDb(HVAPI_HANDLE_EX hHandle, INT nMode);

/**
* @brief		    �鿴���ݿ���������
* @param[in]		hHandle			    ��Ӧ�豸��������Ч���
* @param[out]	    pnUpDateDbRate		���ݿ��������ȡ�����С�������λ:��10.54%������1054
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetHddUpDateDbRate(HVAPI_HANDLE_EX hHandle, INT* pnUpDateDbRate );

/**
* @brief		    ������ʷ��������xml���Ӳ�������ʹ��һ��֮���Զ��ָ�Ϊ���ַ�����
* @param[in]		szExtParam			    ��ʷ��������xml���Ӳ���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL  HVAPI_SetDownloadRecordExtParam(CHAR* szExtParam);

/**
* @brief		    ����ITTS���䷢�͹���
* @param[in]		szSMTPUrl			    smtp��������ַ
* @param[in]		nSMTPPort			    smtp�������˿�
* @param[in]		szLoginUser			    �û���
* @param[in]		szLoginPassword			����
* @param[in]		szSenderName			����������
* @param[in]		szFromEmail			    Դ����
* @param[in]		szToEmail			    Ŀ������
* @param[out]		szMailTestResult		���Խ������ֵ
* @param[out]		nLen			        �������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL  HVAPI_TestEmail(HVAPI_HANDLE_EX hHandle, 
										 CHAR* szSMTPUrl, 
										 INT nSMTPPort, 
										 CHAR* szLoginUser, 
										 CHAR* szLoginPassword, 
										 CHAR* szSenderName, 
										 CHAR* szFromEmail,
										 CHAR* szToEmail,
										 CHAR* szMailTestResult, 
										 INT* pnLen);

/**
* @brief		    ��ȡ3A��ͷ����
* @param[out]		pnLensID			    ��ͷ���
* @param[out]		pnErrorControl			��ͷ�ݲ�
* @param[out]		pZOOMLOW			    ��С����
* @param[out]		pZOOMHIGHT			    ��󽹾�
* @param[out]		pFOCUSLENGTH			���۽�ֵ
* @param[out]		pIRISLENGHT			    ����Ȧֵ

* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetLensConfig(HVAPI_HANDLE_EX hHandle, 
											INT* pnLensID, 
											INT* pnErrorControl, 
											INT* pZOOMLOW, 
											INT* pZOOMHIGHT, 
											INT* pFOCUSLENGTH, 
											INT* pIRISLENGHT);
#endif
