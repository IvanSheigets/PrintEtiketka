// Password.cpp: файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "Password.h"



// диалоговое окно CPassword

IMPLEMENT_DYNAMIC(CPassword, CDialog)

CPassword::CPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CPassword::IDD, pParent)
{

}

CPassword::~CPassword()
{
}

void CPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PASS_SETTING, m_editPassword);
}


BEGIN_MESSAGE_MAP(CPassword, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PASS_ENTER, &CPassword::OnBnClickedButtonPassEnter)
	ON_BN_CLICKED(IDC_BUTTON_PASS_EXIT, &CPassword::OnBnClickedButtonPassExit)
END_MESSAGE_MAP()


// обработчики сообщений CPassword

void CPassword::OnBnClickedButtonPassEnter()
{
	CString str;
	m_editPassword.GetWindowText(str);
	if (str.GetLength()!=0)	{
		if (str=="Ghjcnjrdfibyj1")		{
			m_settings = new CSettings;
			m_settings->DoModal();
			delete m_settings;
			OnOK();
		}else MessageBox("Некоректний пароль!!!");
	}else MessageBox("Введіть пароль!!!");
	
}

BOOL CPassword::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CPassword::OnBnClickedButtonPassExit()
{
	OnOK();
}
