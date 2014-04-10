// ChooseRegim2.cpp: файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "ChooseRegim2.h"


// диалоговое окно CChooseRegim2

IMPLEMENT_DYNAMIC(CChooseRegim2, CDialog)

CChooseRegim2::CChooseRegim2(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseRegim2::IDD, pParent),m_iNumberCar(0),m_iNumberSmena(0)
{

}

CChooseRegim2::~CChooseRegim2()
{
}

void CChooseRegim2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_NUMBER_CAR2, m_comboNumCar);
	DDX_Control(pDX, IDC_COMBO_NUMBER_SMENA2, m_comboNumSmena);
}


BEGIN_MESSAGE_MAP(CChooseRegim2, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CChooseRegim2::OnBnClickedButtonChange)
	ON_CBN_SELCHANGE(IDC_COMBO_NUMBER_SMENA2, &CChooseRegim2::OnCbnSelchangeComboNumberSmena2)
END_MESSAGE_MAP()


// обработчики сообщений CChooseRegim2

void CChooseRegim2::OnBnClickedButtonChange()
{
	if (m_comboNumCar.GetCurSel()!=-1)
	{
		if (m_comboNumSmena.GetCurSel()!=-1)
		{
			//regim = 1;
			CString strTemp;
			m_comboNumCar.GetLBText(m_comboNumCar.GetCurSel(),strTemp);
			m_iNumberCar = atoi(strTemp.GetBuffer(strTemp.GetLength()));
			m_comboNumSmena.GetLBText(m_comboNumSmena.GetCurSel(),strTemp);
			m_iNumberSmena = atoi(strTemp.GetBuffer(strTemp.GetLength()));
			OnOK();
		}
		else MessageBox("Виберіть номер зміни!!!");
	}else MessageBox("Виберіть номер машини!!!");
}

BOOL CChooseRegim2::OnInitDialog()
{
	CDialog::OnInitDialog();

	COLORREF colBkColor = RGB(235, 235, 235);
	COLORREF colTextColor = RGB(0 ,0, 139);

	m_statNumberCar.SetTextColor(colTextColor);
	m_statNumberCar.SetFont(18);
	m_statNumberCar.Create("Номер машини",WS_CHILD|WS_VISIBLE,CRect(25,30,150,50),this,1000);

	m_statNumberSmena.SetBkColor(colBkColor);
	m_statNumberSmena.SetTextColor(colTextColor);
	m_statNumberSmena.SetFont(18);
	m_statNumberSmena.Create("Номер зміни",WS_CHILD|WS_VISIBLE,CRect(25,65,150,90),this,1000);

	CString strCar;
	strCar.Format("%d",m_iNumberCar);
	for (int i=0;i<m_comboNumCar.GetCount();i++)
	{
		CString str;
		m_comboNumCar.GetLBText(i,str);
		if (str == strCar)
		{
			m_comboNumCar.SetCurSel(i);
			break;
		}
	}

	CString strSmena;
	strSmena.Format("%d",m_iNumberSmena);
	for (int i=0;i<m_comboNumSmena.GetCount();i++)
	{
		CString str;
		m_comboNumSmena.GetLBText(i,str);
		if (str == strSmena)
		{
			m_comboNumSmena.SetCurSel(i);
			break;
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CChooseRegim2::SetCar(int car)
{
	m_iNumberCar = car;
}

void CChooseRegim2::SetSmena(int smena)
{
	m_iNumberSmena = smena;
}

void CChooseRegim2::OnCancel()
{
	// TODO: добавьте специализированный код или вызов базового класса

	//CDialog::OnCancel();
}

void CChooseRegim2::OnCbnSelchangeComboNumberSmena2()
{
	// TODO: добавьте свой код обработчика уведомлений
}
