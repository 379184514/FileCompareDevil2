
// FileCompareDevil2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFileCompareDevil2App:
// �йش����ʵ�֣������ FileCompareDevil2.cpp
//

class CFileCompareDevil2App : public CWinAppEx
{
public:
	CFileCompareDevil2App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFileCompareDevil2App theApp;