// EndZakaz.cpp: файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "EndZakaz.h"


// диалоговое окно CEndZakaz

IMPLEMENT_DYNAMIC(CEndZakaz, CDialog)

CEndZakaz::CEndZakaz(CWnd* pParent /*=NULL*/)
	: CDialog(CEndZakaz::IDD, pParent)
{
	m_hAccel = LoadAccelerators( AfxGetResourceHandle(), MAKEINTRESOURCE( IDR_WORK_ACCELERATOR ) );

}

CEndZakaz::~CEndZakaz()
{
}

void CEndZakaz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEndZakaz, CDialog)
	ON_BN_CLICKED(IDOK, &CEndZakaz::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEndZakaz::OnBnClickedCancel)
END_MESSAGE_MAP()


// обработчики сообщений CEndZakaz

BOOL CEndZakaz::PreTranslateMessage(MSG* pMsg)
{
	if ( TranslateAccelerator( m_hWnd, m_hAccel, pMsg ) ) return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}


void CEndZakaz::OnBnClickedOk()
{

}

void CEndZakaz::OnBnClickedCancel()
{
	OnCancel();
}
BOOL CEndZakaz::OnInitDialog()
{
	CDialog::OnInitDialog();

	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	int iWindowPos = 20;
	MoveWindow(iWindowPos,iWindowPos,x-iWindowPos*2,y-iWindowPos*2);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CEndZakaz::SetCountProduct(int count)
{
	if (count!=0)
		m_iCountProduct = count;
	else m_iCountProduct = 0;
}

void CEndZakaz::SetZakazchik(CString zakazchik)
{
	m_strZakazchik = zakazchik;
}

void CEndZakaz::SetTolschina(CString tols)
{
	m_strTolschina = tols;
}

void CEndZakaz::SetMaterial(CString material)
{
	m_strMaterial = material;
}

void CEndZakaz::SetVagaTary(double vaga)
{
	if (vaga!=0)
		m_dVagaTary = vaga;
	else vaga=0;
}

void CEndZakaz::SetPartiya(CString partiya)
{
	m_strPartiya = partiya;
}

void CEndZakaz::SetProduct(CString *name, int count)
{
	for (int i=0;i<count;i++)
		m_strProduct[i] = name[i];
}

void CEndZakaz::SetProductWidth(CString *width, int count)
{
	for (int i=0;i<count;i++)
		m_strProductWidth[i] = width[i];
}