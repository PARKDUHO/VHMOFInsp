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
	LPMODELINFO		lpModelInfo;
	LPINSPWORKINFO	lpInspWorkInfo;
	LPSYSTEMINFO	lpSystemInfo;

	void Lf_InitLocalValue();
	void Lf_InitFontset();
	void Lf_InitColorBrush();
	void Lf_InitDlgDesign();

	void Lf_readyInitialize();
	void Lf_updateQuantityCount();

	BOOL Lf_FinalTestStart(int ch);
	BOOL Lf_InspRoomLEDOnOff(BOOL bOnOff);
	BOOL Lf_checkPanelID(int ch);
	BOOL Lf_getControlBdReady(int ch);
	BOOL Lf_setSystemAutoFusing(int ch);
	BOOL Lf_AutoModelChange();
	BOOL Lf_getFirmwareVersion(int ch);
	BOOL Lf_checkCableOpen(int ch);
	BOOL Lf_setGpioControl(int ch);
	BOOL Lf_setGioSetting(int ch);

	BOOL Lf_openGMESJudge();
	BOOL Lf_sendPanelResult();

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
