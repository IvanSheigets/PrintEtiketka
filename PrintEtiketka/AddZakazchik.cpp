// AddZakazchik.cpp: файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "AddZakazchik.h"


// диалоговое окно CAddZakazchik

IMPLEMENT_DYNAMIC(CAddZakazchik, CDialog)

CAddZakazchik::CAddZakazchik(CWnd* pParent /*=NULL*/)
	: CDialog(CAddZakazchik::IDD, pParent)
{

}

CAddZakazchik::~CAddZakazchik()
{
}

void CAddZakazchik::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_myButOk);
	DDX_Control(pDX, IDC_EDIT_ADDZAKAZCHIK_ADD, m_editAdd);
}


BEGIN_MESSAGE_MAP(CAddZakazchik, CDialog)
	ON_BN_CLICKED(IDOK, &CAddZakazchik::OnBnClickedOk)
//	ON_WM_PAINT()
ON_EN_CHANGE(IDC_EDIT_ADDZAKAZCHIK_ADD, &CAddZakazchik::OnEnChangeEditAddzakazchikAdd)
END_MESSAGE_MAP()


// обработчики сообщений CAddZakazchik

BOOL CAddZakazchik::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	GetClientRect(&rect);
	m_myStatName.SetTextColor(BLUE_TEXT);
	m_myStatName.SetFont(20);
	m_myStatName.Create(m_strName,WS_VISIBLE|WS_CHILD,CRect(rect.left+10,rect.top+10,rect.right-10,30),this,152047);
	m_editAdd.SetLimitText(40);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CAddZakazchik::OnBnClickedOk()
{
	m_editAdd.GetWindowText(m_strData);
	if (m_strData.GetLength()<=0)
		MessageBox("Введіть значення");
	else 
	{
		if (m_strData.Find("'")!=-1)
			m_strData.Replace("'","");

		if (m_strData.Find('"')!=-1)
			m_strData.Replace("\"","");

		m_strData.MakeUpper().Trim();
		//MessageBox(m_strData);
		/*m_strData.MakeLower();
		m_strData.Right(m_strData.GetLength()-1);
		ss.Format("%s%s",s,m_strData.Right(m_strData.GetLength()-1));
		m_strData = ss;*/
		OnOK();
	}
}

void CAddZakazchik::SetName(CString name)
{
	m_strName = name;
}

CString CAddZakazchik::GetData()
{
	return m_strData;
}

void CAddZakazchik::OnEnChangeEditAddzakazchikAdd()
{
	if (m_strName=="Додати нову вагу тари:")
	{
		CString str;
		m_editAdd.GetWindowText(str);
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
					m_editAdd.SetWindowText(str);
				}
				else if (str.GetLength()==2 && strcmp(str.Left(1),"0")==0 &&(strcmp(str.Right(1),",")!=0 &&strcmp(str.Right(1),".")!=0))
				{
					MessageBox("Некоректний ввід");
					str = "";
					m_editAdd.SetWindowText(str);
				}
				else if (strcmp(str.Right(1),",")==0 || strcmp(str.Right(1),".")==0)
				{
					if (c1>=1)
					{
						MessageBox("Некоректний ввід");
						str = "";
						m_editAdd.SetWindowText(str);
						c1=0;
					}else c1++;		
				}
				else 
				{
								
				}
			}
			else
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_editAdd.SetWindowText(str);

			}
			if (str.Find(',')!=-1)
				str.Replace(',','.');
		}	
	}
	else if (m_strName=="Додати нову ширину:")
	{
		CString str;
		m_editAdd.GetWindowText(str);
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
				|| strcmp(str.Right(1),"9")==0)
			{
								
			}
			else
			{
				MessageBox("Некоректний ввід");
				str = "";
				m_editAdd.SetWindowText(str);

			}
		}	
	}
}
