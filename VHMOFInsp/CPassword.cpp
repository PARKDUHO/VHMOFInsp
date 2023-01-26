// CPassword.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CPassword.h"
#include "afxdialogex.h"


// CPassword 대화 상자

IMPLEMENT_DYNAMIC(CPassword, CDialog)

CPassword::CPassword(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PASSWORD, pParent)
{
	password_mode = 0;
}

CPassword::~CPassword()
{
}

void CPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_PW_CONFIRM, m_btnPwConfirm);
	DDX_Control(pDX, IDC_BTN_PW_CLOSE, m_btnPwClose);
	DDX_Control(pDX, IDC_PIC_PW_IMAGE, m_picPwImage);
}


BEGIN_MESSAGE_MAP(CPassword, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PW_CONFIRM, &CPassword::OnBnClickedBtnPwConfirm)
	ON_BN_CLICKED(IDC_BTN_PW_CLOSE, &CPassword::OnBnClickedBtnPwClose)
END_MESSAGE_MAP()


// CPassword 메시지 처리기


BOOL CPassword::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();
	Lf_InitDlgDesign();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CPassword::OnDestroy()
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


BOOL CPassword::PreTranslateMessage(MSG* pMsg)
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
				Lf_confirmPassword();
				return 1;
			}
			case VK_SPACE:		return 1;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


HBRUSH CPassword::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
			if (pWnd->GetDlgCtrlID() == IDC_STT_PW_TITLE)
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


void CPassword::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.

	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, COLOR_WHITE);
}


void CPassword::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnTimer(nIDEvent);
}


void CPassword::OnBnClickedBtnPwConfirm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_confirmPassword();
}


void CPassword::OnBnClickedBtnPwClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnCancel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CPassword::Lf_InitLocalValue()
{

}

void CPassword::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(52, 23, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_PW_TITLE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_EDT_PW_PASSWORD)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(36, 16, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[3].CreateFont(23, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_BTN_PW_CONFIRM)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_BTN_PW_CLOSE)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(18, 7, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[5].CreateFont(16, 6, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

}

void CPassword::Lf_InitColorBrush()
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


void CPassword::Lf_InitDlgDesign()
{
	// Image Load
	CBitmap m_Bit;
	m_Bit.LoadBitmap(IDB_BMP_PASSWORD);
	m_picPwImage.SetBitmap(m_Bit);
	m_Bit.Detach();

	// Button ICON
	m_btnPwConfirm.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
	m_btnPwClose.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DISABLE));
}


void CPassword::Lf_confirmPassword()
{
	BOOL bRet = FALSE;
	CString input_password, set_password;
	GetDlgItem(IDC_EDT_PW_PASSWORD)->GetWindowText(input_password);

	if (password_mode == 0)				// Normal
	{
		Read_SysIniFile(_T("SYSTEM"), _T("PW"), &set_password);
		set_password.MakeUpper();

		if (input_password == set_password)
		{
			bRet = TRUE;
		}
	}
	else if (password_mode == 1)		// Model Info
	{
		Read_SysIniFile(_T("SYSTEM"), _T("PW_MODEL"), &set_password);
		set_password.MakeUpper();

		if (input_password == set_password)
		{
			bRet = TRUE;
		}
	}
	else if (password_mode == 2)		// Safety Lock
	{
		Read_SysIniFile(_T("SYSTEM"), _T("PW_SAFETY"), &set_password);
		set_password.MakeUpper();

		if (input_password == set_password)
		{
			bRet = TRUE;
		}
	}

	if(bRet == TRUE)
	{
		CDialog::OnOK();
	}
	else
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("WRONG PASSWORD"), ERROR_CODE_1);

		GetDlgItem(IDC_EDT_PW_PASSWORD)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDT_PW_PASSWORD)->SetFocus();
		return;
	}

}


