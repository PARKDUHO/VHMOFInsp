
// VHMOFInspDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "VHMOFInsp.h"
#include "VHMOFInspDlg.h"
#include "afxdialogex.h"
#include "CMessageError.h"
#include "CUserID.h"
#include "CModelChange.h"
#include "CModelInfo.h"
#include "CTestReady.h"
#include "CInitialize.h"
#include "CSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVHMOFInspDlg 대화 상자



CVHMOFInspDlg::CVHMOFInspDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VHMOFINSP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVHMOFInspDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_MA_USERID, m_btnMainUserID);
	DDX_Control(pDX, IDC_BTN_MA_MODEL_CHANGE, m_btnMainModelChange);
	DDX_Control(pDX, IDC_BTN_MA_MODEL_INFO, m_btnMainModelInfo);
	DDX_Control(pDX, IDC_BTN_MA_TEST, m_btnMainTest);
	DDX_Control(pDX, IDC_BTN_MA_MAINT, m_btnMainMaint);
	DDX_Control(pDX, IDC_BTN_MA_SYSTEM, m_btnMainSystem);
	DDX_Control(pDX, IDC_BTN_MA_INITIAL, m_btnMainInitial);
	DDX_Control(pDX, IDC_BTN_MA_FIRMWARE, m_btnMainFirmware);
	DDX_Control(pDX, IDC_BTN_MA_EXIT, m_btnMainExit);
	DDX_Control(pDX, IDC_STT_MAIN_MLOG_VIEW, m_sttMainMlogView);
}

BEGIN_MESSAGE_MAP(CVHMOFInspDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_MESSAGE(WM_UPDATE_SYSTEM_INFO, OnUpdateSystemInfo)
	ON_BN_CLICKED(IDC_BTN_MA_USERID, &CVHMOFInspDlg::OnBnClickedBtnMaUserid)
	ON_BN_CLICKED(IDC_BTN_MA_MODEL_CHANGE, &CVHMOFInspDlg::OnBnClickedBtnMaModelChange)
	ON_BN_CLICKED(IDC_BTN_MA_MODEL_INFO, &CVHMOFInspDlg::OnBnClickedBtnMaModelInfo)
	ON_BN_CLICKED(IDC_BTN_MA_TEST, &CVHMOFInspDlg::OnBnClickedBtnMaTest)
	ON_BN_CLICKED(IDC_BTN_MA_MAINT, &CVHMOFInspDlg::OnBnClickedBtnMaMaint)
	ON_BN_CLICKED(IDC_BTN_MA_SYSTEM, &CVHMOFInspDlg::OnBnClickedBtnMaSystem)
	ON_BN_CLICKED(IDC_BTN_MA_INITIAL, &CVHMOFInspDlg::OnBnClickedBtnMaInitial)
	ON_BN_CLICKED(IDC_BTN_MA_FIRMWARE, &CVHMOFInspDlg::OnBnClickedBtnMaFirmware)
	ON_BN_CLICKED(IDC_BTN_MA_EXIT, &CVHMOFInspDlg::OnBnClickedBtnMaExit)
END_MESSAGE_MAP()


// CVHMOFInspDlg 메시지 처리기

BOOL CVHMOFInspDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	lpSystemInfo = m_pApp->GetSystemInfo();
	lpModelInfo = m_pApp->GetModelInfo();
	lpInspWorkInfo = m_pApp->GetInspWorkInfo();

	Lf_InitProgramTitle();
	Lf_InitItemValue();
	Lf_InitFontSet();
	Lf_InitColorBrush();



	ShowWindow(SW_MAXIMIZE);

	CRect rect;
	GetClientRect(rect);
	rect.top = rect.bottom - 50;
	m_sttMainMlogView.MoveWindow(rect);

	SetTimer(1, 500, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CVHMOFInspDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CVHMOFInspDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트
		CRect rect;
		GetClientRect(&rect);
		rect.bottom = 90;
		dc.FillSolidRect(rect, RGB(0,0,0));
		GetClientRect(&rect);
		rect.top = 91;
		dc.FillSolidRect(rect, RGB(64,64,64));

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CVHMOFInspDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CVHMOFInspDlg::PreTranslateMessage(MSG* pMsg)
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
			case VK_ESCAPE:		return 1;
			case VK_RETURN:		return 1;
			case VK_SPACE:
			{
				OnBnClickedBtnMaTest();
				return 1;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CVHMOFInspDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
			if ((pWnd->GetDlgCtrlID() == IDC_STT_STATION_INFO_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_MODEL_INFO_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_FW_VERSION_TIT)
				)
			{
				pDC->SetBkColor(COLOR_DEEP_BLUE);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_DEEP_BLUE];
			}
			if ((pWnd->GetDlgCtrlID() == IDC_STT_EQP_NAME_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_OP_MODE_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_USER_ID_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_USER_NAME_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_MODEL_NAME_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_RESOLUTION_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_SIGNALBIT_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_VCC_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_VDD_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_MAIN_APP_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_MAIN_FPGA_VALUE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_DP_FPGA_VALUE)
				)
			{
				pDC->SetBkColor(COLOR_WHITE);
				pDC->SetTextColor(COLOR_BLACK);
				return m_Brush[COLOR_IDX_WHITE];
			}
			if ((pWnd->GetDlgCtrlID() == IDC_STT_EQP_NAME_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_OP_MODE_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_USER_ID_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_USER_NAME_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_MODEL_NAME_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_RESOLUTION_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_SIGNALBIT_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_VOLT_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_MAIN_APP_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_MAIN_FPGA_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_DP_FPGA_TIT)
				)
			{
				pDC->SetBkColor(COLOR_LIGHT_YELLOW);
				pDC->SetTextColor(COLOR_BLACK);
				return m_Brush[COLOR_IDX_LIGHT_YELLOW];
			}
			if ((pWnd->GetDlgCtrlID() == IDC_STT_VCC_TIT)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_VDD_TIT)
				)
			{
				pDC->SetBkColor(COLOR_LIGHT_BLUE);
				pDC->SetTextColor(COLOR_BLACK);
				return m_Brush[COLOR_IDX_LIGHT_BLUE];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_MAIN_MLOG_VIEW)
			{
				pDC->SetBkColor(COLOR_BLACK);
				pDC->SetTextColor(COLOR_CYAN);
				return m_Brush[COLOR_IDX_BLACK];
			}
			break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CVHMOFInspDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1)
	{
		KillTimer(1);

		CUserID userdlg;
		if (userdlg.DoModal() == IDOK)
		{
			CInitialize initdlg;
			initdlg.DoModal();
		}
		else
		{
			CDialog::OnOK();
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}
LRESULT CVHMOFInspDlg::OnUpdateSystemInfo(WPARAM wParam, LPARAM lParam)
{
	Lf_updateSystemInfo();

	return (0);
}

void CVHMOFInspDlg::OnBnClickedBtnMaUserid()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CUserID userid_dlg;
	userid_dlg.DoModal();

	Lf_updateSystemInfo();
}


void CVHMOFInspDlg::OnBnClickedBtnMaModelChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CModelChange mc_dlg;
	mc_dlg.DoModal();

	Lf_updateSystemInfo();
}


void CVHMOFInspDlg::OnBnClickedBtnMaModelInfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CModelInfo model_dlg;
	model_dlg.DoModal();

	Lf_updateSystemInfo();
}


void CVHMOFInspDlg::OnBnClickedBtnMaTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTestReady ready_dlg;
	ready_dlg.DoModal();
}


void CVHMOFInspDlg::OnBnClickedBtnMaMaint()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CVHMOFInspDlg::OnBnClickedBtnMaSystem()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CSystem system_dlg;
	system_dlg.DoModal();

	Lf_updateSystemInfo();
}


void CVHMOFInspDlg::OnBnClickedBtnMaInitial()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CInitialize init_dlg;
	init_dlg.DoModal();
}


void CVHMOFInspDlg::OnBnClickedBtnMaFirmware()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CVHMOFInspDlg::OnBnClickedBtnMaExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void CVHMOFInspDlg::Lf_InitProgramTitle()
{
	// Main Form Title Set
	CString strPGMTitle;
	char D_String[15] = { 0, };
	char Date_String[15] = { 0, };
	char* Date[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	sprintf_s(D_String, "%s", __DATE__);
	for (int i = 12; i; i--)
	{
		for (int j = 3; j; j--)
		{
			if (D_String[j - 1] != *(Date[i - 1] + (j - 1)))
				break;
			if (j == 1)
			{
				if (D_String[4] == 0x20)	D_String[4] = 0x30;
				sprintf_s(Date_String, "%c%c%c%c/%02d/%c%c", D_String[7], D_String[8], D_String[9], D_String[10], i, D_String[4], D_String[5]);
				i = 1; j = 1;
				break;
			}
		}
	}
	CString m_sSoftwareVersion;
	m_sSoftwareVersion.Format(_T("%s - %s"), char_To_wchar(Date_String), PGM_VERSION);
	strPGMTitle.Format(_T("VH NK BA ( %s )"), m_sSoftwareVersion);

	//m_pApp->Gf_writeLogData(_T("Program Version"), m_sSoftwareVersion);

	// Window Title Update
	SetWindowText(strPGMTitle);
	//m_sttMainMlogView.SetWindowText(strPGMTitle);
}

void CVHMOFInspDlg::Lf_InitItemValue()
{
	m_btnMainUserID.LoadBitmaps(IDB_BMP_USER, IDB_BMP_USER, IDB_BMP_USER, IDB_BMP_USER);
	m_btnMainUserID.SizeToContent();
	m_btnMainModelChange.LoadBitmaps(IDB_BMP_MODEL_CHANGE, IDB_BMP_MODEL_CHANGE, IDB_BMP_MODEL_CHANGE, IDB_BMP_MODEL_CHANGE);
	m_btnMainModelChange.SizeToContent();
	m_btnMainModelInfo.LoadBitmaps(IDB_BMP_MODEL_INFO, IDB_BMP_MODEL_INFO, IDB_BMP_MODEL_INFO, IDB_BMP_MODEL_INFO);
	m_btnMainModelInfo.SizeToContent();
	m_btnMainTest.LoadBitmaps(IDB_BMP_TEST, IDB_BMP_TEST, IDB_BMP_TEST, IDB_BMP_TEST);
	m_btnMainTest.SizeToContent();
	m_btnMainMaint.LoadBitmaps(IDB_BMP_MAINT, IDB_BMP_MAINT, IDB_BMP_MAINT, IDB_BMP_MAINT);
	m_btnMainMaint.SizeToContent();
	m_btnMainSystem.LoadBitmaps(IDB_BMP_SYSTEM, IDB_BMP_SYSTEM, IDB_BMP_SYSTEM, IDB_BMP_SYSTEM);
	m_btnMainSystem.SizeToContent();
	m_btnMainInitial.LoadBitmaps(IDB_BMP_INITIAL, IDB_BMP_INITIAL, IDB_BMP_INITIAL, IDB_BMP_INITIAL);
	m_btnMainInitial.SizeToContent();
	m_btnMainFirmware.LoadBitmaps(IDB_BMP_FIRMWARE, IDB_BMP_FIRMWARE, IDB_BMP_FIRMWARE, IDB_BMP_FIRMWARE);
	m_btnMainFirmware.SizeToContent();
//	m_btnMainBmp.LoadBitmaps(IDB_BITMAP_BMP, IDB_BITMAP_BMP_P, IDB_BITMAP_BMP, IDB_BITMAP_BMP);
//	m_btnMainBmp.SizeToContent();
	m_btnMainExit.LoadBitmaps(IDB_BMP_EXIT, IDB_BMP_EXIT, IDB_BMP_EXIT, IDB_BMP_EXIT);
	m_btnMainExit.SizeToContent();
// 
 	m_pApp->m_pStaticMainLog = (CStatic*)GetDlgItem(IDC_STT_MAIN_MLOG_VIEW);
}

void CVHMOFInspDlg::Lf_InitFontSet()
{
	/*************************************************************************************************/
	// Font Set
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[2].CreateFont(22, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_MAIN_MLOG_VIEW)->SetFont(&m_Font[2]);

	m_Font[3].CreateFont(32, 13, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_STATION_INFO_TIT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_MODEL_INFO_TIT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_FW_VERSION_TIT)->SetFont(&m_Font[3]);

	//mFontH1[3].CreateFont(21, 9, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _DIALOG_FONT_);
	m_Font[4].CreateFont(21, 7, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_EQP_NAME_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_EQP_NAME_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_OP_MODE_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_OP_MODE_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_USER_ID_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_USER_ID_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_USER_NAME_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_USER_NAME_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MODEL_NAME_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MODEL_NAME_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_RESOLUTION_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_RESOLUTION_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_SIGNALBIT_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_SIGNALBIT_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_VOLT_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_VCC_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_VDD_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_VCC_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_VDD_VALUE)->SetFont(&m_Font[4]);

	GetDlgItem(IDC_STT_MAIN_APP_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MAIN_FPGA_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_DP_FPGA_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MAIN_APP_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MAIN_FPGA_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_DP_FPGA_VALUE)->SetFont(&m_Font[4]);

}

void CVHMOFInspDlg::Lf_InitColorBrush()
{
	/*************************************************************************************************/
	// Brush Set
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush(COLOR_GRAY64);
	m_Brush[COLOR_IDX_GRAY94].CreateSolidBrush(COLOR_GRAY94);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush(COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_GRAY192].CreateSolidBrush(COLOR_GRAY192);
	m_Brush[COLOR_IDX_GRAY224].CreateSolidBrush(COLOR_GRAY224);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush(COLOR_WHITE);
	m_Brush[COLOR_IDX_CYAN].CreateSolidBrush(COLOR_CYAN);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
	m_Brush[COLOR_IDX_LIGHT_BLUE].CreateSolidBrush(COLOR_LIGHT_BLUE);
}

void CVHMOFInspDlg::Lf_updateSystemInfo()
{
	CString sdata = _T("");

	GetDlgItem(IDC_STT_EQP_NAME_VALUE)->SetWindowText(lpSystemInfo->m_sEqpName);

	if ((m_pApp->m_bUserIdGieng == TRUE) || (m_pApp->m_bUserIdPM == TRUE))
		GetDlgItem(IDC_STT_OP_MODE_VALUE)->SetWindowText(_T("OFF-LINE"));
	else
		GetDlgItem(IDC_STT_OP_MODE_VALUE)->SetWindowText(_T("IN-LINE"));

	GetDlgItem(IDC_STT_USER_ID_VALUE)->SetWindowText(m_pApp->m_sLoginUserID);
	GetDlgItem(IDC_STT_USER_NAME_VALUE)->SetWindowText(m_pApp->m_sLoginUserName);

	GetDlgItem(IDC_STT_MODEL_NAME_VALUE)->SetWindowText(lpSystemInfo->m_sLastModelName);

	sdata.Format(_T("%d x %d"), lpModelInfo->m_nTimingHorActive, lpModelInfo->m_nTimingVerActive);
	GetDlgItem(IDC_STT_RESOLUTION_VALUE)->SetWindowText(sdata);

	if (lpModelInfo->m_nSignalBit == SIG_6BIT)
		GetDlgItem(IDC_STT_SIGNALBIT_VALUE)->SetWindowText(_T("6 Bit"));
	else if (lpModelInfo->m_nSignalBit == SIG_8BIT)
		GetDlgItem(IDC_STT_SIGNALBIT_VALUE)->SetWindowText(_T("8 Bit"));
	else if (lpModelInfo->m_nSignalBit == SIG_10BIT)
		GetDlgItem(IDC_STT_SIGNALBIT_VALUE)->SetWindowText(_T("10 Bit"));
	else if (lpModelInfo->m_nSignalBit == SIG_12BIT)
		GetDlgItem(IDC_STT_SIGNALBIT_VALUE)->SetWindowText(_T("12 Bit"));

	sdata.Format(_T("%.2f"), lpModelInfo->m_fPowerVcc);
	GetDlgItem(IDC_STT_VCC_VALUE)->SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fPowerVel);
	GetDlgItem(IDC_STT_VDD_VALUE)->SetWindowText(sdata);

	GetDlgItem(IDC_STT_MAIN_APP_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_STT_MAIN_FPGA_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_STT_DP_FPGA_VALUE)->SetWindowText(_T(""));

#if (CODE_MAIN_UI_FW_VER_UPDATE==1)
	// Firmware Version
	int npos = 0;
	npos = lpInspWorkInfo->m_szFirmwareVer.ReverseFind(' ');
	sdata = lpWorkInfo->m_sFirmwareVersion.Left(npos);
	GetDlgItem(IDC_STT_MAIN_APP_VALUE)->SetWindowText(sdata);

	// LVDS FPGA Version
	npos = lpWorkInfo->m_sFpgaVersion.Find(_T(" "));
	sdata = lpWorkInfo->m_sFpgaVersion.Left(npos);
	GetDlgItem(IDC_STT_MAIN_FPGA_VALUE)->SetWindowText(sdata);
	GetDlgItem(IDC_STT_DP_FPGA_VALUE)->SetWindowText(sdata);

	// DP FPGA Version
	npos = lpWorkInfo->m_sFpgaVersion.Find(_T(" "));
	sdata = lpWorkInfo->m_sFpgaVersion.Left(npos);
	GetDlgItem(IDC_STT_DP_FPGA_VALUE)->SetWindowText(sdata);
#endif
}

