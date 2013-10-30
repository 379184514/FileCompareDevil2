// ToolTipListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ToolTipListCtrl.h"


// CToolTipListCtrl

IMPLEMENT_DYNAMIC(CToolTipListCtrl, CListCtrl)

CToolTipListCtrl::CToolTipListCtrl()
: nCheckbox(0)
, clrText(RGB(0, 0, 0))
, clrTextBk(RGB(255, 255, 255))
, nTree(-1)
, nlayers(0)
{

}

CToolTipListCtrl::~CToolTipListCtrl()
{
}


BEGIN_MESSAGE_MAP(CToolTipListCtrl, CListCtrl)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_NCHITTEST()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CToolTipListCtrl::OnNMCustomdraw)
END_MESSAGE_MAP()



// CToolTipListCtrl 消息处理程序

int CToolTipListCtrl::OnToolHitTest(CPoint point, TOOLINFO * pTI) const {

	//See if the point falls onto a list item
	//UINT nFlags = 0;

	LVHITTESTINFO lvhitTestInfo;

	lvhitTestInfo.pt = point;

	int nItem = ListView_SubItemHitTest(
		this->m_hWnd,
		&lvhitTestInfo);
	int nSubItem = lvhitTestInfo.iSubItem;

	UINT nFlags =   lvhitTestInfo.flags;

	//nFlags is 0 if the SubItemHitTest fails
	//Therefore, 0 & <anything> will equal false
	if (nFlags & LVHT_ONITEMLABEL){
		//If it did fall on a list item,
		//and it was also hit one of the
		//item specific sub-areas we wish to show tool tips for

		//Get the client (area occupied by this control
		RECT rcClient;
		GetClientRect( &rcClient );

		//Fill in the TOOLINFO structure
		pTI->hwnd = m_hWnd;
		pTI->uId = (UINT) (nItem * 100 + nSubItem);
		pTI->lpszText = LPSTR_TEXTCALLBACK;
		pTI->rect = rcClient;

		return pTI->uId; //By returning a unique value per listItem,
		//we ensure that when the mouse moves over another list item,
		//the tooltip will change
	}else{
		//Otherwise, we aren't interested, so let the message propagate
		return -1;
	}
}


BOOL CToolTipListCtrl::OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult ){

	//VC6.0则用下面这句
	//_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();

	//VC2003则用这句
	AFX_MODULE_THREAD_STATE* pThreadState = AfxGetModuleThreadState();
	CToolTipCtrl *pToolTip = pThreadState->m_pToolTip;
	pToolTip->SetMaxTipWidth(500);



	//Handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;


	if( (pNMHDR->idFrom == (UINT)m_hWnd) &&
		( ((pNMHDR->code == TTN_NEEDTEXTA) && (pTTTA->uFlags & TTF_IDISHWND)) ||
		((pNMHDR->code == TTN_NEEDTEXTW) && (pTTTW->uFlags & TTF_IDISHWND)) ) ){
			return FALSE;
	}

	*pResult = 0;

	//Get the mouse position
	const MSG* pMessage;
	pMessage = GetCurrentMessage();
	ASSERT ( pMessage );
	CPoint pt;
	pt = pMessage->pt; //Get the point from the message
	ScreenToClient( &pt );



	LVHITTESTINFO lvhitTestInfo;

	lvhitTestInfo.pt = pt;

	int nItem = SubItemHitTest(&lvhitTestInfo);
	int nSubItem = lvhitTestInfo.iSubItem;

	UINT nFlags =   lvhitTestInfo.flags;


	if( nFlags & LVHT_ONITEMLABEL ){

		//在这里设置提示信息显示的内容
		m_strToolTipText = GetItemText(nItem,nSubItem) + _T("\nanlin");
		pTTTA->lpszText = (LPSTR)(LPWSTR)(LPCWSTR)m_strToolTipText;
		pTTTW->lpszText = (LPWSTR)(LPCWSTR)m_strToolTipText;



		//{{下面为提供提示信息的另外一种方法
		//   CString strTipText;//提示信息内容
		//#ifndef _UNICODE
		//   if (pNMHDR->code == TTN_NEEDTEXTA)
		//    lstrcpyn(pTTTA->szText, strTipText, 80);
		//   else
		//    _mbstowcsz(pTTTW->szText, strTipText, 80);
		//#else
		//   if (pNMHDR->code == TTN_NEEDTEXTA)
		//    _wcstombsz(pTTTA->szText, strTipText, 80);
		//   else
		//    lstrcpyn(pTTTW->szText, strTipText, 80);
		//#endif

		//}}另外一种提示方法结束


		return FALSE; 

	}

	return FALSE;
}


BOOL CToolTipListCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	EnableToolTips(TRUE);
	return CListCtrl::PreTranslateMessage(pMsg);
}
void CToolTipListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
	::SendMessage(GetParent()->m_hWnd,WM_HSCROLL,MAKELONG(nSBCode,nPos),(LPARAM)m_hWnd);
	GetParent()->SendMessage(WM_MYLIST_KILLFOCUS,0,0);
}

void CToolTipListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
	nPos=GetScrollPos(SB_VERT);
	::SendMessage(GetParent()->m_hWnd,WM_VSCROLL,MAKELONG(SB_THUMBPOSITION,nPos),(LPARAM)m_hWnd);
	GetParent()->SendMessage(WM_MYLIST_KILLFOCUS,0,0);
}

BOOL CToolTipListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	BOOL re=CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
	UINT nPos=GetScrollPos(SB_VERT);
	::SendMessage(GetParent()->m_hWnd,WM_VSCROLL,MAKELONG(SB_THUMBPOSITION,nPos),(LPARAM)m_hWnd);

	return re;
}

LRESULT CToolTipListCtrl::OnNcHitTest(CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
// 	GetWindowRect(&rect);
// 	ScreenToClient(&rect);
	CPoint pt =point;
	ScreenToClient(&pt);
	int nFrame=4;
	rect.DeflateRect(nFrame,nFrame);
// 	int nmin;
// 	int nmax;
// 	GetScrollRange(SB_HORZ,&nmin,&nmax);
	//if (GetSystemMetrics(SM_CXVSCROLL)>0)
 	CSize size;
 	size= ApproximateViewRect(); 
 	if (size.cx>rect.Width())
 	{
 		rect.bottom += GetSystemMetrics(SM_CYHSCROLL);//水平滚动条宽度
 	}
 	
 	if (GetCountPerPage()<GetItemCount())
 	{
 		rect.right += GetSystemMetrics(SM_CXVSCROLL);//垂直滚动条宽度
 	}
	
	if (!rect.PtInRect(pt))
	{ 
		if (pt.x<=nFrame && pt.y>=rect.bottom-nFrame)
		{
			return HTBOTTOMLEFT;
		}
		else if (pt.x<=nFrame && pt.y<=nFrame)
		{
			return HTTOPLEFT;
		}
		else if (pt.x>=rect.right-nFrame && pt.y<=nFrame)
		{
			return HTTOPRIGHT;
		}
		else if (pt.x>=rect.right-nFrame && pt.y>=rect.bottom-nFrame)
		{
			return HTBOTTOMRIGHT;
		}
		else if (pt.x<=nFrame)
		{
			return HTLEFT;
		}
		else if (pt.y<=nFrame)
		{

			return HTTOP;
		}
		else if (pt.y>=rect.bottom-nFrame)
		{
			return HTBOTTOM;
		}
		else if (pt.x>=rect.right-nFrame)
		{
			return HTRIGHT;
		}
	}
// 	else
// 	{
// 		return HTCAPTION;//内部时拖动
// 	}
	return CListCtrl::OnNcHitTest(point);
}

void CToolTipListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
// 	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
// 	
// 	*pResult = 0;
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	*pResult = CDRF_DODEFAULT;
	if ( pLVCD->nmcd.dwDrawStage == CDDS_PREPAINT )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( pLVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT )
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ( pLVCD->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM) )
	{
		int nItem = static_cast<int> (pLVCD->nmcd.dwItemSpec);
		int nSubItem = pLVCD->iSubItem;
// 		if(pLVCD->iSubItem %2){
// 			pLVCD->clrTextBk = clrTextBk;
// 		}
// 		else{
// 			pLVCD->clrTextBk = RGB(128,128,255);
// 		}

		pLVCD->clrTextBk = clrTextBk;
		pLVCD->clrText = clrText;

		if ( nSubItem == nTree )
		{
			*pResult = CDRF_SKIPDEFAULT;
			CDC* pDC = CDC::FromHandle( pLVCD->nmcd.hdc );
			CRect rect0;
			GetSubItemRect( nItem, nSubItem, LVIR_BOUNDS, rect0 );
			CImageList *imglist = NULL;// new CImageList;
			DWORD dwStyle = GetExtendedStyle();
			POINT pt = {rect0.left, rect0.top};
			IMAGEINFO imageinfo0;
			int w=0;
			int h=0;
			LVITEM item; 
			memset(&item, 0 ,sizeof(LVITEM)); 
			item.mask = LVIF_IMAGE; 
			item.iItem = nItem; 
			item.iSubItem = 0;
			GetItem(&item); 
			int nIndexImage = item.iImage;
			int state = item.state>>12;
			if( imglist = GetImageList(LVSIL_SMALL) )//icon
			{

				if( imglist->GetImageInfo(6, &imageinfo0) )
				{
					w =   imageinfo0.rcImage.right - imageinfo0.rcImage.left; 
					h =   imageinfo0.rcImage.bottom - imageinfo0.rcImage.top;
				}
				pt.x = rect0.left ;
				pt.y = rect0.bottom - h;
				while(nlayers-->1)
				{
					imglist->Draw( pDC, 6, pt, (LVIS_SELECTED==GetItemState(nItem,LVIS_SELECTED)) ? ILD_SELECTED : ILD_NORMAL );
					pt.x += w;
				}
				//if (nlayers==0)
// 				{
// 					imglist->Draw( pDC, 8, pt, (LVIS_SELECTED==GetItemState(nItem,LVIS_SELECTED)) ? ILD_SELECTED : ILD_NORMAL );
// 					pt.x += w;
// 				}
				imglist->Draw( pDC, nIndexImage, pt, (LVIS_SELECTED==GetItemState(nItem,LVIS_SELECTED)) ? ILD_SELECTED : ILD_NORMAL );
				pt.x += w;
			}
 			if( imglist = GetImageList(LVSIL_STATE) )//checkbox
 			{
				if( imglist->GetImageInfo(6, &imageinfo0) )
				{
					w =   imageinfo0.rcImage.right - imageinfo0.rcImage.left; 
					h =   imageinfo0.rcImage.bottom - imageinfo0.rcImage.top;
				}
 				imglist->Draw( pDC, state-1 , pt, (LVIS_SELECTED==GetItemState(nItem,LVIS_SELECTED)) ? ILD_SELECTED : ILD_NORMAL );
				pt.x += w;
 			}
			
			rect0.left = pt.x;
			if( LVIS_SELECTED == GetItemState(nItem,LVIS_SELECTED) /*&& LVIS_FOCUSED == GetItemState(nItem,LVIS_FOCUSED)*/ ) 
			{
				pDC->FillSolidRect( &rect0, GetSysColor(GetFocus()==this ? COLOR_HIGHLIGHT : COLOR_BTNFACE));
			}
			else
			{
				pDC->FillSolidRect( &rect0,clrTextBk);//GetBkColor() );
			}
			UINT nFormat =DT_VCENTER | DT_SINGLELINE;//|DT_CENTER;   
			CString str = GetItemText(nItem,nSubItem); 
			rect0.left += 2;
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(clrText); 
			pDC->DrawText(str,&rect0,nFormat); 
// 			if ( (dwStyle&LVS_EX_CHECKBOXES) /*&& (GetItemText(nItem,nCheckbox)=="1")*/ )
// 			{
// 				*pResult = CDRF_SKIPDEFAULT;
// 
// 				if( LVIS_SELECTED == GetItemState(nItem,LVIS_SELECTED) && LVIS_FOCUSED == GetItemState(nItem,LVIS_FOCUSED) ) 
// 				{
// 					pDC->FillSolidRect( &rect0, GetSysColor(GetFocus()==this ? COLOR_HIGHLIGHT : COLOR_BTNFACE));
// 				}
// 				else
// 				{
// 					pDC->FillSolidRect( &rect0,RGB(255,128,128));//GetBkColor() );
// 				}
// 
// 				
// 				if( imglist = GetImageList(LVSIL_STATE) )//checkbox
// 				{
// 					IMAGEINFO imageinfo0;
// 					int w=0;
// 					int h=0;
// 					BOOL bChecked = (pLVCD->nmcd.uItemState == CDIS_CHECKED);
// 					if( imglist->GetImageInfo(bChecked, &imageinfo0) )
// 					{
// 						w =   imageinfo0.rcImage.right - imageinfo0.rcImage.left; 
// 						h =   imageinfo0.rcImage.bottom - imageinfo0.rcImage.top;
// 					}
// 					pt.x = rect0.left + w/2;
// 					pt.y = ( rect0.top + rect0.bottom - h )/2;//center
// 					//int nOldRopMode = pDC->SetROP2(R2_NOTCOPYPEN);
// 					imglist->Draw( pDC, bChecked, pt, (LVIS_SELECTED==GetItemState(nItem,LVIS_SELECTED)) ? ILD_SELECTED : ILD_NORMAL );
// 					//pDC->SetROP2(nOldRopMode);
// 				}
// 			}
		}

		//if ( nCheckbox != 0 )
		//{
		//	if( nSubItem == nCheckbox )
		//	{
		//		CDC* pDC = CDC::FromHandle( pLVCD->nmcd.hdc );
		//		CRect rect0,rect1;
		//		GetSubItemRect( nItem, nSubItem, LVIR_BOUNDS, rect0 );
		//		rect1 = rect0;
		//		CImageList *imglist = NULL;// new CImageList;
		//		DWORD dwStyle = GetExtendedStyle();

		//		if ( (dwStyle&LVS_EX_CHECKBOXES) /*&& (GetItemText(nItem,nCheckbox)=="1")*/ )
		//		{
		//			*pResult = CDRF_SKIPDEFAULT;

		//			if( LVIS_SELECTED == GetItemState(nItem,LVIS_SELECTED) && LVIS_FOCUSED == GetItemState(nItem,LVIS_FOCUSED) ) 
		//			{
		//				pDC->FillSolidRect( &rect0, GetSysColor(GetFocus()==this ? COLOR_HIGHLIGHT : COLOR_BTNFACE));
		//			}
		//			else
		//			{
		//				pDC->FillSolidRect( &rect0,RGB(255,128,128));//GetBkColor() );
		//			}

 	//				POINT pt;
 	//				if( imglist = GetImageList(LVSIL_STATE) )//checkbox
 	//				{
 	//					IMAGEINFO imageinfo0;
 	//					int w=0;
 	//					int h=0;
		//				BOOL bChecked = (pLVCD->nmcd.uItemState == CDIS_CHECKED);
 	//					if( imglist->GetImageInfo(bChecked, &imageinfo0) )
 	//					{
 	//						w =   imageinfo0.rcImage.right - imageinfo0.rcImage.left; 
 	//						h =   imageinfo0.rcImage.bottom - imageinfo0.rcImage.top;
 	//					}
 	//					pt.x = rect0.left + w/2;
 	//					pt.y = ( rect0.top + rect0.bottom - h )/2;//center
		//				//int nOldRopMode = pDC->SetROP2(R2_NOTCOPYPEN);
 	//					imglist->Draw( pDC, bChecked, pt, (LVIS_SELECTED==GetItemState(nItem,LVIS_SELECTED)) ? ILD_SELECTED : ILD_NORMAL );
		//				//pDC->SetROP2(nOldRopMode);
 	//				}
		//		}
		//	}
		//}



	}
}

BOOL CToolTipListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 在此添加专用代码和/或调用基类
	HD_NOTIFY *pHDN = (HD_NOTIFY*)lParam; 
	switch (((NMHDR*)lParam)-> code) 
	{
	case HDN_BEGINTRACKA:
	case HDN_BEGINTRACKW:
		if ( pHDN->pitem->cxy < 1 )
		{
			*pResult = TRUE; // disable tracking 
			return TRUE;
		}
		break;
	case HDN_ENDTRACKA:
	case HDN_ENDTRACKW:
		if ( pHDN->pitem->cxy < 30 )
		{ 
			pHDN->pitem->cxy = 30;
			//*pResult = TRUE;   // disable tracking 
			//return TRUE; 
		} 
		break; 

// 	case HDN_ITEMCHANGINGA: //SetColumnWidth(LISTLOG_SATE,0);会用到，如果在这里禁止拖动有冲突
// 	case HDN_ITEMCHANGINGW: 
// 		if ( pHDN->pitem->cxy < 30 )
// 		{ 
// 			pHDN->pitem->cxy = 30;
// 			//*pResult = TRUE;   // disable tracking 
// 			//return TRUE; 
// 		} 
// 		break; 

	default:
		break;
	} 
	return CListCtrl::OnNotify(wParam, lParam, pResult);
}

// HRESULT CToolTipListCtrl::accHitTest(long xLeft, long yTop, VARIANT *pvarChild)
// {
// 	// TODO: 在此添加专用代码和/或调用基类
// 
// 	return CListCtrl::accHitTest(xLeft, yTop, pvarChild);
// }

int CToolTipListCtrl::HitTest(LVHITTESTINFO* pHitTestInfo)
{
// 	//if ( pHitTestInfo->iSubItem == nTree )
// 	{
// 		//pHitTestInfo->pt 
// 		//return
// 		CString ss;
// 		ss.Format(L"%d",nlayers);
// 		AfxMessageBox(ss);
// 	}
	return CListCtrl::HitTest(pHitTestInfo);
}