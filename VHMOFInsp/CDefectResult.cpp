// DefectResult.cpp: 구현 파일
//

#include "pch.h"
#include "VHMOFInsp.h"
#include "CDefectResult.h"
#include "afxdialogex.h"


// CDefectResult 대화 상자

IMPLEMENT_DYNAMIC(CDefectResult, CDialog)

CDefectResult::CDefectResult(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DEFECT_RESULT, pParent)
{
	preX = -1;
	preY = -1;
}

CDefectResult::~CDefectResult()
{
}

void CDefectResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_1, m_sttButton_1to1);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_2, m_sttButton_1to2);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_3, m_sttButton_1to3);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_4, m_sttButton_1to4);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_5, m_sttButton_1to5);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_6, m_sttButton_1to6);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_7, m_sttButton_1to7);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_8, m_sttButton_1to8);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_9, m_sttButton_1to9);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_10, m_sttButton_1to10);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_1, m_sttButton_2to1);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_2, m_sttButton_2to2);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_3, m_sttButton_2to3);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_4, m_sttButton_2to4);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_5, m_sttButton_2to5);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_6, m_sttButton_2to6);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_7, m_sttButton_2to7);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_8, m_sttButton_2to8);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_9, m_sttButton_2to9);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_10, m_sttButton_2to10);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_1, m_sttButton_3to1);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_2, m_sttButton_3to2);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_3, m_sttButton_3to3);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_4, m_sttButton_3to4);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_5, m_sttButton_3to5);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_6, m_sttButton_3to6);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_7, m_sttButton_3to7);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_8, m_sttButton_3to8);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_9, m_sttButton_3to9);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_10, m_sttButton_3to10);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_1, m_sttButton_4to1);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_2, m_sttButton_4to2);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_3, m_sttButton_4to3);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_4, m_sttButton_4to4);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_5, m_sttButton_4to5);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_6, m_sttButton_4to6);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_7, m_sttButton_4to7);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_8, m_sttButton_4to8);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_9, m_sttButton_4to9);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_10, m_sttButton_4to10);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_1, m_sttButton_5to1);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_2, m_sttButton_5to2);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_3, m_sttButton_5to3);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_4, m_sttButton_5to4);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_5, m_sttButton_5to5);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_6, m_sttButton_5to6);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_7, m_sttButton_5to7);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_8, m_sttButton_5to8);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_9, m_sttButton_5to9);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_10, m_sttButton_5to10);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_1, m_sttButton_6to1);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_2, m_sttButton_6to2);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_3, m_sttButton_6to3);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_4, m_sttButton_6to4);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_5, m_sttButton_6to5);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_6, m_sttButton_6to6);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_7, m_sttButton_6to7);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_8, m_sttButton_6to8);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_9, m_sttButton_6to9);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_10, m_sttButton_6to10);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_1, m_sttButton_7to1);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_2, m_sttButton_7to2);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_3, m_sttButton_7to3);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_4, m_sttButton_7to4);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_5, m_sttButton_7to5);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_6, m_sttButton_7to6);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_7, m_sttButton_7to7);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_8, m_sttButton_7to8);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_9, m_sttButton_7to9);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_10, m_sttButton_7to10);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_1, m_sttButton_8to1);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_2, m_sttButton_8to2);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_3, m_sttButton_8to3);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_4, m_sttButton_8to4);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_5, m_sttButton_8to5);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_6, m_sttButton_8to6);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_7, m_sttButton_8to7);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_8, m_sttButton_8to8);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_9, m_sttButton_8to9);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_10, m_sttButton_8to10);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_1, m_sttButton_9to1);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_2, m_sttButton_9to2);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_3, m_sttButton_9to3);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_4, m_sttButton_9to4);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_5, m_sttButton_9to5);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_6, m_sttButton_9to6);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_7, m_sttButton_9to7);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_8, m_sttButton_9to8);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_9, m_sttButton_9to9);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_10, m_sttButton_9to10);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_1, m_sttButton_10to1);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_2, m_sttButton_10to2);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_3, m_sttButton_10to3);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_4, m_sttButton_10to4);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_5, m_sttButton_10to5);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_6, m_sttButton_10to6);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_7, m_sttButton_10to7);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_8, m_sttButton_10to8);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_9, m_sttButton_10to9);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_10, m_sttButton_10to10);

}


BEGIN_MESSAGE_MAP(CDefectResult, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_STT_DEF_1_TO_1, &CDefectResult::OnStnClickedSttDef1To1)
	ON_STN_CLICKED(IDC_STT_DEF_1_TO_2, &CDefectResult::OnStnClickedSttDef1To2)
	ON_STN_CLICKED(IDC_STT_DEF_1_TO_3, &CDefectResult::OnStnClickedSttDef1To3)
	ON_STN_CLICKED(IDC_STT_DEF_1_TO_4, &CDefectResult::OnStnClickedSttDef1To4)
	ON_STN_CLICKED(IDC_STT_DEF_1_TO_5, &CDefectResult::OnStnClickedSttDef1To5)
	ON_STN_CLICKED(IDC_STT_DEF_1_TO_6, &CDefectResult::OnStnClickedSttDef1To6)
	ON_STN_CLICKED(IDC_STT_DEF_1_TO_7, &CDefectResult::OnStnClickedSttDef1To7)
	ON_STN_CLICKED(IDC_STT_DEF_1_TO_8, &CDefectResult::OnStnClickedSttDef1To8)
	ON_STN_CLICKED(IDC_STT_DEF_1_TO_9, &CDefectResult::OnStnClickedSttDef1To9)
	ON_STN_CLICKED(IDC_STT_DEF_1_TO_10, &CDefectResult::OnStnClickedSttDef1To10)
	ON_STN_CLICKED(IDC_STT_DEF_2_TO_1, &CDefectResult::OnStnClickedSttDef2To1)
	ON_STN_CLICKED(IDC_STT_DEF_2_TO_2, &CDefectResult::OnStnClickedSttDef2To2)
	ON_STN_CLICKED(IDC_STT_DEF_2_TO_3, &CDefectResult::OnStnClickedSttDef2To3)
	ON_STN_CLICKED(IDC_STT_DEF_2_TO_4, &CDefectResult::OnStnClickedSttDef2To4)
	ON_STN_CLICKED(IDC_STT_DEF_2_TO_5, &CDefectResult::OnStnClickedSttDef2To5)
	ON_STN_CLICKED(IDC_STT_DEF_2_TO_6, &CDefectResult::OnStnClickedSttDef2To6)
	ON_STN_CLICKED(IDC_STT_DEF_2_TO_7, &CDefectResult::OnStnClickedSttDef2To7)
	ON_STN_CLICKED(IDC_STT_DEF_2_TO_8, &CDefectResult::OnStnClickedSttDef2To8)
	ON_STN_CLICKED(IDC_STT_DEF_2_TO_9, &CDefectResult::OnStnClickedSttDef2To9)
	ON_STN_CLICKED(IDC_STT_DEF_2_TO_10, &CDefectResult::OnStnClickedSttDef2To10)
	ON_STN_CLICKED(IDC_STT_DEF_3_TO_1, &CDefectResult::OnStnClickedSttDef3To1)
	ON_STN_CLICKED(IDC_STT_DEF_3_TO_2, &CDefectResult::OnStnClickedSttDef3To2)
	ON_STN_CLICKED(IDC_STT_DEF_3_TO_3, &CDefectResult::OnStnClickedSttDef3To3)
	ON_STN_CLICKED(IDC_STT_DEF_3_TO_4, &CDefectResult::OnStnClickedSttDef3To4)
	ON_STN_CLICKED(IDC_STT_DEF_3_TO_5, &CDefectResult::OnStnClickedSttDef3To5)
	ON_STN_CLICKED(IDC_STT_DEF_3_TO_6, &CDefectResult::OnStnClickedSttDef3To6)
	ON_STN_CLICKED(IDC_STT_DEF_3_TO_7, &CDefectResult::OnStnClickedSttDef3To7)
	ON_STN_CLICKED(IDC_STT_DEF_3_TO_8, &CDefectResult::OnStnClickedSttDef3To8)
	ON_STN_CLICKED(IDC_STT_DEF_3_TO_9, &CDefectResult::OnStnClickedSttDef3To9)
	ON_STN_CLICKED(IDC_STT_DEF_3_TO_10, &CDefectResult::OnStnClickedSttDef3To10)
	ON_STN_CLICKED(IDC_STT_DEF_4_TO_1, &CDefectResult::OnStnClickedSttDef4To1)
	ON_STN_CLICKED(IDC_STT_DEF_4_TO_2, &CDefectResult::OnStnClickedSttDef4To2)
	ON_STN_CLICKED(IDC_STT_DEF_4_TO_3, &CDefectResult::OnStnClickedSttDef4To3)
	ON_STN_CLICKED(IDC_STT_DEF_4_TO_4, &CDefectResult::OnStnClickedSttDef4To4)
	ON_STN_CLICKED(IDC_STT_DEF_4_TO_5, &CDefectResult::OnStnClickedSttDef4To5)
	ON_STN_CLICKED(IDC_STT_DEF_4_TO_6, &CDefectResult::OnStnClickedSttDef4To6)
	ON_STN_CLICKED(IDC_STT_DEF_4_TO_7, &CDefectResult::OnStnClickedSttDef4To7)
	ON_STN_CLICKED(IDC_STT_DEF_4_TO_8, &CDefectResult::OnStnClickedSttDef4To8)
	ON_STN_CLICKED(IDC_STT_DEF_4_TO_9, &CDefectResult::OnStnClickedSttDef4To9)
	ON_STN_CLICKED(IDC_STT_DEF_4_TO_10, &CDefectResult::OnStnClickedSttDef4To10)
	ON_STN_CLICKED(IDC_STT_DEF_5_TO_1, &CDefectResult::OnStnClickedSttDef5To1)
	ON_STN_CLICKED(IDC_STT_DEF_5_TO_2, &CDefectResult::OnStnClickedSttDef5To2)
	ON_STN_CLICKED(IDC_STT_DEF_5_TO_3, &CDefectResult::OnStnClickedSttDef5To3)
	ON_STN_CLICKED(IDC_STT_DEF_5_TO_4, &CDefectResult::OnStnClickedSttDef5To4)
	ON_STN_CLICKED(IDC_STT_DEF_5_TO_5, &CDefectResult::OnStnClickedSttDef5To5)
	ON_STN_CLICKED(IDC_STT_DEF_5_TO_6, &CDefectResult::OnStnClickedSttDef5To6)
	ON_STN_CLICKED(IDC_STT_DEF_5_TO_7, &CDefectResult::OnStnClickedSttDef5To7)
	ON_STN_CLICKED(IDC_STT_DEF_5_TO_8, &CDefectResult::OnStnClickedSttDef5To8)
	ON_STN_CLICKED(IDC_STT_DEF_5_TO_9, &CDefectResult::OnStnClickedSttDef5To9)
	ON_STN_CLICKED(IDC_STT_DEF_5_TO_10, &CDefectResult::OnStnClickedSttDef5To10)
	ON_STN_CLICKED(IDC_STT_DEF_6_TO_1, &CDefectResult::OnStnClickedSttDef6To1)
	ON_STN_CLICKED(IDC_STT_DEF_6_TO_2, &CDefectResult::OnStnClickedSttDef6To2)
	ON_STN_CLICKED(IDC_STT_DEF_6_TO_3, &CDefectResult::OnStnClickedSttDef6To3)
	ON_STN_CLICKED(IDC_STT_DEF_6_TO_4, &CDefectResult::OnStnClickedSttDef6To4)
	ON_STN_CLICKED(IDC_STT_DEF_6_TO_5, &CDefectResult::OnStnClickedSttDef6To5)
	ON_STN_CLICKED(IDC_STT_DEF_6_TO_6, &CDefectResult::OnStnClickedSttDef6To6)
	ON_STN_CLICKED(IDC_STT_DEF_6_TO_7, &CDefectResult::OnStnClickedSttDef6To7)
	ON_STN_CLICKED(IDC_STT_DEF_6_TO_8, &CDefectResult::OnStnClickedSttDef6To8)
	ON_STN_CLICKED(IDC_STT_DEF_6_TO_9, &CDefectResult::OnStnClickedSttDef6To9)
	ON_STN_CLICKED(IDC_STT_DEF_6_TO_10, &CDefectResult::OnStnClickedSttDef6To10)
	ON_STN_CLICKED(IDC_STT_DEF_7_TO_1, &CDefectResult::OnStnClickedSttDef7To1)
	ON_STN_CLICKED(IDC_STT_DEF_7_TO_2, &CDefectResult::OnStnClickedSttDef7To2)
	ON_STN_CLICKED(IDC_STT_DEF_7_TO_3, &CDefectResult::OnStnClickedSttDef7To3)
	ON_STN_CLICKED(IDC_STT_DEF_7_TO_4, &CDefectResult::OnStnClickedSttDef7To4)
	ON_STN_CLICKED(IDC_STT_DEF_7_TO_5, &CDefectResult::OnStnClickedSttDef7To5)
	ON_STN_CLICKED(IDC_STT_DEF_7_TO_6, &CDefectResult::OnStnClickedSttDef7To6)
	ON_STN_CLICKED(IDC_STT_DEF_7_TO_7, &CDefectResult::OnStnClickedSttDef7To7)
	ON_STN_CLICKED(IDC_STT_DEF_7_TO_8, &CDefectResult::OnStnClickedSttDef7To8)
	ON_STN_CLICKED(IDC_STT_DEF_7_TO_9, &CDefectResult::OnStnClickedSttDef7To9)
	ON_STN_CLICKED(IDC_STT_DEF_7_TO_10, &CDefectResult::OnStnClickedSttDef7To10)
	ON_STN_CLICKED(IDC_STT_DEF_8_TO_1, &CDefectResult::OnStnClickedSttDef8To1)
	ON_STN_CLICKED(IDC_STT_DEF_8_TO_2, &CDefectResult::OnStnClickedSttDef8To2)
	ON_STN_CLICKED(IDC_STT_DEF_8_TO_3, &CDefectResult::OnStnClickedSttDef8To3)
	ON_STN_CLICKED(IDC_STT_DEF_8_TO_4, &CDefectResult::OnStnClickedSttDef8To4)
	ON_STN_CLICKED(IDC_STT_DEF_8_TO_5, &CDefectResult::OnStnClickedSttDef8To5)
	ON_STN_CLICKED(IDC_STT_DEF_8_TO_6, &CDefectResult::OnStnClickedSttDef8To6)
	ON_STN_CLICKED(IDC_STT_DEF_8_TO_7, &CDefectResult::OnStnClickedSttDef8To7)
	ON_STN_CLICKED(IDC_STT_DEF_8_TO_8, &CDefectResult::OnStnClickedSttDef8To8)
	ON_STN_CLICKED(IDC_STT_DEF_8_TO_9, &CDefectResult::OnStnClickedSttDef8To9)
	ON_STN_CLICKED(IDC_STT_DEF_8_TO_10, &CDefectResult::OnStnClickedSttDef8To10)
	ON_STN_CLICKED(IDC_STT_DEF_9_TO_1, &CDefectResult::OnStnClickedSttDef9To1)
	ON_STN_CLICKED(IDC_STT_DEF_9_TO_2, &CDefectResult::OnStnClickedSttDef9To2)
	ON_STN_CLICKED(IDC_STT_DEF_9_TO_3, &CDefectResult::OnStnClickedSttDef9To3)
	ON_STN_CLICKED(IDC_STT_DEF_9_TO_4, &CDefectResult::OnStnClickedSttDef9To4)
	ON_STN_CLICKED(IDC_STT_DEF_9_TO_5, &CDefectResult::OnStnClickedSttDef9To5)
	ON_STN_CLICKED(IDC_STT_DEF_9_TO_6, &CDefectResult::OnStnClickedSttDef9To6)
	ON_STN_CLICKED(IDC_STT_DEF_9_TO_7, &CDefectResult::OnStnClickedSttDef9To7)
	ON_STN_CLICKED(IDC_STT_DEF_9_TO_8, &CDefectResult::OnStnClickedSttDef9To8)
	ON_STN_CLICKED(IDC_STT_DEF_9_TO_9, &CDefectResult::OnStnClickedSttDef9To9)
	ON_STN_CLICKED(IDC_STT_DEF_9_TO_10, &CDefectResult::OnStnClickedSttDef9To10)
	ON_STN_CLICKED(IDC_STT_DEF_10_TO_1, &CDefectResult::OnStnClickedSttDef10To1)
	ON_STN_CLICKED(IDC_STT_DEF_10_TO_2, &CDefectResult::OnStnClickedSttDef10To2)
	ON_STN_CLICKED(IDC_STT_DEF_10_TO_3, &CDefectResult::OnStnClickedSttDef10To3)
	ON_STN_CLICKED(IDC_STT_DEF_10_TO_4, &CDefectResult::OnStnClickedSttDef10To4)
	ON_STN_CLICKED(IDC_STT_DEF_10_TO_5, &CDefectResult::OnStnClickedSttDef10To5)
	ON_STN_CLICKED(IDC_STT_DEF_10_TO_6, &CDefectResult::OnStnClickedSttDef10To6)
	ON_STN_CLICKED(IDC_STT_DEF_10_TO_7, &CDefectResult::OnStnClickedSttDef10To7)
	ON_STN_CLICKED(IDC_STT_DEF_10_TO_8, &CDefectResult::OnStnClickedSttDef10To8)
	ON_STN_CLICKED(IDC_STT_DEF_10_TO_9, &CDefectResult::OnStnClickedSttDef10To9)
	ON_STN_CLICKED(IDC_STT_DEF_10_TO_10, &CDefectResult::OnStnClickedSttDef10To10)
	ON_BN_CLICKED(IDC_BTN_DEF_CONFIRM, &CDefectResult::OnBnClickedBtnDefConfirm)
	ON_BN_CLICKED(IDC_BTN_DEF_CANCEL, &CDefectResult::OnBnClickedBtnDefCancel)
	ON_BN_CLICKED(IDC_BTN_DEF_UNDO, &CDefectResult::OnBnClickedBtnDefUndo)
END_MESSAGE_MAP()


// CDefectResult 메시지 처리기


BOOL CDefectResult::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();

	Lf_initStaticButton();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDefectResult::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


BOOL CDefectResult::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_F4)
	{
		if (::GetKeyState(VK_MENU) < 0)	return TRUE;
	}

	// 일반 Key 동작에 대한 Event
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_F12:
		{
			m_pApp->Gf_writeMLog("<KEY> 'F12' Key push.");
			retReasonCode.Empty();
			CDialog::OnCancel();
			return 1;
		}
		case VK_ESCAPE:
		{
			m_pApp->Gf_writeMLog("<KEY> 'ESC' Key push.");
			Lf_setDefectUndo();
			return 1;
		}
		case VK_RETURN:
		{
			m_pApp->Gf_writeMLog("<KEY> 'Enter' Key push.");
			CDialog::OnOK();
			return 1;
		}
		case VK_SPACE:
		{
			m_pApp->Gf_writeMLog("<KEY> 'Space' Key push.");
			CDialog::OnOK();
			return 1;
		}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


HBRUSH CDefectResult::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		if (pWnd->GetDlgCtrlID() == IDC_STT_DEF_DETAIL)
		{
			pDC->SetBkColor(COLOR_BLACK);
			pDC->SetTextColor(COLOR_YELLOW);
			return m_Brush[COLOR_IDX_BLACK];
		}
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CDefectResult::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}

void CDefectResult::OnStnClickedSttDef1To1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(0, 0);
}


void CDefectResult::OnStnClickedSttDef1To2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(0, 1);
}


void CDefectResult::OnStnClickedSttDef1To3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(0, 2);
}


void CDefectResult::OnStnClickedSttDef1To4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(0, 3);
}


void CDefectResult::OnStnClickedSttDef1To5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(0, 4);
}


void CDefectResult::OnStnClickedSttDef1To6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(0, 5);
}


void CDefectResult::OnStnClickedSttDef1To7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(0, 6);
}


void CDefectResult::OnStnClickedSttDef1To8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(0, 7);
}


void CDefectResult::OnStnClickedSttDef1To9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(0, 8);
}


void CDefectResult::OnStnClickedSttDef1To10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(0, 9);
}


void CDefectResult::OnStnClickedSttDef2To1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(1, 0);
}


void CDefectResult::OnStnClickedSttDef2To2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(1, 1);
}


void CDefectResult::OnStnClickedSttDef2To3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(1, 2);
}


void CDefectResult::OnStnClickedSttDef2To4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(1, 3);
}


void CDefectResult::OnStnClickedSttDef2To5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(1, 4);
}


void CDefectResult::OnStnClickedSttDef2To6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(1, 5);
}


void CDefectResult::OnStnClickedSttDef2To7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(1, 6);
}


void CDefectResult::OnStnClickedSttDef2To8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(1, 7);
}


void CDefectResult::OnStnClickedSttDef2To9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(1, 8);
}


void CDefectResult::OnStnClickedSttDef2To10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(1, 9);
}


void CDefectResult::OnStnClickedSttDef3To1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(2, 0);
}


void CDefectResult::OnStnClickedSttDef3To2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(2, 1);
}


void CDefectResult::OnStnClickedSttDef3To3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(2, 2);
}


void CDefectResult::OnStnClickedSttDef3To4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(2, 3);
}


void CDefectResult::OnStnClickedSttDef3To5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(2, 4);
}


void CDefectResult::OnStnClickedSttDef3To6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(2, 5);
}


void CDefectResult::OnStnClickedSttDef3To7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(2, 6);
}


void CDefectResult::OnStnClickedSttDef3To8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(2, 7);
}


void CDefectResult::OnStnClickedSttDef3To9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(2, 8);
}


void CDefectResult::OnStnClickedSttDef3To10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(2, 9);
}


void CDefectResult::OnStnClickedSttDef4To1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(3, 0);
}


void CDefectResult::OnStnClickedSttDef4To2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(3, 1);
}


void CDefectResult::OnStnClickedSttDef4To3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(3, 2);
}


void CDefectResult::OnStnClickedSttDef4To4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(3, 3);
}


void CDefectResult::OnStnClickedSttDef4To5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(3, 4);
}


void CDefectResult::OnStnClickedSttDef4To6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(3, 5);
}


void CDefectResult::OnStnClickedSttDef4To7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(3, 6);
}


void CDefectResult::OnStnClickedSttDef4To8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(3, 7);
}


void CDefectResult::OnStnClickedSttDef4To9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(3, 8);
}


void CDefectResult::OnStnClickedSttDef4To10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(3, 9);
}


void CDefectResult::OnStnClickedSttDef5To1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(4, 0);
}


void CDefectResult::OnStnClickedSttDef5To2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(4, 1);
}


void CDefectResult::OnStnClickedSttDef5To3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(4, 2);
}


void CDefectResult::OnStnClickedSttDef5To4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(4, 3);
}


void CDefectResult::OnStnClickedSttDef5To5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(4, 4);
}


void CDefectResult::OnStnClickedSttDef5To6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(4, 5);
}


void CDefectResult::OnStnClickedSttDef5To7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(4, 6);
}


void CDefectResult::OnStnClickedSttDef5To8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(4, 7);
}


void CDefectResult::OnStnClickedSttDef5To9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(4, 8);
}


void CDefectResult::OnStnClickedSttDef5To10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(4, 9);
}


void CDefectResult::OnStnClickedSttDef6To1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(5, 0);
}


void CDefectResult::OnStnClickedSttDef6To2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(5, 1);
}


void CDefectResult::OnStnClickedSttDef6To3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(5, 2);
}


void CDefectResult::OnStnClickedSttDef6To4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(5, 3);
}


void CDefectResult::OnStnClickedSttDef6To5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(5, 4);
}


void CDefectResult::OnStnClickedSttDef6To6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(5, 5);
}


void CDefectResult::OnStnClickedSttDef6To7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(5, 6);
}


void CDefectResult::OnStnClickedSttDef6To8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(5, 7);
}


void CDefectResult::OnStnClickedSttDef6To9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(5, 8);
}


void CDefectResult::OnStnClickedSttDef6To10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(5, 9);
}


void CDefectResult::OnStnClickedSttDef7To1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(6, 0);
}


void CDefectResult::OnStnClickedSttDef7To2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(6, 1);
}


void CDefectResult::OnStnClickedSttDef7To3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(6, 2);
}


void CDefectResult::OnStnClickedSttDef7To4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(6, 3);
}


void CDefectResult::OnStnClickedSttDef7To5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(6, 4);
}


void CDefectResult::OnStnClickedSttDef7To6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(6, 5);
}


void CDefectResult::OnStnClickedSttDef7To7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(6, 6);
}


void CDefectResult::OnStnClickedSttDef7To8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(6, 7);
}


void CDefectResult::OnStnClickedSttDef7To9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(6, 8);
}


void CDefectResult::OnStnClickedSttDef7To10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(6, 9);
}


void CDefectResult::OnStnClickedSttDef8To1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(7, 0);
}


void CDefectResult::OnStnClickedSttDef8To2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(7, 1);
}


void CDefectResult::OnStnClickedSttDef8To3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(7, 2);
}


void CDefectResult::OnStnClickedSttDef8To4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(7, 3);
}


void CDefectResult::OnStnClickedSttDef8To5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(7, 4);
}


void CDefectResult::OnStnClickedSttDef8To6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(7, 5);
}


void CDefectResult::OnStnClickedSttDef8To7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(7, 6);
}


void CDefectResult::OnStnClickedSttDef8To8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(7, 7);
}


void CDefectResult::OnStnClickedSttDef8To9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(7, 8);
}


void CDefectResult::OnStnClickedSttDef8To10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(7, 9);
}


void CDefectResult::OnStnClickedSttDef9To1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(8, 0);
}


void CDefectResult::OnStnClickedSttDef9To2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(8, 1);
}


void CDefectResult::OnStnClickedSttDef9To3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(8, 2);
}


void CDefectResult::OnStnClickedSttDef9To4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(8, 3);
}


void CDefectResult::OnStnClickedSttDef9To5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(8, 4);
}


void CDefectResult::OnStnClickedSttDef9To6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(8, 5);
}


void CDefectResult::OnStnClickedSttDef9To7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(8, 6);
}


void CDefectResult::OnStnClickedSttDef9To8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(8, 7);
}


void CDefectResult::OnStnClickedSttDef9To9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(8, 8);
}


void CDefectResult::OnStnClickedSttDef9To10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(8, 9);
}


void CDefectResult::OnStnClickedSttDef10To1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(9, 0);
}


void CDefectResult::OnStnClickedSttDef10To2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(9, 1);
}


void CDefectResult::OnStnClickedSttDef10To3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(9, 2);
}


void CDefectResult::OnStnClickedSttDef10To4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(9, 3);
}


void CDefectResult::OnStnClickedSttDef10To5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(9, 4);
}


void CDefectResult::OnStnClickedSttDef10To6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(9, 5);
}


void CDefectResult::OnStnClickedSttDef10To7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(9, 6);
}


void CDefectResult::OnStnClickedSttDef10To8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(9, 7);
}


void CDefectResult::OnStnClickedSttDef10To9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(9, 8);
}


void CDefectResult::OnStnClickedSttDef10To10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_getButtonReasonCode(9, 9);
}


void CDefectResult::OnBnClickedBtnDefUndo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_setDefectUndo();
}

void CDefectResult::OnBnClickedBtnDefConfirm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}


void CDefectResult::OnBnClickedBtnDefCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	retReasonCode.Empty();
	CDialog::OnCancel();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDefectResult::Lf_InitLocalValue()
{
}

void CDefectResult::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	m_Font[1].CreateFont(52, 22, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	GetDlgItem(IDC_STT_DEF_DETAIL)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(32, 13, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	m_Font[3].CreateFont(23, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	GetDlgItem(IDC_BTN_DEF_UNDO)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_BTN_DEF_CONFIRM)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_BTN_DEF_CANCEL)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(17, 6, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
}

void CDefectResult::Lf_InitColorBrush()
{
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_Brush[COLOR_IDX_GRAY240].CreateSolidBrush(COLOR_GRAY240);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush(COLOR_GRAY64);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_GRAY224].CreateSolidBrush(COLOR_GRAY224);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
}

void CDefectResult::Lf_initStaticButton()
{
	CString fileName, strSection, strKey, strValue;

	Read_SysIniFile(_T("DFS"), _T("MODULE_DEFECT_INI"), &fileName);
	fileName.Insert(0, _T("./Module_Defect/"));
	strSection.Format(_T("SIMPLIFY"));

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			strKey.Format(_T("MATRIX(%d,%d)"), x + 1, y + 1);
			//Read_ProfileString(fileName, strSection, strKey, &strValue);
			Read_DefectIniFile(fileName, strSection, strKey, &strValue);

			if (strValue == _T(""))
			{
				m_pDefectButton[x][y].m_pButtonControl = Lf_getStaticControl(x, y);
				m_pDefectButton[x][y].m_sButtonName.Empty();
				m_pDefectButton[x][y].m_sButtonReasonCode.Empty();
				m_pDefectButton[x][y].m_ButtonColor = RGB(255, 255, 255);
			}
			else
			{
				m_pDefectButton[x][y].m_pButtonControl = Lf_getStaticControl(x, y);
				m_pDefectButton[x][y].m_sButtonName = Lf_getStaticButtonName(x, y, strValue);
				m_pDefectButton[x][y].m_sButtonReasonCode = Lf_getStaticReasonCode(x, y, strValue);
				m_pDefectButton[x][y].m_ButtonColor = Lf_getStaticButtonColor(x, y, strValue);

				m_pDefectButton[x][y].m_pButtonControl->SetWindowText(m_pDefectButton[x][y].m_sButtonName);
				m_pApp->Gf_setGradientStatic(m_pDefectButton[x][y].m_pButtonControl, m_pDefectButton[x][y].m_ButtonColor, RGB(0, 0, 0), &m_Font[4], 0);
			}
		}
	}
}

CGradientStatic* CDefectResult::Lf_getStaticControl(int x, int y)
{
	if (x == 0)
	{
		if (y == 0)	return &m_sttButton_1to1;
		if (y == 1)	return &m_sttButton_1to2;
		if (y == 2)	return &m_sttButton_1to3;
		if (y == 3)	return &m_sttButton_1to4;
		if (y == 4)	return &m_sttButton_1to5;
		if (y == 5)	return &m_sttButton_1to6;
		if (y == 6)	return &m_sttButton_1to7;
		if (y == 7)	return &m_sttButton_1to8;
		if (y == 8)	return &m_sttButton_1to9;
		if (y == 9)	return &m_sttButton_1to10;
	}
	else if (x == 1)
	{
		if (y == 0)	return &m_sttButton_2to1;
		if (y == 1)	return &m_sttButton_2to2;
		if (y == 2)	return &m_sttButton_2to3;
		if (y == 3)	return &m_sttButton_2to4;
		if (y == 4)	return &m_sttButton_2to5;
		if (y == 5)	return &m_sttButton_2to6;
		if (y == 6)	return &m_sttButton_2to7;
		if (y == 7)	return &m_sttButton_2to8;
		if (y == 8)	return &m_sttButton_2to9;
		if (y == 9)	return &m_sttButton_2to10;
	}
	else if (x == 2)
	{
		if (y == 0)	return &m_sttButton_3to1;
		if (y == 1)	return &m_sttButton_3to2;
		if (y == 2)	return &m_sttButton_3to3;
		if (y == 3)	return &m_sttButton_3to4;
		if (y == 4)	return &m_sttButton_3to5;
		if (y == 5)	return &m_sttButton_3to6;
		if (y == 6)	return &m_sttButton_3to7;
		if (y == 7)	return &m_sttButton_3to8;
		if (y == 8)	return &m_sttButton_3to9;
		if (y == 9)	return &m_sttButton_3to10;
	}
	else if (x == 3)
	{
		if (y == 0)	return &m_sttButton_4to1;
		if (y == 1)	return &m_sttButton_4to2;
		if (y == 2)	return &m_sttButton_4to3;
		if (y == 3)	return &m_sttButton_4to4;
		if (y == 4)	return &m_sttButton_4to5;
		if (y == 5)	return &m_sttButton_4to6;
		if (y == 6)	return &m_sttButton_4to7;
		if (y == 7)	return &m_sttButton_4to8;
		if (y == 8)	return &m_sttButton_4to9;
		if (y == 9)	return &m_sttButton_4to10;
	}
	else if (x == 4)
	{
		if (y == 0)	return &m_sttButton_5to1;
		if (y == 1)	return &m_sttButton_5to2;
		if (y == 2)	return &m_sttButton_5to3;
		if (y == 3)	return &m_sttButton_5to4;
		if (y == 4)	return &m_sttButton_5to5;
		if (y == 5)	return &m_sttButton_5to6;
		if (y == 6)	return &m_sttButton_5to7;
		if (y == 7)	return &m_sttButton_5to8;
		if (y == 8)	return &m_sttButton_5to9;
		if (y == 9)	return &m_sttButton_5to10;
	}
	else if (x == 5)
	{
		if (y == 0)	return &m_sttButton_6to1;
		if (y == 1)	return &m_sttButton_6to2;
		if (y == 2)	return &m_sttButton_6to3;
		if (y == 3)	return &m_sttButton_6to4;
		if (y == 4)	return &m_sttButton_6to5;
		if (y == 5)	return &m_sttButton_6to6;
		if (y == 6)	return &m_sttButton_6to7;
		if (y == 7)	return &m_sttButton_6to8;
		if (y == 8)	return &m_sttButton_6to9;
		if (y == 9)	return &m_sttButton_6to10;
	}
	else if (x == 6)
	{
		if (y == 0)	return &m_sttButton_7to1;
		if (y == 1)	return &m_sttButton_7to2;
		if (y == 2)	return &m_sttButton_7to3;
		if (y == 3)	return &m_sttButton_7to4;
		if (y == 4)	return &m_sttButton_7to5;
		if (y == 5)	return &m_sttButton_7to6;
		if (y == 6)	return &m_sttButton_7to7;
		if (y == 7)	return &m_sttButton_7to8;
		if (y == 8)	return &m_sttButton_7to9;
		if (y == 9)	return &m_sttButton_7to10;
	}
	else if (x == 7)
	{
		if (y == 0)	return &m_sttButton_8to1;
		if (y == 1)	return &m_sttButton_8to2;
		if (y == 2)	return &m_sttButton_8to3;
		if (y == 3)	return &m_sttButton_8to4;
		if (y == 4)	return &m_sttButton_8to5;
		if (y == 5)	return &m_sttButton_8to6;
		if (y == 6)	return &m_sttButton_8to7;
		if (y == 7)	return &m_sttButton_8to8;
		if (y == 8)	return &m_sttButton_8to9;
		if (y == 9)	return &m_sttButton_8to10;
	}
	else if (x == 8)
	{
		if (y == 0)	return &m_sttButton_9to1;
		if (y == 1)	return &m_sttButton_9to2;
		if (y == 2)	return &m_sttButton_9to3;
		if (y == 3)	return &m_sttButton_9to4;
		if (y == 4)	return &m_sttButton_9to5;
		if (y == 5)	return &m_sttButton_9to6;
		if (y == 6)	return &m_sttButton_9to7;
		if (y == 7)	return &m_sttButton_9to8;
		if (y == 8)	return &m_sttButton_9to9;
		if (y == 9)	return &m_sttButton_9to10;
	}
	else if (x == 9)
	{
		if (y == 0)	return &m_sttButton_10to1;
		if (y == 1)	return &m_sttButton_10to2;
		if (y == 2)	return &m_sttButton_10to3;
		if (y == 3)	return &m_sttButton_10to4;
		if (y == 4)	return &m_sttButton_10to5;
		if (y == 5)	return &m_sttButton_10to6;
		if (y == 6)	return &m_sttButton_10to7;
		if (y == 7)	return &m_sttButton_10to8;
		if (y == 8)	return &m_sttButton_10to9;
		if (y == 9)	return &m_sttButton_10to10;
	}

	return &m_sttButton_1to1;
}

CString CDefectResult::Lf_getStaticButtonName(int x, int y, CString strValue)
{
	CStringArray arrString;
	CString sdata = _T(""), strRtnValue = _T("");

	if (strValue.GetLength() == 0)
		return _T("");

	int nPos = 0;
	while (1)
	{
		arrString.Add(strValue.Tokenize(_T(","), nPos));
		if (nPos == -1)	break;
	}

	for (int i = 0; i < arrString.GetCount() - 4; i++)
	{
		sdata = arrString.GetAt(i);
		sdata.Delete(0, (sdata.Find(_T(">")) + 1));
		strRtnValue.Append(sdata.Mid((sdata.Find(_T("-")) + 1)));
		strRtnValue.Append(_T("-"));
	}

	// 마지막 하이픈(-)은 삭제한다.
	strRtnValue.Delete((strRtnValue.GetLength() - 1), 1);

	return strRtnValue;
}

CString CDefectResult::Lf_getStaticReasonCode(int x, int y, CString strValue)
{
	CStringArray arrString;
	CString sdata = _T(""), strRtnValue = _T("");

	if (strValue.GetLength() == 0)
		return _T("");

	int nPos = 0;
	while (1)
	{
		arrString.Add(strValue.Tokenize(_T(","), nPos));
		if (nPos == -1)	break;
	}

	for (int i = 0; i < arrString.GetCount() - 4; i++)
	{
		sdata = arrString.GetAt(i);
		sdata.Delete(0, (sdata.Find(_T(">")) + 1));
		strRtnValue.Append(sdata.Left(sdata.Find(_T("-"))));
		strRtnValue.Append(_T("-"));
	}

	// 마지막 하이픈(-)은 삭제한다.
	strRtnValue.Delete((strRtnValue.GetLength() - 1), 1);

	return strRtnValue;
}

long CDefectResult::Lf_getStaticButtonColor(int x, int y, CString strValue)
{
	CStringArray arrString;
	CString sdata = _T("");
	long longRtnValue;

	if (strValue.GetLength() == 0)
		return RGB(255, 255, 255);

	int nPos = 0;
	while (1)
	{
		arrString.Add(strValue.Tokenize(_T(","), nPos));
		if (nPos == -1)	break;
	}

	sdata = arrString.GetAt(arrString.GetCount() - 2);
	if (sdata.Left(1) != _T("$"))
		return RGB(255, 255, 255);

	sdata.Delete(0);
	longRtnValue = _tcstol(sdata, NULL, 16);

	return longRtnValue;
}

int CDefectResult::FindRWKField(CString strCode)
{
	char cTemp[10];
	CString strTemp;

	sprintf_s(cTemp, "%s", wchar_To_char(strCode.GetBuffer(0)));
	switch (cTemp[0])
	{
	case 'A':	return 0;
	case 'B':	return 1;
	case 'C':	return 2;
	case 'D':	return 3;
	case 'E':	return 4;
	case 'F':	return 5;
	case 'G':	return 6;
	case 'H':	return 7;
	case 'I':	return 6;	// 2014-05-22 PDH. I는 6으로 한다. 추가.
	case 'J':	return 8;
	case 'K':	return 9;
	case 'L':	return 10;
	case 'M':	return 11;
	case 'N':	return 12;
	case 'P':	return 13;
	case 'Q':	return 14;
	case 'R':	return 15;
	case 'S':	return 16;
	case 'T':	return 17;
	case 'U':	return 6;	// 2020-03-06 PDH. U코드 7번째자리 사용(LGD 김승진SY 요청)
	case 'V':	return 19;
	case 'W':	return 20;
	case 'X':	return 21;
	case 'Y':	return 22;
	case 'Z':	return 6;	// 2021-12-09 PDH. Z코드 7번째자리 사용(LGD 윤석진사원 요청)
	case '0':	return 24;
	case '1':	return 25;
	case '2':	return 6;	// 2019-05-31, 2는 6으로 한다
	case '3':	return 6;
	case '4':	return 6;
	case '5':	return 6;	// 2020-04-27. 숫자5 7번째자리 사용(LGD 김승진SY 요청)
	case '6':	return 30;
	case '7':	return 31;
	case '8':	return 32;
	case '9':	return 33;
	default:	return 0;
	}
}

#define	MAX_FIELD_STEP	10
#define	MAX_RWK_FILED	34
CString CDefectResult::GetRWKCodeToBadCode(CString strRWKCode[])
{
	CString	strBadCode = _T("");

	for (int i = 0; i < MAX_RWK_FILED; i++)	// RWK Field 34개로 고정.
	{
		if (strRWKCode[i] == "")
		{
			if (i == (MAX_RWK_FILED - 1))	break;	// 마지막 Filed Check. 마지막 Field 뒤에는 "-" 추가되지 않음.
			strBadCode += "-";
		}
		else
		{
			strBadCode += strRWKCode[i];
			if (i == (MAX_RWK_FILED - 1))	break;	// 마지막 Filed Check. 마지막 Field 뒤에는 "-" 추가되지 않음.
			strBadCode += "-";
		}
	}
	return strBadCode;
}

CString CDefectResult::BarCodeToBadCode(CString strBarCode)
{
	CString strRtnBadCode = _T("");
	CString strResult;
	CString strRWKField[MAX_RWK_FILED];
	int nField, nStart;

	if (strBarCode == _T("="))	return strBarCode;
	if (strBarCode == _T(""))	return _T("");
	nStart = strBarCode.Find(_T("-"), 0);
	if (nStart != -1)	// Find에서 해당 문자 못찾을 경우 -1 Return.
	{
		for (int i = 0; i < MAX_FIELD_STEP; i++)	// 조합Code Full Display일 경우 10Step까지 지원.
		{
			strResult = strBarCode.Mid(nStart - 3, 3);
			nField = FindRWKField(strResult);
			strRWKField[nField] = strResult;
			nStart = strBarCode.Find(_T("-"), nStart + 1);
			if (nStart == -1)
			{
				strResult = strBarCode.Mid(strBarCode.GetLength() - 3, 3);
				nField = FindRWKField(strResult);
				strRWKField[nField] = strResult;
				break;
			}
		}
		strRtnBadCode = GetRWKCodeToBadCode(strRWKField);
	}
	else
	{
		strRtnBadCode.Format(_T("ERROR"));
	}

	return strRtnBadCode;
}


void CDefectResult::Lf_getButtonReasonCode(int x, int y)
{
	// Button에 할당된 이름이나 Reason Code가 없을 경우 Return 시킨다.
	if ((m_pDefectButton[x][y].m_sButtonName == _T("")) || (m_pDefectButton[x][y].m_sButtonReasonCode == _T("")))
		return;

	// 이전 선택 Button의 색상을 원상태로 복구시킨다.
	if ((preX != -1) && (preY != -1) && ((preX != x) || (preY != y)))
	{
		m_pApp->Gf_setGradientStatic(m_pDefectButton[preX][preY].m_pButtonControl, m_pDefectButton[preX][preY].m_ButtonColor, RGB(0, 0, 0), &m_Font[4], 0);
		m_pDefectButton[preX][preY].m_pButtonControl->Invalidate(FALSE);
		m_pDefectButton[preX][preY].m_pButtonControl->SetWindowText(m_pDefectButton[preX][preY].m_sButtonName);
	}

	// 상단에 선택한 불량 상세정보를 Display 한다.
	GetDlgItem(IDC_STT_DEF_DETAIL)->SetWindowText(m_pDefectButton[x][y].m_sButtonName);

	// 선택된 Button의 색상을 변경한다.
	m_pApp->Gf_setGradientStatic(m_pDefectButton[x][y].m_pButtonControl, RGB(127, 0, 0), RGB(255, 255, 255), &m_Font[4], 0);
	m_pDefectButton[x][y].m_pButtonControl->Invalidate(FALSE);
	m_pDefectButton[x][y].m_pButtonControl->SetWindowText(m_pDefectButton[x][y].m_sButtonName);

	// Return할 Reason Code 값을 저장한다.
	retReasonCode.Format(_T("%s"), BarCodeToBadCode(m_pDefectButton[x][y].m_sButtonReasonCode));

	preX = x;
	preY = y;
}

void CDefectResult::Lf_setDefectUndo()
{
	// 이전 선택 Button의 색상을 원상태로 복구시킨다.
	if ((preX != -1) && (preY != -1))
	{
		m_pApp->Gf_setGradientStatic(m_pDefectButton[preX][preY].m_pButtonControl, m_pDefectButton[preX][preY].m_ButtonColor, RGB(0, 0, 0), &m_Font[4], 0);
		m_pDefectButton[preX][preY].m_pButtonControl->Invalidate(FALSE);
		m_pDefectButton[preX][preY].m_pButtonControl->SetWindowText(m_pDefectButton[preX][preY].m_sButtonName);
	}

	// 상단에 선택한 불량 상세정보를 Clear 한다.
	GetDlgItem(IDC_STT_DEF_DETAIL)->SetWindowText(_T(""));

	// Return할 Reason Code 값을 Clear 한다.
	retReasonCode.Empty();
}

CString CDefectResult::GetWRK_CD()
{
	return retReasonCode;
}