#pragma once
#include "afxwin.h"


// CCompareDlg �Ի���

class CCompareDlg : public CDialog
{
	DECLARE_DYNAMIC(CCompareDlg)

public:
	CCompareDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCompareDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_COMPARE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
