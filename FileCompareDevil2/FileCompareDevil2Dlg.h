
// FileCompareDevil2Dlg.h : 头文件
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
// 	int nIndex;//序号
// 	CString sTitle;//标题
// 	int nAlign;//对齐
// 	int nWidth;//列宽度
// }ListTitle,*pListTitle;

struct FILELIST
{
//	BOOL bChecked;
//	BOOL bExpand;
	CString sFullPath;
	CFileInfo* pFileinfo;	
};




// CFileCompareDevil2Dlg 对话框
class CFileCompareDevil2Dlg : public CDialog
{
// 构造
public:
	CFileCompareDevil2Dlg(CWnd* pParent = NULL);	// 标准构造函数
	~CFileCompareDevil2Dlg();

// 对话框数据
	enum { IDD = IDD_FILECOMPAREDEVIL2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()

public:
	CTabCtrl m_maintab;//选项卡控件
	CFileListDlg m_dlg_filelist;//文件路径列表对话框

	CFilterDlg m_dlg_filter;//过滤选项对话框
	CCompareDlg m_dlg_compare;//对比设置对话框
	CLogActionDlg m_dlg_logaction;//日志/任务对话框

	CToolTipListCtrl m_list_equal;//对比状态列表

	CToolTipListCtrl* ptm_list_path;
	CToolTipListCtrl* ptlist;//文件列表临时变量指针
	CToolTipListCtrl m_list1;//左侧文件列表
	CToolTipListCtrl m_list2;//右侧文件列表

	int* ptnListMax;
	int nListMax1;//文件对比列表显示总行数
	int nListMax2;

	CToolTipCtrl m_tooltip;//标签提示框
	CImageList m_imagelist;//图标list
	CImageList m_imgState;//checkbox图标
	
	CFileInfo** ptm_pRoot;
	CFileInfo* m_pRoot1;// 树形结构文件数据
	CFileInfo* m_pRoot2;
	
	std::vector<FILELIST> *ptFileList;
	std::vector<FILELIST> m_FileList1;// 数组结构文件原始数据
	std::vector<FILELIST> m_FileList2;
	
	BOOL* ptbSortUP;
	BOOL bSortUP1;// 是否递增排序
	BOOL bSortUP2;
	
	int* ptnSortBy;
	int nSortBy1;// 排序规则
	int nSortBy2;

	BOOL bCompared;//是否对比过

	int nListCur;
	
	int** ptpObjIndex;// 排序后数组序号动态数组
	int* pObjIndex1;
	int* pObjIndex2;
	int** ptpViewIdx;//显示用数组序号
	int* pViewIdx1;
	int* pViewIdx2;
	int* pCmpIdxAll1;//对比后数组序号
	int* pCmpIdxAll2;
	int* pCmpIdxAllg;//分组组号
	int* pCmpIdxLRE1;//对比后左右相同数组序号
	int* pCmpIdxLRE2;
	int* pCmpIdxLREg;
	int* pCmpIdxLRN1;//对比后左右不同数组序号
	int* pCmpIdxLRN2;
	int* pCmpIdxLRNg;
	int* pCmpIdxAnyE1;//对比后任何数组序号
	int* pCmpIdxAnyE2;
	int* pCmpIdxAnyEg;
	int* pCmpIdxAllN1;//对比后全部不同数组序号
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

	int SetCurTmp(int nlist);//根据操作的左/右边来设置临时变量
	void BackupData(int nlist);//保存目录数据
	CString FiletimeToString(FILETIME ft);//转换filetime
	ULONGLONG SearchFiles(int nlayers, CString sPath, CFileInfo* pParent);//遍历文件函数
	int ReleaseList(int nlist);//释放列表相关资源
	int AddFileArray(int nlist, CFileInfo* pFileInfo, CString sPath);//树形文件数据添加到数组结构
	int LoadFileinfoData(int nlist);//导入目录数据
	int Export(int nlist);//导出为文本
	int UpdateListTitle(int nlist);//更新列表标题
	int SortFileList(int nlist);//排序
	int ToggleCheckBox(int nlist,int nItem);//选中列表checkbox
	int ExpandCollapse(int nlist, int nItem);
	int UpdateViewIndex(int nlist);
	int IsFilesEquals(FILELIST* pFileList1, FILELIST* pFileList2);
	int CompareFiles();
	void FilelistGo(int nlist);
	void FilelistGo1();//重新枚举文件
	void FilelistGo2();
	//BOOL IsVectorItemExist(CString cFilename, CFileInfo* pParent);
	
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);//切换选项卡
			void OnLvnGetdispinfoListCom(int nlist,NMHDR *pNMHDR, LRESULT *pResult);//虚拟列表数据填充
	afx_msg void OnLvnGetdispinfoList1(NMHDR *pNMHDR, LRESULT *pResult);//虚拟列表数据填充
	afx_msg void OnLvnGetdispinfoList2(NMHDR *pNMHDR, LRESULT *pResult);
			void OnLvnColumnclickListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);//点击列表标题排序
	afx_msg void OnLvnColumnclickList2(NMHDR *pNMHDR, LRESULT *pResult);
			void OnNMClickListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);//点击选中该行	
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
			void OnNMDblclkListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);//双击列表打开文件所在文件夹
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
			void OnLvnKeydownListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult);//列表中按空格选中checkbox
	afx_msg void OnLvnKeydownList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);//拖动竖直滚动条
	afx_msg void OnBnClickedCkLockVscroll();
	afx_msg void OnBnClickedBtnSave1();
	afx_msg void OnBnClickedBtnSave2();
	afx_msg void OnBnClickedBtnOpen1();
	afx_msg void OnBnClickedBtnOpen2();
	afx_msg void OnBnClickedBtnExport1();
	afx_msg void OnBnClickedBtnExport2();
	afx_msg void OnBnClickedBtnEqual();	
	afx_msg void OnBnClickedBtnRefresh();//刷新
	afx_msg LRESULT OnMylistKillfocus(WPARAM, LPARAM); //点击列表滚动条时触发结束重命名
			void FilterFiles(CFileInfo* pFileInfo);//过滤文件
			void OnNMRClickListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);//弹出右键菜单
	afx_msg void OnNMRClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnListMkdir();//新建文件夹
	afx_msg void OnListCopy();//标记选中项为待复制
	afx_msg void OnListCut();//标记选中项为待剪切
	afx_msg void OnListPaste();//粘贴
	afx_msg void OnListDelete();//删除
	afx_msg void OnListIgnore();//清除当前项的待处理状态（待复制、待剪切）
	afx_msg void OnListRename();//重命名
	afx_msg void OnEnKillfocusEditRename();//重命名结束
	afx_msg void OnListSelect();//选中高亮，支持多选
	afx_msg void OnListSelectall();//全选
	afx_msg void OnListSelectinvert();//反选
	afx_msg void OnListExpand();//展开
	afx_msg void OnListFold();//折叠
	afx_msg void OnListExpandson();//展开子项
	afx_msg void OnListFoldson();//折叠子项
	afx_msg void OnListExpandall();//展开全部
	afx_msg void OnListFoldall();//折叠全部
	afx_msg void OnListReflash();//刷新（重新遍历当前路径下的文件列表）
	afx_msg void OnListProperty();//属性
	afx_msg void OnListCopypath();//复制路径
	afx_msg void OnListOpencontains();//打开所在文件夹
	afx_msg void OnBnClickedBtnLogaction();//log对话框
	afx_msg void OnBnClickedBtnLogaction2();//action对话框
	afx_msg void OnListHidedir();//排除路径
	afx_msg void OnListIgnoresel();//清除选中项的待处理状态（待复制、待剪切）
	
	int nSelItem;//弹出右键菜单时点击的行号
	int nSelSubItem;//弹出右键菜单时点击的列号
	int nSelList;//弹出右键菜单时点击的列表
	CEdit m_rename;//重命名编辑框	
	
	CString strloglistn;//当前操作的list字符串
	int nListCopyfrom;
};
