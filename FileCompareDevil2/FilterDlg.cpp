// FilterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileCompareDevil2.h"
#include "FilterDlg.h"


// CFilterDlg 对话框

IMPLEMENT_DYNAMIC(CFilterDlg, CDialog)

CFilterDlg::CFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFilterDlg::IDD, pParent)
	, m_nSize_min(0)
	, m_nSize_max(0)
	, m_strFile_include(_T(""))
	, m_strFile_except(_T(""))
	, m_strFolder_include(_T(""))
	, m_strFolder_except(_T(""))
	, m_strType_include(_T(""))
	, m_strType_except(_T(""))
	, m_time_create_from(0)
	, m_time_create_to(0)
	, m_time_modify_from(0)
	, m_time_modify_to(0)
	, bArchive(TRUE)
	, bSystem(TRUE)
	, bHidden(TRUE)
	, bReadonly(TRUE)
{

}

CFilterDlg::~CFilterDlg()
{
}

void CFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILE_INCLUDE, m_strFile_include);
	DDX_Text(pDX, IDC_EDIT_FILE_EXCEPT, m_strFile_except);
	DDX_Text(pDX, IDC_EDIT_FOLDER_INCLUDE, m_strFolder_include);
	DDX_Text(pDX, IDC_EDIT_FOLDER_EXCEPT, m_strFolder_except);
	DDX_Text(pDX, IDC_EDIT_TYPE_INCLUDE, m_strType_include);
	DDX_Text(pDX, IDC_EDIT_TYPE_EXCEPT, m_strType_except);
	DDX_Text(pDX, IDC_EDIT_SIZE_MIN, m_nSize_min);
	DDX_Text(pDX, IDC_EDIT_SIZE_MAX, m_nSize_max);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_CREATE_FROM, m_time_create_from);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_CREATE_TO, m_time_create_to);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_MODIFY_FROM, m_time_modify_from);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_MODIFY_TO, m_time_modify_to);
	DDX_Control(pDX, IDC_DATETIME_CREATE_FROM, m_timectrl_create_from);
	DDX_Control(pDX, IDC_DATETIME_CREATE_TO, m_timectrl_create_to);
	DDX_Control(pDX, IDC_DATETIME_MODIFY_FROM, m_timectrl_modify_from);
	DDX_Control(pDX, IDC_DATETIME_MODIFY_TO, m_timectrl_modify_to);
	DDX_Check(pDX, IDC_CHECK_ARCHIVE, bArchive);
	DDX_Check(pDX, IDC_CHECK_SYSTEM, bSystem);
	DDX_Check(pDX, IDC_CHECK_HIDDEN, bHidden);
	DDX_Check(pDX, IDC_CHECK_READONLY, bReadonly);
}


BEGIN_MESSAGE_MAP(CFilterDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_OK, &CFilterDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CFilterDlg::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CFilterDlg::OnBnClickedBtnClear)
END_MESSAGE_MAP()


// CFilterDlg 消息处理程序

BOOL CFilterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_timectrl_create_from.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	m_timectrl_create_to.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	m_timectrl_modify_from.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	m_timectrl_modify_to.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	CTime tmin(1970,01,01,8,0,0);
	CTime tmax(2038,01,18,8,0,0);//= CTime::GetCurrentTime();
	m_time_create_from = tmin;
	m_time_create_to = tmax;
	m_time_modify_from = tmin;
	m_time_modify_to = tmax;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFilterDlg::OnCancel()
{
	//CDialog::OnCancel();
}

void CFilterDlg::OnOK()
{
	//CDialog::OnOK();
}

void CFilterDlg::OnBnClickedBtnOk()
{
	UpdateData(TRUE);
// 	CString s_nSize_min;
// 	CString s_nSize_max;
// 	s_nSize_min.Format(L"%I64d",m_nSize_min);
// 	s_nSize_max.Format(L"%I64d",m_nSize_max);
// 	AfxMessageBox(m_strFile_include);
// 	AfxMessageBox(m_strFile_except);
// 	AfxMessageBox(m_strFolder_include);
// 	AfxMessageBox(m_strFolder_except);
// 	AfxMessageBox(m_strType_include);
// 	AfxMessageBox(m_strType_except);
// 	AfxMessageBox(s_nSize_min);
// 	AfxMessageBox(s_nSize_max);
// 	AfxMessageBox(m_time_create_from.Format(_T("%Y-%m-%d %H:%M:%S")));
// 	AfxMessageBox(m_time_create_to.Format(_T("%Y-%m-%d %H:%M:%S")));
// 	AfxMessageBox(m_time_modify_from.Format(_T("%Y-%m-%d %H:%M:%S")));
// 	AfxMessageBox(m_time_modify_to.Format(_T("%Y-%m-%d %H:%M:%S")));
}

void CFilterDlg::OnBnClickedBtnCancel()
{
	UpdateData(FALSE);
}

void CFilterDlg::OnBnClickedBtnClear()
{
	m_strFile_include.Empty();
	m_strFile_except.Empty();
	m_strFolder_include.Empty();
	m_strFolder_except.Empty();
	m_strType_include.Empty();
	m_strType_except.Empty();
	m_nSize_min = 0;
	m_nSize_max = 0;
	CTime tmin(1970,01,01,8,0,0);
	CTime tmax(2038,01,18,8,0,0);
	m_time_create_from = tmin;
	m_time_create_to = tmax;
	m_time_modify_from = tmin;
	m_time_modify_to = tmax;
	bArchive = TRUE;
	bSystem = TRUE;
	bHidden = TRUE;
	bReadonly = TRUE;
	UpdateData(FALSE);
}
