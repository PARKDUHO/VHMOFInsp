#pragma once


// CSystem 대화 상자

class CSystem : public CDialog
{
	DECLARE_DYNAMIC(CSystem)

public:
	CSystem(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSystem();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////////////
// 사용자 정의 Function
///////////////////////////////////////////////////////////////////////////
public:

protected:
	LPSYSTEMINFO		lpSystemInfo;

	void Lf_InitLocalValue();
	void Lf_InitFontset();
	void Lf_InitColorBrush();
	void Lf_InitDlgDesign();

	void Lf_InitDialogControl();
	void Lf_saveSystemInfo();
	CString Lf_FileLoadDialog(CString Temp);

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
	CButton m_btnSySaveExit;
	CButton m_btnSyCancel;
	afx_msg void OnBnClickedBtnSySaveExit();
	afx_msg void OnBnClickedBtnSyCancel();
	afx_msg void OnBnClickedBtnSyModelFilePath();
	afx_msg void OnBnClickedBtnSyPatternFilePath();
	afx_msg void OnBnClickedBtnSyEdidFilePath();
	CEdit m_edtSyEqpName;
	CComboBox m_cmbSyLineType;
	CComboBox m_cmbSyCarrierType;
	CEdit m_edtSyLBStartAddr;
	CEdit m_edtSyLWStartAddr;
	CComboBox m_cmbSyEcsEqpNumber;
	CEdit m_edtSyMesServicePort;
	CEdit m_edtSyMesNetwork;
	CEdit m_edtSyMesDaemonPort;
	CEdit m_edtSyMesLocalSubject;
	CEdit m_edtSyMesRemoteSubject;
	CIPAddressCtrl m_ipaSyMesLocalIp;
	CComboBox m_cmbSyEasUse;
	CEdit m_edtSyEasServicePort;
	CEdit m_edtSyEasNetwork;
	CEdit m_edtSyEasDaemonPort;
	CEdit m_edtSyEasLocalSubject;
	CEdit m_edtSyEasRemoteSubject;
	CEdit m_edtSyModelFilePath;
	CEdit m_edtSyPatternFilePath;
	CEdit m_edtSyEdidFilePath;
};
