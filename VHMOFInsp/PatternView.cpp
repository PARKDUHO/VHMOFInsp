// PatternView.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "T2CmdGen.h"

#include "PatternView.h"

// CPatternView

IMPLEMENT_DYNAMIC(CPatternView, CWnd)

CPatternView::CPatternView()
{
	m_pDC = NULL;
}

CPatternView::~CPatternView()
{
	if(m_pDC != NULL)
		ReleaseDC(m_pDC);
}


BEGIN_MESSAGE_MAP(CPatternView, CWnd)
END_MESSAGE_MAP()



// CPatternView 메시지 처리기입니다.

void CPatternView::InitPatternRect(CDC* pDC, CRect lcdArea, CRect viewArea)
{
	m_pDC		= pDC;			// DC Point
	m_lcdArea	= lcdArea;		// LCD Resolution
	m_frameRect	= viewArea;		// Preview Rect Area
}

void CPatternView::InitPatternPath(CString spath)
{
	m_pathPatternLogical = spath;
}

void CPatternView::InitBmpPatternPath(CString spath)
{
	m_pathPatternBMP = spath;
}

double CPatternView::getZoomH()
{
	return (double)((double)m_frameRect.Width() / (double)m_lcdArea.Width());
}

double CPatternView::getZoomV()
{
	return (double)((double)m_frameRect.Height() / (double)m_lcdArea.Height());
}

void CPatternView::drawPattern(CString ptnName)
{
	CString fullpath;
	CString strTmp;

	fullpath.Format(_T("%s\\%s.pdb"), m_pathPatternLogical, ptnName);

	strTmp = CT2CmdGen::makeT2dataStrFromFile(ptnName);
	strTmp = CT2CmdGen::makeT2PatternStr(strTmp, 1920, 1080);

	drawPrevPattern(strTmp);
}

void CPatternView::drawPatternBmp(CString bmpName)
{
	HANDLE bmp;
	CBitmap cBitmap;
	BITMAP bmpinfo;
	CDC memdc;
	CString fullpath;

	fullpath.Format(_T("%s\\%s"), m_pathPatternBMP, bmpName);
	bmp = LoadImage(NULL, fullpath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	cBitmap.Attach(bmp);
	cBitmap.GetBitmap(&bmpinfo);
	memdc.CreateCompatibleDC(m_pDC);
	memdc.SelectObject(bmp);
	//m_pDC->BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);
	// 만약에 크기를 고정 시키고 싶다면 StretchBit를 사용
	m_pDC->StretchBlt(m_frameRect.left,m_frameRect.top,m_frameRect.Width(),m_frameRect.Height(),&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,SRCCOPY);
	memdc.DeleteDC();
	cBitmap.DeleteObject();
}

void CPatternView::drawPrevPattern(CString ptnString)
{
	setColorBackGround(ptnString);
	setColorForeGround(ptnString);
	setColorLine(ptnString);
	setColorBitmap(ptnString);
	setLineWindow(ptnString);

	// Pattern 미리보기를 그린다.
	drawCanvas(ptnString);			// Layer-1 Canvas
	drawBitmap(ptnString);			// Layer-1 Bitmap
	drawChess(ptnString);			// Layer-1 Chess
	drawCircle(ptnString);			// Layer-2 Line
	drawRect(ptnString);			// Layer-2 Line
	drawExRect(ptnString);			// Layer-2 Line
	drawHLine(ptnString);			// Layer-2 Line
	drawExHLine(ptnString);			// Layer-2 Line
	drawHRepeat(ptnString);			// Layer-2 Line
	drawVLine(ptnString);			// Layer-2 Line
	drawExVLine(ptnString);			// Layer-2 Line
	drawVRepeat(ptnString);			// Layer-2 Line
	drawTLine(ptnString);			// Layer-2 Line
	drawMarker(ptnString);			// Layer-2 Line
	drawCharacter(ptnString);		// Layer-3 Character
}

void CPatternView::setColorBackGround(CString ptnString)
{
	int ipos;
	BYTE red,green,blue;

	m_cbgColor = RGB(0, 0, 0);
	ipos = ptnString.Find(_T("CBG"),0);

	if(ipos != -1)
	{
		red		= (BYTE)_tcstol(ptnString.Mid(ipos+3, 2), NULL, 16);
		green	= (BYTE)_tcstol(ptnString.Mid(ipos+7, 2), NULL, 16);
		blue	= (BYTE)_tcstol(ptnString.Mid(ipos+11, 2), NULL, 16);
		m_cbgColor = RGB(red, green, blue);
	}
}

void CPatternView::setColorForeGround(CString ptnString)
{
	int ipos;
	BYTE red,green,blue;

	m_cfgColor = RGB(0, 0, 0);
	ipos = ptnString.Find(_T("CFG"),0);

	if(ipos != -1)
	{
		red		= (BYTE)_tcstol(ptnString.Mid(ipos+3, 2), NULL, 16);
		green	= (BYTE)_tcstol(ptnString.Mid(ipos+7, 2), NULL, 16);
		blue	= (BYTE)_tcstol(ptnString.Mid(ipos+11, 2), NULL, 16);
		m_cfgColor = RGB(red, green, blue);
	}
}

void CPatternView::setColorLine(CString ptnString)
{
	int ipos;
	BYTE red,green,blue;

	m_clnColor = RGB(0, 0, 0);
	ipos = ptnString.Find(_T("CLN"),0);

	if(ipos != -1)
	{
		red		= (BYTE)_tcstol(ptnString.Mid(ipos+3, 2), NULL, 16);
		green	= (BYTE)_tcstol(ptnString.Mid(ipos+7, 2), NULL, 16);
		blue	= (BYTE)_tcstol(ptnString.Mid(ipos+11, 2), NULL, 16);
		m_clnColor = RGB(red, green, blue);
	}
}

void CPatternView::setColorBitmap(CString ptnString)
{
	int ipos;
	BYTE red,green,blue;

	m_cbtColor = RGB(0, 0, 0);
	ipos = ptnString.Find(_T("CBT"),0);

	if(ipos != -1)
	{
		red		= (BYTE)_tcstol(ptnString.Mid(ipos+3, 2), NULL, 16);
		green	= (BYTE)_tcstol(ptnString.Mid(ipos+7, 2), NULL, 16);
		blue	= (BYTE)_tcstol(ptnString.Mid(ipos+11, 2), NULL, 16);
		m_cbtColor = RGB(red, green, blue);
	}
}

void CPatternView::setLineWindow(CString ptnString)
{
	int ipos;
	RECT rc;

	ZeroMemory(&m_lineWindow, sizeof(m_lineWindow));
	ipos = ptnString.Find(_T("LW"),0);
	if(ipos != -1)
	{
		rc.left		= _ttoi(ptnString.Mid(ipos+5, 4));
		rc.top		= _ttoi(ptnString.Mid(ipos+9, 4));
		rc.right	= _ttoi(ptnString.Mid(ipos+13, 4));
		rc.bottom	= _ttoi(ptnString.Mid(ipos+17, 4));

		m_lineWindow = rc;
	}
}

void CPatternView::drawCanvas(CString ptnString)
{
	CString tastring;
	int m_xIndex, m_pretop=0, m_preleft=0;
	int ipos, m_length, m_istart=0;

	while(1)
	{
		CRect rect;
		int nptr=0;

		ipos = ptnString.Find(_T("TA"),m_istart);
		if(ipos == -1)	break;

		m_length = _ttoi(ptnString.Mid(ipos+2, 3));
		m_istart = ipos + m_length;
		tastring = ptnString.Mid(ipos+5, m_length-5);

		while(nptr < tastring.GetLength())
		{
			COLORREF sColor;
			int gradation;

			m_xIndex = _tcstol(tastring.Mid(nptr+1, 2), NULL, 16);

			if(m_xIndex==0)
			{
				rect.left	= 0;
				rect.top	= m_pretop;
				rect.bottom	= _ttoi(tastring.Mid(3, 4));
				rect.right	= _tcstol(tastring.Mid(7, 4), NULL, 16);
				m_pretop	= rect.bottom;
				m_preleft	= rect.right;

				sColor		= drawCanvas_getColor(tastring.Mid(11,4));
				gradation	= drawCanvas_getGradation(tastring.Mid(15,2));

				drawCanvas_Draw(rect, sColor, gradation);

				nptr += 17;
			}
 			else
 			{
				rect.left	= m_preleft;
				rect.right	= _tcstol(tastring.Mid(nptr+4,3), NULL, 16);
				m_preleft	= rect.right;

				sColor		= drawCanvas_getColor(tastring.Mid(nptr+7,4));
				gradation	= drawCanvas_getGradation(tastring.Mid(nptr+11,2));

				drawCanvas_Draw(rect, sColor, gradation);
 
				nptr += 13;
 			}
		}
	}
}

void CPatternView::drawCanvas_Draw(CRect rc, COLORREF sClr, int m_nGradation)
{
	CRect rect;
	CBrush Brush;
	COLORREF eClr;

	eClr = RGB(0,0,0);

	rect.left	= (LONG)(m_frameRect.left + round((double)rc.left * getZoomH()));
	rect.right	= (LONG)(m_frameRect.left + round((double)rc.right * getZoomH()));
	rect.top	= (LONG)(m_frameRect.top + round((double)rc.top * getZoomV()));
	rect.bottom	= (LONG)(m_frameRect.top + round((double)rc.bottom * getZoomV()));

	if(m_nGradation == EGRADATION_HP)		drawCanvas_HGradient(m_pDC,rect,eClr,sClr);
	else if(m_nGradation == EGRADATION_HM)	drawCanvas_HGradient(m_pDC,rect,sClr,eClr);
	else if(m_nGradation == EGRADATION_VP)  drawCanvas_VGradient(m_pDC,rect,eClr,sClr);
	else if(m_nGradation == EGRADATION_VM)	drawCanvas_VGradient(m_pDC,rect,sClr,eClr);
	else if(m_nGradation == EGRADATION_D1)  drawCanvas_HVGradient(m_pDC,rect,eClr,sClr,m_nGradation);
	else if(m_nGradation == EGRADATION_D2)  drawCanvas_HVGradient(m_pDC,rect,sClr,eClr,m_nGradation);
	else if(m_nGradation == EGRADATION_D3)  drawCanvas_HVGradient(m_pDC,rect,eClr,sClr,m_nGradation);
	else if(m_nGradation == EGRADATION_D4)	drawCanvas_HVGradient(m_pDC,rect,sClr,eClr,m_nGradation);
	else if(m_nGradation == EGRADATION_D5)	drawCanvas_HVGradient(m_pDC,rect,eClr,sClr,m_nGradation);
	else if(m_nGradation == EGRADATION_D6)	drawCanvas_HVGradient(m_pDC,rect,sClr,eClr,m_nGradation);
	else if(m_nGradation == EGRADATION_D7)	drawCanvas_HVGradient(m_pDC,rect,eClr,sClr,m_nGradation);
	else if(m_nGradation == EGRADATION_D8)	drawCanvas_HVGradient(m_pDC,rect,sClr,eClr,m_nGradation);
	else 
	{
		Brush.CreateSolidBrush(sClr);
		m_pDC->FillRect(rect, &Brush);
		Brush.DeleteObject();
	}
}


COLORREF CPatternView::drawCanvas_getColor(CString clrstr)
{
	TCHAR clr_index;
	COLORREF ret_color=RGB(0,0,0);

	if(clrstr.GetLength()==0)	return RGB(0,0,0);

	clr_index = clrstr.GetAt(3);

	int tmp;
	tmp = _tcstol(clrstr.Mid(0,2), NULL, 16);

	if(clr_index==_T('0'))		ret_color = RGB(0, 0, 0);
	if(clr_index==_T('1'))		ret_color = RGB(tmp, 0, 0);
	if(clr_index==_T('2'))		ret_color = RGB(0, tmp, 0);
	if(clr_index==_T('3'))		ret_color = RGB(tmp, tmp, 0);
	if(clr_index==_T('4'))		ret_color = RGB(0, 0, tmp);
	if(clr_index==_T('5'))		ret_color = RGB(tmp, 0, tmp);
	if(clr_index==_T('6'))		ret_color = RGB(0, tmp, tmp);
	if(clr_index==_T('7'))		ret_color = RGB(tmp, tmp, tmp);
	if(clr_index==_T('8'))		ret_color = m_cbgColor;
	if(clr_index==_T('9'))		ret_color = m_cfgColor;

	return ret_color;
}

int CPatternView::drawCanvas_getGradation(CString grastr)
{
	if(grastr==_T("NO"))	return EGRADATION_NO;
	if(grastr==_T("H+"))	return EGRADATION_HP;
	if(grastr==_T("H-"))	return EGRADATION_HM;
	if(grastr==_T("V+"))	return EGRADATION_VP;
	if(grastr==_T("V-"))	return EGRADATION_VM;
	if(grastr==_T("D1"))	return EGRADATION_D1;
	if(grastr==_T("D2"))	return EGRADATION_D2;
	if(grastr==_T("D3"))	return EGRADATION_D3;
	if(grastr==_T("D4"))	return EGRADATION_D4;
	if(grastr==_T("D5"))	return EGRADATION_D5;
	if(grastr==_T("D6"))	return EGRADATION_D6;
	if(grastr==_T("D7"))	return EGRADATION_D7;
	if(grastr==_T("D8"))	return EGRADATION_D8;

	return EGRADATION_NO;
}

void CPatternView::drawCanvas_HGradient(CDC* dc,const CRect& rect, COLORREF sColor,COLORREF eColor)
{
	TRIVERTEX vert[2];
	GRADIENT_RECT grt;

	vert[0].x = rect.left;
	vert[0].y = rect.top;

	vert[0].Red		= GetRValue(sColor)<< 8;
	vert[0].Green	= GetGValue(sColor)<< 8;
	vert[0].Blue	= GetBValue(sColor)<< 8;
	vert[0].Alpha   = 0;

	vert[1].x = rect.right;
	vert[1].y = rect.bottom;

	vert[1].Red		= GetRValue(eColor) <<8;
	vert[1].Green	= GetGValue(eColor) <<8;
	vert[1].Blue	= GetBValue(eColor) <<8;
	vert[1].Alpha   = 0;
	grt.LowerRight = 0;
	grt.UpperLeft  = 1;
	dc->GradientFill(vert,2,&grt,1,GRADIENT_FILL_RECT_H);

}

void CPatternView::drawCanvas_VGradient(CDC* dc,const CRect& rect, COLORREF sColor,COLORREF eColor)
{
	TRIVERTEX vert[2];
	GRADIENT_RECT grt;

	vert[0].x = rect.left;
	vert[0].y = rect.top;

	vert[0].Red		= GetRValue(sColor)<< 8;
	vert[0].Green	= GetGValue(sColor)<< 8;
	vert[0].Blue	= GetBValue(sColor)<< 8;
	vert[0].Alpha   = 0;

	vert[1].x = rect.right;
	vert[1].y = rect.bottom;

	vert[1].Red		= GetRValue(eColor) <<8;
	vert[1].Green	= GetGValue(eColor) <<8;
	vert[1].Blue	= GetBValue(eColor) <<8;
	vert[1].Alpha   = 0;

	grt.LowerRight = 0;
	grt.UpperLeft  = 1;
	dc->GradientFill(vert,2,&grt,1,GRADIENT_FILL_RECT_V);

}


void CPatternView::drawCanvas_HVGradient(CDC* dc,const CRect& rect, COLORREF sColor,COLORREF eColor,UINT nOrder)
{

	TRIVERTEX        vert[4] ;
	GRADIENT_TRIANGLE gTri[2];
	int i = 0;

	if((nOrder == EGRADATION_D1) || (nOrder == EGRADATION_D2))
	{
		CRect rc(rect);
		if( (GetRValue(eColor) == 0x0000) &&
			(GetGValue(eColor) == 0x0000) &&
			(GetBValue(eColor) == 0x0000))
		{
			rc.left  = rect.right;
			rc.right = rect.left;

			vert[0].x		=  rect.left;
			vert[0].y		=  rect.top;
			vert[0].Red		=  GetRValue(eColor)<< 8;
			vert[0].Green	=  GetGValue(eColor)<< 8;
			vert[0].Blue	=  GetBValue(eColor)<< 8;
			vert[0].Alpha	=  0;

			vert[1] .x       =  rect.right;
			vert[1] .y       =  rect.top;
			vert[1] .Red     =  GetRValue(eColor)<< 8;
			vert[1] .Green   =  GetGValue(eColor)<< 8;
			vert[1] .Blue    =  GetBValue(eColor)<< 8;
			vert[1] .Alpha   =  0;

			vert[2] .x       =  rect.left;
			vert[2] .y       =  rect.bottom; 
			vert[2] .Red     =  GetRValue(sColor) <<8;
			vert[2] .Green   =  GetGValue(sColor) <<8;
			vert[2] .Blue    =  GetBValue(sColor) <<8;
			vert[2] .Alpha   =  0;

			vert[3] .x       =  rect.right;
			vert[3] .y       =  rect.bottom;
			vert[3] .Red     =  GetRValue(eColor)<< 8;
			vert[3] .Green   =  GetGValue(eColor)<< 8;
			vert[3] .Blue    =  GetBValue(eColor)<< 8;
			vert[3] .Alpha   =  0x0000;

			gTri[0].Vertex1   = 0;
			gTri[0].Vertex2   = 1;
			gTri[0].Vertex3   = 2;

			gTri[1].Vertex1   = 1;
			gTri[1].Vertex2   = 2;
			gTri[1].Vertex3   = 3;
		}
		else
		{
			vert[0].x		=  rect.left;
			vert[0].y		=  rect.top;
			vert[0].Red		=  GetRValue(sColor)<< 8;
			vert[0].Green	=  GetGValue(sColor)<< 8;
			vert[0].Blue	=  GetBValue(sColor)<< 8;
			vert[0].Alpha	=  0;

			vert[1] .x       =  rect.right;
			vert[1] .y       =  rect.top;
			vert[1] .Red     =  GetRValue(sColor)<< 8;
			vert[1] .Green   =  GetGValue(sColor)<< 8;
			vert[1] .Blue    =  GetBValue(sColor)<< 8;
			vert[1].Alpha	=  0;

			vert[2] .x       =  rect.right;
			vert[2] .y       =  rect.bottom; 
			vert[2] .Red     =  GetRValue(eColor) <<8;
			vert[2] .Green   =  GetGValue(eColor) <<8;
			vert[2] .Blue    =  GetBValue(eColor) <<8;
			vert[2] .Alpha   =  0;

			vert[3] .x       =  rect.left;
			vert[3] .y       =  rect.bottom;
			vert[3] .Red     =  GetRValue(sColor)<< 8;
			vert[3] .Green   =  GetGValue(sColor)<< 8;
			vert[3] .Blue    =  GetBValue(sColor)<< 8;
			vert[3] .Alpha   =  0x0000;

			gTri[0].Vertex1   = 0;
			gTri[0].Vertex2   = 1;
			gTri[0].Vertex3   = 2;

			gTri[1].Vertex1   = 0;
			gTri[1].Vertex2   = 3;
			gTri[1].Vertex3   = 2;
		}

	}
	else if((nOrder == EGRADATION_D3) || (nOrder == EGRADATION_D4))
	{
		if( (GetRValue(eColor) == 0x0000) &&
			(GetGValue(eColor) == 0x0000) &&
			(GetBValue(eColor) == 0x0000))
		{
			//1사분면
			vert[0].x		=  rect.left;
			vert[0].y		=  rect.top;
			vert[0].Red		=  GetRValue(sColor)<< 8;
			vert[0].Green	=  GetGValue(sColor)<< 8;
			vert[0].Blue	=  GetBValue(sColor)<< 8;
			vert[0].Alpha	=  0;

			vert[1] .x       =  rect.right;
			vert[1] .y       =  rect.top;
			vert[1] .Red     =  GetRValue(eColor)<< 8;
			vert[1] .Green   =  GetGValue(eColor)<< 8;
			vert[1] .Blue    =  GetBValue(eColor)<< 8;
			vert[1] .Alpha   =  0;

			vert[2] .x       =  rect.left;
			vert[2] .y       =  rect.bottom; 
			vert[2] .Red     =  GetRValue(eColor) <<8;
			vert[2] .Green   =  GetGValue(eColor) <<8;
			vert[2] .Blue    =  GetBValue(eColor) <<8;
			vert[2] .Alpha   =  0;

			vert[3] .x       =  rect.right;
			vert[3] .y       =  rect.bottom;
			vert[3] .Red     =  GetRValue(eColor)<< 8;
			vert[3] .Green   =  GetGValue(eColor)<< 8;
			vert[3] .Blue    =  GetBValue(eColor)<< 8;
			vert[3] .Alpha   =  0x0000;

			gTri[0].Vertex1   = 0;
			gTri[0].Vertex2   = 1;
			gTri[0].Vertex3   = 3;

			gTri[1].Vertex1   = 0;
			gTri[1].Vertex2   = 2;
			gTri[1].Vertex3   = 3;
		}
		else
		{
			vert[0].x		=  rect.left;
			vert[0].y		=  rect.top;
			vert[0].Red		=  GetRValue(sColor)<< 8;
			vert[0].Green	=  GetGValue(sColor)<< 8;
			vert[0].Blue	=  GetBValue(sColor)<< 8;
			vert[0].Alpha	=  0;

			vert[1] .x       =  rect.right;
			vert[1] .y       =  rect.top;
			vert[1] .Red     =  GetRValue(eColor)<< 8;
			vert[1] .Green   =  GetGValue(eColor)<< 8;
			vert[1] .Blue    =  GetBValue(eColor)<< 8;
			vert[1].Alpha	=  0;

			vert[2] .x       =  rect.right;
			vert[2] .y       =  rect.bottom; 
			vert[2] .Red     =  GetRValue(sColor) <<8;
			vert[2] .Green   =  GetGValue(sColor) <<8;
			vert[2] .Blue    =  GetBValue(sColor) <<8;
			vert[2] .Alpha   =  0;

			vert[3] .x       =  rect.left;
			vert[3] .y       =  rect.bottom;
			vert[3] .Red     =  GetRValue(sColor)<< 8;
			vert[3] .Green   =  GetGValue(sColor)<< 8;
			vert[3] .Blue    =  GetBValue(sColor)<< 8;
			vert[3] .Alpha   =  0x0000;

			gTri[0].Vertex1   = 0;
			gTri[0].Vertex2   = 1;
			gTri[0].Vertex3   = 3;

			gTri[1].Vertex1   = 2;
			gTri[1].Vertex2   = 1;
			gTri[1].Vertex3   = 3;
		}
	}
	if(nOrder == EGRADATION_D5)
	{
		CRect rc(rect);

		rc.left  = rect.right;
		rc.right = rect.left;

		vert[0].x		=  rect.left;
		vert[0].y		=  rect.top;
		vert[0].Red		=  GetRValue(eColor)<< 8;
		vert[0].Green	=  GetGValue(eColor)<< 8;
		vert[0].Blue	=  GetBValue(eColor)<< 8;
		vert[0].Alpha	=  0;

		vert[1] .x       =  rect.right;
		vert[1] .y       =  rect.top;
		vert[1] .Red     =  GetRValue(eColor)<< 8;
		vert[1] .Green   =  GetGValue(eColor)<< 8;
		vert[1] .Blue    =  GetBValue(eColor)<< 8;
		vert[1] .Alpha   =  0;

		vert[2] .x       =  rect.left;
		vert[2] .y       =  rect.bottom; 
		vert[2] .Red     =  GetRValue(eColor) <<8;
		vert[2] .Green   =  GetGValue(eColor) <<8;
		vert[2] .Blue    =  GetBValue(eColor) <<8;
		vert[2] .Alpha   =  0;

		vert[3] .x       =  rect.right;
		vert[3] .y       =  rect.bottom;
		vert[3] .Red     =  GetRValue(sColor)<< 8;
		vert[3] .Green   =  GetGValue(sColor)<< 8;
		vert[3] .Blue    =  GetBValue(sColor)<< 8;
		vert[3] .Alpha   =  0x0000;

		gTri[0].Vertex1   = 0;
		gTri[0].Vertex2   = 1;
		gTri[0].Vertex3   = 3;

		gTri[1].Vertex1   = 0;
		gTri[1].Vertex2   = 2;
		gTri[1].Vertex3   = 3;
	}
	else if(nOrder == EGRADATION_D6)
	{
		vert[0].x		=  rect.left;
		vert[0].y		=  rect.top;
		vert[0].Red		=  GetRValue(sColor)<< 8;
		vert[0].Green	=  GetGValue(sColor)<< 8;
		vert[0].Blue	=  GetBValue(sColor)<< 8;
		vert[0].Alpha	=  0;

		vert[1] .x       =  rect.right;
		vert[1] .y       =  rect.top;
		vert[1] .Red     =  GetRValue(sColor)<< 8;
		vert[1] .Green   =  GetGValue(sColor)<< 8;
		vert[1] .Blue    =  GetBValue(sColor)<< 8;
		vert[1].Alpha	=  0;

		vert[2] .x       =  rect.right;
		vert[2] .y       =  rect.bottom; 
		vert[2] .Red     =  GetRValue(sColor) <<8;
		vert[2] .Green   =  GetGValue(sColor) <<8;
		vert[2] .Blue    =  GetBValue(sColor) <<8;
		vert[2] .Alpha   =  0;

		vert[3] .x       =  rect.left;
		vert[3] .y       =  rect.bottom;
		vert[3] .Red     =  GetRValue(eColor)<< 8;
		vert[3] .Green   =  GetGValue(eColor)<< 8;
		vert[3] .Blue    =  GetBValue(eColor)<< 8;
		vert[3] .Alpha   =  0x0000;

		gTri[0].Vertex1   = 0;
		gTri[0].Vertex2   = 1;
		gTri[0].Vertex3   = 3;

		gTri[1].Vertex1   = 1;
		gTri[1].Vertex2   = 2;
		gTri[1].Vertex3   = 3;
	}
	else if(nOrder == EGRADATION_D7)
	{
		vert[0].x		=  rect.left;
		vert[0].y		=  rect.top;
		vert[0].Red		=  GetRValue(eColor)<< 8;
		vert[0].Green	=  GetGValue(eColor)<< 8;
		vert[0].Blue	=  GetBValue(eColor)<< 8;
		vert[0].Alpha	=  0;

		vert[1] .x       =  rect.right;
		vert[1] .y       =  rect.top;
		vert[1] .Red     =  GetRValue(sColor)<< 8;
		vert[1] .Green   =  GetGValue(sColor)<< 8;
		vert[1] .Blue    =  GetBValue(sColor)<< 8;
		vert[1] .Alpha   =  0;

		vert[2] .x       =  rect.left;
		vert[2] .y       =  rect.bottom; 
		vert[2] .Red     =  GetRValue(eColor) <<8;
		vert[2] .Green   =  GetGValue(eColor) <<8;
		vert[2] .Blue    =  GetBValue(eColor) <<8;
		vert[2] .Alpha   =  0;

		vert[3] .x       =  rect.right;
		vert[3] .y       =  rect.bottom;
		vert[3] .Red     =  GetRValue(eColor)<< 8;
		vert[3] .Green   =  GetGValue(eColor)<< 8;
		vert[3] .Blue    =  GetBValue(eColor)<< 8;
		vert[3] .Alpha   =  0;

		gTri[0].Vertex1   = 0;
		gTri[0].Vertex2   = 1;
		gTri[0].Vertex3   = 2;

		gTri[1].Vertex1   = 1;
		gTri[1].Vertex2   = 2;
		gTri[1].Vertex3   = 3;
	}
	else if (nOrder == EGRADATION_D8)
	{
		vert[0].x		=  rect.left;
		vert[0].y		=  rect.top;
		vert[0].Red		=  GetRValue(eColor)<< 8;
		vert[0].Green	=  GetGValue(eColor)<< 8;
		vert[0].Blue	=  GetBValue(eColor)<< 8;
		vert[0].Alpha	=  0;

		vert[1] .x       =  rect.right;
		vert[1] .y       =  rect.top;
		vert[1] .Red     =  GetRValue(sColor)<< 8;
		vert[1] .Green   =  GetGValue(sColor)<< 8;
		vert[1] .Blue    =  GetBValue(sColor)<< 8;
		vert[1].Alpha	=  0;

		vert[2] .x       =  rect.right;
		vert[2] .y       =  rect.bottom; 
		vert[2] .Red     =  GetRValue(sColor) <<8;
		vert[2] .Green   =  GetGValue(sColor) <<8;
		vert[2] .Blue    =  GetBValue(sColor) <<8;
		vert[2] .Alpha   =  0;

		vert[3] .x       =  rect.left;
		vert[3] .y       =  rect.bottom;
		vert[3] .Red     =  GetRValue(sColor)<< 8;
		vert[3] .Green   =  GetGValue(sColor)<< 8;
		vert[3] .Blue    =  GetBValue(sColor)<< 8;
		vert[3] .Alpha   =  0x0000;

		gTri[0].Vertex1   = 0;
		gTri[0].Vertex2   = 1;
		gTri[0].Vertex3   = 2;

		gTri[1].Vertex1   = 0;
		gTri[1].Vertex2   = 2;
		gTri[1].Vertex3   = 3;
	}

	dc->GradientFill(vert,4,&gTri,2,GRADIENT_FILL_TRIANGLE);

}


void CPatternView::drawBitmap(CString ptnString)
{
	int ipos;

	CRect rect;
	int m_fillopt;
	int sizeX, sizeY;
	CString bitString=_T("");

	// Rect Size & Fill Option
	ipos = ptnString.Find(_T("TB"));
	if(ipos == -1)	return;

	rect.left	= _ttoi(ptnString.Mid(ipos+7,4));
	rect.top	= _ttoi(ptnString.Mid(ipos+11,4));
	rect.right	= _ttoi(ptnString.Mid(ipos+15,4));
	rect.bottom	= _ttoi(ptnString.Mid(ipos+19,4));
	m_fillopt	= _ttoi(ptnString.Mid(ipos+23,1));

	// X, Y size & Bitmap String
	ipos = ptnString.Find(_T("DB"));
	if(ipos == -1)	return;
	sizeX		= _tcstol(ptnString.Mid(ipos+5,2), NULL, 16);

	int istart=ipos+7;
	TCHAR ch;
	while(1)
	{
		ch = ptnString.GetAt(istart);
		if(((ch>=_T('0')) && (ch<=_T('9'))) || ((ch>=_T('A')) && (ch<=_T('F'))))
		{
			bitString.Insert(bitString.GetLength(), ch);
			istart++;
			continue;
		}
		break;
	}
	sizeY		= bitString.GetLength() / sizeX;

	// User Bitmap 생성
	drawBitmap_setUserBrush(bitString, sizeX, sizeY);

	// Draw Bitmap
	drawBitmap_Draw(m_pDC, rect, sizeX, sizeY, m_fillopt);

}

void CPatternView::drawBitmap_Draw(CDC* dc, CRect rc, int sizeX, int sizeY, int fillopt)
{
	double	zoomH = getZoomH();
	double	zoomV = getZoomV();

	CBitmap patternbitmap;
	CBrush bitmpbrush;
	CBrush fgbrush(RGB(0,0,0));


	CRect rect;
	rect.left	= (LONG)(m_frameRect.left + round((double)rc.left * zoomH));
	rect.right	= (LONG)(m_frameRect.left + round((double)rc.right * zoomH));
	rect.top	= (LONG)(m_frameRect.top + round((double)rc.top * zoomV));
	rect.bottom	= (LONG)(m_frameRect.top + round((double)rc.bottom * zoomV));

	//비트 맵 추가
	CRect Framerect((LONG)round(m_frameRect.left),
		(LONG)round(m_frameRect.top),
		(LONG)round(m_frameRect.right),
		(LONG)round(m_frameRect.bottom) );

	if(sizeX == 0) return;

	CRect rcNew = Framerect;

	BITMAPINFO bmi;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth		= sizeX;
	bmi.bmiHeader.biHeight		= sizeY;
	bmi.bmiHeader.biPlanes		= 1;
	bmi.bmiHeader.biBitCount	= 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage	= 0;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;
	bmi.bmiHeader.biClrUsed = 0;
	bmi.bmiHeader.biClrImportant = 0;

	CBitmap bm;
	bm.CreateCompatibleBitmap(dc,sizeX,sizeY);
	::SetDIBits(dc->m_hDC,bm,0,sizeY,&m_bitbrush,&bmi,DIB_RGB_COLORS);

	CBrush brush,*pOldbrush;
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_PATTERN;
	//Warring HGDIOBJ YJK 2020.04.06
	logBrush.lbHatch = (ULONG_PTR) bm.GetSafeHandle();
	logBrush.lbColor = RGB(0,0,0);

	brush.CreateBrushIndirect(&logBrush);
	int savedc = dc->SaveDC();
	pOldbrush=dc->SelectObject(&brush);
	dc->SetBrushOrg(rcNew.left+1,rcNew.top-3);  //? 
	dc->SetBkMode(TRANSPARENT);
	dc->SetBkColor(RGB(255,255,255));
	dc->Rectangle(&rcNew);
	dc->SelectObject(pOldbrush);
	brush.DeleteObject();
	bm.DeleteObject();
	dc->RestoreDC(savedc);


	//사각형 영역추가
	if(fillopt == 1)
	{
		dc->FillRect(&rect,&fgbrush);
	}
	else if(fillopt == 0)
	{
		CRgn rgn1,rgn2,rgn3; 

		rgn1.CreateRectRgn(Framerect.left,Framerect.top,Framerect.right,Framerect.bottom);
		rgn2.CreateRectRgn(rect.left,rect.top,rect.right,rect.bottom);
		rgn3.CreateRectRgn(0,0,0,0);
		rgn3.CombineRgn(&rgn1,&rgn2, RGN_XOR);

		dc->FillRgn(&rgn3,&fgbrush);
	}
}

void CPatternView::drawBitmap_setUserBrush(CString szbrush, int sizeX, int sizeY)
{
	CString m_userBrush;
	COLORREF		c8Brush[8];

	c8Brush[0]		=	RGB(0	,0	 ,0   );
	c8Brush[1]		=	RGB(0	,0	 ,0xFF);    //BLUE
	c8Brush[2]		=	RGB(0	,0xFF,0	  );	//GREEN
	c8Brush[3]		=	RGB(0	,0xFF,0xFF);    //Cyan
	c8Brush[4]		=	RGB(0xFF,0	 ,0	  );	//RED
	c8Brush[5]		=	RGB(0xFF,0	 ,0xFF);    //Magenta
	c8Brush[6]		=	RGB(0xFF,0xFF,0   );	//YELLOW
	c8Brush[7]		=	RGB(0xFF,0xFF,0xFF);    //White

	if(szbrush.GetLength() == 0 )
	{
		memset(m_bitbrush,0,sizeof(DWORD)*256);

		int max = sizeX*sizeY;

		for(int i = 0 ; i < max ; i++)	m_userBrush += _T('0');

	}
	else
	{

		int max  = szbrush.GetLength();
		int oldx = max/sizeY;

		m_userBrush = _T("");
		CString strBuff;

		for(int y = 0 ; y < sizeY ; y++)
		{
			int ydes_s = y*sizeX;
			int ysrc_s = y*oldx;

			//이전 Y라인.
			if(sizeX <= oldx)
			{
				strBuff = szbrush.Mid(ysrc_s,sizeX);
			}
			else if( sizeX > oldx)
			{
				strBuff = szbrush.Mid(ysrc_s,oldx);

				for(int x = oldx ; x < sizeX ; x++)
					strBuff += _T('8');

			}

			m_userBrush += strBuff;
		}
	}

	TCHAR chHex[17] = _T("0123456789ABCDEF");
	//
	for(int i = 0 ; i < m_userBrush.GetLength() ; i++)
	{
		int pi   = i/2;
		TCHAR ch = m_userBrush.GetAt(i);	
		int clr  = (int)(wcschr(chHex,ch) - chHex);
		clr  -=8;

		COLORREF color = c8Brush[clr%8];

		int x = (i%sizeX);	
		int y = i/sizeX;	
		int bi = ((sizeY-1) - y)*sizeX + x;
		m_bitbrush[bi] = RGB(GetBValue(color),GetGValue(color),GetRValue(color));
	}
}


void CPatternView::drawChess(CString ptnString)
{
	int ipos;
	int typeNo, matrixX, matrixY, color1, color2;

	CRect rect;

	ipos = ptnString.Find(_T("TD"));
	if(ipos == -1)	return;

	typeNo	= _ttoi(ptnString.Mid(ipos+5, 1));
	matrixY	= _ttoi(ptnString.Mid(ipos+6, 2));
	matrixX	= _ttoi(ptnString.Mid(ipos+8, 2));
	color1	= _ttoi(ptnString.Mid(ipos+10, 1));
	color2	= _ttoi(ptnString.Mid(ipos+11, 1));

	drawChess_Draw(m_pDC, matrixX, matrixY, color1, color2);
}


void CPatternView::drawChess_Draw(CDC* dc, int matrixX, int matrixY, int color1, int color2)
{
	double Width  = m_frameRect.Width();
	double Height = m_frameRect.Height();

	double xoffset = Width  / matrixX;
	double yoffset = Height / matrixY;

	CBrush Brush[2];
	Brush[0].CreateSolidBrush(drawChess_getColor(color1));
	Brush[1].CreateSolidBrush(drawChess_getColor(color2));

//	if(m_nType == 1)
	{
		for(int y = 0 ; y < matrixY ; y++)
		{
			for(int x = 0 ; x < matrixX ; x++)
			{
				CRect rect2(m_frameRect.left+(int)xoffset*x,
							m_frameRect.top+(int)yoffset*y,
							m_frameRect.left+(int)(xoffset*(x+1)),
							m_frameRect.top+(int)(yoffset*(y+1)));
				dc->FillRect(rect2,&Brush[(x+y)%2]);
			}
		}
	}
	Brush[0].DeleteObject();
	Brush[1].DeleteObject();
}

COLORREF CPatternView::drawChess_getColor(int clr_index)
{
	COLORREF ret_color = RGB(0, 0, 0);

	if(clr_index==0)		ret_color = RGB(0, 0, 0);
	if(clr_index==1)		ret_color = RGB(255, 0, 0);
	if(clr_index==2)		ret_color = RGB(0, 255, 0);
	if(clr_index==3)		ret_color = RGB(255, 255, 0);
	if(clr_index==4)		ret_color = RGB(0, 0, 255);
	if(clr_index==5)		ret_color = RGB(255, 0, 255);
	if(clr_index==6)		ret_color = RGB(0, 255, 255);
	if(clr_index==7)		ret_color = RGB(255, 255, 255);
	if(clr_index==8)		ret_color = m_cbgColor;
	if(clr_index==9)		ret_color = m_cfgColor;

	return ret_color;
}

void CPatternView::drawCircle(CString ptnString)
{
	int m_centerX, m_centerY, m_radius, m_fillopt;
	int ipos, ipos2;

	CRect rect;

	ipos = ptnString.Find(_T("DC"));
	if(ipos == -1)	return;

	m_centerY	= _ttoi(ptnString.Mid(ipos+5, 4));
	m_centerX	= _ttoi(ptnString.Mid(ipos+9, 4));
	m_radius	= _ttoi(ptnString.Mid(ipos+13, 4));

	ipos2 = ptnString.Find(_T("LC"));
	if(ipos2 != -1)
	{
		m_fillopt = _ttoi(ptnString.Mid(ipos2+5, 1));
	}

	rect.left	= m_centerX - m_radius;
	rect.right	= m_centerX + m_radius;
	rect.top	= m_centerY - m_radius;
	rect.bottom	= m_centerY + m_radius;
	drawCircle_Draw(m_pDC, rect, m_fillopt);
}


void CPatternView::drawCircle_Draw(CDC* dc, CRect rc, int fillopt)
{
	CRect rect;

	rect.left	= (LONG)(m_frameRect.left + round((double)rc.left * getZoomH()));
	rect.right	= (LONG)(m_frameRect.left + round((double)rc.right * getZoomH()));
	rect.top	= (LONG)(m_frameRect.top + round((double)rc.top * getZoomV()));
	rect.bottom	= (LONG)(m_frameRect.top + round((double)rc.bottom * getZoomV()));

	if(fillopt== 0)
	{
		CPen mypen;
		CBrush* pOldBursh = NULL;
		CPen*oldpen = NULL;
		pOldBursh = (CBrush*)dc->SelectStockObject(NULL_BRUSH);
		mypen.CreatePen(PS_SOLID,1, m_clnColor);
		oldpen = (CPen*)dc->SelectObject(&mypen);

		dc->Ellipse(&rect);

		dc->SelectObject(pOldBursh);
		dc->SelectObject(oldpen);

	}
	else if(fillopt == 1)
	{
		CPen mypen;
		CBrush* pOldBursh = NULL;
		CPen*oldpen = NULL;
		CBrush brush;
		brush.CreateSolidBrush(m_clnColor);
		mypen.CreatePen(PS_SOLID,1,m_clnColor);
		oldpen = (CPen*)dc->SelectObject(&mypen);
		pOldBursh = (CBrush*)dc->SelectObject(&brush);

		dc->Ellipse(&rect);

		dc->SelectObject(pOldBursh);
		dc->SelectObject(oldpen);

		brush.DeleteObject();
	}
	else if(fillopt == 2)
	{
		CRgn rgn1,rgn2,rgn3; 

		double zoomH = getZoomH();
		double zoomV = getZoomV();
		CRect Framerect(
				(LONG)round(m_frameRect.left * zoomH),
				(LONG)round(m_frameRect.top * zoomV),
				(LONG)round(m_frameRect.right * zoomH),
				(LONG)round(m_frameRect.bottom * zoomV)
				);


		rgn1.CreateRectRgn(Framerect.left,Framerect.top,Framerect.right,Framerect.bottom);
		rgn2.CreateEllipticRgn(rect.left,rect.top,rect.right,rect.bottom);
		rgn3.CreateEllipticRgn(0,0,0,0);
		rgn3.CombineRgn(&rgn1,&rgn2, RGN_XOR);

		CBrush brush(m_clnColor);
		dc->FillRgn(&rgn3,&brush);
	}
}


void CPatternView::drawRect(CString ptnString)
{
	CString rectstring;
	int ipos, m_length, m_istart=0;

	while(1)
	{
		CRect rect;
		int m_fillopt=0;

		ipos = ptnString.Find(_T("LR"),m_istart);
		if(ipos == -1)	break;

		m_length = _ttoi(ptnString.Mid(ipos+2, 3));
		m_istart = ipos + m_length;
		rectstring = ptnString.Mid(ipos, m_length);

		rect.top	= _ttoi(rectstring.Mid(5,4));
		rect.left	= _ttoi(rectstring.Mid(9,4));
		rect.bottom	= _ttoi(rectstring.Mid(13,4));
		rect.right	= _ttoi(rectstring.Mid(17,4));
		m_fillopt	= _ttoi(rectstring.Mid(21,1));
	
		drawRect_Draw(m_pDC, rect, m_fillopt);
	}
}


void CPatternView::drawRect_Draw(CDC* dc, CRect rc, int fillopt)
{
	CRect rect;

	rect.left	= (LONG)(m_frameRect.left + round((double)rc.left * getZoomH()));
	rect.right	= (LONG)(m_frameRect.left + round((double)rc.right * getZoomH()));
	rect.top	= (LONG)(m_frameRect.top + round((double)rc.top * getZoomV()));
	rect.bottom	= (LONG)(m_frameRect.top + round((double)rc.bottom * getZoomV()));

	if(fillopt == 0)
	{
		CBrush* pOldBursh = (CBrush*)dc->SelectStockObject(NULL_BRUSH);
		CPen mypen;
		mypen.CreatePen(PS_SOLID,1,m_clnColor);
		CPen*oldpen = (CPen*)dc->SelectObject(&mypen);

		dc->Rectangle(&rect);

		dc->SelectObject(oldpen);
		dc->SelectObject(pOldBursh);
	}
	else if(fillopt == 1)
	{
		CBrush brush(m_clnColor);
		CBrush* pOldBursh = (CBrush*)dc->SelectObject(&brush);
		CPen mypen;
		mypen.CreatePen(PS_SOLID,1,m_clnColor);
		CPen*oldpen = (CPen*)dc->SelectObject(&mypen);

		dc->Rectangle(&rect);
		dc->SelectObject(oldpen);
		dc->SelectObject(pOldBursh);

	}
	else if(fillopt == 2)
	{
		CRgn rgn1,rgn2,rgn3; 

		double zoomH = getZoomH();
		double zoomV = getZoomV();
		CRect Framerect((LONG)round(m_frameRect.left * zoomH),
			(LONG)round(m_frameRect.top * zoomV),
			(LONG)round(m_frameRect.right * zoomH),
			(LONG)round(m_frameRect.bottom * zoomV) );

		rgn1.CreateRectRgn(Framerect.left,Framerect.top,Framerect.right,Framerect.bottom);
		rgn2.CreateRectRgn(rect.left,rect.top,rect.right,rect.bottom);
		rgn3.CreateRectRgn(0,0,0,0);
		rgn3.CombineRgn(&rgn1,&rgn2, RGN_XOR);

		CBrush brush(m_clnColor);
		dc->FillRgn(&rgn3,&brush);
	}
	else if(fillopt == 4)
	{
		;
	}
}


void CPatternView::drawExRect(CString ptnString)
{
	CString rectstring;
	int ipos, m_length, m_istart=0;

	while(1)
	{
		CRect rect;
		int m_fillopt=0;
		COLORREF lineColor;
		BYTE cred, cgreen, cblue;

		ipos = ptnString.Find(_T("ER"),m_istart);
		if(ipos == -1)	break;

		m_length = _ttoi(ptnString.Mid(ipos+2, 3));
		m_istart = ipos + m_length;
		rectstring = ptnString.Mid(ipos, m_length);

		rect.top	= _ttoi(rectstring.Mid(5,4));
		rect.left	= _ttoi(rectstring.Mid(9,4));
		rect.bottom	= _ttoi(rectstring.Mid(13,4));
		rect.right	= _ttoi(rectstring.Mid(17,4));
		m_fillopt	= _ttoi(rectstring.Mid(21,1));
		cred		= (BYTE)_tcstol(ptnString.Mid(ipos+22, 2), NULL, 16);
		cgreen		= (BYTE)_tcstol(ptnString.Mid(ipos+26, 2), NULL, 16);
		cblue		= (BYTE)_tcstol(ptnString.Mid(ipos+30, 2), NULL, 16);

		lineColor = RGB(cred, cgreen, cblue);
		drawExRect_Draw(m_pDC, rect, m_fillopt, lineColor);
	}
}

void CPatternView::drawExRect_Draw(CDC* dc, CRect rc, int fillopt, COLORREF rectColor)
{
	CRect rect;

	rect.left	= (LONG)(m_frameRect.left + round((double)rc.left * getZoomH()));
	rect.right	= (LONG)(m_frameRect.left + round((double)rc.right * getZoomH()));
	rect.top	= (LONG)(m_frameRect.top + round((double)rc.top * getZoomV()));
	rect.bottom	= (LONG)(m_frameRect.top + round((double)rc.bottom * getZoomV()));

	if(fillopt == 0)
	{
		CBrush* pOldBursh = (CBrush*)dc->SelectStockObject(NULL_BRUSH);
		CPen mypen;
		mypen.CreatePen(PS_SOLID,1,rectColor);
		CPen*oldpen = (CPen*)dc->SelectObject(&mypen);

		dc->Rectangle(&rect);

		dc->SelectObject(oldpen);
		dc->SelectObject(pOldBursh);
	}
	else if(fillopt == 1)
	{
		CBrush brush(rectColor);
		CBrush* pOldBursh = (CBrush*)dc->SelectObject(&brush);
		CPen mypen;
		mypen.CreatePen(PS_SOLID,1,rectColor);
		CPen*oldpen = (CPen*)dc->SelectObject(&mypen);

		dc->Rectangle(&rect);
		dc->SelectObject(oldpen);
		dc->SelectObject(pOldBursh);

	}
	else if(fillopt == 2)
	{
		CRgn rgn1,rgn2,rgn3; 

		double zoomH = getZoomH();
		double zoomV = getZoomV();
		CRect Framerect((LONG)round(m_frameRect.left * zoomH),
			(LONG)round(m_frameRect.top * zoomV),
			(LONG)round(m_frameRect.right * zoomH),
			(LONG)round(m_frameRect.bottom * zoomV) );

		rgn1.CreateRectRgn(Framerect.left,Framerect.top,Framerect.right,Framerect.bottom);
		rgn2.CreateRectRgn(rect.left,rect.top,rect.right,rect.bottom);
		rgn3.CreateRectRgn(0,0,0,0);
		rgn3.CombineRgn(&rgn1,&rgn2, RGN_XOR);

		CBrush brush(rectColor);
		dc->FillRgn(&rgn3,&brush);
	}
	else if(fillopt == 4)
	{
		;
	}
}


void CPatternView::drawHLine(CString ptnString)
{
	CString linestring;
	int ipos, m_length, m_istart=0;

	while(1)
	{
		CRect rect;

		ipos = ptnString.Find(_T("LH"),m_istart);
		if(ipos == -1)	break;

		m_length = _ttoi(ptnString.Mid(ipos+2, 3));
		m_istart = ipos + m_length;
		linestring = ptnString.Mid(ipos, m_length);

		rect.top	= _ttoi(linestring.Mid(5,4));
		rect.left	= _ttoi(linestring.Mid(9,4));
		rect.right	= _ttoi(linestring.Mid(13,4));
		rect.bottom	= rect.top;

		drawHLine_Draw(m_pDC, rect);
	}
}


void CPatternView::drawHLine_Draw(CDC* dc, CRect rc)
{
	CRect rect;

	rect.left	= (LONG)(m_frameRect.left + round((double)rc.left * getZoomH()));
	rect.right	= (LONG)(m_frameRect.left + round((double)rc.right * getZoomH()));
	rect.top	= (LONG)(m_frameRect.top + round((double)rc.top * getZoomV()));
	rect.bottom	= (LONG)(m_frameRect.top + round((double)rc.bottom * getZoomV()));

	CPen mypen;
	mypen.CreatePen(PS_SOLID,1,m_clnColor);
	CPen*oldpen = (CPen*)dc->SelectObject(&mypen);

	RECT rt = {rect.left,rect.top,rect.right,rect.top};
	rt.left++;
	dc->MoveTo(rt.left,rt.top);  dc->LineTo(rt.right,rt.top);
	dc->SelectObject(oldpen);
}


void CPatternView::drawExHLine(CString ptnString)
{
	CString linestring;
	int ipos, m_length, m_istart=0;

	while(1)
	{
		CRect rect;
		COLORREF lineColor;
		BYTE cred, cgreen, cblue;

		ipos = ptnString.Find(_T("EH"),m_istart);
		if(ipos == -1)	break;

		m_length = _ttoi(ptnString.Mid(ipos+2, 3));
		m_istart = ipos + m_length;
		linestring = ptnString.Mid(ipos, m_length);

		rect.top	= _ttoi(linestring.Mid(5,4));
		rect.left	= _ttoi(linestring.Mid(9,4));
		rect.right	= _ttoi(linestring.Mid(13,4));
		rect.bottom	= rect.top;
		cred		= (BYTE)_tcstol(ptnString.Mid(ipos+17, 2), NULL, 16);
		cgreen		= (BYTE)_tcstol(ptnString.Mid(ipos+21, 2), NULL, 16);
		cblue		= (BYTE)_tcstol(ptnString.Mid(ipos+25, 2), NULL, 16);

		lineColor = RGB(cred, cgreen, cblue);
		drawExHLine_Draw(m_pDC, rect, lineColor);
	}
}

void CPatternView::drawExHLine_Draw(CDC* dc, CRect rc, COLORREF lineColor)
{
	CRect rect;

	rect.left	= (LONG)(m_frameRect.left + round((double)rc.left * getZoomH()));
	rect.right	= (LONG)(m_frameRect.left + round((double)rc.right * getZoomH()));
	rect.top	= (LONG)(m_frameRect.top + round((double)rc.top * getZoomV()));
	rect.bottom	= (LONG)(m_frameRect.top + round((double)rc.bottom * getZoomV()));

	CPen mypen;
	mypen.CreatePen(PS_SOLID,1, lineColor);
	CPen*oldpen = (CPen*)dc->SelectObject(&mypen);

	RECT rt = {rect.left,rect.top,rect.right,rect.top};
	dc->MoveTo(rt.left,rt.top);  dc->LineTo(rt.right,rt.top);
	dc->SelectObject(oldpen);
}


void CPatternView::drawHRepeat(CString ptnString)
{
	CString linestring;
	int ipos, m_length, m_istart=0;

	while(1)
	{
		CRect rect;
		int repeatCount, repeatOffset;
		COLORREF lineColor;
		BYTE cred, cgreen, cblue;

		ipos = ptnString.Find(_T("RH"),m_istart);
		if(ipos == -1)	break;

		m_length = _ttoi(ptnString.Mid(ipos+2, 3));
		m_istart = ipos + m_length;
		linestring = ptnString.Mid(ipos, m_length);

		rect.top	= _ttoi(linestring.Mid(7,4));
		rect.left	= _ttoi(linestring.Mid(11,4));
		rect.right	= _ttoi(linestring.Mid(15,4));
		rect.bottom	= rect.top;
		repeatCount = _tcstol(ptnString.Mid(ipos+19, 4), NULL, 16);
		repeatOffset= _tcstol(ptnString.Mid(ipos+23, 4), NULL, 16);
		cred		= (BYTE)_tcstol(ptnString.Mid(ipos+27, 2), NULL, 16);
		cgreen		= (BYTE)_tcstol(ptnString.Mid(ipos+31, 2), NULL, 16);
		cblue		= (BYTE)_tcstol(ptnString.Mid(ipos+35, 2), NULL, 16);

		lineColor = RGB(cred, cgreen, cblue);
		drawHRepeat_Draw(m_pDC, rect, repeatCount, repeatOffset, lineColor);
	}
}

void CPatternView::drawHRepeat_Draw(CDC* dc, CRect rc, int repeatCount, int repeatOffset, COLORREF lineColor)
{
	CPen mypen;

	mypen.CreatePen(PS_SOLID, 1, lineColor);
	CPen*oldpen = (CPen*)dc->SelectObject(&mypen);

	double zoomH	= getZoomH();
	double zoomV	= getZoomV();
	int	   bottom	= m_frameRect.bottom;	//경계선
	int x1			= (int)(m_frameRect.left + round((double)rc.left * zoomH));
	int y1			= (int)(m_frameRect.top + round((double)rc.top * zoomV));
	int x2			= (int)(m_frameRect.left + round((double)rc.right * zoomH));
	double nOffset;

	if(repeatOffset>2)	nOffset = repeatOffset * zoomH;
	else				nOffset = repeatOffset;

	if(nOffset < 1) nOffset = 1;

	for(int i = 0 ; i < repeatCount ; i++)
	{
		if( (y1+i*nOffset) > bottom)		break;

		dc->MoveTo(x1, (int)(y1+i*nOffset));
		dc->LineTo(x2, (int)(y1+i*nOffset));
	}

	dc->SelectObject(oldpen);
}


void CPatternView::drawVLine(CString ptnString)
{
	CString linestring;
	int ipos, m_length, m_istart=0;

	while(1)
	{
		CRect rect;
		int m_fillopt;

		ipos = ptnString.Find(_T("LV"),m_istart);
		if(ipos == -1)	break;

		m_length = _ttoi(ptnString.Mid(ipos+2, 3));
		m_istart = ipos + m_length;
		linestring = ptnString.Mid(ipos, m_length);

		rect.top	= _ttoi(linestring.Mid(5,4));
		rect.left	= _ttoi(linestring.Mid(9,4));
		rect.bottom	= _ttoi(linestring.Mid(13,4));
		rect.right	= rect.left;
		m_fillopt	= _ttoi(linestring.Mid(17,1));

		drawVLine_Draw(m_pDC, rect, m_fillopt);
	}
}

void CPatternView::drawVLine_Draw(CDC* dc, CRect rc, int fillopt)
{
	CRect rect;

	rect.left	= (LONG)(m_frameRect.left + round((double)rc.left * getZoomH()));
	rect.right	= (LONG)(m_frameRect.left + round((double)rc.right * getZoomH()));
	rect.top	= (LONG)(m_frameRect.top + round((double)rc.top * getZoomV()));
	rect.bottom	= (LONG)(m_frameRect.top + round((double)rc.bottom * getZoomV()));


	CPen mypen;
	mypen.CreatePen(PS_SOLID,1,m_clnColor);
	CPen*oldpen = (CPen*)dc->SelectObject(&mypen);

	double	zoomH = getZoomH();
	double	zoomV = getZoomV();
	RECT rt = {rect.left,rect.top,rect.left,rect.bottom};

	if(fillopt == 0)
	{
		dc->MoveTo(rt.left,rt.top);  dc->LineTo(rt.left,rt.bottom);
	}
	//Left
	else if(fillopt == 1)
	{	
		CRect Framerect((LONG)round(m_frameRect.left * zoomH),
			(LONG)round(m_frameRect.top * zoomV),
			(LONG)round(m_frameRect.right * zoomH),
			(LONG)round(m_frameRect.bottom * zoomV) );

		CRect vrect(Framerect.left,rt.top,rt.right,rt.bottom);
		CBrush brush(m_clnColor);

		dc->FillRect(&vrect,&brush);
	}
	//righ
	else if(fillopt == 2)
	{
		CRect Framerect((LONG)round(m_frameRect.left * zoomH),
			(LONG)round(m_frameRect.top * zoomV),
			(LONG)round(m_frameRect.right * zoomH),
			(LONG)round(m_frameRect.bottom * zoomV) );

		CRect vrect(rt.left,rt.top,Framerect.right,rt.bottom);
		CBrush brush(m_clnColor);

		dc->FillRect(&vrect,&brush);;
	}
	else
		;

	dc->SelectObject(oldpen);

}


void CPatternView::drawExVLine(CString ptnString)
{
	CString linestring;
	int ipos, m_length, m_istart=0;

	while(1)
	{
		CRect rect;
		int m_fillopt;
		COLORREF lineColor;
		BYTE cred, cgreen, cblue;

		ipos = ptnString.Find(_T("EV"),m_istart);
		if(ipos == -1)	break;

		m_length = _ttoi(ptnString.Mid(ipos+2, 3));
		m_istart = ipos + m_length;
		linestring = ptnString.Mid(ipos, m_length);

		rect.top	= _ttoi(linestring.Mid(5,4));
		rect.left	= _ttoi(linestring.Mid(9,4));
		rect.bottom	= _ttoi(linestring.Mid(13,4));
		rect.right	= rect.left;
		m_fillopt	= _ttoi(linestring.Mid(17,1));
		cred		= (BYTE)_tcstol(ptnString.Mid(ipos+18, 2), NULL, 16);
		cgreen		= (BYTE)_tcstol(ptnString.Mid(ipos+22, 2), NULL, 16);
		cblue		= (BYTE)_tcstol(ptnString.Mid(ipos+26, 2), NULL, 16);

		lineColor = RGB(cred, cgreen, cblue);

		drawExVLine_Draw(m_pDC, rect, m_fillopt, lineColor);
	}
}

void CPatternView::drawExVLine_Draw(CDC* dc, CRect rc, int fillopt, COLORREF lineColor)
{
	CRect rect;

	rect.left	= (LONG)(m_frameRect.left + round((double)rc.left * getZoomH()));
	rect.right	= (LONG)(m_frameRect.left + round((double)rc.right * getZoomH()));
	rect.top	= (LONG)(m_frameRect.top + round((double)rc.top * getZoomV()));
	rect.bottom	= (LONG)(m_frameRect.top + round((double)rc.bottom * getZoomV()));


	CPen mypen;
	mypen.CreatePen(PS_SOLID,1,lineColor);
	CPen*oldpen = (CPen*)dc->SelectObject(&mypen);

	double	zoomH = getZoomH();
	double	zoomV = getZoomV();
	RECT rt = {rect.left,rect.top,rect.left,rect.bottom};

	if(fillopt == 0)
	{
		dc->MoveTo(rt.left,rt.top);  dc->LineTo(rt.left,rt.bottom);
	}
	//Left
	else if(fillopt == 1)
	{	
		CRect Framerect((LONG)round(m_frameRect.left * zoomH),
			(LONG)round(m_frameRect.top * zoomV),
			(LONG)round(m_frameRect.right * zoomH),
			(LONG)round(m_frameRect.bottom * zoomV) );

		CRect vrect(Framerect.left,rt.top,rt.right,rt.bottom);
		CBrush brush(m_clnColor);

		dc->FillRect(&vrect,&brush);
	}
	//righ
	else if(fillopt == 2)
	{
		CRect Framerect((LONG)round(m_frameRect.left * zoomH),
			(LONG)round(m_frameRect.top * zoomV),
			(LONG)round(m_frameRect.right * zoomH),
			(LONG)round(m_frameRect.bottom * zoomV) );

		CRect vrect(rt.left,rt.top,Framerect.right,rt.bottom);
		CBrush brush(m_clnColor);

		dc->FillRect(&vrect,&brush);;
	}
	else
		;

	dc->SelectObject(oldpen);

}


void CPatternView::drawVRepeat(CString ptnString)
{
	CString linestring;
	int ipos, m_length, m_istart=0;

	while(1)
	{
		CRect rect;
		int repeatCount, repeatOffset;

		ipos = ptnString.Find(_T("RV"),m_istart);
		if(ipos == -1)	break;

		m_length = _ttoi(ptnString.Mid(ipos+2, 3));
		m_istart = ipos + m_length;
		linestring = ptnString.Mid(ipos, m_length);

		rect.top	= _ttoi(linestring.Mid(5,4));
		rect.left	= _ttoi(linestring.Mid(9,4));
		rect.bottom	= _ttoi(linestring.Mid(13,4));
		rect.right	= rect.left;
		repeatCount = _tcstol(ptnString.Mid(ipos+17, 2), NULL, 16);
		repeatOffset= _tcstol(ptnString.Mid(ipos+19, 2), NULL, 16);

		drawVRepeat_Draw(m_pDC, rect, repeatCount, repeatOffset);
	}
}

void CPatternView::drawVRepeat_Draw(CDC* dc, CRect rc, int repeatCount, int repeatOffset)
{
	CPen mypen;

	mypen.CreatePen(PS_SOLID, 1, m_clnColor);
	CPen*oldpen = (CPen*)dc->SelectObject(&mypen);

	double zoomH	= getZoomH();
	double zoomV	= getZoomV();
	int	   right	= m_frameRect.right;	//경계선
	int x1			= (int)(m_frameRect.left + round((double)rc.left * zoomH));
	int y1			= (int)(m_frameRect.top + round((double)rc.top * zoomV));
	int y2			= (int)(m_frameRect.top + round((double)rc.bottom * zoomV));
	double nOffset;

	if(repeatOffset>2)	nOffset = repeatOffset * zoomV;
	else				nOffset = repeatOffset;

	if(nOffset < 1) nOffset = 1;

	for(int i = 0 ; i < repeatCount ; i++)
	{
		if( (x1+(i*nOffset)) > right) break;

		dc->MoveTo((int)(x1+i*nOffset),y1);
		dc->LineTo((int)(x1+i*nOffset),y2);
	}


	dc->SelectObject(oldpen);
}


void CPatternView::drawTLine(CString ptnString)
{
	CString linestring;
	int ipos, m_length, m_istart=0;

	while(1)
	{
		CRect rect;
		int m_fillopt;

		ipos = ptnString.Find(_T("LT"),m_istart);
		if(ipos == -1)	break;

		m_length = _ttoi(ptnString.Mid(ipos+2, 3));
		m_istart = ipos + m_length;
		linestring = ptnString.Mid(ipos, m_length);

		rect.top	= _ttoi(linestring.Mid(5,4));
		rect.left	= _ttoi(linestring.Mid(9,4));
		rect.bottom	= _ttoi(linestring.Mid(13,4));
		rect.right	= _ttoi(linestring.Mid(17,4));
		m_fillopt	= _ttoi(linestring.Mid(21,1));

		drawTLine_Draw(m_pDC, rect, m_fillopt);
	}
}

void CPatternView::drawTLine_Draw(CDC* dc, CRect rc, int fillopt)
{
	CPen mypen;
	mypen.CreatePen(PS_SOLID,1,m_clnColor);
	CPen*oldpen = (CPen*)dc->SelectObject(&mypen);

	POINT vertex[5];

	double zoomH = getZoomH();
	double zoomV = getZoomV();

	CRect rect;

	rect.left	= (LONG)(m_frameRect.left + round((double)rc.left * getZoomH()));
	rect.right	= (LONG)(m_frameRect.left + round((double)rc.right * getZoomH()));
	rect.top	= (LONG)(m_frameRect.top + round((double)rc.top * getZoomV()));
	rect.bottom	= (LONG)(m_frameRect.top + round((double)rc.bottom * getZoomV()));

	if(fillopt == 0)
	{
		dc->MoveTo( rect.TopLeft() );
		dc->LineTo( rect.BottomRight() );
	}
	//left
	else if(fillopt == 1)
	{
		CBrush brush(m_clnColor);
		CRect Framerect((LONG)round(m_frameRect.left),
			(LONG)round(m_frameRect.top),
			(LONG)round(m_frameRect.right),
			(LONG)round(m_frameRect.bottom) );

		if(m_lineWindow.left == 0)
		{	// Line Window 미설정
			vertex[0].x = Framerect.left;
			vertex[0].y = rect.top;
			vertex[1].x = rect.left;
			vertex[1].y = rect.top;
			vertex[2].x = rect.right;
			vertex[2].y = rect.bottom;
			vertex[3].x = Framerect.left;
			vertex[3].y = rect.bottom;
			vertex[4].x = Framerect.left;
			vertex[4].y = rect.top;
		}
		else
		{	// Line Window 설정
			int lwLeft = (int)(m_frameRect.left + round((double)m_lineWindow.left * getZoomH()));

			vertex[0].x = lwLeft;
			vertex[0].y = rect.top;
			vertex[1].x = rect.left;
			vertex[1].y = rect.top;
			vertex[2].x = rect.right;
			vertex[2].y = rect.bottom;
			vertex[3].x = lwLeft;
			vertex[3].y = rect.bottom;
			vertex[4].x = lwLeft;
			vertex[4].y = rect.top;
		}

		CRgn rgn;
		rgn.CreatePolygonRgn(vertex,5,ALTERNATE);
		dc->FillRgn(&rgn,&brush);
	}
	//righ
	else if(fillopt == 2)
	{
		CBrush brush(m_clnColor);
		CRect Framerect((LONG)round(m_frameRect.left),
			(LONG)round(m_frameRect.top),
			(LONG)round(m_frameRect.right),
			(LONG)round(m_frameRect.bottom) );


		if(m_lineWindow.right == 0)
		{	// Line Window 미설정
			vertex[0].x = Framerect.right;
			vertex[0].y = rect.top;
			vertex[1].x = rect.left;
			vertex[1].y = rect.top;
			vertex[2].x = rect.right;
			vertex[2].y = rect.bottom;
			vertex[3].x = Framerect.right;
			vertex[3].y = rect.bottom;
			vertex[4].x = Framerect.right;
			vertex[4].y = rect.top;
		}
		else
		{	// Line Window 설정
			int lwRight = (int)(m_frameRect.left + round((double)m_lineWindow.right * getZoomH()));

			vertex[0].x = lwRight;//Framerect.right;
			vertex[0].y = rect.top;
			vertex[1].x = rect.left;
			vertex[1].y = rect.top;
			vertex[2].x = rect.right;
			vertex[2].y = rect.bottom;
			vertex[3].x = lwRight;//Framerect.right;
			vertex[3].y = rect.bottom;
			vertex[4].x = lwRight;//Framerect.right;
			vertex[4].y = rect.top;
		}

		CRgn rgn;
		rgn.CreatePolygonRgn(vertex,5,ALTERNATE);
		dc->FillRgn(&rgn,&brush);
	}

	dc->SelectObject(oldpen);
}

void CPatternView::drawMarker(CString ptnString)
{
	CString bmString;
	int ipos, m_length, m_istart=0;

	while(1)
	{
		CRect rect;

		ipos = ptnString.Find(_T("BM"),m_istart);
		if(ipos == -1)	break;

		m_length = _ttoi(ptnString.Mid(ipos+2, 3));
		m_istart = ipos + m_length;
		bmString = ptnString.Mid(ipos, m_length);

		rect.left	= _ttoi(bmString.Mid(5,4));
		rect.top	= _ttoi(bmString.Mid(9,4));
		rect.right	= rect.left + _ttoi(bmString.Mid(13,4));
		rect.bottom	= rect.top + _ttoi(bmString.Mid(17,4));

		drawMarker_Draw(m_pDC, rect);
	}
}

void CPatternView::drawMarker_Draw(CDC* dc, CRect rc)
{
	int bmHCount=0;
	int bmVCount=0;
	int bmHPixel=9;
	int bmVPixel=9;

	CPen mypen;
	mypen.CreatePen(PS_SOLID, 1, m_clnColor);
	CPen*oldpen = (CPen*)dc->SelectObject(&mypen);

	int x1=0, x2=0, y1=0, y2=0;
	double hOffset, vOffset;

	CRect rect;

	rect.left	= (LONG)(m_frameRect.left + round((double)rc.left * getZoomH()));
	rect.right	= (LONG)(m_frameRect.left + round((double)rc.right * getZoomH()));
	rect.top	= (LONG)(m_frameRect.top + round((double)rc.top * getZoomV()));
	rect.bottom	= (LONG)(m_frameRect.top + round((double)rc.bottom * getZoomV()));

	bmHCount = rc.Width() / 100;
	bmVCount = rc.Height() / 100;

	hOffset = rect.Width() / bmHCount;
	vOffset = rect.Height() / bmVCount;

	for(int iv=1; iv<bmVCount; iv++)
	{
		for(int ih=1; ih<=bmHCount; ih++)
		{
			if((iv%2)==1)
			{
				if(ih==bmHCount)	break;

				x1 = (int)(rect.left + (ih*hOffset));
				x2 = (int)(rect.left + (ih*hOffset) + bmHPixel);
				y1 = (int)(rect.top  + (iv*vOffset));
				y2 = (int)(rect.top  + (iv*vOffset) + bmVPixel);

				dc->MoveTo(x1,(y1+y2)/2);
				dc->LineTo(x2,(y1+y2)/2);
				dc->MoveTo((x1+x2)/2, y1);
				dc->LineTo((x1+x2)/2, y2);
			}
			else
			{
				x1 = (int)(rect.left + (ih*hOffset) - (hOffset/2));
				x2 = (int)(rect.left + (ih*hOffset) - (hOffset/2) + bmHPixel);
				y1 = (int)(rect.top  + (iv*vOffset));
				y2 = (int)(rect.top  + (iv*vOffset) + bmVPixel);

				dc->MoveTo(x1,(y1+y2)/2);
				dc->LineTo(x2,(y1+y2)/2);
				dc->MoveTo((x1+x2)/2, y1);
				dc->LineTo((x1+x2)/2, y2);
			}
		}
	}

	dc->SelectObject(oldpen);
}


void CPatternView::drawCharacter(CString ptnString)
{
	CString bmString, outstr;
	int ipos, m_length, m_istart=0;

	while(1)
	{
		CRect rect;

		ipos = ptnString.Find(_T("BS"),m_istart);
		if(ipos == -1)	break;

		m_length = _ttoi(ptnString.Mid(ipos+2, 3));
		m_istart = ipos + m_length;
		bmString = ptnString.Mid(ipos, m_length);

		rect.top	= _ttoi(bmString.Mid(5,4));
		rect.left	= _ttoi(bmString.Mid(9,4));
		rect.bottom	= _ttoi(bmString.Mid(13,4));
		rect.right	= _ttoi(bmString.Mid(17,4));

		outstr.Format(_T("%s"), bmString.Mid(21));

		drawCharacter_Draw(m_pDC, rect, outstr);
	}
}

void CPatternView::drawCharacter_Draw(CDC* dc, CRect rc, CString outstr)
{
	double vOffset=0;
	CRect rect;

	rect.left	= (LONG)(m_frameRect.left + round((double)rc.left * getZoomH()));
	rect.right	= (LONG)(m_frameRect.left + round((double)rc.right * getZoomH()));
	rect.top	= (LONG)(m_frameRect.top + round((double)rc.top * getZoomV()));
	rect.bottom	= (LONG)(m_frameRect.top + round((double)rc.bottom * getZoomV()));

	dc->SetBkMode(TRANSPARENT);
	dc->SetTextColor(m_cbtColor);

	CFont Font[5], *pOldFont;
	for(int i=0; i<5; i++)
	{
		Font[i].CreateFont(((i+1)*32),0,0,0,1000,false,false,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("ARIAL"));
		pOldFont=(CFont*)dc->SelectObject(&Font[i]);

		rect.top = rect.top + (i+1)*32*2;
		dc->DrawText(outstr, rect, DT_TOP|DT_LEFT|DT_WORDBREAK);
		dc->SelectObject(pOldFont);
	}
}

