#pragma once

#include "MyStatic.h"
#include "mybutton.h"
#include "afxwin.h"

// ���������� ���� CAddZakazchik

class CAddZakazchik : public CDialog
{
	DECLARE_DYNAMIC(CAddZakazchik)

public:
	CAddZakazchik(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CAddZakazchik();

	void SetName(CString);
	CString GetData();

private:
	CMyStatic m_myStatName;
	CString m_strName ;
	CString m_strData;

// ������ ����������� ����
	enum { IDD = IDD_DIALOG_ADDZAKAZCHIK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CMyButton m_myButOk;
//	afx_msg void OnPaint();
	CEdit m_editAdd;
	afx_msg void OnEnChangeEditAddzakazchikAdd();
};
