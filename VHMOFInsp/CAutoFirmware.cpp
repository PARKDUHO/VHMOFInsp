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
				pDC->SetBkColor(COLOR_BLACK);
				pDC->SetTextColor(COLOR_CYAN);
				return m_Brush[COLOR_IDX_BLACK];
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
	if (target == FW_TARGET_MAIN_FPGA)
	{

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

	GetDlgItem(IDC_BTN_AF_FILE_OPEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_AF_READ_VERSION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_AF_DOWNLOAD_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_AF_CLOSE)->EnableWindow(FALSE);

	Lf_firmwareDownloadStart(ch);

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
	TCHAR szFilePath[1024] = { 0, };

	GetCurrentDirectory(sizeof(szFilePath), szFilePath);

	CFileDialog m_ldFile(TRUE, _T("hex|*"), NULL, OFN_READONLY, _T("Intel Hex File(*.hex)|*.hex|All File(*.*)|*.*|"));

	if (m_ldFile.DoModal() == IDOK)
	{
		m_sFirmwarePath = m_ldFile.GetPathName();

		GetDlgItem(IDC_EDT_AF_FILE_PATH)->SetWindowText(m_sFirmwarePath);
		Lf_readFirmwareFile(m_sFirmwarePath);
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

		ProcessMessage();
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

BOOL CAutoFirmware::Lf_firmwareDownloadStart(int ch)
{
	m_progAfProgress.SetPos(0);
	int nRetryCount = 0;

	// Step1. Download Ready Check - App
	if (Lf_checkDownloadReady1(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_22);
		goto ERR_EXCEPT;
	}

	// Step2. TCP ReConnection - BootSection
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("Wait 5Sec..."));
	delayMs(5000);
	if (Lf_TcpReConnection(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_23);
		goto ERR_EXCEPT;
	}

	// Step3. Download Ready Check - Boot
	if (Lf_checkDownloadReady2(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_24);
		goto ERR_EXCEPT;
	}

	// Step4. Download Start
	delayMs(100);
	if (Lf_sendFirmwareFile(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_25);
		goto ERR_EXCEPT;
	}

	// Step5. Download Complete Check
	delayMs(100);
	if (Lf_sendDownloadComplete(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_26);
		goto ERR_EXCEPT;
	}

	// Step6. TCP ReConnection - App Section
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("Wait 5Sec..."));
	delayMs(5000);
	if (Lf_TcpReConnection(ch) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FIRMWARE DOWNLOAD FAIL"), ERROR_CODE_27);
		goto ERR_EXCEPT;
	}

	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T("Firmware Download Complete!"));

	// Step4. Download Initialize & Ready
	Lf_readyInitialize();

	m_progAfProgress.SetPos(100);
	GetDlgItem(IDC_STT_AF_PERCENT)->SetWindowText(_T("( 100 % )"));

	return TRUE;

ERR_EXCEPT:
	// Error Exception. Initialize.
	Lf_readyInitialize();
	GetDlgItem(IDC_STT_AF_STATUS)->SetWindowText(_T(""));

	return FALSE;
}



