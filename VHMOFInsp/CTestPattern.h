#pragma once


// CTestPattern 대화 상자

class CTestPattern : public CDialogEx
{
	DECLARE_DYNAMIC(CTestPattern)

public:
	CTestPattern(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTestPattern();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_PATTERN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////////////
// 사용자 정의 Function
///////////////////////////////////////////////////////////////////////////
public:


protected:
	LPINSPWORKINFO	lpInspWorkInfo;
	LPSYSTEMINFO	lpSystemInfo;
	LPMODELINFO		lpModelInfo;

	void RemoveMessageFromQueue();
	void Lf_InitLocalValue();
	void Lf_InitFontset();
	void Lf_InitColorBrush();
	void Lf_InitDlgDesign();

	void Lf_sendPtnData();
	BOOL Lf_updateMeasureInfo();
	void Lf_excutePatternList(MSG* pMsg);
	void Lf_insertListColum();
	void Lf_insertListItem();
	void Lf_setPatternGrayLevel(int wParam);
	void Lf_getPatternGrayLevel(CString strPattern, int* r_level, int* g_level, int* b_level);
	BOOL Lf_PatternLockTimeCheck();
	BOOL Lf_PatternCurrentCheck();
	BOOL Lf_PatternVoltageSetting();

	void Lf_PtnTestEventView(CString Event);


	////////////////////////////////////////////////////////////////////////
	int m_nPatternIndex;
	CString m_sTackTime;
	int m_nInspTackTime;
	int m_nInspStartTime;

	float m_fPatternVccOld;
	float m_fPatternVddOld;

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];
	CFont* m_pDefaultFont;

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////



public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListCtrl m_lstTpPatternList;
	CListBox m_lstTpEventView;
};
