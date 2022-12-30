#pragma once

#ifndef _GOLBAL_DEFINE_
#define _GOLBAL_DEFINE_


#define CODE_MES_EAS_USE				0
#define CODE_QSPI_USE					0
#define CODE_DIO_BOARD_USE				0
#define CODE_PATTERN_POWER_SET_USE		0
#define CODE_MAIN_UI_FW_VER_UPDATE		0
#define CODE_DFS_SETTING_USE			0


/////////////////////////////////////////////////////////////////////////////Đs
#define PGM_VERSION						_T("1.0.0_R1")
#define DEFAULT_FONT					_T("Tahoma")

/////////////////////////////////////////////////////////////////////////////
#define MLOG_MAX_LENGTH					16*1024

/////////////////////////////////////////////////////////////////////////////
#define DEBUG_TCP_RECEIVE_OK			1
#define DEBUG_TCP_COMM_LOG				0
#define DEBUG_TCP_PACKET_LOG			0
#define	DEBUG_GMES_TEST_SERVER			0
#define DEBUG_PALLET_ARRIVE				0
#define DEBUG_DIO_SKIP					0

/////////////////////////////////////////////////////////////////////////////
#define TCP_MAIN_1_BOARD_IP			_T("192.168.1.15")
#define TCP_MAIN_2_BOARD_IP			_T("192.168.1.16")
#define TCP_MAIN_PORT				50001

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
#define SIG_TYPE_TMDS					0
#define SIG_TYPE_LVDS					1
#define SIG_TYPE_DP						2
#define SIG_TYPE_EDP					3
#define SIG_TYPE_MIPI					4
#define SIG_TYPE_ALPLD					5

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
#define DIO_OUT_RESET	0x0000

#define DIO_OUT_01		(1<<0)
#define DIO_OUT_02		(1<<1)
#define DIO_OUT_03		(1<<2)
#define DIO_OUT_04		(1<<3)
#define DIO_OUT_05		(1<<4)
#define DIO_OUT_06		(1<<5)
#define DIO_OUT_07		(1<<6)
#define DIO_OUT_08		(1<<7)

#define DIO_IN_01		(1<<0)
#define DIO_IN_02		(1<<1)
#define DIO_IN_03		(1<<2)
#define DIO_IN_04		(1<<3)
#define DIO_IN_05		(1<<4)
#define DIO_IN_06		(1<<5)
#define DIO_IN_07		(1<<6)
#define DIO_IN_08		(1<<7)

#define DI_START_READY		DIO_IN_01
#define DI_BCR_READ_DONE	DIO_IN_02
#define DI_PANEL_OUT_OK		DIO_IN_03
#define DI_PANEL_OUT_NG		DIO_IN_04
#define DI_TEST_SWITCH1		DIO_IN_05
#define DI_TEST_SWITCH2		DIO_IN_06

#define DO_TEST_JUDGE_OK	DIO_OUT_01
#define DO_TEST_JUDGE_NG	DIO_OUT_02
#define DO_TEST_TESTING		DIO_OUT_03
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
#define COLOR_DARK_MAGENTA			RGB(125,100,125)
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
// UD Pattern Generator Control Command
/////////////////////////////////////////////////////////////////////////////
#define TARGET_PC								0xA1
#define TARGET_MAIN								0xA2
#define TARGET_IF								0xA3
#define TARGET_GFD250							0xAB

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
// Command Packet
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
#define CMD_CTRL_POWER_VOLTAGE_SET			0xAA//0xA5
#define CMD_CTRL_POWER_SEQUENCE_ONOFF		0xAC//0xA8
#define CMD_CTRL_LG_DISM_SELECT				0xAF
#define CMD_CTRL_BIT_SELECT					0xB0
#define CMD_CTRL_SIGNAL_ONOFF				0xB1
#define CMD_CTRL_PWM_SETTING				0xB2
#define CMD_CTRL_POWER_ONOFF_SET			0xB3//0xA6
#define CMD_CTRL_MEASURE_ITEM_POWER			0xB5//0xA9
#define CMD_CTRL_MEASURE_ALL_POWER			0xBD//0xAA
#define CMD_CTRL_ZONE_SET					0xB7//0xB0
#define CMD_CTRL_SET_LOGICAL_BMP			0xBA
#define	CMD_CTRL_WRITE_BMP					0xBB		//0xD3

#define CMD_CTRL_ARE_YOU_READY				0xC0
#define CMD_CTRL_POWER_SEND_PACKET_BYPASS	0xCF // POWER CAL. BY Pass CMD (21.03.04)


#define CMD_CTRL_FW_DOWNLOAD				0xF0
#define CMD_CTRL_FW_UPLOAD					0xF1
#define CMD_CTRL_FW_COMPLETE				0xF2
#define CMD_CTRL_GOTO_BOOT_SECTION			0xF3
#define CMD_CTRL_GOTO_BOOT_UPLOAD			0xF4
#define CMD_CTRL_BOARD_RESET				0xFD
#define CMD_CTRL_FW_VERSION					0xFE

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


#endif