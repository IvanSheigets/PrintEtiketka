// Settings.cpp: файл реализации
//

#include "stdafx.h"
#include "PrintEtiketka.h"
#include "Settings.h"


// диалоговое окно CSettings

IMPLEMENT_DYNAMIC(CSettings, CDialog)

CSettings::CSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CSettings::IDD, pParent)
{

}

CSettings::~CSettings()
{
}

void CSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_comboComPort);
	DDX_Control(pDX, IDC_COMBO_COMPORT_BITS, m_comboBits);
	DDX_Control(pDX, IDC_COMBO_COMPORT_SPEED, m_comboSpeed);
	DDX_Control(pDX, IDC_COMBO_COMPORT_CHETNOST, m_comboChet);
	DDX_Control(pDX, IDC_COMBO_COMPORT_STOPBITS, m_comboStopBits);
	DDX_Control(pDX, IDC_EDIT_SETTINGS_ADDRSERVER, m_editAddrServer);
	DDX_Control(pDX, IDC_EDIT_SETTINGS_LOGIN, m_editLogin);
	DDX_Control(pDX, IDC_EDIT_SETTING_PASSWORD, m_editPassword);
}


BEGIN_MESSAGE_MAP(CSettings, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS_PRINTRTIKETOK, &CSettings::OnBnClickedButtonSettingsPrintrtiketok)
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS_PRINTSHTRIH, &CSettings::OnBnClickedButtonSettingsPrintshtrih)
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS_PRINTZVIT, &CSettings::OnBnClickedButtonSettingsPrintzvit)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CSettings::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// обработчики сообщений CSettings

BOOL CSettings::OnInitDialog()
{
	CDialog::OnInitDialog();


	HANDLE hFile;
	CString str,str2;
	int i=1;
	do {
		str.Format("COM%d",i);
		hFile = CreateFile("COM2",GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		m_comboComPort.InsertString(i-1,str);
		i++;
	}while (hFile!=INVALID_HANDLE_VALUE);

	m_statPrintEtiket.Create("",WS_CHILD|WS_VISIBLE,CRect(300,60,540,80),this,170001);
	m_statPrintShtrih.Create("",WS_CHILD|WS_VISIBLE,CRect(300,115,540,130),this,170002);
	m_statPrintZvit.Create("",WS_CHILD|WS_VISIBLE,CRect(300,170,540,185),this,170002);
	
	file = fopen("settings.txt","rb");
	if (file!=NULL)
	{
		char buf[1024];
		while (fgets(buf,1000,file)!='\0')
		{
			str.Format("%s",buf);
			str.Remove('\n');
			if (str.Left(str.Find(" "))=="port")
			{
				for (int i=0;i<m_comboComPort.GetCount();i++)
				{
					m_comboComPort.GetLBText(i,str2);
					if (str2==str.Mid(str.Find(" ")+3))
						m_comboComPort.SetCurSel(i);
				}
			}
			else if (str.Left(str.Find(" "))=="speed")
			{
				for (int i=0;i<m_comboSpeed.GetCount();i++)
				{
					m_comboSpeed.GetLBText(i,str2);
					if (Speed(str.Mid(str.Find(" ")+3))==str2)
						m_comboSpeed.SetCurSel(i);
				}

			}
			else if (str.Left(str.Find(" "))=="bits")
			{
				for (int i=0;i<m_comboBits.GetCount();i++)
				{
					m_comboBits.GetLBText(i,str2);
					if (str2==str.Mid(str.Find(" ")+3))
						m_comboBits.SetCurSel(i);
				}
			}
			else if (str.Left(str.Find(" "))=="chet")
			{
				for (int i=0;i<m_comboChet.GetCount();i++)
				{
					m_comboChet.GetLBText(i,str2);
					if (Chet(str.Mid(str.Find(" ")+3))==str2)
						m_comboChet.SetCurSel(i);
				}
			}
			else if (str.Left(str.Find(" "))=="stopbits")
			{
				for (int i=0;i<m_comboStopBits.GetCount();i++)
				{
					m_comboStopBits.GetLBText(i,str2);
					if (StopBits(str.Mid(str.Find(" ")+3))==str2)
						m_comboStopBits.SetCurSel(i);
				}
			}
			else if (str.Left(str.Find(" "))=="server_addr")
				m_editAddrServer.SetWindowText(str.Mid(str.Find(" ")+3));
			else if (str.Left(str.Find(" "))=="login")
				m_editLogin.SetWindowText(str.Mid(str.Find(" ")+3));
			else if (str.Left(str.Find(" "))=="password")
				m_editPassword.SetWindowText(str.Mid(str.Find(" ")+3));
			else if (str.Left(str.Find(" "))=="printEtik")
				m_statPrintEtiket.SetWindowText(str.Mid(str.Find(" ")+3));
			else if (str.Left(str.Find(" "))=="printShtih")
				m_statPrintShtrih.SetWindowText(str.Mid(str.Find(" ")+3));
			else if (str.Left(str.Find(" "))=="printZvit")
				m_statPrintZvit.SetWindowText(str.Mid(str.Find(" ")+3));
			
		}
		fclose(file);
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

CString CSettings::Speed(CString speed)
{
	if (speed=="CBR_110")
		return "110";
	else if (speed=="CBR_300")
		return "300";
	else if (speed=="CBR_600")
		return "600";
	else if (speed=="CBR_1200")
		return "1200";
	else if (speed=="CBR_2400")
		return "2400";
	else if (speed=="CBR_4800")
		return "4800";
	else if (speed=="CBR_9600")
		return "9600";
	else if (speed=="CBR_14400")
		return "14400";
	else if (speed=="CBR_19200")
		return "19200";
	else if (speed=="CBR_38400")
		return "38400";
	else if (speed=="CBR_57600")
		return "57600";
	else if (speed=="CBR_115200")
		return "115200";
	else if (speed=="CBR_256000")
		return "256000";
}

CString CSettings::Chet(CString chet)
{
	if (chet=="EVENPARITY")
		return "Чет";
	else if (chet=="ODDPARITY")
		return "Нечет";
	else if (chet=="NOPARITY")
		return "Нет";
	else if (chet=="MARKPARITY")
		return "Маркер";
	else if (chet=="SPACEPARITY")
		return "Пробел";
}

CString CSettings::StopBits(CString stop)
{
	if (stop=="ONESTOPBIT")
		return "1";
	else if (stop=="ONE5STOPBITS")
		return "1,5";
	else if (stop=="TWOSTOPBITS")
		return "2";
}

void CSettings::OnBnClickedButtonSettingsPrintrtiketok()
{
	CPrintDialog pr(FALSE);
	if (pr.DoModal()==IDOK)
		m_statPrintEtiket.SetWindowText(pr.GetDeviceName());
}

void CSettings::OnBnClickedButtonSettingsPrintshtrih()
{
	CPrintDialog pr(FALSE);
	if (pr.DoModal()==IDOK)
		m_statPrintShtrih.SetWindowText(pr.GetDeviceName());
}

void CSettings::OnBnClickedButtonSettingsPrintzvit()
{
	CPrintDialog pr(FALSE);
	if (pr.DoModal()==IDOK)
		m_statPrintZvit.SetWindowText(pr.GetDeviceName());
}

void CSettings::OnBnClickedButtonSave()
{
	CString str;
	file = fopen("settings.txt","wb");
	fputs("[COMPORT]\n",file);

	if (m_comboComPort.GetCurSel()!=-1)
	{
		m_comboComPort.GetLBText(m_comboComPort.GetCurSel(),str);
		fputs("port = ",file);
		fputs(str+'\n',file);
	}

	if (m_comboSpeed.GetCurSel()!=-1)
	{
		m_comboSpeed.GetLBText(m_comboSpeed.GetCurSel(),str);

		if (str=="110")
			str = "CBR_110";
		else if (str=="300")
			str = "CBR_300";
		else if (str=="600")
			str = "CBR_600";
		else if (str=="1200")
			str = "CBR_1200";
		else if (str=="2400")
			str = "CBR_2400";
		else if (str=="4800")
			str = "CBR_4800";
		else if (str=="9600")
			str = "CBR_9600";
		else if (str=="14400")
			str = "CBR_14400";
		else if (str=="19200")
			str = "CBR_19200";
		else if (str=="38400")
			str = "CBR_38400";
		else if (str=="57600")
			str = "CBR_57600";
		else if (str=="115200")
			str = "CBR_115200";
		else if (str=="256000")
			str = "CBR_256000";
		fputs("speed = ",file);
		fputs(str+'\n',file);
	}

	if (m_comboBits.GetCurSel()!=-1)
	{
		m_comboBits.GetLBText(m_comboBits.GetCurSel(),str);
		fputs("bits = ",file);
		fputs(str+'\n',file);
	}

	if (m_comboChet.GetCurSel()!=-1)
	{
		m_comboChet.GetLBText(m_comboChet.GetCurSel(),str);
		if (str=="Чет")
			str="EVENPARITY";
		else if (str=="Нечет")
			str="ODDPARITY";
		else if (str=="Нет")
			str="NOPARITY";
		else if (str=="Маркер")
			str="MARKPARITY";
		else if (str=="Пробел")
			str="SPACEPARITY";
		fputs("chet = ",file);
		fputs(str+'\n',file);
	}

	if (m_comboStopBits.GetCurSel()!=-1)
	{
		m_comboStopBits.GetLBText(m_comboStopBits.GetCurSel(),str);
		if (str=="1")
			str="ONESTOPBIT";
		else if (str=="1,5")
			str="ONE5STOPBITS";
		else if (str=="2")
			str="TWOSTOPBITS";
		fputs("stopbits = ",file);
		fputs(str+'\n',file);
	}

	fputs("\n[SERVER]\n",file);

	m_editAddrServer.GetWindowText(str);
	fputs("server_addr = ",file);
	if (str.GetLength()!=0)
		fputs(str+'\n',file);
	else fputs("127.0.0.1\n",file);

	m_editLogin.GetWindowText(str);
	fputs("login = ",file);
	if (str.GetLength()!=0)
		fputs(str+'\n',file);
	else fputs("\n",file);

	m_editPassword.GetWindowText(str);
	fputs("password = ",file);
	if (str.GetLength()!=0)
		fputs(str+'\n',file);
	else fputs("\n",file);

	fputs("\n[PRINTERS]\n",file);

	fputs("printEtik = ",file);
	m_statPrintEtiket.GetWindowText(str);
	if (str.GetLength()!=0)
		fputs(str+'\n',file);
	else fputs("\n",file);

	fputs("printShtih = ",file);
	m_statPrintShtrih.GetWindowText(str);
	if (str.GetLength()!=0)
		fputs(str+'\n',file);
	else fputs("\n",file);

	fputs("printZvit = ",file);
	m_statPrintZvit.GetWindowText(str);
	if (str.GetLength()!=0)
		fputs(str+'\n',file);
	else fputs("\n",file);


	fclose(file);	

	OnOK();
}
