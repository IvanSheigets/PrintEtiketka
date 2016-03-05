// WorkDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "WorkDialog.h"
#include "QPrint.h"

#define BLUE_TEXT RGB(0,0,255)
#define RED_TEXT RGB(255,0,0)

struct MyStruct
{
	CString strNumber;
	CString	strBrytto;
	CString strNetto;
};




// диалоговое окно CWorkDialog

IMPLEMENT_DYNAMIC(CWorkDialog, CDialog)

CWorkDialog::CWorkDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkDialog::IDD, pParent), m_dNetto(0), m_dBrytto(0),m_iNumList(0),
							m_dTempVaga(0),count(1),m_dZagNetto(0),m_dZagBrytto(0),
							m_iZagRylonPorezCount(0),regim(0),m_iZagDlinaZakaza(0),
							m_boolNewZakaz(TRUE),m_boolEndZakaz(TRUE),m_iZagCountEtiketok(0),
							m_iNumPrintPage(0),m_iNumCar(0),m_iNumSmena(0),m_dVhidRylonNetto(0),
							m_dVhidRylonBrytto(0),m_iVhidRylonDlina(0),m_dZagVhidRylonNetto(0),
							m_dZagVhidRylonBrytto(0),m_iZagVhidRylonDlina(0),m_dOstattokKg(0),
							m_dOthodKG(0),m_dObrezokKG(0),m_dBrakKG(0),m_dBrakTPKG(0),m_dNedostatokKG(0),
							m_boolFocusObrezok(FALSE),m_boolFocusOthod(FALSE),m_boolFocusBrak(FALSE),
							m_boolFocusBrakTP(FALSE),m_boolFocusNeDostatok(FALSE),m_boolFocusOstatok(FALSE),
							m_boolFocusOstatokWidth(FALSE),m_dOstatokWidth(0),m_boolButtonExit(FALSE),
							m_iNumZakaz(0),m_iCountEtiketki(0),m_bNewZakazId(FALSE),m_iProductId(0)
{
	m_pEditBkBrushActiv = new CBrush(RGB(0,255,0));
	m_hAccel = LoadAccelerators( AfxGetResourceHandle(), MAKEINTRESOURCE( IDR_WORK_ACCELERATOR ) );

	for (int i=0;i<10;i++)
	{
		m_dObNetto[i] = m_dObBrytto[i] = 0;
		m_iDlinaPorezRylon[i] = 0;
		m_piCountRylon[i] = 0;
		m_piCountEtiketok[i] = 0;
		m_dVagaTary[i]=0;
	}

	m_vMyRecord.clear();
}

CWorkDialog::~CWorkDialog()
{

 	CloseHandle(hFile);
// 	query.Format("update itak_zakaz set vesnetto=%.2f, vesbrytto=%.2f, kolrylonov=%d where id=%d",m_dZagNetto,m_dZagBrytto,m_iZagRylonPorezCount,m_iZakazId);
// 	if (mysql_query(mysql,query)!=0)  MessageBox("Ошибочный запрос!!!");
 	//mysql_close(mysql);

}

void CWorkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, 15110, m_listEndProduct);
}


BEGIN_MESSAGE_MAP(CWorkDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CWorkDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWorkDialog::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CWorkDialog::OnBnClickedButtonAdd)
	ON_BN_CLICKED(15022, &CWorkDialog::OnBnClickedButtonExit)
	ON_BN_CLICKED(15024, &CWorkDialog::OnBnClickedButtonEndZakaz)
	ON_BN_CLICKED(15023, &CWorkDialog::OnBnClickedButtonNewSmena)
	ON_BN_CLICKED(15025, &CWorkDialog::OnBnClickedButtonChangeZakaz)
	ON_BN_CLICKED(16001, &CWorkDialog::OnBnClickedButtonNewZakaz)
	ON_BN_CLICKED(1789, &CWorkDialog::OnBnClickedButtonPrintZvit)

	
	ON_BN_CLICKED(ID_ACCELERATOR_CHANGEDLINA, &CWorkDialog::OnAccelChangeDlina)
	ON_BN_CLICKED(ID_ACCELERATOR_SKLEYKA, &CWorkDialog::OnAccelNewRylon)
	
	ON_EN_CHANGE(16201, &CWorkDialog::OnEnChangeEditObrezok)
	ON_EN_SETFOCUS(16201, &CWorkDialog::OnEnSetfocusEditObrezok)
	ON_EN_CHANGE(16211, &CWorkDialog::OnEnChangeEditOthod)
	ON_EN_SETFOCUS(16211, &CWorkDialog::OnEnSetfocusEditOthod)
	ON_EN_CHANGE(16221, &CWorkDialog::OnEnChangeEditOstatok)
	ON_EN_SETFOCUS(16221, &CWorkDialog::OnEnSetfocusEditOstatok)
	ON_EN_CHANGE(16231, &CWorkDialog::OnEnChangeEditBrak)
	ON_EN_SETFOCUS(16231, &CWorkDialog::OnEnSetfocusEditBrak)
	ON_EN_CHANGE(16241, &CWorkDialog::OnEnChangeEditBrakTP)
	ON_EN_SETFOCUS(16241, &CWorkDialog::OnEnSetfocusEditBrakTP)
	ON_EN_CHANGE(16302, &CWorkDialog::OnEnChangeEditNeDostatok)
	ON_EN_SETFOCUS(16302, &CWorkDialog::OnEnSetfocusEditNeDostatok)
	ON_EN_SETFOCUS(16221, &CWorkDialog::OnEnSetfocusEditOstatok)
	ON_EN_SETFOCUS(16301, &CWorkDialog::OnEnSetfocusEditOstatokWidth)

	ON_NOTIFY(LVN_ITEMACTIVATE, 15080, &CWorkDialog::OnLvnItemActivateList1)
	ON_NOTIFY(LVN_ITEMACTIVATE, 15081, &CWorkDialog::OnLvnItemActivateList2)
	ON_NOTIFY(LVN_ITEMACTIVATE, 15082, &CWorkDialog::OnLvnItemActivateList3)
	ON_NOTIFY(LVN_ITEMACTIVATE, 15083, &CWorkDialog::OnLvnItemActivateList4)
	ON_NOTIFY(LVN_ITEMACTIVATE, 15084, &CWorkDialog::OnLvnItemActivateList5)
	ON_NOTIFY(LVN_ITEMACTIVATE, 15085, &CWorkDialog::OnLvnItemActivateList6)
	ON_NOTIFY(LVN_ITEMACTIVATE, 15086, &CWorkDialog::OnLvnItemActivateList7)
	ON_NOTIFY(LVN_ITEMACTIVATE, 15087, &CWorkDialog::OnLvnItemActivateList8)
	ON_NOTIFY(LVN_ITEMACTIVATE, 15088, &CWorkDialog::OnLvnItemActivateList9)
	ON_NOTIFY(LVN_ITEMACTIVATE, 15089, &CWorkDialog::OnLvnItemActivateList10)

	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_LBN_SELCHANGE(15110, &CWorkDialog::OnLbnSelchangeEndListProduct)
	ON_COMMAND(ID_ACCELERATOR_EXTADD, &CWorkDialog::OnAcceleratorExtadd)
	ON_COMMAND(ID_ACCELERATOR_ADDOBRAZETS, &CWorkDialog::OnAcceleratorAddobrazets)
END_MESSAGE_MAP()


// обработчики сообщений CWorkDialog

void CWorkDialog::OnBnClickedOk()
{
	OnOK();
}

void CWorkDialog::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	//OnCancel();
}


BOOL CWorkDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	int iWindowPos = 20;
	MoveWindow(iWindowPos,iWindowPos,x-iWindowPos*2,y-iWindowPos*2);

	GetClientRect(&m_rectClient);

	CString str;
		
	int left = m_rectClient.left+((iWindowPos-10)/2);
	int top = m_rectClient.top+((iWindowPos-10)/2);

	for (int i=0;i<m_iCountProduct;i++)
		m_dObNetto[i] = m_dObBrytto[i] = 0;	
	
	m_statBorder.CreateEx(WS_EX_CLIENTEDGE, "STATIC", NULL,	WS_CHILD | WS_TABSTOP | WS_VISIBLE,left, top, m_rectClient.right-(iWindowPos-10), 50, m_hWnd, (HMENU)1234);	
	
	CRect rect;
	m_statBorder.GetClientRect(&rect);	
	int width = 220;
	font_size = 18;
	
	width = ((rect.right-40) / 4) - 50;
	int	rastoyanie = ((rect.right - 40) -(4*width))/ (3);
	
	int left_first = left+20;
	m_statZakazchik.Create("Замовник:",WS_CHILD|WS_VISIBLE,CRect(left_first,top+5,left_first+70,top+25),this,15000);
	m_myStatZakazchik.SetFont(font_size);
	m_myStatZakazchik.SetTextColor(BLUE_TEXT);
	m_myStatZakazchik.Create(m_strZakazchik,WS_VISIBLE|WS_CHILD,CRect(left_first+75,top+4,width+left_first,top+25),this,15001);

	int left_second = left_first+width+rastoyanie;
	m_statTolschina.Create("Товщина:",WS_CHILD|WS_VISIBLE,CRect(left_second,top+5,left_second+70,top+25),this,15002);
 	m_myStatTolschina.SetTextColor(BLUE_TEXT);
	m_myStatTolschina.SetFont(font_size);
 	m_myStatTolschina.Create(m_strTolschina+" мкм",WS_CHILD|WS_VISIBLE,CRect(left_second+70,top+4,width+left_second,top+25),this,15003);

	int left_third = left_second+width+rastoyanie;
 	m_statVagaTary.Create("Вага тари:",WS_CHILD|WS_VISIBLE,CRect(left_third,top+5,left_third+70,top+25),this,15004);
 	m_myStatVagaTary.SetTextColor(BLUE_TEXT);
	m_myStatVagaTary.SetFont(font_size);
 	str.Format("%.2f кг",m_dVagaTary[0]);
 	m_myStatVagaTary.Create(str,WS_CHILD|WS_VISIBLE,CRect(left_third+75,top+4,width+left_third,top+25),this,15005);

	int left_fourth = left_third+width+rastoyanie;
	m_statPartiya.Create("Партія:",WS_CHILD|WS_VISIBLE,CRect(left_fourth,top+5,left_fourth+50,top+25),this,15006);
	m_myStatPartiya.SetTextColor(BLUE_TEXT);
	m_myStatPartiya.SetFont(font_size);
	m_myStatPartiya.Create(m_strPartiya,WS_CHILD|WS_VISIBLE,CRect(left_fourth+55,top+4,left_fourth+width,top+25),this,15007);

 	m_statDlinaRylona.Create("Довжина рулону:",WS_CHILD|WS_VISIBLE,CRect(left_first,top+30,left_first+120,top+45),this,15008);
	m_myStatDlinaRylona.SetTextColor(BLUE_TEXT);
	str.Format("%d м",m_iDlinaRylona);
	m_myStatDlinaRylona.SetFont(font_size);
	m_myStatDlinaRylona.Create(str,WS_VISIBLE|WS_CHILD,CRect(left_first+125,top+29,width+left_first,top+45),this,15009);

	m_statDlinaEtiketki.Create("Довжина етикетки:",WS_CHILD|WS_VISIBLE,CRect(left_second,top+30,left_second+130,top+45),this,15010);
	m_myStatDlinaEtiketki.SetTextColor(BLUE_TEXT);
	str.Format("%d мм",m_iDlinaEtiketki);
	m_myStatDlinaEtiketki.SetFont(font_size);
	m_myStatDlinaEtiketki.Create(str,WS_VISIBLE|WS_CHILD,CRect(left_second+135,top+29,width+left_second+10,top+45),this,15011);

	m_statCountEtiketok.Create("Кількість етикеток:",WS_CHILD|WS_VISIBLE,CRect(left_third,top+30,left_third+130,top+45),this,15012);
	m_myStatCountEtiketok.SetTextColor(BLUE_TEXT);
	str.Format("%d шт",m_iCountEtiketki);
	m_myStatCountEtiketok.SetFont(font_size);
	m_myStatCountEtiketok.Create(str,WS_VISIBLE|WS_CHILD,CRect(left_third+130,top+29,width+left_third,top+45),this,15013);

	m_statMaterial.Create("Матеріал:",WS_CHILD|WS_VISIBLE,CRect(left_fourth,top+30,left_fourth+70,top+45),this,15014);
	m_myStatMaterial.SetTextColor(BLUE_TEXT);
	m_myStatMaterial.SetFont(font_size);
	m_myStatMaterial.Create(m_strMaterial,WS_VISIBLE|WS_CHILD,CRect(left_fourth+75,top+29,width+left_fourth,top+45),this,15015);
//////////////////////////////////////////////////////////////////////////
	//int left_zagves = m_rectClient.right/2 - 300/2-50;
	/*int left_zagves = m_rectClient.left+50;
	int top_zagves = m_rectClient.bottom-10;
	m_statBorder2.CreateEx(WS_EX_CLIENTEDGE, "STATIC", NULL,	WS_CHILD | WS_TABSTOP | WS_VISIBLE,left_zagves-10, top_zagves-90,290,75 , m_hWnd, (HMENU)1234);	

	m_statProductZagNetto.Create("Загальна вага нетто:",WS_CHILD|WS_VISIBLE,CRect(left_zagves,top_zagves-80,left_zagves+150,top_zagves-60),this,15016);
	m_statProductZagBrytto.Create("Загальна вага брутто:",WS_CHILD|WS_VISIBLE,CRect(left_zagves,top_zagves-60,left_zagves+160,top_zagves-40),this,15017);
	m_statRylonPorezCount.Create("Кількість порізаних рулонів:",WS_CHILD|WS_VISIBLE,CRect(left_zagves,top_zagves-40,left_zagves+200,top_zagves-25),this,15018);

	str.Format("%.2f кг",m_dZagNetto);
	m_myStatProductZagNetto.SetTextColor(BLUE_TEXT);
	m_myStatProductZagNetto.Create(str,WS_CHILD|WS_VISIBLE,CRect(left_zagves+160,top_zagves-80,left_zagves+260,top_zagves-60),this,15019);

	str.Format("%.2f кг",m_dZagBrytto);
	m_myStatProductBrytto.SetTextColor(BLUE_TEXT);
	m_myStatProductBrytto.Create(str,WS_CHILD|WS_VISIBLE,CRect(left_zagves+170,top_zagves-60,left_zagves+270,top_zagves-40),this,15020);

	str.Format("%d шт",m_iZagRylonPorezCount);
	m_myStatRylonPorezCount.SetTextColor(BLUE_TEXT);
	m_myStatRylonPorezCount.Create(str,WS_CHILD|WS_VISIBLE,CRect(left_zagves+210,top_zagves-40,left_zagves+270,top_zagves-25),this,15021);
	*/

	
//////////////////////////////////////////////////////////////////////////

	int but_left = m_rectClient.right-110;
	int but_top = m_rectClient.bottom-75;
	m_butExit.SetTextColor(RED_TEXT);
	m_butExit.Create("Вихід",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_OWNERDRAW,CRect(but_left,but_top,but_left+100,but_top+50),this,15022);
	GetDlgItem(15022)->ShowWindow(FALSE);


	int xx = m_rectClient.left+20+450+20;
	int yy = m_rectClient.top+80;

	m_butPrintZvit.SetTextColor(BLUE_TEXT);
	m_butPrintZvit.Create("Друкувати звіт",WS_VISIBLE|WS_CHILD|BS_OWNERDRAW,CRect(xx,yy+195+10,xx+150,yy+195+50),this,1789);
	GetDlgItem(1789)->ShowWindow(FALSE);


	m_butNewSmena.SetTextColor(BLUE_TEXT);
	m_butNewSmena.Create("Нова зміна",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_OWNERDRAW,CRect(but_left-110,but_top,but_left-10,but_top+50),this,15023);
	m_butEndZakaz.SetTextColor(BLUE_TEXT);
	m_butEndZakaz.Create("Кінець замовлення",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_OWNERDRAW,CRect(but_left-270,but_top,but_left-120,but_top+50),this,15024);

	m_butChangeZakaz.SetTextColor(BLUE_TEXT);
	m_butChangeZakaz.Create("Редагувати замовлення",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_OWNERDRAW,CRect(but_left-480,but_top,but_left-280,but_top+50),this,15025);
	//m_butChangeZakaz.Create(NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|BS_OWNERDRAW|WS_DISABLED,CRect(but_left-440,but_top,but_left-260,but_top+50),this,15025);
	m_butNewZakaz.SetTextColor(BLUE_TEXT);
	m_butNewZakaz.Create("Нове замовлення",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_OWNERDRAW,CRect(but_left-250,but_top,but_left-120,but_top+50),this,16001);
	m_butNewZakaz.ShowWindow(FALSE);

	int smena_top = m_rectClient.bottom - 50;
	int smena_left = m_rectClient.left+30;
	
	m_statSmena.SetFont(20);
	m_statSmena.Create("Зміна:",WS_CHILD|WS_VISIBLE,CRect(smena_left,smena_top,smena_left+60,smena_top+20),this,15026);
	str.Format("%d/%d",m_iNumCar,m_iNumSmena);
	m_myStatSmena.SetTextColor(BLUE_TEXT);
	m_myStatSmena.SetFont(20);
	m_myStatSmena.Create(str,WS_VISIBLE|WS_CHILD,CRect(smena_left+70,smena_top,smena_left+100,smena_top+20),this,15026);

	CRect statusRect;
	m_status.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,m_rectClient.right,m_rectClient.bottom),this,10021);
	m_status.GetClientRect(&rect);
	int widths[] = { 200,rect.right};
	m_status.SetParts(2, widths) ;
	m_status.SetText("     F2 - зміна довжини рулону",0,0);
	m_status.SetText("     F3 - новий рулон",1,0);

	if (m_iCountProduct>0)
	{
		m_pmyStatProductName = new CMyStatic[m_iCountProduct];
		m_pstatWidth = new CStatic [m_iCountProduct];
		m_pmyStatProductWidth = new CMyStatic[m_iCountProduct];

		m_pstatCountDorojec = new CStatic [m_iCountProduct];
		m_pmyStatCountDorojec = new CMyStatic[m_iCountProduct];

		m_peditVes = new CEdit[m_iCountProduct];
		m_plistTabl = new CMyListCtrl [m_iCountProduct];

		m_pstatVesNetto = new CStatic [m_iCountProduct];
		m_pstatVesBrytto = new CStatic [m_iCountProduct];
		m_pmyStatVesNetto = new CMyStatic[m_iCountProduct];
		m_pmyStatVesBrytto = new CMyStatic[m_iCountProduct];

		m_pstatDlina = new CStatic[m_iCountProduct];
		m_pmyStatDlina = new CMyStatic[m_iCountProduct];


		int left = m_rectClient.left+20;
		int width = 100;
		int left_colomn[10];
		int rastoyanie = 50;

		width = ((m_rectClient.right-40) / m_iCountProduct) ;
		int bby = bby = m_rectClient.bottom -170;
 		if (m_iCountProduct!=1)
		{
			if (m_iCountProduct<=5)
			{
				width = ((m_rectClient.right-40) / m_iCountProduct) - 50;
				rastoyanie = ((m_rectClient.right - 40) -(m_iCountProduct*width))/ (m_iCountProduct-1);
			}
			else 
			{
				width = ((m_rectClient.right-40) / 5) - 50;
				rastoyanie = ((m_rectClient.right - 40) -(5*width))/ 4;
			}
		}
		int by = 0 ;
		int ty = 0;
		int height = 0;
		int columnCounter=0;
		int ras=100;
		for (int i=0;i<m_iCountProduct;i++)
		{
			if (i<5)
			{
				if (i==0)
					left_colomn[columnCounter] = left;
				else left_colomn[columnCounter] = left_colomn[i-1]+width+rastoyanie;

				height = (((m_rectClient.bottom)-170)/2)-80;
				ty = 70;
				by = ty+height;
			}
			else 
			{
				height = (((m_rectClient.bottom)-170)/2)-80;
				ty = 70+ras+height;
				by = ty+height;
			}

			if (m_iCountProduct<=5)
				by = bby;

			m_pmyStatProductName[i].SetTextColor(BLUE_TEXT); 
			m_pmyStatProductName[i].SetFont(font_size);
			m_pmyStatProductName[i].Create(m_strProduct[i],WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter],ty,left_colomn[columnCounter]+width,ty+20),this,15020+i);
			m_pstatWidth[i].Create("Ширина:",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter],ty+20,left_colomn[columnCounter]+60,ty+40),this,15030+i);

			m_pmyStatProductWidth[i].SetTextColor(BLUE_TEXT); 
			m_pmyStatProductWidth[i].SetFont(font_size);
			m_pmyStatProductWidth[i].Create(m_strProductWidth[i]+ " мм",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+70,ty+20,left_colomn[columnCounter]+width,ty+50),this,15040+i);

			m_pstatCountDorojec[i].Create("К-ть доріжок:",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter],ty+40,left_colomn[columnCounter]+90,ty+60),this,15050+i);
			m_pmyStatCountDorojec[i].SetTextColor(BLUE_TEXT); 
			m_pmyStatCountDorojec[i].SetFont(font_size);
			if (m_iCountProduct==1)
				m_iCountDorojec[0] = 1;
			str.Format("%d шт",m_iCountDorojec[i]);
			m_pmyStatCountDorojec[i].Create(str,WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+95,ty+40,left_colomn[columnCounter]+width,ty+60),this,15060+i);

			m_peditVes[i].Create(WS_VISIBLE|WS_CHILD|WS_BORDER|WS_EX_DLGMODALFRAME|WS_DISABLED|WS_TABSTOP,CRect(left_colomn[columnCounter],ty+60,left_colomn[columnCounter]+width,ty+80),this,15070+i);

			m_plistTabl[i].Create(WS_VISIBLE|WS_CHILD|WS_BORDER|LVS_REPORT|LVS_OWNERDRAWFIXED,CRect(left_colomn[columnCounter],ty+85,left_colomn[columnCounter]+width,by),this,15080+i);
			m_plistTabl[i].SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
			CRect columnRect;
			m_plistTabl[i].GetClientRect(&columnRect);
			int col = ((columnRect.right-30)/2)-7;			
			m_plistTabl[i].InsertColumn(0,"№",LVCFMT_LEFT,30);
			m_plistTabl[i].InsertColumn(1,"Брутто",LVCFMT_LEFT,col);
			m_plistTabl[i].InsertColumn(2,"Нетто",LVCFMT_LEFT,col);

			//////////////////////////////////////////////////////////////////////////
			m_pstatVesNetto[i].Create("Нетто:",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+5,by+5,left_colomn[columnCounter]+50,by+20),this,15090+i);
			m_pstatVesBrytto[i].Create("Брутто:",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+5,by+25,left_colomn[columnCounter]+55,by+40),this,15090+i);
			m_pstatDlina[i].Create("Довжина:",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+5,by+45,left_colomn[columnCounter]+70,by+60),this,15090+i);
//
			m_pmyStatVesNetto[i].SetFont(font_size);
			m_pmyStatVesNetto[i].SetTextColor(BLUE_TEXT);
			
			m_strObNetto[i].Format("%.2f",m_dObNetto[i]);
			m_pmyStatVesNetto[i].Create(m_strObNetto[i]+" кг",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+60,by+5,left_colomn[columnCounter]+width,by+20),this,16100+i);
			m_pmyStatVesBrytto[i].SetFont(font_size);
			m_pmyStatVesBrytto[i].SetTextColor(BLUE_TEXT);
			m_strObBrytto[i].Format("%.2f",m_dObBrytto[i]);
			m_pmyStatVesBrytto[i].Create(m_strObBrytto[i]+" кг",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+70,by+25,left_colomn[columnCounter]+width,by+40),this,16110+i);

			m_pmyStatDlina[i].SetFont(font_size);
			m_pmyStatDlina[i].SetTextColor(BLUE_TEXT);
			str.Format("%d м",m_iDlinaPorezRylon[i]);
			m_pmyStatDlina[i].Create(str,WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+90,by+45,left_colomn[columnCounter]+width,by+60),this,16110+i);

			//////////////////////////////////////////////////////////////////////////
			
			columnCounter++;
			if (i==4)
				columnCounter=0;
		}

		m_iZagVhidRylonDlina = m_iVhidRylonDlina;
		m_dZagVhidRylonBrytto = m_dVhidRylonBrytto;
		m_dZagVhidRylonNetto = m_dVhidRylonNetto;

		m_peditVes[0].EnableWindow(TRUE);
		m_peditVes[0].SetWindowText("");
		m_peditVes[0].SetFocus();

		DCB dcb;
		
		FILE * file;
		CString port;
		file = fopen("settings.txt","rb");
		if (file!=NULL)
		{
			char buf[1024];
			while (fgets(buf,1000,file)!='\0')
			{
				str.Format("%s",buf);
				str.Remove('\n');

// 				if (str.Left(str.Find(" "))=="port")
// 					port = str.Mid(str.Find(" ")+3);
// 				else if (str.Left(str.Find(" "))=="speed")
// 				{
// 					str = str.Mid(str.Find(" ")+3);
// 					if (str=="CBR_110")
// 						dcb.BaudRate = CBR_110;
// 					else if (str=="CBR_300")
// 						dcb.BaudRate = CBR_300;
// 					else if (str=="CBR_600")
// 						dcb.BaudRate = CBR_600;
// 					else if (str=="CBR_1200")
// 						dcb.BaudRate = CBR_1200;
// 					else if (str=="CBR_2400")
// 						dcb.BaudRate = CBR_2400;
// 					else if (str=="CBR_4800")
// 						dcb.BaudRate = CBR_4800;
// 					else if (str=="CBR_9600")
// 						dcb.BaudRate = CBR_9600;
// 					else if (str=="CBR_14400")
// 						dcb.BaudRate = CBR_14400;
// 					else if (str=="CBR_19200")
// 						dcb.BaudRate = CBR_19200;
// 					else if (str=="CBR_38400")
// 						dcb.BaudRate = CBR_38400;
// 					else if (str=="CBR_57600")
// 						dcb.BaudRate = CBR_57600;
// 					else if (str=="CBR_115200")
// 						dcb.BaudRate = CBR_115200;
// 					else if (str=="CBR_256000")
// 						dcb.BaudRate = CBR_256000;
// 				}	
// 				else if (str.Left(str.Find(" "))=="bits")
// 				{
// 					str = str.Mid(str.Find(" ")+3);
// 					if (str=="4")
// 						dcb.ByteSize = 4;
// 					if (str=="5")
// 						dcb.ByteSize = 5;
// 					if (str=="6")
// 						dcb.ByteSize = 6;
// 					if (str=="7")
// 						dcb.ByteSize = 7;
// 					if (str=="8")
// 						dcb.ByteSize = 8;
// 				}
// 				else if (str.Left(str.Find(" "))=="chet")
// 				{
// 					str = str.Mid(str.Find(" ")+3);
// 					if (str=="EVENPARITY")
// 						dcb.Parity = EVENPARITY; 
// 					else if (str=="ODDPARITY")
// 						dcb.Parity = ODDPARITY; 
// 					else if (str=="NOPARITY")
// 						dcb.Parity = NOPARITY; 
// 					else if (str=="MARKPARITY")
// 						dcb.Parity = MARKPARITY; 
// 					else if (str=="SPACEPARITY")
// 						dcb.Parity = SPACEPARITY; 
// 				}
// 				else if (str.Left(str.Find(" "))=="stopbits")
// 				{
// 					str = str.Mid(str.Find(" ")+3);
// 					if (str=="ONESTOPBIT")
// 						dcb.StopBits = ONESTOPBIT; 
// 					else if (str=="ONE5STOPBITS")
// 						dcb.StopBits = ONE5STOPBITS; 
// 					else if (str=="TWOSTOPBITS")
// 						dcb.StopBits = TWOSTOPBITS; 
// 				}
				if (str.Left(str.Find(" "))=="printEtik")
					m_strPrintEtiketka = str.Mid(str.Find(" ")+3);
				else if (str.Left(str.Find(" "))=="printShtih")
					m_strPrintShtrih = str.Mid(str.Find(" ")+3);				
			}
			fclose(file);
		}
		else 
		{
// 			dcb.ByteSize = 7;       
// 			dcb.Parity   = NOPARITY;        
// 			dcb.StopBits = TWOSTOPBITS;    
// 			dcb.BaudRate = CBR_9600;
// 			port = "COM2";
		}

		port = "COM2";
		hFile = CreateFile(port,GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if(hFile==INVALID_HANDLE_VALUE){
			MessageBox("error open port Com2");
			CloseHandle(hFile);

						
		};

		GetCommState(hFile, &dcb);
		
		COMMTIMEOUTS CommTimeOuts;
		CommTimeOuts.ReadIntervalTimeout		 = MAXDWORD;
		CommTimeOuts.ReadTotalTimeoutMultiplier  = 0;
		CommTimeOuts.ReadTotalTimeoutConstant    = 0;
		CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
		CommTimeOuts.WriteTotalTimeoutConstant   = 1000;

		SetCommTimeouts(hFile, &CommTimeOuts);
		
		dcb.fParity = TRUE;
		dcb.fOutX = FALSE;
		dcb.ByteSize = 7;       
		dcb.Parity   = EVENPARITY;        
		dcb.StopBits = TWOSTOPBITS;    
		dcb.BaudRate = CBR_9600;

		//dcb.fParity = TRUE;
		//dcb.fOutX = FALSE;
		/*dcb.ByteSize = 8;       
		dcb.Parity   = NOPARITY;        
		dcb.StopBits = ONE5STOPBITS;    
		dcb.BaudRate = CBR_9600;*/
		
		
		SetCommState(hFile, &dcb);
		SetTimer(0,500,0);


		if (!m_database.IsOpen())
		{
			CString strConString = "Driver={SQL Server}; Server="+m_strServerAddr+"; Database=itak_etiketka; UID="+m_strMysqlLogin+"; PWD="+m_strMysqlPass+"";
			if (!m_database.OpenEx(strConString,CDatabase::noOdbcDialog))
			{
				MessageBox("Не возможно подключиться к Базе Данных. Обратитесь к администратору");
				return -1;
			}

			m_pRecord =new CRecordset(&m_database);

			query.Format("select id from itak_zakazchik where zakazchik_name='%s'",m_strZakazchik);
			strZakazchikId = QueryResult(query);

			query.Format("select id from itak_producttols where product_tols=%s",m_strTolschina);
			strProductTolsId = QueryResult(query);

			query.Format("select id from itak_productmaterial where product_material='%s'",m_strMaterial);
			strProductMaterialId = QueryResult(query);

			query.Format("select id from itak_manager where manager_name='%s'",m_strManager);
			strManagerId = QueryResult(query);
		}

		/*mysql = mysql_init(NULL);
		if (mysql == NULL) 
		{
			MessageBox("Error: Ошибка инищиализации MySql!!!");
			return -1;
		}
			
		if (mysql_real_connect(mysql, m_strServerAddr, m_strMysqlLogin, m_strMysqlPass, "itak_etiketka", 3306, NULL, 0) == NULL) {
			MessageBox("Не можливо підключитись до бази данних");
			return -1;
		}
		mysql_query(mysql,"set names 'cp1251'" );*/

		

		

		GetSystemTime(&sysTimeStartWork);
		
		CString strDate,strDay,strMonth;

		if (sysDateStartWork.wDay<10)
			strDay.Format("0%d",sysDateStartWork.wDay);
		else strDay.Format("%d",sysDateStartWork.wDay);

		if (sysDateStartWork.wMonth<10)
			strMonth.Format("0%d",sysDateStartWork.wMonth);
		else strMonth.Format("%d",sysDateStartWork.wMonth);
		strDate.Format("%d-%s-%s",sysTimeStartWork.wYear,strMonth,strDay);

		CString h,m,s;
		CString strTimeStart;
		if (sysTimeStartWork.wHour+3<10)
			if (sysTimeStartWork.wHour+3>24)
				h.Format("0%d",sysTimeStartWork.wHour);
			else 
				h.Format("0%d",sysTimeStartWork.wHour+3);
		else
			if (sysTimeStartWork.wHour+3>24)
				h.Format("%d",sysTimeStartWork.wHour);
			else 
				h.Format("%d",sysTimeStartWork.wHour+3);
		
		
		if ((sysTimeStartWork.wHour+3)==24)
			h.Format("00");

		if (sysTimeStartWork.wMinute<10)
			m.Format("0%d",sysTimeStartWork.wMinute);
		else m.Format("%d",sysTimeStartWork.wMinute);

		if (sysTimeStartWork.wSecond<10)
			s.Format("0%d",sysTimeStartWork.wSecond);
		else s.Format("%d",sysTimeStartWork.wSecond);
		strTimeStart.Format("%s:%s:%s",h,m,s);

		query.Format("select count(id) from itak_zakaz where datezakaz='%s'",strDate);
		m_iNumZakaz = atoi(QueryResult(query));
		m_iNumZakaz++;
		

		query.Format("insert into itak_etiketka.dbo.itak_zakaz (zakazchik_id,producttols_id,partiya,"
			"dlinaetiketki,productmaterial_id,"
			"smena,machine,datezakaz,numzakaz,timestartzakaz, manager_id)"
			"values (%s,%s,'%s',%d,%s,%d,%d,'%s',%d,'%s',%s)",
			strZakazchikId,strProductTolsId,m_strPartiya,
			m_iDlinaEtiketki,strProductMaterialId,m_iNumSmena,m_iNumCar,strDate,m_iNumZakaz,strTimeStart, strManagerId);
		m_database.ExecuteSQL(query);
		
		/*if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);

			str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
			mysql_query(mysql,str);
		}*/

		m_iZakazId = atoi(QueryResult("select IDENT_CURRENT('itak_etiketka.dbo.itak_zakaz')"));
										
		
		

		/*query.Format("insert into itak_vhidrylon (zakaz_id,netto,brytto,dlina) values(%d,%.2f,%.2f,%d)", m_iZakazId,m_dVhidRylonNetto,m_dVhidRylonBrytto, m_iVhidRylonDlina);
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);

			str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
			mysql_query(mysql,str);
		}*/
		
// 		query.Format("insert into itak_zvit (zakaz_id,zakazchik_id,date) values (%d,%s,'%s')",m_iZakazId,strZakazchikId,strDate);
// 		if (mysql_query(mysql,query)!=0)  MessageBox("Ошибочный запрос!!!");

		/*query.Format("select id from itak_zakaz where zakazchik_id=%s and producttols_id=%s and partiya='%s' and "
			"productmaterial_id=%s and smena=%d and machine=%d and datezakaz='%s'",
			strZakazchikId,strProductTolsId,m_strPartiya,strProductMaterialId,m_iNumSmena,m_iNumCar,strDate);
		m_iZakazId = atoi(QueryResult(query));*/
		//OnBnClickedButtonEndZakaz();

		m_pmystatEndWidthProduct.SetFont(font_size);	
		m_pmystatEndWidthProduct.SetTextColor(BLUE_TEXT);
		m_pmystatEndCountRylonProduct.SetFont(font_size);	
		m_pmystatEndCountRylonProduct.SetTextColor(BLUE_TEXT);
		m_pmystatEndVesNettoProduct.SetFont(font_size);	
		m_pmystatEndVesNettoProduct.SetTextColor(BLUE_TEXT);
		m_pmystatEndVesBryttoProduct.SetFont(font_size);	
		m_pmystatEndVesBryttoProduct.SetTextColor(BLUE_TEXT);
		m_pmystatEndDlinaProduct.SetFont(font_size);	
		m_pmystatEndDlinaProduct.SetTextColor(BLUE_TEXT);
		m_myStatEndZagNetto.SetTextColor(BLUE_TEXT);
		m_myStatEndZagNetto.SetFont(font_size);
		m_myStatEndZagBrytto.SetTextColor(BLUE_TEXT);
		m_myStatEndZagBrytto.SetFont(font_size);
		m_myStatEndZagCountRylonov.SetTextColor(BLUE_TEXT);
		m_myStatEndZagCountRylonov.SetFont(font_size);		
		m_myStatEndZagDlinaRylonov.SetTextColor(BLUE_TEXT);
		m_myStatEndZagDlinaRylonov.SetFont(font_size);		
		m_pmystatEndCountEtiketki.SetTextColor(BLUE_TEXT);
		m_pmystatEndCountEtiketki.SetFont(font_size);		
		m_myStatEndZagCountEtiketok.SetTextColor(BLUE_TEXT);
		m_myStatEndZagCountEtiketok.SetFont(font_size);		
		m_myStatEndEndTimeZakaz.SetTextColor(BLUE_TEXT);
		m_myStatEndEndTimeZakaz.SetFont(font_size);		
		m_myStatEndStartTimeZakaz.SetTextColor(BLUE_TEXT);
		m_myStatEndStartTimeZakaz.SetFont(font_size);		
		m_myStatEndTimeZakaz.SetTextColor(BLUE_TEXT);
		m_myStatEndTimeZakaz.SetFont(font_size);		

		m_pmystatEndPrihodKG.SetTextColor(BLUE_TEXT);
		m_pmystatEndPrihodKG.SetFont(font_size);	
		m_pmystatEndZakazKG.SetTextColor(BLUE_TEXT);
		m_pmystatEndZakazKG.SetFont(font_size);	


		m_myStatVhidRyloniBrytto.SetTextColor(BLUE_TEXT);
		m_myStatVhidRyloniBrytto.SetFont(font_size);	
		m_myStatVhidRyloniNetto.SetTextColor(BLUE_TEXT);
		m_myStatVhidRyloniNetto.SetFont(font_size);
		m_myStatVhidRyloniDlina.SetTextColor(BLUE_TEXT);
		m_myStatVhidRyloniDlina.SetFont(font_size);
		//OnBnClickedButtonEndZakaz();

		m_vMyRecord.clear();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CWorkDialog::SetTolschina(CString tols)
{
	m_strTolschina = tols;
}
void CWorkDialog::SetZakazchik(CString zakazchik)
{
	m_strZakazchik = zakazchik;
	m_strZakazchik.Trim();
}
void CWorkDialog::SetCountProduct(int count)
{
	m_iCountProduct = count;
}
void CWorkDialog::SetDlinaRylona(int dlina)
{
	m_iDlinaRylona = dlina;
}

void CWorkDialog::SetCountEtiketki(int count)
{
	m_iCountEtiketki = count;
}

void CWorkDialog::SetData(SYSTEMTIME sysTime)
{
	sysDataEtiketka = sysDateStartWork = sysTime;
}


void CWorkDialog::SetPartiya(CString partiya)
{
	m_strPartiya = partiya;
}


void CWorkDialog::SetProduct(CString *name, int count)
{
	for (int i=0;i<count;i++)
		m_strProduct[i] = name[i];
}

void CWorkDialog::SetProductWidth(CString *width, int count)
{
	for (int i=0;i<count;i++)
		m_strProductWidth[i] = width[i];
}
void CWorkDialog::SetMaterial(CString material)
{
	m_strMaterial = material;
}

void CWorkDialog::SetManager(CString manager)
{
	m_strManager = manager;
}


void CWorkDialog::SetDlinaEtiketki(int dlina)
{
	m_iDlinaEtiketki = dlina;
}

void CWorkDialog::SetNumSmena(int smena)
{
	if (smena>0)
		m_iNumSmena = smena;
	else m_iNumSmena = 0;
}

void CWorkDialog::SetNumCar(int car)
{
	if (car>0)
		m_iNumCar = car;
	else m_iNumCar = 0;
}

void CWorkDialog::SetServerAddr(CString addr)
{
	m_strServerAddr = addr;
}

void CWorkDialog::SetMysqlLogin(CString login)
{
	m_strMysqlLogin = login;
}

void CWorkDialog::SetMysqlPass(CString pass)
{
	m_strMysqlPass = pass;
}

void CWorkDialog::SetCountDorojec(int *doroj, int count)
{
	if (count>0)
		for (int i=0;i<count;i++)
			m_iCountDorojec[i] = doroj[i];
}

void CWorkDialog::SetVagaTary(double *vaga, int count)
{
	if (count>0)
		for (int i=0;i<count;i++)
			m_dVagaTary[i] = vaga[i];
}


void CWorkDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}

HBRUSH CWorkDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor) 
	{
	case CTLCOLOR_EDIT:
		{
			pDC->SetTextColor(RGB( 255, 255,0));
			pDC->SetBkColor(RGB(255, 0, 0));
			return (HBRUSH)(m_pEditBkBrushActiv->GetSafeHandle());
		}
	default: return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	return hbr;	
}

void CWorkDialog::OnBnClickedButtonAdd()
{
	CString str;
	double dVes=0;

//	srand(time(0));
	dVes= rand()%50+1;////бруто получаем с весов
	//str.Format("%.2f",dVes);

	if (m_dTempVaga>1)
	{
		str.Format("%.2f",m_dTempVaga);
		m_peditVes[m_iNumList].SetWindowText(str);

		AddProduct();

		m_dTempVaga = 0;

		if (m_iCountDorojec[m_iNumList]==count)
		{
			if (m_iNumList==m_iCountProduct-1)
			{
				m_peditVes[m_iNumList].EnableWindow(FALSE);
				m_peditVes[0].EnableWindow(TRUE);
				m_peditVes[0].SetWindowText("");
				m_peditVes[0].SetFocus();
			}
			else
			{
				m_peditVes[m_iNumList].EnableWindow(FALSE);
				m_peditVes[m_iNumList+1].EnableWindow(TRUE);
				m_peditVes[m_iNumList+1].SetWindowText("");
				m_peditVes[m_iNumList+1].SetFocus();
			}
		}
		
		if (m_iCountDorojec[m_iNumList]==count)
		{
			if (m_iNumList==m_iCountProduct-1)
				m_iNumList=0;
			else m_iNumList++;
			count = 1;
		}else count++;
	}
}

void CWorkDialog::OnTimer(UINT_PTR nIDEvent)
{
	char buff[100];
	DWORD dwBytesRead = 0;	
	CString str;
	ReadFile(hFile, buff, 100, &dwBytesRead, NULL);
	if (dwBytesRead!=0)
	{
		str.Format("%s",buff);
		str = str.Left(str.Find("kg"));
		
		m_dTempVaga = strtod(str.GetBuffer(str.GetLength()),0);
		OnBnClickedButtonAdd();
	}

	CDialog::OnTimer(nIDEvent);
}

void CWorkDialog::AddProduct()
{
	LVITEM item;
	item.mask = LVIF_TEXT;
	CString str;
	double dVes=0;

	str.Format("%d",m_plistTabl[m_iNumList].GetItemCount()+1);
	m_plistTabl[m_iNumList].InsertItem(0,str);

	m_peditVes[m_iNumList].GetWindowText(str);
	if (str.Find(',')!=-1)
		str.Replace(',','.');

	m_dBrytto =  dVes = strtod(str.GetBuffer(str.GetLength()),0);

	str.Format("%.2f",dVes);
	item.iItem = 0;
	item.pszText = str.GetBuffer(str.GetLength());
	item.iSubItem = 1;
	m_plistTabl[m_iNumList].SetItem(&item);

	m_dObBrytto[m_iNumList]+=dVes;
	m_strObBrytto[m_iNumList].Format("%.2f кг",m_dObBrytto[m_iNumList]);
	m_pmyStatVesBrytto[m_iNumList].SetTextColor(BLUE_TEXT);
	m_pmyStatVesBrytto[m_iNumList].SetWindowText(m_strObBrytto[m_iNumList]);

	m_iZagRylonPorezCount++;
	m_iZagDlinaZakaza += m_iDlinaRylona;

	m_piCountEtiketok[m_iNumList]+=m_iCountEtiketki;
	m_iZagCountEtiketok+=m_iCountEtiketki;

	m_iDlinaPorezRylon[m_iNumList]+=m_iDlinaRylona;
	m_pmyStatDlina[m_iNumList].SetTextColor(BLUE_TEXT);
	str.Format("%d м",m_iDlinaPorezRylon[m_iNumList]);
	m_pmyStatDlina[m_iNumList].SetWindowText(str);
	
	if (m_iNumList==0 && m_iNumList!=m_iCountProduct-1)
		str.Format("%.2f кг",m_dVagaTary[m_iNumList+1]);
	else if (m_iNumList==m_iCountProduct-1)
		str.Format("%.2f кг",m_dVagaTary[0]);
	else if (m_iNumList!=0 && m_iNumList!=m_iCountProduct-1)
		str.Format("%.2f кг",m_dVagaTary[m_iNumList+1]);

	m_myStatVagaTary.SetWindowText(str);
	m_myStatVagaTary.SetTextColor(BLUE_TEXT);


// 	////zag brytto
	m_dZagBrytto+=dVes;
	/*str.Format("%.2f кг",m_dZagBrytto);
	m_myStatProductBrytto.SetTextColor(BLUE_TEXT);
	m_myStatProductBrytto.SetWindowText(str);*/

	///ntto
	m_dNetto = dVes-=m_dVagaTary[m_iNumList];
	str.Format("%.2f",dVes);
	item.pszText = str.GetBuffer(str.GetLength());
	item.iSubItem = 2;
	m_plistTabl[m_iNumList].SetItem(&item);

	////zag netto
	m_dZagNetto+=dVes;
	/*str.Format("%.2f кг",m_dZagNetto);
	m_myStatProductZagNetto.SetTextColor(BLUE_TEXT);
	m_myStatProductZagNetto.SetWindowText(str);	*/

	m_dObNetto[m_iNumList]+=dVes;
	m_strObNetto[m_iNumList].Format("%.2f кг",m_dObNetto[m_iNumList]);
	m_pmyStatVesNetto[m_iNumList].SetTextColor(BLUE_TEXT);
	m_pmyStatVesNetto[m_iNumList].SetWindowText(m_strObNetto[m_iNumList]);

	double width = 1;
	if (m_strProductWidth[m_iNumList]!="0")
		width = atof(m_strProductWidth[m_iNumList]);
	else width = 1;

	double dMxM=m_iDlinaRylona/(width/100);
	if (m_strZakazchik=="АО «JLC»")
	{
		str.Format("%.2f м2",dMxM);
		MessageBox(str);
	}

	//query.Format("select id from itak_product where product_name='%s'",m_strProduct[m_iNumList]);
	CString strProdNameId = ""; //QueryResult(query);

	
	CString strNumRylon;
	strNumRylon.Format("%d",m_plistTabl[m_iNumList].GetItemCount());

	if (!m_database.IsOpen())
	{
		m_database.Close();
		CString strConString = "Driver={SQL Server}; Server="+m_strServerAddr+"; Database=itak_etiketka; UID="+m_strMysqlLogin+"; PWD="+m_strMysqlPass+"";
		if (!m_database.OpenEx(strConString,CDatabase::noOdbcDialog))
		{
			MessageBox("Не возможно подключиться к Базе Данных. Обратитесь к администратору");
		}
		else
		{
			query.Format("select id from itak_product where product_name='%s'",m_strProduct[m_iNumList]);
			strProdNameId = QueryResult(query);

			query.Format("insert into itak_etiketka.dbo.itak_vihidrylon (zakaz_id,product_id,brytto,width,vagatary,koletiketki,dlinarylona,num_rylon, car, smena) values (%d,%s,%.2f,%s,%.2f,%d,%d,%s,%d,%d); ",
				m_iZakazId,strProdNameId,dVes+m_dVagaTary[m_iNumList],m_strProductWidth[m_iNumList],m_dVagaTary[m_iNumList],m_iCountEtiketki,m_iDlinaRylona,strNumRylon, m_iNumCar,m_iNumSmena);
			m_database.ExecuteSQL(query);

			m_iProductId = atoi(QueryResult("SELECT @@IDENTITY;"));
			int iPrID = atoi(QueryResult("select IDENT_CURRENT('itak_etiketka.dbo.itak_vihidrylon')"));
			int iSecondID = atoi(QueryResult("select max(id) from itak_etiketka.dbo.itak_vihidrylon"));

			if (m_iProductId==0 && iPrID!=0)
				m_iProductId =iPrID;

			if (m_iProductId==0 && iSecondID!=0)
				m_iProductId =iSecondID;

			if (m_iProductId==0)
			{
				m_iProductId = atoi(QueryResult("SELECT @@IDENTITY;"));
				iPrID = atoi(QueryResult("select IDENT_CURRENT('itak_etiketka.dbo.itak_vihidrylon')"));
				iSecondID = atoi(QueryResult("select max(id) from itak_etiketka.dbo.itak_vihidrylon"));

				if (m_iProductId==0 && iPrID!=0)
					m_iProductId =iPrID;

				if (m_iProductId==0 && iSecondID!=0)
					m_iProductId =iSecondID;
			}
		}

	}else
	{

		query.Format("select id from itak_product where product_name='%s'",m_strProduct[m_iNumList]);
		strProdNameId = QueryResult(query);

		//query.Format("insert into itak_etiketka.dbo.itak_vihidrylon (zakaz_id,product_id,brytto,width,vagatary,koletiketki,dlinarylona,num_rylon) values (%d,%s,%.2f,%s,%.2f,%d,%d,%s); ",
		//	m_iZakazId,strProdNameId,dVes+m_dVagaTary[m_iNumList],m_strProductWidth[m_iNumList],m_dVagaTary[m_iNumList],m_iCountEtiketki,m_iDlinaRylona,strNumRylon);
		query.Format("insert into itak_etiketka.dbo.itak_vihidrylon (zakaz_id,product_id,brytto,width,vagatary,koletiketki,dlinarylona,num_rylon, car, smena) values (%d,%s,%.2f,%s,%.2f,%d,%d,%s,%d,%d); ",
			m_iZakazId,strProdNameId,dVes+m_dVagaTary[m_iNumList],m_strProductWidth[m_iNumList],m_dVagaTary[m_iNumList],m_iCountEtiketki,m_iDlinaRylona,strNumRylon, m_iNumCar,m_iNumSmena);
		m_database.ExecuteSQL(query);
		
		m_iProductId = atoi(QueryResult("SELECT @@IDENTITY;"));
		int iPrID = atoi(QueryResult("select IDENT_CURRENT('itak_etiketka.dbo.itak_vihidrylon')"));
		int iSecondID = atoi(QueryResult("select max(id) from itak_etiketka.dbo.itak_vihidrylon"));

		if (m_iProductId==0 && iPrID!=0)
			m_iProductId =iPrID;

		if (m_iProductId==0 && iSecondID!=0)
			m_iProductId =iSecondID;

		if (m_iProductId==0)
		{
			m_iProductId = atoi(QueryResult("SELECT @@IDENTITY;"));
			iPrID = atoi(QueryResult("select IDENT_CURRENT('itak_etiketka.dbo.itak_vihidrylon')"));
			iSecondID = atoi(QueryResult("select max(id) from itak_etiketka.dbo.itak_vihidrylon"));

			if (m_iProductId==0 && iPrID!=0)
				m_iProductId =iPrID;

			if (m_iProductId==0 && iSecondID!=0)
				m_iProductId =iSecondID;
		}
	}

	MyRecord rec;
	rec.dBrutto = dVes+m_dVagaTary[m_iNumList];
	rec.iBarCode = m_iProductId;
	rec.iNumList = m_iNumList;
	rec.iListItem = m_plistTabl[m_iNumList].GetItemCount();

	m_vMyRecord.push_back(rec);

	//SYSTEMTIME t;
	//GetSystemTime(&t);


	CString strDlina, strKolEtiket, strSmena, strData,strMonth,strDay,
		strNetto, strBrytto;

	if (sysDataEtiketka.wMonth<10)
		strMonth.Format("0%d",sysDataEtiketka.wMonth);
	else strMonth.Format("%d",sysDataEtiketka.wMonth);

	if (sysDataEtiketka.wDay<10)
		strDay.Format("0%d",sysDataEtiketka.wDay);
	else strDay.Format("%d",sysDataEtiketka.wDay);
	strData.Format("%s.%s.%d",strDay,strMonth,sysDataEtiketka.wYear);

	if (m_strPrintEtiketka.GetLength()!=0)
	{
		CDC dlg;
		dlg.CreateDC (NULL, m_strPrintEtiketka, NULL, NULL);
		HDC hdcPrinter = dlg;

		//////////////////////////////////////////////////////////////////////////
		//barcode coord
		CString csCode;
		CString csStyle="Code39";
		COLORREF clrBar		=RGB(0,0,0);
		COLORREF clrSpace	=RGB(255,255,255);
		int iPenW=2;
		int iL,iT,iB;

		CRect rcT;
		rcT.left	=10;
		rcT.top		=410;
		rcT.bottom	=rcT.top+100;
		rcT.right=rcT.left+500;
		iL=rcT.left;
		iT=rcT.top;
		iB=rcT.bottom;
		//////////////////////////////////////////////////////////////////////////

		if (m_iNumPrintPage!=0)
		{
			if (hdcPrinter == NULL)
			{MessageBox(_T("Нет принтера!"));}
			else
			{
				dcPrinter.Attach(hdcPrinter);
				DOCINFO docinfo;
				memset(&docinfo, 0, sizeof(docinfo));
				docinfo.cbSize = sizeof(docinfo);
				docinfo.lpszDocName = _T("CDC::StartDoc() Code Fragment");

				for (int i=0;i<m_iNumPrintPage;i++)
				{
					if (dcPrinter.StartDoc(&docinfo) < 0)
						MessageBox(_T("Printer wouldn't initalize"));
					else 
					{
						if (dcPrinter.StartPage() < 0)
						{
							MessageBox(_T("Could not start page"));
							dcPrinter.AbortDoc();
						} 
						else 
						{
							CFont font;
							font.CreateFont(40,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Arial");
							dcPrinter.SelectObject(&font);

							strNetto.Format("%.2f",m_dNetto);
							strBrytto.Format("%.2f",m_dBrytto);

							strDlina.Format("%d",m_iDlinaRylona);
							strKolEtiket.Format("%d",m_iCountEtiketki);

							strSmena.Format("%d/%d",m_iNumCar,m_iNumSmena);

							//SYSTEMTIME t;
							//GetSystemTime(&t);

							if (sysDataEtiketka.wMonth<10)
								strMonth.Format("0%d",sysDataEtiketka.wMonth);
							else strMonth.Format("%d",sysDataEtiketka.wMonth);

							if (sysDataEtiketka.wDay<10)
								strDay.Format("0%d",sysDataEtiketka.wDay);
							else strDay.Format("%d",sysDataEtiketka.wDay);
							CString str;
							if (m_strMaterial==" ")
								str = m_strTolschina;
							else str.Format("%s %s",m_strMaterial,m_strTolschina);
							strData.Format("%s.%s.%d",strDay,strMonth,sysDataEtiketka.wYear);
							
							if (m_strZakazchik.Trim()=="АО \"БУКУРИЯ\" Г.КИШИНЕВ (МОЛДОВА)")
							{
								Print(&dcPrinter,m_strZakazchik, m_strProduct[m_iNumList],strNetto,strBrytto,strSmena,m_strPartiya,strData, m_strProductWidth[m_iNumList]);

								csCode.Format("3%d",m_iProductId);
								
								if(csStyle.CompareNoCase("Code39")==0)
								{
									
									Barcode39 code;
									code.Encode39(csCode);
									P_DrawBarcode(&dcPrinter,iL,iT,iB-5,iB,clrBar,clrSpace,iPenW,&code,csCode/*,strProductName,strDate*/);
								}
							}
							else if (m_strZakazchik=="ЗВЕНІГОРОДСЬКИЙ СИРКОМБІНАТ")
							{
								Print(&dcPrinter,m_strZakazchik,strNetto,strBrytto,strSmena,m_strPartiya,strData);
								csCode.Format("3%d",m_iProductId);

								if(csStyle.CompareNoCase("Code39")==0)
								{
									Barcode39 code;
									code.Encode39(csCode);
									P_DrawBarcode(&dcPrinter,iL,iT,iB-10,iB,clrBar,clrSpace,iPenW,&code,csCode/*,strProductName,strDate*/);
								}
							}

							else
							{
								Print(&dcPrinter,m_strZakazchik,m_strProduct[m_iNumList],str,
									m_strProductWidth[m_iNumList],strNumRylon,strNetto,strBrytto,
									strDlina,strKolEtiket,strSmena,m_strPartiya,strData);

								csCode.Format("3%d",m_iProductId);
								
								if(csStyle.CompareNoCase("Code39")==0)
								{
									Barcode39 code;
									code.Encode39(csCode);
									P_DrawBarcode(&dcPrinter,iL,iT,iB-10,iB,clrBar,clrSpace,iPenW,&code,csCode/*,strProductName,strDate*/);
								}
							}
							
							dcPrinter.EndPage();
							dcPrinter.EndDoc();
						}
					}
				}
				
				dcPrinter.Detach();
			}
		}
	}
}

CString CWorkDialog::QueryResult(CString query)
{
	if (m_pRecord->Open(CRecordset::snapshot,query))
	{
		int a = 0;
		m_pRecord->GetFieldValue(a,strData);
		strData = strData.Trim();
		m_pRecord->Close();
		return strData;
	}
	return "";
}

void CWorkDialog::Print (CDC *dc, CString strZakazchik,
						 CString strNetto, CString strBrytto,
						 CString strSmena, CString strPartiya, CString strData)//Звенигора
{
	CFont font;
	double b=0;
	int t = 10;
	int l = 10;
	int r = 430;
	int sdvig = 270;

	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Постачальник:");
	font.DeleteObject();

	font.CreateFont(40,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+190,t-8,"ТОВ \"ІТАК\"");
	font.DeleteObject();

	//zakazchik
	t+=35;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Замовник:");
	font.DeleteObject();

	font.CreateFont(27,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+130,t+2,"Звенігородський сирокомбінат");
	font.DeleteObject();
	///

	//material
	t+=35;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Матеріал:");
	font.DeleteObject();

	font.CreateFont(24,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+125,t+3,"пакувальний ламінований матеріал");
	font.DeleteObject();

	t+=20;
	font.CreateFont(24,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+100,t+3,"на основі паперу (WALKI Oy) глянцевий");
	font.DeleteObject();
	//
	
	//product
	t+=25;
	font.CreateFont(24,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+100,t,"75гр/м.кв*230 мм з малюнком");
	font.DeleteObject();
	///

	//ТУ
	t+=30;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+10,t,"ТУ У 22.1-16476839-001-2004");
	font.DeleteObject();
	//

	//нетто
	t+=35;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Масса нетто:");
	font.DeleteObject();

	font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+165,t+2,strNetto+" кг");
	font.DeleteObject();
	//

	//брутто
	t+=30;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Масса нетто:");
	font.DeleteObject();

	font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+165,t+2,strBrytto+" кг");
	font.DeleteObject();
	//

	//smena
	t+=30;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Зміна:");
	font.DeleteObject();

	font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+130,t+2,strSmena);
	font.DeleteObject();
	//

	//партія
	t+=30;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Партія:");
	font.DeleteObject();

	font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+130,t+2,strPartiya);
	font.DeleteObject();
	//

	//smena
	t+=30;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Дата виготовлення:");
	font.DeleteObject();

	font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+245,t+2,strData);
	font.DeleteObject();
	//

	t+=35;
	font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Гарантійний термін зберігання - 12 міс.");
	font.DeleteObject();
	
	t+=25;
	font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Для харчових продуктів");
	font.DeleteObject();


}


void CWorkDialog::Print (CDC *dc, CString strZakazchik,CString strTovar, CString strNetto, CString strBrytto,
						CString strSmena, CString strPartiya, CString strData, CString strWidth)//БУкурия
{
	CFont font;
	double b=0;
	int t = 10;
	int l = 30;
	int r = 430;
	int sdvig = 270;

	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Заказчик:");
	font.DeleteObject();

	font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	CString strZakazchik1 = strZakazchik.Left(strZakazchik.Find(".")-1);
	dc->TextOut(l+125,t,strZakazchik1);
	font.DeleteObject();
	t+=27;

	font.CreateFont(25,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	CString strZakazchik2 = strZakazchik.Mid(strZakazchik.Find(".")-1,strZakazchik.GetLength());
	dc->TextOut(l+125,t,strZakazchik2);
	font.DeleteObject();

	t+=30;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Продукция:");
	font.DeleteObject();

	font.CreateFont(25,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+145,t+5,"Фольга кашированная с");
	font.DeleteObject();

	t+=27;
	font.CreateFont(25,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+145,t,"рисунком для упаковки");
	font.DeleteObject();

	CString sTovar = strTovar.Left(1).MakeUpper() + strTovar.Mid(1).MakeLower();
	t+=27;
	font.CreateFont(25,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+145,t,"ириса \""+sTovar+"\"");
	font.DeleteObject();

	//ширина бобины
	t+=30;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Ширина бобины:");
	font.DeleteObject();

	//t+=3;
	font.CreateFont(25,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	//dc->TextOut(l+210,t+3,"50 мм");
	
	//dc->TextOut(l+210,t+3,"50 мм");
	dc->TextOut(l+210,t+3,strWidth);
	font.DeleteObject();
	//

	//брутто
	t+=30;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Вес брутто:");
	font.DeleteObject();

	font.CreateFont(25,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+150,t+3,strBrytto+" кг");
	font.DeleteObject();

	//

	//нетто
	t+=30;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Вес нетто:");
	font.DeleteObject();

	font.CreateFont(25,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+150,t+3,strNetto+" кг");
	font.DeleteObject();
	//

	//партия
	t+=30;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Партия:");
	font.DeleteObject();

	font.CreateFont(25,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+150,t+3,strPartiya);
	font.DeleteObject();
	//

	//упаковщик
	t+=30;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Упаковщик:");
	font.DeleteObject();

	font.CreateFont(25,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+160,t+3,strSmena);
	font.DeleteObject();
	//

	//Дата
	t+=30;
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,t,"Дата изготовления:");
	font.DeleteObject();

	font.CreateFont(25,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+240,t+3,strData);
	font.DeleteObject();
	//

	t+=40;
	font.CreateFont(20,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+10,t,"Срок годности - 12 месяцев со дня изготовления,");
	font.DeleteObject();

	t+=20;
	font.CreateFont(20,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+10,t,"согласно ТУ У 22.1-16476839-001-2004");
	font.DeleteObject();
	

}

void CWorkDialog::Print(CDC *dc, CString strZakazchik, CString strTovar, CString strMaterial,
						CString strWidth, CString strNumRylon, CString strNetto, CString strBrytto,
						CString strDlina, CString strKolEtik, CString strSmena, CString strPartiya,
						CString strData)
{
	CFont font;
	double b=0;
	int t = 0;
	int l = 0;
	int r = 430;
	int sdvig = 270;

	if (m_bLogo==true)
	{
		CString strTOVITAK = "ТОВ \"ІТАК\"";
		font.CreateFont(25,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
		dc->SelectObject(&font);
		b = int(((r-l)/2) - ((strTOVITAK.GetLength()/2)*10));
		dc->TextOut((int)b,t,strTOVITAK);
		font.DeleteObject();

		CString strAdress = "м.Київ, вул. Червоноткацька, 44";
		font.CreateFont(25,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
		dc->SelectObject(&font);
		b = (((r-l)/2)- ((strAdress.GetLength()/2)*9));
		dc->TextOut((int)b,(t+=20),strAdress);
		font.DeleteObject();
	}

	CString strEtiketkaDlyaPak = "Етикетка для пакування";
	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	b = (((r-l)/2)- ((strEtiketkaDlyaPak.GetLength()/2)*12));
	dc->TextOut((int)b,(t+=25),strEtiketkaDlyaPak);
	font.DeleteObject();


	font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	//b = (((r-l)/2)- ((strEtiketkaDlyaPak.GetLength()/2)*11));
	dc->TextOut(l,(t+=45),strZakazchik); // zakazchik
	font.DeleteObject();

	//////////////////////////////////////////////////////////////////////////
	if (strTovar.GetLength()<=10)
		font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	else if (strTovar.GetLength()<=20 && strTovar.GetLength()>10)
		font.CreateFont(25,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	else if (strTovar.GetLength()>20)
		font.CreateFont(20,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,(t+=30),strTovar);// naimenovanie
	font.DeleteObject();
	//////////////////////////////////////////////////////////////////////////
	if (m_bLogo==true)
	{
		font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
		dc->SelectObject(&font);
		dc->TextOut(l,(t+=30),"ТУ У 22.1-16476839-001-2004");// TY
	}
	dc->TextOut(l,(t+=30),"Партія");// naimenovanie
	font.DeleteObject();

	font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+80,t,"  "+strPartiya+"  "); // partiya podcherknyto
	font.DeleteObject();

	font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+sdvig,t,"Зміна");// smena
	font.DeleteObject();

	font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+sdvig+70,t,"  "+strSmena+"  "); // smena podcherknyto
	font.DeleteObject();

	font.CreateFont(25,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,(t+=35),strMaterial+ "x"+strWidth);// material
	font.DeleteObject();

	font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,(t+=30),strDlina+" м.п.");// dlina
	dc->TextOut(l+sdvig-20,t,strKolEtik+" шт.");// count etik


	//b = (((r-l)/2)- ((strData.GetLength()/2)*11));
	dc->TextOut(l,(t+=30),strData);

	dc->TextOut(l+sdvig-20,t,"№ рулона");// nomer rylona
	font.DeleteObject();
	font.CreateFont(30,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+sdvig+100,t,"  "+strNumRylon+"  "); // nomer rylona
	font.DeleteObject();

	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,(t+=30),"Маса нетто");
	font.DeleteObject();

	font.CreateFont(35,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+150,t,"     "+strNetto+"     "); // netto podcherknyto
	font.DeleteObject();

	font.CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l,(t+=40),"Маса брутто");
	font.DeleteObject();

	font.CreateFont(35,0,0,0,FW_NORMAL,FALSE,TRUE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	dc->TextOut(l+150,t,"     "+strBrytto+"     "); // brytto podcherknyto
	font.DeleteObject();

	CString strTermin = "Гарантійний термін зберігання - 12 міс.";
	font.CreateFont(25,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");
	dc->SelectObject(&font);
	b = (((r-l)/2)- ((strTermin.GetLength()/2)*10));
	dc->TextOut((int)b,(t+=40),strTermin);
	font.DeleteObject();


}

void CWorkDialog::OnDestroy()
{
	CDialog::OnDestroy();
}

void CWorkDialog::OnBnClickedButtonExit()
{
	CString str;
	m_peditEndObrezok.GetWindowText(str);
	if (str.GetLength()!=0)
	{
		m_peditEndOthod.GetWindowText(str);
		if (str.GetLength()!=0)
		{
			m_peditEndBrak.GetWindowText(str);
			if (str.GetLength()!=0)
			{
				m_peditEndBrakTP.GetWindowText(str);
				if (str.GetLength()!=0)
				{
					m_peditEndOstatok.GetWindowText(str);
					if (str.GetLength()!=0)
					{
						m_peditEndOstatokWidth.GetWindowText(str);
						if (str.GetLength()!=0)
						{
							m_peditEndNeDostatok.GetWindowText(str);
							if (str.GetLength()!=0)
							{
								regim = 3;
								WriteBD();
								OnOK();
							}
							else 
							{
								MessageBox("Введіть недостачу");
								m_peditEndOstatokWidth.SetFocus();
							}
						}
						else 
						{
							MessageBox("Введіть ширину залышку");
							m_peditEndOstatokWidth.SetFocus();
						}
					}
					else
					{
						MessageBox("Введіть вагу залишку");
						m_peditEndOstatok.SetFocus();
					}
				}
				else 
				{
					MessageBox("Введіть вагу брак друку");
					m_peditEndBrakTP.SetFocus();
				}
			}
			else 
			{
				MessageBox("Введіть вагу браку");
				m_peditEndBrak.SetFocus();
			}
		}
		else 
		{
			MessageBox("Введіть вагу відходу");
			m_peditEndOthod.SetFocus();
		}
	}
	else 
	{
		MessageBox("Введіть вагу обрізка");
		m_peditEndObrezok.SetFocus();
	}
}

void CWorkDialog::OnBnClickedButtonNewSmena()
{
	m_chooseRegim = new CChooseRegim2;
	m_chooseRegim->SetCar(m_iNumCar);
	m_chooseRegim->SetSmena(m_iNumSmena);

	if (m_chooseRegim->DoModal()==IDOK)
	{
		SetNumCar(m_chooseRegim->m_iNumberCar);
		SetNumSmena(m_chooseRegim->m_iNumberSmena);
		CString str;
		str.Format("%d/%d",m_iNumCar,m_iNumSmena);
		m_myStatSmena.SetTextColor(BLUE_TEXT);
		m_myStatSmena.SetWindowText(str);

		query.Format("update itak_zakaz set smena=%d, machine=%d where id=%d",m_iNumSmena,m_iNumCar,m_iZakazId);
		m_database.ExecuteSQL(query);
		/*if (mysql_query(mysql,query)!=0)  
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);
			str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
			mysql_query(mysql,str);
		}*/
	}
	delete m_chooseRegim;
}

void CWorkDialog::OnBnClickedButtonEndZakaz()
{

	if (m_boolButtonExit==FALSE)
	{
		GetDlgItem(15022)->ShowWindow(TRUE);
		GetDlgItem(1789)->ShowWindow(TRUE);
		m_boolButtonExit = TRUE;
	}

	if (m_iCountProduct>0)
	{
		for (int i=0;i<m_iCountProduct;i++)
			m_piCountRylon[i] = m_plistTabl[i].GetItemCount();
		
		for (int i=0;i<m_iCountProduct;i++)
		{
			m_pmyStatProductName[i].DestroyWindow();
			m_pstatWidth[i].DestroyWindow();
			m_pmyStatProductWidth[i].DestroyWindow();
			m_pstatCountDorojec[i].DestroyWindow();
			m_pmyStatCountDorojec[i].DestroyWindow();
			m_peditVes[i].DestroyWindow();
			m_plistTabl[i].DestroyWindow();
			m_pstatVesNetto[i].DestroyWindow();
			m_pstatVesBrytto[i].DestroyWindow();
			m_pmyStatVesNetto[i].DestroyWindow();
			m_pmyStatVesBrytto[i].DestroyWindow();
			m_pmyStatDlina[i].DestroyWindow();
			m_pstatDlina[i].DestroyWindow();

 			m_dObNetto[i] = 0;
 			m_dObBrytto[i] = 0;
		}
		m_dNetto = m_dBrytto = 0;
		m_butEndZakaz.ShowWindow(FALSE);
		m_butChangeZakaz.ShowWindow(FALSE);

		m_myStatDlinaRylona.ShowWindow(FALSE);
		m_statDlinaRylona.ShowWindow(FALSE);
		m_myStatCountEtiketok.ShowWindow(FALSE);
		m_statCountEtiketok.ShowWindow(FALSE);
		
		m_pmyStatProductName = 0;
		m_pstatWidth = 0;
		m_pmyStatProductWidth = 0;
		m_pstatCountDorojec = 0;
		m_pmyStatCountDorojec = 0;
		m_peditVes = 0;
		m_plistTabl = 0;
		m_pstatVesNetto = 0;
		m_pstatVesBrytto = 0;
		m_pmyStatVesNetto = 0;
		m_pmyStatVesBrytto = 0;
		m_pmyStatDlina = 0;
		m_pstatDlina = 0;

		m_vMyRecord.clear();

		delete m_pmyStatProductName;
		delete m_pstatWidth;
		delete m_pmyStatProductWidth;
		delete m_pstatCountDorojec;
		delete m_pmyStatCountDorojec;
		delete m_peditVes;
		delete m_plistTabl;
		delete m_pstatVesNetto;
		delete m_pstatVesBrytto;
		delete m_pmyStatVesNetto;
		delete m_pmyStatVesBrytto;
		delete m_pmyStatDlina;
		delete m_pstatDlina;

		m_boolNewZakaz = FALSE;
		m_boolEndZakaz = FALSE;
		m_butNewZakaz.ShowWindow(TRUE);
		
		CString str,strTimeStart,strTimeEnd,strTime;

		int x = m_rectClient.left+20;
		int y = m_rectClient.top+80;
		int width = 450;
		bool f = true;

		m_pstatEndBorder[0].CreateEx(WS_EX_CLIENTEDGE, "STATIC", NULL,	WS_CHILD | WS_TABSTOP | WS_VISIBLE,x, y, width, 220, m_hWnd, (HMENU)1234);	
		m_pstatEndBorder[1].CreateEx(WS_EX_CLIENTEDGE, "STATIC", NULL,	WS_CHILD | WS_TABSTOP | WS_VISIBLE,x, y+230, width, 235, m_hWnd, (HMENU)1234);	

		m_listEndProduct.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LBN_SELCANCEL|WS_VSCROLL,CRect(x+10,y+10,x+width-10,y+100),this,15110);
		for (int i=0;i<m_iCountProduct;i++)
			m_listEndProduct.InsertString(i,m_strProduct[i]);
		m_listEndProduct.SetCurSel(0);
		
		m_pstatEndWidthProduct.Create("Ширина:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+100,x+150,y+115),this,16010);
		m_pmystatEndWidthProduct.Create("0 мм",WS_VISIBLE|WS_CHILD,CRect(x+160,y+100,x+440,y+115),this,16060);

		m_pstatEndCountRylonProduct.Create("Кількість рулонів:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+120,x+150,y+135),this,16020);
		m_pmystatEndCountRylonProduct.Create("0 шт",WS_VISIBLE|WS_CHILD,CRect(x+160,y+120,x+440,y+135),this,16070);
	
		m_pstatEndVesNettoProduct.Create("Вага нетто:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+140,x+150,y+155),this,16030);
		m_pmystatEndVesNettoProduct.Create("0.00 кг",WS_VISIBLE|WS_CHILD,CRect(x+160,y+140,x+440,y+155),this,16080);

		m_pstatEndVesBryttoProduct.Create("Вага брутто:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+160,x+150,y+175),this,16040);
		m_pmystatEndVesBryttoProduct.Create("0.00 кг",WS_VISIBLE|WS_CHILD,CRect(x+160,y+160,x+440,y+175),this,16080);
		
		m_pstatEndDlinaProduct.Create("Довжина:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+180,x+150,y+195),this,16050);
		m_pmystatEndDlinaProduct.Create("0 м",WS_VISIBLE|WS_CHILD,CRect(x+160,y+180,x+440,y+195),this,16100);

		m_pstatEndCountEtiketki.Create("К-ть етикеток:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+200,x+150,y+215),this,16100);
		m_pmystatEndCountEtiketki.Create("0 шт",WS_VISIBLE|WS_CHILD,CRect(x+160,y+200,x+440,y+215),this,16100);

		OnLbnSelchangeEndListProduct();

		m_statEndZagNetto.Create("Вага нетто порізаных рулонів:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+240,x+300,y+260),this,16110);
		str.Format("%.2f кг",m_dZagNetto);
		m_myStatEndZagNetto.Create(str,WS_VISIBLE|WS_CHILD,CRect(x+300,y+240,x+490,y+255),this,16111);

		m_statEndZagBrytto.Create("Вага брутто порізаных рулонів:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+260,x+300,y+280),this,16120);
		str.Format("%.2f кг",m_dZagBrytto);
		m_myStatEndZagBrytto.Create(str,WS_VISIBLE|WS_CHILD,CRect(x+300,y+260,x+490,y+275),this,16112);

		m_statEndZagCountRylonov.Create("К-ть порізаних рулонів:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+280,x+300,y+300),this,16130);
		str.Format("%d шт",m_iZagRylonPorezCount);
		m_myStatEndZagCountRylonov.Create(str,WS_VISIBLE|WS_CHILD,CRect(x+300,y+280,x+490,y+295),this,16113);

		m_statEndZagDlinaRylonov.Create("Довжина порізаних рулонів:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+300,x+300,y+320),this,16140);
		str.Format("%d м",m_iZagDlinaZakaza);
		m_myStatEndZagDlinaRylonov.Create(str,WS_VISIBLE|WS_CHILD,CRect(x+300,y+300,x+width-10,y+315),this,16114);

		m_statEndZagCountEtiketok.Create("К-ть етикеток:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+320,x+200,y+335),this,16150);
		str.Format("%d шт",m_iZagCountEtiketok);
		m_myStatEndZagCountEtiketok.Create(str,WS_VISIBLE|WS_CHILD,CRect(x+300,y+320,x+490,y+335),this,16115);

		/*query.Format("select sum(koletiketki) from itak_vihidrylon where zakaz_id=%d",m_iZakazId);
		str.Format("%d шт",atoi(QueryResult(query)));
		m_myStatEndZagCountEtiketok.Create(str,WS_VISIBLE|WS_CHILD,CRect(x+300,y+320,x+490,y+335),this,16115);*/

		m_statVhidRyloniNetto.Create("Вага нетто вхідних рулонів:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+340,x+200,y+360),this,16180);
		str.Format("%.2f кг",m_dZagVhidRylonNetto);
		m_myStatVhidRyloniNetto.Create(str,WS_VISIBLE|WS_CHILD,CRect(x+300,y+340,x+width-10,y+360),this,16118);

		m_statVhidRyloniBrytto.Create("Вага брутто вхідних рулонів:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+360,x+300,y+380),this,16190);
		str.Format("%.2f кг",m_dZagVhidRylonBrytto);
		m_myStatVhidRyloniBrytto.Create(str,WS_VISIBLE|WS_CHILD,CRect(x+300,y+360,x+width-10,y+380),this,16119);

		m_statVhidRyloniDlina.Create("Довжина вхідних рулонів:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+380,x+300,y+400),this,16200);
		str.Format("%d м",m_iZagVhidRylonDlina);
		m_myStatVhidRyloniDlina.Create(str,WS_VISIBLE|WS_CHILD,CRect(x+300,y+380,x+width-10,y+400),this,16201);

  		m_statEndStartTimeZakaz.Create("Початок роботы:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+400,x+200,y+420),this,16150);
		CString h,m,s;
		/*if (sysTimeStartWork.wHour<10)
			h.Format("0%d",sysTimeStartWork.wHour+3);
		else h.Format("%d",sysTimeStartWork.wHour+3);*/


		if (sysTimeStartWork.wHour+3<10)
			if (sysTimeStartWork.wHour+3>24)
				h.Format("0%d",sysTimeStartWork.wHour);
			else 
				h.Format("0%d",sysTimeStartWork.wHour+3);
		else
			if (sysTimeStartWork.wHour+3>24)
				h.Format("%d",sysTimeStartWork.wHour);
			else 
				h.Format("%d",sysTimeStartWork.wHour+3);

		if ((sysTimeStartWork.wHour+3)==24)
			h.Format("00");
		if (sysTimeStartWork.wMinute<10)
			m.Format("0%d",sysTimeStartWork.wMinute);
		else m.Format("%d",sysTimeStartWork.wMinute);

		if (sysTimeStartWork.wSecond<10)
			s.Format("0%d",sysTimeStartWork.wSecond);
		else s.Format("%d",sysTimeStartWork.wSecond);
		strTimeStart.Format("%s:%s:%s",h,m,s);
		m_myStatEndStartTimeZakaz.Create(strTimeStart,WS_VISIBLE|WS_CHILD,CRect(x+300,y+400,x+width-10,y+420),this,16115);
 
		SYSTEMTIME sysTime;
		GetSystemTime(&sysTime);
		m_statEndEndTimeZakaz.Create("Кінець роботы:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+420,x+200,y+440),this,16160);
		
		

		/*if (sysTime.wHour<10)
			h.Format("0%d",sysTime.wHour+3);
		else h.Format("%d",sysTime.wHour+3);*/


		if (sysTime.wHour+3<10)
			if (sysTime.wHour+3>24)
				h.Format("0%d",sysTime.wHour);
			else 
				h.Format("0%d",sysTime.wHour+3);
		else
			if (sysTime.wHour+3>24)
				h.Format("%d",sysTime.wHour);
			else 
				h.Format("%d",sysTime.wHour+3);

		if ((sysTime.wHour+3)==24)
			h.Format("00");
		if (sysTime.wMinute<10)
			m.Format("0%d",sysTime.wMinute);
		else m.Format("%d",sysTime.wMinute);

		if (sysTime.wSecond<10)
			s.Format("0%d",sysTime.wSecond);
		else s.Format("%d",sysTime.wSecond);
		strTimeEnd.Format("%s:%s:%s",h,m,s);
		m_myStatEndEndTimeZakaz.Create(strTimeEnd,WS_VISIBLE|WS_CHILD,CRect(x+300,y+420,x+width-10,y+440),this,16116);

// 		int hh,mm,ss;
// 		hh = abs (sysTime.wHour - sysTimeStartWork.wHour);
// 		mm = abs(sysTime.wMinute - sysTimeStartWork.wMinute);
// 		ss = abs(sysTime.wSecond - sysTimeStartWork.wSecond);

		COleDateTime mt1;
		mt1.SetTime(sysTimeStartWork.wHour,sysTimeStartWork.wMinute,sysTimeStartWork.wSecond);
		COleDateTime mt2;
		mt2.SetTime(sysTime.wHour,sysTime.wMinute,sysTime.wSecond);
		mt1 =mt1 - mt2;

		int hourWork = mt1.GetHour();
		int minuteWork = mt1.GetMinute();
		int secondsWork = mt1.GetSecond();


// 		int startSec = sysTimeStartWork.wHour*3600 + sysTimeStartWork.wMinute*60+sysTimeStartWork.wSecond;
// 		int endSec = sysTime.wHour*3600 + sysTime.wMinute*60+sysTime.wSecond;
// 		int timeWork = abs (endSec - startSec);
// 		
// 		int hourWork = (int)timeWork/3600;
// 		int minuteWork = (int)((timeWork - (hourWork*3600))/60);
// 		int secondsWork = (int)(timeWork - (hourWork*3600) - (minuteWork*60));


		if (hourWork<10)
			h.Format("0%d",hourWork);
		else h.Format("%d",hourWork);

		
		if (hourWork>=24  )
			h.Format("00");
		if (minuteWork<10)
			m.Format("0%d",minuteWork);
		else m.Format("%d",minuteWork);

		if (secondsWork<10)
			s.Format("0%d",secondsWork);
		else s.Format("%d",secondsWork);
		strTime.Format("%s:%s:%s",h,m,s);

 		m_statEndTimeZakaz.Create("Час роботи:",WS_CHILD|WS_VISIBLE,CRect(x+10,y+440,x+200,y+460),this,16170);
		m_myStatEndTimeZakaz.Create(strTime,WS_VISIBLE|WS_CHILD,CRect(x+300,y+440,x+width-10,y+460),this,16117);

		int xx = x+width+20;
		m_pstatEndBorder[2].CreateEx(WS_EX_CLIENTEDGE, "STATIC", NULL,	WS_CHILD | WS_TABSTOP | WS_VISIBLE,xx, y, width, 195, m_hWnd, (HMENU)1234);	

		m_dOstattokKg = m_dZagVhidRylonNetto - m_dZagNetto;
 		m_pstatEndPrihodKG.Create("Прихід:",WS_CHILD|WS_VISIBLE,CRect(xx+10,y+10,xx+150,y+25),this,16180);
 		str.Format("%.2f кг",m_dZagVhidRylonNetto);
 		m_pmystatEndPrihodKG.Create(str,WS_VISIBLE|WS_CHILD,CRect(xx+150,y+10,xx+width,y+25),this,16118);

 		m_pstatEndZakazKG.Create("Замовлення:",WS_CHILD|WS_VISIBLE,CRect(xx+10,y+30,xx+150,y+50),this,16190);
 		str.Format("%.2f кг",m_dZagNetto);
 		m_pmystatEndZakazKG.Create(str,WS_VISIBLE|WS_CHILD,CRect(xx+150,y+30,xx+width,y+45),this,16119);

		m_pstatEndObrezok.Create("Обрізок (кг):",WS_CHILD|WS_VISIBLE,CRect(xx+10,y+50,xx+150,y+70),this,16200);
		m_peditEndObrezok.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP,CRect(xx+150,y+50,xx+250,y+65),this,16201);
		m_peditEndObrezok.SetLimitText(7);

		m_pstatEndOthod.Create("Отход (кг):",WS_CHILD|WS_VISIBLE,CRect(xx+10,y+70,xx+150,y+85),this,16210);
		m_peditEndOthod.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP,CRect(xx+150,y+70,xx+250,y+85),this,16211);
		m_peditEndOthod.SetLimitText(7);

		m_pstatEndBrak.Create("Брак (кг):",WS_CHILD|WS_VISIBLE,CRect(xx+10,y+90,xx+150,y+105),this,16230);
		m_peditEndBrak.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP,CRect(xx+150,y+90,xx+250,y+105),this,16231);
		m_peditEndBrak.SetLimitText(7);

		m_pstatEndBrakTP.Create("Брак ТП (кг):",WS_CHILD|WS_VISIBLE,CRect(xx+10,y+110,xx+150,y+125),this,16240);
		m_peditEndBrakTP.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP,CRect(xx+150,y+110,xx+250,y+125),this,16241);
		m_peditEndBrakTP.SetLimitText(7);

		m_pstatEndOstatok.Create("Остаток (кг):",WS_CHILD|WS_VISIBLE,CRect(xx+10,y+130,xx+150,y+150),this,16220);
		m_peditEndOstatok.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP,CRect(xx+150,y+130,xx+250,y+145),this,16221);
		str.Format("%.1f",m_dOstattokKg);
		m_peditEndOstatok.SetWindowText(str);
		m_peditEndOstatok.SetLimitText(7);

		m_statEndOstatokWidth.Create("Остаток (мм):",WS_CHILD|WS_VISIBLE,CRect(xx+10,y+150,xx+150,y+170),this,16300);
		m_peditEndOstatokWidth.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|ES_NUMBER|WS_TABSTOP,CRect(xx+150,y+150,xx+250,y+165),this,16301);
		m_peditEndOstatokWidth.SetLimitText(7);

		m_statEndNeDostatok.Create("Недостача (кг):",WS_CHILD|WS_VISIBLE,CRect(xx+10,y+170,xx+150,y+190),this,16310);
		m_peditEndNeDostatok.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP,CRect(xx+150,y+170,xx+250,y+185),this,16302);
		m_peditEndNeDostatok.SetLimitText(7);

		m_peditEndBrakTP.SetWindowText("0");
		m_peditEndBrak.SetWindowText("0");
		m_peditEndObrezok.SetWindowText("0");
		m_peditEndOthod.SetWindowText("0");
		m_peditEndOstatokWidth.SetWindowText("0");
		m_peditEndNeDostatok.SetWindowText("0");

		query.Format("update itak_zakaz set  timeendzakaz='%s', time='%s' where id=%d",strTimeEnd,strTime,m_iZakazId);
		m_database.ExecuteSQL(query);
		
		/*if (mysql_query(mysql,query)!=0)  
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);

			str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
			mysql_query(mysql,str);
		}*/


// 		query.Format("update itak_zakaz set vesnetto=%.2f, vesbrytto=%.2f, kolrylonov=%d where id=%d",m_dZagNetto,m_dZagBrytto,m_iZagRylonPorezCount,m_iZakazId);
// 		if (mysql_query(mysql,query)!=0)
// 		{
// 			CString str;
// 			str.Format("Ошибочный запрос!!! query='%s'",query);
// 			MessageBox(str);
// 		}

// 		query.Format("update itak_zakaz set vhidrylonnetto=%.2f, vhidrylonbrytto=%.2f, vhidrylondlina=%d where id=%d",m_dZagVhidRylonNetto,m_dZagVhidRylonBrytto,m_iZagVhidRylonDlina,m_iZakazId);
// 		if (mysql_query(mysql,query)!=0)  
// 		{
// 			CString str;
// 			str.Format("Ошибочный запрос!!! query='%s'",query);
// 			MessageBox(str);
// 		}
	}
}

void CWorkDialog::OnBnClickedButtonNewZakaz()
{
	CString str;
	m_peditEndObrezok.GetWindowText(str);
	if (str.GetLength()!=0)
	{
		m_peditEndOthod.GetWindowText(str);
		if (str.GetLength()!=0)
		{
			m_peditEndBrak.GetWindowText(str);
			if (str.GetLength()!=0)
			{
				m_peditEndBrakTP.GetWindowText(str);
				if (str.GetLength()!=0)
				{
					m_peditEndOstatok.GetWindowText(str);
					if (str.GetLength()!=0)
					{
						m_peditEndOstatokWidth.GetWindowText(str);
						if (str.GetLength()!=0)
						{
							m_peditEndNeDostatok.GetWindowText(str);
							if (str.GetLength()!=0)
							{
								WriteBD();
								if (m_boolButtonExit==TRUE)
								{
									GetDlgItem(15022)->ShowWindow(FALSE);
									GetDlgItem(1789)->ShowWindow(FALSE);
									m_boolButtonExit = FALSE;
								}
								m_chooseProduct = new CChooseProduct;
								m_chooseProduct->SetMysqlLogin(m_strMysqlLogin);
								m_chooseProduct->SetMysqlPass(m_strMysqlPass);
								m_chooseProduct->SetServerAddr(m_strServerAddr);
								m_chooseProduct->hide = 1;

								if (m_chooseProduct->DoModal()==IDOK && m_chooseProduct->regim==1)
								{
// 									query.Format("update itak_zakaz set vesnetto=%.2f, vesbrytto=%.2f, kolrylonov=%d where id=%d",m_dZagNetto,m_dZagBrytto,m_iZagRylonPorezCount,m_iZakazId);
// 									if (mysql_query(mysql,query)!=0) 
// 									{
// 										CString str;
// 										str.Format("Ошибочный запрос!!! query='%s'",query);
// 										MessageBox(str);
// 									}

									m_iOldCountProduct = m_iCountProduct;
									SetCountProduct(m_chooseProduct->m_iCountProduct);
									SetZakazchik(m_chooseProduct->m_strZakazchik);
									SetTolschina(m_chooseProduct->m_strTolschina);
									SetMaterial(m_chooseProduct->m_strMaterial);
									SetDlinaRylona(m_chooseProduct->m_iDlinaRylona);
									SetDlinaEtiketki(m_chooseProduct->m_iDlinaEtiketki);
									SetCountEtiketki(m_chooseProduct->m_iCountEtiketki);
//////////////////////////////////////////////////////////////////////////
									SetVagaTary(m_chooseProduct->m_dVagaTary,m_chooseProduct->m_iCountProduct);
//////////////////////////////////////////////////////////////////////////
									SetPartiya(m_chooseProduct->m_strPartiya);
									SetProduct(m_chooseProduct->m_strProduct,m_chooseProduct->m_iCountProduct);
									SetCountDorojec(m_chooseProduct->m_iCountDorojec,m_chooseProduct->m_iCountProduct);
									SetProductWidth(m_chooseProduct->m_strProductWidth,m_chooseProduct->m_iCountProduct);
									SetNumPrintPage(m_chooseProduct->m_iNumPrintPage);
									SetVhidRylonNetto(m_chooseProduct->m_dVhidRylonNetto);
									SetVhidRylonBrytto(m_chooseProduct->m_dVhidRylonBrytto);
									SetVhidRylonDlina(m_chooseProduct->m_iVhidRylonDlina);
									SetLogo(m_chooseProduct->m_bLogo);
									SetManager(m_chooseProduct->m_strManager);
									m_dZagVhidRylonNetto = m_dVhidRylonNetto;
									m_dZagVhidRylonBrytto = m_dVhidRylonBrytto;
									m_iZagVhidRylonDlina = m_iVhidRylonDlina;

									m_iNumList = 0;
									//m_iCountEtiketki = 0;
									for (int i=0;i<m_iOldCountProduct;i++)
									{
										m_dObNetto[i] = 0;
										m_dObBrytto[i] = 0;
										m_iDlinaPorezRylon[i] = 0;
										m_piCountEtiketok[i]=0;										
									}

									m_dZagNetto = 0;
									m_dZagBrytto = 0;
									m_iZagRylonPorezCount = 0;
									m_iZagCountEtiketok=0;
									m_iZagVhidRylonDlina=0;
									m_iZagDlinaZakaza = 0;
									
									m_vMyRecord.clear();

									if (m_boolEndZakaz==FALSE)
									{
										m_pstatEndBorder[0].DestroyWindow();
										m_pstatEndBorder[1].DestroyWindow();
										m_pstatEndBorder[2].DestroyWindow();
										m_listEndProduct.DestroyWindow();
										m_pstatEndWidthProduct.DestroyWindow();
										m_pmystatEndWidthProduct.DestroyWindow();
										m_pstatEndCountRylonProduct.DestroyWindow();
										m_pmystatEndCountRylonProduct.DestroyWindow();
										m_pstatEndVesNettoProduct.DestroyWindow();
										m_pmystatEndVesNettoProduct.DestroyWindow();
										m_pstatEndVesBryttoProduct.DestroyWindow();
										m_pmystatEndVesBryttoProduct.DestroyWindow();
										m_pstatEndDlinaProduct.DestroyWindow();
										m_pmystatEndDlinaProduct.DestroyWindow();
										m_pmystatEndCountEtiketki.DestroyWindow();
										m_pstatEndCountEtiketki.DestroyWindow();
										m_statEndZagNetto.DestroyWindow();
										m_statEndZagBrytto.DestroyWindow();
										m_statEndZagCountRylonov.DestroyWindow();
										m_statEndZagDlinaRylonov.DestroyWindow();
										m_statEndStartTimeZakaz.DestroyWindow();
										m_statEndEndTimeZakaz.DestroyWindow();
										m_statEndTimeZakaz.DestroyWindow();
										m_myStatEndStartTimeZakaz.DestroyWindow();
										m_myStatEndEndTimeZakaz.DestroyWindow();
										m_myStatEndTimeZakaz.DestroyWindow();
										m_myStatEndZagCountEtiketok.DestroyWindow();
										m_statEndZagCountEtiketok.DestroyWindow();
										m_myStatEndZagNetto.DestroyWindow();
										m_myStatEndZagBrytto.DestroyWindow();
										m_myStatEndZagCountRylonov.DestroyWindow();
										m_myStatEndZagDlinaRylonov.DestroyWindow();

										m_pstatEndPrihodKG.DestroyWindow();
										m_pmystatEndPrihodKG.DestroyWindow();
										m_pstatEndZakazKG.DestroyWindow();
										m_pmystatEndZakazKG.DestroyWindow();

										m_pstatEndObrezok.DestroyWindow();
										m_pstatEndOthod.DestroyWindow();
										m_pstatEndOstatok.DestroyWindow();
										m_pstatEndBrak.DestroyWindow();
										m_pstatEndBrakTP.DestroyWindow();

										m_peditEndObrezok.DestroyWindow();
										m_peditEndOthod.DestroyWindow();
										m_peditEndOstatok.DestroyWindow();
										m_peditEndBrak.DestroyWindow();
										m_peditEndBrakTP.DestroyWindow();
										m_peditEndOstatokWidth.DestroyWindow();
										m_peditEndNeDostatok.DestroyWindow();

										m_myStatVhidRyloniDlina.DestroyWindow();
										m_myStatVhidRyloniNetto.DestroyWindow();
										m_myStatVhidRyloniBrytto.DestroyWindow();
										m_statVhidRyloniNetto.DestroyWindow();
										m_statVhidRyloniBrytto.DestroyWindow();
										m_statVhidRyloniDlina.DestroyWindow();
										m_statEndOstatokWidth.DestroyWindow();	
										m_statEndNeDostatok.DestroyWindow();
									}			

									m_bNewZakazId = TRUE;
									Initilisation();

									m_myStatDlinaRylona.ShowWindow(TRUE);
									m_statDlinaRylona.ShowWindow(TRUE);
									m_myStatCountEtiketok.ShowWindow(TRUE);
									m_statCountEtiketok.ShowWindow(TRUE);
									m_butEndZakaz.ShowWindow(TRUE);
									m_butNewZakaz.ShowWindow(FALSE);
									m_butChangeZakaz.ShowWindow(TRUE);
								}
								else 
								{
									if (m_boolButtonExit==FALSE)
									{
										GetDlgItem(15022)->ShowWindow(TRUE);
										GetDlgItem(1789)->ShowWindow(TRUE);
										m_boolButtonExit = TRUE;
									}
								}
								delete m_chooseProduct;
							}
							else 
							{
								MessageBox("Введіть недостачу");
								m_peditEndNeDostatok.SetFocus();
							}
						}							
						else 
						{
							MessageBox("Введіть ширину залишку");
							m_peditEndOstatokWidth.SetFocus();
						}
					}
					else
					{
						MessageBox("Введіть вагу залишку");
						m_peditEndOstatok.SetFocus();
					}
				}
				else 
				{
					MessageBox("Введіть вагу брак друку");
					m_peditEndBrakTP.SetFocus();
				}
			}
			else 
			{
				MessageBox("Введіть вагу браку");
				m_peditEndBrak.SetFocus();
			}
		}
		else 
		{
			MessageBox("Введіть вагу відходу");
			m_peditEndOthod.SetFocus();
		}
	}
	else 
	{
		MessageBox("Введіть вагу обрізка");
		m_peditEndObrezok.SetFocus();
	}
}

void CWorkDialog::Initilisation()
{
	CString str;
	m_myStatZakazchik.SetTextColor(BLUE_TEXT);
	m_myStatZakazchik.SetWindowText(m_strZakazchik);

	m_myStatTolschina.SetTextColor(BLUE_TEXT);
	m_myStatTolschina.SetWindowText(m_strTolschina+" мкм");

	m_myStatVagaTary.SetTextColor(BLUE_TEXT);
	str.Format("%.2f кг",m_dVagaTary[m_iNumList]);
	m_myStatVagaTary.SetWindowText(str);

	m_myStatPartiya.SetTextColor(BLUE_TEXT);
	m_myStatPartiya.SetWindowText(m_strPartiya);

	m_myStatDlinaRylona.SetTextColor(BLUE_TEXT);
	str.Format("%d м",m_iDlinaRylona);
	m_myStatDlinaRylona.SetWindowText(str);
	
	m_myStatDlinaEtiketki.SetTextColor(BLUE_TEXT);
	str.Format("%d мм",m_iDlinaEtiketki);
	m_myStatDlinaEtiketki.SetWindowText(str);

	m_myStatCountEtiketok.SetTextColor(BLUE_TEXT);
	str.Format("%d шт",m_iCountEtiketki);
	m_myStatCountEtiketok.SetWindowText(str);

	m_myStatMaterial.SetTextColor(BLUE_TEXT);
	m_myStatMaterial.SetWindowText(m_strMaterial);

	/*m_myStatRylonPorezCount.SetTextColor(BLUE_TEXT);
	str.Format("%d шт",m_iZagRylonPorezCount);
	m_myStatRylonPorezCount.SetWindowText(str);

	m_myStatProductZagNetto.SetTextColor(BLUE_TEXT);
	str.Format("%.2f кг",m_dZagNetto);
	m_myStatProductZagNetto.SetWindowText(str);

	m_myStatProductBrytto.SetTextColor(BLUE_TEXT);
	str.Format("%.2f кг",m_dZagBrytto);
	m_myStatProductBrytto.SetWindowText(str);*/

	if (m_iCountProduct>0)
	{
		if (m_boolNewZakaz==TRUE)
		{
			for (int i=0;i<m_iOldCountProduct;i++)
			{
				m_pmyStatProductName[i].DestroyWindow();
				m_pstatWidth[i].DestroyWindow();
				m_pmyStatProductWidth[i].DestroyWindow();
				m_pstatCountDorojec[i].DestroyWindow();
				m_pmyStatCountDorojec[i].DestroyWindow();
				m_peditVes[i].DestroyWindow();
				m_plistTabl[i].DestroyWindow();
				m_pstatVesNetto[i].DestroyWindow();
				m_pstatVesBrytto[i].DestroyWindow();
				m_pmyStatVesNetto[i].DestroyWindow();
				m_pmyStatVesBrytto[i].DestroyWindow();
				m_pmyStatDlina[i].DestroyWindow();
				m_pstatDlina[i].DestroyWindow();
			}
			m_dNetto = m_dBrytto = 0;
					
			m_pmyStatProductName = 0;
			m_pstatWidth = 0;
			m_pmyStatProductWidth = 0;
			m_pstatCountDorojec = 0;
			m_pmyStatCountDorojec = 0;
			m_peditVes = 0;
			m_plistTabl = 0;
			m_pstatVesNetto = 0;
			m_pstatVesBrytto = 0;
			m_pmyStatVesNetto = 0;
			m_pmyStatVesBrytto = 0;
			m_pmyStatDlina = 0;
			m_pstatDlina = 0;

			m_vMyRecord.clear();

			delete m_pmyStatProductName;
			delete m_pstatWidth;
			delete m_pmyStatProductWidth;
			delete m_pstatCountDorojec;
			delete m_pmyStatCountDorojec;
			delete m_peditVes;
			delete m_plistTabl;
			delete m_pstatVesNetto;
			delete m_pstatVesBrytto;
			delete m_pmyStatVesNetto;
			delete m_pmyStatVesBrytto;
			delete m_pmyStatDlina;
			delete m_pstatDlina;

			m_boolNewZakaz = TRUE;
		}
	
		m_pmyStatProductName = new CMyStatic[m_iCountProduct];
		m_pstatWidth = new CStatic [m_iCountProduct];
		m_pmyStatProductWidth = new CMyStatic[m_iCountProduct];

		m_pstatCountDorojec = new CStatic [m_iCountProduct];
		m_pmyStatCountDorojec = new CMyStatic[m_iCountProduct];

		m_peditVes = new CEdit[m_iCountProduct];
		m_plistTabl = new CMyListCtrl [m_iCountProduct];

		m_pstatVesNetto = new CStatic [m_iCountProduct];
		m_pstatVesBrytto = new CStatic [m_iCountProduct];
		m_pmyStatVesNetto = new CMyStatic[m_iCountProduct];
		m_pmyStatVesBrytto = new CMyStatic[m_iCountProduct];

		m_pstatDlina = new CStatic[m_iCountProduct];
		m_pmyStatDlina = new CMyStatic[m_iCountProduct];

		int left = m_rectClient.left+20;
		int width = 100;
		int left_colomn[10];
		int rastoyanie = 50;

		width = ((m_rectClient.right-40) / m_iCountProduct) ;
		int bby = bby = m_rectClient.bottom -170;
		if (m_iCountProduct!=1)
		{
			if (m_iCountProduct<=5)
			{
				width = ((m_rectClient.right-40) / m_iCountProduct) - 50;
				rastoyanie = ((m_rectClient.right - 40) -(m_iCountProduct*width))/ (m_iCountProduct-1);
			}
			else 
			{
				width = ((m_rectClient.right-40) / 5) - 50;
				rastoyanie = ((m_rectClient.right - 40) -(5*width))/ 4;
			}
		}
		int by = 0 ;
		int ty = 0;
		int height = 0;
		int columnCounter=0;
		int ras=100;
		for (int i=0;i<m_iCountProduct;i++)
		{
			if (i<5)
			{
				if (i==0)
					left_colomn[columnCounter] = left;
				else left_colomn[columnCounter] = left_colomn[i-1]+width+rastoyanie;

				height = (((m_rectClient.bottom)-170)/2)-80;
				ty = 70;
				by = ty+height;
			}
			else 
			{
				height = (((m_rectClient.bottom)-170)/2)-80;
				ty = 70+ras+height;
				by = ty+height;
			}

			if (m_iCountProduct<=5)
				by = bby;

			m_pmyStatProductName[i].SetTextColor(BLUE_TEXT); 
			m_pmyStatProductName[i].SetFont(font_size);
			m_pmyStatProductName[i].Create(m_strProduct[i],WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter],ty,left_colomn[columnCounter]+width,ty+20),this,15020+i);
			m_pstatWidth[i].Create("Ширина:",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter],ty+20,left_colomn[columnCounter]+60,ty+40),this,15030+i);

			m_pmyStatProductWidth[i].SetTextColor(BLUE_TEXT); 
			m_pmyStatProductWidth[i].SetFont(font_size);
			m_pmyStatProductWidth[i].Create(m_strProductWidth[i]+ " мм",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+70,ty+20,left_colomn[columnCounter]+width,ty+50),this,15040+i);

			m_pstatCountDorojec[i].Create("К-ть доріжок:",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter],ty+40,left_colomn[columnCounter]+90,ty+60),this,15050+i);
			m_pmyStatCountDorojec[i].SetTextColor(BLUE_TEXT); 
			m_pmyStatCountDorojec[i].SetFont(font_size);
			if (m_iCountDorojec[i]==-1)
				m_iCountDorojec[i]=1;
			str.Format("%d шт",m_iCountDorojec[i]);
			m_pmyStatCountDorojec[i].Create(str,WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+95,ty+40,left_colomn[columnCounter]+width,ty+60),this,15060+i);

			m_peditVes[i].Create(WS_VISIBLE|WS_CHILD|WS_BORDER|WS_EX_DLGMODALFRAME|WS_DISABLED|WS_TABSTOP,CRect(left_colomn[columnCounter],ty+60,left_colomn[columnCounter]+width,ty+80),this,15070+i);

			m_plistTabl[i].Create(WS_VISIBLE|WS_CHILD|WS_BORDER|LVS_REPORT|LVS_OWNERDRAWFIXED,CRect(left_colomn[columnCounter],ty+85,left_colomn[columnCounter]+width,by),this,15080+i);
			m_plistTabl[i].SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
			CRect columnRect;
			m_plistTabl[i].GetClientRect(&columnRect);
			int col = ((columnRect.right-30)/2)-7;			
			m_plistTabl[i].InsertColumn(0,"№",LVCFMT_LEFT,30);
			m_plistTabl[i].InsertColumn(1,"Брутто",LVCFMT_LEFT,col);
			m_plistTabl[i].InsertColumn(2,"Нетто",LVCFMT_LEFT,col);

			//////////////////////////////////////////////////////////////////////////
			m_pstatVesNetto[i].Create("Нетто:",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+5,by+5,left_colomn[columnCounter]+50,by+20),this,15090+i);
			m_pstatVesBrytto[i].Create("Брутто:",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+5,by+25,left_colomn[columnCounter]+55,by+40),this,15090+i);
			m_pstatDlina[i].Create("Довжина:",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+5,by+45,left_colomn[columnCounter]+70,by+60),this,15090+i);

			m_pmyStatVesNetto[i].SetFont(font_size);
			m_pmyStatVesNetto[i].SetTextColor(BLUE_TEXT);

			m_strObNetto[i].Format("%.2f",m_dObNetto[i]);
			m_pmyStatVesNetto[i].Create(m_strObNetto[i]+" кг",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+60,by+5,left_colomn[columnCounter]+width,by+20),this,16100+i);
			m_pmyStatVesBrytto[i].SetFont(font_size);
			m_pmyStatVesBrytto[i].SetTextColor(BLUE_TEXT);
			m_strObBrytto[i].Format("%.2f",m_dObBrytto[i]);
			m_pmyStatVesBrytto[i].Create(m_strObBrytto[i]+" кг",WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+70,by+25,left_colomn[columnCounter]+width,by+40),this,16110+i);
			//////////////////////////////////////////////////////////////////////////

			m_pmyStatDlina[i].SetFont(font_size);
			m_pmyStatDlina[i].SetTextColor(BLUE_TEXT);
			str.Format("%d м",m_iDlinaPorezRylon[i]);
			m_pmyStatDlina[i].Create(str,WS_CHILD|WS_VISIBLE,CRect(left_colomn[columnCounter]+90,by+45,left_colomn[columnCounter]+width,by+60),this,16110+i);

			columnCounter++;
			if (i==4)
				columnCounter=0;
		}

		m_peditVes[m_iNumList].EnableWindow(TRUE);
		m_peditVes[m_iNumList].SetWindowText("");
		m_peditVes[m_iNumList].SetFocus();

		query.Format("select id from itak_zakazchik where zakazchik_name='%s'",m_strZakazchik);
		strZakazchikId = QueryResult(query);

		query.Format("select id from itak_producttols where product_tols=%s",m_strTolschina);
		strProductTolsId = QueryResult(query);

		query.Format("select id from itak_productmaterial where product_material='%s'",m_strMaterial);
		strProductMaterialId = QueryResult(query);

		query.Format("select id from itak_manager where manager_name='%s'",m_strManager);
		strManagerId = QueryResult(query);

		GetSystemTime(&sysTimeStartWork);
		CString strDate,strDay,strMonth;
		if (sysTimeStartWork.wDay<10)
			strDay.Format("0%d",sysTimeStartWork.wDay);
		else strDay.Format("%d",sysTimeStartWork.wDay);

		if (sysTimeStartWork.wMonth<10)
			strMonth.Format("0%d",sysTimeStartWork.wMonth);
		else strMonth.Format("%d",sysTimeStartWork.wMonth);
		strDate.Format("%d-%s-%s",sysTimeStartWork.wYear,strMonth,strDay);

		query.Format("select count(id) from itak_zakaz where datezakaz='%s'",strDate);
		m_iNumZakaz = atoi(QueryResult(query));
		m_iNumZakaz++;

		CString h,m,s;
		CString strTimeStart;
	/*	if (sysTimeStartWork.wHour+3<10)
			h.Format("0%d",sysTimeStartWork.wHour+3);
		else h.Format("%d",sysTimeStartWork.wHour+3);*/

		if (sysTimeStartWork.wHour+3<10)
			if (sysTimeStartWork.wHour+3>24)
				h.Format("0%d",sysTimeStartWork.wHour);
			else 
				h.Format("0%d",sysTimeStartWork.wHour+3);
		else
			if (sysTimeStartWork.wHour+3>24)
				h.Format("%d",sysTimeStartWork.wHour);
			else 
				h.Format("%d",sysTimeStartWork.wHour+3);


		if ((sysTimeStartWork.wHour+3)==24)
			h.Format("00");
		if (sysTimeStartWork.wMinute<10)
			m.Format("0%d",sysTimeStartWork.wMinute);
		else m.Format("%d",sysTimeStartWork.wMinute);

		if (sysTimeStartWork.wSecond<10)
			s.Format("0%d",sysTimeStartWork.wSecond);
		else s.Format("%d",sysTimeStartWork.wSecond);
		strTimeStart.Format("%s:%s:%s",h,m,s);
		
		if (m_bNewZakazId==TRUE)
		{
			/*query.Format("insert into itak_zakaz (zakazchik_id,producttols_id,partiya,"
				"dlinaetiketki,productmaterial_id,"
				"smena,machine,datezakaz,numzakaz,timestartzakaz)"
				"values (%s,%s,'%s',%d,%s,%d,%d,'%s',%d,'%s')",
				strZakazchikId,strProductTolsId,m_strPartiya,
				m_iDlinaEtiketki,strProductMaterialId,m_iNumSmena,m_iNumCar,strDate,m_iNumZakaz,strTimeStart);
				if (mysql_query(mysql,query)!=0)  
				{
					CString str;
					str.Format("Ошибочный запрос!!! query='%s'",query);
					MessageBox(str);
					str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
					mysql_query(mysql,str);
				}
				m_iZakazId = (int)mysql_insert_id(mysql);*/

			query.Format("insert into itak_etiketka.dbo.itak_zakaz (zakazchik_id,producttols_id,partiya,"
			"dlinaetiketki,productmaterial_id,"
			"smena,machine,datezakaz,numzakaz,timestartzakaz,manager_id)"
			"values (%s,%s,'%s',%d,%s,%d,%d,'%s',%d,'%s',%s)",
			strZakazchikId,strProductTolsId,m_strPartiya,
			m_iDlinaEtiketki,strProductMaterialId,m_iNumSmena,m_iNumCar,strDate,m_iNumZakaz,strTimeStart,strManagerId);
			m_database.ExecuteSQL(query);
			m_iZakazId = atoi(QueryResult("select IDENT_CURRENT('itak_etiketka.dbo.itak_zakaz')"));

				/*query.Format("insert into itak_vhidrylon (zakaz_id,netto,brytto,dlina) values(%d,%.2f,%.2f,%d)", m_iZakazId,m_dVhidRylonNetto,m_dVhidRylonBrytto, m_iVhidRylonDlina);
				if (mysql_query(mysql,query)!=0) 
				{
					CString str;
					str.Format("Ошибочный запрос!!! query='%s'",query);
					MessageBox(str);
					str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
					mysql_query(mysql,str);
				}*/
				m_bNewZakazId = FALSE;
		}
		else 
		{
			query.Format("update itak_zakaz set zakazchik_id=%s,producttols_id=%s,partiya='%s',"
				"dlinaetiketki=%d,productmaterial_id=%s,"
				"smena=%d, machine=%d, manager_id=%s where id=%d",
				strZakazchikId,strProductTolsId,m_strPartiya,
				m_iDlinaEtiketki,strProductMaterialId,m_iNumSmena,m_iNumCar,strManagerId,m_iZakazId);
			m_database.ExecuteSQL(query);
				/*if (mysql_query(mysql,query)!=0)  
				{
					CString str;
					str.Format("Ошибочный запрос!!! query='%s'",query);
					MessageBox(str);
					str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
					mysql_query(mysql,str);
				}*/

				/*query.Format("update itak_vhidrylon set netto=%.2f, brytto=%.2f, dlina=%d where zakaz_id=%d", m_dVhidRylonNetto,m_dVhidRylonBrytto, m_iVhidRylonDlina,m_iZakazId);
				if (mysql_query(mysql,query)!=0) 
				{
					CString str;
					str.Format("Ошибочный запрос!!! query='%s'",query);
					MessageBox(str);
					str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
					mysql_query(mysql,str);
				}*/
		}	
	}
}
BOOL CWorkDialog::PreTranslateMessage(MSG* pMsg)
{
	if ( TranslateAccelerator( m_hWnd, m_hAccel, pMsg ) ) return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CWorkDialog::OnAccelChangeDlina()
{
	m_changeDlina = new CChangeDlina;
	m_changeDlina->SetDlina(m_iDlinaRylona);
	m_changeDlina->SetCountEtiketok(m_iCountEtiketki,m_iDlinaEtiketki);
	if (m_changeDlina->DoModal())
	{
		m_iDlinaRylona = m_changeDlina->m_iDlinaRylona;
		m_iCountEtiketki = m_changeDlina->m_iCountEtiketok;
		CString str;
		str.Format("%d м",m_iDlinaRylona);
		m_myStatDlinaRylona.SetTextColor(BLUE_TEXT);
		m_myStatDlinaRylona.SetWindowText(str);
	
		str.Format("%d шт",m_iCountEtiketki);
		m_myStatCountEtiketok.SetTextColor(BLUE_TEXT);
		m_myStatCountEtiketok.SetWindowText(str);
	}
	delete m_changeDlina;
}


void CWorkDialog::OnAccelNewRylon()
{
	/*m_newVhidRylon = new CNewVhidRylon;

	m_newVhidRylon->SetVhidDlinaRylona(m_iVhidRylonDlina);
	m_newVhidRylon->SetVhidNettoRylona(m_dVhidRylonNetto);
	m_newVhidRylon->SetVhidBryttoRylona(m_dVhidRylonBrytto);
	if (m_newVhidRylon->DoModal()==IDOK)
	{
		m_iVhidRylonDlina = m_newVhidRylon->m_iVhidDlinaRylona;
		m_dVhidRylonNetto = m_newVhidRylon->m_dVhidNetto;
		m_dVhidRylonBrytto = m_newVhidRylon->m_dVhidBrytto;

		m_dZagVhidRylonBrytto+=m_dVhidRylonBrytto;
		m_dZagVhidRylonNetto+=m_dVhidRylonNetto;
		m_iZagVhidRylonDlina+=m_iVhidRylonDlina;

// 		query.Format("update itak_zakaz set vhidrylonnetto=%.2f, vhidrylonbrytto=%.2f, vhidrylondlina=%d where id=%d",m_dZagVhidRylonNetto,m_dZagVhidRylonBrytto,m_iZagVhidRylonDlina,m_iZakazId);
// 		if (mysql_query(mysql,query)!=0)  
// 		{
// 			CString str;
// 			str.Format("Ошибочный запрос!!! query='%s'",query);
// 			MessageBox(str);
// 		}
		query.Format("insert into itak_vhidrylon (zakaz_id,netto,brytto,dlina) values(%d,%.2f,%.2f,%d)", m_iZakazId,m_dVhidRylonNetto,m_dVhidRylonBrytto, m_iVhidRylonDlina);
		if (mysql_query(mysql,query)!=0) 
		{
			CString str;
			str.Format("Ошибочный запрос!!! query='%s'",query);
			MessageBox(str);

			str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
			mysql_query(mysql,str);
		}
	}

	delete m_newVhidRylon;*/
}

void CWorkDialog::OnBnClickedButtonChangeZakaz()
{
	m_chooseProduct = new CChooseProduct;
	
	m_chooseProduct->SetMysqlLogin(m_strMysqlLogin);
	m_chooseProduct->SetMysqlPass(m_strMysqlPass);
	m_chooseProduct->SetServerAddr(m_strServerAddr);
	m_chooseProduct->change=1;
	m_chooseProduct->hide = 1;

	m_chooseProduct->SetCountProduct(m_iCountProduct);
	m_chooseProduct->SetZakazchik(m_strZakazchik);
	m_chooseProduct->SetProduct(m_strProduct);
	m_chooseProduct->SetWidthProduct(m_strProductWidth);
	m_chooseProduct->SetCountDorojec(m_iCountDorojec);
	m_chooseProduct->SetTolschina(m_strTolschina);
	m_chooseProduct->SetMaterial(m_strMaterial);
	m_chooseProduct->SetDlinaRylona(m_iDlinaRylona);
	m_chooseProduct->SetDlinaEtiketki(m_iDlinaEtiketki);
	m_chooseProduct->SetCountEtiketki(m_iCountEtiketki);
//////////////////////////////////////////////////////////////////////////
	m_chooseProduct->SetVesTary(m_dVagaTary);
//////////////////////////////////////////////////////////////////////////
	m_chooseProduct->SetPartiya(m_strPartiya);
	m_chooseProduct->SetVhidRylonNetto(m_dVhidRylonNetto);
	m_chooseProduct->SetVhidRylonBrytto(m_dVhidRylonBrytto);
	m_chooseProduct->SetVhidRylonDlina(m_iVhidRylonDlina);
	m_chooseProduct->SetNumPrintPage(m_iNumPrintPage);
	m_chooseProduct->SetLogo(m_bLogo);
	m_chooseProduct->SetData(sysDataEtiketka);
	m_chooseProduct->SetManager(m_strManager);
	
	if (m_chooseProduct->DoModal()==IDOK && m_chooseProduct->regim==1)
	{
		vector <MyStruct> vmst[10];
		MyStruct mst;
		
		for (int i=0;i<m_iCountProduct;i++)
		{
			for (int j=0;j<m_plistTabl[i].GetItemCount();j++)
			{
				mst.strNumber = m_plistTabl[i].GetItemText(j,0);
				mst.strBrytto = m_plistTabl[i].GetItemText(j,1);
				mst.strNetto = m_plistTabl[i].GetItemText(j,2);
				vmst[i].push_back(mst);
			}			
		}

		m_iOldCountProduct = m_iCountProduct;
		SetCountProduct(m_chooseProduct->m_iCountProduct);
		SetZakazchik(m_chooseProduct->m_strZakazchik);
		SetTolschina(m_chooseProduct->m_strTolschina);
		SetMaterial(m_chooseProduct->m_strMaterial);
		SetDlinaRylona(m_chooseProduct->m_iDlinaRylona);
		SetDlinaEtiketki(m_chooseProduct->m_iDlinaEtiketki);
		SetCountEtiketki(m_chooseProduct->m_iCountEtiketki);

//////////////////////////////////////////////////////////////////////////
		SetVagaTary(m_chooseProduct->m_dVagaTary,m_chooseProduct->m_iCountProduct);
//////////////////////////////////////////////////////////////////////////


		SetPartiya(m_chooseProduct->m_strPartiya);
		SetProduct(m_chooseProduct->m_strProduct,m_chooseProduct->m_iCountProduct);
		SetCountDorojec(m_chooseProduct->m_iCountDorojec,m_chooseProduct->m_iCountProduct);
		SetProductWidth(m_chooseProduct->m_strProductWidth,m_chooseProduct->m_iCountProduct);
		SetNumPrintPage(m_chooseProduct->m_iNumPrintPage);
		SetLogo(m_chooseProduct->m_bLogo);
		SetData(m_chooseProduct->m_sysDate);
		SetManager(m_chooseProduct->m_strManager);

		SetVhidRylonNetto(m_chooseProduct->m_dVhidRylonNetto);
		SetVhidRylonBrytto(m_chooseProduct->m_dVhidRylonBrytto);
		SetVhidRylonDlina(m_chooseProduct->m_iVhidRylonDlina);

		m_boolNewZakaz = TRUE;

		Initilisation();	

		LVITEM item;
		item.mask = LVIF_TEXT;
		for (int i=0;i<m_iCountProduct;i++)
		{
			for (int j=0;j<(int)vmst[i].size();j++)
			{
				m_plistTabl[i].InsertItem(j,vmst[i][j].strNumber);

				item.iItem = j;
				item.pszText = vmst[i][j].strBrytto.GetBuffer(vmst[i][j].strBrytto.GetLength());
				item.iSubItem = 1;
				m_plistTabl[i].SetItem(&item);

				item.iItem = j;
				item.pszText = vmst[i][j].strNetto.GetBuffer(vmst[i][j].strNetto.GetLength());
				item.iSubItem = 2;
				m_plistTabl[i].SetItem(&item);
			}
		}
	}
	delete m_chooseProduct;
}

void CWorkDialog::OnLbnSelchangeEndListProduct()
{
	int i = m_listEndProduct.GetCurSel();
	CString str;

	m_pmystatEndWidthProduct.SetTextColor(BLUE_TEXT);
	m_pmystatEndWidthProduct.SetWindowText(m_strProductWidth[i]+" мм");

	m_pmystatEndCountRylonProduct.SetTextColor(BLUE_TEXT);
	str.Format("%d шт",m_piCountRylon[i]);
	m_pmystatEndCountRylonProduct.SetWindowText(str);

	m_pmystatEndVesBryttoProduct.SetTextColor(BLUE_TEXT);
	m_pmystatEndVesBryttoProduct.SetWindowText(m_strObBrytto[i]);

	m_pmystatEndVesNettoProduct.SetTextColor(BLUE_TEXT);
	m_pmystatEndVesNettoProduct.SetWindowText(m_strObNetto[i]);
	
	m_pmystatEndDlinaProduct.SetTextColor(BLUE_TEXT);
	str.Format("%d м",m_iDlinaPorezRylon[i]);
	m_pmystatEndDlinaProduct.SetWindowText(str);

	m_pmystatEndCountEtiketki.SetTextColor(BLUE_TEXT);
	str.Format("%d шт",m_piCountEtiketok[i]);
	m_pmystatEndCountEtiketki.SetWindowText(str);
}

void CWorkDialog::SetNumPrintPage(int page)
{
	if (page>0)
		m_iNumPrintPage = page;
	else m_iNumPrintPage = 0;
}


void CWorkDialog::SetVhidRylonBrytto(double brytto)
{
	if (brytto>0)
		m_dVhidRylonBrytto = brytto;
	else m_dVhidRylonBrytto = 0;
}

void CWorkDialog::SetVhidRylonDlina(int dlina)
{
	if (dlina>0)
		m_iVhidRylonDlina = dlina;
	else m_iVhidRylonDlina = dlina;
}

void CWorkDialog::SetVhidRylonNetto(double netto)
{
	if (netto>0)
		m_dVhidRylonNetto = netto;
	else m_dVhidRylonNetto = 0;
}


void CWorkDialog::OnEnChangeEditObrezok()
{
	CString str;
	m_peditEndObrezok.GetWindowText(str);
	static int c3=0;	

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
				m_peditEndObrezok.SetWindowText(str);
			}
			else if (str.GetLength()==2 && strcmp(str.Left(1),"0")==0 &&(strcmp(str.Right(1),",")!=0 &&strcmp(str.Right(1),".")!=0))
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_peditEndObrezok.SetWindowText(str);
			}
			else if (strcmp(str.Right(1),",")==0 || strcmp(str.Right(1),".")==0)
			{
				if (c3>=1)
				{
					MessageBox("Некоректний ввід");
					str = "";
					m_peditEndObrezok.SetWindowText(str);
					c3=0;
				}else c3++;		
			}
		}
		else
		{
			MessageBox("Некоректний ввід");
			str = "";
			m_peditEndObrezok.SetWindowText(str);
		}
		if (str.Find(',')!=-1)
			str.Replace(',','.');

		m_dObrezokKG = atof(str.GetBuffer(str.GetLength()));
		str.Format("%.1f",m_dZagVhidRylonNetto-m_dZagNetto-m_dObrezokKG - m_dOthodKG-m_dBrakKG-m_dBrakTPKG);
		m_peditEndOstatok.SetWindowText(str);
	}
}

void CWorkDialog::OnEnChangeEditOthod()
{
	CString str;
	m_peditEndOthod.GetWindowText(str);
	static int c2=0;	

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
				m_peditEndOthod.SetWindowText(str);
			}
			else if (str.GetLength()==2 && strcmp(str.Left(1),"0")==0 &&(strcmp(str.Right(1),",")!=0 &&strcmp(str.Right(1),".")!=0))
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_peditEndOthod.SetWindowText(str);
			}
			else if (strcmp(str.Right(1),",")==0 || strcmp(str.Right(1),".")==0)
			{
				if (c2>=1)
				{
					MessageBox("Некоректний ввід");
					str = "";
					m_peditEndOthod.SetWindowText(str);
					c2=0;
				}else c2++;		
			}
		}
		else
		{
			MessageBox("Некоректний ввід");
			str = "";
			m_peditEndOthod.SetWindowText(str);
		}
		if (str.Find(',')!=-1)
			str.Replace(',','.');

		m_dOthodKG = atof(str.GetBuffer(str.GetLength()));
		str.Format("%.1f",m_dZagVhidRylonNetto-m_dZagNetto-m_dObrezokKG - m_dOthodKG-m_dBrakKG-m_dBrakTPKG);
		m_peditEndOstatok.SetWindowText(str);
	}	
}

void CWorkDialog::OnEnChangeEditBrak()
{
	CString str;
	m_peditEndBrak.GetWindowText(str);
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
				m_peditEndBrak.SetWindowText(str);
			}
			else if (str.GetLength()==2 && strcmp(str.Left(1),"0")==0 &&(strcmp(str.Right(1),",")!=0 &&strcmp(str.Right(1),".")!=0))
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_peditEndBrak.SetWindowText(str);
			}
			else if (strcmp(str.Right(1),",")==0 || strcmp(str.Right(1),".")==0)
			{
				if (c1>=1)
				{
					MessageBox("Некоректний ввід");
					str = "";
					m_peditEndBrak.SetWindowText(str);
					c1=0;
				}else c1++;		
			}
		}
		else
		{
			MessageBox("Некоректний ввід");
			str = "";
			m_peditEndBrak.SetWindowText(str);
		}
		if (str.Find(',')!=-1)
			str.Replace(',','.');

		m_dBrakKG = atof(str.GetBuffer(str.GetLength()));
		str.Format("%.1f",m_dZagVhidRylonNetto-m_dZagNetto-m_dObrezokKG - m_dOthodKG-m_dBrakKG-m_dBrakTPKG);
		m_peditEndOstatok.SetWindowText(str);
	}	
}

void CWorkDialog::OnEnChangeEditBrakTP()
{
	CString str;
	m_peditEndBrakTP.GetWindowText(str);
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
				m_peditEndBrakTP.SetWindowText(str);
			}
			else if (str.GetLength()==2 && strcmp(str.Left(1),"0")==0 &&(strcmp(str.Right(1),",")!=0 &&strcmp(str.Right(1),".")!=0))
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_peditEndBrakTP.SetWindowText(str);
			}
			else if (strcmp(str.Right(1),",")==0 || strcmp(str.Right(1),".")==0)
			{
				if (c>=1)
				{
					MessageBox("Некоректний ввід");
					str = "";
					m_peditEndBrakTP.SetWindowText(str);
					c=0;
				}else c++;		
			}
		}
		else
		{
			MessageBox("Некоректний ввід");
			str = "";
			m_peditEndBrakTP.SetWindowText(str);
		}
		if (str.Find(',')!=-1)
			str.Replace(',','.');
			 
		m_dBrakTPKG = atof(str.GetBuffer(str.GetLength()));
		str.Format("%.1f",m_dZagVhidRylonNetto-m_dZagNetto-m_dObrezokKG - m_dOthodKG-m_dBrakKG-m_dBrakTPKG);
		m_peditEndOstatok.SetWindowText(str);
	}	
}

void CWorkDialog::OnEnChangeEditOstatok()
{
	CString str;
	m_peditEndOstatok.GetWindowText(str);
	static int c4=0;	

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
				m_peditEndOstatok.SetWindowText(str);
			}
			else if (str.GetLength()==2 && strcmp(str.Left(1),"0")==0 &&(strcmp(str.Right(1),",")!=0 &&strcmp(str.Right(1),".")!=0))
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_peditEndOstatok.SetWindowText(str);
			}
			else if (strcmp(str.Right(1),",")==0 || strcmp(str.Right(1),".")==0)
			{
				if (c4>=1)
				{
					MessageBox("Некоректний ввід");
					str = "";
					m_peditEndOstatok.SetWindowText(str);
					c4=0;
				}else c4++;		
			}
		}
		else
		{
			MessageBox("Некоректний ввід");
			str = "";
			m_peditEndOstatok.SetWindowText(str);
		}
		if (str.Find(',')!=-1)
			str.Replace(',','.');
	}
	m_dOstattokKg = atof(str.GetBuffer(str.GetLength()));
}

void CWorkDialog::OnEnChangeEditNeDostatok()
{
	CString str;
	m_peditEndNeDostatok.GetWindowText(str);
	static int c5=0;	

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
				m_peditEndNeDostatok.SetWindowText(str);
			}
			else if (str.GetLength()==2 && strcmp(str.Left(1),"0")==0 &&(strcmp(str.Right(1),",")!=0 &&strcmp(str.Right(1),".")!=0))
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_peditEndNeDostatok.SetWindowText(str);
			}
			else if (strcmp(str.Right(1),",")==0 || strcmp(str.Right(1),".")==0)
			{
				if (c5>=1)
				{
					MessageBox("Некоректний ввід");
					str = "";
					m_peditEndNeDostatok.SetWindowText(str);
					c5=0;
				}else c5++;		
			}
		}
		else
		{
			MessageBox("Некоректний ввід");
			str = "";
			m_peditEndNeDostatok.SetWindowText(str);
		}
		if (str.Find(',')!=-1)
			str.Replace(',','.');
	}
	m_dNedostatokKG = atof(str.GetBuffer(str.GetLength()));
}


void CWorkDialog::OnEnSetfocusEditObrezok()
{
	if (m_boolFocusObrezok==false)
	{
		m_peditEndObrezok.SetWindowText("");
		m_boolFocusObrezok = true;
	}
}

void CWorkDialog::OnEnSetfocusEditOthod()
{
	if (m_boolFocusOthod==false)
	{
		m_peditEndOthod.SetWindowText("");
		m_boolFocusOthod = true;
	}
}

void CWorkDialog::OnEnSetfocusEditBrak()
{
	if (m_boolFocusBrak==false)
	{
		m_peditEndBrak.SetWindowText("");
		m_boolFocusBrak = true;
	}
}

void CWorkDialog::OnEnSetfocusEditBrakTP()
{
	if (m_boolFocusBrakTP==false)
	{
		m_peditEndBrakTP.SetWindowText("");
		m_boolFocusBrakTP = true;
	}
}

void CWorkDialog::OnEnSetfocusEditOstatok()
{
	if (m_boolFocusOstatok==false)
	{
		m_peditEndOstatok.SetWindowText("");
		m_boolFocusOstatok = true;
	}
}

void CWorkDialog::OnEnSetfocusEditOstatokWidth()
{
	if (m_boolFocusOstatokWidth==false)
	{
		m_peditEndOstatokWidth.SetWindowText("");
		m_boolFocusOstatokWidth = true;
	}
}

void CWorkDialog::OnEnSetfocusEditNeDostatok()
{
	if (m_boolFocusNeDostatok==false)
	{
		m_peditEndNeDostatok.SetWindowText("");
		m_boolFocusNeDostatok = true;
	}
}

void CWorkDialog::WriteBD()
{
	CString str;
	m_peditEndOstatokWidth.GetWindowText(str);
	m_dOstatokWidth = atof(str.GetBuffer(str.GetLength()));

	m_peditEndNeDostatok.GetWindowText(str);
	m_dNedostatokKG = atof(str.GetBuffer(str.GetLength()));

	/////!!!!!!!!!!!!!!!!!
	//query.Format("insert into itak_othod (obrezok, othod, brak, braktp, ostatok, ostatokwidth,nedostatok,zakaz_id) values (%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%d)",m_dObrezokKG,m_dOthodKG,m_dBrakKG,m_dBrakTPKG,m_dOstattokKg,m_dOstatokWidth,m_dNedostatokKG,m_iZakazId);
	//m_database.ExecuteSQL(query);



	/*if (mysql_query(mysql,query)!=0) 
	{
		CString str;
		str.Format("Ошибочный запрос!!! query='%s'",query);
		MessageBox(str);

		str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
		mysql_query(mysql,str);
	}*/
}





void CWorkDialog::P_DrawBarCode(CDC*pDC,const BOOL bPrint, CString strCode/*, CString strProductName, CString strDate*/)
{

	//--------------------------------------------
	int iL,iT,iB;
	const int iMapMode=0;

	{
		CRect rcT;
		if(bPrint)
		{
			rcT.left	=10;
			rcT.top		=50;
			rcT.bottom	=rcT.top+100;

			rcT.right=rcT.left+500;
		}
		else
		{
			GetWindowRect(&rcT);
			::MapWindowPoints(0,m_hWnd,(POINT*)&rcT,2);
			rcT.left+=4;
			rcT.bottom+=30;
		}
		pDC->DPtoLP(&rcT);
		iL=rcT.left;
		iT=rcT.top;
		iB=rcT.bottom;
	}
	//--------------------------------------------

	int iPenW=2;
	CString csStyle="Code39";	
	CString csCode = strCode;

	COLORREF clrBar		=RGB(0,0,0);
	COLORREF clrSpace	=RGB(255,255,255);

	if(bPrint)
	{
		pDC->StartDoc("Hello");
		pDC->StartPage();
	}

	if(csStyle.CompareNoCase("Code39")==0)
	{
		Barcode39 code;
		code.Encode39(csCode);
		P_DrawBarcode(pDC,iL,iT,iB-10,iB,clrBar,clrSpace,iPenW,&code,csCode/*,strProductName,strDate*/);
	}

	if(bPrint)
	{
		pDC->EndPage();
		pDC->EndDoc();
	}
	pDC->SetMapMode(iMapMode);
}

void CWorkDialog::P_DrawBarcode(CDC*pDC,int iX,int iY0,int iY10,int iY11,COLORREF clrBar,COLORREF clrSpace,int iPenW,BarcodeBase*pBc,CString strCode/*, CString strProductName, CString strDate*/)
{
	pBc->DrawBarcode(pDC->m_hDC,iX,iY0,iY10,iY11,clrBar,clrSpace,iPenW,strCode);	
}
void CWorkDialog::OnAcceleratorExtadd()
{
	CString str;
	double dVes=0;

	//	srand(time(0));
	dVes= rand()%50+1;////бруто получаем с весов
	str.Format("%.2f",dVes);
	//str.Format("%.2f",m_dTempVaga);
	m_peditVes[m_iNumList].SetWindowText(str);

	AddProduct();

	m_dTempVaga = 0;

	if (m_iCountDorojec[m_iNumList]==count)
	{
		if (m_iNumList==m_iCountProduct-1)
		{
			m_peditVes[m_iNumList].EnableWindow(FALSE);
			m_peditVes[0].EnableWindow(TRUE);
			m_peditVes[0].SetWindowText("");
			m_peditVes[0].SetFocus();
		}
		else
		{
			m_peditVes[m_iNumList].EnableWindow(FALSE);
			m_peditVes[m_iNumList+1].EnableWindow(TRUE);
			m_peditVes[m_iNumList+1].SetWindowText("");
			m_peditVes[m_iNumList+1].SetFocus();
		}
	}

	if (m_iCountDorojec[m_iNumList]==count)
	{
		if (m_iNumList==m_iCountProduct-1)
			m_iNumList=0;
		else m_iNumList++;
		count = 1;
	}else count++;
}

void CWorkDialog::OnBnClickedButtonPrintZvit()
{
	/*CQPrint  prt;
	HPRIVATEFONT   hFont14x14, hFont14x14Bold, hFont12x12, hFont12x12Bold,hFont10x10, hFont10x10Bold;
	CSize  dim;
	CRect  margins;
	double dTemp = 0 ;
	int iTemp = 0 ;

	CString str, query2;

	//	m_lsZakazchik.GetText(m_lsZakazchik.GetCurSel(),str);

	CString strZakazchik = m_strZakazchik;

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

			str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
			mysql_query(mysql,str);
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

			str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
			mysql_query(mysql,str);
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
		t = sysTimeStartWork;
		//m_datetimeZakaz.GetTime(&t);	

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

		for (int j=0;j<m_listEndProduct.GetCount();j++)
		{
			m_listEndProduct.GetText(j,str);
			PrintProduct(str);
		}
	}

}

void CWorkDialog::PrintProduct(CString sProduct)
{
	CQPrint  prt;

	HPRIVATEFONT   hFont14x14, hFont14x14Bold, hFont12x12, hFont12x12Bold,hFont10x10, hFont10x10Bold;

	CSize  dim;
	CRect  margins;

	int iTemp = 0;
	double dTemp = 0;

	CString str, query2;

	//	m_lsZakazchik.GetText(m_lsZakazchik.GetCurSel(),str);
	CString strZakazchik = m_strZakazchik;
	CString strProduct = sProduct;


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

			str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
			mysql_query(mysql,str);
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

			str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
			mysql_query(mysql,str);
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

void CWorkDialog::ChangeRylon(int iNumlist, int iItem)
{
 	
	m_changeRylon = new CChangeRylon;
	m_changeRylon->SetHandleCom(hFile);
	int numrylon = atoi(m_plistTabl[iNumlist].GetItemText(iItem,0));
	m_changeRylon->SetNumRylon(numrylon);
	m_changeRylon->SetBrytto(atof(m_plistTabl[iNumlist].GetItemText(iItem,1)));
	m_changeRylon->SetNetto(atof(m_plistTabl[iNumlist].GetItemText(iItem,2)));
	m_changeRylon->SetVesTary(m_dVagaTary[iNumlist]);
	if (m_changeRylon->DoModal()==IDOK)
	{
		CString str;
		 
		m_dObNetto[iNumlist] -= m_dNetto;
		m_dObBrytto[iNumlist] -= m_dBrytto;

		m_dZagBrytto -= m_dBrytto;
		m_dZagNetto -= m_dNetto;

		m_dNetto = m_changeRylon->m_dNetto;
		m_dBrytto = m_changeRylon->m_dBrytto;

		m_dZagNetto += m_dNetto;
		m_dZagBrytto += m_dBrytto;

		m_dObNetto[iNumlist] += m_dNetto;
		m_strObNetto[m_iNumList].Format("%.2f кг",m_dObNetto[m_iNumList]);
		m_pmyStatVesNetto[m_iNumList].SetTextColor(BLUE_TEXT);
		m_pmyStatVesNetto[m_iNumList].SetWindowText(m_strObNetto[m_iNumList]);
		
		m_dObBrytto[iNumlist] += m_dBrytto;
		m_strObBrytto[m_iNumList].Format("%.2f кг",m_dObBrytto[m_iNumList]);
		m_pmyStatVesBrytto[m_iNumList].SetTextColor(BLUE_TEXT);
		m_pmyStatVesBrytto[m_iNumList].SetWindowText(m_strObBrytto[m_iNumList]);
		
		LVITEM item;
		item.mask = LVIF_TEXT;		
	
		str.Format("%.2f",m_dNetto);
		item.iItem = iItem;
		item.pszText = str.GetBuffer(str.GetLength());
		item.iSubItem = 2;
		m_plistTabl[iNumlist].SetItem(&item);

		str.Format("%.2f",m_dBrytto);
		item.iItem = iItem;
		item.pszText = str.GetBuffer(str.GetLength());
		item.iSubItem = 1;
		m_plistTabl[iNumlist].SetItem(&item);
		
// 		query.Format("update itak_productzakaz set vesnetto=%.2f, vesbrytto=%.2f where id=%d",m_dNetto,m_dBrytto,m_iProductId);
// 		if (mysql_query(mysql,query)!=0) 
// 		{
// 			CString str;
// 			str.Format("Ошибочный запрос!!! query='%s'",query);
// 			MessageBox(str);
// 		}

		int iProductId=0;
		CString strItem = m_plistTabl[iNumlist].GetItemText(iItem,0);
		int iZnachItem = atoi(strItem.GetBuffer());

		for (int i=0;i<m_vMyRecord.size();i++)
		{
			if (m_vMyRecord[i].iNumList==iNumlist && m_vMyRecord[i].iListItem==iZnachItem)
			{
				
				m_vMyRecord[i].dBrutto = m_dBrytto;
				iProductId = m_vMyRecord[i].iBarCode;
				query.Format("update itak_vihidrylon set brytto=%.2f where id=%d",m_dBrytto,iProductId);
				m_database.ExecuteSQL(query);
				/*if (mysql_query(mysql,query)!=0) 
				{
					CString str;
					str.Format("Ошибочный запрос!!! query='%s'",query);
					MessageBox(str);

					str.Format("insert into itak_error (zakaz_id, log) values (%d,'%s')",m_iZakazId,query);
					mysql_query(mysql,str);
				}*/
				break;
			}
		}
		


		//////////////////////////////////////////////////////////////////////////
		//barcode coord
		CString csCode;
		CString csStyle="Code39";
		COLORREF clrBar		=RGB(0,0,0);
		COLORREF clrSpace	=RGB(255,255,255);
		int iPenW=2;
		int iL,iT,iB;

		CRect rcT;
		rcT.left	=10;
		rcT.top		=410;
		rcT.bottom	=rcT.top+100;
		rcT.right=rcT.left+500;
		iL=rcT.left;
		iT=rcT.top;
		iB=rcT.bottom;
		//////////////////////////////////////////////////////////////////////////


		CString strDlina, strKolEtiket, strSmena, strData,strMonth,strDay,
			strNetto, strBrytto, strNumRylon;

		if (m_strPrintEtiketka.GetLength()!=0)
		{
			CDC dlg;
			dlg.CreateDC (NULL, m_strPrintEtiketka, NULL, NULL);
			HDC hdcPrinter = dlg;

			if (m_iNumPrintPage!=0)
			{
				if (hdcPrinter == NULL)
				{MessageBox(_T("Нет принтера!"));}
				else
				{
					dcPrinter.Attach(hdcPrinter);
					DOCINFO docinfo;
					memset(&docinfo, 0, sizeof(docinfo));
					docinfo.cbSize = sizeof(docinfo);
					docinfo.lpszDocName = _T("CDC::StartDoc() Code Fragment");

					for (int i=0;i<m_iNumPrintPage;i++)
					{
						if (dcPrinter.StartDoc(&docinfo) < 0)
							MessageBox(_T("Printer wouldn't initalize"));
						else 
						{
							if (dcPrinter.StartPage() < 0)
							{
								MessageBox(_T("Could not start page"));
								dcPrinter.AbortDoc();
							} 
							else 
							{
								CFont font;
								font.CreateFont(40,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Arial");
								dcPrinter.SelectObject(&font);

								strNumRylon.Format("%d",numrylon);

								strNetto.Format("%.2f",m_dNetto);
								strBrytto.Format("%.2f",m_dBrytto);

								strDlina.Format("%d",m_iDlinaRylona);
								strKolEtiket.Format("%d",m_iCountEtiketki);

								strSmena.Format("%d/%d",m_iNumCar,m_iNumSmena);

								SYSTEMTIME t;
								GetSystemTime(&t);

								if (t.wMonth<10)
									strMonth.Format("0%d",t.wMonth);
								else strMonth.Format("%d",t.wMonth);

								if (t.wDay<10)
									strDay.Format("0%d",t.wDay);
								else strDay.Format("%d",t.wDay);
								CString str;
								if (m_strMaterial==" ")
									str = m_strTolschina;
								else str.Format("%s %s",m_strMaterial,m_strTolschina);
								strData.Format("%s.%s",strDay,strMonth);

								Print(&dcPrinter,m_strZakazchik,m_strProduct[iNumlist],str,
									m_strProductWidth[iNumlist],strNumRylon,strNetto,strBrytto,
									strDlina,strKolEtiket,strSmena,m_strPartiya,strData);

								csCode.Format("3%d",iProductId);

								if(csStyle.CompareNoCase("Code39")==0)
								{

									Barcode39 code;
									code.Encode39(csCode);
									P_DrawBarcode(&dcPrinter,iL,iT,iB-10,iB,clrBar,clrSpace,iPenW,&code,csCode/*,strProductName,strDate*/);
								}

								dcPrinter.EndPage();
								dcPrinter.EndDoc();
							}
						}
					}
					dcPrinter.Detach();
				}
			}
		}

		SYSTEMTIME t;
		GetSystemTime(&t);

		if (t.wMonth<10)
			strMonth.Format("0%d",t.wMonth);
		else strMonth.Format("%d",t.wMonth);

		if (t.wDay<10)
			strDay.Format("0%d",t.wDay);
		else strDay.Format("%d",t.wDay);
		strData.Format("%s.%s.%d",strDay,strMonth,t.wYear);

		/*if (m_strPrintShtrih.GetLength()!=0)
		{
			CDC m_PrinterDC;
			m_PrinterDC.CreateDC (NULL, m_strPrintShtrih, NULL, NULL);
			HDC hDC = m_PrinterDC;
			CDC*pDC=CDC::FromHandle(hDC);

			if (hDC == NULL)
			{MessageBox(_T("Нет принтера!"));}
			else {

				str.Format("%d",m_iProductId);
				P_DrawBarCode(pDC,1,str,m_strProduct[m_iNumList],strData);
			}
		}*/
	}
	delete m_changeRylon;
}

void CWorkDialog::OnLvnItemActivateList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	ChangeRylon(0,pNMIA->iItem);	
	*pResult = 0;
}

void CWorkDialog::OnLvnItemActivateList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	ChangeRylon(1,pNMIA->iItem);	
	*pResult = 0;
}

void CWorkDialog::OnLvnItemActivateList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	ChangeRylon(2,pNMIA->iItem);	
	*pResult = 0;
}

void CWorkDialog::OnLvnItemActivateList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	ChangeRylon(3,pNMIA->iItem);	
	*pResult = 0;
}

void CWorkDialog::OnLvnItemActivateList5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	ChangeRylon(4,pNMIA->iItem);	
	*pResult = 0;
}

void CWorkDialog::OnLvnItemActivateList6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	ChangeRylon(5,pNMIA->iItem);	
	*pResult = 0;
}

void CWorkDialog::OnLvnItemActivateList7(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	ChangeRylon(6,pNMIA->iItem);	
	*pResult = 0;
}

void CWorkDialog::OnLvnItemActivateList8(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	ChangeRylon(7,pNMIA->iItem);	
	*pResult = 0;
}

void CWorkDialog::OnLvnItemActivateList9(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	ChangeRylon(8,pNMIA->iItem);	
	*pResult = 0;
}

void CWorkDialog::OnLvnItemActivateList10(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	ChangeRylon(9,pNMIA->iItem);	
	*pResult = 0;
}

void CWorkDialog::SetLogo(bool bLogo)
{
	m_bLogo = bLogo;
}
void CWorkDialog::OnAcceleratorAddobrazets()
{
	MessageBox("obrazec");
}
