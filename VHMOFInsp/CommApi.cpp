// CommApi.cpp : 구현 파일입니다.
//

#include "pch.h"
#include <string.h>
#include "VHMOFInsp.h"
#include "T2CmdGen.h"

#include "CommApi.h"

//extern CMLTVApp* m_pMltvApp;

CMutex g_mutex(FALSE, NULL);

CCriticalSection Critical_Dio;//DIO Board  (22.11.17)

// CCommApi
IMPLEMENT_DYNAMIC(CCommApi, CCmdTarget)


CCommApi::CCommApi()
{
	lpModelInfo		= m_pApp->GetModelInfo();
	lpSystemInfo	= m_pApp->GetSystemInfo();
	lpInspWorkInfo	= m_pApp->GetInspWorkInfo();

	m_bDioCommStatus[0] = WORK_IDLE;
	m_bDioCommStatus[1] = WORK_IDLE;

	m_bDioEthInit = false;

	nDio_DO_Data[0] = 0;
	nDio_DO_Data[1] = 0;
}

CCommApi::~CCommApi()
{
}


BEGIN_MESSAGE_MAP(CCommApi, CCmdTarget)
END_MESSAGE_MAP()

void CCommApi::makeFusingData(char* pszData)
{
#if 1

	CString stFusingStr = _T("");
	CString stBuff = _T("");

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// INFO
	stBuff.Format(_T("%s"),   _T("INFO"));										stFusingStr += stBuff;	// INFO

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// LCD Resolution Setting
	int nInterface=0, nMode=0, nBitSwap=0;
	float fMclk;
	switch(lpModelInfo->m_nPixelType)
	{
		case 0: // Singel
			nInterface = 0;		fMclk = (float)(lpModelInfo->m_fTimingFrequency );				break;
		case 1: // Dual
			nInterface = 1;		fMclk = (float)(lpModelInfo->m_fTimingFrequency / 2.0f);		break;
		case 2: // Quad
			nInterface = 2;		fMclk = (float)(lpModelInfo->m_fTimingFrequency / 4.0f);		break;
	}
	//if (lpModelInfo->m_nGfd100Use == _ON_)	fMclk = fMclk / 2;
	nMode = 0;
	nBitSwap = (lpModelInfo->m_nSignalRotate<<4);

	stBuff.Format(_T("%02X"), (nInterface | nMode | nBitSwap));					stFusingStr += stBuff;	// MODE
	stBuff.Format(_T("%01d"), 0);												stFusingStr += stBuff;	// Polarity

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Timing Setting
	stBuff.Format(_T("%04d"), lpModelInfo->m_nTimingHorActive);					stFusingStr += stBuff;	// H Active
	stBuff.Format(_T("%04d"), lpModelInfo->m_nTimingVerActive);					stFusingStr += stBuff;	// V Active
	stBuff.Format(_T("%06.2f"), fMclk);											stFusingStr += stBuff;	// MClock
	stBuff.Format(_T("%04d"), lpModelInfo->m_nTimingHorWidth);					stFusingStr += stBuff;	// H Width
	stBuff.Format(_T("%04d"), lpModelInfo->m_nTimingHorFrontPorch);				stFusingStr += stBuff;	// H Front Porch
	stBuff.Format(_T("%04d"), lpModelInfo->m_nTimingHorBackPorch);				stFusingStr += stBuff;	// H Back Porch
	stBuff.Format(_T("%04d"), lpModelInfo->m_nTimingVerWidth);					stFusingStr += stBuff;	// V Width
	stBuff.Format(_T("%04d"), lpModelInfo->m_nTimingVerFrontPorch);				stFusingStr += stBuff;	// V Front Porch
	stBuff.Format(_T("%04d"), lpModelInfo->m_nTimingVerBackPorch);				stFusingStr += stBuff;	// V Back Porch
	stBuff.Format(_T("0"));														stFusingStr += stBuff;	// Clock Delay inc/dec
	stBuff.Format(_T("%03d"), lpModelInfo->m_nClockDelay);						stFusingStr += stBuff;	// Clock Delay Time (ns)

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Aging
	stBuff.Format(_T("0000"));													stFusingStr += stBuff;	// Aging Total time
	stBuff.Format(_T("000"));													stFusingStr += stBuff;	// Aging next pattern
	stBuff.Format(_T("000"));													stFusingStr += stBuff;	// Aging Start LCM
	stBuff.Format(_T("000"));													stFusingStr += stBuff;	// Aging Auto On Time
	stBuff.Format(_T("000"));													stFusingStr += stBuff;	// Aging Auto Off Time
	stBuff.Format(_T("00"));													stFusingStr += stBuff;	// Aging NG Count
	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Signal
	stBuff.Format(_T("%01d"), lpModelInfo->m_nSignalType);						stFusingStr += stBuff;	// Signal Type
	stBuff.Format(_T("%01d"), lpModelInfo->m_nSignalBit);						stFusingStr += stBuff;	// Signal Bit
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPixelType);						stFusingStr += stBuff;	// Pixel Type
	stBuff.Format(_T("%01d"), lpModelInfo->m_nSignalRotate);					stFusingStr += stBuff;	// LG/DISM
	stBuff.Format(_T("%01d"), lpModelInfo->m_nBitSelect);						stFusingStr += stBuff;	// Bit Sel
	stBuff.Format(_T("0"));														stFusingStr += stBuff;	// Cable Open
	stBuff.Format(_T("0"));														stFusingStr += stBuff;	// AGP
	stBuff.Format(_T("0"));														stFusingStr += stBuff;	// SPI Mode
	stBuff.Format(_T("0"));														stFusingStr += stBuff;	// AGP BIST

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Power/ Sequence
	int nData;
	nData = (int)((lpModelInfo->m_fPowerVcc * 100) + (lpModelInfo->m_fPowerVccOffset * 100));
	stBuff.Format(_T("%04d"), nData);											stFusingStr += stBuff;	// VCC
	nData = (int)((lpModelInfo->m_fPowerVel * 100) + (lpModelInfo->m_fPowerVccOffset * 100));
	stBuff.Format(_T("%04d"), nData);											stFusingStr += stBuff;	// VEL
	
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPowerOnSeq1);						stFusingStr += stBuff;	// Power Sequence On VCC
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPowerOnSeq2);						stFusingStr += stBuff;	// Power Sequence On SIGNAL
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPowerOnSeq3);						stFusingStr += stBuff;	// Power Sequence On VEL
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPowerOnSeq4);						stFusingStr += stBuff;	// Power Sequence On 
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPowerOnSeq5);						stFusingStr += stBuff;	// Power Sequence On
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPowerOnSeq6);						stFusingStr += stBuff;	// Power Sequence On 
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPowerOffSeq1);					stFusingStr += stBuff;	// Power Sequence Off VEL
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPowerOffSeq2);					stFusingStr += stBuff;	// Power Sequence Off SIGNAL
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPowerOffSeq3);					stFusingStr += stBuff;	// Power Sequence Off VCC
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPowerOffSeq4);					stFusingStr += stBuff;	// Power Sequence Off 
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPowerOffSeq5);					stFusingStr += stBuff;	// Power Sequence Off
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPowerOffSeq6);					stFusingStr += stBuff;	// Power Sequence Off 
	
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay1);					stFusingStr += stBuff;	// Power Sequence On Time
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay2);					stFusingStr += stBuff;	// Power Sequence On Time
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay3);					stFusingStr += stBuff;	// Power Sequence On Time
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay4);					stFusingStr += stBuff;	// Power Sequence On Time
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay5);					stFusingStr += stBuff;	// Power Sequence On Time
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay1);					stFusingStr += stBuff;	// Power Sequence Off Time
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay2);					stFusingStr += stBuff;	// Power Sequence Off Time
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay3);					stFusingStr += stBuff;	// Power Sequence Off Time
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay4);					stFusingStr += stBuff;	// Power Sequence Off Time
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay5);					stFusingStr += stBuff;	// Power Sequence Off Time
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Power Limit Setting
	stBuff.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitVccLow * 100));		stFusingStr += stBuff;	// VCC Limit Low
	stBuff.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitVccHigh * 100));		stFusingStr += stBuff;	// VCC Limit High
	stBuff.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitVelLow * 100));		stFusingStr += stBuff;	// VEL Limit Low
	stBuff.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitVelHigh * 100));		stFusingStr += stBuff;	// VEL Limit High
	stBuff.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitIccLow * 100));		stFusingStr += stBuff;	// ICC Limit Low
	stBuff.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitIccHigh * 100));		stFusingStr += stBuff;	// ICC Limit High
	stBuff.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitIelLow * 100));		stFusingStr += stBuff;	// IEL Limit Low
	stBuff.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitIelHigh * 100));		stFusingStr += stBuff;	// IEL Limit High

	//stBuff.Format(_T("00"));													stFusingStr += stBuff;	// PWM Duty min(%)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Interface
	stBuff.Format(_T("0"));														stFusingStr += stBuff;	// Type
	stBuff.Format(_T("0"));														stFusingStr += stBuff;	// Sync En/Dis
	stBuff.Format(_T("00000"));													stFusingStr += stBuff;	// PWM Duty Frequency (Hz)
	stBuff.Format(_T("000"));													stFusingStr += stBuff;	// PWM Duty (%)
	stBuff.Format(_T("0"));														stFusingStr += stBuff;	// PWM Level

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Maintenance Info
	stBuff.Format(_T("0"));														stFusingStr += stBuff;	// Line Mode
	int nI2cFre;
	if (lpModelInfo->m_nI2cClock == 0)	nI2cFre = 20;
	if (lpModelInfo->m_nI2cClock == 1)	nI2cFre = 50;
	if (lpModelInfo->m_nI2cClock == 2)	nI2cFre = 100;
	if (lpModelInfo->m_nI2cClock == 3)	nI2cFre = 154;
	if (lpModelInfo->m_nI2cClock == 4)	nI2cFre = 208;
	if (lpModelInfo->m_nI2cClock == 5)	nI2cFre = 250;
	if (lpModelInfo->m_nI2cClock == 6)	nI2cFre = 319;
	if (lpModelInfo->m_nI2cClock == 7)	nI2cFre = 376;
	if (lpModelInfo->m_nI2cClock == 8)	nI2cFre = 422;
	stBuff.Format(_T("%03d"), nI2cFre);											stFusingStr += stBuff;	// I2C Frequency.(KHz)

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// I2C Interface Function
	stBuff.Format(_T("0"));														stFusingStr += stBuff;	// I2C PullUp.
//	stBuff.Format(_T("%01d"), lpModelInfo->m_nI2cLine);							stFusingStr += stBuff;	// I2C Line. I2C Option은 일단 Fix한다.
	stBuff.Format(_T("%01d"), lpModelInfo->m_nSpiPullUp);						stFusingStr += stBuff;	// SPI PullUp Enable
	stBuff.Format(_T("%01d"), lpModelInfo->m_nGpioPullUp);						stFusingStr += stBuff;	// GPIO PullUp Enable
	stBuff.Format(_T("%01d"), lpModelInfo->m_nI2cLevel);						stFusingStr += stBuff;	// I2C PullUp Level
	stBuff.Format(_T("%01d"), lpModelInfo->m_nSpiLevel);						stFusingStr += stBuff;	//  SPI PullUp Level
	stBuff.Format(_T("%01d"), lpModelInfo->m_nGpioLevel);						stFusingStr += stBuff;	//  GPIO PullUp Level

	stBuff.Format(_T("0"));														stFusingStr += stBuff;	//  BIST OnOff
	stBuff.Format(_T("00"));													stFusingStr += stBuff;	//  BIST Interval
	stBuff.Format(_T("00"));													stFusingStr += stBuff;	//  BIST Count
	stBuff.Format(_T("00"));													stFusingStr += stBuff;	//  BIST Pattern Index
	

	wchar_To_char(stFusingStr.GetBuffer(0), pszData);
#endif // 0
}

CString CCommApi::makePGPatternString(CString ptn_name)
{
	CString rtnString;

	rtnString = CT2CmdGen::makeT2dataStrFromFile(ptn_name);
	rtnString = CT2CmdGen::makeT2PatternStr(rtnString, lpModelInfo->m_nTimingHorActive, lpModelInfo->m_nTimingVerActive);

	return rtnString;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


BOOL CCommApi::main_setSystemFusing(int ch)
{
	int ret=0;
	int length;
	char szPacket[1024]={0,};

	makeFusingData(szPacket);
	length = (int)strlen(szPacket);

	ret = Main_setSendQuery(CMD_CTRL_FUSING_SYSTEM, length, szPacket, ch);
	
	if (DEBUG_TCP_COMM_LOG)
	{
		m_pApp->Gf_writeMLog(szPacket);
	}

	delayMs(10);
	return ret;
}

BOOL CCommApi::main_setPowerSequenceOnOff(int ch, int onoff,BOOL bAck)
{
	BOOL ret=TRUE;
	int length;
	char szPacket[1024]={0,};
	CString sLog;

	sprintf_s(szPacket, "%01d", onoff);
	length = (int)strlen(szPacket);

	//ret = m_pApp->rs232_sendPacket(ch,CMD_CTRL_POWER_SEQUENCE_ONOFF, length, szPacket, bAck);
	ret = Main_setSendQuery(CMD_CTRL_POWER_SEQUENCE_ONOFF, length, szPacket, ch);

	// Firmware에서는 Power Sequence On/Off에서 Delay를 가져가지 않고 ACK를 바로 전달한다.
	// 따라서, Power On/Off Sequence Delay는 S/W에서 가져간다.
	if((ret==TRUE) && (bAck==ACK))
	{
		DWORD dwTickS, dwTickE, dwDelay;
		dwTickS = ::GetTickCount();
		if(onoff==_ON_)
			dwDelay = lpModelInfo->m_nPowerOnDelay1 + lpModelInfo->m_nPowerOnDelay2 + lpModelInfo->m_nPowerOnDelay3 + lpModelInfo->m_nPowerOnDelay4 + lpModelInfo->m_nPowerOnDelay5;
		else
			dwDelay = lpModelInfo->m_nPowerOffDelay1 + lpModelInfo->m_nPowerOffDelay2 + lpModelInfo->m_nPowerOffDelay3 + lpModelInfo->m_nPowerOffDelay4 + lpModelInfo->m_nPowerOffDelay5;

		dwDelay = dwDelay + 500;	// Power Sequence보다 대기시간을 길게 설정한다.
		while(1)
		{
			dwTickE = ::GetTickCount();
			if((dwTickE-dwTickS) > dwDelay)
				break;

			//ProcessMessage();
		}
	}
	return ret;
}

BOOL CCommApi::main_getMeasurePowerAll(int ch,BOOL bAck)
{
	//return main_udp_wait(UDP_MAIN_IP, TARGET_MAIN, UDP_CTRL_ID, CMD_CTRL_MEASURE_ALL_POWER, 0, "");
	BOOL ret;
	ret = Main_setSendQuery(CMD_CTRL_MEASURE_ALL_POWER, 0, "", bAck);
	return ret;
}

BOOL CCommApi::main_setPGInfoPatternName(int ch, CString ptn_name, BOOL Ack)
{
	BOOL ret;
	int length;
	CString strtmp=_T("");
	CString sLog;
	char szPacket[4096]={0,};

	strtmp = makePGPatternString(ptn_name);
	if (strtmp.IsEmpty()!=FALSE)
	{
		sLog.Format(_T("<PG> Pattern file find Fail [%s]"), ptn_name);
		m_pApp->Gf_writeMLog(sLog);
		return FALSE;
	}
	wchar_To_char(strtmp.GetBuffer(0), szPacket);
	length = (int)strlen(szPacket);

	//ret= m_pApp->rs232_sendPacket(ch, CMD_PG_PATTERN_INFO, length, szPacket, Ack); // 화면 Display Fail 대응. 2019.08.20
	ret = Main_setSendQuery(CMD_PG_PATTERN_INFO, length, szPacket, ch);

	return ret;	
}

BOOL CCommApi::main_setPGInfoPatternString(int ch, CString strPtnString, BOOL bAck)
{
	BOOL ret;
	int length;
	char szPacket[4096]={0,};

	length = strPtnString.GetLength();
	wchar_To_char(strPtnString.GetBuffer(0), szPacket);

	//ret = m_pApp->rs232_sendPacket(ch,CMD_PG_PATTERN_INFO, length, szPacket, bAck);
	ret = Main_setSendQuery(CMD_PG_PATTERN_INFO, length, szPacket, ch);

	return ret;
}

BOOL CCommApi::main_setBmpAddress(int ch, CString strPtnString)
{
	BOOL ret;
	int length;
	char szPacket[4096] = { 0, };

	length = strPtnString.GetLength();
	wchar_To_char(strPtnString.GetBuffer(0), szPacket);

	//ret = m_pApp->rs232_sendPacket(ch,CMD_PG_PATTERN_INFO, length, szPacket, bAck);
	ret = Main_setSendQuery(CMD_PG_BMP_SET_WRITE_ADDR, length, szPacket, ch);

	return ret;
}

BOOL CCommApi::main_setBmpDisplay(int ch, int index)
{
	int ret;
	char szPacket[4096];
	int dummy = 0x0000;
	int vStart = 0x00;
	int hActive = 2560;
	int vActive = 1665;
	int length;

	sprintf_s(szPacket, "%01d%04X%04X%04d%04d", 2, dummy, vStart, hActive, vActive);
	length = (int)strlen(szPacket);

	ret = Main_setSendQuery(CMD_CTRL_SET_LOGICAL_BMP, length, szPacket, ch);

	return ret;
}

BOOL CCommApi::main_setBmpComplete(int ch)
{
	int ret;
	char szPacket[4096];
	int dummy = 0x0000;
	int vStart = 0x00;
	int hActive = 2560;
	int vActive = 1665;
	int length;

	sprintf_s(szPacket, "%01d", 0x01);
	length = (int)strlen(szPacket);

	ret = Main_setSendQuery(CMD_PG_BMP_WRITE_COMPLETE, length, szPacket, ch);

	return ret;
}

BOOL CCommApi::main_setI2cWrite(int ch, int level, int pullup, int devAddr, int regAddr, char *pData)
{
	int ret;
	char szPacket[4096];
	int length;

	sprintf_s(szPacket, "%01d", 0x01);
	length = (int)strlen(szPacket);

	ret = Main_setSendQuery(CMD_PG_BMP_WRITE_COMPLETE, length, szPacket, ch);

	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CCommApi::main_makeI2cClock(int index)
{
	int i2c_freq;

#if 1
	if (index == 0)		i2c_freq = 20;	//실제20
	if (index == 1)		i2c_freq = 50;	//실제50
	if (index == 2)		i2c_freq = 100;	//실제100
	if (index == 3)		i2c_freq = 154;	//실제150
	if (index == 4)		i2c_freq = 208;	//실제200
	if (index == 5)		i2c_freq = 250;	//실제240
	if (index == 6)		i2c_freq = 319;	//실제300
	if (index == 7)		i2c_freq = 376;	//실제350
	if (index == 8)		i2c_freq = 422;	//실제400
#else
	if (lpModelInfo->m_nI2cFrequency == 0)		i2c_freq = 20;	//실제20
	if (lpModelInfo->m_nI2cFrequency == 1)		i2c_freq = 50;	//실제50
	if (lpModelInfo->m_nI2cFrequency == 2)		i2c_freq = 100;	//실제100
	if (lpModelInfo->m_nI2cFrequency == 3)		i2c_freq = 150;	//실제147
	if (lpModelInfo->m_nI2cFrequency == 4)		i2c_freq = 200;	//실제192
	if (lpModelInfo->m_nI2cFrequency == 5)		i2c_freq = 240;	//실제232
	if (lpModelInfo->m_nI2cFrequency == 6)		i2c_freq = 300;	//실제290
	if (lpModelInfo->m_nI2cFrequency == 7)		i2c_freq = 350;	//실제333
	if (lpModelInfo->m_nI2cFrequency == 8)		i2c_freq = 400;	//실제373
#endif

	return i2c_freq;
}

#if (CODE_QSPI_USE==1)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QSPI
BOOL CCommApi::Lf_setQSPI_SPI_Init(int ch)
{
	char szPacket[1024 * 32];
	int length;
	sprintf_s(szPacket, "%02d%01d%01d%02d", lpModelInfo->m_nQspiClockSpeed, lpModelInfo->m_nQspiLevel, lpModelInfo->m_nQspiPullUp, lpModelInfo->m_nQspiReadClock);
	length = (int)strlen(szPacket);
	return m_pApp->TCP_sendPacket(ch,CMD_QSPI_SPI_INITIALIZE, length, szPacket, ACK, 2000);
}
BOOL CCommApi::Lf_setQSPI_RelayOnOff(int onoff, int ch)
{
	char szPacket[1024 * 32];
	int length;
	sprintf_s(szPacket, "%01d", onoff);
	length = (int)strlen(szPacket);
	return m_pApp->TCP_sendPacket(ch,CMD_QSPI_SPI_RELAY_ONOFF, length, szPacket, ACK, 2000);
}
BOOL CCommApi::Lf_setQSPI_FlashEraseSector(int ch, int start, int end)
{
	char szPacket[1024 * 32];
	int length;
	sprintf_s(szPacket, "%06X%06X", start, end);
	length = (int)strlen(szPacket);
	return m_pApp->TCP_sendPacket(ch,CMD_QSPI_SPI_FLASH_ERASE_SECTOR, length, szPacket, ACK, 2000);
}
BOOL CCommApi::Lf_setQSPI_FlashEraseBlock(int ch, int start, int end)
{
	char szPacket[1024 * 32];
	int length;
	sprintf_s(szPacket, "%06X%06X", start, end);
	length = (int)strlen(szPacket);
	return m_pApp->TCP_sendPacket(ch,CMD_QSPI_SPI_FLASH_ERASE_BLOCK, length, szPacket, ACK, 2000);
}
BOOL CCommApi::Lf_setQSPI_FlashEraseChip(int ch)
{
	return m_pApp->TCP_sendPacket(ch,CMD_QSPI_SPI_FLASH_ERASE_CHIP, 0, "", ACK, 2000);
}
BOOL CCommApi::Lf_setQSPI_FlashWrite(int ch, int startReg, int wrLength, BYTE* wrpData)
{
	char szPacket[1024 * 32];
	int length;

	// 256 : bytePerPage 
	// 3   : pageWriteDelay(3->5테스트)
	// 1   :  0: 24bit, 1 (32bbit)  => bitOfAddr (20.12.21)
	// 
	sprintf_s(szPacket, "%04d%04d%01d%08X%04X", 256, 3, 1/* bitOfAddr */, startReg, wrLength);
	//sprintf_s(szPacket, "%04d%04d%08X%04X", 256, 3, startReg, wrLength);
	length = (int)strlen(szPacket);

	memcpy(&szPacket[length], wrpData, wrLength);

	length += wrLength;
	return m_pApp->TCP_sendPacket(ch,CMD_QSPI_SPI_FLASH_WRITE, length, szPacket, ACK, 2000);
}
BOOL CCommApi::Lf_getQSPI_FlashRead(int ch, int startReg, int rdLength, BYTE* rdpData)
{
	char szPacket[1024 * 32];
	int length;
	sprintf_s(szPacket, "1%08X%04X", startReg, rdLength);
	length = (int)strlen(szPacket);
	
	if (m_pApp->TCP_sendPacket(ch, CMD_QSPI_SPI_FLASH_READ, length, szPacket, ACK, 2000) == TRUE)
	{
		memcpy(rdpData, &gsztcpRcvPacket[ch][PACKET_PT_DATA], rdLength);
		return TRUE;
	}
	return FALSE;
}

int CCommApi::Lf_getQSPI_FlashStatusRead(int ch)
{
	//char szData[1024 * 32];
	int status = 0;
	if (m_pApp->TCP_sendPacket(ch,CMD_QSPI_SPI_FLASH_STATUS_READ, 0, "", ACK, 2000) == TRUE)
	{
		sscanf_s(&gsztcpRcvPacket[ch][PACKET_PT_DATA], "%02X", &status);
		return status;
	}
	return -1;
}
//TEST용함수
int CCommApi::Lf_getQSPI_FlashStatusRead_Temp(int ch)
{
	//char szData[1024 * 32];
	int status = 0;
	if (m_pApp->TCP_sendPacket(ch, 0x076C, 0, "", ACK, 2000) == TRUE)
	{
		sscanf_s(&gsztcpRcvPacket[ch][PACKET_PT_DATA], "%02X", &status);
		return status;
	}
	return -1;
}

BOOL CCommApi::Lf_setQSPI_I2C_Enable(int ch, int nEnable)
{
	char szPacket[1024 * 32];
	int length;

	sprintf_s(szPacket, "%01d", nEnable);
	length = (int)strlen(szPacket);
	return m_pApp->TCP_sendPacket(ch, CMD_QSPI_I2C_ENABLE, length, szPacket, ACK, 2000);
}
BOOL CCommApi::Lf_setQSPI_I2C_Init(int ch)
{
	char szPacket[1024 * 32];
	int length;
	int nI2cFre;
	nI2cFre = main_makeI2cClock(lpModelInfo->m_nI2cFrequency);

	
	sprintf_s(szPacket, "%03d%01d%01d%03d%02d", nI2cFre, lpModelInfo->m_nI2cLevel, lpModelInfo->m_nI2cPullUp, 32,lpModelInfo->m_nI2cPageWriteDelay);
	length = (int)strlen(szPacket);
	return m_pApp->TCP_sendPacket(ch,CMD_QSPI_I2C_INITIALIZE, length, szPacket, ACK, 2000);
}
BOOL CCommApi::Lf_setQSPI_I2cWrite(int ch, int slave, int startReg, int addrType, int wrLength, BYTE* wrpData)
{
	//m_pApp->commApi->Lf_setQSPI_I2C_Enable(ch, _ON_);
	char szPacket[1024 * 32];
	int length;
	sprintf_s(szPacket, "%02X%04X%01d%04X", slave, startReg, addrType, wrLength);
	length = (int)strlen(szPacket);
	memcpy(&szPacket[length], wrpData, wrLength);

	length += wrLength;
	BOOL ret = m_pApp->TCP_sendPacket(ch,CMD_QSPI_I2C_WRITE, length, szPacket, ACK, 2000);
	//m_pApp->commApi->Lf_setQSPI_I2C_Enable(ch, _OFF_);
	return ret;
}
BOOL CCommApi::Lf_getQSPI_I2cRead(int ch, int slave, int startReg, int addrType, int wrLength, BYTE* rdpData)
{
	//m_pApp->commApi->Lf_setQSPI_I2C_Enable(ch, _ON_);
	//delayMs(100);
	char szPacket[1024 * 32];
	int length;
	sprintf_s(szPacket, "%02X%04X%01d%04X", slave, startReg, addrType, wrLength);
	length = (int)strlen(szPacket);
	if (m_pApp->TCP_sendPacket(ch,CMD_QSPI_I2C_READ, length, szPacket, ACK, 2000) == TRUE)
	{
		memcpy(rdpData, &gsztcpRcvPacket[ch][PACKET_PT_DATA], length);
		//m_pApp->commApi->Lf_setQSPI_I2C_Enable(ch, _OFF_);
		return TRUE;
	}
	//m_pApp->commApi->Lf_setQSPI_I2C_Enable(ch, _OFF_);
	return FALSE;
}

BOOL CCommApi::Lf_setQSPI_GPIO_Init(int ch)
{
	char szPacket[1024 * 32];
	int length;
//	int nI2cFre;
	sprintf_s(szPacket, "%01d%01d%01d%01d%01d" 
		, lpModelInfo->m_nQspiGpioLevel
		, lpModelInfo->m_nQspiGpioInOut1
		, lpModelInfo->m_nQspiGpioInOut2
		, lpModelInfo->m_nQspiGpioInOut3
		, lpModelInfo->m_nQspiGpioInOut4);
	//sprintf_s(szPacket, "%01d%01d%01d%01d%01d", lpModelInfo->m_nQspiGpioLevel , 1, 1, 1, 1); //주석처리(21.02.24)
	length = (int)strlen(szPacket);
	return m_pApp->TCP_sendPacket(ch,CMD_QSPI_GPIO_INITIALIZE, length, szPacket, ACK, 2000);
}
BOOL CCommApi::Lf_setQSPI_GpioWriteBit(int ch)
{
	char szPacket[1024 * 32];
	int length;
	sprintf_s(szPacket, "%01d%01d%01d%01d"
		, lpModelInfo->m_nQspiGpioLowHigh1
		, lpModelInfo->m_nQspiGpioLowHigh2
		, lpModelInfo->m_nQspiGpioLowHigh3
		, lpModelInfo->m_nQspiGpioLowHigh4);
	//sprintf_s(szPacket, "%01d%01d%01d%01d", 0,0,0,1); // 사용 주석처리(21.02.24)
	length = (int)strlen(szPacket);
	return m_pApp->TCP_sendPacket(ch,CMD_QSPI_GPIO_WRITE_BIT, length, szPacket, ACK, 2000);
}
BOOL CCommApi::Lf_setQspiGPIO_GTRL(int ch, int IO,int onoff)
{
	char szPacket[1024 * 32];
	int nGPIO_1 = 0, nGPIO_2 = 0, nGPIO_3 = 0, nGPIO_4 = 0;
	int length;
	if (IO & QSPI_GPIO_1)	nGPIO_1 = onoff;
	if (IO & QSPI_GPIO_2)	nGPIO_2 = onoff;
	if (IO & QSPI_GPIO_3)	nGPIO_3 = onoff;
	if (IO & QSPI_GPIO_4)	nGPIO_4 = onoff;

	sprintf_s(szPacket, "%01d%01d%01d%01d"
		, nGPIO_1
		, nGPIO_2
		, nGPIO_3
		, nGPIO_4);
	length = (int)strlen(szPacket);
	return m_pApp->TCP_sendPacket(ch, CMD_QSPI_GPIO_WRITE_BIT, length, szPacket, ACK, 2000);
}
BOOL CCommApi::Lf_getQSPI_GpioReadBit(int ch, char* szData)
{
	if (m_pApp->TCP_sendPacket(ch,CMD_QSPI_GPIO_READ_BIT, 0, "", ACK, 2000) == TRUE)
	{
		memcpy(szData, &m_pApp->commApi->gsztcpRcvPacket[ch][PACKET_PT_DATA], 4);
		return TRUE;
	}
	return FALSE;
}
BOOL CCommApi::Lf_sendQSPI_AreYouReady(int ch)
{
	if (m_pApp->TCP_sendPacket(ch,CMD_QSPI_ARE_YOU_READY, 0, "", ACK, 2000) == TRUE)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CCommApi::Lf_getQSPI_FW_Ver(int ch)
{
	int length=0;
	char szData[128];
	memset(szData, 0x00, 128);
	m_pApp->m_sQspiFWVersion[ch].Empty();
	if (m_pApp->TCP_sendPacket(ch,CMD_QSPI_GET_FW_VERSION, 0, "", ACK, 2000) == TRUE)
	{
		sscanf_s(&gsztcpRcvPacket[ch][PACKET_PT_LEN], "%04x", &length);
		memcpy(&szData, &gsztcpRcvPacket[ch][PACKET_PT_DATA], length);
		m_pApp->m_sQspiFWVersion[ch] = char_To_wchar(szData);
		return TRUE;
	}
	return FALSE;
}
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CCommApi::main_setJumpBootSection(int ch)
{
	BOOL ret;

	//main_udp_wait();
	//ret = m_pApp->rs232_sendPacket(ch,CMD_CTRL_GOTO_BOOT_SECTION, 0, "");
	ret = Main_setSendQuery(CMD_CTRL_GOTO_BOOT_SECTION, 0, "", ch);

	return ret;
}

BOOL CCommApi::main_setDownloadFirmware(int ch, int packetPoint, unsigned char* szData, int dataSize)
{
	BOOL ret;
	int  headLen;
	char szPacket[4096]={0,};

	sprintf_s(szPacket, "%05X", packetPoint);
	headLen = (int)strlen(szPacket);

	memcpy(&szPacket[headLen], szData, dataSize);

	//main_udp_wait();
	//ret = m_pApp->rs232_sendPacket(ch, CMD_CTRL_FW_DOWNLOAD, (dataSize+headLen), szPacket, ACK, 2000);
	ret = Main_setSendQuery(CMD_CTRL_FW_DOWNLOAD, (dataSize + headLen), szPacket, ch);

	return ret;
}

BOOL CCommApi::main_setDownloadComplete(int ch)
{
	BOOL ret;

	//main_udp_wait();
	//ret = m_pApp->rs232_sendPacket(ch, CMD_CTRL_FW_COMPLETE, 0, "");
	ret = Main_setSendQuery(CMD_CTRL_FW_COMPLETE, 0, "", ch);

	return ret;
}

BOOL CCommApi::main_setControlrReset(int ch)
{
	BOOL ret;

	//main_udp_wait();
	//ret = m_pApp->rs232_sendPacket(ch, CMD_CTRL_BOARD_RESET, 0, "");
	ret = Main_setSendQuery(CMD_CTRL_BOARD_RESET, 0, "", ch);

	return ret;
}


BOOL CCommApi::main_getCtrlFWVersion(int ch)
{
	//main_udp_wait();
	char szbuf[100];
	int ret;

	m_pApp->m_sPgFWVersion[ch].Empty();
	memset(szbuf, 0x00, sizeof(szbuf));
	
	//ret = m_pApp->rs232_sendPacket(ch, CMD_CTRL_FW_VERSION, 0, "");
	ret = Main_setSendQuery(CMD_CTRL_FW_VERSION, 0, "", ch);

	if (ret == FALSE)
	{
		return FALSE;
	}
	int nDataLen;
	sscanf_s(&gszMainRcvPacket[ch][PACKET_PT_LEN], "%04X", &nDataLen);
	memcpy(szbuf, &gszMainRcvPacket[ch][PACKET_PT_DATA], nDataLen-2);
	m_pApp->m_sPgFWVersion[ch] = char_To_wchar(szbuf);
	
	
	CString strLog=_T("");

	strLog.Format(_T("<PG> MCU Version [%s]"), m_pApp->m_sPgFWVersion);
	m_pApp->Gf_writeMLog(strLog);

	return TRUE;
}


#if (CODE_DIO_BOARD_USE==1)
/////////////////////////////////////////////////////////////////////////////////////////////////////
// DIO
void CCommApi::Lf_setDioOutput(unsigned int OutBit, int onoff, int ch)
{	
	if (m_pApp->m_bDio7230Init == FALSE && m_bDioEthInit == FALSE)//조건 Init 추가(22.08.26)
	{
		return;
	}
		
	int outBit = OutBit;
	
	if (onoff == _ON_)
	{
		m_pApp->m_nDioOutBit[ch] |= OutBit;
	}
	else
	{
		m_pApp->m_nDioOutBit[ch] &= ~OutBit;
	}	
	
	/// <summary>
	///  IO 보드 구분(22.08.24)
	/// </summary>	
	if (lpSystemInfo->m_nDIO_Board == IO_CARD_7230)
	{
		m_pApp->m_pDio7230->Dio_DO_WritePort(m_pApp->m_nDioOutBit[ch], ch);
	}
	else if (lpSystemInfo->m_nDIO_Board == DIO_BOARD)
	{
		if (onoff == _ON_)	DIO_setOutputChannel(outBit, ch);		
		else  DIO_setClearChannel(outBit, ch);

	}
		
}

//Add(22.08.26)
void CCommApi::Lf_getDioInputPortRead(int ch)
{
	int ret = 0;
	int DI_port = 0;

	if (m_bDioCommStatus[ch] == WORK_BUSY)
		return;

	m_bDioCommStatus[ch] = WORK_BUSY;

	Critical_Dio[ch].Lock();//(22.11.18)
	ret = DIO_getInputPort(&DI_port, ch);
	Critical_Dio[ch].Unlock();//(22.11.18)

	if (ret != FALSE)
	{
		// Board에서 B점접으로 들어옴
		m_pApp->m_nDioInBit[ch] = ~DI_port;//Bit 반전(22.08.26)
	}

	m_bDioCommStatus[ch] = WORK_IDLE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GI DIO 보드 적용=> IT OLED OC 추가분 4대 적용(22.08.08)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CCommApi::DIO_setConnection(int ch)
{
	int ret;
	CString ipAddr;

	DIO_setDisConnection(ch);
	Sleep(200);

	if (ch == CH1)
	{
		ipAddr = TCP_DIO_1_BOARD_IP;
	}
	else
	{
		ipAddr = TCP_DIO_2_BOARD_IP;
	}

	ret = m_pApp->m_pSocketDIO->tcp_DIO_Connection(ipAddr, TCP_DIO_PORT, ch);

	return ret;
}

BOOL CCommApi::DIO_setDisConnection(int ch)
{
	m_pApp->m_pSocketDIO->tcp_DIO_DisConnection(ch);
	
	return TRUE;
}

void CCommApi::DIO_waitIdleStatus(int ch)
{
	DWORD sTick, eTick;
	sTick = ::GetTickCount();

	// Ethernet 통신상태가 IDLE될때까지 기다린다.(max 500ms)
	while (1)
	{
		if (m_bDioCommStatus[ch] == WORK_IDLE)
			break;

		eTick = ::GetTickCount();
		if ((sTick + 500) < eTick)
		{
			break;
		}
	}
}

int  CCommApi::DIO_setSendQuery(int nCommand, int nLength, char* pData, int ch)
{
	char szpacket[4096] = { 0, };
	int  packetlen;
	char lpbuff[20] = { 0, };
	BYTE nChkSum = 0;

	// DIO 초기화 실패시 Ethernet으로 Data를 보내지 않는다.
	if (m_bDioEthInit == false)	return 0;

	// Checksum 앞까지 Packet 생성
	sprintf_s(szpacket, "%cA1%02X00%02X%04X%s", 0x02, TARGET_DIO, nCommand, nLength, pData);

	// 생성된 Packet을 이용하여 CheckSum을 구한다.
	packetlen = (int)strlen(szpacket);
	for (int j = 1; j < packetlen; j++)		// Check Sum
	{
		nChkSum += szpacket[j];
	}

	// Checksum과 ETX를 붙여 다시 Packet을 만든다.
	sprintf_s(szpacket, "%cA1%02X00%02X%04X%s%02X%c", 0x02, TARGET_DIO, nCommand, nLength, pData, nChkSum, 0x03);
	packetlen = (int)strlen(szpacket);

	// Ehternet 상태가 IDLE 상태가 될때까지 기다린다.
	DIO_waitIdleStatus(ch);

	CString strIOLog, strIOLogPacket, strIOLogTitle;

	

	// Send Log를 기록
	if (0)//DEBUG_ETHERNET_COM_LOG == 1)
	{
		//////////////////////////////////////////////////////////
		strIOLogTitle = _T("IO Packet set:");
		strIOLogPacket = szpacket;
		strIOLog.Append(strIOLogTitle);// +szpacket;// _T("IO Packet:")
		strIOLog.Append(strIOLogPacket);//
		m_pApp->Gf_writeMLog(strIOLog);
	}
		

	///////////////////////////////////////////////////////////

	// 생성된 Packet을 전송.
	int ret = 0;

 	ret = m_pApp->m_pSocketDIO->tcp_DIO_SendQuery(szpacket, packetlen, ch);

	memset(gszdioRcvPacket, 0x00, sizeof(gszdioRcvPacket));
	if (DIO_getReceivePacket(gszdioRcvPacket, ch) == TRUE)
	{
		return ret;
	}
	else
	{
		//		m_bDioEthInit = false;
		return 0;
	}
}


BOOL CCommApi::DIO_getReceivePacket(char* m_szRcvPacket, int ch)
{
	BOOL  ret = FALSE;
	DWORD sTick, eTick;
	int rcvSize = 0;

	sTick = ::GetTickCount();

	m_bDioCommStatus[ch] = WORK_BUSY;
	while (1)
	{
		rcvSize = m_pApp->m_pSocketDIO->tcp_DIO_GetReceivePacketSize(ch);
		
		if (rcvSize != 0)
		{
			// Receive Data를 가져온다.
			memset(m_szRcvPacket, 0, sizeof(m_szRcvPacket));
			m_pApp->m_pSocketDIO->tcp_DIO_GetReceivePacketData(m_szRcvPacket, ch);
			
			// Receive Log를 기록
			//if (DEBUG_ETHERNET_COM_LOG == 1)
			//	m_pMltvApp->Gf_LogDataWrite("DIO Recv", m_szRcvPacket);

			if (m_szRcvPacket[13] == '0')
			{
				ret = TRUE;
				break;
			}
			else
			{
				ret = FALSE;
				break;
			}
		}

		// Ack를 기다린다. Wait Time안에 Ack가 들어오지 않으면 False를 Return한다.
		eTick = ::GetTickCount();
		if ((sTick + ETH_ACK_NOR_WAIT_TIME) < eTick)
		{
			ret = FALSE;
			break;
		}

		ProcessMessage();
	}
	m_bDioCommStatus[ch] = WORK_IDLE;

	return ret;
}

BOOL CCommApi::DIO_setOutputChannel(int DO_bit, int ch)
{
	char szCmd[100] = { 0, };

	nDio_DO_Data[ch] = nDio_DO_Data[ch] | DO_bit;
	nDio_DO_Data[ch] = nDio_DO_Data[ch] & 0x00FFFFFF;
	sprintf_s(szCmd, "%06X", nDio_DO_Data[ch]);

	int ret = 0;
	Critical_Dio[ch].Lock();//(22.11.17)

	ret = DIO_setSendQuery(CMD_DIO_OUTPUT, (int)strlen(szCmd), szCmd, ch);

	Critical_Dio[ch].Unlock();//(22.11.17)

	return ret;
}

BOOL CCommApi::DIO_setClearChannel(int DO_bit, int ch)
{
	char szCmd[100] = { 0, };

	nDio_DO_Data[ch] = nDio_DO_Data[ch] & ~DO_bit;
	nDio_DO_Data[ch] = nDio_DO_Data[ch] & 0x00FFFFFF;
	sprintf_s(szCmd, "%06X", nDio_DO_Data[ch]);

	int ret = 0;
	Critical_Dio[ch].Lock();//(22.11.17)

	ret = DIO_setSendQuery(CMD_DIO_OUTPUT, (int)strlen(szCmd), szCmd, ch);

	Critical_Dio[ch].Unlock();//(22.11.17)

	return ret;
}

BOOL CCommApi::DIO_getInputPort(int* DI_Data, int ch)
{
	char szCmd[100] = { 0, };

	sprintf_s(szCmd, "%06X", nDio_DO_Data[ch]);

	int ret = 0;
	ret = DIO_setSendQuery(CMD_DIO_INPUT, 0, "", ch);

	// Receive Packet이 있으면 Packet을 Parsing한다.
	if (ret != 0)
	{
		int data;
		sscanf_s(&gszdioRcvPacket[13], "%01d%06X", &ret, &data);
		// Packet의 Result 값이 0이면 DI Port의 값을 Update한다.
		if (ret == 0)
		{
			*DI_Data = data;
			return TRUE;
		}
	}
	return FALSE;
}
#endif

//////////////////////////////////////////////////////////////////////
// New Gooil Main Board (22.12.08)
int  CCommApi::Main_setSendQuery(int nCommand, int nLength, char* pData, int ch)
{
	char szpacket[4096] = { 0, };
	int  packetlen;
	char lpbuff[20] = { 0, };
	char szbuff[5] = { 0, };
	BYTE nChkSum = 0;

	// Checksum 앞까지 Packet 생성
	sprintf_s(szpacket, "%cA1%02X00%02X%04X", 0x02, TARGET_MAIN, nCommand, nLength);

	// data를 포함하여 packet 생성. hex로 전송할 data가 있으므로 memcpy를 사용
	packetlen = (int)strlen(szpacket);

	memcpy(&szpacket[packetlen], pData, nLength);

	// data 를 포함한 packet의 길이를 구한다.
	packetlen += nLength;

	// 생성된 Packet을 이용하여 CheckSum을 구한다.
	for (int j = 1; j < packetlen; j++)		// Check Sum
	{
		nChkSum += szpacket[j];
	}
	sprintf_s(szbuff, "%02X%c", nChkSum, 0x03);

	// Checksum과 ETX 3byte를 붙여 다시 Packet을 만든다.
	memcpy(&szpacket[packetlen], szbuff, 3);
	packetlen += 3;

	// Packet의 마지막에 String의 끝을 알리기 위하여 NULL을 추가한다.
	szpacket[packetlen] = 0x00;

	// 생성된 Packet을 전송.
	int ret = 0;

	ret = m_pApp->m_pSocketTCPMain->tcp_Main_SendQuery(ch, szpacket, packetlen);

	// Fusing은 약 3초정도 걸림
	if (nCommand == CMD_CTRL_FUSING_SYSTEM)
	{
		Sleep(3000);
	}

	if (DEBUG_TCP_RECEIVE_OK == 1)
		return TRUE;

	memset(gszMainRcvPacket[ch], 0x00, sizeof(gszMainRcvPacket[ch]));
	if (Main_getReceivePacket(gszMainRcvPacket[ch], ch) == TRUE)
	{
		return ret;
	}
	else
	{
		//		m_bDioEthInit = false;
		return 0;
	}
}

BOOL CCommApi::Main_getReceivePacket(char* m_szRcvPacket, int ch)
{
	BOOL  ret = FALSE;
	DWORD sTick, eTick;
	int rcvSize = 0;

	sTick = ::GetTickCount();

	while (1)
	{
		rcvSize = m_pApp->m_pSocketTCPMain->tcp_Main_GetReceivePacketSize(ch);

		if (rcvSize != 0)
		{
			// Receive Data를 가져온다.
			memset(m_szRcvPacket, 0, sizeof(m_szRcvPacket));
			m_pApp->m_pSocketTCPMain->tcp_Main_GetReceivePacketData(ch, m_szRcvPacket);

			// Receive Log를 기록
			//if (DEBUG_ETHERNET_COM_LOG == 1)
			//	m_pMltvApp->Gf_LogDataWrite("DIO Recv", m_szRcvPacket);

			if (m_szRcvPacket[PACKET_PT_RET] == '0')
			{
				ret = TRUE;
				break;
			}
			else
			{
				ret = FALSE;
				break;
			}
		}

		// Ack를 기다린다. Wait Time안에 Ack가 들어오지 않으면 False를 Return한다.
		eTick = ::GetTickCount();
		if ((sTick + ETH_ACK_NOR_WAIT_TIME) < eTick)
		{
			ret = FALSE;
			break;
		}

		ProcessMessage();
	}

	return ret;
}
