// TesTool_FouthHWYDll.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CTesTool_FouthHWYDllApp:
// �йش����ʵ�֣������ TesTool_FouthHWYDll.cpp
//

class CTesTool_FouthHWYDllApp : public CWinApp
{
public:
	CTesTool_FouthHWYDllApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTesTool_FouthHWYDllApp theApp;
