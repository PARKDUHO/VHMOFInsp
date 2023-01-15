// CModelInfo.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CModelInfo.h"
#include "afxdialogex.h"


// CModelInfo 대화 상자

IMPLEMENT_DYNAMIC(CModelInfo, CDialogEx)

CModelInfo::CModelInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_INFO, pParent)
{
	m_nTabSelect = 0;
}

CModelInfo::~CModelInfo()
{
}

void CModelInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MI_MODEL_INFO, m_tabModelInfo);
	DDX_Control(pDX, IDC_BTN_MI_FUSING, m_btnMiFusing);
	DDX_Control(pDX, IDC_BTN_MI_SAVE_EXIT, m_btnMiSaveExit);
	DDX_Control(pDX, IDC_BTN_MI_CANCEL, m_btnMiCancel);
	DDX_Control(pDX, IDC_EDT_MI_SAVE_MODEL, m_edtMiSaveModelName);
}


BEGIN_MESSAGE_MAP(CModelInfo, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_MI_SAVE_EXIT, &CModelInfo::OnBnClickedBtnMiSaveExit)
	ON_BN_CLICKED(IDC_BTN_MI_CANCEL, &CModelInfo::OnBnClickedBtnMiCancel)
	ON_BN_CLICKED(IDC_BTN_MI_FUSING, &CModelInfo::OnBnClickedBtnMiFusing)
END_MESSAGE_MAP()


// CModelInfo 메시지 처리기


BOOL CModelInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	lpModelInfo = m_pApp->GetModelInfo();
	lpSystemInfo = m_pApp->GetSystemInfo();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pApp->Gf_writeMLog(_T("<MODEL> 'Model Information' Dialog Open."));

	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();
	Lf_InitDlgDesign();

	Lf_InitTabControl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CModelInfo::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	delete m_pModelInfoData;
	delete m_pModelInfoFusing;

	for (int i = 0; i < COLOR_IDX_MAX; i++)
	{
		m_Brush[i].DeleteObject();
	}

	for (int i = 0; i < FONT_IDX_MAX; i++)
	{
		m_Font[i].DeleteObject();
	}
}


BOOL CModelInfo::PreTranslateMessage(MSG* pMsg)
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
			case VK_F12:
			{
				Lf_HostModelFileSave();
				return TRUE;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CModelInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		case CTLCOLOR_STATIC:		// Static, CheckBox control
			if ((pWnd->GetDlgCtrlID() == IDC_STT_MI_MODEL_NAME)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_MI_SAVE_MODEL)
				)
			{
				pDC->SetBkColor(COLOR_DEEP_BLUE);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_DEEP_BLUE];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_MI_FUSING_PG1)
			{
				if (m_bFusingResult[CH1] == FUSING_OK)
				{
					pDC->SetBkColor(COLOR_GREEN);
					pDC->SetTextColor(COLOR_BLACK);
					return m_Brush[COLOR_IDX_GREEN];
				}
				else if (m_bFusingResult[CH1] == FUSING_NG)
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_BLACK);
					return m_Brush[COLOR_IDX_RED];
				}
				else
				{
					pDC->SetBkColor(COLOR_GRAY192);
					pDC->SetTextColor(COLOR_BLACK);
					return m_Brush[COLOR_IDX_GRAY192];
				}
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_MI_FUSING_PG2)
			{
				if (m_bFusingResult[CH2] == FUSING_OK)
				{
					pDC->SetBkColor(COLOR_GREEN);
					pDC->SetTextColor(COLOR_BLACK);
					return m_Brush[COLOR_IDX_GREEN];
				}
				else if (m_bFusingResult[CH2] == FUSING_NG)
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_BLACK);
					return m_Brush[COLOR_IDX_RED];
				}
				else
				{
					pDC->SetBkColor(COLOR_GRAY192);
					pDC->SetTextColor(COLOR_BLACK);
					return m_Brush[COLOR_IDX_GRAY192];
				}
			}

			break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CModelInfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}

void CModelInfo::OnBnClickedBtnMiFusing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pApp->Gf_writeMLog(_T("<WND> BUTTON Click => Fusing"));

	Lf_systemFusing();
}


void CModelInfo::OnBnClickedBtnMiSaveExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pApp->Gf_writeMLog(_T("<WND> BUTTON Click => Model Data 'Save&&Exit'"));

	Lf_saveModel();
	//CDialog::OnOK();
}


void CModelInfo::OnBnClickedBtnMiCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pApp->Gf_writeMLog(_T("<WND> BUTTON Click => Model Data 'Cancel'"));

	if (m_bSaved == TRUE)
		CDialog::OnOK();
	else
		CDialog::OnCancel();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CModelInfo::Lf_InitLocalValue()
{
	GetDlgItem(IDC_STT_MI_MODEL_NAME_VALUE)->SetWindowText(lpSystemInfo->m_sLastModelName);
	GetDlgItem(IDC_EDT_MI_SAVE_MODEL)->SetWindowText(lpSystemInfo->m_sLastModelName);

	m_bSaved = FALSE;
}

void CModelInfo::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(32, 13, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_MI_MODEL_NAME)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_MI_MODEL_NAME_VALUE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_MI_SAVE_MODEL)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_EDT_MI_SAVE_MODEL)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(23, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_TAB_MI_MODEL_INFO)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_BTN_MI_FUSING)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_BTN_MI_SAVE_EXIT)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_BTN_MI_CANCEL)->SetFont(&m_Font[2]);

	m_Font[3].CreateFont(21, 9, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[4].CreateFont(17, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[5].CreateFont(16, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_MI_FUSING_PG1)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_STT_MI_FUSING_PG2)->SetFont(&m_Font[5]);
}

void CModelInfo::Lf_InitColorBrush()
{
	// 각 Control의 COLOR 설정을 위한 Brush를 Setting 한다.
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush(COLOR_WHITE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_GREEN].CreateSolidBrush(COLOR_GREEN);
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
	m_Brush[COLOR_IDX_GRAY192].CreateSolidBrush(COLOR_GRAY192);
	m_Brush[COLOR_IDX_GRAY224].CreateSolidBrush(COLOR_GRAY224);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
}

void CModelInfo::Lf_InitDlgDesign()
{
	// Button ICON
	m_btnMiFusing.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
	m_btnMiSaveExit.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
	m_btnMiCancel.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DISABLE));
}

void CModelInfo::Lf_InitTabControl()
{
	m_pModelInfoFusing = new CModelInfoFusing;
	m_pModelInfoFusing->Create(CModelInfoFusing::IDD, &m_tabModelInfo);
	m_tabModelInfo.AddTab(m_pModelInfoFusing, _T("  FUSING  "), 0);

	m_pModelInfoData = new CModelInfoData;
	m_pModelInfoData->Create(CModelInfoData::IDD, &m_tabModelInfo);
	m_tabModelInfo.AddTab(m_pModelInfoData, _T("  MODEL DATA  "), 0);

	//** customizing the tab control --------
	m_tabModelInfo.SetDisabledColor(RGB(0, 0, 0));
	m_tabModelInfo.SetSelectedColor(RGB(0, 0, 255));

	m_tabModelInfo.SelectTab(m_nTabSelect);
}

void CModelInfo::Lf_saveModel()
{
	CString strSource, strTarget;
	CString strSaveModelName;

	// Button을 Disable 시킨다.
	m_btnMiFusing.EnableWindow(FALSE);
	m_btnMiSaveExit.EnableWindow(FALSE);
	m_btnMiCancel.EnableWindow(FALSE);

	// Model File을 다른 이름으로 복사한다.
	strSource.Format(_T(".\\Model\\%s.MOD"), lpSystemInfo->m_sLastModelName);

	m_edtMiSaveModelName.GetWindowText(strSaveModelName);
	strTarget.Format(_T(".\\Model\\%s.MOD"), strSaveModelName);
	CopyFile(strSource, strTarget, FALSE);


	// Last Model Name을 변경한다.
	lpSystemInfo->m_sLastModelName.Format(_T("%s"), strSaveModelName);
	Write_SysIniFile(_T("SYSTEM"), _T("LAST_MODELNAME"), strSaveModelName);

	// Model/Fusing Data를 저장.
	m_pModelInfoFusing->Gf_DataSaveModelFusing(strSaveModelName);
	m_pModelInfoData->Gf_DataSaveModelData(strSaveModelName);

	// 변경된 값을 다시 Read하여 Update한다.
	m_pApp->Gf_LoadModelFile();

	// Model Data 수정 후 Log에 수정 된 Model Data 남김 
	m_pApp->Gf_writeMLog(_T("<MODEL> BUTTON_EVENT => Model Data Save"));

	// Button을 Enable 시킨다.
	m_btnMiFusing.EnableWindow(TRUE);
	m_btnMiSaveExit.EnableWindow(TRUE);
	m_btnMiCancel.EnableWindow(TRUE);

	m_edtMiSaveModelName.SetFocus();
}

void CModelInfo::Lf_HostModelFileSave()
{
	// 	WIN32_FIND_DATA wfd;		
	// 	HANDLE hSearch;
	m_pApp->Gf_writeMLog(_T("<MODEL> Host Model File Update[F12]"));

	CString strTarget;
	if (AfxMessageBox(_T("Do you want to rewrite Model file?"), MB_YESNO | MB_ICONQUESTION) != IDYES)
	{
		return;
	}

	// 변경된 모델정보를 Save 한다.
	Lf_saveModel();
	m_bSaved = TRUE;

	strTarget.Format(_T("%s\\%s.MOD"), lpSystemInfo->m_sDataFileModel, lpSystemInfo->m_sLastModelName);

	// Aging 정보 제외 한 Model 정보만 Host File에 Update 한다. 2019-10-01
	m_pModelInfoFusing->Gf_DataSaveModelFusing(strTarget);						// Fusing Data
	m_pModelInfoData->Gf_DataSaveModelData(strTarget);							// Model Data

	AfxMessageBox(_T("Host Model File Copy Complete!"), MB_OK | MB_ICONINFORMATION);
}

void CModelInfo::Lf_systemFusing()
{
	Lf_saveModel();

	GetDlgItem(IDC_BTN_MI_FUSING)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_MI_SAVE_EXIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_MI_CANCEL)->EnableWindow(FALSE);

	m_bFusingResult[0] = FUSING_READY;
	m_bFusingResult[1] = FUSING_READY;

	GetDlgItem(IDC_STT_MI_FUSING_PG1)->SetWindowText(_T("--"));
	GetDlgItem(IDC_STT_MI_FUSING_PG1)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_MI_FUSING_PG2)->SetWindowText(_T("--"));
	GetDlgItem(IDC_STT_MI_FUSING_PG2)->Invalidate(FALSE);

	for (int ch = CH1; ch < MAX_CH; ch++)
	{
		int idx;
		if (ch == CH1)	idx = CONN_PG1;
		if (ch == CH2)	idx = CONN_PG2;
		if (m_pApp->bConnectInfo[idx] == FALSE)
		{
			if (ch == CH1)	GetDlgItem(IDC_STT_MI_FUSING_PG1)->SetWindowText(_T("SKIP"));
			if (ch == CH2)	GetDlgItem(IDC_STT_MI_FUSING_PG2)->SetWindowText(_T("SKIP"));
			continue;
		}
		else
		{
			if (m_pApp->commApi->main_setSystemFusing(ch) == TRUE)
			{
				m_bFusingResult[ch] = FUSING_OK;

				if (ch == CH1)	GetDlgItem(IDC_STT_MI_FUSING_PG1)->SetWindowText(_T("OK"));
				if (ch == CH2)	GetDlgItem(IDC_STT_MI_FUSING_PG2)->SetWindowText(_T("OK"));
			}
			else
			{
				m_bFusingResult[ch] = FUSING_NG;

				if (ch == CH1)	GetDlgItem(IDC_STT_MI_FUSING_PG1)->SetWindowText(_T("NG"));
				if (ch == CH2)	GetDlgItem(IDC_STT_MI_FUSING_PG2)->SetWindowText(_T("NG"));
			}
		}
	}
	GetDlgItem(IDC_STT_MI_FUSING_PG1)->Invalidate(FALSE);
	GetDlgItem(IDC_STT_MI_FUSING_PG2)->Invalidate(FALSE);

	GetDlgItem(IDC_BTN_MI_FUSING)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_MI_SAVE_EXIT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_MI_CANCEL)->EnableWindow(TRUE);
}