// TesTool_FouthHWYDllDlg.h : ͷ�ļ�
//

#pragma once


// CTesTool_FouthHWYDllDlg �Ի���
class CTesTool_FouthHWYDllDlg : public CDialog
{
// ����
public:
	CTesTool_FouthHWYDllDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTOOL_FOUTHHWYDLL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
