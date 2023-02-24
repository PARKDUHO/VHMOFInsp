#include "pch.h"
#include "VHMOFInsp.h"
#include "FTPInterface.h"

CFTPInterface::CFTPInterface(void)
{
	memset(&m_stFtpInfo, 0x00, sizeof(FTP_CONNECT_INFO));

	m_hOpen = m_hConnect = NULL;
}

CFTPInterface::~CFTPInterface(void)
{
}

void CFTPInterface::ftp_Initialize()
{
	ftp_Disconnect();

	memset(&m_stFtpInfo, 0x00, sizeof(FTP_CONNECT_INFO));

	m_hOpen		= NULL;
	m_hConnect	= NULL;
}

BOOL CFTPInterface::ftp_GetFTPConfiguration()
{
	CString strFileName;

	//Read_OperationIniFile("GIMCODE","DEFECTCODE_VER",szTemp);
	m_stFtpInfo.wszIpAddress;


	if(m_stFtpInfo.wszIpAddress[0] == NULL)		return FALSE;
	if(m_stFtpInfo.nServerPort == 0)			return FALSE;
	if(m_stFtpInfo.wszUserName[0] == NULL)		return FALSE;
	if(m_stFtpInfo.wszPassword[0] == NULL)		return FALSE;

	return TRUE;
}

void CFTPInterface::ftp_writeMLog(CString strLog)
{
	m_pApp->Gf_writeMLog(strLog);
}

// FTP Connection Thread Struct & Method
DWORD WINAPI WorkerFunction(LPVOID);

typedef struct 
{ 
	TCHAR* pHost; 
	INTERNET_PORT pPort;
	TCHAR* pUser; 
	TCHAR* pPass;
	DWORD dwFlags;
	DWORD_PTR dwContext;
} PARM;

BOOL CFTPInterface::ftp_Connect(int timeout)
{
	// Creadte Thread
	PARM    threadParm;
	HANDLE hThread; DWORD dwThreadID; 
	threadParm.pHost = m_stFtpInfo.wszIpAddress;
	threadParm.pPort = m_stFtpInfo.nServerPort;
	threadParm.pUser = m_stFtpInfo.wszUserName;
	threadParm.pPass = m_stFtpInfo.wszPassword;
	threadParm.dwFlags = m_stFtpInfo.dwFlags;
	threadParm.dwContext = m_stFtpInfo.dwContext;

	// FTP Open
	DWORD dwFlag=0;
	DWORD dwTimeout, dwExitCode;

	//왜필요한지 모르겠음. 일단주석
	/*
	int nTimeoutCount=0;
	while(1)
	{
		if (nTimeoutCount > 500)
		{
			m_pObmApp->Gf_fucWriteMLog("<FTP> FTP Connect wait Time out 10s");
			return FALSE;
		}
		if (m_hConnect==NULL)
		{
			break;
		}
		delayMs(20);
		nTimeoutCount++;
	}
	*/

	//TT Check Test Code
	DWORD dwTickS, dwTickE, dwDelay;
	CString TT;

	m_hOpen = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	if(NULL == m_hOpen) 
	{
		return FALSE;
	}

	hThread = CreateThread(
		NULL, // Pointer to thread security attributes 
		0, // Initial thread stack size, in bytes 
		WorkerFunction, // Pointer to thread function 
		&threadParm, // The argument for the new thread 
		0, // Creation flags 
		&dwThreadID // Pointer to returned thread identifier 
	);

	//기존코드
	/*m_hConnect = InternetConnect(
			m_hOpen,
			m_stFtpInfo.wszIpAddress, 
			m_stFtpInfo.nServerPort, 
			m_stFtpInfo.wszUserName, 
			m_stFtpInfo.wszPassword,
			INTERNET_SERVICE_FTP,
			m_stFtpInfo.dwFlags,
			m_stFtpInfo.dwContext
		);*/

	dwTimeout = timeout; // in milliseconds
	TT.Format(_T("<FTP> Set Connect Timeout Delay : %d"), dwTimeout);
	ftp_writeMLog(TT);

	dwTickS = ::GetTickCount();

	if ( WaitForSingleObject ( hThread, dwTimeout ) == WAIT_TIMEOUT ) 
	{
		if ( m_hOpen ) 
			InternetCloseHandle ( m_hOpen ); 
	}

	dwTickE = ::GetTickCount();
	dwDelay = dwTickE - dwTickS;
	TT.Format(_T("<FTP> InternetConnect TT : %d"), dwDelay);
	ftp_writeMLog(TT);

	// The state of the specified object (thread) is signaled 
	dwExitCode = 0; 
	if ( !GetExitCodeThread( hThread, &dwExitCode ) ) 
		DWORD strError = GetLastError();
	
	CloseHandle(hThread);

	if (dwExitCode) // Worker function failed 
		return FALSE;

	if(m_hConnect == NULL)
	{
		InternetCloseHandle(m_hOpen);
		return FALSE;
	}

	return TRUE;
	// FTP Open End
}

/////////////////// WorkerFunction ////////////////////// 
DWORD WINAPI WorkerFunction(IN LPVOID vThreadParm)
/*  Purpose:
		Call InternetConnect to establish a FTP session
	Arguments:
		vThreadParm - points to PARM passed to thread
	Returns:
		returns 0 */
{
	PARM* pThreadParm; // Initialize local pointer to void pointer passed to thread 
	pThreadParm = (PARM*)vThreadParm; 
	m_hConnect = InternetConnect(
			m_hOpen,
			pThreadParm->pHost,
			pThreadParm->pPort,
			pThreadParm->pUser,
			pThreadParm->pPass,
			INTERNET_SERVICE_FTP,
			pThreadParm->dwFlags,
			pThreadParm->dwContext
		);

	if (m_hConnect == NULL)
		return 1; // fail

	return 0; // success 
}


void CFTPInterface::ftp_Disconnect()
{
	BOOL bRet1=TRUE;
	BOOL bRet2=TRUE;

	// FTP Close
	for(int i=0; i<3; i++)
	{
		if(m_hConnect) 
		{
			if(InternetCloseHandle(m_hConnect))
			{
				//m_strFTPStatusMsg = "연결이 종료 되었습니다.";
				bRet1 = TRUE;
				m_hConnect = NULL;
			}
			else
			{
				bRet1 = FALSE;
			}
		}

		if(m_hOpen) 
		{
			if(InternetCloseHandle(m_hOpen))
			{
				//m_strFTPStatusMsg = "연결이 종료 되었습니다.";
				bRet2 = TRUE;
				m_hOpen = NULL;
			}
			else
			{
				bRet2 = FALSE;
			}
		}

		if((bRet1==TRUE) &&(bRet2==TRUE))
			break;

		Sleep(100);
	}
}


BOOL CFTPInterface::ftp_SetCurrentDirectory(CString strDirectory)
{
	int fst=0, lst=0;
	CString strToken;

	if(m_hConnect==NULL)
	{
		ftp_writeMLog(_T("<FTP> FTP server not connection. (m_hConnect == Null)"));
		return FALSE;
	}

	while(1)
	{
		lst = strDirectory.Find(_T("/"), fst);
		if(lst != -1)
		{
			strToken = strDirectory.Mid(fst, (lst-fst));
			if(FtpSetCurrentDirectory(m_hConnect, strToken)==FALSE)
			{
				return FALSE;
			}
			fst = lst+1;
			continue;
		}
		else
		{
			strToken = strDirectory.Mid(fst);

			if(strToken.GetLength() != 0)
			{
				if(FtpSetCurrentDirectory(m_hConnect, strToken)==FALSE)
				{
					return FALSE;
				}
			}
			break;
		}
	}

	return TRUE;
}

BOOL CFTPInterface::ftp_createDirectory(LPCWSTR wszDirectory)
{
	if(m_hConnect==NULL)
	{
		ftp_writeMLog(_T("<FTP> FTP server not connection. (m_hConnect == Null)"));
		return FALSE;
	}

	if(!FtpCreateDirectory(m_hConnect, wszDirectory))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL CFTPInterface::ftp_getFileNameList(CStringArray* pArrFileName, CString searchName)
{
	WIN32_FIND_DATA wfd;
	HINTERNET hFind;
	int n;
	BOOL bResult = TRUE;

	// FTP Root의 File List를 가져온다.
	hFind = FtpFindFirstFile(m_hConnect, searchName, &wfd, 0, 0);
	if (hFind == NULL)
	{
		pArrFileName->RemoveAll();
		return FALSE;
	}

	for (n = 0; bResult; n++)
	{
		pArrFileName->Add(wfd.cFileName);
		bResult = InternetFindNextFile(hFind, &wfd);
	}

	return TRUE;
}

BOOL CFTPInterface::ftp_FileDownload(LPCWSTR wszFilePath)
{
	CString strDestFile, strHostFileName;
	DWORD dwFlags;
	BOOL bReturn=TRUE;


	if(m_hConnect==NULL)
	{
		ftp_writeMLog(_T("<FTP> FTP server not connection. (m_hConnect == Null)"));
		return FALSE;
	}

	strDestFile.Format(_T("%s"), wszFilePath);
	strHostFileName = strDestFile.Mid(strDestFile.ReverseFind(_T('/'))+1);

	CString strLog;
	strLog.Format(_T("<FTP> File Download. HOST[%s] => LOCAL[%s]"), strHostFileName, strDestFile);
	ftp_writeMLog(strLog);

	dwFlags = FTP_TRANSFER_TYPE_BINARY | INTERNET_FLAG_RELOAD;
	if(!FtpGetFile(m_hConnect, strHostFileName, strDestFile, FALSE , NULL, dwFlags, 0))
	{
		ftp_writeMLog(_T("<FTP> File Download = > Fail"));
		bReturn = FALSE;
	}
	else
	{
		ftp_writeMLog(_T("<FTP> File Download = > Success"));
	}
	return bReturn;
	// FTP Download End
}

BOOL CFTPInterface::ftp_FileUpload(CString src_filePath, CString dest_fileName)
{
	DWORD dwFlags;
	BOOL bReturn=TRUE;

	if(m_hConnect==NULL)
	{
		ftp_writeMLog(_T("<FTP> FTP server not connection. (m_hConnect == Null)"));
		return FALSE;
	}

	CString strLog;
	strLog.Format(_T("<FTP> File Upload. LOCAL[%s] => HOST[%s]"), src_filePath, dest_fileName);
	ftp_writeMLog(strLog);

	dwFlags = FTP_TRANSFER_TYPE_BINARY | INTERNET_FLAG_RELOAD;
	if(!FtpPutFile(m_hConnect, src_filePath, dest_fileName, dwFlags, 0))
	{
		ftp_writeMLog(_T("<FTP> File Upload = > Fail"));
		bReturn = FALSE;
	}
	else
	{
		ftp_writeMLog(_T("<FTP> File Upload = > Success"));
	}

	return bReturn;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

