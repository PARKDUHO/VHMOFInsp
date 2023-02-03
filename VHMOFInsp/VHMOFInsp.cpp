
// VHMOFInsp.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "VHMOFInsp.h"
#include "VHMOFInspDlg.h"
#include "CMessageError.h"
#include "CMessageQuestion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVHMOFInspApp

BEGIN_MESSAGE_MAP(CVHMOFInspApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CVHMOFInspApp 생성

CVHMOFInspApp::CVHMOFInspApp()
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
	m_pApp = (CVHMOFInspApp*)AfxGetApp();
	lpModelInfo			= new MODELINFO;
	lpSystemInfo		= new SYSTEMINFO;
	lpInspWorkInfo		= new INSPWORKINFO;
	m_pPatternView		= new CPatternView();
	m_pSocketTCPMain	= new CSocketTcpApp;		// TCP Socket Class 생성(Main Board 1)(22.12.08)
	m_pSocketTCPSpi		= new CSocketTcpApp;
	m_pUDPSocket		= new CSocketUDP;
	commApi				= new CCommApi;
	m_pCimNet			= new CCimNetCommApi;
	pMelsecnetG			= new CMelsecnetG;


	m_pStaticMainLog = NULL;
}

CVHMOFInspApp::~CVHMOFInspApp()
{

}


// 유일한 CVHMOFInspApp 개체입니다.

CVHMOFInspApp theApp;
CVHMOFInspApp* m_pApp;


// CVHMOFInspApp 초기화

BOOL CVHMOFInspApp::InitInstance()
{
	//프로그램 중복 실행 방지
	m_hAppMutex = CreateMutex(NULL, TRUE, _T("IT_OLED"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(m_hAppMutex);
		AfxMessageBox(_T("VH MOFI Program is running!!!"));
		return FALSE;
	}

	// 소켓 초기화
	if (!AfxSocketInit())
	{
		AfxMessageBox(_T("AfxSocket Initialize fail"));
		return FALSE;
	}

	// 애플리케이션 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 대화 상자에 셸 트리 뷰 또는
	// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	CShellManager *pShellManager = new CShellManager;

	// MFC 컨트롤의 테마를 사용하기 위해 "Windows 원형" 비주얼 관리자 활성화
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 애플리케이션 마법사에서 생성된 애플리케이션"));

	//////////////////////////////////////////////////////////////////
	Gf_SoftwareStartLog();					// 프로그램 시작 LOG 기록
	//////////////////////////////////////////////////////////////////

	Gf_LoadSystemData();
	Lf_initGlobalVariable();
	Gf_LoadModelFile();
	Lf_initCreateUdpSocket();

	// GMES DLL Initialize
	if (Gf_gmesInitServer(SERVER_MES) == FALSE)
	{
		AfxMessageBox(_T("TIB Driver Init Fail.\r\nPlease check whether you have installed the TibDriver and registered the MES DLL."), MB_ICONERROR);
	}
	if (Gf_gmesInitServer(SERVER_EAS) == FALSE)
	{
		AfxMessageBox(_T("TIB Driver Init Fail.\r\nPlease check whether you have installed the TibDriver and registered the MES DLL."), MB_ICONERROR);
	}

	CVHMOFInspDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, _T("경고: 대화 상자를 만들지 못했으므로 애플리케이션이 예기치 않게 종료됩니다.\n"));
		TRACE(traceAppMsg, 0, _T("경고: 대화 상자에서 MFC 컨트롤을 사용하는 경우 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS를 수행할 수 없습니다.\n"));
	}

	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고 응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LPMODELINFO CVHMOFInspApp::GetModelInfo()
{
	ASSERT(NULL != lpModelInfo);
	VERIFY(NULL != lpModelInfo);

	return lpModelInfo;
}

LPSYSTEMINFO CVHMOFInspApp::GetSystemInfo()
{
	ASSERT(NULL != lpSystemInfo);
	VERIFY(NULL != lpSystemInfo);

	return lpSystemInfo;
}

LPINSPWORKINFO CVHMOFInspApp::GetInspWorkInfo()
{
	ASSERT(NULL != lpInspWorkInfo);
	VERIFY(NULL != lpInspWorkInfo);

	return lpInspWorkInfo;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global Variable Init
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CVHMOFInspApp::Lf_initGlobalVariable()
{
	Read_SysIniFile(_T("DIO"), _T("CH1_OUT_DATA1"), &m_pApp->m_nDioOutBit[CH1][0]);
	Read_SysIniFile(_T("DIO"), _T("CH1_OUT_DATA2"), &m_pApp->m_nDioOutBit[CH1][1]);
	Read_SysIniFile(_T("DIO"), _T("CH1_OUT_DATA3"), &m_pApp->m_nDioOutBit[CH1][2]);

	Read_SysIniFile(_T("DIO"), _T("CH2_OUT_DATA1"), &m_pApp->m_nDioOutBit[CH2][0]);
	Read_SysIniFile(_T("DIO"), _T("CH2_OUT_DATA2"), &m_pApp->m_nDioOutBit[CH2][1]);
	Read_SysIniFile(_T("DIO"), _T("CH2_OUT_DATA3"), &m_pApp->m_nDioOutBit[CH2][2]);

	ZeroMemory(bConnectInfo, sizeof(bConnectInfo));
	ZeroMemory(lpInspWorkInfo, sizeof(INSPWORKINFO));

	m_bIsSendEAYT = FALSE;
	m_bSafetyDlgOpen = FALSE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CVHMOFInspApp::Gf_SoftwareStartLog()
{
	Read_SysIniFile(_T("SYSTEM"), _T("EQP_NAME"), &lpSystemInfo->m_sEqpName);

	// Main Form Title Set
	CString strPGMTitle;
	char D_String[15] = { 0, };
	char Date_String[15] = { 0, };
	char* Date[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	sprintf_s(D_String, "%s", __DATE__);
	for (int i = 12; i; i--)
	{
		for (int j = 3; j; j--)
		{
			if (D_String[j - 1] != *(Date[i - 1] + (j - 1)))
				break;
			if (j == 1)
			{
				if (D_String[4] == 0x20)	D_String[4] = 0x30;
				sprintf_s(Date_String, "%c%c%c%c/%02d/%c%c", D_String[7], D_String[8], D_String[9], D_String[10], i, D_String[4], D_String[5]);
				i = 1; j = 1;
				break;
			}
		}
	}

	m_sSoftwareVersion.Format(_T("%s"), char_To_wchar(Date_String));
	strPGMTitle.Format(_T("VH Medium OLED ( %s )"), m_sSoftwareVersion);

	CString sLog;
	sLog.Format(_T("***************************** %s *****************************"), strPGMTitle);
	Gf_writeMLog(sLog);
}

void CVHMOFInspApp::Gf_SoftwareEndLog()
{
	CString sLog;
	sLog.Format(_T("*****************************************************************************************"));
	Gf_writeMLog(sLog);
}

void CVHMOFInspApp::Gf_writeMLog(char* szLogData)
{
	CString sLog;
	sLog.Format(_T("%S"), szLogData);

	Gf_writeMLog(sLog);
}

void CVHMOFInspApp::Gf_writeMLog(CString sLogData)
{
	CFile file;
	USHORT nShort = 0xfeff;
	CString strFileName, strLog, path;

	// 엔터 Key 값이 있으면 문자를 변경 시키낟.
	sLogData.Replace(_T("\r\n"), _T(" | "));

	SYSTEMTIME sysTime;
	::GetSystemTime(&sysTime);
	CTime time = CTime::GetCurrentTime();
	strLog.Format(_T("[%02d:%02d:%02d %03d] %06d%03d\t: %s\r\n"), time.GetHour(), time.GetMinute(), time.GetSecond(), sysTime.wMilliseconds, (time.GetHour() * 3600) + (time.GetMinute() * 60) + time.GetSecond(), sysTime.wMilliseconds, sLogData);


	strFileName.Format(_T("%s_%04d%02d%02d"), lpSystemInfo->m_sEqpName, time.GetYear(), time.GetMonth(), time.GetDay());
	path.Format(_T(".\\Logs\\MLog\\%s.txt"), strFileName);

	if ((_access(".\\Logs", 0)) == -1)
		_mkdir(".\\Logs");

	if ((_access(".\\Logs\\MLog", 0)) == -1)
		_mkdir(".\\Logs\\MLog");


	if (file.Open(path, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeBinary))
	{
		if (file.GetLength() == 0)
		{
			file.Write(&nShort, 2);
		}
		file.SeekToEnd();
		file.Write(strLog, (strLog.GetLength() * 2));
		file.Close();

		/*CGIE_BoadAssyDlg* pView = (CGIE_BoadAssyDlg*)(AfxGetApp()->m_pMainWnd)->GetActiveView();
		if (strLog.GetLength() > 300)	strLog = strLog.Left(300);*/
		if (m_pApp->m_pStaticMainLog != NULL)
			m_pStaticMainLog->SetWindowText(strLog);
	}
}

void CVHMOFInspApp::Gf_writeSummaryLog(int ch)
{
	FILE* fp;

	BOOL bNewCsv = FALSE;
	char filepath[128] = { 0 };
	char buff[2048] = { 0 };
	CString sResult = _T("NG");
	CString sdata;

	SYSTEMTIME sysTime;
	::GetSystemTime(&sysTime);
	CTime time = CTime::GetCurrentTime();

	if ((_access(".\\Logs\\SummaryLog", 0)) == -1)
		_mkdir(".\\Logs\\SummaryLog");

	sprintf_s(filepath, ".\\Logs\\SummaryLog\\Summary_%04d%02d%02d.csv", time.GetYear(), time.GetMonth(), time.GetDay());
	fopen_s(&fp, filepath, "r+");
	if (fp == NULL)
	{
		delayMs(1);
		fopen_s(&fp, filepath, "a+");
		if (fp == NULL) // 2007-08-01 : fseek.c(101) error
		{
			if ((_access(filepath, 2)) != -1) // 2007-09-02 : fseek.c(101) error
			{
				delayMs(1);
				fopen_s(&fp, filepath, "a+");
				if (fp == NULL) // 2007-09-02 : fseek.c(101) error
				{
					return;
				}
			}
		}
		bNewCsv = TRUE;
	}

	TCHAR szSwVer[1024] = { 0, };
	GetModuleFileName(NULL, szSwVer, 1024);
	sdata.Format(_T("%s"), szSwVer);
	sdata = sdata.Mid(sdata.ReverseFind(_T('\\')) + 1);
	sdata.Delete(sdata.GetLength() - 4, 4);
	m_summaryInfo.m_sumData[SUM_SW_VER] = sdata;

	m_summaryInfo.m_sumData[SUM_DATE].Format(_T("%04d-%02d-%02d"), time.GetYear(), time.GetMonth(), time.GetDay());
	m_summaryInfo.m_sumData[SUM_CH].Format(_T("CH-%d"), (ch+1));

	m_summaryInfo.m_sumData[SUM_PM_MES].Format(_T("%s"), m_pApp->m_sLoginUserID);
	m_summaryInfo.m_sumData[SUM_FW_VER].Format(_T("%s"), m_pApp->m_sPgFWVersion[ch].Left(19));
	m_summaryInfo.m_sumData[SUM_MODEL].Format(_T("%s"), lpSystemInfo->m_sLastModelName);
	m_summaryInfo.m_sumData[SUM_EQP_ID].Format(_T("%s"), lpSystemInfo->m_sEqpName);
	m_summaryInfo.m_sumData[SUM_PID].Format(_T("%s"), char_To_wchar(lpInspWorkInfo->m_szPanelID));
	if (strlen(lpInspWorkInfo->m_szReasonCode) == 0)
	{
		m_summaryInfo.m_sumData[SUM_PASS_FAIL] = _T("PASS");
		m_summaryInfo.m_sumData[SUM_RWK_CD] = _T("");
	}
	else
	{
		m_summaryInfo.m_sumData[SUM_PASS_FAIL] = _T("FAIL");
		m_summaryInfo.m_sumData[SUM_RWK_CD].Format(_T("%s"), char_To_wchar(lpInspWorkInfo->m_szReasonCode));
	}

	m_summaryInfo.m_sumData[SUM_TACT_TIME].Format(_T("%d"), m_pApp->tt_endTime - m_pApp->tt_startTime);
	m_summaryInfo.m_sumData[SUM_START_TIME].Format(_T("%04d-%02d-%02d_%02d:%02d:%02d")
		, m_pApp->tt_startTime.GetYear()
		, m_pApp->tt_startTime.GetMonth()
		, m_pApp->tt_startTime.GetDay()
		, m_pApp->tt_startTime.GetHour()
		, m_pApp->tt_startTime.GetMinute()
		, m_pApp->tt_startTime.GetSecond()
	);
	m_summaryInfo.m_sumData[SUM_END_TIME].Format(_T("%04d-%02d-%02d_%02d:%02d:%02d")
		, m_pApp->tt_endTime.GetYear()
		, m_pApp->tt_endTime.GetMonth()
		, m_pApp->tt_endTime.GetDay()
		, m_pApp->tt_endTime.GetHour()
		, m_pApp->tt_endTime.GetMinute()
		, m_pApp->tt_endTime.GetSecond()
	);

	if (bNewCsv == TRUE)
	{
		sprintf_s(buff, "Date,CH,PM/MES,S/W_Ver,F/W_Ver,SCRIPT_NAME(Model),EQP_ID,PANEL_ID,FINAL_PASS_FAIL,RWK_CD,TACT_TIME(s),START_TIME,END_TIME\n");
		fprintf(fp, "%s", buff);
	}

	sdata.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n")
		, m_summaryInfo.m_sumData[SUM_DATE]
		, m_summaryInfo.m_sumData[SUM_CH]
		, m_summaryInfo.m_sumData[SUM_PM_MES]
		, m_summaryInfo.m_sumData[SUM_SW_VER]
		, m_summaryInfo.m_sumData[SUM_FW_VER]
		, m_summaryInfo.m_sumData[SUM_MODEL]
		, m_summaryInfo.m_sumData[SUM_EQP_ID]
		, m_summaryInfo.m_sumData[SUM_PID]
		, m_summaryInfo.m_sumData[SUM_PASS_FAIL]
		, m_summaryInfo.m_sumData[SUM_RWK_CD]
		, m_summaryInfo.m_sumData[SUM_TACT_TIME]
		, m_summaryInfo.m_sumData[SUM_START_TIME]
		, m_summaryInfo.m_sumData[SUM_END_TIME]
	);
	sprintf_s(buff, "%s", wchar_To_char(sdata.GetBuffer(0)));

	fseek(fp, 0L, SEEK_END);
	fprintf(fp, "%s", buff);

	fclose(fp);
}


void CVHMOFInspApp::Gf_writeErrorList(int errorCode, CString strError)
{
	FILE* fp;
	FILE* fp_hidden;

	char szbuf[100] = { 0, };
	char szbuf_hidden[100] = { 0, };
	char szYear[5] = { 0, };
	char szMonth[5] = { 0, };
	char szDay[5] = { 0, };
	char filename[256] = { 0 };
	char filepath[1024] = { 0 };
	char filename_hidden[256] = { 0 };
	char filepath_hidden[1024] = { 0 };
	char dataline[4096] = { 0 };

	CString strDate;
	CString strTime;

	SYSTEMTIME sysTime;
	::GetSystemTime(&sysTime);
	CTime time = CTime::GetCurrentTime();

	strDate.Format(_T("%04d%02d%02d"), time.GetYear(), time.GetMonth(), time.GetDay());
	strTime.Format(_T("%02d:%02d:%02d"), time.GetHour(), time.GetMinute(), time.GetSecond());


	// 1. 경로를 찾고 없으면 생성한다.
	sprintf_s(szYear, "%04d", time.GetYear());
	sprintf_s(szMonth, "%02d", time.GetMonth());
	sprintf_s(szDay, "%02d", time.GetDay());

	if ((_access(".\\Logs\\ErrorList", 0)) == -1)
		_mkdir(".\\Logs\\ErrorList");

	sprintf_s(szbuf, ".\\Logs\\ErrorList\\%s", szYear);
	if ((_access(szbuf, 0)) == -1)
		_mkdir(szbuf);

	sprintf_s(szbuf, ".\\Logs\\ErrorList\\%s\\%s", szYear, szMonth);
	if ((_access(szbuf, 0)) == -1)
		_mkdir(szbuf);


	// 2. file을 open한다.
	sprintf_s(filename, "%04d%02d%02d_ErrorList.txt", time.GetYear(), time.GetMonth(), time.GetDay());
	sprintf_s(filepath, "%s\\%s", szbuf, filename);

	fopen_s(&fp, filepath, "r+");
	if (fp == NULL)
	{
		delayMs(10);
		fopen_s(&fp, filepath, "a+");
		if (fp == NULL) // 2007-08-01 : fseek.c(101) error
		{
			return;
		}
	}

	//**************************************************************************************************************//
	// Alarm Log 숨김파일 생성 알고리즘 추가.
	//**************************************************************************************************************//
	if ((_access(".\\Logs\\ErrorList_Hidden", 0)) == -1)
	{
		_mkdir(".\\Logs\\ErrorList_Hidden");

		CString strFile = _T(".\\Logs\\ErrorList_Hidden");
		DWORD attr = GetFileAttributes(strFile);
		SetFileAttributes(strFile, attr | FILE_ATTRIBUTE_HIDDEN);
	}

	sprintf_s(szbuf_hidden, ".\\Logs\\ErrorList_Hidden\\%s", szYear);
	if ((_access(szbuf_hidden, 0)) == -1)
		_mkdir(szbuf_hidden);

	sprintf_s(szbuf_hidden, ".\\Logs\\ErrorList_Hidden\\%s\\%s", szYear, szMonth);
	if ((_access(szbuf_hidden, 0)) == -1)
		_mkdir(szbuf_hidden);

	sprintf_s(filename_hidden, "%04d%02d%02d_ErrorList.txt", time.GetYear(), time.GetMonth(), time.GetDay());
	sprintf_s(filepath_hidden, "%s\\%s", szbuf_hidden, filename_hidden);

	fopen_s(&fp_hidden, filepath_hidden, "r+");
	if (fp_hidden == NULL)
	{
		delayMs(10);
		fopen_s(&fp_hidden, filepath_hidden, "a+");
		if (fp_hidden == NULL) // 2007-08-01 : fseek.c(101) error
		{
			return;
		}
	}
	//**************************************************************************************************************//
	//**************************************************************************************************************//


	// 3. Log를 Write한다.
	char szdate[100] = { 0, };
	char szerror[1024] = { 0, };
	char szDiNumber[100] = { 0, };

	sprintf_s(szdate, "%04d-%02d-%02d %02d:%02d:%02d", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());

	if (strError.Left(3) == _T("(DI"))
	{
		sprintf_s(szDiNumber, "%s", wchar_To_char(strError.Left(7).GetBuffer(0)));
	}

	wchar_To_char(strError.GetBuffer(0), szerror);
	sprintf_s(dataline, "%s,ERROR CODE_%d,%s,%s\n", szdate, errorCode, szDiNumber, szerror);

	fseek(fp, 0L, SEEK_END);
	fseek(fp_hidden, 0L, SEEK_END);

	fwrite(dataline, sizeof(char), strlen(dataline), fp);
	fwrite(dataline, sizeof(char), strlen(dataline), fp_hidden);

	// 4. File을 닫는다.
	fclose(fp);
	fclose(fp_hidden);
}

BOOL CVHMOFInspApp::Gf_ShowMessageBox(int msg_type, CString strTitle, int ErrorCode, CString AppendMessage)
{
	CString strKey, strMessage;

	strKey.Format(_T("%d"), ErrorCode);
	Read_ErrorCode(_T("EQP_ERROR"), strKey, &strMessage);
	if (AppendMessage.GetLength() != 0)
	{
		strMessage.Append(_T("\r\n"));
		strMessage.Append(AppendMessage);
	}

	if (msg_type == MSG_ERROR)
	{
		m_pApp->Gf_writeErrorList(ErrorCode, strMessage);
	}

	CMessageError errDlg;
	errDlg.m_nMessageType	= msg_type;
	errDlg.m_sErrorTitle	= strTitle;
	errDlg.m_sErrorMessage	= strMessage;
	errDlg.DoModal();

	return FALSE;
}

void CVHMOFInspApp::Gf_QtyCountUp(int ch, int ok_ng)
{
	if (ch == CH1)
	{
		if (ok_ng == QTY_OK)
		{
			lpSystemInfo->m_nQuantityOKCh1++;
			Write_SysIniFile(_T("SYSTEM"), _T("QTY_OK_COUNT_CH1"), lpSystemInfo->m_nQuantityOKCh1);
		}
		if (ok_ng == QTY_NG)
		{
			lpSystemInfo->m_nQuantityNGCh1++;
			Write_SysIniFile(_T("SYSTEM"), _T("QTY_NG_COUNT_CH1"), lpSystemInfo->m_nQuantityNGCh1);
		}
	}
	if (ch == CH2)
	{
		if (ok_ng == QTY_OK)
		{
			lpSystemInfo->m_nQuantityOKCh2++;
			Write_SysIniFile(_T("SYSTEM"), _T("QTY_OK_COUNT_CH2"), lpSystemInfo->m_nQuantityOKCh2);
		}
		if (ok_ng == QTY_NG)
		{
			lpSystemInfo->m_nQuantityNGCh2++;
			Write_SysIniFile(_T("SYSTEM"), _T("QTY_NG_COUNT_CH2"), lpSystemInfo->m_nQuantityNGCh2);
		}
	}

	lpSystemInfo->m_nQuantityOKTotal = lpSystemInfo->m_nQuantityOKCh1 + lpSystemInfo->m_nQuantityOKCh2;
	Write_SysIniFile(_T("SYSTEM"), _T("QTY_OK_COUNT_TOTAL"), lpSystemInfo->m_nQuantityOKTotal);

	lpSystemInfo->m_nQuantityNGTotal = lpSystemInfo->m_nQuantityNGCh1 + lpSystemInfo->m_nQuantityNGCh2;
	Write_SysIniFile(_T("SYSTEM"), _T("QTY_NG_COUNT_TOTAL"), lpSystemInfo->m_nQuantityNGTotal);

	AfxGetApp()->GetMainWnd()->SendMessage(WM_UPDATE_QUANTITY_INFO, NULL, NULL);
}

void CVHMOFInspApp::Gf_QtyCountReset(int ch)
{
	if ((ch == CH1) || (ch == MAX_CH))
	{
		lpSystemInfo->m_nQuantityOKCh1 = 0;
		Write_SysIniFile(_T("SYSTEM"), _T("QTY_OK_COUNT_CH1"), _T("0"));

		lpSystemInfo->m_nQuantityNGCh1 = 0;
		Write_SysIniFile(_T("SYSTEM"), _T("QTY_NG_COUNT_CH1"), _T("0"));
	}

	if ((ch == CH2) || (ch == MAX_CH))
	{
		lpSystemInfo->m_nQuantityOKCh2 = 0;
		Write_SysIniFile(_T("SYSTEM"), _T("QTY_OK_COUNT_CH2"), _T("0"));

		lpSystemInfo->m_nQuantityNGCh2 = 0;
		Write_SysIniFile(_T("SYSTEM"), _T("QTY_NG_COUNT_CH2"), _T("0"));
	}

	if (ch == MAX_CH)
	{
		lpSystemInfo->m_nQuantityOKTotal = 0;
		Write_SysIniFile(_T("SYSTEM"), _T("QTY_OK_COUNT_TOTAL"), _T("0"));

		lpSystemInfo->m_nQuantityNGTotal = 0;
		Write_SysIniFile(_T("SYSTEM"), _T("QTY_NG_COUNT_TOTAL"), _T("0"));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gradation Station Function
////////////////////////////////////////////////////////////////////////////////////////////////////////
void CVHMOFInspApp::Gf_setGradientStatic(CGradientStatic* pGStt, long bkColor1, long bkColor2, long fontColor, CFont* pFont, BOOL bSplit)
{
	pGStt->SetFont(pFont);
	pGStt->SetTextAlign(TEXT_ALIGN_CENTER);
	pGStt->SetColor(bkColor1);
	pGStt->SetGradientColor(bkColor2);
	pGStt->SetVerticalGradient();
	if (bSplit == TRUE)	pGStt->SetSplitMode(TRUE);
	pGStt->SetTextColor(fontColor);
	pGStt->SetTextMultiLine(FALSE);
}

void CVHMOFInspApp::Gf_setGradientStatic(CGradientStatic* pGStt, long bkColor, long fontColor, CFont* pFont, BOOL bSplit)
{
	pGStt->SetFont(pFont);
	pGStt->SetTextAlign(TEXT_ALIGN_CENTER);
	pGStt->SetColor(bkColor);
	pGStt->SetGradientColor(bkColor);
	pGStt->SetVerticalGradient();
	if (bSplit == TRUE)	pGStt->SetSplitMode(TRUE);
	pGStt->SetTextColor(fontColor);
	pGStt->SetTextMultiLine(TRUE);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// Model File Load
////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CVHMOFInspApp::Gf_FindModelFile(CString modelName)
{
	CString strDataFolder;

	WIN32_FIND_DATA wfd;
	HANDLE hSearch;
	int nLoof = 1;

	if (modelName == _T(""))
		return FALSE;

	strDataFolder.Format(_T(".\\%s\\%s.mod"), _T("Model"), modelName);
	hSearch = FindFirstFile(strDataFolder, &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		FindClose(hSearch);
		return TRUE;
	}
	else
	{
		FindClose(hSearch);
		return FALSE;
	}
}

void CVHMOFInspApp::Gf_LoadModelData(CString modelName)
{
	CString sValue = _T("");

	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VCC"), &lpModelInfo->m_fPowerVcc);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VEL"), &lpModelInfo->m_fPowerVel);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VDD"), &lpModelInfo->m_fPowerVdd);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VCC_OFFSET"), &lpModelInfo->m_fPowerVccOffset);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VEL_OFFSET"), &lpModelInfo->m_fPowerVelOffset);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VDD_OFFSET"), &lpModelInfo->m_fPowerVddOffset);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VCC_LIMIT_LOW"), &lpModelInfo->m_fLimitVccLow);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VCC_LIMIT_High"), &lpModelInfo->m_fLimitVccHigh);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VEL_LIMIT_LOW"), &lpModelInfo->m_fLimitVelLow);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VEL_LIMIT_High"), &lpModelInfo->m_fLimitVelHigh);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VDD_LIMIT_LOW"), &lpModelInfo->m_fLimitVddLow);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VDD_LIMIT_High"), &lpModelInfo->m_fLimitVddHigh);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("ICC_LIMIT_LOW"), &lpModelInfo->m_nLimitIccLow);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("ICC_LIMIT_High"), &lpModelInfo->m_nLimitIccHigh);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("IEL_LIMIT_LOW"), &lpModelInfo->m_nLimitIelLow);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("IEL_LIMIT_High"), &lpModelInfo->m_nLimitIelHigh);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("IDD_LIMIT_LOW"), &lpModelInfo->m_nLimitIddLow);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("IDD_LIMIT_High"), &lpModelInfo->m_nLimitIddHigh);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX1"), &lpModelInfo->m_nPowerOnSeq1);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX2"), &lpModelInfo->m_nPowerOnSeq2);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX3"), &lpModelInfo->m_nPowerOnSeq3);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX4"), &lpModelInfo->m_nPowerOnSeq4);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX5"), &lpModelInfo->m_nPowerOnSeq5);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX6"), &lpModelInfo->m_nPowerOnSeq6);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX7"), &lpModelInfo->m_nPowerOnSeq7);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX8"), &lpModelInfo->m_nPowerOnSeq8);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX9"), &lpModelInfo->m_nPowerOnSeq9);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX10"), &lpModelInfo->m_nPowerOnSeq10);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX11"), &lpModelInfo->m_nPowerOnSeq11);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX12"), &lpModelInfo->m_nPowerOnSeq12);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX13"), &lpModelInfo->m_nPowerOnSeq13);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX1"), &lpModelInfo->m_nPowerOffSeq1);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX2"), &lpModelInfo->m_nPowerOffSeq2);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX3"), &lpModelInfo->m_nPowerOffSeq3);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX4"), &lpModelInfo->m_nPowerOffSeq4);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX5"), &lpModelInfo->m_nPowerOffSeq5);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX6"), &lpModelInfo->m_nPowerOffSeq6);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX7"), &lpModelInfo->m_nPowerOffSeq7);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX8"), &lpModelInfo->m_nPowerOffSeq8);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX9"), &lpModelInfo->m_nPowerOffSeq9);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX10"), &lpModelInfo->m_nPowerOffSeq10);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX11"), &lpModelInfo->m_nPowerOffSeq11);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX12"), &lpModelInfo->m_nPowerOffSeq12);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX13"), &lpModelInfo->m_nPowerOffSeq13);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY1"), &lpModelInfo->m_nPowerOnDelay1);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY2"), &lpModelInfo->m_nPowerOnDelay2);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY3"), &lpModelInfo->m_nPowerOnDelay3);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY4"), &lpModelInfo->m_nPowerOnDelay4);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY5"), &lpModelInfo->m_nPowerOnDelay5);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY6"), &lpModelInfo->m_nPowerOnDelay6);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY7"), &lpModelInfo->m_nPowerOnDelay7);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY8"), &lpModelInfo->m_nPowerOnDelay8);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY9"), &lpModelInfo->m_nPowerOnDelay9);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY10"), &lpModelInfo->m_nPowerOnDelay10);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY11"), &lpModelInfo->m_nPowerOnDelay11);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY12"), &lpModelInfo->m_nPowerOnDelay12);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY13"), &lpModelInfo->m_nPowerOnDelay13);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY1"), &lpModelInfo->m_nPowerOffDelay1);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY2"), &lpModelInfo->m_nPowerOffDelay2);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY3"), &lpModelInfo->m_nPowerOffDelay3);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY4"), &lpModelInfo->m_nPowerOffDelay4);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY5"), &lpModelInfo->m_nPowerOffDelay5);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY6"), &lpModelInfo->m_nPowerOffDelay6);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY7"), &lpModelInfo->m_nPowerOffDelay7);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY8"), &lpModelInfo->m_nPowerOffDelay8);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY9"), &lpModelInfo->m_nPowerOffDelay9);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY10"), &lpModelInfo->m_nPowerOffDelay10);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY11"), &lpModelInfo->m_nPowerOffDelay11);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY12"), &lpModelInfo->m_nPowerOffDelay12);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY13"), &lpModelInfo->m_nPowerOffDelay13);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("PXEL_TYPE"), &lpModelInfo->m_nPixelType);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("SIGNAL_BIT"), &lpModelInfo->m_nSignalBit);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("ROTATE"), &lpModelInfo->m_nSignalRotate);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("SIGNAL_TYPE"), &lpModelInfo->m_nSignalType);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("BIT_SELECT"), &lpModelInfo->m_nBitSelect);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("FRS_MODE"), &lpModelInfo->m_nFrsMode);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("CLOCK_DELAY"), &lpModelInfo->m_nClockDelay);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("ALPDP_INIT_SCRIPT"), &lpModelInfo->m_nInitScript);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_FRE"), &lpModelInfo->m_fTimingFrequency);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_TOTAL_H"), &lpModelInfo->m_nTimingHorTotal);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_ACTIVE_H"), &lpModelInfo->m_nTimingHorActive);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_WIDTH_H"), &lpModelInfo->m_nTimingHorWidth);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_BACK_P_H"), &lpModelInfo->m_nTimingHorBackPorch);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_Front_P_H"), &lpModelInfo->m_nTimingHorFrontPorch);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_TOTAL_V"), &lpModelInfo->m_nTimingVerTotal);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_ACTIVE_V"), &lpModelInfo->m_nTimingVerActive);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_WIDTH_V"), &lpModelInfo->m_nTimingVerWidth);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_BACK_P_V"), &lpModelInfo->m_nTimingVerBackPorch);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("TIMING_Front_P_V"), &lpModelInfo->m_nTimingVerFrontPorch);

	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("MAIN_BOARD_LED"), &lpModelInfo->m_nMainBoardLED);

	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("I2C_PULL_UP"), &lpModelInfo->m_nI2cPullUp);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("I2C_FREQUENCY"), &lpModelInfo->m_nI2cClock);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("I2C_LEVEL"), &lpModelInfo->m_nI2cLevel);

	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("QSPI_CLOCK"), &lpModelInfo->m_nSpiClock);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("QSPI_LEVEL"), &lpModelInfo->m_nSpiLevel);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("QSPI_PULL_UP"), &lpModelInfo->m_nSpiPullUp);

	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("GPIO_PULL_UP"), &lpModelInfo->m_nGpioPullUp);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("GPIO_LEVEL"), &lpModelInfo->m_nGpioLevel);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("GPIO1_OUTPUT"), &lpModelInfo->m_nGpio1Output);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("GPIO2_OUTPUT"), &lpModelInfo->m_nGpio2Output);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("GPIO3_OUTPUT"), &lpModelInfo->m_nGpio3Output);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("GIO1_SETTING"), &lpModelInfo->m_nGio1Setting);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("GIO2_SETTING"), &lpModelInfo->m_nGio2Setting);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("GIO3_SETTING"), &lpModelInfo->m_nGio3Setting);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("GIO4_SETTING"), &lpModelInfo->m_nGio4Setting);

	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("PWM_FREQUENCY"), &lpModelInfo->m_nPwmFrequency);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("PWM_DUTY"), &lpModelInfo->m_nPwmDuty);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("PWM_LEVEL"), &lpModelInfo->m_nPwmLevel);

	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("CABLE_OPEN_CHECK"), &lpModelInfo->m_nCableOpenCheck);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("JIG_TILTING_CHECK"), &lpModelInfo->m_nJigTiltingCheck);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pattern File 
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CString strKey, sdata;
	TCHAR szParseData[255][255] = { 0, };

	lpModelInfo->m_nPatternListCount = 0;
	for (int nLoop = 0; ; nLoop++)
	{
		strKey.Format(_T("PTN_%d"), nLoop);
		Read_ModelFile(modelName, _T("PATTERN_INFO"), strKey, &sdata);
		Lf_parsingModFileData(sdata, szParseData);

		//if(*szData == NULL)//if(strParseData.IsEmpty())
		if (sdata.IsEmpty())
		{
			memset(szParseData, NULL, sizeof(szParseData));

			lpModelInfo->m_sLbPtnListNAME[nLoop].Empty();
			lpModelInfo->m_sLbPtnListVCC[nLoop].Empty();
			lpModelInfo->m_sLbPtnListVEL[nLoop].Empty();
			lpModelInfo->m_sLbPtnListICC[nLoop].Empty();
			lpModelInfo->m_sLbPtnListIEL[nLoop].Empty();
			lpModelInfo->m_sLbPtnListLockTime[nLoop].Empty();
			lpModelInfo->m_sLbPtnListMaxTIME[nLoop].Empty();
			lpModelInfo->m_sLbPtnListVSYNC[nLoop].Empty();
			lpModelInfo->m_sLbPtnListONOFF[nLoop].Empty();
		}
		else
		{
			lpModelInfo->m_sLbPtnListNAME[nLoop] = szParseData[0];
			lpModelInfo->m_sLbPtnListVCC[nLoop] = szParseData[1];
			lpModelInfo->m_sLbPtnListVEL[nLoop] = szParseData[2];
			lpModelInfo->m_sLbPtnListICC[nLoop] = szParseData[3];
			lpModelInfo->m_sLbPtnListIEL[nLoop] = szParseData[4];
			lpModelInfo->m_sLbPtnListLockTime[nLoop] = szParseData[5];
			lpModelInfo->m_sLbPtnListMaxTIME[nLoop] = szParseData[6];
			lpModelInfo->m_sLbPtnListVSYNC[nLoop] = szParseData[7];
			lpModelInfo->m_sLbPtnListONOFF[nLoop] = szParseData[8];
			lpModelInfo->m_nPatternListCount = nLoop + 1;
		}

		// Data가 NULL값이 있으면 Pasing을 중단한다.
		//if(*szData==NULL)	break;
		if (sdata.IsEmpty())
			break;
	}
}

BOOL CVHMOFInspApp::Gf_LoadSystemData()
{
	CString sValue = _T("");

	Read_SysIniFile(_T("SYSTEM"),			_T("LAST_MODELNAME"),			&lpSystemInfo->m_sLastModelName);
	Read_SysIniFile(_T("SYSTEM"),			_T("EQP_NAME"),					&lpSystemInfo->m_sEqpName);
	Read_SysIniFile(_T("SYSTEM"),			_T("CARRIER_TYPE"),				&lpSystemInfo->m_nCarrierType);
	Read_SysIniFile(_T("SYSTEM"),			_T("MELSEC_LB_START_ADDRESS"),	&sValue);
	lpSystemInfo->m_nLBStartAddr = _tcstol(sValue, NULL, 16);
	Read_SysIniFile(_T("SYSTEM"),			_T("MELSEC_LW_START_ADDRESS"),	&sValue);
	lpSystemInfo->m_nLWStartAddr = _tcstol(sValue, NULL, 16);
	Read_SysIniFile(_T("MES"),				_T("MES_SERVICE"),				&lpSystemInfo->m_sMesServicePort);
	Read_SysIniFile(_T("MES"),				_T("MES_NETWORK"),				&lpSystemInfo->m_sMesNetWork);
	Read_SysIniFile(_T("MES"),				_T("MES_DAEMON_PORT"),			&lpSystemInfo->m_sMesDaemonPort);
	Read_SysIniFile(_T("MES"),				_T("MES_LOCAL_SUBJECT"),		&lpSystemInfo->m_sMesLocalSubject);
	Read_SysIniFile(_T("MES"),				_T("MES_REMOTE_SUBJECT"),		&lpSystemInfo->m_sMesRemoteSubject);
	Read_SysIniFile(_T("MES"),				_T("MES_LOCAL_IP"),				&lpSystemInfo->m_sMesLocalIP);
	Read_SysIniFile(_T("EAS"),				_T("EAS_USE"),					&lpSystemInfo->m_nEasUse);
	Read_SysIniFile(_T("EAS"),				_T("EAS_SERVICE"),				&lpSystemInfo->m_sEasServicePort);
	Read_SysIniFile(_T("EAS"),				_T("EAS_NETWORK"),				&lpSystemInfo->m_sEasNetWork);
	Read_SysIniFile(_T("EAS"),				_T("EAS_DAEMON_PORT"),			&lpSystemInfo->m_sEasDaemonPort);
	Read_SysIniFile(_T("EAS"),				_T("EAS_LOCAL_SUBJECT"),		&lpSystemInfo->m_sEasLocalSubject);
	Read_SysIniFile(_T("EAS"),				_T("EAS_REMOTE_SUBJECT"),		&lpSystemInfo->m_sEasRemoteSubject);
	Read_SysIniFile(_T("DFS"),				_T("DFS_USE"),					&lpSystemInfo->m_nDfsUse);
	Read_SysIniFile(_T("DFS"),				_T("DFS_IP_ADDRESS"),			&lpSystemInfo->m_sDfsIPAddress);
	Read_SysIniFile(_T("DFS"),				_T("DFS_USER_ID"),				&lpSystemInfo->m_sDfsUserId);
	Read_SysIniFile(_T("DFS"),				_T("DFS_PASSWORD"),				&lpSystemInfo->m_sDfsPassword);
	Read_SysIniFile(_T("SYSTEM"),			_T("MODEL_FILE_PATH"),			&lpSystemInfo->m_sDataFileModel);
	Read_SysIniFile(_T("SYSTEM"),			_T("PATTERN_FILE_PATH"),		&lpSystemInfo->m_sDataFilePattern);
	Read_SysIniFile(_T("SYSTEM"),			_T("EDID_PATH"),				&lpSystemInfo->m_sDataFileEdid);
	Read_SysIniFile(_T("SYSTEM"),			_T("QTY_OK_COUNT_CH1"),			&lpSystemInfo->m_nQuantityOKCh1);
	Read_SysIniFile(_T("SYSTEM"),			_T("QTY_NG_COUNT_CH1"),			&lpSystemInfo->m_nQuantityNGCh1);
	Read_SysIniFile(_T("SYSTEM"),			_T("QTY_OK_COUNT_CH2"),			&lpSystemInfo->m_nQuantityOKCh2);
	Read_SysIniFile(_T("SYSTEM"),			_T("QTY_NG_COUNT_CH2"),			&lpSystemInfo->m_nQuantityNGCh2);
	Read_SysIniFile(_T("SYSTEM"),			_T("QTY_OK_COUNT_TOTAL"),		&lpSystemInfo->m_nQuantityOKTotal);
	Read_SysIniFile(_T("SYSTEM"),			_T("QTY_NG_COUNT_TOTAL"),		&lpSystemInfo->m_nQuantityNGTotal);


	return TRUE;
}

void CVHMOFInspApp::Lf_parsingModFileData(CString szData, TCHAR(*szParseData)[255])
{
	TCHAR szTemp[100];

	int nCnt = 0;
	int nItemCnt = 0;
	int nLoop = 0;

	memset(szTemp, 0, sizeof(szTemp));
	int nCmdLength = szData.GetLength();//_tcslen(szData);

	for (nLoop = 0; nLoop <= nCmdLength; nLoop++)
	{
		szTemp[nCnt] = szData[nLoop];
		if ((szData[nLoop] == ',') || (nLoop == nCmdLength))
		{
			szTemp[nCnt] = NULL;
			_stprintf_s(szParseData[nItemCnt++], 100, _T("%s"), szTemp);
			for (int i = 0; i <= nCnt; i++)
				szTemp[i] = NULL;
			nCnt = 0;
		}
		nCnt++;
		if (szData[nLoop] == ',') nCnt = 0;
	}
}

BOOL CVHMOFInspApp::Gf_LoadModelFile()
{
	BOOL ret = TRUE;

	// Model File을 Loading 한다.
	if (Gf_FindModelFile(lpSystemInfo->m_sLastModelName) == TRUE)
	{
		Gf_LoadModelData(lpSystemInfo->m_sLastModelName);
	}
	else
	{
		ret = FALSE;

		CString AppendMessage;
		AppendMessage.Format(_T("(Model\\%s)"), lpSystemInfo->m_sLastModelName);
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("MODEL LOAD ERROR"), ERROR_CODE_35, AppendMessage);
	}

	return ret;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MES Function
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CVHMOFInspApp::Gf_gmesInitServer(BOOL nServerType)
{
	if ((DEBUG_GMES_TEST_SERVER == TRUE) && (nServerType == SERVER_MES))
	{
		m_pCimNet->SetMachineName(lpSystemInfo->m_sEqpName);
		m_pCimNet->SetLocalTest(nServerType);
	}
	else if ((DEBUG_GMES_TEST_SERVER == TRUE) && (nServerType == SERVER_EAS))
	{
		m_pCimNet->SetLocalTest(nServerType);
	}


	if (m_pCimNet->Init(nServerType) == TRUE)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CVHMOFInspApp::Gf_gmesConnect(int nServerType)
{
	char szBuffer[64] = { 0, };

	m_pCimNet->SetMachineName(lpSystemInfo->m_sEqpName);

	if (m_pCimNet->ConnectTibRv(nServerType) == TRUE)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CVHMOFInspApp::Gf_gmesDisConnect(int nServerType)
{
	return m_pCimNet->CloseTibRv(nServerType);
}

void CVHMOFInspApp::Gf_gmesSetGoodInfo()
{
	m_pCimNet->SetPF(_T("P"));
}

void CVHMOFInspApp::Gf_gmesSetBadInfo()
{
	m_pCimNet->SetPF(_T("F"));
}

void CVHMOFInspApp::Lf_gmesSetValuePCHK()
{
	m_pCimNet->SetMachineName(lpSystemInfo->m_sEqpName);

	m_pCimNet->SetPanelID(char_To_wchar(lpInspWorkInfo->m_szPanelID));
	m_pCimNet->SetSerialNumber(char_To_wchar(lpInspWorkInfo->m_szSerialNum));
}

void CVHMOFInspApp::Lf_gmesSetValueAPDR()
{
	CString sAPDInfo;

	m_pCimNet->SetPanelID(char_To_wchar(lpInspWorkInfo->m_szPanelID));
	m_pCimNet->SetSerialNumber(char_To_wchar(lpInspWorkInfo->m_szSerialNum));
	m_pCimNet->SetBLID(_T(""));
	m_pCimNet->SetPalletID(_T(""));

	m_pCimNet->SetAPDInfo(sAPDInfo);
}
void CVHMOFInspApp::Lf_gmesSetValueEICR()
{
	m_pCimNet->SetPanelID(char_To_wchar(lpInspWorkInfo->m_szPanelID));
	m_pCimNet->SetSerialNumber(char_To_wchar(lpInspWorkInfo->m_szSerialNum));
	m_pCimNet->SetBLID(_T(""));
	m_pCimNet->SetPalletID(_T(""));

	// 양품/불량 설정.
	if (!m_pCimNet->GetRwkCode().Compare(_T("")))
	{
		m_pCimNet->SetPF(_T("P"));
		m_pCimNet->SetDefectPattern(_T(""));
	}
	else
	{
		m_pCimNet->SetPF(_T("F"));
		// 불량 Pattern 정보 설정.
		CString strBadPtn;
		strBadPtn.Format(_T("%s"), char_To_wchar(lpInspWorkInfo->m_szBadPattern));
		strBadPtn.Replace(_T(" "), _T("_"));
		m_pCimNet->SetDefectPattern(strBadPtn.GetBuffer(0));
	}

	m_pCimNet->SetPvcomAdjustValue(_T(""));
	m_pCimNet->SetPvcomAdjustDropValue(_T(""));

	// Pattern 정보 설정
	m_pCimNet->SetPatternInfo(Lf_gmesGetPatternData());
}

CString CVHMOFInspApp::Lf_gmesGetPatternData()
{
	CString sdata1 = _T(""), sdata2 = _T(""), rtnData = _T("");
	int cnt = 0, Num = 0;
	float chk = 0.0;

	while (cnt < lpModelInfo->m_nPatternListCount)
	{
		cnt++;
		chk = (float)(m_nPatTime[Num] * 0.001);
		if (chk != 0)
		{
			Num++;
			sdata1.Format(_T("%d:%s:%2.2f,"), Num, lpModelInfo->m_sLbPtnListNAME[Num - 1], chk);
			sdata2.Append(sdata1);
		}
	}

	rtnData = sdata2.Left(sdata2.GetLength() - 1);
	return rtnData;
}

CString CVHMOFInspApp::Gf_gmesGetRTNCD()
{
	CString strBuff;

	m_pCimNet->GetFieldData(&strBuff, _T("RTN_CD"));
	return strBuff;
}

void CVHMOFInspApp::Gf_gmesShowLocalErrorMsg()
{
	CString strMsg;

	m_pCimNet->GetFieldData(&strMsg, _T("ERR_MSG_LOC"));	//ERR_MSG_ENG	ERR_MSG_LOC
	Gf_ShowMessageBox(MSG_ERROR, _T("MES ERROR"), ERROR_CODE_36, strMsg);
}

BOOL CVHMOFInspApp::Gf_gmesSendHost(int nHostCmd)
{
	int nRtnCD;
	CString sLog;
	CString strBuff;
	char Luc_PF = 0;

	if ((m_bUserIdGieng == TRUE) || (m_bUserIdPM == TRUE) || (m_bUserIdIdle == TRUE))
		return TRUE;

Send_RETRY:

	if (nHostCmd == HOST_EAYT)
	{
		nRtnCD = m_pCimNet->EAYT();
	}
	else if (nHostCmd == HOST_UCHK)
	{
		nRtnCD = m_pCimNet->UCHK();
		if (nRtnCD == 0)
		{
			m_pCimNet->GetFieldData(&m_pApp->m_sLoginUserName, _T("USER_NAME"));
			m_pCimNet->SetUserId(m_pApp->m_sLoginUserID);
		}
	}
	else if (nHostCmd == HOST_EDTI)
	{
		nRtnCD = m_pCimNet->EDTI();
	}
	else if (nHostCmd == HOST_PCHK)
	{
		Lf_gmesSetValuePCHK();
		nRtnCD = m_pCimNet->PCHK();

		if (nRtnCD == RTN_OK)
		{
			m_pCimNet->GetFieldData(&strBuff, _T("RTN_PID"));
			sLog.Format(_T("<MES> RTN_PID : %s"), strBuff);
			Gf_writeMLog(sLog);

			m_pCimNet->GetFieldData(&strBuff, _T("TOP_MODEL_NAME"));
			sprintf_s(lpInspWorkInfo->m_szHostTopModelName, "%s", wchar_To_char(strBuff.GetBuffer(0)));
			sLog.Format(_T("<MES> TOP_MODEL_NAME : %s"), strBuff);
			Gf_writeMLog(sLog);
		}
	}
	else if (nHostCmd == HOST_EICR)
	{
		Lf_gmesSetValueEICR();
		nRtnCD = m_pCimNet->EICR();
	}
	else if (nHostCmd == HOST_APDR)
	{
		Lf_gmesSetValueAPDR();
		nRtnCD = m_pCimNet->APDR();
	}
	sLog.Format(_T("<HOST_R> %s"), m_pCimNet->GetHostRecvMessage());
	Gf_writeMLog(sLog);

	if (nRtnCD == RTN_OK)
	{
		return TRUE;
	}
	else if (nRtnCD == RTN_MSG_NOT_SEND)
	{
		CString strVal;
		CMessageQuestion start_dlg;

		start_dlg.m_strQMessage.Format(_T("Failed to send message. "));
		start_dlg.m_strLButton = _T(" Retry");

		Read_ErrorCode(_T("EQP"), _T("0"), &strVal);

		if (start_dlg.DoModal() == IDOK)
			goto Send_RETRY;
		else
			return FALSE;
	}
	else if (nRtnCD == RTN_RCV_TIMEOUT)
	{
		CString strVal;
		CMessageQuestion start_dlg;

		start_dlg.m_strQMessage.Format(_T("No response frome MES Host"));
		start_dlg.m_strLButton = _T(" Retry");

		Read_ErrorCode(_T("EQP"), _T("1"), &strVal);
		if (start_dlg.DoModal() == IDOK)
			goto Send_RETRY;
		else
			return FALSE;
	}
	else
	{
		Gf_gmesShowLocalErrorMsg();
	}
	return FALSE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CVHMOFInspApp::Gf_setStartPtnLockTime(int nPtnNum)
{
	m_nSLockTime = ::GetTickCount();
}

void CVHMOFInspApp::Gf_setEndPtnLockTime(int nPtnNum)
{
	m_nELockTime = ::GetTickCount();
	m_nPtnLockTime[nPtnNum] = m_nELockTime - m_nSLockTime;		// Pattern 검사 시간 저장.
}

void CVHMOFInspApp::Gf_setPatStartCheckTime(int i)
{
	m_nStartCheckTime[i] = ::GetTickCount();
}

void CVHMOFInspApp::Gf_setPatEndCheckTime(int i)
{
	m_nEndCheckTime[i] = ::GetTickCount();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TCP/IP 통신 Protocol (Main Board)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CVHMOFInspApp::main_tcpProcessPacket(int ch, char* recvPacket)
{
	char szbuf[10] = { 0, };
	int recvCMD = 0;
	int recvLen = 0;
	int recvRet = 0;

	sscanf_s(&recvPacket[PACKET_PT_CMD], "%02X%04X%01X", &recvCMD, &recvLen, &recvRet);

	// Message 처리
	switch (recvCMD)
	{
		case CMD_PG_PATTERN_INFO:
		{
			break;
		}
		case CMD_IF_CABLE_OPEN:
		{
			break;
		}
		case CMD_IF_I2C_WRITE:
		{
			break;
		}
		case CMD_IF_I2C_READ:
		{
			break;
		}
		case CMD_IF_I2C_IRREGULAR_WRITE:
		{
			break;
		}
		case CMD_CTRL_FUSING_SYSTEM:
		{
			break;
		}
		case CMD_CTRL_POWER_VOLTAGE_SET:
		{
			break;
		}
		case CMD_CTRL_POWER_SEQUENCE_ONOFF:
		{
			break;
		}
		case CMD_CTRL_MEASURE_ITEM_POWER:
		{
			break;
		}
		case CMD_CTRL_MEASURE_ALL_POWER:
		{
			main_parse_PowerMeasureAll(ch, recvPacket);
			break;
		}
		case CMD_CTRL_CABLE_OPEN_CHECK:
		{
			main_parse_CableOpenCheck(ch, recvPacket);
			break;
		}
		case CMD_CTRL_GIO_CONTROL:
		{
			main_parse_GioControl(ch, recvPacket);
			break;
		}
		case CMD_CTRL_ARE_YOU_READY:
		{
			main_parse_AreYouReady(ch, recvPacket);
			break;
		}
		case CMD_IF_SRUN_STATUS_READ:
		{
			break;
		}
		case CMD_IF_SRUN_DATA_WRITE:
		{
			break;
		}
		case CMD_IF_SRUN_DATA_READ:
		{
			break;
		}
		case CMD_CTRL_TRANSFER_TO_POWER:
		{
			main_parse_PmmStatus(ch, recvPacket);
			break;
		}
		case CMD_CTRL_GOTO_BOOT_SECTION:
		{
			main_parse_GoToBootSection(ch, recvPacket);
			break;
		}
		case CMD_CTRL_FW_VERSION:
		{
			main_parse_FirmwareVersion(ch, recvPacket);
			break;
		}
	}

	// ACK Receive Check는 모든 Packet처리가 완료된 이후 Set한다.
	//m_nAckCmd[recvCMD] = TRUE;

	return TRUE;
}

void CVHMOFInspApp::main_parse_AreYouReady(int ch, char* recvPacket)
{
	if (recvPacket[PACKET_PT_RET] == '0')
	{
		lpInspWorkInfo->m_bAreYouReady = TRUE;
	}
}

void CVHMOFInspApp::main_parse_PowerMeasureAll(int ch, char* recvPacket)
{
	CString strPacket;
	int nPos = PACKET_PT_DATA;

	strPacket.Format(_T("%S"), recvPacket);
	if (strPacket.GetLength() >= 51)	// 잘못된 Packet이 입력되면 Return 시킨다.
	{
		lpInspWorkInfo->m_nMeasureVCC[ch] = (int)_ttoi(strPacket.Mid(nPos, 5));
		lpInspWorkInfo->m_nMeasureVEL[ch] = (int)_ttoi(strPacket.Mid(nPos += 5, 5));
		lpInspWorkInfo->m_nMeasureVDD[ch] = (int)_ttoi(strPacket.Mid(nPos += 5, 5));
		lpInspWorkInfo->m_nMeasureICC[ch] = (int)_ttoi(strPacket.Mid(nPos += 5, 5));
		lpInspWorkInfo->m_nMeasureIEL[ch] = (int)_ttoi(strPacket.Mid(nPos += 5, 5));
		lpInspWorkInfo->m_nMeasureIDD[ch] = (int)_ttoi(strPacket.Mid(nPos += 5, 5));
		lpInspWorkInfo->m_nMeasureErrName[ch] = (int)_ttoi(strPacket.Mid(nPos += 5, 1));
		lpInspWorkInfo->m_nMeasureErrCh[ch] = (int)_ttoi(strPacket.Mid(nPos += 1, 1));
		lpInspWorkInfo->m_nMeasureErrValue[ch] = (int)_ttoi(strPacket.Mid(nPos += 1, 5));
	}
}

void CVHMOFInspApp::main_parse_CableOpenCheck(int ch, char* recvPacket)
{

	if (recvPacket[PACKET_PT_RET] == '0')
	{
		CString strPacket;
		int nPos = PACKET_PT_DATA;

		strPacket.Format(_T("%S"), recvPacket);
		lpInspWorkInfo->nCheckCableOpenValue = _ttoi(strPacket.Mid(PACKET_PT_DATA, 1));
	}
}

void CVHMOFInspApp::main_parse_GioControl(int ch, char* recvPacket)
{

	if (recvPacket[PACKET_PT_RET] == '0')
	{
		CString strPacket;
		int nPos = PACKET_PT_DATA;

		strPacket.Format(_T("%S"), recvPacket);
		lpInspWorkInfo->nGioReadInfo[0] = _ttoi(strPacket.Mid(PACKET_PT_DATA, 1));
		lpInspWorkInfo->nGioReadInfo[1] = _ttoi(strPacket.Mid(PACKET_PT_DATA+1, 1));
		lpInspWorkInfo->nGioReadInfo[2] = _ttoi(strPacket.Mid(PACKET_PT_DATA+2, 1));
		lpInspWorkInfo->nGioReadInfo[3] = _ttoi(strPacket.Mid(PACKET_PT_DATA+3, 1));
	}
}

void CVHMOFInspApp::main_parse_PmmStatus(int ch, char* recvPacket)
{
	int retcode = 0;
	char recvCmd;

	retcode = recvPacket[PACKET_PT_RET];
	recvCmd = recvPacket[PACKET_PT_DATA + 2];

	if (retcode == '0')	// Main Board ACK
	{
		if (recvPacket[PACKET_PT_DATA + 3] == '0')	// Power Module ACK
		{
			lpInspWorkInfo->m_nPmmAck = TRUE;

			if (recvCmd == 'V')
			{
				m_pApp->m_sPmmFWVersion[ch].Format(_T("%s"), char_To_wchar(recvPacket));
				m_pApp->m_sPmmFWVersion[ch].Delete(0, PACKET_PT_DATA + 4);
				m_pApp->m_sPmmFWVersion[ch] = m_pApp->m_sPmmFWVersion[ch].Left(m_pApp->m_sPmmFWVersion[ch].GetLength() - 6);
			}
		}
		else
		{
			lpInspWorkInfo->m_nPmmAck = FALSE;
		}
	}
	else
	{
		lpInspWorkInfo->m_nPmmAck = FALSE;
	}
}

void CVHMOFInspApp::main_parse_FirmwareVersion(int ch, char* recvPacket)
{
	CString strPacket;
	int nPos = PACKET_PT_DATA;

	strPacket.Format(_T("%S"), recvPacket);

	m_pApp->m_sPgFWVersion[ch] = strPacket.Mid(PACKET_PT_DATA, strPacket.GetLength()-17);


	CString strLog = _T("");

	strLog.Format(_T("<PG> CH-%d MCU Version [%s]"), ch+1, m_pApp->m_sPgFWVersion[ch]);
	m_pApp->Gf_writeMLog(strLog);

}

void CVHMOFInspApp::main_parse_GoToBootSection(int ch, char* recvPacket)
{
	CString strPacket;
	int nPos = PACKET_PT_RET;

	if (recvPacket[PACKET_PT_RET] == '0')
	{
		m_nDownloadReadyAckCount++;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UDP 통신 Protocol (DIO Board)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CVHMOFInspApp::Lf_initCreateUdpSocket()
{
	if (m_pUDPSocket->CreatSocket(UDP_SOCKET_PORT, SOCK_DGRAM) == FALSE)
	{
		AfxMessageBox(_T("UDP Socket Create Fail"), MB_ICONERROR);
		return;
	}

	Lf_initLocalHostIPAddress();
}

BOOL CVHMOFInspApp::Lf_initLocalHostIPAddress()
{
	// Receive Message 처리를 제외할 자신의 IP와 GateIP를 가져온다.
	//	m_pUDPSocket->m_bEthernetInit = FALSE;

	m_pUDPSocket->getLocalIPAddress();
	m_pUDPSocket->getLocalGateWay();

	return TRUE;
}

BOOL CVHMOFInspApp::udp_sendPacketUDP_DIO(int ch, int target, int nID, int nCommand, int nSize, char* pdata, int recvACK, int waitTime)
{
	int datalen = 0;
	int packetlen = 0;
	BYTE nChkSum = 0;
	char szbuff[5] = { 0, };
	char sendPacket[1024] = { 0, };

	datalen = nSize;

	// data 앞까지 Packet 생성
	sprintf_s(sendPacket, "%cA1%02X%02X%02X%04X", PACKET_STX, target, nID, nCommand, datalen);

	// data를 포함하여 packet 생성. hex로 전송할 data가 있으므로 memcpy를 사용
	packetlen = (int)strlen(sendPacket);

	memcpy(&sendPacket[packetlen], pdata, datalen);

	// data 를 포함한 packet의 길이를 구한다.
	packetlen += datalen;

	// 생성된 Packet을 이용하여 CheckSum을 구한다.
	for (int j = 1; j < packetlen; j++)		// Check Sum
	{
		nChkSum += sendPacket[j];
	}
	sprintf_s(szbuff, "%02X%c", nChkSum, 0x03);

	// Checksum과 ETX 3byte를 붙여 다시 Packet을 만든다.
	memcpy(&sendPacket[packetlen], szbuff, 3);
	packetlen += 3;

	// Packet의 마지막에 String의 끝을 알리기 위하여 NULL을 추가한다.
	sendPacket[packetlen] = 0x00;

	// Send Log를 기록
#if	(DEBUG_TCP_COMM_LOG==1)
	CString sLog;
	sLog.Format(_T("<UDP Send> [%s] %s"), ip, char_To_wchar(sendPacket));
	m_pApp->Gf_writeMLog(sLog);
#endif

	// 생성된 Packet을 전송.
	UINT ret = TRUE;
	m_nAckCmdDio[ch] = 0;

	CString ip;
	if (ch == CH1)		ip.Format(_T("%s"), UDP_DIO_BOARD1_IP);
	if (ch == CH2)		ip.Format(_T("%s"), UDP_DIO_BOARD2_IP);
	m_pUDPSocket->SendTo(sendPacket, packetlen, UDP_SOCKET_PORT, ip);//m_pUDPSocket->SendToUDP(ip, packetlen, sendPacket);

	// ACK Receive	
	if (recvACK == ACK)
	{
		if (udp_procWaitRecvACK_DIO(ch, nCommand, waitTime) == TRUE)
			ret = TRUE;
		else
			ret = FALSE;
	}

	return ret;
}

BOOL CVHMOFInspApp::udp_procWaitRecvACK_DIO(int ch, int cmd, DWORD waitTime)
{
	DWORD stTick = ::GetTickCount();

	while (1)
	{
		if (cmd == m_nAckCmdDio[ch])
		{
			return TRUE;
		}

		DWORD edTick = GetTickCount();

		if ((edTick - stTick) > waitTime)
		{
			return FALSE;
		}

		ProcessMessage();
	}
	return FALSE;
}

void CVHMOFInspApp::udp_processDioPacket(int ch, CString strPacket)
{
	int recvCMD = 0;

	// Receive Packet에서 Command 정보를 추출한다.
	recvCMD = _tcstol(strPacket.Mid(PACKET_PT_CMD, 2), NULL, 16);

	// Message 처리
	switch (recvCMD)
	{
		case CMD_DIO_INPUT:
		{
			udp_procParseDIO(ch, strPacket);
			break;
		}

		case CMD_DIO_TIME_OUT:
		{
			break;
		}
	}

	// ACK Receive Check는 모든 Packet처리가 완료된 이후 Set한다.
	m_nAckCmdDio[ch] = recvCMD;
}


BOOL CVHMOFInspApp::udp_procParseDIO(int ch, CString packet)
{
	int retcode;
	BYTE status1 = 0, status2 = 0, status3 = 0, status4 = 0, status5 = 0, tmp = 0;
	retcode = _ttoi(packet.Mid(PACKET_PT_RET, 1));

	if (retcode == 0)
	{
		int ptr = 0, len = 0;
		ptr = PACKET_PT_DATA;
		len = 2;

		status5 = (BYTE)_tcstol(packet.Mid(ptr, len), NULL, 16);
		status5 = ~status5;
		ptr += len;	len = 2;

		status4 = (BYTE)_tcstol(packet.Mid(ptr, len), NULL, 16);
		status4 = ~status4;
		ptr += len;	len = 2;

		status3 = (BYTE)_tcstol(packet.Mid(ptr, len), NULL, 16);
		status3 = ~status3;
		ptr += len;	len = 2;

		status2 = (BYTE)_tcstol(packet.Mid(ptr, len), NULL, 16);
		status2 = ~status2;
		ptr += len;	len = 2;

		status1 = (BYTE)_tcstol(packet.Mid(ptr, len), NULL, 16);
		status1 = ~status1;
		ptr += len;	len = 2;

		m_nDioInBit[ch][4] = status5;
		m_nDioInBit[ch][3] = status4;
		m_nDioInBit[ch][2] = status3;
		m_nDioInBit[ch][1] = status2;
		m_nDioInBit[ch][0] = status1;
	}

	return TRUE;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DIO Interlock
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CVHMOFInspApp::Lf_checkDoorOpenInterLock()
{
	if (DEBUG_DIO_ALARM_DISABLE == 1)
		return TRUE;

	if (m_nDioInBit[CH1][0] & DIN_D1_LEFT_SAFETY_DOOR)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("SAFETY DOOR OPEN"), ERROR_CODE_40);
		return FALSE;
	}
	if (m_nDioInBit[CH1][0] & DIN_D1_RIGHT_SAFETY_DOOR)
	{
		m_pApp->Gf_ShowMessageBox(MSG_ERROR, _T("SAFETY DOOR OPEN"), ERROR_CODE_41);
		return FALSE;
	}

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MELSEC 통신 Function
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CVHMOFInspApp::Lf_getMelsecErrorCode(int mnetg_err)
{
	if (mnetg_err == 0x0001)				return 2001;
	else if (mnetg_err == 0x0002)			return 2002;
	else if (mnetg_err == 0x0042)			return 2003;
	else if (mnetg_err == 0x0044)			return 2004;
	else if (mnetg_err == 0x0045)			return 2005;
	else if (mnetg_err == 0x0046)			return 2006;
	else if (mnetg_err == 0x0047)			return 2007;
	else if (mnetg_err == 0x004D)			return 2008;


#if 0
#define MNETG_ERROR_0055H			_T("SEND/RECV channel number error.")
#define MNETG_ERROR_0064H			_T("Board H/W resource busy.")
#define MNETG_ERROR_0065H			_T("Routing parameter error.")
#define MNETG_ERROR_0066H			_T("Board Driver I/F error. An attempt to send request data to the board driver is failed.")
#define MNETG_ERROR_0067H			_T("Board Driver I/F error. An attempt to receive response data from the board driver is failed.")
#define MNETG_ERROR_0085H			_T("Parameter error. A parameter set on the board is incorrect.")
#define MNETG_ERROR_0085H			_T("Parameter error. A parameter set on the board is incorrect.")
#define MNETG_ERROR_1000H			_T("MELSEC data link library internal error.")
#define MNETG_ERROR_4000H			_T("Error detected by the access target CPU.")
#define MNETG_ERROR_4030H			_T("Device error. The specified device type is invalid.")
#define MNETG_ERROR_4031H			_T("Device error. The specified device number is out of the range.")
#define MNETG_ERROR_4080H			_T("Request data error.")
#define MNETG_ERROR_4A00H			_T("Link-related error.")
#define MNETG_ERROR_4A01H			_T("Link-related error.")
#define MNETG_ERROR_4B02H			_T("The request is not for a CPU module.")
#define MNETG_ERROR_FFFFH			_T("Path error. The specified path is invalid.")
#define MNETG_ERROR_FFFEH			_T("Start device number error.")
#define MNETG_ERROR_FFFDH			_T("Device type error. The specified device type is invalid.")
#define MNETG_ERROR_FFFBH			_T("Size error. The set of start device numberand size is over the device range.")
#define MNETG_ERROR_FFFAH			_T("Number of blocks error.")
#define MNETG_ERROR_FFF8H			_T("Channel number error. The channel number specified with mdOpen function is invalid.")
#define MNETG_ERROR_FFF4H			_T("Block number error. The block number of the specified file register is invalid.")
#define MNETG_ERROR_FFF3H			_T("Write protect error.")
#define MNETG_ERROR_FFF0H			_T("Network number and station number error.")
#define MNETG_ERROR_FFEFH			_T("All station specification and group number specification error.")
#define MNETG_ERROR_FFEEH			_T("Remote command code error.")
#define MNETG_ERROR_FFEDH			_T("SEND/RECV channel number error.")
#define MNETG_ERROR_FFE1H			_T("DLL load error. An attempt to load DLL required to execute the function failed.")
#define MNETG_ERROR_FFE0H			_T("Resource time-out error.")
#define MNETG_ERROR_FFDFH			_T("Incorrect access target error.")
#define MNETG_ERROR_FFDEH			_T("Registry access error.")
#define MNETG_ERROR_FFDBH			_T("Communication initialization setting error.")
#define MNETG_ERROR_FFD6H			_T("Close error. The communication cannot be closed.")
#define MNETG_ERROR_FFD5H			_T("ROM operation error.")
#define MNETG_ERROR_FFC3H			_T("Number of events error.")
#define MNETG_ERROR_FFC2H			_T("Event number error.")
#define MNETG_ERROR_FFC1H			_T("Event number duplicate registration error.")
#define MNETG_ERROR_FFC0H			_T("Timeout time error. The timeout time specified with mdWaitBdEvent function is out of the range.")
#define MNETG_ERROR_FFBFH			_T("Event wait time-out error. An event did not occur within the timeout time.")
#define MNETG_ERROR_FFBEH			_T("Event initialization error.")
#define MNETG_ERROR_FFBDH			_T("No event setting error.")
#define MNETG_ERROR_FFBBH			_T("Unsupported function execution error.")
#define MNETG_ERROR_FFBAH			_T("Event duplication occurrence error.")
#define MNETG_ERROR_FFB9H			_T("Remote device station access error.")
#define MNETG_ERROR_FEFFH			_T("Errors detected in the MELSECNET/H and MELSECNET/10 network system.")
#define MNETG_ERROR_F782H			_T("Transient data target station number error.")
#define MNETG_ERROR_EFFFH			_T("Errors detected in the CC-Link IE Controller network system.")
#define MNETG_ERROR_E218H			_T("Transient data target station number error.")
#define MNETG_ERROR_E208H			_T("Transient data target station number error.")
#define MNETG_ERROR_DFFFH			_T("Errors detected in the CC-Link IE Field network system.")
#define MNETG_ERROR_D25DH			_T("Transient data improper.")
#define MNETG_ERROR_D23BH			_T("Network number error.")
#define MNETG_ERROR_D21EH			_T("Station number error.")
#define MNETG_ERROR_D0A0H			_T("Transient data send response wait time-out error.")
#define MNETG_ERROR_CFFFH			_T("Errors detected in the Ethernet network system.")
#define MNETG_ERROR_BFFFH			_T("Errors detected in the CC-Link system.")
#define MNETG_ERROR_B780H			_T("Module mode setting error.")
#define MNETG_ERROR_B774H			_T("Transient unsupported error.")
#define MNETG_ERROR_9E20H			_T("Processing code error.")
#define MNETG_ERROR_9922H			_T("Reset error.")
#define MNETG_ERROR_9920H			_T("Routing request error on routing function unsupported station.")
#define MNETG_ERROR_9302H			_T("Event wait time-out error.")
#define MNETG_ERROR_9216H			_T("Unsupported block data assurance per station.")
#define MNETG_ERROR_9215H			_T("Link refresh error. Link refresh processing did not operate normally.")
#define MNETG_ERROR_9214H			_T("Incorrect mode setting error. An incorrect mode was specified when setting the mode.")
#define MNETG_ERROR_9213H			_T("System sleep error. Entering sleep mode, hibernation mode, or fast startup was detected.")
#define MNETG_ERROR_9212H			_T("Mode error. A request which cannot be used in the currently set mode was executed.")
#define MNETG_ERROR_9211H			_T("Hardware self-diagnosis error. An error was detected by the hardware self-diagnosis.")
#define MNETG_ERROR_9210H			_T("Hardware self-diagnosis error. An error was detected by the hardware self-diagnosis.")
#define MNETG_ERROR_920AH			_T("Data link disconnected device access error.")
#define MNETG_ERROR_9209H			_T("Abnormal data reception error. An incorrect response data was received.")
#define MNETG_ERROR_9202H			_T("Driver WDT error. Driver WDT error is occurring.")
#define MNETG_ERROR_9032H			_T("Channel busy (dedicated instruction) error.")
#define MNETG_ERROR_9026H			_T("Hardware self-diagnosis error. An error was detected by the hardware self-diagnosis.")
#define MNETG_ERROR_9024H			_T("Hardware self-diagnosis error. An error was detected by the hardware self-diagnosis.")
#endif

	return 200;		// undefined error code
}





