#pragma once
#include <wininet.h>		// FTP Library Include

static HINTERNET m_hOpen, m_hConnect;

struct FTP_CONNECT_INFO
{
	TCHAR wszIpAddress[50];
	INTERNET_PORT nServerPort;
	TCHAR wszUserName[50];
	TCHAR wszPassword[50];
	DWORD dwService;
	DWORD dwFlags;
	DWORD_PTR dwContext;
};

class CFTPInterface
{
public:
	CFTPInterface(void);
	~CFTPInterface(void);

	BOOL ftp_Connect(int timeout);
	void ftp_Disconnect();
	void ftp_Initialize();
	void ftp_writeMLog(CString strLog);

	BOOL ftp_GetFTPConfiguration();
	BOOL ftp_SetCurrentDirectory(CString strDirectory);

	BOOL ftp_FileDownload(LPCWSTR wszFilePath);
	BOOL ftp_FileUpload(CString src_filePath, CString dest_fileName);

	BOOL ftp_createDirectory(LPCWSTR wszDirectory);
	BOOL ftp_getFileNameList(CStringArray* pArrFileName, CString searchName);

	FTP_CONNECT_INFO m_stFtpInfo;


	//////////////////////////////////////////////////////////////

protected:

};
