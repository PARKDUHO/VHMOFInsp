#pragma once

using namespace std;
//#import "C:\TibDriver_32bit_x86\ModuleECS_CommTibRV64.tlb" no_namespace, named_guids //no_namespace	//#import "C:\TibDriver_32bit_x86\MES_EAS_x86.tlb" no_namespace, named_guids //no_namespace
#import "C:\TibDriver_64bit_x64\MES_EAS_DLL.tlb" no_namespace, named_guids //no_namespace 

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#define RTN_OK						0
#define RTN_MSG_NOT_SEND			1
#define RTN_RCV_TIMEOUT				5

#define ECS_WAIT_TIME				5000	// 5Sec

#define	ECS_MODE_EAYT				0x01
#define	ECS_MODE_UCHK				0x02
#define	ECS_MODE_EDTI				0x03
#define	ECS_MODE_PCHK				0x04
#define	ECS_MODE_IISQ				0x05
#define	ECS_MODE_EICR				0x06
#define	ECS_MODE_BICD				0x07
#define	ECS_MODE_SCLR				0x08
#define	ECS_MODE_EESR				0x09
#define	ECS_MODE_EEER				0x0A
#define	ECS_MODE_EQCC				0x0B
#define	ECS_MODE_FLDR				0x0C
#define	ECS_MODE_EPCR				0x0D
#define ECS_MODE_AGN_IN				0x0E
#define ECS_MODE_EICR_ABNORMAL		0x0F
#define	ECS_MODE_MSET				0x10
#define	ECS_MODE_MILT				0x11
#define ECS_MODE_APDR				0x12
#define ECS_MODE_WDCR				0x13
#define	ECS_MODE_RPLT				0x14
#define	ECS_MODE_LPIR				0x15
#define	ECS_MODE_RPRQ				0x16
#define	ECS_MODE_SCRA				0x17
#define ECS_MODE_BDCR				0x18
#define ECS_MODE_AGN_INSP			0x19
#define ECS_MODE_INSP_INFO			0x1A
#define ECS_MODE_PINF				0x1B
#define ECS_MODE_AGN_CTR			0x1C
#define ECS_MODE_APTR				0x1D
#define	ECS_MODE_SCRP				0x1E
#define ECS_MODE_PPSET				0x1F
#define ECS_MODE_POIR				0x20

#define UTC_ZONE_VIETNAM			0x00
#define UTC_ZONE_CHINA				0x01
#define UTC_ZONE_KOREA				0x02


class CCimNetCommApi
{
public:
	CCimNetCommApi(void);
	~CCimNetCommApi(void);

	ICallGmesClass *gmes;
	ICallEASClass *eas;

	CLSID			clsid_ECS;
	HRESULT			hr;

	// ----------------------------------------
	void Cim_WriteMLog(CString strSection, CString strData);

	BOOL Init(int nServerType);
	BOOL ConnectTibRv(int nServerType);
	BOOL CloseTibRv(int nServerType);
	INT64 GetbytesSent(CString strIPadress);
	INT64 GetbytesReceived(CString strIPadress);
	BOOL MessageSend(int nMode);
	BOOL MessageReceive();

	BOOL GetFieldData(CString* pszSource, CString wszToken, int nMode=0);
	CString GetHostSendMessage();
	CString GetHostRecvMessage();

	void getLocalSubjectIPAddress();

	// ----------------------------------------
	// ---------------------------------------
	// ----------------------------------------
	BOOL EAYT ();
	BOOL UCHK ();
	BOOL EDTI ();
	BOOL PCHK (int ipa_mode=FALSE, int ipa_value=FALSE);
	// ----------------------------------------
	BOOL EPCR ();
	// ----------------------------------------

	BOOL IISQ ();
	BOOL EICR ();
	BOOL RPLT (int station);
	BOOL RPRQ(int station);
	BOOL SCRA(int station);
	BOOL SCRP(int station);
	BOOL MSET ();

	BOOL EICR_Abnormal ();
	BOOL APDR ();
	BOOL MILT ();
	BOOL WDCR ();

	BOOL FLDR ();

	// ---------------------------------------
	BOOL BICD (char * pszBuff);
	BOOL SCLR ();
	BOOL EESR ();
	BOOL EEER ();
	BOOL EQCC ();
	BOOL AGN_IN ();
	BOOL AGN_INSP ();
	BOOL LPIR();
	BOOL BDCR();
	BOOL INSP_INFO();
	BOOL PINF();
	BOOL AGN_CTR();
	BOOL APTR();
	BOOL POIR();

	// ---------------------------------------
	void SetLocalTest(int nServerType);

	// ---------------------------------------
	void MakeClientTimeString();
	void SetMesHostInterface();
	void SetEasHostInterface();
	void SetLocalTimeZone(int timeZone);
	void SetLocalTimeData(CString strTime);
	void SetMachineName(CString strBuff);
	void SetUserId (CString strBuff);
	void SetComment (CString strBuff);
	void SetAgingChangeTime (CString strBuff);
	void SetAptrAgingTime(CString strBuff);
	void SetRemark (CString strBuff);
	void SetNGPortOut (CString strBuff);
	void SetRwkCode(CString strBuff);
	void SetFLDRFileName(CString strBuff);
	void SetPanelID(CString strBuff);
	void SetBLID(CString strBuff);
	void SetSerialNumber(CString strBuff);
	void SetModelName(CString strBuff);
	void SetPalletID(CString strBuff);
	void SetPF(CString strBuff);
	void SetDefectPattern(CString strBuff);
	void SetPvcomAdjustValue(CString strBuff);
	void SetPvcomAdjustDropValue(CString strBuff);
	void SetPatternInfo(CString strBuff);
	void SetEdidStatus(CString strBuff);
	void SetOverHaulFlag(CString strBuff);
	void SetBaExiFlag(CString strBuff);
	void SetBuyerSerialNo(CString strBuff);
	void SetVthValue(CString strBuff);
	void SetBDInfo(CString strBuff);
	void SetWDRInfo(CString strBuff);
	void SetWDREnd(CString strBuff);
	void SetAPDInfo(CString strBuff);
	void SetDefectCommentCode(CString strBuff);
	void SetFullYN(CString strBuff);
	void SetGibCode(CString strBuff);
	void SetToOper(CString strBuff);
	CString GetToOper();
	void SetRepairCD(CString strBuff);
	void SetRespDept(CString strBuff);
	void SetMaterialInfo(CString strBuff);
	void SetSSFlag(CString strBuff);
	void SetFromOper(CString strBuff);
	void SetTACT(CString strBuff);
	void SetRepairTypeCD(CString strBuff);
	void SetAutoRespDeptFlag(CString strBuff);
	void SetAgingLevelInfo(CString strBuff);
	void SetPOIRProcessCode(CString strBuff);
	void SetPOIRActFlag(CString strBuff);

	// ---------------------------------------
	CString GetRwkCode();
	CString GetPF();
	CString GetComment();
	CString GetMachineName();




protected:
	BOOL	m_bIsGmesLocalTestMode;
	BOOL	m_bIsEasLocalTestMode;


	CString m_strLocalSubjectIP;
	CString m_strLocalSubjectMesF;
	CString m_strLocalSubjectEasF;

	CString m_strRemoteSubject;
	CString m_strLocalSubject;
	CString m_strNetwork;
	CString m_strServicePort;
	CString m_strDaemon;
	CString m_strLocalIP;

	CString m_strRemoteSubjectEAS;
	CString m_strLocalSubjectEAS;
	CString m_strNetworkEAS;
	CString m_strServicePortEAS;
	CString m_strDaemonEAS;
	CString m_strLocalIPEAS;

	CString m_strNgComment;

	CString m_strClientDate;
	CString m_strClientOldDate;
	CString m_strClientNewDate;

	CString m_strMachineName;
	CString m_strUserID;
	CString m_strComment;
	CString m_strAgingChangeTime;
	CString m_strAptrAgingTime;
	CString m_strRemark;
	CString m_strNGPortOut;
	CString m_strRwkCode;
	CString m_strSSFlag;
	CString m_strFLDRFileName;
	CString m_strPanelID;
	CString m_strFrom_Oper;
	CString m_strBLID;
	CString m_strSerialNumber;
	CString m_strModelName;
	CString m_strPalletID;
	CString m_strPF;
	CString m_strDefectPattern;
	CString m_strPvcomAdjustValue;
	CString m_strPvcomAdjustDropValue;
	CString m_strPatternInfo;
	CString m_strEdidStatus;
	CString m_strOverHaulFlag;
	CString m_strExpectedRwk;
	CString m_strBaExiFlag;
	CString m_strBuyerSerialNo;
	CString m_strVthValue;
	CString m_strBDInfo;
	CString m_strWDRInfo;
	CString m_strWDREnd;
	CString m_strAPDInfo;
	CString m_strFullYN;
	CString m_strGibCode;
	CString m_strToOper;
	CString m_strRepairCD;
	CString m_strRespDept;
	CString m_strMaterialInfo;
	CString m_strTactTime;
	CString m_strRepairTypeCD;
	CString m_strAutoRespDeptFlag;
	CString m_strAgingLevelInfo;
	CString m_strPOIRProcessCode;
	CString m_strPOIRActFlag;


	CString m_strHostSendMessage;
	CString m_strHostRecvMessage;
	CString m_strEAYT;
	CString m_strUCHK;
	CString m_strEDTI;
	CString m_strFLDR;
	CString m_strPCHK;
	CString m_strEICR;
	CString m_strRPLT;
	CString m_strMSET;
	CString m_strAGN_IN;
	CString m_strAGN_INSP;
	CString m_strAPDR;
	CString m_strWDCR;
	CString m_strLPIR;
	CString m_strRPRQ;
	CString m_strSCRA;
	CString m_strSCRP;
	CString m_strBDCR;
	CString m_strINSP_INFO;
	CString m_strPINF;
	CString m_strAGN_CTR;
	CString m_strAPTR;
	CString m_strPOIR;

	CString m_strDefectComCode;

};
