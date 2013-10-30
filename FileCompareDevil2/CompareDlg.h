#pragma once
#include "afxwin.h"


// CCompareDlg 对话框

class CCompareDlg : public CDialog
{
	DECLARE_DYNAMIC(CCompareDlg)

public:
	CCompareDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCompareDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_COMPARE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_ckLockVscroll;
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	BOOL bName;
	BOOL bType;
	BOOL bSize;
	BOOL bMD5;
};
