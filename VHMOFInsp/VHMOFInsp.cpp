﻿
// VHMOFInsp.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "VHMOFInsp.h"
#include "VHMOFInspDlg.h"
#include "CMessageError.h"

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
	commApi				= new CCommApi;


	m_pStaticMainLog = NULL;
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
		AfxMessageBox(_T("Program is running!!!"));
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
		TRACE(traceAppMsg, 0, "경고: 대화 상자를 만들지 못했으므로 애플리케이션이 예기치 않게 종료됩니다.\n");
		TRACE(traceAppMsg, 0, "경고: 대화 상자에서 MFC 컨트롤을 사용하는 경우 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS를 수행할 수 없습니다.\n");
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	SYSTEMTIME sysTime;
	::GetSystemTime(&sysTime);
	CTime time = CTime::GetCurrentTime();
	strLog.Format(_T("[%02d:%02d:%02d %03d] %06d%03d\t: %s\r\n"), time.GetHour(), time.GetMinute(), time.GetSecond(), sysTime.wMilliseconds, (time.GetHour() * 3600) + (time.GetMinute() * 60) + time.GetSecond(), sysTime.wMilliseconds, sLogData);


	strFileName.Format(_T("%s_%04d%02d%02d"), _T("TEST"), time.GetYear(), time.GetMonth(), time.GetDay());
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

BOOL CVHMOFInspApp::Gf_ShowMessageBox(int msg_type, CString strTitle, CString strMessage)
{
	CMessageError errDlg;
	errDlg.m_nMessageType	= msg_type;
	errDlg.m_sErrorTitle	= strTitle;
	errDlg.m_sErrorMessage	= strMessage;
	errDlg.DoModal();

	return FALSE;
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
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// Model File Load
////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CVHMOFInspApp::Lf_FindModelFile()
{
	CString lastModel;
	BOOL ret = FALSE;

	WIN32_FIND_DATA wfd;
	HANDLE hSearch;
	int nLoof = 1;

	hSearch = FindFirstFile(_T(".\\Model\\*.MOD"), &wfd);

	lastModel.Format(_T("%s.MOD"), lpSystemInfo->m_sLastModelName);
	if (hSearch != INVALID_HANDLE_VALUE)
	{

		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			while (nLoof)
			{
				// 대/소문자 구분하지 않고 Compare한다. (CompareNoCase)
				if (lastModel.CompareNoCase(wfd.cFileName)) // When model file is't existed in folder, this sentence is executed. : Difference
				{
					nLoof = FindNextFile(hSearch, &wfd);
					if (nLoof == 0)
					{
						// Model Load Fail
						ret = FALSE;
						break;
					}
				}

				if (!lastModel.CompareNoCase(wfd.cFileName)) // When model file is existed in folder, this sentence is executed. : equal
				{
					//ModelName.mol setting
					ret = TRUE;
					break;
				}
			}
		}
		FindClose(hSearch);
	}
	else // case : When Model folder is empty,
	{
		ret = FALSE;
		FindClose(hSearch);
	}

	return ret;
}

BOOL CVHMOFInspApp::Gf_LoadSystemData()
{
	CString sValue = _T("");

	Read_SysIniFile(_T("SYSTEM_CONFIG"),	_T("LAST_MODELNAME"),			&lpSystemInfo->m_sLastModelName);
	Read_SysIniFile(_T("SYSTEM_CONFIG"),	_T("STATION_NO"),				&lpSystemInfo->m_sStationNo);

	Read_SysIniFile(_T("QUANTITY"),			_T("QTY_GOOD"),					&lpSystemInfo->m_nQuantityOK);
	Read_SysIniFile(_T("QUANTITY"),			_T("QTY_NG"),					&lpSystemInfo->m_nQuantityNG);

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

void CVHMOFInspApp::Lf_LoadModelData(CString modelName)
{
	CString sValue=_T("");

	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VCC"), &lpModelInfo->m_fPowerVcc);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VEL"), &lpModelInfo->m_fPowerVel);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VCC_OFFSET"), &lpModelInfo->m_fPowerVccOffset);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VEL_OFFSET"), &lpModelInfo->m_fPowerVelOffset);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VCC_LIMIT_LOW"), &lpModelInfo->m_fLimitVccLow);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VCC_LIMIT_High"), &lpModelInfo->m_fLimitVccHigh);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VEL_LIMIT_LOW"), &lpModelInfo->m_fLimitVelLow);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("VEL_LIMIT_High"), &lpModelInfo->m_fLimitVelHigh);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("ICC_LIMIT_LOW"), &lpModelInfo->m_fLimitIccLow);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("ICC_LIMIT_High"), &lpModelInfo->m_fLimitIccHigh);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("IEL_LIMIT_LOW"), &lpModelInfo->m_fLimitIelLow);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("IEL_LIMIT_High"), &lpModelInfo->m_fLimitIelHigh);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX1"), &lpModelInfo->m_nPowerOnSeq1);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX2"), &lpModelInfo->m_nPowerOnSeq2);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX3"), &lpModelInfo->m_nPowerOnSeq3);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX4"), &lpModelInfo->m_nPowerOnSeq4);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX5"), &lpModelInfo->m_nPowerOnSeq5);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_INDEX6"), &lpModelInfo->m_nPowerOnSeq6);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX1"), &lpModelInfo->m_nPowerOffSeq1);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX2"), &lpModelInfo->m_nPowerOffSeq2);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX3"), &lpModelInfo->m_nPowerOffSeq3);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX4"), &lpModelInfo->m_nPowerOffSeq4);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX5"), &lpModelInfo->m_nPowerOffSeq5);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_INDEX6"), &lpModelInfo->m_nPowerOffSeq6);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY1"), &lpModelInfo->m_nPowerOnDelay1);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY2"), &lpModelInfo->m_nPowerOnDelay2);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY3"), &lpModelInfo->m_nPowerOnDelay3);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY4"), &lpModelInfo->m_nPowerOnDelay4);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY5"), &lpModelInfo->m_nPowerOnDelay5);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_ON_DELAY6"), &lpModelInfo->m_nPowerOnDelay6);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY1"), &lpModelInfo->m_nPowerOffDelay1);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY2"), &lpModelInfo->m_nPowerOffDelay2);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY3"), &lpModelInfo->m_nPowerOffDelay3);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY4"), &lpModelInfo->m_nPowerOffDelay4);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY5"), &lpModelInfo->m_nPowerOffDelay5);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("POWER_SEQ_OFF_DELAY6"), &lpModelInfo->m_nPowerOffDelay6);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("PXEL_TYPE"), &lpModelInfo->m_nPixelType);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("SIGNAL_BIT"), &lpModelInfo->m_nSignalBit);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("ROTATE"), &lpModelInfo->m_nSignalRotate);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("SIGNAL_TYPE"), &lpModelInfo->m_nSignalType);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("BIT_SELECT"), &lpModelInfo->m_nBitSelect);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("FRS_MODE"), &lpModelInfo->m_nFrsMode);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("CLOCK_DELAY"), &lpModelInfo->m_nClockDelay);
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


	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("I2C_PULL_UP"), &lpModelInfo->m_nI2cPullUp);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("I2C_FREQUENCY"), &lpModelInfo->m_nI2cClock);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("I2C_LEVEL"), &lpModelInfo->m_nI2cLevel);

	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("QSPI_CLOCK"), &lpModelInfo->m_nSpiClock);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("QSPI_LEVEL"), &lpModelInfo->m_nSpiLevel);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("QSPI_PULL_UP"), &lpModelInfo->m_nSpiPullUp);

	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("GPIO_PULL_UP"), &lpModelInfo->m_nGpioPullUp);
	Read_ModelFile(modelName, _T("MODEL_DATA"), _T("GPIO_LEVEL"), &lpModelInfo->m_nGpioLevel);

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

BOOL CVHMOFInspApp::Gf_LoadModelFile()
{
	BOOL ret = TRUE;

	// Model File을 Loading 한다.
	if (Lf_FindModelFile() == TRUE)
	{
		Lf_LoadModelData(lpSystemInfo->m_sLastModelName);
	}
	else
	{
		ret = FALSE;

		CString sMsg;
		sMsg.Format(_T("'%s' Model File Not Found !"), lpSystemInfo->m_sLastModelName);
		AfxMessageBox(sMsg, MB_ICONERROR);
	}

	return ret;
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


