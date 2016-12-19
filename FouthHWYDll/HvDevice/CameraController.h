// ���ļ����������WINDOWS-936��ʽ
/**
 * @file   CameraController.h
 * @author Lijj
 * @date   Wed Feb 29 2012
 *
 * @brief
 *         ������ܽӿ��࣬�������������صĺ������ڴ���ʵ��(���������桢����)��
 *         ���ļ�����ȫ�ֶ���g_cCameraController��ʹ��ʱ��������ļ���
 *
 */

#ifndef _CAMERACONTROL_H_
#define _CAMERACONTROL_H_

#ifndef WIN32

#include "hvutils.h"
#include "TcpipCfg.h"
#include "AgcAwbThread.h"

// frome HvPciLinkApi.h
// ��̬���ĵĲ�������
typedef enum _DCP_TYPE
{
    DCP_SEND_TYPE = 0,
    DCP_CAM_OUTPUT,
    DCP_ENABLE_AGC,
    DCP_ENABLE_AWB,
    DCP_AGC_TH,
    DCP_SHUTTER,
    DCP_GAIN,
    DCP_JPEG_EXPECT_SIZE,
    DCP_JPEG_COMPRESS_RATE,
    DCP_JPEG_COMPRESS_RATE_CAPTURE,
    DCP_FLASH_RATE_SYN_SIGNAL_ENABLE,
    DCP_CAPTURE_SYN_SIGNAL_ENABLE,
    DCP_CPL,
    DCP_SETPULSEWIDTH
} DCP_TYPE;

#endif

// -------------------------------------------------------------

struct FpgaRegInfo_500w
{
    DWORD32 reg_video_SHT1;
    DWORD32 reg_capture_SHT2;
    DWORD32 reg_LED_FLASH_OUT_EN;
    DWORD32 reg_capture_mode;
    DWORD32 reg_ACSP;
    DWORD32 reg_soft_capture_trig;
    DWORD32 anti_flicker;
    DWORD32 Th_Custom_ab;
    DWORD32 Th_Count_ab;
    DWORD32 reg_fpga_version;
    DWORD32 reg_capture_edge_select;
    DWORD32 Gamma_Data_ab[8];
    DWORD32 time_cnt_out;
    DWORD32 pxga_addr_r_ab;
    DWORD32 pxga_addr_gr_ab;
    DWORD32 pxga_addr_gb_ab;
    DWORD32 pxga_addr_b_ab;

    DWORD32 data_b_Gr;
    DWORD32 data_k_Gr;
    DWORD32 data_b_Gb;
    DWORD32 data_k_Gb;
    DWORD32 data_b_R;
    DWORD32 data_k_R;
    DWORD32 data_b_B;
    DWORD32 data_k_B;

    DWORD32 time_clock_out;
    DWORD32 sampling_point_ab;
};

typedef struct _FpgaRegInfo
{
#ifdef _CAMERA_PIXEL_500W_
    struct FpgaRegInfo_500w cFpgaRegInfoA;
    struct FpgaRegInfo_500w cFpgaRegInfoB;
#else
    DWORD32 reg_video_SHT1;
    DWORD32 reg_capture_SHT2;
    DWORD32 reg_LED_FLASH_OUT_EN;
    DWORD32 reg_capture_mode;
    DWORD32 reg_ACSP;
    DWORD32 reg_soft_capture_trig;
    DWORD32 anti_flicker;
    DWORD32 Th_Custom;
    DWORD32 Th_Count;
    DWORD32 reg_fpga_version;
    DWORD32 reg_capture_edge_select;
    DWORD32 Gamma_Data[8];
    DWORD32 time_cnt_out;
    DWORD32 time_clock_out;
    DWORD32 sampling_point;
    DWORD32 capture_ID;

    // ��ƼӺ������Ϣ
    DWORD32 th_h_prt;
    DWORD32 th_l_prt;
    DWORD32 th_s_prt;
    DWORD32 colr_prt;
    DWORD32 th_l_reg_new;
    DWORD32 colr_reg_new_l;
    DWORD32 colr_reg_new_h;

    // ��
    DWORD32 sha_th_o;       // �񻯷�ֵ
    DWORD32 sha_ce_o;       // ��ʹ�ܿ���
    DWORD32 sha_s_or_a_o;   // ��ץ��֡��־

    // ���Ͷ�r/g/b����ֵ
    DWORD32 satu_r_f_max_o;
    DWORD32 satu_r_f_min_o;
    DWORD32 satu_g_f_max_o;
    DWORD32 satu_g_f_min_o;
    DWORD32 satu_b_f_max_o;
    DWORD32 satu_b_f_min_o;

    // �Աȶȳ˷�/�ӷ�����
    DWORD32 cont_rgb_f_o;
    DWORD32 cont_add_f_o;
#endif // _CAMERA_PIXEL_500W_
} FpgaRegInfo;

struct AgcAwbInfo_500w
{
    DWORD32 SumR_ab;
    DWORD32 SumG_ab;
    DWORD32 SumB_ab;
    DWORD32 SumY_ab;
    DWORD32 SumU_ab;
    DWORD32 SumV_ab;
    DWORD32 PointCount_ab;
    DWORD32 AvgY_ab[16];

    DWORD32 SUM_Gr_raw_Low_ab;
    DWORD32 SUM_Gr_raw_High_ab;
    DWORD32 SUM_Gb_raw_Low_ab;
    DWORD32 SUM_Gb_raw_High_ab;
    DWORD32 SUM_R_raw_Low_ab;
    DWORD32 SUM_R_raw_High_ab;
    DWORD32 SUM_B_raw_Low_ab;
    DWORD32 SUM_B_raw_High_ab;

    DWORD32 reg_gr_ab;
    DWORD32 reg_gb_ab;
    DWORD32 reg_r_ab;
    DWORD32 reg_b_ab;

    DWORD32 th_h_reg;
    DWORD32 th_l_reg;
    DWORD32 th_s_reg;
    DWORD32 colr_reg;
    DWORD32 addr_prt;
    DWORD32 cod_x_min_in;
    DWORD32 cod_x_max_in;
    DWORD32 cod_y_min_in;
    DWORD32 cod_y_max_in;
};

typedef struct _AgcAwbInfo
{
#ifdef _CAMERA_PIXEL_500W_
    struct AgcAwbInfo_500w cAgcAwbInfoA;
    struct AgcAwbInfo_500w cAgcAwbInfoB;
#else
    DWORD32 SumR;
    DWORD32 SumG;
    DWORD32 SumB;
    DWORD32 SumY;
    DWORD32 SumU;
    DWORD32 SumV;
    DWORD32 PointCount;
    DWORD32 AvgY[16];
#endif
} AgcAwbInfo;

// -------------------------------------------------------------
#ifndef WIN32

// ���������صĽӿ�
class ICameraUtils
{
public:
#ifdef _CAM_APP_
    // ��ȡ����ģʽ
    virtual int GetEncodeMode() = 0;
#endif
    // ����AGC����
    virtual int SetAGCZone(int rgiAGCZone[16]) = 0;
    // ��ȡAGC����
    virtual int GetAGCZone(int *prgiAGCZone) = 0;
    // ����AGC����
    virtual int SetAGCParam(int iShutterMin, int iShutterMax, int iGainMin, int iGainMax) = 0;
    // ���浱ǰ����
    virtual HRESULT SaveCurrentParam() = 0;
    // ��̬�ı����
    virtual HRESULT DynChangeParam(DCP_TYPE eType, int iValue, bool fFromPCI = false) = 0;
};

// �ַ����ӽӿ�
class ICharacterOverlap
{
public:
    virtual HRESULT EnableCharacterOverlap(int iValue) = 0;
    virtual HRESULT SetCharacterOverlap(char* pLattice) = 0;
    virtual HRESULT SaveCharacterInfo(void) = 0;
    virtual HRESULT SetCharacterLightness(int iIsFixedLight) = 0;
};

class CCameraController
{
public:
    CCameraController();
    ~CCameraController();

    int SetRgbGain(int iGainR, int iGainG, int iGainB);
    int SetGain(int iGain);
    int SetShutter(int iShutter);
    int SetCaptureRgbGain(int iGainR, int iGainG, int iGainB, int fEnable);
    int SetCaptureGain(int iGain, int fEnable);
    int SetCaptureShutter(int iShutter, int fEnable);
    int SetFpsMode(int iMode, BOOL fResetH264 = FALSE);
    int GetFpsMode(int& iMode);
    int SynSignalEnable(int iFlashRateEnable, int iCaptureEnable);
    int CaptureEdgeSelect(int iMode);
    int SoftTriggerCapture();
    int SetGammaData(int rgiDataXY[8][2]);
    int FpgaTimeRegClr();
    int SetRegDirect(DWORD32 addr, DWORD32 data);
    int SetTrafficLightEnhanceParam(int iHTh, int iLTh, int iSTh, int iColorFactor);
    int SetControlBoardIOOpt(int fEnable);
    // iLTh ������ֵ
    // iLFactor ���ȳ˷�����
    // iHFactor H�źų˷�����
    int SetTrafficLightEnhanceLumParam(int iLTh, int iLFactor, int iHFactor);
    // SetTrafficLightEnhanceZone˵����
    // iIdΪ��ƼӺ�����IDֵ���Ϸ�ֵΪ0��7(ע����ֵ��ʾ��ƼӺ��������A67�汾FPGA�Ѽ���Ϊ8��)
    // ��Windows��Ļ����ϵ�£�������Ļ���Ͻ�Ϊԭ�㣩��
    // ��iX1��iY1��ΪͼƬ�мӺ���������Ͻ�����㡣
    // ��iX2��iY2��ΪͼƬ�мӺ���������½�����㡣
    int SetTrafficLightEnhanceZone(int iId, int iX1, int iY1, int iX2, int iY2);

    //////////////////////////////
    int SetADSamplingValue(int iValueA, int iValueB);
    int SublaneCapture(int iPsdVersion);
    int FlashDifferentLane(int fEnalbe);
    int FlashDifferentLaneExt(int fEnalbe); // Ӳ����ץ�ķֳ���
    int SlaveSoftTriggerCapture();

    /*---------- A65�����ϰ汾֧�� BEGIN----------*/
    int ResetFpga();    // ��λFPGA
    int SetSmallShutterRaw(int iShutter);   // С����
    int SetOrgRgbGainToZero();      // ��ԭRGB����Ĵ�������Ϊ0
    /*---------- A65�����ϰ汾֧�� END----------*/

    //----------------A67 ��ʼ
    int EnableSharpen(int fEnable);
    int SetSharpenThreshold(int iThreshold);
    int SetSharpenCapture(int fEnable);
    int SetContrast(int nValue);
    int SetSaturation(int nValue);
    int SetRawRGBGain(int iRawR, int iRawGr, int iRawGb, int iRawB);
    //----------------A67 ����

    //----------------A68 ��ʼ
    int SetGammaOutputMode(int iMode);
    //----------------A68 ����

    //----------------A70 ��ʼ
    int SetSaturationMode(int iMode);
    int SetContrastMode(int iMode);
    int SetDpcThreshold(int iValue);
    //----------------A70 ����

    // ���ܺ�������������Ŀ��ţ����棬��ɫ�����Լ�ץ�Ŀ��ţ�ץ�������ץ����ɫ���档
    int SetShutter_Camyu(int iShutter);
    int GetShutter_Camyu(int& iShutter);
    int SetGain_Camyu(int iGain);
    int GetGain_Camyu(int& iGain);
    int SetRgbGain_Camyu(int iGainR, int iGainG, int iGainB);
    int GetRgbGain_Camyu(int& iGainR, int& iGainG, int& iGainB);
    int SetCaptureShutter_Camyu(int iShutter, int fEnable);
    int GetCaptureShutter_Camyu(int& iShutter, int& fEnable);
    int SetCaptureGain_Camyu(int iGain, int fEnable);
    int GetCaptureGain_Camyu(int& iGain, int& fEnable);
    int SetCaptureRgbGain_Camyu(int iGainR, int iGainG, int iGainB, int fEnable);
    int GetCaptureRgbGain_Camyu(int& iGainR, int& iGainG, int& iGainB, int& fEnable);

    // ���ߺ����������λת��
    int Shutter_Raw2Camyu(int iRawValue);
    int Shutter_Camyu2Raw(int iCamyuValue);
    int Gain_Raw2Camyu(int iRawValue);
    int Gain_Camyu2Raw(int iCamyuValue);
    int ColorGain_Raw2Camyu(int iRawValue);
    int ColorGain_Camyu2Raw(int iCamyuValue);
    int SmallShutter_Raw2Camyu(int iRawValue);
    int SmallShutter_Camyu2Raw(int iCamyuValue);

    // ��ȡFPGAǶ����ͼ�������е�����ֵ
    HRESULT GetExtInfoByImage(
        const PBYTE8 pbImageDataY,
        FpgaRegInfo& cFpgaRegInfo,
        AgcAwbInfo& cAgcAwbInfo
    );

    void MountCameraUtils(ICameraUtils* pCameraUtils)
    {
        m_pCameraUtils = pCameraUtils;
    }

    void MoutCharacterUtils(ICharacterOverlap* pCharacterUtils)
    {
        m_pCharacterUtils = pCharacterUtils;
    }

    int GetEncodeMode()
    {
#ifdef _CAM_APP_
        return m_pCameraUtils->GetEncodeMode();
#else
        return -1;
#endif
    }
    // ����AGC����
    int SetAGCZone(int rgiAGCZone[16])
    {
        return m_pCameraUtils->SetAGCZone(rgiAGCZone);
    }
    // ��ȡAGC����
    int GetAGCZone(int *prgiAGCZone)
    {
        return m_pCameraUtils->GetAGCZone(prgiAGCZone);
    }

    // ����AGC����
    int SetAGCParam(int iShutterMin, int iShutterMax, int iGainMin, int iGainMax)
    {
        return m_pCameraUtils->SetAGCParam(iShutterMin, iShutterMax, iGainMin, iGainMax);
    }
    // ���浱ǰ����
    HRESULT SaveCurrentParam()
    {
        return m_pCameraUtils->SaveCurrentParam();
    }
    // ��̬�ı����
    HRESULT DynChangeParam(DCP_TYPE eType, int iValue)
    {
        return m_pCameraUtils->DynChangeParam(eType, iValue);
    }

    // �ַ�����
    HRESULT EnableCharacterOverlap(int iValue)
    {
         return m_pCharacterUtils->EnableCharacterOverlap(iValue);
    }
    HRESULT SetCharacterOverlap(char* pLattice)
    {
        return m_pCharacterUtils->SetCharacterOverlap(pLattice);
    }
    HRESULT SaveCharacterInfo(void)
    {
        return m_pCharacterUtils->SaveCharacterInfo();
    }
    HRESULT SetCharacterLightness(int iIsFixedLight)
    {
        return m_pCharacterUtils->SetCharacterLightness(iIsFixedLight);
    }

private:
    int WriteAD(FPGA_STRUCT datas);
    void SetFpgaStructContext(FPGA_STRUCT& cFpgaStruct, DWORD32 dwAddr, DWORD32 dwData);

private:
    HV_SEM_HANDLE m_hSemSwDev;  //AD��FPGAоƬ�����̰߳�ȫ��
    int m_rgiNowGammaDataXY[8][2];
    ICameraUtils* m_pCameraUtils;   //��������ӿ�
    ICharacterOverlap* m_pCharacterUtils;   // �ַ����ӽӿ�
};

extern CCameraController g_cCameraController;

/**
* @brief �豸�����ṹ��
*/
typedef struct _DeviceInfoParam
{
    char szMac[32];
    char szSn[128];
    char szVer[64];

    _DeviceInfoParam()
    {
        char szIpTmp[32] = {0};
        char szMaskTmp[32] = {0};
        char szGatewayTmp[32] = {0};
        GetLocalTcpipAddr("eth0", szIpTmp, szMaskTmp, szGatewayTmp, szMac);

        GetSN(szSn, sizeof(szSn));

        sprintf(szVer, "%s %s %s",
                PSZ_DSP_BUILD_NO,
                DSP_BUILD_DATE,
                DSP_BUILD_TIME
               );
    };

} DeviceInfoParam;

//���ƽ̨ģ������ṹ��
//ע����Ϊ�˽ṹ��ʹ����ǰ�������������������Ҫ�ŵ��������
typedef struct _CamAppParam
{
    int iSendType;          /**< ����ģʽ��-1�������䣻0�����䡣 */
    int iJpegStream;        /**< �Ƿ���Jpeg����0:��1���ǡ� */
    int iH264Stream;        /**< �Ƿ���H.264����0:��1���ǡ� */

    int iIFrameInterval;    /**< H.264�����е�I֡��� */
    int iTargetBitRate;     /**< H.264���������� */
    int iFrameRate;         /**< H.264����֡�� */

    int iAGCTh;             /**< AGC�������� */
    int iAGCShutterLOri;    /**< AGC���ŵ������� */
    int iAGCShutterHOri;    /**< AGC���ŵ������� */
    int iAGCGainLOri;       /**< AGC����������� */
    int iAGCGainHOri;       /**< AGC����������� */

    int iGainR;             /**< R���� */
    int iGainG;             /**< G���� */
    int iGainB;             /**< B���� */
    int iGain;              /**< ������� */
    int iShutter;           /**< ����ʱ�� */

    int iCaptureGainR;      /**< ץ��R���� */
    int iCaptureGainG;      /**< ץ��G���� */
    int iCaptureGainB;      /**< ץ��B���� */
    int iCaptureGain;       /**< ץ��������� */
    int iCaptureShutter;    /**< ץ�Ŀ���ʱ�� */

    int iEnableCaptureGainRGB;          /**< ʹ��ץ��RGB��ɫ���� */
    int iEnableCaptureGain;             /**< ʹ��ץ������ */
    int iEnableCaptureShutter;          /**< ʹ��ץ�Ŀ��� */

    int iJpegCompressRate;              /**< Jpegѹ���� */
    int iJpegCompressRateCapture;       /**< ץ��Jpegͼѹ���� */

    BOOL fIsSafeSaver;                  /**< �Ƿ�������ȫ�洢 */
    BOOL fSaveVideo;                    /**< �Ƿ�����¼��洢 */
    BOOL fInitHdd;                      /**< �Ƿ��ʼ��Ӳ�� */
    int  iFileSize;                     /**< �����洢�е����ļ��Ĵ�С*/
    char szNFSParam[255];               /**< NFSЭ��Ĺ��ز���*/
    char szSafeSaverInitStr[64];        /**< ��ȫ��������ʼ������ */

    BOOL fIsSideInstall;                /**< ǰ�˾�ͷ�Ƿ�Ϊ��װ */
    int iJpegExpectSize;                /**< JpegͼƬ������С����λ��Byte����ͨ���Զ�����Jpegѹ����ʵ�� */
    int iJpegCompressRateL;             /**< Jpegѹ�����Զ��������� */
    int iJpegCompressRateH;             /**< Jpegѹ�����Զ��������� */

    int iJpegType;                      /**< JpegͼƬ��ʽ */
    int iOutputFrameRate;               /**< ������֡�� */

    int iAGCEnable;                     /**< AGCʹ�� */
    int iAWBEnable;                     /**< AWBʹ�� */
    int iFlashRateSynSignalEnable;      /**< Ƶ��ͬ���ź�ʹ�� */
    int iCaptureSynSignalEnable;        /**< ץ��ͬ���ź�ʹ�� */
    int iENetSyn;                       /**< ����ͬ�� 0:15fps 1:12.5fps */
    int iCaptureEdge;                   /**< ץ�Ĵ����� 0:�ⲿ�½��ش��� 1:�ⲿ�����ش��� 2: �������½��ض����� 3�������� */
    int iFlashDifferentLane;            /**< ����Ʒֳ����� 0:���ֳ��� 1: �ֳ��� */
    int iFlashDifferentLaneExt;         /**< ����Ʒֳ�����(Ӳ����) 0:���ֳ��� 1: �ֳ��� */

    char szNetDiskIP[32];               /**< ����洢��IP��ַ */
    char szFtpRoot[32];                 /**< ����洢��FTP��·�� */
    char szNetDiskUser[32];             /**< ����洢���û����� */
    char szNetDiskPwd[32];		        /**< ����洢���û����� */
    int  iNetDiskSpace;   				/**< ����洢������,��λG */
    int  iDiskType;				        /**< ����Ӳ������ */
    char szNFS[32];                     /**< ����Ӳ��NFS·�� */
    int  iAvgY;                         /**< ����������ֵ*/
    int  rgiDefGamma[8][2];             /**< Ĭ��Gamaֵ*/
    int  rgiGamma[8][2];
    int  iSaveSafeType;                 /**< ��̬Ӳ�̴洢��ʽ 0:û�пͻ�������ʱ�Ŵ洢 1:һֱ�洢 */

    int iX;                             /**< �ַ���X���� */
    int iY;                             /**< �ַ���y���� */
    int iFontSize;                      /**< �����С(ע���˴�СΪ��������������Ϊ24*24�������ֵΪ24) */
    int iDateFormat;                    /**< ���ڸ�ʽ */
    int iFontColor;                     /**< ������ɫ(RGB) */
    int iLatticeLen;                    /**< ���󳤶� */
    char* pbLattice;                    /**< ���󻺳���*/
    int iEnableCharacterOverlap;        /**< �ַ�����ʹ�� */
    int iEnableFixedLight;              /**< ������ɫ�Ƿ�̶����� */

    int iEnableAutoCapture;
    int iShutterCloudy;
    int iGainCloudy;
    int iShutterDay;
    int iGainDay;
    int iShutterBLight;
    int iGainBLight;
    int iShutterFLight;
    int iGainFLight;
    int iShutterNeight;
    int iGainNeight;

    // A67
    int iEnableSharpen;                 /**< ʹ���񻯿��� 0: ��ʹ��  1��ʹ�� */
    int iSharpenThreshold;              /**< �񻯷�ֵ[0~100] */
    int iSharpenCapture;                /**< ��ץ��ͼ��1����ץ��ͼ 0��������ͼ��*/
    int iContrastValue;                 /**< �Աȶ�ֵ[-100~100] */
    int iSaturationValue;               /**< ���Ͷ�ֵ[-100~100] */

    int iAWBRawRGain;
    int iAWBRawGbGain;
    int iAWBRawGrGain;
    int iAWBRawBGain;
    // A67

    BOOL fEnableH264BrightnessAdjust;
    int iAdjustPointX;
    int iAdjustPointY;

    _CamAppParam()
    {
        iSendType = 0;
        iJpegStream = 1;
        iH264Stream = 0;

        iIFrameInterval = 10;
        iTargetBitRate = 6*1024*1024;
        iFrameRate = 12;

        iAGCTh = 100;
        iAGCShutterLOri = 100;
        iAGCShutterHOri = 4200;
        iAGCGainLOri = g_cCameraController.Gain_Raw2Camyu(GAIN_BASELINE) + 10;
        iAGCGainHOri = 220;

        iGainR = 0;
        iGainG = 0;
        iGainB = 0;
        iGain = iAGCGainLOri;
        iShutter = 2000;

        iCaptureGainR = 0;
        iCaptureGainG = 0;
        iCaptureGainB = 0;
        iCaptureGain = iAGCGainLOri;
        iCaptureShutter = 2000;

        iEnableCaptureGainRGB = 0;
        iEnableCaptureGain = 0;
        iEnableCaptureShutter = 0;

        iJpegCompressRate = 60;
        iJpegCompressRateCapture = 80;

        fIsSafeSaver = FALSE;
        fSaveVideo = FALSE;
        fInitHdd = FALSE;
        iFileSize = 512;
        strcpy(szNFSParam, "-o timeo=1,soft,tcp,nolock,retry=1");
        memset(szSafeSaverInitStr, 0, sizeof(szSafeSaverInitStr));

        fIsSideInstall = FALSE;
        iJpegExpectSize = 0;
        iJpegCompressRateL = 30;
        iJpegCompressRateH = 90;

        iOutputFrameRate = 15;
        iJpegType = 0;
        iAGCEnable = 0;
        iAWBEnable = 1;
        iFlashRateSynSignalEnable = 1;
        iCaptureSynSignalEnable = 1;
        iENetSyn = 0;
        iCaptureEdge = 0;
        iFlashDifferentLane = 0;
        iFlashDifferentLaneExt = 0;

        strcpy(szNetDiskIP, "172.18.10.10");
        strcpy(szFtpRoot, "/array1");
        strcpy(szNetDiskUser, "No User");
        strcpy(szNetDiskPwd, "123");
        strcpy(szNFS, "/volume1/nfs");
        iNetDiskSpace = 1;
        iDiskType = 0;
        iSaveSafeType = 0;

        iAvgY = 30;
        rgiGamma[0][0] = 32;
        rgiGamma[0][1] = 32;

        rgiGamma[1][0] = 64;
        rgiGamma[1][1] = 64;

        rgiGamma[2][0] = 96;
        rgiGamma[2][1] = 96;

        rgiGamma[3][0] = 128;
        rgiGamma[3][1] = 128;

        rgiGamma[4][0] = 160;
        rgiGamma[4][1] = 160;

        rgiGamma[5][0] = 192;
        rgiGamma[5][1] = 192;

        rgiGamma[6][0] = 222;
        rgiGamma[6][1] = 222;

        rgiGamma[7][0] = 255;
        rgiGamma[7][1] = 255;

        memcpy(rgiDefGamma, rgiGamma, 64);

        iX = 0;
        iY = 0;
        iFontSize = 24;             // ע��Ĭ����24����
        iDateFormat = 0;
        iFontColor = 0x00ff0000;    // ע����ʱ��Ĭ��ֵ��Ϊ��ɫ(0x00ff0000)
        iLatticeLen = 0;
        pbLattice = NULL;
        iEnableCharacterOverlap = 0;
        iEnableFixedLight = 0;      // ע��Ĭ������������泡�����ȶ��ı�

        iEnableAutoCapture = 0;
        iShutterCloudy = 600;
        iGainCloudy = 140;
        iShutterDay = 400;
        iGainDay = 110;
        iShutterBLight = 500;
        iGainBLight = 140;
        iShutterFLight = 400;
        iGainFLight = 110;
        iShutterNeight = 800;
        iGainNeight = 160;

        iEnableSharpen = 0;
        iSharpenThreshold = 7;
        iSharpenCapture = 1;
        iContrastValue = 0;
        iSaturationValue = 0;

        iAWBRawRGain = 16384;
        iAWBRawGbGain = 16384;
        iAWBRawGrGain = 16384;
        iAWBRawBGain = 16384;

        fEnableH264BrightnessAdjust = FALSE;
        iAdjustPointX = 10;
        iAdjustPointY = 25;
    };

} CamAppParam;

#endif // WIN32

#endif // _CAMERACONTROL_H_
