#pragma once


// CTestReady 대화 상자

class CTestReady : public CDialogEx
{
	DECLARE_DYNAMIC(CTestReady)

public:
	CTestReady(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTestReady();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_READY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////////////
// 사용자 정의 Function
///////////////////////////////////////////////////////////////////////////
public:


protected:
	LPMODELINFO		lpModelInfo;
	LPINSPWORKINFO	lpInspWorkInfo;
	LPSYSTEMINFO	lpSystemInfo;

	void Lf_InitLocalValue();
	void Lf_InitFontset();
	void Lf_InitColorBrush();
	void Lf_InitDlgDesign();

	void Lf_readyInitialize();
	void Lf_updateQuantityCount();

	BOOL Lf_FinalTestStart(int ch);
	BOOL Lf_MachineStartIDLEMode();
	BOOL Lf_InspRoomLEDOnOff(BOOL bOnOff);
	BOOL Lf_checkPanelID(int ch);
	BOOL Lf_getControlBdReady(int ch);
	BOOL Lf_setSystemAutoFusing(int ch);
	BOOL Lf_AutoModelChange();
	BOOL Lf_getFirmwareVersion(int ch);
	BOOL Lf_checkCableOpen(int ch);
	BOOL Lf_setGpioControl(int ch);
	BOOL Lf_setGioSetting(int ch);

	BOOL Lf_openGMESJudge();
	BOOL Lf_sendPanelResult(int ch);


	///////////////////////////////////////////////////////////////////////
	// 물류/ROBOT 자동 Interface Function
	///////////////////////////////////////////////////////////////////////
	BOOL Lf_aif_RobotWaitingCheck();
	BOOL Lf_aif_RearDoorOpen();
	BOOL Lf_aif_RearDoorClose();
	BOOL Lf_aif_RobotInSensorCheck();
	BOOL Lf_aif_RobotOutSensorCheck();
	BOOL Lf_aif_CarrierJigInCheck();
	BOOL Lf_aif_ClampLock();
	BOOL Lf_aif_ClampUnLock();
	BOOL Lf_aif_ClampLockCheck();
	BOOL Lf_aif_ClampUnLockCheck();
	void Lf_aif_ClampErrorDisplay(int checkType);
	BOOL Lf_aif_JigTiltingUp();
	BOOL Lf_aif_JigTiltingDown();
	BOOL Lf_aif_FrontDoorOpen();
	BOOL Lf_aif_FrontDoorClose();
	BOOL Lf_aif_FrontDoorHoldingOn();
	BOOL Lf_aif_FrontDoorHoldingOff();
	BOOL Lf_aif_FrontDoorHoldingOnCheck();
	BOOL Lf_aif_FrontDoorHoldingOffCheck();
	BOOL Lf_aif_CarrierJigOutCheck();




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
	afx_msg void OnBnClickedBtnTrTestStart();
	CButton m_btnTrTestStart;
};
