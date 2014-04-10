// ChangeRylon.cpp: файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "ChangeRylon.h"


// диалоговое окно CChangeRylon

IMPLEMENT_DYNAMIC(CChangeRylon, CDialog)

CChangeRylon::CChangeRylon(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeRylon::IDD, pParent),m_dTempVaga(0), m_iNumRylon(0), m_dVesTary(0),
											m_dNetto(0),m_dBrytto(0)
{
	m_hAccel = LoadAccelerators( AfxGetResourceHandle(), MAKEINTRESOURCE( IDR_ACCELERATOR_CLOSEENTER ) );
}

CChangeRylon::~CChangeRylon()
{
}

void CChangeRylon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CHANGERYLON_BRYTTO, m_editBrytto);
	DDX_Control(pDX, IDC_EDIT_CHANGERYLON_NETTO, m_editNetto);
}


BEGIN_MESSAGE_MAP(CChangeRylon, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CChangeRylon::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CChangeRylon::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_CHANGERYLON_BRYTTO, &CChangeRylon::OnEnChangeEditChangerylonBrytto)
END_MESSAGE_MAP()

void CChangeRylon::SetHandleCom(HANDLE hHandl)
{
	if(hHandl==INVALID_HANDLE_VALUE){
		CloseHandle(hHandl);
	}
	else 
		hFile = hHandl;
}
// обработчики сообщений CChangeRylon

void CChangeRylon::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	char buff[100];
	DWORD dwBytesRead = 0;	
	CString str;
	ReadFile(hFile, buff, 100, &dwBytesRead, NULL);
	if (dwBytesRead!=0)
	{
		str.Format("%s",buff);
		str = str.Left(str.Find("kg"));
		str.TrimLeft(" ");
		m_dTempVaga = strtod(str.GetBuffer(str.GetLength()),0);
		str.Format("%.2f",m_dTempVaga);
		m_editBrytto.SetWindowText(str);
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CChangeRylon::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetTimer(0,500,0);
	CString str;
	str.Format("%.2f",m_dBrytto);
	m_editBrytto.SetWindowText(str);
	str.Format("%.2f",m_dNetto);
	m_editNetto.SetWindowText(str);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CChangeRylon::SetVesTary(double ves)
{
	if (ves!=0)
		m_dVesTary = ves;
	else m_dVesTary = 0;
}

void CChangeRylon::SetNumRylon(int num)
{
	if (num>=0)
		m_iNumRylon = num;
	else m_iNumRylon = 0;
}

void CChangeRylon::OnBnClickedOk()
{
	CString str;
	m_editBrytto.GetWindowText(str);
	if (str.Find(',')!=-1)
		str.Replace(',','.'); 
	m_dBrytto = atof(str.GetBuffer(str.GetLength()));

	m_editNetto.GetWindowText(str);
	if (str.Find(',')!=-1)
		str.Replace(',','.');
	m_dNetto = atof(str.GetBuffer(str.GetLength()));
	OnOK();
}

void CChangeRylon::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	//OnCancel();
	OnCancel();
}


void CChangeRylon::SetNetto(double netto)
{
	if (netto>0)
		m_dNetto = netto;
	else m_dNetto = 0;
}

void CChangeRylon::SetBrytto(double brytto)
{
	if (brytto>0)
		m_dBrytto = brytto;
	else m_dBrytto = 0;
}
BOOL CChangeRylon::PreTranslateMessage(MSG* pMsg)
{
	if ( TranslateAccelerator( m_hWnd, m_hAccel, pMsg ) ) return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CChangeRylon::OnEnChangeEditChangerylonBrytto()
{
	CString str;
	m_editBrytto.GetWindowText(str);
	m_dBrytto = atof(str.GetBuffer(str.GetLength()));

	m_dNetto = m_dBrytto-m_dVesTary;
	str.Format("%.2f",m_dNetto);
	m_editNetto.SetWindowText(str);
}
