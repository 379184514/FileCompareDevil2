// FileListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileCompareDevil2.h"
#include "FileCompareDevil2Dlg.h"
#include "FileListDlg.h"


ListTitle objFileListTitle[]=
{
	{ FILELIST_NO,       _T("NO"),         LVCFMT_RIGHT,  50},
	{ FILELIST_PATH,     _T("·��"),       LVCFMT_LEFT,  200},
	{ FILELIST_INCLUDE,  _T("���������"), LVCFMT_RIGHT,  80},
};
// CFileListDlg �Ի���

IMPLEMENT_DYNAMIC(CFileListDlg, CDialog)

CFileListDlg::CFileListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileListDlg::IDD, pParent)
{

}

CFileListDlg::~CFileListDlg()
{
}

void CFileListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PATH1, m_list_path1);
	DDX_Control(pDX, IDC_LIST_PATH2, m_list_path2);
}


BEGIN_MESSAGE_MAP(CFileListDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADD1, &CFileListDlg::OnBnClickedBtnAdd1)
	ON_BN_CLICKED(IDC_BTN_CLEAR1, &CFileListDlg::OnBnClickedBtnClear1)
	ON_BN_CLICKED(IDC_BTN_DEL1, &CFileListDlg::OnBnClickedBtnDel1)
	ON_BN_CLICKED(IDC_BTN_GO1, &CFileListDlg::OnBnClickedBtnGo1)
	ON_BN_CLICKED(IDC_BTN_ADD2, &CFileListDlg::OnBnClickedBtnAdd2)
	ON_BN_CLICKED(IDC_BTN_CLEAR2, &CFileListDlg::OnBnClickedBtnClear2)
	ON_BN_CLICKED(IDC_BTN_DEL2, &CFileListDlg::OnBnClickedBtnDel2)
	ON_BN_CLICKED(IDC_BTN_GO2, &CFileListDlg::OnBnClickedBtnGo2)
END_MESSAGE_MAP()


// CFileListDlg ��Ϣ�������

BOOL CFileListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_list_path1.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	m_list_path2.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	for (int i=0; i<FILELIST_MAX; i++)
	{
		m_list_path1.InsertColumn( objFileListTitle[i].nIndex, objFileListTitle[i].sTitle, objFileListTitle[i].nAlign, objFileListTitle[i].nWidth);
		m_list_path2.InsertColumn( objFileListTitle[i].nIndex, objFileListTitle[i].sTitle, objFileListTitle[i].nAlign, objFileListTitle[i].nWidth);
	}
	
	//����ͼ��
	m_imagelist.Create(16, 16, TRUE|ILC_COLOR32, 0, 0);
	m_imagelist.Add(LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON_NULL)));//0
	m_imagelist.Add(LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON_INCLUDE)));//1 include

	m_list_path1.SetImageList(&m_imagelist,LVSIL_SMALL);
	m_list_path2.SetImageList(&m_imagelist,LVSIL_SMALL);

	//--���ñ�ǩ��ʾ�ؼ� S----//
	EnableToolTips(TRUE); 
	m_tooltip_filelist.Create(this); 
	m_tooltip_filelist.Activate(TRUE); 
	CWnd* pW=GetDlgItem(IDC_BTN_DEL1);//�õ�����ָ�� 
	m_tooltip_filelist.AddTool(pW,_T("ɾ������ѡ����")); //��ӹ̶��ı�
	//--���ñ�ǩ��ʾ�ؼ� E----//

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//ѡ���ļ���
CString CFileListDlg::BrowseFolder(void)
{
	BROWSEINFO   bf;   
	LPITEMIDLIST   lpitem;   
	memset(&bf,0,sizeof   BROWSEINFO); 
	bf.lpszTitle = _T("select folder");
	bf.ulFlags = BIF_STATUSTEXT|0x0040 |BIF_RETURNONLYFSDIRS|BIF_EDITBOX;//| BIF_BROWSEINCLUDEFILES;
	lpitem=SHBrowseForFolder(&bf);   
	WCHAR pBuffer[MAX_PATH];
	SHGetPathFromIDList(lpitem,pBuffer);
	return CString(pBuffer);
}


void CFileListDlg::AddFilelist(CToolTipListCtrl* plistpath)
{
	int nLastNo = plistpath->GetItemCount();
	CString sInFile = BrowseFolder();
	((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_ADD, sInFile);
	if (sInFile.IsEmpty())
	{
		AfxMessageBox(_T("Invalid selected!"));
		return;
	}
	CString sItemPath;
	CString sIndex,sIncludeIndex;
	sIndex.Format(_T("%d"), nLastNo);
	for (int i=0; i<nLastNo; i++)
	{
		if (!plistpath->GetCheck(i))
		{
			continue;
		}
		sItemPath = plistpath->GetItemText(i,FILELIST_PATH);
		sIncludeIndex.Format(_T("%d"), i);
		if ( sInFile.CompareNoCase( sItemPath ) == 0)//�ظ�
		{
			((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_ADD, _T("Repeat"), sIncludeIndex, sItemPath);
			plistpath->SetItemState(i,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
			AfxMessageBox(_T("Repeat selected! Canceled!"));
			plistpath->SetFocus();
			return;
		}
		else if (sInFile.Find(sItemPath) != -1)//�������·������
		{
			((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_ADD, _T("included by"), sIncludeIndex, sItemPath);
			plistpath->SetItemState(i,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
			plistpath->InsertItem(nLastNo, sIndex, 1);
			plistpath->SetItemText(nLastNo, FILELIST_PATH, sInFile);
			plistpath->SetItemText(nLastNo, FILELIST_INCLUDE, sIncludeIndex);
			if (plistpath->GetCheck(i))//���ԭ����ѡ����ѡ��
			{
				plistpath->SetCheck(nLastNo, FALSE);
			}
			else
			{
				plistpath->SetCheck(nLastNo);
			}

			AfxMessageBox(sItemPath + _T("is included the new selection!"));
			
			plistpath->SetFocus();
			return;
		}
		else if (sItemPath.Find(sInFile) != -1)//��������ӵ�·��
		{
			((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_ADD, _T("include"), sIncludeIndex, sItemPath);
			plistpath->SetItemState(i,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
			plistpath->SetItemText(i, FILELIST_INCLUDE, sIndex);
			plistpath->SetCheck(i, FALSE);
			LVITEM Itemattr;
			Itemattr.iItem=i;  //ָ����һ��
			Itemattr.mask   =   LVIF_IMAGE;
			Itemattr.iImage =1;  //Ҫ�ѵ�ǰͼ��ĳ�m_Imagelist ���±�Ϊ 1��ͼ�ꡣ
			plistpath->SetItem (&Itemattr);

			AfxMessageBox(sItemPath + _T("is inclued by the new selection!"));
			
			plistpath->SetFocus();
		}
	}
	plistpath->InsertItem(nLastNo, sIndex, 0);
	plistpath->SetItemText(nLastNo, FILELIST_PATH, sInFile);
	plistpath->SetCheck(nLastNo);
}
//���·�����
void CFileListDlg::OnBnClickedBtnAdd1()
{
	((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_ADD, _T("list 1"));
	AddFilelist(&m_list_path1);
}
//�ұ�·�����
void CFileListDlg::OnBnClickedBtnAdd2()
{
	((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_ADD, _T("list 2"));
	AddFilelist(&m_list_path2);
}

//���·�����
void CFileListDlg::OnBnClickedBtnClear1()
{
	((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_CLEAR, _T("list 1"));
	m_list_path1.DeleteAllItems();
}
//�ұ�·�����
void CFileListDlg::OnBnClickedBtnClear2()
{
	((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_CLEAR, _T("list 2"));
	m_list_path2.DeleteAllItems();
}
void CFileListDlg::DeleteThenUpdateListIndex(CToolTipListCtrl *plistpath)
{
	int nItemSel = plistpath->GetSelectionMark();
	CString sTmp;
	sTmp.Format(_T("%d"), nItemSel);
	((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_DELSEL, sTmp, _T(""), plistpath->GetItemText(nItemSel,FILELIST_PATH));
	int nTotal = plistpath->GetItemCount();
	for (int i=0; i<nTotal; i++)
	{
		int nInclude = _wtoi(plistpath->GetItemText(i, FILELIST_INCLUDE));
		if ( nInclude > nItemSel)
		{
			sTmp.Format(L"%d",nInclude-1);
			plistpath->SetItemText(i, FILELIST_INCLUDE,sTmp);
		}
		int nIndex = _wtoi(plistpath->GetItemText(i, FILELIST_NO));
		if ( nIndex > nItemSel)
		{
			sTmp.Format(L"%d",nIndex-1);
			plistpath->SetItemText(i, FILELIST_NO,sTmp);
		}
	}
	if (LVIS_SELECTED == plistpath->GetItemState(nItemSel,LVIS_SELECTED))
	{
		plistpath->DeleteItem(nItemSel);
	}

}
//���·��ɾ��������
void CFileListDlg::OnBnClickedBtnDel1()
{
	((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_DELSEL, _T("list 1"));
	DeleteThenUpdateListIndex(&m_list_path1);
}
//�ұ�·��ɾ��������
void CFileListDlg::OnBnClickedBtnDel2()
{
	((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_DELSEL, _T("list 2"));
	DeleteThenUpdateListIndex(&m_list_path2);
}

void CFileListDlg::FilterInclude(CToolTipListCtrl *plistpath)
{
	int nLastNo = plistpath->GetItemCount();
	CString sItemPathOrg, sItemPathCur;
	CString sIndexOrg,sIndexcCur;	
	LVITEM Itemattr;
	Itemattr.mask   =   LVIF_IMAGE;
	Itemattr.iImage =1;  //Ҫ�ѵ�ǰͼ��ĳ�m_Imagelist ���±�Ϊ 1��ͼ�ꡣ
	for (int i=0; i<nLastNo; i++)
	{
		if (!plistpath->GetCheck(i))
		{
			continue;
		}
		sIndexOrg.Format(_T("%d"), i);
		sItemPathOrg = plistpath->GetItemText(i,FILELIST_PATH);
		for (int j=i+1;j<nLastNo;j++)
		{
			if (!plistpath->GetCheck(j))
			{
				continue;
			}
			sIndexcCur.Format(_T("%d"), j);
			sItemPathCur = plistpath->GetItemText(j,FILELIST_PATH);
			if ( sItemPathCur.CompareNoCase( sItemPathOrg ) == 0)//�ظ�
			{
				((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_INCLUDE, sIndexOrg + _T("") + sItemPathOrg, sIndexcCur + _T("") + sItemPathCur, _T("repeat"));
				plistpath->SetCheck(j, FALSE);
				Itemattr.iItem=j;  //ָ����һ��
				plistpath->SetItem (&Itemattr);
			}
			else if (sItemPathCur.Find(sItemPathOrg) != -1)//���Ա������
			{
				((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_INCLUDE, sIndexOrg + _T("") + sItemPathOrg, sIndexcCur + _T("") + sItemPathCur, _T("included"));
				plistpath->SetCheck(j, FALSE);
				Itemattr.iItem = j;  //ָ����һ��
				plistpath->SetItem (&Itemattr);
			}
			else if (sItemPathOrg.Find(sItemPathCur) != -1)//�ο���������
			{
				((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_INCLUDE, sIndexOrg + _T("") + sItemPathOrg, sIndexcCur + _T("") + sItemPathCur, _T("include"));
				plistpath->SetCheck(i, FALSE);
				Itemattr.iItem = i;  //ָ����һ��
				plistpath->SetItem (&Itemattr);
				break;
			}
		}
	}
}

void CFileListDlg::OnBnClickedBtnGo1()
{
	((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_INCLUDE, _T("list 1"));
	FilterInclude(&m_list_path1);
	((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->FilelistGo1();
}
void CFileListDlg::OnBnClickedBtnGo2()
{
	((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->m_dlg_logaction.AddLog(LOG_INCLUDE, _T("list 2"));
	FilterInclude(&m_list_path2);
	((CFileCompareDevil2Dlg*)GetOwner()->GetParent())->FilelistGo2();
}

void CFileListDlg::OnOK()
{
	//CDialog::OnOK();
}

void CFileListDlg::OnCancel()
{
	//CDialog::OnCancel();
}
