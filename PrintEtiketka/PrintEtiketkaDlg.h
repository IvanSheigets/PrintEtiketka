// PrintEtiketkaDlg.h : файл заголовка
//

#pragma once

#include "ChooseRegim.h"
#include "ChooseProduct.h"
#include "WorkDialog.h"
#include "Zvit.h"
#include "Password.h"


// диалоговое окно CPrintEtiketkaDlg
class CPrintEtiketkaDlg : public CDialog
{
// Создание
public:
	CPrintEtiketkaDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_PRINTETIKETKA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV
private:
	HACCEL m_hAccel;

	CBrush m_cbDialogColor;
	CChooseRegim *m_chooseRegim;
	CChooseProduct *m_chooseProduct;
	CWorkDialog *m_workDialog;
	CZvit *m_zvit;
	CPassword *m_password;

	CString m_strServerAddr;
	CString m_strMysqlPass;
	CString m_strMysqlLogin;

	
// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);
//	afx_msg void OnBnClickedButton1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
