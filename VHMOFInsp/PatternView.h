#pragma once


// CPatternView
enum 
{
	EGRADATION_NO=0,
	EGRADATION_HP,
	EGRADATION_HM,
	EGRADATION_VP,
	EGRADATION_VM,
	EGRADATION_D1,
	EGRADATION_D2,
	EGRADATION_D3,
	EGRADATION_D4,
	EGRADATION_D5,
	EGRADATION_D6,
	EGRADATION_D7,
	EGRADATION_D8
};


class CPatternView : public CWnd
{
	DECLARE_DYNAMIC(CPatternView)

public:
	CPatternView();
	virtual ~CPatternView();

	void InitPatternRect(CDC* pDC,  CRect lcdArea, CRect viewArea);
	void InitPatternPath(CString path);
	void InitBmpPatternPath(CString spath);
	void drawPattern(CString ptnName);
	void drawPatternBmp(CString bmpName);

protected:
	DECLARE_MESSAGE_MAP()

	double getZoomH();
	double getZoomV();

	void setColorBackGround(CString ptnString);
	void setColorForeGround(CString ptnString);
	void setColorLine(CString ptnString);
	void setColorBitmap(CString ptnString);
	void setLineWindow(CString ptnString);

	void drawPrevPattern(CString ptnString);

	// CANVAS
	void drawCanvas(CString ptnString);
	void drawCanvas_Draw(CRect rc, COLORREF sClr, int m_nGradation);
	void drawCanvas_HGradient(CDC* dc,const CRect& rect, COLORREF sColor,COLORREF eColor);
	void drawCanvas_VGradient(CDC* dc,const CRect& rect, COLORREF sColor,COLORREF eColor);
	void drawCanvas_HVGradient(CDC* dc,const CRect& rect, COLORREF sColor,COLORREF eColor,UINT nOrder);
	COLORREF drawCanvas_getColor(CString clrstr);
	int  drawCanvas_getGradation(CString grastr);

	// Bit Map (flicker)
	void drawBitmap(CString ptnString);
	void drawBitmap_Draw(CDC* dc, CRect rc, int sizeX, int sizeY, int fillopt);
	void drawBitmap_setUserBrush(CString szbrush, int sizeX, int sizeY);

	// Chess
	void drawChess(CString ptnString);
	void drawChess_Draw(CDC* dc, int matrixX, int matrixY, int color1, int color2);
	COLORREF drawChess_getColor(int clr_index);

	// CIRCLE
	void drawCircle(CString ptnString);
	void drawCircle_Draw(CDC* dc, CRect rc, int fillopt);

	// RECT
	void drawRect(CString ptnString);
	void drawRect_Draw(CDC* dc, CRect rc, int fillopt);

	// Ex-RECT
	void drawExRect(CString ptnString);
	void drawExRect_Draw(CDC* dc, CRect rc, int fillopt, COLORREF rectColor);

	// HLINE
	void drawHLine(CString ptnString);
	void drawHLine_Draw(CDC* dc, CRect rc);

	// Ex-HLINE
	void drawExHLine(CString ptnString);
	void drawExHLine_Draw(CDC* dc, CRect rc, COLORREF lineColor);

	// HLINE Repeat
	void drawHRepeat(CString ptnString);
	void drawHRepeat_Draw(CDC* dc, CRect rc, int repeatCount, int repeatOffset, COLORREF lineColor);

	// VLINE
	void drawVLine(CString ptnString);
	void drawVLine_Draw(CDC* dc, CRect rc, int fillopt);

	// Ex-VLINE
	void drawExVLine(CString ptnString);
	void drawExVLine_Draw(CDC* dc, CRect rc, int fillopt, COLORREF lineColor);

	// VLINE Repeat
	void drawVRepeat(CString ptnString);
	void drawVRepeat_Draw(CDC* dc, CRect rc, int repeatCount, int repeatOffset);

	// TLINE
	void drawTLine(CString ptnString);
	void drawTLine_Draw(CDC* dc, CRect rc, int fillopt);

	// MARKER
	void drawMarker(CString ptnString);
	void drawMarker_Draw(CDC* dc, CRect rc);

	// CHARACTER
	void drawCharacter(CString ptnString);
	void drawCharacter_Draw(CDC* dc, CRect rc, CString outstr);

	CDC* m_pDC;
	CRect m_lcdArea;
	CRect m_frameRect;
	CStringArray patternArray;

	CString m_pathPatternLogical;
	CString m_pathPatternBMP;

	DWORD m_bitbrush[256];


private:
	CStringArray queueStack;

	COLORREF m_cbgColor;
	COLORREF m_cfgColor;
	COLORREF m_clnColor;
	COLORREF m_cbtColor;
	RECT	 m_lineWindow;
};


