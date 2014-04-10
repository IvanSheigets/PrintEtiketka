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
	CFont m_cfFont;//����� ��� �������
	BOOL m_boolSetFont;//���������� �� �����
	
	COLORREF m_colBkColor;//���� ����
	COLORREF m_colTextColor;//���� ������
	BOOL m_boolBkColor;
	BOOL m_boolTextColor;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


