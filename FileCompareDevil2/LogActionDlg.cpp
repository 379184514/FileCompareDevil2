// LogActionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileCompareDevil2.h"
#include "LogActionDlg.h"

ListTitle objListLogTitle[]=
{
	{ LISTLOG_NO,       _T("NO"),       LVCFMT_RIGHT,  80},
	{ LISTLOG_TIME,     _T("ʱ��"),     LVCFMT_RIGHT, 130},
	{ LISTLOG_ACTION,   _T("����"),     LVCFMT_RIGHT,  80},
	{ LISTLOG_OBJ1,     _T("Դ����"),   LVCFMT_LEFT,  200},
	{ LISTLOG_OBJ2,     _T("Ŀ�����"), LVCFMT_LEFT,  200},
	{ LISTLOG_SATE,     _T("״̬"),     LVCFMT_LEFT,   50},
	{ LISTLOG_NOTES,    _T("��ע"),     LVCFMT_RIGHT, 250},
};
CString LOGTEXT[]=
{
	_T("��Ǵ�����"),
	_T("��Ǵ�����"),
	_T("��Ǵ�ɾ��"),
	_T("������"),
	_T("�½��ļ���"),
	_T("�ͷ���Դ"),
	_T("���·��"),
	_T("���·��"),
	_T("ɾ������·��"),
	_T("������"),
	_T("�����ļ�"),
	_T("�л�ѡ�"),
	_T("�Ա�"),
	_T("����"),
	_T("���ѡ��"),
	_T("չ��"),
	_T("���ļ���"),
	_T("�ո�ѡ��"),
	_T("��������"),
	_T("����"),
	_T("����"),
	_T("���±���"),
	_T("������ʾ���"),
	_T("ѡ�и���"),
	_T("�۵�"),
	_T("չ������"),
	_T("�۵�����"),
	_T("չ��ȫ��"),
	_T("�۵�ȫ��"),
	_T("")
};

// CLogActionDlg �Ի���

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


// CLogActionDlg ��Ϣ�������

BOOL CLogActionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list_log.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_OWNERDATA|LVS_EX_CHECKBOXES);
	for (int i=0; i<LISTLOG_MAX; i++)
	{
		m_list_log.InsertColumn( objListLogTitle[i].nIndex, objListLogTitle[i].sTitle, objListLogTitle[i].nAlign, objListLogTitle[i].nWidth);
	}
	m_list_log.SetItemCount(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
					szValue = _T("�ɹ�");
					break;
				case FAILED:
					szValue = _T("ʧ��");
					break;
				case WAIT:
					szValue = _T("�ȴ�");
					break;

				default:
					szValue = _T("�쳣");
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
