
// MyOpenCV.h : MyOpenCV Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMyOpenCVApp:
// �йش����ʵ�֣������ MyOpenCV.cpp
//

class CMyOpenCVApp : public CWinApp
{
public:
	CMyOpenCVApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyOpenCVApp theApp;
