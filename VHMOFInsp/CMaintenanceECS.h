#pragma once


// CMaintenanceECS 대화 상자

class CMaintenanceECS : public CDialog
{
	DECLARE_DYNAMIC(CMaintenanceECS)

public:
	CMaintenanceECS(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMaintenanceECS();

// 대화 상자 데이터입니다.
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINTENANCE_ECS };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()



///////////////////////////////////////////////////////////////////////////
// 사용자 정의 Function
///////////////////////////////////////////////////////////////////////////
public:


protected:
	LPSYSTEMINFO	lpSystemInfo;
	LPMODELINFO		lpModelInfo;
	LPINSPWORKINFO	lpInspWorkInfo;
	void Lf_InitLocalValue();
	void Lf_InitFontset();
	void Lf_InitColorBrush();


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
};
