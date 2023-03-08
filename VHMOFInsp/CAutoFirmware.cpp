// CAutoFirmware.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CAutoFirmware.h"
#include "afxdialogex.h"


// CAutoFirmware 대화 상자

IMPLEMENT_DYNAMIC(CAutoFirmware, CDialog)

CAutoFirmware::CAutoFirmware(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_AUTO_FIRMWARE, pParent)
{

}

CAutoFirmware::~CAutoFirmware()
{
}

void CAutoFirmware::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROG_AF_PROGRESS, m_progAfProgress);
	DDX_Control(pDX, IDC_BTN_AF_DOWNLOAD_START, m_btnAfDownloadStart);
	DDX_Control(pDX, IDC_BTN_AF_CLOSE, m_btnAfClose);
	DDX_Control(pDX, IDC_CMB_AF_CH_SELECT, m_cmbAfChSelect);
	DDX_Control(pDX, IDC_CMB_AF_TARGET, m_cmbAfTarget);
}


BEGIN_MESSAGE_MAP(CAutoFirmware, CDialog)
	ON_BN_CLICKED(IDC_BTN_AF_FILE_OPEN, &CAutoFirmware::OnBnClickedBtnAfFileOpen)
	ON_BN_CLICKED(IDC_BTN_AF_READ_VERSION, &CAutoFirmware::OnBnClickedBtnAfReadVersion)
	ON_BN_CLICKED(IDC_BTN_AF_DOWNLOAD_START, &CAutoFirmware::OnBnClickedBtnAfDownloadStart)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_AF_CLOSE, &CAutoFirmware::OnBnClickedBtnAfClose)
END_MESSAGE_MAP()


// CAutoFirmware 메시지 처리기

BOOL CAutoFirmware::OnInitDialog()
{
	CDialog::OnInitDialog();
	lpInspWorkInfo = m_pApp->GetInspWorkInfo();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();
	Lf_InitDlgDesign();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAutoFirmware::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	for (int i = 0; i < COLOR_IDX_MAX; i++)
	{
		m_Brush[i].DeleteObject();
	}

	for (int i = 0; i < FONT_IDX_MAX; i++)
	{
		m_Font[i].DeleteObject();
	}
}


BOOL CAutoFirmware::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// Alt+F4 동작하지 않도록 한다.
	if (pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_F4)
	{
		if (::GetKeyState(VK_MENU) < 0)	return TRUE;
	}

	// 일반 Key 동작에 대한 Event
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
			case VK_RETURN:		return 1;
			case VK_ESCAPE:		return 1;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


HBRUSH CAutoFirmware::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (nCtlColor)
	{
		case CTLCOLOR_MSGBOX:
			break;
		case CTLCOLOR_EDIT:
			break;
		case CTLCOLOR_LISTBOX:
			break;
		case CTLCOLOR_SCROLLBAR:
			break;
		case CTLCOLOR_BTN:
			break;
		case CTLCOLOR_STATIC:
		{
			if (pWnd->GetDlgCtrlID() == IDC_STT_AF_TITLE)
			{
				pDC->SetBkColor(COLOR_DEEP_BLUE);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_DEEP_BLUE];
			}

			if ((pWnd->GetDlgCtrlID() == IDC_STT_AF_FILE_PATH)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_AF_READ_VERSION)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_AF_PROGRESS)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_AF_CH_SELECT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_AF_TARGET)
				)
			{
				pDC->SetBkColor(COLOR_BLUISH);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_BLUISH];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_AF_STATUS)
			{
				if (m_downloadStatus == 1)
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
				else if (m_downloadStatus == 2)
				{
					pDC->SetBkColor(COLOR_RED128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED128];
				}
				else
				{
					pDC->SetBkColor(COLOR_BLACK);
					pDC->SetTextColor(COLOR_CYAN);
					return m_Brush[COLOR_IDX_BLACK];
				}
			}

			break;
		}
	}	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CAutoFirmware::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}


void CAutoFirmware::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnTimer(nIDEvent);
}


void CAutoFirmware::OnBnClickedBtnAfFileOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_loadFirmwareFile();
}


void CAutoFirmware::OnBnClickedBtnAfReadVersion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int target = m_cmbAfTarget.GetCurSel();
	int ch = m_cmbAfChSelect.GetCurSel();

	if (target == FW_TARGET_MAIN_MCU)
	{
		m_pApp->m_sPgFWVersion[ch].Empty();
		GetDlgItem(IDC_EDT_AF_READ_VERSION)->SetWindowText(_T(""));
		delayMs(100);

		if (m_pApp->commApi->main_getCtrlFWVersion(ch) == TRUE)
		{
			GetDlgItem(IDC_EDT_AF_READ_VERSION)->SetWindowText(m_pApp->m_sPgFWVersion[ch]);
		}
		else
		{
			GetDlgItem(IDC_EDT_AF_READ_VERSION)->SetWindowText(_T("Fail"));
		}
	}
	if (target == FW_TARGET_POWER_MCU)
	{
		m_pApp->m_sPmmFWVersion[ch].Empty();
		GetDlgItem(IDC_EDT_AF_READ_VERSION)->SetWindowText(_T(""));
		delayMs(100);

		if (m_pApp->commApi->main_getPowerFWVersion(ch) == TRUE)
		{
			GetDlgItem(IDC_EDT_AF_READ_VERSION)->SetWindowText(m_pApp->m_sPmmFWVersion[ch]);
		}
		else
		{
			GetDlgItem(IDC_EDT_AF_READ_VERSION)->SetWindowText(_T("Fail"));
		}
	}
	if (target == FW_TARGET_QSPI_BOARD)
	{
		m_pApp->m_sQspiFWVersion[ch].Empty();
		GetDlgItem(IDC_EDT_AF_READ_VERSION)->SetWindowText(_T(""));
		delayMs(100);

		if (m_pApp->commApi->qspi_getFWVersion(ch) == TRUE)
		{
			GetDlgItem(IDC_EDT_AF_READ_VERSION)->SetWindowText(m_pApp->m_sQspiFWVersion[ch]);
		}
		else
		{
			GetDlgItem(IDC_EDT_AF_READ_VERSION)->SetWindowText(_T("Fail"));
		}
	}
}


void CAutoFirmware::OnBnClickedBtnAfDownloadStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int target = m_cmbAfTarget.GetCurSel();
	int ch = m_cmbAfChSelect.GetCurSel();

	if (GetDlgItem(IDC_EDT_AF_FILE_PATH)->GetWindowTextLength() == 0)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_60);
		return;
	}

	GetDlgItem(IDC_CMB_AF_TARGET)->EnableWindow(FALSE);
	GetDlgItem(IDC_CMB_AF_CH_SELECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_AF_FILE_OPEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_AF_READ_VERSION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_AF_DOWNLOAD_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_AF_CLOSE)->EnableWindow(FALSE);

	if (target == FW_TARGET_MAIN_MCU)			Lf_fwMainMcuDownloadStart(ch);
	else if (target == FW_TARGET_POWER_MCU)		Lf_fwPowerMcuDownloadStart(ch);
	else if (target == FW_TARGET_QSPI_BOARD)	Lf_fwQspiMcuDownloadStart(ch);

	GetDlgItem(IDC_CMB_AF_TARGET)->EnableWindow(TRUE);
	GetDlgItem(IDC_CMB_AF_CH_SELECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_AF_FILE_OPEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_AF_READ_VERSION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_AF_DOWNLOAD_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_AF_CLOSE)->EnableWindow(TRUE);
}

void CAutoFirmware::OnBnClickedBtnAfClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAutoFirmware::Lf_InitLocalValue()
{
	m_cmbAfTarget.SetCurSel(0);
	m_cmbAfChSelect.SetCurSel(0);
	m_downloadStatus = 0;

	m_pApp->m_nDownloadReadyAckCount = 0;					//Firmware Download ACK Receive Count 초기화.	
	m_nFirmwareDataLen = 0;									//Firmware File Length 초기화
	m_pFirmwareData = new BYTE[MAX_FILE_SIZE];				//Firmware File Buff Memory 1M 할당.
	ZeroMemory(m_pFirmwareData, MAX_FILE_SIZE);				//Buff Memory 초기화
}

void CAutoFirmware::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(32, 13, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_AF_TITLE)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(23, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_BTN_AF_DOWNLOAD_START)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_BTN_AF_CLOSE)->SetFont(&m_Font[2]);

	m_Font[3].CreateFont(22, 9, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_AF_FILE_PATH)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_EDT_AF_FILE_PATH)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_BTN_AF_FILE_OPEN)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_AF_READ_VERSION)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_EDT_AF_READ_VERSION)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_BTN_AF_READ_VERSION)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_AF_PROGRESS)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_AF_PERCENT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_AF_STATUS)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_AF_CH_SELECT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_CMB_AF_CH_SELECT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_AF_TARGET)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_CMB_AF_TARGET)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(17, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[5].CreateFont(16, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

}

void CAutoFirmware::Lf_InitColorBrush()
{
	// 각 Control의 COLOR 설정을 위한 Brush를 Setting 한다.
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush(COLOR_WHITE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_RED128].CreateSolidBrush(COLOR_RED128);
	m_Brush[COLOR_IDX_GREEN].CreateSolidBrush(COLOR_GREEN);
	m_Brush[COLOR_IDX_GREEN128].CreateSolidBrush(COLOR_GREEN128);
	m_Brush[COLOR_IDX_BLUE].CreateSolidBrush(COLOR_BLUE);
	m_Brush[COLOR_IDX_SEABLUE].CreateSolidBrush(COLOR_SEABLUE);
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_Brush[COLOR_IDX_VERDANT].CreateSolidBrush(COLOR_VERDANT);
	m_Brush[COLOR_IDX_JADEGREEN].CreateSolidBrush(COLOR_JADEGREEN);
	m_Brush[COLOR_IDX_JADEBLUE].CreateSolidBrush(COLOR_JADEBLUE);
	m_Brush[COLOR_IDX_JADERED].CreateSolidBrush(COLOR_JADERED);
	m_Brush[COLOR_IDX_LIGHT_RED].CreateSolidBrush(COLOR_LIGHT_RED);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush(COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_LIGHT_BLUE].CreateSolidBrush(COLOR_LIGHT_BLUE);
	m_Brush[COLOR_IDX_LIGHT_ORANGE].CreateSolidBrush(COLOR_LIGHT_ORANGE);
	m_Brush[COLOR_IDX_DARK_RED].CreateSolidBrush(COLOR_DARK_RED);
	m_Brush[COLOR_IDX_DARK_ORANGE].CreateSolidBrush(COLOR_DARK_ORANGE);
	m_Brush[COLOR_IDX_GRAY128].CreateSolidBrush(COLOR_GRAY128);
	m_Brush[COLOR_IDX_GRAY159].CreateSolidBrush(COLOR_GRAY159);
	m_Brush[COLOR_IDX_GRAY224].CreateSolidBrush(COLOR_GRAY224);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
}

void CAutoFirmware::Lf_InitDlgDesign()
{
	// Button ICON
 	m_btnAfDownloadStart.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
 	m_btnAfClose.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DISABLE));
}

void CAutoFirmware::Lf_readyInitialize()
{
	m_pApp->m_nDownloadReadyAckCount = 0;				//Firmware Download ACK Receive Count 초기화.
}

void CAutoFirmware::Lf_loadFirmwareFile()
{
	CString m_sFirmwarePath;
	CString m_sFileType;
	TCHAR szFilePath[1024] = { 0, };

	GetCurrentDirectory(sizeof(szFilePath), szFilePath);

	if (m_cmbAfTarget.GetCurSel() == FW_TARGET_MAIN_MCU)
	{
		m_sFileType = _T("Intel Hex File(App_MI20_0301_T8LC_HAL*.Hex;*.a90)|App_MI20_0301_T8LC_HAL*.HEX;*.a9|All File(*.*)|*.*|");
 	}
	else if (m_cmbAfTarget.GetCurSel() == FW_TARGET_POWER_MCU)
	{
		m_sFileType = m_sFileType = _T("Binary File(*.bin;*.a90)|*.BIN;*.a9|All File(*.*)|*.*|");
	}

	CFileDialog m_ldFile(TRUE, _T("hex|*"), NULL, OFN_READONLY, m_sFileType);

	if (m_ldFile.DoModal() == IDOK)
	{
		m_sFirmwarePath = m_ldFile.GetPathName();

		GetDlgItem(IDC_EDT_AF_FILE_PATH)->SetWindowText(m_sFirmwarePath);
		if (m_cmbAfTarget.GetCurSel() == FW_TARGET_MAIN_MCU)
		{
			Lf_readFirmwareFile(m_sFirmwarePath);
		}
		else if (m_cmbAfTarget.GetCurSel() == FW_TARGET_POWER_MCU)
		{
			Lf_readPmmFile(m_sFirmwarePath);
		}
	}
	SetCurrentDirectory(szFilePath);
}

void CAutoFirmware::Lf_readFirmwareFile(CString strFilePath)
{
	CStdioFile* pFile;
	pFile = new CStdioFile();

	// File을 Open한다.
	if (pFile->Open(strFilePath, CStdioFile::modeRead | CStdioFile::typeText) == NULL)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FILE OPEN FAIL"), ERROR_CODE_20);
		delete pFile;
		return;
	}

	// Firmware Data를 저장할 Buff 할당하고 초기화 한다.
	unsigned long filesize;
	filesize = (unsigned long)pFile->GetLength();
	szParsingData = (unsigned char*)malloc(filesize * sizeof(unsigned char));
	memset((char*)szParsingData, 0, filesize);

	// Firmware Data를 저장할 Buff를 초기화 한다.
	m_nFirmwareDataLen = 0;								//Firmware File Length 초기화

	// Line이 Null일때까지 읽는다.
	CString lineString;
	CString recStart, recData;
	int recLength, recOffset, recType, recChksum;
	while (pFile->ReadString(lineString) == TRUE)
	{
		recStart = lineString.Left(1);
		recChksum = _tcstol(lineString.Right(2), NULL, 16);

		// 레코드의 시작문자(:)를 확인한다.
		if (recStart == ":")
		{
			recLength = _tcstol(lineString.Mid(1, 2), NULL, 16);
			recOffset = _tcstol(lineString.Mid(3, 4), NULL, 16);
			recType = _tcstol(lineString.Mid(7, 2), NULL, 16);
			recData = lineString.Mid(9, (recLength * 2));

			//00 - Data record 
			//01 - End of file record 
			//02 - Extended segment address record 
			//03 - Start segment address record 
			//04 - Extended linear address record 
			//05 - Start linear address record 
			if (recType == 0x01)
			{	// 파일의 끝이므로 종료.
				break;
			}
			else if ((recType == 0x02) || (recType == 0x04))
			{	// Address Record는 Data에 포함하지 않는다.
			}
			else
			{	// Data Record를 Parsing한다.
				Lf_parseDataRecord(recData, &szParsingData[m_nFirmwareDataLen]);
				m_nFirmwareDataLen += recLength;
			}
		}
		else
		{
			m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FILE TYPE ERROR"), ERROR_CODE_21);
			// Data Buff Memory를 초기화 한다.
			memset((char*)szParsingData, 0, filesize);
			// Data Length를 초기화 한다.
			m_nFirmwareDataLen = 0;
		}
	}

	// File을 닫는다.
	pFile->Close();
	delete pFile;
}

void CAutoFirmware::Lf_parseDataRecord(CString strRecord, BYTE* pData)
{
	int nLen = 0;
	int point = 0;

	nLen = strRecord.GetLength() / 2;
	for (int i = 0; i < nLen; i++)
	{
		*pData = (BYTE)_tcstol(strRecord.Mid(point, 2), NULL, 16);

		point += 2;
		pData++;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main Board MCU Firmware Download
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CAutoFirmware::Lf_checkDownloadReady1(int ch)
{
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("Go To Boot Section!"));
	m_pApp->m_nDownloadReadyAckCount = 0;

	for (int i = 0; i < 5; i++)
	{
		m_pApp->m_nDownloadCountUp = TRUE;
		m_pApp->commApi->main_setGoToBootSection(ch);
		delayMs(200);

		if (m_pApp->m_nDownloadReadyAckCount >= 3)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CAutoFirmware::Lf_TcpReConnection(int ch)
{
	BOOL bRet = FALSE;
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("TCP/IP ReConnection!"));

	m_pApp->m_pSocketTCPMain->tcp_Main_DisConnection(ch);
	delayMs(200);
	
	for (int cnt = 0; cnt < 2; cnt++)
	{
		if (ch == CH1)
		{
			bRet = m_pApp->m_pSocketTCPMain->tcp_Main_Connection(TCP_MAIN1_MCU_IP, TCP_MAIN_PORT, CH1);
		}
		else if (ch == CH2)
		{
			bRet = m_pApp->m_pSocketTCPMain->tcp_Main_Connection(TCP_MAIN2_MCU_IP, TCP_MAIN_PORT, CH2);
		}

		if (bRet == TRUE)
			break;
	}

	return bRet;
}

BOOL CAutoFirmware::Lf_checkDownloadReady2(int ch)
{
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("Firmware Download Ready Check (Boot)"));
	m_pApp->m_nDownloadReadyAckCount = 0;

	for (int i = 0; i < 10; i++)
	{
		m_pApp->m_nDownloadCountUp = TRUE;
		m_pApp->commApi->main_setGoToBootSection(ch);
		delayMs(200);

		if (m_pApp->m_nDownloadReadyAckCount >= 5)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CAutoFirmware::Lf_sendFirmwareFile(int ch)
{
	BOOL bRet = FALSE;
	int startAddr = 0;
	int packetLen = 0;
	char szpacket[4096] = { 0, };
	CString strpacket = _T("");
	int nsize = 0;

	int nProg, nLoop = 0;
	int nsendPageCnt = 0;
	int nRemainPageCnt = 0;
	char szTempBuf[4096];

	nsendPageCnt = m_nFirmwareDataLen / FW_PACKET_SIZE;
	nRemainPageCnt = m_nFirmwareDataLen % FW_PACKET_SIZE;

	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("File Downloading!"));

	for (nLoop = 0; nLoop < nsendPageCnt; nLoop++)
	{
		memset((char*)szTempBuf, 0, sizeof(szTempBuf));

		startAddr = nLoop * FW_PACKET_SIZE;
		sprintf_s(szTempBuf, "%05X", startAddr);

		packetLen = (int)strlen(szTempBuf);

		memcpy((char*)(&szTempBuf[packetLen]), (char*)(szParsingData + (nLoop * FW_PACKET_SIZE)), FW_PACKET_SIZE);

		bRet = m_pApp->commApi->main_setDownloadFirmware(ch, (char*)szTempBuf, (packetLen + FW_PACKET_SIZE));

		nProg = (startAddr * 100) / m_nFirmwareDataLen;
		m_progAfProgress.SetPos(nProg);
		CString strPro;
		strPro.Format(_T("( %d %% )"), nProg);
		GetDlgItem(IDC_STT_AF_PERCENT)->SetWindowText(strPro);

		if (bRet == FALSE)
		{
			//free(szParsingData);
			return FALSE;
		}

		delayMs(1);
	}
	if (nRemainPageCnt != 0)
	{
		memset((char*)szTempBuf, 0, sizeof(szTempBuf));

		startAddr = nLoop * FW_PACKET_SIZE;
		sprintf_s(szTempBuf, "%05X", startAddr);

		packetLen = (int)strlen(szTempBuf);

		memcpy((char*)(&szTempBuf[packetLen]), (char*)(szParsingData + (nLoop * FW_PACKET_SIZE)), FW_PACKET_SIZE);

		bRet = m_pApp->commApi->main_setDownloadFirmware(ch, (char*)szTempBuf, (packetLen + FW_PACKET_SIZE));

		nProg = (startAddr * 100) / m_nFirmwareDataLen;
		m_progAfProgress.SetPos(nProg);

		CString strPro;
		strPro.Format(_T("( %d %% )"), nProg);
		GetDlgItem(IDC_STT_AF_PERCENT)->SetWindowText(strPro);

		if (bRet == FALSE)
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CAutoFirmware::Lf_sendDownloadComplete(int ch)
{
	return m_pApp->commApi->main_setDownloadComplete(ch);
}

BOOL CAutoFirmware::Lf_fwMainMcuDownloadStart(int ch)
{
	m_progAfProgress.SetPos(0);
	int nRetryCount = 0;

	m_downloadStatus = 0;
	GetDlgItem(IDC_STT_AF_STATUS)->Invalidate(FALSE);

	// Step1. Download Ready Check - App
	if (Lf_checkDownloadReady1(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_22);
		goto FW_MAIN_MCU_ERR_EXCEPT;
	}

	// Step2. TCP ReConnection - BootSection
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("Wait 5Sec..."));
	delayMs(5000);
	if (Lf_TcpReConnection(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_23);
		goto FW_MAIN_MCU_ERR_EXCEPT;
	}

	// Step3. Download Ready Check - Boot
	if (Lf_checkDownloadReady2(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_24);
		goto FW_MAIN_MCU_ERR_EXCEPT;
	}

	// Step4. Download Start
	delayMs(100);
	if (Lf_sendFirmwareFile(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_25);
		goto FW_MAIN_MCU_ERR_EXCEPT;
	}

	// Step5. Download Complete Check
	delayMs(100);
	if (Lf_sendDownloadComplete(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_26);
		goto FW_MAIN_MCU_ERR_EXCEPT;
	}

	// Step6. TCP ReConnection - App Section
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("Wait 5Sec..."));
	delayMs(5000);
	if (Lf_TcpReConnection(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_27);
		goto FW_MAIN_MCU_ERR_EXCEPT;
	}

	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("Firmware Download Complete!"));

	// Step4. Download Initialize & Ready
	Lf_readyInitialize();

	m_progAfProgress.SetPos(100);
	GetDlgItem(IDC_STT_AF_PERCENT)->SetWindowText(_T("( 100 % )"));

	m_downloadStatus = 1;
	GetDlgItem(IDC_STT_AF_STATUS)->Invalidate(FALSE);

	return TRUE;

FW_MAIN_MCU_ERR_EXCEPT:
	// Error Exception. Initialize.
	Lf_readyInitialize();
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("Firmware Download Error."));

	m_downloadStatus = 2;
	GetDlgItem(IDC_STT_AF_STATUS)->Invalidate(FALSE);

	return FALSE;
}



/*********************************************************************************************************************************************/
// Power Module MCU 관련 함수.
/*********************************************************************************************************************************************/
void CAutoFirmware::Lf_readPmmFile(CString strFilePath)
{
	CFile mFile;
	BYTE version[8] = { 0, };
	UINT index = 0;
	CString sMsg;

	m_nFrameCount = 0;
	m_nFirmwareDataLen = 0;
	memset(m_pFirmwareData, NULL, MAX_FILE_SIZE);

	if (mFile.Open(strFilePath, CFile::modeRead) == FALSE)
	{
		sMsg.Format(_T("<FILE> Power MCU Firmware File read fail. (%s)"), strFilePath);
		m_pApp->Gf_writeMLog(sMsg);
		return;
	}

	m_nFirmwareDataLen = (UINT)mFile.GetLength();
	mFile.Read((void*)m_pFirmwareData, m_nFirmwareDataLen);
	mFile.Close();

	m_nFrameCount = (m_nFirmwareDataLen / POWER_FW_PACKET_SIZE) + 1;

}

BOOL CAutoFirmware::Lf_checkPmmDownloadReady1(int ch)
{
	BOOL ret = FALSE;
	int length = 0;
	char szPacket[4096] = { 0, };
	unsigned char calc_CRC8 = 0;

	sprintf_s(szPacket, "%c1W0000", 0x02);
	length = (int)strlen(szPacket);
	calc_CRC8 = m_pApp->commApi->CRC8_Calc((BYTE*)&szPacket[1], length - 1);

	sprintf_s(&szPacket[length], 4096 - length, "%02X%c", calc_CRC8, 0x03);
	length = (int)strlen(szPacket);

	ret = m_pApp->commApi->main_setSendQuery(CMD_CTRL_TRANSFER_TO_POWER, length, szPacket, ch);

	return lpInspWorkInfo->m_nPmmAck;
}

BOOL CAutoFirmware::Lf_checkPmmDownloadReady2(int ch)
{
	BOOL ret = FALSE;
	int length = 0;
	char szPacket[4096] = { 0, };
	unsigned char calc_CRC8 = 0;

	sprintf_s(szPacket, "%c1X", 0x02);
	length = (int)strlen(szPacket);
	calc_CRC8 = m_pApp->commApi->CRC8_Calc((BYTE*)&szPacket[1], length - 1);

	sprintf_s(&szPacket[length], 4096 - length, "%02X%c", calc_CRC8, 0x03);
	length = (int)strlen(szPacket);

	ret = m_pApp->commApi->main_setSendQuery(CMD_CTRL_TRANSFER_TO_POWER, length, szPacket, ch);

	return lpInspWorkInfo->m_nPmmAck;
}

BOOL CAutoFirmware::Lf_sendPmmFirmwareFile(int ch)
{
	BOOL bRet = FALSE;
	BOOL bFirstTime = TRUE;
	int startAddr = 0, packetLen = 0;
	int packetLen_temp = POWER_FW_PACKET_SIZE;
	int sendcnt = 1, length = 0, nPos;
	char szpacket[4096] = { 0, };
	CString sPer;
	CString sMsg;
	unsigned char calc_CRC8 = 0;

	while (1)
	{
		lpInspWorkInfo->m_nPmmAck = FALSE;

		if ((startAddr + packetLen_temp) <= m_nFirmwareDataLen)
		{
			sprintf_s(szpacket, "%c1Y%04d%02d%02d", 0x02, POWER_FW_PACKET_SIZE, sendcnt, m_nFrameCount);

			memcpy(&szpacket[11], (char*)&m_pFirmwareData[startAddr], packetLen_temp);
			length = 11 + packetLen_temp;
			calc_CRC8 = m_pApp->commApi->CRC8_Calc((BYTE*)&szpacket[1], length - 1);

			sprintf_s(&szpacket[length], 4096 - length, "%02X%c", calc_CRC8, 0x03);
			length += 3;// CRC8값과 ETX자리수를 더해 준다.

			// 주의 //
			// Power F/W는 절대 Retry 금지 //
			m_pApp->commApi->main_setSendQuery(CMD_CTRL_TRANSFER_TO_POWER, length, szpacket, ch);
			if (lpInspWorkInfo->m_nPmmAck == FALSE)
			{
				return FALSE;
			}
		}
		else
		{
			sprintf_s(szpacket, "%c1Y%04d%02d%02d", 0x02, (m_nFirmwareDataLen - startAddr), sendcnt, m_nFrameCount);

			memcpy(&szpacket[11], (char*)&m_pFirmwareData[startAddr], (m_nFirmwareDataLen - startAddr));
			length = 11 + (m_nFirmwareDataLen - startAddr);
			calc_CRC8 = m_pApp->commApi->CRC8_Calc((BYTE*)&szpacket[1], length - 1);

			sprintf_s(&szpacket[length], 4096 - length, "%02X%c", calc_CRC8, 0x03);
			length += 3;// CRC8값과 ETX자리수를 더해 준다.

			// 주의 //
			// Power F/W는 절대 Retry 금지 //
			m_pApp->commApi->main_setSendQuery(CMD_CTRL_TRANSFER_TO_POWER, length, szpacket, ch);
			if (lpInspWorkInfo->m_nPmmAck == FALSE)
			{
				return FALSE;
			}

			startAddr += (m_nFirmwareDataLen - startAddr);

			nPos = (startAddr * 100) / m_nFirmwareDataLen;
			m_progAfProgress.SetPos(nPos);

			sPer.Format(_T("(%d%%)"), nPos);
			GetDlgItem(IDC_STT_AF_PERCENT)->SetWindowText(sPer);
			break;
		}

		sendcnt++;
		ZeroMemory(szpacket, sizeof(szpacket));
		startAddr += packetLen_temp;

		nPos = (startAddr * 100) / m_nFirmwareDataLen;
		m_progAfProgress.SetPos(nPos);

		sPer.Format(_T("(%d%%)"), nPos);
		GetDlgItem(IDC_STT_AF_PERCENT)->SetWindowText(sPer);

		sMsg.Format(_T("Power F/W Raw File Downloading. Send Data (%d/%d)"), startAddr + packetLen_temp, m_nFirmwareDataLen);
		GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(sMsg);

		delayMs(1);

		if (bFirstTime == TRUE)
		{
			bFirstTime = FALSE;
			delayMs(1000);
		}
		else
		{
			delayMs(100);
		}
	}

	return TRUE;
}

BOOL CAutoFirmware::Lf_sendPmmDownloadComplete(int ch)
{
	BOOL ret = FALSE;
	int length = 0;
	char szPacket[4096] = { 0, };
	unsigned char calc_CRC8 = 0;
	unsigned short crc16 = 0;
	CString sMsg;

	crc16 = m_pApp->commApi->CRC16_Calc((BYTE*)m_pFirmwareData, m_nFirmwareDataLen);

	sprintf_s(szPacket, "%c1Z%02d%04X", 0x02, m_nFrameCount, crc16);
	length = (int)strlen(szPacket);
	calc_CRC8 = m_pApp->commApi->CRC8_Calc((BYTE*)&szPacket[1], length - 1);

	sprintf_s(&szPacket[length], 4096 - length, "%02X%c", calc_CRC8, 0x03);
	length = (int)strlen(szPacket);

	for (int retryCnt = 0; retryCnt < 10; retryCnt++)
	{
		m_pApp->commApi->main_setSendQuery(CMD_CTRL_TRANSFER_TO_POWER, length, szPacket, ch);

		if (lpInspWorkInfo->m_nPmmAck == FALSE)
		{
			sMsg.Format(_T("Power Firmware Download Complete check.Retry Count(%d)"), retryCnt);
			GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(sMsg);

			delayMs(100);
			continue;
		}

		break;
	}


	return lpInspWorkInfo->m_nPmmAck;
}


BOOL CAutoFirmware::Lf_fwPowerMcuDownloadStart(int ch)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bRet = FALSE;
	CString sdata;
	int i = 0;

	m_downloadStatus = 0;
	GetDlgItem(IDC_STT_AF_STATUS)->Invalidate(FALSE);

	// Step1.download status check
	if (Lf_checkPmmDownloadReady1(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_61);
		goto FW_POWER_MCU_ERR_EXCEPT;
	}
	delayMs(1000);

	// Step2.download status check2
	if (Lf_checkPmmDownloadReady2(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_62);
		goto FW_POWER_MCU_ERR_EXCEPT;
	}

	// Step3. Flash에bin Data를 Write 한다.
	if (Lf_sendPmmFirmwareFile(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_63);
		goto FW_POWER_MCU_ERR_EXCEPT;
	}

	// Step6. Flash의 Write Protect 기능을 ON 시킨다.
	if (Lf_sendPmmDownloadComplete(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_64);
		goto FW_POWER_MCU_ERR_EXCEPT;
	}

	GetDlgItem(IDC_STT_AF_PERCENT)->SetWindowText(_T("(100%)"));
	m_progAfProgress.SetPos(100);

	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("Firmware Download Complete"));

	m_downloadStatus = 1;
	GetDlgItem(IDC_STT_AF_STATUS)->Invalidate(FALSE);

	return TRUE;


FW_POWER_MCU_ERR_EXCEPT:
	// Error Exception. Initialize.
	Lf_readyInitialize();
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("Firmware Download Error"));

	m_downloadStatus = 2;
	GetDlgItem(IDC_STT_AF_STATUS)->Invalidate(FALSE);

	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QSPI Board MCU Firmware Download
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CAutoFirmware::Lf_QSpi_checkDownloadReady1(int ch)
{
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("QSPI Go To Boot Section!"));
	m_pApp->m_nDownloadReadyAckCount = 0;

	for (int i = 0; i < 5; i++)
	{
		m_pApp->m_nDownloadCountUp = TRUE;
		m_pApp->commApi->qspi_setGoToBootSection(ch);
		delayMs(200);

		if (m_pApp->m_nDownloadReadyAckCount >= 3)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CAutoFirmware::Lf_QSpi_TcpReConnection(int ch)
{
	BOOL bRet = FALSE;
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("QSPI TCP/IP ReConnection!"));

	m_pApp->m_pSocketTCPMain->tcp_SPI_DisConnection(ch);
	delayMs(200);

	for (int cnt = 0; cnt < 2; cnt++)
	{
		if (ch == CH1)
		{
			bRet = m_pApp->m_pSocketTCPMain->tcp_SPI_Connection(TCP_SPI_BOARD1_IP, TCP_SPI_PORT, CH1);
		}
		else if (ch == CH2)
		{
			bRet = m_pApp->m_pSocketTCPMain->tcp_SPI_Connection(TCP_SPI_BOARD2_IP, TCP_SPI_PORT, CH2);
		}

		if (bRet == TRUE)
			break;
	}

	return bRet;
}

BOOL CAutoFirmware::Lf_QSpi_checkDownloadReady2(int ch)
{
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("QSPI Firmware Download Ready Check (Boot)"));
	m_pApp->m_nDownloadReadyAckCount = 0;

	for (int i = 0; i < 10; i++)
	{
		m_pApp->m_nDownloadCountUp = TRUE;
		m_pApp->commApi->qspi_setGoToBootSection(ch);
		delayMs(200);

		if (m_pApp->m_nDownloadReadyAckCount >= 5)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CAutoFirmware::Lf_QSpi_sendFirmwareFile(int ch)
{
	BOOL bRet = FALSE;
	int startAddr = 0;
	int packetLen = 0;
	char szpacket[4096] = { 0, };
	CString strpacket = _T("");
	int nsize = 0;

	int nProg, nLoop = 0;
	int nsendPageCnt = 0;
	int nRemainPageCnt = 0;
	char szTempBuf[4096];

	nsendPageCnt = m_nFirmwareDataLen / FW_PACKET_SIZE;
	nRemainPageCnt = m_nFirmwareDataLen % FW_PACKET_SIZE;

	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("Firmware File Downloading!"));

	for (nLoop = 0; nLoop < nsendPageCnt; nLoop++)
	{
		memset((char*)szTempBuf, 0, sizeof(szTempBuf));

		startAddr = nLoop * FW_PACKET_SIZE;
		sprintf_s(szTempBuf, "%05X", startAddr);

		packetLen = (int)strlen(szTempBuf);

		memcpy((char*)(&szTempBuf[packetLen]), (char*)(szParsingData + (nLoop * FW_PACKET_SIZE)), FW_PACKET_SIZE);

		bRet = m_pApp->commApi->qspi_setDownloadFirmware(ch, (char*)szTempBuf, (packetLen + FW_PACKET_SIZE));

		nProg = (startAddr * 100) / m_nFirmwareDataLen;
		m_progAfProgress.SetPos(nProg);
		CString strPro;
		strPro.Format(_T("( %d %% )"), nProg);
		GetDlgItem(IDC_STT_AF_PERCENT)->SetWindowText(strPro);

		if (bRet == FALSE)
		{
			//free(szParsingData);
			return FALSE;
		}

		delayMs(1);
	}
	if (nRemainPageCnt != 0)
	{
		memset((char*)szTempBuf, 0, sizeof(szTempBuf));

		startAddr = nLoop * FW_PACKET_SIZE;
		sprintf_s(szTempBuf, "%05X", startAddr);

		packetLen = (int)strlen(szTempBuf);

		memcpy((char*)(&szTempBuf[packetLen]), (char*)(szParsingData + (nLoop * FW_PACKET_SIZE)), FW_PACKET_SIZE);

		bRet = m_pApp->commApi->qspi_setDownloadFirmware(ch, (char*)szTempBuf, (packetLen + FW_PACKET_SIZE));

		nProg = (startAddr * 100) / m_nFirmwareDataLen;
		m_progAfProgress.SetPos(nProg);

		CString strPro;
		strPro.Format(_T("( %d %% )"), nProg);
		GetDlgItem(IDC_STT_AF_PERCENT)->SetWindowText(strPro);

		if (bRet == FALSE)
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CAutoFirmware::Lf_QSpi_sendDownloadComplete(int ch)
{
	return m_pApp->commApi->qspi_setDownloadComplete(ch);
}

BOOL CAutoFirmware::Lf_fwQspiMcuDownloadStart(int ch)
{
	m_progAfProgress.SetPos(0);
	int nRetryCount = 0;

	m_downloadStatus = 0;
	GetDlgItem(IDC_STT_AF_STATUS)->Invalidate(FALSE);

	// Step1. Download Ready Check - App
	if (Lf_QSpi_checkDownloadReady1(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("QSPI FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_22);
		goto FW_QSPI_MCU_ERR_EXCEPT;
	}

	// Step2. TCP ReConnection - BootSection
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("Wait 5Sec..."));
	delayMs(5000);
	if (Lf_QSpi_TcpReConnection(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("QSPI FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_23);
		goto FW_QSPI_MCU_ERR_EXCEPT;
	}

	// Step3. Download Ready Check - Boot
	if (Lf_QSpi_checkDownloadReady2(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("QSPI FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_24);
		goto FW_QSPI_MCU_ERR_EXCEPT;
	}

	// Step4. Download Start
	delayMs(100);
	if (Lf_QSpi_sendFirmwareFile(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("QSPI FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_25);
		goto FW_QSPI_MCU_ERR_EXCEPT;
	}

	// Step5. Download Complete Check
	delayMs(100);
	if (Lf_QSpi_sendDownloadComplete(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("QSPI FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_26);
		goto FW_QSPI_MCU_ERR_EXCEPT;
	}

	// Step6. TCP ReConnection - App Section
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("Wait 5Sec..."));
	delayMs(5000);
	if (Lf_QSpi_TcpReConnection(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("QSPI FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_27);
		goto FW_QSPI_MCU_ERR_EXCEPT;
	}

	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("QSPI Firmware Download Complete!"));

	// Step4. Download Initialize & Ready
	Lf_readyInitialize();

	m_progAfProgress.SetPos(100);
	GetDlgItem(IDC_STT_AF_PERCENT)->SetWindowText(_T("( 100 % )"));

	m_downloadStatus = 1;
	GetDlgItem(IDC_STT_AF_STATUS)->Invalidate(FALSE);

	return TRUE;

FW_QSPI_MCU_ERR_EXCEPT:
	// Error Exception. Initialize.
	Lf_readyInitialize();
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("QSPI Firmware Download Error."));

	m_downloadStatus = 2;
	GetDlgItem(IDC_STT_AF_STATUS)->Invalidate(FALSE);

	return FALSE;
}

