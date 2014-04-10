#pragma once
#include "Settings.h"
#include "afxwin.h"

// диалоговое окно CPassword

class CPassword : public CDialog
{
	DECLARE_DYNAMIC(CPassword)

public:
	CPassword(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CPassword();
	CSettings *m_settings;

// Данные диалогового окна
	enum { IDD = IDD_PRINTETIKETKA_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPassEnter();
	CEdit m_editPassword;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPassExit();
};
