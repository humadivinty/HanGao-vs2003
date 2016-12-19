// TesTool_FouthHWYDllDlg.h : 头文件
//

#pragma once


// CTesTool_FouthHWYDllDlg 对话框
class CTesTool_FouthHWYDllDlg : public CDialog
{
// 构造
public:
	CTesTool_FouthHWYDllDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTOOL_FOUTHHWYDLL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonSetserverport();
	afx_msg void OnBnClickedButtonStartserver();
	afx_msg void OnBnClickedButtonRegi();
	afx_msg void OnBnClickedButtonTrigger();
	afx_msg void OnBnClickedButtonStopserver();
	afx_msg void OnBnClickedButtonGetplateinfo();
	afx_msg void OnBnClickedButtonTimer();
	afx_msg void OnClose();

private:
	bool m_bTimerEnable;
public:
	afx_msg void OnTimer(UINT nIDEvent);
};
