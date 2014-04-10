#pragma once


// CMyButton

class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)

public:
	CMyButton();
	virtual ~CMyButton();

	void SetTextColor(COLORREF color);

private:
	COLORREF m_colRGB;
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnPaint();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


