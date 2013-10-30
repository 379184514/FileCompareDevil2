// LogActionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileCompareDevil2.h"
#include "LogActionDlg.h"

ListTitle objListLogTitle[]=
{
	{ LISTLOG_NO,       _T("NO"),       LVCFMT_RIGHT,  80},
	{ LISTLOG_TIME,     _T("时间"),     LVCFMT_RIGHT, 130},
	{ LISTLOG_ACTION,   _T("操作"),     LVCFMT_RIGHT,  80},
	{ LISTLOG_OBJ1,     _T("源对象"),   LVCFMT_LEFT,  200},
	{ LISTLOG_OBJ2,     _T("目标对象"), LVCFMT_LEFT,  200},
	{ LISTLOG_SATE,     _T("状态"),     LVCFMT_LEFT,   50},
	{ LISTLOG_NOTES,    _T("备注"),     LVCFMT_RIGHT, 250},
};
CString LOGTEXT[]=
{
	_T("标记待复制"),
	_T("标记待剪切"),
	_T("标记待删除"),
	_T("重命名"),
	_T("新建文件夹"),
	_T("释放资源"),
	_T("添加路径"),
	_T("清除路径"),
	_T("删除高亮路径"),
	_T("检查包含"),
	_T("遍历文件"),
	_T("切换选项卡"),
	_T("对比"),
	_T("排序"),
	_T("点击选中"),
	_T("展开"),
	_T("打开文件夹"),
	_T("空格选中"),
	_T("保存数据"),
	_T("载入"),
	_T("导出"),
	_T("更新标题"),
	_T("更新显示序号"),
	_T("选中高亮"),
	_T("折叠"),
	_T("展开子项"),
	_T("折叠子项"),
	_T("展开全部"),
	_T("折叠全部"),
	_T("")
};

// CLogActionDlg 对话框

IMPLEMENT_DYNAMIC(CLogActionDlg, CDialog)

CLogActionDlg::CLogActionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogActionDlg::IDD, pParent)
	, bLog(false)
	, nListActionMax(0)
	, nListLogMax(0)
{

}

CLogActionDlg::~CLogActionDlg()
{
}

void CLogActionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, m_list_log);
}


BEGIN_MESSAGE_MAP(CLogActionDlg, CDialog)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_LOG, &CLogActionDlg::OnLvnGetdispinfoListLog)
END_MESSAGE_MAP()


// CLogActionDlg 消息处理程序

BOOL CLogActionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list_log.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_OWNERDATA|LVS_EX_CHECKBOXES);
	for (int i=0; i<LISTLOG_MAX; i++)
	{
		m_list_log.InsertColumn( objListLogTitle[i].nIndex, objListLogTitle[i].sTitle, objListLogTitle[i].nAlign, objListLogTitle[i].nWidth);
	}
	m_list_log.SetItemCount(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

int CLogActionDlg::AddLog(int nAction, CString sPathOrg, CString sPathDest, CString sNote)
{
	LOGLIST olog;
	olog.nAction = nAction;
	olog.nSate = -1;
	olog.sPathOrg = sPathOrg;
	olog.sPathDest = sPathDest;
	//olog.tTime = CTime::GetCurrentTime();
	GetLocalTime(&olog.stTime);
	olog.sNote = sNote;
	m_dateList_log.push_back(olog);
	nListLogMax++;
	m_list_log.SetItemCount(nListLogMax);
	m_list_log.RedrawItems(0, nListLogMax-1);
	return 0;
}

int CLogActionDlg::AddAction(int nAction, CString sPathOrg, CString sPathDest, CString sNote)
{
	LOGLIST oAction;
	oAction.nAction = nAction;
	oAction.nSate = WAIT;
	oAction.sPathOrg = sPathOrg;
	oAction.sPathDest = sPathDest;
	//oAction.tTime = CTime::GetCurrentTime();
	GetLocalTime(&oAction.stTime);
	oAction.sNote = sNote;
	m_dateList_action.push_back(oAction);
	nListActionMax++;
	m_list_log.SetItemCount(nListActionMax);
	m_list_log.RedrawItems(0, nListActionMax-1);
	return 0;
}

void CLogActionDlg::OnLvnGetdispinfoListLog(NMHDR *pNMHDR, LRESULT *pResult)
{
	//NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	CString szValue=L"";
	long nItem = pDispInfo->item.iItem;
	long nSubItem =  pDispInfo->item.iSubItem;
	std::vector<LOGLIST> *ptLogListTmp;
	try
	{
		if (bLog)
		{
			m_list_log.SetColumnWidth(LISTLOG_SATE,0);
			ptLogListTmp = &m_dateList_log;
		}
		else //action
		{
			m_list_log.SetColumnWidth(LISTLOG_SATE,50);
			ptLogListTmp = &m_dateList_action;
		}
		if (ptLogListTmp->size()<1)
		{
			return;
		}
		COLORREF clrTextBk = RGB(255, 255, 255);
		if ( nItem % 2)
		{
			clrTextBk = RGB(200,255,255);
		}
		SYSTEMTIME st = (*ptLogListTmp)[nItem].stTime;
		switch( nSubItem )
		{
		case LISTLOG_NO:
			szValue.Format(_T("%d"), nItem+1);
			break;
		case LISTLOG_TIME:
			//szValue = (*ptLogListTmp)[nItem].tTime.Format("%Y-%m-%d %H:%M:%S");
			szValue.Format(_T("%.4d-%.2d-%.2d %.2d:%.2d:%.2d.%.3d"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
			break;
		case LISTLOG_ACTION:
			{
				szValue = LOGTEXT[ (*ptLogListTmp)[nItem].nAction ];
			}
			break;
		case LISTLOG_OBJ1:
			szValue = (*ptLogListTmp)[nItem].sPathOrg;
			break;
		case LISTLOG_OBJ2:
			szValue = (*ptLogListTmp)[nItem].sPathDest;
			break;
		case LISTLOG_SATE:
			{
				switch( (*ptLogListTmp)[nItem].nSate )
				{
				case SUCCESS:
					szValue = _T("成功");
					break;
				case FAILED:
					szValue = _T("失败");
					break;
				case WAIT:
					szValue = _T("等待");
					break;

				default:
					szValue = _T("异常");
					break;
				}
			}
			break;
		case LISTLOG_NOTES:
			szValue = (*ptLogListTmp)[nItem].sNote;
			break;

		default:
			break;
		}
		if (pDispInfo->item.mask & LVIF_TEXT)
		{
			if ( szValue.IsEmpty() )
			{
				clrTextBk = RGB(220,220,220);
			}
			m_list_log.clrTextBk = clrTextBk;
			wcscpy (pDispInfo->item.pszText,szValue.GetString());
		}
		if (pDispInfo->item.mask & LVIF_IMAGE)
		{

				//pDispInfo->item.iImage = 5;//"0\"
			
			pDispInfo->item.mask |= LVIF_STATE;
			pDispInfo->item.stateMask = LVIS_STATEIMAGEMASK;

				//pDispInfo->item.state = INDEXTOSTATEIMAGEMASK(2);//checkbox checked

				pDispInfo->item.state = INDEXTOSTATEIMAGEMASK(1);//unchecked
		}	
	}
	catch (CMemoryException* e)
	{
		
	}
	catch (CFileException* e)
	{
	}
	catch (CException* e)
	{
	}

	*pResult = 0;
}
