#pragma once

// CSocketUDP 명령 대상입니다.
#define WM_UDP_RECEIVE				(WM_USER+200)
#define UDP_SOCKET_PORT				50001
#define LOCAL_HOST_IP				_T("127.0.0.1")



class CSocketUDP : public CAsyncSocket
{
public:
	CSocketUDP();
	virtual ~CSocketUDP();

/////////////////////////////////////////////////////////////////////////////
// 사용자 정의 Function/Variable
/////////////////////////////////////////////////////////////////////////////
public:
#if (DEBUG_RECV_COUNT==1)
	LPINSPWORKINFO	lpInspWorkInfo;
#endif

	BOOL m_bEthernetInit;
	BOOL m_bUDPSendFail;
	char m_sendBuf[PACKET_SIZE];	// 보낼 데이터를 저장

	char m_recvBuf[PACKET_SIZE*4];	// 받은 데이터를 저장
	int  m_recvSize;				// 받은 데이터의 Size
	int  m_recvCommand;				// 받은 Command
	int  m_recvTotalLength;			// 전체 받을 Packet의 Length
	BOOL m_bIsContinueRecv;			// 연속된 Packet인지 새로운 Packet인지 구분하는 Flag

	CString m_strLocalIP1, m_strLocalIP2, m_strGateway;

	SOCKADDR_IN *m_recvSocketAddr;	//받는 주소정보를 담고있음

	CString _hex_to_string(int size, char* hexStr);

	void getLocalIPAddress();
	void getLocalGateWay();

	void parseReceivePacket(int nRead, char* buf);

	BOOL CreatSocket(UINT nSocketPort, int nSocketType);
	BOOL CloseSocket();
	BOOL SendToUDP(CString remoteIP, int length, char* m_sendPacket);

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


	// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocketUDP)
public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSocketUDP)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	// Implementation
protected:
};


