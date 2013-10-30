
// FileCompareDevil2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileCompareDevil2.h"
#include "FileCompareDevil2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


ListTitle objListTitle[]=
{
	{ LIST_NO,       _T("NO"),       LVCFMT_RIGHT,  80},
	{ LIST_TREE,     _T("树"),       LVCFMT_LEFT,  180},
	{ LIST_INDEX,    _T("Index"),    LVCFMT_RIGHT,  80},
	{ LIST_SATE,     _T("状态"),     LVCFMT_RIGHT,  80},
	{ LIST_PATH,     _T("路径"),     LVCFMT_LEFT,  200},
	{ LIST_NAME,     _T("文件名"),   LVCFMT_LEFT,  100},
	{ LIST_TYPE,     _T("类型"),     LVCFMT_LEFT,   50},
	{ LIST_SIZE,     _T("大小"),     LVCFMT_RIGHT,  50},
	{ LIST_CURDIRS,  _T("目录"),     LVCFMT_RIGHT,  50},
	{ LIST_CURFILES, _T("文件"),     LVCFMT_RIGHT,  50},
	{ LIST_ALLDIR,   _T("目录总数"), LVCFMT_RIGHT,  50},
	{ LIST_ALLFILES, _T("文件总数"), LVCFMT_RIGHT,  50},
	{ LIST_READONLY, _T("只读"),     LVCFMT_LEFT,   50},
	{ LIST_SYSTEM,   _T("系统"),     LVCFMT_LEFT,   50},
	{ LIST_HIDDEN,   _T("隐藏"),     LVCFMT_LEFT,   50},
	{ LIST_CREATE,   _T("创建时间"), LVCFMT_LEFT,  150},
	{ LIST_ACCESS,   _T("访问时间"), LVCFMT_LEFT,  150},
	{ LIST_WRITE,    _T("修改时间"), LVCFMT_LEFT,  150}
};

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CFileCompareDevil2Dlg 对话框




CFileCompareDevil2Dlg::CFileCompareDevil2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileCompareDevil2Dlg::IDD, pParent)
	, ptlist(NULL)
	, ptnListMax(NULL)
	, ptFileList(NULL)
	, ptm_list_path(NULL)
	, nListMax1(0)
	, nListMax2(0)
	, ptm_pRoot(NULL)
	, m_pRoot1(NULL)
	, m_pRoot2(NULL)
	, ptbSortUP(NULL)
	, bSortUP1(FALSE)
	, bSortUP2(FALSE)
	, ptnSortBy(NULL)
	, nSortBy1(0)
	, nSortBy2(0)
	, bCompared(FALSE)
	, nListCur(0)
	, ptpObjIndex(NULL)
	, pObjIndex1(NULL)
	, pObjIndex2(NULL)
	, ptpViewIdx(NULL)
	, pViewIdx1(NULL)
	, pViewIdx2(NULL)
	, pCmpIdxAll1(NULL)
	, pCmpIdxAll2(NULL)
	, pCmpIdxAllg(NULL)
	, pCmpIdxLRE1(NULL)
	, pCmpIdxLRE2(NULL)
	, pCmpIdxLREg(NULL)
	, pCmpIdxLRN1(NULL)
	, pCmpIdxLRN2(NULL)
	, pCmpIdxLRNg(NULL)
	, pCmpIdxAnyE1(NULL)
	, pCmpIdxAnyE2(NULL)
	, pCmpIdxAnyEg(NULL)
	, pCmpIdxAllN1(NULL)
	, pCmpIdxAllN2(NULL)
	, pCmpIdxAllNg(NULL)
	, nOffsetVscroll(0)
	, ptnListMaxView(NULL)
	, nListMaxView1(0)
	, nListMaxView2(0)
	, nListMaxAll(0)
	, bSortUPEqual(FALSE)
	, nSelItem(0)
	, nSelSubItem(0)
	, nSelList(0)
	, strloglistn(_T(""))
	, nListCopyfrom(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


int CFileCompareDevil2Dlg::ReleaseList(int nlist)
{
	
	if ( nlist == 1 )
	{
		//m_dlg_logaction.AddLog(LOG_RELEASE, _T("list 1"), _T(""));
		if(m_pRoot1 != NULL)
		{
			delete m_pRoot1;
		}
		m_pRoot1 = NULL;
		if (pObjIndex1 != NULL)
		{
			delete[] pObjIndex1;	
		}
		pObjIndex1 = NULL;
		if (pViewIdx1 != NULL)
		{
			delete[] pViewIdx1;	
		}
		pViewIdx1 = NULL;
		m_FileList1.clear();
	}
	else if ( nlist == 2 )
	{
		//m_dlg_logaction.AddLog(LOG_RELEASE, _T("list 2"), _T(""));
		if(m_pRoot2 != NULL)
		{
			delete m_pRoot2;	
		}
		m_pRoot2 = NULL;
		if (pObjIndex2 != NULL)
		{
			delete[] pObjIndex2;	
		}
		pObjIndex2 = NULL;
		if (pViewIdx2 != NULL)
		{
			delete[] pViewIdx2;	
		}
		pViewIdx2 = NULL;
		m_FileList2.clear();
	}
	if ( bCompared )
	{
		//m_dlg_logaction.AddLog(LOG_RELEASE, _T("compare list"), _T(""));
		if (pCmpIdxAll1 != NULL)
		{
			delete[] pCmpIdxAll1;
		}
		pCmpIdxAll1 = NULL;
		if (pCmpIdxAll2 != NULL)
		{
			delete[] pCmpIdxAll2;
		}
		pCmpIdxAll2 = NULL;
		if (pCmpIdxAllg != NULL)
		{
			delete[] pCmpIdxAllg;
		}
		pCmpIdxAllg = NULL;
	}
	return 0;
}

CFileCompareDevil2Dlg::~CFileCompareDevil2Dlg()
{
	ReleaseList(1);
	ReleaseList(2);
	if (pObjIndex1 != NULL)
	{
		delete[] pObjIndex1;
		pObjIndex1 = NULL;
	}
	if (pObjIndex2 != NULL)
	{
		delete[] pObjIndex2;
		pObjIndex2 = NULL;
	}
	// 	if (pObjIndexEqual != NULL)
	// 	{
	// 		delete[] pObjIndexEqual;
	// 		pObjIndexEqual = NULL;
	// 	}
	// 	if (pObjIndex1Compared != NULL)
	// 	{
	// 		delete[] pObjIndex1Compared;
	// 		pObjIndex1Compared = NULL;
	// 	}
	// 	if (pObjIndex2Compared != NULL)
	// 	{
	// 		delete[] pObjIndex2Compared;
	// 		pObjIndex2Compared = NULL;
	// 	}
}
void CFileCompareDevil2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_maintab);
	DDX_Control(pDX, IDC_LIST_EQUAL, m_list_equal);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_EDIT_RENAME, m_rename);
}

BEGIN_MESSAGE_MAP(CFileCompareDevil2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CFileCompareDevil2Dlg::OnBnClickedBtnRefresh)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CFileCompareDevil2Dlg::OnTcnSelchangeTab1)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST1, &CFileCompareDevil2Dlg::OnLvnGetdispinfoList1)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST2, &CFileCompareDevil2Dlg::OnLvnGetdispinfoList2)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CFileCompareDevil2Dlg::OnLvnColumnclickList1)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST2, &CFileCompareDevil2Dlg::OnLvnColumnclickList2)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CFileCompareDevil2Dlg::OnNMClickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CFileCompareDevil2Dlg::OnNMClickList2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CFileCompareDevil2Dlg::OnNMDblclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CFileCompareDevil2Dlg::OnNMDblclkList2)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, &CFileCompareDevil2Dlg::OnLvnKeydownList1)	
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST2, &CFileCompareDevil2Dlg::OnLvnKeydownList2)
	ON_BN_CLICKED(IDC_BTN_SAVE1, &CFileCompareDevil2Dlg::OnBnClickedBtnSave1)
	ON_BN_CLICKED(IDC_BTN_SAVE2, &CFileCompareDevil2Dlg::OnBnClickedBtnSave2)
	ON_BN_CLICKED(IDC_BTN_OPEN1, &CFileCompareDevil2Dlg::OnBnClickedBtnOpen1)
	ON_BN_CLICKED(IDC_BTN_OPEN2, &CFileCompareDevil2Dlg::OnBnClickedBtnOpen2)
	ON_BN_CLICKED(IDC_BTN_EXPORT1, &CFileCompareDevil2Dlg::OnBnClickedBtnExport1)
	ON_BN_CLICKED(IDC_BTN_EXPORT2, &CFileCompareDevil2Dlg::OnBnClickedBtnExport2)
	ON_BN_CLICKED(IDC_BTN_EQUAL, &CFileCompareDevil2Dlg::OnBnClickedBtnEqual)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CFileCompareDevil2Dlg::OnNMRClickList1)
	ON_COMMAND(ID_LIST_COPY, &CFileCompareDevil2Dlg::OnListCopy)
	ON_COMMAND(ID_LIST_CUT, &CFileCompareDevil2Dlg::OnListCut)
	ON_COMMAND(ID_LIST_PASTE, &CFileCompareDevil2Dlg::OnListPaste)
	ON_COMMAND(ID_LIST_DELETE, &CFileCompareDevil2Dlg::OnListDelete)
	ON_COMMAND(ID_LIST_IGNORE, &CFileCompareDevil2Dlg::OnListIgnore)
	ON_COMMAND(ID_LIST_RENAME, &CFileCompareDevil2Dlg::OnListRename)
	ON_COMMAND(ID_LIST_SELECT, &CFileCompareDevil2Dlg::OnListSelect)
	ON_COMMAND(ID_LIST_SELECTALL, &CFileCompareDevil2Dlg::OnListSelectall)
	ON_COMMAND(ID_LIST_SELECTINVERT, &CFileCompareDevil2Dlg::OnListSelectinvert)
	ON_COMMAND(ID_LIST_EXPAND, &CFileCompareDevil2Dlg::OnListExpand)
	ON_COMMAND(ID_LIST_FOLD, &CFileCompareDevil2Dlg::OnListFold)
	ON_COMMAND(ID_LIST_EXPANDALL, &CFileCompareDevil2Dlg::OnListExpandall)
	ON_COMMAND(ID_LIST_FOLDALL, &CFileCompareDevil2Dlg::OnListFoldall)
	ON_COMMAND(ID_LIST_REFLASH, &CFileCompareDevil2Dlg::OnListReflash)
	ON_COMMAND(ID_LIST_PROPERTY, &CFileCompareDevil2Dlg::OnListProperty)
	ON_COMMAND(ID_LIST_COPYPATH, &CFileCompareDevil2Dlg::OnListCopypath)
	ON_COMMAND(ID_LIST_OPENCONTAINS, &CFileCompareDevil2Dlg::OnListOpencontains)
	ON_BN_CLICKED(IDC_BTN_LOGACTION, &CFileCompareDevil2Dlg::OnBnClickedBtnLogaction)
	ON_BN_CLICKED(IDC_BTN_LOGACTION2, &CFileCompareDevil2Dlg::OnBnClickedBtnLogaction2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &CFileCompareDevil2Dlg::OnNMRClickList2)
	ON_COMMAND(ID_LIST_HIDEDIR, &CFileCompareDevil2Dlg::OnListHidedir)
	ON_COMMAND(ID_LIST_EXPANDSON, &CFileCompareDevil2Dlg::OnListExpandson)
	ON_COMMAND(ID_LIST_FOLDSON, &CFileCompareDevil2Dlg::OnListFoldson)
	ON_COMMAND(ID_LIST_IGNORESEL, &CFileCompareDevil2Dlg::OnListIgnoresel)
	ON_MESSAGE(WM_MYLIST_KILLFOCUS, OnMylistKillfocus)
	ON_EN_KILLFOCUS(IDC_EDIT_RENAME, &CFileCompareDevil2Dlg::OnEnKillfocusEditRename)
	ON_COMMAND(ID_LIST_MKDIR, &CFileCompareDevil2Dlg::OnListMkdir)
END_MESSAGE_MAP()

//------- 控制台窗口，使用printf调试 S --------
#include <io.h>
#include <fcntl.h>
void InitConsoleWindow()
{
	int nCrt = 0;
	FILE* fp;
	AllocConsole();
	nCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	fp = _fdopen(nCrt, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("----------------printf debug-------------\n");
}
//------- 控制台窗口，使用printf调试 E --------

// CFileCompareDevil2Dlg 消息处理程序

BOOL CFileCompareDevil2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//InitConsoleWindow();//初始化控制台，使用printf调试

	m_maintab.InsertItem(0,L"文件列表");  //添加参数一选项卡
	m_maintab.InsertItem(1,L"过滤器");  //添加参数二选项卡
	m_maintab.InsertItem(2,L"对比选项");    //添加结果选项卡 
	m_maintab.SetCurSel(0);
	
	m_dlg_filelist.Create(IDD_DIALOG_FILELIST,GetDlgItem(IDC_TAB1)); 
	m_dlg_filter.Create(IDD_DIALOG_FILTER,GetDlgItem(IDC_TAB1)); 
	m_dlg_compare.Create(IDD_DIALOG_COMPARE,GetDlgItem(IDC_TAB1)); 
 	m_dlg_logaction.Create(IDD_DIALOG_LOG,GetDesktopWindow()); 
	//m_dlg_logaction.SetWindowPos()
	//	vSetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
 	//m_dlg_logaction.bLog = true;
 	//m_dlg_logaction.ShowWindow(SW_SHOW);


	CRect rsTab;
	m_maintab.GetClientRect(&rsTab);
	//调整子对话框在父窗口中的位置
	rsTab.top+=25; 
	rsTab.bottom-=5; 
	rsTab.left+=5; 
	rsTab.right-=5;
	m_dlg_filelist.MoveWindow(&rsTab);
	m_dlg_filter.MoveWindow(&rsTab);
	m_dlg_compare.MoveWindow(&rsTab);
	
	m_dlg_filelist.ShowWindow(SW_SHOW);
	m_dlg_filter.ShowWindow(SW_HIDE);
	m_dlg_compare.ShowWindow(SW_HIDE);
	
 
	m_list_equal.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_equal.InsertColumn( 0,         _T("?="),       LVCFMT_RIGHT, 30);

	m_list1.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_OWNERDATA|LVS_EX_CHECKBOXES);
	m_list2.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_OWNERDATA|LVS_EX_CHECKBOXES);
	for (int i=0; i<LIST_MAX; i++)
	{
		m_list1.InsertColumn( objListTitle[i].nIndex, objListTitle[i].sTitle, objListTitle[i].nAlign, objListTitle[i].nWidth);
		m_list2.InsertColumn( objListTitle[i].nIndex, objListTitle[i].sTitle, objListTitle[i].nAlign, objListTitle[i].nWidth);
	}
	m_list1.SetItemCount(nListMax1);
	m_list1.nTree = LIST_TREE;
	m_list2.SetItemCount(nListMax2);
	m_list2.nTree = LIST_TREE;

	//加载图标
	m_imgState.Create(IDB_BITMAP_CHECKBOX,16, 1, RGB(255,255,255));
	m_list1.SetImageList(&m_imgState,TVSIL_STATE);
	m_list2.SetImageList(&m_imgState,TVSIL_STATE);

	m_imagelist.Create(16, 16, TRUE|ILC_COLOR32, 0, 0);
	//HICON hIconNull = (HICON)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_NULL), IMAGE_ICON, 16, 16, 0);
	m_imagelist.Add(LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON_NULL)));//0
	m_imagelist.Add(LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON_CLOSE)));//1 "-"
	m_imagelist.Add(LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON_OPEN)));//2 "+"
	m_imagelist.Add(LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON_EQUAL)));//3 "="
	m_imagelist.Add(LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON_NOTEQUAL)));//4 "!="
	m_imagelist.Add(LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON_DELETED)));//5 "0/"
	m_imagelist.Add(LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON_LINE)));//6 "|"
	m_imagelist.Add(LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON_END)));//7 "└"
	m_imagelist.Add(LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON_TREE)));//8 "├"
	m_imagelist.Add(LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON_ONE)));//9 "─"
	m_list1.SetImageList(&m_imagelist,LVSIL_SMALL);
	m_list2.SetImageList(&m_imagelist,LVSIL_SMALL);
	m_list_equal.SetImageList(&m_imagelist,LVSIL_SMALL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFileCompareDevil2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFileCompareDevil2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFileCompareDevil2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFileCompareDevil2Dlg::OnBnClickedBtnRefresh()
{
	
}

void CFileCompareDevil2Dlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	int CurSel = m_maintab.GetCurSel();
	m_dlg_filelist.ShowWindow(SW_HIDE);
	m_dlg_filter.ShowWindow(SW_HIDE);
	m_dlg_compare.ShowWindow(SW_HIDE);
	switch(CurSel)
	{
	case 0:
		m_dlg_logaction.AddLog(LOG_CHANGETAB, _T("filelist tab"));
		m_dlg_filelist.ShowWindow(SW_SHOW);
		break;
	case 1:
		m_dlg_logaction.AddLog(LOG_CHANGETAB, _T("filter tab"));
		m_dlg_filter.ShowWindow(SW_SHOW);
		break;
	case 2:
		m_dlg_logaction.AddLog(LOG_CHANGETAB, _T("compare tab"));
		m_dlg_compare.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}    

	*pResult = 0;
}

//根据操作的左/右边来设置临时变量
int CFileCompareDevil2Dlg::SetCurTmp(int nlist)
{
	if (nlist == 1)
	{
		strloglistn = _T("list 1");
		ptnListMax = &nListMax1;
		ptm_pRoot = &m_pRoot1;
		ptm_list_path = &m_dlg_filelist.m_list_path1;
		ptFileList = &m_FileList1;
		ptbSortUP = &bSortUP1;
		ptnSortBy = &nSortBy1;
		ptnListMaxView = &nListMaxView1;
		ptlist = &m_list1;
		ptpObjIndex = &pObjIndex1;
		ptpViewIdx = &pViewIdx1;
		
	}
	else if (nlist == 2)
	{
		strloglistn = _T("list 2");
		ptnListMax = &nListMax2;
		ptm_pRoot = &m_pRoot2;
		ptm_list_path = &m_dlg_filelist.m_list_path2;
		ptFileList = &m_FileList2;
		ptbSortUP = &bSortUP2;
		ptnSortBy = &nSortBy2;
		ptnListMaxView = &nListMaxView2;
		ptlist = &m_list2;
		ptpObjIndex = &pObjIndex2;
		ptpViewIdx = &pViewIdx2;
	}
	
	return 0;
}


//搜索路径下所有文件
void CFileCompareDevil2Dlg::FilelistGo(int nlist)
{
	SetCurTmp(nlist);
	m_dlg_logaction.AddLog(LOG_LIST, strloglistn);
	bCompared = FALSE;
	*ptnListMax = 0;
	m_dlg_logaction.AddLog(LOG_RELEASE, strloglistn);
	ReleaseList(nlist);
	(*ptm_pRoot) = new CFileInfo;
	(*ptm_pRoot)->szFilename = _T("");
	(*ptm_pRoot)->nlayers = 0;
	int nTotalPath = ptm_list_path->GetItemCount();
	for (int i=0; i<nTotalPath; i++)
	{
		if ( ptm_list_path->GetCheck(i) )
		{
			CFileInfo* ofileinfo = new CFileInfo;
			ofileinfo->pParent = (*ptm_pRoot);
			ofileinfo->dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
			ofileinfo->szFilename = ptm_list_path->GetItemText(i,FILELIST_PATH);
			ofileinfo->nlayers = 1;
			ofileinfo->nFileSize = SearchFiles(ofileinfo->nlayers+1, ofileinfo->szFilename, ofileinfo);
			(*ptm_pRoot)->children.push_back(ofileinfo);
		}
	}
	AddFileArray(nlist,(*ptm_pRoot),_T(""));
	//过滤-----------------------------------------------------------------
	FilterFiles((*ptm_pRoot));
	(*ptnListMax) = (*ptFileList).size();
	if ((*ptnListMax) < 1)
	{
		AfxMessageBox(_T("No Files!"));
		return;
	}
	if (*ptpObjIndex != NULL)
	{
		delete[] (*ptpObjIndex);
		*ptpObjIndex = NULL;
	}
	*ptpObjIndex = new int[(*ptnListMax)];
	for (int i=0;i<(*ptnListMax);i++)
	{
		(*ptpObjIndex)[i] = i;
	}
	*ptbSortUP = FALSE;
	*ptnSortBy = LIST_INDEX;
	UpdateViewIndex(nlist);
	SortFileList(nlist);
	UpdateListTitle(nlist);
	ptlist->SetItemCount(*ptnListMaxView);
	ptlist->RedrawItems(0, *ptnListMaxView-1);
}

void CFileCompareDevil2Dlg::FilelistGo1()
{
	FilelistGo(1);
}

//搜索右边路径下所有文件
void CFileCompareDevil2Dlg::FilelistGo2()
{
	FilelistGo(2);
}

void CFileCompareDevil2Dlg::OnBnClickedBtnEqual()
{
	m_dlg_logaction.AddLog(LOG_COMPARE, _T("list 1"), _T("list 2"));
	CompareFiles();
	//bCompared = TRUE;
	// 	bSortUP1 = TRUE;
	// 	bSortUP2 = TRUE;
	// 	bSortUPEqual = TRUE;
	// 	nSortBy1 = LIST_SIZE;
	// 	nSortBy2 = LIST_SIZE;
	// 	OnSort(1);
	// 	OnSort(2);
	// 	doFileCompare();
	// 	UpdateListTitle(1);
	// 	UpdateListTitle(2);
	// 	m_list1.SetItemCount(nListMaxCompared);
	// 	m_list2.SetItemCount(nListMaxCompared);
	// 	m_list1.RedrawItems(0,nListMaxCompared);
	// 	m_list2.RedrawItems(0,nListMaxCompared);
}

//通用文件信息列表显示函数
void CFileCompareDevil2Dlg::OnLvnGetdispinfoListCom(int nlist,NMHDR *pNMHDR, LRESULT *pResult)
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	CString szValue=L"";
	long nItem = pDispInfo->item.iItem;
	long nSubItem =  pDispInfo->item.iSubItem;

	//std::vector<FILELIST> *ptFileList;
	int nListMax;
	BOOL bSortUP;
	int *pObjIndex = NULL;
	CToolTipListCtrl tmpList;

	if (nlist == 1)
	{
		ptFileList = &(m_FileList1);
		ptlist = &m_list1;
		if ( bCompared )
		{
			pObjIndex = pCmpIdxAll1;
			bSortUP = bSortUPEqual;
			nListMax = nListMaxAll;
		}
		else
		{
			pObjIndex = pViewIdx1;
			bSortUP = bSortUP1;
			nListMax = nListMaxView1;
		}
	}
	else if (nlist == 2)
	{
		ptFileList = &(m_FileList2);
		ptlist = &m_list2;
		if ( bCompared )
		{
			pObjIndex = pCmpIdxAll2;
			bSortUP = bSortUPEqual;
			nListMax = nListMaxAll;
		}
		else
		{
			pObjIndex = pViewIdx2;
			bSortUP = bSortUP2;
			nListMax = nListMaxView2;
		}
	}
	if (nItem>=nListMax || nItem<0)
	{
		*pResult = 0;
		return;
	}
	long objIndex = bSortUP ? pObjIndex[ nItem ] : pObjIndex[ nListMax-1-nItem ];
	if (objIndex == -1)
	{
		*pResult = 0;
		return;
	}
	CString sSate;
	try
	{
		COLORREF clrTextBk = RGB(255, 255, 255);
		COLORREF clrText = RGB(0, 0, 0);
//		int nlayers = 0;
		switch(nSubItem)
		{
		case LIST_NO:
			szValue.Format(_T("%d"), nItem+1);
			//状态：0-正常，1-新增，2-待复制，3-待剪切，4-待删除，5-已复制，6-已剪切/已删除，7-重命名过；
			switch( (*ptFileList)[objIndex].pFileinfo->nSate )
			{
			case 0:
				clrTextBk = RGB(255, 255, 255);
				break;
			case 1:
				clrTextBk = RGB(179, 202, 101);
				break;
			case 2:
				clrTextBk = RGB(250, 205, 137);
				break;
			case 3:
				clrTextBk = RGB(241, 158, 194);
				break;
			case 4:
				clrTextBk = RGB(228, 0, 127);
				break;
			case 5:
				clrTextBk = RGB(255, 247, 153);
				break;
			case 6:
				clrTextBk = RGB(137, 137, 137);
				break;
			case 7:
				clrTextBk = RGB(0, 183, 238);
				clrText = RGB(255, 0, 0);
				break;

			default:
				clrTextBk = RGB(255,255,255);
				break;
			}
			ptlist->clrTextBk = clrTextBk;
			ptlist->clrText = clrText;
			break;
		case LIST_TREE:
			ptlist->nlayers = (*ptFileList)[objIndex].pFileinfo->nlayers;
			//szValue.Format(_T("%d,%s"), (*ptFileList)[objIndex].pFileinfo->nlayers,(*ptFileList)[objIndex].pFileinfo->szFilename);
			szValue.Format(_T("%s"), (*ptFileList)[objIndex].pFileinfo->szFilename);
			break;
		case LIST_INDEX:
			szValue.Format(_T("%d"), (*ptFileList)[objIndex].pFileinfo->nIndex);
			break;
		case LIST_SATE:
			{
				//状态：0-正常，1-新增，2-待复制，3-待剪切，4-待删除，5-已复制，6-已剪切/已删除，7-重命名过，8-已排除；
				switch( (*ptFileList)[objIndex].pFileinfo->nSate )
				{
				case 0:
					sSate = "0原始";
					break;
				case 1:
					sSate = "1新增";
					break;
				case 2:
					sSate = "2待复制";
					break;
				case 3:
					sSate = "3待剪切";
					break;
				case 4:
					sSate = "4待删除";
					break;
				case 5:
					sSate = "5已复制";
					break;
				case 6:
					sSate = "6已剪切/删除";
					break;
				case 7:
					sSate = "7已重命名";
					break;
				case 8:
					sSate = "8已排除";
					break;

				default:
					sSate = "-错误";
					break;
				}
			}
			szValue.Format(_T("%s"), sSate);
			break;
		case LIST_PATH:
			szValue.Format(_T("%s"), (*ptFileList)[objIndex].sFullPath);
			break;
		case LIST_NAME:
			szValue.Format(_T("%s"), (*ptFileList)[objIndex].pFileinfo->szFilename);
			break;
		case LIST_TYPE:
			szValue.Format(_T("%s"), (*ptFileList)[objIndex].pFileinfo->szFileType);
			break;
		case LIST_SIZE:
			szValue.Format(_T("%I64d"),(*ptFileList)[objIndex].pFileinfo->nFileSize);
			break;
		case LIST_CURDIRS:
			szValue.Format(_T("%d"), (*ptFileList)[objIndex].pFileinfo->nDirsCur);
			break;
		case LIST_CURFILES:
			szValue.Format(_T("%d"), (*ptFileList)[objIndex].pFileinfo->nFilesCur);
			break;
		case LIST_ALLDIR:
			szValue.Format(_T("%d"), (*ptFileList)[objIndex].pFileinfo->nDirsAll);
			break;
		case LIST_ALLFILES:
			szValue.Format(_T("%d"), (*ptFileList)[objIndex].pFileinfo->nFilesAll);
			break;
			// 		case LIST_:
			// 			szValue.Format(_T("%d"),(*ptFileList)[objIndex]->dwFileAttributes);
			// 			break;
		case LIST_READONLY:
			szValue = (*ptFileList)[objIndex].pFileinfo->bReadOnly ? _T("Y") : _T("N");
			break;
		case LIST_SYSTEM:
			szValue = (*ptFileList)[objIndex].pFileinfo->bSystem ? _T("Y") : _T("N");
			break;
		case LIST_HIDDEN:
			szValue = (*ptFileList)[objIndex].pFileinfo->bHidden ? _T("Y") : _T("N");
			break;
		case LIST_CREATE:
			szValue = FiletimeToString((*ptFileList)[objIndex].pFileinfo->ftCreationTime);
			break;
		case LIST_ACCESS:
			szValue = FiletimeToString((*ptFileList)[objIndex].pFileinfo->ftLastAccessTime);
			break;
		case LIST_WRITE:
			szValue = FiletimeToString((*ptFileList)[objIndex].pFileinfo->ftLastWriteTime);
			break;

		default:
			break;

		}

		if (pDispInfo->item.mask & LVIF_TEXT)
		{
			wcscpy (pDispInfo->item.pszText,szValue.GetString());
		}
		if (pDispInfo->item.mask & LVIF_IMAGE)
		{
			if ( (*ptFileList)[objIndex].pFileinfo->bDeleted )
			{
				pDispInfo->item.iImage = 5;//"0\"
			}
			else if ( (*ptFileList)[objIndex].pFileinfo->dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY )
			{
				if ( (*ptFileList)[objIndex].pFileinfo->bExpand )
				{
					pDispInfo->item.iImage = 1;//"-"
				}
				else
				{
					pDispInfo->item.iImage = 2;//"+"
				}
			}
			else
			{
				pDispInfo->item.iImage = 8;//""
				if ( (*ptFileList)[objIndex].pFileinfo->pParent != NULL)
				{
					if ( objIndex == (*ptFileList)[objIndex].pFileinfo->pParent->nIndex + (*ptFileList)[objIndex].pFileinfo->pParent->nDirsAll + (*ptFileList)[objIndex].pFileinfo->pParent->nFilesAll )
					{
						pDispInfo->item.iImage = 7;//"L"
					}
// 					else
// 					{
// 						pDispInfo->item.iImage = 0;//""
// 					}
				}
			}
			pDispInfo->item.mask |= LVIF_STATE;
			pDispInfo->item.stateMask = LVIS_STATEIMAGEMASK;
 			if ( (*ptFileList)[objIndex].pFileinfo->nChecked == 1 )
 			{
 				pDispInfo->item.state = INDEXTOSTATEIMAGEMASK(LVIS_SELECTED);//2-checkbox checked
 // 				if (nlist == 1)
 // 				{
 // 					m_list1.SetCheck(nItem);
 // 				}
 // 				else if (nlist == 2)
 // 				{
 // 					m_list2.SetCheck(nItem);
 // 				}
 			}
 			else if( (*ptFileList)[objIndex].pFileinfo->nChecked == 0 )
 			{
 				pDispInfo->item.state = INDEXTOSTATEIMAGEMASK(LVIS_FOCUSED);//1-unchecked
 			}
 			else if( (*ptFileList)[objIndex].pFileinfo->nChecked == 2 )
 			{
 				pDispInfo->item.state = INDEXTOSTATEIMAGEMASK(3);//greychecked
 			}
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

//显示左侧文件信息列表
void CFileCompareDevil2Dlg::OnLvnGetdispinfoList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	OnLvnGetdispinfoListCom(1, pNMHDR, pResult);
	*pResult = 0;
}
void CFileCompareDevil2Dlg::OnLvnGetdispinfoList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	//NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	OnLvnGetdispinfoListCom(2, pNMHDR, pResult);
	*pResult = 0;
}

//单击列表标题项（排序）
void CFileCompareDevil2Dlg::OnLvnColumnclickListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	SetCurTmp(nlist);
	NM_LISTVIEW*   pNMListView = (NM_LISTVIEW*)pNMHDR; 
	if ( pNMListView->iSubItem > LIST_NO && !bCompared )
	{
		if( pNMListView->iSubItem == *ptnSortBy )
		{
			*ptbSortUP = !(*ptbSortUP);//up or down
		}
		*ptnSortBy = pNMListView->iSubItem;
		CString ssort;
		ssort.Format(_T("%d,%s"), *ptnSortBy,objListTitle[*ptnSortBy].sTitle);
		m_dlg_logaction.AddLog(LOG_SORT, strloglistn, _T(""), ssort);
		SortFileList(nlist);
		UpdateListTitle(nlist);
		ptlist->RedrawItems( 0, *ptnListMaxView-1 );
	}
	*pResult = 0;
}

//单击列表标题项（排序）
void CFileCompareDevil2Dlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnLvnColumnclickListCom(1, pNMHDR, pResult);
}
void CFileCompareDevil2Dlg::OnLvnColumnclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnLvnColumnclickListCom(2, pNMHDR, pResult);
}


//单击列表项图标（折叠）
void CFileCompareDevil2Dlg::OnNMClickListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	SetCurTmp(nlist);
	NMLISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;
	int nSubItem = pNMListView->iSubItem;
	if (pNMListView->iSubItem == ptlist->nTree)
	{
		long objIndex = (*ptbSortUP) ? (*ptpViewIdx)[ nItem ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - nItem ];
		if (objIndex == -1)
		{
			*pResult = 0;
			return;
		}
		int nlayers = (*ptFileList)[objIndex].pFileinfo->nlayers;
		IMAGEINFO imageinfo0;
		IMAGEINFO imageinfo1;
		int wi=0;
		int wc=0;
		int h=0;
		CImageList* imglist;
		if( imglist = ptlist->GetImageList(LVSIL_SMALL) )//icon
		{
			if( imglist->GetImageInfo(6, &imageinfo0) )
			{
				wi =   imageinfo0.rcImage.right - imageinfo0.rcImage.left; 
			}
		}
		if( imglist = ptlist->GetImageList(LVSIL_STATE) )//checkbox
		{
			if( imglist->GetImageInfo(0, &imageinfo1) )
			{
				wc =   imageinfo1.rcImage.right - imageinfo1.rcImage.left; 
			}
		}
		CRect rect0;
		ptlist->GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect0 );
		LONG ptx = pNMListView->ptAction.x - rect0.left;//鼠标坐标相对于单元格坐标的距离
		if (ptx < wi *(nlayers-1) ) //折叠的左边
		{
		}
		else if (ptx < wi*(nlayers) ) //折叠
		{
			m_dlg_logaction.AddLog(LOG_EXPAND, strloglistn, _T(""), ptlist->GetItemText(pNMListView->iItem, LIST_PATH));
			ExpandCollapse(nlist, pNMListView->iItem);
		}
		else if (ptx < wi*(nlayers)+wc)//checkbox
		{
			m_dlg_logaction.AddLog(LOG_CHECKBOX, strloglistn, _T(""), ptlist->GetItemText(pNMListView->iItem, LIST_PATH));
			ToggleCheckBox(nlist,pNMListView->iItem);
		}
		else//文本
		{

		}

	}
	else
	{
		LVHITTESTINFO hitinfo;
		hitinfo.pt = pNMListView->ptAction;
		int item = ptlist->HitTest(&hitinfo);
		if(item != -1)
		{
			if( hitinfo.flags == LVHT_ONITEMSTATEICON ) //checkbox
			{
				m_dlg_logaction.AddLog(LOG_CHECKBOX, strloglistn, _T(""), ptlist->GetItemText(item, LIST_PATH));
				ToggleCheckBox(nlist,item);
			}
			else if ( hitinfo.flags == LVHT_ONITEMICON )//icon
			{
				m_dlg_logaction.AddLog(LOG_EXPAND, strloglistn, _T(""), ptlist->GetItemText(item, LIST_PATH));
				ExpandCollapse(nlist, item);
			}
		}
	}

	*pResult = 0;
}
//单击列表项图标（折叠）
void CFileCompareDevil2Dlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickListCom(1, pNMHDR, pResult);
}
void CFileCompareDevil2Dlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickListCom(2, pNMHDR, pResult);
}


//双击列表项（打开文件所在文件夹）
void CFileCompareDevil2Dlg::OnNMDblclkListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	SetCurTmp(nlist);
	NMLISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;
	if (nItem != -1)
	{
		CString sdir = ptlist->GetItemText(nItem,LIST_PATH);
		m_dlg_logaction.AddLog(LOG_EXPLORER, strloglistn, _T(""), sdir);
		CString sCmd = _T("explorer.exe /select,") + sdir;//打开并选中
		WinExec(CT2CA(sCmd), SW_SHOWNORMAL);
	}
	*pResult = 0;
}
void CFileCompareDevil2Dlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMDblclkListCom(1, pNMHDR, pResult);
}
void CFileCompareDevil2Dlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMDblclkListCom(2, pNMHDR, pResult);
}


//按空格键选中列表checkbox
void CFileCompareDevil2Dlg::OnLvnKeydownListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	SetCurTmp(nlist);
	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;

	if( pLVKeyDown->wVKey == VK_SPACE )
	{
		int item = ptlist->GetSelectionMark();
		if(item != -1)
		{
			m_dlg_logaction.AddLog(LOG_SPACE, strloglistn, _T(""), ptlist->GetItemText(item, LIST_PATH));
			ToggleCheckBox(nlist,item);
		}
	}
	*pResult = 0;
}
void CFileCompareDevil2Dlg::OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnLvnKeydownListCom(1, pNMHDR, pResult);
}
void CFileCompareDevil2Dlg::OnLvnKeydownList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnLvnKeydownListCom(2, pNMHDR, pResult);
}


CString CFileCompareDevil2Dlg::FiletimeToString(FILETIME ft)
{
	SYSTEMTIME stLocal;
	CString szValue;
	FileTimeToSystemTime(&ft, &stLocal);
	szValue.Format(_T("%.4d-%.2d-%.2d %.2d:%.2d:%.2d"), stLocal.wYear, stLocal.wMonth,stLocal.wDay, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
	return szValue;
}


void CFileCompareDevil2Dlg::BackupData(int nlist)
{
	SetCurTmp(nlist);
	CFileDialog dlg(0,_T("dat"),0,OFN_OVERWRITEPROMPT);
	if(dlg.DoModal()==IDCANCEL)
	{
		return;
	}
	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeReadWrite|CFile::modeCreate);
	CArchive ar(&file,CArchive::store);
	m_dlg_logaction.AddLog(LOG_SAVE, strloglistn, _T(""), dlg.GetPathName());
	(*ptm_pRoot)->Serialize(ar);
	ar.Close();
	file.Close();
}

//保存文件列表信息
void CFileCompareDevil2Dlg::OnBnClickedBtnSave1()
{
	BackupData(1);
}

void CFileCompareDevil2Dlg::OnBnClickedBtnSave2()
{
	BackupData(2);
}


int CFileCompareDevil2Dlg::LoadFileinfoData(int nlist)
{
	SetCurTmp(nlist);
	CFileDialog dlg(TRUE,_T("dat"));// TRUE for FileOpen, FALSE for FileSaveAs
	if(dlg.DoModal()==IDCANCEL)
	{
		return 1;
	}
	CFile file;
	if(!file.Open(dlg.GetPathName(), CFile::modeRead))
	{
		return 1;
	}
	CArchive ar(&file,CArchive::load);
	m_dlg_logaction.AddLog(LOG_RELEASE, _T("list load"), _T(""));
	ReleaseList(nlist);
	m_dlg_logaction.AddLog(LOG_LOAD, strloglistn, _T(""), dlg.GetPathName());
	*ptm_pRoot = new CFileInfo;
	(*ptm_pRoot)->Serialize(ar);
	ar.Close();
	file.Close();

	AddFileArray(nlist,(*ptm_pRoot),_T(""));
	*ptnListMax = ptFileList->size();
	if (*ptnListMax < 1)
	{
		AfxMessageBox(_T("No Files!"));
		return 1;
	}
	*ptpObjIndex = new int[*ptnListMax];
	for (int i=0;i<*ptnListMax;i++)
	{
		(*ptpObjIndex)[i] = i;
	}
	UpdateViewIndex(nlist);
	SortFileList(nlist);
	UpdateListTitle(nlist);
	ptlist->SetItemCount(*ptnListMaxView);
	ptlist->RedrawItems(0, *ptnListMaxView-1);
	return 0;
}

//导入备份的文件列表信息
void CFileCompareDevil2Dlg::OnBnClickedBtnOpen1()
{
	LoadFileinfoData(1);
}

void CFileCompareDevil2Dlg::OnBnClickedBtnOpen2()
{
	LoadFileinfoData(2);
}

//导出当前显示列表到html文件
int CFileCompareDevil2Dlg::Export(int nlist)
{
	SetCurTmp(nlist);
	CString filter_str = _T("html files (*.htm)|*.htm||");
	CFileDialog mSaveDlg(FALSE, _T("htm"), _T(""), NULL, filter_str, NULL);//初始化
	mSaveDlg.m_ofn.lpstrTitle = _T("保存为文本文件"); 
	if(mSaveDlg.DoModal()==IDCANCEL)
	{
		return 0;
	}
	m_dlg_logaction.AddLog(LOG_EXPORT, strloglistn, _T(""), mSaveDlg.GetPathName());
	long objIndex = 0;
	CString sOuttxt = mSaveDlg.GetPathName();
	CFile mFile;
	if (mFile.Open(sOuttxt,CFile::modeReadWrite|CFile::modeCreate))
	{
		int unicodeh=65279;//Unicode header：FF,FE
		mFile.Write(&unicodeh,2);
		CString sObjFile;
		sObjFile.Format(_T("<style>td{text-overflow:ellipsis;overflow:hidden;white-space:nowrap;padding:2px}\
						   </style><table border=\"1\"><tr><th>序号</th><th>文件路径</th><th>文件名</th><th>扩展名</th><th>大小</th><th>\
						   属性</th><th>创建时间</th><th>访问时间</th><th>修改时间</th><th>只读</th><th>系统</th><th>隐藏</th><th>当前文\
						   件数</th><th>当前文件数</th><th>子目录总数</th><th>子目录文件总数</th></tr>\r\n"));
		mFile.Write(sObjFile,sObjFile.GetLength()*2);
		for(int i=0;i<ptFileList->size();i++)
		{
			objIndex = (*ptbSortUP) ? (*ptpViewIdx)[ i ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - i ];
			//sObjFile.Format(L"%8d,%-256s,%-256s,%-20s,%15I64d,%8d,%25s,%25s,%25s,%d,%d,%d,%8d,%8d,%8d,%8d\r\n",
			sObjFile.Format(L"<tr><td align=\"right\">%d</td><td>%s</td><td>%s</td><td>%s</td><td align=\"right\">%I64d</td><td>%d</td>\
							 <td>%s</td><td>%s</td>\<td>%s</td><td>%d</td><td>%d</td><td>%d</td><td align=\"right\">%d</td>\
							 <td align=\"right\">%d</td><td align=\"right\">%d</td><td align=\"right\">%d</td></tr>\r\n",
							 (*ptFileList)[ objIndex ].pFileinfo->nIndex,
							 (*ptFileList)[ objIndex ].sFullPath,
							 (*ptFileList)[ objIndex ].pFileinfo->szFilename,
							 (*ptFileList)[ objIndex ].pFileinfo->szFileType,
							 (*ptFileList)[ objIndex ].pFileinfo->nFileSize,
							 (*ptFileList)[ objIndex ].pFileinfo->dwFileAttributes,
							 FiletimeToString((*ptFileList)[ objIndex ].pFileinfo->ftCreationTime),
							 FiletimeToString((*ptFileList)[ objIndex ].pFileinfo->ftLastAccessTime),
							 FiletimeToString((*ptFileList)[ objIndex ].pFileinfo->ftLastWriteTime),
							 (*ptFileList)[ objIndex ].pFileinfo->bReadOnly,
							 (*ptFileList)[ objIndex ].pFileinfo->bSystem,
							 (*ptFileList)[ objIndex ].pFileinfo->bHidden,
							 (*ptFileList)[ objIndex ].pFileinfo->nDirsCur,
							 (*ptFileList)[ objIndex ].pFileinfo->nFilesCur,
							 (*ptFileList)[ objIndex ].pFileinfo->nDirsAll,
							 (*ptFileList)[ objIndex ].pFileinfo->nFilesAll
							 );
			mFile.Write(sObjFile,sObjFile.GetLength()*2);
		}
		sObjFile.Format(_T("</table>"));
		mFile.Write(sObjFile,sObjFile.GetLength()*2);
		mFile.Close();
	}
	CString sCmd = _T("explorer.exe ") + sOuttxt;
	WinExec(CT2CA(sCmd), SW_SHOWNORMAL);
	return 0;
}

void CFileCompareDevil2Dlg::OnBnClickedBtnExport1()
{
	Export(1);
}

void CFileCompareDevil2Dlg::OnBnClickedBtnExport2()
{
	Export(2);
}
//// 目录包含项已经过滤，不会出现重复项
// BOOL CFileCompareDevil2Dlg::IsVectorItemExist(CString cFilename, CFileInfo* pParent)
// {
// 	for(int i=0; i<pParent->children.size(); i++)
// 	{
// 		if ( pParent->children[i]->szFilename.CompareNoCase(cFilename) == 0)
// 		{
// 			return TRUE;
// 		}
// 	}
// 	return FALSE;
// }

//递归遍历文件
ULONGLONG CFileCompareDevil2Dlg::SearchFiles(int nlayers, CString sPath, CFileInfo* pParent)
{
	ULONGLONG nFolderSize = 0;
	int nLastDot = -1;
	if( sPath.Right(1) != _T("\\") )
	{
		sPath += _T("\\");
	}
	WIN32_FIND_DATA fdata;
	HANDLE hfind = ::FindFirstFile( sPath + _T("*"), &fdata );
	if(hfind != INVALID_HANDLE_VALUE)
	{	
		do
		{
			if( fdata.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY )
			{
				if(_tccmp(fdata.cFileName,_T(".")) ==0 || _tccmp(fdata.cFileName,_T("..")) == 0)
				{
					continue;
				}
////目录包含项已经过滤，不会出现重复项
// 				if (  IsVectorItemExist(fdata.cFileName, pParent) )//如果已经存在则不添加
// 				{
// 					continue;
// 				}
				CFileInfo* pfile = new CFileInfo;
				pfile->pParent = pParent;
				pfile->szFileType = _T("");
				pfile->szFilename = fdata.cFileName;
				pfile->dwFileAttributes = fdata.dwFileAttributes;
				pfile->ftCreationTime = fdata.ftCreationTime;
				pfile->ftLastAccessTime = fdata.ftLastAccessTime;
				pfile->ftLastWriteTime = fdata.ftLastWriteTime;
				pfile->bReadOnly = fdata.dwFileAttributes&FILE_ATTRIBUTE_READONLY;
				pfile->bSystem = fdata.dwFileAttributes&FILE_ATTRIBUTE_SYSTEM;
				pfile->bHidden = fdata.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN;
				pfile->nSate = 0;//正常
				pfile->bIgnored = FALSE;
				pfile->nChecked = 0;
				pfile->bExpand = TRUE;
				pfile->nlayers = nlayers;
				pfile->nFileSize = SearchFiles(nlayers+1, sPath + fdata.cFileName, pfile );
				pParent->children.push_back( pfile );
				//pParent->nDirsCur ++;
				//pParent->nDirsAll ++;
				nFolderSize += pfile->nFileSize;
			}
			else
			{
////目录包含项已经过滤，不会出现重复项
// 				if (  IsVectorItemExist(fdata.cFileName, pParent) )//如果已经存在则不添加
// 				{
// 					continue;
// 				}
				CFileInfo* pfile = new CFileInfo;
				pfile->pParent = pParent;
				pfile->szFilename = fdata.cFileName;
				nLastDot = pfile->szFilename.ReverseFind('.');
				if (nLastDot != -1)
				{
					pfile->szFileType = pfile->szFilename.Mid(nLastDot);
				}
				pfile->nFileSize = ((ULONGLONG)fdata.nFileSizeHigh << 32) + fdata.nFileSizeLow;
				pfile->dwFileAttributes = fdata.dwFileAttributes;
				pfile->ftCreationTime = fdata.ftCreationTime;
				pfile->ftLastAccessTime = fdata.ftLastAccessTime;
				pfile->ftLastWriteTime = fdata.ftLastWriteTime;
				pfile->bReadOnly = fdata.dwFileAttributes&FILE_ATTRIBUTE_READONLY;
				pfile->bSystem = fdata.dwFileAttributes&FILE_ATTRIBUTE_SYSTEM;
				pfile->bHidden = fdata.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN;
				pfile->nSate = 0;//正常
				pfile->bIgnored = FALSE;
				pfile->nChecked = 0;
				pfile->bExpand = TRUE;
				pfile->nlayers = nlayers;
				pParent->children.push_back( pfile );
				//pParent->nFilesCur ++;
				//pParent->nFilesAll ++;
				nFolderSize += pfile->nFileSize;
			}		
		}while(FindNextFile(hfind,&fdata));

		FindClose(hfind);
	}
	return nFolderSize;
}

//多层树形结构转换成单层数组列表结构
int CFileCompareDevil2Dlg::AddFileArray(int nlist, CFileInfo* pFileInfo, CString sPath)
{
	pFileInfo->nFilesCur = 0;
	pFileInfo->nDirsCur = 0;
	pFileInfo->nDirsAll = 0;
	pFileInfo->nFilesAll = 0;
	if( pFileInfo->pParent != NULL)
	{
		FILELIST fl;
		if( sPath.IsEmpty() )
		{
			fl.sFullPath = pFileInfo->szFilename;
		}
		else
		{
			if( sPath.Right(1) != _T("\\") )
			{
				sPath += _T("\\");
			}
			fl.sFullPath = sPath + pFileInfo->szFilename;
		}
		fl.pFileinfo = pFileInfo;
		if (nlist == 1)
		{
			fl.pFileinfo->nIndex = m_FileList1.size();
			m_FileList1.push_back(fl);
		}
		else if (nlist == 2)
		{
			fl.pFileinfo->nIndex = m_FileList2.size();
			m_FileList2.push_back(fl);
		}
		pFileInfo->nlayers = pFileInfo->pParent->nlayers+1;
	}

	for(int i=0; i<pFileInfo->children.size(); i++)
	{
		if (pFileInfo->children[i]->dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			pFileInfo->nDirsCur ++;
		}
		if(sPath.IsEmpty())
		{
			AddFileArray(nlist,pFileInfo->children[i],pFileInfo->szFilename);
		}
		else
		{
			if( sPath.Right(1) != _T("\\") )
			{
				sPath += _T("\\");
			}
			AddFileArray(nlist,pFileInfo->children[i], sPath + pFileInfo->szFilename);
		}
		pFileInfo->nDirsAll += pFileInfo->children[i]->nDirsAll;
		pFileInfo->nFilesAll += pFileInfo->children[i]->nFilesAll;
	}
	pFileInfo->nFilesCur = pFileInfo->children.size() - pFileInfo->nDirsCur;
	pFileInfo->nDirsAll += pFileInfo->nDirsCur;
	pFileInfo->nFilesAll += pFileInfo->nFilesCur;


	return 0;
}

//更新排序后的标题栏
int CFileCompareDevil2Dlg::UpdateListTitle(int nlist)
{
	SetCurTmp(nlist);
	m_dlg_logaction.AddLog(LOG_TITLE, strloglistn, _T(""), objListTitle[*ptnSortBy].sTitle);

	LVCOLUMN column; 
	column.mask = LVCF_TEXT;
	CString sTitle;
	for (int i=0;i<LIST_MAX;i++)
	{
		sTitle = objListTitle[i].sTitle;
		if (*ptnSortBy == i)
		{
			sTitle += (*ptbSortUP) ? _T("▼") : _T("▲");//△▽
		}
		column.pszText = sTitle.GetBuffer(); 
		ptlist->SetColumn(i,&column);
	}
	return 0;
}

//快速排序回调函数
int cmpObj (void *pIn, const void *x, const void *y)
{
	int *pNodex = (int*)x, *pNodey = (int*)y;
	CFileCompareDevil2Dlg *pdlg = (CFileCompareDevil2Dlg*)pIn;
	std::vector<FILELIST> *ptFileList;
	int nSortBy;
	if (pdlg->nListCur == 1)
	{
		ptFileList = &(pdlg->m_FileList1);
		nSortBy = pdlg->nSortBy1;
	}
	else if (pdlg->nListCur == 2)
	{
		ptFileList = &(pdlg->m_FileList2);
		nSortBy = pdlg->nSortBy2;
	}

	int nRet = 1;
	switch(nSortBy)
	{
	case LIST_NO:
	case LIST_INDEX:
		nRet = (*ptFileList)[*pNodey].pFileinfo->nIndex > (*ptFileList)[*pNodex].pFileinfo->nIndex ? 1 : -1;
		break;
	case LIST_SATE:
		nRet = (*ptFileList)[*pNodey].pFileinfo->nSate > (*ptFileList)[*pNodex].pFileinfo->nSate ? 1 : -1;
		break;
	case LIST_PATH:
		nRet = (*ptFileList)[*pNodey].sFullPath.CompareNoCase( (*ptFileList)[*pNodex].sFullPath );
		break;
	case LIST_NAME:
		nRet = (*ptFileList)[*pNodey].pFileinfo->szFilename.CompareNoCase( (*ptFileList)[*pNodex].pFileinfo->szFilename );
		break;
	case LIST_TYPE:
		nRet = (*ptFileList)[*pNodey].pFileinfo->szFileType.CompareNoCase( (*ptFileList)[*pNodex].pFileinfo->szFileType );
		break;
	case LIST_SIZE:
		nRet = (*ptFileList)[*pNodey].pFileinfo->nFileSize > (*ptFileList)[*pNodex].pFileinfo->nFileSize ? 1 : -1;
		break;
	case LIST_CURDIRS:
		nRet = (*ptFileList)[*pNodey].pFileinfo->nDirsCur > (*ptFileList)[*pNodex].pFileinfo->nDirsCur ? 1 : -1;
		break;
	case LIST_CURFILES:
		nRet = (*ptFileList)[*pNodey].pFileinfo->nFilesCur > (*ptFileList)[*pNodex].pFileinfo->nFilesCur ? 1 : -1;
		break;
	case LIST_ALLDIR:
		nRet = (*ptFileList)[*pNodey].pFileinfo->nDirsAll > (*ptFileList)[*pNodex].pFileinfo->nDirsAll ? 1 : -1;
		break;
	case LIST_ALLFILES:
		nRet = (*ptFileList)[*pNodey].pFileinfo->nFilesAll > (*ptFileList)[*pNodex].pFileinfo->nFilesAll ? 1 : -1;
		break;
	case LIST_READONLY:
		nRet = (*ptFileList)[*pNodey].pFileinfo->bReadOnly > (*ptFileList)[*pNodex].pFileinfo->bReadOnly ? 1 : -1;
		break;
	case LIST_SYSTEM:
		nRet = (*ptFileList)[*pNodey].pFileinfo->bSystem > (*ptFileList)[*pNodex].pFileinfo->bSystem ? 1 : -1;
		break;
	case LIST_HIDDEN:
		nRet = (*ptFileList)[*pNodey].pFileinfo->bHidden > (*ptFileList)[*pNodex].pFileinfo->bHidden ? 1 : -1;
		break;
	case LIST_CREATE:
		nRet = CompareFileTime(&(*ptFileList)[*pNodey].pFileinfo->ftCreationTime, &(*ptFileList)[*pNodex].pFileinfo->ftCreationTime);
		break;
	case LIST_ACCESS:
		nRet = CompareFileTime(&(*ptFileList)[*pNodey].pFileinfo->ftLastAccessTime, &(*ptFileList)[*pNodex].pFileinfo->ftLastAccessTime);
		break;
	case LIST_WRITE:
		nRet = CompareFileTime(&(*ptFileList)[*pNodey].pFileinfo->ftLastWriteTime, &(*ptFileList)[*pNodex].pFileinfo->ftLastWriteTime);
		break;
	default:
		break;
	}
	return nRet;
}
//排序
int CFileCompareDevil2Dlg::SortFileList(int nlist)
{
	SetCurTmp(nlist);
	m_dlg_logaction.AddLog(LOG_SORT, strloglistn);
	nListCur = nlist;
	qsort_s(*ptpViewIdx, *ptnListMaxView, sizeof(int), cmpObj,this);
	ptlist->RedrawItems(0,*ptnListMaxView-1);
	return 0;
}
//锁定2个列表同时滚动
void CFileCompareDevil2Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if ( m_dlg_compare.m_ckLockVscroll.GetCheck() )
	{
		switch( pScrollBar->GetDlgCtrlID() )
		{
			//Slider1
		case IDC_LIST1:
			{
				//m_list2.GetTopIndex()
				//	CPoint pt;
				//m_list1.GetItemPosition(nPos,&pt);
				//m_list2.GetScrollBarCtrl(SB_VERT)->SetScrollPos(nPos);
				//SB_THUMBTRACK
				//if ( m_list2.IsItemVisible(nPos) )
				int nPos1 = m_list1.GetScrollPos(SB_VERT);
				{
					m_list2.EnsureVisible(nPos1 + m_list2.GetCountPerPage()-1 + nOffsetVscroll, FALSE);
				}
				//else
				{
					m_list2.EnsureVisible(nPos1 + nOffsetVscroll, FALSE);
				}
				//m_list2.SetScrollPos(SB_VERT,nPos);
				//wprintf(L"%d\n",nSBCode);
				// 			SCROLLINFO oscrollinfo;
				// 			m_list1.GetScrollInfo(SB_VERT,&oscrollinfo);
				// 			m_list2.SetScrollInfo(SB_VERT,&oscrollinfo);
				//m_list2.Scroll(CSize(0,nPos));
				//m_list2.RedrawItems(0,m_list2.GetItemCount()-1);
				//	::SendMessage(m_list2.m_hWnd,WM_VSCROLL,MAKELONG(SB_THUMBTRACK,nPos),(LPARAM)m_list2.m_hWnd);
				m_list2.SetScrollPos(SB_VERT, nPos1 + nOffsetVscroll);
			}
			break;
			//Slider2
		case IDC_LIST2:
			{
				int nPos2 = m_list2.GetScrollPos(SB_VERT);
				m_list1.EnsureVisible(nPos2 + m_list1.GetCountPerPage()-1 - nOffsetVscroll, FALSE);
				m_list1.EnsureVisible(nPos2 - nOffsetVscroll, FALSE);
				m_list1.SetScrollPos(SB_VERT, nPos2 - nOffsetVscroll);
				break;
			}

		}
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
//点击列表项的checkbox
int CFileCompareDevil2Dlg::ToggleCheckBox(int nlist,int nItem)
{
	SetCurTmp(nlist);
	if (nItem>=*ptnListMaxView || nItem<0)
	{
		return 0;
	}
	long objIndex = (*ptbSortUP) ? (*ptpViewIdx)[nItem] : (*ptpViewIdx)[*ptnListMaxView-1-nItem];
	(*ptFileList)[objIndex].pFileinfo->nChecked = (*ptFileList)[objIndex].pFileinfo->nChecked==0 ? 1 : 0;
	for (int i=0; i<((*ptFileList)[objIndex].pFileinfo->nFilesAll + (*ptFileList)[objIndex].pFileinfo->nDirsAll); i++)
	{
		(*ptFileList)[objIndex+i+1].pFileinfo->nChecked = (*ptFileList)[objIndex].pFileinfo->nChecked;
	}
	CFileInfo* pParent = (*ptFileList)[objIndex].pFileinfo->pParent;
	while( pParent != NULL )
	{
		int ncount0 = 0;
		int ncount1 = 0;
		for(int i=0;i<pParent->children.size();i++)
		{
			if ( pParent->children[i]->nChecked == 0 )
			{
				ncount0 ++;
			}
			else if ( pParent->children[i]->nChecked == 1 )
			{
				ncount1 ++;
			}
			else //if ( pParent->children[i]->nChecked == 2 )
			{
				pParent->nChecked = 2;//greychecked
				break;
			}
		}
		if (ncount1 == pParent->children.size())
		{
			pParent->nChecked = 1;//checked
		}
		else if (ncount0 == pParent->children.size())
		{
			pParent->nChecked = 0;//unchecked
		}
		else
		{
			pParent->nChecked = 2;//greychecked
		}
		pParent = pParent->pParent;
	}
// 	UpdateViewIndex(nlist);
// 	SortFileList(nlist);
// 	UpdateListTitle(nlist);
	ptlist->SetItemCount(*ptnListMaxView);
	ptlist->RedrawItems(0,*ptnListMaxView-1);
	return 0;
}
//点击锁定滚动checkbox
void CFileCompareDevil2Dlg::OnBnClickedCkLockVscroll()
{
	if ( m_dlg_compare.m_ckLockVscroll.GetCheck() )
	{
		nOffsetVscroll = m_list2.GetScrollPos(SB_VERT) - m_list1.GetScrollPos(SB_VERT);
	}
	else
	{
		nOffsetVscroll = 0;
	}
}

int CFileCompareDevil2Dlg::ExpandCollapse(int nlist, int nItem)
{
	//m_dlg_logaction.AddLog(LOG_EXPAND, _T("list 1"), _T(""), m_list1.GetItemText(item, LIST_PATH));
	SetCurTmp(nlist);
	if (nItem>=*ptnListMaxView || nItem<0)
	{
		return 0;
	}
	long objIndex = (*ptbSortUP) ? (*ptpViewIdx)[nItem] : (*ptpViewIdx)[*ptnListMaxView-1-nItem];
	(*ptFileList)[objIndex].pFileinfo->bExpand = !(*ptFileList)[objIndex].pFileinfo->bExpand;
	//for (int i=0; i<((*ptFileList)[objIndex]->nFilesAll + (*ptFileList)[objIndex]->nDirsAll); i++)
	//{
	//	//(*ptFileList)[objIndex+i+1]->bExpand = (*ptFileList)[objIndex]->bExpand;
	//	(*ptFileList)[objIndex+i+1]->bVisible = (*ptFileList)[objIndex]->bExpand;
	//}
 	UpdateViewIndex(nlist);
 	SortFileList(nlist);
 	UpdateListTitle(nlist);
	ptlist->SetItemCount(*ptnListMaxView);
	ptlist->RedrawItems(0,*ptnListMaxView-1);
	return 0;
}

int CFileCompareDevil2Dlg::UpdateViewIndex(int nlist)
{
	SetCurTmp(nlist);
	m_dlg_logaction.AddLog(LOG_VIEWINDEX, strloglistn);
	// 	if (bCompared == TRUE)
	// 	{
	// 		return 0;
	// 	}

		// 		if (bCompared == TRUE)
		// 		{
		// 			pObjIndex = pCmpIdxAll2;
		// 			nListMax = nListMaxAll;
		// 		}
		// 		else

	if ( (*ptpViewIdx) != NULL )
	{
		delete[] (*ptpViewIdx);
	}
	(*ptpViewIdx) = new int[*ptnListMax];

	*ptnListMaxView = 0;
	for (int i=0;i<*ptnListMax;i++)
	{
		//父目录折叠或者父目录隐藏则隐藏
		(*ptFileList)[ i ].pFileinfo->bVisible = (*ptFileList)[ i ].pFileinfo->pParent->bExpand && (*ptFileList)[ i ].pFileinfo->pParent->bVisible;

		//父目录被排除则不显示
		if ( (*ptFileList)[ i ].pFileinfo->pParent->bIgnored )
		{
			(*ptFileList)[ i ].pFileinfo->bIgnored = TRUE;
			(*ptFileList)[ i ].pFileinfo->nSate = 8;//已排除
		}

		//已删除的、主动隐藏、主动忽略的不计数
		if ( !(*ptFileList)[ i ].pFileinfo->bDeleted && (*ptFileList)[ i ].pFileinfo->bVisible && !(*ptFileList)[ i ].pFileinfo->bIgnored )
		{
			(*ptpViewIdx)[*ptnListMaxView] = (*ptpObjIndex)[i];
			(*ptnListMaxView) ++;
		}
	}
	return 0;
}

int CFileCompareDevil2Dlg::CompareFiles()
{
	//m_dlg_logaction.AddLog(LOG_COMPARE, _T("list 1"), _T("list 2"));
	bSortUP1 = FALSE;
	bSortUP2 = FALSE;
	bSortUPEqual = FALSE;
	nSortBy1 = LIST_SIZE;
	nSortBy2 = LIST_SIZE;

	UpdateViewIndex(1);
	UpdateViewIndex(2);
	SortFileList(1);
	SortFileList(2);
	int nTotal = nListMaxView1 + nListMaxView2;

	int* pALLA = pCmpIdxAll1;
	int* pALLB = pCmpIdxAll2;
	int* pALLg = pCmpIdxAllg;
	if ( pALLA != NULL )
	{
		delete[] pALLA;
	}
	pALLA = new int[ nTotal ];
	if ( pALLB != NULL )
	{
		delete[] pALLB;
	}
	pALLB = new int[ nTotal ];
	if ( pALLg != NULL )
	{
		delete[] pALLg;
	}
	pALLg = new int[ nTotal ];

	int i=0;
	int j=0;
	int g=0;
	bool a2a1=0;//a[i]==a[i-1] //同侧相邻2个是否相同
	bool b2b1=0;//b[j]==b[j-1]
	int nCount=0;
	int nCmp=0;
	for(int k=0; k<nTotal; k++)
	{
		if (i>0 && i<nListMaxView1)
		{
			a2a1 = (IsFilesEquals(&m_FileList1[ pViewIdx1[nListMaxView1 - i -1] ],&m_FileList1[ pViewIdx1[nListMaxView1 - 1 - i-1] ]) == 0);
		}
		else
		{
			a2a1 = false;
		}
		if (j>0 && j<nListMaxView2)
		{
			b2b1 = (IsFilesEquals(&m_FileList2[ pViewIdx2[nListMaxView2 -1-j] ],&m_FileList2[ pViewIdx2[nListMaxView2-1-j-1] ]) == 0);
		}
		else
		{
			b2b1 = false;
		}
		if (i>0 || j>0)
		{
			if ( !(a2a1 || b2b1) )
			{
				g++;
			}
		}
		pALLg[k] = g;
		if (i<nListMaxView1 && j<nListMaxView2)
		{
			nCmp = IsFilesEquals(&m_FileList1[ pViewIdx1[nListMaxView1-1-i] ], &m_FileList2[ pViewIdx2[nListMaxView2-1-j] ]);
			if( nCmp<0 )
			{
				pALLA[k] = pViewIdx1[nListMaxView1-1-i];
				pALLB[k] = -1;
				i++;
			}
			else if( nCmp>0 )
			{
				pALLA[k] = -1;
				pALLB[k] = pViewIdx2[nListMaxView2-1-j];
				j++;
			}
			else
			{
				pALLA[k] = pViewIdx1[nListMaxView1-1-i];
				pALLB[k] = pViewIdx2[nListMaxView2-1-j];
				if (i<nListMaxView1-1)
				{
					i++;
				}
				if (j<nListMaxView2-1)
				{
					j++;
				}
			}
		}
		else
		{
			if(i == nListMaxView1)
			{
				pALLA[k] = -1;
				pALLB[k] = pViewIdx2[nListMaxView2-1-j];
				j++;
			}
			else if(j == nListMaxView2)
			{
				pALLA[k] = pViewIdx1[nListMaxView1-1-i];
				pALLB[k] = -1;
				i++;
			}
		}
		if (i==nListMaxView1 && j==nListMaxView2)
		{
			nCount=k;
			break;
		}
	}
	pCmpIdxAll1 = pALLA;
	pCmpIdxAll2 = pALLB;
	pCmpIdxAllg = pALLg;
	nListMaxAll = nCount+1;
	if (nListMaxAll==1)
	{
		nListMaxAll = nTotal;
	}
	bCompared = TRUE;
	//UpdateViewIndex(1);
	//UpdateViewIndex(2);
	m_dlg_compare.m_ckLockVscroll.SetCheck( TRUE );
	UpdateListTitle(1);
	m_list1.SetItemCount(nListMaxAll);
	m_list1.RedrawItems(0, nListMaxAll-1);
	UpdateListTitle(2);
	m_list2.SetItemCount(nListMaxAll);
	m_list2.RedrawItems(0, nListMaxAll-1);
	return 0;
}
int CFileCompareDevil2Dlg::IsFilesEquals(FILELIST* pFileList1, FILELIST* pFileList2)
{
	if ( m_dlg_compare.bSize )
	{
		return (pFileList1->pFileinfo->nFileSize - pFileList2->pFileinfo->nFileSize) ;
	}
	if (m_dlg_compare.bType)
	{
		return pFileList1->pFileinfo->szFileType.CompareNoCase(pFileList2->pFileinfo->szFileType);
	}
	if (m_dlg_compare.bName)
	{
		return pFileList1->pFileinfo->szFilename.CompareNoCase(pFileList2->pFileinfo->szFilename);
	}
	if (m_dlg_compare.bMD5)
	{
	}
}



void CFileCompareDevil2Dlg::FilterFiles(CFileInfo* pFileInfo)
{

	for(int i=0; i<pFileInfo->children.size(); i++)
	{
		FilterFiles(pFileInfo->children[i]);
	}
	pFileInfo->bIgnored = FALSE;
	if (pFileInfo->dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
	{
		if (pFileInfo->children.size()>0)
		{
			return;
		}
		//------ 文件夹名 ---
		WCHAR* next_token1 = NULL;
		WCHAR* orgstring = m_dlg_filter.m_strFolder_except.AllocSysString();
		WCHAR* token1 = wcstok_s( orgstring, L"\r\n", &next_token1);
		while ( token1 != NULL )
		{
			if ( pFileInfo->szFilename.MakeUpper().Find( CString(token1).MakeUpper() ) != -1 )
			{
				pFileInfo->bIgnored = TRUE;
				return;
			}
			token1 = wcstok_s( NULL, L"\r\n", &next_token1);
		}
		SysFreeString(orgstring);
		orgstring = m_dlg_filter.m_strFolder_include.AllocSysString();
		token1 = wcstok_s( orgstring, L"\r\n", &next_token1);
		pFileInfo->bIgnored = TRUE;
		while ( token1 != NULL )
		{
			if ( pFileInfo->szFilename.MakeUpper().Find( CString(token1).MakeUpper() ) != -1 )
			{
				pFileInfo->bIgnored = FALSE;
				break;
			}
			token1 = wcstok_s( NULL, L"\r\n", &next_token1);
		}
		SysFreeString(orgstring);
	}
	else
	{
		//////////////////////////////////////////////////////////////////////////
		//-------- 类型 ----
		if ( !m_dlg_filter.m_strType_include.IsEmpty() )
		{
			CString sTypeTmp = m_dlg_filter.m_strType_include;
			sTypeTmp += L"\'";
			sTypeTmp.Replace(L"\r",L"\'");
			sTypeTmp.Replace(L"\n",L"\'");
			if ( sTypeTmp.MakeUpper().Find( pFileInfo->szFileType.Mid(1).MakeUpper()+L"\'" ) == -1 )
			{
				pFileInfo->bIgnored = TRUE;
				return;
			}
		} 
		else if ( !m_dlg_filter.m_strType_except.IsEmpty() )
		{
			CString sTypeTmp = m_dlg_filter.m_strType_except;
			sTypeTmp += L"\'";
			sTypeTmp.Replace(L"\r",L"\'");
			sTypeTmp.Replace(L"\n",L"\'");
			if ( sTypeTmp.MakeUpper().Find( pFileInfo->szFileType.Mid(1).MakeUpper()+L"\'" ) != -1 )
			{
				pFileInfo->bIgnored = TRUE;
				return;
			}
		}
		//---------  大小  -----------
		if (m_dlg_filter.m_nSize_min != 0)
		{
			if ( pFileInfo->nFileSize < m_dlg_filter.m_nSize_min*1024)
			{
				pFileInfo->bIgnored = TRUE;
				return;
			}
		}
		if (m_dlg_filter.m_nSize_max != 0)
		{
			if ( pFileInfo->nFileSize > m_dlg_filter.m_nSize_max*1024 )
			{
				pFileInfo->bIgnored = TRUE;
				return;
			}
		}
		//--------- 属性 ----------
// 		if (m_dlg_filter.bArchive != pFileInfo->bArchive)
// 		{
// 			pFileInfo->bIgnored = TRUE;
// 			return;
// 		}
// 		if (m_dlg_filter.bHidden != pFileInfo->bHidden)
// 		{
// 			pFileInfo->bIgnored = TRUE;
// 			return;
// 		}
// 		if (m_dlg_filter.bSystem != pFileInfo->bSystem)
// 		{
// 			pFileInfo->bIgnored = TRUE;
// 			return;
// 		}
// 		if (m_dlg_filter.bReadonly != pFileInfo->bReadOnly)
// 		{
// 			pFileInfo->bIgnored = TRUE;
// 			return;
// 		}
		//------ 时间 -----
		CTime tCreateTmp(pFileInfo->ftCreationTime);
		if ( tCreateTmp < m_dlg_filter.m_time_create_from)
		{
			pFileInfo->bIgnored = TRUE;
			return;
		}
		if ( tCreateTmp > m_dlg_filter.m_time_create_to)
		{
			pFileInfo->bIgnored = TRUE;
			return;
		}
		CTime tModifyTmp(pFileInfo->ftLastWriteTime);
		if ( tModifyTmp < m_dlg_filter.m_time_modify_from)
		{
			pFileInfo->bIgnored = TRUE;
			return;
		}
		if ( tModifyTmp > m_dlg_filter.m_time_modify_to)
		{
			pFileInfo->bIgnored = TRUE;
			return;
		}
		//------ 文件名 ---
		WCHAR* next_token1 = NULL;
		WCHAR* orgstring = m_dlg_filter.m_strFile_except.AllocSysString();
		WCHAR* token1 = wcstok_s( orgstring, L"\r\n", &next_token1);
		while ( token1 != NULL )
		{
			if ( pFileInfo->szFilename.MakeUpper().Find( CString(token1).MakeUpper() ) != -1 )
			{
				pFileInfo->bIgnored = TRUE;
				return;
			}
			token1 = wcstok_s( NULL, L"\r\n", &next_token1);
		}
		SysFreeString(orgstring);
		orgstring = m_dlg_filter.m_strFile_include.AllocSysString();
		token1 = wcstok_s( orgstring, L"\r\n", &next_token1);
		
		while ( token1 != NULL )
		{
			if ( pFileInfo->szFilename.MakeUpper().Find( CString(token1).MakeUpper() ) != -1 )
			{
				pFileInfo->bIgnored = FALSE;
				break;
			}
			else
			{
				pFileInfo->bIgnored = TRUE;
			}
			token1 = wcstok_s( NULL, L"\r\n", &next_token1);
		}
		SysFreeString(orgstring);



		//////////////////////////////////////////////////////////////////////////
		

	}
	return;
}
//右键弹出菜单
void CFileCompareDevil2Dlg::OnNMRClickListCom(int nlist, NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if(pNMItemActivate->iItem != -1)
	{
		CMenu menu ,* pSubMenu;//定义下面要用到的cmenu对象
		menu.LoadMenu(IDR_MENU_LIST);//装载自定义的右键菜单
		pSubMenu = menu.GetSubMenu(0);//获取第一个弹出菜单，所以第一个菜单必须有子菜单
		CPoint oPoint;//定义一个用于确定光标位置的位置
		GetCursorPos(&oPoint);//获取当前光标的位置，以便使得菜单可以跟随光标
		pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //在指定位置显示弹出菜单
		nSelItem = pNMItemActivate->iItem;
		nSelSubItem = pNMItemActivate->iSubItem;
		nSelList = nlist;
	}
	*pResult = 0;
}
void CFileCompareDevil2Dlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMRClickListCom(1, pNMHDR, pResult);
}
void CFileCompareDevil2Dlg::OnNMRClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMRClickListCom(2, pNMHDR, pResult);
}

//新建目录
void CFileCompareDevil2Dlg::OnListMkdir()
{
	SetCurTmp(nSelList);
	long objIndex = (*ptbSortUP) ? (*ptpViewIdx)[ nSelItem ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - nSelItem ];
	CFileInfo* pParent;
	CFileInfo* pfile = new CFileInfo;
	if ( (*ptFileList)[objIndex].pFileinfo->dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY )//folder
	{
		pParent = (*ptFileList)[objIndex].pFileinfo;
	} 
	else//file
	{
		pParent = (*ptFileList)[objIndex].pFileinfo->pParent;
	}

	m_dlg_logaction.AddAction(ACTION_MKDIR, (*ptFileList)[pParent->nIndex].sFullPath + _T("\\新建文件夹"));
	CTime time(CTime::GetCurrentTime());
	SYSTEMTIME st;
	time.GetAsSystemTime(st);
	FILETIME ft;
	::SystemTimeToFileTime(&st, &ft);
	pfile->pParent = pParent;
	pfile->szFileType = _T("");
	pfile->szFilename = _T("新建文件夹");
	pfile->dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
	pfile->ftCreationTime = ft;
	pfile->ftLastAccessTime = ft;
	pfile->ftLastWriteTime = ft;
	pfile->bReadOnly = false;
	pfile->bSystem = false;
	pfile->bHidden = false;
	pfile->nSate = 1;//新增
	pfile->bIgnored = FALSE;
	pfile->nChecked = 0;
	pfile->bExpand = TRUE;
	pfile->nlayers = pParent->nlayers + 1;
	pfile->nFileSize = 0;
	pParent->children.push_back( pfile );
	pParent->nDirsCur ++;
	//pParent->nDirsAll ++;
	while(pParent->pParent != NULL)
	{
		pParent->nDirsAll ++;
		pParent = pParent->pParent;
	}
	(*ptnListMax) ++;
	FILELIST fl;
	CString sPath = (*ptFileList)[ pfile->pParent->nIndex ].sFullPath;
	if( sPath.Right(1) != _T("\\") )
	{
		sPath += _T("\\");
	}
	fl.sFullPath = sPath + pfile->szFilename;

	fl.pFileinfo = pfile;
	(*ptFileList).insert((*ptFileList).begin( ) + pfile->pParent->nIndex +1,fl);
	for (int i=pfile->pParent->nIndex+1;i<*ptnListMax;i++)
	{
		(*ptFileList)[i].pFileinfo->nIndex++;
	}
	pfile->nIndex = pfile->pParent->nIndex + 1;
	if ((*ptpObjIndex) != NULL)
	{
		delete[] (*ptpObjIndex);
		(*ptpObjIndex) = NULL;
	}
	(*ptpObjIndex) = new int[*ptnListMax];
	for (int i=0;i<*ptnListMax;i++)
	{
		(*ptpObjIndex)[i] = i;
	}
	UpdateViewIndex(nSelList);
	SortFileList(nSelList);
	UpdateListTitle(nSelList);
	ptlist->SetItemCount(*ptnListMaxView);
	ptlist->RedrawItems(0,*ptnListMaxView-1);
	for (int i=0;i<*ptnListMaxView;i++)
	{
		if ( (*ptpViewIdx)[i] == pfile->nIndex )
		{
			nSelItem = i;
			break;
		}
	}
	nSelItem = (*ptbSortUP) ? nSelItem : *ptnListMaxView - 1 - nSelItem ;
	OnListRename();
}

//把选中项标记为待复制
void CFileCompareDevil2Dlg::OnListCopy()
{
	SetCurTmp(nSelList);
	m_dlg_logaction.AddLog(ACTION_COPY, strloglistn);
	for (int i=0;i<(*ptFileList).size();i++)
	{
		if ((*ptFileList)[i].pFileinfo->nChecked == 1)
		{
			(*ptFileList)[i].pFileinfo->nSate = 2;
		}
	}
	ptlist->RedrawItems(0,*ptnListMaxView-1);
	nListCopyfrom = nSelList;
}

//把选中项标记为待剪切
void CFileCompareDevil2Dlg::OnListCut()
{
	SetCurTmp(nSelList);
	m_dlg_logaction.AddLog(ACTION_COPY, strloglistn);
	for (int i=0;i<(*ptFileList).size();i++)
	{
		if ((*ptFileList)[i].pFileinfo->nChecked == 1)
		{
			(*ptFileList)[i].pFileinfo->nSate = 3;
		}
	}
	ptlist->RedrawItems(0,*ptnListMaxView-1);
	nListCopyfrom = nSelList;
}

//粘贴
void CFileCompareDevil2Dlg::OnListPaste()
{
	SetCurTmp(nSelList);
	CFileInfo** ptm_pRootCur = ptm_pRoot;
	long objIndexCur = (*ptbSortUP) ? (*ptpViewIdx)[ nSelItem ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - nSelItem ];
	std::vector<FILELIST> *ptFileListCur = ptFileList;
	CFileInfo* ptDest = (*ptFileListCur)[objIndexCur].pFileinfo;
	if (ptDest->dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY ==0)
	{
		ptDest = ptDest->pParent;
	}
	CString strDest0 = (*ptFileListCur)[objIndexCur].sFullPath;
	CString strDest;
	CString strSrc0;
	CString strSrc;
	SetCurTmp(nListCopyfrom);
	CFileInfo* aa = NULL;
	for (int i=0;i<*ptnListMaxView;i++)
	{
		long objIndex = (*ptbSortUP) ? (*ptpViewIdx)[ i ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - i ];
		if ((*ptFileList)[objIndex].pFileinfo->nSate == 2)
		{
			strSrc0 = (*ptFileList)[objIndex].sFullPath;
			strSrc0 = strSrc0.Mid(0, strSrc0.ReverseFind(_T('\\')));
			aa = (*ptFileList)[objIndex].pFileinfo->Copy();
			ptDest->children.push_back(aa);
			aa->pParent = ptDest;
			(*ptFileList)[objIndex].pFileinfo->nSate = 5;//5-已复制
			aa->nSate = 1;
			i += aa->nDirsAll + aa->nFilesAll;
			for (int j=0;j<aa->nDirsAll+aa->nFilesAll+1;j++)
			{
				strDest = (*ptFileList)[objIndex+j].sFullPath;
				strDest.Replace(strSrc0, strDest0);
				if ((*ptFileList)[objIndex+j].pFileinfo->dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
				{
					m_dlg_logaction.AddAction(ACTION_MKDIR, strDest);
				}
				else
				{
					m_dlg_logaction.AddAction(ACTION_COPY, (*ptFileList)[objIndex+j].sFullPath, strDest);
				}
			}
		}
		else if ((*ptFileList)[objIndex].pFileinfo->nSate == 3)
		{
			strSrc0 = (*ptFileList)[objIndex].sFullPath;
			strSrc0 = strSrc0.Mid(0, strSrc0.ReverseFind(_T('\\')));
			aa = (*ptFileList)[objIndex].pFileinfo->Copy();
			ptDest->children.push_back(aa);
			aa->pParent = ptDest;
			(*ptFileList)[objIndex].pFileinfo->nSate = 6;//6-已剪切/已删除
			aa->nSate = 1;
			i += aa->nDirsAll + aa->nFilesAll;
			for (int j=0;j<aa->nDirsAll+aa->nFilesAll+1;j++)
			{
				strDest = (*ptFileList)[objIndex+j].sFullPath;
				strDest.Replace(strSrc0, strDest0);
				if ((*ptFileList)[objIndex+j].pFileinfo->dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
				{
					m_dlg_logaction.AddAction(ACTION_MKDIR, strDest);
				}
				else
				{
					m_dlg_logaction.AddAction(ACTION_CUT, (*ptFileList)[objIndex+j].sFullPath, strDest);
				}
			}
		}
	}
	SetCurTmp(nSelList);
	(*ptFileList).clear();
	(*ptm_pRoot)->nDirsAll = 0;
	(*ptm_pRoot)->nFilesAll = 0;
	(*ptm_pRoot)->nDirsCur = 0;
	(*ptm_pRoot)->nFilesCur = 0;
	AddFileArray(nSelList,(*ptm_pRoot),_T(""));
	(*ptnListMax) = (*ptFileList).size();
	if (*ptpObjIndex != NULL)
	{
		delete[] (*ptpObjIndex);
		*ptpObjIndex = NULL;
	}
	*ptpObjIndex = new int[(*ptnListMax)];
	for (int i=0;i<(*ptnListMax);i++)
	{
		(*ptpObjIndex)[i] = i;
	}
	UpdateViewIndex(nSelList);
	SortFileList(nSelList);
	UpdateListTitle(nSelList);
	ptlist->SetItemCount(*ptnListMaxView);
	ptlist->RedrawItems(0,*ptnListMaxView-1);
	//CFileInfo* aa = (*ptFileList)[objIndex].pFileinfo->Copy();
	//aa->szFilename = L"sdfasdfa";
}

//把选中项标记为待删除
void CFileCompareDevil2Dlg::OnListDelete()
{
	SetCurTmp(nSelList);
	m_dlg_logaction.AddLog(ACTION_COPY, strloglistn);
	for (int i=0;i<(*ptFileList).size();i++)
	{
		if ((*ptFileList)[i].pFileinfo->nChecked == 1)
		{
			(*ptFileList)[i].pFileinfo->nSate = 4;
			m_dlg_logaction.AddAction(ACTION_DEL, (*ptFileList)[i].sFullPath );
		}
	}
	ptlist->RedrawItems(0,*ptnListMaxView-1);
}

//排除路径，此路径及子目录不显示
void CFileCompareDevil2Dlg::OnListHidedir()
{
	SetCurTmp(nSelList);
	long objIndex = (*ptbSortUP) ? (*ptpViewIdx)[ nSelItem ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - nSelItem ];
	(*ptFileList)[objIndex].pFileinfo->bIgnored = TRUE;
	(*ptFileList)[objIndex].pFileinfo->nSate = 8;//已排除
// 	for (int i=0; i<(m_FileList1[objIndex].pFileinfo->nFilesAll + m_FileList1[objIndex].pFileinfo->nDirsAll +1); i++)
// 	{
// 		m_FileList1[objIndex+i].pFileinfo->bIgnored = TRUE;
// 		//m_dlg_logaction.AddLog(LOG_EXPANDSON, _T("list 1"), _T(""), m_list1.GetItemText(nItem,LIST_PATH));
// 	}
	UpdateViewIndex(nSelList);
	SortFileList(nSelList);
	UpdateListTitle(nSelList);
	ptlist->SetItemCount(*ptnListMaxView);
	ptlist->RedrawItems(0,*ptnListMaxView-1);
}

//忽略标记的待处理项
void CFileCompareDevil2Dlg::OnListIgnore()
{
	SetCurTmp(nSelList);
	m_dlg_logaction.AddLog(ACTION_COPY, strloglistn, _T("list 2"));
	m_dlg_logaction.AddLog(LOG_EXPAND, strloglistn);
	//CFileInfo* pParent = NULL;
	if(nSelItem >=0 && nSelItem<ptlist->GetItemCount())
	{
		long objIndex = *ptbSortUP ? (*ptpViewIdx)[ nSelItem ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - nSelItem ];
		switch( (*ptFileList)[objIndex].pFileinfo->nSate )
		{
			//状态：0-正常，1-新增，2-待复制，3-待剪切，4-待删除，5-已复制，6-已剪切/已删除；
		case 2:
		case 3:
		//case 4:
// 			pParent=(*ptFileList)[objIndex].pFileinfo->pParent;
// 			while( pParent != NULL)
// 			{
// 				if ( pParent->nSate == (*ptFileList)[objIndex].pFileinfo->nSate )
// 				{
// 					pParent->nSate = 0;
// 				}
// 				pParent = pParent->pParent;
// 			}
			(*ptFileList)[objIndex].pFileinfo->nSate = 0;
			break;
		}
		m_dlg_logaction.AddLog(LOG_EXPAND, strloglistn, _T(""), ptlist->GetItemText(nSelItem,LIST_PATH));
	}	
	ptlist->RedrawItems(0,*ptnListMaxView - 1);
	//m_dlg_logaction.AddAction()
}

//忽略勾选的标记的待处理项
void CFileCompareDevil2Dlg::OnListIgnoresel()
{
	SetCurTmp(nSelList);
	//m_dlg_logaction.AddLog(ACTION_COPY, _T("list 1"), _T("list 2"));
	//CFileInfo* pParent = NULL;
	for (int i=0;i<*ptnListMaxView;i++)
	{
		long objIndex = *ptbSortUP ? (*ptpViewIdx)[ i ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - i ];
		if ((*ptFileList)[objIndex].pFileinfo->nChecked == 1)
		{
			switch( (*ptFileList)[objIndex].pFileinfo->nSate )
			{
				//状态：0-正常，1-新增，2-待复制，3-待剪切，4-待删除，5-已复制，6-已剪切/已删除，7-重命名过；
			case 2:
			case 3:
			//case 4:
// 				pParent=(*ptFileList)[objIndex].pFileinfo->pParent;
// 				while( pParent != NULL)
// 				{
// 					if ( pParent->nSate == (*ptFileList)[objIndex].pFileinfo->nSate )
// 					{
// 						pParent->nSate = 0;
// 					}
// 					pParent = pParent->pParent;
// 				}
				(*ptFileList)[objIndex].pFileinfo->nSate = 0;
				break;
			}
		}
	}
	ptlist->RedrawItems(0,*ptnListMaxView - 1);
	//m_dlg_logaction.AddAction()
}


//重命名
void CFileCompareDevil2Dlg::OnListRename()
{
	SetCurTmp(nSelList);
	long objIndex = *ptbSortUP ? (*ptpViewIdx)[ nSelItem ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - nSelItem ];
	//if (pNMListView->iSubItem == m_list1.nTree)
	{
		if (objIndex == -1)
		{
			return;
		}
		int nlayers = (*ptFileList)[objIndex].pFileinfo->nlayers;
		IMAGEINFO imageinfo0;
		IMAGEINFO imageinfo1;
		int wi=0;
		int wc=0;
		int h=0;
		CImageList* imglist;
		if( imglist = ptlist->GetImageList(LVSIL_SMALL) )//icon
		{
			if( imglist->GetImageInfo(6, &imageinfo0) )
			{
				wi = imageinfo0.rcImage.right - imageinfo0.rcImage.left; 
			}
		}
		if( imglist = ptlist->GetImageList(LVSIL_STATE) )//checkbox
		{
			if( imglist->GetImageInfo(0, &imageinfo1) )
			{
				wc =   imageinfo1.rcImage.right - imageinfo1.rcImage.left; 
			}
		}
		CRect rect0;
		ptlist->GetSubItemRect(nSelItem, nSelSubItem, LVIR_BOUNDS, rect0 );
		rect0.left += wi*(nlayers)+wc;
		m_rename.SetParent(ptlist);
		m_rename.MoveWindow(rect0);
		m_rename.SetWindowText((*ptFileList)[objIndex].pFileinfo->szFilename);
		m_rename.ShowWindow(SW_SHOW);
		m_rename.SetSel(0,-1);
		m_rename.SetFocus();
	}
}

void CFileCompareDevil2Dlg::OnEnKillfocusEditRename()
{
	SetCurTmp(nSelList);
	long objIndex = *ptbSortUP ? (*ptpViewIdx)[ nSelItem ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - nSelItem ];
	CString sNew;
	m_rename.GetWindowText(sNew);
	if (sNew.IsEmpty())
	{
		return;
	}
	if (sNew.CompareNoCase((*ptFileList)[objIndex].pFileinfo->szFilename)!=0)
	{
		for (int i=0;i<(*ptFileList)[objIndex].pFileinfo->pParent->children.size();i++)
		{
			if (sNew.CompareNoCase((*ptFileList)[objIndex].pFileinfo->pParent->children[i]->szFilename) ==0)//文件名已存在
			{
				AfxMessageBox(L"文件名已存在！");
				OnListRename();
				return;
			}
		}
		(*ptFileList)[objIndex].pFileinfo->nSate = 7;//重命名过
	}

	(*ptFileList)[objIndex].pFileinfo->szFilename = sNew;
	m_rename.ShowWindow(SW_HIDE);
	ptlist->RedrawItems(nSelItem,nSelItem);
}

LRESULT CFileCompareDevil2Dlg::OnMylistKillfocus(WPARAM, LPARAM)
{
	SetCurTmp(nSelList);
	OnEnKillfocusEditRename();
	ptlist->SetFocus();
	return 0;
}
//选中高亮行
void CFileCompareDevil2Dlg::OnListSelect()
{
	SetCurTmp(nSelList);
	m_dlg_logaction.AddLog(LOG_SELECT, strloglistn);
	POSITION pos = ptlist->GetFirstSelectedItemPosition(); //pos选中的首行位置
	if(pos == NULL)
	{
		AfxMessageBox(L"no item were selected!");
	}
	else
	{
		while( pos )   //如果你选择多行
		{
			int nItem = ptlist->GetNextSelectedItem(pos);
			if(nItem >=0 && nItem<ptlist->GetItemCount())
			{
				ToggleCheckBox(nSelList, nItem);
				m_dlg_logaction.AddLog(LOG_SELECT, strloglistn, _T(""), ptlist->GetItemText(nItem,LIST_PATH));
			}
		}
	}
}

//选中全部
void CFileCompareDevil2Dlg::OnListSelectall()
{
	SetCurTmp(nSelList);
	long objIndex = -1;
	for(int i=0;i<ptlist->GetItemCount();i++)
	{
		objIndex = *ptbSortUP ? (*ptpViewIdx)[ i ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - i ];
		(*ptFileList)[objIndex].pFileinfo->nChecked = 1;
	}
	ptlist->RedrawItems(0,*ptnListMaxView - 1);
}

//反选
void CFileCompareDevil2Dlg::OnListSelectinvert()
{
	SetCurTmp(nSelList);
	long objIndex = -1;
	for(int i=0;i<ptlist->GetItemCount();i++)
	{
		objIndex = *ptbSortUP ? (*ptpViewIdx)[ i ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - i ];
		if ((*ptFileList)[objIndex].pFileinfo->nChecked != 2)
		{
			(*ptFileList)[objIndex].pFileinfo->nChecked = (*ptFileList)[objIndex].pFileinfo->nChecked==0 ? 1 : 0;
		}
	}
	ptlist->RedrawItems(0,*ptnListMaxView - 1);
}

//展开
void CFileCompareDevil2Dlg::OnListExpand()
{
	SetCurTmp(nSelList);
	m_dlg_logaction.AddLog(LOG_EXPAND, strloglistn);
	long objIndex = *ptbSortUP ? (*ptpViewIdx)[ nSelItem ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - nSelItem ];
	(*ptFileList)[objIndex].pFileinfo->bExpand = TRUE;
	m_dlg_logaction.AddLog(LOG_EXPAND, strloglistn, _T(""), ptlist->GetItemText(nSelItem,LIST_PATH));

	UpdateViewIndex(nSelList);
	SortFileList(nSelList);
	UpdateListTitle(nSelList);
	ptlist->SetItemCount(*ptnListMaxView);
	ptlist->RedrawItems(0,*ptnListMaxView -1);
}

//折叠
void CFileCompareDevil2Dlg::OnListFold()
{
	SetCurTmp(nSelList);
	m_dlg_logaction.AddLog(LOG_FOLD, strloglistn);
	long objIndex = *ptbSortUP ? (*ptpViewIdx)[ nSelItem ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - nSelItem ];
	(*ptFileList)[objIndex].pFileinfo->bExpand = FALSE;
	m_dlg_logaction.AddLog(LOG_EXPAND, strloglistn, _T(""), ptlist->GetItemText(nSelItem,LIST_PATH));
	UpdateViewIndex(nSelList);
	SortFileList(nSelList);
	UpdateListTitle(nSelList);
	ptlist->SetItemCount(*ptnListMaxView);
	ptlist->RedrawItems(0,*ptnListMaxView -1);
}

//展开所有子项
void CFileCompareDevil2Dlg::OnListExpandson()
{
	SetCurTmp(nSelList);
	m_dlg_logaction.AddLog(LOG_EXPANDSON, strloglistn);

	long objIndex = *ptbSortUP ? (*ptpViewIdx)[ nSelItem ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - nSelItem ];
	for (int i=0; i<((*ptFileList)[objIndex].pFileinfo->nFilesAll + (*ptFileList)[objIndex].pFileinfo->nDirsAll +1); i++)
	{
		(*ptFileList)[objIndex+i].pFileinfo->bExpand = TRUE;
		m_dlg_logaction.AddLog(LOG_EXPANDSON, strloglistn, _T(""), ptlist->GetItemText(nSelItem,LIST_PATH));
	}

	UpdateViewIndex(nSelList);
	SortFileList(nSelList);
	UpdateListTitle(nSelList);
	ptlist->SetItemCount(*ptnListMaxView);
	ptlist->RedrawItems(0,*ptnListMaxView -1);
}

//折叠所有子项
void CFileCompareDevil2Dlg::OnListFoldson()
{
	SetCurTmp(nSelList);
	m_dlg_logaction.AddLog(LOG_FOLDSON, strloglistn);

	long objIndex = *ptbSortUP ? (*ptpViewIdx)[ nSelItem ] : (*ptpViewIdx)[ *ptnListMaxView - 1 - nSelItem ];
	for (int i=0; i<((*ptFileList)[objIndex].pFileinfo->nFilesAll + (*ptFileList)[objIndex].pFileinfo->nDirsAll +1); i++)
	{
		(*ptFileList)[objIndex+i].pFileinfo->bExpand = FALSE;
		m_dlg_logaction.AddLog(LOG_FOLDSON, strloglistn, _T(""), ptlist->GetItemText(nSelItem,LIST_PATH));
	}

	UpdateViewIndex(nSelList);
	SortFileList(nSelList);
	UpdateListTitle(nSelList);
	ptlist->SetItemCount(*ptnListMaxView);
	ptlist->RedrawItems(0,*ptnListMaxView -1);
}

//全部展开
void CFileCompareDevil2Dlg::OnListExpandall()
{
	SetCurTmp(nSelList);
	m_dlg_logaction.AddLog(LOG_EXPANDALL, strloglistn);
	for (int i=0; i<*ptnListMax; i++)
	{
		(*ptFileList)[i].pFileinfo->bExpand = TRUE;
	}
	UpdateViewIndex(nSelList);
	SortFileList(nSelList);
	UpdateListTitle(nSelList);
	ptlist->SetItemCount(*ptnListMaxView);
	ptlist->RedrawItems(0,*ptnListMaxView -1);
}

//全部折叠
void CFileCompareDevil2Dlg::OnListFoldall()
{
	SetCurTmp(nSelList);
	m_dlg_logaction.AddLog(LOG_FOLDALL, strloglistn);
	for (int i=0; i<*ptnListMax; i++)
	{
		(*ptFileList)[i].pFileinfo->bExpand = FALSE;
	}
	UpdateViewIndex(nSelList);
	SortFileList(nSelList);
	UpdateListTitle(nSelList);
	ptlist->SetItemCount(*ptnListMaxView);
	ptlist->RedrawItems(0,*ptnListMaxView -1);
}

//刷新目录，重新遍历其子目录文件
void CFileCompareDevil2Dlg::OnListReflash()
{
	SetCurTmp(nSelList);
	// TODO: 在此添加命令处理程序代码
}

//属性
void CFileCompareDevil2Dlg::OnListProperty()
{
	SetCurTmp(nSelList);
	CString sdir = ptlist->GetItemText(nSelItem,LIST_PATH);
	SHELLEXECUTEINFO execInfo ;
	memset( &execInfo, 0, sizeof( execInfo ) ) ;
	execInfo.fMask  = SEE_MASK_INVOKEIDLIST ;     
	execInfo.cbSize = sizeof( execInfo ) ;   
	execInfo.hwnd   = m_hWnd ;   
	execInfo.lpVerb = _T( "properties" ) ;     
	execInfo.lpFile = sdir ;  
	execInfo.lpParameters = NULL ;   
	execInfo.lpDirectory  = NULL ;   
	execInfo.nShow        = SW_SHOWNORMAL ;   
	execInfo.hProcess     = NULL ;   
	execInfo.lpIDList     = 0 ;   
	execInfo.hInstApp     = 0 ;  
	ShellExecuteEx( &execInfo ) ;
}

//复制路径
void CFileCompareDevil2Dlg::OnListCopypath()
{
	SetCurTmp(nSelList);
	CString sdir = ptlist->GetItemText(nSelItem,LIST_PATH);
	if(OpenClipboard())
	{
		HGLOBAL clipbuffer;
		WCHAR* buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, (sdir.GetLength()+1)*2);
		buffer = (TCHAR*)GlobalLock(clipbuffer);
		_tcscpy(buffer, sdir.GetString());
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_UNICODETEXT,clipbuffer);
		CloseClipboard();
	}
}

//打开所在文件夹
void CFileCompareDevil2Dlg::OnListOpencontains()
{
	SetCurTmp(nSelList);
	CString sdir = ptlist->GetItemText(nSelItem,LIST_PATH);
	m_dlg_logaction.AddLog(LOG_EXPLORER, strloglistn, _T(""), sdir);
	CString sCmd = _T("explorer.exe /select,") + sdir;//打开并选中
	WinExec(CT2CA(sCmd), SW_SHOWNORMAL);
}

//打开log对话框
void CFileCompareDevil2Dlg::OnBnClickedBtnLogaction()
{
	m_dlg_logaction.bLog = TRUE;
	m_dlg_logaction.m_list_log.SetItemCount(m_dlg_logaction.nListLogMax);
	m_dlg_logaction.ShowWindow(SW_SHOW);
	m_dlg_logaction.SetFocus();
	//m_dlg_logaction.m_list_log.SetColumnWidth(LISTLOG_SATE,0);
}

//打开action对话框
void CFileCompareDevil2Dlg::OnBnClickedBtnLogaction2()
{
	m_dlg_logaction.bLog = FALSE;
	m_dlg_logaction.m_list_log.SetItemCount(m_dlg_logaction.nListActionMax);
	m_dlg_logaction.ShowWindow(SW_SHOW);
	m_dlg_logaction.SetFocus();
}

//屏蔽回车关闭窗口
void CFileCompareDevil2Dlg::OnOK()
{
	//CDialog::OnOK();
}


void CFileCompareDevil2Dlg::OnCancel()
{
	CDialog::OnCancel();
}




