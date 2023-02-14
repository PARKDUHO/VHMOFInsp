#pragma once

/////////////////////////////////////////////////////////////
#define PLC_DEVIDE_TYPE_LB				23
#define PLC_DEVIDE_TYPE_LW				24
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
#define ECS_TIME_SET_REQUEST			0x0002


#define ECS_LINK_REQUEST_ACK			0x0002
////////////////////////////////////////////////////////////

class CModuleECS
{
public:
	CModuleECS();
	~CModuleECS();

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
	BOOL ecs_TakeOutReport();
	BOOL ecs_ECSRestart();
	BOOL ecs_NormalOperation();
	BOOL ecs_GlassPositionData();
	BOOL ecs_LostGlassDataRequest();



protected:
	LPSYSTEMINFO		lpSystemInfo;


private:

};

