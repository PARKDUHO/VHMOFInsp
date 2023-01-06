
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


// CVHMOFInspApp:
// 이 클래스의 구현에 대해서는 VHMOFInsp.cpp을(를) 참조하세요.
//

class CVHMOFInspApp : public CWinApp
{
public:
	CVHMOFInspApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
public:
	void Gf_writeMLog(char* szLogData);
	void Gf_writeMLog(CString sLogData);
	BOOL Gf_ShowMessageBox(int msg_type, CString strTitle, int ErrorCode, CString AppendMessage=_T(""));

	void Gf_setGradientStatic(CGradientStatic* pGStt, long bkColor1, long bkColor2, long fontColor, CFont* pFont, BOOL bSplit);

	BOOL Gf_LoadSystemData();
	BOOL Gf_LoadModelFile();

	// Global GMES Function
	BOOL Gf_gmesInitServer(BOOL nServerType);
	BOOL Gf_gmesConnect(int nServerType);
	BOOL Gf_gmesDisConnect(int nServerType);
	void Gf_setGMesGoodInfo();
	void Gf_setGMesBGradeInfo();
	void Gf_setGMesBadInfo();
	CString Gf_getGmesRTNCD();
	void Gf_showLocalErrorMsg();
	BOOL Gf_sendGmesHost(int nHostCmd);


	void Gf_setStartPtnLockTime(int nPtnNum);
	void Gf_setEndPtnLockTime(int nPtnNum);
	void Gf_setPatStartCheckTime(int i);
	void Gf_setPatEndCheckTime(int i);

	BOOL main_tcpProcessPacket(int ch, char* recvPacket);
	void main_parse_AreYouReady(int ch, char* recvPacket);
	void main_parse_PowerMeasureAll(int ch, char* recvPacket);
	void main_parse_FirmwareVersion(int ch, char* recvPacket);
	void main_parse_GoToBootSection(int ch, char* recvPacket);

	LPMODELINFO				GetModelInfo();
	LPSYSTEMINFO			GetSystemInfo();
	LPINSPWORKINFO			GetInspWorkInfo();
	CPatternView*			m_pPatternView;

	CSocketTcpApp*			m_pSocketTCPAppCh1;
	CSocketTcpApp*			m_pSocketDIO;
	CSocketTcpApp*			m_pSocketTCPMain;
	CCommApi* commApi;
	CCimNetCommApi*			m_pCimNet;

	HANDLE					m_hAppMutex;

	// Initialize Status
	BOOL m_bPgConnectStatus[2];
	BOOL m_bSpiConnectStatus[2];
	BOOL m_bDio7230Init;

	CStatic* m_pStaticMainLog;
	CString m_sLoginUserID;
	CString m_sLoginUserName;
	BOOL m_bUserIdGieng;
	BOOL m_bUserIdPM;

	// MES Status
	BOOL m_bMesComuCheck;
	BOOL m_bIsGmesConnect;
	BOOL m_bIsEasConnect;


	// Firmware Version
	CString m_sQspiFWVersion[MAX_CH];
	CString m_sPgFWVersion[MAX_CH];
	CString m_sSwVersion;

	// Firmware Download
	int	m_nDownloadReadyAckCount;
	int	m_nDownloadCountUp;

	int m_nSLockTime, m_nELockTime, m_nPtnLockTime[PTN_LIST_MAX], m_nPatLock[PTN_LIST_MAX];
	int m_nStartCheckTime[PTN_LIST_MAX], m_nEndCheckTime[PTN_LIST_MAX], m_nPatTime[PTN_LIST_MAX];


protected:
	LPMODELINFO				lpModelInfo;
	LPSYSTEMINFO			lpSystemInfo;
	LPINSPWORKINFO			lpInspWorkInfo;

	BOOL Lf_FindModelFile();
	void Lf_parsingModFileData(CString szData, TCHAR(*szParseData)[255]);
	void Lf_LoadModelData(CString modelName);

	// Local MES Function
	void Lf_setGmesValueEICR();
	void Lf_setEasValueAPDR();
	void Lf_setGmesValuePCHK();
	CString Lf_getGmesPatternData();

private:

	
/////////////////////////////////////////////////////////////////////////////

};

extern CVHMOFInspApp theApp;
extern CVHMOFInspApp* m_pApp;