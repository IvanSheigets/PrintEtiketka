#pragma once
#include "afxwin.h"


// диалоговое окно CChangeDlina

class CChangeDlina : public CDialog
{
	DECLARE_DYNAMIC(CChangeDlina)

public:
	CChangeDlina(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CChangeDlina();
	CStatic m_statCountEtiketok;
	CStatic m_statDlina;
	void SetDlina(int);
	void SetCountEtiketok(int,int);

// Данные диалогового окна
	enum { IDD = IDD_DIALOG_CHANGEDLINA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int m_iDlinaRylona;
	int m_iCountEtiketok;
	int m_iDlinaEtiketki;
	virtual BOOL OnInitDialog();
	CEdit m_editDlina;
	CEdit m_editCountEtiketok;
protected:
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedButtonChange();
	
	afx_msg void OnEnChangeEditChangedlinaDlina();
};
