#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CFilterDlg 对话框

class CFilterDlg : public CDialog
{
	DECLARE_DYNAMIC(CFilterDlg)

public:
	CFilterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFilterDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_FILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	ULONGLONG m_nSize_min;
	ULONGLONG m_nSize_max;
	CString m_strFile_include;
	CString m_strFile_except;
	CString m_strFolder_include;
	CString m_strFolder_except;
	CString m_strType_include;
	CString m_strType_except;
	CTime m_time_create_from;
	CTime m_time_create_to;
	CTime m_time_modify_from;
	CTime m_time_modify_to;
	CDateTimeCtrl m_timectrl_create_from;
	CDateTimeCtrl m_timectrl_create_to;
	CDateTimeCtrl m_timectrl_modify_from;
	CDateTimeCtrl m_timectrl_modify_to;
protected:
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnBnClickedBtnClear();
	BOOL bArchive;
	BOOL bSystem;
	BOOL bHidden;
	BOOL bReadonly;
};
