#pragma once
#include "MyStatic.h"
#include "afxwin.h"

// диалоговое окно CChooseRegim

class CChooseRegim : public CDialog
{
	DECLARE_DYNAMIC(CChooseRegim)

public:
	CChooseRegim(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CChooseRegim();

	int regim;			//какая кнопка нажата
	int m_iNumberCar;	//номер машины
	int m_iNumberSmena;//номер смены


private:
	HACCEL m_hAccel;
	CMyStatic m_statNumberCar;
	CMyStatic m_statNumberSmena;


// Данные диалогового окна
	enum { IDD = IDD_DIALOG_CHOOSE_REGIM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonEnter();
	afx_msg void OnBnClickedButtonZvity();
	afx_msg void OnBnClickedButtonSettings();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedCancel();
	CComboBox m_comboNumberCar;
	CComboBox m_comboNumberSmena;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
