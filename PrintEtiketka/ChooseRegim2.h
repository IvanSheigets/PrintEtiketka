#pragma once
#include "afxwin.h"

#include "MyStatic.h"


// диалоговое окно CChooseRegim2

class CChooseRegim2 : public CDialog
{
	DECLARE_DYNAMIC(CChooseRegim2)

public:
	CChooseRegim2(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CChooseRegim2();

	int m_iNumberCar;
	int m_iNumberSmena;

	CMyStatic m_statNumberCar;
	CMyStatic m_statNumberSmena;

	void SetSmena(int );
	void SetCar(int);

// Данные диалогового окна
	enum { IDD = IDD_DIALOG_CHOOSE_REGIM2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonChange();
	CComboBox m_comboNumCar;
	CComboBox m_comboNumSmena;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnCancel();
public:
	afx_msg void OnCbnSelchangeComboNumberSmena2();
};
