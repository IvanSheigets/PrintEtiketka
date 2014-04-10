// PrintEtiketkaDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "PrintEtiketkaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// диалоговое окно CPrintEtiketkaDlg


CPrintEtiketkaDlg::CPrintEtiketkaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintEtiketkaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_cbDialogColor.CreateSolidBrush(RGB(46, 139, 87));
	m_hAccel = LoadAccelerators( AfxGetResourceHandle(), MAKEINTRESOURCE( IDR_WORK_ACCELERATOR ) );

		
}

void CPrintEtiketkaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPrintEtiketkaDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CPrintEtiketkaDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPrintEtiketkaDlg::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
//	ON_BN_CLICKED(IDC_BUTTON1, &CPrintEtiketkaDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// обработчики сообщений CPrintEtiketkaDlg

BOOL CPrintEtiketkaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок
	
	//SetWindowPos(&wndTopMost,1,1,200,200,SWP_SHOWWINDOW); //всегда поверх остальных окон

	bool flag = true;

	FILE * file;
	CString str;
	file = fopen("settings.txt","rb");
	if (file!=NULL)
	{
		char buf[1024];
		while (fgets(buf,1000,file)!='\0')
		{
			str.Format("%s",buf);
			str.Remove('\n');
			if (str.Left(str.Find(" "))=="server_addr")
				m_strServerAddr = str.Mid(str.Find(" ")+3);
			else if (str.Left(str.Find(" "))=="login")
				m_strMysqlLogin = str.Mid(str.Find(" ")+3);
			else if (str.Left(str.Find(" "))=="password")
				m_strMysqlPass=str.Mid(str.Find(" ")+3);
		}
		fclose(file);
	}
	else 
	{
		m_strServerAddr = "127.0.0.1";
		m_strMysqlLogin = "root";
		m_strMysqlPass = "";
	}
	
	while(flag)
	{
		//flag = false;
		m_chooseRegim = new CChooseRegim ;
		CString str;
		m_chooseRegim->regim=1;
//////////////////////////////////////////////////////////////////////////
		int t = 1;
		CString strProductName[10];
		CString strProductWidth[10];
		int countdoroj[10];
		double v[10];
//////////////////////////////////////////////////////////////////////////
		
		if (m_chooseRegim->DoModal()==IDOK)
		{			
			switch (m_chooseRegim->regim)
			{
				case 1:		//Enter
					m_chooseProduct = new CChooseProduct ;

					m_chooseProduct->SetServerAddr(m_strServerAddr);
					m_chooseProduct->SetMysqlLogin(m_strMysqlLogin);
					m_chooseProduct->SetMysqlPass(m_strMysqlPass);
					m_chooseProduct->regim=1;
					if (m_chooseProduct->DoModal()==IDOK)
					{
						m_workDialog = new CWorkDialog;
						switch (m_chooseProduct->regim)
						{
							case 1:	//запуск главного рабочего окна
								m_workDialog->SetCountProduct(m_chooseProduct->m_iCountProduct);
								m_workDialog->SetZakazchik(m_chooseProduct->m_strZakazchik);
								m_workDialog->SetTolschina(m_chooseProduct->m_strTolschina);
								m_workDialog->SetMaterial(m_chooseProduct->m_strMaterial);
								m_workDialog->SetDlinaRylona(m_chooseProduct->m_iDlinaRylona);
								m_workDialog->SetDlinaEtiketki(m_chooseProduct->m_iDlinaEtiketki);
								m_workDialog->SetCountEtiketki(m_chooseProduct->m_iCountEtiketki);
//////////////////////////////////////////////////////////////////////////
								m_workDialog->SetVagaTary(m_chooseProduct->m_dVagaTary,m_chooseProduct->m_iCountProduct);
//////////////////////////////////////////////////////////////////////////
								m_workDialog->SetPartiya(m_chooseProduct->m_strPartiya);
								m_workDialog->SetProduct(m_chooseProduct->m_strProduct,m_chooseProduct->m_iCountProduct);
								m_workDialog->SetCountDorojec(m_chooseProduct->m_iCountDorojec,m_chooseProduct->m_iCountProduct);
								m_workDialog->SetProductWidth(m_chooseProduct->m_strProductWidth,m_chooseProduct->m_iCountProduct);
								m_workDialog->SetNumCar(m_chooseRegim->m_iNumberCar);
								m_workDialog->SetNumSmena(m_chooseRegim->m_iNumberSmena);
								m_workDialog->SetNumPrintPage(m_chooseProduct->m_iNumPrintPage);
								m_workDialog->SetVhidRylonNetto(m_chooseProduct->m_dVhidRylonNetto);
								m_workDialog->SetVhidRylonBrytto(m_chooseProduct->m_dVhidRylonBrytto);
								m_workDialog->SetVhidRylonDlina(m_chooseProduct->m_iVhidRylonDlina);	
								//m_workDialog->SetNumberZakazTK((m_chooseProduct->m_iNumberZakazTK));
								m_workDialog->SetLogo(m_chooseProduct->m_bLogo);
								m_workDialog->SetData(m_chooseProduct->m_sysDate);
								m_workDialog->SetManager(m_chooseProduct->m_strManager);
																

								m_workDialog->SetServerAddr(m_strServerAddr);
								m_workDialog->SetMysqlLogin(m_strMysqlLogin);
								m_workDialog->SetMysqlPass(m_strMysqlPass);

								/*m_workDialog->SetCountProduct(t);
								m_workDialog->SetZakazchik("ЗВЕНІГОРОДСЬКИЙ СИРКОМБІНАТ");
								m_workDialog->SetTolschina("35");
								m_workDialog->SetMaterial("ЖЕМЧУГ");
								m_workDialog->SetDlinaRylona(2000);
								m_workDialog->SetDlinaEtiketki(120);
								m_workDialog->SetCountEtiketki(12348);
								
								m_workDialog->SetPartiya("32/6");

								for (int i=0;i<t;i++)
									strProductName[i] = "СОФИЯ КИЕВСКАЯ 1.5Л";
								m_workDialog->SetProduct(strProductName,t);

								for (int i=0;i<t;i++)
								{
									strProductWidth[i] = "94";
									v[i]=0.5;
								}
								m_workDialog->SetVagaTary(v,t);
								m_workDialog->SetProductWidth(strProductWidth,t);

								for (int i=0;i<t;i++)
									countdoroj[i] = i+1;

								m_workDialog->SetCountDorojec(countdoroj,t);								
								m_workDialog->SetNumCar(1);
								m_workDialog->SetNumSmena(3);
								m_workDialog->SetNumPrintPage(1);

								m_workDialog->SetVhidRylonNetto(500);
								m_workDialog->SetVhidRylonBrytto(700);
								m_workDialog->SetVhidRylonDlina(270);*/
								

						
								if (m_workDialog->DoModal()==IDOK)
								{
									switch(m_workDialog->regim)
									{
										case 1:	MessageBox("1");	break;
										case 2:	
											
										break;
										case 3:
											//system("shutdown -s -t 0 -f");
											exit(1);		break;
									}
									
								}
								delete m_workDialog;
							break;
							case 2:	
								flag=true;
								delete m_chooseRegim;
							break;
							case 3:	
								//system("shutdown -s -t 0 -f");
								exit(1); 	break;//выход из программы
						}
						delete m_chooseProduct;
					}					
				break;
				case 2:
					m_zvit = new CZvit;
					m_zvit->SetServerAddr(m_strServerAddr);
					m_zvit->SetMysqlLogin(m_strMysqlLogin);
					m_zvit->SetMysqlPass(m_strMysqlPass);
					if (m_zvit->DoModal()==IDOK)
					{

					}
					delete m_zvit;
				break;
				case 3:		
					m_password = new CPassword;
					if (m_password->DoModal()==IDOK)
					{
						
					}
					delete m_password;					
					break;
				case 4:
					//system("shutdown -s -t 0 -f");
					exit(1);	
					break;//выход из программы
			}
		}
	}
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}


void CPrintEtiketkaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		int x = GetSystemMetrics(SM_CXSCREEN);
		int y = GetSystemMetrics(SM_CYSCREEN);
		MoveWindow(0,0,x,y);
		CDialog::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CPrintEtiketkaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPrintEtiketkaDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	OnOK();
}

void CPrintEtiketkaDlg::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	OnCancel();
}

HBRUSH CPrintEtiketkaDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return m_cbDialogColor;
	return hbr;
}

LRESULT CPrintEtiketkaDlg::OnNcHitTest(CPoint point)
{
	UINT nHitTest = CWnd::OnNcHitTest(point);
	if (nHitTest == HTCAPTION)
		nHitTest = HTCLIENT;   
	return nHitTest;

	return CDialog::OnNcHitTest(point);
}


BOOL CPrintEtiketkaDlg::PreTranslateMessage(MSG* pMsg)
{
	if ( TranslateAccelerator( m_hWnd, m_hAccel, pMsg ) ) return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}
