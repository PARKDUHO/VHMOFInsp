#pragma once


// CModelChange 대화 상자

class CModelChange : public CDialogEx
{
	DECLARE_DYNAMIC(CModelChange)

public:
	CModelChange(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CModelChange();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_CHANGE };
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


protected:
	LPMODELINFO		lpModelInfo;
	LPSYSTEMINFO	lpSystemInfo;

	void Lf_InitModelInchInfo();
	void Lf_LoadModelList();
	void Lf_initLoadModelList();

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
	afx_msg void OnBnClickedBtnMcLoad();
	CListBox m_lstMcModelList;
	CComboBox m_cmbMcModelInch;
	afx_msg void OnBnClickedBtnMcAllModel();
	afx_msg void OnCbnSelchangeCmbMcModelInch();
	CButton m_btnMcLoad;
};
