// MyListCtrl.cpp: файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "MyListCtrl.h"


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)

CMyListCtrl::CMyListCtrl()
{

}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// обработчики сообщений CMyListCtrl



void CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);//Поучаем указатель на контекст Листктрл
	CRect rcItem(lpDrawItemStruct->rcItem);//Получаем прямоугольник строки
	UINT uiFlags = ILD_TRANSPARENT;
	int nItem = lpDrawItemStruct->itemID;//Номер строки

	COLORREF bg = RGB (255,0,0);
	COLORREF Text = RGB (50,255,50);

	if (lpDrawItemStruct->itemID%2==0)
	{
		Text = RGB (0,0,255);
		bg = RGB (255,255,0);
	}
	else 
	{
		Text = RGB (255,255,0);
		bg = RGB (30 ,144, 255);
	}


	static _TCHAR  szBuff[MAX_PATH];
	CString pszText;
	LV_ITEM lvi;                  //Заполним структуру
	lvi.mask = LVIF_TEXT;
	lvi.iItem = nItem;
	lvi.iSubItem = 0;
	lvi.pszText = szBuff;
	lvi.cchTextMax = sizeof(szBuff);
	lvi.stateMask = 0xFFFF;     // get all state flags
	CMyListCtrl::GetItem(&lvi);

	CRect rcAllLabels;
	CMyListCtrl::GetItemRect(nItem, rcAllLabels, LVIR_BOUNDS);
	pDC->FillRect(rcAllLabels, &CBrush(bg));//Заливаем
	CMyListCtrl::GetItemRect(nItem, rcItem, LVIR_LABEL);
	pszText =  szBuff;
	CRect rcLabel = rcItem;

	/////////////////////////////////////////Рисуем текст////////////////////////////////////////////////////////////////////
	pDC->SetTextColor(Text);
	pDC->DrawText(pszText,-1,rcLabel,DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
	/////////////////////////////////////Заполним Колонки для LVS_REPORT////////////////////////////////////////////

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH;
	for(int nColumn = 1; CMyListCtrl::GetColumn(nColumn, &lvc); nColumn++)
	{
		rcItem.left = rcItem.right+3;
		rcItem.right += lvc.cx;
		CMyListCtrl::GetItemText(nItem, nColumn,szBuff, sizeof(szBuff));
		pszText = szBuff;
		pDC->DrawText(pszText, pszText.GetLength(), rcItem, DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
	}

	//CClientDC dc(this);

// 	CDC *dc = CWnd::GetDC();
// 
// 	int x=5;
// 	int y=58;
// 	int xx=184;
// 	int yy=580;
// 
// 	int t=2;
// 
// 
// 	COLORREF rgb = RGB(255,0,0);
// 	
// 
// 	pDC->FillSolidRect(x,y,xx-x,t,rgb);
// 	dc->FillSolidRect(x,y,t,yy-y,rgb);
// 	dc->FillSolidRect(x,yy,xx-x,t,rgb);
// 	dc->FillSolidRect(xx,y,t,yy-y+t,rgb);
}

void CMyListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
//	MessageBox("ssss");


	CListCtrl::OnLButtonDblClk(nFlags, point);
}
