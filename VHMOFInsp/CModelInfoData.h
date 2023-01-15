#pragma once

enum
{
	MOD_PTN_NONE = 0,
	MOD_PTN_NAME,
	MOD_PTN_VCC,
	MOD_PTN_VEL,
	MOD_PTN_ICC,
	MOD_PTN_IEL,
	MOD_PTN_LOCKTIME,
	MOD_PTN_MAXTIME,
	MOD_PTN_VSYNC,
	MOD_PTN_ONOFF,
	MOD_PTN_MAX
};
// CModelInfoData 대화 상자

class CModelInfoData : public CDialogEx
{
	DECLARE_DYNAMIC(CModelInfoData)

public:
	CModelInfoData(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CModelInfoData();

// 대화 상자 데이터입니다.
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_INFO_DATA };
//#endif

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

	void Gf_DataSaveModelData(CString modelName);

protected:
	LPMODELINFO		lpModelInfo;
	LPSYSTEMINFO	lpSystemInfo;

	void Lf_loadPatternListToCombo();

	void Lf_InitDialogControl();
	void Lf_InitPatternListColum();
	void Lf_InitPatternListUpdate();

	void Lf_calcHorResolution();
	void Lf_calcVerResolution();

	int  Lf_getPatternListSubitem(CString* subitem);
	void Lf_getPatternDataToControl(int itemidx);
	void Lf_ListControlItemAdd(CListCtrl* pListCtrl, CString* subItem, int subitem_cnt);
	void Lf_ListControlItemDelete(CListCtrl* pListCtrl);
	void Lf_ListControlItemChange(CListCtrl* pListCtrl, CString* subItem, int subitem_cnt);
	void Lf_ListControlItemChangeAll(CListCtrl* pListCtrl, int subIndex, CString subItem);
	void Lf_ListControlItemUp(CListCtrl* pListCtrl, int subitem_cnt);
	void Lf_ListControlItemDown(CListCtrl* pListCtrl, int subitem_cnt);
	void Lf_ListControlItemApplyAll(CListCtrl* pListCtrl, CString* subItem);

	void Lf_UpdateInvalidate();

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
	CComboBox m_cmbMdPtnName;
	CComboBox m_cmbI2cPullUp;
	CComboBox m_cmbI2cLevel;
	CComboBox m_cmbI2cClock;
	CComboBox m_cmbSpiPullUp;
	CComboBox m_cmbSpiLevel;
	CComboBox m_cmbSpiClock;
	CComboBox m_cmbGpioPullUp;
	CComboBox m_cmbGpioLevel;
	CComboBox m_cmbGpio1Output;
	CComboBox m_cmbGpio2Output;
	CComboBox m_cmbGpio3Output;
	CComboBox m_cmbGio1Setting;
	CComboBox m_cmbGio2Setting;
	CComboBox m_cmbGio3Setting;
	CComboBox m_cmbGio4Setting;
	CEdit m_edtMdPtnVcc;
	CEdit m_edtMdPtnVel;
	CEdit m_edtMdPtnIcc;
	CEdit m_edtMdPtnIel;
	CEdit m_edtMdPtnLockTime;
	CEdit m_edtMdPtnMaxTime;
	CEdit m_edtMdPtnVSync;
	CComboBox m_cmbMdPtnOnOff;
	CListCtrl m_lstMdPtnList;
	afx_msg void OnBnClickedBtnMdPtnAdd();
	afx_msg void OnBnClickedBtnMdPtnModify();
	afx_msg void OnBnClickedBtnMdPtnDel();
	afx_msg void OnBnClickedBtnMdPtnUp();
	afx_msg void OnBnClickedBtnMdPtnDown();
	afx_msg void OnBnClickedBtnMdPtnApplyAll();
	afx_msg void OnLvnItemchangedLstMdPtnList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCbnSelchangeCmbMdPtnName();
	CStatic m_picMdPatternPreview;
	CEdit m_edtMdPwmFrequency;
	CEdit m_edtMdPwmDuty;
	CComboBox m_cmbMdPwmLevel;
	CComboBox m_cmbMdCableOpenCheck;
};
