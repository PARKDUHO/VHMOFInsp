#pragma once

#include "SocketTcp.h"
/////////////////////////////////////////////////////////////////////////////
// User Define

class CSocketTcpApp
{
public:
	CSocketTcpApp(void);
	~CSocketTcpApp(void);

	CSocketTCP* pSocketTcp;

	//////////////////////////////////////////////////////////////////////
	// Main Board Function
	BOOL tcp_Main_Connection(CString ip, int port, int ch);
	BOOL tcp_Main_DisConnection(int ch);
	BOOL tcp_Main_SendQuery(int ch, char* data, int nDataLen);
	BOOL tcp_Main_GetReceivePacketData(int ch, char* szRcvPacket);
	BOOL tcp_Main_GetReceivePacketSize(int ch);

	//////////////////////////////////////////////////////////////////////
	// Main (FPGA SPARTAN-7) Board Function
	BOOL tcp_FPGA_Connection(CString ip, int port, int ch);
	BOOL tcp_FPGA_DisConnection(int ch);
	BOOL tcp_FPGA_SendQuery(int ch, char* data, int nDataLen);

	//////////////////////////////////////////////////////////////////////
	// SPI Control Function
	BOOL tcp_SPI_Connection(CString ip, int port, int ch);
	BOOL tcp_SPI_DisConnection(int ch);
	BOOL tcp_SPI_SendQuery(int socketID, char *data, int nDataLen);
	BOOL tcp_SPI_GetReceivePacketData(int socketID, char* szRcvPacket);
	int tcp_SPI_GetReceivePacketSize(int socketID);

	//////////////////////////////////////////////////////////////////////


};

extern CSocketTcpApp* lpSocketTcpApp;
