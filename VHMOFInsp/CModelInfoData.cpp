// CModelInfoData.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CModelInfoData.h"
#include "afxdialogex.h"


// CModelInfoData 대화 상자

IMPLEMENT_DYNAMIC(CModelInfoData, CDialogEx)

CModelInfoData::CModelInfoData(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_INFO_DATA, pParent)
{
	m_pDefaultFont = new CFont();
	m_pDefaultFont->CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
}

CModelInfoData::~CModelInfoData()
{
	if (m_pDefaultFont != NULL)
	{
		delete m_pDefaultFont;
	}
}

void CModelInfoData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_MD_PTN_NAME, m_cmbMdPtnName);
	DDX_Control(pDX, IDC_CMB_MD_I2C_PULL_UP, m_cmbI2cPullUp);
	DDX_Control(pDX, IDC_CMB_MD_I2C_LEVEL, m_cmbI2cLevel);
	DDX_Control(pDX, IDC_CMB_MD_I2C_CLOCK, m_cmbI2cClock);
	DDX_Control(pDX, IDC_CMB_MD_SPI_PULL_UP, m_cmbSpiPullUp);
	DDX_Control(pDX, IDC_CMB_MD_SPI_LEVEL, m_cmbSpiLevel);
	DDX_Control(pDX, IDC_CMB_MD_SPI_CLOCK, m_cmbSpiClock);
	DDX_Control(pDX, IDC_CMB_MD_GPIO_PULL_UP, m_cmbGpioPullUp);
	DDX_Control(pDX, IDC_CMB_MD_GPIO_LEVEL, m_cmbGpioLevel);
	DDX_Control(pDX, IDC_EDT_MD_PTN_VCC, m_edtMdPtnVcc);
	DDX_Control(pDX, IDC_EDT_MD_PTN_VEL, m_edtMdPtnVel);
	DDX_Control(pDX, IDC_EDT_MD_PTN_ICC, m_edtMdPtnIcc);
	DDX_Control(pDX, IDC_EDT_MD_PTN_IEL, m_edtMdPtnIel);
	DDX_Control(pDX, IDC_EDT_MD_PTN_LOCK_TIME, m_edtMdPtnLockTime);
	DDX_Control(pDX, IDC_EDT_MD_PTN_MAX_TIME, m_edtMdPtnMaxTime);
	DDX_Control(pDX, IDC_EDT_MD_PTN_VSYNC, m_edtMdPtnVSync);
	DDX_Control(pDX, IDC_CMB_MD_PTN_ONOFF, m_cmbMdPtnOnOff);
	DDX_Control(pDX, IDC_LST_MD_PTN_LIST, m_lstMdPtnList);
	DDX_Control(pDX, IDC_PIC_MD_PTN_PREVIEW, m_picMdPatternPreview);
}


BEGIN_MESSAGE_MAP(CModelInfoData, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_MD_PTN_ADD, &CModelInfoData::OnBnClickedBtnMdPtnAdd)
	ON_BN_CLICKED(IDC_BTN_MD_PTN_MODIFY, &CModelInfoData::OnBnClickedBtnMdPtnModify)
	ON_BN_CLICKED(IDC_BTN_MD_PTN_DEL, &CModelInfoData::OnBnClickedBtnMdPtnDel)
	ON_BN_CLICKED(IDC_BTN_MD_PTN_UP, &CModelInfoData::OnBnClickedBtnMdPtnUp)
	ON_BN_CLICKED(IDC_BTN_MD_PTN_DOWN, &CModelInfoData::OnBnClickedBtnMdPtnDown)
	ON_BN_CLICKED(IDC_BTN_MD_PTN_APPLY_ALL, &CModelInfoData::OnBnClickedBtnMdPtnApplyAll)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LST_MD_PTN_LIST, &CModelInfoData::OnLvnItemchangedLstMdPtnList)
	ON_CBN_SELCHANGE(IDC_CMB_MD_PTN_NAME, &CModelInfoData::OnCbnSelchangeCmbMdPtnName)
END_MESSAGE_MAP()


// CModelInfoData 메시지 처리기


BOOL CModelInfoData::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	lpModelInfo = m_pApp->GetModelInfo();
	lpSystemInfo = m_pApp->GetSystemInfo();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// Dialog의 기본 FONT 설정.
	SendMessageToDescendants(WM_SETFONT, (WPARAM)m_pDefaultFont->GetSafeHandle(), 1, TRUE, FALSE);

	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();

	Lf_loadPatternListToCombo();

	Lf_InitDialogControl();
	Lf_InitPatternListColum();
	Lf_InitPatternListUpdate();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CModelInfoData::OnDestroy()
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


BOOL CModelInfoData::PreTranslateMessage(MSG* pMsg)
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

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CModelInfoData::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
			if ((pWnd->GetDlgCtrlID() == IDC_STT_MD_INTERFACE_TITLE)
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


void CModelInfoData::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}

void CModelInfoData::OnBnClickedBtnMdPtnAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString subitem[20];
	int itemcnt = 0;

	// subitem의 list와 count를 가져온다.
	itemcnt = Lf_getPatternListSubitem(subitem);

	// subitem중 null data를 검사한다.
	for (int i = 0; i < itemcnt; i++)
	{
		if (subitem[i].GetLength() == 0)	return;
	}

	Lf_ListControlItemAdd(&m_lstMdPtnList, subitem, itemcnt);
}


void CModelInfoData::OnBnClickedBtnMdPtnModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString subitem[20];
	int itemcnt = 0;

	// subitem의 list와 count를 가져온다.
	itemcnt = Lf_getPatternListSubitem(subitem);

	// subitem중 null data를 검사한다.
	for (int i = 1; i < itemcnt; i++)
	{
		if (subitem[i].GetLength() == 0)	return;
	}

	Lf_ListControlItemChange(&m_lstMdPtnList, subitem, itemcnt);
}


void CModelInfoData::OnBnClickedBtnMdPtnDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_ListControlItemDelete(&m_lstMdPtnList);
}


void CModelInfoData::OnBnClickedBtnMdPtnUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString subitem[20];
	int itemcnt = 0;

	itemcnt = Lf_getPatternListSubitem(subitem);
	Lf_ListControlItemUp(&m_lstMdPtnList, itemcnt);
}


void CModelInfoData::OnBnClickedBtnMdPtnDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString subitem[20];
	int itemcnt = 0;

	itemcnt = Lf_getPatternListSubitem(subitem);
	Lf_ListControlItemDown(&m_lstMdPtnList, itemcnt);
}


void CModelInfoData::OnBnClickedBtnMdPtnApplyAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int m_nAllApplyIndex=0;
	CString strValue;

	//m_nAllApplyIndex = m_cmbPatternApplyAll.GetCurSel();

	if (m_nAllApplyIndex == MOD_PTN_NAME)				m_cmbMdPtnName.GetWindowText(strValue);
	else if (m_nAllApplyIndex == MOD_PTN_VCC)			m_edtMdPtnVcc.GetWindowText(strValue);
	else if (m_nAllApplyIndex == MOD_PTN_VEL)			m_edtMdPtnVel.GetWindowText(strValue);
	else if (m_nAllApplyIndex == MOD_PTN_ICC)			m_edtMdPtnIcc.GetWindowText(strValue);
	else if (m_nAllApplyIndex == MOD_PTN_IEL)			m_edtMdPtnIel.GetWindowText(strValue);
	else if (m_nAllApplyIndex == MOD_PTN_LOCKTIME)		m_edtMdPtnLockTime.GetWindowText(strValue);
	else if (m_nAllApplyIndex == MOD_PTN_MAXTIME)		m_edtMdPtnMaxTime.GetWindowText(strValue);
	else if (m_nAllApplyIndex == MOD_PTN_VSYNC)			m_edtMdPtnVSync.GetWindowText(strValue);
	else if (m_nAllApplyIndex == MOD_PTN_ONOFF)			m_cmbMdPtnOnOff.GetWindowText(strValue);
	else												return;

	CString subitem[20];
	Lf_getPatternListSubitem(subitem);
	Lf_ListControlItemChangeAll(&m_lstMdPtnList, m_nAllApplyIndex, subitem[m_nAllApplyIndex - 1]);
}


void CModelInfoData::OnLvnItemchangedLstMdPtnList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMLV->iItem < 0)
		return;
	if (pNMLV->uOldState && !pNMLV->uNewState)
		return;
	if (!pNMLV->uOldState && !pNMLV->uNewState)
		return;

	*pResult = 0;
	Lf_getPatternDataToControl(pNMLV->iItem);
}

void CModelInfoData::OnCbnSelchangeCmbMdPtnName()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strPtnName;

	m_cmbMdPtnName.GetWindowText(strPtnName);

	////////////////////////////////////////////////////////////////////////////////
	m_pApp->m_pPatternView->drawPattern(strPtnName);
	////////////////////////////////////////////////////////////////////////////////
	/*CPaintDC dc(this);
	OnDraw(&dc);*/
	Invalidate(FALSE);
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CModelInfoData::Lf_InitLocalValue()
{
	// 제품의 해상도 설정
	CRect rcLCD, rcFrame;

	rcLCD.top = 0;
	rcLCD.left = 0;
	rcLCD.right = 1919;
	rcLCD.bottom = 1079;

	// Preview 영역 설정
	m_picMdPatternPreview.GetWindowRect(rcFrame);
	ScreenToClient(rcFrame);

	// Preview 영역 초기화
	m_pApp->m_pPatternView->InitPatternRect(GetDC(), rcLCD, rcFrame);
	m_pApp->m_pPatternView->InitPatternPath(_T(".\\Pattern\\Logical"));
	m_pApp->m_pPatternView->InitBmpPatternPath(_T(""));

	// Pattern Data 초기값 설정.
	CString sdata;
	m_cmbMdPtnName.SetCurSel(0);
	sdata.Format(_T("%.1f"), lpModelInfo->m_fPowerVcc);
	m_edtMdPtnVcc.SetWindowText(sdata);
	sdata.Format(_T("%.1f"), lpModelInfo->m_fPowerVel);
	m_edtMdPtnVel.SetWindowText(sdata);
	m_edtMdPtnIcc.SetWindowText(_T("0"));
	m_edtMdPtnIel.SetWindowText(_T("0"));
	m_edtMdPtnLockTime.SetWindowText(_T("0"));
	m_edtMdPtnMaxTime.SetWindowText(_T("0"));
	sdata.Format(_T("%d"), (int)((lpModelInfo->m_fTimingFrequency/(float)lpModelInfo->m_nTimingHorTotal)/(float)lpModelInfo->m_nTimingVerTotal)*1000000);
	m_edtMdPtnVSync.SetWindowText(sdata);
	m_cmbMdPtnOnOff.SetCurSel(0);
}

void CModelInfoData::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(32, 13, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[2].CreateFont(23, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[3].CreateFont(21, 9, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_MD_INTERFACE_TITLE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_MD_PATTERN_TITLE)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(17, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[5].CreateFont(17, 6, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

}

void CModelInfoData::Lf_InitColorBrush()
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

void CModelInfoData::Gf_DataSaveModelData(CString modelName)
{
	int i = 0, iValue = 0;
	float fValue = 0;
	CString sValue;
	CString strKey;

	//=====================================================================================================================
	//Interface Setting
	//=====================================================================================================================
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("I2C_PULL_UP"), m_cmbI2cPullUp.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("I2C_LEVEL"), m_cmbI2cLevel.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("I2C_FREQUENCY"), m_cmbI2cClock.GetCurSel());

	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("QSPI_PULL_UP"), m_cmbSpiPullUp.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("QSPI_LEVEL"), m_cmbSpiLevel.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("QSPI_CLOCK"), m_cmbSpiClock.GetCurSel());

	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("GPIO_PULL_UP"), m_cmbGpioPullUp.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("GPIO_LEVEL"), m_cmbGpioLevel.GetCurSel());


	//=====================================================================================================================
	//Pattern Info
	//=====================================================================================================================
	int nLbItemCnt = 0;
	CString strPtnInfo = _T(""), strTemp = _T("");

	nLbItemCnt = m_lstMdPtnList.GetItemCount();
	if (nLbItemCnt < lpModelInfo->m_nPatternListCount) // When ListControl Item is deleted, Compare gnLbCnt to nLbItenCnt. 
	{
		strTemp.Empty();

		for (i = nLbItemCnt; i < lpModelInfo->m_nPatternListCount; i++)
		{
			strKey.Format(_T("PTN_%d"), i);
			Write_ModelFile(modelName, _T("PATTERN_INFO"), strKey, strTemp);
		}
		lpModelInfo->m_nPatternListCount = nLbItemCnt;
	}

	for (i = 0; i < nLbItemCnt; i++)
	{
		strPtnInfo.Empty();

		strTemp.Format(_T("%s"), m_lstMdPtnList.GetItemText(i, 1));			strPtnInfo.Append(strTemp);
		strTemp.Format(_T(",%s"), m_lstMdPtnList.GetItemText(i, 2));		strPtnInfo.Append(strTemp);
		strTemp.Format(_T(",%s"), m_lstMdPtnList.GetItemText(i, 3));		strPtnInfo.Append(strTemp);
		strTemp.Format(_T(",%s"), m_lstMdPtnList.GetItemText(i, 4));		strPtnInfo.Append(strTemp);
		strTemp.Format(_T(",%s"), m_lstMdPtnList.GetItemText(i, 5));		strPtnInfo.Append(strTemp);
		strTemp.Format(_T(",%s"), m_lstMdPtnList.GetItemText(i, 6));		strPtnInfo.Append(strTemp);
		strTemp.Format(_T(",%s"), m_lstMdPtnList.GetItemText(i, 7));		strPtnInfo.Append(strTemp);
		strTemp.Format(_T(",%s"), m_lstMdPtnList.GetItemText(i, 8));		strPtnInfo.Append(strTemp);
		strTemp.Format(_T(",%s"), m_lstMdPtnList.GetItemText(i, 9));		strPtnInfo.Append(strTemp);

		strKey.Format(_T("PTN_%d"), i);
		Write_ModelFile(modelName, _T("PATTERN_INFO"), strKey, NULL);
		Write_ModelFile(modelName, _T("PATTERN_INFO"), strKey, strPtnInfo);
	}
}

void CModelInfoData::Lf_loadPatternListToCombo()
{
	CString strfilename;
	WIN32_FIND_DATA wfd;
	HANDLE hSearch;

	hSearch = FindFirstFile(_T(".\\Pattern\\Logical\\*.pdb"), &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			strfilename.Format(_T("%s"), wfd.cFileName);
			m_cmbMdPtnName.AddString(strfilename.Mid(0, strfilename.GetLength() - 4));
		}
		while (FindNextFile(hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				strfilename.Format(_T("%s"), wfd.cFileName);
				m_cmbMdPtnName.AddString(strfilename.Mid(0, strfilename.GetLength() - 4));
			}
		}
		FindClose(hSearch);
	}

	m_cmbMdPtnName.SetCurSel(0);
}


void CModelInfoData::Lf_InitDialogControl()
{
	CString sdata;

	m_cmbI2cPullUp.SetCurSel(lpModelInfo->m_nI2cPullUp);
	m_cmbI2cLevel.SetCurSel(lpModelInfo->m_nI2cLevel);
	m_cmbI2cClock.SetCurSel(lpModelInfo->m_nI2cClock);
	m_cmbSpiPullUp.SetCurSel(lpModelInfo->m_nSpiPullUp);
	m_cmbSpiLevel.SetCurSel(lpModelInfo->m_nSpiLevel);
	m_cmbSpiClock.SetCurSel(lpModelInfo->m_nSpiClock);
	m_cmbGpioPullUp.SetCurSel(lpModelInfo->m_nGpioPullUp);
	m_cmbGpioLevel.SetCurSel(lpModelInfo->m_nGpioLevel);
}

void CModelInfoData::Lf_InitPatternListColum()
{
	CRect rect2;
	int nColum = 0;
	m_lstMdPtnList.InsertColumn(nColum, _T("NO"), LVCFMT_CENTER, -1, -1);
	m_lstMdPtnList.SetColumnWidth(nColum, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // NO
	m_lstMdPtnList.SetColumnWidth(nColum, 40);
	nColum++;
	m_lstMdPtnList.InsertColumn(nColum, _T("PATTERN"), LVCFMT_CENTER, -1, -1);
	m_lstMdPtnList.SetColumnWidth(nColum, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // Pattern Name
	GetDlgItem(IDC_CMB_MD_PTN_NAME)->GetWindowRect(&rect2);
	m_lstMdPtnList.SetColumnWidth(nColum, rect2.Width());
	nColum++;
	m_lstMdPtnList.InsertColumn(nColum, _T("VCC"), LVCFMT_CENTER, -1, -1);
	m_lstMdPtnList.SetColumnWidth(nColum, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // VDD
	GetDlgItem(IDC_EDT_MD_PTN_VCC)->GetWindowRect(&rect2);
	m_lstMdPtnList.SetColumnWidth(nColum, rect2.Width());
	nColum++;
	m_lstMdPtnList.InsertColumn(nColum, _T("VEL"), LVCFMT_CENTER, -1, -1);
	m_lstMdPtnList.SetColumnWidth(nColum, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // VEL
	GetDlgItem(IDC_EDT_MD_PTN_VEL)->GetWindowRect(&rect2);
	m_lstMdPtnList.SetColumnWidth(nColum, rect2.Width());
	nColum++;
	m_lstMdPtnList.InsertColumn(nColum, _T("ICC"), LVCFMT_CENTER, -1, -1);
	m_lstMdPtnList.SetColumnWidth(nColum, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // IVDD
	GetDlgItem(IDC_EDT_MD_PTN_ICC)->GetWindowRect(&rect2);
	m_lstMdPtnList.SetColumnWidth(nColum, rect2.Width());
	nColum++;
	m_lstMdPtnList.InsertColumn(nColum, _T("IEL"), LVCFMT_CENTER, -1, -1);
	m_lstMdPtnList.SetColumnWidth(nColum, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // IEL
	GetDlgItem(IDC_EDT_MD_PTN_IEL)->GetWindowRect(&rect2);
	m_lstMdPtnList.SetColumnWidth(nColum, rect2.Width());
	nColum++;
	m_lstMdPtnList.InsertColumn(nColum, _T("LockTime"), LVCFMT_CENTER, -1, -1);
	m_lstMdPtnList.SetColumnWidth(nColum, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // LOCK TIME
	GetDlgItem(IDC_EDT_MD_PTN_LOCK_TIME)->GetWindowRect(&rect2);
	m_lstMdPtnList.SetColumnWidth(nColum, rect2.Width());
	nColum++;
	m_lstMdPtnList.InsertColumn(nColum, _T("MaxTime"), LVCFMT_CENTER, -1, -1);
	m_lstMdPtnList.SetColumnWidth(nColum, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // Max TIME
	GetDlgItem(IDC_EDT_MD_PTN_MAX_TIME)->GetWindowRect(&rect2);
	m_lstMdPtnList.SetColumnWidth(nColum, rect2.Width());
	nColum++;
	m_lstMdPtnList.InsertColumn(nColum, _T("VSYNC"), LVCFMT_CENTER, -1, -1);
	m_lstMdPtnList.SetColumnWidth(nColum, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // VSYNC
	GetDlgItem(IDC_EDT_MD_PTN_VSYNC)->GetWindowRect(&rect2);
	m_lstMdPtnList.SetColumnWidth(nColum, rect2.Width());
	nColum++;
	m_lstMdPtnList.InsertColumn(nColum, _T("ON/OFF"), LVCFMT_CENTER, -1, -1);
	m_lstMdPtnList.SetColumnWidth(nColum, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // ON/OFF
	GetDlgItem(IDC_CMB_MD_PTN_ONOFF)->GetWindowRect(&rect2);
	m_lstMdPtnList.SetColumnWidth(nColum, rect2.Width());
	nColum++;

	DWORD dwStype = m_lstMdPtnList.GetExtendedStyle(); // CListCtrl::
	dwStype |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_lstMdPtnList.SetExtendedStyle(dwStype); // CListCtrl::
}

void CModelInfoData::Lf_InitPatternListUpdate()
{
	CString strbuf;

	for (int i = 0; i < lpModelInfo->m_nPatternListCount; i++)
	{
		strbuf.Format(_T("%d"), i + 1);
		m_lstMdPtnList.InsertItem(i, strbuf);

		m_lstMdPtnList.SetItemText(i, 1, lpModelInfo->m_sLbPtnListNAME[i]);
		m_lstMdPtnList.SetItemText(i, 2, lpModelInfo->m_sLbPtnListVCC[i]);
		m_lstMdPtnList.SetItemText(i, 3, lpModelInfo->m_sLbPtnListVEL[i]);
		m_lstMdPtnList.SetItemText(i, 4, lpModelInfo->m_sLbPtnListICC[i]);
		m_lstMdPtnList.SetItemText(i, 5, lpModelInfo->m_sLbPtnListIEL[i]);
		m_lstMdPtnList.SetItemText(i, 6, lpModelInfo->m_sLbPtnListLockTime[i]);
		m_lstMdPtnList.SetItemText(i, 7, lpModelInfo->m_sLbPtnListMaxTIME[i]);
		m_lstMdPtnList.SetItemText(i, 8, lpModelInfo->m_sLbPtnListVSYNC[i]);
		m_lstMdPtnList.SetItemText(i, 9, lpModelInfo->m_sLbPtnListONOFF[i]);
	}
}

int  CModelInfoData::Lf_getPatternListSubitem(CString* subitem)
{
	int itemcnt = 0;

	m_cmbMdPtnName.GetWindowText(subitem[itemcnt++]);
	m_edtMdPtnVcc.GetWindowText(subitem[itemcnt++]);
	m_edtMdPtnVel.GetWindowText(subitem[itemcnt++]);
	m_edtMdPtnIcc.GetWindowText(subitem[itemcnt++]);
	m_edtMdPtnIel.GetWindowText(subitem[itemcnt++]);
	m_edtMdPtnLockTime.GetWindowText(subitem[itemcnt++]);
	m_edtMdPtnMaxTime.GetWindowText(subitem[itemcnt++]);
	m_edtMdPtnVSync.GetWindowText(subitem[itemcnt++]);
	m_cmbMdPtnOnOff.GetWindowText(subitem[itemcnt++]);

	return itemcnt;
}

void CModelInfoData::Lf_getPatternDataToControl(int itemidx)
{
	int find_idx = 0;
	int subitem_idx = 1;
	CString strPtnName, strbuf;
	WCHAR wszbuf[50] = { 0, };

	// subitem_idx=1. Pattern Name
	strPtnName = m_lstMdPtnList.GetItemText(itemidx, subitem_idx++);
	strPtnName.MakeUpper();
	find_idx = m_cmbMdPtnName.FindStringExact(0, strPtnName);
	if (find_idx == -1)
	{
		AfxMessageBox(_T("The selected pattern information was not found."), MB_ICONERROR);
		m_cmbMdPtnName.SetCurSel(0);
	}
	else
	{
		m_cmbMdPtnName.SetCurSel(find_idx);
	}

	// subitem_idx=2. VDD
	strbuf = m_lstMdPtnList.GetItemText(itemidx, subitem_idx++);
	m_edtMdPtnVcc.SetWindowText(strbuf);

	// subitem_idx=3. VEL
	strbuf = m_lstMdPtnList.GetItemText(itemidx, subitem_idx++);
	m_edtMdPtnVel.SetWindowText(strbuf);

	// subitem_idx=4. ICC
	strbuf = m_lstMdPtnList.GetItemText(itemidx, subitem_idx++);
	m_edtMdPtnIcc.SetWindowText(strbuf);

	// subitem_idx=5. IEL
	strbuf = m_lstMdPtnList.GetItemText(itemidx, subitem_idx++);
	m_edtMdPtnIel.SetWindowText(strbuf);

	// subitem_idx=6. LOCK TIME
	strbuf = m_lstMdPtnList.GetItemText(itemidx, subitem_idx++);
	m_edtMdPtnLockTime.SetWindowText(strbuf);

	// subitem_idx=7. MAX TIME
	strbuf = m_lstMdPtnList.GetItemText(itemidx, subitem_idx++);
	m_edtMdPtnMaxTime.SetWindowText(strbuf);

	// subitem_idx=8. VSYNC
	strbuf = m_lstMdPtnList.GetItemText(itemidx, subitem_idx++);
	m_edtMdPtnVSync.SetWindowText(strbuf);

	// subitem_idx=9. ON/OFF
	strbuf = m_lstMdPtnList.GetItemText(itemidx, subitem_idx++);
	if (!strbuf.CompareNoCase(_T("ON")))	m_cmbMdPtnOnOff.SetCurSel(1);
	else									m_cmbMdPtnOnOff.SetCurSel(0);

	////////////////////////////////////////////////////////////////////////////////
	m_pApp->m_pPatternView->drawPattern(strPtnName);
	////////////////////////////////////////////////////////////////////////////////
}

void CModelInfoData::Lf_ListControlItemAdd(CListCtrl* pListCtrl, CString* subItem, int subitem_cnt)
{
	int nItemCount = 0;

	nItemCount = pListCtrl->GetItemCount();

	POSITION pSelectItemPos = pListCtrl->GetFirstSelectedItemPosition();
	int nItemPosition = pListCtrl->GetNextSelectedItem(pSelectItemPos);

	// 선택된 Item의 아래 Position 위치를 가져온다.
	nItemPosition++;
	if (nItemPosition < 0)
	{
		nItemPosition = nItemCount;
	}

	// ITEM을 추가한다.
	CString strIndex;
	strIndex.Format(_T("%d"), nItemPosition + 1);
	pListCtrl->InsertItem(nItemPosition, strIndex);

	// ITEM의 값을 Setting한다.
	for (int i = 0; i < subitem_cnt; i++)
	{
		pListCtrl->SetItem(nItemPosition, i + 1, LVIF_TEXT, subItem[i], 0, LVIF_STATE, 0, 0);
	}
	for (int i = nItemPosition; i <= nItemCount; i++)
	{
		strIndex.Format(_T("%d"), i + 1);
		pListCtrl->SetItem(i, 0, LVIF_TEXT, strIndex, 0, LVIF_STATE, 0, 0);
	}
	// List의 Focus 및 Select 상태를 Update한다.
	pListCtrl->SetSelectionMark(nItemPosition); // Item Select & Focus
	pListCtrl->SetItemState(nItemPosition, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	pListCtrl->EnsureVisible(nItemPosition, FALSE);


}

void CModelInfoData::Lf_ListControlItemDelete(CListCtrl* pListCtrl)
{
	POSITION pSelectItemPos = pListCtrl->GetFirstSelectedItemPosition();
	int nItemPosition = pListCtrl->GetNextSelectedItem(pSelectItemPos);

	if (nItemPosition < 0)
	{
		return;
	}

	pListCtrl->DeleteItem(nItemPosition);

	if (!pListCtrl->GetItemCount())
	{
		return;
	}
	else
	{
		if (pListCtrl->GetItemCount() <= nItemPosition)
			nItemPosition--;

		pListCtrl->SetSelectionMark(nItemPosition); // Item Select & Focus
		pListCtrl->SetItemState(nItemPosition, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
		pListCtrl->SetFocus();
		pListCtrl->EnsureVisible(nItemPosition, FALSE);
	}
}

void CModelInfoData::Lf_ListControlItemChange(CListCtrl* pListCtrl, CString* subItem, int subitem_cnt)
{
	POSITION pSelectItemPos = pListCtrl->GetFirstSelectedItemPosition();
	int nItemPosition = pListCtrl->GetNextSelectedItem(pSelectItemPos);
	if (nItemPosition < 0)
	{
		return;
	}

	for (int i = 0; i < subitem_cnt; i++)
	{
		pListCtrl->SetItem(nItemPosition, i + 1, LVIF_TEXT, subItem[i], 0, LVIF_STATE, 0, 0);
	}

	pListCtrl->SetSelectionMark(nItemPosition); // Item Select & Focus
	pListCtrl->SetItemState(nItemPosition, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	pListCtrl->EnsureVisible(nItemPosition, FALSE);
}

void CModelInfoData::Lf_ListControlItemChangeAll(CListCtrl* pListCtrl, int subIndex, CString subItem)
{
	int pos = 0;
	int nItemCount = pListCtrl->GetItemCount();
	if (nItemCount <= 0)
	{
		return;
	}

	for (pos = 0; pos < nItemCount; pos++)
	{
		pListCtrl->SetItem(pos, subIndex, LVIF_TEXT, subItem, 0, LVIF_STATE, 0, 0);
	}
}

void CModelInfoData::Lf_ListControlItemUp(CListCtrl* pListCtrl, int subitem_cnt)
{
	POSITION pSelectItemPos = pListCtrl->GetFirstSelectedItemPosition();
	int nItemPosition = pListCtrl->GetNextSelectedItem(pSelectItemPos);
	if (nItemPosition < 1)
	{
		return;
	}

	// Item Swap
	WCHAR swapItem1[100];
	WCHAR swapItem2[100];
	int pos1, pos2;
	pos1 = nItemPosition;	// Select Item Position
	pos2 = nItemPosition - 1;	// Upper Item Position
	// 번호는 이동하지 않는다.
	for (int i = 0; i < subitem_cnt; i++)
	{
		pListCtrl->GetItemText(pos1, i + 1, swapItem1, 100);
		pListCtrl->GetItemText(pos2, i + 1, swapItem2, 100);
		pListCtrl->SetItem(pos2, i + 1, LVIF_TEXT, swapItem1, 0, LVIF_STATE, 0, 0);
		pListCtrl->SetItem(pos1, i + 1, LVIF_TEXT, swapItem2, 0, LVIF_STATE, 0, 0);
	}
	pSelectItemPos = pListCtrl->GetFirstSelectedItemPosition();
	pListCtrl->GetNextSelectedItem(pSelectItemPos);
	// Item Swap End

	pListCtrl->SetSelectionMark(nItemPosition); // Item Select & Focus
	pListCtrl->SetItemState(nItemPosition - 1, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	pListCtrl->SetFocus();
	pListCtrl->EnsureVisible(nItemPosition - 1, FALSE);
}

void CModelInfoData::Lf_ListControlItemDown(CListCtrl* pListCtrl, int subitem_cnt)
{

	POSITION pSelectItemPos = pListCtrl->GetFirstSelectedItemPosition();
	int nItemPosition = pListCtrl->GetNextSelectedItem(pSelectItemPos);
	int count = pListCtrl->GetItemCount();

	if (nItemPosition > (count - 2))
	{
		return;
	}

	// Item Swap
	WCHAR swapItem1[100];
	WCHAR swapItem2[100];
	int pos1, pos2;
	pos1 = nItemPosition;	// Select Item Position
	pos2 = nItemPosition + 1;	// Upper Item Position
	for (int i = 0; i < subitem_cnt; i++)
	{
		pListCtrl->GetItemText(pos1, i + 1, swapItem1, 100);
		pListCtrl->GetItemText(pos2, i + 1, swapItem2, 100);
		pListCtrl->SetItem(pos2, i + 1, LVIF_TEXT, swapItem1, 0, LVIF_STATE, 0, 0);
		pListCtrl->SetItem(pos1, i + 1, LVIF_TEXT, swapItem2, 0, LVIF_STATE, 0, 0);
	}
	pSelectItemPos = pListCtrl->GetFirstSelectedItemPosition();
	pListCtrl->GetNextSelectedItem(pSelectItemPos);
	// Item Swap End


	pListCtrl->SetSelectionMark(nItemPosition); // Item Select & Focus
	pListCtrl->SetItemState(nItemPosition + 1, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	pListCtrl->SetFocus();
	pListCtrl->EnsureVisible(nItemPosition + 1, FALSE);
}

void CModelInfoData::Lf_ListControlItemApplyAll(CListCtrl* pListCtrl, CString* subItem)
{
	int pos = 0;
	int nItemCount = pListCtrl->GetItemCount();
	if (nItemCount <= 0)
	{
		return;
	}

	for (pos = 0; pos < nItemCount; pos++)
	{
		pListCtrl->SetItem(pos, 2, LVIF_TEXT, subItem[0], 0, LVIF_STATE, 0, 0);
		pListCtrl->SetItem(pos, 3, LVIF_TEXT, subItem[1], 0, LVIF_STATE, 0, 0);
	}
}



