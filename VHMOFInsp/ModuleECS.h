#pragma once

/////////////////////////////////////////////////////////////
#define PLC_DEVIDE_TYPE_LB					23
#define PLC_DEVIDE_TYPE_LW					24
////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
#define ECS_OFFLINE							0
#define ECS_ONLINE							1

/////////////////////////////////////////////////////////////////////////////
#define ECS_ROBOT_UNIT_1					0
#define ECS_ROBOT_UNIT_2					1
#define ECS_ROBOT_UNIT_3					2

////////////////////////////////////////////////////////////
#define ECS_RESTART							0x0001
#define ECS_RESTART_ACK						0x0001
#define ECS_TIME_SET_REQUEST				0x0002
#define ECS_LINK_REQUEST_ACK				0x0002
#define ECS_APD_REPORT						0x0001
#define ECS_LOST_GLASS_DATA_REQUEST			0x0001
#define ECS_CONTROL_STATUS_CHANGE_REPORT	0x0004
#define ECS_EQP_STATUS_CHANGE_REPORT		0x0008
#define ECS_CGA_CP_TAKE_OUT_REPORT			0x0001
#define ECS_OQC_ASSM_TAKE_OUT_REPORT		0x0040

#define ECS_ROBOT_LOAD_NONINTERFERENCE		0x0001
#define ECS_ROBOT_GLASS_DATA_REPORT			0x0002
#define ECS_ROBOT_BUSY						0x0004
#define ECS_ROBOT_LOAD_COMPLETE				0x0008
#define ECS_ROBOT_NORMAL_STATUS				0x0010

#define ECS_ROBOT_UNLOAD_NONINTERFERENCE	0x0001
#define ECS_ROBOT_UNLOAD_COMPLETE			0x0008

#define ECS_EQP_LOAD_ENABLE					0x0001
#define ECS_EQP_GLASS_DATA_REQUEST			0x0002
#define ECS_EQP_NORMAL_STATUS				0x0010
#define ECS_EQP_LOAD_REQUEST				0x0020
#define ECS_EQP_LOAD_COMPLETE_CONFIRM		0x0040

#define ECS_EQP_UNLOAD_ENABLE				0x0001
#define ECS_EQP_GLASS_DATA_REPORT			0x0002
#define ECS_EQP_UNLOAD_REQUEST				0x0020
#define ECS_EQP_UNLOAD_COMPLETE_CONFIRM		0x0040
////////////////////////////////////////////////////////////

class CModuleECS
{
public:
	CModuleECS();
	~CModuleECS();

	LPECSGLASSDATA	lpEcsGlassData[2];

	WORD ecs_readDataLB(LONG devno);
	BOOL ecs_writeDataLB(LONG devno, WORD maskBit, BOOL bOnOff);

	BOOL ecs_isOffLineMode();
	BOOL ecs_LinkTest();
	BOOL ecs_TimeDataSend();

	BOOL ecs_LightAlarmSet();
	BOOL ecs_LightAlarmReset();
	BOOL ecs_HeavyAlarmSet();
	BOOL ecs_HeavyAlarmReset();
	BOOL ecs_T3TimeoutOccurrence();
	BOOL ecs_APD();		// Actual Process Data
	BOOL ecs_ControlStatusChangeReport();
	BOOL ecs_EQPStatusChangeReport();
	BOOL ecs_TakeOutReport(int ch);
	BOOL ecs_ECSRestart();
	BOOL ecs_NormalOperation();
	BOOL ecs_GlassPositionData();
	BOOL ecs_LostGlassDataRequest(int type, char* pid);
	BOOL ecs_InterlockType1Load();
	BOOL ecs_InterlockType1UnLoad();
	BOOL ecs_InterlockType5UnLoad();
	BOOL ecs_InterlockType10Load();
	BOOL ecs_InterlockType10UnLoad();



protected:
	LPSYSTEMINFO		lpSystemInfo;


private:

};

