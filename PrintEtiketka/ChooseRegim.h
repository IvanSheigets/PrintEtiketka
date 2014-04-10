#pragma once
#include "MyStatic.h"
#include "afxwin.h"

// ���������� ���� CChooseRegim

class CChooseRegim : public CDialog
{
	DECLARE_DYNAMIC(CChooseRegim)

public:
	CChooseRegim(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CChooseRegim();

	int regim;			//����� ������ ������
	int m_iNumberCar;	//����� ������
	int m_iNumberSmena;//����� �����


private:
	HACCEL m_hAccel;
	CMyStatic m_statNumberCar;
	CMyStatic m_statNumberSmena;


// ������ ����������� ����
	enum { IDD = IDD_DIALOG_CHOOSE_REGIM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

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
