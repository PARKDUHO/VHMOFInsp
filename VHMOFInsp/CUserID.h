#pragma once


// CUserID 대화 상자

class CUserID : public CDialog
{
	DECLARE_DYNAMIC(CUserID)

public:
	CUserID(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUserID();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERID };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////
// 사용자 정의 Function
///////////////////////////////////////////////////////////////////////////
public:
	void Lf_InitLocalValue();
	void Lf_InitFontset();
	void Lf_InitColorBrush();
	void Lf_InitDlgDesign();

	BOOL m_bUserManualLogin;
	BOOL m_bUserLoginAutoReady;
	BOOL m_bUserLogout;

protected:
	LPINSPWORKINFO	lpInspWorkInfo;
	LPSYSTEMINFO	lpSystemInfo;

	BOOL Lf_loginProcess();

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
	CStatic m_picUserImage;
	CGradientStatic m_sttUserIDTitle;
	CGradientStatic m_sttUserIDInput;
	CButton m_btnUserCancel;
	CButton m_btnUserConfirm;
	afx_msg void OnBnClickedBtnUiConfirm();
	afx_msg void OnBnClickedBtnUiCancel();
};
