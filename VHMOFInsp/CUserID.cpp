// CUserID.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CUserID.h"
#include "afxdialogex.h"


// CUserID 대화 상자

IMPLEMENT_DYNAMIC(CUserID, CDialog)

CUserID::CUserID(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_USERID, pParent)
{

}

CUserID::~CUserID()
{
}

void CUserID::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_UI_IMAGE, m_picUserImage);
	DDX_Control(pDX, IDC_STT_USER_ID_TITLE, m_sttUserIDTitle);
	DDX_Control(pDX, IDC_STT_UI_USER_ID_TIT, m_sttUserIDInput);
	DDX_Control(pDX, IDC_BTN_UI_CANCEL, m_btnUserCancel);
	DDX_Control(pDX, IDC_BTN_UI_CONFIRM, m_btnUserConfirm);
}


BEGIN_MESSAGE_MAP(CUserID, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_UI_CONFIRM, &CUserID::OnBnClickedBtnUiConfirm)
	ON_BN_CLICKED(IDC_BTN_UI_CANCEL, &CUserID::OnBnClickedBtnUiCancel)
END_MESSAGE_MAP()


// CUserID 메시지 처리기


BOOL CUserID::OnInitDialog()
{
	CDialog::OnInitDialog();
	lpInspWorkInfo	= m_pApp->GetInspWorkInfo();
	lpSystemInfo	= m_pApp->GetSystemInfo();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pApp->Gf_writeMLog(_T("<USER> 'USER ID' Dialog Open."));

	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();
	Lf_InitDlgDesign();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CUserID::OnDestroy()
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


BOOL CUserID::PreTranslateMessage(MSG* pMsg)
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
			case VK_ESCAPE:
			{
				return 1;
			}
			case VK_RETURN:
			{
				if (Lf_loginProcess() == FALSE)
				{
					GetDlgItem(IDC_EDT_UI_USER_ID)->EnableWindow(TRUE);
					GetDlgItem(IDC_BTN_UI_CONFIRM)->EnableWindow(TRUE);
					GetDlgItem(IDC_BTN_UI_CANCEL)->EnableWindow(TRUE);
				}
				return 1;
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


HBRUSH CUserID::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
			break;
		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CUserID::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.

	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, COLOR_WHITE);
}


void CUserID::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnTimer(nIDEvent);
}

void CUserID::OnBnClickedBtnUiConfirm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (Lf_loginProcess() == FALSE)
	{
		GetDlgItem(IDC_EDT_UI_USER_ID)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_UI_CONFIRM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_UI_CANCEL)->EnableWindow(TRUE);
	}
}


void CUserID::OnBnClickedBtnUiCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnCancel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CUserID::Lf_InitLocalValue()
{
	CString sdata;
	Read_SysIniFile(_T("SYSTEM"), _T("LOGIN_USERID"), &sdata);

	GetDlgItem(IDC_EDT_UI_USER_ID)->SetWindowText(sdata);
}

void CUserID::Lf_InitFontset()
{
	m_Font[0].CreateFont(80, 32, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(48, 20, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_EDT_UI_USER_ID)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(34, 14, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_BTN_UI_CONFIRM)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_BTN_UI_CANCEL)->SetFont(&m_Font[2]);

	m_Font[3].CreateFont(24, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[4].CreateFont(19, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
}

void CUserID::Lf_InitColorBrush()
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
}

void CUserID::Lf_InitDlgDesign()
{
	// Image Load
	CBitmap m_Bit;
	m_Bit.LoadBitmap(IDB_BITMAP_USERID);
	m_picUserImage.SetBitmap(m_Bit);
	m_Bit.Detach();

	// Gradation Static
	m_pApp->Gf_setGradientStatic(&m_sttUserIDTitle, COLOR_DEEP_BLUE, COLOR_DEEP_BLUE, COLOR_WHITE, &m_Font[1], FALSE);
	m_pApp->Gf_setGradientStatic(&m_sttUserIDInput, RGB(0,192,0), RGB(0,128,0), COLOR_WHITE, &m_Font[1], FALSE);

	// Button ICON
	m_btnUserConfirm.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
	m_btnUserCancel.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DISABLE));
}

BOOL CUserID::Lf_loginProcess()
{
	CString strUserid, szpassword;

	GetDlgItem(IDC_EDT_UI_USER_ID)->GetWindowText(strUserid);

	// Button을 비활성화 시킨다.
	GetDlgItem(IDC_EDT_UI_USER_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_UI_CONFIRM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_UI_CANCEL)->EnableWindow(FALSE);

	wchar_To_char(strUserid.GetBuffer(0), lpInspWorkInfo->smf_OperatorID);
	if ((!strUserid.Compare(_T("GIENG"))) || (!strUserid.Compare(_T("gieng"))))
	{
		m_pApp->m_sLoginUserID = _T("Administrator");
		m_pApp->m_sLoginUserName = _T("");
		m_pApp->m_bUserIdGieng = TRUE;
		m_pApp->m_bUserIdPM = FALSE;
		m_pApp->Gf_writeMLog(_T("<USER> UserID : Administrator"));
	}
	// 20150112 라인 작업자 요청에 의해 삭제 CNZ
	else if ((!strUserid.Compare(_T("PM"))) || (!strUserid.Compare(_T("pm"))))
	{
		m_pApp->m_sLoginUserID = strUserid;
		m_pApp->m_sLoginUserName = _T("");
		m_pApp->m_bUserIdGieng = FALSE;
		m_pApp->m_bUserIdPM = TRUE;
	}
	else
	{
		//MES Connect
		if (m_pApp->m_bIsGmesConnect == FALSE) {

			if (m_pApp->Gf_gmesConnect(SERVER_MES) == FALSE)
			{
				m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("MES CONNECTION FAIL"), ERROR_CODE_29);

				CString sLog;
				sLog.Format(_T("[GMES] Connection Fail"));
				m_pApp->Gf_writeMLog(sLog);

				return FALSE;
			}
		}
		//EAS Connect
		if (lpSystemInfo->m_nEasUse == TRUE)
		{
			if (m_pApp->m_bIsEasConnect == FALSE)
			{
				if (m_pApp->Gf_gmesConnect(SERVER_EAS) == FALSE)
				{
					m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("EAS CONNECTION FAIL"), ERROR_CODE_30);

					CString sLog;
					sLog.Format(_T("[EAS] Connection Fail"));
					m_pApp->Gf_writeMLog(sLog);

					return FALSE;
				}
			}
		}

		if (strUserid.GetLength() > 4)	// 2009-04-13 PDH. USE_GMES
		{
			m_pApp->m_bUserIdGieng = FALSE;
			m_pApp->m_bUserIdPM = FALSE;

			{
				if (m_pApp->m_bIsSendEAYT == FALSE)
				{
					if (m_pApp->Gf_gmesSendHost(HOST_EAYT) == FALSE)
					{
						return FALSE;
					}
					m_pApp->m_bIsSendEAYT = TRUE;
				}

				m_pApp->m_pCimNet->SetUserId(strUserid);
				if (m_pApp->Gf_gmesSendHost(HOST_UCHK) == FALSE)
				{
					return FALSE;
				}

				if (m_pApp->Gf_gmesSendHost(HOST_EDTI) == FALSE)
				{
					return FALSE;
				}

				CString sLog;
				sLog.Format(_T("<PGM> User ID : %s"), strUserid);
				m_pApp->Gf_writeMLog(sLog);
				CDialog::OnOK();
			}
		}
		else
		{
			m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("USER ID WRONG"), ERROR_CODE_19);
		}
	}

	Write_SysIniFile(_T("SYSTEM"), _T("LOGIN_USERID"), strUserid);

	CDialog::OnOK();
	AfxGetApp()->GetMainWnd()->SendMessage(WM_UPDATE_SYSTEM_INFO, NULL, NULL);

	return TRUE;
}


