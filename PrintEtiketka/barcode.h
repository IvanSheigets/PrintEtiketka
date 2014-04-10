

#ifndef Barcode_h_djdfkjdjkfgjgjghdhdhdgdgfgfgfgeue
#define Barcode_h_djdfkjdjkfgjgjghdhdhdgdgfgfgfgeue


class Barcode39;


class BarcodeBase
{
public:
	BarcodeBase()
	{
		Clear();
		i_Ratio=3;
	}

	void operator=(const BarcodeBase&bc)
	{
		i_LenBuf=bc.i_LenBuf;
		i_Ratio	=bc.i_Ratio;
		memcpy(ia_Buf,bc.ia_Buf,sizeof(ia_Buf));
	}

	void Clear()
	{
		memset(ia_Buf,0,sizeof(ia_Buf));
		i_LenBuf=0;
	}

	int GetEncodeLength()	const
	{
		BYTE*pb=(BYTE*)ia_Buf;
		int i,iLen=0;
		for(i=0;i<i_LenBuf;i++)
		{
			//wide is 3
			if(*pb&2)	iLen+=(i_Ratio-1);
			pb++;
		}
		return iLen+i_LenBuf;
	}
	int GetBufferLength()	const
	{
		return i_LenBuf;
	}
	const BYTE&GetAt(int i)	const 
	{
		return ia_Buf[i];
	}
	int GetRatio()	const
	{
		return i_Ratio;
	}
	int SetRatio(int iRatio)
	{
		i_Ratio=iRatio;
		if(i_Ratio<=0)	i_Ratio=1;
	}
	void DrawBarcode(HDC hDC,int iX,int iY0,int iY10,int iY11,const COLORREF clrBar,const COLORREF clrSpace,const int iPenW, CString strCode/*, CString strProductName, CString strDate*/)
	{
		HPEN hPenBar	=::CreatePen(PS_SOLID,iPenW,clrBar);
		HPEN hPenSpace	=::CreatePen(PS_SOLID,iPenW,clrSpace);

		HPEN hPenOld=(HPEN)::SelectObject(hDC,hPenBar);

		BYTE*pb=ia_Buf;
		int i0,iNum0=i_LenBuf;

		int x1 = iX;
		int x2 = iX;
		
		BYTE bBar;
		int i1,iNum1;
		int iY;
		for(i0=0;i0<iNum0;i0++)
		{
			bBar	=*pb&0x01;
			iNum1	=(*pb&0x02)?i_Ratio:1;
			iY		=(*pb&0x04)?iY11:iY10;
			for(i1=0;i1<iNum1;i1++)
			{
				if(bBar)	::SelectObject(hDC,hPenBar);
				else		::SelectObject(hDC,hPenSpace);
				
				::MoveToEx(hDC,iX,iY0,0);
				::LineTo(hDC,iX,iY);
				iX+=iPenW;
			}
			pb++;
		}
		x1  = x1 + (iNum0/2 -  strCode.GetLength()/2);
		int ff = iX/2 - ((strCode.GetLength()/2)*9);

		::TextOut(hDC,ff,iY+5,strCode,strCode.GetLength());

		LOGFONT		log;

		log.lfHeight = 20; 
		log.lfWidth = 10;
		log.lfEscapement = 0;   
		log.lfOrientation = 0;   
		log.lfWeight = FW_NORMAL;   
		log.lfItalic =  false;
		log.lfUnderline = false;   
		log.lfStrikeOut = 0;   
		log.lfCharSet = ANSI_CHARSET;
		log.lfOutPrecision = OUT_DEFAULT_PRECIS;   
		log.lfClipPrecision = CLIP_DEFAULT_PRECIS;   
		log.lfQuality = DEFAULT_QUALITY;
		log.lfPitchAndFamily = DEFAULT_PITCH || FF_ROMAN;   
		strcpy (log.lfFaceName,"Times New Roman");
		CFont  m_fnt;
		m_fnt.CreateFontIndirect (&log);

		::SelectObject(hDC,m_fnt);

		//::TextOut(hDC,x2,iY+40,strProductName,strProductName.GetLength());

		//::TextOut(hDC,x2,iY+60,strDate,strDate.GetLength());
		

		::SelectObject(hDC,hPenOld);

		::DeleteObject(hPenBar);
		::DeleteObject(hPenSpace);
	}

protected:
	BYTE	ia_Buf[4096];
	int		i_LenBuf;

	int		i_Ratio;

	struct IntString
	{
		int ch;
		char*psz;
	};

};

class Barcode39:public BarcodeBase
{
	//[n/a][n/a][n/a][n/a][n/a][n/a][w-n][b-s]
public:
	Barcode39()
	{
	}
	~Barcode39()
	{
	}

	BOOL Encode39(const char*pszCodeIn)
	{
		int iLen=strlen(pszCodeIn);

		char*pszCode=new char[iLen+3];
		sprintf(pszCode,"*%s*",pszCodeIn);
		strupr(pszCode);

		BYTE*pFst=ia_Buf;
		BYTE*p0=pFst,*p1;

		iLen+=2;
		int i;
		for(i=0;i<iLen;i++)
		{
			p1=P_GetNarrowWideBarSpace39(pszCode[i],p0);
			if(p1==0)	return 0;
			p0=p1;
		}
		i_LenBuf=p1-pFst;
		delete []pszCode;
		return 1;
	}

	void Draw39(HDC hDC,int iX,int iY0,int iY1,const COLORREF clrBar,const COLORREF clrSpace,const int iPenW,CString strCode, CString strProductName, CString strDate)
	{
		DrawBarcode(hDC,iX,iY0,iY1,iY1,clrBar,clrSpace,iPenW,strCode/*, strProductName, strDate*/);
	}

private:
	BYTE*P_GetNarrowWideBarSpace39(char ch,BYTE*pb)
	{
		IntString infs[]=
		{
			{'1',	"wnnwnnnnwn"},
			{'2',	"nnwwnnnnwn"},
			{'3',	"wnwwnnnnnn"},
			{'4',	"nnnwwnnnwn"},
			{'5',	"wnnwwnnnnn"},
			{'6',	"nnwwwnnnnn"},
			{'7',	"nnnwnnwnwn"},
			{'8',	"wnnwnnwnnn"},
			{'9',	"nnwwnnwnnn"},
			{'0',	"nnnwwnwnnn"},
			{'A',	"wnnnnwnnwn"},
			{'B',	"nnwnnwnnwn"},
			{'C',	"wnwnnwnnnn"},
			{'D',	"nnnnwwnnwn"},
			{'E',	"wnnnwwnnnn"},
			{'F',	"nnwnwwnnnn"},
			{'G',	"nnnnnwwnwn"},
			{'H',	"wnnnnwwnnn"},
			{'I',	"nnwnnwwnnn"},
			{'J',	"nnnnwwwnnn"},
			{'K',	"wnnnnnnwwn"},
			{'L',	"nnwnnnnwwn"},
			{'M',	"wnwnnnnwnn"},
			{'N',	"nnnnwnnwwn"},
			{'O',	"wnnnwnnwnn"},
			{'P',	"nnwnwnnwnn"},
			{'Q',	"nnnnnnwwwn"},
			{'R',	"wnnnnnwwnn"},
			{'S',	"nnwnnnwwnn"},
			{'T',	"nnnnwnwwnn"},
			{'U',	"wwnnnnnnwn"},
			{'V',	"nwwnnnnnwn"},
			{'W',	"wwwnnnnnnn"},
			{'X',	"nwnnwnnnwn"},
			{'Y',	"wwnnwnnnnn"},
			{'Z',	"nwwnwnnnnn"},
			{'-',	"nwnnnnwnwn"},
			{'.',	"wwnnnnwnnn"},
			{' ',	"nwwnnnwnnn"},
			{'*',	"nwnnwnwnnn"},
			{'$',	"nwnwnwnnnn"},
			{'/',	"nwnwnnnwnn"},
			{'+',	"nwnnnwnwnn"},
			{'%',	"nnnwnwnwnn"},
		};
		
		int i0,iNum0=sizeof(infs)/sizeof(infs[0]);
		int i1;
		for(i0=0;i0<iNum0;i0++)
		{
			IntString&inf=infs[i0];
			if(inf.ch==ch)
			{
				for(i1=0;i1<10;i1++)
				{
					if(inf.psz[i1]=='w')	*pb+=2;
					if(i1%2==0)			*pb+=1;
					pb++;
				}
				return pb;
			}
		}
		return 0;
	}
};

//=============================================


#endif
