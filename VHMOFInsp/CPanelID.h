#pragma once


// CPanelID 대화 상자

class CPanelID : public CDialog
{
	DECLARE_DYNAMIC(CPanelID)

public:
	CPanelID(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CPanelID();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PANELID };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////////////
// 사용자 정의 Function
///////////////////////////////////////////////////////////////////////////
public:
	CString strInputPID;

protected:
	LPINSPWORKINFO	lpInspWorkInfo;
	void Lf_InitLocalValue();
	void Lf_InitFontset();
	void Lf_InitColorBrush();
	void Lf_InitDlgDesign();

	void Lf_confirmPanelID();

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
	afx_msg void OnBnClickedBtnPidConfirm();
	afx_msg void OnBnClickedBtnPidCancel();
	CButton m_btnPidConfirm;
	CButton m_btnPidCancel;
};
