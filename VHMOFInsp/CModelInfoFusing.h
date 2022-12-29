﻿#pragma once


// CModelInfoFusing 대화 상자

class CModelInfoFusing : public CDialogEx
{
	DECLARE_DYNAMIC(CModelInfoFusing)

public:
	CModelInfoFusing(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CModelInfoFusing();

// 대화 상자 데이터입니다.
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_INFO_FUSING };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()



///////////////////////////////////////////////////////////////////////////
// 사용자 정의 Function
///////////////////////////////////////////////////////////////////////////
public:
	void Gf_DataSaveModelFusing(CString modelName);

protected:
	LPMODELINFO		lpModelInfo;
	LPSYSTEMINFO	lpSystemInfo;

	void Lf_InitLocalValue();
	void Lf_InitFontset();
	void Lf_InitColorBrush();

	void Lf_calcHorResolution();
	void Lf_calcVerResolution();
	void Lf_calcVSync();

	void Lf_updateSequenceText(int index);
	void Lf_InitDialogControl();
	void Lf_loadPatternListToCombo();

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];
	CFont* m_pDefaultFont;

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////



public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CEdit m_edtMfVcc;
	CEdit m_edtMfVccOffset;
	CEdit m_edtMfVel;
	CEdit m_edtMfVelOffset;
	CEdit m_edtMfLimitVccLow;
	CEdit m_edtMfLimitVccHigh;
	CEdit m_edtMfLimitVelLow;
	CEdit m_edtMfLimitVelHigh;
	CEdit m_edtMfLimitIccLow;
	CEdit m_edtMfLimitIccHigh;
	CEdit m_edtMfLimitIelLow;
	CEdit m_edtMfLimitIelHigh;
	CComboBox m_cmbMfPowerOnSeq1;
	CComboBox m_cmbMfPowerOnSeq2;
	CComboBox m_cmbMfPowerOnSeq3;
	CComboBox m_cmbMfPowerOnSeq4;
	CComboBox m_cmbMfPowerOnSeq5;
	CComboBox m_cmbMfPowerOnSeq6;
	CEdit m_edtMfPowerOnDelay1;
	CEdit m_edtMfPowerOnDelay2;
	CEdit m_edtMfPowerOnDelay3;
	CEdit m_edtMfPowerOnDelay4;
	CEdit m_edtMfPowerOnDelay5;
	CEdit m_edtMfPowerOnDelay6;
	CComboBox m_cmbMfPowerOffSeq1;
	CComboBox m_cmbMfPowerOffSeq2;
	CComboBox m_cmbMfPowerOffSeq3;
	CComboBox m_cmbMfPowerOffSeq4;
	CComboBox m_cmbMfPowerOffSeq5;
	CComboBox m_cmbMfPowerOffSeq6;
	CEdit m_edtMfPowerOffDelay1;
	CEdit m_edtMfPowerOffDelay2;
	CEdit m_edtMfPowerOffDelay3;
	CEdit m_edtMfPowerOffDelay4;
	CEdit m_edtMfPowerOffDelay5;
	CEdit m_edtMfPowerOffDelay6;
	CComboBox m_cmbMfSignalType;
	CComboBox m_cmbMfPixel;
	CComboBox m_cmbMfSignalBit;
	CComboBox m_cmbMfRotate;
	CComboBox m_cmbMfBitSelect;
	CComboBox m_cmbMfFrsMode;
	CEdit m_edtMfClockDelay;
	CEdit m_edtMfTimingFrequency;
	CEdit m_edtMfTimingVSync;
	CEdit m_edtMfTimingHorTotal;
	CEdit m_edtMfTimingHorActive;
	CEdit m_edtMfTimingHorWidth;
	CEdit m_edtMfTimingHorBackPorch;
	CEdit m_edtMfTimingHorFrontPorch;
	CEdit m_edtMfTimingVerTotal;
	CEdit m_edtMfTimingVerActive;
	CEdit m_edtMfTimingVerWidth;
	CEdit m_edtMfTimingVerBackPorch;
	CEdit m_edtMfTimingVerFrontPorch;
	afx_msg void OnEnChangeEdtMfTimingFreq();
	afx_msg void OnEnChangeEdtMfTimingHorActive();
	afx_msg void OnEnChangeEdtMfTimingHorWidth();
	afx_msg void OnEnChangeEdtMfTimingHorBp();
	afx_msg void OnEnChangeEdtMfTimingHorFp();
	afx_msg void OnEnChangeEdtMfTimingVerActive();
	afx_msg void OnEnChangeEdtMfTimingVerWidth();
	afx_msg void OnEnChangeEdtMfTimingVerBp();
	afx_msg void OnEnChangeEdtMfTimingVerFp();
};