#pragma once


// CIOReadyCheck 대화 상자

class CIOReadyCheck : public CDialog
{
	DECLARE_DYNAMIC(CIOReadyCheck)

public:
	CIOReadyCheck(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CIOReadyCheck();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IO_READY_CHECK };
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
	void Lf_controlButtonEnable(BOOL bEnable);

	void Lf_updateIOReadyStatus();


	BOOL m_rdyRearDoorClose;
	BOOL m_rdyFrontDoorClose;
	BOOL m_rdyFrontDoorHoldingBackward;
	BOOL m_rdyRobotInSensor;
	BOOL m_rdyJigTiltingDown;
	BOOL m_rdyJigDoorClose;
	BOOL m_rdyJigTrayIn;
	BOOL m_rdyCh1ClampUnlock;
	BOOL m_rdyCh2ClampUnlock;


	BOOL m_ingRearDoorClose;
	BOOL m_ingFrontDoorClose;
	BOOL m_ingFrontDoorHoldingBackward;
	BOOL m_ingJigTiltingDown;
	BOOL m_ingCh1ClampUnlock;
	BOOL m_ingCh2ClampUnlock;

	BOOL m_bVisiableToggle;

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];
	CFont* m_pDefaultFont;

	CBitmap m_BitButtonRed, m_BitButtonGreen;

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////



public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_btnIrClose;
	CStatic m_picRearDoorLeftCylinderDown;
	CStatic m_picRearDoorRightCylinderDown;
	CStatic m_picFrontDoorLeftCylinderDown;
	CStatic m_picFrontDoorRightCylinderDown;
	CStatic m_picFrontDoorHoldingCylinderBack;
	CStatic m_picRobotInSensor1;
	CStatic m_picRobotInSensor2;
	afx_msg void OnBnClickedBtnIrClose();
	CStatic m_picJigDownSensor1;
	CStatic m_picJigDownSensor2;
	CStatic m_picJigDownSensor3;
	CStatic m_picJigHomeSensor;
	CStatic m_picJigDoorClose;
	CStatic m_picJigTrayInCh1;
	CStatic m_picJigTrayInCh2;
	CStatic m_picCh1Clamp1Unlock;
	CStatic m_picCh1Clamp2Unlock;
	CStatic m_picCh1Clamp3Unlock;
	CStatic m_picCh1Clamp4Unlock;
	CStatic m_picCh1Clamp5Unlock;
	CStatic m_picCh1Clamp6Unlock;
	CStatic m_picCh2Clamp1Unlock;
	CStatic m_picCh2Clamp2Unlock;
	CStatic m_picCh2Clamp3Unlock;
	CStatic m_picCh2Clamp4Unlock;
	CStatic m_picCh2Clamp5Unlock;
	CStatic m_picCh2Clamp6Unlock;
	afx_msg void OnStnClickedSttIrRearDoorReady();
	afx_msg void OnStnClickedSttIrFrontDoorReady();
	afx_msg void OnStnClickedSttIrFrontDoorHoldingReady();
	afx_msg void OnStnClickedSttIrRobotInSensorReady();
	afx_msg void OnStnClickedSttIrJigTiltingDownReady();
	afx_msg void OnStnClickedSttIrJigDoorCloseReady();
	afx_msg void OnStnClickedSttIrJigTrayInReady();
	afx_msg void OnStnClickedSttIrCh1ClampReady();
	afx_msg void OnStnClickedSttIrCh2ClampReady();
};
