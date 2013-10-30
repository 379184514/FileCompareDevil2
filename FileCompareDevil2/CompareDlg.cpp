// CompareDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileCompareDevil2.h"
#include "CompareDlg.h"


// CCompareDlg 对话框

IMPLEMENT_DYNAMIC(CCompareDlg, CDialog)

CCompareDlg::CCompareDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompareDlg::IDD, pParent)
	, bName(FALSE)
	, bType(FALSE)
	, bSize(FALSE)
	, bMD5(FALSE)
{

}

CCompareDlg::~CCompareDlg()
{
}

void CCompareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CK_LOCK_VSCROLL, m_ckLockVscroll);
	DDX_Check(pDX, IDC_CK_NAME, bName);
	DDX_Check(pDX, IDC_CK_TYPE, bType);
	DDX_Check(pDX, IDC_CK_SIZE, bSize);
	DDX_Check(pDX, IDC_CK_MD5, bMD5);
}


BEGIN_MESSAGE_MAP(CCompareDlg, CDialog)
END_MESSAGE_MAP()


// CCompareDlg 消息处理程序

void CCompareDlg::OnOK()
{
	//CDialog::OnOK();
}

void CCompareDlg::OnCancel()
{
	//CDialog::OnCancel();
}
