#pragma once

//////////////////////////////////////////////////
// Initialize 결과
#define INIT_NG			0
#define INIT_OK			1
#define INIT_NONE		2

//////////////////////////////////////////////////
// Initialize Code
enum {
	INIT_SYSTEM = 0,
	INIT_MODEL,
	INIT_PATTERN,
	INIT_PG1,
	INIT_PG2,
	INIT_QSPI,
	INIT_DIO,
	INIT_MELSEC,
	INIT_MAX
};

// CInitialize 대화 상자

class CInitialize : public CDialogEx
{
	DECLARE_DYNAMIC(CInitialize)

public:
	CInitialize(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInitialize();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INITIALIZE };
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

	void Lf_initFileSystem();
	void Lf_initFileModel();
	void Lf_initFilePattern();

	void Lf_initConnPG();
	void Lf_initConnQspi();
	void Lf_initConnDIO();
	void Lf_initConnMelsec();


private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];

	BYTE nSysInitResult[INIT_MAX];

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnIniRetry();
	afx_msg void OnBnClickedBtnIniCancel();
	CButton m_btnIniRetry;
	CButton m_btnIniCancel;
};
