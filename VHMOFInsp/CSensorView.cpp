// CSensorView.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CSensorView.h"
#include "CPassword.h"
#include "afxdialogex.h"


// CSensorView 대화 상자

IMPLEMENT_DYNAMIC(CSensorView, CDialog)

CSensorView::CSensorView(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SENSOR_VIEW, pParent)
{

}

CSensorView::~CSensorView()
{
}

void CSensorView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_SV_ERROR_LIST, m_lstSvErrorList);
	DDX_Control(pDX, IDC_BTN_SV_EXIT, m_btnSvExit);
	DDX_Control(pDX, IDC_BTN_SV_RESET, m_btnSvReset);
	DDX_Control(pDX, IDC_BTN_SV_LEFT_DOOR_OPEN, m_btnSvLeftDoorOpen);
	DDX_Control(pDX, IDC_BTN_SV_RIGHT_DOOR_OPEN, m_btnSvRightDoorOpen);
}


BEGIN_MESSAGE_MAP(CSensorView, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_SV_EXIT, &CSensorView::OnBnClickedBtnSvExit)
	ON_BN_CLICKED(IDC_BTN_SV_RESET, &CSensorView::OnBnClickedBtnSvReset)
	ON_BN_CLICKED(IDC_BTN_SV_LEFT_DOOR_OPEN, &CSensorView::OnBnClickedBtnSvLeftDoorOpen)
	ON_BN_CLICKED(IDC_BTN_SV_RIGHT_DOOR_OPEN, &CSensorView::OnBnClickedBtnSvRightDoorOpen)
END_MESSAGE_MAP()


// CSensorView 메시지 처리기


BOOL CSensorView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();
	Lf_InitDlgDesign();

	Lf_updateErrorMessageList();

	SetTimer(1, 1000, NULL);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSensorView::OnDestroy()
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


BOOL CSensorView::PreTranslateMessage(MSG* pMsg)
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
			case VK_RETURN:		return 1;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


HBRUSH CSensorView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
			if (pWnd->GetDlgCtrlID() == IDC_LST_SV_ERROR_LIST)
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
			if (pWnd->GetDlgCtrlID() == IDC_STT_SV_EMO)
			{
				if (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_EMO_SWITCH)
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
				else
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SV_LIGHT_CURTAIN)
			{
				if (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_LIGHT_CURTAIN)
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
				else
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SV_LEFT_SAFETY_DOOR)
			{
				if (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_LEFT_SAFETY_DOOR)
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
				else
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SV_RIGHT_SAFETY_DOOR)
			{
				if (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_RIGHT_SAFETY_DOOR)
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
				else
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SV_FAN_IN)
			{
				if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_FAN_IN_ALARM) == 0)
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
				else
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SV_FAN_OUT)
			{
				if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_FAN_OUT_ALARM) == 0)
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
				else
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SV_TEMPATURE)
			{
				if (m_pApp->m_nDioInBit[CH1][1] & DIN_D1_TEMPATURE_HIGH_ALARM)
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
				else
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SV_MAIN_AIR)
			{
				if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_MAIN_AIR_DIGITAL_PRESSURE_GAGE) == 0)
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
				else
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SV_ION_AIR)
			{
				if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_IONIZER_AIR_DIGITAL_PRESSURE_GAGE) == 0)
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
				else
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SV_CYLINDER_AIR)
			{
				if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_CYLINDER_DIGITAL_PRESSURE_GAGE) == 0)
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
				else
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SV_JIG_AIR)
			{
				if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_JIG_DIGITAL_PRESSURE_GAGE) == 0)
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
				else
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_SV_IONIZER)
			{
				if (m_pApp->m_nDioInBit[CH1][2] & DIN_D1_IONIZER_ALARM)
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
				else
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
			}
			break;
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CSensorView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, COLOR_GRAY64);

	Lf_showSensorImage();
}


void CSensorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1)
	{
		KillTimer(1);

		if (m_bToggle == TRUE)
		{
			m_bToggle = FALSE;
			Lf_toggleSensorPosition(m_bToggle);
		}
		else
		{
			m_bToggle = TRUE;
			Lf_toggleSensorPosition(m_bToggle);
		}

		SetTimer(1, 1000, NULL);
	}

	CDialog::OnTimer(nIDEvent);
}


void CSensorView::OnBnClickedBtnSvLeftDoorOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CPassword pass_dlg;
	pass_dlg.password_mode = 2;
	if (pass_dlg.DoModal() == IDOK)
	{
		m_pApp->commApi->dio_LeftSafetyDoorOpen();
	}
}


void CSensorView::OnBnClickedBtnSvRightDoorOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CPassword pass_dlg;
	pass_dlg.password_mode = 2;
	if (pass_dlg.DoModal() == IDOK)
	{
		m_pApp->commApi->dio_RightSafetyDoorOpen();
	}
}


void CSensorView::OnBnClickedBtnSvReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_updateErrorMessageList();
}


void CSensorView::OnBnClickedBtnSvExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CSensorView::Lf_InitLocalValue()
{
	m_bToggle = TRUE;

}

void CSensorView::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(120, 50, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[2].CreateFont(50, 20, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[3].CreateFont(34, 15, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[4].CreateFont(30, 12, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_LST_SV_ERROR_LIST)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_BTN_SV_RESET)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_BTN_SV_EXIT)->SetFont(&m_Font[4]);

	m_Font[5].CreateFont(18, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_SV_EMO)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_STT_SV_LIGHT_CURTAIN)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_STT_SV_LEFT_SAFETY_DOOR)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_STT_SV_RIGHT_SAFETY_DOOR)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_STT_SV_FAN_IN)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_STT_SV_FAN_OUT)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_STT_SV_TEMPATURE)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_STT_SV_MAIN_AIR)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_STT_SV_ION_AIR)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_STT_SV_CYLINDER_AIR)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_STT_SV_JIG_AIR)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_STT_SV_IONIZER)->SetFont(&m_Font[5]);

	GetDlgItem(IDC_BTN_SV_LEFT_DOOR_OPEN)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_BTN_SV_RIGHT_DOOR_OPEN)->SetFont(&m_Font[5]);
}

void CSensorView::Lf_InitColorBrush()
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


void CSensorView::Lf_InitDlgDesign()
{
	// Button ICON
	m_btnSvLeftDoorOpen.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
	m_btnSvRightDoorOpen.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));

	m_btnSvReset.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
	m_btnSvExit.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DISABLE));
}


void CSensorView::Lf_showSensorImage()
{

	CClientDC dc(this);
	CImage m_image;
	CString sPath;

	sPath.Format(_T(".\\Image\\SensorView2.JPG"));
	if (m_image.Load(sPath) == S_OK)
	{
		m_image.Draw(dc.m_hDC, 10, 10, 1590, 820);
	}
	else
	{
		CString smsg;
		smsg.Format(_T("%s 파일을 찾을 수 없습니다."), sPath);
		AfxMessageBox(smsg);
	}
}

void CSensorView::Lf_toggleSensorPosition(BOOL bFlag)
{
	if (bFlag == TRUE)
	{
		GetDlgItem(IDC_STT_SV_EMO)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_STT_SV_LIGHT_CURTAIN)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_STT_SV_LEFT_SAFETY_DOOR)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_STT_SV_RIGHT_SAFETY_DOOR)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_STT_SV_FAN_IN)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_STT_SV_FAN_OUT)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_STT_SV_TEMPATURE)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_STT_SV_MAIN_AIR)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_STT_SV_ION_AIR)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_STT_SV_CYLINDER_AIR)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_STT_SV_JIG_AIR)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_STT_SV_IONIZER)->ShowWindow(SW_SHOWNORMAL);
	}
	else
	{
 		if (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_EMO_SWITCH)								GetDlgItem(IDC_STT_SV_EMO)->ShowWindow(SW_HIDE);
  		if (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_LIGHT_CURTAIN)								GetDlgItem(IDC_STT_SV_LIGHT_CURTAIN)->ShowWindow(SW_HIDE);
		if (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_LEFT_SAFETY_DOOR)							GetDlgItem(IDC_STT_SV_LEFT_SAFETY_DOOR)->ShowWindow(SW_HIDE);
		if (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_RIGHT_SAFETY_DOOR)							GetDlgItem(IDC_STT_SV_RIGHT_SAFETY_DOOR)->ShowWindow(SW_HIDE);
 		if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_FAN_IN_ALARM) == 0)						GetDlgItem(IDC_STT_SV_FAN_IN)->ShowWindow(SW_HIDE);
		if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_FAN_OUT_ALARM) == 0)						GetDlgItem(IDC_STT_SV_FAN_OUT)->ShowWindow(SW_HIDE);
		if (m_pApp->m_nDioInBit[CH1][1] & DIN_D1_TEMPATURE_HIGH_ALARM)						GetDlgItem(IDC_STT_SV_TEMPATURE)->ShowWindow(SW_HIDE);
		if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_MAIN_AIR_DIGITAL_PRESSURE_GAGE) == 0)		GetDlgItem(IDC_STT_SV_MAIN_AIR)->ShowWindow(SW_HIDE);
		if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_IONIZER_AIR_DIGITAL_PRESSURE_GAGE) == 0)	GetDlgItem(IDC_STT_SV_ION_AIR)->ShowWindow(SW_HIDE);
		if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_CYLINDER_DIGITAL_PRESSURE_GAGE) == 0)		GetDlgItem(IDC_STT_SV_CYLINDER_AIR)->ShowWindow(SW_HIDE);
		if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_JIG_DIGITAL_PRESSURE_GAGE) == 0)			GetDlgItem(IDC_STT_SV_JIG_AIR)->ShowWindow(SW_HIDE);
		if (m_pApp->m_nDioInBit[CH1][2] & DIN_D1_IONIZER_ALARM)								GetDlgItem(IDC_STT_SV_IONIZER)->ShowWindow(SW_HIDE);
	}

	GetDlgItem(IDC_STT_SV_EMO)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_SV_LIGHT_CURTAIN)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_SV_LEFT_SAFETY_DOOR)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_SV_RIGHT_SAFETY_DOOR)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_SV_FAN_IN)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_SV_FAN_OUT)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_SV_TEMPATURE)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_SV_MAIN_AIR)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_SV_ION_AIR)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_SV_CYLINDER_AIR)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_SV_JIG_AIR)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_SV_IONIZER)->Invalidate(FALSE);
	GetDlgItem(IDC_BTN_SV_LEFT_DOOR_OPEN)->Invalidate(FALSE);
	GetDlgItem(IDC_BTN_SV_RIGHT_DOOR_OPEN)->Invalidate(FALSE);
}

void CSensorView::Lf_updateErrorMessageList()
{
	CString strKey, strErr;

	m_lstSvErrorList.ResetContent();
	if (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_EMO_SWITCH)
	{
		strKey.Format(_T("%d"), ERROR_CODE_38);
		Read_ErrorCode(_T("EQP_ERROR"), strKey, &strErr);
		strErr.Insert(0, _T("▶"));
		m_lstSvErrorList.AddString(strErr);
	}
	if (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_LIGHT_CURTAIN)
	{
		strKey.Format(_T("%d"), ERROR_CODE_39);
		Read_ErrorCode(_T("EQP_ERROR"), strKey, &strErr);
		strErr.Insert(0, _T("▶"));
		m_lstSvErrorList.AddString(strErr);
	}
	if (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_LEFT_SAFETY_DOOR)
	{
		strKey.Format(_T("%d"), ERROR_CODE_40);
		Read_ErrorCode(_T("EQP_ERROR"), strKey, &strErr);
		strErr.Insert(0, _T("▶"));
		m_lstSvErrorList.AddString(strErr);
	}
	if (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_RIGHT_SAFETY_DOOR)
	{
		strKey.Format(_T("%d"), ERROR_CODE_41);
		Read_ErrorCode(_T("EQP_ERROR"), strKey, &strErr);
		strErr.Insert(0, _T("▶"));
		m_lstSvErrorList.AddString(strErr);
	}
	if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_FAN_IN_ALARM) == 0)
	{
		strKey.Format(_T("%d"), ERROR_CODE_42);
		Read_ErrorCode(_T("EQP_ERROR"), strKey, &strErr);
		strErr.Insert(0, _T("▶"));
		m_lstSvErrorList.AddString(strErr);
	}
	if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_FAN_OUT_ALARM) == 0)
	{
		strKey.Format(_T("%d"), ERROR_CODE_43);
		Read_ErrorCode(_T("EQP_ERROR"), strKey, &strErr);
		strErr.Insert(0, _T("▶"));
		m_lstSvErrorList.AddString(strErr);
	}
	if (m_pApp->m_nDioInBit[CH1][1] & DIN_D1_TEMPATURE_HIGH_ALARM)
	{
		strKey.Format(_T("%d"), ERROR_CODE_44);
		Read_ErrorCode(_T("EQP_ERROR"), strKey, &strErr);
		strErr.Insert(0, _T("▶"));
		m_lstSvErrorList.AddString(strErr);
	}
	if (m_pApp->m_nDioInBit[CH1][2] & DIN_D1_IONIZER_ALARM)
	{
		strKey.Format(_T("%d"), ERROR_CODE_45);
		Read_ErrorCode(_T("EQP_ERROR"), strKey, &strErr);
		strErr.Insert(0, _T("▶"));
		m_lstSvErrorList.AddString(strErr);
	}
	if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_MAIN_AIR_DIGITAL_PRESSURE_GAGE) == 0)
	{
		strKey.Format(_T("%d"), ERROR_CODE_46);
		Read_ErrorCode(_T("EQP_ERROR"), strKey, &strErr);
		strErr.Insert(0, _T("▶"));
		m_lstSvErrorList.AddString(strErr);
	}
	if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_IONIZER_AIR_DIGITAL_PRESSURE_GAGE) == 0)
	{
		strKey.Format(_T("%d"), ERROR_CODE_47);
		Read_ErrorCode(_T("EQP_ERROR"), strKey, &strErr);
		strErr.Insert(0, _T("▶"));
		m_lstSvErrorList.AddString(strErr);
	}
	if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_CYLINDER_DIGITAL_PRESSURE_GAGE) == 0)
	{
		strKey.Format(_T("%d"), ERROR_CODE_48);
		Read_ErrorCode(_T("EQP_ERROR"), strKey, &strErr);
		strErr.Insert(0, _T("▶"));
		m_lstSvErrorList.AddString(strErr);
	}
	if ((m_pApp->m_nDioInBit[CH1][1] & DIN_D1_JIG_DIGITAL_PRESSURE_GAGE) == 0)
	{
		strKey.Format(_T("%d"), ERROR_CODE_49);
		Read_ErrorCode(_T("EQP_ERROR"), strKey, &strErr);
		strErr.Insert(0, _T("▶"));
		m_lstSvErrorList.AddString(strErr);
	}
}




