#pragma once

#include "afxcmn.h"
#include "afxwin.h"
#include "CModelInfoData.h"
#include "CModelInfoFusing.h"

#define	FUSING_READY		0
#define FUSING_OK			1
#define FUSING_NG			2

// CModelInfo 대화 상자

class CModelInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CModelInfo)

public:
	CModelInfo(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CModelInfo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()



///////////////////////////////////////////////////////////////////////////
// 사용자 정의 Function
///////////////////////////////////////////////////////////////////////////
public:
	void Lf_InitLocalValue();
	void Lf_InitFontset();
	void Lf_InitColorBrush();
	void Lf_InitDlgDesign();

	void Lf_InitTabControl();
	void Lf_saveModel();
	void Lf_HostModelFileSave();

	void Lf_systemFusing();

	BOOL m_bSaved;
	int  m_nTabSelect;

protected:
	LPMODELINFO			lpModelInfo;
	LPSYSTEMINFO		lpSystemInfo;

	CModelInfoData* m_pModelInfoData;
	CModelInfoFusing* m_pModelInfoFusing;

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];

	int m_bFusingResult[MAX_CH];

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////



public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CXTabCtrl m_tabModelInfo;
	CButton m_btnMiFusing;
	CButton m_btnMiSaveExit;
	CButton m_btnMiCancel;
	CEdit m_edtMiSaveModelName;
	afx_msg void OnBnClickedBtnMiSaveExit();
	afx_msg void OnBnClickedBtnMiCancel();
	afx_msg void OnBnClickedBtnMiFusing();
};
