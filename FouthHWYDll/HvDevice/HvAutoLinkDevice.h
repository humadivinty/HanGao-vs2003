#ifndef _HV_AUTOLINK_DEVICE_H_
#define _HV_AUTOLINK_DEVICE_H_

/* �������Ӽ������� */
#define	LISTEN_TYPE_RECORD  0x00000001  /**< ������� */
#define LISTEN_TYPE_VEDIO   0x00000002  /**< ��Ƶ���� */
#define LISTEN_TYPE_IMAGE   0x00000003  /**< ͼ������ */
#define LISTEN_TYPE_CMD     0x00000004  /**< �������� */


/**
* @brief			�����������ӷ����� ���ģ��
* @param[in]		nMaxMonitorCount ������� 
* @param[in]		szApiVer		 ��Ӧ�豸��API�汾��ע��ΪNULL��Ĭ��HVAPI_API_VERSION
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/

HV_API HRESULT CDECL HVAPI_LoadMonitor(INT nMaxMonitorCount, LPCSTR szApiVer);

/**
* @brief			��ָ������ ���������
* @param[in]		wPort			��ض˿�
* @param[in]		nType			����������ͣ��������Ƶ��ͼ�����
* @param[in]		szApiVer		��Ӧ�豸��API�汾��ע��ΪNULL��Ĭ��HVAPI_API_VERSION
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPI_OpenServer(INT nPort , INT nType, LPCSTR szApiVer);

/**
* @brief			�ر�ָ������ ���������
* @param[in]		nType			�����������
* @return			�ɹ���S_OK ��ʧ�ܣ�E_FAIL
*/
HV_API HRESULT CDECL HVAPI_CloseServer(INT nType);

/**
* @brief			ж���������ӷ����� ���ģ��
* @return			�ɹ���S_OK��ʧ�ܣ�E_FAIL
*/

HV_API HRESULT CDECL HVAPI_UnLoadMonitor();


/**
* @brief			�������������豸
* @param[in]		nDevListLen		�豸�б�ĳ���
* @param[in]		szApiVer		��Ӧ�豸��API�汾��ע��ΪNULL��Ĭ��HVAPI_API_VERSION
* @return			�ɹ����豸�����ʧ�ܣ�E_FAIL
*/

HV_API HRESULT CDECL HVAPI_GetDeviceListSize(INT& nDevListLen , LPCSTR szApiVer);

/**
* @brief			�������������豸
* @param[in]		szDevList		�����豸�б�Ļ�����
* @param[in]		nDevListLen		����������
* @param[in]		szApiVer		��Ӧ�豸��API�汾��ע��ΪNULL��Ĭ��HVAPI_API_VERSION
* @return			�ɹ����豸�����ʧ�ܣ�E_FAIL
*/

HV_API INT CDECL HVAPI_GetDeviceList(LPSTR szDevList, INT nDevListLen , LPCSTR szApiVer);

/**
* @brief			���豸���
* @param[in]		szDevSN			�豸���
* @param[in]		szApiVer		��Ӧ�豸��API�汾��ע��ΪNULL��Ĭ��HVAPI_API_VERSION
* @return			�ɹ����豸�����ʧ�ܣ�NULL
*/

HV_API HRESULT CDECL HVAPI_GetDeviceStatus(LPSTR szDevSN ,INT& nRecordLinkStatus , INT& nRecordLinkReConCount , LPCSTR szApiVer);


/**
* @brief			���豸���
* @param[in]		pDevName		�豸������
* @param[in]		szApiVer		��Ӧ�豸��API�汾��ע��ΪNULL��Ĭ��HVAPI_API_VERSION
* @return			�ɹ����豸�����ʧ�ܣ�NULL
*/
HV_API HVAPI_HANDLE_EX CDECL HVAPI_OpenAutoLink(LPCSTR szDevName, LPCSTR szApiVer);

/**
* @brief			��ȡ�豸IP���˿ں�
* @param[in]		pDevName		�豸������
* @param[in]		szApiVer		��Ӧ�豸��API�汾��ע��ΪNULL��Ĭ��HVAPI_API_VERSION
* @param[out]		strIP			��Ӧ�豸IP�ַ���
* @param[in]		strLen			��Ӧ�豸IP�ַ�������
* @param[out]		dwPORT			��Ӧ�豸�˿ں�
* @return			�ɹ����豸�����ʧ�ܣ�NULL
*/
HV_API HRESULT CDECL HVAPI_GetDeviceInfoAutoLink(LPCSTR szDevName, LPCSTR szApiVer, LPSTR strIP, INT strLen, INT& dwPORT);








#endif