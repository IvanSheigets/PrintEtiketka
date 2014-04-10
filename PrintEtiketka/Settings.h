#pragma once
#include "afxwin.h"


// диалоговое окно CSettings

class CSettings : public CDialog
{
	DECLARE_DYNAMIC(CSettings)

public:
	CSettings(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CSettings();

	FILE *file;
// Данные диалогового окна
	enum { IDD = IDD_PRINTETIKETKA_SETTINGS };
	CString Speed(CString);
	CString Chet(CString);
	CString StopBits(CString);

	CStatic m_statPrintEtiket;
	CStatic m_statPrintShtrih;
	CStatic m_statPrintZvit;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_comboComPort;
	CComboBox m_comboBits;
	CComboBox m_comboSpeed;
	CComboBox m_comboChet;
	CComboBox m_comboStopBits;
	CEdit m_editAddrServer;
	CEdit m_editLogin;
	CEdit m_editPassword;
	afx_msg void OnBnClickedButtonSettingsPrintrtiketok();
	afx_msg void OnBnClickedButtonSettingsPrintshtrih();
	afx_msg void OnBnClickedButtonSettingsPrintzvit();
	afx_msg void OnBnClickedButtonSave();
};
