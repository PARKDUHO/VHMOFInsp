// CAutoFirmware.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CAutoFirmware.h"
#include "afxdialogex.h"


// CAutoFirmware 대화 상자

IMPLEMENT_DYNAMIC(CAutoFirmware, CDialog)

CAutoFirmware::CAutoFirmware(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_AUTO_FIRMWARE, pParent)
{

}

CAutoFirmware::~CAutoFirmware()
{
}

void CAutoFirmware::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROG_AF_PROGRESS, m_progAfProgress);
	DDX_Control(pDX, IDC_BTN_AF_DOWNLOAD_START, m_btnAfDownloadStart);
}


BEGIN_MESSAGE_MAP(CAutoFirmware, CDialog)
	ON_BN_CLICKED(IDC_BTN_AF_FILE_OPEN, &CAutoFirmware::OnBnClickedBtnAfFileOpen)
	ON_BN_CLICKED(IDC_BTN_AF_READ_VERSION, &CAutoFirmware::OnBnClickedBtnAfReadVersion)
	ON_BN_CLICKED(IDC_BTN_AF_DOWNLOAD_START, &CAutoFirmware::OnBnClickedBtnAfDownloadStart)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAutoFirmware 메시지 처리기

BOOL CAutoFirmware::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAutoFirmware::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


BOOL CAutoFirmware::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialog::PreTranslateMessage(pMsg);
}


HBRUSH CAutoFirmware::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CAutoFirmware::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}


void CAutoFirmware::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnTimer(nIDEvent);
}


void CAutoFirmware::OnBnClickedBtnAfFileOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAutoFirmware::OnBnClickedBtnAfReadVersion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAutoFirmware::OnBnClickedBtnAfDownloadStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
