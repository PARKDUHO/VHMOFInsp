// CommApi.cpp : 구현 파일입니다.
//

#include "pch.h"
#include <string.h>
#include "VHMOFInsp.h"
#include "T2CmdGen.h"

#include "CommApi.h"

//extern CMLTVApp* m_pMltvApp;

CMutex g_mutex(FALSE, NULL);

CCriticalSection Critical_Dio[2];//DIO Board  (22.11.17)

// CCommApi
IMPLEMENT_DYNAMIC(CCommApi, CCmdTarget)


CCommApi::CCommApi()
{
	lpModelInfo		= m_pApp->GetModelInfo();
	lpSystemInfo	= m_pApp->GetSystemInfo();
	lpInspWorkInfo	= m_pApp->GetInspWorkInfo();
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
	if (lpModelInfo->m_nSignalType == SIGNAL_TYPE_DP)	fMclk = fMclk / 2;

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
	// Signal
	stBuff.Format(_T("%01d"), lpModelInfo->m_nSignalType);						stFusingStr += stBuff;	// Signal Type
	stBuff.Format(_T("%01d"), lpModelInfo->m_nSignalBit);						stFusingStr += stBuff;	// Signal Bit
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPixelType);						stFusingStr += stBuff;	// Pixel Type
	stBuff.Format(_T("%01d"), lpModelInfo->m_nSignalRotate);					stFusingStr += stBuff;	// LG/DISM
	stBuff.Format(_T("%01d"), lpModelInfo->m_nBitSelect);						stFusingStr += stBuff;	// Bit Sel
	stBuff.Format(_T("0"));														stFusingStr += stBuff;	// Cable Open Check
	stBuff.Format(_T("0"));														stFusingStr += stBuff;	// AGP
	stBuff.Format(_T("0"));														stFusingStr += stBuff;	// Power On SPI Mode Set
	stBuff.Format(_T("0"));														stFusingStr += stBuff;	// AGP BIST Active

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Power/ Sequence
	int nData;
	nData = (int)((lpModelInfo->m_fPowerVcc * 100) + (lpModelInfo->m_fPowerVccOffset * 100));
	stBuff.Format(_T("%04d"), nData);											stFusingStr += stBuff;	// VCC
	nData = (int)((lpModelInfo->m_fPowerVel * 100) + (lpModelInfo->m_fPowerVccOffset * 100));
	stBuff.Format(_T("%04d"), nData);											stFusingStr += stBuff;	// VIN
	nData = (int)((lpModelInfo->m_fPowerVdd * 100) + (lpModelInfo->m_fPowerVddOffset * 100));
	stBuff.Format(_T("%04d"), nData);											stFusingStr += stBuff;	// VDD

	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeq1);						stFusingStr += stBuff;	// Power Sequence On 1
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeq2);						stFusingStr += stBuff;	// Power Sequence On 2
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeq3);						stFusingStr += stBuff;	// Power Sequence On 3
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeq4);						stFusingStr += stBuff;	// Power Sequence On 4
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeq5);						stFusingStr += stBuff;	// Power Sequence On 5
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeq6);						stFusingStr += stBuff;	// Power Sequence On 6
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeq7);						stFusingStr += stBuff;	// Power Sequence On 7
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeq8);						stFusingStr += stBuff;	// Power Sequence On 8
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeq9);						stFusingStr += stBuff;	// Power Sequence On 9
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeq10);					stFusingStr += stBuff;	// Power Sequence On 10
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeq11);					stFusingStr += stBuff;	// Power Sequence On 11
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeq12);					stFusingStr += stBuff;	// Power Sequence On 12
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeq13);					stFusingStr += stBuff;	// Power Sequence On 13
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeq1);					stFusingStr += stBuff;	// Power Sequence Off 1
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeq2);					stFusingStr += stBuff;	// Power Sequence Off 2
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeq3);					stFusingStr += stBuff;	// Power Sequence Off 3
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeq4);					stFusingStr += stBuff;	// Power Sequence Off 4
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeq5);					stFusingStr += stBuff;	// Power Sequence Off 5
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeq6);					stFusingStr += stBuff;	// Power Sequence Off 6
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeq7);					stFusingStr += stBuff;	// Power Sequence Off 7
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeq8);					stFusingStr += stBuff;	// Power Sequence Off 8
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeq9);					stFusingStr += stBuff;	// Power Sequence Off 9
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeq10);					stFusingStr += stBuff;	// Power Sequence Off 10
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeq11);					stFusingStr += stBuff;	// Power Sequence Off 11
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeq12);					stFusingStr += stBuff;	// Power Sequence Off 12
	stBuff.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeq13);					stFusingStr += stBuff;	// Power Sequence Off 13

	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay1);					stFusingStr += stBuff;	// Power Sequence On Time 1
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay2);					stFusingStr += stBuff;	// Power Sequence On Time 2
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay3);					stFusingStr += stBuff;	// Power Sequence On Time 3
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay4);					stFusingStr += stBuff;	// Power Sequence On Time 4
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay5);					stFusingStr += stBuff;	// Power Sequence On Time 5
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay6);					stFusingStr += stBuff;	// Power Sequence On Time 6
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay7);					stFusingStr += stBuff;	// Power Sequence On Time 7
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay8);					stFusingStr += stBuff;	// Power Sequence On Time 8
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay9);					stFusingStr += stBuff;	// Power Sequence On Time 9
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay10);					stFusingStr += stBuff;	// Power Sequence On Time 10
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay11);					stFusingStr += stBuff;	// Power Sequence On Time 11
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOnDelay12);					stFusingStr += stBuff;	// Power Sequence On Time 12
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay1);					stFusingStr += stBuff;	// Power Sequence Off Time 1
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay2);					stFusingStr += stBuff;	// Power Sequence Off Time 2
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay3);					stFusingStr += stBuff;	// Power Sequence Off Time 3
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay4);					stFusingStr += stBuff;	// Power Sequence Off Time 4
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay5);					stFusingStr += stBuff;	// Power Sequence Off Time 5
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay6);					stFusingStr += stBuff;	// Power Sequence Off Time 6
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay7);					stFusingStr += stBuff;	// Power Sequence Off Time 7
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay8);					stFusingStr += stBuff;	// Power Sequence Off Time 8
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay9);					stFusingStr += stBuff;	// Power Sequence Off Time 9
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay10);					stFusingStr += stBuff;	// Power Sequence Off Time 10
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay11);					stFusingStr += stBuff;	// Power Sequence Off Time 11
	stBuff.Format(_T("%04d"), lpModelInfo->m_nPowerOffDelay12);					stFusingStr += stBuff;	// Power Sequence Off Time 12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Power Limit Setting
	stBuff.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitVccLow * 100));		stFusingStr += stBuff;	// VCC Limit Low
	stBuff.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitVccHigh * 100));		stFusingStr += stBuff;	// VCC Limit High
	stBuff.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitVelLow * 100));		stFusingStr += stBuff;	// VIN Limit Low
	stBuff.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitVelHigh * 100));		stFusingStr += stBuff;	// VIN Limit High
	stBuff.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitVddLow * 100));		stFusingStr += stBuff;	// VDD Limit Low
	stBuff.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitVddHigh * 100));		stFusingStr += stBuff;	// VDD Limit High
	stBuff.Format(_T("%04d"), lpModelInfo->m_nLimitIccLow);						stFusingStr += stBuff;	// ICC Limit Low
	stBuff.Format(_T("%04d"), lpModelInfo->m_nLimitIccHigh);					stFusingStr += stBuff;	// ICC Limit High
	stBuff.Format(_T("%04d"), lpModelInfo->m_nLimitIelLow);						stFusingStr += stBuff;	// IIN Limit Low
	stBuff.Format(_T("%04d"), lpModelInfo->m_nLimitIelHigh);					stFusingStr += stBuff;	// IIN Limit High
	stBuff.Format(_T("%04d"), lpModelInfo->m_nLimitIddLow);						stFusingStr += stBuff;	// IDD Limit Low
	stBuff.Format(_T("%04d"), lpModelInfo->m_nLimitIddHigh);					stFusingStr += stBuff;	// IDD Limit High

	stBuff.Format(_T("%05d"), lpModelInfo->m_nPwmFrequency);					stFusingStr += stBuff;	// PWM Frequency
	stBuff.Format(_T("%03d"), lpModelInfo->m_nPwmDuty);							stFusingStr += stBuff;	// PWM Duty
	stBuff.Format(_T("%01d"), lpModelInfo->m_nPwmLevel);						stFusingStr += stBuff;	// PWM Level

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
	// Pull-up Enable Expend
	stBuff.Format(_T("%01d"), lpModelInfo->m_nI2cPullUp);						stFusingStr += stBuff;	// I2C Pull Up
	stBuff.Format(_T("%01d"), lpModelInfo->m_nSpiPullUp);						stFusingStr += stBuff;	// SPI Pull Up
	stBuff.Format(_T("%01d"), lpModelInfo->m_nGpioPullUp);						stFusingStr += stBuff;	// GPIO Pull Up
	stBuff.Format(_T("%01d"), lpModelInfo->m_nI2cLevel);						stFusingStr += stBuff;	// I2C Level
	stBuff.Format(_T("%01d"), lpModelInfo->m_nSpiLevel);						stFusingStr += stBuff;	// SPI Level
	stBuff.Format(_T("%01d"), lpModelInfo->m_nGpioLevel);						stFusingStr += stBuff;	// GPIO Level
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function
	stBuff.Format(_T("%01d"), lpModelInfo->m_nMainBoardLED);					stFusingStr += stBuff;	// Main Board(PG) Status LED On/Off

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
BOOL CCommApi::main_getAreYouReady(int ch)
{
	BOOL bRtnCode = FALSE;

	bRtnCode = main_setSendQuery(CMD_CTRL_ARE_YOU_READY, 0, "", ch);

	return bRtnCode;
}

BOOL CCommApi::main_setSystemFusing(int ch)
{
	int ret=0;
	int length;
	char szPacket[1024]={0,};

	makeFusingData(szPacket);
	length = (int)strlen(szPacket);

	ret = main_setSendQuery(CMD_CTRL_FUSING_SYSTEM, length, szPacket, ch);

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
	ret = main_setSendQuery(CMD_CTRL_POWER_SEQUENCE_ONOFF, length, szPacket, ch);

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
	BOOL ret;
	ret = main_setSendQuery(CMD_CTRL_MEASURE_ALL_POWER, 0, "", ch);
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
	ret = main_setSendQuery(CMD_PG_PATTERN_INFO, length, szPacket, ch);

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
	ret = main_setSendQuery(CMD_PG_PATTERN_INFO, length, szPacket, ch);

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
	ret = main_setSendQuery(CMD_PG_BMP_SET_WRITE_ADDR, length, szPacket, ch);

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

	ret = main_setSendQuery(CMD_PG_BMP_WRITE_COMPLETE, length, szPacket, ch);

	return ret;
}

BOOL CCommApi::main_setI2cWrite(int ch, int line, int devAddr, int regAddr, int regAddrType, int wrLength, char *pData)
{
	int ret;
	char szPacket[4096];
	int packet_length;
	int i2c_freq = 200;

	if (lpModelInfo->m_nI2cClock == 0)	i2c_freq = 20;
	if (lpModelInfo->m_nI2cClock == 1)	i2c_freq = 50;
	if (lpModelInfo->m_nI2cClock == 2)	i2c_freq = 100;
	if (lpModelInfo->m_nI2cClock == 3)	i2c_freq = 154;
	if (lpModelInfo->m_nI2cClock == 4)	i2c_freq = 208;
	if (lpModelInfo->m_nI2cClock == 5)	i2c_freq = 250;
	if (lpModelInfo->m_nI2cClock == 6)	i2c_freq = 319;
	if (lpModelInfo->m_nI2cClock == 7)	i2c_freq = 376;
	if (lpModelInfo->m_nI2cClock == 8)	i2c_freq = 422;

	sprintf_s(szPacket, "%01d%03d%02X%04X%01d%04X", line, i2c_freq, devAddr, regAddr, regAddrType, wrLength);
	packet_length = (int)strlen(szPacket);

	memcpy(&szPacket[packet_length], pData, wrLength);
	packet_length += wrLength;

	ret = main_setSendQuery(CMD_IF_I2C_WRITE, packet_length, szPacket, ch);

	return ret;
}

BOOL CCommApi::main_setI2cRead(int ch, int line, int devAddr, int regAddr, int regAddrType, int rdLength, char* pData)
{
	int ret;
	char szPacket[4096];
	int packet_length;
	int i2c_freq = 200;

	if (lpModelInfo->m_nI2cClock == 0)	i2c_freq = 20;
	if (lpModelInfo->m_nI2cClock == 1)	i2c_freq = 50;
	if (lpModelInfo->m_nI2cClock == 2)	i2c_freq = 100;
	if (lpModelInfo->m_nI2cClock == 3)	i2c_freq = 154;
	if (lpModelInfo->m_nI2cClock == 4)	i2c_freq = 208;
	if (lpModelInfo->m_nI2cClock == 5)	i2c_freq = 250;
	if (lpModelInfo->m_nI2cClock == 6)	i2c_freq = 319;
	if (lpModelInfo->m_nI2cClock == 7)	i2c_freq = 376;
	if (lpModelInfo->m_nI2cClock == 8)	i2c_freq = 422;

	sprintf_s(szPacket, "%01d%03d%02X%04X%01d%04X", line, i2c_freq, devAddr, regAddr, regAddrType, rdLength);
	packet_length = (int)strlen(szPacket);

	ret = main_setSendQuery(CMD_IF_I2C_READ, packet_length, szPacket, ch);
	if (ret == TRUE)
	{
		memcpy(pData, gszMainRcvPacket, rdLength);
	}

	return ret;
}

BOOL CCommApi::main_setCableOpenCheck(int ch)
{
	int ret;
	char szPacket[4096];
	int length;

	sprintf_s(szPacket, "1");
	length = (int)strlen(szPacket);

	ret = main_setSendQuery(CMD_CTRL_CABLE_OPEN_CHECK, length, szPacket, ch);

	return ret;
}

BOOL CCommApi::main_setGpioControl(int ch, int gpio1, int gpio2, int gpio3)
{
	int ret;
	char szPacket[4096];
	int length;

	sprintf_s(szPacket, "%01d%01d%01d", gpio1, gpio2, gpio3);
	length = (int)strlen(szPacket);

	ret = main_setSendQuery(CMD_CTRL_GPIO_CONTROL, length, szPacket, ch);

	return ret;
}

BOOL CCommApi::main_setGioSetting(int ch, int gio1, int gio2, int gio3, int gio4)
{
	int ret;
	char szPacket[4096];
	int length;

	sprintf_s(szPacket, "%01d%01d%01d%01d", gio1, gio2, gio3, gio4);
	length = (int)strlen(szPacket);

	ret = main_setSendQuery(CMD_CTRL_GIO_CONTROL, length, szPacket, ch);

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QSPI
BOOL CCommApi::qspi_setSendQuery(int ch, int nCommand, int nLength, char* pData, int recvACK, int waitTime)
{
	char szlog[1024] = { 0, };
	char szpacket[4096] = { 0, };
	int  packetlen;
	char lpbuff[20] = { 0, };
	BYTE nChkSum = 0;

	// data 앞까지 Packet 생성
	sprintf_s(szpacket, "%cA1A400%02X%04X", 0x02, nCommand, nLength);

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
	sprintf_s(lpbuff, "%02X%c", nChkSum, 0x03);

	// Checksum과 ETX 3byte를 붙여 다시 Packet을 만든다.
	memcpy(&szpacket[packetlen], lpbuff, 3);
	packetlen += 3;

	// Packet의 마지막에 String의 끝을 알리기 위하여 NULL을 추가한다.
	szpacket[packetlen] = 0x00;


	// Receive Buff를 Clear
	ZeroMemory(m_szQspiRecvData[ch], sizeof(m_szQspiRecvData[ch]));

	// 생성된 Packet을 전송.
	if (ch == CH1)	m_pApp->m_pSocketTCPMain->tcp_SPI_SendQuery(ch, szpacket, packetlen);
	if (ch == CH2)	m_pApp->m_pSocketTCPMain->tcp_SPI_SendQuery(ch, szpacket, packetlen);

	// ACK Receive
	UINT ret = TRUE;

	if (recvACK == ACK)
	{
		if (qspi_procWaitRecvACK(ch, nCommand, waitTime) == TRUE)
			ret = TRUE;
		else
			ret = FALSE;
	}

	return ret;
}


BOOL CCommApi::qspi_procWaitRecvACK(int ch, int cmd, DWORD waitTime)
{
	DWORD stTick = ::GetTickCount();
	int recvCmd = 0;

	while (1)
	{
		DWORD edTick = GetTickCount();
		if ((edTick - stTick) > waitTime)
		{
			return FALSE;
		}
		if (ch == CH1)
		{
			if (m_pApp->m_pSocketTCPMain->tcp_SPI_GetReceivePacketSize(CH1) > 0)
			{
				if (m_pApp->m_pSocketTCPMain->tcp_SPI_GetReceivePacketData(CH1, m_szQspiRecvData[CH1]) == TRUE)
				{
					sscanf_s(&m_szQspiRecvData[CH1][PACKET_PT_CMD], "%02X", &recvCmd);
					if (recvCmd == cmd)
					{
						if (m_szQspiRecvData[CH1][PACKET_PT_RET] != '0')
							return FALSE;
						return TRUE;
					}
				}
			}
		}
		if (ch == CH2)
		{
			if (m_pApp->m_pSocketTCPMain->tcp_SPI_GetReceivePacketSize(CH2) > 0)
			{
				if (m_pApp->m_pSocketTCPMain->tcp_SPI_GetReceivePacketData(CH2, m_szQspiRecvData[CH2]) == TRUE)
				{
					sscanf_s(&m_szQspiRecvData[CH2][PACKET_PT_CMD], "%02X", &recvCmd);
					if (recvCmd == cmd)
					{
						if (m_szQspiRecvData[CH2][PACKET_PT_RET] != '0')
						{
							return FALSE;
						}
						return TRUE;
					}
				}
			}
		}

		//ProcessMessage();
	}
	return FALSE;
}

#if (CODE_QSPI_USE==1)
BOOL CCommApi::Lf_setQSPI_SPI_Init(int ch)
{
	char szPacket[1024 * 32];
	int length;
	sprintf_s(szPacket, "%02d%01d%01d%02d", lpModelInfo->m_nSpiClock, lpModelInfo->m_nSpiLevel, lpModelInfo->m_nSpiPullUp, 8/*lpModelInfo->m_nQspiReadClock*/);
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
		memcpy(rdpData, &m_szQspiRecvData[ch][PACKET_PT_DATA], rdLength);
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
		sscanf_s(&m_szQspiRecvData[ch][PACKET_PT_DATA], "%02X", &status);
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
		sscanf_s(&m_szQspiRecvData[ch][PACKET_PT_DATA], "%02X", &status);
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
		memcpy(rdpData, &m_szQspiRecvData[ch][PACKET_PT_DATA], length);
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
		memcpy(szData, &m_pApp->commApi->m_szQspiRecvData[ch][PACKET_PT_DATA], 4);
		return TRUE;
	}
	return FALSE;
}
#endif

BOOL CCommApi::qspi_AreYouReady(int ch)
{
	if (qspi_setSendQuery(ch,CMD_QSPI_ARE_YOU_READY, 0, "", ACK, 2000) == TRUE)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCommApi::qspi_getFWVersion(int ch)
{
	int length=0;
	char szData[128];
	memset(szData, 0x00, 128);
	m_pApp->m_sQspiFWVersion[ch].Empty();
	if (qspi_setSendQuery(ch, CMD_QSPI_GET_FW_VERSION, 0, "", ACK, 2000) == TRUE)
	{
		sscanf_s(&m_szQspiRecvData[ch][PACKET_PT_LEN], "%04x", &length);
		memcpy(&szData, &m_szQspiRecvData[ch][PACKET_PT_DATA], length-1);
		m_pApp->m_sQspiFWVersion[ch] = char_To_wchar(szData);
		return TRUE;
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CCommApi::main_setGoToBootSection(int ch)
{
	BOOL ret;

	//main_udp_wait();
	//ret = m_pApp->rs232_sendPacket(ch,CMD_CTRL_GOTO_BOOT_SECTION, 0, "");
	ret = main_setSendQuery(CMD_CTRL_GOTO_BOOT_SECTION, 0, "", ch);

	return ret;
}

BOOL CCommApi::main_setDownloadFirmware(int ch, char* szData, int dataSize)
{
	BOOL ret;

	ret = main_setSendQuery(CMD_CTRL_FW_DOWNLOAD, dataSize, szData, ch);

	return ret;
}

BOOL CCommApi::main_setDownloadComplete(int ch)
{
	BOOL ret;

	//main_udp_wait();
	//ret = m_pApp->rs232_sendPacket(ch, CMD_CTRL_FW_COMPLETE, 0, "");
	ret = main_setSendQuery(CMD_CTRL_FW_COMPLETE, 0, "", ch);

	return ret;
}

BOOL CCommApi::main_setControlrReset(int ch)
{
	BOOL ret;

	//main_udp_wait();
	//ret = m_pApp->rs232_sendPacket(ch, CMD_CTRL_BOARD_RESET, 0, "");
	ret = main_setSendQuery(CMD_CTRL_BOARD_RESET, 0, "", ch);

	return ret;
}


BOOL CCommApi::main_getCtrlFWVersion(int ch)
{
	//main_udp_wait();
	char szbuf[100];
	int ret;

	m_pApp->m_sPgFWVersion[ch].Empty();
	memset(szbuf, 0x00, sizeof(szbuf));
	
	ret = main_setSendQuery(CMD_CTRL_FW_VERSION, 0, "", ch);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
// DIO
/////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CCommApi::dio_writeDioOutput(int ch, int OutData)
{
	BOOL ret = FALSE;
	int length = 0;
	char szPacket[128] = { 0, };

	m_pApp->m_nDioOutBit[ch][0] = (BYTE)(OutData >> 0);
	m_pApp->m_nDioOutBit[ch][1] = (BYTE)(OutData >> 8);
	m_pApp->m_nDioOutBit[ch][2] = (BYTE)(OutData >> 16);

	sprintf_s(szPacket, "%02X00%02X00%02X00", m_pApp->m_nDioOutBit[ch][2], m_pApp->m_nDioOutBit[ch][1], m_pApp->m_nDioOutBit[ch][0]);
	length = (int)strlen(szPacket);

	Critical_Dio[ch].Lock();//(22.11.18)
	ret = m_pApp->udp_sendPacketUDP_DIO(ch, TARGET_DIO, 0, CMD_DIO_OUTPUT, length, szPacket, ACK);
	Critical_Dio[ch].Unlock();//(22.11.18)

	return ret;
}


BOOL CCommApi::dio_writeDioPortOnOff(int ch, int OutBit, int onoff)
{
	BOOL ret = FALSE;
	int length = 0;
	char szPacket[128] = { 0, };

	if (onoff == _ON_)
	{
		m_pApp->m_nDioOutBit[ch][0] |= (BYTE)(OutBit >> 0);
		m_pApp->m_nDioOutBit[ch][1] |= (BYTE)(OutBit >> 8);
		m_pApp->m_nDioOutBit[ch][2] |= (BYTE)(OutBit >> 16);
	}
	else
	{
		OutBit = ~OutBit;
		m_pApp->m_nDioOutBit[ch][0] &= (BYTE)(OutBit >> 0);
		m_pApp->m_nDioOutBit[ch][1] &= (BYTE)(OutBit >> 8);
		m_pApp->m_nDioOutBit[ch][2] &= (BYTE)(OutBit >> 16);
	}

	sprintf_s(szPacket, "%02X00%02X00%02X00", m_pApp->m_nDioOutBit[ch][2], m_pApp->m_nDioOutBit[ch][1], m_pApp->m_nDioOutBit[ch][0]);
	length = (int)strlen(szPacket);

	Critical_Dio[ch].Lock();//(22.11.18)
	ret = m_pApp->udp_sendPacketUDP_DIO(ch, TARGET_DIO, 0, CMD_DIO_OUTPUT, length, szPacket, ACK);
	Critical_Dio[ch].Unlock();//(22.11.18)

	return ret;
}

BOOL CCommApi::dio_readDioInput(int ch, BOOL bACK)
{
	BOOL ret = FALSE;
	int length = 0;
	char szPacket[128] = { 0, };

	Critical_Dio[ch].Lock();//(22.11.18)
	ret = m_pApp->udp_sendPacketUDP_DIO(ch, TARGET_DIO, 0, CMD_DIO_INPUT, 0, NULL, bACK);
	Critical_Dio[ch].Unlock();//(22.11.18)

	return ret;
}


//////////////////////////////////////////////////////////////////////
// New Gooil Main Board (22.12.08)
//////////////////////////////////////////////////////////////////////
int  CCommApi::main_setSendQuery(int nCommand, int nLength, char* pData, int ch)
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

	if (DEBUG_TCP_RECEIVE_OK == 1)
		return TRUE;

	// Fusing은 약 3초정도 걸림
	int ackWaitTime = ETH_ACK_NOR_WAIT_TIME;
	if (nCommand == CMD_CTRL_FUSING_SYSTEM)
	{
		ackWaitTime = 3000;
	}

	memset(gszMainRcvPacket[ch], 0x00, sizeof(gszMainRcvPacket[ch]));
	if (main_getReceivePacket(gszMainRcvPacket[ch], ch, ackWaitTime) == TRUE)
	{
		return ret;
	}
	else
	{
		//		m_bDioEthInit = false;
		return 0;
	}
}

BOOL CCommApi::main_getReceivePacket(char* m_szRcvPacket, int ch, int ackWaitTime)
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

			m_pApp->main_tcpProcessPacket(ch, m_szRcvPacket);
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
		if ((sTick + ackWaitTime) < eTick)
		{
			ret = FALSE;
			break;
		}

		ProcessMessage();
	}

	return ret;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CCommApi::alpdp_executePythonScript(int ch, CString strPara)
{
	if (lpModelInfo->m_nSignalType != SIGNAL_TYPE_ALPLD)
		return TRUE;

	// Param Setting
	TCHAR szCurPath[2048] = { 0, };
	CString exeFile;
	CString strCurPath;

	// Parameter Set
	GetCurrentDirectory(2048, szCurPath);

	strCurPath.Format(_T("%s\\Script"), szCurPath);

	// Exe File
	exeFile.Format(_T("python.exe"));

	// Shell Execute
	SetCurrentDirectory(strCurPath);// strPathFull);

	SHELLEXECUTEINFO sel;
	memset(&sel, 0, sizeof(sel));
	sel.cbSize = sizeof(sel);
	sel.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_DDEWAIT;
	sel.lpFile = exeFile;
	sel.lpParameters = strPara;
	sel.hwnd = NULL;
	sel.lpVerb = _T("open");
	sel.nShow = SW_HIDE;// SW_SHOW;
	ShellExecuteEx(&sel);
	SetCurrentDirectory(szCurPath);

	// command view
	CString sLog;
	sLog.Format(_T("<SHELL> %s %s"), exeFile, strPara);
	m_pApp->Gf_writeMLog(sLog);

	// wait for converter complete
	DWORD dwResult = ::WaitForSingleObject(sel.hProcess, 500);
	while (1)
	{
		if (dwResult == WAIT_OBJECT_0)	break;
		else	dwResult = ::WaitForSingleObject(sel.hProcess, 500);
	}

	return TRUE;
}



