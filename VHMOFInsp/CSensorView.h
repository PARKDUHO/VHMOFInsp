#pragma once


// CSensorView 대화 상자

class CSensorView : public CDialog
{
	DECLARE_DYNAMIC(CSensorView)

public:
	CSensorView(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSensorView();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SENSOR_VIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////////////
// 사용자 정의 Function
///////////////////////////////////////////////////////////////////////////
public:

protected:
	void Lf_InitLocalValue();
	void Lf_InitFontset();
	void Lf_InitColorBrush();
	void Lf_InitDlgDesign();

	void Lf_showSensorImage();
	void Lf_toggleSensorPosition(BOOL bFlag);
	void Lf_updateErrorMessageList();



	BOOL m_bToggle;

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
	CListBox m_lstSvErrorList;
	CButton m_btnSvExit;
	afx_msg void OnBnClickedBtnSvExit();
	CButton m_btnSvReset;
	afx_msg void OnBnClickedBtnSvReset();
	CButton m_btnSvLeftDoorOpen;
	CButton m_btnSvLeftDoorClose;
	CButton m_btnSvRightDoorOpen;
	CButton m_btnSvRightDoorClose;
	afx_msg void OnBnClickedBtnSvLeftDoorOpen();
	afx_msg void OnBnClickedBtnSvRightDoorOpen();
	afx_msg void OnBnClickedBtnSvLeftDoorClose();
	afx_msg void OnBnClickedBtnSvRightDoorClose();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
