// CSystem.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CSystem.h"
#include "afxdialogex.h"


// CSystem 대화 상자

IMPLEMENT_DYNAMIC(CSystem, CDialog)

CSystem::CSystem(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SYSTEM, pParent)
{
	m_pDefaultFont = new CFont();
	m_pDefaultFont->CreateFont(17, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
}

CSystem::~CSystem()
{
	if (m_pDefaultFont != NULL)
	{
		delete m_pDefaultFont;
	}
}

void CSystem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_SY_SAVE_EXIT, m_btnSySaveExit);
	DDX_Control(pDX, IDC_BTN_SY_CANCEL, m_btnSyCancel);
	DDX_Control(pDX, IDC_EDT_SY_EQP_NAME, m_edtSyEqpName);
	DDX_Control(pDX, IDC_CBO_SY_LINE_TYPE, m_cmbSyLineType);
	DDX_Control(pDX, IDC_CBO_SY_CARRIER_TYPE, m_cmbSyCarrierType);
	DDX_Control(pDX, IDC_CBO_SY_ECS_ONLINE_MODE, m_cmbSyEcsOnLineMode);
	DDX_Control(pDX, IDC_EDT_SY_LB_START_ADDR, m_edtSyLBStartAddr);
	DDX_Control(pDX, IDC_EDT_SY_LW_START_ADDR1, m_edtSyLWStartAddr1);
	DDX_Control(pDX, IDC_EDT_SY_LW_START_ADDR2, m_edtSyLWStartAddr2);
	DDX_Control(pDX, IDC_CBO_SY_ECS_EQP_NUMBER, m_cmbSyEcsEqpNumber);
	DDX_Control(pDX, IDC_EDT_SY_MES_SERVICEPORT, m_edtSyMesServicePort);
	DDX_Control(pDX, IDC_EDT_SY_MES_NETWORK, m_edtSyMesNetwork);
	DDX_Control(pDX, IDC_EDT_SY_MES_DEMONPORT, m_edtSyMesDaemonPort);
	DDX_Control(pDX, IDC_EDT_SY_MES_LOCALSUBJECT, m_edtSyMesLocalSubject);
	DDX_Control(pDX, IDC_EDT_SY_MES_REMOTESUBJECT, m_edtSyMesRemoteSubject);
	DDX_Control(pDX, IDC_IPD_SY_MES_LOCAL_IP, m_ipaSyMesLocalIp);
	DDX_Control(pDX, IDC_CBO_SY_EAS_USE, m_cmbSyEasUse);
	DDX_Control(pDX, IDC_EDT_SY_EAS_SERVICEPORT, m_edtSyEasServicePort);
	DDX_Control(pDX, IDC_EDT_SY_EAS_NETWORK, m_edtSyEasNetwork);
	DDX_Control(pDX, IDC_EDT_SY_EAS_DEMONPORT, m_edtSyEasDaemonPort);
	DDX_Control(pDX, IDC_EDT_SY_EAS_LOCALSUBJECT, m_edtSyEasLocalSubject);
	DDX_Control(pDX, IDC_EDT_SY_EAS_REMOTESUBJECT, m_edtSyEasRemoteSubject);
	DDX_Control(pDX, IDC_EDT_SY_MODEL_FILE_PATH, m_edtSyModelFilePath);
	DDX_Control(pDX, IDC_EDT_SY_PATTERN_FILE_PATH, m_edtSyPatternFilePath);
	DDX_Control(pDX, IDC_EDT_SY_EDID_FILE_PATH, m_edtSyEdidFilePath);
}


BEGIN_MESSAGE_MAP(CSystem, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_SY_SAVE_EXIT, &CSystem::OnBnClickedBtnSySaveExit)
	ON_BN_CLICKED(IDC_BTN_SY_CANCEL, &CSystem::OnBnClickedBtnSyCancel)
	ON_BN_CLICKED(IDC_BTN_SY_MODEL_FILE_PATH, &CSystem::OnBnClickedBtnSyModelFilePath)
	ON_BN_CLICKED(IDC_BTN_SY_PATTERN_FILE_PATH, &CSystem::OnBnClickedBtnSyPatternFilePath)
	ON_BN_CLICKED(IDC_BTN_SY_EDID_FILE_PATH, &CSystem::OnBnClickedBtnSyEdidFilePath)
END_MESSAGE_MAP()


// CSystem 메시지 처리기


BOOL CSystem::OnInitDialog()
{
	CDialog::OnInitDialog();
	lpSystemInfo = m_pApp->GetSystemInfo();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// Dialog의 기본 FONT 설정.
	SendMessageToDescendants(WM_SETFONT, (WPARAM)m_pDefaultFont->GetSafeHandle(), 1, TRUE, FALSE);

	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();
	Lf_InitDlgDesign();

	Lf_InitDialogControl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSystem::OnDestroy()
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


BOOL CSystem::PreTranslateMessage(MSG* pMsg)
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


HBRUSH CSystem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
			if (pWnd->GetDlgCtrlID() == IDC_STT_SY_SYSTEM_TITLE)
			{
				pDC->SetBkColor(COLOR_DEEP_BLUE);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_DEEP_BLUE];
			}
			if ((pWnd->GetDlgCtrlID() == IDC_STT_SY_STATION_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_SY_MELSEC_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_SY_MES_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_SY_EAS_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_SY_PATH_TIT)
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


void CSystem::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}


void CSystem::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnTimer(nIDEvent);
}

void CSystem::OnBnClickedBtnSySaveExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_saveSystemInfo();

	CDialog::OnOK();
}


void CSystem::OnBnClickedBtnSyCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnCancel();
}


void CSystem::OnBnClickedBtnSyModelFilePath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sdata;

	UpdateData(TRUE);
	m_edtSyModelFilePath.GetWindowText(sdata);
	m_edtSyModelFilePath.SetWindowText(Lf_FileLoadDialog(sdata));
	UpdateData(FALSE);
}


void CSystem::OnBnClickedBtnSyPatternFilePath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sdata;

	UpdateData(TRUE);
	m_edtSyPatternFilePath.GetWindowText(sdata);
	m_edtSyPatternFilePath.SetWindowText(Lf_FileLoadDialog(sdata));
	UpdateData(FALSE);
}


void CSystem::OnBnClickedBtnSyEdidFilePath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sdata;

	UpdateData(TRUE);
	m_edtSyEdidFilePath.GetWindowText(sdata);
	m_edtSyEdidFilePath.SetWindowText(Lf_FileLoadDialog(sdata));
	UpdateData(FALSE);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CSystem::Lf_InitLocalValue()
{

}

void CSystem::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(32, 13, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_SY_SYSTEM_TITLE)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(23, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_BTN_SY_SAVE_EXIT)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_BTN_SY_CANCEL)->SetFont(&m_Font[2]);

	m_Font[3].CreateFont(19, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_SY_STATION_TIT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_SY_MELSEC_TIT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_SY_MES_TIT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_SY_EAS_TIT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_SY_PATH_TIT)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(17, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

}

void CSystem::Lf_InitColorBrush()
{
	// 각 Control의 COLOR 설정을 위한 Brush를 Setting 한다.
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush(COLOR_WHITE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_RED128].CreateSolidBrush(COLOR_RED128);
	m_Brush[COLOR_IDX_GREEN].CreateSolidBrush(COLOR_GREEN);
	m_Brush[COLOR_IDX_GREEN128].CreateSolidBrush(COLOR_GREEN128);
	m_Brush[COLOR_IDX_BLUE].CreateSolidBrush(COLOR_BLUE);
	m_Brush[COLOR_IDX_SEABLUE].CreateSolidBrush(COLOR_SEABLUE);
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_Brush[COLOR_IDX_VERDANT].CreateSolidBrush(COLOR_VERDANT);
	m_Brush[COLOR_IDX_JADEGREEN].CreateSolidBrush(COLOR_JADEGREEN);
	m_Brush[COLOR_IDX_JADEBLUE].CreateSolidBrush(COLOR_JADEBLUE);
	m_Brush[COLOR_IDX_JADERED].CreateSolidBrush(COLOR_JADERED);
	m_Brush[COLOR_IDX_LIGHT_RED].CreateSolidBrush(COLOR_LIGHT_RED);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush(COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_LIGHT_BLUE].CreateSolidBrush(COLOR_LIGHT_BLUE);
	m_Brush[COLOR_IDX_LIGHT_ORANGE].CreateSolidBrush(COLOR_LIGHT_ORANGE);
	m_Brush[COLOR_IDX_DARK_RED].CreateSolidBrush(COLOR_DARK_RED);
	m_Brush[COLOR_IDX_DARK_ORANGE].CreateSolidBrush(COLOR_DARK_ORANGE);
	m_Brush[COLOR_IDX_GRAY128].CreateSolidBrush(COLOR_GRAY128);
	m_Brush[COLOR_IDX_GRAY159].CreateSolidBrush(COLOR_GRAY159);
	m_Brush[COLOR_IDX_GRAY224].CreateSolidBrush(COLOR_GRAY224);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
}

void CSystem::Lf_InitDlgDesign()
{
	// Button ICON
 	m_btnSySaveExit.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
	m_btnSyCancel.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DISABLE));
}

void CSystem::Lf_InitDialogControl()
{
	CString sdata = _T("");

	for (int i = 0; i < 65; i++)	// 가장 먼저 Combo Box에 값을 넣어야 한다.
	{
		sdata.Format(_T("%02d"), i);
		m_cmbSyEcsEqpNumber.AddString(sdata);
	}

	m_edtSyEqpName.SetWindowText(lpSystemInfo->m_sEqpName);
	m_cmbSyLineType.SetCurSel(lpSystemInfo->m_nLineType);
	m_cmbSyCarrierType.SetCurSel(lpSystemInfo->m_nCarrierType);

	m_cmbSyEcsOnLineMode.SetCurSel(lpSystemInfo->m_nEcsOnLineMode);
	sdata.Format(_T("%04X"), lpSystemInfo->m_nLBStartAddr);
	m_edtSyLBStartAddr.SetWindowText(sdata);
	sdata.Format(_T("%04X"), lpSystemInfo->m_nLWStartAddr1);
	m_edtSyLWStartAddr1.SetWindowText(sdata);
	sdata.Format(_T("%04X"), lpSystemInfo->m_nLWStartAddr2);
	m_edtSyLWStartAddr2.SetWindowText(sdata);
	m_cmbSyEcsEqpNumber.SetCurSel(lpSystemInfo->m_nEcsEqpNumber);

	m_edtSyMesServicePort.SetWindowText(lpSystemInfo->m_sMesServicePort);
	m_edtSyMesNetwork.SetWindowText(lpSystemInfo->m_sMesNetWork);
	m_edtSyMesDaemonPort.SetWindowText(lpSystemInfo->m_sMesDaemonPort);
	m_edtSyMesLocalSubject.SetWindowText(lpSystemInfo->m_sMesLocalSubject);
	m_edtSyMesRemoteSubject.SetWindowText(lpSystemInfo->m_sMesRemoteSubject);
	m_ipaSyMesLocalIp.SetWindowText(lpSystemInfo->m_sMesLocalIP);
	m_cmbSyEasUse.SetCurSel(lpSystemInfo->m_nEasUse);
	m_edtSyEasServicePort.SetWindowText(lpSystemInfo->m_sEasServicePort);
	m_edtSyEasNetwork.SetWindowText(lpSystemInfo->m_sEasNetWork);
	m_edtSyEasDaemonPort.SetWindowText(lpSystemInfo->m_sEasDaemonPort);
	m_edtSyEasLocalSubject.SetWindowText(lpSystemInfo->m_sEasLocalSubject);
	m_edtSyEasRemoteSubject.SetWindowText(lpSystemInfo->m_sEasRemoteSubject);

#if (CODE_DFS_SETTING_USE==1)
	m_cmbSyDfsUse.SetCurSel(lpSystemInfo->m_nDfsUse);
	m_ipaSyDfsIPAddress.SetWindowText(lpSystemInfo->m_sDfsIPAddress);
	m_edtSyDfsUserId.SetWindowText(lpSystemInfo->m_sDfsUserId);
	m_edtSyDfsPassword.SetWindowText(lpSystemInfo->m_sDfsPassword);
#endif

	m_edtSyModelFilePath.SetWindowText(lpSystemInfo->m_sDataFileModel);
	m_edtSyPatternFilePath.SetWindowText(lpSystemInfo->m_sDataFilePattern);
	m_edtSyEdidFilePath.SetWindowText(lpSystemInfo->m_sDataFileEdid);


}

void CSystem::Lf_saveSystemInfo()
{
	CString sdata = _T("");

	m_pApp->Gf_writeMLog(_T("<WND> SYSTEM Setting Save"));

	m_edtSyEqpName.GetWindowText(sdata);
	lpSystemInfo->m_sEqpName.Format(_T("%s"), sdata);
	Write_SysIniFile(_T("SYSTEM"), _T("EQP_NAME"), lpSystemInfo->m_sEqpName);

	lpSystemInfo->m_nLineType = m_cmbSyLineType.GetCurSel();
	Write_SysIniFile(_T("SYSTEM"), _T("LINE_TYPE"), lpSystemInfo->m_nLineType);

	lpSystemInfo->m_nCarrierType = m_cmbSyCarrierType.GetCurSel();
	Write_SysIniFile(_T("SYSTEM"), _T("CARRIER_TYPE"), lpSystemInfo->m_nCarrierType);

	lpSystemInfo->m_nEcsOnLineMode = m_cmbSyEcsOnLineMode.GetCurSel();
	Write_SysIniFile(_T("SYSTEM"), _T("ECS_ONLINE_MODE"), lpSystemInfo->m_nEcsOnLineMode);

	m_edtSyLBStartAddr.GetWindowText(sdata);
	lpSystemInfo->m_nLBStartAddr = _tcstol(sdata, NULL, 16);
	Write_SysIniFile(_T("SYSTEM"), _T("MELSEC_LB_START_ADDR"), sdata);

	m_edtSyLWStartAddr1.GetWindowText(sdata);
	lpSystemInfo->m_nLWStartAddr1 = _tcstol(sdata, NULL, 16);
	Write_SysIniFile(_T("SYSTEM"), _T("MELSEC_LW_START_ADDR1"), sdata);

	m_edtSyLWStartAddr2.GetWindowText(sdata);
	lpSystemInfo->m_nLWStartAddr2 = _tcstol(sdata, NULL, 16);
	Write_SysIniFile(_T("SYSTEM"), _T("MELSEC_LW_START_ADDR2"), sdata);

	lpSystemInfo->m_nEcsEqpNumber = m_cmbSyEcsEqpNumber.GetCurSel();
	Write_SysIniFile(_T("SYSTEM"), _T("ECS_EQP_NUMBER"), lpSystemInfo->m_nEcsEqpNumber);

	m_edtSyMesServicePort.GetWindowText(lpSystemInfo->m_sMesServicePort);
	Write_SysIniFile(_T("MES"), _T("MES_SERVICE"), lpSystemInfo->m_sMesServicePort);

	m_edtSyMesNetwork.GetWindowText(lpSystemInfo->m_sMesNetWork);
	Write_SysIniFile(_T("MES"), _T("MES_NETWORK"), lpSystemInfo->m_sMesNetWork);

	m_edtSyMesDaemonPort.GetWindowText(lpSystemInfo->m_sMesDaemonPort);
	Write_SysIniFile(_T("MES"), _T("MES_DAEMON_PORT"), lpSystemInfo->m_sMesDaemonPort);

	m_edtSyMesLocalSubject.GetWindowText(lpSystemInfo->m_sMesLocalSubject);
	Write_SysIniFile(_T("MES"), _T("MES_LOCAL_SUBJECT"), lpSystemInfo->m_sMesLocalSubject);

	m_edtSyMesRemoteSubject.GetWindowText(lpSystemInfo->m_sMesRemoteSubject);
	Write_SysIniFile(_T("MES"), _T("MES_REMOTE_SUBJECT"), lpSystemInfo->m_sMesRemoteSubject);

	m_ipaSyMesLocalIp.GetWindowText(lpSystemInfo->m_sMesLocalIP);
	Write_SysIniFile(_T("MES"), _T("MES_LOCAL_IP"), lpSystemInfo->m_sMesLocalIP);

	lpSystemInfo->m_nEasUse = m_cmbSyEasUse.GetCurSel();
	Write_SysIniFile(_T("EAS"), _T("EAS_USE"), lpSystemInfo->m_nEasUse);

	m_edtSyEasServicePort.GetWindowText(lpSystemInfo->m_sEasServicePort);
	Write_SysIniFile(_T("EAS"), _T("EAS_SERVICE"), lpSystemInfo->m_sEasServicePort);

	m_edtSyEasNetwork.GetWindowText(lpSystemInfo->m_sEasNetWork);
	Write_SysIniFile(_T("EAS"), _T("EAS_NETWORK"), lpSystemInfo->m_sEasNetWork);

	m_edtSyEasDaemonPort.GetWindowText(lpSystemInfo->m_sEasDaemonPort);
	Write_SysIniFile(_T("EAS"), _T("EAS_DAEMON_PORT"), lpSystemInfo->m_sEasDaemonPort);

	m_edtSyEasLocalSubject.GetWindowText(lpSystemInfo->m_sEasLocalSubject);
	Write_SysIniFile(_T("EAS"), _T("EAS_LOCAL_SUBJECT"), lpSystemInfo->m_sEasLocalSubject);

	m_edtSyEasRemoteSubject.GetWindowText(lpSystemInfo->m_sEasRemoteSubject);
	Write_SysIniFile(_T("EAS"), _T("EAS_REMOTE_SUBJECT"), lpSystemInfo->m_sEasRemoteSubject);

#if (CODE_DFS_SETTING_USE==1)
	lpSystemInfo->m_nDfsUse = m_cmbSyDfsUse.GetCurSel();
	Write_SysIniFile(_T("DFS"), _T("DFS_USE"), lpSystemInfo->m_nDfsUse);

	m_ipaSyDfsIPAddress.GetWindowText(lpSystemInfo->m_sDfsIPAddress);
	Write_SysIniFile(_T("DFS"), _T("DFS_IP_ADDRESS"), lpSystemInfo->m_sDfsIPAddress);

	m_edtSyDfsUserId.GetWindowText(lpSystemInfo->m_sDfsUserId);
	Write_SysIniFile(_T("DFS"), _T("DFS_USER_ID"), lpSystemInfo->m_sDfsUserId);

	m_edtSyDfsPassword.GetWindowText(lpSystemInfo->m_sDfsPassword);
	Write_SysIniFile(_T("DFS"), _T("DFS_PASSWORD"), lpSystemInfo->m_sDfsPassword);
#endif

	m_edtSyModelFilePath.GetWindowText(lpSystemInfo->m_sDataFileModel);
	Write_SysIniFile(_T("SYSTEM"), _T("MODEL_FILE_PATH"), lpSystemInfo->m_sDataFileModel);

	m_edtSyPatternFilePath.GetWindowText(lpSystemInfo->m_sDataFilePattern);
	Write_SysIniFile(_T("SYSTEM"), _T("PATTERN_FILE_PATH"), lpSystemInfo->m_sDataFilePattern);

	m_edtSyEdidFilePath.GetWindowText(lpSystemInfo->m_sDataFileEdid);
	Write_SysIniFile(_T("SYSTEM"), _T("EDID_PATH"), lpSystemInfo->m_sDataFileEdid);
}

CString CSystem::Lf_FileLoadDialog(CString Temp)
{
	LPITEMIDLIST pidlBrowse;

	BOOL bRtn = FALSE;

	wchar_t wszPathName[256] = { 0, };
	wsprintf(wszPathName, _T("%s"), Temp.GetBuffer(0));

	BROWSEINFO BrInfo;
	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = NULL;
	memset(&BrInfo, 0, sizeof(BrInfo));
	BrInfo.pszDisplayName = NULL;

	BrInfo.lpszTitle = _T("Select Folder");
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;

	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	BrInfo.lpfn = BrowseForFolder_CallbackProc;
	BrInfo.lParam = (LPARAM)wszPathName;


	if (pidlBrowse = SHBrowseForFolder(&BrInfo))
	{
		if (SUCCEEDED(SHGetPathFromIDList(pidlBrowse, wszPathName)))
			bRtn = TRUE;

		LPMALLOC pMalloc;
		if (SUCCEEDED(SHGetMalloc(&pMalloc)))
		{
			pMalloc->Free(pidlBrowse);
			pMalloc->Release();
		}
	}

	if (pidlBrowse != NULL)
	{
		return  wszPathName;
	}
	else
	{
		return Temp;
	}
}