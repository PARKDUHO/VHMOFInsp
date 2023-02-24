#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//
#include "_GlobalDefine.h"

typedef struct _ST_MODELINFO_{

	float	m_fPowerVcc;
	float	m_fPowerVccOffset;
	float	m_fPowerVel;
	float	m_fPowerVelOffset;
	float	m_fPowerVdd;
	float	m_fPowerVddOffset;

	float	m_fLimitVccLow;
	float	m_fLimitVccHigh;
	float	m_fLimitVelLow;
	float	m_fLimitVelHigh;
	float	m_fLimitVddLow;
	float	m_fLimitVddHigh;
	int		m_nLimitIccLow;
	int		m_nLimitIccHigh;
	int		m_nLimitIelLow;
	int		m_nLimitIelHigh;
	int		m_nLimitIddLow;
	int		m_nLimitIddHigh;

	int		m_nPowerOnSeq1;
	int		m_nPowerOnSeq2;
	int		m_nPowerOnSeq3;
	int		m_nPowerOnSeq4;
	int		m_nPowerOnSeq5;
	int		m_nPowerOnSeq6;
	int		m_nPowerOnSeq7;
	int		m_nPowerOnSeq8;
	int		m_nPowerOnSeq9;
	int		m_nPowerOnSeq10;
	int		m_nPowerOnSeq11;
	int		m_nPowerOnSeq12;
	int		m_nPowerOnSeq13;
	int		m_nPowerOnDelay1;
	int		m_nPowerOnDelay2;
	int		m_nPowerOnDelay3;
	int		m_nPowerOnDelay4;
	int		m_nPowerOnDelay5;
	int		m_nPowerOnDelay6;
	int		m_nPowerOnDelay7;
	int		m_nPowerOnDelay8;
	int		m_nPowerOnDelay9;
	int		m_nPowerOnDelay10;
	int		m_nPowerOnDelay11;
	int		m_nPowerOnDelay12;
	int		m_nPowerOnDelay13;
	int		m_nPowerOffSeq1;
	int		m_nPowerOffSeq2;
	int		m_nPowerOffSeq3;
	int		m_nPowerOffSeq4;
	int		m_nPowerOffSeq5;
	int		m_nPowerOffSeq6;
	int		m_nPowerOffSeq7;
	int		m_nPowerOffSeq8;
	int		m_nPowerOffSeq9;
	int		m_nPowerOffSeq10;
	int		m_nPowerOffSeq11;
	int		m_nPowerOffSeq12;
	int		m_nPowerOffSeq13;
	int		m_nPowerOffDelay1;
	int		m_nPowerOffDelay2;
	int		m_nPowerOffDelay3;
	int		m_nPowerOffDelay4;
	int		m_nPowerOffDelay5;
	int		m_nPowerOffDelay6;
	int		m_nPowerOffDelay7;
	int		m_nPowerOffDelay8;
	int		m_nPowerOffDelay9;
	int		m_nPowerOffDelay10;
	int		m_nPowerOffDelay11;
	int		m_nPowerOffDelay12;
	int		m_nPowerOffDelay13;

	int		m_nSignalType;
	int		m_nPixelType;
	int		m_nSignalBit;
	int		m_nSignalRotate;
	int		m_nBitSelect;
	int		m_nFrsMode;
	int		m_nClockDelay;
	int		m_nInitScript;

	float	m_fTimingFrequency;
	int		m_nTimingHorTotal;
	int		m_nTimingHorActive;
	int		m_nTimingHorWidth;
	int		m_nTimingHorFrontPorch;
	int		m_nTimingHorBackPorch;
	int		m_nTimingVerTotal;
	int		m_nTimingVerActive;
	int		m_nTimingVerWidth;
	int		m_nTimingVerFrontPorch;
	int		m_nTimingVerBackPorch;

	int		m_nMainBoardLED;

	int		m_nI2cPullUp;
	int		m_nI2cLevel;
	int		m_nI2cClock;

	int		m_nSpiPullUp;
	int		m_nSpiLevel;
	int		m_nSpiClock;

	int		m_nGpioPullUp;
	int		m_nGpioLevel;
	int		m_nGpio1Output;
	int		m_nGpio2Output;
	int		m_nGpio3Output;
	int		m_nGio1Setting;
	int		m_nGio2Setting;
	int		m_nGio3Setting;
	int		m_nGio4Setting;

	int		m_nPwmFrequency;
	int		m_nPwmDuty;
	int		m_nPwmLevel;

	int		m_nCableOpenCheck;
	int		m_nJigTiltingCheck;

	int		m_nPatternListCount;
	CString	m_sLbPtnListNAME[PTN_LIST_MAX];
	CString	m_sLbPtnListVCC[PTN_LIST_MAX];
	CString	m_sLbPtnListVEL[PTN_LIST_MAX];
	CString	m_sLbPtnListICC[PTN_LIST_MAX];
	CString	m_sLbPtnListIEL[PTN_LIST_MAX];
	CString	m_sLbPtnListLockTime[PTN_LIST_MAX];
	CString	m_sLbPtnListMaxTIME[PTN_LIST_MAX];
	CString	m_sLbPtnListVSYNC[PTN_LIST_MAX];
	CString	m_sLbPtnListONOFF[PTN_LIST_MAX];

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
// 	int		m_nEdidUse;
// 	int		m_nEdidLine;
// 	int		m_nEdidAddress;
// 	WORD	m_nEdidChecksum;
// 	int		m_nEdidData;
// 
// 	int		m_nWriteProtect;		// Bit Select
// 
// 	int		m_nI2cDelay;


}MODELINFO, *LPMODELINFO;


typedef struct _ST_SYSTEMINFO_{
	// STATION 정보 설정 //
	CString m_sEqpName;					// EQP NAME
	int		m_nLineType;
	int		m_nCarrierType;

	// MELSEC 정보 설정 //
	int		m_nEcsOnLineMode;
	int		m_nLBStartAddr;
	int		m_nLWStartAddr1;
	int		m_nLWStartAddr2;
	int		m_nEcsEqpNumber;
	int		m_nRobotInspUnitNumber;
	int		m_nRobotLBStartAddr;
	int		m_nRobotLWStartAddr1;

	CString	m_sLastModelName;			// 마지막 M/C 모델명
	int		m_nQuantityOKTotal;
	int		m_nQuantityNGTotal;
	int		m_nQuantityOKCh1;
	int		m_nQuantityNGCh1;
	int		m_nQuantityOKCh2;
	int		m_nQuantityNGCh2;

	// MES 정보 설정 //
	CString m_sMesServicePort;
	CString m_sMesNetWork;
	CString m_sMesDaemonPort;
	CString m_sMesLocalSubject;
	CString m_sMesRemoteSubject;
	CString m_sMesLocalIP;

	// EAS 정보 설정 //
	int		m_nEasUse;
	CString m_sEasServicePort;
	CString m_sEasNetWork;
	CString m_sEasDaemonPort;
	CString m_sEasLocalSubject;
	CString m_sEasRemoteSubject;

	// DFS 정보 설정 //
	int		m_nDfsUse;
	CString m_sDfsIPAddress;
	CString m_sDfsUserId;
	CString m_sDfsPassword;

	// DATA FILE Download 설정 //
	CString m_sDataFileModel;
	CString m_sDataFilePattern;
	CString m_sDataFileEdid;

	// HOT KEY 설정 //
	CString m_sHotKeyPattern[HOTKEY_LIST_MAX];

	// Gray Level 가변STEP 설정
	int		m_nGrayLevelUp;
	int		m_nGrayLevelDown;
	int		m_nGrayLevelLeft;
	int		m_nGrayLevelRight;

}SYSTEMINFO, *LPSYSTEMINFO;


typedef struct _ST_INSPWORKINFO_{
	char  m_szPalletID[20];				// 현재 도착 Pallet 정보.
	char  m_szPanelID[20];				// 현재 검사중인 Panel ID의 정보
	char  m_szSerialNum[50];			// 현재 검사중인 Panel의 Serial Number정보
	char  m_szFirmwareVer[50];			// 현재 검사중인 Main Board의 Firmware Version 정보
	char  m_szFpgaMainVer[10];			// 현재 검사중인 FPGA의 Firmware Version 정보
	char  m_szFpgaIFVer[10];			// 현재 검사중인 FPGA의 Firmware Version 정보
	char  m_szPowerFwVer[10];			// 현재 검사중인 POWER Module의 Firmware Version 정보
	int   m_nCurPatternIdx;				// 현재 검사중인 Pattern의 Index 정보
	char  m_szBadPattern[50];			// 불량패턴명
	char  m_szReasonCode[100];			// 불량코드
	int   m_nPanelJudgeResult;			// 불량 판정 결과
	char  m_szHostTopModelName[50];		// MES에서 내려받은 Top Model Name 정보

	char  m_szExtInputPID1[20];			// CH1 외부에서 입력된 임시 Panel ID. (BCR 또는 PID 입력 UI)
	char  m_szExtInputPID2[20];			// CH1 외부에서 입력된 임시 Panel ID. (BCR 또는 PID 입력 UI)

	char  m_szPLTModelName[50];
	char  m_szPLTPalletID[50];
	char  m_szPLTPanelID[50];
	char  m_szLPIRProcessCode[50];

	BOOL  m_bAreYouReady;
	BOOL  bPowerOnOffStatus;		// LCM Power OnOff 상태
	bool  bPowerOnOffCheck;			// LCM Power OnOff 검사 완료 Flag
	DWORD nTickPatternStart[PTN_LIST_MAX];	// Pattern Start Time
	DWORD nTickPatternEnd[PTN_LIST_MAX];		// Pattern End Time
	DWORD nPatternTestTime[PTN_LIST_MAX];		// Pattern별 검사 횟수
	int   nPatternTestCount[PTN_LIST_MAX];	// Pattern별 검사 횟수
	int   nCheckShortTestResult;	// Short Test Result
	int   nCheckShortTestValue;		// Short Test Value
	int   nCheckCableOpenComplete;	// Cable Open Check 검사여부
	UINT  nCheckCableOpenResult;	// Cable Open Result
	int   nCheckCableOpenValue;		// Cable Open Value
	int   nMeasVCC;					// VDD : mV 단위
	int   nMeasVEL;					// ELVDD : mV 단위
	int   nMeasICC;					// IVDD : mA 단위
	int   nMeasIEL;					// IELVDD : mA 단위
	int   nMeasErrName;				// 0:VDD, 1:ELVDD, 2:I_VDD, 3:I_ELVDD
	int   nMeasErrResult;			// 0:Normal, 1:Low, 2:High
	int   nMeasErrValue;			// Error Value : 1/1000V, 1/1000A 단위
	int   nGioReadInfo[4];			// GIO PIN Read Value

	int   tt_MachineTactTime;		// 1Cycle TactTime
	int   tt_FrontDoorUpTime;		// Front Door Up Time
	int   tt_FrontDoorDownTime;		// Front Door Down Time
	int   tt_RearDoorUpTime;		// Rear Door Up Time
	int   tt_RearDoorDownTime;		// Rear Door Down Time
	int   tt_JigTiltingUpTime;		// JIG Tilting Up Time
	int   tt_JigTiltingDownTime;	// JIG Tilting Down Time

	char  def_INSPTIME_START[30];	// 검사 시작 시간(YYYYMMDDHHMMSS)
	char  def_INSPTIME_END[30];		// 검사 종료 시간(YYYYMMDDHHMMSS)
	char  def_PROC_ID[20];			// 검사 공정 번호
	char  def_MACHINE_ID[50];		// 검사기 MACHINE ID
	char  def_finalJudge[10];		// Defect File JUDGE 입력 정보
	char  def_finalReasonCode[100]; // Defect File Reason Code
	char  def_finalReason[100];		// Defect File Reason 입력 정보
	char  def_workYYYYMMDD[10];		// 착공시간 (년월일)
	char  def_workHHMMSS[10];		// 착공시간 (시분초)
	char  def_inputDFS[10];			// 검사 시작 DFS판정 ※ Defect File Loading時 기존 기록된 JUDGE_INFO > LATEST > JUDGE 값
	char  def_inputJudge[10];		// 검사 시작 DFS VS MES 판정 우선순위  ※ Defect File 최초기록시 MES로 부터 받은 판정 기록(1자리로)
	char  def_inputReason[10];		// 검사 시작 불량코드(DFS VS MES 판정 우선순위의 불량코드) ※ Defect File 최초기록시 MES로 부터 받은 불량코드 기록
	int	  def_TotalSTEP;			// DEFECT_NO의 TOTAL STEP 정보
	int   def_TotalNEW;				// 현 공정에서 추가된 DEFECT 갯수

	char  smf_TotalInput;			// Summary File 정보. 전수입력
	char  smf_InspDay[20];			// Summary File 정보. 검사날짜
	char  smf_OperatorID[20];		// Summary File 정보. 검사자
	char  smf_EQPName[20];			// Summary File 정보. 검사호기(EQPNAME)
	char  smf_ModelName[30];		// Summary File 정보. 모델(RECIPE)
	char  smf_FPGAVersion[10];		// Summary File 정보. FPGA_VERSION
	int   smf_PROCCount;			// Summary File 정보. 해당공정진행횟수
	int   smf_ORTAfterInspCount;	// Summary File 정보. ORT전_공정진행횟수
	int   smf_ORTBeforeInspCount;	// Summary File 정보. ORT후_공정진행횟수
	int   smf_ProcessNumber;		// Summary File 정보. 공정번호
	char  smf_ORTStatus;			// Summary File 정보. ORT이력
	char  smf_MESJudge;				// Summary File 정보. MES JUDGE
	char  smf_DefectFileJudge[10];	// Summary File 정보. Defect File Judge
	char  smf_PanelReason[200];		// Summary File 정보. PNL REASON
	char  smf_DefectCode[4096];		// Summary File 정보. 불량코드명1 ~ 50
	char  smf_DefectFileName[100];	// Summary File 정보. DEFECT FILE명
	char  smf_DefectInfo[1024*16];	// Summary File 정보. DEFECT INFO

	BOOL  m_bEscDetect;
	BOOL  m_bIsEdidFail;

	// Power Measure
	int	m_nMeasureVCC[2];
	int m_nMeasureVEL[2];
	int m_nMeasureVDD[2];
	int m_nMeasureICC[2];
	int m_nMeasureIEL[2];
	int m_nMeasureIDD[2];
	int m_nMeasureErrName[2];
	int m_nMeasureErrCh[2];
	int m_nMeasureErrValue[2];

	// Fimrware(Main, FPGA, Power) Download
	BYTE  m_nSRunnerStatus;
	BYTE  m_nPmmAck;
	char  m_nSRunnerReadBuf[1024];

	// SW Version
	char  m_szSoftwareVer[200];

}INSPWORKINFO, *LPINSPWORKINFO;


enum
{
	SUM_DATE = 0,
	SUM_CH,
	SUM_PM_MES,
	SUM_SW_VER,
	SUM_FW_VER,
	SUM_MODEL,
	SUM_EQP_ID,
	SUM_PID,
	SUM_PASS_FAIL,
	SUM_RWK_CD,
	SUM_TACT_TIME,
	SUM_START_TIME,
	SUM_END_TIME,
	SUM_INFO_MAX
};

typedef struct _ST_SUMMARY_
{
	CString	m_sumData[SUM_INFO_MAX];

} SUMMARYINFO, * LPSUMMARYINFO;


// ★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
// ★                                   주의                                     ★
// ★ Glass Data는 Memory Copy로 Data가 넘어가므로 변수 순서를 변경하면 안된다.  ★
// ★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
typedef struct _ST_ECSGLASSDATA_
{
	DWORD LOT_ID[8];
	DWORD ProcessingCode[4];
	DWORD LOT_AddData[4];
	DWORD RecipeNumber;
	DWORD PanelType;
	DWORD PanelCODE;
	DWORD PanelID[8];
	DWORD PanelJudge;
	DWORD PanelAddData[4];
	DWORD PreviousUnitProcessingData[8];
	DWORD PanelProcessingStatus[8];
	DWORD MeterialID[15];
	DWORD MeterialType;
} ECSGLASSDATA, * LPECSGLASSDATA;
