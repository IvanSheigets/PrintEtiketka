// PrintEtiketka.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CPrintEtiketkaApp:
// � ���������� ������� ������ ��. PrintEtiketka.cpp
//

class CPrintEtiketkaApp : public CWinApp
{
public:
	CPrintEtiketkaApp();

// ���������������
	public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CPrintEtiketkaApp theApp;