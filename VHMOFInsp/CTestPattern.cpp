// CTestPattern.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CTestPattern.h"
#include "afxdialogex.h"


// CTestPattern 대화 상자

IMPLEMENT_DYNAMIC(CTestPattern, CDialogEx)

CTestPattern::CTestPattern(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_PATTERN, pParent)
{
	m_pDefaultFont = new CFont();
	m_pDefaultFont->CreateFont(17, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_nTargetCh = CH1;
}

CTestPattern::~CTestPattern()
{
	if (m_pDefaultFont != NULL)
	{
		delete m_pDefaultFont;
	}
}

void CTestPattern::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_TP_PATTERN_LIST, m_lstTpPatternList);
	DDX_Control(pDX, IDC_LST_TP_EVENT_MSG, m_lstTpEventView);
}


BEGIN_MESSAGE_MAP(CTestPattern, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTestPattern 메시지 처리기


BOOL CTestPattern::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	lpInspWorkInfo = m_pApp->GetInspWorkInfo();
	lpSystemInfo = m_pApp->GetSystemInfo();
	lpModelInfo = m_pApp->GetModelInfo();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pApp->Gf_writeMLog(_T("<TEST> 'TEST PATTERN' Dialog Open."));

	// Dialog의 기본 FONT 설정.
	SendMessageToDescendants(WM_SETFONT, (WPARAM)m_pDefaultFont->GetSafeHandle(), 1, TRUE, FALSE);

	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();
	Lf_InitDlgDesign();

	Lf_insertListColum();
	Lf_insertListItem();

	// 첫번째 Pattern 출력 및 POWER ON
	Lf_setPowerOnAnd1stPattern();


	SetTimer(1, 200, NULL);	// EDID
	SetTimer(2, 1000, NULL);	// Power Measure
	SetTimer(3, 1000, NULL);  // OK,NG DIO Input Check
	SetTimer(5, 500, NULL);  // 첫번째 패턴 이미지 출력

	SetTimer(99, 200, NULL); // 마우스 고정
	SetTimer(100, 100, NULL);

	m_pApp->Gf_setStartPtnLockTime(0);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTestPattern::OnDestroy()
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

	m_pApp->commApi->main_setPowerSequenceOnOff(m_nTargetCh, POWER_OFF);
}

void CTestPattern::RemoveMessageFromQueue()
{
	MSG msg;
	while (PeekMessage(&msg, m_hWnd, WM_KEYDOWN, WM_LBUTTONUP, PM_NOREMOVE))
		PeekMessage(&msg, GetSafeHwnd(), NULL, NULL, PM_REMOVE);
}

BOOL CTestPattern::PreTranslateMessage(MSG* pMsg)
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
		RemoveMessageFromQueue();
		switch (pMsg->wParam)
		{
			case VK_RETURN:
			case VK_SPACE:
			case VK_HOME:
			case VK_BACK:
			case VK_END:
			{
				// ALT 또는 CONTROL 또는 SHIFT Key 입력 방지.
				if ((GetKeyState(VK_MENU) < 0) || (GetKeyState(VK_CONTROL) < 0) || (GetKeyState(VK_SHIFT) < 0))
					return TRUE;

				if (Lf_PatternLockTimeCheck() != TRUE)
					return TRUE;

				Lf_excutePatternList(pMsg);

				return TRUE;
			}
			case VK_RIGHT:
			case VK_LEFT:
			case VK_UP:
			case VK_DOWN:
			{
				RemoveMessageFromQueue();

				m_lstTpPatternList.SetSelectionMark(m_nPatternIndex);
				m_lstTpPatternList.SetItemState(m_nPatternIndex, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
				m_lstTpPatternList.SetFocus();

				Lf_setPatternGrayLevel((int)pMsg->wParam);
				return TRUE;
			}
			case VK_ESCAPE:
			{
				sprintf_s(lpInspWorkInfo->m_szBadPattern, "%S", lpModelInfo->m_sLbPtnListNAME[m_nPatternIndex].GetBuffer(0));
				lpInspWorkInfo->m_bEscDetect = true;

				Lf_PtnTestEventView(_T("ESC Key"));
				CDialog::OnCancel();
				return TRUE;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CTestPattern::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		{
			if (pWnd->GetDlgCtrlID() == IDC_LST_TP_EVENT_MSG)
			{
				pDC->SetBkColor(COLOR_BLACK);
				pDC->SetTextColor(COLOR_CYAN);
				return m_Brush[COLOR_IDX_BLACK];
			}
		}
		break;
		case CTLCOLOR_SCROLLBAR:
			break;
		case CTLCOLOR_BTN:
			break;
		case CTLCOLOR_STATIC:
			if ((pWnd->GetDlgCtrlID() == IDC_STT_TP_MEAS_VCC_TITLE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_MEAS_VEL_TITLE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_MEAS_VDD_TITLE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_MEAS_ICC_TITLE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_MEAS_IEL_TITLE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_MEAS_IDD_TITLE)
				)
			{
				pDC->SetBkColor(COLOR_DEEP_BLUE);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_DEEP_BLUE];
			}
			if ((pWnd->GetDlgCtrlID() == IDC_STT_TP_MEAS_VCC_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_MEAS_VEL_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_MEAS_VDD_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_MEAS_ICC_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_MEAS_IEL_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_MEAS_IDD_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_TACT_TIME_VALUE))
			{
				pDC->SetBkColor(COLOR_BLACK);
				pDC->SetTextColor(COLOR_GREEN);
				return m_Brush[COLOR_IDX_BLACK];
			}
			if ((pWnd->GetDlgCtrlID() == IDC_STT_TP_PATTERN_LIST_TITLE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_EVENT_MSG_TITLE)
				)
			{
				pDC->SetBkColor(COLOR_LIGHT_BLUE);
				pDC->SetTextColor(COLOR_BLACK);
				return m_Brush[COLOR_IDX_LIGHT_BLUE];
			}
			if ((pWnd->GetDlgCtrlID() == IDC_STT_TP_GRAY_LEVEL_R_TITLE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_GRAY_LEVEL_R_VALUE))
			{
				pDC->SetBkColor(COLOR_RED128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED128];
			}
			if ((pWnd->GetDlgCtrlID() == IDC_STT_TP_GRAY_LEVEL_G_TITLE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_GRAY_LEVEL_G_VALUE))
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			if ((pWnd->GetDlgCtrlID() == IDC_STT_TP_GRAY_LEVEL_B_TITLE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_TP_GRAY_LEVEL_B_VALUE))
			{
				pDC->SetBkColor(COLOR_BLUE128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_BLUE128];
			}

			break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CTestPattern::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, COLOR_GRAY64);
}


void CTestPattern::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1)
	{
		KillTimer(1);
	}
	else if (nIDEvent == 2)
	{
		KillTimer(2);
		if (Lf_updateMeasureInfo() == FALSE)
		{
			CDialog::OnCancel();
			return;
		}

		SetTimer(2, 1000, NULL);
	}
	else if (nIDEvent == 3)
	{
		KillTimer(3);
	}
	else if (nIDEvent == 5)
	{
		KillTimer(5);
	}
	else if (nIDEvent == 99)
	{
		KillTimer(99);
	}
	else if (nIDEvent == 100)
	{
		m_nInspTackTime = ::GetTickCount();
		m_nInspTackTime = m_nInspTackTime - m_nInspStartTime;
		if (m_nInspTackTime < 0)	m_nInspTackTime = 0;
		m_sTackTime.Format(_T("%.1f"), (m_nInspTackTime / 1000.0));
		GetDlgItem(IDC_STT_TP_TACT_TIME_VALUE)->SetWindowText(m_sTackTime);
	}
	CDialogEx::OnTimer(nIDEvent);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTestPattern::Lf_InitLocalValue()
{
	memset(m_pApp->m_nPatLock, 0x00, sizeof(m_pApp->m_nPatLock));

	m_nPatternIndex = 0;
	m_nInspStartTime = ::GetTickCount();

	lpInspWorkInfo->m_bEscDetect = false;
	lpInspWorkInfo->m_bIsEdidFail = false;
}

void CTestPattern::Lf_InitFontset()
{
	m_Font[0].CreateFont(80, 32, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(48, 20, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[2].CreateFont(34, 14, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[3].CreateFont(30, 12, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_TP_TACT_TIME_VALUE)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(24, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[5].CreateFont(17, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
}

void CTestPattern::Lf_InitColorBrush()
{
	// 각 Control의 COLOR 설정을 위한 Brush를 Setting 한다.
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush(COLOR_WHITE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_RED128].CreateSolidBrush(COLOR_RED128);
	m_Brush[COLOR_IDX_GREEN].CreateSolidBrush(COLOR_GREEN);
	m_Brush[COLOR_IDX_GREEN128].CreateSolidBrush(COLOR_GREEN128);
	m_Brush[COLOR_IDX_BLUE].CreateSolidBrush(COLOR_BLUE);
	m_Brush[COLOR_IDX_BLUE128].CreateSolidBrush(COLOR_BLUE128);
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

void CTestPattern::Lf_InitDlgDesign()
{
	// 	// Gradation Static
	// 	m_pApp->Gf_setGradientStatic(&m_sttUserIDTitle, COLOR_DEEP_BLUE, COLOR_DEEP_BLUE, COLOR_WHITE, &mFontH1[1], FALSE);
	// 	m_pApp->Gf_setGradientStatic(&m_sttUserIDInput, RGB(0, 192, 0), RGB(0, 128, 0), COLOR_WHITE, &mFontH1[1], FALSE);
	// 
	// 	// Button ICON
	// 	m_btnUserConfirm.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
	// 	m_btnUserCancel.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DISABLE));
}

void CTestPattern::Lf_insertListColum()
{
	CRect rect, rect2;
	DWORD dwStype;

	m_lstTpPatternList.GetClientRect(&rect);
	m_lstTpPatternList.InsertColumn(0, _T("No"), LVCFMT_CENTER, -1, -1);
	m_lstTpPatternList.InsertColumn(1, _T("Pattern Name"), LVCFMT_CENTER, -1, -1);
	m_lstTpPatternList.InsertColumn(2, _T("VCC(V)"), LVCFMT_CENTER, -1, -1);
	m_lstTpPatternList.InsertColumn(3, _T("VIN(V)"), LVCFMT_CENTER, -1, -1);
	m_lstTpPatternList.InsertColumn(4, _T("ICC(mA)"), LVCFMT_CENTER, -1, -1);
	m_lstTpPatternList.InsertColumn(5, _T("IIN(mA)"), LVCFMT_CENTER, -1, -1);
	m_lstTpPatternList.InsertColumn(6, _T("LockTime"), LVCFMT_CENTER, -1, -1);
	m_lstTpPatternList.InsertColumn(7, _T("MaxTime"), LVCFMT_CENTER, -1, -1);
	m_lstTpPatternList.InsertColumn(8, _T("VSYNC"), LVCFMT_CENTER, -1, -1);
	m_lstTpPatternList.InsertColumn(9, _T("ON/OFF"), LVCFMT_CENTER, -1, -1);

	m_lstTpPatternList.SetColumnWidth(0, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // NO
	m_lstTpPatternList.SetColumnWidth(0, 40);

	m_lstTpPatternList.SetColumnWidth(1, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // Pattern Name
	m_lstTpPatternList.SetColumnWidth(1, 300);

	m_lstTpPatternList.SetColumnWidth(2, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // VCC
	m_lstTpPatternList.SetColumnWidth(2, 80);

	m_lstTpPatternList.SetColumnWidth(3, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // VIN
	m_lstTpPatternList.SetColumnWidth(3, 80);

	m_lstTpPatternList.SetColumnWidth(4, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // ICC
	m_lstTpPatternList.SetColumnWidth(4, 80);

	m_lstTpPatternList.SetColumnWidth(5, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // IIN
	m_lstTpPatternList.SetColumnWidth(5, 80);

	m_lstTpPatternList.SetColumnWidth(6, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // LockTime
	m_lstTpPatternList.SetColumnWidth(6, 80);

	m_lstTpPatternList.SetColumnWidth(7, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // MaxTime
	m_lstTpPatternList.SetColumnWidth(7, 80);

	m_lstTpPatternList.SetColumnWidth(8, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // VSync
	m_lstTpPatternList.SetColumnWidth(8, 80);

	m_lstTpPatternList.SetColumnWidth(9, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // ON/OFF
	m_lstTpPatternList.SetColumnWidth(9, 80);

	dwStype = m_lstTpPatternList.GetExtendedStyle();
	dwStype |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_lstTpPatternList.SetExtendedStyle(dwStype);
}

void CTestPattern::Lf_insertListItem()
{
	int loop = 0;
	CString strNum = _T("");

	for (loop = 0; loop < lpModelInfo->m_nPatternListCount; loop++)
	{
		strNum.Format(_T("%d"), loop + 1);
		m_lstTpPatternList.InsertItem(loop, strNum);
		m_lstTpPatternList.SetItemText(loop, 1, lpModelInfo->m_sLbPtnListNAME[loop]);
		m_lstTpPatternList.SetItemText(loop, 2, lpModelInfo->m_sLbPtnListVCC[loop]);
		m_lstTpPatternList.SetItemText(loop, 3, lpModelInfo->m_sLbPtnListVEL[loop]);
		m_lstTpPatternList.SetItemText(loop, 4, lpModelInfo->m_sLbPtnListICC[loop]);
		m_lstTpPatternList.SetItemText(loop, 5, lpModelInfo->m_sLbPtnListIEL[loop]);
		m_lstTpPatternList.SetItemText(loop, 6, lpModelInfo->m_sLbPtnListLockTime[loop]);
		m_lstTpPatternList.SetItemText(loop, 7, lpModelInfo->m_sLbPtnListMaxTIME[loop]);
		m_lstTpPatternList.SetItemText(loop, 8, lpModelInfo->m_sLbPtnListVSYNC[loop]);
		m_lstTpPatternList.SetItemText(loop, 9, lpModelInfo->m_sLbPtnListONOFF[loop]);
	}

	m_lstTpPatternList.SetSelectionMark(m_nPatternIndex);
	m_lstTpPatternList.SetItemState(m_nPatternIndex, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	m_lstTpPatternList.SetFocus();
}

void CTestPattern::Lf_sendPtnData()
{
	CString sdata = _T("");

	CString strPacket;
	strPacket = m_pApp->commApi->makePGPatternString(lpModelInfo->m_sLbPtnListNAME[m_nPatternIndex]);
	int nRedData, nGreenData, nBlueData;
	Lf_getPatternGrayLevel(strPacket, &nRedData, &nGreenData, &nBlueData);

	//Lf_PtnTestEventView(strPacket);

	sdata.Format(_T("%d"), nRedData);
	GetDlgItem(IDC_STT_TP_GRAY_LEVEL_R_VALUE)->SetWindowTextW(sdata);
	sdata.Format(_T("%d"), nGreenData);
	GetDlgItem(IDC_STT_TP_GRAY_LEVEL_G_VALUE)->SetWindowTextW(sdata);
	sdata.Format(_T("%d"), nBlueData);
	GetDlgItem(IDC_STT_TP_GRAY_LEVEL_B_VALUE)->SetWindowTextW(sdata);

	sdata.Format(_T("%s (%sHz)"), lpModelInfo->m_sLbPtnListNAME[m_nPatternIndex].GetBuffer(0)
		, lpModelInfo->m_sLbPtnListVSYNC[m_nPatternIndex].GetBuffer(0));

	Lf_PtnTestEventView(sdata);

	if (lpModelInfo->m_nSignalType == SIGNAL_TYPE_ALPLD)
	{
		CString scriptName;
		scriptName.Format(_T("log_%s_CH%d.py"), lpModelInfo->m_sLbPtnListNAME[m_nPatternIndex], (m_nTargetCh + 1));
		m_pApp->commApi->alpdp_executePythonScript(m_nTargetCh, scriptName);
	}
	else
	{
		m_pApp->commApi->main_setPGInfoPatternName(m_nTargetCh, lpModelInfo->m_sLbPtnListNAME[m_nPatternIndex]);
	}
}

BOOL CTestPattern::Lf_updateMeasureInfo()
{
	CString sdata = _T("");
	CString strPacket;

	if (DEBUG_TCP_RECEIVE_OK == 1)
		return TRUE;

	if (m_pApp->commApi->main_getMeasurePowerAll(m_nTargetCh) == TRUE)
	{
		if (lpInspWorkInfo->m_nMeasureErrName[m_nTargetCh] != 0)
		{
			CString strSection, strErrMsg, strValue;
			if (lpInspWorkInfo->m_nMeasureErrName[m_nTargetCh] == 5)
			{
				strSection.Format(_T("POWER ALARM"));
				m_pApp->Gf_ShowMessageBox(MSG_ERROR, strSection, ERROR_CODE_14);
			}
			else
			{
				int errName, errCh;
				errName = lpInspWorkInfo->m_nMeasureErrName[m_nTargetCh];
				errCh = lpInspWorkInfo->m_nMeasureErrCh[m_nTargetCh];
				strSection.Format(_T("POWER LIMIT ALARM"));


				// VCC, I_VCC Limit Error
				if ((errName == 1) || (errName == 2))
					strValue.Format(_T("Setting[%.2fV ~ %.2fV]  Measure[%.2fV]"), lpModelInfo->m_fLimitVccLow, lpModelInfo->m_fLimitVccHigh, lpInspWorkInfo->m_nMeasureErrValue[m_nTargetCh] / 1000.0);
				else if ((errName == 3) || (errName == 4))
					strValue.Format(_T("Setting[%dmA ~ %dmA]  Measure[%dmA]"), lpModelInfo->m_nLimitIccLow, lpModelInfo->m_nLimitIccHigh, lpInspWorkInfo->m_nMeasureErrValue[m_nTargetCh]);

				if ((errCh == 1) && (errName == 1))	m_pApp->Gf_ShowMessageBox(MSG_ERROR, strSection, ERROR_CODE_2, strValue);
				if ((errCh == 1) && (errName == 2))	m_pApp->Gf_ShowMessageBox(MSG_ERROR, strSection, ERROR_CODE_3, strValue);
				if ((errCh == 1) && (errName == 3))	m_pApp->Gf_ShowMessageBox(MSG_ERROR, strSection, ERROR_CODE_4, strValue);
				if ((errCh == 1) && (errName == 4))	m_pApp->Gf_ShowMessageBox(MSG_ERROR, strSection, ERROR_CODE_5, strValue);


				// VIN, I_VIN Limit Error
				if ((errName == 1) || (errName == 2))
					strValue.Format(_T("Setting[%.2fV ~ %.2fV]  Measure[%.2fV]"), lpModelInfo->m_fLimitVelLow, lpModelInfo->m_fLimitVelHigh, lpInspWorkInfo->m_nMeasureErrValue[m_nTargetCh] / 1000.0);
				else if ((errName == 3) || (errName == 4))
					strValue.Format(_T("Setting[%dmA ~ %dmA]  Measure[%dmA]"), lpModelInfo->m_nLimitIelLow, lpModelInfo->m_nLimitIelHigh, lpInspWorkInfo->m_nMeasureErrValue[m_nTargetCh]);

				if ((errCh == 2) && (errName == 1))	m_pApp->Gf_ShowMessageBox(MSG_ERROR, strSection, ERROR_CODE_6, strValue);
				if ((errCh == 2) && (errName == 2))	m_pApp->Gf_ShowMessageBox(MSG_ERROR, strSection, ERROR_CODE_7, strValue);
				if ((errCh == 2) && (errName == 3))	m_pApp->Gf_ShowMessageBox(MSG_ERROR, strSection, ERROR_CODE_8, strValue);
				if ((errCh == 2) && (errName == 4))	m_pApp->Gf_ShowMessageBox(MSG_ERROR, strSection, ERROR_CODE_9, strValue);


				// VDD, I_VDD Limit Error
				if ((errName == 1) || (errName == 2))
					strValue.Format(_T("Setting[%.2fV ~ %.2fV]  Measure[%.2fV]"), lpModelInfo->m_fLimitVddLow, lpModelInfo->m_fLimitVddHigh, lpInspWorkInfo->m_nMeasureErrValue[m_nTargetCh] / 1000.0);
				else if ((errName == 3) || (errName == 4))
					strValue.Format(_T("Setting[%dmA ~ %dmA]  Measure[%dmA]"), lpModelInfo->m_nLimitIddLow, lpModelInfo->m_nLimitIddHigh, lpInspWorkInfo->m_nMeasureErrValue[m_nTargetCh]);

				if ((errCh == 3) && (errName == 1))	m_pApp->Gf_ShowMessageBox(MSG_ERROR, strSection, ERROR_CODE_10, strValue);
				if ((errCh == 3) && (errName == 2))	m_pApp->Gf_ShowMessageBox(MSG_ERROR, strSection, ERROR_CODE_11, strValue);
				if ((errCh == 3) && (errName == 3))	m_pApp->Gf_ShowMessageBox(MSG_ERROR, strSection, ERROR_CODE_12, strValue);
				if ((errCh == 3) && (errName == 4))	m_pApp->Gf_ShowMessageBox(MSG_ERROR, strSection, ERROR_CODE_13, strValue);
			}

			return FALSE;
		}
		sdata.Format(_T("%.2f"), (float)(lpInspWorkInfo->m_nMeasureVCC[m_nTargetCh] / 1000.f));
		GetDlgItem(IDC_STT_TP_MEAS_VCC_VALUE)->SetWindowText(sdata);
		sdata.Format(_T("%.2f"), (float)(lpInspWorkInfo->m_nMeasureVEL[m_nTargetCh] / 1000.f));
		GetDlgItem(IDC_STT_TP_MEAS_VEL_VALUE)->SetWindowText(sdata);
		sdata.Format(_T("%.2f"), (float)(lpInspWorkInfo->m_nMeasureVDD[m_nTargetCh] / 1000.f));
		GetDlgItem(IDC_STT_TP_MEAS_VDD_VALUE)->SetWindowText(sdata);
		sdata.Format(_T("%.2f"), (float)(lpInspWorkInfo->m_nMeasureICC[m_nTargetCh] / 1000.f));
		GetDlgItem(IDC_STT_TP_MEAS_ICC_VALUE)->SetWindowText(sdata);
		sdata.Format(_T("%.2f"), (float)(lpInspWorkInfo->m_nMeasureIDD[m_nTargetCh] / 1000.f));
		GetDlgItem(IDC_STT_TP_MEAS_IDD_VALUE)->SetWindowText(sdata);
	}
	return TRUE;
}

void CTestPattern::Lf_excutePatternList(MSG* pMsg)
{
	if ((GetKeyState(VK_MENU) < 0) || (GetKeyState(VK_CONTROL) < 0) || (GetKeyState(VK_SHIFT) < 0))
		return;

	switch (pMsg->wParam)
	{
	case VK_SPACE:
	case VK_RETURN:
		if (lpModelInfo->m_nPatternListCount - 1 <= m_nPatternIndex)
		{
			Lf_PtnTestEventView(_T("Pattern Test END"));
			CDialog::OnOK();
			return;
		}
		m_nPatternIndex++;

		break;
	case VK_BACK:
		if (m_nPatternIndex <= 0)
		{
			return;
		}
		m_nPatternIndex--;
		break;

	case VK_HOME:
		if (m_nPatternIndex == 0)	return;
		m_nPatternIndex = 0;
		break;

	case VK_END:
		if (m_nPatternIndex == lpModelInfo->m_nPatternListCount - 1)	return;
		m_nPatternIndex = lpModelInfo->m_nPatternListCount - 1;
		break;
	}
	m_lstTpPatternList.SetSelectionMark(m_nPatternIndex);
	m_lstTpPatternList.SetItemState(m_nPatternIndex, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	m_lstTpPatternList.SetFocus();

	RemoveMessageFromQueue();
	m_pApp->Gf_setPatStartCheckTime(m_nPatternIndex);
	m_pApp->Gf_setStartPtnLockTime(m_nPatternIndex);

	// Pattern Data 출력.
	Lf_sendPtnData();

	////////////////////////////////////////////////////////////////
	// Pattern별 기능검사
	////////////////////////////////////////////////////////////////
	if (Lf_PatternCurrentCheck() == FALSE)
	{
		CDialog::OnCancel();
	}
}

void CTestPattern::Lf_PtnTestEventView(CString Event)
{
	m_lstTpEventView.SetCurSel(m_lstTpEventView.AddString(Event));
	m_pApp->Gf_writeMLog(Event);	// MLOG 기록
}

void CTestPattern::Lf_setPatternGrayLevel(int wParam)
{
	CString strPattern;
	CString strPacket;
	CString strRdata, strGdata, strBdata;
	int colorConf = 0;
	int adjustValue = 0;
	int R_Val = 0, G_Val = 0, B_Val = 0;

	// 1. Pattern Name과 Index를 가져온다.

	strPattern = lpModelInfo->m_sLbPtnListNAME[m_nPatternIndex];

	strPattern.MakeUpper();

	// 2. Pattern 이름을 기준으로 가변할 Color 정보를 가져온다.
	// Pattern String을 만든다.
	int nPtnGrayLevel, nRedData, nGreenData, nBlueData;
	CString sdata;
	GetDlgItem(IDC_STT_TP_GRAY_LEVEL_R_VALUE)->GetWindowTextW(sdata);
	nRedData = (int)_ttoi(sdata);
	GetDlgItem(IDC_STT_TP_GRAY_LEVEL_G_VALUE)->GetWindowTextW(sdata);
	nGreenData = (int)_ttoi(sdata);
	GetDlgItem(IDC_STT_TP_GRAY_LEVEL_B_VALUE)->GetWindowTextW(sdata);
	nBlueData = (int)_ttoi(sdata);

	//    하위 3bit만 사용하며 R:2 G:1 B:0  bit를 할당한다. 
	if (strPattern.Find(_T("GRAY")) != -1) { colorConf = 0x07;	nPtnGrayLevel = nRedData; }
	else if (strPattern.Find(_T("WHITE")) != -1) { colorConf = 0x07;	nPtnGrayLevel = nRedData; }
	else if (strPattern.Find(_T("BLACK")) != -1) { colorConf = 0x07;	nPtnGrayLevel = nRedData; }
	else if (strPattern.Find(_T("RED")) != -1) { colorConf = 0x04;	nPtnGrayLevel = nRedData; }
	else if (strPattern.Find(_T("GREEN")) != -1) { colorConf = 0x02;	nPtnGrayLevel = nGreenData; }
	else if (strPattern.Find(_T("BLUE")) != -1) { colorConf = 0x01;	nPtnGrayLevel = nBlueData; }
	else if (strPattern.Find(_T("CYAN")) != -1) { colorConf = 0x03;	nPtnGrayLevel = nBlueData; }
	else if (strPattern.Find(_T("MAGENTA")) != -1) { colorConf = 0x05;	nPtnGrayLevel = nRedData; }
	else if (strPattern.Find(_T("YELLOW")) != -1) { colorConf = 0x06;	nPtnGrayLevel = nRedData; }
	else { return; }

	// 3. Gray 가변 Step 정보를 가져온다.
	if (wParam == VK_UP)	adjustValue = 5;
	if (wParam == VK_DOWN)	adjustValue = -5;
	if (wParam == VK_LEFT)	adjustValue = -2;
	if (wParam == VK_RIGHT)	adjustValue = 2;

	// 4. Gray Level 값을 변경한다.
	if (colorConf & 0x04)		R_Val = nPtnGrayLevel + adjustValue;
	if (colorConf & 0x02)		G_Val = nPtnGrayLevel + adjustValue;
	if (colorConf & 0x01)		B_Val = nPtnGrayLevel + adjustValue;

	// 5. Gray Level의 Limit를 계산한다.
	int upLimit = 0;
	if (lpModelInfo->m_nSignalBit == SIG_6BIT)	upLimit = 63;	// 6bit
	if (lpModelInfo->m_nSignalBit == SIG_8BIT)	upLimit = 255;	// 8bit
	if (lpModelInfo->m_nSignalBit == SIG_10BIT)	upLimit = 1023;	// 10bit
	if (lpModelInfo->m_nSignalBit == SIG_12BIT)	upLimit = 4095;	// 10bit

	if (R_Val < 0)			R_Val = 0;
	if (R_Val > upLimit)	R_Val = upLimit;
	if (G_Val < 0)			G_Val = 0;
	if (G_Val > upLimit)	G_Val = upLimit;
	if (B_Val < 0)			B_Val = 0;
	if (B_Val > upLimit)	B_Val = upLimit;

	// 6. PG에 전달할 String을 만든다.
	int nBitShift;
	if (lpModelInfo->m_nSignalBit == SIG_6BIT) // 6bit
	{
		nBitShift = 10;
		R_Val = (R_Val << nBitShift) | 0x03FF;
		G_Val = (G_Val << nBitShift) | 0x03FF;
		B_Val = (B_Val << nBitShift) | 0x03FF;
	}
	if (lpModelInfo->m_nSignalBit == SIG_8BIT) // 8bit
	{
		nBitShift = 8;
		R_Val = (R_Val << nBitShift) | 0xFF;
		G_Val = (G_Val << nBitShift) | 0xFF;
		B_Val = (B_Val << nBitShift) | 0xFF;
	}
	if (lpModelInfo->m_nSignalBit == SIG_10BIT) // 10bit
	{
		nBitShift = 6;
		R_Val = (R_Val << nBitShift) | 0x3F;
		G_Val = (G_Val << nBitShift) | 0x3F;
		B_Val = (B_Val << nBitShift) | 0x3F;
	}
	if (lpModelInfo->m_nSignalBit == SIG_12BIT) // 12bit
	{
		nBitShift = 4;
		R_Val = (R_Val << nBitShift) | 0x0F;
		G_Val = (G_Val << nBitShift) | 0x0F;
		B_Val = (B_Val << nBitShift) | 0x0F;
	}


	strPacket.Format(_T("CFG%04X%04X%04X"), R_Val, G_Val, B_Val);

	BOOL ret;
	ret = m_pApp->commApi->main_setPGInfoPatternString(m_nTargetCh, strPacket, FALSE);
	// 7. Pattern Data를 PG에 전송한다.
	if (ret == TRUE)
	{
		sdata.Format(_T("%d"), (R_Val >> nBitShift));
		GetDlgItem(IDC_STT_TP_GRAY_LEVEL_R_VALUE)->SetWindowText(sdata);
		sdata.Format(_T("%d"), (G_Val >> nBitShift));
		GetDlgItem(IDC_STT_TP_GRAY_LEVEL_G_VALUE)->SetWindowText(sdata);
		sdata.Format(_T("%d"), (B_Val >> nBitShift));
		GetDlgItem(IDC_STT_TP_GRAY_LEVEL_B_VALUE)->SetWindowText(sdata);
	}
}

void CTestPattern::Lf_getPatternGrayLevel(CString strPattern, int* r_level, int* g_level, int* b_level)
{
	int p_st;

	p_st = strPattern.Find(_T("CFG"));
	int gray = 0;
	if (lpModelInfo->m_nSignalBit == SIG_6BIT)	gray = 63;
	if (lpModelInfo->m_nSignalBit == SIG_8BIT)	gray = 255;
	if (lpModelInfo->m_nSignalBit == SIG_10BIT)	gray = 1023;
	if (lpModelInfo->m_nSignalBit == SIG_12BIT)	gray = 4095;

	if (p_st == -1)
	{
		*r_level = gray;
		*g_level = gray;
		*b_level = gray;
	}
	else
	{
		*r_level = _tcstol(strPattern.Mid(p_st + 3, 4), 0, 16);
		*g_level = _tcstol(strPattern.Mid(p_st + 7, 4), 0, 16);
		*b_level = _tcstol(strPattern.Mid(p_st + 11, 4), 0, 16);

		if (lpModelInfo->m_nSignalBit == SIG_6BIT)
		{
			*r_level = *r_level >> 10;
			*g_level = *g_level >> 10;
			*b_level = *b_level >> 10;
		}
		if (lpModelInfo->m_nSignalBit == SIG_8BIT)
		{
			*r_level = *r_level >> 8;
			*g_level = *g_level >> 8;
			*b_level = *b_level >> 8;
		}
		if (lpModelInfo->m_nSignalBit == SIG_10BIT)
		{
			*r_level = *r_level >> 6;
			*g_level = *g_level >> 6;
			*b_level = *b_level >> 6;
		}
		if (lpModelInfo->m_nSignalBit == SIG_12BIT)
		{
			*r_level = *r_level >> 4;
			*g_level = *g_level >> 4;
			*b_level = *b_level >> 4;
		}

		if (*r_level > gray)		*r_level = gray;
		if (*g_level > gray)		*g_level = gray;
		if (*b_level > gray)		*b_level = gray;
	}
}

BOOL CTestPattern::Lf_PatternLockTimeCheck()
{
	m_pApp->Gf_setPatEndCheckTime(m_nPatternIndex);
	m_pApp->m_nPatTime[m_nPatternIndex] = (m_pApp->m_nEndCheckTime[m_nPatternIndex] - m_pApp->m_nStartCheckTime[m_nPatternIndex]);

	int SetTime;
	m_pApp->Gf_setEndPtnLockTime(m_nPatternIndex);
	SetTime = _ttoi(lpModelInfo->m_sLbPtnListNAME[m_nPatternIndex]) * 1000;

	if ((m_pApp->m_nPtnLockTime[m_nPatternIndex] < SetTime) && (m_pApp->m_nPatLock[m_nPatternIndex] == FALSE))
		return FALSE;
	else
		m_pApp->m_nPatLock[m_nPatternIndex] = TRUE;

	return TRUE;
}

BOOL CTestPattern::Lf_PatternVoltageSetting()
{
#if (CODE_PATTERN_POWER_SET_USE == 1)
	float fVcc, fVel;
	fVcc = (float)_ttof(lpModelInfo->m_sLbPtnListVCC[m_nPatternIndex]);
	fVel = (float)_ttof(lpModelInfo->m_sLbPtnListVEL[m_nPatternIndex]);
	if ((m_fPatternVccOld != fVcc) || (m_fPatternVddOld != fVel))
	{
		m_fPatternVccOld = fVcc;
		m_fPatternVddOld = fVel;

		char szPacket[128];
		int length;
		sprintf_s(szPacket, "%05d%05d", (int)(fVcc * 1000 + 0.5), (int)(fVel * 1000 + 0.5));
		length = (int)strlen(szPacket);
		if (m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_POWER_VOLTAGE_SET, length, szPacket) == FALSE)
		{
			m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("POWER SET FAIL"), ERROR_CODE_15);
			return FALSE;
		}
	}
#endif
	return TRUE;
}

BOOL CTestPattern::Lf_PatternCurrentCheck()
{
	CString strmsg;
	int nIcc, nIel;
	nIcc = (int)_ttoi(lpModelInfo->m_sLbPtnListICC[m_nPatternIndex]);
	nIel = (int)_ttoi(lpModelInfo->m_sLbPtnListIEL[m_nPatternIndex]);

	if ((nIcc > 0) || (nIel > 0))
	{
		if (m_nPatternIndex == 0)
		{
			Lf_updateMeasureInfo();
		}
		delayMs(2000);
	}
	if (nIcc > 0)
	{
		if (nIcc < lpInspWorkInfo->m_nMeasureICC[m_nTargetCh])
		{
			m_pApp->commApi->main_setPowerSequenceOnOff(m_nTargetCh, POWER_OFF);
			strmsg.Format(_T("- ICC Setting[%dmA]  ICC Measure[%dmA]"), nIcc, lpInspWorkInfo->m_nMeasureICC[m_nTargetCh]);
			m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("ICC CHECK ERROR (PATTERN)"), ERROR_CODE_16, strmsg);
			return FALSE;
		}
	}
	if (nIel > 0)
	{
		if (nIel < lpInspWorkInfo->m_nMeasureIEL[m_nTargetCh])
		{
			m_pApp->commApi->main_setPowerSequenceOnOff(m_nTargetCh, POWER_OFF);
			strmsg.Format(_T("- IIN Setting[%dmA]  IIN Measure[%dmA]"), nIel, lpInspWorkInfo->m_nMeasureIEL[m_nTargetCh]);
			m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("IIN CHECK ERROR"), ERROR_CODE_17, strmsg);
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CTestPattern::Lf_sendAlpdpInitScript()
{
	if (lpModelInfo->m_nSignalType != SIGNAL_TYPE_ALPLD)
		return TRUE;

	if (lpModelInfo->m_nInitScript == ALPDP_INIT_NONE)
		return TRUE;

	CString scriptName;

	if (lpModelInfo->m_nInitScript == ALPDP_INIT_X2146)
		scriptName.Format(_T("X2146_CH%d.py"), (m_nTargetCh + 1));
	else if (lpModelInfo->m_nInitScript == ALPDP_INIT_X2180)
		scriptName.Format(_T("X2180_CH%d.py"), (m_nTargetCh + 1));

	m_pApp->commApi->alpdp_executePythonScript(m_nTargetCh, scriptName);

	return TRUE;
}

void CTestPattern::Lf_setPowerOnAnd1stPattern()
{
	if (lpModelInfo->m_nSignalType == SIGNAL_TYPE_ALPLD)
	{
		// ALPDP는 Power ON이후 Link Training 및 Pattern 전송을 해야한다.
		m_pApp->commApi->main_setPowerSequenceOnOff(m_nTargetCh, POWER_ON);
		Lf_sendAlpdpInitScript();
		Lf_sendPtnData();
	}
	else
	{
		// DP는 Pattern을 출력후 Power On 하도록 한다.
		Lf_sendPtnData();
		m_pApp->commApi->main_setPowerSequenceOnOff(m_nTargetCh, POWER_ON);
	}

}
