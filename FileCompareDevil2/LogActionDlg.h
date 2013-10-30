#pragma once
#include "afxcmn.h"
//#include "FileCompareDevil2Dlg.h"
#include "ToolTipListCtrl.h"
#include <vector>

struct LOGLIST
{
	int nAction;
	int nSate;
	//CTime tTime;
	SYSTEMTIME stTime;
	CString sPathOrg;
	CString sPathDest;
	CString sNote;
};

enum LISTLOG_ROW 
{ 
	LISTLOG_NO = 0,
	LISTLOG_TIME,
	LISTLOG_ACTION,
	LISTLOG_OBJ1,
	LISTLOG_OBJ2,
	LISTLOG_SATE,
	LISTLOG_NOTES,
	LISTLOG_MAX
};

enum LOG_ACTION
{ 
	ACTION_COPY = 0,//标记待复制
	ACTION_CUT,		//标记待剪切
	ACTION_DEL,		//标记待删除
	ACTION_REN,		//重命名
	ACTION_MKDIR,	//新建文件夹
	LOG_RELEASE,	//释放资源
	LOG_ADD,		//添加路径
	LOG_CLEAR,		//清除路径
	LOG_DELSEL,		//删除高亮路径
	LOG_INCLUDE,	//检查包含
	LOG_LIST,		//遍历文件
	LOG_CHANGETAB,	//切换选项卡
	LOG_COMPARE,	//对比
	LOG_SORT,		//排序
	LOG_CHECKBOX,	//点击选中
	LOG_EXPAND,		//展开
	LOG_EXPLORER,	//打开文件夹
	LOG_SPACE,		//空格选中
	LOG_SAVE,		//保存数据
	LOG_LOAD,		//载入
	LOG_EXPORT,		//导出
	LOG_TITLE,		//更新标题
	LOG_VIEWINDEX,	//更新显示序号
	LOG_SELECT,		//选中高亮
	LOG_FOLD,		//折叠
	LOG_EXPANDSON,	//展开子项
	LOG_FOLDSON,	//折叠子项
	LOG_EXPANDALL,	//展开全部
	LOG_FOLDALL,	//折叠全部
	LOG_MAX
};
enum LOG_SATE
{ 
	SUCCESS = 0,
	FAILED,
	WAIT
};
typedef struct ListTitle
{
	int nIndex;//序号
	CString sTitle;//标题
	int nAlign;//对齐
	int nWidth;//列宽度
}ListTitle,*pListTitle;


// CLogActionDlg 对话框

class CLogActionDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogActionDlg)

public:
	CLogActionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogActionDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CToolTipListCtrl m_list_log;
	//CListCtrl m_list_log;
	std::vector<LOGLIST> m_dateList_log;
	std::vector<LOGLIST> m_dateList_action;
	int AddLog(int nAction, CString sPathOrg, CString sPathDest = _T(""), CString sNote = _T(""));
	int AddAction(int nAction, CString sPathOrg, CString sPathDest = _T(""), CString sNote = _T(""));
	bool bLog;//log or action
	afx_msg void OnLvnGetdispinfoListLog(NMHDR *pNMHDR, LRESULT *pResult);
	int nListActionMax;
	int nListLogMax;
};
