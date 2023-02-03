#pragma once


// CErrorList 대화 상자입니다.

class CErrorList : public CDialog
{
	DECLARE_DYNAMIC(CErrorList)

public:
	CErrorList(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CErrorList();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ERROR_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	LPMODELINFO		lpModelInfo;
	LPSYSTEMINFO	lpSystemInfo;
	LPINSPWORKINFO	lpInspWorkInfo;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnElClose();

protected:
	void Lf_initVariable();
	void Lf_initFontset();
	void Lf_initColorBrush();
	void Lf_initDesign();
	void Lf_initErrorListViewList();

	void Lf_loadErrorList();
	int  Lf_readAgingErrorList(CString lpDate, CString* lpTime, CString* lpGroup, CString* lpChannel, CString* lpError);

public:
	CButton m_btnElClose;
	CDateTimeCtrl m_ctrAlmDateTime;
	CListCtrl m_lstElErrorListView;

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];
public:
	afx_msg void OnDtnDatetimechangeCtrElDatetime(NMHDR* pNMHDR, LRESULT* pResult);
};
