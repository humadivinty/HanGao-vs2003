// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� FOUTHHWYDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// FOUTHHWYDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef FOUTHHWYDLL_EXPORTS
#define FOUTHHWYDLL_API __declspec(dllexport)
#else
#define FOUTHHWYDLL_API __declspec(dllimport)
#endif


typedef int (_stdcall  *CallbackNETStatusFuc  )(char* pszIP);

// ����2.1�����߳���ʶ�����ӿڱ�׼�淶��

// ����ʶ�𳧼���Ҫ���������˵������װһ����̬���ӿ⣬����Ϊ��FouthHWYDll.dll��������BINĿ¼�ڼ��ɲ��ԡ�

// 1���ṩ����ʶ���豸��IP��ַ���˿ںţ���ʱʱ�䣨��ָ��ʱ���ڣ�û�л�ȡ���ƣ��ͻ������ƣ�

// 2�������ο����������Ķ��壬���£�

/* 
(1)�����ü����������Ķ˿ں�

���������룬UINT nPort 
˵�����������˿ںţ���ΧΪ��1000��65535��֮�䡣
�޷���ֵ
 */
FOUTHHWYDLL_API void  __stdcall SetServerPort(UINT nPort);

/*
(2)����������
 
�޲���
����ֵ��true ���ɷ�������ˣ�
        false�������ɷ��������
*/
FOUTHHWYDLL_API  BOOL  __stdcall StartServer();

/* 
(3)��ģ�ⴥ����������ʶ���豸����ģ�ⴥ��ָ�ץ�ĳ�����Ϣ

���������룬char  *chIP
����ֵ��true ģ�ⴥ���ɹ�;
        false ģ�ⴥ��ʧ�� 
*/
FOUTHHWYDLL_API BOOL __stdcall Trigger (char  *chIP);

/* 
(4)�������쳣�Ͽ���ʾ
ע�������쳣�ص�����
    
������NETStatusFuc
˵������������Ҫ�ڹ����������������͵Ļص�����
      VB��
      void (CALLBACK  * CallbackNETStatusFuc)( _bstr_t  strIP)
      PB��VC�еĻص�����
      void (CALLBACK  * CallbackNETStatusFuc)( char  *chIP)
      �ص�������ڲ���˵����strIP��chIP���豸IP������ʾĳ���豸��������쳣
 */
FOUTHHWYDLL_API void __stdcall RegisterNETStatusEvent(CallbackNETStatusFuc NETFuc);

/*
(5)��ֹͣ������

�޲���
����ֵ��true�ɹ���false ʧ�� 
*/
FOUTHHWYDLL_API BOOL __stdcall StopServer();

/* 
(6)���õ�ʶ����

������lpPlate    �����������ɫ�ĳ����գ���ʽΪ����ɫ���ơ������磺����A1234��
������lpTwoImg   �����280�ֽڵĳ����ն�ֵ��ͼƬ
������strIP      ���룬����ʶ���豸��IP��ַ
������nDelayTime ���룬��ʱʱ�䣬������ʱ�䣬���û�л�ȡ���ƣ�ֱ�ӷ������ƣ���lpPlateΪ�ջ�������ֵΪfalse
����ֵ��true��ȡ���Ƴɹ���false��ȡ����ʧ��
 */
FOUTHHWYDLL_API BOOL __stdcall GetPlateInfo(char* lpPlate,unsigned char* lpTwoImg,char* strIP, int nDelayTime);

       




// ���������ǣ�

// (1)��ע��ص�����       RegisterNETStatusEvent(CallbackNETStatusFuc NETFuc) 
// (2)������һЩ���ú���   SetServerPort,StartServer
// (3)������ģ�ⴥ��       Trigger
// (4)����ʼ��ȡ���       GetPlateInfo
// (5)���˳�               StopServer


// ���Թ��ߵ�ʹ�ã�

// 1�����ú�AutoVehPlate.ini�е�IP���˿ڣ���ʱ�ȴ�ʱ��

// 2���򿪲��Թ���

// 3����ʼ��

// 4����ȡʶ�����������ʾ��WP������ʾ���ƣ����ȡ����ʧ�ܡ�
