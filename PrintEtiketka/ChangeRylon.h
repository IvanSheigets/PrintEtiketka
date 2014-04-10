#pragma once
#include "afxwin.h"


// диалоговое окно CChangeRylon

class CChangeRylon : public CDialog
{
	DECLARE_DYNAMIC(CChangeRylon)

public:
	CChangeRylon(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CChangeRylon();

// Данные диалогового окна
	enum { IDD = IDD_WORKDIALOG_CHANGERYLON };

	HANDLE hFile;
	double m_dTempVaga;
	double m_dVesTary;
	double m_dBrytto;
	double m_dNetto;
	int m_iNumRylon;
	HACCEL m_hAccel;

	void SetHandleCom(HANDLE);
	void SetVesTary(double);
	void SetNumRylon(int);
	void SetBrytto(double);
	void SetNetto(double);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	CEdit m_editBrytto;
	CEdit m_editNetto;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeEditChangerylonBrytto();
};
