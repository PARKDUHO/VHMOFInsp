// CTestReady.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CTestReady.h"
#include "afxdialogex.h"
#include "CTestPattern.h"


// CTestReady 대화 상자

IMPLEMENT_DYNAMIC(CTestReady, CDialogEx)

CTestReady::CTestReady(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_READY, pParent)
{

}

CTestReady::~CTestReady()
{
}

void CTestReady::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_TR_TEST_START, m_btnTrTestStart);
}


BEGIN_MESSAGE_MAP(CTestReady, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_STT_TR_QTY_RESET, &CTestReady::OnStnClickedSttTrQtyReset)
	ON_BN_CLICKED(IDC_BTN_TR_TEST_START, &CTestReady::OnBnClickedBtnTrTestStart)
END_MESSAGE_MAP()


// CTestReady 메시지 처리기


BOOL CTestReady::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	lpInspWorkInfo = m_pApp->GetInspWorkInfo();
	lpSystemInfo = m_pApp->GetSystemInfo();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pApp->Gf_writeMLog(_T("<TEST> 'TEST READY' Dialog Open."));

	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();
	Lf_InitDlgDesign();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTestReady::OnDestroy()
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


BOOL CTestReady::PreTranslateMessage(MSG* pMsg)
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
			case VK_RETURN:
			{
				return 1;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CTestReady::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
			if (pWnd->GetDlgCtrlID() == IDC_STT_TR_TITLE)
			{
				pDC->SetBkColor(COLOR_DEEP_BLUE);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_DEEP_BLUE];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_TR_PID_TITLE
				|| pWnd->GetDlgCtrlID() == IDC_STT_TR_QTY_TOTAL_TITLE
				|| pWnd->GetDlgCtrlID() == IDC_STT_TR_QTY_OK_TITLE
				|| pWnd->GetDlgCtrlID() == IDC_STT_TR_QTY_NG_TITLE
				)
			{
				pDC->SetBkColor(COLOR_LIGHT_YELLOW);
				pDC->SetTextColor(COLOR_BLACK);
				return m_Brush[COLOR_IDX_LIGHT_YELLOW];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_TR_PID_VALUE)
			{
				pDC->SetBkColor(COLOR_WHITE);
				pDC->SetTextColor(COLOR_BLACK);
				return m_Brush[COLOR_IDX_WHITE];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_TR_QTY_RESET)
			{
				pDC->SetBkColor(COLOR_ORANGE);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_ORANGE];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_TR_QTY_TOTAL_VALUE)
			{
				pDC->SetBkColor(COLOR_BLACK);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_BLACK];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_TR_QTY_OK_VALUE)
			{
				pDC->SetBkColor(COLOR_BLACK);
				pDC->SetTextColor(COLOR_GREEN);
				return m_Brush[COLOR_IDX_BLACK];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_TR_QTY_NG_VALUE)
			{
				pDC->SetBkColor(COLOR_BLACK);
				pDC->SetTextColor(COLOR_RED);
				return m_Brush[COLOR_IDX_BLACK];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_TR_STATUS_MSG)
			{
				pDC->SetBkColor(COLOR_BLACK);
				pDC->SetTextColor(COLOR_CYAN);
				return m_Brush[COLOR_IDX_BLACK];
			}

			break;
		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CTestReady::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = 90;
	dc.FillSolidRect(rect, COLOR_DEEP_BLUE);

//	GetClientRect(&rect);
//	rect.top = 91;
//	dc.FillSolidRect(rect, COLOR_BLUE);

	GetClientRect(&rect);
	rect.top = 92;
	dc.FillSolidRect(rect, COLOR_GRAY64);
}


void CTestReady::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}

void CTestReady::OnStnClickedSttTrQtyReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTestReady::OnBnClickedBtnTrTestStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_FinalTestStart();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTestReady::Lf_InitLocalValue()
{
	ZeroMemory(lpInspWorkInfo, sizeof(LPINSPWORKINFO));
}

void CTestReady::Lf_InitFontset()
{
	m_Font[0].CreateFont(80, 32, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(48, 20, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_TR_TITLE)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(34, 14, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_BTN_TR_TEST_START)->SetFont(&m_Font[2]);

	m_Font[3].CreateFont(30, 12, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_TR_QTY_TOTAL_VALUE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_TR_QTY_OK_VALUE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_TR_QTY_NG_VALUE)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(24, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_TR_PID_TITLE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_TR_PID_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_TR_QTY_RESET)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_TR_QTY_TOTAL_TITLE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_TR_QTY_OK_TITLE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_TR_QTY_NG_TITLE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_TR_STATUS_MSG)->SetFont(&m_Font[4]);

	m_Font[5].CreateFont(16, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
}

void CTestReady::Lf_InitColorBrush()
{
	// 각 Control의 COLOR 설정을 위한 Brush를 Setting 한다.
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush(COLOR_WHITE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_GREEN].CreateSolidBrush(COLOR_GREEN);
	m_Brush[COLOR_IDX_BLUE].CreateSolidBrush(COLOR_BLUE);
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_Brush[COLOR_IDX_JADEGREEN].CreateSolidBrush(COLOR_JADEGREEN);
	m_Brush[COLOR_IDX_LIGHT_RED].CreateSolidBrush(COLOR_LIGHT_RED);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush(COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_LIGHT_BLUE].CreateSolidBrush(COLOR_LIGHT_BLUE);
	m_Brush[COLOR_IDX_LIGHT_ORANGE].CreateSolidBrush(COLOR_LIGHT_ORANGE);
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
	m_Brush[COLOR_IDX_DARK_RED].CreateSolidBrush(COLOR_DARK_RED);
	m_Brush[COLOR_IDX_DARK_ORANGE].CreateSolidBrush(COLOR_DARK_ORANGE);
	m_Brush[COLOR_IDX_GRAY224].CreateSolidBrush(COLOR_GRAY224);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
}

void CTestReady::Lf_InitDlgDesign()
{
// 	// Gradation Static
// 	m_pApp->Gf_setGradientStatic(&m_sttUserIDTitle, COLOR_DEEP_BLUE, COLOR_DEEP_BLUE, COLOR_WHITE, &mFontH1[1], FALSE);
// 	m_pApp->Gf_setGradientStatic(&m_sttUserIDInput, RGB(0, 192, 0), RGB(0, 128, 0), COLOR_WHITE, &mFontH1[1], FALSE);
// 
// 	// Button ICON
 	m_btnTrTestStart.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
// 	m_btnUserCancel.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DISABLE));
}

BOOL CTestReady::Lf_FinalTestStart()
{
	int ch = CH2;

	if ((m_pApp->m_bUserIdPM == TRUE) || (m_pApp->m_bUserIdGieng == TRUE))
	{
		m_pApp->Gf_ShowMessageBox(MSG_WARNING, _T("PM MODE"), ERROR_CODE_0);
	}

	if (Lf_getControlBdReady(ch) == FALSE)
	{
		return FALSE;
	}

	if (Lf_getFirmwareVersion(ch) == FALSE)
	{
		return FALSE;
	}

	CTestPattern pattern_dlg;
	pattern_dlg.m_nTargetCh = ch;
	if (pattern_dlg.DoModal() == IDOK)
	{

	}


	return TRUE;
}

BOOL CTestReady::Lf_getControlBdReady(int ch)
{
	int nCnt = 0;

	m_pApp->Gf_writeMLog(_T("<PG> CTRL B/D Ready Check START"));
	GetDlgItem(IDC_STT_TR_STATUS_MSG)->SetWindowText(_T("CTRL B/D Ready Check"));

	if (DEBUG_TCP_RECEIVE_OK)
		return TRUE;

	while (lpInspWorkInfo->m_bAreYouReady == FALSE)
	{
		if (m_pApp->commApi->main_getAreYouReady(ch) == TRUE)
			break;

		delayMs(20);

		if (nCnt > 3)
		{
			GetDlgItem(IDC_STT_TR_STATUS_MSG)->SetWindowText(_T("No Response PG!"));

			m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("Communication Error"), ERROR_CODE_18);
			return FALSE;

		}
		nCnt++;
	}
	m_pApp->Gf_writeMLog(_T("<PG> CTRL B/D Ready Check OK."));

	return TRUE;
}

BOOL CTestReady::Lf_getFirmwareVersion(int ch)
{
	if (m_pApp->commApi->main_getCtrlFWVersion(ch) == FALSE)
	{
		return FALSE;
	}

	AfxGetApp()->GetMainWnd()->SendMessage(WM_UPDATE_SYSTEM_INFO, NULL, NULL);

	return TRUE;
}

