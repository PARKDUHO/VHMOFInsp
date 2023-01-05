#pragma once


// CTestReady 대화 상자

class CTestReady : public CDialogEx
{
	DECLARE_DYNAMIC(CTestReady)

public:
	CTestReady(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTestReady();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_READY };
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

	void Lf_InitLocalValue();
	void Lf_InitFontset();
	void Lf_InitColorBrush();
	void Lf_InitDlgDesign();

	BOOL Lf_FinalTestStart();
	BOOL Lf_getControlBdReady(int ch);
	BOOL Lf_getFirmwareVersion(int ch);

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////



public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedSttTrQtyReset();
	afx_msg void OnBnClickedBtnTrTestStart();
	CButton m_btnTrTestStart;
};
