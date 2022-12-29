// CInitialize.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CInitialize.h"
#include "afxdialogex.h"


// CInitialize 대화 상자

IMPLEMENT_DYNAMIC(CInitialize, CDialogEx)

CInitialize::CInitialize(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INITIALIZE, pParent)
{

}

CInitialize::~CInitialize()
{
}

void CInitialize::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_INI_RETRY, m_btnIniRetry);
	DDX_Control(pDX, IDC_BTN_INI_CANCEL, m_btnIniCancel);
}


BEGIN_MESSAGE_MAP(CInitialize, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_INI_RETRY, &CInitialize::OnBnClickedBtnIniRetry)
	ON_BN_CLICKED(IDC_BTN_INI_CANCEL, &CInitialize::OnBnClickedBtnIniCancel)
END_MESSAGE_MAP()


// CInitialize 메시지 처리기


BOOL CInitialize::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();
	Lf_InitDlgDesign();

	SetTimer(1, 200, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CInitialize::OnDestroy()
{
	CDialogEx::OnDestroy();

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


BOOL CInitialize::PreTranslateMessage(MSG* pMsg)
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

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CInitialize::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

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
		if (pWnd->GetDlgCtrlID() == IDC_STT_INI_TITLE)
		{
			pDC->SetBkColor(COLOR_DEEP_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_DEEP_BLUE];
		}

		if ((pWnd->GetDlgCtrlID() == IDC_STT_INI_FILE_TITLE)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_INI_CONN_TITLE)
			)
		{
			pDC->SetBkColor(COLOR_BLACK);
			pDC->SetTextColor(COLOR_YELLOW);
			return m_Brush[COLOR_IDX_BLACK];
		}

		if (pWnd->GetDlgCtrlID() == IDC_STT_INI_FILE_SYSTEM)
		{
			if (nSysInitResult[INIT_SYSTEM] == INIT_NG)
			{
				pDC->SetBkColor(COLOR_RED128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED128];
			}
			else if (nSysInitResult[INIT_SYSTEM] == INIT_OK)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_GRAY159);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY159];
			}
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_INI_FILE_MODEL)
		{
			if (nSysInitResult[INIT_MODEL] == INIT_NG)
			{
				pDC->SetBkColor(COLOR_RED128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED128];
			}
			else if (nSysInitResult[INIT_MODEL] == INIT_OK)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_GRAY159);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY159];
			}
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_INI_FILE_PATTERN)
		{
			if (nSysInitResult[INIT_PATTERN] == INIT_NG)
			{
				pDC->SetBkColor(COLOR_RED128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED128];
			}
			else if (nSysInitResult[INIT_PATTERN] == INIT_OK)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_GRAY159);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY159];
			}
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_INI_CONN_PG1)
		{
			if (nSysInitResult[INIT_PG1] == INIT_NG)
			{
				pDC->SetBkColor(COLOR_RED128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED128];
			}
			else if (nSysInitResult[INIT_PG1] == INIT_OK)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_GRAY159);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY159];
			}
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_INI_CONN_PG2)
		{
			if (nSysInitResult[INIT_PG2] == INIT_NG)
			{
				pDC->SetBkColor(COLOR_RED128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED128];
			}
			else if (nSysInitResult[INIT_PG2] == INIT_OK)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_GRAY159);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY159];
			}
		}


		break;
	}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CInitialize::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}


void CInitialize::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1)
	{
		KillTimer(1);

		Lf_initFileSystem();
		delayMs(10);

		Lf_initFileModel();
		delayMs(10);

		Lf_initFilePattern();
		delayMs(10);

		Lf_initConnPG();
		delayMs(10);

		Lf_initConnQspi();
		delayMs(10);

		Lf_initConnDIO();
		delayMs(10);

		Lf_initConnMelsec();
		delayMs(10);

		//////////////////////////////////////////////////////////////////
		// Initial NG 항목이 있으면 자동으로 창히지 않도록 한다.
		for (int i = 0; i < INIT_MAX; i++)
		{
			if (nSysInitResult[i] == INIT_NG)
				return;
		}
		CDialog::OnOK();
		//////////////////////////////////////////////////////////////////
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CInitialize::OnBnClickedBtnIniRetry()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	memset(nSysInitResult, INIT_NONE, sizeof(nSysInitResult));
	Invalidate(FALSE);

	SetTimer(1, 200, NULL);
}


void CInitialize::OnBnClickedBtnIniCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CInitialize::Lf_InitLocalValue()
{
	memset(nSysInitResult, INIT_NONE, sizeof(nSysInitResult));
}

void CInitialize::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(32, 13, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_INI_TITLE)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(23, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_INI_FILE_TITLE)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_STT_INI_CONN_TITLE)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_BTN_INI_RETRY)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_BTN_INI_CANCEL)->SetFont(&m_Font[2]);

	m_Font[3].CreateFont(21, 9, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_INI_FILE_SYSTEM)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_STT_INI_FILE_MODEL)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_STT_INI_FILE_PATTERN)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_STT_INI_CONN_PG1)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_STT_INI_CONN_PG2)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_STT_INI_CONN_QSPI)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_STT_INI_CONN_DIO)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_STT_INI_CONN_MELSEC)->SetFont(&m_Font[2]);

	m_Font[4].CreateFont(17, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[5].CreateFont(16, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

}

void CInitialize::Lf_InitColorBrush()
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

void CInitialize::Lf_InitDlgDesign()
{
	// Button ICON
	m_btnIniRetry.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
	m_btnIniCancel.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DISABLE));
}

void CInitialize::Lf_initFileSystem()
{
	if(m_pApp->Gf_LoadSystemData() == TRUE)
		nSysInitResult[INIT_SYSTEM] = INIT_OK;
	else
		nSysInitResult[INIT_SYSTEM] = INIT_NG;

	GetDlgItem(IDC_STT_INI_FILE_SYSTEM)->Invalidate(FALSE);
}

void CInitialize::Lf_initFileModel()
{
	if(m_pApp->Gf_LoadModelFile()==TRUE)
		nSysInitResult[INIT_MODEL] = INIT_OK;
	else
		nSysInitResult[INIT_MODEL] = INIT_NG;

	GetDlgItem(IDC_STT_INI_FILE_MODEL)->Invalidate(FALSE);
}

void CInitialize::Lf_initFilePattern()
{

	nSysInitResult[INIT_PATTERN] = INIT_OK;
	GetDlgItem(IDC_STT_INI_FILE_PATTERN)->Invalidate(FALSE);
}

void CInitialize::Lf_initConnPG()
{
	CString strmsg, ip;
	///////////////////////////////////////////////////////////////////////////////////
	// CH1
	m_pApp->m_pSocketTCPMain->tcp_Main_DisConnection(CH1);
	delayMs(1000);
	ip.Format(TCP_MAIN_1_BOARD_IP);
	strmsg.Format(_T("IP:%s Port:%d"), ip, TCP_MAIN_PORT);
	if (m_pApp->m_pSocketTCPMain->tcp_Main_Connection(ip, TCP_MAIN_PORT, CH1) == TRUE)
	{
		nSysInitResult[INIT_PG1] = INIT_OK;
		m_pApp->m_bPgConnectStatus[CH1] = TRUE;
	}
	else
	{
		nSysInitResult[INIT_PG1] = INIT_NG;
		m_pApp->m_bPgConnectStatus[CH1] = FALSE;
		//return FALSE;
	}
	GetDlgItem(IDC_STT_INI_CONN_PG1)->Invalidate(FALSE);

	///////////////////////////////////////////////////////////////////////////////////
	// CH2
	m_pApp->m_pSocketTCPMain->tcp_Main_DisConnection(CH2);
	delayMs(1000);
	ip.Format(TCP_MAIN_2_BOARD_IP);
	strmsg.Format(_T("IP:%s Port:%d"), ip, TCP_MAIN_PORT);
	if (m_pApp->m_pSocketTCPMain->tcp_Main_Connection(ip, TCP_MAIN_PORT, CH2) == TRUE)
	{
		nSysInitResult[INIT_PG2] = INIT_OK;
		m_pApp->m_bPgConnectStatus[CH2] = TRUE;
	}
	else
	{
		nSysInitResult[INIT_PG2] = INIT_NG;
		m_pApp->m_bPgConnectStatus[CH2] = FALSE;
		//return FALSE;
	}
	GetDlgItem(IDC_STT_INI_CONN_PG2)->Invalidate(FALSE);
}

void CInitialize::Lf_initConnQspi()
{

	nSysInitResult[INIT_QSPI] = INIT_OK;
}


void CInitialize::Lf_initConnDIO()
{

	nSysInitResult[INIT_DIO] = INIT_OK;
}


void CInitialize::Lf_initConnMelsec()
{

	nSysInitResult[INIT_MELSEC] = INIT_OK;
}
