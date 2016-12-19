// ���ļ������ʽ������WIN936
//	hvCameralink.h
//	�������ݴ���ӿڼ�������ݽṹ
//
//

#ifndef _HVCAMERALINK_H_
#define _HVCAMERALINK_H_

#ifndef WIN32
#include "HvCameraLinkOpt.h"
#include "hvutils.h"
#include "safesaver.h"
#include "swimageobj.h"
#endif

namespace HiVideo
{
#ifndef WIN32
    // ���ݽṹ����

    //���ͼƬ
    typedef struct tag_CameraImage
    {
        DWORD32 dwImageType;
        DWORD32 dwWidth;
        DWORD32 dwHeight;
        DWORD32 dwTimeLow;
        DWORD32 dwTimeHigh;
        DWORD32 dwImageOffset;
        ImageExtInfo cImageExtInfo;
        FpgaExtInfo cFpgaExtInfo;
        DWORD32 dwJpegCompressRate;
        DWORD32 dwY;
        DWORD32 dwImageSize;
        PBYTE8	pbImage;
        IReferenceComponentImage* pRefImage;
        IReferenceMemory* pRefMemory;           // zhaopy �Ӵ������ģ��ʱ�õ�
        tag_CameraImage()
        {
            memset(this, 0, sizeof(*this));
        }
    }
    SEND_CAMERA_IMAGE;

    //H.264
    typedef struct tag_CamVideo
    {
        DWORD32 dwVideoType;
        DWORD32 dwFrameType;
        DWORD32 dwTimeLow;
        DWORD32 dwTimeHigh;
        VideoExtInfo cVideoExtInfo;
        DWORD32 dwY;
        DWORD32 dwWidth;
        DWORD32 dwHeight;
        DWORD32 dwOutputFrameRate;
        DWORD32 dwVideoSize;
        PBYTE8 pbVideo;
        HV_RECT rcRedLight[20];
        float   fltFPS;
        IReferenceComponentImage* pRefImage;
        tag_CamVideo()
        {
            memset(this, 0, sizeof(*this));
        }
    }
    SEND_CAMERA_VIDEO;

    //ʶ����
    typedef struct tag_Record
    {
        int iCurCarId; // ��ǰʶ��������
        DWORD32 dwRecordType;
        PBYTE8 pbXML;
        DWORD32 dwXMLSize;
        PBYTE8 pbRecord;
        DWORD32 dwRecordSize;
        IReferenceMemory* pRefMemory;
    }
    SEND_RECORD;

    // ����
    // ���ͼƬ����
    typedef struct tag_SendImageParam
    {
    }
    SEND_IMAGE_PARAM;

    // ��Ƶ������
    typedef struct tag_SendVideoParam
    {
        //�ɿ��Ա���ģ��
        ISafeSaver* pcSafeSaver;    /**< ��ȫ������ */
        int iSendHisVideoSpace;    /**< ������ʷ¼��ļ�� */

        tag_SendVideoParam()
        {
            pcSafeSaver = NULL;
            iSendHisVideoSpace = 1;
        };
    }
    SEND_VIDEO_PARAM;

    // ʶ�������Ͳ���
    typedef struct tag_SendRecordParam
    {
        //�ɿ��Ա���ģ��
        ISafeSaver* pcSafeSaver;    /**< ��ȫ������ */
		int iOutputOnlyPeccancy;
		int iSendRecordSpace;
		int nDiskType;
        tag_SendRecordParam()
        {
            pcSafeSaver = NULL;
            iOutputOnlyPeccancy = 0;
            iSendRecordSpace = 5;
            nDiskType = 0;
        };
    }
    SEND_RECORD_PARAM;

    //�ӿڶ���

    //ͼƬ����ӿ�
    class ISendCameraImage
    {
    public:
        virtual ~ISendCameraImage() {};
        virtual HRESULT SendCameraImage(const SEND_CAMERA_IMAGE* pImage) = 0;
        virtual HRESULT SetParam(const SEND_IMAGE_PARAM* pParam) = 0;
        virtual HRESULT GetCurStatus(char* pszStatus, int nStatusSizes) = 0;
        virtual HRESULT GetIsCaptureMode(BOOL* fIsCaptureLink) = 0;
    };

    //H.264����ӿ�
    class ISendCameraVideo
    {
    public:
        virtual ~ISendCameraVideo() {};
        virtual HRESULT SendCameraVideo(const SEND_CAMERA_VIDEO* pVideo) = 0;
        virtual HRESULT SetParam(const SEND_VIDEO_PARAM* pParam) = 0;
        virtual HRESULT GetCurStatus(char* pszStatus, int nStatusSizes) = 0;
    };

    //ʶ��������ӿ�
    class ISendRecord
    {
    public:
        virtual ~ISendRecord() {};
        virtual HRESULT SendRecord(const SEND_RECORD* pRecord, DWORD32 dwTimeMsLow, DWORD32 dwTimeMsHigh) = 0;
        virtual HRESULT SetParam(SEND_RECORD_PARAM* pParam) = 0;
        virtual HRESULT GetCurStatus(char* pszStatus, int nStatusSizes) = 0;
    };

    // �����֤�ӿ�
    class ICheckPassword
    {
    public:
        virtual ~ICheckPassword(){};
        virtual HRESULT SendCheckCmd() = 0;
        virtual HRESULT ReceivePassword() = 0;
    };

#else

    // ����������Ϣͷ
    typedef struct tag_head
    {
        DWORD32 dwType;
        DWORD32 dwInfoLen;
        DWORD32 dwDataLen;
    }
    INFO_HEADER;

    // ��������չ��Ϣͷ
    typedef struct tag_block
    {
        DWORD32 dwID;
        DWORD32 dwLen;
    }
    BLOCK_HEADER;

#endif // WIN32

    // ��������

    // �����ͷ
    typedef struct tag_CameraCmdHeader
    {
        DWORD32 dwID;
        DWORD32 dwInfoSize;
    }
    CAMERA_CMD_HEADER;

    // �����Ӧ��
    typedef struct tag_CameraCmdRespond
    {
        DWORD32 dwID;
        DWORD32 dwInfoSize;
        int dwResult;
    }
    CAMERA_CMD_RESPOND;

	//�ַ����ݰ�
	typedef struct tag_CHAR_DATA
	{
		int nTopLeftX;      //�ַ����Ͻ�����Xֵ
		int nTopLeftY;      //�ַ����Ͻ�����Yֵ
		int nSize;        //�ַ���С
		int nDateType;      //ʱ����ʾ����
		int nRGB;            //RGBֵ
	}
	CHAR_DATA;

#ifndef WIN32

    // ��������ӿ�
    class ICameraCmdLink
    {
    public:
        virtual ~ICameraCmdLink(){};

        virtual HRESULT ReceiveHeader(CAMERA_CMD_HEADER* pCmdHeader) = 0;
        virtual HRESULT SendRespond(const CAMERA_CMD_RESPOND* pCmdRespond) = 0;
        virtual HRESULT ReceiveData(PBYTE8 pbData, const DWORD32& dwSize, DWORD32* pdwRecvSize) = 0;
        virtual HRESULT SendData(PBYTE8 pbData, const DWORD32& dwSize) = 0;
    };

    // �����ӿ�
    class ICameraCmdProcess
    {
    public:
        virtual ~ICameraCmdProcess(){};
        virtual HRESULT Process( CAMERA_CMD_HEADER* pCmdHeader, ICameraCmdLink* pCmdLink ) = 0;
    };

#endif // WIN32
}

#endif
