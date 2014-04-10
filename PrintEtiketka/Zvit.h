#pragma once

#include "MyStatic.h"
#include "afxdtctl.h"

/*#include <mysql.h>
#include <my_global.h>
#include "afxwin.h"
#pragma comment(lib, "libmySQL.lib")*/

#include "QPrint.h"
#include "AddZakazchik.h"
#include "afxcmn.h"


// диалоговое окно CZvit

class CZvit : public CDialog
{
	DECLARE_DYNAMIC(CZvit)

public:
	CZvit(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CZvit();

	void SetMysqlPass(CString);
	void SetMysqlLogin(CString);
	void SetServerAddr(CString);

private:
	CString m_strServerAddr;
	CString m_strMysqlPass;
	CString m_strMysqlLogin;

//////////////////////////////////////////////////////////////////////////
	CMyStatic m_myStatData;
	CMyStatic m_myStatZakazchik;
	CMyStatic m_myStatProduct;
	
	CMyStatic m_myStatZagVagaNetto;
	CMyStatic m_myStatZagVagaBrytto;
	CMyStatic m_myStatZagCountRylonov;
	CMyStatic m_myStatZagDlinaRylonov;
	CMyStatic m_myStatZagCountEtiketok;
	CMyStatic m_myStatTolschina;
	CMyStatic m_myStatMaterial;
	CMyStatic m_myStatDlinaEtiket;
	CMyStatic m_myStatVagaTary;
	CMyStatic m_myStatPartiya;
	CMyStatic m_myStatTimeStartWork;
	CMyStatic m_myStatTimeEndWork;
	CMyStatic m_myStatTimeWork;
	CMyStatic m_myStatSmena;


	CMyStatic m_myStatZagVagaNettoZnach;
	CMyStatic m_myStatZagVagaBryttoZnach;
	CMyStatic m_myStatZagCountRylonovZnach;
	CMyStatic m_myStatZagDlinaRylonovZnach;
	CMyStatic m_myStatZagCountEtiketokZnach;
	CMyStatic m_myStatTimeStartWorkZnach;
	CMyStatic m_myStatTimeEndWorkZnach;
	CMyStatic m_myStatTimeWorkZnach;
	CMyStatic m_myStatTolschinaZnach;
	CMyStatic m_myStatMaterialZnach;
	CMyStatic m_myStatDlinaEtiketZnach;
	CMyStatic m_myStatVagaTaryZnach;
	CMyStatic m_myStatPartiyaZnach;
	CMyStatic m_myStatSmenaZnach;

	CMyStatic m_myStatWidth;
	CMyStatic m_myStatCountRylonov;
	CMyStatic m_myStatDlinaRylonov;
	CMyStatic m_myStatVagaNetto;
	CMyStatic m_myStatVagaBrytto;
	CMyStatic m_myStatCountEtiketok;

	CMyStatic m_myStatWidthZnach;
	CMyStatic m_myStatCountRylonovZnach;
	CMyStatic m_myStatDlinaRylonovZnach;
	CMyStatic m_myStatVagaNettoZnach;
	CMyStatic m_myStatVagaBryttoZnach;
	CMyStatic m_myStatCountEtiketokZnach;

	CMyStatic m_myStatTU;
	CMyStatic m_myStatMaster;

	CString m_strTU;
	CString m_strDateZakaz;

	CAddZakazchik *m_add;

//////////////////////////////////////////////////////////////////////////
	CRect m_rect;

	/*MYSQL *mysql;
	MYSQL_RES *res,*res2;
	MYSQL_ROW row,row2;
	CString query,query2;*/

//////////////////////////////////////////////////////////////////////////
	int m_iZakazchikId;
	int m_iZakazId;
	int m_iNumZakaz;

	int font_size;
	HACCEL m_hAccel;
	
//////////////////////////////////////////////////////////////////////////

// Данные диалогового окна
	enum { IDD = IDD_DIALOG_ZVIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDtnCloseupDatetimepickerZakaz(NMHDR *pNMHDR, LRESULT *pResult);
	CDateTimeCtrl m_datetimeZakaz;
	//	afx_msg void OnLbnSelchangeListZakazchik();
	
	CListBox m_lsProduct;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLbnSelchangeListproduct();
	CComboBox m_comboTU;
	afx_msg void OnBnClickedButtonAddTu();
	CComboBox m_comboMaster;
	afx_msg void OnCbnSelchangeComboTu();
	afx_msg void OnBnClickedButtonAddMaster();
	afx_msg void OnBnClickedButtonZvitzakazchik();
	afx_msg void OnBnClickedButtonZvitproduct();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedButtonZvitexit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CListCtrl m_listZakzazchik;
	afx_msg void OnLvnItemActivateListZvitZakazchik(NMHDR *pNMHDR, LRESULT *pResult);

};
