// ChooseRegim.cpp: файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "ChooseRegim.h"


// диалоговое окно CChooseRegim

IMPLEMENT_DYNAMIC(CChooseRegim, CDialog)

CChooseRegim::CChooseRegim(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseRegim::IDD, pParent)
{
	m_hAccel = LoadAccelerators( AfxGetResourceHandle(), MAKEINTRESOURCE( IDR_WORK_ACCELERATOR ) );
	regim = 0;
}

CChooseRegim::~CChooseRegim()
{
}

void CChooseRegim::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_NUMBER_CAR, m_comboNumberCar);
	DDX_Control(pDX, IDC_COMBO_NUMBER_SMENA, m_comboNumberSmena);
}


BEGIN_MESSAGE_MAP(CChooseRegim, CDialog)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_ENTER, &CChooseRegim::OnBnClickedButtonEnter)
	ON_BN_CLICKED(IDC_BUTTON_ZVITY, &CChooseRegim::OnBnClickedButtonZvity)
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS, &CChooseRegim::OnBnClickedButtonSettings)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CChooseRegim::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDCANCEL, &CChooseRegim::OnBnClickedCancel)
END_MESSAGE_MAP()


// обработчики сообщений CChooseRegim

void CChooseRegim::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	CRect rect;
	GetClientRect(&rect);

	int x1 = x/2 - rect.right/2;
	int x2 = rect.right;

	int y1=y/2-rect.bottom/2;
	int y2=rect.bottom;

	MoveWindow(x1,y1,x2,y2);

}

HBRUSH CChooseRegim::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Вернуть другое значение дескриптора кисти, если оно не определено по умолчанию
	//hbr = m_colorDialog;
	return hbr;
}

BOOL CChooseRegim::OnInitDialog()
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

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CChooseRegim::OnBnClickedButtonEnter()
{	
	if (m_comboNumberCar.GetCurSel()!=-1)
	{
		if (m_comboNumberSmena.GetCurSel()!=-1)
		{
			regim = 1;
			CString strTemp;
			m_comboNumberCar.GetLBText(m_comboNumberCar.GetCurSel(),strTemp);
			m_iNumberCar = atoi(strTemp.GetBuffer(strTemp.GetLength()));
			m_comboNumberSmena.GetLBText(m_comboNumberSmena.GetCurSel(),strTemp);
			m_iNumberSmena = atoi(strTemp.GetBuffer(strTemp.GetLength()));
			OnOK();
		}
		else MessageBox("Виберіть номер зміни!!!");
	}else MessageBox("Виберіть номер машини!!!");
}

void CChooseRegim::OnBnClickedButtonZvity()
{
	regim = 2;
	OnOK();
}

void CChooseRegim::OnBnClickedButtonSettings()
{
	regim = 3;
	OnOK();
}

void CChooseRegim::OnBnClickedButtonExit()
{
	regim = 4;
	OnOK();
}

void CChooseRegim::OnBnClickedCancel()
{
	// Запрет на нажатие ESC
	//OnCancel();
}

BOOL CChooseRegim::PreTranslateMessage(MSG* pMsg)
{
	if ( TranslateAccelerator( m_hWnd, m_hAccel, pMsg ) ) return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}
