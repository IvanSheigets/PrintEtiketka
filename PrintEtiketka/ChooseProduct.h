#pragma once

#include <afxdb.h>
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"


#include "MyStatic.h"


/*#include <mysql.h>
#include <my_global.h>
#pragma comment(lib, "libmySQL.lib")*/


//


#include "AddZakazchik.h"


// диалоговое окно CChooseProduct

class CChooseProduct : public CDialog
{
	DECLARE_DYNAMIC(CChooseProduct)

	int regim;
	int hide;
	int change;

public:
	CChooseProduct(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CChooseProduct();

	void SetMysqlPass(CString);
	void SetMysqlLogin(CString);
	void SetServerAddr(CString);

	void SetCountProduct(int iCount);
	void SetZakazchik(CString strZakazchik);
	void SetProduct(CString *);
	void SetWidthProduct(CString *);
	void SetCountDorojec(int *);
	void SetTolschina(CString );
	void SetMaterial(CString );
	void SetDlinaRylona(int);
	void SetDlinaEtiketki(int);
	void SetCountEtiketki(int);
	
	void SetVesTary(double *);

	void SetPartiya(CString);
	void SetVhidRylonNetto(double);
	void SetVhidRylonBrytto(double);
	void SetVhidRylonDlina(int);
	
	void SetNumPrintPage(int);
	void SetLogo(bool);
	void SetData(SYSTEMTIME);
	void SetManager(CString strManager);

	SYSTEMTIME m_sysDate;

	int m_iCountProduct2;
	int m_iCountDorojec2[10];

	CString m_strZakazchik;
	int m_iCountProduct;	//количество продуктов
	CString m_strTolschina;
	CString m_strMaterial;
	CString m_strManager;
	int m_iDlinaRylona;
	int m_iDlinaEtiketki;
	int m_iCountEtiketki;
	//double m_dVagaTary;
	CString m_strPartiya;
	int m_iNumPrintPage;

	double m_dVhidRylonNetto;
	double m_dVhidRylonBrytto;
	int m_iVhidRylonDlina;




	CString m_strProduct[10];
	int m_iCountDorojec[10];
	CString m_strProductWidth[10];
	double m_dVagaTary[10];
	int m_iNumberZakazTK;
	bool m_bLogo;

	
	
private:
	HACCEL m_hAccel;

//надписи
	CMyStatic m_statZakazchik;
	CMyStatic m_statCountProduct;
	CMyStatic m_statTolsProduct;
	CMyStatic m_statMaterial;
	CMyStatic m_statDlinaRylona;
	CMyStatic m_statDlinaEtiketki;
	CMyStatic m_statCountEtiketki;
	CMyStatic m_statVesTary;
	CMyStatic m_statPartiya;
	CMyStatic m_statPrihod;
	CMyStatic m_statZakaz;
	CMyStatic m_statNumPrintpage;

	CMyStatic m_statDate;
	CMyStatic m_statManager;

	CMyStatic m_myStatVihidRylon;
	
	CMyStatic m_myStatVhidniyRylon;
 	CMyStatic m_myStatVhidniyRylonNetto;
 	CMyStatic m_myStatVhidniyRylonBrytto;
 	CMyStatic m_myStatVhidniyRylonDlina;

	CMyStatic m_myStatLogo;

	//CMyStatic m_myStatDate;
	

//mysql
	/*MYSQL *mysql;
	MYSQL_RES *res,*res2;
	MYSQL_ROW row,row2;*/
	CString query;

	CDatabase m_database;
	CRecordset *m_pRecord;
	CString strData;
	
//adressa k mysql
private:
	CString m_strServerAddr;
	CString m_strMysqlPass;
	CString m_strMysqlLogin;

//product
	
	CComboBox *m_pcomboProduct;//продукты которые создаються динамически
	CComboBox *m_pcomboWidthProduct;

	CMyStatic *m_pstatProduct;//надписи возле каждого добавленого продукта
	CMyStatic *m_pstatWidthProduct;
	CMyStatic *m_pstatCountDorojec;

	CEdit *m_peditCountDorojec;
	CSpinButtonCtrl *m_pspinCountDorojec;

	CMyStatic *m_pMyStatVagaTary;
	CComboBox *m_pcomboVagaTary;

	
	int m_iCurSelProduct[10];	//что бы остались выбраные продукты 
	int m_iCurSelWidthProduct[10];	//после добавления еще одного продукта
	int m_iCurSelVagaTary[10];	//после добавления еще одного продукта

	CAddZakazchik *m_addZakazchik;
public:
		

private:
	CRect m_rectClient;
	void Plus(int h);
	void CalcKolEtiket(CString DlinaRylona, CString DlinaEtik);
	
// Данные диалогового окна
	enum { IDD = IDD_DIALOG_CHOOSE_PRODUCT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CComboBox m_comboZakazchik;
	afx_msg void OnEnChangeEditCountProduct();
	CSpinButtonCtrl m_spinCountProduct;
	CEdit m_editCountProduct;
	afx_msg void OnCbnSelchangeComboZakazchik();
	CComboBox m_comboTolschina;
	afx_msg void OnCbnSelchangeComboTolschina();
	CComboBox m_comboMaterial;
	afx_msg void OnCbnSelchangeComboMaterial();
	CEdit m_editDlinaRylona;
	afx_msg void OnEnChangeEditDlinarylona();
	CEdit m_editDlinaEtiketki;
	afx_msg void OnEnChangeEditDlinaetiketki();
	CEdit m_editCountEtiketki;
	CEdit m_editVesTary;
	afx_msg void OnEnChangeEditVesTary();
	afx_msg void OnEnChangeEditCountEtiketki();
	CEdit m_editPartiya;
	afx_msg void OnEnChangeEditPartiya();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonProductExit();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButtonAddzakazchik();
	afx_msg void OnBnClickedButtonAddmaterial();
	afx_msg void OnBnClickedButtonAddtolschina();
	afx_msg void OnBnClickedButtonAddproduct();
	afx_msg void OnBnClickedButtonAddwidth();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_editNumPrintPage;
	CSpinButtonCtrl m_spinNumPrintPage;
	afx_msg void OnEnChangeEditNumprintpage();
	CEdit m_editVhidRylonNetto;
	CEdit m_editVhidRylonBrytto;
	CEdit m_editVhidRylonDlina;
	afx_msg void OnEnChangeEditVhidrylonNetto();
	afx_msg void OnEnChangeEditVhidrylonBrytto();
	afx_msg void OnEnChangeEditVhidrylonDlina();
	afx_msg void OnBnClickedButtonAddvagatary();
	CComboBox m_comboLogo;
	CDateTimeCtrl m_date;
	CComboBox m_comboManager;
};
