// NewVhidRylon.cpp: файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "NewVhidRylon.h"


// диалоговое окно CNewVhidRylon

IMPLEMENT_DYNAMIC(CNewVhidRylon, CDialog)

CNewVhidRylon::CNewVhidRylon(CWnd* pParent /*=NULL*/)
	: CDialog(CNewVhidRylon::IDD, pParent)
{
	m_iVhidDlinaRylona = 0;
	m_dVhidNetto = 0;
	m_dVhidBrytto = 0;
}

CNewVhidRylon::~CNewVhidRylon()
{
}

void CNewVhidRylon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NEWRYLON_NETTO, m_editNetto);
	DDX_Control(pDX, IDC_EDIT_NEWRYLON_BRYTTO, m_editBrytto);
	DDX_Control(pDX, IDC_EDIT_NEWRYLON_DLINARYLONA, m_editDlina);
}


BEGIN_MESSAGE_MAP(CNewVhidRylon, CDialog)
	ON_EN_CHANGE(IDC_EDIT_NEWRYLON_NETTO, &CNewVhidRylon::OnEnChangeEditNewrylonNetto)
	ON_EN_CHANGE(IDC_EDIT_NEWRYLON_BRYTTO, &CNewVhidRylon::OnEnChangeEditNewrylonBrytto)
ON_BN_CLICKED(IDC_BUTTON_NEWRYLON_ADD, &CNewVhidRylon::OnBnClickedButtonNewrylonAdd)
END_MESSAGE_MAP()


// обработчики сообщений CNewVhidRylon

BOOL CNewVhidRylon::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_editDlina.SetLimitText(6);
	m_editNetto.SetLimitText(6);
	m_editBrytto.SetLimitText(6);

	CRect rect;
	GetClientRect(&rect);
	m_statNetto.Create("Масса нетто (кг):",WS_CHILD|WS_VISIBLE,CRect(rect.left+20,rect.top+25,rect.left+160,rect.top+45),this,16005);
	m_statBrytto.Create("Масса брутто (кг):",WS_CHILD|WS_VISIBLE,CRect(rect.left+20,rect.top+60,rect.left+160,rect.top+75),this,16005);
	m_statDlina.Create("Довжина рулону (м):",WS_CHILD|WS_VISIBLE,CRect(rect.left+20,rect.top+90,rect.left+160,rect.top+110),this,16005);

	CString str;
	str.Format("%.2f",m_dVhidNetto);
	m_editNetto.SetWindowText(str);

	str.Format("%.2f",m_dVhidBrytto);
	m_editBrytto.SetWindowText(str);

	str.Format("%d",m_iVhidDlinaRylona);
	m_editDlina.SetWindowText(str);
	

	// TODO:  Добавить дополнительную инициализацию

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CNewVhidRylon::OnEnChangeEditNewrylonNetto()
{
	CString str;
	m_editNetto.GetWindowText(str);
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
				m_editNetto.SetWindowText(str);
			}
			else if (str.GetLength()==2 && strcmp(str.Left(1),"0")==0 &&(strcmp(str.Right(1),",")!=0 &&strcmp(str.Right(1),".")!=0))
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_editNetto.SetWindowText(str);
			}
			else if (strcmp(str.Right(1),",")==0 || strcmp(str.Right(1),".")==0)
			{
				if (c1>=1)
				{
					MessageBox("Некоректний ввід");
					str = "";
					m_editNetto.SetWindowText(str);
					c1=0;
				}else c1++;		
			}
		}
		else
		{
			MessageBox("Некоректний ввід");
			str = "";
			m_editNetto.SetWindowText(str);
		}
		if (str.Find(',')!=-1)
			str.Replace(',','.');
	}	
}

void CNewVhidRylon::OnEnChangeEditNewrylonBrytto()
{
	CString str;
	m_editBrytto.GetWindowText(str);
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
				m_editBrytto.SetWindowText(str);
			}
			else if (str.GetLength()==2 && strcmp(str.Left(1),"0")==0 &&(strcmp(str.Right(1),",")!=0 &&strcmp(str.Right(1),".")!=0))
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_editBrytto.SetWindowText(str);
			}
			else if (strcmp(str.Right(1),",")==0 || strcmp(str.Right(1),".")==0)
			{
				if (c1>=1)
				{
					MessageBox("Некоректний ввід");
					str = "";
					m_editBrytto.SetWindowText(str);
					c1=0;
				}else c1++;		
			}
		}
		else
		{
			MessageBox("Некоректний ввід");
			str = "";
			m_editBrytto.SetWindowText(str);
		}
		if (str.Find(',')!=-1)
			str.Replace(',','.');
	}
}

void CNewVhidRylon::SetVhidDlinaRylona(int dlina)
{
	if (dlina>0)
		m_iVhidDlinaRylona = dlina;
	else m_iVhidDlinaRylona = 0;
}

void CNewVhidRylon::SetVhidNettoRylona(double netto)
{
	if (netto>0)
		m_dVhidNetto = netto;
	else m_dVhidNetto = 0;
}

void CNewVhidRylon::SetVhidBryttoRylona(double brytto)
{
	if (brytto>0)
		m_dVhidBrytto = brytto;
	else m_dVhidBrytto = 0;
}

void CNewVhidRylon::OnBnClickedButtonNewrylonAdd()
{
	CString str;
	m_editNetto.GetWindowText(str);
	
	if (str.GetLength()!=0)
	{
		m_dVhidNetto = atof(str.GetBuffer(str.GetLength()));
		m_editBrytto.GetWindowText(str);
		if (str.GetLength()!=0)
		{
			m_dVhidBrytto = atof(str.GetBuffer(str.GetLength()));
			m_editDlina.GetWindowText(str);
			if (str.GetLength()!=0)
			{
				m_iVhidDlinaRylona = atoi(str.GetBuffer(str.GetLength()));				
				OnOK();
			}
			else MessageBox("Введіть довжину рулону");
		}
		else MessageBox("Введіть брутто рулону");
	}
	else MessageBox("Введіть нетто рулону");
}

void CNewVhidRylon::OnCancel()
{
	// TODO: добавьте специализированный код или вызов базового класса

	//CDialog::OnCancel();
}

void CNewVhidRylon::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса

	CDialog::OnOK();
}
