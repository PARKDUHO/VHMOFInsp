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

		Sleep(100);
	}
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CModuleECS::CModuleECS()
{
	lpSystemInfo = m_pApp->GetSystemInfo();


	AfxBeginThread(ThreadModuleECS, this);
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
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData = 0;
	WORD sendData = 0;

	if (ecs_isOffLineMode() == TRUE)
		return TRUE;

	if ((lpSystemInfo->m_nEcsEqpNumber >= 1) && (lpSystemInfo->m_nEcsEqpNumber <= 16))
	{
		readData = ecs_readDataLB(0x00C0);

		int mask = 0x0001;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 1);
		if (readData & mask)		bLinkTestSend = TRUE;
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 17) && (lpSystemInfo->m_nEcsEqpNumber <= 32))
	{
		readData = ecs_readDataLB(0x00D0);

		int mask = 0x0001;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 17);
		if (readData & mask)		bLinkTestSend = TRUE;
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 33) && (lpSystemInfo->m_nEcsEqpNumber <= 48))
	{
		readData = ecs_readDataLB(0x00E0);

		int mask = 0x0001;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 33);
		if (readData & mask)		bLinkTestSend = TRUE;
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 49) && (lpSystemInfo->m_nEcsEqpNumber <= 64))
	{
		readData = ecs_readDataLB(0x00F0);

		int mask = 0x0001;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 49);
		if (readData & mask)		bLinkTestSend = TRUE;
	}
	if(bLinkTestSend  == TRUE)
	{
		devno = lpSystemInfo->m_nLBStartAddr + 0x0000;
		ecs_writeDataLB(devno, ECS_LINK_REQUEST_ACK, ON);
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


BOOL CModuleECS::ecs_TakeOutReport()
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


BOOL CModuleECS::ecs_LostGlassDataRequest()
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