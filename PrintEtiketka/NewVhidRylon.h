#pragma once
#include "afxwin.h"


// ���������� ���� CNewVhidRylon

class CNewVhidRylon : public CDialog
{
	DECLARE_DYNAMIC(CNewVhidRylon)

public:
	CNewVhidRylon(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CNewVhidRylon();

	int m_iVhidDlinaRylona;
	double m_dVhidNetto;
	double m_dVhidBrytto;

	void SetVhidDlinaRylona(int);
	void SetVhidNettoRylona(double);
	void SetVhidBryttoRylona(double);

private:
	CStatic m_statNetto;
	CStatic m_statBrytto;
	CStatic m_statDlina;

// ������ ����������� ����
	enum { IDD = IDD_DIALOG_NEWRYLON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_editNetto;
	CEdit m_editBrytto;
	CEdit m_editDlina;
	afx_msg void OnEnChangeEditNewrylonNetto();
	afx_msg void OnEnChangeEditNewrylonBrytto();
	afx_msg void OnBnClickedButtonNewrylonAdd();
protected:
	virtual void OnCancel();
	virtual void OnOK();
};
