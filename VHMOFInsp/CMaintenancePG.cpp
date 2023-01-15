// CMaintenancePG.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CMaintenancePG.h"
#include "afxdialogex.h"


// CMaintenancePG 대화 상자

IMPLEMENT_DYNAMIC(CMaintenancePG, CDialog)

CMaintenancePG::CMaintenancePG(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MAINTENANCE_PG, pParent)
{
	m_pDefaultFont = new CFont();
	m_pDefaultFont->CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
}

CMaintenancePG::~CMaintenancePG()
{
	if (m_pDefaultFont != NULL)
	{
		delete m_pDefaultFont;
	}
}

void CMaintenancePG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_MP_PATTERN_LIST, m_cmbMpPatternList);
}


BEGIN_MESSAGE_MAP(CMaintenancePG, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMaintenancePG 메시지 처리기


BOOL CMaintenancePG::OnInitDialog()
{
	CDialog::OnInitDialog();
	lpSystemInfo = m_pApp->GetSystemInfo();
	lpModelInfo = m_pApp->GetModelInfo();
	lpInspWorkInfo = m_pApp->GetInspWorkInfo();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// Dialog의 기본 FONT 설정.
	SendMessageToDescendants(WM_SETFONT, (WPARAM)m_pDefaultFont->GetSafeHandle(), 1, TRUE, FALSE);

	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();

	Lf_loadPatternListToCombo();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMaintenancePG::OnDestroy()
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


BOOL CMaintenancePG::PreTranslateMessage(MSG* pMsg)
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


HBRUSH CMaintenancePG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CMaintenancePG::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}


void CMaintenancePG::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnTimer(nIDEvent);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMaintenancePG::Lf_InitLocalValue()
{

}

void CMaintenancePG::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(32, 13, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[2].CreateFont(23, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[3].CreateFont(21, 9, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[4].CreateFont(17, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[5].CreateFont(17, 6, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_GRP_MP_POWER)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_GRP_MP_I2C)->SetFont(&m_Font[5]);

}

void CMaintenancePG::Lf_InitColorBrush()
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

void CMaintenancePG::Lf_loadPatternListToCombo()
{
	CString strfilename;
	WIN32_FIND_DATA wfd;
	HANDLE hSearch;

	if (lpModelInfo->m_nSignalType == SIGNAL_TYPE_ALPLD)
	{
		m_cmbMpPatternList.AddString(_T("Black"));
		m_cmbMpPatternList.AddString(_T("Blue"));
		m_cmbMpPatternList.AddString(_T("Chess"));
		m_cmbMpPatternList.AddString(_T("Cyan"));
		m_cmbMpPatternList.AddString(_T("Gray_Hor"));
		m_cmbMpPatternList.AddString(_T("Gray_Ver"));
		m_cmbMpPatternList.AddString(_T("Green"));
		m_cmbMpPatternList.AddString(_T("Magenta"));
		m_cmbMpPatternList.AddString(_T("Rainbow_Hor"));
		m_cmbMpPatternList.AddString(_T("Rainbow_Ver"));
		m_cmbMpPatternList.AddString(_T("Red"));
		m_cmbMpPatternList.AddString(_T("White"));
		m_cmbMpPatternList.AddString(_T("Yellow"));
	}
	else
	{
		hSearch = FindFirstFile(_T(".\\Pattern\\Logical\\*.pdb"), &wfd);
		if (hSearch != INVALID_HANDLE_VALUE)
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				strfilename.Format(_T("%s"), wfd.cFileName);
				m_cmbMpPatternList.AddString(strfilename.Mid(0, strfilename.GetLength() - 4));
			}
			while (FindNextFile(hSearch, &wfd))
			{
				if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
				{
					strfilename.Format(_T("%s"), wfd.cFileName);
					m_cmbMpPatternList.AddString(strfilename.Mid(0, strfilename.GetLength() - 4));
				}
			}
			FindClose(hSearch);
		}
	}

	m_cmbMpPatternList.SetCurSel(0);
}