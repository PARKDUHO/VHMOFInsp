#pragma once


// CSafetyLock 대화 상자

class CSafetyLock : public CDialog
{
	DECLARE_DYNAMIC(CSafetyLock)

public:
	CSafetyLock(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSafetyLock();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAFETY_LOCK };
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

	void Lf_confirmPassword();
	void Lf_openDlgSensorView();


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
	afx_msg void OnBnClickedBtnSlOk();
	CButton m_btnSlConfirm;
	CListBox m_lstSlAlarmList;
	afx_msg void OnBnClickedBtnSlSensorView();
	CButton m_btnSlSensorView;
	afx_msg void OnBnClickedBtnSlBuzzOff();
};
