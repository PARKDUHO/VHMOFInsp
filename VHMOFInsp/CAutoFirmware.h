#pragma once

#define MAX_FILE_SIZE		1024*1024		// 최대 1M Buff 할당.
#define MAX_DATASIZE		400000			// FW File에서 읽을 수있는 최대 크기
#define FW_PACKET_SIZE		1024

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


///////////////////////////////////////////////////////////////////////////
// 사용자 정의 Function
///////////////////////////////////////////////////////////////////////////
public:


protected:
	LPINSPWORKINFO lpInspWorkInfo;
	void Lf_InitLocalValue();
	void Lf_InitFontset();
	void Lf_InitColorBrush();
	void Lf_InitDlgDesign();

	void Lf_readyInitialize();

	// MCU Firmware File Load
	void Lf_loadFirmwareFile();
	void Lf_readFirmwareFile(CString strFilePath);
	void Lf_parseDataRecord(CString strRecord, BYTE* pData);

	// MCU Firmware Download
	BOOL Lf_checkDownloadReady1(int ch);
	BOOL Lf_TcpReConnection(int ch);
	BOOL Lf_checkDownloadReady2(int ch);
	BOOL Lf_sendFirmwareFile(int ch);
	BOOL Lf_sendDownloadComplete(int ch);
	BOOL Lf_firmwareDownloadStart(int ch);

	int	  m_nFirmwareDataLen;
	BYTE* m_pFirmwareData;
	BYTE* szParsingData;


private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


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
	CButton m_btnAfClose;
	afx_msg void OnBnClickedBtnAfClose();
	CComboBox m_cmbAfChSelect;
};
