// CModelInfoFusing.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CModelInfoFusing.h"
#include "afxdialogex.h"


// CModelInfoFusing 대화 상자

IMPLEMENT_DYNAMIC(CModelInfoFusing, CDialogEx)

CModelInfoFusing::CModelInfoFusing(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_INFO_FUSING, pParent)
{
	m_pDefaultFont = new CFont();
	m_pDefaultFont->CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
}

CModelInfoFusing::~CModelInfoFusing()
{
	if (m_pDefaultFont != NULL)
	{
		delete m_pDefaultFont;
	}
}

void CModelInfoFusing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_MF_VCC, m_edtMfVcc);
	DDX_Control(pDX, IDC_EDT_MF_VCC_OFFSET, m_edtMfVccOffset);
	DDX_Control(pDX, IDC_EDT_MF_VEL, m_edtMfVel);
	DDX_Control(pDX, IDC_EDT_MF_VEL_OFFSET, m_edtMfVelOffset);
	DDX_Control(pDX, IDC_EDT_MF_LIMIT_VCC_LOW, m_edtMfLimitVccLow);
	DDX_Control(pDX, IDC_EDT_MF_LIMIT_VCC_HIGH, m_edtMfLimitVccHigh);
	DDX_Control(pDX, IDC_EDT_MF_LIMIT_VEL_LOW, m_edtMfLimitVelLow);
	DDX_Control(pDX, IDC_EDT_MF_LIMIT_VEL_HIGH, m_edtMfLimitVelHigh);
	DDX_Control(pDX, IDC_EDT_MF_LIMIT_ICC_LOW, m_edtMfLimitIccLow);
	DDX_Control(pDX, IDC_EDT_MF_LIMIT_ICC_HIGH, m_edtMfLimitIccHigh);
	DDX_Control(pDX, IDC_EDT_MF_LIMIT_IEL_LOW, m_edtMfLimitIelLow);
	DDX_Control(pDX, IDC_EDT_MF_LIMIT_IEL_HIGH, m_edtMfLimitIelHigh);
	DDX_Control(pDX, IDC_CMB_MF_PWR_ON_SEQ_1, m_cmbMfPowerOnSeq1);
	DDX_Control(pDX, IDC_CMB_MF_PWR_ON_SEQ_2, m_cmbMfPowerOnSeq2);
	DDX_Control(pDX, IDC_CMB_MF_PWR_ON_SEQ_3, m_cmbMfPowerOnSeq3);
	DDX_Control(pDX, IDC_CMB_MF_PWR_ON_SEQ_4, m_cmbMfPowerOnSeq4);
	DDX_Control(pDX, IDC_CMB_MF_PWR_ON_SEQ_5, m_cmbMfPowerOnSeq5);
	DDX_Control(pDX, IDC_CMB_MF_PWR_ON_SEQ_6, m_cmbMfPowerOnSeq6);
	DDX_Control(pDX, IDC_CMB_MF_PWR_ON_DELAY_1, m_edtMfPowerOnDelay1);
	DDX_Control(pDX, IDC_CMB_MF_PWR_ON_DELAY_2, m_edtMfPowerOnDelay2);
	DDX_Control(pDX, IDC_CMB_MF_PWR_ON_DELAY_3, m_edtMfPowerOnDelay3);
	DDX_Control(pDX, IDC_CMB_MF_PWR_ON_DELAY_4, m_edtMfPowerOnDelay4);
	DDX_Control(pDX, IDC_CMB_MF_PWR_ON_DELAY_5, m_edtMfPowerOnDelay5);
	DDX_Control(pDX, IDC_CMB_MF_PWR_ON_DELAY_6, m_edtMfPowerOnDelay6);
	DDX_Control(pDX, IDC_CMB_MF_PWR_OFF_SEQ_1, m_cmbMfPowerOffSeq1);
	DDX_Control(pDX, IDC_CMB_MF_PWR_OFF_SEQ_2, m_cmbMfPowerOffSeq2);
	DDX_Control(pDX, IDC_CMB_MF_PWR_OFF_SEQ_3, m_cmbMfPowerOffSeq3);
	DDX_Control(pDX, IDC_CMB_MF_PWR_OFF_SEQ_4, m_cmbMfPowerOffSeq4);
	DDX_Control(pDX, IDC_CMB_MF_PWR_OFF_SEQ_5, m_cmbMfPowerOffSeq5);
	DDX_Control(pDX, IDC_CMB_MF_PWR_OFF_SEQ_6, m_cmbMfPowerOffSeq6);
	DDX_Control(pDX, IDC_CMB_MF_PWR_OFF_DELAY_1, m_edtMfPowerOffDelay1);
	DDX_Control(pDX, IDC_CMB_MF_PWR_OFF_DELAY_2, m_edtMfPowerOffDelay2);
	DDX_Control(pDX, IDC_CMB_MF_PWR_OFF_DELAY_3, m_edtMfPowerOffDelay3);
	DDX_Control(pDX, IDC_CMB_MF_PWR_OFF_DELAY_4, m_edtMfPowerOffDelay4);
	DDX_Control(pDX, IDC_CMB_MF_PWR_OFF_DELAY_5, m_edtMfPowerOffDelay5);
	DDX_Control(pDX, IDC_CMB_MF_PWR_OFF_DELAY_6, m_edtMfPowerOffDelay6);
	DDX_Control(pDX, IDC_CMB_MF_SIGNAL_TYPE, m_cmbMfSignalType);
	DDX_Control(pDX, IDC_CMB_MF_SIGNAL_PIXEL, m_cmbMfPixel);
	DDX_Control(pDX, IDC_CMB_MF_SIGNAL_BIT, m_cmbMfSignalBit);
	DDX_Control(pDX, IDC_CMB_MF_SIGNAL_ROTATE, m_cmbMfRotate);
	DDX_Control(pDX, IDC_CMB_MF_SIGNAL_BIT_SELECT, m_cmbMfBitSelect);
	DDX_Control(pDX, IDC_CMB_MF_SIGNAL_FRS_MODE, m_cmbMfFrsMode);
	DDX_Control(pDX, IDC_EDT_MF_SIGNAL_CLOCK_DELAY, m_edtMfClockDelay);
	DDX_Control(pDX, IDC_EDT_MF_TIMING_FREQ, m_edtMfTimingFrequency);
	DDX_Control(pDX, IDC_EDT_MF_TIMING_VSYNC, m_edtMfTimingVSync);
	DDX_Control(pDX, IDC_EDT_MF_TIMING_HOR_TOTAL, m_edtMfTimingHorTotal);
	DDX_Control(pDX, IDC_EDT_MF_TIMING_HOR_ACTIVE, m_edtMfTimingHorActive);
	DDX_Control(pDX, IDC_EDT_MF_TIMING_HOR_WIDTH, m_edtMfTimingHorWidth);
	DDX_Control(pDX, IDC_EDT_MF_TIMING_HOR_BP, m_edtMfTimingHorBackPorch);
	DDX_Control(pDX, IDC_EDT_MF_TIMING_HOR_FP, m_edtMfTimingHorFrontPorch);
	DDX_Control(pDX, IDC_EDT_MF_TIMING_VER_TOTAL, m_edtMfTimingVerTotal);
	DDX_Control(pDX, IDC_EDT_MF_TIMING_VER_ACTIVE, m_edtMfTimingVerActive);
	DDX_Control(pDX, IDC_EDT_MF_TIMING_VER_WIDTH, m_edtMfTimingVerWidth);
	DDX_Control(pDX, IDC_EDT_MF_TIMING_VER_BP, m_edtMfTimingVerBackPorch);
	DDX_Control(pDX, IDC_EDT_MF_TIMING_VER_FP, m_edtMfTimingVerFrontPorch);
}


BEGIN_MESSAGE_MAP(CModelInfoFusing, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDT_MF_TIMING_FREQ, &CModelInfoFusing::OnEnChangeEdtMfTimingFreq)
	ON_EN_CHANGE(IDC_EDT_MF_TIMING_HOR_ACTIVE, &CModelInfoFusing::OnEnChangeEdtMfTimingHorActive)
	ON_EN_CHANGE(IDC_EDT_MF_TIMING_HOR_WIDTH, &CModelInfoFusing::OnEnChangeEdtMfTimingHorWidth)
	ON_EN_CHANGE(IDC_EDT_MF_TIMING_HOR_BP, &CModelInfoFusing::OnEnChangeEdtMfTimingHorBp)
	ON_EN_CHANGE(IDC_EDT_MF_TIMING_HOR_FP, &CModelInfoFusing::OnEnChangeEdtMfTimingHorFp)
	ON_EN_CHANGE(IDC_EDT_MF_TIMING_VER_ACTIVE, &CModelInfoFusing::OnEnChangeEdtMfTimingVerActive)
	ON_EN_CHANGE(IDC_EDT_MF_TIMING_VER_WIDTH, &CModelInfoFusing::OnEnChangeEdtMfTimingVerWidth)
	ON_EN_CHANGE(IDC_EDT_MF_TIMING_VER_BP, &CModelInfoFusing::OnEnChangeEdtMfTimingVerBp)
	ON_EN_CHANGE(IDC_EDT_MF_TIMING_VER_FP, &CModelInfoFusing::OnEnChangeEdtMfTimingVerFp)
END_MESSAGE_MAP()


// CModelInfoFusing 메시지 처리기


BOOL CModelInfoFusing::OnInitDialog()
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

	Lf_InitDialogControl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CModelInfoFusing::OnDestroy()
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


BOOL CModelInfoFusing::PreTranslateMessage(MSG* pMsg)
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


HBRUSH CModelInfoFusing::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
			if ((pWnd->GetDlgCtrlID() == IDC_STT_MF_POWER_SEQ_TITLE)
 				|| (pWnd->GetDlgCtrlID() == IDC_STT_MF_POWER_INFO_TITLE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_MF_POWER_LIMIT_TITLE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_MF_SIGNAL_INFO_TITLE)
				|| (pWnd->GetDlgCtrlID() == IDC_STT_MF_TIMING_TITLE)
				)
			{
				pDC->SetBkColor(COLOR_BLACK);
				pDC->SetTextColor(COLOR_YELLOW);
				return m_Brush[COLOR_IDX_BLACK];
			}

			if ((pWnd->GetDlgCtrlID() == IDC_EDT_MF_TIMING_HOR_TOTAL)
				|| (pWnd->GetDlgCtrlID() == IDC_EDT_MF_TIMING_VER_TOTAL))
			{
				pDC->SetBkColor(COLOR_JADEGREEN);
				pDC->SetTextColor(COLOR_BLACK);
				return m_Brush[COLOR_IDX_JADEGREEN];
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


void CModelInfoFusing::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}


void CModelInfoFusing::OnEnChangeEdtMfTimingFreq()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_calcVSync();
}


void CModelInfoFusing::OnEnChangeEdtMfTimingHorActive()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_calcHorResolution();
}


void CModelInfoFusing::OnEnChangeEdtMfTimingHorWidth()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_calcHorResolution();
}


void CModelInfoFusing::OnEnChangeEdtMfTimingHorBp()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_calcHorResolution();
}


void CModelInfoFusing::OnEnChangeEdtMfTimingHorFp()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_calcHorResolution();
}


void CModelInfoFusing::OnEnChangeEdtMfTimingVerActive()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_calcVerResolution();
}


void CModelInfoFusing::OnEnChangeEdtMfTimingVerWidth()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_calcVerResolution();
}


void CModelInfoFusing::OnEnChangeEdtMfTimingVerBp()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_calcVerResolution();
}


void CModelInfoFusing::OnEnChangeEdtMfTimingVerFp()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_calcVerResolution();
}


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void CModelInfoFusing::Lf_InitLocalValue()
{

}

void CModelInfoFusing::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(32, 13, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[2].CreateFont(23, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[3].CreateFont(19, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_MF_POWER_INFO_TITLE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_MF_POWER_LIMIT_TITLE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_MF_POWER_SEQ_TITLE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_MF_SIGNAL_INFO_TITLE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_MF_TIMING_TITLE)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(17, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[5].CreateFont(16, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
}

void CModelInfoFusing::Lf_InitColorBrush()
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
	m_Brush[COLOR_IDX_JADERED].CreateSolidBrush(COLOR_JADERED);
	m_Brush[COLOR_IDX_JADEGREEN].CreateSolidBrush(COLOR_JADEGREEN);
	m_Brush[COLOR_IDX_JADEBLUE].CreateSolidBrush(COLOR_JADEBLUE);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
	m_Brush[COLOR_IDX_GRAY128].CreateSolidBrush(COLOR_GRAY128);
	m_Brush[COLOR_IDX_GRAY192].CreateSolidBrush(COLOR_GRAY192);
	m_Brush[COLOR_IDX_GRAY224].CreateSolidBrush(COLOR_GRAY224);
	m_Brush[COLOR_IDX_GRAY240].CreateSolidBrush(COLOR_GRAY240);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
}

void CModelInfoFusing::Lf_InitDialogControl()
{
	CString sdata;

	sdata.Format(_T("%.1f"), lpModelInfo->m_fPowerVcc);
	m_edtMfVcc.SetWindowText(sdata);
	sdata.Format(_T("%.1f"), lpModelInfo->m_fPowerVel);
	m_edtMfVel.SetWindowText(sdata);
	sdata.Format(_T("%.1f"), lpModelInfo->m_fPowerVccOffset);
	m_edtMfVccOffset.SetWindowText(sdata);
	sdata.Format(_T("%.1f"), lpModelInfo->m_fPowerVelOffset);
	m_edtMfVelOffset.SetWindowText(sdata);

	sdata.Format(_T("%.1f"), lpModelInfo->m_fLimitVccLow);
	m_edtMfLimitVccLow.SetWindowText(sdata);
	sdata.Format(_T("%.1f"), lpModelInfo->m_fLimitVccHigh);
	m_edtMfLimitVccHigh.SetWindowText(sdata);
	sdata.Format(_T("%.1f"), lpModelInfo->m_fLimitVelLow);
	m_edtMfLimitVelLow.SetWindowText(sdata);
	sdata.Format(_T("%.1f"), lpModelInfo->m_fLimitVelHigh);
	m_edtMfLimitVelHigh.SetWindowText(sdata);
	sdata.Format(_T("%.1f"), lpModelInfo->m_fLimitIccLow);
	m_edtMfLimitIccLow.SetWindowText(sdata);
	sdata.Format(_T("%.1f"), lpModelInfo->m_fLimitIccHigh);
	m_edtMfLimitIccHigh.SetWindowText(sdata);
	sdata.Format(_T("%.1f"), lpModelInfo->m_fLimitIelLow);
	m_edtMfLimitIelLow.SetWindowText(sdata);
	sdata.Format(_T("%.1f"), lpModelInfo->m_fLimitIelHigh);
	m_edtMfLimitIelHigh.SetWindowText(sdata);

	m_cmbMfPowerOnSeq1.SetCurSel(lpModelInfo->m_nPowerOnSeq1);
	m_cmbMfPowerOnSeq2.SetCurSel(lpModelInfo->m_nPowerOnSeq2);
	m_cmbMfPowerOnSeq3.SetCurSel(lpModelInfo->m_nPowerOnSeq3);
	m_cmbMfPowerOnSeq4.SetCurSel(lpModelInfo->m_nPowerOnSeq4);
	m_cmbMfPowerOnSeq5.SetCurSel(lpModelInfo->m_nPowerOnSeq5);
	m_cmbMfPowerOnSeq6.SetCurSel(lpModelInfo->m_nPowerOnSeq6);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnDelay1);
	m_edtMfPowerOnDelay1.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnDelay2);
	m_edtMfPowerOnDelay2.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnDelay3);
	m_edtMfPowerOnDelay3.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnDelay4);
	m_edtMfPowerOnDelay4.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnDelay5);
	m_edtMfPowerOnDelay5.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnDelay6);
	m_edtMfPowerOnDelay6.SetWindowText(sdata);

	m_cmbMfPowerOffSeq1.SetCurSel(lpModelInfo->m_nPowerOffSeq1);
	m_cmbMfPowerOffSeq2.SetCurSel(lpModelInfo->m_nPowerOffSeq2);
	m_cmbMfPowerOffSeq3.SetCurSel(lpModelInfo->m_nPowerOffSeq3);
	m_cmbMfPowerOffSeq4.SetCurSel(lpModelInfo->m_nPowerOffSeq4);
	m_cmbMfPowerOffSeq5.SetCurSel(lpModelInfo->m_nPowerOffSeq5);
	m_cmbMfPowerOffSeq6.SetCurSel(lpModelInfo->m_nPowerOffSeq6);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffDelay1);
	m_edtMfPowerOffDelay1.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffDelay2);
	m_edtMfPowerOffDelay2.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffDelay3);
	m_edtMfPowerOffDelay3.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffDelay4);
	m_edtMfPowerOffDelay4.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffDelay5);
	m_edtMfPowerOffDelay5.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffDelay6);
	m_edtMfPowerOffDelay6.SetWindowText(sdata);

	m_cmbMfSignalType.SetCurSel(lpModelInfo->m_nSignalType);
	m_cmbMfPixel.SetCurSel(lpModelInfo->m_nPixelType);
	m_cmbMfSignalBit.SetCurSel(lpModelInfo->m_nSignalBit);
	m_cmbMfRotate.SetCurSel(lpModelInfo->m_nSignalRotate);
	m_cmbMfBitSelect.SetCurSel(lpModelInfo->m_nBitSelect);
	m_cmbMfFrsMode.SetCurSel(lpModelInfo->m_nFrsMode);
	sdata.Format(_T("%d"), lpModelInfo->m_nClockDelay);
	m_edtMfClockDelay.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fTimingFrequency);
	m_edtMfTimingFrequency.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nTimingHorActive);
	m_edtMfTimingHorActive.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nTimingHorWidth);
	m_edtMfTimingHorWidth.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nTimingHorBackPorch);
	m_edtMfTimingHorBackPorch.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nTimingHorFrontPorch);
	m_edtMfTimingHorFrontPorch.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nTimingVerActive);
	m_edtMfTimingVerActive.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nTimingVerWidth);
	m_edtMfTimingVerWidth.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nTimingVerBackPorch);
	m_edtMfTimingVerBackPorch.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nTimingVerFrontPorch);
	m_edtMfTimingVerFrontPorch.SetWindowText(sdata);

}

void CModelInfoFusing::Lf_calcHorResolution()
{
	CString sdata;
	int fp, active, bp, width;

	GetDlgItem(IDC_EDT_MF_TIMING_HOR_ACTIVE)->GetWindowText(sdata);
	active = _ttoi(sdata);
	GetDlgItem(IDC_EDT_MF_TIMING_HOR_WIDTH)->GetWindowText(sdata);
	width = _ttoi(sdata);
	GetDlgItem(IDC_EDT_MF_TIMING_HOR_BP)->GetWindowText(sdata);
	bp = _ttoi(sdata);
	GetDlgItem(IDC_EDT_MF_TIMING_HOR_FP)->GetWindowText(sdata);
	fp = _ttoi(sdata);

	sdata.Format(_T("%d"), active + width + bp + fp);
	GetDlgItem(IDC_EDT_MF_TIMING_HOR_TOTAL)->SetWindowText(sdata);

	Lf_calcVSync();
}

void CModelInfoFusing::Lf_calcVerResolution()
{
	CString sdata;
	int fp, active, bp, width;

	GetDlgItem(IDC_EDT_MF_TIMING_VER_ACTIVE)->GetWindowText(sdata);
	active = _ttoi(sdata);
	GetDlgItem(IDC_EDT_MF_TIMING_VER_WIDTH)->GetWindowText(sdata);
	width = _ttoi(sdata);
	GetDlgItem(IDC_EDT_MF_TIMING_VER_BP)->GetWindowText(sdata);
	bp = _ttoi(sdata);
	GetDlgItem(IDC_EDT_MF_TIMING_VER_FP)->GetWindowText(sdata);
	fp = _ttoi(sdata);

	sdata.Format(_T("%d"), active + width + bp + fp);
	GetDlgItem(IDC_EDT_MF_TIMING_VER_TOTAL)->SetWindowText(sdata);

	Lf_calcVSync();
}

void CModelInfoFusing::Lf_calcVSync()
{
	CString sdata;
	double mclk, vsync;
	int htotal, vtotal;

	GetDlgItem(IDC_EDT_MF_TIMING_FREQ)->GetWindowText(sdata);
	mclk = _tstof(sdata);
	GetDlgItem(IDC_EDT_MF_TIMING_HOR_TOTAL)->GetWindowText(sdata);
	htotal = _ttoi(sdata);
	GetDlgItem(IDC_EDT_MF_TIMING_VER_TOTAL)->GetWindowText(sdata);
	vtotal = _ttoi(sdata);

	mclk = mclk * 1000 * 1000;
	vsync = mclk / (double)(htotal * vtotal);

	sdata.Format(_T("%.1f"), vsync);
	GetDlgItem(IDC_EDT_MF_TIMING_VSYNC)->SetWindowText(sdata);
}

void CModelInfoFusing::Gf_DataSaveModelFusing(CString modelName)
{
	int i = 0, iValue = 0;
	float fValue = 0;
	CString sValue;
	CString strKey;

	//=====================================================================================================================
	//POWER Setting
	//=====================================================================================================================
	m_edtMfVcc.GetWindowText(sValue);						sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("VCC"), sValue);

	m_edtMfVel.GetWindowText(sValue);						sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("VEL"), sValue);

	m_edtMfVccOffset.GetWindowText(sValue);					sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("VCC_OFFSET"), sValue);

	m_edtMfVelOffset.GetWindowText(sValue);					sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("VEL_OFFSET"), sValue);

	//=====================================================================================================================
	//POWER Limit
	//=====================================================================================================================
	m_edtMfLimitVccLow.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("VCC_LIMIT_LOW"), sValue);

	m_edtMfLimitVccHigh.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("VCC_LIMIT_HIGH"), sValue);

	m_edtMfLimitVelLow.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("VEL_LIMIT_LOW"), sValue);

	m_edtMfLimitVelHigh.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("VEL_LIMIT_HIGH"), sValue);

	m_edtMfLimitIccLow.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("ICC_LIMIT_LOW"), sValue);

	m_edtMfLimitIccHigh.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("ICC_LIMIT_HIGH"), sValue);

	m_edtMfLimitIelLow.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("IEL_LIMIT_LOW"), sValue);

	m_edtMfLimitIelHigh.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("IEL_LIMIT_HIGH"), sValue);

	//=====================================================================================================================
	//POWER Sequence ON
	//=====================================================================================================================
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX1"), m_cmbMfPowerOnSeq1.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX2"), m_cmbMfPowerOnSeq2.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX3"), m_cmbMfPowerOnSeq3.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX4"), m_cmbMfPowerOnSeq4.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX5"), m_cmbMfPowerOnSeq5.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX6"), m_cmbMfPowerOnSeq6.GetCurSel());

	m_edtMfPowerOnDelay1.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY1"), sValue);

	m_edtMfPowerOnDelay2.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY2"), sValue);

	m_edtMfPowerOnDelay3.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY3"), sValue);

	m_edtMfPowerOnDelay4.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY4"), sValue);

	m_edtMfPowerOnDelay5.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY5"), sValue);

	m_edtMfPowerOnDelay6.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY6"), sValue);


	//=====================================================================================================================
	//POWER Sequence OFF
	//=====================================================================================================================
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX1"), m_cmbMfPowerOffSeq1.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX2"), m_cmbMfPowerOffSeq2.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX3"), m_cmbMfPowerOffSeq3.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX4"), m_cmbMfPowerOffSeq4.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX5"), m_cmbMfPowerOffSeq5.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX6"), m_cmbMfPowerOffSeq6.GetCurSel());

	m_edtMfPowerOffDelay1.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY1"), sValue);

	m_edtMfPowerOffDelay2.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY2"), sValue);

	m_edtMfPowerOffDelay3.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY3"), sValue);

	m_edtMfPowerOffDelay4.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY4"), sValue);

	m_edtMfPowerOffDelay5.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY5"), sValue);

	m_edtMfPowerOffDelay6.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY6"), sValue);


	//=====================================================================================================================
	//SIGNAL Info
	//=====================================================================================================================
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("SIGNAL_TYPE"),		m_cmbMfSignalType.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("PXEL_TYPE"),		m_cmbMfPixel.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("SIGNAL_BIT"),		m_cmbMfSignalBit.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("ROTATE"),			m_cmbMfRotate.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("BIT_SELECT"),		m_cmbMfBitSelect.GetCurSel());
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("FRS_MODE"),		m_cmbMfFrsMode.GetCurSel());

	m_edtMfClockDelay.GetWindowText(sValue);				sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("CLOCK_DELAY"), sValue);


	//=====================================================================================================================
	//Timing Set
	//=====================================================================================================================
	m_edtMfTimingFrequency.GetWindowText(sValue);						sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_FRE"), sValue);

	m_edtMfTimingHorTotal.GetWindowText(sValue);						sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_TOTAL_H"), sValue);

	m_edtMfTimingHorActive.GetWindowText(sValue);						sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_ACTIVE_H"), sValue);

	m_edtMfTimingHorWidth.GetWindowText(sValue);						sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_WIDTH_H"), sValue);

	m_edtMfTimingHorBackPorch.GetWindowText(sValue);					sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_BACK_P_H"), sValue);

	m_edtMfTimingHorFrontPorch.GetWindowText(sValue);					sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_Front_P_H"), sValue);

	m_edtMfTimingVerTotal.GetWindowText(sValue);						sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_TOTAL_V"), sValue);

	m_edtMfTimingVerActive.GetWindowText(sValue);						sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_ACTIVE_V"), sValue);

	m_edtMfTimingVerWidth.GetWindowText(sValue);						sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_WIDTH_V"), sValue);

	m_edtMfTimingVerBackPorch.GetWindowText(sValue);					sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_BACK_P_V"), sValue);

	m_edtMfTimingVerFrontPorch.GetWindowText(sValue);					sValue.Trim();
	Write_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_Front_P_V"), sValue);

}


