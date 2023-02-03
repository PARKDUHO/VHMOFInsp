#pragma once


// CMaintenanceDIO 대화 상자

class CMaintenanceDIO : public CDialog
{
	DECLARE_DYNAMIC(CMaintenanceDIO)

public:
	CMaintenanceDIO(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMaintenanceDIO();

// 대화 상자 데이터입니다.
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINTENANCE_DIO };
//#endif

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
	void Lf_initListDIN();

	void Lf_setListCheck();
	void Lf_updateStautsDio1In();
	void Lf_updateStautsDio2In();

	void Lf_controlButtonEnable(BOOL bEnable);
	BOOL Lf_confirmDioWrite();

	BOOL Lf_checkSafetyAlarmOn();

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
	afx_msg void OnNMCustomdrawLstMoDio1In(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawLstMoDio1Out(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_lstMoDio1In;
	CListCtrl m_lstMoDio1Out;
	CListCtrl m_lstMoDio2In;
	CListCtrl m_lstMoDio2Out;
	afx_msg void OnNMCustomdrawLstMoDio2In(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawLstMoDio2Out(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedBtnMoWriteDio1();
	afx_msg void OnBnClickedBtnMoWriteDio2();
	CButton m_btnMoWriteDIO1;
	CButton m_btnMoWriteDIO2;
	CStatic m_sttMoFrontDoorOpen;
	CStatic m_sttMoFrontDoorClose;
	CStatic m_sttMoFrontDoorHoldingOn;
	CStatic m_sttMoFrontDoorHoldingOff;
	CStatic m_sttMoRearDoorOpen;
	CStatic m_sttMoRearDoorClose;
	CStatic m_sttMoLightCurationMuteOn;
	CStatic m_sttMoLightCurationMuteOff;
	CStatic m_sttMoJigTiltingUp;
	CStatic m_sttMoJigTiltingDown;
	CStatic m_sttMoLeftSafetyDoorOpen;
	CStatic m_sttMoRightSafetyDoorOpen;
	CStatic m_sttMoClampLockCh1;
	CStatic m_sttMoClampUnLockCh1;
	CStatic m_sttMoClampLockCh2;
	CStatic m_sttMoClampUnLockCh2;
	CButton m_chkMoAutoConfirm;
	afx_msg void OnStnClickedSttMoFrontDoorOpen();
	afx_msg void OnStnClickedSttMoFrontDoorClose();
	afx_msg void OnStnClickedSttMoFrontDoorHoldingOn();
	afx_msg void OnStnClickedSttMoFrontDoorHoldingOff();
	afx_msg void OnStnClickedSttMoRearDoorOpen();
	afx_msg void OnStnClickedSttMoRearDoorClose();
	afx_msg void OnStnClickedSttMoLightCurtainMuteOn();
	afx_msg void OnStnClickedSttMoLightCurtainMuteOff();
	afx_msg void OnStnClickedSttMoJigTiltingUp();
	afx_msg void OnStnClickedSttMoJigTiltingDown();
	afx_msg void OnStnClickedSttMoLeftSafetyDoorOpen();
	afx_msg void OnStnClickedSttMoRightSafetyDoorOpen();
	afx_msg void OnStnClickedSttMoClampLockCh1();
	afx_msg void OnStnClickedSttMoClampUnlockCh1();
	afx_msg void OnStnClickedSttMoClampLockCh2();
	afx_msg void OnStnClickedSttMoClampUnlockCh2();
};
