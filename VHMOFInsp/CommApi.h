
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
	BOOL main_setI2cWrite(int ch, int line, int devAddr, int regAddr, int regAddrType, int length, char* pData);
	BOOL main_setI2cRead(int ch, int line, int devAddr, int regAddr, int regAddrType, int rdLength, char* pData);

	BOOL main_setCableOpenCheck(int ch);
	BOOL main_setGpioControl(int ch, int gpio1, int gpio2, int gpio3);
	BOOL main_setGioSetting(int ch, int gio1, int gio2, int gio3, int gio4);

	BOOL main_setGoToBootSection(int ch);
	BOOL main_setDownloadFirmware(int ch, char* szData, int dataSize);
	BOOL main_setDownloadComplete(int ch);
	BOOL main_setControlrReset(int ch);
	BOOL main_getCtrlFWVersion(int ch);

	// Control Function (POWER MCU)
	BYTE CRC8_Calc(BYTE* pBuf, WORD usLen);
	WORD CRC16_Calc(BYTE* pBuf, WORD usLen);
	BOOL main_getPowerFWVersion(int ch);

	int	 main_setSendQuery(int nCommand, int nLength, char* pData, int ch);
	BOOL main_getReceivePacket(char* m_szRcvPacket, int ch, int ackWaitTime);
	char gszMainRcvPacket[MAX_CH][256];

	BOOL qspi_setSendQuery(int ch, int nCommand, int nLength, char* pData, int recvACK, int waitTime=1000);
	BOOL qspi_procWaitRecvACK(int ch, int cmd, DWORD waitTime);
	BOOL Lf_setQSPI_SPI_Init(int ch);
	BOOL Lf_setQSPI_FlashEraseSector(int ch, int start, int end);
	BOOL Lf_setQSPI_FlashEraseBlock(int ch, int start, int end);
	BOOL Lf_setQSPI_FlashEraseChip(int ch);
	BOOL Lf_setQSPI_FlashWrite(int ch, int startReg, int wrLength, BYTE* wrpData);
	BOOL Lf_getQSPI_FlashRead(int ch, int startReg, int rdLength, BYTE* rdpData);
	BOOL Lf_getQSPI_FlashStatusRead(int ch);
	BOOL Lf_getQSPI_FlashStatusRead_Temp(int ch);//테스트용(20.12.17)
	BOOL Lf_setQSPI_I2C_Enable(int ch, int nEnable);
	BOOL Lf_getQSPI_I2cRead(int ch, int slave, int startReg, int addrType, int wrLength, BYTE* wrpData);
	BOOL Lf_setQSPI_GPIO_Init(int ch);
	BOOL Lf_setQSPI_GpioWriteBit(int ch);
	BOOL Lf_setQspiGPIO_GTRL(int ch, int IO, int onoff);
	BOOL Lf_getQSPI_GpioReadBit(int ch, char* szData);

	BOOL qspi_RelayOnOff(int ch, int onoff);
	BOOL qspi_DP855SpiWrite(int ch, int writeAddr, int writeSize, char* pWriteData);
	BOOL qspi_DP855SpiRead(int ch, int readAddr, int readSize, char* pReadData);
	BOOL qspi_LevelSelect(int ch, int levelSel);
	BOOL qspi_AreYouReady(int ch);
	BOOL qspi_getFWVersion(int ch);
	BOOL qspi_setGoToBootSection(int ch);
	BOOL qspi_setDownloadFirmware(int ch, char* szData, int dataSize);
	BOOL qspi_setDownloadComplete(int ch);


	//GI DIO Board 변경
	BOOL dio_InspReadyCheck();
	BOOL dio_writeDioOutput(int ch, int OutData);
	BOOL dio_readDioInput(int ch, int bACK=ACK);
	BOOL dio_writeDioPortOnOff(int ch, int OutBit, int onoff);
	BOOL dio_LEDOnOff(BOOL bOnOff);
	BOOL dio_LightCurtainMuteOnOff(BOOL bOnOff);
	BOOL dio_LeftSafetyDoorOpen();
	BOOL dio_LeftSafetyDoorClose();
	BOOL dio_RightSafetyDoorOpen();
	BOOL dio_RightSafetyDoorClose();
	BOOL dio_RobotInLEDOnOff(BOOL bOnOff);
	BOOL dio_RobotInSensorCheck();
	BOOL dio_RearDoorOpen();
	BOOL dio_RearDoorClose();
	BOOL dio_FrontDoorOpen();
	BOOL dio_FrontDoorClose();
	BOOL dio_FrontDoorHoldingOn();
	BOOL dio_FrontDoorHoldingOff();
	BOOL dio_JigClampLock(int ch);
	BOOL dio_JigClampUnLock(int ch);
	BOOL dio_JigClampStatusCheck(int ch, int lockType);
	BOOL dio_JigClampErrorDisplay(int checkType);
	BOOL dio_JigTiltingUp();
	BOOL dio_JigTiltingUpCheck();
	BOOL dio_JigTiltingDown();
	BOOL dio_JigTiltingDownCheck();
	BOOL dio_IonizerBlowOn();
	BOOL dio_IonizerBlowOff();
	BOOL dio_LedLampOn();
	BOOL dio_LedLampOff();
	BOOL dio_TowerLampOnOff(BOOL bRED, BOOL bYELLOW, BOOL bGREEN, BOOL bBUZZER);
	BOOL dio_TowerLampBuzzOff(BOOL bBUZZER);
	BOOL dio_AdsorptionOnOff(int ch, BOOL bOnOff);
	BOOL dio_AdsorptionCheck(int ch);

	

	char gszRs232RcvPacket[2][1024 * 64];
	char m_szQspiRecvData[2][1024 * 64];

	int	 m_nI2cReadRtnCodeCh1;
	int	 m_nI2cReadRtnCodeCh2;



	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ALPDP Function
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	BOOL alpdp_executePythonScript(int ch, CString strPara);


protected:

	DECLARE_MESSAGE_MAP()


private:


};


