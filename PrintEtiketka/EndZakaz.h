#pragma once


// диалоговое окно CEndZakaz

class CEndZakaz : public CDialog
{
	DECLARE_DYNAMIC(CEndZakaz)

public:
	CEndZakaz(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CEndZakaz();

// ƒанные диалогового окна
	enum { IDD = IDD_DIALOG_ENDZAKAZ };

protected:
	HACCEL m_hAccel;
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

	void SetCountProduct(int);
	void SetZakazchik(CString);
	void SetTolschina(CString);
	void SetMaterial(CString);
	void SetVagaTary(double);
	void SetPartiya(CString);

	void SetProduct(CString *, int );
	void SetProductWidth(CString *, int);

	void SetNumSmena(int);
	void SetNumCar(int);

private:
	CString m_strZakazchik;
	int m_iCountProduct;	//количество продуктов
	CString m_strTolschina;
	CString m_strMaterial;
	
	double m_dVagaTary;
	CString m_strPartiya;
	
	CString m_strProduct[10];
	CString m_strProductWidth[10];
};
