#pragma once

#include <direct.h>
#include <io.h>

class CIniProfileAPI
{
public:
	CIniProfileAPI(void);
	~CIniProfileAPI(void);
};

static TCHAR	wszConv[2048]={0,};
static char		szConv[2048]={0,};
static CString	sRetString;

/////////////////////////////////////////////////////////////////////////////
static void ProcessMessage()
{
	MSG msg;
	if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
static void delayMs(DWORD delay)
{
	__int64 stTick, edTick;

	stTick = ::GetTickCount64();
	while (1)
	{
		edTick = ::GetTickCount64();
		if ((edTick - stTick) >= delay)
			break;

		ProcessMessage();
	}
}
/////////////////////////////////////////////////////////////////////////////
static int _str_to_dec(CString hexStr)
{
	int dwRtnData=0;
	TCHAR tmpdata=0;
	int nLength=0, index=0;

	hexStr.MakeUpper();

	nLength = hexStr.GetLength();
	while(nLength != 0)
	{
		// Hex Char에 해당하는 Decimal 값을 가져온다.
		if(hexStr.GetAt(index)=='0')			tmpdata=0;
		else if(hexStr.GetAt(index)=='1')		tmpdata=1;
		else if(hexStr.GetAt(index)=='2')		tmpdata=2;
		else if(hexStr.GetAt(index)=='3')		tmpdata=3;
		else if(hexStr.GetAt(index)=='4')		tmpdata=4;
		else if(hexStr.GetAt(index)=='5')		tmpdata=5;
		else if(hexStr.GetAt(index)=='6')		tmpdata=6;
		else if(hexStr.GetAt(index)=='7')		tmpdata=7;
		else if(hexStr.GetAt(index)=='8')		tmpdata=8;
		else if(hexStr.GetAt(index)=='9')		tmpdata=9;
		else if(hexStr.GetAt(index)=='A')		tmpdata=10;
		else if(hexStr.GetAt(index)=='B')		tmpdata=11;
		else if(hexStr.GetAt(index)=='C')		tmpdata=12;
		else if(hexStr.GetAt(index)=='D')		tmpdata=13;
		else if(hexStr.GetAt(index)=='E')		tmpdata=14;
		else if(hexStr.GetAt(index)=='F')		tmpdata=15;

		// 결과 값을 누적한다.
		dwRtnData += tmpdata;

		// Index 값을 증가 시킨다.
		index++;

		// 마지막 Data이면 while문을 빠져 나간다.
		if(nLength == index)	break;

		// 누적된 Data 값을 Shift 시킨다.
		dwRtnData <<= 4;
	}

	return dwRtnData;
}

/////////////////////////////////////////////////////////////////////////////
static void char_To_wchar(char* szOrg, wchar_t* wszConv)
{
	// char*형의 모델명을 wchar 형태의 모델명으로 변환.
	int mlen = (int)strlen(szOrg);
	int wlen = 0;
	wlen		= MultiByteToWideChar(CP_ACP,0,szOrg,mlen,NULL,0);
	memset((void*)wszConv, 0, sizeof(WCHAR)*(wlen+1));
	wlen		= MultiByteToWideChar(CP_ACP,0,szOrg,mlen,wszConv,wlen);
}

static wchar_t* char_To_wchar(char* szOrg)
{
	// char*형의 모델명을 wchar 형태의 모델명으로 변환.
	int mlen = (int)strlen(szOrg);
	int wlen = 0;
	wlen		= MultiByteToWideChar(CP_ACP,0,szOrg,mlen,NULL,0);
	memset((void*)wszConv, 0, sizeof(WCHAR)*(wlen+1));
	wlen		= MultiByteToWideChar(CP_ACP,0,szOrg,mlen,wszConv,wlen);

	return wszConv;
}

static void wchar_To_char(wchar_t* wszOrg, char* szConv)
{
	//먼저 길이를 구한다.
	int nMultiByteLen = WideCharToMultiByte(CP_ACP, 0, wszOrg, -1, NULL, 0, NULL,NULL);
	//변환한다.
	WideCharToMultiByte(CP_ACP, 0, wszOrg, -1, szConv, nMultiByteLen, NULL, NULL);
}

static char* wchar_To_char(wchar_t* wszOrg)
{
	//먼저 길이를 구한다.
	int nMultiByteLen = WideCharToMultiByte(CP_ACP, 0, wszOrg, -1, NULL, 0, NULL,NULL);
	//변환한다.
	WideCharToMultiByte(CP_ACP, 0, wszOrg, -1, szConv, nMultiByteLen, NULL, NULL);

	return szConv;
}


static int CALLBACK BrowseForFolder_CallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if(uMsg == BFFM_INITIALIZED)
		SendMessage(hwnd, BFFM_SETSELECTION, (WPARAM)TRUE, (LPARAM)lpData);
	return 0;

}

static void Write_ProfileString(LPCWSTR lpFileName, LPCWSTR lpTitle, LPCWSTR lpKey, LPCWSTR lpValue)
{
	::WritePrivateProfileString(lpTitle, lpKey, lpValue, lpFileName);
}

static void Write_SysIniFile(LPCWSTR lpTitle, LPCWSTR lpKey, LPCWSTR lpValue)
{

	::WritePrivateProfileString(lpTitle, lpKey, lpValue, _T(".\\Operation.ini"));
}

static void Write_SysIniFile(LPCWSTR lpTitle, LPCWSTR lpKey, long nData)
{
	CString szData;

	szData.Format(_T("%d"), nData);
	::WritePrivateProfileString(lpTitle, lpKey, szData, _T(".\\Operation.ini"));
}
static void Write_CB_CICFile(LPCWSTR lpTitle, LPCWSTR lpKey, long nData)
{
	CString szData;

	szData.Format(_T("%d"), nData);
	::WritePrivateProfileString(lpTitle, lpKey, szData, _T(".\\LGD_CB_CIC_INI.ini"));
}

static void Read_SysIniFile(LPCWSTR lpTitle, LPCWSTR lpKey, char *szRetString)
{
	wchar_t wszData[100] = {0,};


	memset(szRetString,'\0',sizeof(szRetString));
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\Operation.ini"));

	wchar_To_char(wszData, szRetString);
}

static void Read_SysIniFile(LPCWSTR lpTitle, LPCWSTR lpKey, int *pRetValue)
{
	wchar_t wszData[100] = {0,};
	char szData[50] = {0,};


	*pRetValue = 0;
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\Operation.ini"));        

	wchar_To_char(wszData, szData);
	*pRetValue = atoi(szData);
}

static void Read_SysIniFile(LPCWSTR lpTitle, LPCWSTR lpKey, CString *szRetString)
{
	wchar_t wszData[100] = {0,};

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\Operation.ini"));

	szRetString->Format(_T("%s"), wszData);
}

static void Read_SysIniFile(LPCWSTR lpTitle, LPCWSTR lpKey, TCHAR *wszRetString)
{
	wchar_t wszData[100] = {0,};

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\Operation.ini"));
	wcscpy_s(wszRetString, (wcslen(wszData)+1), wszData);
}

static void Write_ModelFile(LPCWSTR lpModelName, LPCWSTR lpTitle, LPCWSTR lpKey, LPCWSTR lpValue)
{
	CString szModelPath;

	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);
	::WritePrivateProfileString(lpTitle, lpKey, lpValue, szModelPath);        
}

static void Write_ModelFile(LPCWSTR lpModelName, LPCWSTR lpTitle, LPCWSTR lpKey, int ndata)
{
	CString szData;
	CString szModelPath;

	szData.Format(_T("%d"), ndata);
	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);
	::WritePrivateProfileString(lpTitle, lpKey, szData, szModelPath);        
}

static void Write_ModelFile(LPCWSTR lpModelName, LPCWSTR lpTitle, LPCWSTR lpKey, long nData)
{
	CString szData;
	CString szModelPath;

	szData.Format(_T("%d"), nData);
	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);
	::WritePrivateProfileString(lpTitle, lpKey, szData, szModelPath);        
}

static void Write_ModelFile(LPCWSTR lpModelName, LPCWSTR lpTitle, LPCWSTR lpKey, double fdata)
{
	CString szData;
	CString szModelPath;

	szData.Format(_T("%f"), fdata);
	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);
	::WritePrivateProfileString(lpTitle, lpKey, szData, szModelPath);        
}

static void Read_ProfileString(LPCWSTR lpFileName, LPCWSTR lpSection, LPCWSTR lpKey, CString *retValue)
{
	wchar_t wszData[512] = {0,};
	::GetPrivateProfileString(lpSection, lpKey, 0, wszData, sizeof(wszData), lpFileName);

	retValue->Format(_T("%s"), wszData);
}

static void Read_ModelFile(CString sModelName, LPCWSTR lpTitle, LPCWSTR lpKey, CString *szRetString)
{
	wchar_t wszData[100] = {0,};
	CString sModelPath;

	// 모델 File 경로 설정
	sModelPath.Format(_T(".\\Model\\%s.MOD"), sModelName);

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), sModelPath);

	szRetString->Format(_T("%s"), wszData);
}

static void Read_ModelFile(CString sModelName, LPCWSTR lpTitle, LPCWSTR lpKey, char *szRetString)
{
	wchar_t wszData[100] = { 0, };
	CString sModelPath;

	// Return Memory Initialize
	memset(szRetString,'\0',sizeof(szRetString));

	// 모델 File 경로 설정
	sModelPath.Format(_T(".\\Model\\%s.MOD"), sModelName);

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), sModelPath);

	wchar_To_char(wszData, szRetString);
}

static void Read_ModelFile(CString sModelName, LPCWSTR lpTitle, LPCWSTR lpKey, int *pRetValue)
{
	CString sModelPath, sdata;
	wchar_t wszData[100] = {0,};
	char szData[50] = {0,};

	// 모델 File 경로 설정
	*pRetValue = 0;
	sModelPath.Format(_T(".\\Model\\%s.MOD"), sModelName);

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), sModelPath);

	sdata.Format(_T("%s"), wszData);
	*pRetValue = _ttoi(sdata);
}

static void Read_ModelFile(CString sModelName, LPCWSTR lpTitle, LPCWSTR lpKey, LONG *pRetValue)
{
	CString sModelPath, sdata;
	wchar_t wszData[100] = {0,};
	wchar_t wszModel[100] = {0,};

	// 모델 File 경로 설정
	sModelPath.Format(_T(".\\Model\\%s.MOD"), sModelName);

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), sModelPath);

	sdata.Format(_T("%s"), wszData);
	*pRetValue = _tcstol(sdata, NULL, 10);
}

static void Read_ModelFile(CString sModelName, LPCWSTR lpTitle, LPCWSTR lpKey, float *pRetValue)
{
	CString sModelPath, sdata;
	wchar_t wszData[100] = {0,};
	char szData[50] = {0,};

	// 모델 File 경로 설정
	sModelPath.Format(_T(".\\Model\\%s.MOD"), sModelName);

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), sModelPath);        

	sdata.Format(_T("%s"), wszData);
	*pRetValue = (float)_tstof(sdata);
}

static void Read_ModelFile(CString sModelName, LPCWSTR lpTitle, LPCWSTR lpKey, double *pRetValue)
{
	CString sModelPath, sdata;
	wchar_t wszData[100] = { 0, };
	char szData[50] = { 0, };

	// 모델 File 경로 설정
	sModelPath.Format(_T(".\\Model\\%s.MOD"), sModelName);

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), sModelPath);

	sdata.Format(_T("%s"), wszData);
	*pRetValue = (float)_tstof(sdata);
}

static void Read_SummaryFile(LPCWSTR lpTitle, LPCWSTR lpKey, int *pRetValue)
{
	wchar_t wszData[100] = {0,};
	char szData[50] = {0,};

	*pRetValue = 0;
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\Summary.ini"));        

	wchar_To_char(wszData, szData);
	*pRetValue = atoi(szData);
}

static void Read_SummaryFile(LPCWSTR lpTitle, LPCWSTR lpKey, char *szRetString)
{
	wchar_t wszData[100] = {0,};


	memset(szRetString,'\0',sizeof(szRetString));
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\Summary.ini"));        

	wchar_To_char(wszData, szRetString);
}

static void Read_SummaryFile(LPCWSTR lpTitle, LPCWSTR lpKey, CString *szRetString)
{
	wchar_t wszData[100] = {0,};

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\Summary.ini"));

	szRetString->Format(_T("%s"), wszData);
}

static void Write_WDRRequestInform(LPCWSTR lpWdrFileName, LPCWSTR lpTitle, LPCWSTR lpKey, CString strValue)
{
	::WritePrivateProfileString(lpTitle, lpKey, strValue, lpWdrFileName);
}

static void Write_AgingRackIniFile(LPCWSTR lpTitle, LPCWSTR lpKey, LPCWSTR lpValue)
{

	::WritePrivateProfileString(lpTitle, lpKey, lpValue, _T(".\\AgingInfo.ini"));        
}

static void Write_AgingRackIniFile(LPCWSTR lpTitle, LPCWSTR lpKey, int nData)
{
	CString szData;

	szData.Format(_T("%d"), nData);
	::WritePrivateProfileString(lpTitle, lpKey, szData, _T(".\\AgingInfo.ini"));        
}

static void Read_AgingRackIniFile(LPCWSTR lpTitle, LPCWSTR lpKey, char *szRetString)
{
	wchar_t wszData[100] = {0,};


	memset(szRetString,'\0',sizeof(szRetString));
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\AgingInfo.ini"));        

	wchar_To_char(wszData, szRetString);
}

static void Read_AgingRackIniFile(LPCWSTR lpTitle, LPCWSTR lpKey, int *pRetValue)
{
	wchar_t wszData[100] = {0,};
	char szData[50] = {0,};


	*pRetValue = 0;
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\AgingInfo.ini"));        

	wchar_To_char(wszData, szData);
	*pRetValue = atoi(szData);
}

static void Read_AgingRackIniFile(LPCWSTR lpTitle, LPCWSTR lpKey, CString *szRetString)
{
	wchar_t wszData[100] = {0,};
	wchar_t wszModel[100] = {0,};
	CString szModelPath;

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\AgingInfo.ini"));

	szRetString->Format(_T("%s"), wszData);
}

static void Write_AgingPatternGroup(LPCWSTR wszAPGPath, LPCWSTR lpTitle, LPCWSTR lpKey, LPCWSTR lpValue)
{
	::WritePrivateProfileString(lpTitle, lpKey, lpValue, wszAPGPath);        
}

static void Write_AgingPatternGroup(LPCWSTR wszAPGPath, LPCWSTR lpTitle, LPCWSTR lpKey, int nValue)
{
	CString strValue;

	strValue.Format(_T("%d"), nValue);
	::WritePrivateProfileString(lpTitle, lpKey, strValue, wszAPGPath);        
}
static void Write_AgingPatternGroup(LPCWSTR wszAPGPath, LPCWSTR lpTitle, LPCWSTR lpKey, float fValue)
{
	CString strValue;

	strValue.Format(_T("%.1f"), fValue);
	::WritePrivateProfileString(lpTitle, lpKey, strValue, wszAPGPath);        
}

static void Read_AgingPatternGroup(LPCWSTR wszAPGPath, LPCWSTR lpTitle, LPCWSTR lpKey, CString *szRetString)
{
	wchar_t wszData[100] = {0,};

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), wszAPGPath);

	szRetString->Format(_T("%s"), wszData);
}

static void Read_MV15A_U77_YB_ErrorCode(LPCWSTR lpTitle, LPCWSTR lpKey, CString *szRetString)
{
	wchar_t wszData[100] = {0,};

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\MV15_U77A_YB_Error_Code.ini"));

	szRetString->Format(_T("%s"), wszData);
}
static void Read_MV16A_U77_YB_ErrorCode(LPCWSTR lpTitle, LPCWSTR lpKey, CString *szRetString)
{
	wchar_t wszData[100] = {0,};

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\MV16_U77A_YB_Error_Code.ini"));

	szRetString->Format(_T("%s"), wszData);
}

static void Write_MV15A_U77_YB_WPD(LPCWSTR lpTitle, LPCWSTR lpKey, int nValue)
{
	CString szData;

	szData.Format(_T("%d"), nValue);
	::WritePrivateProfileString(lpTitle, lpKey, szData, _T(".\\WPD\\WPD.ini"));
}
static void Read_MV15A_U77_YB_WPD(LPCWSTR lpTitle, LPCWSTR lpKey, int *pRetValue)
{
	wchar_t wszData[100] = {0,};
	char szData[50] = {0,};


	*pRetValue = 0;
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\WPD\\WPD.ini"));

	wchar_To_char(wszData, szData);
	*pRetValue = atoi(szData);
}

static void Read_MV15A_U77_YB_WPD(LPCWSTR lpTitle, LPCWSTR lpKey, CString *pstrRetString)
{
	wchar_t wszData[100] = {0,};

	pstrRetString->Empty();
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\WPD\\WPD.ini"));

	pstrRetString->Format(_T("%s"), wszData);
}

static void Read_MV15A_U77_ADDLD_Result(LPCWSTR lpFileName, LPCWSTR lpTitle, LPCWSTR lpKey, CString *pstrRetString)
{
	wchar_t wszData[100] = {0,};

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), lpFileName);

	pstrRetString->Format(_T("%s"), wszData);
}

static void Write_AgingErrorLog(int rackID, int channel, CString strError, CString strErrPattern)
{
	FILE *fp;

	char buff1[1024]={0,};
	char buff2[1024]={0,};
	char buff3[1024]={0,};
	char filepath[50]={0,};
	char szLine[1024]={0,};

	CString strDate;
	CString strTime;

	SYSTEMTIME sysTime;
	::GetSystemTime (&sysTime);
	CTime time = CTime::GetCurrentTime ();

	strDate.Format(_T("%04d%02d%02d"), time.GetYear(), time.GetMonth(), time.GetDay());
	strTime.Format(_T("%02d:%02d:%02d"), time.GetHour(), time.GetMinute(), time.GetSecond());


	// 1. Aging Log폴더를 찾아 File을 Open하고 없으면 폴더와 파일을 생성한다.
	wchar_To_char(strDate.GetBuffer(0), buff1);
	sprintf_s(filepath, sizeof(filepath), ".\\Aging_Log\\%s_AgingLog.txt", buff1);
	fopen_s(&fp, filepath, "a+");
	if (fp == NULL)
	{
		if( (_access( ".\\Aging_Log", 0 )) == -1 )
			_mkdir ( ".\\Aging_Log" );

		fopen_s (&fp, filepath, "a+");
		if (fp == NULL) // 2007-08-01 : fseek.c(101) error
		{
			if( (_access( filepath, 2 )) != -1 ) // 2007-09-02 : fseek.c(101) error
			{
				fopen_s (&fp, filepath, "a+");
			}
		}
	}
	fseek (fp, 0L, SEEK_END);

	// 2. Aging Log Data를 Write한다.

	// 2.1 줄바꿈은 @@로 대체하여 File에 저장한다. 보여줄때는 원복시킨다.
	strError.Replace(_T("\r\n"), _T("@@"));

	wchar_To_char(strTime.GetBuffer(0), buff1);
	wchar_To_char(strError.GetBuffer(0), buff2);
	wchar_To_char(strErrPattern.GetBuffer(0), buff3);
	sprintf_s(szLine, "%d\t%d\t%s\t%s\t%s\r\n", rackID, (channel+1), buff1, buff2, buff3);
	fwrite(szLine, sizeof(char), strlen(szLine), fp);

	// 3. File을 닫는다.
	fclose(fp);
}


static int Read_AgingErrorLog(CString lpDate, int *rackID, int *channel, CString *lpTime, CString *lpResult, CString *lpErrPattern, int maxlogcount)
{
	int linecount=0;
	CStdioFile cfile;
	CString filepath;
	CString readline;

	// 변수 초기화
	*rackID = 0xFF;
	lpTime[0].Format(_T(""));
	lpResult[0].Format(_T(""));

	// File을 읽는다.
	filepath.Format(_T(".\\Aging_Log\\%s_AgingLog.txt"), lpDate);

	// File을 Open한다.
	if(cfile.Open(filepath, CFile::modeRead | CFile::typeText))
	{
		while(cfile.ReadString(readline))
		{
			CString resToken;
			int curPos=0;

			resToken= readline.Tokenize(_T("\t"),curPos);
			rackID[linecount] = _ttoi(resToken);

			resToken= readline.Tokenize(_T("\t"),curPos);
			channel[linecount] = _ttoi(resToken);

			resToken= readline.Tokenize(_T("\t"),curPos);
			lpTime[linecount].Format(_T("%s"), resToken);

			resToken= readline.Tokenize(_T("\t"),curPos);
			lpResult[linecount].Format(_T("%s"), resToken);

			resToken= readline.Tokenize(_T("\t"),curPos);
			lpErrPattern[linecount].Format(_T("%s"), resToken);

			lpResult[linecount].Replace(_T("@@"), _T("\r\n"));

			linecount++;

			if(linecount > maxlogcount)	break;
		}

		cfile.Close();
	}

	return linecount;
}

static CString Read_GBSettingValue(CString keyString)
{
	CStdioFile* pFile;
	CString readString=_T("");

	sRetString.Empty();
	pFile = new CStdioFile();

	if (pFile->Open(_T("GB_Setting.txt"), CStdioFile::modeRead | CStdioFile::typeText)==NULL)
	{
		if(pFile->Open(_T("GB_Value.txt"), CStdioFile::modeRead | CStdioFile::typeText)==NULL)
		{
			AfxMessageBox(_T("GB_Value.txt 파일을 열수 없습니다."), MB_ICONERROR);	
			delete pFile;
			return FALSE;
		}
	}
	

	// Line이 Null일때까지 읽는다.
	while(pFile->ReadString(readString)==TRUE)
	{
		// String의 예외처리 부분을 추가한다.
		readString.TrimLeft();
		readString.TrimRight();

		// CA310 Channel 정보가 저장된 Line을 찾는다.
		if(readString.Left(keyString.GetLength()) == keyString)
		{
			// CA310 Channel 정보를 Parsing 한다.
			sRetString = readString.Mid(readString.Find(_T(" "))+1);

			sRetString.TrimLeft();
			sRetString.TrimRight();

			break;
		}
	}

	pFile->Close();
	delete pFile;

	return sRetString;
}
static void Write_WinMessageFrom(CString strDlgName , CString strFileName)
{
	::WritePrivateProfileString(_T("Default Setting"),_T("Windows_Name"), strDlgName, strFileName);
}
static void Read_YBSettingFile(LPCWSTR lpFileName, LPCWSTR lpTitle, LPCWSTR lpKey, CString *pstrRetString)
{
	wchar_t wszData[100] = {0,};

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), lpFileName);
	for (int i=0; i<100; i++)
	{
		if(wszData[i] == 0x09)	break;
		if(wszData[i] == 0x00)	break;
		if(wszData[i] == 0x20)	break;
		pstrRetString->Insert(i,wszData[i]);
		
	}
	pstrRetString->MakeUpper();
	//pstrRetString->Format(_T("%s"), wszData);
}
static void Write_YBSettingFile(LPCWSTR lpDlgName ,LPCWSTR lpTitle ,LPCWSTR lpKey ,LPCWSTR lpData)
{
	CString strFilePath;

	strFilePath.Format(_T(".\\%s"),lpDlgName);

	::WritePrivateProfileString(lpTitle,lpKey, lpData,strFilePath);
}
static void Read_UHD_ADPD_Result(LPCWSTR lpFileName, LPCWSTR lpTitle, LPCWSTR lpKey, CString *pstrRetString)
{
	wchar_t wszData[100] = {0,};

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), lpFileName);

	pstrRetString->Format(_T("%s"), wszData);
}

static bool measureCA310_Multi(double &Lv, double &x, double &y, double &Lv_01, double &x_01, double &y_01, double &Lv_02, double &x_02, double &y_02, double &Lv_03, double &x_03, double &y_03)
{
	Lv_01 = 0;
	x_01 = 0;
	y_01 = 0;
	Lv_02 = 0;
	x_02 = 0;
	y_02 = 0;
	Lv_03 = 0;
	x_03 = 0;
	y_03 = 0;

	return FALSE;
}
static void Read_CB_ErrorCode(LPCWSTR lpTitle, LPCWSTR lpKey, CString *szRetString)
{
	wchar_t wszData[100] = {0,};

	szRetString->Empty();
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\CB_Error_Code.ini"));

	szRetString->Format(_T("%s"), wszData);
}
static void Read_CB_Setting(LPCWSTR lpTitle, LPCWSTR lpKey, int *pRetValue)
{
	wchar_t wszData[100] = {0,};
	char szData[50]; 

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\CB_Setting.ini"));

	wchar_To_char(wszData, szData);

	*pRetValue = atoi(szData);
}
static void Read_CB_Setting(LPCWSTR lpTitle, LPCWSTR lpKey, CString *szRetString)
{
	wchar_t wszData[100] = {0,};

	szRetString->Empty();
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\CB_Setting.ini"));

	szRetString->Format(_T("%s"),wszData);
}
static void Read_YCB_Setting(LPCWSTR lpTitle, LPCWSTR lpKey, int *pRetValue)
{
	wchar_t wszData[100] = {0,};
	char szData[50]; 

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\YCB_Setting.ini"));

	wchar_To_char(wszData, szData);

	*pRetValue = atoi(szData);
}
static void Read_YCB_Setting(LPCWSTR lpTitle, LPCWSTR lpKey, CString *szRetString)
{
	wchar_t wszData[100] = {0,};

	szRetString->Empty();
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\YCB_Setting.ini"));

	szRetString->Format(_T("%s"),wszData);
}
static void Read_YCB_Setting(LPCWSTR lpTitle, LPCWSTR lpKey, LONG *pRetValue)
{
	wchar_t wszData[100] = {0,};


	// 모델 File 경로 설정
	*pRetValue = 0;

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\YCB_Setting.ini"));        

	*pRetValue = wcstol(wszData, NULL, 10);
}
static void Write_YCB_Setting(LPCWSTR lpTitle, LPCWSTR lpKey, CString szRetString)
{
	wchar_t wszData[100] = {0,};

	::WritePrivateProfileString(lpTitle, lpKey, szRetString, _T(".\\YCB_Setting.ini"));
}
static void Write_CB_Setting(LPCWSTR lpTitle, LPCWSTR lpKey, CString szRetString)
{
	wchar_t wszData[100] = {0,};

	::WritePrivateProfileString(lpTitle, lpKey, szRetString, _T(".\\CB_Setting.ini"));
}
static void Read_CB_Uniformity(char* lpSavePath, LPCWSTR lpTitle, LPCWSTR lpKey, double *pRetValue)
{
	wchar_t wszData[100] = {0,};
	wchar_t wszSavePath[200]={0,};
	CString strPath;
	char szData[50]={0,}; 


	char_To_wchar(lpSavePath,wszSavePath);
	strPath.Format(_T("%s"),wszSavePath);
	*pRetValue=0;

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), strPath);

	wchar_To_char(wszData, szData);

	*pRetValue =atof(szData);
}
static void Read_CB_Uniformity(char* lpSavePath,LPCWSTR lpTitle, LPCWSTR lpKey, CString *szRetString)
{
	wchar_t wszData[100] = {0,};
	wchar_t wszSavePath[200]={0,};
	CString strPath;

	szRetString->Empty();
	char_To_wchar(lpSavePath,wszSavePath);
	strPath.Format(_T("%s"),wszSavePath);

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), strPath);

	szRetString->Format(_T("%s"),wszData);
}

static void Read_ErrorCode(LPCWSTR lpTitle, LPCWSTR lpKey, CString *szRetString)
{
	wchar_t wszData[100] = {0,};

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\Error_Code.ini"));

	szRetString->Format(_T("%s"), wszData);

// 	int pos=0;
// 	pos=szRetString->Find(_T("="),0);
// 	if (pos!=-1)
// 	{
// 		szRetString->Delete(0,pos+1);
// 		pos=szRetString->Find(_T("="),0);
// 		if (pos!=-1)
// 		{
// 			szRetString->Delete(pos,szRetString->GetLength()-pos);
// 		}
// 	}
}
static void Read_WdrResult_Info(LPCWSTR lpFilePath, LPCWSTR lpTitle, LPCWSTR lpKey, CString *szRetString)
{
	wchar_t wszData[100] = {0,};

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), lpFilePath);

	szRetString->Format(_T("%s"), wszData);
}
static void Write_WorkLog_Data(LPCWSTR lpPath, LPCWSTR lpKey, CString szRetString)
{
	wchar_t wszData[100] = {0,};

	LPCWSTR lpTitle=_T("NO");

	::WritePrivateProfileString(lpTitle,lpKey, szRetString, lpPath);
}


static CString GetDefectIniProfileString(CString fileName, CString section, CString key)
{
	BOOL bRead = TRUE;
	CString lineStringW;

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	FILE* fStream = NULL;
	wchar_t* pFilePath = (wchar_t*)fileName.GetBuffer();
	errno_t e = _tfopen_s(&fStream, pFilePath, _T("rt,ccs=UNICODE"));	// rt가 핵심

	if (!e)
	{
		CStdioFile cfile(fStream);

		BOOL bAppendBDINFO = FALSE, bAppendWDRINFO = FALSE;

		section.Insert(0, _T("["));
		section.Append(_T("]"));
		while (cfile.ReadString(lineStringW))
		{
			lineStringW.Replace(_T("\n"), _T(""));
			lineStringW.Replace(_T("\r"), _T(""));

			if (!lineStringW.Compare(section))
			{
				int len;
				key.Append(_T("="));
				len = key.GetLength();
				while (cfile.ReadString(lineStringW))
				{
					lineStringW.TrimLeft();
					lineStringW.TrimRight();

					// 다음 Section을 만나면 Return한다.
					if (lineStringW.Left(1) == _T("["))
						break;

					if (lineStringW.Left(len) == key)
					{
						lineStringW.Delete(0, len);
						cfile.Close();

						return lineStringW;
					}
				}
				break;
			}
		}
		cfile.Close();
	}

	return _T("");
}

static void Read_DefectIniFile(CString fileName, LPCWSTR lpSection, LPCWSTR lpKey, CString* pRetValue)
{
	CString sdata;
	sdata = GetDefectIniProfileString(fileName, lpSection, lpKey);
	pRetValue->Format(_T("%s"), sdata);
}