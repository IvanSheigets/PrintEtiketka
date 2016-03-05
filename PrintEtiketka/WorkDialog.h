#pragma once

// диалоговое окно CWorkDialog
#include <afxdb.h>

#include "Mystatic.h"
#include "MyListCtrl.h"
#include "MyButton.h"
#include "ChooseRegim2.h"
#include "ChooseProduct.h"
#include "ChangeDlina.h"
#include "EndZakaz.h"
#include "NewVhidRylon.h"
#include "ChangeRylon.h"

#include <vector>
using namespace std;

#include "Barcode.h"

//#include <mysql.h>
//#include <my_global.h>
//#pragma comment(lib, "libmySQL.lib")


struct MyRecord
{
	int iNumList;
	int iListItem;
	int iBarCode;
	double dBrutto;
};

class CWorkDialog : public CDialog
{
	DECLARE_DYNAMIC(CWorkDialog)

public:
	CWorkDialog(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CWorkDialog();

// Данные диалогового окна
	enum { IDD = IDD_DIALOG_WORKDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
private:
	vector <MyRecord>m_vMyRecord;

public:

	
	void SetCountProduct(int);
	void SetZakazchik(CString);
	void SetTolschina(CString);
	void SetMaterial(CString);
	void SetDlinaRylona(int);
	void SetDlinaEtiketki(int);
	void SetCountEtiketki(int);
	//void SetVagaTary(double);
	void SetPartiya(CString);
	void SetProduct(CString *, int );
	void SetManager(CString manager);

	void SetVagaTary(double*, int count);

	void SetCountDorojec(int *,int);
	void SetProductWidth(CString *, int);
	void SetNumPrintPage(int);
	
	void SetVhidRylonNetto(double);
	void SetVhidRylonBrytto(double);
	void SetVhidRylonDlina(int);

	//void SetNumberZakazTK(int iNumberZakaz);

	void SetNumSmena(int);
	void SetNumCar(int);

	void SetMysqlPass(CString);
	void SetMysqlLogin(CString);
	void SetServerAddr(CString);

	void SetLogo(bool);
	void SetData(SYSTEMTIME);

	void P_DrawBarCode(CDC*pDC,const BOOL bPrint, CString strCode/*, CString strProductName, CString strDate*/);
	void P_DrawBarcode(CDC*pDC,int iX,int iY0,int iY10,int iY11,COLORREF clrBar,COLORREF clrSpace,int iPenW,BarcodeBase*pBc,  CString strCode/*, CString strProductName, CString strDate*/);

	int regim;

private:
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
	CString m_strProduct[10];
	int m_iCountDorojec[10];
	double m_dVagaTary[10];
	CString m_strProductWidth[10];

	bool m_bLogo;



//////////////////////////////////////////////////////////////////////////
	
	double m_dZagVhidRylonNetto;
	double m_dZagVhidRylonBrytto;
	int m_iZagVhidRylonDlina;

	double m_dVhidRylonNetto;
	double m_dVhidRylonBrytto;
	int m_iVhidRylonDlina;

	double m_dOstattokKg;
	BOOL m_bNewZakazId;

//////////////////////////////////////////////////////////////////////////
	
	int m_iNumCar;
	int m_iNumSmena;

	int m_iNumZakaz;

	CString m_strServerAddr;
	CString	m_strMysqlLogin;
	CString m_strMysqlPass;

	//////////////////////////////////////////////////////////////////////////
	CStatic m_statBorder;
	
	CStatic m_statBorder2;
	CRect m_rectClient;

	CStatic m_statZakazchik;
	CMyStatic m_myStatZakazchik;

	CStatic m_statTolschina;
	CMyStatic m_myStatTolschina;

	CStatic m_statVagaTary;
	CMyStatic m_myStatVagaTary;

	CStatic m_statPartiya;
	CMyStatic m_myStatPartiya;

	CStatic m_statDlinaRylona;
	CMyStatic m_myStatDlinaRylona;

	CStatic m_statDlinaEtiketki;
	CMyStatic m_myStatDlinaEtiketki;

	CStatic m_statCountEtiketok;
	CMyStatic m_myStatCountEtiketok;

	CStatic m_statMaterial;
	CMyStatic m_myStatMaterial;

	//int m_iNumberZakazTK;

	//////////////////////////////////////////////////////////////////////////
	CMyStatic *m_pmyStatProductName;
	CStatic *m_pstatWidth;
	CMyStatic *m_pmyStatProductWidth;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	CStatic *m_pstatCountDorojec;
	CMyStatic *m_pmyStatCountDorojec;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	CBrush* m_pEditBkBrushActiv;
	//////////////////////////////////////////////////////////////////////////

	CEdit *m_peditVes;
	CMyListCtrl *m_plistTabl;

	//////////////////////////////////////////////////////////////////////////
	CStatic *m_pstatVesNetto;
	CStatic *m_pstatVesBrytto;
	CMyStatic *m_pmyStatVesNetto;
	CMyStatic *m_pmyStatVesBrytto;

	CStatic *m_pstatDlina;
	CMyStatic *m_pmyStatDlina;

	CString m_strObNetto[10];
	CString m_strObBrytto[10];
	double m_dNetto;
	double m_dBrytto;
	double m_dObNetto[10];
	double m_dObBrytto[10];
	int m_iDlinaPorezRylon[10];
	int m_iZagDlinaZakaza;	
	int m_piCountEtiketok[10];
	int m_iZagCountEtiketok;
	//////////////////////////////////////////////////////////////////////////
	int m_iNumList;
	double m_dTempVaga;
	HANDLE hFile;
	void AddProduct();
	int count;

	CStatic m_statProductZagNetto;
	CStatic m_statProductZagBrytto;
	CStatic m_statRylonPorezCount;

	CMyStatic m_myStatProductZagNetto;
	CMyStatic m_myStatProductBrytto;
	CMyStatic m_myStatRylonPorezCount;

	int m_iZagRylonPorezCount;
	double m_dZagNetto;
	double m_dZagBrytto;

	//MYSQL *mysql;
	//MYSQL_RES *res,*res2;
	//MYSQL_ROW row,row2;
	CString query;

	CDatabase m_database;
	CRecordset *m_pRecord;
	CString strData;

	CString QueryResult(CString query);
	int m_iZakazId;
	int m_iProductId;

	CDC dcPrinter;
	void Print (CDC *dc, CString strZakazchik, CString strTovar, CString strMaterial,
		CString strWidth, CString strNumRylon, CString strNetto, CString strBrytto,
		CString strDlina, CString strKolEtik, CString strSmena, CString strPartiya, CString strData);//все
	
	void Print (CDC *dc, CString strZakazchik, CString strTovar, 
		CString strNetto, CString strBrytto,
		CString strSmena, CString strPartiya, CString strData, CString strWidth);//Букурия

	void Print (CDC *dc, CString strZakazchik, 
		CString strNetto, CString strBrytto,
		CString strSmena, CString strPartiya, CString strData);//Звенигород



	CMyButton m_butExit;
	CMyButton m_butNewZakaz;
	CMyButton m_butEndZakaz;

	CMyButton m_butPrintZvit;

	CMyButton m_butNewSmena;
	CMyButton m_butChangeZakaz;

	CChooseRegim2 *m_chooseRegim;
	CChooseProduct *m_chooseProduct;
	CNewVhidRylon *m_newVhidRylon;

	void Initilisation();
	int font_size;

	int m_iOldCountProduct;

	CMyStatic m_statSmena;
	CMyStatic m_myStatSmena;

	CStatusBarCtrl m_status;

	CChangeDlina *m_changeDlina;
	CChangeRylon *m_changeRylon;

	CEndZakaz *m_endZakaz;

	BOOL m_boolNewZakaz;
	BOOL m_boolEndZakaz;

	////endzakaz///
	CStatic m_pstatEndBorder[3];

	CStatic m_pstatEndNameProduct;
	

	CStatic m_pstatEndWidthProduct;
	CMyStatic m_pmystatEndWidthProduct;
	CStatic m_pstatEndCountRylonProduct;
	CMyStatic m_pmystatEndCountRylonProduct;
	CStatic m_pstatEndVesNettoProduct;
	CMyStatic m_pmystatEndVesNettoProduct;
	CStatic m_pstatEndVesBryttoProduct;
	CMyStatic m_pmystatEndVesBryttoProduct;
	CStatic m_pstatEndDlinaProduct;
	CMyStatic m_pmystatEndDlinaProduct;

	CStatic m_pstatEndCountEtiketki;
	CMyStatic m_pmystatEndCountEtiketki;
//////////////////////////////////////////////////////////////////////////

	CStatic m_statVhidRyloniNetto;
	CMyStatic m_myStatVhidRyloniNetto;
	CStatic m_statVhidRyloniBrytto;
	CMyStatic m_myStatVhidRyloniBrytto;

	CStatic m_statVhidRyloniDlina;
	CMyStatic m_myStatVhidRyloniDlina;


	CStatic m_pstatEndZakazKG;
	CMyStatic m_pmystatEndZakazKG;

	CStatic m_pstatEndPrihodKG;
	CMyStatic m_pmystatEndPrihodKG;
	//////////////////////////////////////////////////////////////////////////

	CStatic m_pstatEndObrezok;
	CStatic m_pstatEndOthod;
	CStatic m_pstatEndOstatok;
	CStatic m_pstatEndBrak;
	CStatic m_pstatEndBrakTP;
	CStatic m_statEndOstatokWidth;
	CStatic m_statEndNeDostatok;
	

	CEdit m_peditEndObrezok;
	CEdit m_peditEndOthod;
	CEdit m_peditEndOstatok;
	CEdit m_peditEndBrak;
	CEdit m_peditEndBrakTP;
	CEdit m_peditEndOstatokWidth;
	CEdit m_peditEndNeDostatok;

	CString m_strPrintEtiketka;
	CString m_strPrintShtrih;

	void WriteBD();

	//////////////////////////////////////////////////////////////////////////
	BOOL m_boolButtonExit;
	//////////////////////////////////////////////////////////////////////////





	CStatic m_statEndZagNetto;
	CStatic m_statEndZagBrytto;
	CStatic m_statEndZagCountRylonov;
	CStatic m_statEndZagDlinaRylonov;
	CStatic m_statEndZagCountEtiketok;
	CStatic m_statEndStartTimeZakaz;
	CStatic m_statEndEndTimeZakaz;
	CStatic m_statEndTimeZakaz;

	CMyStatic m_myStatEndZagNetto;
	CMyStatic m_myStatEndZagBrytto;
	CMyStatic m_myStatEndZagCountRylonov;
	CMyStatic m_myStatEndZagDlinaRylonov;
	
	CMyStatic m_myStatEndStartTimeZakaz;
	CMyStatic m_myStatEndEndTimeZakaz;
	CMyStatic m_myStatEndTimeZakaz;
	
	CMyStatic m_myStatEndZagCountEtiketok;
	SYSTEMTIME sysTimeStartWork;
	
	SYSTEMTIME sysDateStartWork;
	SYSTEMTIME sysDataEtiketka;

	int m_piCountRylon[10];
	CListBox m_listEndProduct;

	int m_iNumPrintPage;

	double m_dOthodKG;
	double m_dObrezokKG;
	double m_dBrakKG;
	double m_dBrakTPKG;
	double m_dNedostatokKG;
	double m_dOstatokWidth;

	BOOL m_boolFocusObrezok;
	BOOL m_boolFocusOthod;
	BOOL m_boolFocusOstatok;
	BOOL m_boolFocusOstatokWidth;
	BOOL m_boolFocusBrak;
	BOOL m_boolFocusBrakTP;
	BOOL m_boolFocusNeDostatok;

	////
	CString strZakazchikId;
	CString strProductTolsId;
	CString strProductMaterialId;
	CString strManagerId;
	
	//////////////////////////////////////////////////////////////////////////


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnCompacting(UINT nCpuTime);
//	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonNewZakaz();
	afx_msg void OnBnClickedButtonEndZakaz();
	afx_msg void OnBnClickedButtonNewSmena();
	afx_msg void OnBnClickedButtonPrintZvit();

	afx_msg void OnAccelChangeDlina();
	afx_msg void OnAccelNewRylon();
	afx_msg void OnBnClickedButtonChangeZakaz();
	afx_msg void OnLbnSelchangeEndListProduct();
	
	afx_msg void OnEnChangeEditObrezok();
	afx_msg void OnEnChangeEditOthod();
	afx_msg void OnEnChangeEditBrak();
	afx_msg void OnEnChangeEditBrakTP();
	afx_msg void OnEnChangeEditOstatok();
	afx_msg void OnEnChangeEditNeDostatok();
	
	afx_msg void OnEnSetfocusEditNeDostatok();
	afx_msg void OnEnSetfocusEditOstatokWidth();
	afx_msg void OnEnSetfocusEditOstatok();
	afx_msg void OnEnSetfocusEditBrakTP();
	afx_msg void OnEnSetfocusEditBrak();
	afx_msg void OnEnSetfocusEditOthod();
	afx_msg void OnEnSetfocusEditObrezok();

	afx_msg void OnLvnItemActivateList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateList5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateList6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateList7(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateList8(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateList9(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateList10(NMHDR *pNMHDR, LRESULT *pResult);
	
	void ChangeRylon(int iNumlist, int iItem);
	void PrintProduct(CString);

	

	

protected:
	HACCEL m_hAccel;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnAcceleratorExtadd();
	afx_msg void OnAcceleratorAddobrazets();
};
