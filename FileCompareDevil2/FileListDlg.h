#pragma once
#include "afxcmn.h"
#include "ToolTipListCtrl.h"

enum FILELIST_ROW 
{ 
	FILELIST_NO = 0,//行序号号
	FILELIST_PATH,//要搜索的路径
	FILELIST_INCLUDE,//包含当前行路径的行的序号
	FILELIST_MAX
};
// CFileListDlg 对话框

class CFileListDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileListDlg)

public:
	CFileListDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileListDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_FILELIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CToolTipListCtrl m_list_path1;
	CToolTipListCtrl m_list_path2;
	CString BrowseFolder(void);
	afx_msg void OnBnClickedBtnAdd1();
	afx_msg void OnBnClickedBtnClear1();
	afx_msg void OnBnClickedBtnDel1();
	afx_msg void OnBnClickedBtnGo1();
	afx_msg void OnBnClickedBtnAdd2();
	afx_msg void OnBnClickedBtnClear2();
	afx_msg void OnBnClickedBtnDel2();
	afx_msg void OnBnClickedBtnGo2();
	void AddFilelist(CToolTipListCtrl *plistpath);
	void DeleteThenUpdateListIndex(CToolTipListCtrl *plistpath);
	void FilterInclude(CToolTipListCtrl *plistpath);
	
	CToolTipCtrl m_tooltip_filelist;// 标签提示框
	CImageList m_imagelist;//图标list
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
