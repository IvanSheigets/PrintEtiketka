// MyStatic.cpp: файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "MyStatic.h"


// CMyStatic

IMPLEMENT_DYNAMIC(CMyStatic, CStatic)

CMyStatic::CMyStatic()
{
	m_boolSetFont = FALSE;
	m_boolBkColor = FALSE;
	m_boolTextColor = FALSE;

}

CMyStatic::~CMyStatic()
{
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// обработчики сообщений CMyStatic



void CMyStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
// 	if (m_boolSetFont==FALSE)
// 		m_cfFont.CreateFont(16,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Arial");

	dc.SelectObject(&m_cfFont);

	if (m_boolBkColor==FALSE)
		m_colBkColor = RGB(235,235,235);

	if (m_boolTextColor==FALSE)
		m_colTextColor = RGB(0,0,0);

	dc.SetTextColor(m_colTextColor);
	dc.SetBkColor(m_colBkColor);

	CString str;
	CStatic::GetWindowText(str);
	CRect rect;
	CStatic::GetClientRect(&rect);
	dc.DrawText(str,rect,DT_LEFT);
	//m_cfFont.DeleteObject();


}

void CMyStatic::SetFont(int iWidth)
{
	m_cfFont.CreateFont(iWidth,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Arial");
	m_boolSetFont = TRUE;
}

void CMyStatic::SetBkColor(COLORREF colColor)
{
	m_colBkColor = colColor;
	m_boolBkColor = TRUE;
}

void CMyStatic::SetTextColor(COLORREF colColor)
{
	m_colTextColor = colColor;
	if (m_boolTextColor==TRUE)
		Redraw();
	m_boolTextColor = TRUE;
	
}

void CMyStatic::Redraw()
{
	Invalidate();
}