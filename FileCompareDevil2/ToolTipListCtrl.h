#pragma once
#define WM_MYLIST_KILLFOCUS (WM_USER+1234)

// CToolTipListCtrl

class CToolTipListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CToolTipListCtrl)

public:
	CToolTipListCtrl();
	virtual ~CToolTipListCtrl();
	virtual int OnToolHitTest(CPoint point, TOOLINFO * pTI) const;

protected:
	DECLARE_MESSAGE_MAP()
	virtual afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT *  pResult );
	CString m_strToolTipText;//Item的提示信息
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	int nCheckbox;
	COLORREF clrText;
	COLORREF clrTextBk;
	//virtual HRESULT accHitTest(long xLeft, long yTop, VARIANT *pvarChild);
	virtual int HitTest( LVHITTESTINFO* pHitTestInfo);
	int nTree;//树形显示的列标号。-1为无效
	int nlayers;//树形目录层数
};


