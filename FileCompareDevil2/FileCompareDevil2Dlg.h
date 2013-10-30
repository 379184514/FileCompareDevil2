
// FileCompareDevil2Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "FileListDlg.h"
#include "FileInfo.h"
#include "FilterDlg.h"
#include "CompareDlg.h"
#include "LogActionDlg.h"


enum LIST_ROW 
{ 
	LIST_NO = 0,
	LIST_TREE,
	LIST_INDEX,
	LIST_SATE,
	LIST_PATH,
	LIST_NAME,
	LIST_TYPE,
	LIST_SIZE,
	LIST_CURDIRS,
	LIST_CURFILES,
	LIST_ALLDIR,
	LIST_ALLFILES,
	LIST_READONLY,
	LIST_SYSTEM,
	LIST_HIDDEN,
	LIST_CREATE,
	LIST_ACCESS,
	LIST_WRITE,
	LIST_MAX
};
// typedef struct ListTitle
// {
// 	int nIndex;//���
// 	CString sTitle;//����
// 	int nAlign;//����
// 	int nWidth;//�п��
// }ListTitle,*pListTitle;

struct FILELIST
{
//	BOOL bChecked;
//	BOOL bExpand;
	CString sFullPath;
	CFileInfo* pFileinfo;	
};




// CFileCompareDevil2Dlg �Ի���
class CFileCompareDevil2Dlg : public CDialog
{
// ����
public:
	CFileCompareDevil2Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CFileCompareDevil2Dlg();

// �Ի�������
	enum { IDD = IDD_FILECOMPAREDEVIL2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()

public:
	CTabCtrl m_maintab;//ѡ��ؼ�
	CFileListDlg m_dlg_filelist;//�ļ�·���б�Ի���

	CFilterDlg m_dlg_filter;//����ѡ��Ի���
	CCompareDlg m_dlg_compare;//�Ա����öԻ���
	CLogActionDlg m_dlg_logaction;//��־/����Ի���

	CToolTipListCtrl m_list_equal;//�Ա�״̬�б�

	CToolTipListCtrl* ptm_list_path;
	CToolTipListCtrl* ptlist;//�ļ��б���ʱ����ָ��
	CToolTipListCtrl m_list1;//����ļ��б�
	CToolTipListCtrl m_list2;//�Ҳ��ļ��б�

	int* ptnListMax;
	int nListMax1;//�ļ��Ա��б���ʾ������
	int nListMax2;

	CToolTipCtrl m_tooltip;//��ǩ��ʾ��
	CImageList m_imagelist;//ͼ��list
	CImageList m_imgState;//checkboxͼ��
	
	CFileInfo** ptm_pRoot;
	CFileInfo* m_pRoot1;// ���νṹ�ļ�����
	CFileInfo* m_pRoot2;
	
	std::vector<FILELIST> *ptFileList;
	std::vector<FILELIST> m_FileList1;// ����ṹ�ļ�ԭʼ����
	std::vector<FILELIST> m_FileList2;
	
	BOOL* ptbSortUP;
	BOOL bSortUP1;// �Ƿ��������
	BOOL bSortUP2;
	
	int* ptnSortBy;
	int nSortBy1;// �������
	int nSortBy2;

	BOOL bCompared;//�Ƿ�Աȹ�

	int nListCur;
	
	int** ptpObjIndex;// �����������Ŷ�̬����
	int* pObjIndex1;
	int* pObjIndex2;
	int** ptpViewIdx;//��ʾ���������
	int* pViewIdx1;
	int* pViewIdx2;
	int* pCmpIdxAll1;//�ԱȺ��������
	int* pCmpIdxAll2;
	int* pCmpIdxAllg;//�������
	int* pCmpIdxLRE1;//�ԱȺ�������ͬ�������
	int* pCmpIdxLRE2;
	int* pCmpIdxLREg;
	int* pCmpIdxLRN1;//�ԱȺ����Ҳ�ͬ�������
	int* pCmpIdxLRN2;
	int* pCmpIdxLRNg;
	int* pCmpIdxAnyE1;//�ԱȺ��κ��������
	int* pCmpIdxAnyE2;
	int* pCmpIdxAnyEg;
	int* pCmpIdxAllN1;//�ԱȺ�ȫ����ͬ�������
	int* pCmpIdxAllN2;
	int* pCmpIdxAllNg;

	int nOffsetVscroll;

	int nListMaxView;
	int* ptnListMaxView; 
	int nListMaxView1;
	int nListMaxView2;
	int nListMaxAll;

	BOOL bSortUPEqual;
	///////////////////////////////////////////////////////////////////////////////////////////

	int SetCurTmp(int nlist);//���ݲ�������/�ұ���������ʱ����
	void BackupData(int nlist);//����Ŀ¼����
	CString FiletimeToString(FILETIME ft);//ת��filetime
	ULONGLONG SearchFiles(int nlayers, CString sPath, CFileInfo* pParent);//�����ļ�����
	int ReleaseList(int nlist);//�ͷ��б������Դ
	int AddFileArray(int nlist, CFileInfo* pFileInfo, CString sPath);//�����ļ�������ӵ�����ṹ
	int LoadFileinfoData(int nlist);//����Ŀ¼����
	int Export(int nlist);//����Ϊ�ı�
	int UpdateListTitle(int nlist);//�����б����
	int SortFileList(int nlist);//����
	int ToggleCheckBox(int nlist,int nItem);//ѡ���б�checkbox
	int ExpandCollapse(int nlist, int nItem);
	int UpdateViewIndex(int nlist);
	int IsFilesEquals(FILELIST* pFileList1, FILELIST* pFileList2);
	int CompareFiles();
	void FilelistGo(int nlist);
	void FilelistGo1();//����ö���ļ�
	void FilelistGo2();
	//BOOL IsVectorItemExist(CString cFilename, CFileInfo* pParent);
	
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);//�л�ѡ�
			void OnLvnGetdispinfoListCom(int nlist,NMHDR *pNMHDR, LRESULT *pResult);//�����б��������
	afx_msg void OnLvnGetdispinfoList1(NMHDR *pNMHDR, LRESULT *pResult);//�����б��������
	afx_msg void OnLvnGetdispinfoList2(NMHDR *pNMHDR, LRESULT *pResult);
			void OnLvnColumnclickListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);//����б��������
	afx_msg void OnLvnColumnclickList2(NMHDR *pNMHDR, LRESULT *pResult);
			void OnNMClickListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);//���ѡ�и���	
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
			void OnNMDblclkListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);//˫���б���ļ������ļ���
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
			void OnLvnKeydownListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult);//�б��а��ո�ѡ��checkbox
	afx_msg void OnLvnKeydownList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);//�϶���ֱ������
	afx_msg void OnBnClickedCkLockVscroll();
	afx_msg void OnBnClickedBtnSave1();
	afx_msg void OnBnClickedBtnSave2();
	afx_msg void OnBnClickedBtnOpen1();
	afx_msg void OnBnClickedBtnOpen2();
	afx_msg void OnBnClickedBtnExport1();
	afx_msg void OnBnClickedBtnExport2();
	afx_msg void OnBnClickedBtnEqual();	
	afx_msg void OnBnClickedBtnRefresh();//ˢ��
	afx_msg LRESULT OnMylistKillfocus(WPARAM, LPARAM); //����б������ʱ��������������
			void FilterFiles(CFileInfo* pFileInfo);//�����ļ�
			void OnNMRClickListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);//�����Ҽ��˵�
	afx_msg void OnNMRClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnListMkdir();//�½��ļ���
	afx_msg void OnListCopy();//���ѡ����Ϊ������
	afx_msg void OnListCut();//���ѡ����Ϊ������
	afx_msg void OnListPaste();//ճ��
	afx_msg void OnListDelete();//ɾ��
	afx_msg void OnListIgnore();//�����ǰ��Ĵ�����״̬�������ơ������У�
	afx_msg void OnListRename();//������
	afx_msg void OnEnKillfocusEditRename();//����������
	afx_msg void OnListSelect();//ѡ�и�����֧�ֶ�ѡ
	afx_msg void OnListSelectall();//ȫѡ
	afx_msg void OnListSelectinvert();//��ѡ
	afx_msg void OnListExpand();//չ��
	afx_msg void OnListFold();//�۵�
	afx_msg void OnListExpandson();//չ������
	afx_msg void OnListFoldson();//�۵�����
	afx_msg void OnListExpandall();//չ��ȫ��
	afx_msg void OnListFoldall();//�۵�ȫ��
	afx_msg void OnListReflash();//ˢ�£����±�����ǰ·���µ��ļ��б�
	afx_msg void OnListProperty();//����
	afx_msg void OnListCopypath();//����·��
	afx_msg void OnListOpencontains();//�������ļ���
	afx_msg void OnBnClickedBtnLogaction();//log�Ի���
	afx_msg void OnBnClickedBtnLogaction2();//action�Ի���
	afx_msg void OnListHidedir();//�ų�·��
	afx_msg void OnListIgnoresel();//���ѡ����Ĵ�����״̬�������ơ������У�
	
	int nSelItem;//�����Ҽ��˵�ʱ������к�
	int nSelSubItem;//�����Ҽ��˵�ʱ������к�
	int nSelList;//�����Ҽ��˵�ʱ������б�
	CEdit m_rename;//�������༭��	
	
	CString strloglistn;//��ǰ������list�ַ���
	int nListCopyfrom;
};
