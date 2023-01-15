// CPanelID.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CPanelID.h"
#include "afxdialogex.h"


// CPanelID 대화 상자

IMPLEMENT_DYNAMIC(CPanelID, CDialog)

CPanelID::CPanelID(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PANELID, pParent)
{

}

CPanelID::~CPanelID()
{
}

void CPanelID::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_PID_CONFIRM, m_btnPidConfirm);
	DDX_Control(pDX, IDC_BTN_PID_CANCEL, m_btnPidCancel);
}


BEGIN_MESSAGE_MAP(CPanelID, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PID_CONFIRM, &CPanelID::OnBnClickedBtnPidConfirm)
	ON_BN_CLICKED(IDC_BTN_PID_CANCEL, &CPanelID::OnBnClickedBtnPidCancel)
END_MESSAGE_MAP()


// CPanelID 메시지 처리기


BOOL CPanelID::OnInitDialog()
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


void CPanelID::OnDestroy()
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


BOOL CPanelID::PreTranslateMessage(MSG* pMsg)
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
			case VK_RETURN:
			{
				Lf_confirmPanelID();
				return 1;
			}
			case VK_SPACE:		return 1;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


HBRUSH CPanelID::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		case CTLCOLOR_STATIC:		// Static, CheckBox control
			if (pWnd->GetDlgCtrlID() == IDC_STT_PID_TITLE)
			{
				pDC->SetBkColor(COLOR_DEEP_BLUE);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_DEEP_BLUE];
			}
			break;
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CPanelID::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}


void CPanelID::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnTimer(nIDEvent);
}


void CPanelID::OnBnClickedBtnPidConfirm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_confirmPanelID();
}


void CPanelID::OnBnClickedBtnPidCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnCancel();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CPanelID::Lf_InitLocalValue()
{

}

void CPanelID::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(52, 23, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_PID_TITLE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_EDT_PID_INPUT)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(36, 16, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[3].CreateFont(23, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_BTN_PID_CONFIRM)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_BTN_PID_CANCEL)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(18, 7, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[5].CreateFont(16, 6, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

}

void CPanelID::Lf_InitColorBrush()
{
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_RED128].CreateSolidBrush(COLOR_RED128);
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_Brush[COLOR_IDX_GRAY240].CreateSolidBrush(COLOR_GRAY240);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
	m_Brush[COLOR_IDX_GRAY128].CreateSolidBrush(COLOR_GRAY128);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush(COLOR_GRAY64);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
	m_Brush[COLOR_IDX_DARK_ORANGE].CreateSolidBrush(COLOR_DARK_ORANGE);
}


void CPanelID::Lf_InitDlgDesign()
{
	// Button ICON
	m_btnPidConfirm.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
	m_btnPidCancel.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DISABLE));
}


void CPanelID::Lf_confirmPanelID()
{
	BOOL isDataOK = TRUE;
	char cbuff[128] = { 0, };
	int i = 0, len = 0;

	GetDlgItem(IDC_EDT_PID_INPUT)->GetWindowText(strInputPID);
	if (((strInputPID.GetLength() < 7) || (strInputPID.GetLength() > 20)) && (strInputPID != _T("ESC")))
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("WRONG PANEL ID"), ERROR_CODE_54);
		GetDlgItem(IDC_EDT_PID_INPUT)->SetWindowText(_T(""));
		return;
	}
	strInputPID.Replace(_T("\r"), _T(""));
	strInputPID.Replace(_T("\n"), _T(""));

	CString sLog;
	sLog.Format(_T("<PID INPUT> %s"), strInputPID);
	m_pApp->Gf_writeMLog(sLog);
	wchar_To_char(strInputPID.GetBuffer(0), cbuff);
	len = (int)strlen(cbuff);
	for (i = 0; i < len; i++)
	{
		if ((('0' <= cbuff[i]) && (cbuff[i] <= '9'))
			|| (('a' <= cbuff[i]) && (cbuff[i] <= 'z'))
			|| (('A' <= cbuff[i]) && (cbuff[i] <= 'Z')))
		{
		}
		else
		{
			isDataOK = FALSE;
			break;
		}
	}

	if (isDataOK == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("WRONG PANEL ID"), ERROR_CODE_55);
		GetDlgItem(IDC_EDT_PID_INPUT)->SetWindowText(_T(""));
		return;
	}

	CDialog::OnOK();
}


