#pragma once

class CMelsecnetG
{
public:
	CMelsecnetG();
	~CMelsecnetG();

	long mnetg_getPath();

	int mnetg_mdOpen(short channel, short mode);
	int mnetg_mdClose();
	int mnetg_mdSendEx(LONG devtyp, LONG devno, LONG* pWriteByte, WORD* data);
	int mnetg_mdReceiveEx(LONG devtyp, LONG devno, LONG* pReadByte, WORD* data);

	
protected:
	LONG m_mnetPath;

	WORD memRecvData[256];

private:

};

