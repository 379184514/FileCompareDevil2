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
	ACTION_COPY = 0,//��Ǵ�����
	ACTION_CUT,		//��Ǵ�����
	ACTION_DEL,		//��Ǵ�ɾ��
	ACTION_REN,		//������
	ACTION_MKDIR,	//�½��ļ���
	LOG_RELEASE,	//�ͷ���Դ
	LOG_ADD,		//���·��
	LOG_CLEAR,		//���·��
	LOG_DELSEL,		//ɾ������·��
	LOG_INCLUDE,	//������
	LOG_LIST,		//�����ļ�
	LOG_CHANGETAB,	//�л�ѡ�
	LOG_COMPARE,	//�Ա�
	LOG_SORT,		//����
	LOG_CHECKBOX,	//���ѡ��
	LOG_EXPAND,		//չ��
	LOG_EXPLORER,	//���ļ���
	LOG_SPACE,		//�ո�ѡ��
	LOG_SAVE,		//��������
	LOG_LOAD,		//����
	LOG_EXPORT,		//����
	LOG_TITLE,		//���±���
	LOG_VIEWINDEX,	//������ʾ���
	LOG_SELECT,		//ѡ�и���
	LOG_FOLD,		//�۵�
	LOG_EXPANDSON,	//չ������
	LOG_FOLDSON,	//�۵�����
	LOG_EXPANDALL,	//չ��ȫ��
	LOG_FOLDALL,	//�۵�ȫ��
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
	int nIndex;//���
	CString sTitle;//����
	int nAlign;//����
	int nWidth;//�п��
}ListTitle,*pListTitle;


// CLogActionDlg �Ի���

class CLogActionDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogActionDlg)

public:
	CLogActionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogActionDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
