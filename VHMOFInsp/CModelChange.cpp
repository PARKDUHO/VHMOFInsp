// CModelChange.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CModelChange.h"
#include "afxdialogex.h"
#include "CInitialize.h"


// CModelChange 대화 상자

IMPLEMENT_DYNAMIC(CModelChange, CDialogEx)

CModelChange::CModelChange(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_CHANGE, pParent)
{

}

CModelChange::~CModelChange()
{
}

void CModelChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_MC_MODEL_LIST, m_lstMcModelList);
	DDX_Control(pDX, IDC_CMB_MC_MODEL_INCH, m_cmbMcModelInch);
	DDX_Control(pDX, IDC_BTN_MC_LOAD, m_btnMcLoad);
}


BEGIN_MESSAGE_MAP(CModelChange, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_MC_LOAD, &CModelChange::OnBnClickedBtnMcLoad)
	ON_BN_CLICKED(IDC_BTN_MC_ALL_MODEL, &CModelChange::OnBnClickedBtnMcAllModel)
	ON_CBN_SELCHANGE(IDC_CMB_MC_MODEL_INCH, &CModelChange::OnCbnSelchangeCmbMcModelInch)
END_MESSAGE_MAP()


// CModelChange 메시지 처리기


BOOL CModelChange::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	lpSystemInfo = m_pApp->GetSystemInfo();
	lpModelInfo = m_pApp->GetModelInfo();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pApp->Gf_writeMLog(_T("<M/C> Model Change Dialog Open"));

	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();
	Lf_InitDlgDesign();

	Lf_initLoadModelList();
	Lf_InitModelInchInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CModelChange::OnDestroy()
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


BOOL CModelChange::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CModelChange::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
			if (pWnd->GetDlgCtrlID() == IDC_STT_MC_TITLE)
			{
				pDC->SetBkColor(COLOR_DEEP_BLUE);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_DEEP_BLUE];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_MC_MODEL_INCH_TITLE)
			{
				pDC->SetBkColor(COLOR_BLUISH);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_BLUISH];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_MC_MODEL_LIST_TITLE)
			{
				pDC->SetBkColor(COLOR_BLACK);
				pDC->SetTextColor(COLOR_YELLOW);
				return m_Brush[COLOR_IDX_BLACK];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_MC_DRIVE_PATH)
			{
				pDC->SetBkColor(COLOR_LIGHT_YELLOW);
				pDC->SetTextColor(COLOR_RED);
				return m_Brush[COLOR_IDX_LIGHT_YELLOW];
			}
			if (pWnd->GetDlgCtrlID() == IDC_STT_MC_INCH)
			{
				pDC->SetBkColor(COLOR_GRAY64);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY64];
			}
			break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CModelChange::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;

	GetClientRect(&rect);
	rect.bottom = 90;
	dc.FillSolidRect(rect, COLOR_DEEP_BLUE);

	GetClientRect(&rect);
	rect.top = 91;
	dc.FillSolidRect(rect, COLOR_RED);

	GetClientRect(&rect);
	rect.top = 92;
	dc.FillSolidRect(rect, COLOR_GRAY64);
}


void CModelChange::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}

void CModelChange::OnBnClickedBtnMcAllModel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cmbMcModelInch.SetCurSel(0);	// 0번 Index는 무조건 ALL 이다.
	Lf_LoadModelList();
}


void CModelChange::OnCbnSelchangeCmbMcModelInch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_LoadModelList();
}


void CModelChange::OnBnClickedBtnMcLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString modelName = _T("");

	m_lstMcModelList.GetText(m_lstMcModelList.GetCurSel(), modelName);

	lpSystemInfo->m_sLastModelName = modelName;
	Write_SysIniFile(_T("SYSTEM"), _T("LAST_MODELNAME"), modelName);

	CString strLog;
	strLog.Format(_T("<M/C> Model Change : %s"), modelName);
	m_pApp->Gf_writeMLog(strLog);

	CInitialize initDlg;
	initDlg.DoModal();

	CDialog::OnOK();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CModelChange::Lf_InitLocalValue()
{

}

void CModelChange::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(50, 23, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_MC_TITLE)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(36, 16, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_BTN_MC_LOAD)->SetFont(&m_Font[2]);

	m_Font[3].CreateFont(28, 13, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_LST_MC_MODEL_LIST)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(24, 11, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_MC_MODEL_INCH_TITLE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_CMB_MC_MODEL_INCH)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MC_INCH)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_BTN_MC_ALL_MODEL)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MC_DRIVE_PATH)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MC_MODEL_LIST_TITLE)->SetFont(&m_Font[4]);

	m_Font[5].CreateFont(16, 6, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

}

void CModelChange::Lf_InitColorBrush()
{
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_Brush[COLOR_IDX_GRAY240].CreateSolidBrush(COLOR_GRAY240);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
	m_Brush[COLOR_IDX_GRAY128].CreateSolidBrush(COLOR_GRAY128);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush(COLOR_GRAY64);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
}

void CModelChange::Lf_InitDlgDesign()
{
	// Button ICON
	m_btnMcLoad.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ENABLE));
}

void CModelChange::Lf_InitModelInchInfo()
{
	CString sDatafolder;
	CString sFile, sInch, sDrive;
	int find_idx;
	WIN32_FIND_DATA wfd;
	HANDLE hSearch;

	m_cmbMcModelInch.ResetContent();
	m_cmbMcModelInch.AddString(_T("ALL"));

	// ********* Host에서 MOD List를 불러올떄  **********
	sDatafolder.Format(_T("%s\\*.MOD"), lpSystemInfo->m_sDataFileModel);
	hSearch = FindFirstFile(sDatafolder, &wfd);
	if (hSearch != INVALID_HANDLE_VALUE)
	{
		sDrive.Format(_T("DRIVE : %s"), lpSystemInfo->m_sDataFileModel.Left(1));
		GetDlgItem(IDC_STT_MC_DRIVE_PATH)->SetWindowText(sDrive);

		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			sFile.Format(_T("%s"), wfd.cFileName);
			sInch.Format(_T("%s"), sFile.Mid(2, 3));
			m_cmbMcModelInch.AddString(sInch);
		}
		while (FindNextFile(hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				sFile.Format(_T("%s"), wfd.cFileName);
				sInch.Format(_T("%s"), sFile.Mid(2, 3));
				find_idx = m_cmbMcModelInch.FindStringExact(0, sInch);
				if (find_idx == -1)
				{
					m_cmbMcModelInch.AddString(sInch);
				}
			}
		}
		FindClose(hSearch);
	}
	else
	{
		TCHAR szCurrentPath[1024] = { 0, };
		GetCurrentDirectory(sizeof(szCurrentPath), szCurrentPath);

		sDrive.Format(_T("DRIVE : %c"), szCurrentPath[0]);
		GetDlgItem(IDC_STT_MC_DRIVE_PATH)->SetWindowText(sDrive);

		// Local Folder에서 Model List를 가져올 때
		sDatafolder.Format(_T(".\\Model\\*.MOD"));
		hSearch = FindFirstFile(sDatafolder, &wfd);

		if (hSearch != INVALID_HANDLE_VALUE)
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				sFile.Format(_T("%s"), wfd.cFileName);
				sInch.Format(_T("%s"), sFile.Mid(2, 3));
				m_cmbMcModelInch.AddString(sInch);
			}
			while (FindNextFile(hSearch, &wfd))
			{
				sFile.Format(_T("%s"), wfd.cFileName);
				sInch.Format(_T("%s"), sFile.Mid(2, 3));
				find_idx = m_cmbMcModelInch.FindStringExact(0, sInch);
				if (find_idx == -1)
				{
					m_cmbMcModelInch.AddString(sInch);
				}
			}
			FindClose(hSearch);
		}
		else
		{
		}
	}

	m_cmbMcModelInch.SetCurSel(0);
}

void CModelChange::Lf_LoadModelList()
{
	CString sDatafolder;
	CString sInch;
	WIN32_FIND_DATA wfd;
	HANDLE hSearch;

	GetDlgItem(IDC_CMB_MC_MODEL_INCH)->GetWindowText(sInch);

	if (sInch == _T("ALL"))
		sDatafolder.Format(_T("%s\\*.MOD"), lpSystemInfo->m_sDataFileModel);
	else
		sDatafolder.Format(_T("%s\\*%s*.MOD"), lpSystemInfo->m_sDataFileModel, sInch);

	m_lstMcModelList.ResetContent();
	// ********* Host에서 MOD List를 불러올떄  **********
	hSearch = FindFirstFile(sDatafolder, &wfd);
	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			CString filename;
			filename = wfd.cFileName;
			filename.Delete(filename.GetLength() - 4, 4);
			m_lstMcModelList.AddString(filename);
		}
		while (FindNextFile(hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				CString filename;
				filename = wfd.cFileName;
				filename.Delete(filename.GetLength() - 4, 4);
				m_lstMcModelList.AddString(filename);
			}
		}
		FindClose(hSearch);
	}
	else
	{
		// Local Folder에서 Model List를 가져올 때
		if (sInch == _T("ALL"))
			sDatafolder.Format(_T(".\\Model\\*.MOD"));
		else
			sDatafolder.Format(_T(".\\Model\\*%s*.MOD"), sInch);

		hSearch = FindFirstFile(sDatafolder, &wfd);

		if (hSearch != INVALID_HANDLE_VALUE)
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				CString filename;
				filename = wfd.cFileName;
				filename.Delete(filename.GetLength() - 4, 4);
				m_lstMcModelList.AddString(filename);
			}
			while (FindNextFile(hSearch, &wfd))
			{
				if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
				{
					CString filename;
					filename = wfd.cFileName;
					filename.Delete(filename.GetLength() - 4, 4);
					m_lstMcModelList.AddString(filename);
				}
			}
			FindClose(hSearch);
		}
		else
		{
		}
	}
	UpdateData(FALSE);


	CString buff;

	m_lstMcModelList.SetCurSel(0);
	for (int i = 0; i < m_lstMcModelList.GetCount(); i++)
	{
		m_lstMcModelList.GetText(i, buff);
		if (!lpSystemInfo->m_sLastModelName.Compare(buff))
		{
			m_lstMcModelList.SetCurSel(i);
			break;
		}
	}
}

void CModelChange::Lf_initLoadModelList()
{
	CString strfilename = _T("");
	CString strfilepath = _T("");
	WIN32_FIND_DATA wfd;
	HANDLE hSearch;

	strfilepath.Format(_T(".\\Model\\*.mod"));
	hSearch = FindFirstFile(strfilepath, &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			strfilename.Format(_T("%s"), wfd.cFileName);
			strfilename = strfilename.Mid(0, strfilename.GetLength() - 4);
			strfilename.MakeUpper();
			m_lstMcModelList.AddString(strfilename);
		}
		while (FindNextFile(hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				strfilename.Format(_T("%s"), wfd.cFileName);
				strfilename = strfilename.Mid(0, strfilename.GetLength() - 4);
				strfilename.MakeUpper();
				m_lstMcModelList.AddString(strfilename);
			}
		}
		FindClose(hSearch);
	}

	for (int i = 0; i < m_lstMcModelList.GetCount(); i++)
	{
		m_lstMcModelList.GetText(i, strfilename);
		if (strfilename == lpSystemInfo->m_sLastModelName)
		{
			m_lstMcModelList.SetCurSel(i);
			break;
		}
	}
}



