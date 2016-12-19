// TesTool_FouthHWYDllDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TesTool_FouthHWYDll.h"
#include "TesTool_FouthHWYDllDlg.h"
#include ".\testool_fouthhwydlldlg.h"
#include "FouthHWYDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef DEBUG
#pragma comment(lib, "../Debug/FouthHWYDll.lib")
#else
#pragma comment(lib, "../Release/FouthHWYDll.lib")
#endif

bool ConnectFlag = false;
void* pDlg = NULL;
typedef int (_stdcall  *CallbackNETStatusFuc  )(char* pszIP);
CallbackNETStatusFuc g_function;
int _stdcall StatusFuc(char* chIP)
{
	//GetDlgItem(IDC_STATIC_DeviStatus)->SetWindowText("异常");
	if (ConnectFlag)
	{
		char chDebugString[MAX_PATH] = {0};
		sprintf(chDebugString, "相机 %s 状态异常 \n", chIP);
		OutputDebugStringA(chDebugString);
		if (pDlg)
		{
			CTesTool_FouthHWYDllDlg* pTesTollDlg = (CTesTool_FouthHWYDllDlg*)pDlg;
			pTesTollDlg->GetDlgItem(IDC_STATIC_DeviStatus)->SetWindowText(chDebugString);
		}
	}

	return 0;
};
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTesTool_FouthHWYDllDlg 对话框



CTesTool_FouthHWYDllDlg::CTesTool_FouthHWYDllDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTesTool_FouthHWYDllDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTesTool_FouthHWYDllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTesTool_FouthHWYDllDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_SetServerPort, OnBnClickedButtonSetserverport)
	ON_BN_CLICKED(IDC_BUTTON_StartServer, OnBnClickedButtonStartserver)
	ON_BN_CLICKED(IDC_BUTTON_Regi, OnBnClickedButtonRegi)
	ON_BN_CLICKED(IDC_BUTTON_Trigger, OnBnClickedButtonTrigger)
	ON_BN_CLICKED(IDC_BUTTON_StopServer, OnBnClickedButtonStopserver)
	ON_BN_CLICKED(IDC_BUTTON_GetPlateInfo, OnBnClickedButtonGetplateinfo)
	ON_BN_CLICKED(IDC_BUTTON_Timer, OnBnClickedButtonTimer)
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTesTool_FouthHWYDllDlg 消息处理程序

BOOL CTesTool_FouthHWYDllDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	g_function = StatusFuc;
	pDlg = this;
	m_bTimerEnable = false;

	SetTimer(1, 2000, NULL);
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CTesTool_FouthHWYDllDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTesTool_FouthHWYDllDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CTesTool_FouthHWYDllDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTesTool_FouthHWYDllDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	char FileName[MAX_PATH];
	GetModuleFileNameA(NULL, FileName, MAX_PATH-1);

	PathRemoveFileSpecA(FileName);
	char iniFileName[MAX_PATH] = {0};
	char iniDeviceInfoName[MAX_PATH] = {0};
	strcat(iniFileName, FileName);
	strcat(iniFileName,"\\FouthHWYDll_XLW.ini");

	CString  cstrIP;
	char chDeviceIP[128] = {0};
	GetDlgItem(IDC_IPADDRESS1)->GetWindowTextA(cstrIP);
	sprintf(chDeviceIP,"%s", cstrIP.GetBuffer());
	WritePrivateProfileStringA("Device", "IP", chDeviceIP , iniFileName);
	cstrIP.ReleaseBuffer();

	char chLog[MAX_PATH] = {0};
	sprintf(chLog, "配置文件设置结束, 设置的IP为%s", chDeviceIP);
	MessageBox(chLog);
}

void CTesTool_FouthHWYDllDlg::OnBnClickedButtonSetserverport()
{
	// TODO: Add your control notification handler code here
	SetServerPort(123);
	char chLog[MAX_PATH] = {0};
	sprintf(chLog, "SetServerPort 调用结束");
	MessageBox(chLog);
}

void CTesTool_FouthHWYDllDlg::OnBnClickedButtonStartserver()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_StartServer)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Trigger)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_StopServer)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GetPlateInfo)->EnableWindow(FALSE);

	BOOL bRet = StartServer();
	char chLog[MAX_PATH] = {0};
	if (bRet)
	{
		ConnectFlag = true;
		sprintf(chLog, "StartServer 调用返回成功");
	}
	else
	{
		ConnectFlag = false;
		sprintf(chLog, "StartServer 调用返回失败");
	}
	MessageBox(chLog);

	GetDlgItem(IDC_BUTTON_StartServer)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Trigger)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_StopServer)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GetPlateInfo)->EnableWindow(TRUE);
}

void CTesTool_FouthHWYDllDlg::OnBnClickedButtonRegi()
{
	// TODO: Add your control notification handler code here
	RegisterNETStatusEvent(g_function);
	char chLog[MAX_PATH] = {0};
	sprintf(chLog, "RegisterNETStatusEvent 调用结束");

	MessageBox(chLog);
}

void CTesTool_FouthHWYDllDlg::OnBnClickedButtonTrigger()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_StartServer)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Trigger)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_StopServer)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GetPlateInfo)->EnableWindow(FALSE);

	CString  cstrIP;
	GetDlgItem(IDC_IPADDRESS1)->GetWindowTextA(cstrIP);
	char chDeviceIP[32] = {0};
	sprintf(chDeviceIP, "%s", cstrIP.GetBuffer());
	cstrIP.ReleaseBuffer();

	BOOL bRet = Trigger(chDeviceIP);

	char chLog[MAX_PATH] = {0};
	if (bRet)
	{
		sprintf(chLog, "设备%s调用Trigger返回成功",chDeviceIP);
	}
	else
	{
		sprintf(chLog, "设备%s调用Trigger返回失败", chDeviceIP);
	}
	MessageBox(chLog);

	GetDlgItem(IDC_BUTTON_StartServer)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Trigger)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_StopServer)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GetPlateInfo)->EnableWindow(TRUE);
}

void CTesTool_FouthHWYDllDlg::OnBnClickedButtonStopserver()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_StartServer)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Trigger)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_StopServer)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GetPlateInfo)->EnableWindow(FALSE);

	BOOL bRet = StopServer();

	char chLog[MAX_PATH] = {0};
	if (bRet)
	{
		sprintf(chLog, "调用返回成功");
	}
	else
	{
		sprintf(chLog, "调用返回失败");
	}
	MessageBox(chLog);
	GetDlgItem(IDC_BUTTON_StartServer)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Trigger)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_StopServer)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GetPlateInfo)->EnableWindow(TRUE);
}

void CTesTool_FouthHWYDllDlg::OnBnClickedButtonGetplateinfo()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_StartServer)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Trigger)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_StopServer)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GetPlateInfo)->EnableWindow(FALSE);

	char chPlateNo[128] = {0};
	int iDelayTime = 1000;
	unsigned char* pByteBinImg = NULL;

	CString  cstrIP, cstrDelayTime;
	GetDlgItem(IDC_IPADDRESS1)->GetWindowTextA(cstrIP);
	GetDlgItem(IDC_EDIT_Time)->GetWindowTextA(cstrDelayTime);
	char chDeviceIP[32] = {0};
	sprintf(chDeviceIP, "%s", cstrIP.GetBuffer());
	cstrIP.ReleaseBuffer();
	int iTime = atoi(cstrDelayTime.GetBuffer());
	if (iTime > 0)
	{
		iDelayTime = iTime;
	}
	pByteBinImg = new unsigned char[280];
	BOOL bRet = GetPlateInfo(chPlateNo, pByteBinImg, chDeviceIP, iDelayTime);

	char chLog[MAX_PATH] = {0};
	if (bRet)
	{
		GetDlgItem(IDC_EDIT_PlateNO)->SetWindowText(chPlateNo);

		char chFileName[MAX_PATH] = {0};
		sprintf(chFileName, ".\\Buffer\\%s-%d-%s.bin", chDeviceIP, GetTickCount(), chPlateNo);
		MakeSureDirectoryPathExists(chFileName);
		FILE* pTempFile = fopen(chFileName, "wb+");
		if (pTempFile)
		{
			fwrite(pByteBinImg, 280, 1, pTempFile);
			fclose(pTempFile);		
		}
		pTempFile = NULL;

		sprintf(chLog, "设备%s GetPlateInfo 调用返回成功", chDeviceIP);
	}
	else
	{
		sprintf(chLog, "设备%s GetPlateInfo 调用返回失败", chDeviceIP);
	}

	if (pByteBinImg != NULL)
	{
		delete pByteBinImg;
		pByteBinImg = NULL;
	}

	MessageBox(chLog);

	GetDlgItem(IDC_BUTTON_StartServer)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Trigger)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_StopServer)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GetPlateInfo)->EnableWindow(TRUE);
}

void CTesTool_FouthHWYDllDlg::OnBnClickedButtonTimer()
{
	// TODO: Add your control notification handler code here
	m_bTimerEnable = !m_bTimerEnable;
	if (m_bTimerEnable)
	{
		GetDlgItem(IDC_BUTTON_Timer)->SetWindowTextA("关闭定时器");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_Timer)->SetWindowTextA("定时获取车牌信息");
	}
}

void CTesTool_FouthHWYDllDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	pDlg = NULL;

	CDialog::OnClose();
}

void CTesTool_FouthHWYDllDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (1 == nIDEvent && m_bTimerEnable)
	{
		char chPlateNo[128] = {0};
		int iDelayTime = 1000;
		unsigned char* pByteBinImg = NULL;

		CString  cstrIP, cstrDelayTime;
		GetDlgItem(IDC_IPADDRESS1)->GetWindowText(cstrIP);
		GetDlgItem(IDC_EDIT_Time)->GetWindowText(cstrDelayTime);
		char chDeviceIP[32] = {0};
		sprintf(chDeviceIP, "%s", cstrIP.GetBuffer());
		cstrIP.ReleaseBuffer();
		int iTime = atoi(cstrDelayTime.GetBuffer());
		if (iTime > 0)
		{
			iDelayTime = iTime;
		}
		pByteBinImg = new unsigned char[280];
		BOOL bRet = GetPlateInfo(chPlateNo, pByteBinImg, chDeviceIP, iDelayTime);

		char chLog[MAX_PATH] = {0};
		if (bRet)
		{
			GetDlgItem(IDC_EDIT_PlateNO)->SetWindowText(chPlateNo);

			char chFileName[MAX_PATH] = {0};
			sprintf(chFileName, ".\\Buffer\\%s-%d-%s.bin", chDeviceIP, GetTickCount(), chPlateNo);
			MakeSureDirectoryPathExists(chFileName);
			FILE* pTempFile = fopen(chFileName, "wb+");
			if (pTempFile)
			{
				fwrite(pByteBinImg, 280, 1, pTempFile);
				fclose(pTempFile);		
			}
			pTempFile = NULL;

			sprintf(chLog, "设备%s GetPlateInfo 调用返回成功", chDeviceIP);
		}
		else
		{
			sprintf(chLog, "设备%s GetPlateInfo 调用返回失败", chDeviceIP);
		}

		if (pByteBinImg != NULL)
		{
			delete pByteBinImg;
			pByteBinImg = NULL;
		}

	}
	//在这里清一下设备状态信息
	GetDlgItem(IDC_STATIC_DeviStatus)->SetWindowText("");

	CDialog::OnTimer(nIDEvent);
}
