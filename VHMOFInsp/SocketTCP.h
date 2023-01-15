#pragma once

/////////////////////////////////////////////////////////////////////////////
// User Define
#define ETH_ACK_PWR_WAIT_TIME		10000	// Power On/Off Receive Wait time : 10Sec
#define ETH_ACK_NOT_WAIT			0		// ACK를 기다리지 않음. : 0Sec
#define ETH_ACK_NOR_WAIT_TIME		2000	// Normal Control Receive Wait time : 2Sec
#define ETH_CONNECT_WAIT_TIME		2000	// Connect Wait time : 2Sec

enum
{
	SOC_SERVER_SPI_1 = 0,
	SOC_SERVER_SPI_2,
	SOC_MAIN_BD_1,
	SOC_MAIN_BD_2,
	SOC_FPGA_BD_1,
	SOC_FPGA_BD_2,
	MAX_SOCKET
};

#define SOC_SERVER_MAX				255






class CSocketTCP
{
public:
	CSocketTCP(void);
	~CSocketTCP(void);
	int eth_getSpiKeyPadInput();

	BYTE eth_SockInit();
	BOOL eth_Connection(char* ipAddr, int nPort, int socketID);
	void eth_DisConnection(int socketID);

	BOOL eth_SpiSendQuery(int ch, char *data, int nDataLen);
	BOOL eth_getSpiRcvPacket(int ch, char* szRcvPacket);
	int eth_getSpiRcvPacketSize(int ch);

	BOOL eth_DIOSendQuery(char* data, int nDataLen, int socketID);
	BOOL eth_getDIORcvPacket(char* szRcvPacket, int socketID);
	int eth_getDIORcvPacketSize(int socketID);

	BOOL eth_MainSendQuery(int socketID, char* data, int nDataLen);
	BOOL eth_getMainRcvPacket(int socketID, char* szRcvPacket);
	BOOL eth_getMainRcvPacketSize(int socketID);

	void Gf_DEBUGfucWriteMLog(char* mLogData);
	void Gf_DEBUGfucWriteMLog(CString pStrWideChar);


	char* eth_getErrorCode();

	CWinThread* m_pThread1;
	CWinThread* m_pThread2;
	CWinThread* m_pThreadDIO1;
	CWinThread* m_pThreadDIO2;
	CWinThread* m_pThreadMain1;
	CWinThread* m_pThreadMain2;

	char szDioRcvData[4096];//(22.08.08)

public:
	SOCKADDR_IN servAddr;
	SOCKET hSocket[MAX_SOCKET];

	bool m_bCon[MAX_SOCKET];	// is Connection.

	char szRcvDataTcp[2][1024 * 32];
	char szMainDataTcp[2][1024 * 32];

	WORD rcvDataLen[MAX_SOCKET];

};

extern CSocketTCP* pSocketTcpApp;
