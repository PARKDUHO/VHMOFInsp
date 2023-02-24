// ModuleECS.cpp: ECS Communication Function (by MelsecNetG)
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "VHMOFInsp.h"
#include "ModuleECS.h"
#include "MelsecnetG.h"


UINT ThreadModuleECS(LPVOID pParam)
{
	while (1)
	{
		if (m_pApp->bConnectInfo[CONN_MELSEC] == TRUE)
		{
			m_pApp->pModuleECS->ecs_LinkTest();
			m_pApp->pModuleECS->ecs_TimeDataSend();
			m_pApp->pModuleECS->ecs_ECSRestart();
		}

		Sleep(10);
	}
}
UINT ThreadModuleECS_LoadingType1(LPVOID pParam)
{
	while (1)
	{
		if (m_pApp->bConnectInfo[CONN_MELSEC] == TRUE)
		{
			m_pApp->pModuleECS->ecs_LoadingType1Normal();
		}
		Sleep(10);
	}
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CModuleECS::CModuleECS()
{
	lpSystemInfo = m_pApp->GetSystemInfo();


	AfxBeginThread(ThreadModuleECS, this);
	AfxBeginThread(ThreadModuleECS_LoadingType1, this);
}

CModuleECS::~CModuleECS()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
WORD CModuleECS::ecs_readDataLB(LONG devno)
{
	BOOL ret = FALSE;
	LONG readSize = 2;
	WORD readData = 0;

	ret = m_pApp->pMelsecnetG->mnetg_mdReceiveEx(PLC_DEVIDE_TYPE_LB, devno, &readSize, &readData);

	if (ret == 0)
		return readData;
	else
		return 0;
}

BOOL CModuleECS::ecs_writeDataLB(LONG devno, WORD maskBit, BOOL bOnOff)
{
	CString sLog;
	BOOL ret = FALSE;
	LONG sendLen = 2, readSize = 2;
	WORD readData = 0;
	WORD sendData = 0;

	m_pApp->pMelsecnetG->mnetg_mdReceiveEx(PLC_DEVIDE_TYPE_LB, devno, &readSize, &readData);

	if(bOnOff == ON)
		sendData = readData | maskBit;
	else if (bOnOff == OFF)
		sendData = readData & ~maskBit;

	ret = m_pApp->pMelsecnetG->mnetg_mdSendEx(PLC_DEVIDE_TYPE_LB, devno, &sendLen, &sendData);

	if (ret == 0)
	{
		sLog.Format(_T("<MELSEC> LB Write OK : LB Address[%04X]  LB Data[%04X]"), devno, sendData);
		m_pApp->Gf_writeMLog(sLog);

		return TRUE;
	}
	else
	{
		sLog.Format(_T("<MELSEC> LB Write NG : LB Address[%04X]  LB Data[%04X]"), devno, sendData);
		m_pApp->Gf_writeMLog(sLog);

		return FALSE;
	}
}

BOOL CModuleECS::ecs_isOffLineMode()
{
	if (lpSystemInfo->m_nEcsOnLineMode == ECS_OFFLINE)
		return TRUE;

	return FALSE;
}

BOOL CModuleECS::ecs_LinkTest()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, devno_LTReq = 0;
	WORD readData = 0;
	WORD sendData = 0;
	int mask = 0x0001;

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;

	if ((lpSystemInfo->m_nEcsEqpNumber >= 1) && (lpSystemInfo->m_nEcsEqpNumber <= 16))
	{
		devno_LTReq = 0x00C0;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 1);
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 17) && (lpSystemInfo->m_nEcsEqpNumber <= 32))
	{
		devno_LTReq = 0x00D0;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 17);
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 33) && (lpSystemInfo->m_nEcsEqpNumber <= 48))
	{
		devno_LTReq = 0x00E0;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 33);
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 49) && (lpSystemInfo->m_nEcsEqpNumber <= 64))
	{
		devno_LTReq = 0x00F0;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 49);
	}

	readData = ecs_readDataLB(devno_LTReq);
	if (readData & mask)
	{
		devno = lpSystemInfo->m_nLBStartAddr + 0x0000;
		ecs_writeDataLB(devno, ECS_LINK_REQUEST_ACK, ON);

		DWORD sTick, eTick;
		sTick = ::GetTickCount();
		while (1)
		{
			eTick = ::GetTickCount();
			if ((eTick - sTick) > 3000)
			{
				ecs_writeDataLB(devno, ECS_LINK_REQUEST_ACK, OFF);
				return FALSE;
			}

			readData = ecs_readDataLB(devno_LTReq);
			if ((readData & mask) == 0)
			{
				ecs_writeDataLB(devno, ECS_LINK_REQUEST_ACK, OFF);
				ret = TRUE;
				break;
			}
		}
	}

	return ret;
}


BOOL CModuleECS::ecs_TimeDataSend()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;

	readData[0] = ecs_readDataLB(0x0000);

	if (readData[0] & ECS_TIME_SET_REQUEST)
	{
		sLog.Format(_T("<MELSEC> ECS->EQP Time Set Request"));
		m_pApp->Gf_writeMLog(sLog);

		readSize = 12;
		devno = lpSystemInfo->m_nLWStartAddr1;
		m_pApp->pMelsecnetG->mnetg_mdReceiveEx(PLC_DEVIDE_TYPE_LW, devno, &readSize, readData);
	}

	return ret;
}


BOOL CModuleECS::ecs_LightAlarmSet()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;



	return ret;
}

BOOL CModuleECS::ecs_LightAlarmReset()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;



	return ret;
}


BOOL CModuleECS::ecs_HeavyAlarmSet()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;



	return ret;
}

BOOL CModuleECS::ecs_HeavyAlarmReset()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;



	return ret;
}


BOOL CModuleECS::ecs_T3TimeoutOccurrence()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;



	return ret;
}


BOOL CModuleECS::ecs_APD()		// Actual Process Data
{
	BOOL ret = FALSE;
	LONG devno = 0;

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;

	// LW_1B000 ~ 1B1FF에 APD Data를 Write한다.
	

	// APD 보고 설정 Bit를 Setting 한다.
	devno = lpSystemInfo->m_nLBStartAddr + 0x00A0;
	ecs_writeDataLB(devno, ECS_APD_REPORT, ON);


	// APD Report ACK를 확인한다.


	return ret;
}


BOOL CModuleECS::ecs_ControlStatusChangeReport()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };
	WORD sendData = 0;

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;

	// Step1. Control Status Data를 Setting 한다.
	devno = lpSystemInfo->m_nLWStartAddr1 + 0x0003;
	if(ecs_isOffLineMode() == TRUE)
		sendData = 0;
	else
		sendData = 1;

	sendLen = 2;
	ret = m_pApp->pMelsecnetG->mnetg_mdSendEx(PLC_DEVIDE_TYPE_LW, devno, &sendLen, &sendData);

	sLog.Format(_T("<MELSEC> LW Write : LW Address[%04X]  LW Data[%04X]"), devno, sendData);
	m_pApp->Gf_writeMLog(sLog);


	// Step2. Control Status Change Report Bit를 ON한다.
	devno = lpSystemInfo->m_nLBStartAddr + 0x0000;
	ecs_writeDataLB(devno, ECS_CONTROL_STATUS_CHANGE_REPORT, ON);

	// Step3. Delay 1초를 가져간다.
	delayMs(1000);

	// Step4. Control Status Change Report Bit를 OFF한다.
	devno = lpSystemInfo->m_nLBStartAddr + 0x0000;
	ecs_writeDataLB(devno, ECS_CONTROL_STATUS_CHANGE_REPORT, OFF);


	return ret;
}


BOOL CModuleECS::ecs_EQPStatusChangeReport()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };
	WORD sendData = 0;

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;

	// Step1. EQP Status Data를 Setting 한다.
	devno = lpSystemInfo->m_nLWStartAddr1 + 0x0003;
	sendData = m_pApp->m_nEcsEqpStatus;
	sendLen = 2;
	ret = m_pApp->pMelsecnetG->mnetg_mdSendEx(PLC_DEVIDE_TYPE_LW, devno, &sendLen, &sendData);

	sLog.Format(_T("<MELSEC> LW Write : LW Address[%04X]  LW Data[%04X]"), devno, sendData);
	m_pApp->Gf_writeMLog(sLog);

	if (m_pApp->m_nEcsEqpStatus == EQP_STATUS_DOWN)
		sendData = m_pApp->m_nLastAlarmCode;
	else
		sendData = 0;

	// Step2. Alarm Code를 셋팅한다.
	devno = lpSystemInfo->m_nLWStartAddr1 + 0x0004;
	sendLen = 2;
	ret = m_pApp->pMelsecnetG->mnetg_mdSendEx(PLC_DEVIDE_TYPE_LW, devno, &sendLen, &sendData);

	sLog.Format(_T("<MELSEC> LW Write : LW Address[%04X]  LW Data[%04X]"), devno, sendData);
	m_pApp->Gf_writeMLog(sLog);


	// Step3. EQP Status Change Report Bit를 ON한다.
	devno = lpSystemInfo->m_nLBStartAddr + 0x0000;
	ecs_writeDataLB(devno, ECS_EQP_STATUS_CHANGE_REPORT, ON);

	// Step4. Delay 1초를 가져간다.
	delayMs(1000);

	// Step5. EQP Status Change Report Bit를 OFF한다.
	devno = lpSystemInfo->m_nLBStartAddr + 0x0000;
	ecs_writeDataLB(devno, ECS_EQP_STATUS_CHANGE_REPORT, OFF);

	return ret;
}


BOOL CModuleECS::ecs_TakeOutReport(int ch)
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, devno_TOReg = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };
	WORD sendData[16] = { 0, };
	int mask = 0x0001;

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;

	// Step1. PID(Take Out Report Data) 정보를 Setting 한다.
	if((lpSystemInfo->m_nLineType== LINE_TYPE_CGA) || (lpSystemInfo->m_nLineType == LINE_TYPE_CP))
		devno = lpSystemInfo->m_nLWStartAddr1 + 0x0090;
	else if ((lpSystemInfo->m_nLineType == LINE_TYPE_OQC) || (lpSystemInfo->m_nLineType == LINE_TYPE_ASSEMBLY))
		devno = lpSystemInfo->m_nLWStartAddr1 + 0x0030;

	memcpy(sendData, lpEcsGlassData[ch]->PanelID, 16);
	sendLen = 16;
	ret = m_pApp->pMelsecnetG->mnetg_mdSendEx(PLC_DEVIDE_TYPE_LW, devno, &sendLen, sendData);
	sLog.Format(_T("<MELSEC> LW Write : LW Address[%04X]  LW Data[%04X]"), devno, sendData);
	m_pApp->Gf_writeMLog(sLog);


	// Step2. Take Out Report Bit를 ON한다.
	if ((lpSystemInfo->m_nLineType == LINE_TYPE_CGA) || (lpSystemInfo->m_nLineType == LINE_TYPE_CP))
	{
		devno = lpSystemInfo->m_nLBStartAddr + 0x0060;
		ecs_writeDataLB(devno, ECS_CGA_CP_TAKE_OUT_REPORT, ON);
	}
	else if ((lpSystemInfo->m_nLineType == LINE_TYPE_OQC) || (lpSystemInfo->m_nLineType == LINE_TYPE_ASSEMBLY))
	{
		devno = lpSystemInfo->m_nLBStartAddr + 0x0010;
		ecs_writeDataLB(devno, ECS_OQC_ASSM_TAKE_OUT_REPORT, ON);
	}

	if ((lpSystemInfo->m_nEcsEqpNumber >= 1) && (lpSystemInfo->m_nEcsEqpNumber <= 16))
	{
		devno_TOReg = 0x02C0;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 1);
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 17) && (lpSystemInfo->m_nEcsEqpNumber <= 32))
	{
		devno_TOReg = 0x02D0;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 17);
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 33) && (lpSystemInfo->m_nEcsEqpNumber <= 48))
	{
		devno_TOReg = 0x02E0;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 33);
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 49) && (lpSystemInfo->m_nEcsEqpNumber <= 64))
	{
		devno_TOReg = 0x02F0;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 49);
	}

	// Step3. Take Out Report_ACK Bit를 기다린다.
	DWORD sTick, eTick;
	sTick = ::GetTickCount();
	while (1)
	{
		eTick = ::GetTickCount();
		if ((eTick - sTick) > 3000)
		{
			ret = FALSE;
			break;
		}

		readData[0] = ecs_readDataLB(devno_TOReg);
		if (readData[0] & mask)
		{
			ret = TRUE;
			break;
		}
	}


	// Step4. Take Out Report Bit를 OFF 시킨다.
	if ((lpSystemInfo->m_nLineType == LINE_TYPE_CGA) || (lpSystemInfo->m_nLineType == LINE_TYPE_CP))
	{
		devno = lpSystemInfo->m_nLBStartAddr + 0x0060;
		ecs_writeDataLB(devno, ECS_CGA_CP_TAKE_OUT_REPORT, OFF);
	}
	else if ((lpSystemInfo->m_nLineType == LINE_TYPE_OQC) || (lpSystemInfo->m_nLineType == LINE_TYPE_ASSEMBLY))
	{
		devno = lpSystemInfo->m_nLBStartAddr + 0x0010;
		ecs_writeDataLB(devno, ECS_OQC_ASSM_TAKE_OUT_REPORT, OFF);
	}


	return ret;
}


BOOL CModuleECS::ecs_ECSRestart()
{
	CString sLog;
	BOOL ret = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;

	// Step1. ECS Restart Bit ON 감시
	readData[0] = ecs_readDataLB(0x0000);

	if (readData[0] & ECS_RESTART)
	{
		sLog.Format(_T("<MELSEC> ECS->EQP ECS Restart"));
		m_pApp->Gf_writeMLog(sLog);

		// Step2. ECS Restart ACK Bit ON 시킨다.
		devno = lpSystemInfo->m_nLBStartAddr + 0x0000;
		ecs_writeDataLB(devno, ECS_RESTART_ACK, ON);

		// Step3. ECS Restart Bit OFF 대기
		DWORD sTick, eTick;
		sTick = ::GetTickCount();
		while (1)
		{
			eTick = ::GetTickCount();

			readData[0] = ecs_readDataLB(0x0000);
			if ((readData[0] & ECS_RESTART) == 0)
			{
				break;
			}

			// ECS Restart Bit OFF되지 않을 시 3초후 ECS Restart Bit OFF후 False Return 시킨다.
			if ((eTick - sTick) > 3000)
			{
				devno = lpSystemInfo->m_nLBStartAddr + 0x0000;
				ecs_writeDataLB(devno, ECS_RESTART_ACK, OFF);
				return FALSE;
			}
			delayMs(1);
		}

		// Step4. ECS Restart ACK Bit OFF 시킨다.
		devno = lpSystemInfo->m_nLBStartAddr + 0x0000;
		ecs_writeDataLB(devno, ECS_RESTART_ACK, OFF);

		// Step5. Control Status Change Report Flow를 진행한다.
		ecs_ControlStatusChangeReport();

		// Step6. EQP Status Change Report Flow를 진행한다.
		ecs_EQPStatusChangeReport();
	}

	return ret;
}


BOOL CModuleECS::ecs_NormalOperation()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;



	return ret;
}


BOOL CModuleECS::ecs_GlassPositionData()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;



	return ret;
}


BOOL CModuleECS::ecs_LostGlassDataRequest(int type, char* pid)
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, devno_LPReg = 0, sendLen = 0, readSize = 0;
	WORD readData[64] = { 0, };
	WORD sendData[16] = { 0, };
	int mask = 0x0001;

	memset(sendData, 0x00, sizeof(sendData));

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;

	// Step1. 검사기 Lost Glass Data PID를 Write 한다.
	if ((lpSystemInfo->m_nLineType == LINE_TYPE_CGA) || (lpSystemInfo->m_nLineType == LINE_TYPE_CP))
	{
		devno = lpSystemInfo->m_nLWStartAddr1 + 0x0080;
	}
	else if ((lpSystemInfo->m_nLineType == LINE_TYPE_OQC) || (lpSystemInfo->m_nLineType == LINE_TYPE_ASSEMBLY))
	{
		devno = lpSystemInfo->m_nLWStartAddr1 + 0x0020;
	}
	sendLen = 32; // 16Word이므로 16Word * 2byte = 32byte이다.
	memcpy(sendData, pid, strlen(pid));
	sendData[0x0E] = type;
	ret = m_pApp->pMelsecnetG->mnetg_mdSendEx(PLC_DEVIDE_TYPE_LW, devno, &sendLen, sendData);


	// Step2. 검사기 Lost Glass Data Request Bit ON
	devno = lpSystemInfo->m_nLBStartAddr + 0x0010;
	ecs_writeDataLB(devno, ECS_LOST_GLASS_DATA_REQUEST, ON);


	if ((lpSystemInfo->m_nEcsEqpNumber >= 1) && (lpSystemInfo->m_nEcsEqpNumber <= 16))
	{
		devno_LPReg = 0x01C0;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 1);
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 17) && (lpSystemInfo->m_nEcsEqpNumber <= 32))
	{
		devno_LPReg = 0x01D0;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 17);
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 33) && (lpSystemInfo->m_nEcsEqpNumber <= 48))
	{
		devno_LPReg = 0x01E0;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 33);
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 49) && (lpSystemInfo->m_nEcsEqpNumber <= 64))
	{
		devno_LPReg = 0x01F0;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 49);
	}

	// Step3. ECS Lost Glass Data Report Bit ON을 확인한다.
	DWORD sTick, eTick;
	sTick = ::GetTickCount();
	while (1)
	{
		eTick = ::GetTickCount();
		if ((eTick - sTick) > 3000)
		{
			ecs_writeDataLB(devno, ECS_LOST_GLASS_DATA_REQUEST, OFF);
			return FALSE;
		}

		readData[0] = ecs_readDataLB(devno_LPReg);
		if (readData[0] & mask)
		{
			ret = TRUE;
			break;
		}
	}

	// Step4. Lost Panel Data를 가져 온다.
	devno = 0x00C0;
	readSize = 128; // WORD Type이기에 64Byte*2=128Byte로 Read 한다.
	m_pApp->pMelsecnetG->mnetg_mdReceiveEx(PLC_DEVIDE_TYPE_LW, devno, &readSize, readData);
	memcpy(lpEcsGlassData, readData, readSize);


	// Step5. ECS Lost Glass Data Report Bit OFF를 확인한다.
	sTick = ::GetTickCount();
	while (1)
	{
		eTick = ::GetTickCount();
		if ((eTick - sTick) > 3000)
		{
			ecs_writeDataLB(devno, ECS_LOST_GLASS_DATA_REQUEST, OFF);
			return FALSE;
		}

		readData[0] = ecs_readDataLB(devno_LPReg);
		if ((readData[0] & mask) == 0)
		{
			ret = TRUE;
			break;
		}
	}

	// Step6. 검사기 Lost Glass Data Request Bit를 OFF 시킨다.
	ecs_writeDataLB(devno, ECS_LOST_GLASS_DATA_REQUEST, OFF);

	return ret;
}


BOOL CModuleECS::ecs_LoadingType1Normal()
{
	BOOL ret = TRUE;
	LONG devno, devnoROBOT = 0, devnoEQP = 0;
	WORD readData[64] = { 0, };
	LONG readSize=0;

	devnoEQP = lpSystemInfo->m_nLBStartAddr + 0x0120;
	if (lpSystemInfo->m_nRobotInspUnitNumber == ECS_ROBOT_UNIT_1)
	{
		devnoROBOT = lpSystemInfo->m_nRobotLBStartAddr + 0x0170;
	}
	else if (lpSystemInfo->m_nRobotInspUnitNumber == ECS_ROBOT_UNIT_2)
	{
		devnoROBOT = lpSystemInfo->m_nRobotLBStartAddr + 0x0180;
	}

	// Step1. 화상 물류 Normal Status Bit 감시
	readData[0] = ecs_readDataLB(devnoROBOT);
	if (readData[0] & ECS_ROBOT_NORMAL_STATUS)
	{
		m_pApp->Gf_writeMLog(_T("<LOADING> ROBOT 'NORMAL STATUS' = 1"));
		// Step2. 검사기 Normal Status Bit ON
		ecs_writeDataLB(devnoEQP, ECS_EQP_NORMAL_STATUS, ON);

		// Step3. 검사기 Glass Data Request Bit ON
		ecs_writeDataLB(devnoEQP, ECS_EQP_GLASS_DATA_REQUEST, ON);

		// Step4. 화상물류 Glass Data Report Bit 감시
		DWORD sTick, eTIck;
		sTick = ::GetTickCount();
		while (1)
		{
			eTIck = ::GetTickCount();
			if ((eTIck - sTick) > 3000)
			{
				ecs_writeDataLB(devnoEQP, ECS_EQP_NORMAL_STATUS, OFF);
				ecs_writeDataLB(devnoEQP, ECS_EQP_GLASS_DATA_REQUEST, OFF);
				return FALSE;
			}
			readData[0] = ecs_readDataLB(devnoROBOT);
			if (readData[0] & ECS_ROBOT_GLASS_DATA_REPORT)
			{
				m_pApp->Gf_writeMLog(_T("<LOADING> ROBOT 'GLASS DATA REPORT' = 1"));

				if(lpSystemInfo->m_nRobotInspUnitNumber==ECS_ROBOT_UNIT_1)
					devno = lpSystemInfo->m_nRobotLWStartAddr1 + 0x0200;
				else if (lpSystemInfo->m_nRobotInspUnitNumber == ECS_ROBOT_UNIT_2)
					devno = lpSystemInfo->m_nRobotLWStartAddr1 + 0x0280;
				readSize = 128; // WORD Type이기에 64Byte*2=128Byte로 Read 한다.
				m_pApp->pMelsecnetG->mnetg_mdReceiveEx(PLC_DEVIDE_TYPE_LW, devno, &readSize, readData);
				memcpy(lpEcsGlassData, readData, readSize);
			}
		}

		// Step5. 검사기 Load Request Bit ON
		ecs_writeDataLB(devnoEQP, ECS_EQP_LOAD_REQUEST, ON);
		delayMs(10);

		// Step6. Loading 중비가 끝나면 검사기 Rear Door Open 한다.
		if (m_pApp->commApi->dio_RearDoorOpen() == FALSE)
		{
			ecs_writeDataLB(devnoEQP, ECS_EQP_NORMAL_STATUS, OFF);
			ecs_writeDataLB(devnoEQP, ECS_EQP_GLASS_DATA_REQUEST, OFF);
			ecs_writeDataLB(devnoEQP, ECS_EQP_LOAD_REQUEST, OFF);

			return FALSE;
		}

		// Step7. 검사기 Load Enable Bit ON
		ecs_writeDataLB(devnoEQP, ECS_EQP_LOAD_ENABLE, ON);

		// Step8. ROBOT이 loading 완료 신호를 보낼때까지 대기한다.
		sTick = ::GetTickCount();
		while (1)
		{
			eTIck = ::GetTickCount();
			if ((eTIck - sTick) > 30000)
			{
				ecs_writeDataLB(devnoEQP, ECS_EQP_NORMAL_STATUS, OFF);
				ecs_writeDataLB(devnoEQP, ECS_EQP_GLASS_DATA_REQUEST, OFF);
				return FALSE;
			}

			readData[0] = ecs_readDataLB(devnoROBOT);
			if (readData[0] & ECS_ROBOT_LOAD_COMPLETE)
			{
				m_pApp->Gf_writeMLog(_T("<LOADING> ROBOT 'LOAD COMPLETE' = 1"));

				ecs_writeDataLB(devnoEQP, ECS_EQP_LOAD_COMPLETE_CONFIRM, ON);
				delayMs(500);
				ecs_writeDataLB(devnoEQP, ECS_EQP_GLASS_DATA_REQUEST, OFF);
				ecs_writeDataLB(devnoEQP, ECS_EQP_LOAD_REQUEST, OFF);
				ecs_writeDataLB(devnoEQP, ECS_EQP_LOAD_COMPLETE_CONFIRM, OFF);

				sTick = ::GetTickCount();
				while (1)
				{
					eTIck = ::GetTickCount();
					if ((eTIck - sTick) > 3000)
					{
						ecs_writeDataLB(devnoEQP, ECS_EQP_LOAD_ENABLE, OFF);
						return FALSE;
					}
					readData[0] = ecs_readDataLB(devnoROBOT);
					if (((readData[0] & ECS_ROBOT_LOAD_NONINTERFERENCE) != 0)
						&& ((readData[0] & ECS_ROBOT_GLASS_DATA_REPORT) == 0)
						&& ((readData[0] & ECS_ROBOT_BUSY) == 0)
						&& ((readData[0] & ECS_ROBOT_LOAD_COMPLETE) == 0)
						)
					{
						ecs_writeDataLB(devnoEQP, ECS_EQP_LOAD_ENABLE, OFF);
						ret = TRUE;
						break;
					}

					delayMs(1);
				}
			}
			delayMs(1);
		}
	}

	return ret;
}


BOOL CModuleECS::ecs_UnLoadingType5Normal()
{
	BOOL ret = TRUE;
	LONG devno, devnoROBOT = 0, devnoEQP = 0;
	WORD readData[6] = { 0, };
	WORD sendData[64] = { 0, };
	LONG readSize = 0, sendSize = 0;

	devnoEQP = lpSystemInfo->m_nLBStartAddr + 0x0130;
	if (lpSystemInfo->m_nRobotInspUnitNumber == ECS_ROBOT_UNIT_1)
	{
		devnoROBOT = lpSystemInfo->m_nRobotLBStartAddr + 0x0150;
	}
	else if (lpSystemInfo->m_nRobotInspUnitNumber == ECS_ROBOT_UNIT_2)
	{
		devnoROBOT = lpSystemInfo->m_nRobotLBStartAddr + 0x0160;
	}

	// Step1. 검사기 Normal Status Bit ON
	ecs_writeDataLB(devnoEQP, ECS_EQP_NORMAL_STATUS, ON);

	// Step2. 화상 물류 Normal Status Bit 감시
	readData[0] = ecs_readDataLB(devnoROBOT);
	if (readData[0] & ECS_ROBOT_NORMAL_STATUS)
	{
		m_pApp->Gf_writeMLog(_T("<UNLOADING> ROBOT 'NORMAL STATUS' = 1"));

		devno = lpSystemInfo->m_nLWStartAddr1 + 0x0200;
		sendSize = 128; // WORD Type이기에 64Byte*2=128Byte로 Read 한다.
		memcpy(sendData, lpEcsGlassData, sendSize);
		m_pApp->pMelsecnetG->mnetg_mdSendEx(PLC_DEVIDE_TYPE_LW, devno, &sendSize, sendData);

		// Step3. 검사기 Glass Data Request Bit ON
		ecs_writeDataLB(devnoEQP, ECS_EQP_GLASS_DATA_REPORT, ON);

		// Step4. Delay Ms (500ms) : 물류 ROBOT에서 Glass Data를 Read하기 위한 강제 Delay. Report Confirm 신호가 없다
		delayMs(500);

		// Step5. 검사기 Unload Request Bit ON
		ecs_writeDataLB(devnoEQP, ECS_EQP_UNLOAD_REQUEST, ON);

		// Step6. Loading 중비가 끝나면 검사기 Rear Door Open 한다.
		if (m_pApp->commApi->dio_RearDoorOpen() == FALSE)
		{
			ecs_writeDataLB(devnoEQP, ECS_EQP_GLASS_DATA_REPORT, OFF);
			ecs_writeDataLB(devnoEQP, ECS_EQP_UNLOAD_REQUEST, OFF);
			return FALSE;
		}

		// Step7. 검사기 Unload Enable Bit ON
		ecs_writeDataLB(devnoEQP, ECS_EQP_UNLOAD_ENABLE, ON);

		// Step8. 화상물류 Unload Complete Bit 감시
		DWORD sTick, eTIck;
		sTick = ::GetTickCount();
		while (1)
		{
			eTIck = ::GetTickCount();
			if ((eTIck - sTick) > 30000)
			{
				ecs_writeDataLB(devnoEQP, ECS_EQP_GLASS_DATA_REPORT, OFF);
				ecs_writeDataLB(devnoEQP, ECS_EQP_UNLOAD_REQUEST, OFF);
				ecs_writeDataLB(devnoEQP, ECS_EQP_UNLOAD_ENABLE, OFF);
				return FALSE;
			}

			readData[0] = ecs_readDataLB(devnoROBOT);
			if (readData[0] & ECS_ROBOT_UNLOAD_COMPLETE)
			{
				m_pApp->Gf_writeMLog(_T("<LOADING> ROBOT 'UNLOAD COMPLETE' = 1"));
				ecs_writeDataLB(devnoEQP, ECS_EQP_UNLOAD_COMPLETE_CONFIRM, ON);
				delayMs(500);
				ecs_writeDataLB(devnoEQP, ECS_EQP_UNLOAD_COMPLETE_CONFIRM, OFF);
				ecs_writeDataLB(devnoEQP, ECS_EQP_GLASS_DATA_REPORT, OFF);
				ecs_writeDataLB(devnoEQP, ECS_EQP_UNLOAD_REQUEST, OFF);

				// Step10. 화상물류 BUSY=0, UNLOAD NONINTERFERENCE=1 Bit 감시
				sTick = ::GetTickCount();
				while (1)
				{
					eTIck = ::GetTickCount();
					if ((eTIck - sTick) > 3000)
					{
						ecs_writeDataLB(devnoEQP, ECS_EQP_UNLOAD_ENABLE, OFF);
						return FALSE;
					}
					readData[0] = ecs_readDataLB(devnoROBOT);
					if (((readData[0] & ECS_ROBOT_BUSY) == 0)
						&& ((readData[0] & ECS_ROBOT_UNLOAD_NONINTERFERENCE) != 0)
						)
					{
						ecs_writeDataLB(devnoEQP, ECS_EQP_UNLOAD_ENABLE, OFF);
						ret = TRUE;
						break;
					}
					delayMs(1);
				}
			}
			delayMs(1);
		}
	}

	return ret;
}


