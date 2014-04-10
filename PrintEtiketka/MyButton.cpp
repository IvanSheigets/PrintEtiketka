// MyButton.cpp: ���� ����������
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{
	m_colRGB = RGB(0,0,0);

}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
//	ON_WM_PAINT()
END_MESSAGE_MAP()



// ����������� ��������� CMyButton


void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	UINT uStyle = DFCS_BUTTONPUSH;

	// This code only works with buttons.
	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

	// If drawing selected, add the pushed style to DrawFrameControl.
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
		uStyle |= DFCS_PUSHED;

	// Draw the button frame.
	::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, 
		DFC_BUTTON, uStyle);

	// Get the button's text.
	CString strText;
	GetWindowText(strText);

	// Draw the button text using the text color red.
	COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, m_colRGB);
	::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(), 
		&lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	::SetTextColor(lpDrawItemStruct->hDC, crOldColor);
}

void CMyButton::SetTextColor(COLORREF color)
{
	m_colRGB = color;

}