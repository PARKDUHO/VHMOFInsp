// CMaintenanceDIO.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CMaintenanceDIO.h"
#include "afxdialogex.h"


// CMaintenanceDIO 대화 상자

IMPLEMENT_DYNAMIC(CMaintenanceDIO, CDialog)

CMaintenanceDIO::CMaintenanceDIO(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MAINTENANCE_DIO, pParent)
{
	m_pDefaultFont = new CFont();
	m_pDefaultFont->CreateFont(14, 6, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
}

CMaintenanceDIO::~CMaintenanceDIO()
{
	if (m_pDefaultFont != NULL)
	{
		delete m_pDefaultFont;
	}
}

void CMaintenanceDIO::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_MO_DIO1_IN, m_lstMoDio1In);
	DDX_Control(pDX, IDC_LST_MO_DIO1_OUT, m_lstMoDio1Out);
	DDX_Control(pDX, IDC_LST_MO_DIO2_IN, m_lstMoDio2In);
	DDX_Control(pDX, IDC_LST_MO_DIO2_OUT, m_lstMoDio2Out);
}


BEGIN_MESSAGE_MAP(CMaintenanceDIO, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LST_MO_DIO1_IN, &CMaintenanceDIO::OnNMCustomdrawLstMoDio1In)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LST_MO_DIO1_OUT, &CMaintenanceDIO::OnNMCustomdrawLstMoDio1Out)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LST_MO_DIO2_IN, &CMaintenanceDIO::OnNMCustomdrawLstMoDio2In)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LST_MO_DIO2_OUT, &CMaintenanceDIO::OnNMCustomdrawLstMoDio2Out)
	ON_BN_CLICKED(IDC_BTN_MO_WRITE_DIO1, &CMaintenanceDIO::OnBnClickedBtnMoWriteDio1)
	ON_BN_CLICKED(IDC_BTN_MO_WRITE_DIO2, &CMaintenanceDIO::OnBnClickedBtnMoWriteDio2)
END_MESSAGE_MAP()


// CMaintenanceDIO 메시지 처리기


BOOL CMaintenanceDIO::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// Dialog의 기본 FONT 설정.
	SendMessageToDescendants(WM_SETFONT, (WPARAM)m_pDefaultFont->GetSafeHandle(), 1, TRUE, FALSE);

	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();

	Lf_initListDIN();
	Lf_setListCheck();

	SetTimer(1, 500, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMaintenanceDIO::OnDestroy()
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


BOOL CMaintenanceDIO::PreTranslateMessage(MSG* pMsg)
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


HBRUSH CMaintenanceDIO::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
			if ((pWnd->GetDlgCtrlID() == IDC_STT_MD_INTERFACE_TITLE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_MD_PWM_SET_TITLE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_MD_PATTERN_TITLE)
				)
			{
				pDC->SetBkColor(COLOR_BLACK);
				pDC->SetTextColor(COLOR_YELLOW);
				return m_Brush[COLOR_IDX_BLACK];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STATIC)
			{
				pDC->SetBkColor(COLOR_BLUISH);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_BLUISH];
			}


			break;
		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CMaintenanceDIO::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}


void CMaintenanceDIO::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1)
	{
		KillTimer(1);

		//if (m_pApp->commApi->dio_readDioInput(CH1) == TRUE)
		{
			// DIO 상태 변수는 Main Dialog의 Thread에서 업데이트 된다.
			Lf_updateStautsDio1In();
		}
		//if (m_pApp->commApi->dio_readDioInput(CH2) == TRUE)
		{
			// DIO 상태 변수는 Main Dialog의 Thread에서 업데이트 된다.
			Lf_updateStautsDio2In();
		}

		SetTimer(1, 500, NULL);
	}

	CDialog::OnTimer(nIDEvent);
}

void CMaintenanceDIO::OnNMCustomdrawLstMoDio1In(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bChecked;
	BOOL bErrorFlag = FALSE;
	BOOL bWarnningFlag = FALSE;

	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;
	bChecked = m_lstMoDio1In.GetCheck((int)pLVCD->nmcd.dwItemSpec);

	*pResult = 0;

	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
		*pResult = CDRF_NOTIFYITEMDRAW;

	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		if (bChecked)
		{
			pLVCD->clrText = RGB(255, 255, 255);	// 글자 색 변경 
			pLVCD->clrTextBk = RGB(0, 127, 0);		// 배경 색 변경 
		}
		else
		{
			pLVCD->clrText = RGB(0, 0, 0);			// 글자 색 변경 
			pLVCD->clrTextBk = RGB(224, 224, 224);	// 배경 색 변경 
		}

		*pResult = CDRF_DODEFAULT;
	}
}


void CMaintenanceDIO::OnNMCustomdrawLstMoDio1Out(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bChecked;
	BOOL bErrorFlag = FALSE;
	BOOL bWarnningFlag = FALSE;

	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;
	bChecked = m_lstMoDio1Out.GetCheck((int)pLVCD->nmcd.dwItemSpec);

	*pResult = 0;

	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
		*pResult = CDRF_NOTIFYITEMDRAW;

	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		if (bChecked)
		{
			pLVCD->clrText = RGB(255, 255, 255);	// 글자 색 변경 
			pLVCD->clrTextBk = RGB(0, 127, 0);		// 배경 색 변경 
		}
		else
		{
			pLVCD->clrText = RGB(0, 0, 0);			// 글자 색 변경 
			pLVCD->clrTextBk = RGB(255, 255, 255);	// 배경 색 변경 
		}

		*pResult = CDRF_DODEFAULT;
	}
}


void CMaintenanceDIO::OnNMCustomdrawLstMoDio2In(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bChecked;
	BOOL bErrorFlag = FALSE;
	BOOL bWarnningFlag = FALSE;

	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;
	bChecked = m_lstMoDio2In.GetCheck((int)pLVCD->nmcd.dwItemSpec);

	*pResult = 0;

	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
		*pResult = CDRF_NOTIFYITEMDRAW;

	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		if (bChecked)
		{
			pLVCD->clrText = RGB(255, 255, 255);	// 글자 색 변경 
			pLVCD->clrTextBk = RGB(0, 127, 0);		// 배경 색 변경 
		}
		else
		{
			pLVCD->clrText = RGB(0, 0, 0);			// 글자 색 변경 
			pLVCD->clrTextBk = RGB(224, 224, 224);	// 배경 색 변경 
		}

		*pResult = CDRF_DODEFAULT;
	}
}


void CMaintenanceDIO::OnNMCustomdrawLstMoDio2Out(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bChecked;
	BOOL bErrorFlag = FALSE;
	BOOL bWarnningFlag = FALSE;

	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;
	bChecked = m_lstMoDio2Out.GetCheck((int)pLVCD->nmcd.dwItemSpec);

	*pResult = 0;

	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
		*pResult = CDRF_NOTIFYITEMDRAW;

	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		if (bChecked)
		{
			pLVCD->clrText = RGB(255, 255, 255);	// 글자 색 변경 
			pLVCD->clrTextBk = RGB(0, 127, 0);		// 배경 색 변경 
		}
		else
		{
			pLVCD->clrText = RGB(0, 0, 0);			// 글자 색 변경 
			pLVCD->clrTextBk = RGB(255, 255, 255);	// 배경 색 변경 
		}

		*pResult = CDRF_DODEFAULT;
	}
}


void CMaintenanceDIO::OnBnClickedBtnMoWriteDio1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDOut = 0;

	if (m_lstMoDio1Out.GetCheck(0) == TRUE)		nDOut |= DOUT_D1_TOWER_LAMP_RED;
	if (m_lstMoDio1Out.GetCheck(1) == TRUE)		nDOut |= DOUT_D1_TOWER_LAMP_YELLOW;
	if (m_lstMoDio1Out.GetCheck(2) == TRUE)		nDOut |= DOUT_D1_TOWER_LAMP_GREEN;
	if (m_lstMoDio1Out.GetCheck(3) == TRUE)		nDOut |= DOUT_D1_TOWER_LAMP_BUZZER;
	if (m_lstMoDio1Out.GetCheck(4) == TRUE)		nDOut |= DOUT_D1_MUTTING_1;
	if (m_lstMoDio1Out.GetCheck(5) == TRUE)		nDOut |= DOUT_D1_MUTTING_2;
	if (m_lstMoDio1Out.GetCheck(6) == TRUE)		nDOut |= DOUT_D1_LEFT_SAFETY_DOOR_OPEN;
	if (m_lstMoDio1Out.GetCheck(7) == TRUE)		nDOut |= DOUT_D1_RIGHT_SAFETY_DOOR_OPEN;
	if (m_lstMoDio1Out.GetCheck(8) == TRUE)		nDOut |= DOUT_D1_FRONT_SHUTTER_DOWN;
	if (m_lstMoDio1Out.GetCheck(9) == TRUE)		nDOut |= DOUT_D1_FRONT_SHUTTER_UP;
	if (m_lstMoDio1Out.GetCheck(10) == TRUE)	nDOut |= DOUT_D1_REAR_SHUTTER_DOWN;
	if (m_lstMoDio1Out.GetCheck(11) == TRUE)	nDOut |= DOUT_D1_REAR_SHUTTER_UP;
	if (m_lstMoDio1Out.GetCheck(12) == TRUE)	nDOut |= DOUT_D1_JIG_TILTING01_DOWN;
	if (m_lstMoDio1Out.GetCheck(13) == TRUE)	nDOut |= DOUT_D1_JIG_TILTING01_UP;
	if (m_lstMoDio1Out.GetCheck(14) == TRUE)	nDOut |= DOUT_D1_JIG_TILTING02_DOWN;
	if (m_lstMoDio1Out.GetCheck(15) == TRUE)	nDOut |= DOUT_D1_JIG_TILTING02_UP;
	if (m_lstMoDio1Out.GetCheck(16) == TRUE)	nDOut |= DOUT_D1_IONIZER_BLOW;
	if (m_lstMoDio1Out.GetCheck(17) == TRUE)	nDOut |= DOUT_D1_IONIZER_ON_OFF;
	if (m_lstMoDio1Out.GetCheck(18) == TRUE)	nDOut |= DOUT_D1_LED_ON_OFF;
	if (m_lstMoDio1Out.GetCheck(19) == TRUE)	nDOut |= DOUT_D1_SPARE0;
	if (m_lstMoDio1Out.GetCheck(20) == TRUE)	nDOut |= DOUT_D1_SPARE1;
	if (m_lstMoDio1Out.GetCheck(21) == TRUE)	nDOut |= DOUT_D1_SPARE2;
	if (m_lstMoDio1Out.GetCheck(22) == TRUE)	nDOut |= DOUT_D1_SPARE3;
	if (m_lstMoDio1Out.GetCheck(23) == TRUE)	nDOut |= DOUT_D1_SPARE4;

	if (m_pApp->commApi->dio_writeDioOutput(CH1, nDOut) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("CH1 DIO WRITE FAIL"), ERROR_CODE_37);
	}
}


void CMaintenanceDIO::OnBnClickedBtnMoWriteDio2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDOut = 0;

	if (m_lstMoDio2Out.GetCheck(0) == TRUE)		nDOut |= DOUT_D2_CH1_TRAY_UNCLAMP_1;
	if (m_lstMoDio2Out.GetCheck(1) == TRUE)		nDOut |= DOUT_D2_CH1_TRAY_UNCLAMP_2;
	if (m_lstMoDio2Out.GetCheck(2) == TRUE)		nDOut |= DOUT_D2_CH1_TRAY_UNCLAMP_3;
	if (m_lstMoDio2Out.GetCheck(3) == TRUE)		nDOut |= DOUT_D2_CH1_TRAY_UNCLAMP_4;
	if (m_lstMoDio2Out.GetCheck(4) == TRUE)		nDOut |= DOUT_D2_CH1_TRAY_UNCLAMP_5;
	if (m_lstMoDio2Out.GetCheck(5) == TRUE)		nDOut |= DOUT_D2_CH1_TRAY_UNCLAMP_6;
	if (m_lstMoDio2Out.GetCheck(6) == TRUE)		nDOut |= DOUT_D2_CH2_TRAY_UNCLAMP_1;
	if (m_lstMoDio2Out.GetCheck(7) == TRUE)		nDOut |= DOUT_D2_CH2_TRAY_UNCLAMP_2;
	if (m_lstMoDio2Out.GetCheck(8) == TRUE)		nDOut |= DOUT_D2_CH2_TRAY_UNCLAMP_3;
	if (m_lstMoDio2Out.GetCheck(9) == TRUE)		nDOut |= DOUT_D2_CH2_TRAY_UNCLAMP_4;
	if (m_lstMoDio2Out.GetCheck(10) == TRUE)	nDOut |= DOUT_D2_CH2_TRAY_UNCLAMP_5;
	if (m_lstMoDio2Out.GetCheck(11) == TRUE)	nDOut |= DOUT_D2_CH2_TRAY_UNCLAMP_6;
	if (m_lstMoDio2Out.GetCheck(12) == TRUE)	nDOut |= DOUT_D2_CH1_ADSORPTION_EJECTOR;
	if (m_lstMoDio2Out.GetCheck(13) == TRUE)	nDOut |= DOUT_D2_CH1_PIN_CYLINDER_UP;
	if (m_lstMoDio2Out.GetCheck(14) == TRUE)	nDOut |= DOUT_D2_CH2_ADSORPTION_EJECTOR;
	if (m_lstMoDio2Out.GetCheck(15) == TRUE)	nDOut |= DOUT_D2_CH2_PIN_CYLINDER_UP;
	if (m_lstMoDio2Out.GetCheck(16) == TRUE)	nDOut |= DOUT_D2_SPARE1;
	if (m_lstMoDio2Out.GetCheck(17) == TRUE)	nDOut |= DOUT_D2_SPARE2;
	if (m_lstMoDio2Out.GetCheck(18) == TRUE)	nDOut |= DOUT_D2_SPARE3;
	if (m_lstMoDio2Out.GetCheck(19) == TRUE)	nDOut |= DOUT_D2_SPARE4;
	if (m_lstMoDio2Out.GetCheck(20) == TRUE)	nDOut |= DOUT_D2_SPARE5;
	if (m_lstMoDio2Out.GetCheck(21) == TRUE)	nDOut |= DOUT_D2_SPARE6;
	if (m_lstMoDio2Out.GetCheck(22) == TRUE)	nDOut |= DOUT_D2_SPARE7;
	if (m_lstMoDio2Out.GetCheck(23) == TRUE)	nDOut |= DOUT_D2_SPARE8;

	if (m_pApp->commApi->dio_writeDioOutput(CH2, nDOut) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("CH2 DIO WRITE FAIL"), ERROR_CODE_37);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMaintenanceDIO::Lf_InitLocalValue()
{

}

void CMaintenanceDIO::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(32, 13, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[2].CreateFont(23, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_LST_MO_DIO1_TITLE)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_LST_MO_DIO2_TITLE)->SetFont(&m_Font[2]);

	m_Font[3].CreateFont(21, 9, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[4].CreateFont(17, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[5].CreateFont(17, 6, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

}

void CMaintenanceDIO::Lf_InitColorBrush()
{
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush(COLOR_WHITE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_GREEN].CreateSolidBrush(COLOR_GREEN);
	m_Brush[COLOR_IDX_BLUE].CreateSolidBrush(COLOR_BLUE);
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_Brush[COLOR_IDX_YELLOW].CreateSolidBrush(COLOR_YELLOW);
	m_Brush[COLOR_IDX_MAGENTA].CreateSolidBrush(COLOR_MAGENTA);
	m_Brush[COLOR_IDX_VERDANT2].CreateSolidBrush(COLOR_VERDANT2);
	m_Brush[COLOR_IDX_JADEBLUE].CreateSolidBrush(COLOR_JADEBLUE);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
	m_Brush[COLOR_IDX_GRAY128].CreateSolidBrush(COLOR_GRAY128);
	m_Brush[COLOR_IDX_GRAY159].CreateSolidBrush(COLOR_GRAY159);
	m_Brush[COLOR_IDX_GRAY192].CreateSolidBrush(COLOR_GRAY192);
	m_Brush[COLOR_IDX_GRAY224].CreateSolidBrush(COLOR_GRAY224);
	m_Brush[COLOR_IDX_GRAY240].CreateSolidBrush(COLOR_GRAY240);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
}


CString strNameDIN1[40] =
{
	_T("EMO_SWITCH"),
	_T("START_SWITCH"),
	_T("RESET_SWITCH"),
	_T("MUTTING_SWITCH"),
	_T("LIGHT_CURTAIN"),
	_T("LEFT_SAFETY_DOOR"),
	_T("RIGHT_SAFETY_DOOR"),
	_T("LEFT_SHUTTER_HOLDING_SENSOR"),
	_T("RIGHT_SHUTTER_HOLDING_SENSOR"),
	_T("FAN_IN_ALARM"),
	_T("FAN_OUT_ALARM"),
	_T("TEMPATURE_HIGH_ALARM"),
	_T("MAIN_AIR_DIGITAL_PRESSURE_GAGE"),
	_T("IONIZER_AIR_DIGITAL_PRESSURE_GAGE"),
	_T("CYLINDER_DIGITAL_PRESSURE_GAGE"),
	_T("JIG_DIGITAL_PRESSURE_GAGE"),
	_T("IONIZER_ALARM"),
	_T("IONIZER (SPARE)"),
	_T("ROBOT_IN_SENSOR_1"),
	_T("ROBOT_IN_SENSOR_2"),
	_T("FRONT_SHUTTER_LEFT_BACKWARD"),
	_T("FRONT_SHUTTER_LEFT_FORWARD"),
	_T("FRONT_SHUTTER_RIGHT_BACKWARD"),
	_T("FRONT_SHUTTER_RIGHT_FORWARD"),
	_T("REAR_SHUTTER_LEFT_BACKWARD"),
	_T("REAR_SHUTTER_LEFT_FORWARD"),
	_T("REAR_SHUTTER_RIGHT_BACKWARD"),
	_T("REAR_SHUTTER_RIGHT_FORWARD"),
	_T("JIG_DOWN_1_SENSOR"),
	_T("JIG_UP_1_SENSOR"),
	_T("JIG_DOWN_2_SENSOR"),
	_T("JIG_UP_2_SENSOR"),
	_T("JIG_DOWN_3_SENSOR"),
	_T("JIG_UP_3_SENSOR"),
	_T(""),
	_T(""),
	_T(""),
	_T(""),
	_T(""),
};

CString strNameDOUT1[24] =
{
	_T("TOWER_LAMP_RED"),
	_T("TOWER_LAMP_YELLOW"),
	_T("TOWER_LAMP_GREEN"),
	_T("TOWER_LAMP_BUZZER"),
	_T("MUTTING_1"),
	_T("MUTTING_2"),
	_T("LEFT_SAFETY_DOOR_OPEN"),
	_T("RIGHT_SAFETY_DOOR_OPEN"),
	_T("FRONT_SHUTTER_DOWN"),
	_T("FRONT_SHUTTER_UP"),
	_T("REAR_SHUTTER_DOWN"),
	_T("REAR_SHUTTER_UP"),
	_T("JIG_TILTING01_DOWN"),
	_T("JIG_TILTING01_UP"),
	_T("JIG_TILTING02_DOWN"),
	_T("JIG_TILTING02_UP"),
	_T("IONIZER_BLOW"),
	_T("IONIZER_ON_OFF"),
	_T("LED_ON_OFF"),
	_T(""),
	_T(""),
	_T(""),
	_T(""),
	_T("")
};

CString strNameDIN2[40] =
{
	_T("JIG_HOME_SENSOR"),
	_T("JIG_DOOR_CLOSE_PHOTO_SENSOR"),
	_T("TILTING_60_SENSOR"),
	_T("TILTING_70_SENSOR"),
	_T("CH1_JIG_TRAY_IN_SENSOR"),
	_T("CH2_JIG_TRAY_IN_SENSOR"),
	_T("CH1_TRAY_UNCLAMP1"),
	_T("CH1_TRAY_UNCLAMP2"),
	_T("CH1_TRAY_UNCLAMP3"),
	_T("CH1_TRAY_UNCLAMP4"),
	_T("CH1_TRAY_UNCLAMP5"),
	_T("CH1_TRAY_UNCLAMP6"),
	_T("CH2_TRAY_UNCLAMP1"),
	_T("CH2_TRAY_UNCLAMP2"),
	_T("CH2_TRAY_UNCLAMP3"),
	_T("CH2_TRAY_UNCLAMP4"),
	_T("CH2_TRAY_UNCLAMP5"),
	_T("CH2_TRAY_UNCLAMP6"),
	_T("CH1_ADSORPTION_EJECTOR_DIGITAL_PRESSURE_GAUGE"),
	_T("CH2_ADSORPTION_EJECTOR_DIGITAL_PRESSURE_GAUGE"),
	_T(""),
	_T(""),
	_T(""),
	_T(""),
	_T("CH1_KEYPAD_AUTO_MANUAL"),
	_T("CH1_KEYPAD_BACK"),
	_T("CH1_KEYPAD_NEXT"),
	_T("CH1_KEYPAD_REPEAT"),
	_T("CH1_KEYPAD_RESET"),
	_T("CH1_KEYPAD_UP"),
	_T("CH1_KEYPAD_DOWN"),
	_T("CH1_KEYPAD_SEND"),
	_T("CH2_KEYPAD_AUTO_MANUAL"),
	_T("CH2_KEYPAD_BACK"),
	_T("CH2_KEYPAD_NEXT"),
	_T("CH2_KEYPAD_REPEAT"),
	_T("CH2_KEYPAD_RESET"),
	_T("CH2_KEYPAD_UP"),
	_T("CH2_KEYPAD_DOWN"),
	_T("CH2_KEYPAD_SEND")
};

CString strNameDOUT2[24] =
{
	_T("CH1_TRAY_UNCLAMP_1"),
	_T("CH1_TRAY_UNCLAMP_2"),
	_T("CH1_TRAY_UNCLAMP_3"),
	_T("CH1_TRAY_UNCLAMP_4"),
	_T("CH1_TRAY_UNCLAMP_5"),
	_T("CH1_TRAY_UNCLAMP_6"),
	_T("CH2_TRAY_UNCLAMP_1"),
	_T("CH2_TRAY_UNCLAMP_2"),
	_T("CH2_TRAY_UNCLAMP_3"),
	_T("CH2_TRAY_UNCLAMP_4"),
	_T("CH2_TRAY_UNCLAMP_5"),
	_T("CH2_TRAY_UNCLAMP_6"),
	_T("CH1_ADSORPTION_EJECTOR"),
	_T("CH1_PIN_CYLINDER_UP"),
	_T("CH2_ADSORPTION_EJECTOR"),
	_T("CH2_PIN_CYLINDER_UP"),
	_T(""),
	_T(""),
	_T(""),
	_T("")
};


void CMaintenanceDIO::Lf_initListDIN()
{
	DWORD dwStype;
	CString sdata;

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	m_lstMoDio1In.InsertColumn(0, _T("C"), LVCFMT_LEFT, -1, -1);
	m_lstMoDio1In.SetColumnWidth(0, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // Type
	m_lstMoDio1In.SetColumnWidth(0, 20);

	m_lstMoDio1In.InsertColumn(1, _T("DIN No"), LVCFMT_LEFT, -1, -1);
	m_lstMoDio1In.SetColumnWidth(1, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // Type
	m_lstMoDio1In.SetColumnWidth(1, 70);

	m_lstMoDio1In.InsertColumn(2, _T("Description"), LVCFMT_LEFT, -1, -1);
	m_lstMoDio1In.SetColumnWidth(2, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // Judge
	m_lstMoDio1In.SetColumnWidth(2, 300);

	dwStype = m_lstMoDio1In.GetExtendedStyle();
	dwStype |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES;
	m_lstMoDio1In.SetExtendedStyle(dwStype);

	for (int i = 0; i < 40; i++)
	{
		m_lstMoDio1In.InsertItem(i, _T(""));
		sdata.Format(_T("IN-%d"), i + 1);
		m_lstMoDio1In.SetItem(i, 1, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
		m_lstMoDio1In.SetItem(i, 2, LVIF_TEXT, strNameDIN1[i], 0, LVIF_STATE, 0, 0);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	m_lstMoDio1Out.InsertColumn(0, _T("C"), LVCFMT_LEFT, -1, -1);
	m_lstMoDio1Out.SetColumnWidth(0, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER);
	m_lstMoDio1Out.SetColumnWidth(0, 20);

	m_lstMoDio1Out.InsertColumn(1, _T("DOUT No"), LVCFMT_LEFT, -1, -1);
	m_lstMoDio1Out.SetColumnWidth(1, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER);
	m_lstMoDio1Out.SetColumnWidth(1, 70);

	m_lstMoDio1Out.InsertColumn(2, _T("Description"), LVCFMT_LEFT, -1, -1);
	m_lstMoDio1Out.SetColumnWidth(2, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER);
	m_lstMoDio1Out.SetColumnWidth(2, 250);

	dwStype = m_lstMoDio1Out.GetExtendedStyle();
	dwStype |= /*LVS_EX_FULLROWSELECT*/ LVS_EX_SINGLEROW | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES;
	m_lstMoDio1Out.SetExtendedStyle(dwStype);

	for (int i = 0; i < 24; i++)
	{
		m_lstMoDio1Out.InsertItem(i, _T(""));
		sdata.Format(_T("OUT-%d"), (i + 1));
		m_lstMoDio1Out.SetItem(i, 1, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
		m_lstMoDio1Out.SetItem(i, 2, LVIF_TEXT, strNameDOUT1[i], 0, LVIF_STATE, 0, 0);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	m_lstMoDio2In.InsertColumn(0, _T("C"), LVCFMT_LEFT, -1, -1);
	m_lstMoDio2In.SetColumnWidth(0, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // Type
	m_lstMoDio2In.SetColumnWidth(0, 20);

	m_lstMoDio2In.InsertColumn(1, _T("DIN No"), LVCFMT_LEFT, -1, -1);
	m_lstMoDio2In.SetColumnWidth(1, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // Type
	m_lstMoDio2In.SetColumnWidth(1, 70);

	m_lstMoDio2In.InsertColumn(2, _T("Description"), LVCFMT_LEFT, -1, -1);
	m_lstMoDio2In.SetColumnWidth(2, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // Judge
	m_lstMoDio2In.SetColumnWidth(2, 300);

	dwStype = m_lstMoDio2In.GetExtendedStyle();
	dwStype |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES;
	m_lstMoDio2In.SetExtendedStyle(dwStype);

	for (int i = 0; i < 40; i++)
	{
		m_lstMoDio2In.InsertItem(i, _T(""));
		sdata.Format(_T("IN-%d"), i + 1);
		m_lstMoDio2In.SetItem(i, 1, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
		m_lstMoDio2In.SetItem(i, 2, LVIF_TEXT, strNameDIN2[i], 0, LVIF_STATE, 0, 0);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	m_lstMoDio2Out.InsertColumn(0, _T("C"), LVCFMT_LEFT, -1, -1);
	m_lstMoDio2Out.SetColumnWidth(0, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER);
	m_lstMoDio2Out.SetColumnWidth(0, 20);

	m_lstMoDio2Out.InsertColumn(1, _T("DOUT No"), LVCFMT_LEFT, -1, -1);
	m_lstMoDio2Out.SetColumnWidth(1, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER);
	m_lstMoDio2Out.SetColumnWidth(1, 70);

	m_lstMoDio2Out.InsertColumn(2, _T("Description"), LVCFMT_LEFT, -1, -1);
	m_lstMoDio2Out.SetColumnWidth(2, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER);
	m_lstMoDio2Out.SetColumnWidth(2, 250);

	dwStype = m_lstMoDio2Out.GetExtendedStyle();
	dwStype |= /*LVS_EX_FULLROWSELECT*/ LVS_EX_SINGLEROW | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES;
	m_lstMoDio2Out.SetExtendedStyle(dwStype);

	for (int i = 0; i < 24; i++)
	{
		m_lstMoDio2Out.InsertItem(i, _T(""));
		sdata.Format(_T("OUT-%d"), (i + 1));
		m_lstMoDio2Out.SetItem(i, 1, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
		m_lstMoDio2Out.SetItem(i, 2, LVIF_TEXT, strNameDOUT2[i], 0, LVIF_STATE, 0, 0);
	}

}


void CMaintenanceDIO::Lf_setListCheck()
{
	if (m_pApp->m_nDioOutBit[CH1][0] & DOUT_D1_TOWER_LAMP_RED)					m_lstMoDio1Out.SetCheck(0, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][0] & DOUT_D1_TOWER_LAMP_YELLOW)				m_lstMoDio1Out.SetCheck(1, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][0] & DOUT_D1_TOWER_LAMP_GREEN)				m_lstMoDio1Out.SetCheck(2, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][0] & DOUT_D1_TOWER_LAMP_BUZZER)				m_lstMoDio1Out.SetCheck(3, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][0] & DOUT_D1_MUTTING_1)						m_lstMoDio1Out.SetCheck(4, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][0] & DOUT_D1_MUTTING_2)						m_lstMoDio1Out.SetCheck(5, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][0] & DOUT_D1_LEFT_SAFETY_DOOR_OPEN)			m_lstMoDio1Out.SetCheck(6, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][0] & DOUT_D1_RIGHT_SAFETY_DOOR_OPEN)			m_lstMoDio1Out.SetCheck(7, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][1] & (DOUT_D1_FRONT_SHUTTER_DOWN >> 8))		m_lstMoDio1Out.SetCheck(8, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][1] & (DOUT_D1_FRONT_SHUTTER_UP >> 8))			m_lstMoDio1Out.SetCheck(9, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][1] & (DOUT_D1_REAR_SHUTTER_DOWN >> 8))		m_lstMoDio1Out.SetCheck(10, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][1] & (DOUT_D1_REAR_SHUTTER_UP >> 8))			m_lstMoDio1Out.SetCheck(11, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][1] & (DOUT_D1_JIG_TILTING01_DOWN >> 8))		m_lstMoDio1Out.SetCheck(12, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][1] & (DOUT_D1_JIG_TILTING01_UP >> 8))			m_lstMoDio1Out.SetCheck(13, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][1] & (DOUT_D1_JIG_TILTING02_DOWN >> 8))		m_lstMoDio1Out.SetCheck(14, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][1] & (DOUT_D1_JIG_TILTING02_UP >> 8))			m_lstMoDio1Out.SetCheck(15, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][2] & (DOUT_D1_IONIZER_BLOW >> 16))			m_lstMoDio1Out.SetCheck(16, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][2] & (DOUT_D1_IONIZER_ON_OFF >> 16))			m_lstMoDio1Out.SetCheck(17, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][2] & (DOUT_D1_LED_ON_OFF >> 16))				m_lstMoDio1Out.SetCheck(18, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][2] & (DOUT_D1_SPARE0 >> 16))					m_lstMoDio1Out.SetCheck(19, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][2] & (DOUT_D1_SPARE1 >> 16))					m_lstMoDio1Out.SetCheck(20, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][2] & (DOUT_D1_SPARE2 >> 16))					m_lstMoDio1Out.SetCheck(21, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][2] & (DOUT_D1_SPARE3 >> 16))					m_lstMoDio1Out.SetCheck(22, TRUE);
	if (m_pApp->m_nDioOutBit[CH1][2] & (DOUT_D1_SPARE4 >> 16))					m_lstMoDio1Out.SetCheck(23, TRUE);

	if (m_pApp->m_nDioOutBit[CH2][0] & DOUT_D2_CH1_TRAY_UNCLAMP_1)				m_lstMoDio2Out.SetCheck(0, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][0] & DOUT_D2_CH1_TRAY_UNCLAMP_2)				m_lstMoDio2Out.SetCheck(1, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][0] & DOUT_D2_CH1_TRAY_UNCLAMP_3)				m_lstMoDio2Out.SetCheck(2, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][0] & DOUT_D2_CH1_TRAY_UNCLAMP_4)				m_lstMoDio2Out.SetCheck(3, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][0] & DOUT_D2_CH1_TRAY_UNCLAMP_5)				m_lstMoDio2Out.SetCheck(4, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][0] & DOUT_D2_CH1_TRAY_UNCLAMP_6)				m_lstMoDio2Out.SetCheck(5, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][0] & DOUT_D2_CH2_TRAY_UNCLAMP_1)				m_lstMoDio2Out.SetCheck(6, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][0] & DOUT_D2_CH2_TRAY_UNCLAMP_2)				m_lstMoDio2Out.SetCheck(7, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][1] & (DOUT_D2_CH2_TRAY_UNCLAMP_3 >> 8))		m_lstMoDio2Out.SetCheck(8, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][1] & (DOUT_D2_CH2_TRAY_UNCLAMP_4 >> 8))		m_lstMoDio2Out.SetCheck(9, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][1] & (DOUT_D2_CH2_TRAY_UNCLAMP_5 >> 8))		m_lstMoDio2Out.SetCheck(10, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][1] & (DOUT_D2_CH2_TRAY_UNCLAMP_6 >> 8))		m_lstMoDio2Out.SetCheck(11, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][1] & (DOUT_D2_CH1_ADSORPTION_EJECTOR >> 8))	m_lstMoDio2Out.SetCheck(12, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][1] & (DOUT_D2_CH1_PIN_CYLINDER_UP >> 8))		m_lstMoDio2Out.SetCheck(13, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][1] & (DOUT_D2_CH2_ADSORPTION_EJECTOR >> 8))	m_lstMoDio2Out.SetCheck(14, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][1] & (DOUT_D2_CH2_PIN_CYLINDER_UP >> 8))		m_lstMoDio2Out.SetCheck(15, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][2] & (DOUT_D2_SPARE1 >> 16))					m_lstMoDio2Out.SetCheck(16, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][2] & (DOUT_D2_SPARE2 >> 16))					m_lstMoDio2Out.SetCheck(17, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][2] & (DOUT_D2_SPARE3 >> 16))					m_lstMoDio2Out.SetCheck(18, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][2] & (DOUT_D2_SPARE4 >> 16))					m_lstMoDio2Out.SetCheck(19, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][2] & (DOUT_D2_SPARE5 >> 16))					m_lstMoDio2Out.SetCheck(20, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][2] & (DOUT_D2_SPARE6 >> 16))					m_lstMoDio2Out.SetCheck(21, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][2] & (DOUT_D2_SPARE7 >> 16))					m_lstMoDio2Out.SetCheck(22, TRUE);
	if (m_pApp->m_nDioOutBit[CH2][2] & (DOUT_D2_SPARE8 >> 16))					m_lstMoDio2Out.SetCheck(23, TRUE);
}


void CMaintenanceDIO::Lf_updateStautsDio1In()
{
	m_lstMoDio1In.SetCheck(0, (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_EMO_SWITCH));
	m_lstMoDio1In.SetCheck(1, (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_START_SWITCH));
	m_lstMoDio1In.SetCheck(2, (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_RESET_SWITCH));
	m_lstMoDio1In.SetCheck(3, (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_MUTTING_SWITCH));
	m_lstMoDio1In.SetCheck(4, (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_LIGHT_CURTAIN));
	m_lstMoDio1In.SetCheck(5, (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_LEFT_SAFETY_DOOR));
	m_lstMoDio1In.SetCheck(6, (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_RIGHT_SAFETY_DOOR));
	m_lstMoDio1In.SetCheck(7, (m_pApp->m_nDioInBit[CH1][0] & DIN_D1_LEFT_SHUTTER_HOLDING_SENSOR));

	m_lstMoDio1In.SetCheck(8, (m_pApp->m_nDioInBit[CH1][1] & DIN_D1_RIGHT_SHUTTER_HOLDING_SENSOR));
	m_lstMoDio1In.SetCheck(9, (m_pApp->m_nDioInBit[CH1][1] & DIN_D1_FAN_IN_ALARM));
	m_lstMoDio1In.SetCheck(10, (m_pApp->m_nDioInBit[CH1][1] & DIN_D1_FAN_OUT_ALARM));
	m_lstMoDio1In.SetCheck(11, (m_pApp->m_nDioInBit[CH1][1] & DIN_D1_TEMPATURE_HIGH_ALARM));
	m_lstMoDio1In.SetCheck(12, (m_pApp->m_nDioInBit[CH1][1] & DIN_D1_MAIN_AIR_DIGITAL_PRESSURE_GAGE));
	m_lstMoDio1In.SetCheck(13, (m_pApp->m_nDioInBit[CH1][1] & DIN_D1_IONIZER_AIR_DIGITAL_PRESSURE_GAGE));
	m_lstMoDio1In.SetCheck(14, (m_pApp->m_nDioInBit[CH1][1] & DIN_D1_CYLINDER_DIGITAL_PRESSURE_GAGE));
	m_lstMoDio1In.SetCheck(15, (m_pApp->m_nDioInBit[CH1][1] & DIN_D1_JIG_DIGITAL_PRESSURE_GAGE));

	m_lstMoDio1In.SetCheck(16, (m_pApp->m_nDioInBit[CH1][2] & DIN_D1_IONIZER_ALARM));
	m_lstMoDio1In.SetCheck(17, (m_pApp->m_nDioInBit[CH1][2] & DIN_D1_IONIZER_SPARE));
	m_lstMoDio1In.SetCheck(18, (m_pApp->m_nDioInBit[CH1][2] & DIN_D1_ROBOT_IN_SENSOR_1));
	m_lstMoDio1In.SetCheck(19, (m_pApp->m_nDioInBit[CH1][2] & DIN_D1_ROBOT_IN_SENSOR_2));
	m_lstMoDio1In.SetCheck(20, (m_pApp->m_nDioInBit[CH1][2] & DIN_D1_FRONT_SHUTTER_LEFT_BACKWARD));
	m_lstMoDio1In.SetCheck(21, (m_pApp->m_nDioInBit[CH1][2] & DIN_D1_FRONT_SHUTTER_LEFT_FORWARD));
	m_lstMoDio1In.SetCheck(22, (m_pApp->m_nDioInBit[CH1][2] & DIN_D1_FRONT_SHUTTER_RIGHT_BACKWARD));
	m_lstMoDio1In.SetCheck(23, (m_pApp->m_nDioInBit[CH1][2] & DIN_D1_FRONT_SHUTTER_RIGHT_FORWARD));

	m_lstMoDio1In.SetCheck(24, (m_pApp->m_nDioInBit[CH1][3] & DIN_D1_REAR_SHUTTER_LEFT_BACKWARD));
	m_lstMoDio1In.SetCheck(25, (m_pApp->m_nDioInBit[CH1][3] & DIN_D1_REAR_SHUTTER_LEFT_FORWARD));
	m_lstMoDio1In.SetCheck(26, (m_pApp->m_nDioInBit[CH1][3] & DIN_D1_REAR_SHUTTER_RIGHT_BACKWARD));
	m_lstMoDio1In.SetCheck(27, (m_pApp->m_nDioInBit[CH1][3] & DIN_D1_REAR_SHUTTER_RIGHT_FORWARD));
	m_lstMoDio1In.SetCheck(28, (m_pApp->m_nDioInBit[CH1][3] & DIN_D1_JIG_DOWN_1_SENSOR));
	m_lstMoDio1In.SetCheck(29, (m_pApp->m_nDioInBit[CH1][3] & DIN_D1_JIG_UP_1_SENSOR));
	m_lstMoDio1In.SetCheck(30, (m_pApp->m_nDioInBit[CH1][3] & DIN_D1_JIG_DOWN_2_SENSOR));
	m_lstMoDio1In.SetCheck(31, (m_pApp->m_nDioInBit[CH1][3] & DIN_D1_JIG_UP_2_SENSOR));

	m_lstMoDio1In.SetCheck(32, (m_pApp->m_nDioInBit[CH1][4] & DIN_D1_JIG_DOWN_3_SENSOR));
	m_lstMoDio1In.SetCheck(33, (m_pApp->m_nDioInBit[CH1][4] & DIN_D1_JIG_UP_3_SENSOR));
	m_lstMoDio1In.SetCheck(34, (m_pApp->m_nDioInBit[CH1][4] & DIN_D1_SPARE1));
	m_lstMoDio1In.SetCheck(35, (m_pApp->m_nDioInBit[CH1][4] & DIN_D1_SPARE2));
	m_lstMoDio1In.SetCheck(36, (m_pApp->m_nDioInBit[CH1][4] & DIN_D1_SPARE3));
	m_lstMoDio1In.SetCheck(37, (m_pApp->m_nDioInBit[CH1][4] & DIN_D1_SPARE4));
	m_lstMoDio1In.SetCheck(38, (m_pApp->m_nDioInBit[CH1][4] & DIN_D1_SPARE5));
	m_lstMoDio1In.SetCheck(39, (m_pApp->m_nDioInBit[CH1][4] & DIN_D1_SPARE6));
}


void CMaintenanceDIO::Lf_updateStautsDio2In()
{
	m_lstMoDio2In.SetCheck(0, (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_JIG_HOME_SENSOR));
	m_lstMoDio2In.SetCheck(1, (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_JIG_DOOR_CLOSE_PHOTO_SENSOR));
	m_lstMoDio2In.SetCheck(2, (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_TILTING_60_SENSOR));
	m_lstMoDio2In.SetCheck(3, (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_TILTING_70_SENSOR));
	m_lstMoDio2In.SetCheck(4, (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_CH1_JIG_TRAY_IN_SENSOR));
	m_lstMoDio2In.SetCheck(5, (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_CH2_JIG_TRAY_IN_SENSOR));
	m_lstMoDio2In.SetCheck(6, (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_CH1_TRAY_UNCLAMP1));
	m_lstMoDio2In.SetCheck(7, (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_CH1_TRAY_UNCLAMP2));

	m_lstMoDio2In.SetCheck(8, (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH1_TRAY_UNCLAMP3));
	m_lstMoDio2In.SetCheck(9, (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH1_TRAY_UNCLAMP4));
	m_lstMoDio2In.SetCheck(10, (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH1_TRAY_UNCLAMP5));
	m_lstMoDio2In.SetCheck(11, (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH1_TRAY_UNCLAMP6));
	m_lstMoDio2In.SetCheck(12, (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH2_TRAY_UNCLAMP1));
	m_lstMoDio2In.SetCheck(13, (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH2_TRAY_UNCLAMP2));
	m_lstMoDio2In.SetCheck(14, (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH2_TRAY_UNCLAMP3));
	m_lstMoDio2In.SetCheck(15, (m_pApp->m_nDioInBit[CH2][1] & DIN_D2_CH2_TRAY_UNCLAMP4));

	m_lstMoDio2In.SetCheck(16, (m_pApp->m_nDioInBit[CH2][2] & DIN_D2_CH2_TRAY_UNCLAMP5));
	m_lstMoDio2In.SetCheck(17, (m_pApp->m_nDioInBit[CH2][2] & DIN_D2_CH2_TRAY_UNCLAMP6));
	m_lstMoDio2In.SetCheck(18, (m_pApp->m_nDioInBit[CH2][2] & DIN_D2_SPARE1));
	m_lstMoDio2In.SetCheck(19, (m_pApp->m_nDioInBit[CH2][2] & DIN_D2_SPARE2));
	m_lstMoDio2In.SetCheck(20, (m_pApp->m_nDioInBit[CH2][2] & DIN_D2_SPARE3));
	m_lstMoDio2In.SetCheck(21, (m_pApp->m_nDioInBit[CH2][2] & DIN_D2_SPARE4));
	m_lstMoDio2In.SetCheck(22, (m_pApp->m_nDioInBit[CH2][2] & DIN_D2_SPARE5));
	m_lstMoDio2In.SetCheck(23, (m_pApp->m_nDioInBit[CH2][2] & DIN_D2_SPARE6));

	m_lstMoDio2In.SetCheck(24, (m_pApp->m_nDioInBit[CH2][3] & DIN_D2_CH1_KEYPAD_AUTO_MANUAL));
	m_lstMoDio2In.SetCheck(25, (m_pApp->m_nDioInBit[CH2][3] & DIN_D2_CH1_KEYPAD_BACK));
	m_lstMoDio2In.SetCheck(26, (m_pApp->m_nDioInBit[CH2][3] & DIN_D2_CH1_KEYPAD_NEXT));
	m_lstMoDio2In.SetCheck(27, (m_pApp->m_nDioInBit[CH2][3] & DIN_D2_CH1_KEYPAD_REPEAT));
	m_lstMoDio2In.SetCheck(28, (m_pApp->m_nDioInBit[CH2][3] & DIN_D2_CH1_KEYPAD_RESET));
	m_lstMoDio2In.SetCheck(29, (m_pApp->m_nDioInBit[CH2][3] & DIN_D2_CH1_KEYPAD_UP));
	m_lstMoDio2In.SetCheck(30, (m_pApp->m_nDioInBit[CH2][3] & DIN_D2_CH1_KEYPAD_DOWN));
	m_lstMoDio2In.SetCheck(31, (m_pApp->m_nDioInBit[CH2][3] & DIN_D2_CH1_KEYPAD_SEND));

	m_lstMoDio2In.SetCheck(32, (m_pApp->m_nDioInBit[CH2][4] & DIN_D2_CH2_KEYPAD_AUTO_MANUAL));
	m_lstMoDio2In.SetCheck(33, (m_pApp->m_nDioInBit[CH2][4] & DIN_D2_CH2_KEYPAD_BACK));
	m_lstMoDio2In.SetCheck(34, (m_pApp->m_nDioInBit[CH2][4] & DIN_D2_CH2_KEYPAD_NEXT));
	m_lstMoDio2In.SetCheck(35, (m_pApp->m_nDioInBit[CH2][4] & DIN_D2_CH2_KEYPAD_REPEAT));
	m_lstMoDio2In.SetCheck(36, (m_pApp->m_nDioInBit[CH2][4] & DIN_D2_CH2_KEYPAD_RESET));
	m_lstMoDio2In.SetCheck(37, (m_pApp->m_nDioInBit[CH2][4] & DIN_D2_CH2_KEYPAD_UP));
	m_lstMoDio2In.SetCheck(38, (m_pApp->m_nDioInBit[CH2][4] & DIN_D2_CH2_KEYPAD_DOWN));
	m_lstMoDio2In.SetCheck(39, (m_pApp->m_nDioInBit[CH2][4] & DIN_D2_CH2_KEYPAD_SEND));
}