#include "pch.h"

#include "VHMOFInsp.h"
#include "SocketTcpApp.h"

/////////////////////////////////////////////////////////////////////////////
CSocketTcpApp* lpSocketTcpApp;

/////////////////////////////////////////////////////////////////////////////

CSocketTcpApp::CSocketTcpApp(void)
{
	pSocketTcp = new CSocketTCP;
}

CSocketTcpApp::~CSocketTcpApp(void)
{
	delete pSocketTcp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// TCP Main Board Function
//////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CSocketTcpApp::tcp_Main_Connection(CString ip, int port, int ch)
{
	char szIp[50];
	int socketID;

	wchar_To_char(ip.GetBuffer(0), szIp);
	if (ch == CH1)	socketID = SOC_MAIN_BD_1;
	else        	socketID = SOC_MAIN_BD_2;
	return pSocketTcp->eth_Connection(szIp, port, socketID);
}

BOOL CSocketTcpApp::tcp_Main_DisConnection(int ch)
{
	int socketID;

	if (ch == CH1)	socketID = SOC_MAIN_BD_1;
	else        	socketID = SOC_MAIN_BD_2;
	pSocketTcp->eth_DisConnection(socketID);
	return TRUE;
}

BOOL CSocketTcpApp::tcp_Main_SendQuery(int ch, char* data, int nDataLen)
{
	int socketID;

	if (ch == CH1)	socketID = SOC_MAIN_BD_1;
	else        	socketID = SOC_MAIN_BD_2;

	return pSocketTcp->eth_MainSendQuery(socketID, data, nDataLen);
}

BOOL CSocketTcpApp::tcp_Main_GetReceivePacketData(int ch, char* szRcvPacket)
{
	BOOL bRet;
	int socketID;

	if (ch == CH1)	socketID = SOC_MAIN_BD_1;
	else        	socketID = SOC_MAIN_BD_2;

	bRet = pSocketTcp->eth_getMainRcvPacket(socketID, szRcvPacket);

	// Receive Log?? ????
	if (DEBUG_TCP_COMM_LOG)
	{
		CString sLog;
		sLog.Format(_T("<MAIN RECV> Socket(%d) : %S"), socketID, szRcvPacket);
		m_pApp->Gf_writeMLog(sLog);
	}

	return bRet;
}

int CSocketTcpApp::tcp_Main_GetReceivePacketSize(int ch)
{
	int socketID;

	if (ch == CH1)	socketID = SOC_MAIN_BD_1;
	else         	socketID = SOC_MAIN_BD_2;
	return pSocketTcp->eth_getMainRcvPacketSize(socketID);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// TCP Main FPGA (SPARTAN-7) Board Function
//////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CSocketTcpApp::tcp_FPGA_Connection(CString ip, int port, int ch)
{
	char szIp[50];
	int socketID;

	wchar_To_char(ip.GetBuffer(0), szIp);
	if (ch == CH1)	socketID = SOC_FPGA_BD_1;
	else        	socketID = SOC_FPGA_BD_2;
	return pSocketTcp->eth_Connection(szIp, port, socketID);
}

BOOL CSocketTcpApp::tcp_FPGA_DisConnection(int ch)
{
	int socketID;

	if (ch == CH1)	socketID = SOC_FPGA_BD_1;
	else        	socketID = SOC_FPGA_BD_2;
	pSocketTcp->eth_DisConnection(socketID);
	return TRUE;
}

BOOL CSocketTcpApp::tcp_FPGA_SendQuery(int ch, char* data, int nDataLen)
{
	int socketID;

	if (ch == CH1)	socketID = SOC_FPGA_BD_1;
	else        	socketID = SOC_FPGA_BD_2;

	return pSocketTcp->eth_MainSendQuery(socketID, data, nDataLen);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// TCP SPI Function
//////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CSocketTcpApp::tcp_SPI_Connection(CString ip, int port, int ch)
{
	char szIp[50];
	int socketID;

	wchar_To_char(ip.GetBuffer(0), szIp);
	if (ch == CH1)	socketID = SOC_SERVER_SPI_1;
	else        	socketID = SOC_SERVER_SPI_2;
	return pSocketTcp->eth_Connection(szIp, port, socketID);
}

BOOL CSocketTcpApp::tcp_SPI_DisConnection(int ch)
{
	int socketID;

	if (ch == CH1)	socketID = SOC_SERVER_SPI_1;
	else         	socketID = SOC_SERVER_SPI_2;
	pSocketTcp->eth_DisConnection(socketID);
	return TRUE;
}

BOOL CSocketTcpApp::tcp_SPI_SendQuery(int ch, char *data, int nDataLen)
{
	int socketID;

	if (ch == CH1)	socketID = SOC_SERVER_SPI_1;
	else         	socketID = SOC_SERVER_SPI_2;

	return pSocketTcp->eth_SpiSendQuery(socketID, data, nDataLen);
}

BOOL CSocketTcpApp::tcp_SPI_GetReceivePacketData(int ch, char* szRcvPacket)
{
	int socketID;

	if (ch == CH1)	socketID = SOC_SERVER_SPI_1;
	else         	socketID = SOC_SERVER_SPI_2;
	return pSocketTcp->eth_getSpiRcvPacket(socketID, szRcvPacket);;
}

int CSocketTcpApp::tcp_SPI_GetReceivePacketSize(int ch)
{
	int socketID;

	if (ch == CH1)	socketID = SOC_SERVER_SPI_1;
	else         	socketID = SOC_SERVER_SPI_2;
	return pSocketTcp->eth_getSpiRcvPacketSize(socketID);
}


