#pragma once


// CMyStatic

class CMyStatic : public CStatic
{
	DECLARE_DYNAMIC(CMyStatic)

public:

	void SetFont(int iWidth);
	void SetBkColor(COLORREF);
	void SetTextColor(COLORREF);
	void Redraw();

	CMyStatic();
	virtual ~CMyStatic();

private:
	CFont m_cfFont;//шрифт для статика
	BOOL m_boolSetFont;//установлен ли шрифт
	
	COLORREF m_colBkColor;//цвет фона
	COLORREF m_colTextColor;//цвет текста
	BOOL m_boolBkColor;
	BOOL m_boolTextColor;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


