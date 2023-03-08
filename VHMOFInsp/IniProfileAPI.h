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
	//if (PeekMessage( &msg, 0, 0, 500, PM_REMOVE ) )
	if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
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

static void Read_SysIniFile(LPCWSTR lpTitle, LPCWSTR lpKey, BYTE* pRetValue)
{
	wchar_t wszData[100] = { 0, };
	char szData[50] = { 0, };

	*pRetValue = 0;
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\Operation.ini"));

	wchar_To_char(wszData, szData);
	*pRetValue = (BYTE)atoi(szData);
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

static void Read_SysIniFile(LPCWSTR lpTitle, LPCWSTR lpKey, float* fRetValue)
{
	wchar_t wszData[100] = { 0, };

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\Operation.ini"));
	*fRetValue = (float)_tstof(wszData);
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

static void Write_WinMessageFrom(CString strDlgName , CString strFileName)
{
	::WritePrivateProfileString(_T("Default Setting"),_T("Windows_Name"), strDlgName, strFileName);
}

static void Read_ErrorCode(LPCWSTR lpTitle, LPCWSTR lpKey, CString *szRetString)
{
	wchar_t wszData[100] = {0,};

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\ErrorCode\\ErrorCode.ini"));

	szRetString->Format(_T("%s"), wszData);
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