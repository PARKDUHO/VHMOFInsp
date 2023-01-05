#pragma once


// CAutoFirmware 대화 상자

class CAutoFirmware : public CDialog
{
	DECLARE_DYNAMIC(CAutoFirmware)

public:
	CAutoFirmware(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAutoFirmware();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_FIRMWARE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_progAfProgress;
	CButton m_btnAfDownloadStart;
	afx_msg void OnBnClickedBtnAfFileOpen();
	afx_msg void OnBnClickedBtnAfReadVersion();
	afx_msg void OnBnClickedBtnAfDownloadStart();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
