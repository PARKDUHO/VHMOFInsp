// T4CmdGen.cpp: implementation of the T4CmdGen class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "T2CmdGen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CT2CmdGen::CT2CmdGen()
{
	pbdData.RemoveAll();
	hResol = 0;
	vResol = 0;
}

CT2CmdGen::CT2CmdGen(int h, int v)
{
	pbdData.RemoveAll();
	hResol = h;
	vResol = v;
}

CT2CmdGen::~CT2CmdGen()
{
	
}

int CT2CmdGen::isPatternType(CStringArray* sArray)
{
	int ret=PTN_NORMAL;
	CString stmp;

	stmp = sArray->GetAt(sArray->GetSize()-2);
	if(stmp == _T("0"))
	{
		ret = PTN_UPGRADE;
	}

	// 0:T2  1:T2Upgrade
	return ret;
}

CString CT2CmdGen::makeT2dataStrFromFile(CString pbdFilePath)
{
	CFile mFile;
	CString strPatternPath;

	strPatternPath.Format(_T(".\\Pattern\\Logical\\%s.pdb"), pbdFilePath);

	if( mFile.Open(strPatternPath, CFile::modeRead) == FALSE )
	{
		return _T("");
	}

	WCHAR tmpBuff[4096] = {0};
	mFile.Read((void*)tmpBuff, sizeof(tmpBuff));
	CString tmpStr(tmpBuff);
	mFile.Close();
	return tmpStr;
}


CString CT2CmdGen::makeT2PatternStr(CString dataStr, int width, int height)
{
	CT2CmdGen* pObj = NULL;
	pObj = new CT2CmdGen(width, height);

	CString retStr=_T("");
	int cnt = pObj->makeStringArray(dataStr);
	if( cnt > 0 )
	{
		retStr = pObj->makeObjStr(dataStr);
	}

	delete pObj;
	pObj = NULL;
	return retStr;
}

CString CT2CmdGen::makeObjStr(CString dataStr)
{
	CString retStr=_T("");

	retStr.Format(_T(""));
	for(int i=0; i<pbdData.GetSize(); i++)
	{
		CString tmpStr("");
		tmpStr = pbdData.GetAt(i);
		retStr += makeSubStr(tmpStr, i);
	}

	return retStr;
}

CString CT2CmdGen::makeSubStr(CString dataStr, int idx)
{
	CString retStr("");
	CStringArray dStrAry;
	dStrAry.RemoveAll();

	CString tmpStr(_T(""));
	char szbuff[256]={0,};
	int i=0;
	while(1)
	{
		int oldI = i;
		i = dataStr.Find(_T(","), i) + 1;
		if( i == 0 )
		{
			if( dataStr.GetLength() >= oldI )
			{
				tmpStr = dataStr.Mid(oldI, dataStr.GetLength()-oldI);
				dStrAry.Add(tmpStr);
			}
			break;
		}
		tmpStr = dataStr.Mid(oldI, i-oldI-1);
		dStrAry.Add(tmpStr);
	}
	//////////////////////////////////////////////////////////////////////////
	tmpStr = dStrAry.GetAt(0);

	////////////////////////////////////////////////////////////////////////// TB
	if( tmpStr == "TB" )	// CDrawBitmap
	{
		// Reading
		tmpStr = dStrAry.GetAt(1);
		int m_nIndex = wcstoul(tmpStr, 0, 16);

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
	
		tmpStr = dStrAry.GetAt(3);
		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);
	
		tmpStr = dStrAry.GetAt(5);
		int y2 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(6);
		int m_nFillOpt = _ttoi(tmpStr);

		int m_BitmapSizeX = 0;
		int m_BitmapSizeY = 0;
		CString szBrush("");
		if( m_nIndex == 0xFF )
		{
			tmpStr = dStrAry.GetAt(7);
			m_BitmapSizeX = _ttoi(tmpStr);

			tmpStr = dStrAry.GetAt(8);
			m_BitmapSizeY = _ttoi(tmpStr);

			tmpStr = dStrAry.GetAt(9);
			szBrush = tmpStr;
		}

		int max = m_BitmapSizeX * m_BitmapSizeY;

		CString m_userBrush("");

		m_userBrush = szBrush;

		CString strCode("");
		CString str("");
		CString szBmpPattern("");
		if( m_nIndex == 0xFF)
		{
			szBmpPattern.Format(_T("DB%03d%02X"), m_userBrush.GetLength()+7,m_BitmapSizeX);
			szBmpPattern += m_userBrush;
		}

		str.Format(_T("%02X%04d%04d%04d%04d%01d"),
					m_nIndex,
					x1,
					y1,
					x2,
					y2,
					m_nFillOpt);

		CString szData;
		int n = str.GetLength();

		szData.Format(_T("TB%03d"), n+5);
		szData  += str;
		strCode += szBmpPattern;
		strCode += szData;

		retStr = strCode;
	}
	////////////////////////////////////////////////////////////////////////// TA
	else if( tmpStr == "TA" )	// CDrawCanvasY
	{
		CString strCode("");
		CString str("");
		CString strBuf("");

		// Reading
		int nPTNType=PTN_NORMAL;
		int nCurPos = 1;
		int nTotal  = (int)dStrAry.GetSize();

		int m_yindex = 0;
		int m_xindex = 0;
		int endY = 0;
		int endX = 0;
		int nColorOpt = 0;
		int m_Clr2 = 0;
		CString Gradation("");
		CString BitCtrl;


		nPTNType = isPatternType(&dStrAry);

		while(nCurPos < nTotal)
		{
			if((nCurPos+2) > nTotal)
				break;

			tmpStr = dStrAry.GetAt(nCurPos++);
			m_yindex = _tcstol(tmpStr, 0, 16);

			tmpStr = dStrAry.GetAt(nCurPos++);
			m_xindex = _tcstol(tmpStr, 0, 16);


			if( m_xindex == 0 )
			{
				if((nCurPos + 5) > nTotal )
				{
					break;
				}
				// Reading
				tmpStr = dStrAry.GetAt(nCurPos++);
				endY = (int)String2Float(tmpStr, vResol);

				tmpStr = dStrAry.GetAt(nCurPos++);
				endX = (int)String2Float(tmpStr, hResol);

				tmpStr = dStrAry.GetAt(nCurPos++);
				nColorOpt = _ttoi(tmpStr);

				tmpStr = dStrAry.GetAt(nCurPos++);
				m_Clr2 = _tcstol(tmpStr, 0, 16);

				//////////////////////////////////
				//8k  확장 알고리즘
				m_Clr2 &= 0xFFF0;
				m_Clr2 |= nColorOpt&0x0F;
				////////////////////////////////

				tmpStr = dStrAry.GetAt(nCurPos++);
				Gradation = tmpStr;

				if(nPTNType==PTN_UPGRADE)
				{
					tmpStr= dStrAry.GetAt(nCurPos++);
					BitCtrl = tmpStr;
				}

				str.Format(_T("%04X%04X%s"),
							endX,
							m_Clr2,
							Gradation);

				strBuf += str;

			}
			else if( m_xindex > 0 )
			{
				if((nCurPos + 4) > nTotal )
				{
					break;
				}

				// Reading
				tmpStr = dStrAry.GetAt(nCurPos++);
				endX = (int)String2Float(tmpStr, hResol);

				tmpStr = dStrAry.GetAt(nCurPos++);
				nColorOpt = _ttoi(tmpStr);

				tmpStr = dStrAry.GetAt(nCurPos++);
				m_Clr2 = _tcstol(tmpStr, 0, 16);

				//////////////////////////////////
				//8k  확장 알고리즘
				m_Clr2 &= 0xFFF0;
				m_Clr2 |= nColorOpt&0x0F;
				////////////////////////////////

				tmpStr = dStrAry.GetAt(nCurPos++);
				Gradation = tmpStr;

				if(nPTNType==PTN_UPGRADE)
				{
					tmpStr= dStrAry.GetAt(nCurPos++);
					BitCtrl = tmpStr;
				}

				// Store
				str.Format(_T("%1X%02X%04X%04X%s"),
							m_yindex,m_xindex,
							endX,
							m_Clr2,
							Gradation);
	
				strBuf += str;
			}
		}

		strCode.Format(_T("TA%03d%1X%02X%04d"),strBuf.GetLength()+12,m_yindex,0,endY);
		strCode += strBuf;

		retStr = strCode;
	}
	////////////////////////////////////////////////////////////////////////// BD
	else if( tmpStr == "BD")
	{
		CString str=_T("");

		str.Format(_T("BD%03d%s%s%s%s%s%s"), 21, dStrAry.GetAt(1), dStrAry.GetAt(2), dStrAry.GetAt(3), dStrAry.GetAt(4), dStrAry.GetAt(5), dStrAry.GetAt(6));
		retStr = str;
	}

	////////////////////////////////////////////////////////////////////////// TD
	else if( tmpStr == "TD" )	// CDrawChess
	{
		CString strCode("");
		CString str("");

		tmpStr = dStrAry.GetAt(1);
		int m_nType = wcstoul(tmpStr, 0, 10);

		int m_matrixY = 0;
		int m_matrixX = 0;
		int m_Clr1Opt = 0;
		int m_Clr2Opt = 0;
		CString m_szUser("");
		int m_Width = 0;
		int m_Height = 0;
		int m_clrOpt = 0;
		int m_clr = 0;

		if( m_nType == 1 )
		{
			// Reading..
			tmpStr = dStrAry.GetAt(2);
			m_matrixY = _ttoi(tmpStr);

			tmpStr = dStrAry.GetAt(3);
			m_matrixX = _ttoi(tmpStr);

			tmpStr = dStrAry.GetAt(4);
			m_Clr1Opt = _ttoi(tmpStr);

			tmpStr = dStrAry.GetAt(5);
			m_Clr2Opt = _ttoi(tmpStr);


			// Store..
			str.Format(_T("%01d%02d%02d%01d%01d"), m_nType, m_matrixY, m_matrixX, m_Clr1Opt, m_Clr2Opt);
		}
		else if(m_nType == 2)
		{
			// Reading..
			tmpStr = dStrAry.GetAt(2);
			m_matrixY = _ttoi(tmpStr);

			tmpStr = dStrAry.GetAt(3);
			m_matrixX = _ttoi(tmpStr);

			tmpStr = dStrAry.GetAt(4);
			m_Clr1Opt = _ttoi(tmpStr);

			tmpStr = dStrAry.GetAt(5);
			m_Clr2Opt = _ttoi(tmpStr);

			tmpStr = dStrAry.GetAt(6);
			m_szUser = tmpStr;

		
			// Store..
			CString strHex = Chess2AsciiHex(m_szUser,m_matrixX,m_matrixY);
			str.Format(_T("%01d%02d%02d%01d%01d"),m_nType,m_matrixY,m_matrixX,m_Clr1Opt,m_Clr2Opt);
			str += strHex;
		}
		else if(m_nType == 3)
		{
			// Reading..
			tmpStr = dStrAry.GetAt(2);
			m_matrixY = _ttoi(tmpStr);

			tmpStr = dStrAry.GetAt(3);
			m_matrixX = _ttoi(tmpStr);

			tmpStr = dStrAry.GetAt(4);
			m_Clr1Opt = _ttoi(tmpStr);

			tmpStr = dStrAry.GetAt(5);
			m_Clr2Opt = _ttoi(tmpStr);

			tmpStr = dStrAry.GetAt(6);
			m_Width = (int)String2Float(tmpStr, hResol);

			tmpStr = dStrAry.GetAt(7);
			m_Height = (int)String2Float(tmpStr, vResol);

			tmpStr = dStrAry.GetAt(8);
			m_clrOpt = wcstoul(tmpStr, 0, 16);

			tmpStr = dStrAry.GetAt(9);
			m_clr = wcstoul(tmpStr, 0, 16);		

		
			// Store..
			str.Format(_T("%01d%02d%02d%1d%1d%04d%04d%01X%04X"),
						m_nType,
						m_matrixY,	  m_matrixX,
						m_Clr1Opt,	  m_Clr2Opt,
  						m_Width,		  m_Height,
						m_clrOpt,		  m_clr );
		}

		strCode.Format(_T("TD%03d"),str.GetLength()+5);
		strCode += str;

		retStr = strCode;
	}
	////////////////////////////////////////////////////////////////////////// LC
	else if( tmpStr == "LC" )	// CDrawCircle
	{
		CString str("");

		tmpStr = dStrAry.GetAt(1);
		int m_centerY = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(2);
		int m_centerX = (int)String2Float(tmpStr, hResol);

		int m_halfX = 0;
		tmpStr = dStrAry.GetAt(3);
		if( hResol <= vResol )
		{
			m_halfX = (int)String2Float(tmpStr, hResol);
		}
		else
		{
			m_halfX = (int)String2Float(tmpStr, vResol);
		}

		tmpStr = dStrAry.GetAt(5);
		int m_fillopt = _ttoi(tmpStr);

		str.Format(_T("DC%03d%04d%04d%04dLC%03d%1d"),17,m_centerY,m_centerX,m_halfX,6,m_fillopt);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// TC
	else if( tmpStr == "TC" )	// CDrawCross
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int x1 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(2);
		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(3);
		int x2 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(4);
		int y2 = (int)String2Float(tmpStr, vResol);

		str.Format(_T("%04d%04d%04d%04d%s%s%s%s%s%s%s%s%s"),
					x1,y1,x2,y2,
					dStrAry.GetAt(5),dStrAry.GetAt(6),
					dStrAry.GetAt(7),dStrAry.GetAt(8),dStrAry.GetAt(9),
					dStrAry.GetAt(10),dStrAry.GetAt(11),dStrAry.GetAt(12),
					dStrAry.GetAt(13));
		tmpStr.Format(_T("TC%03d%s"), str.GetLength()+5, str);

		retStr = tmpStr;
	}
	////////////////////////////////////////////////////////////////////////// RH
	else if( tmpStr == "RH" )	// CDrawHRepeat
	{
		CString str("");
		
		tmpStr = dStrAry.GetAt(1);
		int idx = _ttoi(tmpStr);
		
		tmpStr = dStrAry.GetAt(2);
		int y1 = (int)String2Float(tmpStr, vResol);
		
		tmpStr = dStrAry.GetAt(3);
		int x1 = (int)String2Float(tmpStr, hResol);
		
		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);
		
		str.Format(_T("%02d%04d%04d%04d%s%s%s%s%s"),
			idx,
			y1,
			x1,
			x2,
			dStrAry.GetAt(5),	// 반복회수
			dStrAry.GetAt(6),	// 반복간격
			dStrAry.GetAt(7),	// Red Color
			dStrAry.GetAt(8),	// Green Color
			dStrAry.GetAt(9)	// Blue Color
			);
		tmpStr.Format(_T("RH%03d%s"), str.GetLength()+5, str);
		
		retStr = tmpStr;
	}
	////////////////////////////////////////////////////////////////////////// OL
	else if( tmpStr == "OL" )	// CDrawLine
	{
		CString str("");
		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(3);
		int y1 = (int)String2Float(tmpStr, vResol);
		
		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(5);
		int y2 = (int)String2Float(tmpStr, vResol);

		str.Format(_T("OL%03d%04d%04d%04d%04d"),21,x1,y1,x2,y2);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// LH
	else if( tmpStr == "LH" )	// CDrawHLine
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(3);
		int x2 = (int)String2Float(tmpStr, hResol);

#if 1
		// BMP Maker에서는 아래의 조건 사용.
		if(y1 > vResol)		y1 = vResol;
#else
		// T2 PG의 Firmware에 전달할 경우 아래의 조건 사용.
		if(y1 >= vResol)	y1 = vResol-1;
#endif

		str.Format(_T("LH%03d%04d%04d%04d"),17,y1,x1,x2);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// LV
	else if( tmpStr == "LV" )	// CDrawVLine
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);

#if 1
		// BMP Maker에서는 아래의 조건 사용.
		if(x1 > hResol)		x1 = hResol;
#else
		// T2 PG의 Firmware에 전달할 경우 아래의 조건 사용.
		if(x1 >= hResol)	x1 = hResol-1;
#endif

		tmpStr = dStrAry.GetAt(4);
		int m_FillType = _ttoi(tmpStr);

		str.Format(_T("LV%03d%04d%04d%04d%1d"),18,y1,x1,y2,m_FillType);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// LT
	else if( tmpStr == "LT" )	// CDrawTLine
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		
		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);

#if 1
		// BMP Maker에서는 아래의 조건 사용.
		if(y1 > vResol)		y1 = vResol;
		if(x1 > hResol)		x1 = hResol;
		if(y2 > vResol)		y2 = vResol;
		if(x2 > hResol)		x2 = hResol;
#else
		// T2 PG의 Firmware에 전달할 경우 아래의 조건 사용.
		if(y1 >= vResol)	y1 = vResol-1;
		if(x1 >= hResol)	x1 = hResol-1;
		if(y2 >= vResol)	y2 = vResol-1;
		if(x2 >= hResol)	x2 = hResol-1;
#endif

		tmpStr = dStrAry.GetAt(5);
		int m_FillType = _ttoi(tmpStr);

		str.Format(_T("LT%03d%04d%04d%04d%04d%1d"),22,y1,x1,y2,x2,m_FillType);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// LP
	else if( tmpStr == "LP" )	// CDrawPolyGon
	{
		CString str("");
		CString strMsg("");
		tmpStr = dStrAry.GetAt(1);
		int m_count = _ttoi(tmpStr);

		int max = m_count * 2 + 3;

		int ti = 2;

		int minx = 0;
		int maxx = 0;

		for(int i=0; i<m_count; i++)
		{
			tmpStr = dStrAry.GetAt(ti++);
			int m_szVY = (int)String2Float(tmpStr, vResol);
			tmpStr = dStrAry.GetAt(ti++);
			int m_szVX = (int)String2Float(tmpStr, hResol);

			if( i == 0 )
			{
				minx = m_szVX;
				maxx = m_szVX;
			}

			if(minx > m_szVX) minx = m_szVX;
			if(maxx < m_szVX) maxx = m_szVX;

			CString strVectex;
			strVectex.Format(_T("%04d%04d"), m_szVY, m_szVX);
			strMsg += strVectex;
		}

		tmpStr = dStrAry.GetAt(ti++);
		int m_FillType = _ttoi(tmpStr);

		str.Format(_T("LP%03d%04d%s%1d"), strMsg.GetLength()+10, (maxx-minx)/2, strMsg, m_FillType);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// LR
	else if( tmpStr == "LR" )	// CDrawRect
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		
		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);

#if 1
		// BMP Maker에서는 아래의 조건 사용.
		if(y1 > vResol)		y1 = vResol;
		if(x1 > hResol)		x1 = hResol;
		if(y2 > vResol)		y2 = vResol;
		if(x2 > hResol)		x2 = hResol;
#else
		// T2 PG의 Firmware에 전달할 경우 아래의 조건 사용.
		if(y1 >= vResol)	y1 = vResol-1;
		if(x1 >= hResol)	x1 = hResol-1;
		if(y2 >= vResol)	y2 = vResol-1;
		if(x2 >= hResol)	x2 = hResol-1;
#endif


		tmpStr = dStrAry.GetAt(5);
		int m_fillopt = _ttoi(tmpStr);

		str.Format(_T("LR%03d%04d%04d%04d%04d%01d"),22,y1,x1,y2,x2,m_fillopt);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// LW
	else if( tmpStr == "LW" )	// CLine Window
	{
		CString str("");
		int m_opt=0;

		tmpStr = dStrAry.GetAt(1);
		int x1 = (int)String2Float(tmpStr, hResol);
		if(x1 >= hResol)
			x1 = hResol-1;

		tmpStr = dStrAry.GetAt(2);
		int y1 = (int)String2Float(tmpStr, vResol);
		if(y1 >= vResol)
			y1 = vResol-1;

		tmpStr = dStrAry.GetAt(3);
		int x2 = (int)String2Float(tmpStr, hResol);
		if(x2 >= hResol)
			x2 = hResol-1;

		tmpStr = dStrAry.GetAt(4);
		int y2 = (int)String2Float(tmpStr, vResol);
		if(y2 >= vResol)
			y2 = vResol-1;

		if(dStrAry.GetCount()==6)
		{
			tmpStr = dStrAry.GetAt(5);
			m_opt = _ttoi(tmpStr);
		}

		str.Format(_T("LW%03d%04d%04d%04d%04d%01d"),22,x1,y1,x2,y2,m_opt);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// RV
	else if( tmpStr == "RV" )	// CDrawVRepeat
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		
		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);

		//str.Format(_T("RV%03d%04d%04d%04d%04X"),21,y1,x1,y2,repeat);
		str.Format(_T("RV%03d%04d%04d%04d%s"), 21, y1, x1, y2, dStrAry.GetAt(4));

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// BM
	else if( tmpStr == "BM" )	// CDrawXFile
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int x1 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(2);
		int y1 = (int)String2Float(tmpStr, vResol);
		
		tmpStr = dStrAry.GetAt(3);
		int x2 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(4);
		int y2 = (int)String2Float(tmpStr, vResol);

		str.Format(_T("%04d%04d%04d%04d"),x1,y1,x2,y2);
		tmpStr.Format(_T("BM%03d%s"), str.GetLength()+5, str);

		retStr = tmpStr;
	}
	////////////////////////////////////////////////////////////////////////// BS
	else if( tmpStr == "BS" )	// CDrawMyString
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(6);

		str.Format(_T("%04d%04d%04d%04d%s"),y1,x1,y2,x2,tmpStr);
		tmpStr.Format(_T("BS%03d%s"), str.GetLength()+5, str);

		retStr = tmpStr;
	}
	////////////////////////////////////////////////////////////////////////// EV (Expand VLine)
	else if( tmpStr == "EV" )	// CDrawVLine
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);
		if(y1 > vResol)		y1 = vResol;
		else if(y1 < 0)		y1 = 0;
		
		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		if(x1 > hResol)		x1 = hResol-1;
		else if(x1 < 0)		x1 = 0;
		
		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);
		if(y2 > vResol)		y2 = vResol;
		else if(y2 < 0)		y2 = 0;
		
		tmpStr = dStrAry.GetAt(4);
		int m_FillType = _ttoi(tmpStr);
		
		str.Format(_T("%04d%04d%04d%1d%s%s%s"),y1,x1,y2,m_FillType, dStrAry.GetAt(5), dStrAry.GetAt(6), dStrAry.GetAt(7));
		tmpStr.Format(_T("EV%03d%s"), str.GetLength()+5, str);
		
		retStr = tmpStr;
	}
	
	////////////////////////////////////////////////////////////////////////// EH (Expand HLine)
	else if( tmpStr == "EH" )	// CDrawExpandHLine
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);
		if(y1 > vResol)		y1 = vResol;
		else if(y1 < 0)		y1 = 0;
		
		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		if(x1 > hResol)		x1 = hResol;
		else if(x1 < 0)		x1 = 0;
		
		tmpStr = dStrAry.GetAt(3);
		int x2 = (int)String2Float(tmpStr, hResol);
		if(x2 > hResol)		x2 = hResol-1;
		else if(x2 < 0)		x2 = 0;

		str.Format(_T("%04d%04d%04d%s%s%s"),y1,x1,x2,dStrAry.GetAt(4),dStrAry.GetAt(5),dStrAry.GetAt(6));
		tmpStr.Format(_T("EH%03d%s"), str.GetLength()+5, str);
		
		retStr = tmpStr;
	}
	////////////////////////////////////////////////////////////////////////// ER (Expand Rect)
	else if( tmpStr == "ER" )	// CDrawExpandRect
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);
		if(y1 >= vResol)
			y1 = vResol-1;
		
		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		if(x1 >= hResol)
			x1 = hResol-1;
		
		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);
		if(y2 >= vResol)
			y2 = vResol-1;
		
		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);
		if(x2 >= hResol)
			x2 = hResol-1;
		
		tmpStr = dStrAry.GetAt(5);
		int m_fillopt = _ttoi(tmpStr);
		
		str.Format(_T("%04d%04d%04d%04d%01d%s%s%s"),y1,x1,y2,x2,m_fillopt,dStrAry.GetAt(6),dStrAry.GetAt(7),dStrAry.GetAt(8));
		tmpStr.Format(_T("ER%03d%s"), str.GetLength()+5, str);
		
		retStr = tmpStr;
	}
	////////////////////////////////////////////////////////////////////////// CI (Calibration Pattern, AMI+CIC)
	else if( tmpStr == "CI" )	// Calibration Information, AMI+CIC
	{
		CString str("");

		if(dStrAry.GetCount() < 14)	return _T("");

		tmpStr = dStrAry.GetAt(1);
		WORD y0_start	= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(2);
		WORD y0_end		= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(3);
		WORD y1_start	= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(4);
		WORD y1_end		= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(5);
		WORD y2_start	= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(6);
		WORD y2_end		= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(7);
		WORD y3_start	= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(8);
		WORD y3_end		= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(9);
		WORD x_start	= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(10);
		WORD x_end		= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(11);
		WORD box_width	= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(12);
		WORD box_height	= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(13);
		WORD x_gap		= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(14);
		WORD y_gap		= _ttoi(tmpStr);


		str.Format(_T("%04X%04X%04X%04X%04X%04X%04X%04X%04X%04X%04X%04X%04X%04X"), y0_start, y1_start, y2_start, y3_start, y0_end, y1_end, y2_end, y3_end, x_start, x_end, box_width, box_height, x_gap, y_gap);
		tmpStr.Format(_T("CI%03d%s"), str.GetLength()+5, str);

		retStr = tmpStr;
	}
	////////////////////////////////////////////////////////////////////////// CV (Calibration Vertical Line Pattern, AMI+CIC)
	else if( tmpStr == "CV" )	// Calibration Vertical Line Draw, AMI+CIC
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int x_start	= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(2);
		int y_start	= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(3);
		int y_end	= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(4);
		int width	= _ttoi(tmpStr);

		str.Format(_T("%04d%04d%04d%04d"), x_start, y_start, y_end, width);
		tmpStr.Format(_T("CV%03d%s"), str.GetLength()+5, str);

		retStr = tmpStr;
	}
	////////////////////////////////////////////////////////////////////////// CV (Calibration Horizontal Line Pattern, AMI+CIC)
	else if( tmpStr == "CH" )	// Calibration Horizontal Line Draw, AMI+CIC
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int x_start	= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(2);
		int y_start	= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(3);
		int x_end	= _ttoi(tmpStr);

		tmpStr = dStrAry.GetAt(4);
		int width	= _ttoi(tmpStr);

		str.Format(_T("%04d%04d%04d%04d"), x_start, y_start, x_end, width);
		tmpStr.Format(_T("CH%03d%s"), str.GetLength()+5, str);

		retStr = tmpStr;
	}
	////////////////////////////////////////////////////////////////////////// BM
	else if( tmpStr == "IS" )	// BMP Index
	{
		CString str("");
		CString strCode("");

		str = dStrAry.GetAt(1);

		tmpStr = dStrAry.GetAt(2);
		int idx = _ttoi(tmpStr);

		strCode.Format(_T("IS%03d%s%02d"),5, str,idx);	// IS Command는 Data의 길이를 5로 고정하여 전송.

		retStr = strCode;
	}
	else if( tmpStr == "CD" )	// Color Description
	{
		CString str("");
		str.Format(_T("CD%s%s%s%s%s%s%s%s%s%s%s%s"), dStrAry.GetAt(1), dStrAry.GetAt(2), dStrAry.GetAt(3),
													dStrAry.GetAt(4), dStrAry.GetAt(5), dStrAry.GetAt(6),
													dStrAry.GetAt(7), dStrAry.GetAt(8), dStrAry.GetAt(9),
													dStrAry.GetAt(10), dStrAry.GetAt(11), dStrAry.GetAt(12));
		retStr = str;
	}
	else if( tmpStr == "CLN" )	// Line Color
	{
		CString str("");
		str.Format(_T("CLN%s%s%s"), dStrAry.GetAt(1), dStrAry.GetAt(2), dStrAry.GetAt(3));
		retStr = str;
	}
	else if( tmpStr == "CBT" )	// Bitmap Color
	{
		CString str("");
		str.Format(_T("CBT%s%s%s"), dStrAry.GetAt(1), dStrAry.GetAt(2), dStrAry.GetAt(3));
		retStr = str;
	}
	else if( tmpStr == "CFG" )	// FG Color
	{
		CString str("");
		str.Format(_T("CFG%s%s%s"), dStrAry.GetAt(1), dStrAry.GetAt(2), dStrAry.GetAt(3));
		retStr = str;
	}
	else if( tmpStr == "CBG" )	// BG Color
	{
		CString str("");
		str.Format(_T("CBG%s%s%s"), dStrAry.GetAt(1), dStrAry.GetAt(2), dStrAry.GetAt(3));
		retStr = str;
	}
	else if( tmpStr == "SH" )	// H Scroll
	{
		CString str("");
		int nstep1=0,nDirction=0,nResolution=0,interval=0, mode=0, step=1, surfacePosition=0, tmp=0;

		nstep1=(int)_ttoi(dStrAry.GetAt(1));

		nDirction=(int)_ttoi(dStrAry.GetAt(2));

		tmpStr = dStrAry.GetAt(3);
		nResolution = (int)String2Float(tmpStr, hResol);

		interval=(int)_ttoi(dStrAry.GetAt(4));

		mode=(int)_ttoi(dStrAry.GetAt(5));

		step=(int)_ttoi(dStrAry.GetAt(6));
		if(step < 1)		step = 1;
		else if(step > 255)	step = 255;

		tmpStr = dStrAry.GetAt(7);
		tmp = _ttoi(tmpStr.Left(tmpStr.GetLength()-1));
		if(tmp == 0)		tmpStr.Format(_T("1%%"));
		else if(tmp > 50)	tmpStr.Format(_T("50%%"));

		if(nDirction == 0)
		{
			surfacePosition = (int)String2Float(tmpStr, hResol);
		}
		else
		{	
			int position = _ttoi(tmpStr.Left(tmpStr.GetLength()-1));
			tmpStr.Format(_T("%d%%"), (100-position));
			surfacePosition = (int)String2Float(tmpStr, hResol);
		}

		if(mode == 1)// full line이면 shape도 면으로 된 패턴 파일이라도 line으로 바까준다.
		{
			if(nstep1 == 0)	nstep1=1;
		}
		str.Format(_T("SH%01d%01d%04d%03d%01d%03d%04d"),nstep1,nDirction, nResolution,interval, mode, step, surfacePosition);//면이냐 라인이냐, 좌에서우냐 우에서 좌냐, active영역, interval
		retStr=str;
	}
	else if( tmpStr == "SV" )	// V Scroll
	{
		CString str("");
		int nstep1=0,nDirction=0,nResolution=0,interval=0, mode=0, step=1, surfacePosition=0, tmp=0;

		nstep1=(int)_ttoi(dStrAry.GetAt(1));

		nDirction=(int)_ttoi(dStrAry.GetAt(2));

		tmpStr = dStrAry.GetAt(3);
		nResolution = (int)String2Float(tmpStr, vResol);

		interval=(int)_ttoi(dStrAry.GetAt(4));

		mode=(int)_ttoi(dStrAry.GetAt(5));

		step=(int)_ttoi(dStrAry.GetAt(6));

		if(step < 1)		step = 1;
		else if(step > 255)	step = 255;

		tmpStr = dStrAry.GetAt(7);
		tmp = _ttoi(tmpStr.Left(tmpStr.GetLength()-1));
		if(tmp == 0)		tmpStr.Format(_T("1%%"));
		else if(tmp > 50)	tmpStr.Format(_T("50%%"));

		if(nDirction == 0)
		{
			surfacePosition = (int)String2Float(tmpStr, vResol);
		}
		else
		{	
			int position = _ttoi(tmpStr.Left(tmpStr.GetLength()-1));
			tmpStr.Format(_T("%d%%"), (100-position));
			surfacePosition = (int)String2Float(tmpStr, vResol);
		}

		if(mode == 1)// full line이면 shape도 면으로 된 패턴 파일이라도 line으로 바까준다.
		{
			if(nstep1 == 0)	nstep1=1;
		}

		str.Format(_T("SV%01d%01d%04d%03d%01d%03d%04d"),nstep1,nDirction, nResolution,interval, mode, step, surfacePosition);//면이냐 라인이냐, 상에서하냐 하에서 상이냐, active영역, interval
		retStr=str;
	}
	else if (tmpStr == "CP")	//AMI Calibration Defect Position drawing
	{
		CString str("");

		int figure = (int)_ttoi(dStrAry.GetAt(1));

		int fontUse = (int)_ttoi(dStrAry.GetAt(2));

		int hor = (int)_ttoi(dStrAry.GetAt(3));

		int ver = (int)_ttoi(dStrAry.GetAt(4));

		str.Format(_T("CP%03d%02d%01d%04d%04d%s%s%s"), 28, figure, fontUse, hor, ver, dStrAry.GetAt(5), dStrAry.GetAt(6), dStrAry.GetAt(7));

		retStr = str;
	}
	return retStr;
}

int CT2CmdGen::makeStringArray(CString dataStr)
{
	CString tmpStr("");
	int i=0;
	while(1)
	{
		int oldI = i;
		i = dataStr.Find(_T("\n"), i) + 1;
		if( i == 0 )
		{
			if( dataStr.GetLength() > oldI )
			{
				if(dataStr.GetAt(dataStr.GetLength()) == _T(','))
				{
					tmpStr = dataStr.Mid(oldI, dataStr.GetLength()-oldI-1);
				}
				else
				{
					tmpStr = dataStr.Mid(oldI, dataStr.GetLength()-oldI);
				}
				pbdData.Add(tmpStr);
			}
			break;
		}
		tmpStr = dataStr.Mid(oldI, i-oldI-1);
		pbdData.Add(tmpStr);
	}
	return (int)pbdData.GetSize();
}

double CT2CmdGen::String2Float(LPCTSTR pStrNum,int base)
{
	CString strNum(pStrNum);
	int nNumber = 0;

	strNum.TrimLeft();
	strNum.TrimRight();

	CString strReturn("");
	CString strValue("");

	BOOL bfraction = FALSE;
	BOOL bPoint = FALSE;
	double eReturn = 0.0;

	for(int i=0; i<strNum.GetLength(); i++)
	{
		TCHAR ch = strNum[i];

		if( isdigit(ch) )
		{
			strValue += ch;	
		}
		else if( ch == '%' )
		{
			CString pText = strValue;
			double value = 0.0;
			if(bPoint)
			{
				value = _tcstod(pText, NULL);
			}
			else
			{
				value = _ttoi(pText);
			}

			eReturn += (base * value * 0.01);
			bPoint = FALSE;
			strValue = "";
		}
		else if( ch == '/' )
		{
			bfraction = TRUE;
			strValue += ch;
		}
		else if( ch == '.' )
		{
			bPoint = TRUE;
			strValue += ch;
		}
		else if( ch == '+' )
		{
			if( strValue.IsEmpty() )
			{
				strValue = '+';
				continue;
			}

			CString pText = strValue;
			double value = 0.0;

			if( bfraction )
			{
				double numerator = 0.0;
				double denominator = 0.0;

				int nIdx = strValue.Find('/');
				CString strNumerator	= strValue.Left(nIdx);
				CString strDenominator	= strValue.Right(strValue.GetLength() - (nIdx+1));

				numerator	= _tcstod(strNumerator, NULL);
				denominator = _tcstod(strDenominator, NULL);	
				denominator = (denominator == 0.0) ? 1.0 : denominator;	// 0.0인경우.

				value = ( base * 1.0 / denominator * numerator);
			}
			else if(bPoint)
			{
				value = _tcstod(pText, NULL);
			}
			else
			{
				value = _tcstod(pText, NULL);
			}

			eReturn += value;
			bPoint = FALSE;
			bfraction = FALSE;
			strValue = "";
			strValue = '+';
		}
		else if(ch == '-')
		{	
			if(strValue.IsEmpty())
			{
				strValue = '-';
				continue;
			}
			
			CString pText = strValue;
			double value = 0.0;

			if(bfraction)
			{
				double numerator	= 0.0;
				double denominator	= 0.0;

				int nIdx = strValue.Find('/');
				CString strNumerator	= strValue.Left(nIdx);
				CString strDenominator	= strValue.Right(strValue.GetLength() - (nIdx+1));

				numerator	= _tcstod(strNumerator, NULL);
				denominator = _tcstod(strDenominator, NULL);	
				denominator = (denominator == 0.0) ? 1.0 : denominator;	// 0.0인경우.

				value = ( base * 1.0 / denominator * numerator);
			}
			else if(bPoint)  value = _tcstod(pText, NULL);
			else			 value = _ttoi(pText);

			eReturn += value;
			bPoint		= FALSE;
			bfraction	= FALSE;
			strValue = "";
			strValue = '-';
		}
	}	

	if(!strValue.IsEmpty())
	{

		CString pText = strValue;
		double   value = 0.0;

		if(bfraction)
		{
			double numerator	= 0.0;
			double denominator	= 0.0;

			int nIdx = strValue.Find('/');
			CString strNumerator	= strValue.Left(nIdx);
			CString strDenominator	= strValue.Right(strValue.GetLength() - (nIdx+1));

			numerator	= _tcstod(strNumerator, NULL);
			denominator = _tcstod(strDenominator, NULL);	
			denominator = (denominator == 0.0) ? 1.0 : denominator;	// 0.0인경우.

			value = ( base * 1.0 / denominator * numerator);
		}
		else if(bPoint)  value = _tcstod(pText, NULL);
		else			 value = _ttoi(pText);

		eReturn += value;
		bPoint		= FALSE;
		bfraction	= FALSE;
		strValue = "";
	}

	return eReturn;
}
	
CString CT2CmdGen::Chess2AsciiHex(CString& szBits,int x, int y)
{
	CString strChess("");
	
	if(x == 16)
	{
		strChess  = szBits;
	}
	else
	{
		CString strArray[16];
		int yi;
		
		for(yi = 0  ;  yi < y ; yi++)
		{
			//잘라내기.
			strArray[yi] = szBits.Mid(yi*x,x);
			
			unsigned short uHex = 0;
			for(int xi = 0 ; xi < strArray[yi].GetLength() ; xi++)
			{
				if(strArray[yi].GetAt(xi) == '1')
					uHex |= (0x1 << (15-xi));
			}

			strArray[yi].Format(_T("%04X"),uHex);
		}

		for(yi = 0 ; yi < y ; yi++)
		{
			strChess += strArray[yi];
		}

	}

	return strChess;
}

/////////////////////////////////////////////////////////////////////////////
CString CT2CmdGen::makeT2FileStr(CString dataStr)
{
	CT2CmdGen* pObj = NULL;
	pObj = new CT2CmdGen;
	
	CString retStr("");
	int cnt = pObj->makeStringArray(dataStr);
	if( cnt > 0 )
	{
		retStr = pObj->makeFieldStr(dataStr);
	}
	
	delete pObj;
	pObj = NULL;
	return retStr;
}

CString CT2CmdGen::makeFieldStr(CString dataStr)
{
	CString retStr("");
	CString tmpStr("");
	CString parStr("");
	
	for(int nline=0; nline<pbdData.GetSize(); nline++)
	{
		tmpStr = pbdData.GetAt(nline);
		
		int oldI=0, i=0;
		i = tmpStr.Find(_T(","), i) + 1;

		if( i == 0 )
		{
			if( tmpStr.GetLength() > oldI )
			{
				parStr = tmpStr.Mid(oldI, tmpStr.GetLength()-oldI);
			}
		}
		else
		{
			parStr = dataStr.Mid(oldI, i-oldI-1);
			
			if( parStr != "NAME" )
			{
				retStr += tmpStr.Left(tmpStr.GetLength()-1);
			}
		}
	}
	
	return retStr;

}

