#include "pch.h"
#include "VHMOFInsp.h"
#include "SocketTcp.h"
#include <winsock2.h>

/////////////////////////////////////////////////////////////////////////////
CSocketTCP* pSocketTcpApp;


/////////////////////////////////////////////////////////////////////////////
// New Main B/D(22.12.08)
UINT ThreadSocketMain1(LPVOID pParam)
{
	int nLength = 0;
	CSocketTCP* pSocketTcp = (CSocketTCP*)pParam;
	char szbuf[1024 * 64];

	while (1)
	{
		memset(szbuf, 0x00, sizeof(szbuf));
		nLength = recv(pSocketTcp->hSocket[SOC_MAIN_BD_1], szbuf, sizeof(szbuf), 0);

		if ((nLength == 0) || (nLength == -1) || (nLength == 0xFFFF))
		{
			pSocketTcp->rcvDataLen[SOC_MAIN_BD_1] = 0;
			Sleep(10);
			continue;
		}

		if (nLength > 0)
		{
			if (szbuf[0] == 0x02)
			{
				memcpy(pSocketTcp->szMainDataTcp[CH1], &szbuf[0], nLength);
				pSocketTcp->rcvDataLen[SOC_MAIN_BD_1] = nLength;
			}
		}
	}
}

UINT ThreadSocketMain2(LPVOID pParam)
{
	int nLength = 0;
	CSocketTCP* pSocketTcp = (CSocketTCP*)pParam;
	char szbuf[1024 * 64];

	while (1)
	{
		memset(szbuf, 0x00, sizeof(szbuf));
		nLength = recv(pSocketTcp->hSocket[SOC_MAIN_BD_2], szbuf, sizeof(szbuf), 0);

		if ((nLength == 0) || (nLength == -1) || (nLength == 0xFFFF))
		{
			pSocketTcp->rcvDataLen[SOC_MAIN_BD_2] = 0;
			Sleep(10);
			continue;
		}

		if (nLength > 0)
		{
			if (szbuf[0] == 0x02)
			{
				memcpy(pSocketTcp->szMainDataTcp[CH2], &szbuf[0], nLength);
				pSocketTcp->rcvDataLen[SOC_MAIN_BD_2] = nLength;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
UINT ThreadSocketSPI_1(LPVOID pParam)
{
	CSocketTCP* pSocketTcp = (CSocketTCP*)pParam;
	int nLength=0, recvLen=0, stx = 0, totRecvLen = 0;
	char szbuf[1024*64];
	while(1)
	{
		memset(szbuf, 0x00, sizeof(szbuf));
		nLength = recv(pSocketTcp->hSocket[SOC_SERVER_SPI_1], szbuf, sizeof(szbuf), 0);
		pSocketTcp->Gf_DEBUGfucWriteMLog(char_To_wchar(szbuf));
		if((nLength==0) || (nLength==-1) || (nLength==0xFFFF))
		{
			pSocketTcp->rcvDataLen[SOC_SERVER_SPI_1] = 0;
			Sleep(10);
			continue;
		}
		if (nLength > 0)
		{
			if (szbuf[0] == 0x02)
			{
				sscanf_s(&szbuf[9], "%04X", &totRecvLen);
				totRecvLen += 16;	// 16는 stx, etx, head와 checksum 길이이다.
				recvLen = nLength;
				memcpy(pSocketTcp->szRcvDataTcp[SOC_SERVER_SPI_1], szbuf, nLength);

				// 받아야할 Data가 더 있다면...
				if (recvLen < totRecvLen)
				{
					while (1)
					{
						nLength = recv(pSocketTcp->hSocket[SOC_SERVER_SPI_1], szbuf, sizeof(szbuf), 0);
						pSocketTcp->Gf_DEBUGfucWriteMLog(char_To_wchar(szbuf));
						if ((nLength == 0) || (nLength == -1) || (nLength == 0xFFFF))
						{
							pSocketTcp->rcvDataLen[SOC_SERVER_SPI_1] = 0;
							break;
						}
						if (nLength > 0)
						{
							memcpy(&pSocketTcp->szRcvDataTcp[SOC_SERVER_SPI_1][recvLen], szbuf, nLength);
							recvLen += nLength;
						}
						sprintf_s(szbuf, "recvLen=%d nLength=%d totRecvLen=%d", recvLen, nLength, totRecvLen);
						pSocketTcp->Gf_DEBUGfucWriteMLog(szbuf);
						if (recvLen >= totRecvLen)	break;	// 모든 Data를 받았으면 빠져나간다.

						delayMs(1);
					}
				}
			}
			else
			{
				nLength = 0;
				ZeroMemory(szbuf, sizeof(szbuf));
			}
		}

		if (nLength == 0)
		{
			if (pSocketTcp->rcvDataLen[SOC_SERVER_SPI_1] == 0)		// Packet의 중간부분이 Receive되면 Buff를 Clear하고 다시 받는다.
			{
				SleepEx(1, FALSE);
				continue;
			}
		}
		//szbuf[nLength] = NULL;
		//memcpy(pSocketTcp->szRcvDataTcp, szbuf, sizeof(szbuf));
		pSocketTcp->rcvDataLen[SOC_SERVER_SPI_1] = recvLen;
		pSocketTcp->szRcvDataTcp[SOC_SERVER_SPI_1][recvLen] = NULL;
		int ncmd=0;
		sscanf_s(&pSocketTcp->szRcvDataTcp[SOC_SERVER_SPI_1][PACKET_PT_CMD], "%02X", &ncmd);
		
		nLength = 0;
		ZeroMemory(szbuf, sizeof(szbuf));

		Sleep(10);
	}
	return 0;
}
UINT ThreadSocketSPI_2(LPVOID pParam)
{
	CSocketTCP* pSocketTcp = (CSocketTCP*)pParam;
	int nLength = 0, recvLen = 0, stx = 0, totRecvLen = 0;
	char szbuf[1024 * 64];
	while (1)
	{
		memset(szbuf, 0x00, sizeof(szbuf));
		nLength = recv(pSocketTcp->hSocket[SOC_SERVER_SPI_2], szbuf, sizeof(szbuf), 0);

		pSocketTcp->Gf_DEBUGfucWriteMLog(szbuf);
		if ((nLength == 0) || (nLength == -1) || (nLength == 0xFFFF))
		{
			pSocketTcp->rcvDataLen[SOC_SERVER_SPI_2] = 0;
			Sleep(10);
			continue;
		}
		if (nLength > 0)
		{
			if (szbuf[0] == 0x02)
			{
				sscanf_s(&szbuf[9], "%04X", &totRecvLen);
				totRecvLen += 16;	// 16는 stx, etx, head와 checksum 길이이다.
				recvLen = nLength;
				memcpy(pSocketTcp->szRcvDataTcp[SOC_SERVER_SPI_2], szbuf, nLength);

				// 받아야할 Data가 더 있다면...
				if (recvLen < totRecvLen)
				{
					while (1)
					{
						nLength = recv(pSocketTcp->hSocket[SOC_SERVER_SPI_2], szbuf, sizeof(szbuf), 0);
						pSocketTcp->Gf_DEBUGfucWriteMLog(szbuf);
						if ((nLength == 0) || (nLength == -1) || (nLength == 0xFFFF))
						{
							pSocketTcp->rcvDataLen[SOC_SERVER_SPI_2] = 0;
							break;
						}
						if (nLength > 0)
						{
							memcpy(&pSocketTcp->szRcvDataTcp[SOC_SERVER_SPI_2][recvLen], szbuf, nLength);
							recvLen += nLength;
						}

						if (recvLen >= totRecvLen)	break;	// 모든 Data를 받았으면 빠져나간다.

						delayMs(1);
					}
				}
			}
			else
			{
				nLength = 0;
				ZeroMemory(szbuf, sizeof(szbuf));
			}
		}

		if (nLength == 0)
		{
			if (pSocketTcp->rcvDataLen[SOC_SERVER_SPI_2] == 0)		// Packet의 중간부분이 Receive되면 Buff를 Clear하고 다시 받는다.
			{
				SleepEx(1, FALSE);
				continue;
			}
		}
		//szbuf[nLength] = NULL;
		//memcpy(pSocketTcp->szRcvDataTcp, szbuf, sizeof(szbuf));
		pSocketTcp->rcvDataLen[SOC_SERVER_SPI_2] = recvLen;
		pSocketTcp->szRcvDataTcp[SOC_SERVER_SPI_2][recvLen] = NULL;

		int ncmd = 0;
		sscanf_s(&pSocketTcp->szRcvDataTcp[SOC_SERVER_SPI_2][PACKET_PT_CMD], "%02X", &ncmd);

		nLength = 0;
		ZeroMemory(szbuf, sizeof(szbuf));

		Sleep(10);
	}
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
CSocketTCP::CSocketTCP(void)
{
	m_pThread1 = NULL;
	m_pThread2 = NULL;
	memset(rcvDataLen, 0x00, sizeof(rcvDataLen));
}

CSocketTCP::~CSocketTCP(void)
{
	for(int i=0; i<SOC_SERVER_MAX; i++)
	{
		if(m_bCon[i])
		{
			shutdown(hSocket[i], SD_SEND);
		}
		closesocket(hSocket[i]);
	}

	WSACleanup();	// WSACleanup은 한번만 한다.
}

int CSocketTCP::eth_getSpiKeyPadInput()
{
	int cmd,nData=0;
	for (int ch = 0; ch < 2; ch++)
	{
		if (rcvDataLen[ch] > 0)
		{
			sscanf_s(&szRcvDataTcp[ch][PACKET_PT_CMD], "%02X", &cmd);
			if (cmd == CMD_QSPI_KEYPAD_INPUT)
			{
				sscanf_s(&szRcvDataTcp[ch][PACKET_PT_DATA], "%01d", &nData);
				rcvDataLen[ch] = 0;
				return nData;
			}
		}
	}
	return -1;
}


BYTE CSocketTCP::eth_SockInit()
{
	WORD wversionRequested;
	WSADATA wsadata;
	int err; 
	wversionRequested = MAKEWORD( 2, 2 ); 
	err = ::WSAStartup( wversionRequested, &wsadata );

	if ( err != 0 ) 
	{
		return -1;
	}
	if ( LOBYTE( wsadata.wVersion ) != 2 ||
		HIBYTE( wsadata.wVersion ) != 2 ) 
	{
		return -1;
	}

	return 0;
}

// 소켓연결 실패 시 기다리는 시간을 줄이기 위한 함수.
BOOL CSocketTCP::eth_Connection(char* ipAddr, int nPort, int socketID)
{
	int nTimeout=ETH_CONNECT_WAIT_TIME;

	if (0 != eth_SockInit())
	{
		//AfxMessageBox(_T("fucSockInit() Fail"));
		return FALSE;
	}

	hSocket[socketID]=socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_addr.s_addr = inet_addr(ipAddr);
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(nPort);

	ULONG nonBlk = TRUE;
	if(ioctlsocket(hSocket[socketID], FIONBIO, &nonBlk ) == SOCKET_ERROR)
	{
		//AfxMessageBox(_T("ioctlsocket1() Fail"));
		return FALSE;
	}

	int ret = connect(hSocket[socketID], (LPSOCKADDR)&servAddr, sizeof(servAddr));

	if(ret == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
	{
		//AfxMessageBox(_T("WSAGetLastError() Fail"));
		return FALSE;
	}

	fd_set fdset;
	FD_ZERO( &fdset );
	FD_SET( hSocket[socketID], &fdset );

	struct  timeval     timevalue;
	timevalue.tv_sec = nTimeout/1000;
	timevalue.tv_usec = 0;

	if(select(0, NULL, &fdset, NULL, &timevalue ) == SOCKET_ERROR)
	{
		//AfxMessageBox(_T("select() Fail"));
		return FALSE;
	}

	if ( !FD_ISSET( hSocket[socketID], &fdset ) )
	{       
		closesocket(hSocket[socketID]);
		hSocket[socketID] = INVALID_SOCKET;
		//AfxMessageBox(_T("FD_ISSET() Fail"));
		return FALSE;
	}

	nonBlk = FALSE;
	if(ioctlsocket(hSocket[socketID], FIONBIO, &nonBlk ) == SOCKET_ERROR)
	{
		//AfxMessageBox(_T("ioctlsocket2() Fail"));
		return FALSE;
	}

	//////////////////////////////////////////////////////////////
	// Socket Variable Init
	//////////////////////////////////////////////////////////////
	m_bCon[socketID] = true;

	memset(szRcvDataTcp, 0x00, sizeof(szRcvDataTcp));
	memset(szMainDataTcp, 0x00, sizeof(szMainDataTcp));

	//////////////////////////////////////////////////////////////
	// Socket Thread Start
	//////////////////////////////////////////////////////////////
	DWORD nExitCode = NULL;
	if (socketID == SOC_SERVER_SPI_1)
	{
		if (m_pThread1 != NULL)
		{
			nExitCode = NULL;
			GetExitCodeThread(m_pThread1->m_hThread, &nExitCode);
			TerminateThread(m_pThread1->m_hThread, nExitCode);
			m_pThread1 = NULL;
		}
		m_pThread1 = AfxBeginThread(ThreadSocketSPI_1, this);
	}
	if (socketID == SOC_SERVER_SPI_2)
	{
		if (m_pThread2 != NULL)
		{
			nExitCode = NULL;
			GetExitCodeThread(m_pThread2->m_hThread, &nExitCode);
			TerminateThread(m_pThread2->m_hThread, nExitCode);
			m_pThread2 = NULL;
		}
		m_pThread2 = AfxBeginThread(ThreadSocketSPI_2, this);
	}

	if (socketID == SOC_MAIN_BD_1)//(22.12.08)
	{
		if (m_pThreadMain1 != NULL)
		{
			nExitCode = NULL;
			GetExitCodeThread(m_pThreadMain1->m_hThread, &nExitCode);
			TerminateThread(m_pThreadMain1->m_hThread, nExitCode);
			m_pThreadMain1 = NULL;
		}
		m_pThreadMain1 = AfxBeginThread(ThreadSocketMain1, this);
	}

	if (socketID == SOC_MAIN_BD_2)//(22.12.08)
	{
		if (m_pThreadMain2 != NULL)
		{
			nExitCode = NULL;
			GetExitCodeThread(m_pThreadMain2->m_hThread, &nExitCode);
			TerminateThread(m_pThreadMain2->m_hThread, nExitCode);
			m_pThreadMain2 = NULL;
		}
		m_pThreadMain2 = AfxBeginThread(ThreadSocketMain2, this);
	}

	return TRUE;
}

void CSocketTCP::eth_DisConnection(int socketID)
{
	// TODO: Add your control notification handler code here

	if(m_bCon[socketID]==true)
	{
		shutdown(hSocket[socketID], SD_SEND);
	}
	closesocket(hSocket[socketID]);

	m_bCon[socketID] = false;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//// SPI Board
BOOL CSocketTCP::eth_SpiSendQuery(int socketID, char *data, int nDataLen)
{
	int sendlength=0;

	// Receive Buff를 Clear 한다.
	rcvDataLen[socketID] = 0;

	if (DEBUG_TCP_COMM_LOG)
	{
		CString sLog;
		sLog.Format(_T("<SPI SEND> Socket(%d) : %s"), socketID, data);
		m_pApp->Gf_writeMLog(sLog);
	}

	// Socket Send
	sendlength = send(hSocket[socketID], data, nDataLen, 0);

	if(sendlength==0)	return FALSE;
	else				return TRUE;
}

BOOL CSocketTCP::eth_getSpiRcvPacket(int socketID, char* szRcvPacket)
{
	if(rcvDataLen[socketID]>0)
	{
		for (int i = 0; i < 3; i++)
		{
			memcpy(szRcvPacket, szRcvDataTcp[socketID], rcvDataLen[socketID]);
			if (strlen(szRcvPacket) > 0)
			{
				break;
			}
			else
			{
				Sleep(100);
			}
		}
		memset(szRcvDataTcp[socketID], 0x00, sizeof(szRcvDataTcp[socketID]));

		rcvDataLen[socketID] = 0;
		return TRUE;
		
	}
	else
	{
		return FALSE;
	}
}

int CSocketTCP::eth_getSpiRcvPacketSize(int socketID)
{
	return rcvDataLen[socketID];
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//// Main Board
BOOL CSocketTCP::eth_MainSendQuery(int socketID, char* data, int nDataLen)
{
	int sendlength = 0;

	// Receive Buff를 Clear 한다.
	rcvDataLen[socketID] = 0;

	if (DEBUG_TCP_COMM_LOG)
	{
		CString sLog;
		sLog.Format(_T("<MAIN SEND> Socket(%d) : %S"), socketID, data);
		m_pApp->Gf_writeMLog(sLog);
	}


	// Socket Send
	sendlength = send(hSocket[socketID], data, nDataLen, 0);

	if (sendlength == 0)	return FALSE;
	else					return TRUE;
}

BOOL CSocketTCP::eth_getMainRcvPacket(int socketID, char* szRcvPacket)
{
	int ch;

	if (socketID == SOC_MAIN_BD_1)	ch = 0;
	else                            ch = 1;

	if (rcvDataLen[socketID] > 0)
	{
		for (int i = 0; i < 3; i++)
		{
			memcpy(szRcvPacket, szMainDataTcp[ch], rcvDataLen[socketID]);
			if (strlen(szRcvPacket) > 0)
			{
				break;
			}
			else
			{
				Sleep(100);
			}
		}
		memset(szMainDataTcp[ch], 0x00, sizeof(szMainDataTcp[ch]));

		rcvDataLen[socketID] = 0;
		return TRUE;

	}
	else
	{
		return FALSE;
	}
}

int CSocketTCP::eth_getMainRcvPacketSize(int socketID)
{
	return rcvDataLen[socketID];
}

void CSocketTCP::Gf_DEBUGfucWriteMLog(char* mLogData)
{
	if (DEBUG_TCP_COMM_LOG == 0)	return;
	CString sLog;
	sLog.Format(_T("%S"), mLogData);
	Gf_DEBUGfucWriteMLog(sLog);
}

void CSocketTCP::Gf_DEBUGfucWriteMLog(CString pStrWideChar)
{
	if (DEBUG_TCP_COMM_LOG == 0)	return;
#if 1
	CFile file;
	USHORT nShort = 0xfeff;
	CString strFileName, strLog, path, sEQP;

	SYSTEMTIME sysTime;
	::GetSystemTime(&sysTime);
	CTime time = CTime::GetCurrentTime();

	strLog.Format(_T("[%02d:%02d:%02d %03d] %06d%03d\t: %s\r\n"), time.GetHour(), time.GetMinute(), time.GetSecond(), sysTime.wMilliseconds, (time.GetHour() * 3600) + (time.GetMinute() * 60) + time.GetSecond(), sysTime.wMilliseconds, pStrWideChar);


	strFileName.Format(_T("DEBUG_SPI_%04d%02d%02d"), time.GetYear(), time.GetMonth(), time.GetDay());
	path.Format(_T(".\\Logs\\DEBUG\\%s.txt"), strFileName);

	if ((_access(".\\Logs", 0)) == -1)
		_mkdir(".\\Logs");

	if ((_access(".\\Logs\\DEBUG", 0)) == -1)
		_mkdir(".\\Logs\\DEBUG");


	if (file.Open(path, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeBinary))
	{
		if (file.GetLength() == 0)
		{
			file.Write(&nShort, 2);
		}
		file.SeekToEnd();
		file.Write(strLog, (strLog.GetLength() * 2));
		file.Close();
	}

#endif // 0
}


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
BOOL CSocketTCP::eth_DIOSendQuery(char* data, int nDataLen, int socketID)
{
	int sendlength = 0;

	// Receive Buff를 Clear 한다.
	rcvDataLen[socketID] = 0;

	if (DEBUG_TCP_COMM_LOG)
	{
		CString sLog;
		sLog.Format(_T("<DIO SEND> Socket(%d) : %s"), socketID, data);
		m_pApp->Gf_writeMLog(sLog);
	}

	// Socket Send
	sendlength = send(hSocket[socketID], data, nDataLen, 0);

	if (sendlength == 0)	return FALSE;
	else				return TRUE;
}

BOOL CSocketTCP::eth_getDIORcvPacket(char* szRcvPacket, int socketID)
{
	if (rcvDataLen[socketID] > 0)
	{
		memcpy(szRcvPacket, szDioRcvData, rcvDataLen[socketID]);
		memset(szDioRcvData, 0x00, sizeof(szDioRcvData));

		rcvDataLen[socketID] = 0;
		//return true;

		/*for (int i = 0; i < 3; i++)
		{
			memcpy(szRcvPacket, szRcvDataTcp[SOC_SERVER_DIO], rcvDataLen[SOC_SERVER_DIO]);
			if (strlen(szRcvPacket) > 0)
			{
				break;
			}
			else
			{
				Sleep(100);
			}
		}*/
		//memset(szRcvDataTcp[SOC_SERVER_DIO], 0x00, sizeof(szRcvDataTcp[SOC_SERVER_DIO]));

		rcvDataLen[socketID] = 0;
		return TRUE;

	}
	else
	{
		return FALSE;
	}
}

int CSocketTCP::eth_getDIORcvPacketSize(int socketID)
{
	return rcvDataLen[socketID];
}