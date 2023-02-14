// CSafetyLock.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CSafetyLock.h"
#include "CSensorView.h"
#include "afxdialogex.h"


// CSafetyLock 대화 상자

IMPLEMENT_DYNAMIC(CSafetyLock, CDialog)

CSafetyLock::CSafetyLock(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SAFETY_LOCK, pParent)
{

}

CSafetyLock::~CSafetyLock()
{
}

void CSafetyLock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_SL_OK, m_btnSlConfirm);
	DDX_Control(pDX, IDC_STT_SL_ALARM_LIST, m_lstSlAlarmList);
	DDX_Control(pDX, IDC_BTN_SL_SENSOR_VIEW, m_btnSlSensorView);
}


BEGIN_MESSAGE_MAP(CSafetyLock, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_SL_OK, &CSafetyLock::OnBnClickedBtnSlOk)
	ON_BN_CLICKED(IDC_BTN_SL_SENSOR_VIEW, &CSafetyLock::OnBnClickedBtnSlSensorView)
END_MESSAGE_MAP()


// CSafetyLock 메시지 처리기


BOOL CSafetyLock::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pApp->m_bSafetyDlgOpen = TRUE;

	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();
	Lf_InitDlgDesign();

	Lf_openDlgSensorView();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSafetyLock::OnDestroy()
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

	m_pApp->m_bSafetyDlgOpen = FALSE;
}


BOOL CSafetyLock::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_F4)
	{
		if (::GetKeyState(VK_MENU) < 0)	return TRUE;
	}

	// 일반 Key 동작에 대한 Event
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
			case VK_ESCAPE:		return 1;
			case VK_RETURN:
			{
				Lf_confirmPassword();
				return 1;
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


HBRUSH CSafetyLock::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
			if (pWnd->GetDlgCtrlID() == IDC_STT_SL_ALARM_LIST)
			{
				pDC->SetBkColor(COLOR_WHITE);
				pDC->SetTextColor(COLOR_RED);
				return m_Brush[COLOR_IDX_WHITE];
			}
			break;
		case CTLCOLOR_SCROLLBAR:
			break;
		case CTLCOLOR_BTN:
			break;
		case CTLCOLOR_STATIC:		// Static, CheckBox control
			if (pWnd->GetDlgCtrlID() == IDC_STT_SL_TOP)
			{
				pDC->SetBkColor(COLOR_RED);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SL_FIRST)
			{
				pDC->SetBkColor(COLOR_WHITE);
				pDC->SetTextColor(COLOR_RED);
				return m_Brush[COLOR_IDX_WHITE];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SL_SECOND)
			{
				pDC->SetBkColor(COLOR_WHITE);
				pDC->SetTextColor(COLOR_DARK_BLUE);
				return m_Brush[COLOR_IDX_WHITE];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SL_PHONE)
			{
				pDC->SetBkColor(COLOR_WHITE);
				pDC->SetTextColor(COLOR_BLACK);
				return m_Brush[COLOR_IDX_WHITE];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SL_NAME)
			{
				pDC->SetBkColor(COLOR_WHITE);
				pDC->SetTextColor(COLOR_BLACK);
				return m_Brush[COLOR_IDX_WHITE];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SL_BOTTOM1)
			{
				pDC->SetBkColor(COLOR_DARK_BLUE);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_DARK_BLUE];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SL_BOTTOM2)
			{
				pDC->SetBkColor(COLOR_GRAY64);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY64];
			}
			break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CSafetyLock::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;

	GetClientRect(&rect);
	rect.top = (int)(rect.Height() * 0.6);
	dc.FillSolidRect(rect, COLOR_BLUE);
}


void CSafetyLock::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnTimer(nIDEvent);
}


void CSafetyLock::OnBnClickedBtnSlOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_confirmPassword();
}

void CSafetyLock::OnBnClickedBtnSlSensorView()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_openDlgSensorView();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CSafetyLock::Lf_InitLocalValue()
{
}

void CSafetyLock::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(120, 50, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_SL_TOP)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(50, 20, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_SL_BOTTOM1)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_STT_SL_FIRST)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_STT_SL_SECOND)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_STT_SL_PHONE)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_STT_SL_NAME)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_EDT_SL_PASSWORD)->SetFont(&m_Font[2]);

	m_Font[3].CreateFont(34, 15, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_SL_ALARM_LIST)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(30, 12, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_BTN_SL_OK)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_BTN_SL_SENSOR_VIEW)->SetFont(&m_Font[4]);

	m_Font[5].CreateFont(16, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
}

void CSafetyLock::Lf_InitColorBrush()
{
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush(COLOR_WHITE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_RED128].CreateSolidBrush(COLOR_RED128);
	m_Brush[COLOR_IDX_GREEN].CreateSolidBrush(COLOR_GREEN);
	m_Brush[COLOR_IDX_GREEN128].CreateSolidBrush(COLOR_GREEN128);
	m_Brush[COLOR_IDX_BLUE].CreateSolidBrush(COLOR_BLUE);
	m_Brush[COLOR_IDX_BLUE128].CreateSolidBrush(COLOR_BLUE128);
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_Brush[COLOR_IDX_GRAY240].CreateSolidBrush(COLOR_GRAY240);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
	m_Brush[COLOR_IDX_GRAY128].CreateSolidBrush(COLOR_GRAY128);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush(COLOR_GRAY64);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
	m_Brush[COLOR_IDX_DARK_BLUE].CreateSolidBrush(COLOR_DARK_BLUE);
	m_Brush[COLOR_IDX_DARK_ORANGE].CreateSolidBrush(COLOR_DARK_ORANGE);
}


void CSafetyLock::Lf_InitDlgDesign()
{
	int DialogWidth = GetSystemMetrics(SM_CXSCREEN);
	int DialogHeight = GetSystemMetrics(SM_CYSCREEN);

	CWnd* dlgItem = GetDlgItem(IDC_STT_SL_TOP);
	dlgItem->SetWindowPos(0, 0, 0, DialogWidth, (int)(DialogHeight * 0.20), SWP_NOREDRAW);

	dlgItem = GetDlgItem(IDC_EDT_SL_PASSWORD);
	dlgItem->SetWindowPos(0, (int)(DialogWidth / 2 - 210), (int)(DialogHeight * 0.90), 200, 60, SWP_NOREDRAW);
	dlgItem = GetDlgItem(IDC_BTN_SL_OK);
	dlgItem->SetWindowPos(0, (int)(DialogWidth / 2 + 10), (int)(DialogHeight * 0.90), 200, 60, SWP_NOREDRAW);
	dlgItem = GetDlgItem(IDC_BTN_SL_SENSOR_VIEW);
	dlgItem->SetWindowPos(0, (int)(DialogWidth - 210), (int)(DialogHeight * 0.90), 210, 60, SWP_NOREDRAW);

	dlgItem = GetDlgItem(IDC_STT_SL_FIRST);
	dlgItem->SetWindowPos(0, 0, (int)(DialogHeight * 0.20), DialogWidth, (int)(DialogHeight * 0.10), SWP_NOREDRAW);

	dlgItem = GetDlgItem(IDC_STT_SL_SECOND);
	dlgItem->SetWindowPos(0, 0, (int)(DialogHeight * 0.30), DialogWidth, (int)(DialogHeight * 0.20), SWP_NOREDRAW);

	dlgItem = GetDlgItem(IDC_STT_SL_PHONE);
	dlgItem->SetWindowPos(0, 0, (int)(DialogHeight * 0.50), (int)(DialogWidth / 2), (int)(DialogHeight * 0.10), SWP_NOREDRAW);

	dlgItem = GetDlgItem(IDC_STT_SL_NAME);
	dlgItem->SetWindowPos(0, (int)(DialogWidth / 2), (int)(DialogHeight * 0.50), (int)(DialogWidth / 2), (int)(DialogHeight * 0.10), SWP_NOREDRAW);

	dlgItem = GetDlgItem(IDC_STT_SL_BOTTOM1);
	dlgItem->SetWindowPos(0, 0, (int)(DialogHeight * 0.60), DialogWidth, (int)(DialogHeight * 0.25), SWP_NOREDRAW);

	dlgItem = GetDlgItem(IDC_STT_SL_ALARM_LIST);
	dlgItem->SetWindowPos(0, (int)(DialogWidth / 2 - 600), (int)(DialogHeight * 0.62), 1200, (int)(DialogHeight * 0.26), SWP_NOREDRAW);

	dlgItem = GetDlgItem(IDC_STT_SL_BOTTOM2);
	dlgItem->SetWindowPos(0, 0, (int)(DialogHeight * 0.85), DialogWidth, (int)(DialogHeight * 0.15), SWP_NOREDRAW);

	ShowWindow(SW_SHOWMAXIMIZED);

	// Button ICON
	m_btnSlConfirm.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
	m_btnSlSensorView.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
	//m_btnPwClose.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DISABLE));
}

void CSafetyLock::Lf_confirmPassword()
{
	CString password, input;

	m_pApp->m_bAdminPassword = FALSE;

	Read_SysIniFile(_T("SYSTEM"), _T("PW_SAFETY"), &password);
	password.MakeUpper();

	GetDlgItem(IDC_EDT_SL_PASSWORD)->GetWindowText(input);
	if (input == password)
	{
		CDialog::OnOK();
	}
	else if (input == _T("****"))
	{
		m_pApp->m_bAdminPassword = TRUE;
		CDialog::OnOK();
	}
	else
	{
		MessageBox(_T("Password Fail"), _T("Error"), MB_ICONERROR);
	}
}

void CSafetyLock::Lf_openDlgSensorView()
{
	CSensorView sensor_dlg;
	sensor_dlg.DoModal();
}