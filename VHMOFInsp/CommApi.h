
#pragma once

#define WORK_IDLE					0
#define WORK_BUSY					1

// CCommApi 명령 대상입니다.


class CCommApi : public CCmdTarget
{
	DECLARE_DYNAMIC(CCommApi)

public:
	CCommApi();
	virtual ~CCommApi();

	LPMODELINFO			lpModelInfo;
	LPSYSTEMINFO		lpSystemInfo;
	LPINSPWORKINFO		lpInspWorkInfo;

	void makeFusingData(char* pszData);
	CString makePGPatternString(CString ptn_name);
	int main_makeI2cClock(int index);

	// Control Function
	BOOL main_getAreYouReady(int ch);
	BOOL main_setSystemFusing(int ch);
	BOOL main_setPowerSequenceOnOff(int ch, int onoff, BOOL bAck=ACK);
	BOOL main_getMeasurePowerAll(int ch,BOOL bAck=ACK);
	BOOL main_setPGInfoPatternName(int ch, CString ptn_name, BOOL Ack = ACK);
	BOOL main_setPGInfoPatternString(int ch, CString szPatternString, BOOL bAck = ACK);
	
	BOOL main_setBmpAddress(int ch, CString strPtnString);
	BOOL main_setBmpComplete(int ch);
	BOOL main_setI2cWrite(int ch, int level, int pullup, int devAddr, int regAddr, char* pData);

	BOOL main_setJumpBootSection(int ch);
	BOOL main_setDownloadFirmware(int ch, int packetPoint, unsigned char* szPacket, int packetSizeint);
	BOOL main_setDownloadComplete(int ch);
	BOOL main_setControlrReset(int ch);
	BOOL main_getCtrlFWVersion(int ch);

	BOOL Lf_setQSPI_SPI_Init(int ch);
	BOOL Lf_setQSPI_RelayOnOff(int ch, int onoff);
	BOOL Lf_setQSPI_FlashEraseSector(int ch, int start, int end);
	BOOL Lf_setQSPI_FlashEraseBlock(int ch, int start, int end);
	BOOL Lf_setQSPI_FlashEraseChip(int ch);
	BOOL Lf_setQSPI_FlashWrite(int ch, int startReg, int wrLength, BYTE* wrpData);
	BOOL Lf_getQSPI_FlashRead(int ch, int startReg, int rdLength, BYTE* rdpData);
	BOOL Lf_getQSPI_FlashStatusRead(int ch);
	BOOL Lf_getQSPI_FlashStatusRead_Temp(int ch);//테스트용(20.12.17)
	BOOL Lf_setQSPI_I2C_Enable(int ch, int nEnable);
	BOOL Lf_setQSPI_I2C_Init(int ch);
	BOOL Lf_setQSPI_I2cWrite(int ch, int slave, int startReg, int addrType, int wrLength, BYTE* wrpData);
	BOOL Lf_getQSPI_I2cRead(int ch, int slave, int startReg, int addrType, int wrLength, BYTE* wrpData);
	BOOL Lf_setQSPI_GPIO_Init(int ch);
	BOOL Lf_setQSPI_GpioWriteBit(int ch);
	BOOL Lf_setQspiGPIO_GTRL(int ch, int IO, int onoff);
	BOOL Lf_getQSPI_GpioReadBit(int ch, char* szData);
	BOOL Lf_sendQSPI_AreYouReady(int ch);
	BOOL Lf_getQSPI_FW_Ver(int ch);

	void Lf_setDioOutput(unsigned int OutBit, int onoff, int ch);

	
	//BOOL UDP_setControlrIP(int sockSID, CString IPstring);

	char gszRs232RcvPacket[2][1024 * 64];
	char gsztcpRcvPacket[2][1024 * 64];

	int	 m_nI2cReadRtnCodeCh1;
	int	 m_nI2cReadRtnCodeCh2;

	//추가 (22.08.24)
	void Lf_getDioInputPortRead(int ch);//(22.08.26)

	//GI DIO Board 변경(IT OLED 추가분 4대적용)(22.08.08)
	void DIO_waitIdleStatus(int ch);
	BOOL DIO_setConnection(int ch);
	BOOL DIO_setDisConnection(int ch);
	int  DIO_setSendQuery(int nCommand, int nLength, char* pData, int ch);
	BOOL DIO_getReceivePacket(char* m_szRcvPacket, int ch);

	BOOL DIO_setOutputChannel(int DO_bit, int ch);
	BOOL DIO_setClearChannel(int DO_bit, int ch);
	BOOL DIO_getInputPort(int* DI_data, int ch);

	BOOL m_bDioCommStatus[MAX_CH];//(22.08.08)
	bool m_bDioEthInit;//(22.08.08)
	char gszdioRcvPacket[256];

	int  nDio_DO_Data[MAX_CH];

	int	 main_setSendQuery(int nCommand, int nLength, char* pData, int ch);
	BOOL main_getReceivePacket(char* m_szRcvPacket, int ch, int ackWaitTime);
	char gszMainRcvPacket[MAX_CH][256];

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ALPDP Function
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	BOOL alpdp_executePythonScript(int ch, CString strPara);


protected:

	DECLARE_MESSAGE_MAP()

};


