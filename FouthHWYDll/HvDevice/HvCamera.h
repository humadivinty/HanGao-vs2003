#ifndef _HVCAMARA_H__
#define _HVCAMARA_H__

#include "HvDeviceBaseType.h"
#include "HvDeviceCommDef.h"

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
* @brief		������Ƶ��֡��
* @param[in]	hHandle				��Ӧ�豸����Ч���
* @param[in]	nStreamId			��Ƶ��ID��0��H264,1:MJPEG
* @param[in]	nFps				֡��
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetStreamFps(HVAPI_HANDLE_EX hHandle, INT nStreamId, INT nFps);

/**
* @brief		����H264���ʿ��Ʒ�ʽ
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nType			0��VBR ,1 CBR
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetH264BitRateControl(HVAPI_HANDLE_EX hHandle, INT nType );

/**
* @brief		����H264����
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nBitRate		��Χ 32768~8388608(32Kbps-8Mbps)
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetH264BitRate(HVAPI_HANDLE_EX hHandle, INT nBitRate );

/**
* @brief		����JPEGѹ������
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nJpegCompressRate		��Χ 20��80
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetJpegCompressRate(HVAPI_HANDLE_EX hHandle, INT nJpegCompressRate );


/**
* @brief		�����ַ����ӿ���
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nStreamId		��Ƶ��ID��0��H264,1:MJPEG
* @param[in]	fOSDEnable		0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetOSDEnable(HVAPI_HANDLE_EX hHandle, INT nStreamId ,BOOL fOSDEnable);
/**
* @brief		���ó����ַ����ӿ���
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nStreamId		��Ƶ��ID��0��H264,1:MJPEG
* @param[in]	fOSDEnable		0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetOSDPlateEnable(HVAPI_HANDLE_EX hHandle, INT nStreamId ,BOOL fOSDEnable);

/**
* @brief		�����ַ�����-ʱ����ӿ���
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nStreamId		��Ƶ��ID��0��H264,1:MJPEG
* @param[in]	fEnable			�ַ�����ʱ����ӿ��أ���Χ��0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetOSDTimeEnable(HVAPI_HANDLE_EX hHandle, INT nStreamId, BOOL fEnable);

/**
* @brief		�����ַ�����λ��
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nStreamId		��Ƶ��ID��0��H264,1:MJPEG
* @param[in]	nPosX			����λ��X���꣬��Χ: 0~ͼ���
* @param[in]	nPosY			����λ��Y���꣬��Χ��0~ͼ���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetOSDPos( HVAPI_HANDLE_EX hHandle,INT nStreamId, INT nPosX ,INT nPosY );

/**
* @brief		�����ַ���������
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nStreamId		��Ƶ��ID��0��H264,1:MJPEG
* @param[in]	nFontSize		�����С����Χ��16~32
* @param[in]	nColorR			������ɫRֵ����Χ0��255
* @param[in]	nColorG			������ɫGֵ����Χ0��255
* @param[in]	nColorB			������ɫBֵ����Χ0��255
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetOSDFont(HVAPI_HANDLE_EX hHandle, INT nStreamId ,INT nFontSize ,
										 INT nColorR ,INT nColorG,INT nColorB);
/**
* @brief		�����ַ������ַ���
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nStreamId		��Ƶ��ID��0��H264,1:MJPEG
* @param[in]	szText			�����ַ��� ���ȷ�Χ��0��255
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetOSDText(HVAPI_HANDLE_EX hHandle, INT nStreamId,CHAR* szText  );

/**
* @brief		����CVBS��ʽ
* @param[in]	hHandle		��Ӧ�豸����Ч���
* @param[in]	nMode		CVBS��ʽ����Χ��0:PAL,1:NTSC
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetCVBDisPlayMode(HVAPI_HANDLE_EX hHandle, INT nMode );

/**
* @brief		�����ֶ�����
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nShutter		���ţ���Χ��100~30000
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetManualShutter(HVAPI_HANDLE_EX hHandle, INT nShutter );

/**
* @brief		�����ֶ�����
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nGain			���棬��Χ��0~42
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetManualGain(HVAPI_HANDLE_EX hHandle, INT nGain );

/**
* @brief		����AWB����
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nEnable			AWB����,��Χ��0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetAWBEnable(HVAPI_HANDLE_EX hHandle, INT nEnable );

/**
* @brief		�����ֶ�RGB
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nGainR			Rֵ����Χ��0��255
* @param[in]	nGainG			Gֵ����Χ��0��255
* @param[in]	nGainB			Bֵ����Χ��0��255
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetManualRGB(HVAPI_HANDLE_EX hHandle, INT nGainR, INT nGainG, INT nGainB  );


/**
* @brief		����AGCʹ�ܿ���
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nEnable			���أ���Χ��0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetAGCEnable(HVAPI_HANDLE_EX hHandle, INT nEnable );


/**
* @brief		����AGC��׼ֵ
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nLightBaseLine	��׼ֵ����Χ��0��255
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetAGCLightBaseLine(HVAPI_HANDLE_EX hHandle, INT nLightBaseLine );


/**
* @brief		����AGC����
* @param[in]	hHandle		��Ӧ�豸����Ч���
* @param[in]	rgZone		AGC����ֵ����Χ��0�������⣬1��������
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetAGCZone(HVAPI_HANDLE_EX hHandle, INT rgZone[16] );

/**
* @brief		��ȡAGC�������,16��ֵ
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	rgZone[16]	    ACG����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetAGCZone(HVAPI_HANDLE_EX hHandle, INT rgZone[16]);


/**
* @brief		����AGC����
* @param[in]	hHandle		��Ӧ�豸����Ч���
* @param[in]	nShutterMin ,AGC��С���ţ���Χ�� 100~30000
* @param[in]	nShutterMax ,AGC�����ţ���Χ�� 100~30000
* @param[in]	nGainMin    ,AGC��С���棬��Χ�� 0~42
* @param[in]	nGainMax    ,AGC������棬��Χ�� 0~42
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetAGCParam(HVAPI_HANDLE_EX hHandle,INT nShutterMin , INT nShutterMax ,
										  INT nGainMin , INT nGainMax );

/**
* @brief		��������LUT
* @param[in]	hHandle				��Ӧ�豸����Ч���
* @param[in]	rgLUT				LUT��
* @param[in]	nLUTPointCount		LUT��������Χ��8
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetLUT(HVAPI_HANDLE_EX hHandle, CHvPoint rgLUT[] , INT nLUTPointCount );

/**
* @brief		��ȡ����LUT״̬
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	rgLUT			LUT��״̬
* @param[in]	pnLUTPointCount	LUT������
** @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetLUT(HVAPI_HANDLE_EX hHandle, CHvPoint rgLUT[] , INT* pnLUTPointCount );


/**
* @brief		��������ֵ
* @param[in]	hHandle		 ��Ӧ�豸����Ч���
* @param[in]	nBrightness ,����ֵ����Χ��0��255  
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetBrightness(HVAPI_HANDLE_EX hHandle, INT nBrightness );


/**
* @brief		���öԱȶ�
* @param[in]	hHandle		 ��Ӧ�豸����Ч���
* @param[in]	nContrast    �Աȶ�ֵ����Χ��0��255  
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetContrast(HVAPI_HANDLE_EX hHandle, INT nContrast );


/**
* @brief		�������
* @param[in]	hHandle		 ��Ӧ�豸����Ч���
* @param[in]	nSharpness    �Աȶ�ֵ����Χ��0��255  
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetSharpness(HVAPI_HANDLE_EX hHandle, INT nSharpness );


/**
* @brief		���ñ��Ͷ�
* @param[in]	hHandle		 ��Ӧ�豸����Ч���
* @param[in]	nSaturation   ���Ͷ�ֵ����Χ��0��255  
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetSaturation(HVAPI_HANDLE_EX hHandle, INT nSaturation );


/**
* @brief		���ÿ�̬����
* @param[in]	hHandle	      ��Ӧ�豸����Ч���
* @param[in]	fEnable		  ��̬���أ���Χ��0���رգ�1����  
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetWDREnable(HVAPI_HANDLE_EX hHandle, BOOL fEnable  );


/**
* @brief		���ÿ�̬�ȼ�
* @param[in]	hHandle	      ��Ӧ�豸����Ч���
* @param[in]	nLevel		  ��̬�ȼ�����Χ��0������1���У�2��ǿ
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetWDRLevel(HVAPI_HANDLE_EX hHandle, INT nLevel );

/**
* @brief		������Ƶ����TNF����
* @param[in]	hHandle	      ��Ӧ�豸����Ч���
* @param[in]	fEnable		  ��Ƶ���뿪�أ���Χ��0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetDeNoiseTNFEnable(HVAPI_HANDLE_EX hHandle, BOOL fEnable );


/**
* @brief		������Ƶ����SNF����
* @param[in]	hHandle	      ��Ӧ�豸����Ч���
* @param[in]	fEnable		  ��Ƶ���뿪�أ���Χ��0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetDeNoiseSNFEnable(HVAPI_HANDLE_EX hHandle, BOOL fEnable );

/**
* @brief		������Ƶ����ģʽ
* @param[in]	hHandle	      ��Ӧ�豸����Ч���
* @param[in]	nMode		  ��Ƶ����ģʽ����Χ��0���ٶ� ��1������ ���ýӿ������踴λ��Ч
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetDeNoiseMode(HVAPI_HANDLE_EX hHandle, INT nMode );

/**
* @brief		������Ƶ������Ͽ���
* @param[in]	hHandle	      ��Ӧ�豸����Ч���
* @param[in]	nMode		  ��Ƶ���뿪�أ���Χ��0��SNF,1:TNF,2:TNF+SNF
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetDeNoiseSwitch(HVAPI_HANDLE_EX hHandle, INT nSwitch );

/**
* @brief		������Ƶ����ȼ�
* @param[in]	hHandle	      ��Ӧ�豸����Ч���
* @param[in]	nLevel		  ��Ƶ����ȼ�����Χ��0: �Զ� 1������2���У�3��ǿ
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetDeNoiseLevel(HVAPI_HANDLE_EX hHandle,INT nLevel );


/**
* @brief		�����˹�Ƭģʽ
* @param[in]	hHandle	      ��Ӧ�豸����Ч���
* @param[in]	nMode		  �˹�Ƭģʽ����Χ��0: �Զ���1�����˺��� ��2�������˺���
										 �������÷��Զ�ģʽ ���ϲ��ã�2 ������ã�1��
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetFilterMode(HVAPI_HANDLE_EX hHandle, INT nMode );


/**
* @brief		�����˹�Ƭʹ��
* @param[in]	hHandle	      ��Ӧ�豸����Ч���	
* @param[in]	fEnable		  �˹�Ƭʹ�ܣ���Χ��0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetCtrlCplEnable(HVAPI_HANDLE_EX hHandle, BOOL fEnable );


/**
* @brief		����DC��Ȧ�Զ�����
* @param[in]	hHandle	      ��Ӧ�豸����Ч���
* @param[in]	fEnable		  DC��Ȧ�Զ����ƿ��أ���Χ��0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetDCIRIS(HVAPI_HANDLE_EX hHandle, BOOL fEnable );


/**
* @brief		����IP��Ϣ
* @param[in]	hHandle	      ��Ӧ�豸����Ч���
* @param[in]	szIP		  IP�ַ���
* @param[in]	szMask		  ���������ַ���
* @param[in]	szGateWay	  �����ַ���
* @param[in]	szDNS		  DNS�ַ���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetIPInfo(HVAPI_HANDLE_EX hHandle, CHAR* szIP 
										,CHAR* szMask 
										,CHAR* szGateWay 
										,CHAR* szDNS  );

/**
* @brief		����RTSP�ಥ����
* @param[in]	hHandle	      ��Ӧ�豸����Ч���
* @param[in]	fEnable		RTSP�ಥ���أ���Χ��0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetRTSPMulticastEnable(HVAPI_HANDLE_EX hHandle, BOOL fEnable );


/**
* @brief		����ʱ��
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	nYear		��
* @param[in]	nMon		��
* @param[in]	nDay		��
* @param[in]	nHour		ʱ
* @param[in]	nMin		��
* @param[in]	nSec		��
* @param[in]	nMSec		����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetTime(HVAPI_HANDLE_EX hHandle, INT nYear , INT nMon , INT nDay , INT nHour ,INT nMin , INT nSec , INT nMSec );

/**
* @brief		����ʱ��
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	nZoneNum	 ʱ����� 0~24
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetTimeZone(HVAPI_HANDLE_EX hHandle, INT nZoneNum );

/**
* @brief		����NTP������IP
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	szIP		 NTP������IP�ַ���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetNTPServerIP(HVAPI_HANDLE_EX hHandle, CHAR* szIP );


/**
* @brief		����NTP������IP
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	dw32UpdateIntervalMS		 ����NTP������ʱ����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetNTPServerUpdateInterval(HVAPI_HANDLE_EX hHandle,DWORD32 dw32UpdateIntervalMS );


/**
* @brief		����NTP����
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	fEnable		 NTP���񿪹� 0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetNTPEnable(HVAPI_HANDLE_EX hHandle, BOOL fEnable );

/*
* @brief		����OC��
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	fEnable		 ���أ���Χ��0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetOCGate(HVAPI_HANDLE_EX hHandle, BOOL fEnable );

/*
* @brief		����ɫ��
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	nValue		 ��Χ��0:���Զ���; 32; 40 ;52 ;55 ; 60 ;70 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetColor(HVAPI_HANDLE_EX hHandle, INT nValue );

/*
* @brief		����2D���뿪��
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	fEnable		 ��Χ��0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_Set2DDeNoiseEnable(HVAPI_HANDLE_EX hHandle, BOOL fEnable );

/*
* @brief		����2D����ǿ��
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	nValue		 ��Χ��0��255
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_Set2DDeNoiseStrength(HVAPI_HANDLE_EX hHandle, INT nValue );

/*
* @brief		����GAMMA����
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	fEnable		 ��Χ��0�� �رգ� 1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetGammaEnable(HVAPI_HANDLE_EX hHandle, BOOL fValue );

/*
* @brief		����GAMMAǿ��
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	fValue		 ��Χ��1��5
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetGammaStrength(HVAPI_HANDLE_EX hHandle, INT nValue );

/**
* @brief		��λ�豸
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_ResetDevice(HVAPI_HANDLE_EX hHandle , INT nRetsetMode );

/**
* @brief		�ָ�Ĭ������
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  
*/
HV_API_EX HRESULT CDECL HVAPI_RestoreDefaultParam(HVAPI_HANDLE_EX hHandle);

/**
* @brief		�ָ���������
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_RestoreFactoryParam(HVAPI_HANDLE_EX hHandle);

/**
* @brief		��ȡ�豸������Ϣ
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	pbasicInfo	 �豸������Ϣ
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetDevBasicInfo(HVAPI_HANDLE_EX hHandle, CDevBasicInfo* pbasicInfo  );

/**
* @brief		��ȡ����ģʽ
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	pnRunMode	����ģʽָ��
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetRunMode(HVAPI_HANDLE_EX hHandle, INT* pnRunMode );

/**
* @brief		��ȡ�豸״̬
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	pState	 ״̬�ṹ��ָ��
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetDevState(HVAPI_HANDLE_EX hHandle, CDevState* pState  );

/**
* @brief		��ȡ�豸״̬
* @param[in]	hHandle	     ��Ӧ�豸����Ч���
* @param[in]	pReportBuf	 ��λ�����ڴ�ָ��
* @param[in]	pnBufLen	 ��λ�������ݳ���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetResetReport(HVAPI_HANDLE_EX hHandle,CHAR* pReportBuf, INT* pnBufLen  );

/**
* @brief		��ȡ�豸״̬
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	pnResetCount	��λ����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetResetCount(HVAPI_HANDLE_EX hHandle, INT* pnResetCount );

/**
* @brief		��ȡ�豸״̬
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	szLog			������־�����ڴ�ָ��
* @param[in]	pnLogLen		������־���ݳ���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetLog(HVAPI_HANDLE_EX hHandle, CHAR* szLog , INT* pnLogLen );

/**
* @brief		��ȡ�豸״̬
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	szLog			������־�����ڴ�ָ��
* @param[in]	pnLogLen		������־���ݳ���
* @param[in]	iLogType        ��־����   1������־  2������־   3������־
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetLogEx(HVAPI_HANDLE_EX hHandle, CHAR* szLog , INT* pnLogLen ,INT iLogType);

/**
* @brief		��ȡ�豸״̬
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	pVideoState		��Ƶ״̬
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetVideoState(HVAPI_HANDLE_EX hHandle, CVideoState* pVideoState );

/**
* @brief		��ȡ���״̬
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	pCameraState	���״ָ̬��
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetCameraState(HVAPI_HANDLE_EX hHandle, CCameraState* pCameraState );


/**
* @brief		��ȡ���������Ϣ
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	pCameraBasicInfo	���������Ϣָ��
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetCameraBasicInfo(HVAPI_HANDLE_EX hHandle, CCameraBasicInfo* pCameraBasicInfo );

/**
* @brief		��ȡӲ�̼�ⱨ��
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	szReport		��ⱨ��
* @param[in]	piReportLen		��ⱨ�泤��
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetHddCheckReport(HVAPI_HANDLE_EX hHandle, CHAR* szReport , INT *piReportLen  );

/**
* @brief		��ȡ�ַ�������Ϣ
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	nStreamId		��Ƶ��ID
* @param[in]	pOSDInfo		�ַ�������Ϣ
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetOSDInfo(HVAPI_HANDLE_EX hHandle,  INT nStreamId , COSDInfo* pOSDInfo  );


/**
* @brief		��¼
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	szUserName		�û����ַ���  ���ȷ�Χ��4��16�ֽ�
* @param[in]	szPassword		�����ַ���  ���ȷ�Χ��4��16�ֽ�
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_Login(HVAPI_HANDLE_EX hHandle, CHAR* szUserName ,  CHAR* szPassword  );

/**
* @brief		�����û�
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	szUserName		�û����ַ��� ���ȷ�Χ��4��16�ֽ�
* @param[in]	szPassword		�����ַ���  ���ȷ�Χ��4��16�ֽ�
* @param[in]	nAuthority		�û��ȼ�
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
* @Remark		�˽ӿڵ���ǰ����ɹ�����HVAPI_Login
*/
HV_API_EX HRESULT CDECL HVAPI_AddUser( HVAPI_HANDLE_EX hHandle, CHAR* szUserName , CHAR* szPassword,  INT nAuthority );

/**
* @brief		ɾ���û�
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	szUserName		�û����ַ���  ���ȷ�Χ��4��16�ֽ�
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
* @Remark		�˽ӿڵ���ǰ����ɹ�����HVAPI_Login
*/
HV_API_EX HRESULT CDECL HVAPI_DelUser(HVAPI_HANDLE_EX hHandle, CHAR* szUserName );

/**
* @brief		��ȡ�û��б�
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	rgUserInfo		�û���Ϣ�б�
* @param[in]	pnUserCount		�û���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
* @Remark		�˽ӿڵ���ǰ����ɹ�����HVAPI_Login
*/
HV_API_EX HRESULT CDECL HVAPI_GetUsersList(HVAPI_HANDLE_EX hHandle, CUserInfo rgUserInfo[] , INT* pnUserCount );

/**
* @brief		�޸��û���Ϣ
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	szUserName		�û����ַ���  ���ȷ�Χ��4��16�ֽ�
* @param[in]	szOldPassword	�����ַ���	  ���ȷ�Χ��4��16�ֽ�
* @param[in]	szNewPassword	�����ַ���	  ���ȷ�Χ��4��16�ֽ�
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
* @Remark		�˽ӿڵ���ǰ����ɹ�����HVAPI_Login
*/
HV_API_EX HRESULT CDECL HVAPI_ModUser(HVAPI_HANDLE_EX hHandle,CHAR* szUserName ,CHAR* szOldPassword, CHAR* szNewPassword );
/**
* @brief		����ͼƬ
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	pCapImage		ץ��ͼ�ڴ�ָ��
* @param[in]	pnCapImageSize	ץ��ͼ�ڴ��С
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_TriggerImage(HVAPI_HANDLE_EX hHandle, PBYTE pCapImage , INT* pnCapImageSize );


/**
* @brief		�����豸���ڼ�⹦��
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	nCOMNum			������������
* @param[in]	fEnable	        ���ر�ʶ
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_StartCOMCheck(HVAPI_HANDLE_EX hHandle, INT nCOMNum, BOOL fEnable );


/**
* @brief		�������ʹ��
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetSharpnessEnable(HVAPI_HANDLE_EX hHandle, BOOL fEnable);

/**
* @brief		���������Ȧ�Ŵ� 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_ZoomDCIRIS(HVAPI_HANDLE_EX hHandle); 

/**
* @brief		���������Ȧ��С 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_ShrinkDCIRIS(HVAPI_HANDLE_EX hHandle); 



/**
* @brief		�ڰ�ͼģʽ
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	fEnable	        ������־
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetGrayImageEnable(HVAPI_HANDLE_EX hHandle, BOOL fEnable); 


/**
* @brief		����ͬ��
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	nLevel	        ����ͬ��ģʽ
* @param[in]	dwDelayMS	    ͬ����ʱ
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetACSync(HVAPI_HANDLE_EX hHandle, INT nLevel, DWORD32 dw32DelayMS); 

/**
* @brief		���õ�����������
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @param[in]	fEnable			������������
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetDebugJpegStatus(HVAPI_HANDLE_EX hHandle, BOOL fEnable);  

/**
* @brief		�����Զ������������
* @param[in]	hHandle	        ��Ӧ�豸����Ч���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_StartCameraTest(HVAPI_HANDLE_EX hHandle);  

/**
* @brief		����jpeg�Զ�ѹ��ʹ��
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetAutoJpegCompressEnable(HVAPI_HANDLE_EX hHandle,  BOOL fEnable);

/**
* @brief		��ȡ���Եȼ�
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetTraceRank(HVAPI_HANDLE_EX hHandle, INT nlevel);

/**
* @brief		����jpeg�Զ�ѹ������
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetAutoJpegCompressParam (HVAPI_HANDLE_EX hHandle, INT nMaxCompressRate, INT nMinCompressRate, INT nImageSize);

/**
* @brief		����ͼ����ǿʹ��
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetImageEnhancementEnable(HVAPI_HANDLE_EX hHandle, BOOL fEnable);

/**
* @brief		���ú�ƼӺ���ֵ
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetEnRedLightThreshold(HVAPI_HANDLE_EX hHandle, INT nValue);

/**
* @brief		�������ӱ�Ե��ǿ
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetEdgeEnhance(HVAPI_HANDLE_EX hHandle, INT nValue);

/**
* @brief		��ȡ��Ƶ�ɼ�������Ϣ
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetRunStatusString(HVAPI_HANDLE_EX hHandle, CHAR* szRunStatusString, INT* pnRunStatusStringLen  );

/**
* @brief		��ȡ�������������״̬
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetCameraWorkState(HVAPI_HANDLE_EX hHandle, CHAR* szStatus, INT* pnStatusStringLen  );

/**
* @brief		��ȡӲ��״̬
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetHDDStatus(HVAPI_HANDLE_EX hHandle, CHAR* szStatus, INT* pnStatusStringLen  );


/**
* @brief		���ô���ץ������IO�ڴ�������
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetTGIO(HVAPI_HANDLE_EX hHandle, INT nValue  );

/**
* @brief		��ȡ����ץ������IO�ڴ�������
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetTGIO(HVAPI_HANDLE_EX hHandle, INT* pnValue  );

/**
* @brief		���ô������IO��״̬ 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetF1IO(HVAPI_HANDLE_EX hHandle, INT nPolarity, INT nType);

/**
* @brief		��ȡ�������IO��״̬
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetF1IO(HVAPI_HANDLE_EX hHandle, INT* pnPolarity, INT* pnType);


/**
* @brief		���ò����IO��״̬ 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetEXPIO(HVAPI_HANDLE_EX hHandle, INT nPolarity, INT nType);


/**
* @brief		��ȡ�����IO��״̬ 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetEXPIO(HVAPI_HANDLE_EX hHandle, INT* pnPolarity, INT* pnType);


/**
* @brief		���ñ���IO��״̬ 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetALMIO(HVAPI_HANDLE_EX hHandle, INT nPolarity, INT nType);


/**
* @brief		��ȡ����IO��״̬ 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetALMIO(HVAPI_HANDLE_EX hHandle, INT* pnPolarity, INT* pnType);

/**
* @brief		����MJPEG����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetMJPEGRect(HVAPI_HANDLE_EX hHandle, CHvPoint PosTopLeft, CHvPoint PosLowerRight);


/**
* @brief		����ɫ�� 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetColorGradation(HVAPI_HANDLE_EX hHandle, INT nValue);

/**
* @brief		������Ƶ������� 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetVedioRequestControl(HVAPI_HANDLE_EX hHandle, BOOL fEnable,  DWORD32 dwIP, INT nPort);

/**
* @brief		����AE���� 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetAEScene(HVAPI_HANDLE_EX hHandle, INT nMode);

/**
* @brief		��ȡAE���� 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetAEScene(HVAPI_HANDLE_EX hHandle, INT* pnMode);


/**
* @brief		��ȡ�豸�� 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetCustomizedDevName(HVAPI_HANDLE_EX hHandle, CHAR* pszDevName, INT* pnDevNameLen);


/**
* @brief		�����豸�� 
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetCustomizedDevName(HVAPI_HANDLE_EX hHandle, CHAR* pszDevName);


/**
* @brief		����H264����
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nBitRate		
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetH264SecondBitRate(HVAPI_HANDLE_EX hHandle, INT nBitRate );


/**
* @brief		��ȡH264����
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	pnBitRate		
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetH264SecondBitRate(HVAPI_HANDLE_EX hHandle, INT* pnBitRate );

/**
* @brief		����ץ��
* @param[in]	hHandle			��Ӧ�豸����Ч���	
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SoftTriggerCapture(HVAPI_HANDLE_EX hHandle);

/**
* @brief		����ץ�Ŀ���
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nEnable			ʹ�ܿ���
* @param[in]	nValue			ץ�Ŀ���ֵ
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetManualCaptureShutter(HVAPI_HANDLE_EX hHandle, INT nEnable, INT nValue);

/**
* @brief		����ץ������
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nEnable			ʹ�ܿ���
* @param[in]	nValue			ץ������ֵ
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetManualCaptureGain(HVAPI_HANDLE_EX hHandle, INT nEnable, INT nValue);

/**
* @brief		����ץ��RGB����
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nEnable			ʹ�ܿ���
* @param[in]	nValueR			ץ��R����
* @param[in]	nValueG			ץ��G����
* @param[in]	nValueB			ץ��B����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetManualCaptureRGB(HVAPI_HANDLE_EX hHandle, INT nEnable, INT nValueR, INT nValueG, INT nValueB);

/**
* @brief		����ץ�����
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nEnable			ʹ�ܿ���
* @param[in]	nValue			ץ�����ֵ
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetManualCaptureSharpen(HVAPI_HANDLE_EX hHandle, INT nEnable, INT nSharpen);

/**
* @brief		����LED����
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nValue			����ֵ
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetExpPluseWidth(HVAPI_HANDLE_EX hHandle, INT nValue);

/**
* @brief			����������
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		nNum			Ҫ���õ����   0��׼��  1��ǿ��    2 ������Ϣ��
* @param[in]		szUploadDate		Ҫ���浽�豸������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetFaceDataAdv(HVAPI_HANDLE_EX hHandle, INT nNum, CHAR* szUploadDate, DWORD32 dwDataLen);

/**
* @brief			����DSP����
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szUploadDate		Ҫ���浽�豸������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetDSPParam(HVAPI_HANDLE_EX hHandle, CHAR* szUploadDate, DWORD32 dwDataLen);

/**
* @brief                ����AEģʽ
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]	nValue 		AEģʽ����Χ��0:�Զ�;1:�ֶ�;2:��Ȧ����;3:��������
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetAEMode(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡAEģʽ
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]	pnValue	AEģʽ   
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetAEMode(HVAPI_HANDLE_EX hHandle, INT* pnValue );


/**
* @brief                ���ð�ƽ��ģʽ
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue 	��ƽ��ģʽ����Χ0:�Զ�;1:ATW(Auto Tracing White balance);2:����;3:����;4:����һ�ε���(�ðװ��ʱ���õ����ϵ����ڵ�ֵ�Żᶪʧ);5:�ֶ�;6:�Զ�����;7:�Զ��ɵ�;8:�ɵ�
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetManualAWBMode(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡ��ƽ��ģʽ
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]	pnValue  ��ƽ��ģʽ   
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetManualAWBMode(HVAPI_HANDLE_EX hHandle, INT* pnValue );


/**
* @brief                ����AFʹ��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  �Զ��۽�ʹ�ܣ���Χ0:�Զ��۽�;1:�ֶ��۽�;
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetAFEnable(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡAFʹ��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue    �Զ��۽�ʹ��
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetAFEnable(HVAPI_HANDLE_EX hHandle, INT* pnValue );


/**
* @brief                ���ù�Ȧֵ
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ��Ȧֵ����Χ��13:F1.6;12:F2;11:F2.4;10:F2.8;9:F3.4;8:F4;7:F4.8;6:F5.6;5:F6.8;4:F8;3:F9.6;2:F11;1:F14;0:CLOSE
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetIRIS(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡ��Ȧֵ
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue   ��Ȧֵ 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetIRIS(HVAPI_HANDLE_EX hHandle, INT* pnValue );


/**
* @brief                ���þ۽�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  �۽�ֵ����Χ��0x1000 ~ 0xd000
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetFocusing(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡ�۽�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue    �۽�ֵ
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetFocusing(HVAPI_HANDLE_EX hHandle, INT* pnValue );


/**
* @brief                ���ý��ࣨ���÷Ŵ�ͼ��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ���࣬��Χ��100~3000
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetZoom(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡ���ࣨ��ȡ�Ŵ�����
* @param[in]     hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue    ����
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetZoom(HVAPI_HANDLE_EX hHandle, INT* pnValue );


/**
* @brief                ���ø����۽�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetAssistantFocus(HVAPI_HANDLE_EX hHandle);

/**
* @brief                ΢����Ȧ
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ���ڱ�ʶ  ��Χ��0 ��С��  1����
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_TuneIris(HVAPI_HANDLE_EX hHandle, INT nValue );
/**
* @brief                ΢���۽�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ��Χ��0 ��С��  1����
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_TuneFocus(HVAPI_HANDLE_EX hHandle, INT nValue );

/**
* @brief                ��ʼ��������
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue   ���ű�ʶ ��Χ��0�Ŵ�  1��С
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StartZoom(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ֹͣ��������
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StopZoom(HVAPI_HANDLE_EX hHandle);

/**
* @brief                ���ú���LED�����ģʽ
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  LEDģʽ����Χ:0-�ر� 1-�ֶ� 2-�Զ����ƣ��豸���ݹ����������ȣ� 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetLEDMode(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡ����LED�����״̬
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue    LEDģʽ
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetLEDMode(HVAPI_HANDLE_EX hHandle, INT* pnValue);;

/**
* @brief                ���ú���LED����ƹ���
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ����LED����ƹ��ʣ���Χ��100~3000
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetLEDPower(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡ����LED����ƹ���
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue    ����LED����ƹ���
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetLEDPower(HVAPI_HANDLE_EX hHandle, INT* pnValue );

/**
* @brief                ��ʼ��ˢ����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StartWiper(HVAPI_HANDLE_EX hHandle);


/**
* @brief                ����Ԥ��λ
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nNum    Ԥ��λ���	��Χ��0~255
* @param[in]    szName 	Ԥ��λ���ַ���  ���ȷ�Χ��1��31�ֽ�
* @param[in]    nValue  ���Υ�±�־ ��Χ�� 0���رգ�  1:����
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetPreset(HVAPI_HANDLE_EX hHandle,  INT nNum, CHAR* szName,  BOOL nValue );


/**
* @brief                ��ȡԤ��λ
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[in]    nNum    Ԥ��λ���	��Χ��0~255
* @param[out]    szName 	Ԥ��λ���ַ���
* @param[out]    pnNameLen 	Ԥ��λ���ַ�������
* @param[out]    pfValue 	���Υ�±�־
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetPreset(HVAPI_HANDLE_EX hHandle,   INT nNum, CHAR* szName,INT* pnNameLen, BOOL* pfValue );


/**
* @brief                ����Ԥ��λ
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  Ԥ��λ���	��Χ��0~255
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_CallPreset(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ���Ԥ��λ
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  Ԥ��λ���	��Χ��0~255
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_ClearPreset(HVAPI_HANDLE_EX hHandle, INT nValue );



/**
* @brief                ��ȡԤ��λ�����б�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    szNameList  Ԥ��λ���ƺͼ��Υ�±�־�б�(��������;�ŷָ��������ƺͼ��Υ�±�־��:��������"Ԥ��λ1:0;Ԥ��λ2:1;")     
* @param[out]    pnNameListLen    Ԥ��λ�����б���   
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetPresetNameList(HVAPI_HANDLE_EX hHandle,  CHAR szNameList[], INT* pnNameListLen );


/**
* @brief                ���û��涳���־
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    fEnable ���涳���־  ��Χ�� 0�������� 1������    
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetFreezeFlag(HVAPI_HANDLE_EX hHandle, BOOL fEnable);


/**
* @brief                ��ȡ���涳���־
* @param[in]    hHandle                 ��Ӧ�豸����Ч��� 
* @param[out]    pfEnable   ���涳���־   
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetFreezeFlag(HVAPI_HANDLE_EX hHandle, BOOL* pfEnable);

/**
* @brief                ����ˮƽɨ����������ơ��ٶȡ�����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nNum	 ˮƽɨ����� ��Χ�� 0~7
* @param[in]    szScanName   ˮƽɨ������  ���ȷ�Χ��1��31�ֽ� 
* @param[in]    nSpeed   ˮƽɨ���ٶȵȼ�   ��Χ��1~30   
* @param[in]    nDirection   ˮƽɨ�跽��   ��Χ��0��˳ʱ�� 1����ʱ��   
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetHScanParam(HVAPI_HANDLE_EX hHandle,  INT nNum, CHAR* szScanName, INT nSpeed, INT nDirection );


/**
* @brief                ��ȡˮƽɨ����������ơ��ٶȡ�����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[in]    nNum	 ˮƽɨ����� ��Χ�� 0~7
* @param[out]    szScanName   ˮƽɨ������ 
* @param[out]    pnNameLen 	ˮƽɨ�����ַ�������
* @param[out]    pnSpeed   ˮƽɨ���ٶȵȼ�  
* @param[out]    pnDirection   ˮƽɨ�跽��     
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetHScanParam(HVAPI_HANDLE_EX hHandle,  INT nNum, CHAR* szScanName, INT* pnNameLen, INT* pnSpeed, INT* pnDirection );

/**
* @brief                ����ˮƽɨ������λ
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nNum  ˮƽɨ����� ��Χ�� 0~7
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetHScanLeftPos(HVAPI_HANDLE_EX hHandle, INT nNum );



/**
* @brief                ����ˮƽɨ������λ
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nNum  ˮƽɨ����� ��Χ�� 0~7
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetHScanRightPos(HVAPI_HANDLE_EX hHandle, INT nNum );


/**
* @brief                ��ʼˮƽɨ��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nNum  ˮƽɨ����� ��Χ�� 0~7
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StartHScan(HVAPI_HANDLE_EX hHandle, INT nNum );


/**
* @brief                ֹͣˮƽɨ��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nNum  ˮƽɨ����� ��Χ�� 0~7
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StopHScan(HVAPI_HANDLE_EX hHandle, INT nNum );

/**
* @brief                ���ˮƽɨ��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nNum  ˮƽɨ����� ��Χ�� 0~7
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_ClearHScan(HVAPI_HANDLE_EX hHandle, INT nNum );



/**
* @brief                ��ʼ����ɨ��·��¼��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ����ɨ�����  ��Χ��0~3
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StartFigureScanRecord(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ֹͣ����ɨ��·��¼��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue   ����ɨ�����  ��Χ��0~3
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StopFigureScanRecord(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ���û���ɨ��·��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue   ����ɨ�����  ��Χ��0~3
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_CallFigureScan(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ֹͣ����ɨ��·��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue   ����ɨ�����  ��Χ��0~3
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StopFigureScan (HVAPI_HANDLE_EX hHandle, INT nValue );

/**
* @brief                �������ɨ��·��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue   ����ɨ�����  ��Χ��0~3
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_ClearFigureScan(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ���û���ɨ��·������
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nNum    ����ɨ�����	��Χ��0~255
* @param[in]    szName 	����ɨ�����ַ���  ���ȷ�Χ��1��31�ֽ�
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetFigureScanName(HVAPI_HANDLE_EX hHandle,  INT nNum, CHAR* szName );


/**
* @brief                ��ȡ����ɨ��·������
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[in]    nNum    ����ɨ�����	��Χ��0~255
* @param[out]    szName 	����ɨ�����ַ���  ���ȷ�Χ��1��31�ֽ�
* @param[out]    pnNameLen 	����ɨ�����ַ�������
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetFigureScanName(HVAPI_HANDLE_EX hHandle,  INT nNum, CHAR* szName, INT* pnNameLen );


/**
* @brief                ��ȡ����ɨ�������б�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    szNameList     ����ɨ�������б�(��������;�ŷָ���)         
* @param[out]    pnNameListLen 	����ɨ�������б���   
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetFigureScanNameList(HVAPI_HANDLE_EX hHandle,  CHAR szNameList[], INT* pnNameListLen );


/**
* @brief                ����Ѳ��·��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nNum   Ѳ����� ��Χ��0~7 
* @param[in]    szName 	Ѳ�����ַ���  ���ȷ�Χ��1��31�ֽ� 
* @param[in]    nActCount �������� ��Χ�� 0~14
* @param[in]    ActType  ������������ ��Χ���������� 0~2��0Ԥ��λ 1ˮƽɨ�� 2����ɨ�� ��  
* @param[in]    ActNum   �����������  ��Χ����Ԥ��λ0~255  ˮƽɨ��0~7 ����ɨ��0~3��  
* @param[in]    Time  פ��ʱ��  ��Χ�� 1~3600��
* @param[in]    fCheckPeccancy  �������� 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetCruise(HVAPI_HANDLE_EX hHandle,  INT nNum, CHAR* szName, INT nActCount, INT ActType[], INT ActNum[], INT Time[], BOOL fCheckPeccancy );


/**
* @brief                ��ȡѲ��·��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[in]     nNum   Ѳ����� ��Χ��0~7 
* @param[out]    szName 	Ѳ�����ַ��� 
* @param[out]    pNameLen 	Ѳ�����ַ������� 
* @param[out]    pnActCount �������� 
* @param[out]    ActType  ������������  
* @param[out]    ActNum   �����������    
* @param[out]    Time  פ��ʱ��  
* @param[out]    pfCheckPeccancy  ��������  
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetCruise(HVAPI_HANDLE_EX hHandle,  INT nNum, CHAR* szName, INT* pNameLen, INT* pnActCount, INT ActType[], INT ActNum[],  INT Time[], BOOL* pfCheckPeccancy );


/**
* @brief                ����Ѳ��·��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  Ѳ����� ��Χ��0~7 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_CallCruise(HVAPI_HANDLE_EX hHandle, INT nValue );

/**
* @brief                ֹͣѲ��·��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  Ѳ����� ��Χ��0~7 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StopCruise(HVAPI_HANDLE_EX hHandle, INT nValue );

/**
* @brief                ���Ѳ��·��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  Ѳ����� ��Χ��0~7 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_ClearCruise(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��������
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    ActType  ��������   ��Χ���������� 0~3��0Ԥ��λ 1ˮƽɨ�� 2����ɨ�� 3Ѳ�� ��  
* @param[in]    ActNum   �������  ��Χ��Ԥ��λ0~255  ˮƽɨ��0~7 ����ɨ��0~3 Ѳ��0~7
* @param[in]    Time     �����ȴ�ʱ��  ��Χ 5~3600��
* @param[in]    fEnable  �Ƿ����ñ�־  ��Χ�� 0~1
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetWatch(HVAPI_HANDLE_EX hHandle,  INT ActType, INT ActNum, INT Time, BOOL fEnable );


/**
* @brief                ��ȡ����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    ActType  ��������    
* @param[out]    ActNum   �������  
* @param[out]    Time     �����ȴ�ʱ��   
* @param[out]    pfEnable  �Ƿ����ñ�־    
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetWatch(HVAPI_HANDLE_EX hHandle,  INT* ActType, INT* ActNum, INT* Time, BOOL* pfEnable );

/**
* @brief                ��ʼ����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StartWatchKeeping(HVAPI_HANDLE_EX hHandle);



/**
* @brief                ������˽����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nNum   ��˽�������  ��Χ��0~15
* @param[in]    szName  ��˽�����������ַ���  ���ȷ�Χ��1��31�ֽ�
* @param[in]    nPoxX  ������  ��Χ�� 0~1920����
* @param[in]    nPoxY  ������  ��Χ�� 0~1080����
* @param[in]    nwidth ��  ��Χ�� 0~1920����
* @param[in]    nheight ��  ��Χ�� 0~1080����
* @param[in]    nColor  ��˽������ɫ����Χ��0x00~0x0D 0x00:Black   0x01:Gray1   0x02:Gray2   0x03:Gray3   0x04:Gray4   0x05:Gray5   0x06:Gray6   0x07:White   0x08:Red:  0x09:Green   0x0A:Blue: 0x0B:Cyan: 0x0C:Yellow  0x0D:Magenta   
* @param[in]    nPreSet Ԥ��λ���  ��Χ�� 0~255
* @param[in]    nFlag  �Ƿ�������˽���� ��Χ0~1
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetMask(HVAPI_HANDLE_EX hHandle,  INT nNum, CHAR* szName, INT nPoxX,INT nPoxY, INT nwidth, INT nheight, INT nColor, INT nPreSet, INT nFlag );


/**
* @brief                ��ȡ��˽����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[in]    nNum   ��˽�������  ��Χ��0~15
* @param[out]    szName  ��˽�����������ַ��� 
* @param[out]    pnNameLen 	��˽���������ַ�������
* @param[out]    nPoxX  ������   
* @param[out]    nPoxY  ������   
* @param[out]    nwidth ��   
* @param[out]    nheight ��   
* @param[out]    nColor  ��˽������ɫ 
* @param[out]    nPreSet Ԥ��λ���   
* @param[out]    pnFlag  �Ƿ�������˽����  
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetMask(HVAPI_HANDLE_EX hHandle,  INT nNum, CHAR* szName,INT* pnNameLen, INT* nPoxX,  INT* nPoxY,  INT* nwidth, INT* nheight,  INT* nColor, INT* nPreSet, INT* pnFlag );

/**
* @brief                �����˽����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ��˽�������  ��Χ��0~15
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_ClearMask(HVAPI_HANDLE_EX hHandle, INT nValue );



/**
* @brief                ��ʼˮƽ�˶�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ˮƽ�˶�����  ��Χ�� 0����1����
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StartPan(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ֹͣˮƽ�˶�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StopPan(HVAPI_HANDLE_EX hHandle);


/**
* @brief                ����ˮƽ�˶��ٶ�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ˮƽ�˶��ٶ�  ��Χ��1~30
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetPanSpeed(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡˮƽ�˶��ٶ�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue	ˮƽ�˶��ٶ�
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetPanSpeed(HVAPI_HANDLE_EX hHandle, INT* pnValue );


/**
* @brief                ��ʼ��ֱ�˶�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ��ֱ�˶�����  ��Χ�� 0���� ��  1����
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StartTilt(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ֹͣ��ֱ�˶�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StopTilt(HVAPI_HANDLE_EX hHandle);


/**
* @brief                ��ʼ��ֱ��ת
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StartVturnOver(HVAPI_HANDLE_EX hHandle);


/**
* @brief                ֹͣ��ֱ��ת
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StopVturnOver(HVAPI_HANDLE_EX hHandle);


/**
* @brief                ���ô�ֱ�˶��ٶ�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ��ֱ�˶��ٶ�  ��Χ��1~30
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetTiltSpeed(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡ��ֱ�˶��ٶ�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue    ��ֱ�˶��ٶ�
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetTiltSpeed(HVAPI_HANDLE_EX hHandle, INT* pnValue );


/**
* @brief                ���ö�ʱ����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nNum    ��ʱ�����  ��Χ��0~11
* @param[in]    szName   ��ʱ�����ַ���  ���ȷ�Χ��1��31�ֽ� 
* @param[in]    bitArrDays    ���ڱ�������   ��Χ��0 ~ ��2^7-1��   1Ϊ��һ 2Ϊ�ܶ�  4���� 8Ϊ���� 16Ϊ���� 32Ϊ���� 64Ϊ���գ��������ڷ��䣬���л������
* @param[in]    BeginMinu    ��ʼʱ�� ��Χ��0~24*60-1 ����
* @param[in]    EndMinu      ����ʱ�� ��Χ��0~24*60-1 ����
* @param[in]    ActType    ��������  ��Χ�� 0~3��0Ԥ��λ 1ˮƽɨ�� 2����ɨ�� 3Ѳ�� ��  
* @param[in]    ActNum    �������   ��Χ��Ԥ��λ0~255  ˮƽɨ��0~7 ����ɨ��0~3 Ѳ��0~7 
* @param[in]    fValue    �Ƿ�����  ��Χ0~1
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetTimingParam(HVAPI_HANDLE_EX hHandle, INT nNum, CHAR* szName, INT bitArrDays, INT BeginMinu, INT EndMinu, INT ActType, INT ActNum , BOOL fValue );


/**
* @brief                ��ȡ��ʱ����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[in]    nNum    ��ʱ�����  ��Χ��0~11
* @param[out]    szName   ��ʱ�����ַ���  ���ȷ�Χ��1��31�ֽ� 
* @param[out]    pnNameLen 	��ʱ�����ַ�������
* @param[out]    bitArrDays    ���ڱ�������   
* @param[out]    BeginMintu    ��ʼʱ��  
* @param[out]    EndMinu      ����ʱ�� 
* @param[out]    ActType    ��������  
* @param[out]    ActNum    �������   
* @param[out]    pfValue    �Ƿ�����   
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetTimingParam(HVAPI_HANDLE_EX hHandle,INT nNum, CHAR* szName, INT* pnNameLen,INT *bitArrDays, INT* BeginMintu, INT* EndMinu, INT* ActType, INT*ActNum, BOOL* pfValue ) ;


/**
* @brief                ����Tilt�˶�����ٶ�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ���ֱ�˶��ٶ�  ��Χ��1~30
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetMaxTiltSpeed(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡTilt�˶�����ٶ�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue	Tilt�˶�����ٶ�
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetMaxTiltSpeed(HVAPI_HANDLE_EX hHandle, INT* pnValue );


/**
* @brief                ����Pan�˶�����ٶ�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ���ˮƽ�˶��ٶ�  ��Χ��1~30
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetMaxPanSpeed(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡPan�˶�����ٶ�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue  Pan�˶�����ٶ�  
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetMaxPanSpeed(HVAPI_HANDLE_EX hHandle, INT* pnValue );


/**
* @brief                ����ˮƽ����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ˮƽ���� ��Χ��0~3599
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetPanCoordinate(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡˮƽ����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue    ˮƽ����
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetPanCoordinate(HVAPI_HANDLE_EX hHandle, INT* pnValue );


/**
* @brief                ���ô�ֱ����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ��ֱ����  ��Χ��0~900
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetTiltCoordinate(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡ��ֱ����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue ��ֱ����
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetTiltCoordinate(HVAPI_HANDLE_EX hHandle, INT* pnValue );


/**
* @brief                ��ʼˮƽ��ֱ�˶�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  ˮƽ��ֱ�˶����� ��Χ��0�����£�1���ϣ�2�����£�3������
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StartPanAndTilt(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ֹͣˮƽ��ֱ�˶�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StopPanAndTilt(HVAPI_HANDLE_EX hHandle);


/**
* @brief                ���ƶ�������
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nPoxX   ������ ��Χ��0~1920 ����
* @param[in]    nPoxY	������ ��Χ��0~1080 ����
* @param[in]    fZoomOut �Ƿ���С��ʶ  ��Χ��0������С  1����С 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_MovePointToCenter(HVAPI_HANDLE_EX hHandle, INT nPoxX, INT nPoxY, BOOL fZoomOut );


/**
* @brief                �����ƶ�������
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nPoxX   ������ ��Χ��0~1920 ����
* @param[in]    nPoxY	������ ��Χ��0~1080 ����
* @param[in]    nWidth   ��   ��Χ��0~1920 ����
* @param[in]    nHeight	��   ��Χ��0~1080 ����
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_MoveBlockToCenter(HVAPI_HANDLE_EX hHandle, INT nPoxX, INT nPoxY, INT nWidth, INT nHeight );

/**
* @brief                ��λ���λ�õ���ʼ��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_ResetDevicePosition(HVAPI_HANDLE_EX hHandle);


/**
* @brief			���������ϢXML
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szUploadDate		Ҫ���浽�豸������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetSpeedDomeParam(HVAPI_HANDLE_EX hHandle,  CHAR* szUploadDate, DWORD32 dwDataLen);

/**
* @brief			���������ϢXML
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szDownloadDate		Ҫ���浽�豸������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetSpeedDomeParam(HVAPI_HANDLE_EX hHandle, CHAR* szDownloadDate, DWORD32* dwDataLen);

/**
* @brief			�ϴ��㷨����
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szUploadDate		�ϴ��㷨����
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetAlgorithmParameterData(HVAPI_HANDLE_EX hHandle, CHAR* szUploadDate, DWORD32 dwDataLen); 

/**
* @brief			�ϴ��㷨ģ��
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szUploadDate		�ϴ��㷨ģ��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetAlgorithmModelData(HVAPI_HANDLE_EX hHandle, CHAR* szUploadDate, DWORD32 dwDataLen);

/**
* @brief			͸�����ڴ���
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szUploadDate		͸�����ڴ���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetTransparentSerialData(HVAPI_HANDLE_EX hHandle, CHAR* szUploadDate, DWORD32 dwDataLen);

/**
* @brief			͸�����ڴ���
* @param[in]		hHandle			��Ӧ�豸����Ч���
* @param[in]		szUploadDate		͸�����ڴ���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetLastEor(INT* pEorCode);

/**
* @brief                ��ȡ��ǰִ������
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    szTaskName     ��ǰִ��������  ��Χ������ɨ�衢ˮƽ��Ѳ�������С�����ɨ��¼�ơ�����ˮƽɨ�衢��λ������ֱ��ӦFscan��Hscan��Cruise��idle��FScanRecord��InfinityPan��Reset
* @param[out]    pnNameLen   ִ������������     
* @param[out]    pTaskID     ��ǰִ������ID ��Χ����ɨ�衢ˮƽ��Ѳ�������С�����ɨ��¼�ơ�����ˮƽɨ�衢��λ������ֱ��ӦFscan��0~3��  Hscan��0~7�� Cruise��0~7�� idle�� 65535�� FScanRecordFScanRecord(0~3) InfinityPan��65535�� Reset��65535��
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetCurrentTask(HVAPI_HANDLE_EX hHandle, CHAR* szTaskName, INT* pnNameLen, INT* pTaskID );

/**
* @brief                ��ʼ������ת
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StartInfinityPan(HVAPI_HANDLE_EX hHandle);


/**
* @brief                ����������ת
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_StopInfinityPan(HVAPI_HANDLE_EX hHandle);


/**
* @brief                ����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue  �����ر�ʶ ��Χ��0�رգ�1����
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetDefog(HVAPI_HANDLE_EX hHandle, INT nValue );

/**
* @brief                ����I֡���
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetH264IFrameInterval(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡI֡���
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue    
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetH264IFrameInterval(HVAPI_HANDLE_EX hHandle, INT* pValue );


/**
* @brief                ����VBR�ĳ����仯ʱ��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetH264VbrDuration(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ����VBR�����仯�����ж�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetH264VbrSensitivity(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ���õڶ�·I֡���
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetH264SecondIFrameInterval(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ��ȡ�ڶ�·I֡���
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue    
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetH264SecondIFrameInterval(HVAPI_HANDLE_EX hHandle, INT* pValue );


/**
* @brief                ���õڶ�·���ʿ��Ʒ�ʽ0��VBR  1��CBR
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetH264SecondRateControl(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ���õڶ�·VBR�ĳ����仯ʱ��
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetH264SecondVbrDuration(HVAPI_HANDLE_EX hHandle, INT nValue );


/**
* @brief                ���õڶ�·VBR�����仯�����ж�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetH264SecondVbrSensitivity(HVAPI_HANDLE_EX hHandle, INT nValue );

/**
* @brief                ����ֹͣMJPEG�ַ�����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���      
* @param[in]    nValue 
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetMJPEGOverlay(HVAPI_HANDLE_EX hHandle, INT nValue );



/**
* @brief			����JPEG�������
* @param[in]		hHandle		��Ӧ�豸����Ч���
* @param[in]		nMode		Ҫ���浽�豸������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetJpegOutType(HVAPI_HANDLE_EX hHandle,  INT nMode);

/**
* @brief			��ȡJPEG�������
* @param[in]		hHandle		��Ӧ�豸����Ч���
* @param[out]		pnMode		��ȡ��������ֵ
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetJpegOutType(HVAPI_HANDLE_EX hHandle,  INT* pnMode);

/**
* @brief			������Ƶ����������ѡ��
* @param[in]		hHandle		��Ӧ�豸����Ч���
* @param[in]		nMode		Ҫ���浽�豸������
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetCoilEnable(HVAPI_HANDLE_EX hHandle,  INT nMode);

/**
* @brief			��ȡ��Ƶ����������ѡ��
* @param[in]		hHandle		��Ӧ�豸����Ч���
* @param[out]		pnMode		��ȡ����״ֵ̬
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetCoilEnable(HVAPI_HANDLE_EX hHandle,  INT* pnMode);


/**
* @brief			��ȡAWB����ģʽ
* @param[in]		hHandle		��Ӧ�豸����Ч���
* @param[out]		pfEnable		��ȡ��������ֵ
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetAWBWorkMode(HVAPI_HANDLE_EX hHandle,  BOOL* pfEnable);

/**
* @brief			����AWB����ģʽ
* @param[in]		hHandle		��Ӧ�豸����Ч���
* @param[in]		nEnable		���õ��豸��ģʽֵ
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetAWBWorkMode(HVAPI_HANDLE_EX hHandle, INT nEnable );

/**
* @brief			��ȡ���ȫ����
* @param[in]		hHandle		��Ӧ�豸����Ч���
* @param[out]		pfEnable		��ȡ����״ֵ̬
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetAutoControlCammeraEnable(HVAPI_HANDLE_EX hHandle,  BOOL* pfEnable);

/**
* @brief			�������ȫ����
* @param[in]		hHandle		��Ӧ�豸����Ч���
* @param[in]		nEnable		���õ��豸��ģʽֵ
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetAutoControlCammeraEnable(HVAPI_HANDLE_EX hHandle, INT nEnable );

/**
* @brief			��ȡH264�ֱ���
* @param[in]		hHandle		��Ӧ�豸����Ч���
* @param[out]		piValue		��ȡ����ֵ
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetH264Resolution(HVAPI_HANDLE_EX hHandle,  INT* piValue);

/**
* @brief			����H264�ֱ���
* @param[in]		hHandle		��Ӧ�豸����Ч���
* @param[in]		nEnable		���õ��豸��ֵ
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetH264Resolution(HVAPI_HANDLE_EX hHandle, INT nEnable );

/**
* @brief                ��ȡ�Զ��۽�״̬���жϾ۽��ɹ���������ɴ�0�� �����Զ��۽����-1 �ٵ� 0���״̬��״̬���С�
* @param[in]    hHandle                 ��Ӧ�豸����Ч���    
* @param[out]    pnValue       0����ǰδ�����Զ��۽�������Ƿ����Զ��۽�����󣬱�ʾ�Զ��۽��ѳɹ���  -1��δ��ɣ��Զ��۽��С�
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetAutoFocusStatus(HVAPI_HANDLE_EX hHandle, INT* pValue );

/**
* @brief                ����F1ץ�����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���     
* @param[in]    nEnable    1 ʹ�� 0��ʹ��
* @param[in]    nCoupling    1 ��� 0�����
* @param[in]    nOutputType    �������  1OC�����أ�  0��������ƽ��
* @param[in]    nPolarity    1 ������ 0������
* @param[in]    nPulseWidth    ���� 0~100
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetF1TriggerOut(HVAPI_HANDLE_EX hHandle, INT nEnable, INT  nCoupling, INT  nOutputType, INT  nPolarity, INT  nPulseWidth );


/**
* @brief                ��ȡF1ץ�����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���   
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetF1TriggerOut(HVAPI_HANDLE_EX hHandle, INT* pnEnable, INT*  pnCoupling, INT*  pnOutputType, INT*  pnPolarity, INT*  pnPulseWidth );


/**
* @brief                ����ALM��ץ�����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���   
* @param[in]    nEnable    1 ʹ�� 0��ʹ��
* @param[in]    nCoupling    1 ��� 0�����
* @param[in]    nOutputType    �������  1OC�����أ�  0��������ƽ��
* @param[in]    nPolarity    1 ������ 0������
* @param[in]    nPulseWidth    ���� 0~100
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_SetAlarmTriggerOut(HVAPI_HANDLE_EX hHandle, INT nEnable, INT  nCoupling, INT  nOutputType, INT  nPolarity, INT  nPulseWidth );


/**
* @brief                ��ȡALM��ץ�����
* @param[in]    hHandle                 ��Ӧ�豸����Ч���   
* @return               �ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetAlarmTriggerOut(HVAPI_HANDLE_EX hHandle, INT* pnEnable, INT*  pnCoupling, INT*  pnOutputType, INT*  pnPolarity, INT*  pnPulseWidth );

/**
* @brief		����ץ�Ĳ����Զ�����ʹ��
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[in]	nEnable			����,��Χ��0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetCaptureAutoParamEnable(HVAPI_HANDLE_EX hHandle, INT nEnable );

/**
* @brief		��ȡץ�Ĳ����Զ�����ʹ��
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[out]	nEnable			����,��Χ��0���رգ�1����
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetCaptureAutoParamEnable(HVAPI_HANDLE_EX hHandle, INT* pnEnable );

/**
* @brief		����������װ
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_TriggerAssistantInstallation(HVAPI_HANDLE_EX hHandle );

/**
* @brief		��ȡ������װ״̬
* @param[in]	hHandle			��Ӧ�豸����Ч���
* @param[out]	pnValue		״̬,��Χ��0��100�� 0δ��ʼ  100���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_GetAssistantInstallationStatus(HVAPI_HANDLE_EX hHandle, INT* pnValue );

/**
* @brief		����IP��Ϣ
* @param[in]	hHandle	      ��Ӧ�豸����Ч���
* @param[in]	nEthNO		  ������   0��ʾ�޸�eth0����
* @param[in]	szIP		  IP�ַ���
* @param[in]	szMask		  ���������ַ���
* @param[in]	szGateWay	  �����ַ���
* @param[in]	szDNS		  DNS�ַ���
* @return		�ɹ���S_OK��ʧ�ܣ�E_FAIL  ��������쳣��S_FALSE
*/
HV_API_EX HRESULT CDECL HVAPI_SetIPInfoEx(HVAPI_HANDLE_EX hHandle, 
										INT  nEthNO,
										CHAR* szIP,
										CHAR* szMask,
										CHAR* szGateWay,
										CHAR* szDNS   );

/**
* @brief		    ��ȡ�豸��IP��ַ/����/����
* @param[in]		hHandle			��Ӧ�豸��������Ч���
* @param[out]		pnEthNO			������
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
HV_API_EX HRESULT CDECL HVAPI_GetIPInfoEx(HVAPI_HANDLE_EX hHandle, 
										  INT  nEthNO,
										  CHAR* szIP,
										  INT*szIPLen,
										  CHAR* szMask ,
										  INT*szMaskLen ,
										  CHAR* szGateWay,
										  INT*szGateWayLen,
										  CHAR* szMac,
										  INT*szMacLen  );


/**
* @brief			��ʼ�ָ����ݿ�
* @param[in]		hHandle		��Ӧ�豸��������Ч���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_StartHddRecorverDb(HVAPI_HANDLE_EX hHandle);

/**
* @brief			ֹͣ�ָ����ݿ�
* @param[in]		hHandle		��Ӧ�豸��������Ч���
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_StopHddRecorverDb(HVAPI_HANDLE_EX hHandle);

/**
* @brief			������ݿ�ָ�ʱ�Ѿ�ɨ���Ӳ�̴�С
* @param[in]		hHandle		��Ӧ�豸��������Ч���
* @param[out]		pnHddSize	�Ѿ�ɨ���Ӳ�̴�С����λGB��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API_EX HRESULT CDECL HVAPI_GetHddRecorverDbSize(HVAPI_HANDLE_EX hHandle, INT* pnHddSize);
#endif
