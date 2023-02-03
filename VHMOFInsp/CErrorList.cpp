// CErrorList.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CErrorList.h"
#include "afxdialogex.h"


// CErrorList 대화 상자입니다.

IMPLEMENT_DYNAMIC(CErrorList, CDialog)

CErrorList::CErrorList(CWnd* pParent /*=NULL*/)
	: CDialog(CErrorList::IDD, pParent)
{

}

CErrorList::~CErrorList()
{
}

void CErrorList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_EL_CLOSE, m_btnElClose);
	DDX_Control(pDX, IDC_CTR_EL_DATETIME, m_ctrAlmDateTime);
	DDX_Control(pDX, IDC_LST_EL_ERRORLIST_VIEW, m_lstElErrorListView);
}


BEGIN_MESSAGE_MAP(CErrorList, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_EL_CLOSE, &CErrorList::OnBnClickedBtnElClose)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_CTR_EL_DATETIME, &CErrorList::OnDtnDatetimechangeCtrElDatetime)
END_MESSAGE_MAP()


// CErrorList 메시지 처리기입니다.

BOOL CErrorList::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pApp->Gf_writeMLog("<ERROR LIST> Dialog OPEN");

	lpModelInfo = m_pApp->GetModelInfo();
	lpSystemInfo = m_pApp->GetSystemInfo();
	lpInspWorkInfo = m_pApp->GetInspWorkInfo();

	Lf_initVariable();
	Lf_initFontset();
	Lf_initColorBrush();
	Lf_initDesign();
	Lf_initErrorListViewList();

	Lf_loadErrorList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CErrorList::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO:  여기서 DC의 특성을 변경합니다.
	for (int i = 0; i < COLOR_IDX_MAX; i++)
	{
		m_Brush[i].DeleteObject();
	}

	for (int i = 0; i < FONT_IDX_MAX; i++)
	{
		m_Font[i].DeleteObject();
	}
}

HBRUSH CErrorList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
			if (pWnd->GetDlgCtrlID() == IDC_STT_EL_TITLE)
			{
				pDC->SetBkColor(COLOR_DEEP_BLUE);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_DEEP_BLUE];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_EL_ERRORLIST_OPE)
			{
				pDC->SetBkColor(COLOR_GRAY128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY128];
			}
			break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CErrorList::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = 100;
	dc.FillSolidRect(rect, COLOR_DEEP_BLUE);
}

void CErrorList::OnBnClickedBtnElClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnCancel();
}

void CErrorList::Lf_initVariable()
{

}

void CErrorList::Lf_initFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	m_Font[1].CreateFont(44, 20, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	GetDlgItem(IDC_STT_EL_TITLE)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(27, 11, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	GetDlgItem(IDC_BTN_EL_CLOSE)->SetFont(&m_Font[2]);

	m_Font[3].CreateFont(22, 9, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	m_Font[4].CreateFont(19, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	m_ctrAlmDateTime.SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_EL_ERRORLIST_OPE)->SetFont(&m_Font[4]);

	m_Font[5].CreateFont(16, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	GetDlgItem(IDC_LST_EL_ERRORLIST_VIEW)->SetFont(&m_Font[5]);
}

void CErrorList::Lf_initColorBrush()
{
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
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
	m_Brush[COLOR_IDX_DARK_RED].CreateSolidBrush(COLOR_DARK_RED);
	m_Brush[COLOR_IDX_DARK_ORANGE].CreateSolidBrush(COLOR_DARK_ORANGE);
	m_Brush[COLOR_IDX_GRAY128].CreateSolidBrush(COLOR_GRAY128);
	m_Brush[COLOR_IDX_GRAY224].CreateSolidBrush(COLOR_GRAY224);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
}

void CErrorList::Lf_initDesign()
{
	// Button ICON
	m_btnElClose.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DISABLE));
}

void CErrorList::Lf_initErrorListViewList()
{
	//////////////////////////////////////////////////////
	// List Control의 높이를 설정한다.
	CImageList m_image;
	m_image.Create(1, 25, ILC_COLORDDB, 1, 0);    // <- 높이.
	m_lstElErrorListView.SetImageList(&m_image, LVSIL_SMALL);
	//////////////////////////////////////////////////////

	m_lstElErrorListView.InsertColumn(0, _T("No"), LVCFMT_CENTER, -1, -1);
	m_lstElErrorListView.SetColumnWidth(0, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // No
	m_lstElErrorListView.SetColumnWidth(0, 50);

	m_lstElErrorListView.InsertColumn(1, _T("Date"), LVCFMT_LEFT, -1, -1);
	m_lstElErrorListView.SetColumnWidth(1, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // Date
	m_lstElErrorListView.SetColumnWidth(1, 150);

	m_lstElErrorListView.InsertColumn(2, _T("ERROR_CODE"), LVCFMT_LEFT, -1, -1);
	m_lstElErrorListView.SetColumnWidth(2, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // ERROR_CODE
	m_lstElErrorListView.SetColumnWidth(2, 130);

	m_lstElErrorListView.InsertColumn(3, _T("I/O"), LVCFMT_LEFT, -1, -1);
	m_lstElErrorListView.SetColumnWidth(3, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // I/O 접점
	m_lstElErrorListView.SetColumnWidth(3, 70);

	m_lstElErrorListView.InsertColumn(4, _T("Error Name"), LVCFMT_LEFT, -1, -1);
	m_lstElErrorListView.SetColumnWidth(4, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // Error Name
	m_lstElErrorListView.SetColumnWidth(4, 700);

	DWORD dwStype = m_lstElErrorListView.GetExtendedStyle();
	dwStype |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_lstElErrorListView.SetExtendedStyle(dwStype);
}

int CErrorList::Lf_readAgingErrorList(CString lpDate, CString* lpTime, CString* lpErrorCode, CString* lpIONumber, CString* lpError)
{
	int linecount = 0;
	CStdioFile cfile;
	CString filepath;
	CString readline;

	// 변수 초기화
	lpTime[0].Format(_T(""));
	lpErrorCode[0].Format(_T(""));
	lpError[0].Format(_T(""));

	// File을 읽는다.
	filepath.Format(_T(".\\Logs\\ErrorList\\%s\\%s\\%s_ErrorList.txt"), lpDate.Left(4), lpDate.Mid(4, 2), lpDate);

	// File을 Open한다.
	if (cfile.Open(filepath, CFile::modeRead | CFile::typeText))
	{
		while (cfile.ReadString(readline))
		{
			CString resToken;
			int curPos = 0;

			resToken = readline.Tokenize(_T(","), curPos);
			lpTime[linecount].Format(_T("%s"), resToken);
			if (curPos == -1)	continue;

			resToken = readline.Tokenize(_T(","), curPos);
			lpErrorCode[linecount].Format(_T("%s"), resToken);
			if (curPos == -1)	continue;

			resToken = readline.Tokenize(_T(","), curPos);
			lpIONumber[linecount].Format(_T("%s"), resToken);
			if (curPos == -1)	continue;

			resToken = readline.Tokenize(_T(","), curPos);
			lpError[linecount].Format(_T("%s"), resToken);

			linecount++;
		}

		cfile.Close();
	}

	return linecount;
}

void CErrorList::Lf_loadErrorList()
{
	int errorCount;
	CString dateString;
	COleDateTime timeDest;

	// 달력에서 선택된 날짜를 가져온다.
	m_ctrAlmDateTime.GetTime(timeDest);
	dateString.Format(_T("%04d%02d%02d"), timeDest.GetYear(), timeDest.GetMonth(), timeDest.GetDay());

	// 달력에서 선택된 날짜에 해당하는 File 을 찾아 로그 기록을 가져온다.
	CString eventTime[2000];
	CString eventErrorCode[2000];
	CString eventIONumber[2000];
	CString eventErrLog[2000];
	errorCount = Lf_readAgingErrorList(dateString, &eventTime[0], &eventErrorCode[0], &eventIONumber[0], &eventErrLog[0]);

	// 현재 출력되어있는 모든 아이템을 삭제한다.
	m_lstElErrorListView.DeleteAllItems();

	// 해당 날짜의 아이템을 출력한다.
	CString datastr;
	for (int i = 0; i < errorCount; i++)
	{
		// Index 번호
		datastr.Format(_T("%d"), (i + 1));
		m_lstElErrorListView.InsertItem(i, datastr);

		// DataTime을 출력한다
		m_lstElErrorListView.SetItemText(i, 1, eventTime[i]);

		// Channel Number를 출력한다
		m_lstElErrorListView.SetItemText(i, 2, eventErrorCode[i]);

		// Error 발생 시간을 출력한다
		m_lstElErrorListView.SetItemText(i, 3, eventIONumber[i]);

		// Error 내용을 출력한다
		m_lstElErrorListView.SetItemText(i, 4, eventErrLog[i]);
	}
}


void CErrorList::OnDtnDatetimechangeCtrElDatetime(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	Lf_loadErrorList();
}
