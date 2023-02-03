#pragma once

#ifndef _GOLBAL_DEFINE_
#define _GOLBAL_DEFINE_


#define CODE_QSPI_USE					0
#define CODE_PATTERN_POWER_SET_USE		0
#define CODE_DFS_SETTING_USE			0


/////////////////////////////////////////////////////////////////////////////Đs
#define PGM_VERSION						_T("1.0.0_R1")
#define DEFAULT_FONT					_T("Tahoma")

/////////////////////////////////////////////////////////////////////////////
#define MLOG_MAX_LENGTH					16*1024

/////////////////////////////////////////////////////////////////////////////
#define DEBUG_TCP_RECEIVE_OK			0
#define	DEBUG_GMES_TEST_SERVER			0
#define DEBUG_TCP_COMM_LOG				0
#define DEBUG_PALLET_ARRIVE				0
#define DEBUG_DIO_SKIP					0
#define DEBUG_ROBOT_WAIT_CHECK_ON		1
#define DEBUG_PG1_TEST_ONLY				1
#define DEBUG_DIO_ALARM_DISABLE			0

/////////////////////////////////////////////////////////////////////////////
#define TCP_MAIN1_MCU_IP				_T("192.168.1.14")	// 13
#define TCP_MAIN2_MCU_IP				_T("192.168.1.15")	// 14

#define TCP_MAIN1_FPGA_IP				_T("192.168.1.3")
#define TCP_MAIN2_FPGA_IP				_T("192.168.1.4")

#define UDP_DIO_BOARD1_IP				_T("192.168.1.20")
#define UDP_DIO_BOARD2_IP				_T("192.168.1.21")

#define TCP_SPI_BOARD1_IP				_T("192.168.1.30")
#define TCP_SPI_BOARD2_IP				_T("192.168.1.31")

#define TCP_MAIN_PORT					50001
#define TCP_SPI_PORT					50004

/////////////////////////////////////////////////////////////////////////////
#define PACKET_SIZE						1024*64

/////////////////////////////////////////////////////////////////////////////
// ON/OFF와 TRUE/FALSE에 관련된 Define은 여기에서 한다.
/////////////////////////////////////////////////////////////////////////////
#define _OFF_							0
#define _ON_							1

#define _DISABLE_						0
#define _ENABLE_						1

#define POWER_OFF						0
#define POWER_ON						1

#define NACK							0
#define ACK								1

#define _CLEAR_							0
#define _SET_							1

#define QTY_OK							0
#define QTY_NG							1

#define ROOM_LED_ON						0
#define ROOM_LED_OFF					1

/////////////////////////////////////////////////////////////////////////////
#define PTN_LIST_MAX					500
#define HOTKEY_LIST_MAX					10

/////////////////////////////////////////////////////////////////////////////
#define OFF_LINE						0
#define IN_LINE							1

/////////////////////////////////////////////////////////////////////////////
#define SIGNAL_TYPE_LVDS				0
#define SIGNAL_TYPE_DP					1
#define SIGNAL_TYPE_ALPLD				2

/////////////////////////////////////////////////////////////////////////////
#define ALPDP_INIT_NONE					0
#define ALPDP_INIT_X2146				1
#define ALPDP_INIT_X2180				2

/////////////////////////////////////////////////////////////////////////////
#define SINGLE							0
#define DUAL							1
#define QUAD							2

/////////////////////////////////////////////////////////////////////////////
#define I2C_LINE_ODC					0
#define I2C_LINE_GENERIC				3

#define I2C_ADDR_BYTE					0
#define I2C_ADDR_WORD					1

/////////////////////////////////////////////////////////////////////////////
#define MSG_ERROR						0
#define MSG_WARNING						1


#define CH1								0
#define CH2								1
#define MAX_CH							2

/////////////////////////////////////////////////////////////////////////////
//DIO
/////////////////////////////////////////////////////////////////////////////
#define AIF_NORMAL_CYLINDER_WAIT_TIME	2000
#define AIF_DOOR_OPEN_CLOSE_WAIT_TIME	15000
#define AIF_ROBOT_IN_SENSOR_WAIT_TIME	30000
#define AIF_ROBOT_OUT_SENSOR_WAIT_TIME	30000
#define AIF_CARRIER_JIG_IN_WAIT_TIME	10000
#define AIF_JIG_TILTING_WAIT_TIME		20000

#define CLAMP_ERROR_LOCK				0
#define CLAMP_ERROR_UNLOCK				1


static CString strNameDIN1[40] =
{
	_T("EMO_SWITCH"),
	_T("START_SWITCH"),
	_T("RESET_SWITCH"),
	_T("MUTTING_SWITCH"),
	_T("LIGHT_CURTAIN"),
	_T("LEFT_SAFETY_DOOR"),
	_T("RIGHT_SAFETY_DOOR"),
	_T("DOOR HOLDING FORWARD"),
	_T("DOOR HOLDING BACKWARD"),
	_T("FAN_IN_ALARM"),
	_T("FAN_OUT_ALARM"),
	_T("TEMPATURE_HIGH_ALARM"),
	_T("MAIN_AIR_DIGITAL_GAGE"),
	_T("IONIZER_AIR_DIGITAL_GAGE"),
	_T("CYLINDER_DIGITAL_GAGE"),
	_T("JIG_DIGITAL_GAGE"),
	_T("IONIZER_ALARM"),
	_T(""),
	_T("ROBOT_IN_SENSOR_1"),
	_T("ROBOT_IN_SENSOR_2"),
	_T("FRONT_DOOR_LEFT_DOWN"),
	_T("FRONT_DOOR_LEFT_UP"),
	_T("FRONT_DOOR_RIGHT_DOWN"),
	_T("FRONT_DOOR_RIGHT_UP"),
	_T("REAR_DOOR_LEFT_DOWN"),
	_T("REAR_DOOR_LEFT_UP"),
	_T("REAR_DOOR_RIGHT_DOWN"),
	_T("REAR_DOOR_RIGHT_UP"),
	_T("JIG_DOWN_1_SENSOR"),
	_T("JIG_UP_CYLINDER_60_SENSOR"),
	_T("JIG_DOWN_2_SENSOR"),
	_T("JIG_UP_CYLINDER_70_SENSOR"),
	_T("JIG_DOWN_3_SENSOR"),
	_T("JIG_UP_3_SENSOR"),
	_T("SAFETY ALARM"),
	_T(""),
	_T(""),
	_T(""),
	_T(""),
	_T("")
};

static CString strNameDIN2[40] =
{
	_T("JIG_HOME_SENSOR"),
	_T("JIG_DOOR_CLOSE_SENSOR"),
	_T("TILTING_60_SENSOR"),
	_T("TILTING_70_SENSOR"),
	_T("CH1_JIG_TRAY_IN_SENSOR"),
	_T("CH2_JIG_TRAY_IN_SENSOR"),
	_T("CH1_TRAY_UNCLAMP1"),
	_T("CH1_TRAY_UNCLAMP2"),
	_T("CH1_TRAY_UNCLAMP3"),
	_T("CH1_TRAY_UNCLAMP4"),
	_T("CH1_TRAY_UNCLAMP5"),
	_T("CH1_TRAY_UNCLAMP6"),
	_T("CH2_TRAY_UNCLAMP1"),
	_T("CH2_TRAY_UNCLAMP2"),
	_T("CH2_TRAY_UNCLAMP3"),
	_T("CH2_TRAY_UNCLAMP4"),
	_T("CH2_TRAY_UNCLAMP5"),
	_T("CH2_TRAY_UNCLAMP6"),
	_T("CH1_ADSORPTION_GAUGE1"),
	_T("CH1_ADSORPTION_GAUGE2"),
	_T("CH2_ADSORPTION_GAUGE1"),
	_T("CH2_ADSORPTION_GAUGE2"),
	_T("CH1_PIN_BLOCK_CLOSE"),
	_T("CH2_PIN_BLOCK_CLOSE"),
	_T("CH1_KEY_AUTO_MANUAL"),
	_T("CH1_KEY_BACK"),
	_T("CH1_KEY_NEXT"),
	_T("CH1_KEY_REPEAT"),
	_T("CH1_KEY_RESET"),
	_T("CH1_KEY_UP"),
	_T("CH1_KEY_DOWN"),
	_T("CH1_KEY_SEND"),
	_T("CH2_KEY_AUTO_MANUAL"),
	_T("CH2_KEY_BACK"),
	_T("CH2_KEY_NEXT"),
	_T("CH2_KEY_REPEAT"),
	_T("CH2_KEY_RESET"),
	_T("CH2_KEY_UP"),
	_T("CH2_KEY_DOWN"),
	_T("CH2_KEY_SEND")
};

static CString strNameDOUT1[24] =
{
	_T("TOWER_LAMP_RED"),
	_T("TOWER_LAMP_YELLOW"),
	_T("TOWER_LAMP_GREEN"),
	_T("TOWER_LAMP_BUZZER"),
	_T("MUTTING_1"),
	_T("MUTTING_2"),
	_T("LEFT_SAFETY_DOOR_OPEN"),
	_T("RIGHT_SAFETY_DOOR_OPEN"),
	_T("FRONT_DOOR_DOWN"),
	_T("FRONT_DOOR_UP"),
	_T("REAR_DOOR_DOWN"),
	_T("REAR_DOOR_UP"),
	_T("JIG_TILTING01_DOWN"),
	_T("JIG_TILTING01_UP"),
	_T("JIG_TILTING02_DOWN"),
	_T("JIG_TILTING02_UP"),
	_T("IONIZER_BLOW_ON"),
	_T("IONIZER_ON_OFF"),
	_T("LED_OFF"),
	_T("IONIZER_BLOW_OFF"),
	_T("ROBOT_IN_LAMP_ON"),
	_T("DOOR HOLDING BACKWARD"),
	_T("DOOR HOLDING FORWARD"),
	_T("")
};

static CString strNameDOUT2[24] =
{
	_T("CH1_TRAY_UNCLAMP_1"),
	_T("CH1_TRAY_UNCLAMP_2"),
	_T("CH1_TRAY_UNCLAMP_3"),
	_T("CH1_TRAY_UNCLAMP_4"),
	_T("CH1_TRAY_UNCLAMP_5"),
	_T("CH1_TRAY_UNCLAMP_6"),
	_T("CH2_TRAY_UNCLAMP_1"),
	_T("CH2_TRAY_UNCLAMP_2"),
	_T("CH2_TRAY_UNCLAMP_3"),
	_T("CH2_TRAY_UNCLAMP_4"),
	_T("CH2_TRAY_UNCLAMP_5"),
	_T("CH2_TRAY_UNCLAMP_6"),
	_T("CH1_ADSORPTION_EJECTOR1"),
	_T("CH1_ADSORPTION_EJECTOR2"),
	_T("CH1_PIN_CYLINDER_UP"),
	_T("CH2_ADSORPTION_EJECTOR1"),
	_T("CH2_ADSORPTION_EJECTOR2"),
	_T("CH2_PIN_CYLINDER_UP"),
	_T(""),
	_T(""),
	_T(""),
	_T(""),
	_T(""),
	_T("")
};

#define DIN_D1_EMO_SWITCH							(0x01 << 0)
#define DIN_D1_START_SWITCH							(0x01 << 1)
#define DIN_D1_RESET_SWITCH							(0x01 << 2)
#define DIN_D1_MUTTING_SWITCH						(0x01 << 3)
#define DIN_D1_LIGHT_CURTAIN						(0x01 << 4)
#define DIN_D1_LEFT_SAFETY_DOOR						(0x01 << 5)
#define DIN_D1_RIGHT_SAFETY_DOOR					(0x01 << 6)
#define DIN_D1_SHUTTER_HOLDING_FORWARD				(0x01 << 7)

#define DIN_D1_SHUTTER_HOLDING_BACKWARD				(0x01 << 0)
#define DIN_D1_FAN_IN_ALARM							(0x01 << 1)
#define DIN_D1_FAN_OUT_ALARM						(0x01 << 2)
#define DIN_D1_TEMPATURE_HIGH_ALARM					(0x01 << 3)
#define DIN_D1_MAIN_AIR_DIGITAL_PRESSURE_GAGE		(0x01 << 4)
#define DIN_D1_IONIZER_AIR_DIGITAL_PRESSURE_GAGE	(0x01 << 5)
#define DIN_D1_CYLINDER_DIGITAL_PRESSURE_GAGE		(0x01 << 6)
#define DIN_D1_JIG_DIGITAL_PRESSURE_GAGE			(0x01 << 7)

#define DIN_D1_IONIZER_ALARM						(0x01 << 0)
#define DIN_D1_IONIZER_SPARE						(0x01 << 1)
#define DIN_D1_ROBOT_IN_SENSOR_1					(0x01 << 2)
#define DIN_D1_ROBOT_IN_SENSOR_2					(0x01 << 3)
#define DIN_D1_FRONT_DOOR_LEFT_CYLINDER_DOWN		(0x01 << 4)
#define DIN_D1_FRONT_DOOR_LEFT_CYLINDER_UP			(0x01 << 5)
#define DIN_D1_FRONT_DOOR_RIGHT_CYLINDER_DOWN		(0x01 << 6)
#define DIN_D1_FRONT_DOOR_RIGHT_CYLINDER_UP			(0x01 << 7)

#define DIN_D1_REAR_DOOR_LEFT_CYLINDER_DOWN			(0x01 << 0)
#define DIN_D1_REAR_DOOR_LEFT_CYLINDER_UP			(0x01 << 1)
#define DIN_D1_REAR_DOOR_RIGHT_CYLINDER_DOWN		(0x01 << 2)
#define DIN_D1_REAR_DOOR_RIGHT_CYLINDER_UP			(0x01 << 3)
#define DIN_D1_JIG_DOWN_1_SENSOR					(0x01 << 4)
#define DIN_D1_JIG_UP_CYLINDER_60_SENSOR			(0x01 << 5)
#define DIN_D1_JIG_DOWN_2_SENSOR					(0x01 << 6)
#define DIN_D1_JIG_UP_CYLINDER_70_SENSOR			(0x01 << 7)

#define DIN_D1_JIG_DOWN_3_SENSOR					(0x01 << 0)
#define DIN_D1_JIG_UP_3_SENSOR						(0x01 << 1)
#define DIN_D1_SAFETY_PLC_ALARM						(0x01 << 2)
#define DIN_D1_SPARE2								(0x01 << 3)
#define DIN_D1_SPARE3								(0x01 << 4)
#define DIN_D1_SPARE4								(0x01 << 5)
#define DIN_D1_SPARE5								(0x01 << 6)
#define DIN_D1_SPARE6								(0x01 << 7)

////////////////////////////////////////////////////////////////////////////////
#define	DOUT_D1_TOWER_LAMP_RED						0x000001
#define	DOUT_D1_TOWER_LAMP_YELLOW					0x000002
#define	DOUT_D1_TOWER_LAMP_GREEN					0x000004
#define	DOUT_D1_TOWER_LAMP_BUZZER					0x000008
#define	DOUT_D1_MUTTING_1							0x000010
#define	DOUT_D1_MUTTING_2							0x000020
#define	DOUT_D1_LEFT_SAFETY_DOOR_OPEN				0x000040
#define	DOUT_D1_RIGHT_SAFETY_DOOR_OPEN				0x000080
#define	DOUT_D1_FRONT_SHUTTER_DOWN					0x000100
#define	DOUT_D1_FRONT_SHUTTER_UP					0x000200
#define	DOUT_D1_REAR_SHUTTER_DOWN					0x000400
#define	DOUT_D1_REAR_SHUTTER_UP						0x000800
#define	DOUT_D1_JIG_TILTING01_DOWN					0x001000
#define	DOUT_D1_JIG_TILTING01_UP					0x002000
#define	DOUT_D1_JIG_TILTING02_DOWN					0x004000
#define	DOUT_D1_JIG_TILTING02_UP					0x008000
#define	DOUT_D1_IONIZER_BLOW_ON						0x010000
#define	DOUT_D1_IONIZER_ON_OFF						0x020000
#define	DOUT_D1_LED_OFF								0x040000
#define	DOUT_D1_IONIZER_BLOW_OFF					0x080000
#define	DOUT_D1_ROBOT_IN_LED						0x100000
#define	DOUT_D1_SHUTTER_HOLDING_BACKWARD			0x200000
#define	DOUT_D1_SHUTTER_HOLDING_FORWARD				0x400000
#define	DOUT_D1_SPARE4								0x800000

////////////////////////////////////////////////////////////////////////////////
#define DIN_D2_JIG_HOME_SENSOR						(0x01 << 0)
#define DIN_D2_JIG_DOOR_CLOSE_PHOTO_SENSOR			(0x01 << 1)
#define DIN_D2_TILTING_60_SENSOR					(0x01 << 2)
#define DIN_D2_TILTING_70_SENSOR					(0x01 << 3)
#define DIN_D2_CH1_JIG_TRAY_IN_SENSOR				(0x01 << 4)
#define DIN_D2_CH2_JIG_TRAY_IN_SENSOR				(0x01 << 5)
#define DIN_D2_CH1_TRAY_UNCLAMP1					(0x01 << 6)
#define DIN_D2_CH1_TRAY_UNCLAMP2					(0x01 << 7)

#define DIN_D2_CH1_TRAY_UNCLAMP3					(0x01 << 0)
#define DIN_D2_CH1_TRAY_UNCLAMP4					(0x01 << 1)
#define DIN_D2_CH1_TRAY_UNCLAMP5					(0x01 << 2)
#define DIN_D2_CH1_TRAY_UNCLAMP6					(0x01 << 3)
#define DIN_D2_CH2_TRAY_UNCLAMP1					(0x01 << 4)
#define DIN_D2_CH2_TRAY_UNCLAMP2					(0x01 << 5)
#define DIN_D2_CH2_TRAY_UNCLAMP3					(0x01 << 6)
#define DIN_D2_CH2_TRAY_UNCLAMP4					(0x01 << 7)

#define DIN_D2_CH2_TRAY_UNCLAMP5					(0x01 << 0)
#define DIN_D2_CH2_TRAY_UNCLAMP6					(0x01 << 1)
#define DIN_D2_SPARE1								(0x01 << 2)
#define DIN_D2_SPARE2								(0x01 << 3)
#define DIN_D2_SPARE3								(0x01 << 4)
#define DIN_D2_SPARE4								(0x01 << 5)
#define DIN_D2_SPARE5								(0x01 << 6)
#define DIN_D2_SPARE6								(0x01 << 7)

#define DIN_D2_CH1_KEYPAD_AUTO_MANUAL				(0x01 << 0)
#define DIN_D2_CH1_KEYPAD_BACK						(0x01 << 1)
#define DIN_D2_CH1_KEYPAD_NEXT						(0x01 << 2)
#define DIN_D2_CH1_KEYPAD_REPEAT					(0x01 << 3)
#define DIN_D2_CH1_KEYPAD_RESET						(0x01 << 4)
#define DIN_D2_CH1_KEYPAD_UP						(0x01 << 5)
#define DIN_D2_CH1_KEYPAD_DOWN						(0x01 << 6)
#define DIN_D2_CH1_KEYPAD_SEND						(0x01 << 7)

#define DIN_D2_CH2_KEYPAD_AUTO_MANUAL				(0x01 << 0)
#define DIN_D2_CH2_KEYPAD_BACK						(0x01 << 1)
#define DIN_D2_CH2_KEYPAD_NEXT						(0x01 << 2)
#define DIN_D2_CH2_KEYPAD_REPEAT					(0x01 << 3)
#define DIN_D2_CH2_KEYPAD_RESET						(0x01 << 4)
#define DIN_D2_CH2_KEYPAD_UP						(0x01 << 5)
#define DIN_D2_CH2_KEYPAD_DOWN						(0x01 << 6)
#define DIN_D2_CH2_KEYPAD_SEND						(0x01 << 7)

////////////////////////////////////////////////////////////////////////////////
#define	DOUT_D2_CH1_TRAY_UNCLAMP_1					0x000001
#define	DOUT_D2_CH1_TRAY_UNCLAMP_2					0x000002
#define	DOUT_D2_CH1_TRAY_UNCLAMP_3					0x000004
#define	DOUT_D2_CH1_TRAY_UNCLAMP_4					0x000008
#define	DOUT_D2_CH1_TRAY_UNCLAMP_5					0x000010
#define	DOUT_D2_CH1_TRAY_UNCLAMP_6					0x000020
#define	DOUT_D2_CH2_TRAY_UNCLAMP_1					0x000040
#define	DOUT_D2_CH2_TRAY_UNCLAMP_2					0x000080
#define	DOUT_D2_CH2_TRAY_UNCLAMP_3					0x000100
#define	DOUT_D2_CH2_TRAY_UNCLAMP_4					0x000200
#define	DOUT_D2_CH2_TRAY_UNCLAMP_5					0x000400
#define	DOUT_D2_CH2_TRAY_UNCLAMP_6					0x000800
#define	DOUT_D2_CH1_ADSORPTION_EJECTOR				0x001000
#define	DOUT_D2_CH1_PIN_CYLINDER_UP					0x002000
#define	DOUT_D2_CH2_ADSORPTION_EJECTOR				0x004000
#define	DOUT_D2_CH2_PIN_CYLINDER_UP					0x008000
#define	DOUT_D2_SPARE1								0x010000
#define	DOUT_D2_SPARE2								0x020000
#define	DOUT_D2_SPARE3								0x040000
#define	DOUT_D2_SPARE4								0x080000
#define	DOUT_D2_SPARE5								0x100000
#define	DOUT_D2_SPARE6								0x200000
#define	DOUT_D2_SPARE7								0x400000
#define	DOUT_D2_SPARE8								0x800000




////////////////////////////////////////////
//------------GMES DEFINE-------------------
#define	HOST_EAYT					0
#define	HOST_UCHK					1
#define	HOST_EDTI					2
#define	HOST_PCHK					3
#define	HOST_EPCR					4
#define	HOST_FLDR					5
#define	HOST_EICR					6
#define	HOST_AGN_INSP				7
#define	HOST_EQCC					8
#define	HOST_APDR					9


#define SERVER_MES					0
#define SERVER_EAS					1

/////////////////////////////////////////////////////////////////////////////
// COLORREF
/////////////////////////////////////////////////////////////////////////////
#define COLOR_BLACK					RGB(0,0,0)
#define COLOR_WHITE					RGB(255,255,255)
#define COLOR_RED					RGB(255,0,0)
#define COLOR_GREEN					RGB(0,255,0)
#define COLOR_BLUE					RGB(0,0,255)
#define COLOR_YELLOW				RGB(255,255,0)
#define COLOR_CYAN					RGB(0,255,255)
#define COLOR_SKYBLUE				RGB(173,216,230)
#define COLOR_SEABLUE				RGB(31,78,121)
#define COLOR_ORANGE				RGB(245,136,22)
#define COLOR_VERDANT				RGB(116,192,24)
#define COLOR_VERDANT2				RGB(154,205,50)
#define COLOR_GRAY32				RGB(32,32,32)
#define COLOR_GRAY64				RGB(64,64,64)
#define COLOR_GRAY94				RGB(94,94,94)
#define COLOR_GRAY96				RGB(96,96,96)
#define COLOR_GRAY128				RGB(128,128,128)
#define COLOR_GRAY159				RGB(159,159,159)
#define COLOR_GRAY192				RGB(192,192,192)
#define COLOR_GRAY224				RGB(224,224,224)
#define COLOR_GRAY240				RGB(240,240,240)
#define COLOR_GREEN128				RGB(0,128,0)
#define COLOR_RED128				RGB(128,0,0)
#define COLOR_BLUE128				RGB(0,0,128)
#define COLOR_PINK					RGB(255,192,192)
#define COLOR_MAGENTA				RGB(224,0,224)
#define COLOR_DARK_RED				RGB(255,63,63)
#define COLOR_DARK_GREEN			RGB(63,192,63)
#define COLOR_DARK_BLUE				RGB(63,63,255)
#define COLOR_DARK_ORANGE			RGB(230,160,0)
#define COLOR_DARK_YELLOW			RGB(127,127,32)
#define COLOR_DARK_MAGENTA			RGB(64,16,64)
#define COLOR_BLUISH				RGB(65, 105, 225)
#define COLOR_LIGHT_RED				RGB(255,224,224)
#define COLOR_LIGHT_GREEN			RGB(224,255,224)
#define COLOR_LIGHT_BLUE			RGB(224,224,255)
#define COLOR_LIGHT_ORANGE			RGB(255,234,218)
#define COLOR_LIGHT_CYAN			RGB(150,230,220)
#define COLOR_LIGHT_YELLOW			RGB(254,250,205)
#define COLOR_JADEGREEN				RGB(192,220,192)
#define COLOR_JADEBLUE				RGB(0,156,220)
#define COLOR_JADERED				RGB(236,112,112)
#define COLOR_DEEP_BLUE				RGB(77,97,128)

typedef enum _COLOR_IDX_{
	COLOR_IDX_BLACK=0,
	COLOR_IDX_RED,
	COLOR_IDX_GREEN,
	COLOR_IDX_BLUE,
	COLOR_IDX_YELLOW,
	COLOR_IDX_ORANGE,
	COLOR_IDX_VERDANT,
	COLOR_IDX_VERDANT2,
	COLOR_IDX_CYAN,
	COLOR_IDX_MAGENTA,
	COLOR_IDX_SKYBLUE,
	COLOR_IDX_SEABLUE,
	COLOR_IDX_LIGHT_RED,
	COLOR_IDX_LIGHT_GREEN,
	COLOR_IDX_LIGHT_BLUE,
	COLOR_IDX_LIGHT_ORANGE,
	COLOR_IDX_LIGHT_CYAN,
	COLOR_IDX_LIGHT_YELLOW,
	COLOR_IDX_GRAY64,
	COLOR_IDX_GRAY94,
	COLOR_IDX_GRAY96,
	COLOR_IDX_GRAY128,
	COLOR_IDX_GRAY159,
	COLOR_IDX_GRAY192,
	COLOR_IDX_GRAY224,
	COLOR_IDX_GRAY240,
	COLOR_IDX_RED128,
	COLOR_IDX_GREEN128,
	COLOR_IDX_BLUE128,
	COLOR_IDX_PINK,
	COLOR_IDX_BLUISH,
	COLOR_IDX_JADEGREEN,
	COLOR_IDX_JADEBLUE,
	COLOR_IDX_JADERED,
	COLOR_IDX_DARK_RED,
	COLOR_IDX_DARK_GREEN,
	COLOR_IDX_DARK_BLUE,
	COLOR_IDX_DARK_ORANGE,
	COLOR_IDX_DARK_YELLOW,
	COLOR_IDX_DARK_MAGENTA,
	COLOR_IDX_WHITE,
	COLOR_IDX_DEEP_BLUE,
	COLOR_IDX_MAX
}_COLOR_IDX_;

#define FONT_IDX_MAX			10

/////////////////////////////////////////////////////////////////////////////
// Control Target Command
/////////////////////////////////////////////////////////////////////////////
#define TARGET_PC								0xA1
#define TARGET_MAIN								0xA2
#define TARGET_IF								0xA3
#define TARGET_DIO								0xA9

#define PACKET_STX								0x02
#define PACKET_ETX								0x03

#define PG_CMD									0x10						
#define NIOS_CMD								0x20

#define PACKET_PT_SOURCE						1
#define PACKET_PT_DEST							3
#define PACKET_PT_ID							5
#define PACKET_PT_CMD							7//+6
#define PACKET_PT_LEN							9//+6
#define PACKET_PT_RET							13//+6
#define PACKET_PT_DATA							14//+6

/////////////////////////////////////////////////////////////////////////////
// PG Command Packet
/////////////////////////////////////////////////////////////////////////////
// Command Define
#define FLASH_PAGE_SIZE						(1024*32)
#define I2C_PAGE_SIZE						(1024*32)

#define CMD_MAX_PACKET_LEN					2000		// 한번에 전송하는 최대 Data Length

#define CMD_PG_PATTERN_INFO					0x10
#define CMD_PG_DRAWPATTERN					0x14
#define CMD_PG_BMP_SET_WRITE_ADDR			0x1C
#define CMD_PG_BMP_TRANSPARENT_COLOR		0x1D

#define CMD_PG_BMP_WR_FILENAME				0x15
#define CMD_PG_BMP_WR_RAWDATA				0x17
#define CMD_PG_BMP_WRITE_COMPLETE			0x1E

#define CMD_IF_FUSING_SYSTEM				0x20
#define CMD_IF_CABLE_OPEN					0x29

#define CMD_IF_I2C_WRITE					0x30
#define CMD_IF_I2C_READ						0x31
#define CMD_IF_I2C_IRREGULAR_WRITE			0x34
#define CMD_IF_I2C_GPIO_READ				0x37
#define CMD_IF_I2C_GPIO_WRITE				0x38

#define CMD_IF_SRUN_ENABLE					0x40
#define CMD_IF_SRUN_CHIP_ERASE				0x41
#define CMD_IF_SRUN_STATUS_READ				0x42
#define CMD_IF_SRUN_DATA_WRITE				0x43
#define CMD_IF_SRUN_DATA_READ				0x44
#define CMD_IF_SRUN_COMPLETE				0x45
#define CMD_IF_SRUN_DEVICE					0x46
#define CMD_IF_GET_ONRF_DONE				0x47

#define CMD_QSPI_SPI_INITIALIZE				0x70
#define CMD_QSPI_SPI_RELAY_ONOFF			0x71
#define CMD_QSPI_SPI_FLASH_ERASE_SECTOR		0x72
#define CMD_QSPI_SPI_FLASH_ERASE_BLOCK		0x73
#define CMD_QSPI_SPI_FLASH_ERASE_CHIP		0x74
#define CMD_QSPI_SPI_FLASH_WRITE			0x75
#define CMD_QSPI_SPI_FLASH_READ				0x76
#define CMD_QSPI_SPI_FLASH_STATUS_READ		0x77
#define CMD_QSPI_I2C_INITIALIZE				0x7A
#define CMD_QSPI_I2C_WRITE					0x7B
#define CMD_QSPI_I2C_READ					0x7C
#define CMD_QSPI_I2C_ENABLE					0x7D
#define CMD_QSPI_GPIO_INITIALIZE			0x80
#define CMD_QSPI_GPIO_WRITE_BIT				0x81
#define CMD_QSPI_GPIO_READ_BIT				0x82
#define CMD_QSPI_KEYPAD_INPUT				0x87
#define CMD_QSPI_ARE_YOU_READY				0xC0
#define CMD_QSPI_GET_FW_VERSION				0xFE

#define CMD_CTRL_FUSING_SYSTEM				0xA0
#define CMD_CTRL_POWER_VOLTAGE_SET			0xA5
#define CMD_CTRL_POWER_SEQUENCE_ONOFF		0xA8
#define CMD_CTRL_MEASURE_ITEM_POWER			0xA9
#define CMD_CTRL_MEASURE_ALL_POWER			0xAA
#define CMD_CTRL_BIT_SELECT					0xB0
#define CMD_CTRL_SIGNAL_ONOFF				0xB1
#define CMD_CTRL_PWM_SETTING				0xB2
#define CMD_CTRL_CABLE_OPEN_CHECK			0xB3
#define CMD_CTRL_GPIO_CONTROL				0xB4	// Output만 가능한 I/O
#define CMD_CTRL_GIO_CONTROL				0xB5	// Input/Output Direction 변경 가능한 I/O

#define CMD_CTRL_ARE_YOU_READY				0xC0
#define CMD_CTRL_POWER_SEND_PACKET_BYPASS	0xCF // POWER CAL. BY Pass CMD (21.03.04)

#define CMD_CTRL_TRANSFER_TO_POWER			0xE0

#define CMD_CTRL_FW_DOWNLOAD				0xF0
#define CMD_CTRL_FW_UPLOAD					0xF1
#define CMD_CTRL_FW_COMPLETE				0xF2
#define CMD_CTRL_GOTO_BOOT_SECTION			0xF3
#define CMD_CTRL_GOTO_BOOT_UPLOAD			0xF4
#define CMD_CTRL_BOARD_RESET				0xFD
#define CMD_CTRL_FW_VERSION					0xFE

/////////////////////////////////////////////////////////////////////////////
// DIO Command Packet
/////////////////////////////////////////////////////////////////////////////
#define CMD_DIO_OUTPUT						0x02	// DIO Board Output
#define CMD_DIO_INPUT						0x03	// DIO Board Input
#define CMD_DIO_TIME_OUT					0xFF


/////////////////////////////////////////////////////////////////////////////
// MELSEC 통신 ErrorCode Define
/////////////////////////////////////////////////////////////////////////////
#define MNETG_OK					0
#define MNETG_ERROR_0000H			_T("CMD OK")
#define MNETG_ERROR_0001H			_T("Driver not started.")
#define MNETG_ERROR_0002H			_T("Time-out error.")
#define MNETG_ERROR_0042H			_T("Channel-opened error.")
#define MNETG_ERROR_0044H			_T("Path error.")
#define MNETG_ERROR_0045H			_T("Unsupported function execution error.")
#define MNETG_ERROR_0046H			_T("Station number error.")
#define MNETG_ERROR_0047H			_T("No reception data error (for RECV function).")
#define MNETG_ERROR_004DH			_T("Memory reservation error/resource memory shortage error.")
#define MNETG_ERROR_0055H			_T("SEND/RECV channel number error.")
#define MNETG_ERROR_0064H			_T("Board H/W resource busy.")
#define MNETG_ERROR_0065H			_T("Routing parameter error.")
#define MNETG_ERROR_0066H			_T("Board Driver I/F error. An attempt to send request data to the board driver is failed.")
#define MNETG_ERROR_0067H			_T("Board Driver I/F error. An attempt to receive response data from the board driver is failed.")
#define MNETG_ERROR_0085H			_T("Parameter error. A parameter set on the board is incorrect.")
#define MNETG_ERROR_0085H			_T("Parameter error. A parameter set on the board is incorrect.")
#define MNETG_ERROR_1000H			_T("MELSEC data link library internal error.")
#define MNETG_ERROR_4000H			_T("Error detected by the access target CPU.")
#define MNETG_ERROR_4030H			_T("Device error. The specified device type is invalid.")
#define MNETG_ERROR_4031H			_T("Device error. The specified device number is out of the range.")
#define MNETG_ERROR_4080H			_T("Request data error.")
#define MNETG_ERROR_4A00H			_T("Link-related error.")
#define MNETG_ERROR_4A01H			_T("Link-related error.")
#define MNETG_ERROR_4B02H			_T("The request is not for a CPU module.")
#define MNETG_ERROR_FFFFH			_T("Path error. The specified path is invalid.")
#define MNETG_ERROR_FFFEH			_T("Start device number error.")
#define MNETG_ERROR_FFFDH			_T("Device type error. The specified device type is invalid.")
#define MNETG_ERROR_FFFBH			_T("Size error. The set of start device numberand size is over the device range.")
#define MNETG_ERROR_FFFAH			_T("Number of blocks error.")
#define MNETG_ERROR_FFF8H			_T("Channel number error. The channel number specified with mdOpen function is invalid.")
#define MNETG_ERROR_FFF4H			_T("Block number error. The block number of the specified file register is invalid.")
#define MNETG_ERROR_FFF3H			_T("Write protect error.")
#define MNETG_ERROR_FFF0H			_T("Network number and station number error.")
#define MNETG_ERROR_FFEFH			_T("All station specification and group number specification error.")
#define MNETG_ERROR_FFEEH			_T("Remote command code error.")
#define MNETG_ERROR_FFEDH			_T("SEND/RECV channel number error.")
#define MNETG_ERROR_FFE1H			_T("DLL load error. An attempt to load DLL required to execute the function failed.")
#define MNETG_ERROR_FFE0H			_T("Resource time-out error.")
#define MNETG_ERROR_FFDFH			_T("Incorrect access target error.")
#define MNETG_ERROR_FFDEH			_T("Registry access error.")
#define MNETG_ERROR_FFDBH			_T("Communication initialization setting error.")
#define MNETG_ERROR_FFD6H			_T("Close error. The communication cannot be closed.")
#define MNETG_ERROR_FFD5H			_T("ROM operation error.")
#define MNETG_ERROR_FFC3H			_T("Number of events error.")
#define MNETG_ERROR_FFC2H			_T("Event number error.")
#define MNETG_ERROR_FFC1H			_T("Event number duplicate registration error.")
#define MNETG_ERROR_FFC0H			_T("Timeout time error. The timeout time specified with mdWaitBdEvent function is out of the range.")
#define MNETG_ERROR_FFBFH			_T("Event wait time-out error. An event did not occur within the timeout time.")
#define MNETG_ERROR_FFBEH			_T("Event initialization error.")
#define MNETG_ERROR_FFBDH			_T("No event setting error.")
#define MNETG_ERROR_FFBBH			_T("Unsupported function execution error.")
#define MNETG_ERROR_FFBAH			_T("Event duplication occurrence error.")
#define MNETG_ERROR_FFB9H			_T("Remote device station access error.")
#define MNETG_ERROR_FEFFH			_T("Errors detected in the MELSECNET/H and MELSECNET/10 network system.")
#define MNETG_ERROR_F782H			_T("Transient data target station number error.")
#define MNETG_ERROR_EFFFH			_T("Errors detected in the CC-Link IE Controller network system.")
#define MNETG_ERROR_E218H			_T("Transient data target station number error.")
#define MNETG_ERROR_E208H			_T("Transient data target station number error.")
#define MNETG_ERROR_DFFFH			_T("Errors detected in the CC-Link IE Field network system.")
#define MNETG_ERROR_D25DH			_T("Transient data improper.")
#define MNETG_ERROR_D23BH			_T("Network number error.")
#define MNETG_ERROR_D21EH			_T("Station number error.")
#define MNETG_ERROR_D0A0H			_T("Transient data send response wait time-out error.")
#define MNETG_ERROR_CFFFH			_T("Errors detected in the Ethernet network system.")
#define MNETG_ERROR_BFFFH			_T("Errors detected in the CC-Link system.")
#define MNETG_ERROR_B780H			_T("Module mode setting error.")
#define MNETG_ERROR_B774H			_T("Transient unsupported error.")
#define MNETG_ERROR_9E20H			_T("Processing code error.")
#define MNETG_ERROR_9922H			_T("Reset error.")
#define MNETG_ERROR_9920H			_T("Routing request error on routing function unsupported station.")
#define MNETG_ERROR_9302H			_T("Event wait time-out error.")
#define MNETG_ERROR_9216H			_T("Unsupported block data assurance per station.")
#define MNETG_ERROR_9215H			_T("Link refresh error. Link refresh processing did not operate normally.")
#define MNETG_ERROR_9214H			_T("Incorrect mode setting error. An incorrect mode was specified when setting the mode.")
#define MNETG_ERROR_9213H			_T("System sleep error. Entering sleep mode, hibernation mode, or fast startup was detected.")
#define MNETG_ERROR_9212H			_T("Mode error. A request which cannot be used in the currently set mode was executed.")
#define MNETG_ERROR_9211H			_T("Hardware self-diagnosis error. An error was detected by the hardware self-diagnosis.")
#define MNETG_ERROR_9210H			_T("Hardware self-diagnosis error. An error was detected by the hardware self-diagnosis.")
#define MNETG_ERROR_920AH			_T("Data link disconnected device access error.")
#define MNETG_ERROR_9209H			_T("Abnormal data reception error. An incorrect response data was received.")
#define MNETG_ERROR_9202H			_T("Driver WDT error. Driver WDT error is occurring.")
#define MNETG_ERROR_9032H			_T("Channel busy (dedicated instruction) error.")
#define MNETG_ERROR_9026H			_T("Hardware self-diagnosis error. An error was detected by the hardware self-diagnosis.")
#define MNETG_ERROR_9024H			_T("Hardware self-diagnosis error. An error was detected by the hardware self-diagnosis.")


//----------------------------------------------------------------------------
// LED B/L 점등기 제어 Command

#define	_MIN_									0
#define	_MAX_									1
#define	_USERSET_								2

#define OFF										FALSE
#define ON										TRUE

#define SIG_6BIT	0
#define SIG_8BIT	1
#define SIG_10BIT	2
#define SIG_12BIT	3

/////////////////////////////////////////////////////////////////////////////
// Macro Define
/////////////////////////////////////////////////////////////////////////////
#define round(a) ( int ) ( a + .5 )


#define	WM_UPDATE_SYSTEM_INFO					(WM_USER+102)
#define WM_UPDATE_QUANTITY_INFO					(WM_USER+103)

enum
{
	CONN_MES = 0,
	CONN_EAS,
	CONN_ECS,
	CONN_PG1,
	CONN_PG2,
	CONN_SPI1,
	CONN_SPI2,
	CONN_DIO1,
	CONN_DIO2,
	CONN_MELSEC,
	CONN_MAX
};

#define NORMAL									0x00
#define	OVER_CURRENT							0x01
#define	LOW_CURRENT								0x02

#define SPLIT_MODE								1

#define EQP_OFFLINE								0
#define EQP_INLINE								1

#define	FAST_JUDGE_NONE							0
#define	FAST_JUDGE_OK							1
#define	FAST_JUDGE_NG							2
#define	FAST_JUDGE_MAX							3

#define	GMES_PNF_NONE							0
#define	GMES_PNF_PASS							1
#define	GMES_PNF_FAIL							2
#define	GMES_PNF_MAX							3

#define GOOD_CNT								0
#define BAD_CNT									1

enum
{
	ERROR_CODE_0 = 0,
	ERROR_CODE_1,
	ERROR_CODE_2,
	ERROR_CODE_3,
	ERROR_CODE_4,
	ERROR_CODE_5,
	ERROR_CODE_6,
	ERROR_CODE_7,
	ERROR_CODE_8,
	ERROR_CODE_9,
	ERROR_CODE_10,
	ERROR_CODE_11,
	ERROR_CODE_12,
	ERROR_CODE_13,
	ERROR_CODE_14,
	ERROR_CODE_15,
	ERROR_CODE_16,
	ERROR_CODE_17,
	ERROR_CODE_18,
	ERROR_CODE_19,
	ERROR_CODE_20,
	ERROR_CODE_21,
	ERROR_CODE_22,
	ERROR_CODE_23,
	ERROR_CODE_24,
	ERROR_CODE_25,
	ERROR_CODE_26,
	ERROR_CODE_27,
	ERROR_CODE_28,
	ERROR_CODE_29,
	ERROR_CODE_30,
	ERROR_CODE_31,
	ERROR_CODE_32,
	ERROR_CODE_33,
	ERROR_CODE_34,
	ERROR_CODE_35,
	ERROR_CODE_36,
	ERROR_CODE_37,
	ERROR_CODE_38,
	ERROR_CODE_39,
	ERROR_CODE_40,
	ERROR_CODE_41,
	ERROR_CODE_42,
	ERROR_CODE_43,
	ERROR_CODE_44,
	ERROR_CODE_45,
	ERROR_CODE_46,
	ERROR_CODE_47,
	ERROR_CODE_48,
	ERROR_CODE_49,
	ERROR_CODE_50,
	ERROR_CODE_51,
	ERROR_CODE_52,
	ERROR_CODE_53,
	ERROR_CODE_54,
	ERROR_CODE_55,
	ERROR_CODE_56,
	ERROR_CODE_57,
	ERROR_CODE_58,
	ERROR_CODE_59,
	ERROR_CODE_60,
	ERROR_CODE_61,
	ERROR_CODE_62,
	ERROR_CODE_63,
	ERROR_CODE_64,
	ERROR_CODE_65,
	ERROR_CODE_66,
	ERROR_CODE_67,
	ERROR_CODE_68,
	ERROR_CODE_69,
	ERROR_CODE_70,
	ERROR_CODE_71,
	ERROR_CODE_72,
	ERROR_CODE_73,
	ERROR_CODE_74,
	ERROR_CODE_75,
	ERROR_CODE_76,
	ERROR_CODE_77,
	ERROR_CODE_78,
	ERROR_CODE_79,
	ERROR_CODE_80,
	ERROR_CODE_81,
	ERROR_CODE_82,
	ERROR_CODE_83,
	ERROR_CODE_84,
	ERROR_CODE_85,
	ERROR_CODE_86,
	ERROR_CODE_87,
	ERROR_CODE_88,
	ERROR_CODE_89,
	ERROR_CODE_90,
	ERROR_CODE_91,
	ERROR_CODE_92,
	ERROR_CODE_93,
	ERROR_CODE_94,
	ERROR_CODE_95,
	ERROR_CODE_96,
	ERROR_CODE_97,
	ERROR_CODE_98,
	ERROR_CODE_99,
	ERROR_CODE_2000 = 2000,		// MELSEC ERROR CODE : 2000 ~
	ERROR_CODE_2001,
	ERROR_CODE_2002,
	ERROR_CODE_2003,
	ERROR_CODE_2004,
	ERROR_CODE_2005,
	ERROR_CODE_2006,
	ERROR_CODE_2007,
	ERROR_CODE_2008,
	ERROR_CODE_2009,
	ERROR_CODE_MAX
};

#endif