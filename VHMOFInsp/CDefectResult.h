#pragma once


// CDefectResult 대화 상자
struct DEFECT_BUTTON
{
	CGradientStatic* m_pButtonControl;
	CString m_sButtonName;
	CString m_sButtonReasonCode;
	COLORREF m_ButtonColor;
};


class CDefectResult : public CDialog
{
	DECLARE_DYNAMIC(CDefectResult)

public:
	CDefectResult(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDefectResult();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEFECT_RESULT };
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

	void Lf_initStaticButton();
	CGradientStatic* Lf_getStaticControl(int x, int y);
	CString Lf_getStaticButtonName(int x, int y, CString strValue);
	CString Lf_getStaticReasonCode(int x, int y, CString strValue);
	long Lf_getStaticButtonColor(int x, int y, CString strValue);

	void Lf_getButtonReasonCode(int x, int y);

	int FindRWKField(CString strCode);
	CString GetRWKCodeToBadCode(CString strRWKCode[]);
	CString BarCodeToBadCode(CString strBarCode);

	void Lf_setDefectUndo();

	CString GetWRK_CD();
	CString retReasonCode;


protected:
	DEFECT_BUTTON m_pDefectButton[10][10];

	int preX, preY;


private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];

	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////





public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CGradientStatic m_sttButton_1to1;
	CGradientStatic m_sttButton_1to2;
	CGradientStatic m_sttButton_1to3;
	CGradientStatic m_sttButton_1to4;
	CGradientStatic m_sttButton_1to5;
	CGradientStatic m_sttButton_1to6;
	CGradientStatic m_sttButton_1to7;
	CGradientStatic m_sttButton_1to8;
	CGradientStatic m_sttButton_1to9;
	CGradientStatic m_sttButton_1to10;
	CGradientStatic m_sttButton_2to1;
	CGradientStatic m_sttButton_2to2;
	CGradientStatic m_sttButton_2to3;
	CGradientStatic m_sttButton_2to4;
	CGradientStatic m_sttButton_2to5;
	CGradientStatic m_sttButton_2to6;
	CGradientStatic m_sttButton_2to7;
	CGradientStatic m_sttButton_2to8;
	CGradientStatic m_sttButton_2to9;
	CGradientStatic m_sttButton_2to10;
	CGradientStatic m_sttButton_3to1;
	CGradientStatic m_sttButton_3to2;
	CGradientStatic m_sttButton_3to3;
	CGradientStatic m_sttButton_3to4;
	CGradientStatic m_sttButton_3to5;
	CGradientStatic m_sttButton_3to6;
	CGradientStatic m_sttButton_3to7;
	CGradientStatic m_sttButton_3to8;
	CGradientStatic m_sttButton_3to9;
	CGradientStatic m_sttButton_3to10;
	CGradientStatic m_sttButton_4to1;
	CGradientStatic m_sttButton_4to2;
	CGradientStatic m_sttButton_4to3;
	CGradientStatic m_sttButton_4to4;
	CGradientStatic m_sttButton_4to5;
	CGradientStatic m_sttButton_4to6;
	CGradientStatic m_sttButton_4to7;
	CGradientStatic m_sttButton_4to8;
	CGradientStatic m_sttButton_4to9;
	CGradientStatic m_sttButton_4to10;
	CGradientStatic m_sttButton_5to1;
	CGradientStatic m_sttButton_5to2;
	CGradientStatic m_sttButton_5to3;
	CGradientStatic m_sttButton_5to4;
	CGradientStatic m_sttButton_5to5;
	CGradientStatic m_sttButton_5to6;
	CGradientStatic m_sttButton_5to7;
	CGradientStatic m_sttButton_5to8;
	CGradientStatic m_sttButton_5to9;
	CGradientStatic m_sttButton_5to10;
	CGradientStatic m_sttButton_6to1;
	CGradientStatic m_sttButton_6to2;
	CGradientStatic m_sttButton_6to3;
	CGradientStatic m_sttButton_6to4;
	CGradientStatic m_sttButton_6to5;
	CGradientStatic m_sttButton_6to6;
	CGradientStatic m_sttButton_6to7;
	CGradientStatic m_sttButton_6to8;
	CGradientStatic m_sttButton_6to9;
	CGradientStatic m_sttButton_6to10;
	CGradientStatic m_sttButton_7to1;
	CGradientStatic m_sttButton_7to2;
	CGradientStatic m_sttButton_7to3;
	CGradientStatic m_sttButton_7to4;
	CGradientStatic m_sttButton_7to5;
	CGradientStatic m_sttButton_7to6;
	CGradientStatic m_sttButton_7to7;
	CGradientStatic m_sttButton_7to8;
	CGradientStatic m_sttButton_7to9;
	CGradientStatic m_sttButton_7to10;
	CGradientStatic m_sttButton_8to1;
	CGradientStatic m_sttButton_8to2;
	CGradientStatic m_sttButton_8to3;
	CGradientStatic m_sttButton_8to4;
	CGradientStatic m_sttButton_8to5;
	CGradientStatic m_sttButton_8to6;
	CGradientStatic m_sttButton_8to7;
	CGradientStatic m_sttButton_8to8;
	CGradientStatic m_sttButton_8to9;
	CGradientStatic m_sttButton_8to10;
	CGradientStatic m_sttButton_9to1;
	CGradientStatic m_sttButton_9to2;
	CGradientStatic m_sttButton_9to3;
	CGradientStatic m_sttButton_9to4;
	CGradientStatic m_sttButton_9to5;
	CGradientStatic m_sttButton_9to6;
	CGradientStatic m_sttButton_9to7;
	CGradientStatic m_sttButton_9to8;
	CGradientStatic m_sttButton_9to9;
	CGradientStatic m_sttButton_9to10;
	CGradientStatic m_sttButton_10to1;
	CGradientStatic m_sttButton_10to2;
	CGradientStatic m_sttButton_10to3;
	CGradientStatic m_sttButton_10to4;
	CGradientStatic m_sttButton_10to5;
	CGradientStatic m_sttButton_10to6;
	CGradientStatic m_sttButton_10to7;
	CGradientStatic m_sttButton_10to8;
	CGradientStatic m_sttButton_10to9;
	CGradientStatic m_sttButton_10to10;
	afx_msg void OnStnClickedSttDef1To1();
	afx_msg void OnStnClickedSttDef1To2();
	afx_msg void OnStnClickedSttDef1To3();
	afx_msg void OnStnClickedSttDef1To4();
	afx_msg void OnStnClickedSttDef1To5();
	afx_msg void OnStnClickedSttDef1To6();
	afx_msg void OnStnClickedSttDef1To7();
	afx_msg void OnStnClickedSttDef1To8();
	afx_msg void OnStnClickedSttDef1To9();
	afx_msg void OnStnClickedSttDef1To10();
	afx_msg void OnStnClickedSttDef2To1();
	afx_msg void OnStnClickedSttDef2To2();
	afx_msg void OnStnClickedSttDef2To3();
	afx_msg void OnStnClickedSttDef2To4();
	afx_msg void OnStnClickedSttDef2To5();
	afx_msg void OnStnClickedSttDef2To6();
	afx_msg void OnStnClickedSttDef2To7();
	afx_msg void OnStnClickedSttDef2To8();
	afx_msg void OnStnClickedSttDef2To9();
	afx_msg void OnStnClickedSttDef2To10();
	afx_msg void OnStnClickedSttDef3To1();
	afx_msg void OnStnClickedSttDef3To2();
	afx_msg void OnStnClickedSttDef3To3();
	afx_msg void OnStnClickedSttDef3To4();
	afx_msg void OnStnClickedSttDef3To5();
	afx_msg void OnStnClickedSttDef3To6();
	afx_msg void OnStnClickedSttDef3To7();
	afx_msg void OnStnClickedSttDef3To8();
	afx_msg void OnStnClickedSttDef3To9();
	afx_msg void OnStnClickedSttDef3To10();
	afx_msg void OnStnClickedSttDef4To1();
	afx_msg void OnStnClickedSttDef4To2();
	afx_msg void OnStnClickedSttDef4To3();
	afx_msg void OnStnClickedSttDef4To4();
	afx_msg void OnStnClickedSttDef4To5();
	afx_msg void OnStnClickedSttDef4To6();
	afx_msg void OnStnClickedSttDef4To7();
	afx_msg void OnStnClickedSttDef4To8();
	afx_msg void OnStnClickedSttDef4To9();
	afx_msg void OnStnClickedSttDef4To10();
	afx_msg void OnStnClickedSttDef5To1();
	afx_msg void OnStnClickedSttDef5To2();
	afx_msg void OnStnClickedSttDef5To3();
	afx_msg void OnStnClickedSttDef5To4();
	afx_msg void OnStnClickedSttDef5To5();
	afx_msg void OnStnClickedSttDef5To6();
	afx_msg void OnStnClickedSttDef5To7();
	afx_msg void OnStnClickedSttDef5To8();
	afx_msg void OnStnClickedSttDef5To9();
	afx_msg void OnStnClickedSttDef5To10();
	afx_msg void OnStnClickedSttDef6To1();
	afx_msg void OnStnClickedSttDef6To2();
	afx_msg void OnStnClickedSttDef6To3();
	afx_msg void OnStnClickedSttDef6To4();
	afx_msg void OnStnClickedSttDef6To5();
	afx_msg void OnStnClickedSttDef6To6();
	afx_msg void OnStnClickedSttDef6To7();
	afx_msg void OnStnClickedSttDef6To8();
	afx_msg void OnStnClickedSttDef6To9();
	afx_msg void OnStnClickedSttDef6To10();
	afx_msg void OnStnClickedSttDef7To1();
	afx_msg void OnStnClickedSttDef7To2();
	afx_msg void OnStnClickedSttDef7To3();
	afx_msg void OnStnClickedSttDef7To4();
	afx_msg void OnStnClickedSttDef7To5();
	afx_msg void OnStnClickedSttDef7To6();
	afx_msg void OnStnClickedSttDef7To7();
	afx_msg void OnStnClickedSttDef7To8();
	afx_msg void OnStnClickedSttDef7To9();
	afx_msg void OnStnClickedSttDef7To10();
	afx_msg void OnStnClickedSttDef8To1();
	afx_msg void OnStnClickedSttDef8To2();
	afx_msg void OnStnClickedSttDef8To3();
	afx_msg void OnStnClickedSttDef8To4();
	afx_msg void OnStnClickedSttDef8To5();
	afx_msg void OnStnClickedSttDef8To6();
	afx_msg void OnStnClickedSttDef8To7();
	afx_msg void OnStnClickedSttDef8To8();
	afx_msg void OnStnClickedSttDef8To9();
	afx_msg void OnStnClickedSttDef8To10();
	afx_msg void OnStnClickedSttDef9To1();
	afx_msg void OnStnClickedSttDef9To2();
	afx_msg void OnStnClickedSttDef9To3();
	afx_msg void OnStnClickedSttDef9To4();
	afx_msg void OnStnClickedSttDef9To5();
	afx_msg void OnStnClickedSttDef9To6();
	afx_msg void OnStnClickedSttDef9To7();
	afx_msg void OnStnClickedSttDef9To8();
	afx_msg void OnStnClickedSttDef9To9();
	afx_msg void OnStnClickedSttDef9To10();
	afx_msg void OnStnClickedSttDef10To1();
	afx_msg void OnStnClickedSttDef10To2();
	afx_msg void OnStnClickedSttDef10To3();
	afx_msg void OnStnClickedSttDef10To4();
	afx_msg void OnStnClickedSttDef10To5();
	afx_msg void OnStnClickedSttDef10To6();
	afx_msg void OnStnClickedSttDef10To7();
	afx_msg void OnStnClickedSttDef10To8();
	afx_msg void OnStnClickedSttDef10To9();
	afx_msg void OnStnClickedSttDef10To10();
	afx_msg void OnBnClickedBtnDefConfirm();
	afx_msg void OnBnClickedBtnDefCancel();
	afx_msg void OnBnClickedBtnDefUndo();
};
