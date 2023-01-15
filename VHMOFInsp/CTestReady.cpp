﻿// CTestReady.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CTestReady.h"
#include "afxdialogex.h"
#include "CTestPattern.h"
#include "CPanelID.h"
#include "CMessageQuestion.h"
#include "CDefectResult.h"

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
	lpModelInfo = m_pApp->GetModelInfo();
	lpInspWorkInfo = m_pApp->GetInspWorkInfo();
	lpSystemInfo = m_pApp->GetSystemInfo();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pApp->Gf_writeMLog(_T("<TEST> 'TEST READY' Dialog Open."));

	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();
	Lf_InitDlgDesign();

	Lf_readyInitialize();

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
	CMessageQuestion que_dlg;
	que_dlg.m_strQMessage.Format(_T("Do you want clear quantity count?"));
	que_dlg.m_strLButton = _T("YES");
	que_dlg.m_strRButton = _T("NO");
	if (que_dlg.DoModal() == IDOK)
	{
		CString sLog;
		sLog.Format(_T("<QTY> Quentity Count Reset."));
		m_pApp->Gf_writeMLog(sLog);

		m_pApp->Gf_QtyCountReset();
		Lf_updateQuantityCount();
	}
}


void CTestReady::OnBnClickedBtnTrTestStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for (int ch = CH1; ch < MAX_CH; ch++)
	{
		if (DEBUG_PG1_TEST_ONLY == TRUE)
		{
			Lf_FinalTestStart(ch);
			break;
		}
		else
		{
			if (ch == CH1)
			{
				if (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_CH1_JIG_TRAY_IN_SENSOR)
				{
					Lf_FinalTestStart(ch);
				}
			}
			if (ch == CH2)
			{
				if (m_pApp->m_nDioInBit[CH2][0] & DIN_D2_CH2_JIG_TRAY_IN_SENSOR)
				{
					Lf_FinalTestStart(ch);
				}
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTestReady::Lf_InitLocalValue()
{

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

void CTestReady::Lf_readyInitialize()
{
	Lf_updateQuantityCount();

	ZeroMemory(lpInspWorkInfo, sizeof(INSPWORKINFO));
	GetDlgItem(IDC_STT_TR_STATUS_MSG)->SetWindowText(_T(""));
}

void CTestReady::Lf_updateQuantityCount()
{
	CString sdata = _T("");

	sdata.Format(_T("%d"), lpSystemInfo->m_nQuantityOK + lpSystemInfo->m_nQuantityNG);
	GetDlgItem(IDC_STT_TR_QTY_TOTAL_VALUE)->SetWindowText(sdata);

	sdata.Format(_T("%d"), lpSystemInfo->m_nQuantityOK);
	GetDlgItem(IDC_STT_TR_QTY_OK_VALUE)->SetWindowText(sdata);

	sdata.Format(_T("%d"), lpSystemInfo->m_nQuantityNG);
	GetDlgItem(IDC_STT_TR_QTY_NG_VALUE)->SetWindowText(sdata);

	sdata.Format(_T("<QTY> Quantity Count.   TOTAL(%d), OK(%d), NG(%d)"), lpSystemInfo->m_nQuantityOK + lpSystemInfo->m_nQuantityNG, lpSystemInfo->m_nQuantityOK, lpSystemInfo->m_nQuantityNG);
	m_pApp->Gf_writeMLog(sdata);
}

BOOL CTestReady::Lf_FinalTestStart(int ch)
{
	CTestPattern pattern_dlg;
	pattern_dlg.m_nTargetCh = ch;

	if (m_pApp->Lf_checkDoorOpenInterLock() == FALSE)
	{
		goto ERR_EXCEPT;
	}

	if ((m_pApp->m_bUserIdPM == TRUE) || (m_pApp->m_bUserIdGieng == TRUE))
	{
		m_pApp->Gf_ShowMessageBox(MSG_WARNING, _T("PM MODE"), ERROR_CODE_0);
	}

	m_pApp->tt_startTime = CTime::GetCurrentTime();
	Lf_InspRoomLEDOnOff(ROOM_LED_OFF);

	if (Lf_checkPanelID(ch) == FALSE)
	{
		goto ERR_EXCEPT;
	}

	if (Lf_getControlBdReady(ch) == FALSE)
	{
		goto ERR_EXCEPT;
	}

	if (Lf_setSystemAutoFusing(ch) == FALSE)
	{
		goto ERR_EXCEPT;
	}

	if (m_pApp->Gf_gmesSendHost(HOST_PCHK) == FALSE)
	{
		return false;
	}

	if (Lf_AutoModelChange() == FALSE)
	{
		return false;
	}

	if (Lf_checkCableOpen(ch) == FALSE)
	{
		goto ERR_EXCEPT;
	}

	if (Lf_setGpioControl(ch) == FALSE)
	{
		goto ERR_EXCEPT;
	}

	if (Lf_setGioSetting(ch) == FALSE)
	{
		goto ERR_EXCEPT;
	}

	if (Lf_getFirmwareVersion(ch) == FALSE)
	{
		goto ERR_EXCEPT;
	}

	pattern_dlg.DoModal();
	m_pApp->tt_endTime = CTime::GetCurrentTime();

	if (Lf_sendPanelResult() == TRUE)
	{
		m_pApp->Gf_writeSummaryLog(ch);
	}

	/*********************************************************************************************************************/
	Lf_readyInitialize();
	Lf_InspRoomLEDOnOff(ROOM_LED_ON);

	return TRUE;

ERR_EXCEPT:
	// Error Exception. Initialize.
	m_pApp->tt_endTime = CTime::GetCurrentTime();

	Lf_readyInitialize();
	Lf_InspRoomLEDOnOff(ROOM_LED_ON);

	return FALSE;
}

BOOL CTestReady::Lf_InspRoomLEDOnOff(BOOL bOnOff)
{
	return m_pApp->commApi->dio_writeDioPortOnOff(CH1, DOUT_D1_LED_ON_OFF, bOnOff);
}

BOOL CTestReady::Lf_checkPanelID(int ch)
{
	char szTmpPID[1024] = { 0, };


	if (ch == CH1)		sprintf_s(szTmpPID, "%s", lpInspWorkInfo->m_szExtInputPID1);
	if (ch == CH2)		sprintf_s(szTmpPID, "%s", lpInspWorkInfo->m_szExtInputPID2);

	if (strlen(szTmpPID) == 0)
	{
		CPanelID pid_dlg;
		if (pid_dlg.DoModal() == IDCANCEL)
		{
			return FALSE;
		}
		sprintf_s(szTmpPID, "%s", wchar_To_char(pid_dlg.strInputPID.GetBuffer(0)));
	}
	else
	{
		if (((strlen(szTmpPID) < 7) || (strlen(szTmpPID) > 20)))
		{
			m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("WRONG PANEL ID"), ERROR_CODE_54);
			GetDlgItem(IDC_EDT_PID_INPUT)->SetWindowText(_T(""));
			return FALSE;
		}
	}

	sprintf_s(lpInspWorkInfo->m_szPanelID, "%s", szTmpPID);

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

			CString sTitle;
			sTitle.Format(_T("[CH%d] PG Communication Error"), ch);
			m_pApp->Gf_ShowMessageBox(MSG_ERROR, sTitle, ERROR_CODE_18);
			return FALSE;

		}
		nCnt++;
	}
	m_pApp->Gf_writeMLog(_T("<PG> CTRL B/D Ready Check OK."));

	return TRUE;
}

BOOL CTestReady::Lf_setSystemAutoFusing(int ch)
{
	m_pApp->Gf_writeMLog(_T("<TEST> System Auto Fusing"));
	if (m_pApp->commApi->main_setSystemFusing(ch) == TRUE)
	{
		m_pApp->Gf_writeMLog(_T("<TEST> System Auto Fusing => OK"));
		return TRUE;
	}
	else
	{
		m_pApp->Gf_writeMLog(_T("<TEST> System Auto Fusing => NG"));

		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("AUTO FUSING ERROR"), ERROR_CODE_58);
		return FALSE;
	}
}

BOOL CTestReady::Lf_AutoModelChange()
{
	if ((m_pApp->m_bUserIdGieng == TRUE) || (m_pApp->m_bUserIdPM == TRUE))
		return TRUE;

	CString strTopModelName;
	strTopModelName.Format(_T("%s"), char_To_wchar(lpInspWorkInfo->m_szHostTopModelName));
	// 현재 모델과 MES TOP_MODEL이 서로 다르면 자동 M/C를 진행한다.
	if (lpSystemInfo->m_sLastModelName != strTopModelName)
	{
		if (m_pApp->Gf_FindModelFile(strTopModelName) == TRUE)
		{
			CString sLog;
			sLog.Format(_T("<AUTO M/C> Auto Model Change OK.  [%s] => [%s]"), lpSystemInfo->m_sLastModelName, strTopModelName);
			m_pApp->Gf_writeMLog(sLog);

			lpSystemInfo->m_sLastModelName = strTopModelName;
			Write_SysIniFile(_T("SYSTEM"), _T("LAST_MODELNAME"), lpSystemInfo->m_sLastModelName);

			m_pApp->Gf_LoadModelData(strTopModelName);
			AfxGetApp()->GetMainWnd()->SendMessage(WM_UPDATE_SYSTEM_INFO, NULL, NULL);
		}
		else
		{
			m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("AUTO M/C ERROR"), ERROR_CODE_59, strTopModelName);
			return FALSE;
		}
	}

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

BOOL CTestReady::Lf_checkCableOpen(int ch)
{
	CString sLog;

	if (lpModelInfo->m_nCableOpenCheck == TRUE)
	{
		sLog.Format(_T("<TEST> Cable Open Check => Start"));
		m_pApp->Gf_writeMLog(sLog);

		if (m_pApp->commApi->main_setCableOpenCheck(ch) == TRUE)
		{
			lpInspWorkInfo->nCheckCableOpenComplete = TRUE;
			if (lpInspWorkInfo->nCheckCableOpenValue == 0)
			{
				sLog.Format(_T("<TEST> Cable Open Check => Complete"));
				m_pApp->Gf_writeMLog(sLog);

				lpInspWorkInfo->nCheckCableOpenResult = TRUE;
				return TRUE;
			}

			m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("USER CABLE OPEN CHECK ERROR"), ERROR_CODE_51);
		}
		else
		{
			m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("USER CABLE OPEN CHECK ERROR"), ERROR_CODE_50);
		}


		lpInspWorkInfo->nCheckCableOpenResult = FALSE;
		return FALSE;
	}
	else
	{
		sLog.Format(_T("<TEST> Cable Open Check => Skip"));
		m_pApp->Gf_writeMLog(sLog);
	}

	return TRUE;
}

BOOL CTestReady::Lf_setGpioControl(int ch)
{
	BOOL bRet;
	CString sLog;

	sLog.Format(_T("<TEST> GPIO PIN Control.  (GPIO1:%d, GPIO2:%d, GPIO3:%d"), lpModelInfo->m_nGpio1Output, lpModelInfo->m_nGpio2Output, lpModelInfo->m_nGpio3Output);
	m_pApp->Gf_writeMLog(sLog);

	bRet = m_pApp->commApi->main_setGpioControl(ch, lpModelInfo->m_nGpio1Output, lpModelInfo->m_nGpio2Output, lpModelInfo->m_nGpio3Output);

	if (bRet == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("GPIO CONTROL FAIL"), ERROR_CODE_52);
	}

	return bRet;
}

BOOL CTestReady::Lf_setGioSetting(int ch)
{
	BOOL bRet;
	CString sLog;

	sLog.Format(_T("<TEST> GIO PIN Setting.  (GIO1:%d, GIO2:%d, GIO3:%d, GIO4:%d"), lpModelInfo->m_nGio1Setting, lpModelInfo->m_nGio2Setting, lpModelInfo->m_nGio3Setting, lpModelInfo->m_nGio4Setting);
	m_pApp->Gf_writeMLog(sLog);

	bRet = m_pApp->commApi->main_setGioSetting(ch, lpModelInfo->m_nGio1Setting, lpModelInfo->m_nGio2Setting, lpModelInfo->m_nGio3Setting, lpModelInfo->m_nGio4Setting);

	if (bRet == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("GIO SETTING FAIL"), ERROR_CODE_53);
	}

	return bRet;
}

BOOL CTestReady::Lf_openGMESJudge()
{
	CString sdata = _T(""), outLog = _T("");
	CString strRwkCD;

	m_pApp->Gf_writeMLog(_T("<MES> Panel Judge Data"));

	int defecetResult = 0;

#if (MES_COMBI_CODE_USE==1)
	m_pApp->Gf_writeMLog(_T("<MES> CombiCode Dialog Open"));
	defecetResult = ShowDefectResult(GetSafeOwner());
	strRwkCD = GetRWK_CD();
#else
	m_pApp->Gf_writeMLog(_T("<MES> DefectCode Dialog Open"));
	CDefectResult dlg;
	defecetResult = (int)dlg.DoModal();
	strRwkCD = dlg.GetWRK_CD();
#endif

	m_pApp->m_pCimNet->SetRwkCode(strRwkCD);
	sprintf_s(lpInspWorkInfo->m_szReasonCode, "%s", wchar_To_char(strRwkCD.GetBuffer(0)));

	if ((defecetResult == IDOK) && (strRwkCD.IsEmpty() == TRUE))
	{
		lpInspWorkInfo->m_nPanelJudgeResult = GMES_PNF_PASS;
	}
	else if ((defecetResult == IDOK) && (strRwkCD.IsEmpty() == FALSE))
	{
		outLog.Format(_T("<MES> Select Reason Code - %s"), strRwkCD);
		m_pApp->Gf_writeMLog(outLog);

		lpInspWorkInfo->m_nPanelJudgeResult = GMES_PNF_FAIL;
	}
	else
	{
		m_pApp->Gf_writeMLog(_T("<MES> JUDGE CANCEL"));
		return FALSE;
	}

//	GetForegroundWindow()->PostMessage(WM_KEYDOWN, VK_F12, 0);
	return TRUE;
}

BOOL CTestReady::Lf_sendPanelResult()
{
	m_pApp->Gf_writeMLog(_T("<TEST> Panel Result Start"));

	if (Lf_openGMESJudge() == TRUE)
	{
		if (lpInspWorkInfo->m_nPanelJudgeResult == GMES_PNF_PASS)
		{
			if (m_pApp->Gf_gmesSendHost(HOST_EICR) == TRUE)
			{
				m_pApp->Gf_QtyCountUp(QTY_OK);
			}
		}
		if (lpInspWorkInfo->m_nPanelJudgeResult == GMES_PNF_FAIL)
		{
			if (m_pApp->Gf_gmesSendHost(HOST_EICR) == TRUE)
			{
				m_pApp->Gf_QtyCountUp(QTY_NG);
			}
		}

		return TRUE;
	}

	return FALSE;
}

