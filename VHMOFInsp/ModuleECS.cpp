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
BOOL CModuleECS::ecs_LinkTest()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[4] = { 0, };
	WORD sendData = 0;

	readSize = 8;
	devno = 0x00C0;
	ret = m_pApp->pMelsecnetG->mnetg_mdReceiveEx(PLC_DEVIDE_TYPE_LB, devno, &readSize, readData);

	if ((lpSystemInfo->m_nEcsEqpNumber >= 1) && (lpSystemInfo->m_nEcsEqpNumber <= 16))
	{
		int mask = 0x0001;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 1);
		if (readData[0] & mask)		bLinkTestSend = TRUE;
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 17) && (lpSystemInfo->m_nEcsEqpNumber <= 32))
	{
		int mask = 0x0001;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 17);
		if (readData[2] & mask)		bLinkTestSend = TRUE;
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 33) && (lpSystemInfo->m_nEcsEqpNumber <= 48))
	{
		int mask = 0x0001;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 33);
		if (readData[2] & mask)		bLinkTestSend = TRUE;
	}
	else if ((lpSystemInfo->m_nEcsEqpNumber >= 49) && (lpSystemInfo->m_nEcsEqpNumber <= 64))
	{
		int mask = 0x0001;
		mask = mask << (lpSystemInfo->m_nEcsEqpNumber - 49);
		if (readData[3] & mask)		bLinkTestSend = TRUE;
	}
	if(bLinkTestSend  == TRUE)
	{
		sendLen = 2;
		devno = lpSystemInfo->m_nLBStartAddr + 0x0001;
		m_pApp->pMelsecnetG->mnetg_mdReceiveEx(PLC_DEVIDE_TYPE_LB, devno, &readSize, &sendData);
		sendData |= ECS_LINK_REQUEST_ACK;
		ret = m_pApp->pMelsecnetG->mnetg_mdSendEx(PLC_DEVIDE_TYPE_LB, devno, &sendLen, &sendData);

		sLog.Format(_T("<MELSEC> LB Write : LB Address[%04X]  LB Data[%04X]"), devno, sendData);
		m_pApp->Gf_writeMLog(sLog);
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

	readSize = 2;
	devno = 0x0000;
	ret = m_pApp->pMelsecnetG->mnetg_mdReceiveEx(PLC_DEVIDE_TYPE_LB, devno, &readSize, readData);

	if (readData[0] & ECS_TIME_SET_REQUEST)
	{
		sLog.Format(_T("<MELSEC> ECS->EQP Time Set Request"));
		m_pApp->Gf_writeMLog(sLog);

		readSize = 12;
		devno = lpSystemInfo->m_nLWStartAddr;
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




	return ret;
}

BOOL CModuleECS::ecs_LightAlarmReset()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };




	return ret;
}


BOOL CModuleECS::ecs_HeavyAlarmSet()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };




	return ret;
}

BOOL CModuleECS::ecs_HeavyAlarmReset()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };




	return ret;
}


BOOL CModuleECS::ecs_T3TimeoutOccurrence()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };




	return ret;
}


BOOL CModuleECS::ecs_APD()		// Actual Process Data
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };




	return ret;
}


BOOL CModuleECS::ecs_ControlStatusChangeReport()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };




	return ret;
}


BOOL CModuleECS::ecs_EQPStatusChangeReport()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };




	return ret;
}


BOOL CModuleECS::ecs_TakeOutReport()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };




	return ret;
}


BOOL CModuleECS::ecs_ECSRestart()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };




	return ret;
}


BOOL CModuleECS::ecs_NormalOperation()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };




	return ret;
}


BOOL CModuleECS::ecs_GlassPositionData()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };




	return ret;
}


BOOL CModuleECS::ecs_LostGlassDataRequest()
{
	CString sLog;
	BOOL ret = FALSE;
	BOOL bLinkTestSend = FALSE;
	LONG devno = 0, sendLen = 0, readSize = 0;
	WORD readData[6] = { 0, };




	return ret;
}