#pragma once
#include "afxcmn.h"
#include "ToolTipListCtrl.h"

enum FILELIST_ROW 
{ 
	FILELIST_NO = 0,//����ź�
	FILELIST_PATH,//Ҫ������·��
	FILELIST_INCLUDE,//������ǰ��·�����е����
	FILELIST_MAX
};
// CFileListDlg �Ի���

class CFileListDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileListDlg)

public:
	CFileListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFileListDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_FILELIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	
	CToolTipCtrl m_tooltip_filelist;// ��ǩ��ʾ��
	CImageList m_imagelist;//ͼ��list
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
