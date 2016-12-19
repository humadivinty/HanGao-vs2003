/**
* @file		HvDevice.h
* @version	1.0
* @brief	HvDevice.dllͷ�ļ�
* @date		2011-10-21
*/

#ifndef _HVAPI_H_
#define _HVAPI_H_

#include "HvDeviceBaseType.h"
#include "HvDeviceCommDef.h"

#ifdef HVDEVICE_EXPORTS
    #define HV_API extern "C" __declspec(dllexport)
#elif HVDEVICE_LIB
    #define HV_API
#else
    #define HV_API extern "C" __declspec(dllimport)
#endif

#define HVAPI_API_VERSION "1.0"     /**< API�汾�� */

typedef PVOID HVAPI_HANDLE;         /**< HvAPI������� */

/* �ص����������� */
#define STREAM_TYPE_UNKNOWN         0xffff0000	/**< δ֪ */
#define STREAM_TYPE_IMAGE           0xffff0001	/**< ͼƬ */
#define STREAM_TYPE_VIDEO           0xffff0002	/**< ��Ƶ */
#define STREAM_TYPE_RECORD          0xffff0003	/**< ʶ���� */
#define STREAM_TYPE_GATHER_INFO     0xffff0004	/**< ��ͨͳ����Ϣ */

#define PACKET_RECORD_VIDEO_ILLEGAL 0x80000001	/**Υ����Ƶ������*/

/**
* @brief			�����豸
* @param[in]		dwDevType		Ҫ�������豸����
* @param[out]		szDevInfoList	����������������Էֺŷָ����豸��ַ��Ϣ�б�
* @param[in]		nBufLen			szDevInfoList����������
* @return			���������豸����
*/
HV_API DWORD CDECL HVAPI_SearchDevice(DWORD dwDevType, LPSTR szDevInfoList, INT nBufLen);

/**
* @brief			ͨ���豸MAC��ַ�޸��豸��IP��ַ
* @param[in]		dw64MacAddr			Ҫ�޸ĵ��豸MAC��ַ
* @param[in]		dwIP				�޸ĺ��IP��ַ
* @param[in]		dwMask				�޸ĺ����������
* @param[in]		dwGateway			�޸ĺ�����ص�ַ
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPI_SetIPFromMac(DWORD64 dw64MacAddr,
                                        DWORD32 dwIP,
                                        DWORD32 dwMask,
                                        DWORD32 dwGateway);

/**
* @brief		��ȡ�豸����
* @param[in]	pcIP		�豸IP
* @param[out]	iDeviceType	�豸����
* @return		�ɹ�S_OK ʧ�� E_FAILE
*/
HV_API HRESULT CDECL HVAPI_GetDevType(PSTR pcIP, int* iDeviceType);


/**
* @brief			���豸���
* @param[in]		szIp			�豸��IP��ַ
* @param[in]		szApiVer		��Ӧ�豸��API�汾��ע��ΪNULL��Ĭ��HVAPI_API_VERSION
* @return			�ɹ����豸�����ʧ�ܣ�NULL
*/
HV_API HVAPI_HANDLE CDECL HVAPI_Open(LPCSTR szIp, LPCSTR szApiVer);

/**
* @brief			�ر��豸���
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPI_Close(HVAPI_HANDLE hHandle);

/**
* @brief			��ȡ�豸����
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szParamDoc		��ȡ���Ĳ�����XML��ʽ��
* @param[in]		nBufLen			szParam�������ĳ���
* @param[out]		pnRetLen		ʵ�ʷ��صĲ������ȡ�ע��ΪNULL����Ըò�����
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPI_GetParam(HVAPI_HANDLE hHandle,
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
HV_API HRESULT CDECL HVAPI_SetParam(HVAPI_HANDLE hHandle, LPCSTR szParamDoc);

/**
* @brief			ִ������
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szCmd			�������豸����ĳ��������ַ���
* @param[in]		szRetBuf		���ص�ִ�н��(XML��ʽ)
* @param[in]		nBufLen			szRetBuf�������ĳ���
* @param[out]		pnRetLen		ʵ�ʷ��ص�ִ�н�����ȡ�ע��ΪNULL����Ըò�����
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPI_ExecCmd(HVAPI_HANDLE hHandle,
                                   LPCSTR szCmd,
                                   LPSTR szRetBuf,
                                   INT nBufLen,
                                   INT* pnRetLen);

/**
* @brief			��ȡ�豸��Ϣ
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szCmd			�������豸��ѯĳЩ��Ϣ���ַ���
* @param[in]		szRetBuf		���ص�ִ�н��(XML��ʽ)
* @param[in]		nBufLen			szRetBuf�������ĳ���
* @param[out]		pnRetLen		ʵ�ʷ��ص�ִ�н�����ȡ�ע��ΪNULL����Ըò�����
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPI_GetInfo(HVAPI_HANDLE hHandle,
                                   LPCSTR szCmd,
                                   LPSTR szRetBuf,
                                   INT nBufLen,
                                   INT* pnRetLen);

/**
* @brief			�������������ջص�����
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		pFunc			�ص�����ָ�롣ע��ΪNULLʱ��ʾ�ر�nStreamType���͵���������
* @param[in]		pUserData		����ص��������û�����ָ��
* @param[in]		nStreamType		�ص�����������
* @param[in]		szConnCmd		��������������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPI_SetCallBack(HVAPI_HANDLE hHandle,
                                       PVOID pFunc,
                                       PVOID pUserData,
                                       INT nStreamType,
                                       LPCSTR szConnCmd);

/**
* @brief			���»ص���������������
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		nStreamType		�ص�����������
* @param[in]		szConnCmd		��������������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPI_UpdateCallBackCmd(HVAPI_HANDLE hHandle,
                                             INT nStreamType,
                                             LPCSTR szConnCmd);

/**
* @brief			��ȡ����״̬
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		nStreamType		���������ͣ������������ͣ�
* @param[out]		pdwConnStatus	�����ӵĵ�ǰ״̬
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPI_GetConnStatus(HVAPI_HANDLE hHandle,
                                         INT nStreamType,
                                         DWORD* pdwConnStatus);

/**
* @brief			ͼƬ�ص�����
* @param[out]		pUserData		��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		pbImageData		ͼƬ����
* @param[out]		dwImageDataLen	ͼƬ���ݳ���
* @param[out]		dwImageType		ͼƬ����
* @param[out]		szImageExtInfo	ͼƬ��չ��Ϣ���ַ�����ʽ��
* @return			0
*/
typedef INT (CDECL *HVAPI_CALLBACK_IMAGE)(PVOID pUserData,
                                          PBYTE pbImageData,
                                          DWORD dwImageDataLen,
                                          PBYTE pbImageInfoData,
                                          DWORD dwImageInfoLen,
                                          DWORD dwImageType,
                                          LPCSTR szImageExtInfo);

/**
* @brief			��Ƶ�ص�����
* @param[out]		pUserData		��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		pbVideoData		��Ƶ����
* @param[out]		dwVideoDataLen	��Ƶ���ݳ���
* @param[out]		dwVideoType		��Ƶ����
* @param[out]		szVideoExtInfo	��Ƶ��չ��Ϣ���ַ�����ʽ��
* @return			0
*/
typedef INT (CDECL *HVAPI_CALLBACK_VIDEO)(PVOID pUserData,
                                          PBYTE pbVideoData,
                                          DWORD dwVideoDataLen,
                                          DWORD dwVideoType,
                                          LPCSTR szVideoExtInfo);

/**
* @brief			ʶ�����ص�����
* @param[out]		pUserData		��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		pbResultPacket	ʶ�������ݰ�
* @param[out]		dwPacketLen		ʶ�������ݰ�����
* @param[out]		dwRecordType	ʶ��������
* @param[out]		szResultInfo	ʶ����(XML��ʽ)
* @return			0
*/
typedef INT (CDECL *HVAPI_CALLBACK_RECORD)(PVOID pUserData,
                                           PBYTE pbResultPacket,
                                           DWORD dwPacketLen,
                                           DWORD dwRecordType,
                                           LPCSTR szResultInfo);

/**
* @brief			������ͳ����Ϣ�ص�
* @param[out]		pUserData		��HVAPI_SetCallBack���õĴ���ص��������û�����ָ��
* @param[out]		pbInfoData		��������Ϣ����
* @param[out]		dwInfoDataLen	��Ϣ����
* @return			0
*/
typedef INT (CDECL *HVAPI_CALLBACK_GATHER_INFO)(PVOID pUserData,
                                                PBYTE pbInfoData,
                                                DWORD dwInfoDataLen);

/* ���ͼƬ���� */
typedef enum
{
    RECORD_IMAGE_BEST_SNAPSHOT = 0,	/**< ��������ͼ��	ע�����ݸ�ʽΪJpeg */
    RECORD_IMAGE_LAST_SNAPSHOT,		/**< ����ͼ��		ע�����ݸ�ʽΪJpeg */
    RECORD_IMAGE_BEGIN_CAPTURE,		/**< ��һ��ץ��ͼ��	ע�����ݸ�ʽΪJpeg */
    RECORD_IMAGE_BEST_CAPTURE,		/**< �ڶ���ץ��ͼ��	ע�����ݸ�ʽΪJpeg */
    RECORD_IMAGE_LAST_CAPTURE,		/**< ������ץ��ͼ��	ע�����ݸ�ʽΪJpeg */
    RECORD_IMAGE_SMALL_IMAGE,		/**< ����Сͼ��		ע�����ݸ�ʽΪYUV422 */
    RECORD_IMAGE_BIN_IMAGE,			/**< ���ƶ�ֵͼ��	ע�����ݸ�ʽΪ������ */
	RECORD_IMAGE_COMPOSE_NEW  		//�ºϳ�ͼ
}
RECORD_IMAGE_TYPE;

/* ���ͼƬ��Ϣ */
typedef struct _RECORD_IMAGE_INFO
{
    DWORD32 dwCarID;				/**< ��ͼƬ��Ӧ�ĳ���ID */
    DWORD32 dwWidth;				/**< ͼƬ��� */
    DWORD32 dwHeight;				/**< ͼƬ�߶� */
    DWORD64 dw64TimeMs;				/**< ͼƬʱ�� */
}
RECORD_IMAGE_INFO;

/* ���ͼƬ */
typedef struct _RECORD_IMAGE
{
    RECORD_IMAGE_INFO cImgInfo;		/**< ͼƬ��Ϣ */
    PBYTE pbImgData;				/**< ͼƬ���� */
    PBYTE pbImgInfoEx;				/**< ͼƬԭʼ��Ϣ */
    DWORD dwImgDataLen;				/**< ͼƬ���� */
    DWORD dwImgInfoLen;				/**< ͼƬԭʼ��Ϣ���� */
}
RECORD_IMAGE;

/* ���ͼƬ�� */
typedef struct _RECORD_IMAGE_GROUP
{
    RECORD_IMAGE_INFO cImgInfoBestSnapshot;			//��������ͼ��Ϣ
    RECORD_IMAGE_INFO cImgInfoLastSnapshot;			//����ͼ��Ϣ
    RECORD_IMAGE_INFO cImgInfoBeginCapture;			//��һ��ץ��ͼ��Ϣ
    RECORD_IMAGE_INFO cImgInfoBestCapture;			//������ץ��ͼ��Ϣ
    RECORD_IMAGE_INFO cImgInfoLastCapture;			//���һ��ץ��ͼ��Ϣ
    RECORD_IMAGE_INFO cImgInfoSmaller;				//����Сͼ��Ϣ
    RECORD_IMAGE_INFO cImgInfoBinary;				//���ƶ�ֵͼ��Ϣ
	

    PBYTE pbImgDataBestSnapShot;					//��������ͼ����
    PBYTE pbImgDataLastSnapShot;					//����ͼ����
    PBYTE pbImgDataBeginCapture;					//��һ��ץ��ͼ����
    PBYTE pbImgDataBestCapture;						//������ץ��ͼ����
    PBYTE pbImgDataLastCapture;						//���һ��ץ��ͼ����
    PBYTE pbImgDataSmaller;							//����Сͼ����
    PBYTE pbImgDataBinary;							//���ƶ�ֵͼ����

    PBYTE pbImgInfoBestSnapShot;					//��������ͼԭʼ��Ϣ
    PBYTE pbImgInfoLastSnapShot;					//����ͼԭʼ��Ϣ
    PBYTE pbImgInfoBeginCapture;					//��һ��ץ��ͼԭʼ��Ϣ
    PBYTE pbImgInfoBestCapture;						//������ץ��ͼԭʼ��Ϣ
    PBYTE pbImgInfoLastCapture;						//���һ��ץ��ͼԭʼ��Ϣ
    PBYTE pbImgInfoSmaller;							//����Сͼԭʼ��Ϣ
    PBYTE pbImgInfoBinary;							//���ƶ�ֵͼԭʼ��Ϣ

    DWORD dwImgDataBestSnapShotLen;					//��������ͼͼƬ���ݳ���
    DWORD dwImgDataLastSnapShotLen;					//����ͼͼƬ���ݳ���
    DWORD dwImgDataBeginCaptureLen;					//��һ��ץ��ͼͼƬ���ݳ���
    DWORD dwImgDataBestCaptureLen;					//������ץ��ͼͼƬ���ݳ���
    DWORD dwImgDataLastCaptureLen;					//���һ��ץ��ͼͼƬ���ݳ���
    DWORD dwImgDataSmallerLen;						//����СͼͼƬ���ݳ���
    DWORD dwImgDataBinaryLen;						//���ƶ�ֵͼͼƬ���ݳ���

    DWORD dwImgInfoBestSnapShotLen;					//��������ͼԭʼ��Ϣ����
    DWORD dwImgInfoLastSnapShotLen;					//����ͼԭʼ��Ϣ����
    DWORD dwImgInfoBeginCaptureLen;					//��һ��ץ��ͼԭʼ��Ϣ����
    DWORD dwImgInfoBestCaptureLen;					//������ץ��ͼԭʼ��Ϣ����
    DWORD dwImgInfoLastCaptureLen;					//���һ��ץ��ͼԭʼ��Ϣ����
    DWORD dwImgInfoSmallerLen;						//����Сͼԭʼ��Ϣ����
    DWORD dwImgInfoBinaryLen;						//���ƶ�ֵͼԭʼ��Ϣ����
}
RECORD_IMAGE_GROUP;

/**
* @brief			��ʶ��������Ϣ����ȡ���ƺ��ַ���
* @param[in]		szResultInfo	ʶ��������Ϣ
* @param[out]		szPlateBuf		���صĳ��ƺ��ַ���
* @param[in]		nBufLen			���ƺ��ַ������泤��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPIUTILS_GetPlateString(LPCSTR szResultInfo,
                                               LPSTR szPlateBuf,
                                               INT nBufLen);

/**
* @brief			��ʶ������������ȡͼƬ
* @param[in]		pbResultPacket	ʶ�������ݰ�
* @param[in]		dwPacketLen		ʶ�������ݰ�����
* @param[in]		eImageType		��Ҫ��ȡ��ͼƬ����
* @param[out]		pcRecordImage	���صĽ��ͼƬ��ע��pcRecordImage��pbImgData��ָ����ڴ�ռ�ΪpbResultPacket��ָ���ڴ�ռ��ĳһ���֡�
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPIUTILS_GetRecordImage(PBYTE pbResultPacket,
                                               DWORD dwPacketLen,
                                               RECORD_IMAGE_TYPE eImageType,
                                               RECORD_IMAGE* pcRecordImage);

/**
* @brief			��ʶ������������ȡ����ͼƬ
* @param[in]		pbResultPacket			ʶ�������ݰ�
* @param[in]		dwPacketLen				ʶ�������ݰ�����
* @param[out]		pcRecordImageGroup		���صĽ��ͼƬ����ע��pcRecordImage������ָ��ָ����ڴ�ռ�ΪpbResultPacket��ָ���ڴ�ռ��ĳһ���֡�
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPIUTILS_GetRecordImageAll(PBYTE pbResultPacket,
                                                  DWORD dwPacketLen,
                                                  RECORD_IMAGE_GROUP* pcRecordImageGroup);

/**
* @brief			����ʷ¼�����ݰ��ڻ�ȡͼƬ���ݼ����������Ϣ
* @param[in]		pbVideoFrameData		��ʷ��Ƶ������
* @param[in]		dwFrameLen				��ʷ��Ƶ�����ݳ���
* @param[out]		iRedLightCount			���������������
* @param[in]		iRedLightBufLen			�������껺��������
* @param[out]		pbRedLightPos			�������껺����
* @param[out]		pbJPEGData				��ͼ������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPIUTILS_ParseHistoryVideoFrame(PBYTE pbVideoFrameData,
                                                       DWORD dwFrameLen,
                                                       int& iRedLightCount, 
                                                       int iRedLightBufLen,
                                                       PBYTE pbRedLightPos,
                                                       PBYTE& pbJPEGData,
                                                       DWORD& dwJPEGDataLen);

/**
* @brief			��ʶ����Сͼת��ΪBMPλͼ
* @param[in]		pbSmallImageData	ʶ����Сͼ��ע����ΪСͼ�����ݸ�ʽΪYUV422���������СΪ��(nSmallImageWidth * nSmallImageHeight * 2)
* @param[in]		nSmallImageWidth	ʶ����Сͼ���
* @param[in]		nSmallImageHeight	ʶ����Сͼ�߶�
* @param[in]		pbBitmapData		BMPλͼ���ݴ�Ż�����
* @param[in,out]	pnBitmapDataLen		BMPλͼ���ݴ�Ż��������ȡ��������غ���Ϊ��BMPλͼ����ʵ�ʳ���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPIUTILS_SmallImageToBitmap(PBYTE pbSmallImageData,
                                                   INT nSmallImageWidth,
                                                   INT nSmallImageHeight,
                                                   PBYTE pbBitmapData,
                                                   INT* pnBitmapDataLen);

/**
* @brief			��ʶ������ֵͼת��ΪBMPλͼ
* @param[in]		pbBinImageData		ʶ������ֵͼ
* @param[in]		pbBitmapData		BMPλͼ���ݴ�Ż�����
* @param[in,out]	pnBitmapDataLen		BMPλͼ���ݴ�Ż��������ȡ��������غ���Ϊ��BMPλͼ����ʵ�ʳ���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPIUTILS_BinImageToBitmap(PBYTE pbBinImageData,
                                                 PBYTE pbBitmapData,
                                                 INT* pnBitmapDataLen);

/**
* @brief			�����ͼ��ƼӺ촦��
* @param[in]		pcSrcImage			ʶ������ͼ
* @param[in]		pbDstImage			�Ӻ��Ľ����ͼ����
* @param[in out]	iDstBufLen			������ͼƬ���������ȣ�������ͼƬ���ݳ���
* @param[in]		iBrightness			������ǿ
* @param[in]		iHueThreshold		ɫ�ȷ�ֵ
* @param[in]		iCompressRate		ѹ����
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPIUTILS_TrafficLightEnhance(PBYTE pbSrcImg,
                                                    int iSrcImgDataLen,
                                                    int iRedLightCount,
                                                    PBYTE pbRedLightPos,
                                                    PBYTE pbDstImage,
                                                    int& iDstBufLen, 
                                                    int iBrightness,
                                                    int iHueThreshold,
                                                    int iCompressRate);

/**
* @brief			��ʶ������ͼ�л�ȡ�������λ��
* @param[in]		pcRecordImage		ʶ������ͼ
* @param[in]		iRedLightPosBufLen	���λ�û����С
* @param[in]		pbRedLightPos		���λ�û���
* @param[out]		iRedLightCount		��Ƹ���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPIUTILS_GetRedLightPosFromeRecordImage(RECORD_IMAGE* pcRecordImage,
                                                               int iRedLightPosBufLen, 
                                                               PBYTE pbRedLightPos,
                                                               int& iRedLightCount);

/**
* @brief			����Ƶͼ�񸽼���Ϣ�л�ȡ��������λ��
* @param[in]		pszVideoExtInfo		��ƵͼƬ������Ϣ
* @param[in]		iPlatePosBufLen		����λ�û����С
* @param[in]		pbPlatePos			����λ�û���
* @param[out]		iPlateCount			���Ƹ���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPIUTILS_GetPlatePosFromeJpegInfo(PBYTE pbJpegInfo,
                                                         DWORD dwJpegInfoLen,
                                                         int iPlatePosBufLen, 
                                                         PBYTE pbPlatePos,
                                                         int& iPlateCount);

/**
* @brief			��HVAPI_ExecCmdִ�з��صĽ���н�����������
* @param[in]		szXmlBuf			HVAPI_ExecCmdִ�з��صĽ��
* @param[out]		szRetcode			������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPIUTILS_ParseXmlCmdRespRetcode(const char* szXmlBuf,
                                                       char* szRetcode);
/**
* @brief			��HVAPI_ExecCmdִ�з��صĽ���н����������ı���Ϣ
* @param[in]		szXmlBuf			HVAPI_ExecCmdִ�з��صĽ��
* @param[in]		szMsgID				��ϢID
* @param[out]		szMsgOut			��ϢID��Ӧ���ı���Ϣ
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPIUTILS_ParseXmlCmdRespMsg(const char* szXmlBuf,
                                                   const char* szMsgID,
                                                   char* szMsgOut);

/**
* @brief			��HVAPI_GetInfoִ�з��صĽ���н�����ָ����Ϣ
* @param[in]		szXmlBuf			HVAPI_GetInfoִ�з��صĽ��
* @param[in]		szInfoName			��Ϣ��
* @param[in]		nInfoValueName		ֵ��
* @param[out]		szInfoValueText		��Ӧ���ı���Ϣ
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPIUTILS_ParseXmlInfoRespValue(const char* szXmlBuf,
                                                      const char* szInfoName, 
                                                      const char* nInfoValueName,
                                                      char* szInfoValueText);

/**
* @brief			�����豸����
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szParamDoc		Ҫ���浽�豸�Ĳ�����XML��ʽ��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
* @warning			���Ĺ��Ĳ���Ҫ���豸�´�������Ż���Ч
*/
HV_API HRESULT CDECL HVAPI_SendControllPannelUpdateFile(HVAPI_HANDLE hHandle,
														PBYTE pUpdateFileBuffer,
														DWORD dwFileSize);

/**
* @brief			�����豸����
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szParamDoc		Ҫ���浽�豸�Ĳ�����XML��ʽ��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
* @warning			���Ĺ��Ĳ���Ҫ���豸�´�������Ż���Ч
*/
HV_API HRESULT CDECL HVAPIUTILS_GetExecXmlCmdResString(HVAPI_HANDLE hHandle, 
													   char* szXmlBuf, 
													   char* szCmdName, 
													   char* szCmdValueName, 
													   char* szCmdValueText);

/**
* @brief			�ӽ��������Ϣ�л�ȡĳ����Ϣ
* @param[in]		szAppened			���������Ϣ
* @param[in]		szInfoName			��ȡ����
* @param[out]		szRetInfo			����ִ�
* @param[in]		iRetInfoBufLen		����ִ����滺������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPIUTILS_GetRecordInfoFromAppenedString(LPCSTR szAppened, LPCSTR szInfoName, LPSTR szRetInfo, INT iRetInfoBufLen);

/**
* @brief			�ӽ��������Ϣ����ȡȫ����Ϣÿ��Ŀ��Ϣʹ�ûس�������
* @param[in]		pszXmlPlateInfo			���������Ϣ
* @param[out]		pszPlateInfoBuf			����ִ�������
* @param[in]		iPlateInfoBufLen		����ִ�����������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPIUTILS_ParsePlateXmlString(LPCSTR pszXmlPlateInfo, LPSTR pszPlateInfoBuf, INT iPlateInfoBufLen);

#endif // _HVAPI_H_
