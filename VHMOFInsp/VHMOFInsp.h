
// VHMOFInsp.h: PROJECT_NAME 애플리케이션에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.

#include "PatternView.h"
#include "SocketTCP.h"
#include "SocketTCPApp.h"
#include "SocketUDP.h"
#include "CIMNetCommApp.h"
#include "MelsecnetG.h"


// CVHMOFInspApp:
// 이 클래스의 구현에 대해서는 VHMOFInsp.cpp을(를) 참조하세요.
//

class CVHMOFInspApp : public CWinApp
{
public:
	CVHMOFInspApp();
	virtual ~CVHMOFInspApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
public:
	void Gf_SoftwareStartLog();
	void Gf_SoftwareEndLog();

	void Gf_writeMLog(char* szLogData);
	void Gf_writeMLog(CString sLogData);
	void Gf_writeSummaryLog(int ch);
	BOOL Gf_ShowMessageBox(int msg_type, CString strTitle, int ErrorCode, CString AppendMessage=_T(""));
	void Gf_QtyCountUp(int ok_ng);
	void Gf_QtyCountReset();

	void Gf_setGradientStatic(CGradientStatic* pGStt, long bkColor1, long bkColor2, long fontColor, CFont* pFont, BOOL bSplit);
	void Gf_setGradientStatic(CGradientStatic* pGStt, long bkColor, long fontColor, CFont* pFont, BOOL bSplit);

	BOOL Gf_LoadSystemData();
	BOOL Gf_LoadModelFile();

	BOOL Gf_FindModelFile(CString modelName);
	void Gf_LoadModelData(CString modelName);

	// Global GMES Function
	BOOL Gf_gmesInitServer(BOOL nServerType);
	BOOL Gf_gmesConnect(int nServerType);
	BOOL Gf_gmesDisConnect(int nServerType);
	void Gf_gmesSetGoodInfo();
	void Gf_gmesSetBadInfo();
	CString Gf_gmesGetRTNCD();
	void Gf_gmesShowLocalErrorMsg();
	BOOL Gf_gmesSendHost(int nHostCmd);


	void Gf_setStartPtnLockTime(int nPtnNum);
	void Gf_setEndPtnLockTime(int nPtnNum);
	void Gf_setPatStartCheckTime(int i);
	void Gf_setPatEndCheckTime(int i);

	// TCP/IP 통신 Protocol (Main Board)
	BOOL main_tcpProcessPacket(int ch, char* recvPacket);
	void main_parse_AreYouReady(int ch, char* recvPacket);
	void main_parse_PowerMeasureAll(int ch, char* recvPacket);
	void main_parse_CableOpenCheck(int ch, char* recvPacket);
	void main_parse_GioControl(int ch, char* recvPacket);
	void main_parse_FirmwareVersion(int ch, char* recvPacket);
	void main_parse_GoToBootSection(int ch, char* recvPacket);


	// UDP 통신 Protocol (DIO Board)
	void Lf_initCreateUdpSocket();
	BOOL Lf_initLocalHostIPAddress();
	BOOL udp_sendPacketUDP_DIO(int ch, int target, int nID, int nCommand, int nSize, char* pdata, int recvACK = ACK, int waitTime = 1000);
	BOOL udp_procWaitRecvACK_DIO(int ch, int cmd, DWORD waitTime);
	void udp_processDioPacket(int ch, CString strPacket);
	BOOL udp_procParseDIO(int ch, CString packet);

	// DIO InterLock
	BOOL Lf_checkDoorOpenInterLock();

	// MELSEC Function
	int Lf_getMelsecErrorCode(int mnetg_err);


	LPMODELINFO				GetModelInfo();
	LPSYSTEMINFO			GetSystemInfo();
	LPINSPWORKINFO			GetInspWorkInfo();
	CPatternView*			m_pPatternView;

	CSocketTcpApp*			m_pSocketTCPSpi;
	CSocketTcpApp*			m_pSocketTCPMain;
	CSocketUDP*				m_pUDPSocket;
	CCommApi* commApi;
	CCimNetCommApi*			m_pCimNet;
	CMelsecnetG*			pMelsecnetG;

	HANDLE					m_hAppMutex;

	// Software Version
	CString m_sSoftwareVersion;

	// Initialize Status
	CStatic* m_pStaticMainLog;
	CString m_sLoginUserID;
	CString m_sLoginUserName;
	BOOL m_bUserIdGieng;
	BOOL m_bUserIdPM;

	// DIO Board Data
	int m_nAckCmdDio[2];
	BYTE m_nDioOutBit[2][3];	// 2CH, 24Bit(3Byte) 선언이다.
	BYTE m_nDioInBit[2][5];		// 2CH, 40Bit(5Byte) 선언이다.

	// MES Status
	BOOL m_bMesComuCheck;
	BOOL m_bIsGmesConnect;
	BOOL m_bIsEasConnect;
	BOOL m_bIsSendEAYT;

	// Connect Status
	BOOL bConnectInfo[CONN_MAX];

	// Firmware Version
	CString m_sQspiFWVersion[MAX_CH];
	CString m_sPgFWVersion[MAX_CH];
	CString m_sSwVersion;

	// Firmware Download
	int	m_nDownloadReadyAckCount;
	int	m_nDownloadCountUp;

	// START/END Time
	CTime tt_startTime;
	CTime tt_endTime;


	int m_nSLockTime, m_nELockTime, m_nPtnLockTime[PTN_LIST_MAX], m_nPatLock[PTN_LIST_MAX];
	int m_nStartCheckTime[PTN_LIST_MAX], m_nEndCheckTime[PTN_LIST_MAX], m_nPatTime[PTN_LIST_MAX];


protected:
	LPMODELINFO				lpModelInfo;
	LPSYSTEMINFO			lpSystemInfo;
	LPINSPWORKINFO			lpInspWorkInfo;
	SUMMARYINFO				m_summaryInfo;

	void Lf_initGlobalVariable();
	void Lf_parsingModFileData(CString szData, TCHAR(*szParseData)[255]);

	// Local MES Function
	void Lf_gmesSetValueEICR();
	void Lf_gmesSetValueAPDR();
	void Lf_gmesSetValuePCHK();
	CString Lf_gmesGetPatternData();

private:

	
/////////////////////////////////////////////////////////////////////////////

};

extern CVHMOFInspApp theApp;
extern CVHMOFInspApp* m_pApp;