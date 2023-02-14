// CIOReadyCheck.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CIOReadyCheck.h"
#include "afxdialogex.h"


// CIOReadyCheck 대화 상자

IMPLEMENT_DYNAMIC(CIOReadyCheck, CDialog)

CIOReadyCheck::CIOReadyCheck(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_IO_READY_CHECK, pParent)
{
	m_pDefaultFont = new CFont();
	m_pDefaultFont->CreateFont(17, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
}

CIOReadyCheck::~CIOReadyCheck()
{
	if (m_pDefaultFont != NULL)
	{
		delete m_pDefaultFont;
	}
}

void CIOReadyCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_IR_CLOSE, m_btnIrClose);
	DDX_Control(pDX, IDC_PIC_IR_REAR_DOOR_LEFT_CYLINDER_DOWN, m_picRearDoorLeftCylinderDown);
	DDX_Control(pDX, IDC_PIC_IR_REAR_DOOR_RIGHT_CYLINDER_DOWN, m_picRearDoorRightCylinderDown);
	DDX_Control(pDX, IDC_PIC_IR_FRONT_DOOR_LEFT_CYLINDER_DOWN, m_picFrontDoorLeftCylinderDown);
	DDX_Control(pDX, IDC_PIC_IR_FRONT_DOOR_RIGHT_CYLINDER_DOWN, m_picFrontDoorRightCylinderDown);
	DDX_Control(pDX, IDC_PIC_IR_FRONT_DOOR_HOLDING_CYLINDER_BACK, m_picFrontDoorHoldingCylinderBack);
	DDX_Control(pDX, IDC_PIC_IR_ROBOT_IN_SENSOR1, m_picRobotInSensor1);
	DDX_Control(pDX, IDC_PIC_IR_ROBOT_IN_SENSOR2, m_picRobotInSensor2);
	DDX_Control(pDX, IDC_PIC_IR_JIG_DOWN_SENSOR1, m_picJigDownSensor1);
	DDX_Control(pDX, IDC_PIC_IR_JIG_DOWN_SENSOR2, m_picJigDownSensor2);
	DDX_Control(pDX, IDC_PIC_IR_JIG_DOWN_SENSOR3, m_picJigDownSensor3);
	DDX_Control(pDX, IDC_PIC_IR_JIG_HOME_SENSOR, m_picJigHomeSensor);
	DDX_Control(pDX, IDC_PIC_IR_JIG_DOOR_CLOSE, m_picJigDoorClose);
	DDX_Control(pDX, IDC_PIC_IR_JIG_TRAY_IN_CH1, m_picJigTrayInCh1);
	DDX_Control(pDX, IDC_PIC_IR_JIG_TRAY_IN_CH2, m_picJigTrayInCh2);
	DDX_Control(pDX, IDC_PIC_IR_CH1_CLAMP1_UNLOCK, m_picCh1Clamp1Unlock);
	DDX_Control(pDX, IDC_PIC_IR_CH1_CLAMP2_UNLOCK, m_picCh1Clamp2Unlock);
	DDX_Control(pDX, IDC_PIC_IR_CH1_CLAMP3_UNLOCK, m_picCh1Clamp3Unlock);
	DDX_Control(pDX, IDC_PIC_IR_CH1_CLAMP4_UNLOCK, m_picCh1Clamp4Unlock);
	DDX_Control(pDX, IDC_PIC_IR_CH1_CLAMP5_UNLOCK, m_picCh1Clamp5Unlock);
	DDX_Control(pDX, IDC_PIC_IR_CH1_CLAMP6_UNLOCK, m_picCh1Clamp6Unlock);
	DDX_Control(pDX, IDC_PIC_IR_CH2_CLAMP1_UNLOCK, m_picCh2Clamp1Unlock);
	DDX_Control(pDX, IDC_PIC_IR_CH2_CLAMP2_UNLOCK, m_picCh2Clamp2Unlock);
	DDX_Control(pDX, IDC_PIC_IR_CH2_CLAMP3_UNLOCK, m_picCh2Clamp3Unlock);
	DDX_Control(pDX, IDC_PIC_IR_CH2_CLAMP4_UNLOCK, m_picCh2Clamp4Unlock);
	DDX_Control(pDX, IDC_PIC_IR_CH2_CLAMP5_UNLOCK, m_picCh2Clamp5Unlock);
	DDX_Control(pDX, IDC_PIC_IR_CH2_CLAMP6_UNLOCK, m_picCh2Clamp6Unlock);
}


BEGIN_MESSAGE_MAP(CIOReadyCheck, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_IR_CLOSE, &CIOReadyCheck::OnBnClickedBtnIrClose)
	ON_STN_CLICKED(IDC_STT_IR_REAR_DOOR_READY, &CIOReadyCheck::OnStnClickedSttIrRearDoorReady)
	ON_STN_CLICKED(IDC_STT_IR_FRONT_DOOR_READY, &CIOReadyCheck::OnStnClickedSttIrFrontDoorReady)
	ON_STN_CLICKED(IDC_STT_IR_FRONT_DOOR_HOLDING_READY, &CIOReadyCheck::OnStnClickedSttIrFrontDoorHoldingReady)
	ON_STN_CLICKED(IDC_STT_IR_ROBOT_IN_SENSOR_READY, &CIOReadyCheck::OnStnClickedSttIrRobotInSensorReady)
	ON_STN_CLICKED(IDC_STT_IR_JIG_TILTING_DOWN_READY, &CIOReadyCheck::OnStnClickedSttIrJigTiltingDownReady)
	ON_STN_CLICKED(IDC_STT_IR_JIG_DOOR_CLOSE_READY, &CIOReadyCheck::OnStnClickedSttIrJigDoorCloseReady)
	ON_STN_CLICKED(IDC_STT_IR_JIG_TRAY_IN_READY, &CIOReadyCheck::OnStnClickedSttIrJigTrayInReady)
	ON_STN_CLICKED(IDC_STT_IR_CH1_CLAMP_READY, &CIOReadyCheck::OnStnClickedSttIrCh1ClampReady)
	ON_STN_CLICKED(IDC_STT_IR_CH2_CLAMP_READY, &CIOReadyCheck::OnStnClickedSttIrCh2ClampReady)
END_MESSAGE_MAP()


// CIOReadyCheck 메시지 처리기


BOOL CIOReadyCheck::OnInitDialog()
{
	CDialog::OnInitDialog();
	lpSystemInfo = m_pApp->GetSystemInfo();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SendMessageToDescendants(WM_SETFONT, (WPARAM)m_pDefaultFont->GetSafeHandle(), 1, TRUE, FALSE);

	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();
	Lf_InitDlgDesign();

	SetTimer(1, 200, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CIOReadyCheck::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_BitButtonRed.Detach();
	m_BitButtonGreen.Detach();

	for (int i = 0; i < COLOR_IDX_MAX; i++)
	{
		m_Brush[i].DeleteObject();
	}

	for (int i = 0; i < FONT_IDX_MAX; i++)
	{
		m_Font[i].DeleteObject();
	}
}


BOOL CIOReadyCheck::PreTranslateMessage(MSG* pMsg)
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


HBRUSH CIOReadyCheck::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
			if (pWnd->GetDlgCtrlID() == IDC_STATIC)
			{
				pDC->SetBkColor(COLOR_WHITE);
				pDC->SetTextColor(COLOR_BLACK);
				return m_Brush[COLOR_IDX_WHITE];
			}

			if ((pWnd->GetDlgCtrlID() == IDC_STT_IR_REAR_DOOR_CLOSE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_IR_FRONT_DOOR_CLOSE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_IR_FRONT_DOOR_HOLDING)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_IR_ROBOT_IN_CHECK)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_IR_JIG_TILTING_DOWN)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_IR_JIG_DOOR_CLOSE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_IR_JIG_TRAY_IN)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_IR_CH1_CLAMP_UNLOCK)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_IR_CH2_CLAMP_UNLOCK)
				)
			{
				pDC->SetBkColor(COLOR_GRAY64);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY64];
			}

			if (pWnd->GetDlgCtrlID() == IDC_STT_IR_REAR_DOOR_READY)
			{
				if (m_rdyRearDoorClose == TRUE)
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
				else
				{
					if (m_ingRearDoorClose == TRUE)
					{
						pDC->SetBkColor(COLOR_ORANGE);
						pDC->SetTextColor(COLOR_BLACK);
						return m_Brush[COLOR_IDX_ORANGE];
					}
					else
					{
						pDC->SetBkColor(COLOR_RED);
						pDC->SetTextColor(COLOR_WHITE);
						return m_Brush[COLOR_IDX_RED];
					}
				}
			}

			if (pWnd->GetDlgCtrlID() == IDC_STT_IR_FRONT_DOOR_READY)
			{
				if (m_rdyFrontDoorClose == TRUE)
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
				else
				{
					if (m_ingFrontDoorClose == TRUE)
					{
						pDC->SetBkColor(COLOR_ORANGE);
						pDC->SetTextColor(COLOR_BLACK);
						return m_Brush[COLOR_IDX_ORANGE];
					}
					else
					{
						pDC->SetBkColor(COLOR_RED);
						pDC->SetTextColor(COLOR_WHITE);
						return m_Brush[COLOR_IDX_RED];
					}
				}
			}

			if (pWnd->GetDlgCtrlID() == IDC_STT_IR_FRONT_DOOR_HOLDING_READY)
			{
				if (m_rdyFrontDoorHoldingBackward == TRUE)
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
				else
				{
					if (m_ingFrontDoorHoldingBackward == TRUE)
					{
						pDC->SetBkColor(COLOR_ORANGE);
						pDC->SetTextColor(COLOR_BLACK);
						return m_Brush[COLOR_IDX_ORANGE];
					}
					else
					{
						pDC->SetBkColor(COLOR_RED);
						pDC->SetTextColor(COLOR_WHITE);
						return m_Brush[COLOR_IDX_RED];
					}
				}
			}

			if (pWnd->GetDlgCtrlID() == IDC_STT_IR_ROBOT_IN_SENSOR_READY)
			{
				if (m_rdyRobotInSensor == TRUE)
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
				else
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
			}

			if (pWnd->GetDlgCtrlID() == IDC_STT_IR_JIG_TILTING_DOWN_READY)
			{
				if (m_rdyJigTiltingDown == TRUE)
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
				else
				{
					if (m_ingJigTiltingDown == TRUE)
					{
						pDC->SetBkColor(COLOR_ORANGE);
						pDC->SetTextColor(COLOR_BLACK);
						return m_Brush[COLOR_IDX_ORANGE];
					}
					else
					{
						pDC->SetBkColor(COLOR_RED);
						pDC->SetTextColor(COLOR_WHITE);
						return m_Brush[COLOR_IDX_RED];
					}
				}
			}

			if (pWnd->GetDlgCtrlID() == IDC_STT_IR_JIG_DOOR_CLOSE_READY)
			{
				if (m_rdyJigDoorClose == TRUE)
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
				else
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
			}

			if (pWnd->GetDlgCtrlID() == IDC_STT_IR_JIG_TRAY_IN_READY)
			{
				if (m_rdyJigTrayIn == TRUE)
				{
					pDC->SetBkColor(COLOR_GREEN128);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN128];
				}
				else
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
			}

			if (pWnd->GetDlgCtrlID() == IDC_STT_IR_CH1_CLAMP_READY)
			{
				if (lpSystemInfo->m_nCarrierType == INSP_TYPE_CARRIER)
				{
					if (m_rdyCh1ClampUnlock == TRUE)
					{
						pDC->SetBkColor(COLOR_GREEN128);
						pDC->SetTextColor(COLOR_WHITE);
						return m_Brush[COLOR_IDX_GREEN128];
					}
					else
					{
						if (m_ingCh1ClampUnlock == TRUE)
						{
							pDC->SetBkColor(COLOR_ORANGE);
							pDC->SetTextColor(COLOR_BLACK);
							return m_Brush[COLOR_IDX_ORANGE];
						}
						else
						{
							pDC->SetBkColor(COLOR_RED);
							pDC->SetTextColor(COLOR_WHITE);
							return m_Brush[COLOR_IDX_RED];
						}
					}
				}
				else
				{
					pDC->SetBkColor(COLOR_GRAY128);
					pDC->SetTextColor(COLOR_BLACK);
					return m_Brush[COLOR_IDX_GRAY128];
				}
			}

			if (pWnd->GetDlgCtrlID() == IDC_STT_IR_CH2_CLAMP_READY)
			{
				if (lpSystemInfo->m_nCarrierType == INSP_TYPE_CARRIER)
				{
					if (m_rdyCh2ClampUnlock == TRUE)
					{
						pDC->SetBkColor(COLOR_GREEN128);
						pDC->SetTextColor(COLOR_WHITE);
						return m_Brush[COLOR_IDX_GREEN128];
					}
					else
					{
						if (m_ingCh2ClampUnlock == TRUE)
						{
							pDC->SetBkColor(COLOR_ORANGE);
							pDC->SetTextColor(COLOR_BLACK);
							return m_Brush[COLOR_IDX_ORANGE];
						}
						else
						{
							pDC->SetBkColor(COLOR_RED);
							pDC->SetTextColor(COLOR_WHITE);
							return m_Brush[COLOR_IDX_RED];
						}
					}
				}
				else
				{
					pDC->SetBkColor(COLOR_GRAY128);
					pDC->SetTextColor(COLOR_BLACK);
					return m_Brush[COLOR_IDX_GRAY128];
				}
			}

			break;
		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CIOReadyCheck::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.

	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, COLOR_GRAY159);
}


void CIOReadyCheck::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1)
	{
		KillTimer(1);

		Lf_updateIOReadyStatus();

		SetTimer(1, 200, NULL);

	}

	CDialog::OnTimer(nIDEvent);
}

void CIOReadyCheck::OnBnClickedBtnIrClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ((m_rdyRearDoorClose == TRUE)
		&& (m_rdyFrontDoorClose == TRUE)
		&& (m_rdyFrontDoorHoldingBackward == TRUE)
		&& (m_rdyRobotInSensor == TRUE)
		&& (m_rdyJigTiltingDown == TRUE)
		&& (m_rdyJigDoorClose == TRUE)
		&& (m_rdyJigTrayIn == TRUE)
		&& (m_rdyCh1ClampUnlock == TRUE)
		&& (m_rdyCh2ClampUnlock == TRUE)
		)
	{
		CDialog::OnOK();
	}
	else
	{
		CDialog::OnCancel();
	}
}


void CIOReadyCheck::OnStnClickedSttIrRearDoorReady()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_controlButtonEnable(FALSE);
	m_ingRearDoorClose = TRUE;

	if (m_pApp->commApi->dio_RearDoorClose() == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("REAR DOOR CLOSE TIME OUT"), ERROR_CODE_78);
	}

	m_ingRearDoorClose = FALSE;
	Lf_controlButtonEnable(TRUE);

	GetDlgItem(IDC_STT_IR_REAR_DOOR_READY)->ShowWindow(SW_SHOWNORMAL);
}


void CIOReadyCheck::OnStnClickedSttIrFrontDoorReady()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_controlButtonEnable(FALSE);
	m_ingFrontDoorClose = TRUE;

	if (m_pApp->commApi->dio_FrontDoorClose() == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FRONT DOOR CLOSE TIME OUT"), ERROR_CODE_84);
	}

	m_ingFrontDoorClose = FALSE;
	Lf_controlButtonEnable(TRUE);

	GetDlgItem(IDC_STT_IR_FRONT_DOOR_READY)->ShowWindow(SW_SHOWNORMAL);
}


void CIOReadyCheck::OnStnClickedSttIrFrontDoorHoldingReady()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_controlButtonEnable(FALSE);
	m_ingFrontDoorHoldingBackward = TRUE;

	if (m_pApp->commApi->dio_FrontDoorHoldingOff() == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("FRONT DOOR HOLDING OFF TIME OUT"), ERROR_CODE_86);
	}

	m_ingFrontDoorHoldingBackward = FALSE;
	Lf_controlButtonEnable(TRUE);

	GetDlgItem(IDC_STT_IR_FRONT_DOOR_HOLDING_READY)->ShowWindow(SW_SHOWNORMAL);
}


void CIOReadyCheck::OnStnClickedSttIrRobotInSensorReady()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CIOReadyCheck::OnStnClickedSttIrJigTiltingDownReady()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_controlButtonEnable(FALSE);
	m_ingJigTiltingDown = TRUE;

	if (m_pApp->commApi->dio_JigTiltingDown() == FALSE)
	{
		m_pApp->commApi->dio_JigTiltingDownCheck();
	}

	m_ingJigTiltingDown = FALSE;
	Lf_controlButtonEnable(TRUE);

	GetDlgItem(IDC_STT_IR_JIG_TILTING_DOWN_READY)->ShowWindow(SW_SHOWNORMAL);
}


void CIOReadyCheck::OnStnClickedSttIrJigDoorCloseReady()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CIOReadyCheck::OnStnClickedSttIrJigTrayInReady()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CIOReadyCheck::OnStnClickedSttIrCh1ClampReady()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_controlButtonEnable(FALSE);
	m_ingCh1ClampUnlock = TRUE;

	m_pApp->commApi->dio_JigClampUnLock(CH1);

	m_ingCh1ClampUnlock = FALSE;
	Lf_controlButtonEnable(TRUE);

	GetDlgItem(IDC_STT_IR_CH1_CLAMP_READY)->ShowWindow(SW_SHOWNORMAL);
}


void CIOReadyCheck::OnStnClickedSttIrCh2ClampReady()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_controlButtonEnable(FALSE);
	m_ingCh2ClampUnlock = TRUE;

	m_pApp->commApi->dio_JigClampUnLock(CH2);

	m_ingCh2ClampUnlock = FALSE;
	Lf_controlButtonEnable(TRUE);

	GetDlgItem(IDC_STT_IR_CH2_CLAMP_READY)->ShowWindow(SW_SHOWNORMAL);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CIOReadyCheck::Lf_InitLocalValue()
{
	m_BitButtonRed.LoadBitmap(IDB_BMP_BUTTON_RED);
	m_BitButtonGreen.LoadBitmap(IDB_BMP_BUTTON_GREEN);

	m_ingRearDoorClose = FALSE;
	m_ingFrontDoorClose = FALSE;
	m_ingFrontDoorHoldingBackward = FALSE;
	m_ingJigTiltingDown = FALSE;
	m_ingCh1ClampUnlock = FALSE;
	m_ingCh2ClampUnlock = FALSE;
}


void CIOReadyCheck::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(52, 23, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[2].CreateFont(30, 13, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[3].CreateFont(23, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_IR_REAR_DOOR_CLOSE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_FRONT_DOOR_CLOSE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_FRONT_DOOR_HOLDING)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_ROBOT_IN_CHECK)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_JIG_TILTING_DOWN)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_JIG_DOOR_CLOSE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_JIG_TRAY_IN)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_CH1_CLAMP_UNLOCK)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_CH2_CLAMP_UNLOCK)->SetFont(&m_Font[3]);

	GetDlgItem(IDC_STT_IR_REAR_DOOR_READY)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_FRONT_DOOR_READY)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_FRONT_DOOR_HOLDING_READY)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_ROBOT_IN_SENSOR_READY)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_JIG_TILTING_DOWN_READY)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_JIG_DOOR_CLOSE_READY)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_JIG_TRAY_IN_READY)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_CH1_CLAMP_READY)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_IR_CH2_CLAMP_READY)->SetFont(&m_Font[3]);

	GetDlgItem(IDC_BTN_IR_CLOSE)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(18, 7, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[5].CreateFont(16, 6, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

}

void CIOReadyCheck::Lf_InitColorBrush()
{
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush(COLOR_WHITE);
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_RED128].CreateSolidBrush(COLOR_RED128);
	m_Brush[COLOR_IDX_GREEN].CreateSolidBrush(COLOR_GREEN);
	m_Brush[COLOR_IDX_GREEN128].CreateSolidBrush(COLOR_GREEN128);
	m_Brush[COLOR_IDX_BLUE].CreateSolidBrush(COLOR_BLUE);
	m_Brush[COLOR_IDX_BLUE128].CreateSolidBrush(COLOR_BLUE128);
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush(COLOR_GRAY64);
	m_Brush[COLOR_IDX_GRAY96].CreateSolidBrush(COLOR_GRAY96);
	m_Brush[COLOR_IDX_GRAY128].CreateSolidBrush(COLOR_GRAY128);
	m_Brush[COLOR_IDX_GRAY159].CreateSolidBrush(COLOR_GRAY159);
	m_Brush[COLOR_IDX_GRAY192].CreateSolidBrush(COLOR_GRAY192);
	m_Brush[COLOR_IDX_GRAY240].CreateSolidBrush(COLOR_GRAY240);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
	m_Brush[COLOR_IDX_DARK_ORANGE].CreateSolidBrush(COLOR_DARK_ORANGE);
	m_Brush[COLOR_IDX_DARK_BLUE].CreateSolidBrush(COLOR_DARK_BLUE);
}


void CIOReadyCheck::Lf_InitDlgDesign()
{
	// Button ICON
	m_btnIrClose.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DISABLE));


	if (lpSystemInfo->m_nCarrierType == INSP_TYPE_NONE_CARRIER)
	{
		GetDlgItem(IDC_STT_IR_CH1_CLAMP_READY)->EnableWindow(FALSE);
		GetDlgItem(IDC_STT_IR_CH2_CLAMP_READY)->EnableWindow(FALSE);
	}
}


void CIOReadyCheck::Lf_controlButtonEnable(BOOL bEnable)
{
	GetDlgItem(IDC_STT_IR_REAR_DOOR_READY)->EnableWindow(bEnable);
	GetDlgItem(IDC_STT_IR_FRONT_DOOR_READY)->EnableWindow(bEnable);
	GetDlgItem(IDC_STT_IR_FRONT_DOOR_HOLDING_READY)->EnableWindow(bEnable);
	GetDlgItem(IDC_STT_IR_ROBOT_IN_SENSOR_READY)->EnableWindow(bEnable);
	GetDlgItem(IDC_STT_IR_JIG_TILTING_DOWN_READY)->EnableWindow(bEnable);
	GetDlgItem(IDC_STT_IR_JIG_DOOR_CLOSE_READY)->EnableWindow(bEnable);
	GetDlgItem(IDC_STT_IR_JIG_TRAY_IN_READY)->EnableWindow(bEnable);

	if (lpSystemInfo->m_nCarrierType == INSP_TYPE_CARRIER)
	{
		GetDlgItem(IDC_STT_IR_CH1_CLAMP_READY)->EnableWindow(bEnable);
		GetDlgItem(IDC_STT_IR_CH2_CLAMP_READY)->EnableWindow(bEnable);
	}
}


void CIOReadyCheck::Lf_updateIOReadyStatus()
{
	// REAR DOOR : LEFT CYLINDER DOWN
	if(m_pApp->m_nDioInBit[CH1][3] & DIN_D1_REAR_DOOR_LEFT_CYLINDER_DOWN)
		m_picRearDoorLeftCylinderDown.SetBitmap(m_BitButtonGreen);
	else
		m_picRearDoorLeftCylinderDown.SetBitmap(m_BitButtonRed);

	// REAR DOOR : RIGHT CYLINDER DOWN
	if (m_pApp->m_nDioInBit[CH1][3] & DIN_D1_REAR_DOOR_RIGHT_CYLINDER_DOWN)
		m_picRearDoorRightCylinderDown.SetBitmap(m_BitButtonGreen);
	else
		m_picRearDoorRightCylinderDown.SetBitmap(m_BitButtonRed);

	if ((m_pApp->m_nDioInBit[CH1][3] & DIN_D1_REAR_DOOR_LEFT_CYLINDER_DOWN)
		&& (m_pApp->m_nDioInBit[CH1][3] & DIN_D1_REAR_DOOR_RIGHT_CYLINDER_DOWN))
	{
		m_rdyRearDoorClose = TRUE;
	}
	else
	{
		m_rdyRearDoorClose = FALSE;
	}

	// FRONT DOOR : LEFT CYLINDER DOWN
	if (m_pApp->m_nDioInBit[CH1][2] & DIN_D1_FRONT_DOOR_LEFT_CYLINDER_DOWN)
		m_picFrontDoorLeftCylinderDown.SetBitmap(m_BitButtonGreen);
	else
		m_picFrontDoorLeftCylinderDown.SetBitmap(m_BitButtonRed);

	// FRONT DOOR : RIGHT CYLINDER DOWN
	if (m_pApp->m_nDioInBit[CH1][2] & DIN_D1_FRONT_DOOR_RIGHT_CYLINDER_DOWN)
		m_picFrontDoorRightCylinderDown.SetBitmap(m_BitButtonGreen);
	else
		m_picFrontDoorRightCylinderDown.SetBitmap(m_BitButtonRed);

	if ((m_pApp->m_nDioInBit[CH1][2] & DIN_D1_FRONT_DOOR_LEFT_CYLINDER_DOWN)
		&& (m_pApp->m_nDioInBit[CH1][2] & DIN_D1_FRONT_DOOR_RIGHT_CYLINDER_DOWN))
	{
		m_rdyFrontDoorClose = TRUE;
	}
	else
	{
		m_rdyFrontDoorClose = FALSE;
	}

	// FRONT DOOR HOLDING : CYLINDER BACKWARD
	if (m_pApp->m_nDioInBit[CH1][1] & DIN_D1_SHUTTER_HOLDING_BACKWARD)
	{
		m_picFrontDoorHoldingCylinderBack.SetBitmap(m_BitButtonGreen);
		m_rdyFrontDoorHoldingBackward = TRUE;
	}
	else
	{
		m_picFrontDoorHoldingCylinderBack.SetBitmap(m_BitButtonRed);
		m_rdyFrontDoorHoldingBackward = FALSE;
	}


	// ROBOT IN SENSOR : ROBOT IN SENSOR 1
	if ((m_pApp->m_nDioInBit[CH1][2] & DIN_D1_ROBOT_IN_SENSOR_1) ==0)
		m_picRobotInSensor1.SetBitmap(m_BitButtonGreen);
	else
		m_picRobotInSensor1.SetBitmap(m_BitButtonRed);

	// ROBOT IN SENSOR : ROBOT IN SENSOR 2
	if ((m_pApp->m_nDioInBit[CH1][2] & DIN_D1_ROBOT_IN_SENSOR_2) == 0)
		m_picRobotInSensor2.SetBitmap(m_BitButtonGreen);
	else
		m_picRobotInSensor2.SetBitmap(m_BitButtonRed);

	if (((m_pApp->m_nDioInBit[CH1][2] & DIN_D1_ROBOT_IN_SENSOR_1) == 0)
		&& ((m_pApp->m_nDioInBit[CH1][2] & DIN_D1_ROBOT_IN_SENSOR_2) == 0))
	{
		m_rdyRobotInSensor = TRUE;
	}
	else
	{
		m_rdyRobotInSensor = FALSE;
	}


	// JIG TILTING DOWN : JIG DOWN SENSOR1
	if (m_pApp->m_nDioInBit[CH1][3] & DIN_D1_JIG_DOWN_1_SENSOR)
		m_picJigDownSensor1.SetBitmap(m_BitButtonGreen);
	else
		m_picJigDownSensor1.SetBitmap(m_BitButtonRed);

	// JIG TILTING DOWN : JIG DOWN SENSOR2
	if (m_pApp->m_nDioInBit[CH1][3] & DIN_D1_JIG_DOWN_2_SENSOR)
		m_picJigDownSensor2.SetBitmap(m_BitButtonGreen);
	else
		m_picJigDownSensor2.SetBitmap(m_BitButtonRed);

	// JIG TILTING DOWN : JIG DOWN SENSOR3
	if (m_pApp->m_nDioInBit[CH1][4] & DIN_D1_JIG_DOWN_3_SENSOR)
		m_picJigDownSensor3.SetBitmap(m_BitButtonGreen);
	else
		m_picJigDownSensor3.SetBitmap(m_BitButtonRed);

	// JIG TILTING DOWN : JIG HOME SENSOR
	if (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_JIG_HOME_SENSOR)
		m_picJigHomeSensor.SetBitmap(m_BitButtonGreen);
	else
		m_picJigHomeSensor.SetBitmap(m_BitButtonRed);

	if ((m_pApp->m_nDioInBit[CH1][3] & DIN_D1_JIG_DOWN_1_SENSOR)
		&& (m_pApp->m_nDioInBit[CH1][3] & DIN_D1_JIG_DOWN_2_SENSOR)
		&& (m_pApp->m_nDioInBit[CH1][4] & DIN_D1_JIG_DOWN_3_SENSOR)
#if (DEBUG_JIG_HOME_SENSOR_PASS == 0)
		&& (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_JIG_HOME_SENSOR)
#endif
		)
	{
		m_rdyJigTiltingDown = TRUE;
	}
	else
	{
		m_rdyJigTiltingDown = FALSE;
	}


	// JIG DOOR CLOSE : JIG DOOR CLOSE SENSOR
	if (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_JIG_DOOR_CLOSE_SENSOR)
	{
		m_picJigDoorClose.SetBitmap(m_BitButtonGreen);
		m_rdyJigDoorClose = TRUE;
	}
	else
	{
		m_picJigDoorClose.SetBitmap(m_BitButtonRed);
		m_rdyJigDoorClose = FALSE;
	}


	// JIG TRAY IN : CH1 JIG TRAY IN
	if ((m_pApp->m_nDioInBit[CH2][0] & DIN_D2_CH1_JIG_TRAY_IN_SENSOR) == 0)
		m_picJigTrayInCh1.SetBitmap(m_BitButtonGreen);
	else
		m_picJigTrayInCh1.SetBitmap(m_BitButtonRed);

	// JIG TRAY IN : CH2 JIG TRAY IN
	if ((m_pApp->m_nDioInBit[CH2][0] & DIN_D2_CH2_JIG_TRAY_IN_SENSOR) == 0)
		m_picJigTrayInCh2.SetBitmap(m_BitButtonGreen);
	else
		m_picJigTrayInCh1.SetBitmap(m_BitButtonRed);

	if (((m_pApp->m_nDioInBit[CH2][0] & DIN_D2_CH1_JIG_TRAY_IN_SENSOR) == 0)
		&& ((m_pApp->m_nDioInBit[CH2][0] & DIN_D2_CH2_JIG_TRAY_IN_SENSOR) == 0))
	{
		m_rdyJigTrayIn = TRUE;
	}
	else
	{
		m_rdyJigTrayIn = FALSE;
	}


	if (lpSystemInfo->m_nCarrierType == INSP_TYPE_CARRIER)
	{
		// CH1 CLAMP UNLOCK : CH1 CLAMP1 UNLOCK
		if (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_CH1_TRAY_UNCLAMP1)
			m_picCh1Clamp1Unlock.SetBitmap(m_BitButtonGreen);
		else
			m_picCh1Clamp1Unlock.SetBitmap(m_BitButtonRed);

		// CH1 CLAMP UNLOCK : CH1 CLAMP2 UNLOCK
		if (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_CH1_TRAY_UNCLAMP2)
			m_picCh1Clamp2Unlock.SetBitmap(m_BitButtonGreen);
		else
			m_picCh1Clamp2Unlock.SetBitmap(m_BitButtonRed);

		// CH1 CLAMP UNLOCK : CH1 CLAMP3 UNLOCK
		if (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH1_TRAY_UNCLAMP3)
			m_picCh1Clamp3Unlock.SetBitmap(m_BitButtonGreen);
		else
			m_picCh1Clamp3Unlock.SetBitmap(m_BitButtonRed);

		// CH1 CLAMP UNLOCK : CH1 CLAMP4 UNLOCK
		if (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH1_TRAY_UNCLAMP4)
			m_picCh1Clamp4Unlock.SetBitmap(m_BitButtonGreen);
		else
			m_picCh1Clamp4Unlock.SetBitmap(m_BitButtonRed);

		// CH1 CLAMP UNLOCK : CH1 CLAMP5 UNLOCK
		if (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH1_TRAY_UNCLAMP5)
			m_picCh1Clamp5Unlock.SetBitmap(m_BitButtonGreen);
		else
			m_picCh1Clamp5Unlock.SetBitmap(m_BitButtonRed);

		// CH1 CLAMP UNLOCK : CH1 CLAMP6 UNLOCK
		if (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH1_TRAY_UNCLAMP6)
			m_picCh1Clamp6Unlock.SetBitmap(m_BitButtonGreen);
		else
			m_picCh1Clamp6Unlock.SetBitmap(m_BitButtonRed);

		if (m_pApp->commApi->dio_JigClampStatusCheck(CH1, CLAMP_UNLOCK) == TRUE)
		{
			m_rdyCh1ClampUnlock = TRUE;
		}
		else
		{
			m_rdyCh1ClampUnlock = FALSE;
		}


		// CH2 CLAMP UNLOCK : CH2 CLAMP1 UNLOCK
		if (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH2_TRAY_UNCLAMP1)
			m_picCh2Clamp1Unlock.SetBitmap(m_BitButtonGreen);
		else
			m_picCh2Clamp1Unlock.SetBitmap(m_BitButtonRed);

		// CH2 CLAMP UNLOCK : CH2 CLAMP2 UNLOCK
		if (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH2_TRAY_UNCLAMP2)
			m_picCh2Clamp2Unlock.SetBitmap(m_BitButtonGreen);
		else
			m_picCh2Clamp2Unlock.SetBitmap(m_BitButtonRed);

		// CH2 CLAMP UNLOCK : CH2 CLAMP3 UNLOCK
		if (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH2_TRAY_UNCLAMP3)
			m_picCh2Clamp3Unlock.SetBitmap(m_BitButtonGreen);
		else
			m_picCh2Clamp3Unlock.SetBitmap(m_BitButtonRed);

		// CH2 CLAMP UNLOCK : CH2 CLAMP4 UNLOCK
		if (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH2_TRAY_UNCLAMP4)
			m_picCh2Clamp4Unlock.SetBitmap(m_BitButtonGreen);
		else
			m_picCh2Clamp4Unlock.SetBitmap(m_BitButtonRed);

		// CH2 CLAMP UNLOCK : CH2 CLAMP5 UNLOCK
		if (m_pApp->m_nDioInBit[CH2][2] & DIN_D2_CH2_TRAY_UNCLAMP5)
			m_picCh2Clamp5Unlock.SetBitmap(m_BitButtonGreen);
		else
			m_picCh2Clamp5Unlock.SetBitmap(m_BitButtonRed);

		// CH2 CLAMP UNLOCK : CH2 CLAMP6 UNLOCK
		if (m_pApp->m_nDioInBit[CH2][2] & DIN_D2_CH2_TRAY_UNCLAMP6)
			m_picCh2Clamp6Unlock.SetBitmap(m_BitButtonGreen);
		else
			m_picCh2Clamp6Unlock.SetBitmap(m_BitButtonRed);

		if (m_pApp->commApi->dio_JigClampStatusCheck(CH2, CLAMP_UNLOCK) == TRUE)
		{
			m_rdyCh2ClampUnlock = TRUE;
		}
		else
		{
			m_rdyCh2ClampUnlock = FALSE;
		}
	}
	else
	{
		m_picCh1Clamp1Unlock.SetBitmap(m_BitButtonGreen);
		m_picCh1Clamp2Unlock.SetBitmap(m_BitButtonGreen);
		m_picCh1Clamp3Unlock.SetBitmap(m_BitButtonGreen);
		m_picCh1Clamp4Unlock.SetBitmap(m_BitButtonGreen);
		m_picCh1Clamp5Unlock.SetBitmap(m_BitButtonGreen);
		m_picCh1Clamp6Unlock.SetBitmap(m_BitButtonGreen);
		m_picCh2Clamp1Unlock.SetBitmap(m_BitButtonGreen);
		m_picCh2Clamp2Unlock.SetBitmap(m_BitButtonGreen);
		m_picCh2Clamp3Unlock.SetBitmap(m_BitButtonGreen);
		m_picCh2Clamp4Unlock.SetBitmap(m_BitButtonGreen);
		m_picCh2Clamp5Unlock.SetBitmap(m_BitButtonGreen);
		m_picCh2Clamp6Unlock.SetBitmap(m_BitButtonGreen);
	}


	GetDlgItem(IDC_STT_IR_REAR_DOOR_READY)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_IR_FRONT_DOOR_READY)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_IR_FRONT_DOOR_HOLDING_READY)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_IR_ROBOT_IN_SENSOR_READY)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_IR_JIG_TILTING_DOWN_READY)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_IR_JIG_DOOR_CLOSE_READY)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_IR_JIG_TRAY_IN_READY)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_IR_CH1_CLAMP_READY)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_IR_CH2_CLAMP_READY)->Invalidate(FALSE);

	if (m_ingRearDoorClose == TRUE)
	{
		if (m_bVisiableToggle == TRUE)	GetDlgItem(IDC_STT_IR_REAR_DOOR_READY)->ShowWindow(SW_SHOWNORMAL);
		else							GetDlgItem(IDC_STT_IR_REAR_DOOR_READY)->ShowWindow(SW_HIDE);
	}
	if (m_ingFrontDoorClose == TRUE)
	{
		if (m_bVisiableToggle == TRUE)	GetDlgItem(IDC_STT_IR_FRONT_DOOR_READY)->ShowWindow(SW_SHOWNORMAL);
		else							GetDlgItem(IDC_STT_IR_FRONT_DOOR_READY)->ShowWindow(SW_HIDE);
	}
	if (m_ingFrontDoorHoldingBackward == TRUE)
	{
		if (m_bVisiableToggle == TRUE)	GetDlgItem(IDC_STT_IR_FRONT_DOOR_HOLDING_READY)->ShowWindow(SW_SHOWNORMAL);
		else							GetDlgItem(IDC_STT_IR_FRONT_DOOR_HOLDING_READY)->ShowWindow(SW_HIDE);
	}
	if (m_ingJigTiltingDown == TRUE)
	{
		if (m_bVisiableToggle == TRUE)	GetDlgItem(IDC_STT_IR_JIG_TILTING_DOWN_READY)->ShowWindow(SW_SHOWNORMAL);
		else							GetDlgItem(IDC_STT_IR_JIG_TILTING_DOWN_READY)->ShowWindow(SW_HIDE);
	}
	if (m_ingCh1ClampUnlock == TRUE)
	{
		if (m_bVisiableToggle == TRUE)	GetDlgItem(IDC_STT_IR_CH1_CLAMP_READY)->ShowWindow(SW_SHOWNORMAL);
		else							GetDlgItem(IDC_STT_IR_CH1_CLAMP_READY)->ShowWindow(SW_HIDE);
	}
	if (m_ingCh2ClampUnlock == TRUE)
	{
		if (m_bVisiableToggle == TRUE)	GetDlgItem(IDC_STT_IR_CH2_CLAMP_READY)->ShowWindow(SW_SHOWNORMAL);
		else							GetDlgItem(IDC_STT_IR_CH2_CLAMP_READY)->ShowWindow(SW_HIDE);
	}

	if (m_bVisiableToggle == TRUE)
	{
		m_bVisiableToggle = FALSE;
	}
	else
	{
		m_bVisiableToggle = TRUE;
	}
}


