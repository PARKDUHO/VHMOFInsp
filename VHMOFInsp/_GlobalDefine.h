#pragma once

#ifndef _GOLBAL_DEFINE_
#define _GOLBAL_DEFINE_


#define CODE_QSPI_USE					0
#define CODE_PATTERN_POWER_SET_USE		0
#define CODE_MAIN_UI_FW_VER_UPDATE		0
#define CODE_DFS_SETTING_USE			0


/////////////////////////////////////////////////////////////////////////////Đs
#define PGM_VERSION						_T("1.0.0_R1")
#define DEFAULT_FONT					_T("Tahoma")

/////////////////////////////////////////////////////////////////////////////
#define MLOG_MAX_LENGTH					16*1024

/////////////////////////////////////////////////////////////////////////////
#define DEBUG_TCP_RECEIVE_OK			0
#define	DEBUG_GMES_TEST_SERVER			0
#define DEBUG_TCP_COMM_LOG				1
#define DEBUG_TCP_PACKET_LOG			0
#define DEBUG_PALLET_ARRIVE				0
#define DEBUG_DIO_SKIP					0

/////////////////////////////////////////////////////////////////////////////
#define TCP_MAIN_1_BOARD_IP				_T("192.168.1.10")
#define TCP_MAIN_2_BOARD_IP				_T("192.168.1.11")

#define UDP_DIO_BOARD1_IP				_T("192.168.1.200")
#define UDP_DIO_BOARD2_IP				_T("192.168.1.201")

#define TCP_MAIN_PORT					50001

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
#define MSG_ERROR						0
#define MSG_WARNING						1


#define CH1								0
#define CH2								1
#define MAX_CH							2

/////////////////////////////////////////////////////////////////////////////
//DIO
/////////////////////////////////////////////////////////////////////////////
#define DIN_D1_EMO_SWITCH							(0x01 << 1)
#define DIN_D1_START_SWITCH							(0x01 << 2)
#define DIN_D1_RESET_SWITCH							(0x01 << 3)
#define DIN_D1_MUTTING_SWITCH						(0x01 << 4)
#define DIN_D1_LIGHT_CURTAIN						(0x01 << 5)
#define DIN_D1_LEFT_SAFETY_DOOR						(0x01 << 6)
#define DIN_D1_RIGHT_SAFETY_DOOR					(0x01 << 7)
#define DIN_D1_LEFT_SHUTTER_HOLDING_SENSOR			(0x01 << 8)

#define DIN_D1_RIGHT_SHUTTER_HOLDING_SENSOR			(0x01 << 1)
#define DIN_D1_FAN_IN_ALARM							(0x01 << 2)
#define DIN_D1_FAN_OUT_ALARM						(0x01 << 3)
#define DIN_D1_TEMPATURE_HIGH_ALARM					(0x01 << 4)
#define DIN_D1_MAIN_AIR_DIGITAL_PRESSURE_GAGE		(0x01 << 5)
#define DIN_D1_IONIZER_AIR_DIGITAL_PRESSURE_GAGE	(0x01 << 6)
#define DIN_D1_CYLINDER_DIGITAL_PRESSURE_GAGE		(0x01 << 7)
#define DIN_D1_JIG_DIGITAL_PRESSURE_GAGE			(0x01 << 8)

#define DIN_D1_IONIZER_CLEANSING_ALARM				(0x01 << 1)
#define DIN_D1_IONIZER_HIGH_VOLTAGE_ALARM			(0x01 << 2)
#define DIN_D1_ROBOT_IN_SENSOR_1					(0x01 << 3)
#define DIN_D1_ROBOT_IN_SENSOR_2					(0x01 << 4)
#define DIN_D1_FRONT_SHUTTER_LEFT_BACKWARD			(0x01 << 5)
#define DIN_D1_FRONT_SHUTTER_LEFT_FORWARD			(0x01 << 6)
#define DIN_D1_FRONT_SHUTTER_RIGHT_BACKWARD			(0x01 << 7)
#define DIN_D1_FRONT_SHUTTER_RIGHT_FORWARD			(0x01 << 8)

#define DIN_D1_REAR_SHUTTER_LEFT_BACKWARD			(0x01 << 1)
#define DIN_D1_REAR_SHUTTER_LEFT_FORWARD			(0x01 << 2)
#define DIN_D1_REAR_SHUTTER_RIGHT_BACKWARD			(0x01 << 3)
#define DIN_D1_REAR_SHUTTER_RIGHT_FORWARD			(0x01 << 4)
#define DIN_D1_JIG_DOWN_1_SENSOR					(0x01 << 5)
#define DIN_D1_JIG_UP_1_SENSOR						(0x01 << 6)
#define DIN_D1_JIG_DOWN_2_SENSOR					(0x01 << 7)
#define DIN_D1_JIG_UP_2_SENSOR						(0x01 << 8)

#define DIN_D1_JIG_DOWN_3_SENSOR					(0x01 << 1)
#define DIN_D1_JIG_UP_3_SENSOR						(0x01 << 2)
#define DIN_D1_SPARE1								(0x01 << 3)
#define DIN_D1_SPARE2								(0x01 << 4)
#define DIN_D1_SPARE3								(0x01 << 5)
#define DIN_D1_SPARE4								(0x01 << 6)
#define DIN_D1_SPARE5								(0x01 << 7)
#define DIN_D1_SPARE6								(0x01 << 8)

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
#define	DOUT_D1_IONIZER_BLOW						0x010000
#define	DOUT_D1_IONIZER_ON_OFF						0x020000
#define	DOUT_D1_LED_ON_OFF							0x040000
#define	DOUT_D1_ROBOT_IN_SENSOR_LAMP				0x080000		// 사용여부 확인 필요
#define	DOUT_D1_SPARE1								0x100000
#define	DOUT_D1_SPARE2								0x200000
#define	DOUT_D1_SPARE3								0x400000
#define	DOUT_D1_SPARE4								0x800000

////////////////////////////////////////////////////////////////////////////////
#define DIN_D2_JIG_SENSOR							(0x01 << 1)
#define DIN_D2_JIG_DOOR_SENSOR						(0x01 << 2)
#define DIN_D2_TILTING_60_SENSOR					(0x01 << 3)
#define DIN_D2_TILTING_70_SENSOR					(0x01 << 4)
#define DIN_D2_CH1_JIG_TRAY_IN_SENSOR				(0x01 << 5)
#define DIN_D2_CH2_JIG_TRAY_IN_SENSOR				(0x01 << 6)
#define DIN_D2_CH1_TRAY_UNCLAMP1					(0x01 << 7)
#define DIN_D2_CH1_TRAY_UNCLAMP2					(0x01 << 8)

#define DIN_D2_CH1_TRAY_UNCLAMP3					(0x01 << 1)
#define DIN_D2_CH1_TRAY_UNCLAMP4					(0x01 << 2)
#define DIN_D2_CH1_TRAY_UNCLAMP5					(0x01 << 3)
#define DIN_D2_CH1_TRAY_UNCLAMP6					(0x01 << 4)
#define DIN_D2_CH2_TRAY_UNCLAMP1					(0x01 << 5)
#define DIN_D2_CH2_TRAY_UNCLAMP2					(0x01 << 6)
#define DIN_D2_CH2_TRAY_UNCLAMP3					(0x01 << 7)
#define DIN_D2_CH2_TRAY_UNCLAMP4					(0x01 << 8)

#define DIN_D2_CH2_TRAY_UNCLAMP5					(0x01 << 1)
#define DIN_D2_CH2_TRAY_UNCLAMP6					(0x01 << 2)
#define DIN_D2_SPARE1								(0x01 << 3)
#define DIN_D2_SPARE2								(0x01 << 4)
#define DIN_D2_SPARE3								(0x01 << 5)
#define DIN_D2_SPARE4								(0x01 << 6)
#define DIN_D2_SPARE5								(0x01 << 7)
#define DIN_D2_SPARE6								(0x01 << 8)

#define DIN_D2_CH1_PENDANT_AUTO_MANUAL				(0x01 << 1)
#define DIN_D2_CH1_PENDANT_BACK						(0x01 << 2)
#define DIN_D2_CH1_PENDANT_NEXT						(0x01 << 3)
#define DIN_D2_CH1_PENDANT_REPEAT					(0x01 << 4)
#define DIN_D2_CH1_PENDANT_RESET					(0x01 << 5)
#define DIN_D2_CH1_PENDANT_UP						(0x01 << 6)
#define DIN_D2_CH1_PENDANT_DOWN						(0x01 << 7)
#define DIN_D2_CH1_PENDANT_SEND						(0x01 << 8)

#define DIN_D2_CH2_PENDANT_AUTO_MANUAL				(0x01 << 1)
#define DIN_D2_CH2_PENDANT_BACK						(0x01 << 2)
#define DIN_D2_CH2_PENDANT_NEXT						(0x01 << 3)
#define DIN_D2_CH2_PENDANT_REPEAT					(0x01 << 4)
#define DIN_D2_CH2_PENDANT_RESET					(0x01 << 5)
#define DIN_D2_CH2_PENDANT_UP						(0x01 << 6)
#define DIN_D2_CH2_PENDANT_DOWN						(0x01 << 7)
#define DIN_D2_CH2_PENDANT_SEND						(0x01 << 8)

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
#define	DOUT_D2_SPARE1								0x001000
#define	DOUT_D2_SPARE2								0x002000
#define	DOUT_D2_SPARE3								0x004000
#define	DOUT_D2_SPARE4								0x008000
#define	DOUT_D2_SPARE5								0x010000
#define	DOUT_D2_SPARE6								0x020000
#define	DOUT_D2_SPARE7								0x040000
#define	DOUT_D2_SPARE8								0x080000
#define	DOUT_D2_SPARE9								0x100000
#define	DOUT_D2_SPARE10								0x200000
#define	DOUT_D2_SPARE11								0x400000
#define	DOUT_D2_SPARE12								0x800000




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

#define CMD_CTRL_ARE_YOU_READY				0xC0
#define CMD_CTRL_POWER_SEND_PACKET_BYPASS	0xCF // POWER CAL. BY Pass CMD (21.03.04)


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

#define SEQ_MAX_ITEM 4

// 0xBD : CTRL_Measure_All_Power
//VCC,ICC,VDD,IDD,VBL,IBL,VGH,IGH,VGL,IGL,VCC_FB,VBL_FB,VLED_FB,THERMISTOR
enum
{
	PINFO_VCC =0,
	PINFO_ICC,
	PINFO_VDD,
	PINFO_IDD,
	PINFO_VBL,
	PINFO_IBL,
	PINFO_VGH,
	PINFO_IGH,
	PINFO_VGL,
	PINFO_IGL,
	PINFO_VCC_FB,
	PINFO_VBL_FB,
	PINFO_VLED_FB,
	PINFO_THERMISTOR,
	PINFO_ERR_RESULT,
	PINFO_ERR_NAME,
	PINFO_ERR_VALUE
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
	ERROR_CODE_MAX
};

#endif