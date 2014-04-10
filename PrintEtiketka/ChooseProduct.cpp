// ChooseProduct.cpp: файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "ChooseProduct.h"


// диалоговое окно CChooseProduct

IMPLEMENT_DYNAMIC(CChooseProduct, CDialog)

//#define RED_TEXT RGB(255, 0, 0)
#define GREEN_TEXT RGB(50, 205, 50)

CChooseProduct::CChooseProduct(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseProduct::IDD, pParent), hide(0),change(0)
{
	regim = 0;
	m_iNumPrintPage = 1;
	m_dVhidRylonNetto = 0;
	m_dVhidRylonBrytto = 0;
	m_iVhidRylonDlina = 0;
	m_hAccel = LoadAccelerators( AfxGetResourceHandle(), MAKEINTRESOURCE( IDR_WORK_ACCELERATOR ) );
	m_bLogo = true;
}

CChooseProduct::~CChooseProduct()
{
}

void CChooseProduct::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ZAKAZCHIK, m_comboZakazchik);
	DDX_Control(pDX, IDC_SPIN_COUNT_PRODUCT, m_spinCountProduct);
	DDX_Control(pDX, IDC_EDIT_COUNT_PRODUCT, m_editCountProduct);
	DDX_Control(pDX, IDC_COMBO_TOLSCHINA, m_comboTolschina);
	DDX_Control(pDX, IDC_COMBO_MATERIAL, m_comboMaterial);
	DDX_Control(pDX, IDC_EDIT_DLINARYLONA, m_editDlinaRylona);
	DDX_Control(pDX, IDC_EDIT_DLINAETIKETKI, m_editDlinaEtiketki);
	DDX_Control(pDX, IDC_EDIT_COUNT_ETIKETKI, m_editCountEtiketki);
	DDX_Control(pDX, IDC_EDIT_VES_TARY, m_editVesTary);
	DDX_Control(pDX, IDC_EDIT_PARTIYA, m_editPartiya);
	DDX_Control(pDX, IDC_EDIT_NUMPRINTPAGE, m_editNumPrintPage);
	DDX_Control(pDX, IDC_SPIN_NUMPRINTPAGE, m_spinNumPrintPage);
	DDX_Control(pDX, IDC_EDIT_VHIDRYLON_NETTO, m_editVhidRylonNetto);
	DDX_Control(pDX, IDC_EDIT_VHIDRYLON_BRYTTO, m_editVhidRylonBrytto);
	DDX_Control(pDX, IDC_EDIT_VHIDRYLON_DLINA, m_editVhidRylonDlina);
	DDX_Control(pDX, IDC_COMBO_LOGO, m_comboLogo);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_date);
	DDX_Control(pDX, IDC_COMBO_MANAGER, m_comboManager);
}


BEGIN_MESSAGE_MAP(CChooseProduct, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CChooseProduct::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CChooseProduct::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_COUNT_PRODUCT, &CChooseProduct::OnEnChangeEditCountProduct)
	ON_CBN_SELCHANGE(IDC_COMBO_ZAKAZCHIK, &CChooseProduct::OnCbnSelchangeComboZakazchik)
	ON_CBN_SELCHANGE(IDC_COMBO_TOLSCHINA, &CChooseProduct::OnCbnSelchangeComboTolschina)
	ON_CBN_SELCHANGE(IDC_COMBO_MATERIAL, &CChooseProduct::OnCbnSelchangeComboMaterial)
	ON_EN_CHANGE(IDC_EDIT_DLINARYLONA, &CChooseProduct::OnEnChangeEditDlinarylona)
	ON_EN_CHANGE(IDC_EDIT_DLINAETIKETKI, &CChooseProduct::OnEnChangeEditDlinaetiketki)
	ON_EN_CHANGE(IDC_EDIT_VES_TARY, &CChooseProduct::OnEnChangeEditVesTary)
	ON_EN_CHANGE(IDC_EDIT_COUNT_ETIKETKI, &CChooseProduct::OnEnChangeEditCountEtiketki)
	ON_EN_CHANGE(IDC_EDIT_PARTIYA, &CChooseProduct::OnEnChangeEditPartiya)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CChooseProduct::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CChooseProduct::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_PRODUCT_EXIT, &CChooseProduct::OnBnClickedButtonProductExit)
	ON_BN_CLICKED(IDC_BUTTON_ADDZAKAZCHIK, &CChooseProduct::OnBnClickedButtonAddzakazchik)
	ON_BN_CLICKED(IDC_BUTTON_ADDMATERIAL, &CChooseProduct::OnBnClickedButtonAddmaterial)
	ON_BN_CLICKED(IDC_BUTTON_ADDTOLSCHINA, &CChooseProduct::OnBnClickedButtonAddtolschina)
	ON_BN_CLICKED(IDC_BUTTON_ADDPRODUCT, &CChooseProduct::OnBnClickedButtonAddproduct)
	ON_BN_CLICKED(IDC_BUTTON_ADDWIDTH, &CChooseProduct::OnBnClickedButtonAddwidth)
	ON_EN_CHANGE(IDC_EDIT_NUMPRINTPAGE, &CChooseProduct::OnEnChangeEditNumprintpage)
	ON_EN_CHANGE(IDC_EDIT_VHIDRYLON_NETTO, &CChooseProduct::OnEnChangeEditVhidrylonNetto)
	ON_EN_CHANGE(IDC_EDIT_VHIDRYLON_BRYTTO, &CChooseProduct::OnEnChangeEditVhidrylonBrytto)
	ON_EN_CHANGE(IDC_EDIT_VHIDRYLON_DLINA, &CChooseProduct::OnEnChangeEditVhidrylonDlina)
	ON_BN_CLICKED(IDC_BUTTON_ADDVAGATARY, &CChooseProduct::OnBnClickedButtonAddvagatary)
END_MESSAGE_MAP()


// обработчики сообщений CChooseProduct

void CChooseProduct::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
}

BOOL CChooseProduct::OnInitDialog()
{
	
	CDialog::OnInitDialog();

	if (hide!=0)
		GetDlgItem(IDC_BUTTON_PRODUCT_EXIT)->ShowWindow(SW_HIDE);

	GetClientRect(&m_rectClient);
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	MoveWindow(x/2 - m_rectClient.right/2,y/2-m_rectClient.bottom/2,m_rectClient.right,m_rectClient.bottom);

	m_iCountProduct = 0;
		
	m_spinCountProduct.SetRange(1,10);
	m_spinCountProduct.SetBuddy(&m_editCountProduct);
	m_editCountProduct.SetWindowText("1");

	m_spinNumPrintPage.SetRange(0,2);
	m_spinNumPrintPage.SetBuddy(&m_editNumPrintPage);
	m_editNumPrintPage.SetWindowText("1");

	m_statZakazchik.SetTextColor(RED_TEXT);
	m_statZakazchik.SetFont(20);
	m_statZakazchik.Create("Замовник",WS_CHILD|WS_VISIBLE,CRect(10,5,100,20),this,0);

	m_statCountProduct.Create("Кількість видів",WS_CHILD|WS_VISIBLE,CRect(10,60,190,80),this,0);

	m_statTolsProduct.Create("Товщина (мкм)",WS_CHILD|WS_VISIBLE,CRect(10,95,150,115),this,0);
	m_statMaterial.Create("Матеріал",WS_CHILD|WS_VISIBLE,CRect(10,128,150,150),this,0);

	m_statPartiya.Create("Партія",WS_CHILD|WS_VISIBLE,CRect(10,160,110,180),this,0);

	m_myStatVhidniyRylon.SetTextColor(BLUE_TEXT);
	m_myStatVhidniyRylon.SetFont(20);
	m_myStatVhidniyRylon.Create("ВХІДНИЙ РУЛОН",WS_CHILD|WS_VISIBLE,CRect(10,200,160,220),this,0);

	m_myStatVhidniyRylonNetto.Create("Маса нетто (кг)",WS_CHILD|WS_VISIBLE,CRect(20,230,200,250),this,0);
	m_myStatVhidniyRylonBrytto.Create("Маса брутто (кг)",WS_CHILD|WS_VISIBLE,CRect(20,263,200,285),this,0);
	m_myStatVhidniyRylonDlina.Create("Довжина (м)",WS_CHILD|WS_VISIBLE,CRect(20,295,200,315),this,0);


  	m_myStatVihidRylon.SetTextColor(BLUE_TEXT);
  	m_myStatVihidRylon.SetFont(20);
 	m_myStatVihidRylon.Create("ВИХІДНИЙ РУЛОН",WS_CHILD|WS_VISIBLE,CRect(10,335,190,355),this,0);
   	
  	m_statDlinaRylona.Create("Довжина рулону  (м)",WS_CHILD|WS_VISIBLE,CRect(20,365,200,385),this,0);
   	m_statDlinaEtiketki.Create("Довжина етикетки (мм)",WS_CHILD|WS_VISIBLE,CRect(20,398,215,418),this,0);
   
   	m_statCountEtiketki.Create("Кількість етикеток (шт)",WS_CHILD|WS_VISIBLE,CRect(20,431,210,451),this,0);
   //	m_statVesTary.Create("№ замовлення (ТК)",WS_CHILD|WS_VISIBLE,CRect(20,464,180,484),this,0);
// 	


	//m_statPrihod.Create("Рулон (кг)",WS_CHILD|WS_VISIBLE,CRect(20,417,160,435),this,0);
	

//	m_statPrihod.Create("Рулон (кг)",WS_CHILD|WS_VISIBLE,CRect(20,455,160,475),this,0);
//	m_statZakaz.Create("Замовлення (кг)",WS_CHILD|WS_VISIBLE,CRect(20,494,160,514),this,0);

	m_myStatLogo.Create("Етикетка з ",WS_CHILD|WS_VISIBLE,CRect(20,465,180,524),this,0);
	
	

	m_comboLogo.AddString("БЕЗ ЛОГО");
	m_comboLogo.AddString("ЛОГО");
	//m_comboLogo.SetCurSel(1);


	m_statNumPrintpage.Create("Друк етикеток (шт)",WS_CHILD|WS_VISIBLE,CRect(20,504,180,524),this,0);

	m_statDate.Create("Дата",WS_CHILD|WS_VISIBLE,CRect(20,540,180,560),this,0);
	m_statManager.Create("Менеджер",WS_CHILD|WS_VISIBLE,CRect(20,570,180,596),this,0);

//////////////////////////////////////////////////////////////////////////

	if (!m_database.IsOpen())
	{
		CString strConString = "Driver={SQL Server}; Server="+m_strServerAddr+"; Database=itak_etiketka; UID="+m_strMysqlLogin+"; PWD="+m_strMysqlPass+"";
		if (!m_database.OpenEx(strConString,CDatabase::noOdbcDialog))
		{
			MessageBox("Не возможно подключиться к Базе Данных. Обратитесь к администратору");
			return -1;
		}

	}

	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
		/*mysql = mysql_init(NULL);
		if (mysql == NULL) 
		{
			MessageBox("Error: Ошибка инищиализации MySql!!!");
			
		}

		if (mysql_real_connect(mysql, m_strServerAddr, m_strMysqlLogin, m_strMysqlPass, "itak_etiketka", 3306, NULL, 0) == NULL) {
			MessageBox("Не можливо підключитись до бази данних");
			//return -1;
		}
		mysql_query(mysql,"set names 'cp1251'" );*/
		////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////

	if (m_database.IsOpen())
	{
		m_pRecord =new CRecordset(&m_database);

		if (m_pRecord->Open(CRecordset::snapshot,"select id, zakazchik_name from itak_zakazchik order by zakazchik_name desc"))
		{
			for(int i=0;!m_pRecord->IsEOF();i++)
			{
				m_pRecord->GetFieldValue("zakazchik_name",strData);
				strData = strData.Trim();
				m_comboZakazchik.InsertString(0,strData);
				m_pRecord->MoveNext();
			}
		}
		m_pRecord->Close();

		if (m_pRecord->Open(CRecordset::snapshot,"select product_tols from itak_producttols order by product_tols desc"))
		{
			for(int i=0;!m_pRecord->IsEOF();i++)
			{
				m_pRecord->GetFieldValue("product_tols",strData);
				strData = strData.Trim();
				m_comboTolschina.InsertString(0,strData);
				m_pRecord->MoveNext();
			}
		}
		m_pRecord->Close();

		if (m_pRecord->Open(CRecordset::snapshot,"select product_material from itak_productmaterial  where material_state=1 order by product_material desc"))
		{
			for(int i=0;!m_pRecord->IsEOF();i++)
			{
				m_pRecord->GetFieldValue("product_material",strData);
				strData = strData.Trim();
				m_comboMaterial.InsertString(0,strData);
				m_pRecord->MoveNext();
			}
		}
		m_pRecord->Close();

		if (m_pRecord->Open(CRecordset::snapshot,"select manager_name from itak_manager where manager_name<>' ' order by manager_name desc"))
		{
			for(int i=0;!m_pRecord->IsEOF();i++)
			{
				m_pRecord->GetFieldValue("manager_name",strData);
				strData = strData.Trim();
				m_comboManager.InsertString(0,strData);
				m_pRecord->MoveNext();
			}
		}
		m_pRecord->Close();
	}

	/*query.Format("select id, zakazchik_name from itak_zakazchik order by zakazchik_name desc");
	if (mysql_query(mysql,query)!=0) 
	{
		CString str;
		str.Format("Ошибочный запрос!!! query='%s'",query);
		MessageBox(str);
	}
	res = mysql_store_result(mysql);
	while((row = mysql_fetch_row(res)))
		m_comboZakazchik.InsertString(0,row[1]);*/
	//////////////////////////////////////////////////////////////////////////


	/*query.Format("select product_tols from itak_producttols order by product_tols desc");
	if (mysql_query(mysql,query)!=0) 
	{
		CString str;
		str.Format("Ошибочный запрос!!! query='%s'",query);
		MessageBox(str);
	}
	res = mysql_store_result(mysql);
	while((row = mysql_fetch_row(res)))
		m_comboTolschina.InsertString(0,row[0]);*/
	//////////////////////////////////////////////////////////////////////////
	/*query.Format("select product_material from itak_productmaterial order by product_material desc");
	if (mysql_query(mysql,query)!=0) 
	{
		CString str;
		str.Format("Ошибочный запрос!!! query='%s'",query);
		MessageBox(str);
	}
	res = mysql_store_result(mysql);
	while((row = mysql_fetch_row(res)))
		m_comboMaterial.InsertString(0,row[0]);
*/
	//////////////////////////////////////////////////////////////////////////
	
	m_pcomboProduct[0].EnableWindow(FALSE);
	m_pcomboWidthProduct[0].EnableWindow(FALSE);
	m_pcomboVagaTary[0].EnableWindow(FALSE);

	//////////////////////////////////////////////////////////////////////////

	m_editDlinaRylona.SetLimitText(5);
	m_editDlinaEtiketki.SetLimitText(5);
	m_editCountEtiketki.SetLimitText(7);
	m_editVesTary.SetLimitText(5);
	m_editPartiya.SetLimitText(12);
	m_editVhidRylonNetto.SetLimitText(5);
	m_editVhidRylonBrytto.SetLimitText(5);
	m_editVhidRylonDlina.SetLimitText(5);

	if (m_bLogo==true)
		m_comboLogo.SetCurSel(1);
	else
		m_comboLogo.SetCurSel(0);

	
	

	if (change==1)
	{
		CString str;
		for (int i=0;i<m_comboZakazchik.GetCount();i++)
		{
			m_comboZakazchik.GetLBText(i,str);
			if (str == m_strZakazchik)
			{
				m_comboZakazchik.SetCurSel(i);
				OnCbnSelchangeComboZakazchik();
				break;
			}
		}
		m_spinCountProduct.SetPos(m_iCountProduct2);

		for (int i=0;i<m_iCountProduct2;i++)
		{
			for (int j=0;j<m_pcomboProduct[i].GetCount();j++)
			{
				m_pcomboProduct[i].GetLBText(j,str);
				if (str == m_strProduct[i])
				{
					m_pcomboProduct[i].SetCurSel(j);
					break;
				}
			}
		}

		double dTemp;
		for (int i=0;i<m_iCountProduct2;i++)
		{
			for (int j=0;j<m_pcomboVagaTary[i].GetCount();j++)
			{
				m_pcomboVagaTary[i].GetLBText(j,str);
				dTemp = atof(str);
				if (dTemp == m_dVagaTary[i])
				{
					m_pcomboVagaTary[i].SetCurSel(j);
					break;
				}
			}
		}

		for (int i=0;i<m_iCountProduct2;i++)
		{
			for (int j=0;j<m_pcomboWidthProduct[i].GetCount();j++)
			{
				m_pcomboWidthProduct[i].GetLBText(j,str);
				if (str == m_strProductWidth[i])
				{
					m_pcomboWidthProduct[i].SetCurSel(j);
					break;
				}
			}
		}

		if (m_iCountProduct2>1)
			for (int i=0;i<m_iCountProduct2;i++)
				m_pspinCountDorojec[i].SetPos(m_iCountDorojec2[i]);

	
		for (int j=0;j<m_comboTolschina.GetCount();j++)
		{
			m_comboTolschina.GetLBText(j,str);
			if (str == m_strTolschina)
			{
				m_comboTolschina.SetCurSel(j);
				OnCbnSelchangeComboTolschina();
				break;
			}
		}

		for (int j=0;j<m_comboMaterial.GetCount();j++)
		{
			m_comboMaterial.GetLBText(j,str);
			if (str == m_strMaterial)
			{
				m_comboMaterial.SetCurSel(j);
				OnCbnSelchangeComboMaterial();
				break;
			}
		}

		for (int j=0;j<m_comboManager.GetCount();j++)
		{
			m_comboManager.GetLBText(j,str);
			if (str == m_strManager)
			{
				m_comboManager.SetCurSel(j);
				//OnCbnSelchangeComboMaterial();
				break;
			}
		}
	

		str.Format("%d",m_iDlinaRylona);
		m_editDlinaRylona.SetWindowText(str);
		OnEnChangeEditDlinarylona();

		str.Format("%d",m_iDlinaEtiketki);
		m_editDlinaEtiketki.SetWindowText(str);
		OnEnChangeEditDlinaetiketki();

		str.Format("%d",m_iCountEtiketki);
		m_editCountEtiketki.SetWindowText(str);
		OnEnChangeEditCountEtiketki();

		str.Format("%.2f",m_dVagaTary);
		m_editVesTary.SetWindowText(str);
		OnEnChangeEditVesTary();

		m_editPartiya.SetWindowText(m_strPartiya);
		OnEnChangeEditPartiya();		

 		
		str.Format("%.2f",m_dVhidRylonBrytto);
 		m_editVhidRylonBrytto.SetWindowText(str);
		OnEnChangeEditVhidrylonBrytto();

 		str.Format("%.2f",m_dVhidRylonNetto);
 		m_editVhidRylonNetto.SetWindowText(str);
 		OnEnChangeEditVhidrylonNetto();

		str.Format("%d",m_iVhidRylonDlina);
		m_editVhidRylonDlina.SetWindowText(str);
		OnEnChangeEditVhidrylonDlina();

		//if (m_iNumPrintPage!=0)
			m_spinNumPrintPage.SetPos(m_iNumPrintPage);
		//else m_spinNumPrintPage.SetPos(1);

		m_date.SetTime(m_sysDate);		
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CChooseProduct::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	OnOK();
}

void CChooseProduct::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
//	OnCancel();
}


void CChooseProduct::OnEnChangeEditCountProduct()
{

	if (m_iCountProduct>0)
		for (int i=0;i<m_iCountProduct;i++)
		{
			m_iCurSelProduct[i] = m_pcomboProduct[i].GetCurSel();
			m_iCurSelWidthProduct[i] = m_pcomboWidthProduct[i].GetCurSel();
			m_iCurSelVagaTary[i] = m_pcomboVagaTary[i].GetCurSel();
			if (m_iCountProduct>1)
				m_iCountDorojec [i] = m_pspinCountDorojec[i].GetPos();
		}

		for (int i=0;i<m_iCountProduct;i++)
		{
			m_pcomboProduct[i].ShowWindow(SW_HIDE);
			m_pstatProduct[i].ShowWindow(SW_HIDE);

			if (m_iCountProduct>1)
			{
				m_pspinCountDorojec[i].ShowWindow(SW_HIDE);
				m_peditCountDorojec[i].ShowWindow(SW_HIDE);
				m_pstatCountDorojec[i].ShowWindow(SW_HIDE);
			}

			m_pstatWidthProduct[i].ShowWindow(SW_HIDE);
			m_pcomboWidthProduct[i].ShowWindow(SW_HIDE);

			m_pMyStatVagaTary[i].ShowWindow(SW_HIDE);
			m_pcomboVagaTary[i].ShowWindow(SW_HIDE);
		}

		if (m_iCountProduct>0)
		{
			m_pcomboProduct = 0;
			m_pcomboWidthProduct = 0;
			m_pstatWidthProduct = 0;
			m_pstatProduct = 0;		
			m_pcomboVagaTary = 0;
			m_pMyStatVagaTary = 0;

			if (m_iCountProduct>1)
			{
				m_peditCountDorojec = 0;
				m_pspinCountDorojec = 0;
				m_pstatCountDorojec = 0;
				delete m_peditCountDorojec;
				delete m_pspinCountDorojec;
				delete m_pstatCountDorojec;
			}

			delete m_pcomboProduct;
			delete m_pcomboWidthProduct;
			delete m_pstatProduct;
			delete m_pstatWidthProduct;

			delete m_pMyStatVagaTary;
			delete m_pcomboVagaTary;

		}

		m_iCountProduct = m_spinCountProduct.GetPos();
// 		switch (m_iCountProduct)
// 		{
// 		//	case 8:	Plus(453);	break;
// 		//	case 9:	Plus(492);	break;
// 		//	case 10:	Plus(542);	break;
// 		}

		CRect rect;
		rect.top = 25;
		rect.bottom = 160;
		rect.left = 353;
		rect.right = 700;

		m_pcomboProduct = new CComboBox[m_iCountProduct];
		m_pstatProduct = new CMyStatic[m_iCountProduct];
		m_peditCountDorojec = new CEdit[m_iCountProduct];
		m_pspinCountDorojec = new CSpinButtonCtrl [m_iCountProduct];
		m_pstatCountDorojec = new CMyStatic [m_iCountProduct];
		m_pstatWidthProduct = new CMyStatic[m_iCountProduct];
		m_pcomboWidthProduct = new CComboBox[m_iCountProduct];

		m_pMyStatVagaTary = new CMyStatic [m_iCountProduct];
		m_pcomboVagaTary = new CComboBox[m_iCountProduct];

		CString str;
		for (int i=0;i<m_iCountProduct;i++)
		{
			str.Format("Вид замовлення №%d",i+1);
			m_pstatProduct[i].Create(str,WS_CHILD|WS_VISIBLE,CRect(rect.left-10,rect.top-20,rect.right,rect.bottom-20),this,10100+i);	
			m_pcomboProduct[i].Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|WS_VSCROLL,rect,this,10100+i);
 			m_pstatWidthProduct[i].Create("Ширина (мм)",WS_CHILD|WS_VISIBLE,CRect(rect.left+350,rect.top-20,rect.right+230,rect.bottom-20),this,1101+i);
 			m_pcomboWidthProduct[i].Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(rect.left+370,rect.top,rect.right+80,rect.bottom),this,1210+i);		

			m_pMyStatVagaTary[i].Create("Вага тары (кг)",WS_CHILD|WS_VISIBLE,CRect(rect.left+455,rect.top-20,rect.right+380,rect.bottom-20),this,111201+i);
			m_pcomboVagaTary[i].Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(rect.left+460,rect.top,rect.right+180,rect.bottom),this,1210+i);		
	
			if (m_iCountProduct>1)
			{
				m_pstatCountDorojec[i].Create("К-ть доріжок",WS_CHILD|WS_VISIBLE,CRect(rect.left+560,rect.top-20,rect.right+310,rect.bottom-20),this,1221+i);
				m_peditCountDorojec[i].Create(WS_VISIBLE|WS_CHILD|WS_BORDER|ES_NUMBER|ES_READONLY,CRect(rect.left+590,rect.top,rect.right+280,rect.top+20),this,10102+i);
				m_pspinCountDorojec[i].Create(WS_VISIBLE|WS_CHILD|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|WS_BORDER,CRect(rect.left+620,rect.top,rect.right+280,rect.top+20),this,10112+i);
				m_pspinCountDorojec[i].SetBuddy(&m_peditCountDorojec[i]);
				m_pspinCountDorojec[i].SetRange(1,20);
				m_pspinCountDorojec[i].SetPos(1);			
			}

			rect.top += 50;
			rect.bottom += 50;
		}

		if (m_iCountProduct>1)
		{
			int a = 0;
			if (m_comboZakazchik.GetCurSel()<0)
				a = 0;
			else a = m_comboZakazchik.GetCurSel();

			m_comboZakazchik.GetLBText(a,str);

			CRecordset record2(&m_database);
			CString strData1;
			for (int j=0;j<m_iCountProduct;j++)
			{
				if (m_database.IsOpen())
				{
					query.Format("select id from itak_zakazchik where zakazchik_name='%s'",str);
					if (m_pRecord->Open(CRecordset::snapshot,query))
					{
						for(int i=0;!m_pRecord->IsEOF();i++)
						{
							m_pRecord->GetFieldValue("id",strData);
							strData = strData.Trim();
							query.Format("select product_name from itak_product where id_zakazchik=%s order by product_name desc",strData);
							if (record2.Open(CRecordset::snapshot,query))
							{
								for(int i=0;!record2.IsEOF();i++)
								{
									record2.GetFieldValue("product_name",strData1);
									strData1 = strData1.Trim();
									m_pcomboProduct[j].InsertString(0,strData1);

									record2.MoveNext();
								}
							}
							record2.Close();

							m_pRecord->MoveNext();
						}
					}
					m_pRecord->Close();


					if (m_pRecord->Open(CRecordset::snapshot,"select product_width from itak_productwidth order by product_width desc"))
					{
						for(int i=0;!m_pRecord->IsEOF();i++)
						{
							m_pRecord->GetFieldValue("product_width",strData);
							strData = strData.Trim();
							m_pcomboWidthProduct[j].InsertString(0,strData);
							m_pRecord->MoveNext();
						}
					}
					m_pRecord->Close();

					CString str;
					double val=0;
					if (m_pRecord->Open(CRecordset::snapshot,"select vaga from itak_vagatary order by vaga desc"))
					{
						for(int i=0;!m_pRecord->IsEOF();i++)
						{
							m_pRecord->GetFieldValue("vaga",strData);
							strData = strData.Trim();
							val = atof(strData.GetBuffer(strData.GetLength()));
							str.Format("%.2f",val);
							m_pcomboVagaTary[j].InsertString(0,str);
							m_pRecord->MoveNext();
						}
					}
					m_pRecord->Close();
				}
			}

			/*for (int i=0;i<m_iCountProduct;i++)
			{


				query.Format("select id from itak_zakazchik where zakazchik_name='%s'",str);
				if (mysql_query(mysql,query)!=0) 
				{
					CString str;
					str.Format("Ошибочный запрос!!! query='%s'",query);
					MessageBox(str);
				}
				res = mysql_store_result(mysql);
				while((row = mysql_fetch_row(res)))
				{
					query.Format("select product_name from itak_product where id_zakazchik=%s",row[0]);
					if (mysql_query(mysql,query)!=0) 
					{
						CString str;
						str.Format("Ошибочный запрос!!! query='%s'",query);
						MessageBox(str);
					}
					res2 = mysql_store_result(mysql);
					while((row2 = mysql_fetch_row(res2)))
					{
						m_pcomboProduct[i].InsertString(0,row2[0]);
					}	
					mysql_free_result(res2);
				}
				mysql_free_result(res);
			}

			for (int i=0;i<m_iCountProduct;i++)
			{
				query.Format("select product_width from itak_productwidth order by product_width desc");
				if (mysql_query(mysql,query)!=0) 
				{
					CString str;
					str.Format("Ошибочный запрос!!! query='%s'",query);
					MessageBox(str);
				}
				res = mysql_store_result(mysql);
				while((row = mysql_fetch_row(res)))
					m_pcomboWidthProduct[i].InsertString(0,row[0]);
				mysql_free_result(res);
			}

			for (int i=0;i<m_iCountProduct;i++)
			{
				query.Format("select vaga from itak_vagatary order by vaga desc");
				if (mysql_query(mysql,query)!=0) 
				{
					CString str;
					str.Format("Ошибочный запрос!!! query='%s'",query);
					MessageBox(str);
				}
				res = mysql_store_result(mysql);
				while((row = mysql_fetch_row(res)))
					m_pcomboVagaTary[i].InsertString(0,row[0]);
				mysql_free_result(res);
			}*/
		}

		for (int i=0;i<m_iCountProduct;i++)
		{
			m_pcomboProduct[i].SetCurSel(m_iCurSelProduct[i]);
			m_pcomboWidthProduct[i].SetCurSel(m_iCurSelWidthProduct[i]);
			m_pcomboVagaTary[i].SetCurSel(m_iCurSelVagaTary[i]);
			if (m_iCountProduct>1)
				m_pspinCountDorojec[i].SetPos(m_iCountDorojec [i]);
		}
}

void CChooseProduct::OnCbnSelchangeComboZakazchik()
{
	if (m_comboZakazchik.GetCurSel()!=-1)
	{
		if (GetDlgItem(IDC_COMBO_TOLSCHINA)->IsWindowEnabled()==FALSE)
		{
			m_statZakazchik.SetTextColor(GREEN_TEXT);
			m_statCountProduct.SetTextColor(GREEN_TEXT);
			m_statCountProduct.SetFont(20);

			m_statTolsProduct.SetFont(20);
			m_statTolsProduct.SetTextColor(RED_TEXT);
			Invalidate();
		}

		GetDlgItem(IDC_COMBO_TOLSCHINA)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUTTON_ADDTOLSCHINA)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ADDPRODUCT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ADDWIDTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ADDVAGATARY)->EnableWindow(TRUE);

		

		
		GetDlgItem(IDC_SPIN_COUNT_PRODUCT)->EnableWindow(TRUE);
		m_pcomboProduct[0].EnableWindow(TRUE);
		m_pcomboWidthProduct[0].EnableWindow(TRUE);
		m_pcomboVagaTary[0].EnableWindow(TRUE);

		if (m_iCountProduct>1)
		{
			m_peditCountDorojec[0].EnableWindow(TRUE);
			m_pspinCountDorojec[0].EnableWindow(TRUE);
		}

		m_spinCountProduct.SetPos(1);
		for (int i=0;i<10;i++)
		{
			m_iCurSelProduct[i] = -1;
			m_iCurSelWidthProduct[i]=-1;
			m_iCurSelVagaTary[i]=-1;
			m_iCountDorojec [i] = -1;
		}
		for(int i=m_pcomboProduct[0].GetCount();i>=0;i--)
			m_pcomboProduct[0].DeleteString(i);

		for(int i=m_pcomboWidthProduct[0].GetCount();i>=0;i--)
			m_pcomboWidthProduct[0].DeleteString(i);

		for(int i=m_pcomboVagaTary[0].GetCount();i>=0;i--)
			m_pcomboVagaTary[0].DeleteString(i);


		CString str;
		m_comboZakazchik.GetLBText(m_comboZakazchik.GetCurSel(),str);
		/*if (str == "АО \"БУКУРИЯ\" Г.КИШИНЕВ (МОЛДОВА)")
		{
			GetDlgItem(IDC_BUTTON_ADDPRODUCT)->EnableWindow(FALSE);
		}*/

		if (m_database.IsOpen())
		{
			CRecordset record2(&m_database);
			CString strData1;

			query.Format("select id from itak_zakazchik where zakazchik_name='%s'",str);
			if (m_pRecord->Open(CRecordset::snapshot,query))
			{
				for(int i=0;!m_pRecord->IsEOF();i++)
				{
					m_pRecord->GetFieldValue("id",strData);
					strData = strData.Trim();
					query.Format("select product_name from itak_product where id_zakazchik=%s order by product_name desc",strData);
					if (record2.Open(CRecordset::snapshot,query))
					{
						for(int i=0;!record2.IsEOF();i++)
						{
							record2.GetFieldValue("product_name",strData1);
							strData1 = strData1.Trim();
							m_pcomboProduct[0].InsertString(0,strData1);

							record2.MoveNext();
						}
					}
					record2.Close();

					m_pRecord->MoveNext();
				}
			}
			m_pRecord->Close();

			
			if (m_pRecord->Open(CRecordset::snapshot,"select product_width from itak_productwidth order by product_width desc"))
			{
				for(int i=0;!m_pRecord->IsEOF();i++)
				{
					m_pRecord->GetFieldValue("product_width",strData);
					strData = strData.Trim();
					m_pcomboWidthProduct[0].InsertString(0,strData);
					m_pRecord->MoveNext();
				}
			}
			m_pRecord->Close();

			CString str;
			double val=0;
			if (m_pRecord->Open(CRecordset::snapshot,"select vaga from itak_vagatary order by vaga desc"))
			{
				for(int i=0;!m_pRecord->IsEOF();i++)
				{
					m_pRecord->GetFieldValue("vaga",strData);
					strData = strData.Trim();
					val = atof(strData.GetBuffer(strData.GetLength()));
					str.Format("%.2f",val);
					m_pcomboVagaTary[0].InsertString(0,str);
					m_pRecord->MoveNext();
				}
			}
			m_pRecord->Close();
		}

		/*query.Format("select id from itak_zakazchik where zakazchik_name='%s'",str);
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}
		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
		{
			query.Format("select product_name from itak_product where id_zakazchik=%s order by product_name desc",row[0]);
			if (mysql_query(mysql,query)!=0) 
			{
				CString str;
				str.Format("Ошибочный запрос!!! query='%s'",query);
				MessageBox(str);
			}
			res2 = mysql_store_result(mysql);
			while((row2 = mysql_fetch_row(res2)))
				m_pcomboProduct[0].InsertString(0,row2[0]);
		}*/

		/*query.Format("select product_width from itak_productwidth order by product_width desc");
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}
		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
			m_pcomboWidthProduct[0].InsertString(0,row[0]);*/

		/*query.Format("select vaga from itak_vagatary order by vaga desc");
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}
		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
			m_pcomboVagaTary[0].InsertString(0,row[0]);*/
	}
}

void CChooseProduct::Plus( int h)
{
	CRect rect,r;
	GetWindowRect(&rect);
	r = rect;
	ScreenToClient(&rect);
	MoveWindow(r.left,r.top,rect.right-rect.left,h);

 	WINDOWINFO f;
 	GetDlgItem(IDC_BUTTON_NEXT)->GetWindowInfo(&f);
 	ScreenToClient(&f.rcWindow);
 	GetDlgItem(IDC_BUTTON_NEXT)->MoveWindow(f.rcWindow.left,h-66,93,35);

	GetDlgItem(IDC_BUTTON_BACK)->GetWindowInfo(&f);
	ScreenToClient(&f.rcWindow);
	GetDlgItem(IDC_BUTTON_BACK)->MoveWindow(f.rcWindow.left,h-66,93,35);

	GetDlgItem(IDC_BUTTON_PRODUCT_EXIT)->GetWindowInfo(&f);
	ScreenToClient(&f.rcWindow);
	GetDlgItem(IDC_BUTTON_PRODUCT_EXIT)->MoveWindow(f.rcWindow.left,h-66,93,35);
}

void CChooseProduct::OnCbnSelchangeComboTolschina()
{
	if (m_comboTolschina.GetCurSel()!=-1)
	{
		if (GetDlgItem(IDC_COMBO_MATERIAL)->IsWindowEnabled()==FALSE)
		{
			m_statTolsProduct.SetTextColor(GREEN_TEXT);
			m_statMaterial.SetTextColor(RED_TEXT);
			m_statMaterial.SetFont(20);
			GetDlgItem(IDC_COMBO_MATERIAL)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_ADDMATERIAL)->EnableWindow(TRUE);
			Invalidate();
		}
	}
}

void CChooseProduct::OnCbnSelchangeComboMaterial()
{
	if (m_comboMaterial.GetCurSel()!=-1)
	{
		if (GetDlgItem(IDC_EDIT_PARTIYA)->IsWindowEnabled()==FALSE)
		{
			m_statMaterial.SetTextColor(GREEN_TEXT);
			m_statPartiya.SetTextColor(RED_TEXT);
			m_statPartiya.SetFont(20);
			GetDlgItem(IDC_EDIT_PARTIYA)->EnableWindow(TRUE);
			Invalidate();
		}
	}
}

void CChooseProduct::OnEnChangeEditDlinarylona()
{
	if (GetDlgItem(IDC_EDIT_DLINAETIKETKI)->IsWindowEnabled()==FALSE)
	{
		m_statDlinaRylona.SetTextColor(GREEN_TEXT);
		m_statDlinaEtiketki.SetTextColor(RED_TEXT);
		m_statDlinaEtiketki.SetFont(20);

		GetDlgItem(IDC_EDIT_DLINAETIKETKI)->EnableWindow(TRUE);
		Invalidate();
	}
	CString str,str1;
	m_editDlinaEtiketki.GetWindowText(str1);
	m_editDlinaRylona.GetWindowText(str);
	CalcKolEtiket(str,str1);
}

void CChooseProduct::OnEnChangeEditDlinaetiketki()
{
	if (GetDlgItem(IDC_EDIT_COUNT_ETIKETKI)->IsWindowEnabled()==FALSE)
	{
 		m_statDlinaEtiketki.SetTextColor(GREEN_TEXT);
		m_statCountEtiketki.SetTextColor(GREEN_TEXT);
		m_statCountEtiketki.SetFont(20);
		m_myStatLogo.SetTextColor(GREEN_TEXT);
		m_myStatLogo.SetFont(20);
		//m_statVesTary.SetTextColor(RED_TEXT);
		//m_statVesTary.SetFont(20);
		GetDlgItem(IDC_EDIT_COUNT_ETIKETKI)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_LOGO)->EnableWindow(TRUE);

		//m_statVesTary.SetTextColor(GREEN_TEXT);
		//m_statNumPrintpage.SetTextColor(GREEN_TEXT);
		//m_statNumPrintpage.SetFont(20);

		//GetDlgItem(IDC_SPIN_NUMPRINTPAGE)->EnableWindow(TRUE);
		//GetDlgItem(IDC_BUTTON_NEXT)->EnableWindow(TRUE);
		Invalidate();

	}
	CString str,str1;
	m_editDlinaEtiketki.GetWindowText(str1);
	m_editDlinaRylona.GetWindowText(str);
	CalcKolEtiket(str,str1);
}

void CChooseProduct::CalcKolEtiket(CString DlinaRylona, CString DlinaEtik)
{
	CString temp;
	if (DlinaRylona.GetLength()<=0)
		DlinaRylona = "1";
	else //if (DlinaRylona.GetLength()>0)
	{
		double dtemp = strtod(DlinaRylona.GetBuffer(DlinaRylona.GetLength()),0);
		double dtemp1 = strtod(DlinaEtik.GetBuffer(DlinaEtik.GetLength()),0);
		if (DlinaEtik=="0" || DlinaEtik=="0." || DlinaEtik.GetLength()==0)
			dtemp1 = 1;
		dtemp =(dtemp*1000/dtemp1);
		//dtemp /=100;
		int a = (int)dtemp+0.5;
		temp.Format("%d",a);
		m_editCountEtiketki.SetWindowText(temp);
	}
}

void CChooseProduct::OnEnChangeEditCountEtiketki()
{
	/*if (GetDlgItem(IDC_EDIT_VES_TARY)->IsWindowEnabled()==FALSE)
		GetDlgItem(IDC_EDIT_VES_TARY)->EnableWindow(TRUE);*/

	if (GetDlgItem(IDC_SPIN_NUMPRINTPAGE)->IsWindowEnabled()==FALSE)
	{
		//m_statVesTary.SetTextColor(GREEN_TEXT);
		m_statNumPrintpage.SetTextColor(GREEN_TEXT);
		m_statNumPrintpage.SetFont(20);

		GetDlgItem(IDC_SPIN_NUMPRINTPAGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_NEXT)->EnableWindow(TRUE);
		Invalidate();
	}
}

void CChooseProduct::OnEnChangeEditVesTary()
{
	/*CString str;
	m_editVesTary.GetWindowText(str);
	static int c=0;	

	if (str.GetLength()!=0)
	{
		if (strcmp(str.Right(1),"0")==0
			|| strcmp(str.Right(1),"1")==0
			|| strcmp(str.Right(1),"2")==0
			|| strcmp(str.Right(1),"3")==0
			|| strcmp(str.Right(1),"4")==0
			|| strcmp(str.Right(1),"5")==0
			|| strcmp(str.Right(1),"6")==0
			|| strcmp(str.Right(1),"7")==0
			|| strcmp(str.Right(1),"8")==0
			|| strcmp(str.Right(1),"9")==0
			|| strcmp(str.Right(1),".")==0
			|| strcmp(str.Right(1),",")==0)
		{
			if (strcmp(str.Left(1),",")==0
				|| strcmp(str.Left(1),".")==0)
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_editVesTary.SetWindowText(str);
			}
			else if (str.GetLength()==2 && strcmp(str.Left(1),"0")==0 &&(strcmp(str.Right(1),",")!=0 &&strcmp(str.Right(1),".")!=0))
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_editVesTary.SetWindowText(str);
			}
			else if (strcmp(str.Right(1),",")==0 || strcmp(str.Right(1),".")==0)
			{
				if (c>=1)
				{
					MessageBox("Некоректний ввід");
					str = "";
					m_editVesTary.SetWindowText(str);
					c=0;
				}else c++;		
			}
		}
		else
		{
			MessageBox("Некоректний ввід");
			str = "";
			m_editVesTary.SetWindowText(str);
		}
		if (str.Find(',')!=-1)
			str.Replace(',','.');
		//m_edSendVesTaty = str;				 
	}*/
	if (GetDlgItem(IDC_SPIN_NUMPRINTPAGE)->IsWindowEnabled()==FALSE)
	{
		//m_statVesTary.SetTextColor(GREEN_TEXT);
		m_statNumPrintpage.SetTextColor(GREEN_TEXT);
		m_statNumPrintpage.SetFont(20);

		GetDlgItem(IDC_SPIN_NUMPRINTPAGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_NEXT)->EnableWindow(TRUE);
		Invalidate();
	}
}


void CChooseProduct::OnEnChangeEditPartiya()
{
	if (GetDlgItem(IDC_EDIT_VHIDRYLON_NETTO)->IsWindowEnabled()==FALSE)
	{
		m_statPartiya.SetTextColor(GREEN_TEXT);
		m_myStatVhidniyRylonNetto.SetTextColor(RED_TEXT);
		m_myStatVhidniyRylonNetto.SetFont(20);
		CString s;
		m_editVhidRylonNetto.GetWindowText(s);
		if (s.GetLength()<=1)
			Invalidate();
		GetDlgItem(IDC_EDIT_VHIDRYLON_NETTO)->EnableWindow(TRUE);
	}
}

void CChooseProduct::OnBnClickedButtonNext()
{
	bool flag = false;
	CString err;
	CString str;
// 	m_editVesTary.GetWindowText(str);
// 	if (str.Find(',')!=-1)
// 		str.Replace(',','.');
// 	m_editVesTary.SetWindowText(str);
	if (m_comboZakazchik.GetCurSel()!=-1)
	{
		if (flag==false)
		{
			for (int i=0;i<m_spinCountProduct.GetPos();i++)
			{
				if (m_pcomboProduct[i].GetCurSel()==-1)
				{
					err.Format("Виберіть продукцію №%d",i+1);
					m_pstatProduct[i].SetTextColor(RED_TEXT);
					Invalidate();
					MessageBox(err);
					flag = false;
					break;
				}
				else 
				{
					m_pstatProduct[i].SetTextColor(GREEN_TEXT);
					Invalidate();
				}
				
				if (m_pcomboWidthProduct[i].GetCurSel()==-1)
				{
					err.Format("Виберіть ширину продукції №%d",i+1);
					m_pstatWidthProduct[i].SetTextColor(RED_TEXT);
					Invalidate();
					MessageBox(err);
					flag = false;
					break;
				}
				else
				{
					flag =true;
					m_pstatWidthProduct[i].SetTextColor(GREEN_TEXT);
					Invalidate();
				}
				
				if (m_pcomboVagaTary[i].GetCurSel()==-1)
				{
					err.Format("Виберіть вагу тари №%d",i+1);
					m_pMyStatVagaTary[i].SetTextColor(RED_TEXT);
					Invalidate();
					MessageBox(err);
					flag = false;
					break;
				}
				else
				{
					flag =true;
					m_pMyStatVagaTary[i].SetTextColor(GREEN_TEXT);
					Invalidate();
				}
			}
		}
		if (flag==true)
		{
			if (m_comboTolschina.GetCurSel()!=-1)
			{
				if (m_comboMaterial.GetCurSel()!=-1)
				{
					m_editDlinaRylona.GetWindowText(err);
					if (err.GetLength()!=0)
					{
						m_editCountEtiketki.GetWindowText(err);
						if (err.GetLength()!=0)
						{
							//m_editVesTary.GetWindowText(err);
							//if (err.GetLength()!=0)
							{
								m_editPartiya.GetWindowText(err);
								if (err.GetLength()!=0)
								{
 									m_editVhidRylonNetto.GetWindowText(err);
 									if (err.GetLength()!=0)
 									{
 										m_editVhidRylonBrytto.GetWindowText(err);
 										if (err.GetLength()!=0)
 										{
											m_editVhidRylonDlina.GetWindowText(err);
											if (err.GetLength()!=0)
											{
												if (m_comboManager.GetCurSel()!=-1)
												{
													regim = 1;
													OnOK();
												}
												else
												{
													MessageBox("Виберіть менеджера");	
												}
												
											}else 
											{
												MessageBox("Введіть довжину вхідного рулону");	
												m_myStatVhidniyRylonDlina.SetTextColor(RED_TEXT);
											}
 										}else
										{
											MessageBox("Введіть вагу брутто вхідного рулону");	
											m_myStatVhidniyRylonBrytto.SetTextColor(RED_TEXT);
										}
 									}else 
									{
										MessageBox("Введіть вагу нетто вхідного рулону");	
										m_myStatVhidniyRylonNetto.SetTextColor(RED_TEXT);
									}
								}else 
								{
									MessageBox("Введіть партію");	
									m_statPartiya.SetTextColor(RED_TEXT);
								}
							}
							//else
							{
								//MessageBox("Введіть № замовлення (ТК)");
								//m_statVesTary.SetTextColor(RED_TEXT);
							}
						}else 
						{
							MessageBox("Введіть кількість етикеток");
							m_statCountEtiketki.SetTextColor(RED_TEXT);
						}
					}else 
					{
						MessageBox("Введіть довжину рулона");
						m_statDlinaRylona.SetTextColor(RED_TEXT);
					}
				}else 
				{
					MessageBox("Виберіть матеріал");
					m_statMaterial.SetTextColor(RED_TEXT);
				}
			}else 
			{
				MessageBox("Виберіть товщину матеріала");
				m_statTolsProduct.SetTextColor(RED_TEXT);
			}
		}
	}else MessageBox("Виберіть замовника");	
}

void CChooseProduct::OnBnClickedButtonBack()
{
	regim = 2;
	OnOK();
}

void CChooseProduct::OnBnClickedButtonProductExit()
{
	regim = 3;
	OnOK();
}


void CChooseProduct::OnOK()
{
	if (regim ==1)
	{
		if (m_comboZakazchik.GetCurSel()!=-1)
			m_comboZakazchik.GetLBText(m_comboZakazchik.GetCurSel(),m_strZakazchik);
		else m_strZakazchik = "NULL";

		m_iCountProduct = m_spinCountProduct.GetPos();
		m_iNumPrintPage = m_spinNumPrintPage.GetPos();

		if (m_comboTolschina.GetCurSel()!=-1)
			m_comboTolschina.GetLBText(m_comboTolschina.GetCurSel(),m_strTolschina);
		else m_strTolschina = "NULL";

		if (m_comboMaterial.GetCurSel()!=-1)
			m_comboMaterial.GetLBText(m_comboMaterial.GetCurSel(),m_strMaterial);
		else m_strMaterial = "NULL";

		if (m_comboManager.GetCurSel()!=-1)
			m_comboManager.GetLBText(m_comboManager.GetCurSel(),m_strManager);
		else m_strManager = "NULL";

		CString str;
		m_editDlinaRylona.GetWindowText(str);
		m_iDlinaRylona = atoi(str.GetBuffer(str.GetLength()));

		m_editDlinaEtiketki.GetWindowText(str);
		m_iDlinaEtiketki = atoi(str.GetBuffer(str.GetLength()));

		m_editCountEtiketki.GetWindowText(str);
		m_iCountEtiketki = atoi(str.GetBuffer(str.GetLength()));

 		m_editVesTary.GetWindowText(str);
 		m_iNumberZakazTK = atoi(str.GetBuffer(str.GetLength()));


		m_editPartiya.GetWindowText(m_strPartiya);

		m_editVhidRylonNetto.GetWindowText(str);
		m_dVhidRylonNetto = atof(str.GetBuffer(str.GetLength()));

		m_editVhidRylonBrytto.GetWindowText(str);
		m_dVhidRylonBrytto = atof(str.GetBuffer(str.GetLength()));

		m_editVhidRylonDlina.GetWindowText(str);
		m_iVhidRylonDlina = atoi(str.GetBuffer(str.GetLength()));

		if (m_comboLogo.GetCurSel()==1)
			m_bLogo = true;
		else m_bLogo = false;

		m_date.GetTime(&m_sysDate);

		if (m_iCountProduct>0)
		{
			for (int i=0;i<m_iCountProduct;i++)
			{
				m_pcomboProduct[i].GetLBText(m_pcomboProduct[i].GetCurSel(),m_strProduct[i]);
				if (m_iCountProduct>1)
					m_iCountDorojec [i] = m_pspinCountDorojec[i].GetPos();
				m_pcomboWidthProduct[i].GetLBText(m_pcomboWidthProduct[i].GetCurSel(),m_strProductWidth[i]);
				m_pcomboVagaTary[i].GetLBText(m_pcomboVagaTary[i].GetCurSel(),str);
				m_dVagaTary[i] = atof(str.GetBuffer(str.GetLength()));
			}
		}
	}
	
	CDialog::OnOK();
}


void CChooseProduct::SetServerAddr(CString addr)
{
	m_strServerAddr = addr;
}

void CChooseProduct::SetMysqlLogin(CString login)
{
	m_strMysqlLogin = login;
}

void CChooseProduct::SetMysqlPass(CString pass)
{
	m_strMysqlPass = pass;
}
void CChooseProduct::OnBnClickedButtonAddzakazchik()
{
	m_addZakazchik = new CAddZakazchik;
	m_addZakazchik->SetName("Додати нового замовника:");
	if (m_addZakazchik->DoModal()==IDOK)
	{		
		bool bRepeat = false;
		if (m_database.IsOpen())
		{

			query.Format("select count(id) from itak_etiketka.dbo.itak_zakazchik where zakazchik_name='%s'",m_addZakazchik->GetData());
			if (m_pRecord->Open(CRecordset::snapshot,query))
			{
				short index = 0;
				for(int i=0;!m_pRecord->IsEOF();i++)
				{
					m_pRecord->GetFieldValue(index,strData);
					strData = strData.Trim();
					m_pRecord->MoveNext();
				}
			}
			m_pRecord->Close();

			if (strData=="0")
				bRepeat = true;
			else
				bRepeat=false;

			if (bRepeat==true)
			{
				query.Format("insert into itak_etiketka.dbo.itak_zakazchik (zakazchik_name) values ('%s');",m_addZakazchik->GetData());
				m_database.ExecuteSQL(query);

				for (int i=m_comboZakazchik.GetCount();i>=0;i--)
					m_comboZakazchik.DeleteString(i);

				if (m_pRecord->Open(CRecordset::snapshot,"select id, zakazchik_name from itak_zakazchik order by zakazchik_name desc"))
				{
					for(int i=0;!m_pRecord->IsEOF();i++)
					{
						m_pRecord->GetFieldValue("zakazchik_name",strData);
						strData = strData.Trim();
						m_comboZakazchik.InsertString(0,strData);
						m_pRecord->MoveNext();
					}
				}
				m_pRecord->Close();

				CString str;
				for (int i=0;i<m_comboZakazchik.GetCount();i++)
				{
					m_comboZakazchik.GetLBText(i,str);
					if (str == m_addZakazchik->GetData())
					{
						m_comboZakazchik.SetCurSel(i);
						break;
					}
				}
				OnCbnSelchangeComboZakazchik();
			}
			else MessageBox("Данное значение уже есть в базе данных");
		}

		

		/*query.Format("insert into itak_zakazchik (zakazchik_name) value ('%s')",m_addZakazchik->GetData());
		if (mysql_query(mysql,query)!=0)  MessageBox("Ошибочный запрос!!!");*/

		

		/*query.Format("select zakazchik_name from itak_zakazchik order by zakazchik_name asc");
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}
		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
			m_comboZakazchik.InsertString(0,row[0]);*/

		
	}
	delete m_addZakazchik;
}


void CChooseProduct::OnBnClickedButtonAddmaterial()
{
	m_addZakazchik = new CAddZakazchik;
	m_addZakazchik->SetName("Додати новий матеріал:");
	if (m_addZakazchik->DoModal()==IDOK)
	{
		bool bRepeat = false;
		if (m_database.IsOpen())
		{
			query.Format("select count(id) from itak_etiketka.dbo.itak_productmaterial where product_material='%s'",m_addZakazchik->GetData());
			if (m_pRecord->Open(CRecordset::snapshot,query))
			{
				short index = 0;
				for(int i=0;!m_pRecord->IsEOF();i++)
				{
					m_pRecord->GetFieldValue(index,strData);
					strData = strData.Trim();
					m_pRecord->MoveNext();
				}
			}
			m_pRecord->Close();

			if (strData=="0")
				bRepeat = true;
			else
				bRepeat=false;

			if (bRepeat==true)
			{

			
				query.Format("insert into itak_etiketka.dbo.itak_productmaterial (product_material) values ('%s');",m_addZakazchik->GetData());
				m_database.ExecuteSQL(query);

				for (int i=m_comboMaterial.GetCount();i>=0;i--)
					m_comboMaterial.DeleteString(i);

				if (m_pRecord->Open(CRecordset::snapshot,"select product_material from itak_productmaterial where material_state=1 order by product_material desc"))
				{
					for(int i=0;!m_pRecord->IsEOF();i++)
					{
						m_pRecord->GetFieldValue("product_material",strData);
						strData = strData.Trim();
						m_comboMaterial.InsertString(0,strData);
						m_pRecord->MoveNext();
					}
				}
				m_pRecord->Close();

				CString str;
				for (int i=0;i<m_comboMaterial.GetCount();i++)
				{
					m_comboMaterial.GetLBText(i,str);
					if (str == m_addZakazchik->GetData())
					{
						m_comboMaterial.SetCurSel(i);
						break;
					}
				}
				OnCbnSelchangeComboMaterial();
			}
			else MessageBox("Данное значение уже есть в базе данных");
				
		}

		

		

		/*query.Format("select product_material from itak_productmaterial order by product_material asc");
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}
		res = mysql_store_result(mysql);
		while((row = mysql_fetch_row(res)))
			m_comboMaterial.InsertString(0,row[0]);*/

		
	}
	delete m_addZakazchik;
}

void CChooseProduct::OnBnClickedButtonAddtolschina()
{
	m_addZakazchik = new CAddZakazchik;
	m_addZakazchik->SetName("Додати нову товщину:");
	if (m_addZakazchik->DoModal()==IDOK)
	{
		bool bRepeat = false;
		if (m_database.IsOpen())
		{
			query.Format("select count(id) from itak_etiketka.dbo.itak_producttols where product_tols=%s",m_addZakazchik->GetData());
			if (m_pRecord->Open(CRecordset::snapshot,query))
			{
				short index = 0;
				for(int i=0;!m_pRecord->IsEOF();i++)
				{
					m_pRecord->GetFieldValue(index,strData);
					strData = strData.Trim();
					m_pRecord->MoveNext();
				}
			}
			m_pRecord->Close();

			if (strData=="0")
				bRepeat = true;
			else
				bRepeat=false;

			if (bRepeat==true)
			{
				query.Format("insert into itak_etiketka.dbo.itak_producttols (product_tols) values (%s);",m_addZakazchik->GetData());
				m_database.ExecuteSQL(query);

				for (int i=m_comboMaterial.GetCount();i>=0;i--)
					m_comboTolschina.DeleteString(i);

				if (m_pRecord->Open(CRecordset::snapshot,"select product_tols from itak_producttols order by product_tols desc"))
				{
					for(int i=0;!m_pRecord->IsEOF();i++)
					{
						m_pRecord->GetFieldValue("product_tols",strData);
						strData = strData.Trim();
						m_comboTolschina.InsertString(0,strData);
						m_pRecord->MoveNext();
					}
				}
				m_pRecord->Close();

				CString str;
				for (int i=0;i<m_comboTolschina.GetCount();i++)
				{
					m_comboTolschina.GetLBText(i,str);
					if (str == m_addZakazchik->GetData())
					{
						m_comboTolschina.SetCurSel(i);
						break;
					}
				}
				OnCbnSelchangeComboTolschina();
			}
			else MessageBox("Данное значение уже есть в базе данных");
		}
	}

	delete m_addZakazchik;	
}

void CChooseProduct::OnBnClickedButtonAddproduct()
{
	m_addZakazchik = new CAddZakazchik;
	m_addZakazchik->SetName("Додати новий продукт:");
	if (m_addZakazchik->DoModal()==IDOK)
	{
		CString str;
		m_comboZakazchik.GetLBText(m_comboZakazchik.GetCurSel(),str);

		if (m_database.IsOpen())
		{
			query.Format("select id from itak_zakazchik where zakazchik_name='%s'",str);
			if (m_pRecord->Open(CRecordset::snapshot,query))
			{
				for(int i=0;!m_pRecord->IsEOF();i++)
				{
					m_pRecord->GetFieldValue("id",str);

					m_pRecord->MoveNext();
				}
			}
			m_pRecord->Close();


			bool bRepeat = false;
			query.Format("select count(id) from itak_etiketka.dbo.itak_product where product_name='%s' and id_zakazchik=%s",m_addZakazchik->GetData(),str);
			if (m_pRecord->Open(CRecordset::snapshot,query))
			{
				short index = 0;
				for(int i=0;!m_pRecord->IsEOF();i++)
				{
					m_pRecord->GetFieldValue(index,strData);
					strData = strData.Trim();
					m_pRecord->MoveNext();
				}
			}
			m_pRecord->Close();

			if (strData=="0")
				bRepeat = true;
			else
				bRepeat=false;


			if (bRepeat==true)
			{
				query.Format("insert into itak_etiketka.dbo.itak_product (product_name,id_zakazchik) values ('%s',%s)",m_addZakazchik->GetData(),str);
				m_database.ExecuteSQL(query);


				/////////////////////////////////////////
				CRecordset record2(&m_database);
				CString strData1;

				for (int k=0;k<m_spinCountProduct.GetPos();k++)		
				{
					for (int j=m_pcomboProduct[k].GetCount();j>=0;j--)
						m_pcomboProduct[k].DeleteString(j);

					CString str;
					m_comboZakazchik.GetLBText(m_comboZakazchik.GetCurSel(),str);
				
					query.Format("select id from itak_zakazchik where zakazchik_name='%s'",str);
					if (m_pRecord->Open(CRecordset::snapshot,query))
					{
						for(int i=0;!m_pRecord->IsEOF();i++)
						{
							m_pRecord->GetFieldValue("id",strData);
							strData = strData.Trim();
							query.Format("select product_name from itak_product where id_zakazchik=%s order by product_name desc",strData);
							if (record2.Open(CRecordset::snapshot,query))
							{
								for(int i=0;!record2.IsEOF();i++)
								{
									record2.GetFieldValue("product_name",strData1);
									strData1 = strData1.Trim();
									m_pcomboProduct[k].InsertString(0,strData1);

									record2.MoveNext();
								}
							}
							record2.Close();

							m_pRecord->MoveNext();
						}
					}
					m_pRecord->Close();
				}
			}
			else MessageBox("Данное значение уже есть в базе данных");
			////////////////////////
		}

		/**/


		/*query.Format("select id from itak_zakazchik where zakazchik_name='%s'",str);
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}
		res = mysql_store_result(mysql);
		row = mysql_fetch_row(res);*/
		
		/*if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
		}*/
	
		/*for (int i=0;i<m_spinCountProduct.GetPos();i++)		
		{
			for (int j=m_pcomboProduct[i].GetCount();j>=0;j--)
					m_pcomboProduct[i].DeleteString(j);

			CString str;
			m_comboZakazchik.GetLBText(m_comboZakazchik.GetCurSel(),str);
			query.Format("select id from itak_zakazchik where zakazchik_name='%s'",str);
			if (mysql_query(mysql,query)!=0) 
			{
				CString str;
				str.Format("Ошибочный запрос!!! query='%s'",query);
				MessageBox(str);
			}
			res = mysql_store_result(mysql);
			while((row = mysql_fetch_row(res)))
			{
				query.Format("select product_name from itak_product where id_zakazchik=%s order by product_name asc",row[0]);
				if (mysql_query(mysql,query)!=0) 
				{
					CString str;
					str.Format("Ошибочный запрос!!! query='%s'",query);
					MessageBox(str);; 
					break ;
				}
				res2 = mysql_store_result(mysql);
				while((row2 = mysql_fetch_row(res2)))
					m_pcomboProduct[i].InsertString(0,row2[0]);
			}
		}*/
	}
	delete m_addZakazchik;		
}

void CChooseProduct::OnBnClickedButtonAddwidth()
{
	m_addZakazchik = new CAddZakazchik;
	m_addZakazchik->SetName("Додати нову ширину:");
	if (m_addZakazchik->DoModal()==IDOK)
	{

		bool bRepeat = false;
		if (m_database.IsOpen())
		{
			query.Format("select count(id) from itak_etiketka.dbo.itak_productwidth where product_width=%s",m_addZakazchik->GetData());
			if (m_pRecord->Open(CRecordset::snapshot,query))
			{
				short index = 0;
				for(int i=0;!m_pRecord->IsEOF();i++)
				{
					m_pRecord->GetFieldValue(index,strData);
					strData = strData.Trim();
					m_pRecord->MoveNext();
				}
			}
			m_pRecord->Close();

			if (strData=="0")
				bRepeat = true;
			else
				bRepeat=false;

			if (bRepeat==true)
			{
				query.Format("insert into itak_etiketka.dbo.itak_productwidth (product_width) values (%s);",m_addZakazchik->GetData());
				m_database.ExecuteSQL(query);

				for (int i=0;i<m_spinCountProduct.GetPos();i++)		
				{
					for (int j=m_pcomboWidthProduct[i].GetCount();j>=0;j--)
						m_pcomboWidthProduct[i].DeleteString(j);
				}

				if (m_pRecord->Open(CRecordset::snapshot,"select product_width from itak_productwidth order by product_width desc"))
				{
					for(int i=0;!m_pRecord->IsEOF();i++)
					{
						m_pRecord->GetFieldValue("product_width",strData);

						strData = strData.Trim();
						for (int j=0;j<m_spinCountProduct.GetPos();j++)		
							m_pcomboWidthProduct[j].InsertString(0,strData);
						m_pRecord->MoveNext();
					}
				}
				m_pRecord->Close();
			}
			else MessageBox("Данное значение уже есть в базе данных");

		}
	}
			
	delete m_addZakazchik;	
}

BOOL CChooseProduct::PreTranslateMessage(MSG* pMsg)
{
	if ( TranslateAccelerator( m_hWnd, m_hAccel, pMsg ) ) return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}


void CChooseProduct::SetCountProduct(int iCount)
{
	m_iCountProduct2 = iCount;
}



void CChooseProduct::SetZakazchik(CString strZakazchik)
{
	m_strZakazchik = strZakazchik;
}

void CChooseProduct::SetProduct(CString * strProduct)
{
	for (int i=0;i<m_iCountProduct2;i++)
		m_strProduct[i] = strProduct[i];
}

void CChooseProduct::SetWidthProduct(CString *strWidth)
{
	for (int i=0;i<m_iCountProduct2;i++)
		m_strProductWidth[i] = strWidth[i];
}

void CChooseProduct::SetCountDorojec(int * iCountDoroj)
{
	for (int i=0;i<m_iCountProduct2;i++)
		m_iCountDorojec2[i] = iCountDoroj[i];
}

void CChooseProduct::SetTolschina(CString strTolschina)
{
	m_strTolschina = strTolschina;
}

void CChooseProduct::SetMaterial(CString strMaterial)
{
	m_strMaterial = strMaterial;
}

void CChooseProduct::SetManager(CString strManager)
{
	m_strManager = strManager;
}

void CChooseProduct::SetDlinaRylona(int iDlinaRylona)
{
	if (iDlinaRylona!=0)
		m_iDlinaRylona = iDlinaRylona;
	else m_iDlinaRylona = 0;
}

void CChooseProduct::SetDlinaEtiketki(int iDlinaEtiketki)
{
	if (iDlinaEtiketki!=0)
		m_iDlinaEtiketki = iDlinaEtiketki;
	else m_iDlinaEtiketki = 0;
}

void CChooseProduct::SetCountEtiketki(int iCountEtiketki)
{
	if (iCountEtiketki!=0)
		m_iCountEtiketki = iCountEtiketki;
	else m_iCountEtiketki = 0;
}

void CChooseProduct::SetVesTary(double *dVesTary)
{
	for (int i=0;i<m_iCountProduct2;i++)
		m_dVagaTary[i] = dVesTary[i];
}


void CChooseProduct::SetPartiya(CString strPartiya)
{
	m_strPartiya = strPartiya;
}


void CChooseProduct::OnEnChangeEditNumprintpage()
{
	if (GetDlgItem(IDC_BUTTON_NEXT)->IsWindowEnabled()==FALSE && GetDlgItem(IDC_SPIN_NUMPRINTPAGE)->IsWindowEnabled()==TRUE)
	{
		m_statNumPrintpage.SetTextColor(GREEN_TEXT);
		GetDlgItem(IDC_BUTTON_NEXT)->EnableWindow(TRUE);
	}	
}

void CChooseProduct::SetVhidRylonNetto(double netto)
{
 	if (netto>0)
 		m_dVhidRylonNetto = netto;
 	else m_dVhidRylonNetto = 0;
}
void CChooseProduct::SetVhidRylonBrytto(double brytto)
{
	if (brytto>0)
		m_dVhidRylonBrytto = brytto;
	else m_dVhidRylonBrytto = 0;
}

void CChooseProduct::SetVhidRylonDlina(int dlina)
{
	if (dlina>0)
		m_iVhidRylonDlina = dlina;
	else m_iVhidRylonDlina = dlina;
}

void CChooseProduct::SetNumPrintPage(int num)
{
	//if (num>0)
		m_iNumPrintPage = num;
	//else m_iNumPrintPage = 0;
}

void CChooseProduct::OnEnChangeEditVhidrylonNetto()
{
	CString str;
	m_editVhidRylonNetto.GetWindowText(str);
	static int c1=0;	

	if (str.GetLength()!=0)
	{
		if (strcmp(str.Right(1),"0")==0
			|| strcmp(str.Right(1),"1")==0
			|| strcmp(str.Right(1),"2")==0
			|| strcmp(str.Right(1),"3")==0
			|| strcmp(str.Right(1),"4")==0
			|| strcmp(str.Right(1),"5")==0
			|| strcmp(str.Right(1),"6")==0
			|| strcmp(str.Right(1),"7")==0
			|| strcmp(str.Right(1),"8")==0
			|| strcmp(str.Right(1),"9")==0
			|| strcmp(str.Right(1),".")==0
			|| strcmp(str.Right(1),",")==0)
		{
			if (strcmp(str.Left(1),",")==0
				|| strcmp(str.Left(1),".")==0)
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_editVhidRylonNetto.SetWindowText(str);
			}
			else if (str.GetLength()==2 && strcmp(str.Left(1),"0")==0 &&(strcmp(str.Right(1),",")!=0 &&strcmp(str.Right(1),".")!=0))
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_editVhidRylonNetto.SetWindowText(str);
			}
			else if (strcmp(str.Right(1),",")==0 || strcmp(str.Right(1),".")==0)
			{
				if (c1>=1)
				{
					MessageBox("Некоректний ввід");
					str = "";
					m_editVhidRylonNetto.SetWindowText(str);
					c1=0;
				}else c1++;		
			}
			else 
			{
				if (GetDlgItem(IDC_EDIT_VHIDRYLON_BRYTTO)->IsWindowEnabled()==FALSE)
				{
					m_myStatVhidniyRylonNetto.SetTextColor(GREEN_TEXT);
					if (change!=1)
						m_myStatVhidniyRylonBrytto.SetTextColor(RED_TEXT);
					m_myStatVhidniyRylonBrytto.SetFont(20);
					CString s;
					m_editVhidRylonBrytto.GetWindowText(s);
					if (s.GetLength()<=1)
						Invalidate();
					GetDlgItem(IDC_EDIT_VHIDRYLON_BRYTTO)->EnableWindow(TRUE);
				}				
			}
		}
		else
		{
			MessageBox("Некоректний ввід");
			str = "";
			m_editVhidRylonNetto.SetWindowText(str);
		}
		if (str.Find(',')!=-1)
			str.Replace(',','.');
	}	
}

void CChooseProduct::OnEnChangeEditVhidrylonBrytto()
{
	CString str;
	m_editVhidRylonBrytto.GetWindowText(str);
	static int c1=0;	

	if (str.GetLength()!=0)
	{
		if (strcmp(str.Right(1),"0")==0
			|| strcmp(str.Right(1),"1")==0
			|| strcmp(str.Right(1),"2")==0
			|| strcmp(str.Right(1),"3")==0
			|| strcmp(str.Right(1),"4")==0
			|| strcmp(str.Right(1),"5")==0
			|| strcmp(str.Right(1),"6")==0
			|| strcmp(str.Right(1),"7")==0
			|| strcmp(str.Right(1),"8")==0
			|| strcmp(str.Right(1),"9")==0
			|| strcmp(str.Right(1),".")==0
			|| strcmp(str.Right(1),",")==0)
		{
			if (strcmp(str.Left(1),",")==0
				|| strcmp(str.Left(1),".")==0)
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_editVhidRylonBrytto.SetWindowText(str);
			}
			else if (str.GetLength()==2 && strcmp(str.Left(1),"0")==0 &&(strcmp(str.Right(1),",")!=0 &&strcmp(str.Right(1),".")!=0))
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_editVhidRylonBrytto.SetWindowText(str);
			}
			else if (strcmp(str.Right(1),",")==0 || strcmp(str.Right(1),".")==0)
			{
				if (c1>=1)
				{
					MessageBox("Некоректний ввід");
					str = "";
					m_editVhidRylonBrytto.SetWindowText(str);
					c1=0;
				}else c1++;		
			}
			else 
			{
				if (GetDlgItem(IDC_EDIT_VHIDRYLON_DLINA)->IsWindowEnabled()==FALSE)
				{
					m_myStatVhidniyRylonBrytto.SetTextColor(GREEN_TEXT);
					m_myStatVhidniyRylonDlina.SetTextColor(RED_TEXT);
					m_myStatVhidniyRylonDlina.SetFont(20);
					CString s;
					m_editVhidRylonDlina.GetWindowText(s);
					if (s.GetLength()<=1)
						Invalidate();
					GetDlgItem(IDC_EDIT_VHIDRYLON_DLINA)->EnableWindow(TRUE);
				}
			}
		}
		else
		{
			MessageBox("Некоректний ввід");
			str = "";
			m_editVhidRylonBrytto.SetWindowText(str);
		}
		if (str.Find(',')!=-1)
			str.Replace(',','.');
	}
}

void CChooseProduct::OnEnChangeEditVhidrylonDlina()
{
	if (GetDlgItem(IDC_EDIT_DLINARYLONA)->IsWindowEnabled()==FALSE)
	{
		m_myStatVhidniyRylonDlina.SetTextColor(GREEN_TEXT);
		if (change!=1)
			m_statDlinaRylona.SetTextColor(RED_TEXT);
		m_statDlinaRylona.SetFont(20);
		CString s;
		m_editDlinaRylona.GetWindowText(s);
		if (s.GetLength()<=1)
			Invalidate();
		GetDlgItem(IDC_EDIT_DLINARYLONA)->EnableWindow(TRUE);
	}
}

void CChooseProduct::OnBnClickedButtonAddvagatary()
{
	m_addZakazchik = new CAddZakazchik;
	m_addZakazchik->SetName("Додати нову вагу тари:");
	if (m_addZakazchik->DoModal()==IDOK)
	{
		bool bRepeat = false;
		if (m_database.IsOpen())
		{
			query.Format("select count(id) from itak_etiketka.dbo.itak_vagatary where vaga=%s",m_addZakazchik->GetData());
			if (m_pRecord->Open(CRecordset::snapshot,query))
			{
				short index = 0;
				for(int i=0;!m_pRecord->IsEOF();i++)
				{
					m_pRecord->GetFieldValue(index,strData);
					strData = strData.Trim();
					m_pRecord->MoveNext();
				}
			}
			m_pRecord->Close();

			if (strData=="0")
				bRepeat = true;
			else
				bRepeat=false;

			if (bRepeat==true)
			{
				query.Format("insert into itak_etiketka.dbo.itak_vagatary (vaga) values (%s);",m_addZakazchik->GetData());
				m_database.ExecuteSQL(query);

				for (int i=0;i<m_spinCountProduct.GetPos();i++)		
				{
					for (int j=m_pcomboVagaTary[i].GetCount();j>=0;j--)
						m_pcomboVagaTary[i].DeleteString(j);
				}

				CString str;
				double val=0;

				if (m_pRecord->Open(CRecordset::snapshot,"select vaga from itak_vagatary order by vaga desc"))
				{
					for(int i=0;!m_pRecord->IsEOF();i++)
					{
						m_pRecord->GetFieldValue("vaga",strData);
						strData = strData.Trim();
						val = atof(strData.GetBuffer(strData.GetLength()));
						str.Format("%.2f",val);
						for (int j=0;j<m_spinCountProduct.GetPos();j++)		
							m_pcomboVagaTary[j].InsertString(0,str);
						m_pRecord->MoveNext();
					}
				}
				m_pRecord->Close();
			}
			else MessageBox("Данное значение уже есть в базе данных");

		}
	}

	delete m_addZakazchik;	
}

void CChooseProduct::SetLogo(bool bLogo)
{
		m_bLogo = bLogo;
}
void CChooseProduct::SetData(SYSTEMTIME sysTime)
{
	m_sysDate = sysTime;
}
