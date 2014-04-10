// PrintEtiketka.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CPrintEtiketkaApp:
// О реализации данного класса см. PrintEtiketka.cpp
//

class CPrintEtiketkaApp : public CWinApp
{
public:
	CPrintEtiketkaApp();

// Переопределение
	public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CPrintEtiketkaApp theApp;