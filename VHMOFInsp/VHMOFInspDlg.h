
// VHMOFInspDlg.h: 헤더 파일
//

#pragma once


// CVHMOFInspDlg 대화 상자
class CVHMOFInspDlg : public CDialogEx
{
// 생성입니다.
public:
	CVHMOFInspDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VHMOFINSP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnUdpReceiveDio(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()



///////////////////////////////////////////////////////////////////////////
// 사용자 정의 Function
///////////////////////////////////////////////////////////////////////////
public:
// 	void Lf_InitLocalValue();
// 	void Lf_InitFontset();
// 	void Lf_InitColorBrush();


protected:
	LPSYSTEMINFO		lpSystemInfo;
	LPMODELINFO			lpModelInfo;
	LPINSPWORKINFO		lpInspWorkInfo;

	void Lf_InitFontSet();
	void Lf_InitColorBrush();
	void Lf_InitProgramTitle();
	void Lf_InitItemValue();

	void Lf_updateSystemInfo();
	void Lf_openToDayMLog();

	void Lf_updateIOStautsDIN1();
	void Lf_updateIOStautsDIN2();
	void Lf_checkExtAlarmDio1();
	void Lf_checkExtAlarmDio2();
	void Lf_checkRobotInSensor();

	void Lf_updateMaQuantityCount();

	void Lf_InitListDin();

	BOOL m_bRobotInLedStatus;

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////




public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBitmapButton m_btnMainUserID;
	CBitmapButton m_btnMainModelChange;
	CBitmapButton m_btnMainModelInfo;
	CBitmapButton m_btnMainTest;
	CBitmapButton m_btnMainMaint;
	CBitmapButton m_btnMainSystem;
	CBitmapButton m_btnMainInitial;
	CBitmapButton m_btnMainFirmware;
	CBitmapButton m_btnMainErrorList;
	CBitmapButton m_btnMainExit;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_sttMainMlogView;
	afx_msg LRESULT OnUpdateSystemInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateQuantity(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnMaUserid();
	afx_msg void OnBnClickedBtnMaModelChange();
	afx_msg void OnBnClickedBtnMaModelInfo();
	afx_msg void OnBnClickedBtnMaTest();
	afx_msg void OnBnClickedBtnMaMaint();
	afx_msg void OnBnClickedBtnMaSystem();
	afx_msg void OnBnClickedBtnMaInitial();
	afx_msg void OnBnClickedBtnMaFirmware();
	afx_msg void OnBnClickedBtnMaErrorList();
	afx_msg void OnBnClickedBtnMaExit();
	afx_msg void OnBnClickedBtnDioCtrlLedOff();
	afx_msg void OnBnClickedBtnDioCtrlLedOn();
	afx_msg void OnStnClickedSttMaQtyReset();
	afx_msg void OnStnClickedSttMaQtyResetCh1();
	afx_msg void OnStnClickedSttMaQtyResetCh2();
	afx_msg void OnBnClickedBtnDioCtrlMuteOff();
	afx_msg void OnBnClickedBtnDioCtrlMuteOn();
	afx_msg void OnBnClickedBtnDioCtrlDoorOpen();
	CListCtrl m_lstMaDinListA;
	CListCtrl m_lstMaDinListB;
	afx_msg void OnNMCustomdrawLstMaDinListA(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawLstMaDinListB(NMHDR* pNMHDR, LRESULT* pResult);
};
