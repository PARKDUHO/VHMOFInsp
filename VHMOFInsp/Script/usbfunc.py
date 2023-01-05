#oscar.feng@paradetech.com
from ctypes import *
from string import *
from time import *
from ConfigParser import *
from USBDevice import *


def FindChip (gChipList, gChipDict, BoardNo):
    global gPcbCfg 
    ChipID = 0
    li, did_li = USBDevice("Cyusb-0").FindBoards()
    li=[li[BoardNo]]
    did_li=[did_li[BoardNo]]
    for i in range(0, len(li)):
        buf = create_string_buffer(16, 16)
        UsbDevName = li[i]
        iDevice = did_li[i]
        segname = "%04x" %iDevice
        PcbName = gPcbCfg.get(segname, "PCB name")
        #print PcbName
        DevList = gPcbCfg.items(PcbName)
        #print DevList
        for Device in DevList:
            if Device[0].count('config') or Device[0].count('saddr'):
                continue
            
                print '%s - %s' %(UsbDevName, PcbName)
                print '    ID %d: Chip Name: %s, 4052 Bus NO. 0x%04x\n' %(ChipID, Device[0], atoi(Device[1], 16))
            
            ChipPara = (USBDevice(UsbDevName, 0xa2, 0x08), atoi(Device[1], 16))
            #Add to list
            gChipList.append(ChipPara)
            #Add to Chip Dictionary
            ChipString = Device[0] + '@' + PcbName 
            gChipDict.update({ChipString : ChipID})
            ChipID += 1
    return


def SelectChipById(ID):
    global gCurChipID
    gCurChipID = ID
    ChipPara = gChipList[gCurChipID]
    #Select corresponding 4052 bus number
    ChipPara[0].WritePortB(ChipPara[1])

def ReadReg_2 (slaveAddr, offset, printen = 0):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID]
    buf = create_string_buffer(1, 1)
    ChipPara[0].addrSize = 2
    ChipPara[0].SlaveAddr = slaveAddr >> 1
    ChipPara[0].IICRead(offset, 1, buf)
    RetVal = ord(buf[0])
    ChipPara[0].addrSize = 1
    return RetVal

def WriteReg_2 (slaveAddr, offset, data):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID]
    ChipPara[0].addrSize = 2
    ChipPara[0].SlaveAddr = slaveAddr >> 1
    ChipPara[0].IICWrite(offset, 1, chr(data))
    ChipPara[0].AddrSize = 1

def ReadReg (slaveAddr, offset, printen = 0):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID]
    buf = create_string_buffer(1, 1)
    ChipPara[0].SlaveAddr = slaveAddr >> 1
    ChipPara[0].IICRead(offset, 1, buf)
    RetVal = ord(buf[0])
    return RetVal


def WriteReg (slaveAddr, offset, data):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID]
    ChipPara[0].SlaveAddr = slaveAddr >> 1
    ChipPara[0].IICWrite(offset, 1, chr(data))

def ReadWord (slaveAddr, offset):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID]
    RetVal = 0
    buf = create_string_buffer(2, 2)    
    ChipPara[0].SlaveAddr = slaveAddr >> 1
    ChipPara[0].IICRead(offset, 2, buf)
    RetVal = ord(buf[0]) + ord(buf[1])*256
    return RetVal

def BurstWrite(slaveaddr,offset,length, databuf):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID]
    buf = create_string_buffer(length, length)
    for i in range(length):
      buf[i] = chr(databuf[i])
    ChipPara[0].BurstMode = 1
    ChipPara[0].SlaveAddr = slaveaddr >> 1
    ChipPara[0].IICWrite(offset, length, buf)
    sleep(0.001)

def WriteWord (slaveAddr, offset, data):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID]
    buf = create_string_buffer(2, 2)
    buf[0] = chr(data%256)
    buf[1] = chr(data//256)
    ChipPara[0].SlaveAddr = slaveAddr >> 1
    ChipPara[0].IICWrite(offset, 2, buf)
    
def BurstRead(slaveaddr,offset,length):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID]
    BurstRead = []
    buf = create_string_buffer(length,length)
    ChipPara[0].BurstMode = 1
    ChipPara[0].SlaveAddr = slaveaddr >> 1
    ChipPara[0].IICRead(offset, length, buf)
    for i in range(0,length):
        val = ord(buf[i])
        BurstRead.append(val)
    return BurstRead

def BurstReadSeg(segaddr,segdata,slaveaddr,offset,length):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID]
    BurstRead = []
    buf = create_string_buffer(length,length)
    ChipPara[0].SetStartCondition()
    ChipPara[0].WriteBytes(1, chr(segaddr))
    ChipPara[0].WriteBytes(1, chr(segdata))
    ChipPara[0].SetStartCondition()
    ChipPara[0].WriteBytes(1, chr(slaveaddr))
    ChipPara[0].WriteBytes(1, chr(offset))
    ChipPara[0].SetStartCondition()
    ChipPara[0].WriteBytes(1, chr(slaveaddr+1))
    ChipPara[0].ReadBytes(length,buf)
    for i in range(0,length):
        val = ord(buf[i])
        BurstRead.append(val)
    return BurstRead

def BurstShortRead(slaveaddr,length):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID]
    ifodd = slaveaddr%2
    if ifodd != 1:
        slaveaddr = slaveaddr + 1
    BurstRead = []
    buf = create_string_buffer(length,length)
    ChipPara[0].SetStartCondition()
    ChipPara[0].WriteBytes(1, chr(slaveaddr))
    ChipPara[0].ReadBytes(length,buf)
    for i in range(0,length):
        val = ord(buf[i])
        BurstRead.append(val)
    return BurstRead

def WritePortB(val):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID]   
    ChipPara[0].WritePortB(val)

def WritePortA (val):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID]   
    ChipPara[0].WritePortA(val)


def EnableSlaveFIFO (bEnable = True,nRD = 1):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID]   
    if bEnable:
        if(nRD == 1): val = 0x0808
        else: val = 0x0908
        ChipPara[0].WritePortA(val)
    else: ChipPara[0].WritePortA(0x0000)
    ChipPara[0].EnableSlaveFIFO(bEnable)


def BulkReadEP(length, buf, timeout=3000):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID] 
    cnt = ChipPara[0].BulkReadEP(ChipPara[0].devNum, 3, length, buf, timeout)
    return cnt


def BulkWriteEP(length, buf, timeout=3000):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID] 
    cnt = ChipPara[0].BulkWriteEP(ChipPara[0].devNum, 1, length, buf, timeout)
    ##cnt = usbDev.BulkWriteEP(usbDev.devNum, 1, length, buf)
    return cnt


def CRC_Check(bmpLength, buf):
    global gCurChipID
    global gChipList
    #Get USB device instance
    ChipPara = gChipList[gCurChipID] 
    val = ChipPara[0].CRC_Check(bmpLength, buf)
    return val
    
    
def PrtListHex(val,fl=0):
    length = len(val)
    for i in range(0,length):
        if fl==0:
            print '%02X' %(val[i]) ,
        else:
            if (i+1)%fl == 0:
                print '%02X' %(val[i])
            else:   
                print '%02X' %(val[i]) ,
    print ''
    return

def SelectChipByNameStr(NameStr):
    global gCurChipID
    global gChipDict
    if not gChipDict.has_key(NameStr):
        print "Error! No such chip found(%s). Please check Name String." %NameStr
        return False
    gCurChipID = gChipDict[NameStr]
    ChipPara = gChipList[gCurChipID]
    #print gChipDict
    #print ChipPara[0]
    #Select corresponding 4052 bus number
    ChipPara[0].WritePortB(ChipPara[1])


def UsbFuncInit(BoardNo):
    global gCurChipID
    global gChipList
    global gChipDict
    global gPcbCfg

    ## add 2022/11/24 to avoid gChipList appending more times
    gCurChipID = 0
    gChipList = []
    gChipDict = {}
    #Read pcb config from configuration file.
    #Please make sure the pcblist.ini file does exist in the same directory
    gPcbCfg = ConfigParser()
    gPcbCfg.read("pcblist.ini")

    #Creat Chip list and Chip name searching dictionary
    FindChip(gChipList, gChipDict, BoardNo)

#Current Selected Chip
gCurChipID = 0
#Chip list which store {USB class instance, 4052 bus number}
gChipList = []
#Chip unique name string dictionary
gChipDict = {}
#
gPcbCfg = []

