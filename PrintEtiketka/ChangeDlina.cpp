// ChangeDlina.cpp: файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "ChangeDlina.h"


// диалоговое окно CChangeDlina

IMPLEMENT_DYNAMIC(CChangeDlina, CDialog)

CChangeDlina::CChangeDlina(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeDlina::IDD, pParent),m_iDlinaRylona(0),m_iCountEtiketok(0),m_iDlinaEtiketki(0)
{

}

CChangeDlina::~CChangeDlina()
{
}

void CChangeDlina::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CHANGEDLINA_DLINA, m_editDlina);
	DDX_Control(pDX, IDC_EDIT_CHANGECOUNTETIKETOK, m_editCountEtiketok);
}


BEGIN_MESSAGE_MAP(CChangeDlina, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CChangeDlina::OnBnClickedButtonChange)
	ON_EN_CHANGE(IDC_EDIT_CHANGEDLINA_DLINA, &CChangeDlina::OnEnChangeEditChangedlinaDlina)
END_MESSAGE_MAP()


// обработчики сообщений CChangeDlina

BOOL CChangeDlina::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editDlina.SetLimitText(6);
	m_editCountEtiketok.SetLimitText(7);

	CRect rect;
	GetClientRect(&rect);

	m_statDlina.Create("Довжина рулону (м):",WS_CHILD|WS_VISIBLE,CRect(rect.left+20,rect.top+25,rect.left+160,rect.top+45),this,16005);
	m_statCountEtiketok.Create("К-ть етикеток (шт):",WS_CHILD|WS_VISIBLE,CRect(rect.left+20,rect.top+55,rect.left+160,rect.top+75),this,16005);
	
	CString str;
	str.Format("%d",m_iDlinaRylona);
	m_editDlina.SetWindowText(str);

	str.Format("%d",m_iCountEtiketok);
	m_editCountEtiketok.SetWindowText(str);

	m_editDlina.SetSel(0,-1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CChangeDlina::OnCancel()
{
	// TODO: добавьте специализированный код или вызов базового класса

//	CDialog::OnCancel();
}

void CChangeDlina::OnBnClickedButtonChange()
{
	CString str;
	m_editDlina.GetWindowText(str);
	if (str.GetLength()!=0)
	{
		m_iDlinaRylona = atoi(str.GetBuffer(str.GetLength()));
		m_editCountEtiketok.GetWindowText(str);
		if (str.GetLength()!=0)
		{
			m_iCountEtiketok = atoi(str.GetBuffer(str.GetLength()));
			OnOK();
		}else MessageBox("Введіть к-ть етикеток");
	}
	else MessageBox("Введіть довжину рулона");

}

void CChangeDlina::SetDlina(int dlina)
{
	if (dlina>0)
		m_iDlinaRylona = dlina;
	else m_iDlinaRylona = 0;
}

void CChangeDlina::SetCountEtiketok(int count,int dlina)
{
	if (count>0)
		m_iCountEtiketok = count;
	else m_iCountEtiketok = 0;

	if (dlina>0)
		m_iDlinaEtiketki=dlina;
	else m_iDlinaEtiketki = 0;
}

void CChangeDlina::OnEnChangeEditChangedlinaDlina()
{
	CString str;
	m_editDlina.GetWindowText(str);
	m_iDlinaRylona = atoi(str.GetBuffer(str.GetLength()));
	double dtemp =(m_iDlinaRylona*1000/m_iDlinaEtiketki);
	m_iCountEtiketok = (int)(dtemp+0.5);
	
	str.Format("%d",m_iCountEtiketok);
	m_editCountEtiketok.SetWindowText(str);
}
