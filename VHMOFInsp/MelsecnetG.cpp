// CA210Machine.cpp: implementation of the CMeasureMachine class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "MelsecnetG.h"
#include "./MelsecNetG/inc/Mdfunc.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMelsecnetG::CMelsecnetG()
{
	m_mnetPath = -1;
}

CMelsecnetG::~CMelsecnetG()
{

}

long CMelsecnetG::mnetg_getPath()
{
	return m_mnetPath;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Opens a communication line.
//
// Format		ret = mdOpen(chan, mode, path);
//
// Argument		short ret;		//Return value									OUT
//				short chan;		//Channel number of communication line			IN
//				short mode;		//Dummy											IN
//				long* path;		//Opened line path pointer						OUT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CMelsecnetG::mnetg_mdOpen(short channel, short mode)
{
	int ret=0;

	ret = mdOpen(channel, mode, &m_mnetPath);

	return ret;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Closes a communication line.
//
// Format		ret = mdClose(path);
// Argument		short ret;		//Return value									OUT
//				long path;		//Path of channel								IN
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CMelsecnetG::mnetg_mdClose()
{
	int ret=0;

	ret = mdClose(m_mnetPath);

	return ret;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Batch writes devices.
//
// Format		ret = mdSendEx(path, netno, stno, devtyp, devno, size, data);
// Argument		long ret;		//Return value									OUT
//				long path;		//Path of channel								IN
//				long netno;		//Network number								IN
//				long stno;		//Station number								IN
//				long devtyp;	//Device type									IN
//				long devno;		//Start device number							IN
//				long* pWriteByte;//Written byte size							IN/OUT
//				short data[];	//Written data (single-precision integer array)	IN
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CMelsecnetG::mnetg_mdSendEx(LONG devtyp, LONG devno, LONG* pWriteByte, WORD* data)
{
	int ret=0;
	LONG netno, stno;

#if (DEBUG_MAIN_UDP_RECV_OK==1)
	return 0;
#endif

	netno = 0;				/*	network No. 0 fixed			*/
	stno = 255;				/*	station No. 255 fixed			*/
	//	devtyp = 13;				/*	device type "D" fixed		*/ 

	ret = mdSendEx(m_mnetPath, netno, stno, devtyp, devno, pWriteByte, data);

	return ret;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Batch reads devices.
//
// Format		ret = mdReceiveEx(path, netno, stno, devtyp, devno, size, data);
// Argument		long ret;		//Return value									OUT
//				long path;		//Path of channel								IN
//				long netno;		//Network number								IN
//				long stno;		//Station number								IN
//				long devtyp;	//Device type									IN
//				long devno;		//Start device number							IN
//				long* pReadByte;//Read byte size (Must be set Even Size)		IN/OUT
//				short data[];	//Read data (single-precision integer array)	OUT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CMelsecnetG::mnetg_mdReceiveEx(LONG devtyp, LONG devno, LONG* pReadByte, WORD* data)
{
	int ret=0;
	LONG netno, stno;

#if (DEBUG_MAIN_UDP_RECV_OK==1)
	return 0;
#endif

	netno = 0x00;				/*	network No. 0 fixed			*/
	stno = 255;					/*	station No. 255 fixed			*/
//	devtyp = 13;				/*	device type "D" fixed		*/

	ret = mdReceiveEx(m_mnetPath, netno, stno, devtyp, devno, pReadByte, data);

	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

