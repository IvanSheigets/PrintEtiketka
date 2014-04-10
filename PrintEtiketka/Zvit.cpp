// Zvit.cpp: файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "Zvit.h"
#include "QPrint.h"


// диалоговое окно CZvit

IMPLEMENT_DYNAMIC(CZvit, CDialog)

CZvit::CZvit(CWnd* pParent /*=NULL*/)
	: CDialog(CZvit::IDD, pParent),m_iZakazchikId(0),m_iZakazId(0),m_iNumZakaz(0)
{
	m_hAccel = LoadAccelerators( AfxGetResourceHandle(), MAKEINTRESOURCE( IDR_ACCELERATOR_CLOSEENTER ) );
}

CZvit::~CZvit()
{
}

void CZvit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ZAKAZ, m_datetimeZakaz);
	DDX_Control(pDX, IDC_LIST_product, m_lsProduct);
	DDX_Control(pDX, IDC_COMBO_TU, m_comboTU);
	DDX_Control(pDX, IDC_COMBO_MASTER, m_comboMaster);
	DDX_Control(pDX, IDC_LIST_ZVIT_ZAKAZCHIK, m_listZakzazchik);
}


BEGIN_MESSAGE_MAP(CZvit, CDialog)
	ON_NOTIFY(DTN_CLOSEUP, IDC_DATETIMEPICKER_ZAKAZ, &CZvit::OnDtnCloseupDatetimepickerZakaz)

	ON_BN_CLICKED(IDC_BUTTON1, &CZvit::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST_product, &CZvit::OnLbnSelchangeListproduct)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TU, &CZvit::OnBnClickedButtonAddTu)
	ON_CBN_SELCHANGE(IDC_COMBO_TU, &CZvit::OnCbnSelchangeComboTu)
	ON_BN_CLICKED(IDC_BUTTON_ADD_MASTER, &CZvit::OnBnClickedButtonAddMaster)
	ON_BN_CLICKED(IDC_BUTTON_ZVITZAKAZCHIK, &CZvit::OnBnClickedButtonZvitzakazchik)
	ON_BN_CLICKED(IDC_BUTTON_ZVITPRODUCT, &CZvit::OnBnClickedButtonZvitproduct)
	ON_BN_CLICKED(IDC_BUTTON_ZVITEXIT, &CZvit::OnBnClickedButtonZvitexit)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_ZVIT_ZAKAZCHIK, &CZvit::OnLvnItemActivateListZvitZakazchik)

END_MESSAGE_MAP()


// обработчики сообщений CZvit

BOOL CZvit::OnInitDialog()
{
	CDialog::OnInitDialog();

	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	int iWindowPos = 20;
	//MoveWindow(iWindowPos,iWindowPos,x-iWindowPos*2,y-iWindowPos*2);

	GetClientRect(&m_rect);
	GetDlgItem(IDC_BUTTON_ZVITEXIT)->MoveWindow(m_rect.right-110,m_rect.bottom-50,100,40);

/*	mysql = mysql_init(NULL);
	if (mysql == NULL) 
	{
		MessageBox("Error: Ошибка инищиализации MySql!!!");
		return -1;
	}

	if (mysql_real_connect(mysql, m_strServerAddr, m_strMysqlLogin, m_strMysqlPass, "itak_etiketka", 3306, NULL, 0) == NULL) {
		MessageBox("Не можливо підключитись до бази данних");
		exit(1);
		return -1;
	}
	mysql_query(mysql,"set names 'cp1251'" );*/

	CRect m_listRect;
	m_listZakzazchik.GetClientRect(&m_listRect);
	m_listZakzazchik.InsertColumn(0,"Замовник",LVCFMT_LEFT,/*m_listRect.right/2*/120);
	m_listZakzazchik.InsertColumn(1,"Початок",LVCFMT_LEFT,60);
	m_listZakzazchik.InsertColumn(2,"Партія",LVCFMT_LEFT,50);
	m_listZakzazchik.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	

	font_size = 20;
	m_myStatData.SetFont(font_size);
	m_myStatData.SetTextColor(BLUE_TEXT);
	m_myStatData.Create("Дата виконання замовлення",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+20,m_rect.top+23,m_rect.left+300,m_rect.top+50),this,15001);

	
	m_myStatZakazchik.SetFont(font_size);
	m_myStatZakazchik.Create("Замовник",WS_CHILD|WS_VISIBLE|WS_DISABLED,CRect(m_rect.left+30,m_rect.top+130,m_rect.left+300,m_rect.top+200),this,15002);
	
	m_myStatProduct.SetFont(font_size);
	m_myStatProduct.Create("Продукти",WS_CHILD|WS_VISIBLE|WS_DISABLED,CRect(m_rect.left+30,m_rect.top+300	,m_rect.left+300,m_rect.top+350),this,15003);


	m_myStatZagVagaNetto.Create("Вага нетто:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+400,m_rect.top+75,m_rect.left+550,m_rect.top+95),this,15004);
	m_myStatZagVagaNettoZnach.Create("0 кг",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+560,m_rect.top+75,m_rect.left+650,m_rect.top+95),this,15014);
	m_myStatZagVagaBrytto.Create("Вага брутто:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+400,m_rect.top+95,m_rect.left+550,m_rect.top+115),this,15005);
	m_myStatZagVagaBryttoZnach.Create("0 кг",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+560,m_rect.top+95,m_rect.left+650,m_rect.top+115),this,15015);
	m_myStatZagCountRylonov.Create("К-ть рулонів:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+400,m_rect.top+115,m_rect.left+550,m_rect.top+135),this,15006);
	m_myStatZagCountRylonovZnach.Create("0 шт",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+560,m_rect.top+115,m_rect.left+650,m_rect.top+135),this,15016);	
	m_myStatZagDlinaRylonov.Create("Довжина рулонів:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+400,m_rect.top+135,m_rect.left+550,m_rect.top+155),this,15007);
	m_myStatZagDlinaRylonovZnach.Create("0 м",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+560,m_rect.top+135,m_rect.left+650,m_rect.top+155),this,15017);	
	m_myStatZagCountEtiketok.Create("К-ть етикеток:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+400,m_rect.top+155,m_rect.left+550,m_rect.top+175),this,15008);
	m_myStatZagCountEtiketokZnach.Create("0 шт",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+560,m_rect.top+155,m_rect.left+650,m_rect.top+175),this,15018);	
	m_myStatTolschina.Create("Товщина:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+400,m_rect.top+175,m_rect.left+550,m_rect.top+195),this,15008);
	m_myStatTolschinaZnach.Create("0 мкм",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+560,m_rect.top+175,m_rect.left+650,m_rect.top+195),this,15018);	
	m_myStatMaterial.Create("Матеріал:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+400,m_rect.top+195,m_rect.left+550,m_rect.top+215),this,15009);
	m_myStatMaterialZnach.Create("",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+560,m_rect.top+195,m_rect.left+650,m_rect.top+210),this,15019);	
	m_myStatDlinaEtiket.Create("Довжина етикетки:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+660,m_rect.top+75,m_rect.left+790,m_rect.top+95),this,15020);
	m_myStatDlinaEtiketZnach.Create("0 мм",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+800,m_rect.top+75,m_rect.left+900,m_rect.top+95),this,1521);	
	
	m_myStatPartiya.Create("Партія:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+660,m_rect.top+95,m_rect.left+790,m_rect.top+115),this,15040);
	m_myStatPartiyaZnach.Create("",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+800,m_rect.top+95,m_rect.left+900,m_rect.top+115),this,15041);	
	m_myStatTimeStartWork.Create("Початок роботи:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+660,m_rect.top+115,m_rect.left+790,m_rect.top+135),this,15050);
	m_myStatTimeStartWorkZnach.Create("00:00:00",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+800,m_rect.top+115,m_rect.left+900,m_rect.top+135),this,15051);	
	m_myStatTimeEndWork.Create("Кінець роботи:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+660,m_rect.top+135,m_rect.left+790,m_rect.top+155),this,15060);
	m_myStatTimeEndWorkZnach.Create("00:00:00",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+800,m_rect.top+135,m_rect.left+900,m_rect.top+155),this,15061);	
	m_myStatTimeWork.Create("Час роботи:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+660,m_rect.top+155,m_rect.left+790,m_rect.top+175),this,15070);
	m_myStatTimeWorkZnach.Create("00:00:00",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+800,m_rect.top+155,m_rect.left+900,m_rect.top+175),this,15071);	
	m_myStatSmena.Create("Зміна:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+660,m_rect.top+175,m_rect.left+790,m_rect.top+195),this,15080);
	m_myStatSmenaZnach.Create("0/0",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+800,m_rect.top+175,m_rect.left+900,m_rect.top+195),this,15081);	

	m_myStatWidth.Create("Ширина:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+400,m_rect.top+250,m_rect.left+550,m_rect.top+270),this,15090);
	m_myStatWidthZnach.Create("0 мм",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+560,m_rect.top+250,m_rect.left+650,m_rect.top+270),this,15081);
	m_myStatCountRylonov.Create("К-ть рулонів:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+400,m_rect.top+270,m_rect.left+550,m_rect.top+290),this,15100);
	m_myStatCountRylonovZnach.Create("0 шт",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+560,m_rect.top+270,m_rect.left+650,m_rect.top+290),this,15101);
	m_myStatDlinaRylonov.Create("Довжина рулонів:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+400,m_rect.top+290,m_rect.left+550,m_rect.top+310),this,15103);
	m_myStatDlinaRylonovZnach.Create("0 м",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+560,m_rect.top+290,m_rect.left+650,m_rect.top+310),this,15102);
	m_myStatVagaNetto.Create("Вага нетто:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+400,m_rect.top+310,m_rect.left+550,m_rect.top+330),this,15110);
	m_myStatVagaNettoZnach.Create("0 кг",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+560,m_rect.top+310,m_rect.left+650,m_rect.top+330),this,150111);
	m_myStatVagaBrytto.Create("Вага брутто:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+400,m_rect.top+330,m_rect.left+550,m_rect.top+350),this,15120);
	m_myStatVagaBryttoZnach.Create("0 кг",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+560,m_rect.top+330,m_rect.left+650,m_rect.top+350),this,15121);
	m_myStatCountEtiketok.Create("К-ть етикеток:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+400,m_rect.top+350,m_rect.left+550,m_rect.top+370),this,15130);
	m_myStatCountEtiketokZnach.Create("0 шт",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+560,m_rect.top+350,m_rect.left+650,m_rect.top+370),this,15131);
	m_myStatVagaTary.Create("Вага тари:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+400,m_rect.top+370,m_rect.left+550,m_rect.top+390),this,150030);
	m_myStatVagaTaryZnach.Create("0 кг",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+560,m_rect.top+370,m_rect.left+650,m_rect.top+390),this,15031);	

// 	m_myStatTU.SetFont(font_size);
// 	m_myStatTU.Create("Стандарт:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+30,m_rect.top+405,m_rect.left+550,m_rect.top+500),this,15130);
// 	m_myStatMaster.SetFont(font_size);
// 	m_myStatMaster.Create("Майстер:",WS_CHILD|WS_VISIBLE,CRect(m_rect.left+30,m_rect.top+455,m_rect.left+550,m_rect.top+500),this,15130);

	m_myStatZagVagaNettoZnach.SetTextColor(BLUE_TEXT);
	m_myStatZagVagaBryttoZnach.SetTextColor(BLUE_TEXT);
	m_myStatZagCountRylonovZnach.SetTextColor(BLUE_TEXT);
	m_myStatZagDlinaRylonovZnach.SetTextColor(BLUE_TEXT);
	m_myStatZagCountEtiketokZnach.SetTextColor(BLUE_TEXT);
	m_myStatTimeStartWorkZnach.SetTextColor(BLUE_TEXT);
	m_myStatTimeEndWorkZnach.SetTextColor(BLUE_TEXT);
	m_myStatTimeWorkZnach.SetTextColor(BLUE_TEXT);
	m_myStatTolschinaZnach.SetTextColor(BLUE_TEXT);
	m_myStatMaterialZnach.SetTextColor(BLUE_TEXT);
	m_myStatDlinaEtiketZnach.SetTextColor(BLUE_TEXT);
	m_myStatVagaTaryZnach.SetTextColor(BLUE_TEXT);
	m_myStatPartiyaZnach.SetTextColor(BLUE_TEXT);
	m_myStatSmenaZnach.SetTextColor(BLUE_TEXT);
	m_myStatWidthZnach.SetTextColor(BLUE_TEXT);
	m_myStatCountRylonovZnach.SetTextColor(BLUE_TEXT);
	m_myStatVagaNettoZnach.SetTextColor(BLUE_TEXT);
	m_myStatVagaBryttoZnach.SetTextColor(BLUE_TEXT);
	m_myStatCountEtiketokZnach.SetTextColor(BLUE_TEXT);
	m_myStatDlinaRylonovZnach.SetTextColor(BLUE_TEXT);

// 	query.Format("select tu from itak_tu");
// 	if (mysql_query(mysql,query)!=0) 
// 	{MessageBox("Ошибочный запрос!!!");}
// 	res = mysql_store_result(mysql);
// 	while((row = mysql_fetch_row(res)))
// 		m_comboTU.InsertString(0,row[0]);

// 	query.Format("select master_name from itak_master");
// 	if (mysql_query(mysql,query)!=0) 
// 	{MessageBox("Ошибочный запрос!!!");}
// 	res = mysql_store_result(mysql);
// 	while((row = mysql_fetch_row(res)))
// 		m_comboMaster.InsertString(0,row[0]);


	

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CZvit::SetServerAddr(CString addr)
{
	m_strServerAddr = addr;
}

void CZvit::SetMysqlLogin(CString login)
{
	m_strMysqlLogin = login;
}

void CZvit::SetMysqlPass(CString pass)
{
	m_strMysqlPass = pass;
}

void CZvit::OnDtnCloseupDatetimepickerZakaz(NMHDR *pNMHDR, LRESULT *pResult)
{
	SYSTEMTIME t;
	m_datetimeZakaz.GetTime(&t);	
	m_strDateZakaz.Format("%d-%d-%d",t.wYear,t.wMonth,t.wDay);
	
/*	query.Format("select count(id) from itak_zakaz where datezakaz='%s' ",m_strDateZakaz);
	if (mysql_query(mysql,query)!=0) 
	{
		CString str;
		str.Format("Ошибочный запрос!!! query='%s'",query);
		MessageBox(str);
	}

	res = mysql_store_result(mysql);
	row = mysql_fetch_row(res);

	m_iNumZakaz = atoi(row[0]);
	
	m_listZakzazchik.DeleteAllItems();

	query.Format("select zakazchik_id, timestartzakaz, partiya from itak_zakaz where datezakaz='%s'",m_strDateZakaz);
	if (mysql_query(mysql,query)!=0) 
	{
		CString str;
		str.Format("Ошибочный запрос!!! query='%s'",query);
		MessageBox(str);
	}
	CString str;
	LVITEM item;
	item.mask = LVIF_TEXT;
	int pos = 0;

	res = mysql_store_result(mysql);
	while((row = mysql_fetch_row(res)))
	{
		query2.Format("select zakazchik_name from itak_zakazchik where id=%s",row[0]);
		if (mysql_query(mysql,query2)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query2);
			MessageBox(str);
		}

		res2 = mysql_store_result(mysql);
		while((row2 = mysql_fetch_row(res2)))
		{
			pos = m_listZakzazchik.GetItemCount();
			m_listZakzazchik.InsertItem(pos,row2[0]);
			item.iItem = pos;
			item.pszText = row[1];
			item.iSubItem = 1;
			m_listZakzazchik.SetItem(&item);

			item.iItem = pos;
			item.pszText = row[2];
			item.iSubItem = 2;
			m_listZakzazchik.SetItem(&item);
		}
	}*/
	m_listZakzazchik.EnableWindow(TRUE);
	m_myStatZakazchik.SetTextColor(BLUE_TEXT);
	Invalidate();
	*pResult = 0;
}

void CZvit::OnBnClickedButton1()
{
	CQPrint  prt;
	HPRIVATEFONT   hFont,hFont1,hFont2;
	CSize  dim;
	CRect  margins;

	CString str;

	m_myStatPartiyaZnach.GetWindowText(str);
	CString m_strPartiya = str;

	CString m_strPrihodnaSpechfikaciya = "Hello";
	
//	m_lsZakazchik.GetText(m_lsZakazchik.GetCurSel(),str);
	CString m_strZakazchik = str;
//////////////////////////////////////////////////////////////////////////
	CString m_strAddrZakazchik="вул., Богатирська, 3, тел. 44-412-83-11";

	CString m_strMaterial = "Плівка поліпропіленова з малюнком";
	CString m_strMaster = "sdfsdf";
//////////////////////////////////////////////////////////////////////////

	m_comboTU.GetLBText(m_comboTU.GetCurSel(),str);
	CString m_strTU = str;

	m_myStatSmenaZnach.GetWindowText(str);
	CString m_strSmena = str;

	m_myStatDlinaEtiketZnach.GetWindowText(str);
	CString m_strDlinaEtiketki = str;

	m_myStatTolschinaZnach.GetWindowText(str);
	CString m_strTolschinaEtiketki = str;

	SYSTEMTIME t;
	m_datetimeZakaz.GetTime(&t);	
	
	CString d,m;
	if (t.wDay<10)
		d.Format("0%d",t.wDay);
	else 
		d.Format("%d",t.wDay);

	if (t.wMonth<10)
		m.Format("0%d",t.wMonth);
	else 
		m.Format("%d",t.wMonth);
	
	CString strDateZakaz;
	strDateZakaz.Format("%s.%s.%d",d,m,t.wYear);

	m_myStatWidthZnach.GetWindowText(str);
	CString m_strWidthEtiketka = str;
	
	m_lsProduct.GetText(m_lsProduct.GetCurSel(),str);
	CString strProduct=str;

	m_myStatZagVagaBryttoZnach.GetWindowText(str);
	CString m_strZagBrytto = str;

	m_myStatZagCountEtiketokZnach.GetWindowText(str);
	CString m_strZagCountEtiketki = str;

	m_myStatZagDlinaRylonovZnach.GetWindowText(str);
	CString m_strZagCountRylonov = str;
	
	
	int i=1;
	CString strNetto="10"
		, strBrytto="10",
		strDlina="10",
		strCount="10";
	CString m_strProductRecord;

	char pr[] = "Brother HL-5140 series";
	// initializing the class and printer selection
	if (prt.Dialog(pr) == -1)
		return;

	// create the print document in the spooler
	prt.SetPageOrientation (DMORIENT_PORTRAIT);
	prt.StartPrint();


	// Adding the arial font to the class
	hFont = prt.AddFontToEnvironment("Times New Roman",14,14);
	hFont1 = prt.AddFontToEnvironment("Times New Roman",10,10);
	hFont2 = prt.AddFontToEnvironment("Times New Roman",12,12);

	prt.SetMargins(10,10,10,50);
	prt.SetDistance(5);  

	prt.GetDrawDimension(dim);
	prt.GetMargins(margins);
	//prt.SetHPos(dim.cy-margins.top);
	prt.SetHPos(5);
	// activate a header and footer line
	prt.SetActiveFont (hFont);
	//prt.ActivateHF(HeaderFooter);



	// set margins and line spacing

	prt.StartPage();
	// start printing the lines


	prt.SetFace(hFont,FACE_NORMALBOLD);
	prt.SetFace(hFont1,FACE_BIG);
	prt.lf(hFont2);

	prt.Print(hFont,"Приходна специфікація № _________",FORMAT_NOLF,500); 
	prt.Print(hFont2,m_strPartiya,FORMAT_NOLF,1950); 

	prt.Print(hFont,"Партія № _________",FORMAT_NOLF,3200);    
	prt.Print(hFont2,m_strPartiya,FORMAT_NORMAL,3800);    

	prt.IncrementHPos(20);
	prt.Print(hFont,"Від: ______________________",FORMAT_NOLF,100);    
	prt.Print(hFont2,"",FORMAT_NORMAL,350);  

	int iZakazchikPos = 100;
	prt.IncrementHPos(50);
	prt.Print(hFont1,"Замовник: ",FORMAT_NOLF,iZakazchikPos);    
	prt.IncrementHPos(-30);
	prt.Print(hFont,"«"+m_strZakazchik+"»",FORMAT_NOLF,iZakazchikPos+400); 
	//prt.IncrementHPos(30);
// 	int a = iZakazchikPos+400+m_strZakazchik.GetLength()*100;
// 	prt.Print(hFont1,",Україна, м. Київ",FORMAT_NOLF,a);    


	int iVirobnikPos = 2900;
	prt.Print(hFont1,"Виробник: ",FORMAT_NOLF,iVirobnikPos);    
	prt.IncrementHPos(-30);
	prt.Print(hFont,"ТОВ «ІТАК»",FORMAT_NOLF,iVirobnikPos+400); 
	prt.IncrementHPos(30);
	prt.Print(hFont1,",Україна, м. Київ",FORMAT_NORMAL,iVirobnikPos+1100);    

	prt.IncrementHPos(-10);
//	prt.Print(hFont1,"Україна, м. Київ",FORMAT_NOLF,iZakazchikPos); 
	prt.Print(hFont1,m_strAddrZakazchik,FORMAT_NOLF,iZakazchikPos);    
	prt.IncrementHPos(-10);
	prt.Print(hFont1,"вул., Червоноткацька, 44, тел. 44-574-03-40",FORMAT_NORMAL,iVirobnikPos); 


	int iEtiketkaInfoPos=100;
	prt.IncrementHPos(70);
	HPRIVATEFONT   hFontEtiketkaInfo;
	hFontEtiketkaInfo = prt.AddFontToEnvironment("Times New Roman",14,14);
	prt.Print(hFontEtiketkaInfo,m_strMaterial,FORMAT_NOLF,iEtiketkaInfoPos);    
	int a = iEtiketkaInfoPos + m_strMaterial.GetLength()*60;
	prt.Print(hFont,m_strTU,FORMAT_NORMAL,a);   

	HPRIVATEFONT   hFontEtiketkaInfoBold;
	hFontEtiketkaInfoBold = prt.AddFontToEnvironment("Times New Roman",12,12);
	prt.SetFace(hFontEtiketkaInfoBold,FACE_NORMALBOLD);
	prt.IncrementHPos(-40);
	prt.Print(hFont2,"Ширина етикетки: ",FORMAT_NOLF,iEtiketkaInfoPos);
	prt.Print(hFontEtiketkaInfoBold,m_strWidthEtiketka,FORMAT_NORMAL,iEtiketkaInfoPos+1000);
	prt.IncrementHPos(-40);
	prt.Print(hFont2,"Товщина етикетки: ",FORMAT_NOLF,iEtiketkaInfoPos);
	prt.Print(hFontEtiketkaInfoBold,m_strTolschinaEtiketki,FORMAT_NORMAL,iEtiketkaInfoPos+1000);
	prt.IncrementHPos(-40);
	prt.Print(hFont2,"Довжина етикетки: ",FORMAT_NOLF,iEtiketkaInfoPos);
	prt.Print(hFontEtiketkaInfoBold,m_strDlinaEtiketki,FORMAT_NORMAL,iEtiketkaInfoPos+1000);

	prt.Print(hFont2,"Малюнок:",FORMAT_NOLF,iEtiketkaInfoPos);
	prt.IncrementHPos(-20);
	prt.Print(hFont,"«"+strProduct+"»",FORMAT_NORMAL,iEtiketkaInfoPos+500); 


	//////////////////////////////////////////////////////////////////////////
	prt.lf(hFont2);
	m_lsProduct.GetText(m_lsProduct.GetCurSel(),str);
/*	query.Format("select pz.vesnetto , pz.vesbrytto, pz.dlinarylona, pz.koletiketki from itak_productzakaz pz, itak_zakaz z, itak_product pr where z.id=%d and pz.zakaz_id=z.id and pz.product_id=pr.id and pr.product_name='%s'",m_iZakazId,str);	
	if (mysql_query(mysql,query)!=0) 
	{
		CString str;
		str.Format("Ошибочный запрос!!! query='%s'",query);
		MessageBox(str);
	}

	res = mysql_store_result(mysql);
	int countProduct = mysql_num_rows(res);
	CString *strPr = new CString[countProduct];
	int k=0;
	while((row = mysql_fetch_row(res)))
	{
		strNetto = row[0];
		strBrytto = row[1];
		strDlina = row[2];
		strCount = row[3];
		strPr[k].Format("%d|%s|%s|%s|%s",k+1,strNetto,strBrytto,strDlina,strCount);
		k++;
	}

	int size[11];
	if (countProduct<=18)
	{
		size[0]=50;
		size[1]=230;
		size[2]=260;
		size[3]=400;
		size[4]=360;
		prt.SetTableColumnsSize(5,size);
	}
	else 
	{
		size[0]=50;
		size[1]=230;
		size[2]=260;
		size[3]=400;
		size[4]=360;

		size[5]=0;
		size[6]=230;
		size[7]=260;
		size[8]=400;
		size[9]=360;
		prt.SetTableColumnsSize(10,size);
	}

	prt.SetTableHorLine (TRUE);
	prt.SetTableVerLine (TRUE);
	prt.SetTableBorderSize (200);
	prt.SetTableJustify(FORMAT_CENTER);
	prt.SetTableBorderLine(3);
	//set the headers
	HPRIVATEFONT   hFontTableHeader;
	hFontTableHeader = prt.AddFontToEnvironment("Times New Roman",10,10);
	prt.SetFace (hFontTableHeader,FACE_NORMALBOLD);

	if (countProduct<=18)
	{
		prt.AddTableRecord (hFontTableHeader,"№|Нетто кг|Брутто кг|Довжина м.п.|К-ть тис.шт",FORMAT_CENTER);
		prt.SetFace (hFontTableHeader,FACE_NORMAL);
		for (int i=0;i<countProduct;i++)
		{
			m_strProductRecord = strPr[i];
			prt.AddTableRecord (hFontTableHeader,m_strProductRecord,FORMAT_CENTER);
		}		
	}
	else
	{
		prt.SetFace (hFontTableHeader,FACE_NORMALBOLD);
		prt.AddTableRecord (hFontTableHeader,"№|Нетто кг|Брутто кг|Довжина м.п.|К-ть тис.шт|№|Нетто кг|Брутто кг|Довжина м.п.|К-ть тис.шт",FORMAT_CENTER);
		prt.SetFace (hFontTableHeader,FACE_NORMAL);
		for (int i=0;i<countProduct/2+1;i++)
		{
			if (i+countProduct/2+1 == countProduct)
			{
				strPr[0].Format(" | | | | ");
				m_strProductRecord.Format("%s|%s",strPr[i],strPr[0]);
				prt.AddTableRecord (hFontTableHeader,m_strProductRecord,FORMAT_CENTER);
			}
			else
			{
				m_strProductRecord.Format("%s|%s",strPr[i],strPr[i+countProduct/2+1]);
				prt.AddTableRecord (hFontTableHeader,m_strProductRecord,FORMAT_CENTER);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	int iZagPos=100;
	prt.lf(hFont2);
	HPRIVATEFONT hFontZagFontNormal = prt.AddFontToEnvironment("Times New Roman",12,12);
	HPRIVATEFONT hFontZagFontBold = prt.AddFontToEnvironment("Times New Roman",12,12);
	prt.SetFace (hFontZagFontNormal,FACE_NORMAL);
	prt.SetFace (hFontZagFontBold,FACE_NORMALBOLD);

	prt.Print(hFontZagFontNormal,"Маса брутто: _______________",FORMAT_NOLF,iZagPos);
	prt.IncrementHPos(-10);
	prt.Print(hFontZagFontBold,m_strZagBrytto,FORMAT_NOLF,iZagPos+620);

	prt.Print(hFontZagFontNormal,"Дата виготовлення ________________",FORMAT_NOLF,iZagPos+2700);
	prt.IncrementHPos(-10);
	prt.Print(hFontZagFontBold,strDateZakaz,FORMAT_NORMAL,iZagPos+3600);



	prt.IncrementHPos(-10);
	prt.Print(hFontZagFontNormal,"К-ть рулонів: _______________ ",FORMAT_NOLF,iZagPos);
	prt.IncrementHPos(-10);
	prt.Print(hFontZagFontBold,m_strZagCountRylonov,FORMAT_NORMAL,iZagPos+620);

	prt.IncrementHPos(-20);
	prt.Print(hFontZagFontNormal,"К-ть етикетки тис.шт: _______________",FORMAT_NOLF,iZagPos);
	prt.IncrementHPos(-10);
	prt.Print(hFontZagFontBold,m_strZagCountEtiketki,FORMAT_NOLF,iZagPos+1000);

	prt.Print(hFontZagFontNormal,"Зміна: _____",FORMAT_NOLF,iZagPos+2700);
	prt.IncrementHPos(-10);
	prt.Print(hFontZagFontBold,m_strSmena,FORMAT_NOLF,iZagPos+3050);

	prt.Print(hFontZagFontNormal,"Мастер: _____________",FORMAT_NOLF,iZagPos+3300);
	prt.IncrementHPos(-10);
	prt.Print(hFontZagFontBold,m_strMaster,FORMAT_NORMAL,iZagPos+3700);

	prt.lf(hFont2);

	prt.Print(hFont,"Термін зберігання - 6 місяців від дати виготовлення.",FORMAT_NORMAL,100); 
	prt.Print(hFontZagFontBold,"Умови зберігання:",FORMAT_NORMAL,100); 
	prt.Print(hFontZagFontBold,"Плівка повинна зберігатися в закритому приміщенні при температурі від +5С до +25С і відносній ",FORMAT_NORMAL,200); 
	prt.IncrementHPos(-10);
	prt.Print(hFontZagFontBold,"вологості  повітря  не  більше  80%, на  відстані  не  менш  1  метра  від  нагріваючих  пристроїв, в ",FORMAT_NORMAL,200); 
	prt.IncrementHPos(-10);
	prt.Print(hFontZagFontBold,"захищеному  місці  від  дії  прямих  сонячних  променів, при  відсутності  у  приміщенні  кислотно",FORMAT_NORMAL,200); 
	prt.IncrementHPos(-10);
	prt.Print(hFontZagFontBold,"лужних та інших агресивних середовищ.",FORMAT_NORMAL,200); 


	// now end the page
	prt.EndPage();

	// close the print document and release it in the spooler
	prt.EndPrint();*/
}

void CZvit::OnLbnSelchangeListproduct()
{
	CString str;
	int pos = m_lsProduct.GetCurSel();
	m_lsProduct.GetText(pos,str);
	if (str.GetLength()!=0)
	{
		m_myStatWidthZnach.SetTextColor(BLUE_TEXT);
		m_myStatCountRylonovZnach.SetTextColor(BLUE_TEXT);
		m_myStatVagaNettoZnach.SetTextColor(BLUE_TEXT);
		m_myStatVagaBryttoZnach.SetTextColor(BLUE_TEXT);
		m_myStatCountEtiketokZnach.SetTextColor(BLUE_TEXT);
		m_myStatDlinaRylonovZnach.SetTextColor(BLUE_TEXT);
		m_myStatVagaTaryZnach.SetTextColor(BLUE_TEXT);

		/*query.Format("select id from itak_product where product_name='%s'",str);
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}

		double dTemp = 0;
		res = mysql_store_result(mysql);
		//while((row = mysql_fetch_row(res)))
		row = mysql_fetch_row(res);
		{
			query2.Format("select sum(brytto),sum(dlinarylona), sum(koletiketki),count(id), sum(vagatary) from itak_vihidrylon where zakaz_id=%d and product_id=%s",m_iZakazId,row[0]);
			if (mysql_query(mysql,query2)!=0) 
			{
				CString str;
				str.Format("Ошибочный запрос!!! query='%s'",query2);
				MessageBox(str);
			}
			
			res2 = mysql_store_result(mysql);
			while((row2 = mysql_fetch_row(res2)))
			{
				dTemp = atof(row2[0]);
				str.Format("%.2f кг", dTemp);
				m_myStatVagaBryttoZnach.SetWindowText(str);

				dTemp = atof(row2[0]) - atof(row2[4]);
				str.Format("%.2f кг", dTemp);
				m_myStatVagaNettoZnach.SetWindowText(str);

				str.Format("%s м", row2[1]);
				m_myStatDlinaRylonovZnach.SetWindowText(str);

				str.Format("%s шт", row2[2]);
				m_myStatCountEtiketokZnach.SetWindowText(str);

				str.Format("%s шт", row2[3]);
				m_myStatCountRylonovZnach.SetWindowText(str);

			}
		
			query2.Format("select width,vagatary from itak_vihidrylon where zakaz_id=%d and product_id=%s",m_iZakazId,row[0]);
			if (mysql_query(mysql,query2)!=0) 
			{
				CString str;
				str.Format("Ошибочный запрос!!! query='%s'",query2);
				MessageBox(str);
			}
			res2 = mysql_store_result(mysql);
			while((row2 = mysql_fetch_row(res2)))
			{
				str.Format("%s мм", row2[0]);
				m_myStatWidthZnach.SetWindowText(str);
				str.Format("%s кг",row2[1]);
				m_myStatVagaTaryZnach.SetWindowText(str);
			}
		}*/

	}
	if (GetDlgItem(IDC_BUTTON_ZVITPRODUCT)->IsWindowEnabled()==FALSE)
		GetDlgItem(IDC_BUTTON_ZVITPRODUCT)->EnableWindow(TRUE);
}

void CZvit::OnBnClickedButtonAddTu()
{
	/*CString str;
	m_add = new CAddZakazchik;
	m_add->SetName("Додати стандарт");
	if (m_add->DoModal()==IDOK)
	{
		str = m_add->GetData();
		query.Format("insert into itak_tu (tu) value ('%s')",str);
		if (mysql_query(mysql,query)!=0) 
		{MessageBox("Ошибочный запрос!!!");}

		for (int i=m_comboTU.GetCount();i>=0;i--)
			m_comboTU.DeleteString(i);

		query.Format("select tu from itak_tu");
		if (mysql_query(mysql,query)!=0) 
		{MessageBox("Ошибочный запрос!!!");}
		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
			m_comboTU.InsertString(0,row[0]);

		
	}
	delete m_add;*/
}

void CZvit::OnCbnSelchangeComboTu()
{
// 	if(GetDlgItem(IDC_COMBO_MASTER)->IsWindowEnabled()==FALSE)
// 	{
// 		GetDlgItem(IDC_COMBO_MASTER)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_BUTTON_ADD_MASTER)->EnableWindow(TRUE);
// 		m_myStatMaster.SetTextColor(BLUE_TEXT);
// 	}
}

void CZvit::OnBnClickedButtonAddMaster()
{
	/*CString str;
	m_add = new CAddZakazchik;
	m_add->SetName("Додати майстра");
	if (m_add->DoModal()==IDOK)
	{
		str = m_add->GetData();
		query.Format("insert into itak_master (master_name) value ('%s')",str);
		if (mysql_query(mysql,query)!=0) 
		{MessageBox("Ошибочный запрос!!!");}

		for (int i=m_comboMaster.GetCount();i>=0;i--)
			m_comboTU.DeleteString(i);

		query.Format("select master_name from itak_master");
		if (mysql_query(mysql,query)!=0) 
		{MessageBox("Ошибочный запрос!!!");}
		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
			m_comboMaster.InsertString(0,row[0]);
	}
	delete m_add;	*/
}



void CZvit::OnBnClickedButtonZvitzakazchik()
{
/*	CQPrint  prt;
	HPRIVATEFONT   hFont14x14, hFont14x14Bold, hFont12x12, hFont12x12Bold,hFont10x10, hFont10x10Bold;
	CSize  dim;
	CRect  margins;
	double dTemp = 0 ;
	int iTemp = 0 ;

	CString str;

//	m_lsZakazchik.GetText(m_lsZakazchik.GetCurSel(),str);
	
	CString strZakazchik = m_listZakzazchik.GetItemText(m_listZakzazchik.GetSelectionMark(),0);

	FILE * file;
	file = fopen("settings.txt","rb");
	if (file!=NULL)
	{
		char buf[1024];
		while (fgets(buf,1000,file)!='\0')
		{
			str.Format("%s",buf);
			str.Remove('\n');
			if (str.Left(str.Find(" "))=="printZvit")
			{
				str=str.Mid(str.Find(" ")+3);
				break;
			}

		}
		fclose(file);
	}
	//char pr[] = "Brother HL-5140 series";
	// initializing the class and printer selection
	if (str.GetLength()!=0)
	{
		if (prt.Dialog(str.GetBuffer(str.GetLength())) == -1)
			return;

		// create the print document in the spooler
		prt.SetPageOrientation (DMORIENT_PORTRAIT);
		prt.StartPrint();

		prt.SetMargins(10,10,10,50);
		prt.SetDistance(5);  
		// 
		prt.GetDrawDimension(dim);
		prt.GetMargins(margins);
		prt.SetHPos(5);
		// 	// activate a header and footer line


		// set margins and line spacing

		prt.StartPage();
		// start printing the lines
		hFont14x14 = prt.AddFontToEnvironment("Times New Roman",14,14);
		hFont14x14Bold = prt.AddFontToEnvironment("Times New Roman",14,14);
		prt.SetFace(hFont14x14Bold,FACE_NORMALBOLD);

		hFont12x12 = prt.AddFontToEnvironment("Times New Roman",12,12);
		hFont12x12Bold = prt.AddFontToEnvironment("Times New Roman",12,12);
		prt.SetFace(hFont12x12Bold,FACE_NORMALBOLD);

		hFont10x10 = prt.AddFontToEnvironment("Times New Roman",8,8);
		hFont10x10Bold = prt.AddFontToEnvironment("Times New Roman",10,10);
		prt.SetFace(hFont10x10Bold,FACE_NORMALBOLD);

		prt.lf(hFont14x14Bold);

		prt.Print(hFont14x14,"Замовник:",FORMAT_NOLF,200); 
		prt.Print(hFont14x14Bold,strZakazchik,FORMAT_NORMAL,800); 

		prt.lf(hFont14x14Bold);
		int size[9];
		size[0]=50;			//№
		size[1]=1100;		//product
		size[2]=270;		//width
		size[3]=490;		//count rylon
		size[4]=530;		//count etik
		size[5]=290;		//dlina
		size[6]=150;		//netto
		size[7]=200;		//brytto

		prt.SetTableColumnsSize(8,size);

		prt.SetTableHorLine (TRUE);
		prt.SetTableVerLine (TRUE);
		prt.SetTableBorderSize (200);
		prt.SetTableJustify(FORMAT_CENTER);
		prt.SetTableBorderLine(3);
		// 	//set the headers
		prt.AddTableRecord (hFont12x12Bold,"№|Продукція|Ширина|К-ть рулонів|К-ть етикеток|Довжина|Нетто|Брутто",FORMAT_CENTER);

		int i=1;
		double dTemp = 0;
		query.Format("select DISTINCT pr.product_name, pz.width from itak_vihidrylon pz, itak_product pr where pz.zakaz_id=%d and pr.id=pz.product_id",m_iZakazId);	
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}
		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
		{
			query2.Format("select count(pz.id),sum(pz.koletiketki), sum(pz.dlinarylona),  sum(pz.brytto),sum(pz.vagatary) from itak_vihidrylon pz, itak_product pr where pz.zakaz_id=%d and pz.product_id=pr.id and pr.product_name='%s'",m_iZakazId,row[0]);
			if (mysql_query(mysql,query2)!=0) 
			{
				CString str;
				str.Format("Ошибочный запрос!!! query='%s'",query2);
				MessageBox(str);
			}
			res2 = mysql_store_result(mysql);
			while((row2 = mysql_fetch_row(res2)))
			{
				dTemp = atof(row2[3])- atof(row2[4]);
				str.Format("%d|%s|%s|%s|%s|%s|%.2f|%s",i++,row[0],row[1],row2[0],row2[1],row2[2],dTemp,row2[3]);
				prt.AddTableRecord (hFont10x10,str,FORMAT_CENTER);
			}
		}

		prt.lf(hFont12x12Bold);

		query2.Format("select sum(brytto),sum(vagatary),count(id),sum(dlinarylona),sum(koletiketki) from itak_vihidrylon where zakaz_id=%d",m_iZakazId);
		if (mysql_query(mysql,query2)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query2);
			MessageBox(str);
		}
		res2 = mysql_store_result(mysql);
		while((row2 = mysql_fetch_row(res2)))
		{

			dTemp = atof(row2[0]) - atof(row2[1]);
			str.Format("%.2f кг",dTemp);
			prt.Print(hFont12x12,"Загальна вага нето:",FORMAT_NOLF,200); 
			prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 

			prt.IncrementHPos(-40);
			dTemp = atof(row2[0]);
			str.Format("%.2f кг",dTemp);
			prt.Print(hFont12x12,"Загальна вага брутто:",FORMAT_NOLF,200); 
			prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 

			prt.IncrementHPos(-40);
			str.Format("%s шт",row2[2]);
			prt.Print(hFont12x12,"Загальна к-ть рулонів:",FORMAT_NOLF,200); 
			prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 

			prt.IncrementHPos(-40);
			iTemp = atoi(row2[3]);
			str.Format("%d м",iTemp);
			prt.Print(hFont12x12,"Загальна довжина рулонів:",FORMAT_NOLF,200); 
			prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 

			prt.IncrementHPos(-40);
			iTemp = atoi(row2[4]);
			str.Format("%d шт",iTemp);
			prt.Print(hFont12x12,"Загальна к-ть етикетки:",FORMAT_NOLF,200); 
			prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 
		}

		query.Format("select dlinaetiketki,partiya,machine,smena,timestartzakaz,timeendzakaz,time,partiya,machine,smena,dlinaetiketki  "
			"from itak_zakaz  where id=%d",m_iZakazId);
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}
		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
		{
			prt.IncrementHPos(-40);
			str.Format("%s мм",row[0]);
			prt.Print(hFont12x12,"Довжина етикетки:",FORMAT_NOLF,200); 
			prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 

			query2.Format("select pm.product_material from itak_productmaterial pm, itak_zakaz z  where z.id=%d and z.productmaterial_id=pm.id",m_iZakazId);
			if (mysql_query(mysql,query2)!=0) 
			{
				CString str;
				str.Format("Ошибочный запрос!!! query='%s'",query2);
				MessageBox(str);
			}
			res2 = mysql_store_result(mysql);
			while((row2 = mysql_fetch_row(res2)))
			{
				prt.IncrementHPos(-40);
				prt.Print(hFont12x12,"Матеріал:",FORMAT_NOLF,200); 
				prt.Print(hFont12x12Bold,row2[0],FORMAT_NORMAL,1500); 
			}
		 
			query2.Format("select pt.product_tols from itak_producttols pt,itak_zakaz z where z.id=%d and z.producttols_id=pt.id",m_iZakazId);
			if (mysql_query(mysql,query2)!=0) 
			{
				CString str;
				str.Format("Ошибочный запрос!!! query='%s'",query2);
				MessageBox(str);
			}
			res2 = mysql_store_result(mysql);
			while((row2 = mysql_fetch_row(res2)))
			{
				prt.IncrementHPos(-40);
				str.Format("%s мкм",row2[0]);
				prt.Print(hFont12x12,"Товщина:",FORMAT_NOLF,200); 
				prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 
			}

			prt.IncrementHPos(-40);
			prt.Print(hFont12x12,"Партія:",FORMAT_NOLF,200); 
			prt.Print(hFont12x12Bold,row[1],FORMAT_NORMAL,1500); 
 
			prt.IncrementHPos(-40);
			str.Format("%s/%s",row[2],row[3]);
			prt.Print(hFont12x12,"Зміна:",FORMAT_NOLF,200); 
			prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500);

			query2.Format("select obrezok, othod, brak, braktp, ostatok, nedostatok  from itak_othod where zakaz_id=%d",m_iZakazId);
			if (mysql_query(mysql,query2)!=0) 
			{
				CString str;
				str.Format("Ошибочный запрос!!! query='%s'",query2);
				MessageBox(str);
			}
			res2 = mysql_store_result(mysql);
			while((row2 = mysql_fetch_row(res2)))
			{
				prt.IncrementHPos(-40);
				dTemp = atof(row2[0]);
				str.Format("%.2f кг",dTemp);
				prt.Print(hFont12x12,"Обрізок:",FORMAT_NOLF,200); 
				prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 

				prt.IncrementHPos(-40);
				dTemp = atof(row2[1]);
				str.Format("%.2f кг",dTemp);
				prt.Print(hFont12x12,"Отход:",FORMAT_NOLF,200); 
				prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 

				prt.IncrementHPos(-40);
				dTemp = atof(row2[2]);
				str.Format("%.2f кг",dTemp);
				prt.Print(hFont12x12,"Брак:",FORMAT_NOLF,200); 
				prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500);

				prt.IncrementHPos(-40);
				dTemp = atof(row2[3]);
				str.Format("%.2f кг",dTemp);
				prt.Print(hFont12x12,"Брак друку:",FORMAT_NOLF,200); 
				prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500);

				prt.IncrementHPos(-40);
				dTemp = atof(row2[4]);
				str.Format("%.2f кг",dTemp);
				prt.Print(hFont12x12,"Залишок:",FORMAT_NOLF,200); 
				prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500);

				prt.IncrementHPos(-40);
				dTemp = atof(row2[5]);
				str.Format("%.2f кг",dTemp);
				prt.Print(hFont12x12,"Недостача:",FORMAT_NOLF,200); 
				prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500);

			}
			prt.IncrementHPos(-40);
			prt.Print(hFont12x12,"Початок роботи:",FORMAT_NOLF,200); 
			prt.Print(hFont12x12Bold,row[4],FORMAT_NORMAL,1500); 

			prt.IncrementHPos(-40);
			prt.Print(hFont12x12,"Кінець роботи:",FORMAT_NOLF,200); 
			prt.Print(hFont12x12Bold,row[5],FORMAT_NORMAL,1500); 

			prt.IncrementHPos(-40);
			prt.Print(hFont12x12,"Час роботи:",FORMAT_NOLF,200); 
			prt.Print(hFont12x12Bold,row[6],FORMAT_NORMAL,1500); 
		}

			SYSTEMTIME t;
			m_datetimeZakaz.GetTime(&t);	

			CString d,m;
			if (t.wDay<10)
				d.Format("0%d",t.wDay);
			else 
				d.Format("%d",t.wDay);

			if (t.wMonth<10)
				m.Format("0%d",t.wMonth);
			else 
				m.Format("%d",t.wMonth);
			str.Format("%s.%s.%d",d,m,t.wYear);

			prt.IncrementHPos(-40);
			prt.Print(hFont12x12,"Дата виконання замовлення:",FORMAT_NOLF,200); 
			prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 
 
			GetSystemTime(&t);
			if (t.wDay<10)
				d.Format("0%d",t.wDay);
			else 
				d.Format("%d",t.wDay);

			if (t.wMonth<10)
				m.Format("0%d",t.wMonth);
			else 
			m.Format("%d",t.wMonth);
			str.Format("%s.%s.%d",d,m,t.wYear);
			prt.IncrementHPos(-40);
			prt.Print(hFont12x12,"Дата друку звіту:",FORMAT_NOLF,200); 
			prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 

		prt.EndPage();
		prt.EndPrint();
	}*/
	
}

void CZvit::OnBnClickedButtonZvitproduct()
{
	/*CQPrint  prt;

	HPRIVATEFONT   hFont14x14, hFont14x14Bold, hFont12x12, hFont12x12Bold,hFont10x10, hFont10x10Bold;

	CSize  dim;
	CRect  margins;

	int iTemp = 0;
	double dTemp = 0;
	
	CString str;

//	m_lsZakazchik.GetText(m_lsZakazchik.GetCurSel(),str);
	CString strZakazchik = m_listZakzazchik.GetItemText(m_listZakzazchik.GetSelectionMark(),0);

	m_lsProduct.GetText(m_lsProduct.GetCurSel(),str);
	CString strProduct = str;
	

	FILE * file;
	file = fopen("settings.txt","rb");
	if (file!=NULL)
	{
		char buf[1024];
		while (fgets(buf,1000,file)!='\0')
		{
			str.Format("%s",buf);
			str.Remove('\n');
			if (str.Left(str.Find(" "))=="printZvit")
			{
				str=str.Mid(str.Find(" ")+3);
				break;
			}			
		}
		fclose(file);
	}
	//char pr[] = "Brother HL-5140 series";
	// initializing the class and printer selection
	if (str.GetLength()!=0)
	{
		if (prt.Dialog(str.GetBuffer(str.GetLength())) == -1)
			return;

		// create the print document in the spooler
		prt.SetPageOrientation (DMORIENT_PORTRAIT);
		prt.StartPrint();

		prt.SetMargins(10,10,10,50);
		prt.SetDistance(5);  
		// 
		prt.GetDrawDimension(dim);
		prt.GetMargins(margins);
		prt.SetHPos(5);
		// 	// activate a header and footer line


		// set margins and line spacing

		prt.StartPage();
		// start printing the lines
		hFont14x14 = prt.AddFontToEnvironment("Times New Roman",14,14);
		hFont14x14Bold = prt.AddFontToEnvironment("Times New Roman",14,14);
		prt.SetFace(hFont14x14Bold,FACE_NORMALBOLD);

		hFont12x12 = prt.AddFontToEnvironment("Times New Roman",12,12);
		hFont12x12Bold = prt.AddFontToEnvironment("Times New Roman",12,12);
		prt.SetFace(hFont12x12Bold,FACE_NORMALBOLD);

		hFont10x10 = prt.AddFontToEnvironment("Times New Roman",8,8);
		hFont10x10Bold = prt.AddFontToEnvironment("Times New Roman",10,10);
		prt.SetFace(hFont10x10Bold,FACE_NORMALBOLD);

		prt.lf(hFont14x14Bold);

		prt.Print(hFont14x14,"Замовник:",FORMAT_NOLF,200); 
		prt.Print(hFont14x14Bold,strZakazchik,FORMAT_NORMAL,800); 

		prt.Print(hFont14x14,"Продукція:",FORMAT_NOLF,200); 
		prt.Print(hFont14x14Bold,strProduct,FORMAT_NORMAL,800); 

		prt.lf(hFont14x14Bold);
		query.Format("select pz.vagatary , pz.brytto, pz.dlinarylona, pz.koletiketki from itak_vihidrylon pz, itak_zakaz z, itak_product pr where z.id=%d and pz.zakaz_id=z.id and pz.product_id=pr.id and pr.product_name='%s'",m_iZakazId,strProduct);	
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}
		res = mysql_store_result(mysql);
		int countProduct = mysql_num_rows(res);

		int i=1;
		CString strNetto="10"
			, strBrytto="10",
			strDlina="10",
			strCount="10";
		CString m_strProductRecord;
		CString *strPr = new CString[countProduct];
		int k=0;
		while((row = mysql_fetch_row(res)))
		{
			dTemp = atof(row[1]) - atof(row[0]);
			strNetto.Format("%.2f",dTemp);
			strBrytto = row[1];
			strDlina = row[2];
			strCount = row[3];
			strPr[k].Format("%d|%s|%s|%s|%s",k+1,strNetto,strBrytto,strDlina,strCount);
			k++;
		}

		int size[11];
		if (countProduct<=25)
		{
			size[0]=50;
			size[1]=230;
			size[2]=260;
			size[3]=400;
			size[4]=360;
			prt.SetTableColumnsSize(5,size);
		}
		else 
		{
			size[0]=50;
			size[1]=230;
			size[2]=260;
			size[3]=400;
			size[4]=360;

			size[5]=0;
			size[6]=230;
			size[7]=260;
			size[8]=400;
			size[9]=360;
			prt.SetTableColumnsSize(10,size);
		}

		prt.SetTableHorLine (TRUE);
		prt.SetTableVerLine (TRUE);
		prt.SetTableBorderSize (200);
		prt.SetTableJustify(FORMAT_CENTER);
		prt.SetTableBorderLine(3);
		//set the headers
		HPRIVATEFONT   hFontTableHeader;
		hFontTableHeader = prt.AddFontToEnvironment("Times New Roman",10,10);
		prt.SetFace (hFontTableHeader,FACE_NORMALBOLD);

		if (countProduct<=25)
		{
			prt.AddTableRecord (hFontTableHeader,"№|Нетто кг|Брутто кг|Довжина м.п.|К-ть тис.шт",FORMAT_CENTER);
			prt.SetFace (hFontTableHeader,FACE_NORMAL);
			for (int i=0;i<countProduct;i++)
			{
				m_strProductRecord = strPr[i];
				prt.AddTableRecord (hFontTableHeader,m_strProductRecord,FORMAT_CENTER);
			}		
		}
		else
		{
			//////////////////////////////////////////////////////////////////////////
			//owibka
			prt.SetFace (hFontTableHeader,FACE_NORMALBOLD);
			prt.AddTableRecord (hFontTableHeader,"№|Нетто кг|Брутто кг|Довжина м.п.|К-ть тис.шт|№|Нетто кг|Брутто кг|Довжина м.п.|К-ть тис.шт",FORMAT_CENTER);
			prt.SetFace (hFontTableHeader,FACE_NORMAL);
			if (countProduct%2!=0)
			{
				for (int i=0;i<countProduct/2+1;i++)
				{
					if (i+countProduct/2+1 == countProduct)
					{
						strPr[0].Format(" | | | | ");
						m_strProductRecord.Format("%s|%s",strPr[i],strPr[0]);
						prt.AddTableRecord (hFontTableHeader,m_strProductRecord,FORMAT_CENTER);
					}
					else
					{
						m_strProductRecord.Format("%s|%s",strPr[i],strPr[i+countProduct/2+1]);
						prt.AddTableRecord (hFontTableHeader,m_strProductRecord,FORMAT_CENTER);
					}
				}
			}
			else
			{
				for (int i=0;i<countProduct/2;i++)
				{
					m_strProductRecord.Format("%s|%s",strPr[i],strPr[i+countProduct/2]);
					prt.AddTableRecord (hFontTableHeader,m_strProductRecord,FORMAT_CENTER);
				}
			}
			//////////////////////////////////////////////////////////////////////////
		}

		query.Format("select id from itak_product where product_name='%s'",strProduct);
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}
		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
		{
			query2.Format("select sum(vagatary), sum(brytto),sum(dlinarylona), sum(koletiketki),count(id) from itak_vihidrylon where zakaz_id=%d and product_id=%s",m_iZakazId,row[0]);
			if (mysql_query(mysql,query2)!=0) 
			{
				CString str;
				str.Format("Ошибочный запрос!!! query='%s'",query2);
				MessageBox(str);
			}
			res2 = mysql_store_result(mysql);
			while((row2 = mysql_fetch_row(res2)))
			{

				dTemp = atof(row2[1]) - atof(row2[0]);
				str.Format("%.2f кг", dTemp);
				prt.Print(hFont12x12,"Загальна вага нето:",FORMAT_NOLF,200); 
				prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 

				prt.IncrementHPos(-40);
				dTemp = atof(row2[1]);
				str.Format("%.2f кг", dTemp);
				prt.Print(hFont12x12,"Загальна вага брутто:",FORMAT_NOLF,200); 
				prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 

				prt.IncrementHPos(-40);
				str.Format("%s м", row2[2]);
				prt.Print(hFont12x12,"Загальна довжина рулонів:",FORMAT_NOLF,200); 
				prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 

				prt.IncrementHPos(-40);
				str.Format("%s шт", row2[4]);
				prt.Print(hFont12x12,"Загальна к-ть рулонів:",FORMAT_NOLF,200); 
				prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 

				prt.IncrementHPos(-40);
				str.Format("%s шт", row2[3]);
				prt.Print(hFont12x12,"Загальна к-ть етикетки:",FORMAT_NOLF,200); 
				prt.Print(hFont12x12Bold,str,FORMAT_NORMAL,1500); 
			}
		}

		// now end the page
		prt.EndPage();

		// close the print document and release it in the spooler
		prt.EndPrint();
	}*/
}

void CZvit::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса

	CDialog::OnOK();
}

void CZvit::OnCancel()
{
	// TODO: добавьте специализированный код или вызов базового класса

//	CDialog::OnCancel();
}

void CZvit::OnBnClickedButtonZvitexit()
{
	OnOK();
}

BOOL CZvit::PreTranslateMessage(MSG* pMsg)
{
	if ( TranslateAccelerator( m_hWnd, m_hAccel, pMsg ) ) return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}


void CZvit::OnLvnItemActivateListZvitZakazchik(NMHDR *pNMHDR, LRESULT *pResult)
{
	/*LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	CString str;
	double dTemp = 0;
	int iTemp = 0;
	int pos = pNMIA->iItem;
	
	CString strZakazchik = m_listZakzazchik.GetItemText(pos,0);
	CString strStartTime = m_listZakzazchik.GetItemText(pos,1);

 	if (strZakazchik.GetLength()!=0)
 	{
 		for (int i=m_lsProduct.GetCount();i>=0;i--)
 			m_lsProduct.DeleteString(i);

		query.Format("select DISTINCT pr.product_name,z.id from itak_product pr ,itak_vihidrylon vh, itak_zakaz z where vh.zakaz_id=z.id and vh.product_id=pr.id and z.datezakaz='%s' and z.timestartzakaz='%s'",m_strDateZakaz,strStartTime);
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}
		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
		{
			m_lsProduct.InsertString(0,row[0]);
			m_iZakazId = atoi(row[1]);	
		}

		if (GetDlgItem(IDC_BUTTON_ZVITZAKAZCHIK)->IsWindowEnabled()==FALSE)
		{
			m_lsProduct.EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_ZVITZAKAZCHIK)->EnableWindow(TRUE);
		}

		m_myStatZagVagaNettoZnach.SetTextColor(BLUE_TEXT);
		m_myStatZagVagaBryttoZnach.SetTextColor(BLUE_TEXT);
		m_myStatZagCountRylonovZnach.SetTextColor(BLUE_TEXT);
		m_myStatZagDlinaRylonovZnach.SetTextColor(BLUE_TEXT);
		m_myStatZagCountEtiketokZnach.SetTextColor(BLUE_TEXT);
		m_myStatTimeStartWorkZnach.SetTextColor(BLUE_TEXT);
		m_myStatTimeEndWorkZnach.SetTextColor(BLUE_TEXT);
		m_myStatTimeWorkZnach.SetTextColor(BLUE_TEXT);
		m_myStatTolschinaZnach.SetTextColor(BLUE_TEXT);
		m_myStatMaterialZnach.SetTextColor(BLUE_TEXT);
		m_myStatDlinaEtiketZnach.SetTextColor(BLUE_TEXT);
		m_myStatPartiyaZnach.SetTextColor(BLUE_TEXT);
		m_myStatSmenaZnach.SetTextColor(BLUE_TEXT);
		m_myStatProduct.SetTextColor(BLUE_TEXT);
		Invalidate();

		query.Format("select timestartzakaz,timeendzakaz,time,partiya,machine,smena,dlinaetiketki  "
			" from itak_zakaz  where id=%d",m_iZakazId);
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}
		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
		{
			m_myStatTimeStartWorkZnach.SetWindowText(row[0]);
			m_myStatTimeEndWorkZnach.SetWindowText(row[1]);
			m_myStatTimeWorkZnach.SetWindowText(row[2]);
			m_myStatPartiyaZnach.SetWindowText(row[3]);
			str.Format("%s/%s",row[4],row[5]);
			m_myStatSmenaZnach.SetWindowText(str);
			str.Format("%s мм",row[6]);
			m_myStatDlinaEtiketZnach.SetWindowText(str);
		}

		query.Format("select sum(brytto),count(id),sum(koletiketki),sum(dlinarylona),sum(vagatary) from itak_vihidrylon where zakaz_id=%d",m_iZakazId);
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}
		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
		{
			if (row[0]!=NULL)
			{
				dTemp = atof(row[0]);
				str.Format("%.2f кг",dTemp);
				m_myStatZagVagaBryttoZnach.SetWindowText(str);
			}

			if (row[1]!=NULL)
			{
				iTemp = atoi(row[1]);
				str.Format("%d шт",iTemp);
				m_myStatZagCountRylonovZnach.SetWindowText(str);
			}
			
			if (row[2]!=NULL)
			{
				iTemp = atoi(row[2]);
				str.Format("%d шт",iTemp);
				m_myStatZagCountEtiketokZnach.SetWindowText(str);
			}

			if (row[3]!=NULL)
			{
				iTemp = atoi(row[3]);
				str.Format("%d м",iTemp);
				m_myStatZagDlinaRylonovZnach.SetWindowText(str);
			}

			if (row[0]!=NULL && row[4]!=NULL)
			{
				dTemp = atof(row[0]) - atof(row[4]);
				str.Format("%.2f кг",dTemp);
				m_myStatZagVagaNettoZnach.SetWindowText(str);
			}
		}

		query.Format("select pm.product_material from itak_productmaterial pm, itak_zakaz z  where z.id=%d and z.productmaterial_id=pm.id",m_iZakazId);
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}
		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
			m_myStatMaterialZnach.SetWindowText(row[0]);

		query.Format("select pt.product_tols from itak_producttols pt,itak_zakaz z where z.id=%d and z.producttols_id=pt.id",m_iZakazId);
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}

		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
		{
			str.Format("%s мкм",row[0]);
			m_myStatTolschinaZnach.SetWindowText(str);
		}

		str.Format("0 кг");
		m_myStatVagaNettoZnach.SetWindowText(str);
		str.Format("0 кг");
		m_myStatVagaBryttoZnach.SetWindowText(str);
		str.Format("0 м");
		m_myStatDlinaRylonovZnach.SetWindowText(str);
		str.Format("0 шт");
		m_myStatCountEtiketokZnach.SetWindowText(str);
		str.Format("0 шт");
		m_myStatCountRylonovZnach.SetWindowText(str);
	}
	*pResult = 0;*/
}

