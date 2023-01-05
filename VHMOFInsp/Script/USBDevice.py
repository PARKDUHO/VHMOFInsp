from ctypes import *
import platform
import os, sys

class USBDevice:
    devName = "Ezusb-0"
    devNum = -1
    usbCmd = 0xa1
    SlaveAddr = 0x51
    addrSize = 1
    BurstMode = 1
    START_CONDITION = 0x01
    STOP_CONDITION	= 0x02
    WRITE_BYTES		= 0x03
    READ_BYTES		= 0x05
    WAIT_EEPROM     = 0x06
    
    def __init__(self, devName="Ezusb-0", usbCmd = 0xa2, SlaveAddr = 0x51, addrSize = 1, BurstMode = 1):
        self.devName = devName
        self.usbCmd = usbCmd
        self.SlaveAddr = SlaveAddr
        self.addrSize = addrSize
        self.BurstMode = BurstMode
#       self.GetDeviceDescriptor = windll.LoadLibrary("USBUtil.dll").GetDeviceDescriptor
        self.curPath = (os.path.dirname(os.path.realpath(sys.argv[0]))) + "/"

        if devName == "":
            self.devNum = 0
        else:
            li = devName.split('-')
            if len(li) < 2: return
            if li[0].lower() == "ezusb": self.devNum = -1
            else: self.devNum = int(li[1])

        if self.devNum >= 0:
            if self.__is_64bit_python():
                self.func = windll.LoadLibrary(self.curPath + "CyUsbApi64.dll").SendVendorRequest
                self.FindDevice = windll.LoadLibrary(self.curPath + "CyUsbApi64.dll").FindDevice
                self.BulkReadEP = windll.LoadLibrary(self.curPath + "CyUsbApi64.dll").BulkReadEP
                self.BulkWriteEP = windll.LoadLibrary(self.curPath + "CyUsbApi64.dll").BulkWriteEP
                self.BeginXferReadThread = windll.LoadLibrary(self.curPath + "CyUsbApi64.dll").BeginXferReadThread
                self.EndXferReadThread = windll.LoadLibrary(self.curPath + "CyUsbApi64.dll").EndXferReadThread
                self.ReadBuffer = windll.LoadLibrary(self.curPath + "CyUsbApi64.dll").ReadBuffer
                self.CRC_Check = windll.LoadLibrary(self.curPath + "CyUsbApi64.dll").CRC_Check
                self._GetDeviceDescriptor = windll.LoadLibrary(self.curPath + "CyUsbApi64.dll").GetDeviceDescriptor
                self.DownloadHex = windll.LoadLibrary(self.curPath + "CyUsbApi64.dll").DownloadHex
            else:
                self.func = windll.LoadLibrary(self.curPath + "CyUsbApi32.dll").SendVendorRequest
                self.FindDevice = windll.LoadLibrary(self.curPath + "CyUsbApi32.dll").FindDevice
                self.BulkReadEP = windll.LoadLibrary(self.curPath + "CyUsbApi32.dll").BulkReadEP
                self.BulkWriteEP = windll.LoadLibrary(self.curPath + "CyUsbApi32.dll").BulkWriteEP
                self.BeginXferReadThread = windll.LoadLibrary(self.curPath + "CyUsbApi32.dll").BeginXferReadThread
                self.EndXferReadThread = windll.LoadLibrary(self.curPath + "CyUsbApi32.dll").EndXferReadThread
                self.ReadBuffer = windll.LoadLibrary(self.curPath + "CyUsbApi32.dll").ReadBuffer
                self.CRC_Check = windll.LoadLibrary(self.curPath + "CyUsbApi32.dll").CRC_Check
                self._GetDeviceDescriptor = windll.LoadLibrary(self.curPath + "CyUsbApi32.dll").GetDeviceDescriptor
                self.DownloadHex = windll.LoadLibrary(self.curPath + "CyUsbApi32.dll").DownloadHex

        else:
            self.func = windll.LoadLibrary(self.curPath + "USBUtil.dll").SendVendorRequest
            self._GetDeviceDescriptor = windll.LoadLibrary(self.curPath + "USBUtil.dll").GetDeviceDescriptor

#           self.GetDeviceDescriptor = windll.LoadLibrary("CyUsbApi.dll").GetDeviceDescriptor

    def ReNUM (self):
        oldCmd = self.usbCmd
        self.usbCmd = 0xa8
        self.IICRead( 0, 0, 0)
        self.usbCmd = oldCmd

    def FindBoards(self):
        li = []
        did_li = []
        for i in range(0, 8):
            devName = "Cyusb-%d" %i
            board = USBDevice(devName, 0xa2, 0x51, 2)
            buf = create_string_buffer(16, 16)
            board.GetDeviceDescriptor(len(buf), buf)
	    
            
            iVendor = ord(buf[9]) * 256 + ord(buf[8])
            iDevice = ord(buf[11]) * 256 + ord(buf[10])
            #print devName
            #print ('Cyusb-%d :%02x %02x' %(i, iVendor, iDevice))
            if iVendor == 0x4b4 or iVendor == 0x512:
                if iDevice == 0x82:
                    board.DownloadHex(i, b"Vend_Ax.hex")
                    iDevice = ord(buf[13]) * 256 + ord(buf[12])
                elif iDevice == 0x1003:
                    board.DownloadHex(i, b"BulkGeneral.hex")
                    iDevice = ord(buf[13]) * 256 + ord(buf[12])
                elif iDevice == 0x1004:
                    board.WritePortB(0x0f0f)
                    board.IICRead(0, 8, buf)
                    #for k in range(8): print("%02x " %ord(buf[k]), end="")
                    iDevice = ord(buf[6]) * 256 + ord(buf[5])
                li.append(devName)
                did_li.append(iDevice)

		print li ##test

        return li, did_li

    def EnableSlaveFIFO (self, bEnable = True):
        if bEnable: val = 0x03
        else: val = 0x00
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xad), c_int(0), \
                c_int(val), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)
        else:
            self.func(c_buffer(self.devName), c_int(0xad), c_int(0), \
                c_int(val), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)

    
    def  IICRead(self, offset, length, pbuf):
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(self.usbCmd), c_int(self.SlaveAddr), \
                c_int(offset), c_int(self.addrSize), c_int(self.BurstMode), c_int(1), \
                c_int(length), pbuf)
        else:
            self.func(c_buffer(self.devName), c_int(self.usbCmd), c_int(self.SlaveAddr), \
                c_int(offset), c_int(self.addrSize), c_int(self.BurstMode), c_int(1), \
                c_int(length), pbuf)


    def IICWrite(self, offset, length, pbuf):
        #func = windll.LoadLibrary("USBUtil.dll").SendVendorRequest
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(self.usbCmd), c_int(self.SlaveAddr), \
                c_int(offset), c_int(self.addrSize), c_int(self.BurstMode), c_int(0), \
                c_int(length), pbuf)
        else:
            self.func(c_buffer(self.devName), c_int(self.usbCmd), c_int(self.SlaveAddr), \
                c_int(offset), c_int(self.addrSize), c_int(self.BurstMode), c_int(0), \
                c_int(length), pbuf)

    
    def SetFastMode(self, bFast = 1):
        oldCmd = self.usbCmd
        if bFast:
            self.usbCmd = 0xab
        else:
            self.usbCmd = 0xaa
        self.IICRead( 0, 0, 0)
        self.usbCmd = oldCmd

    def GetDeviceDescriptor (self, length, pBuf):
        if self.devNum < 0:
            #func = windll.LoadLibrary("USBUtil.dll").GetDeviceDescriptor
            self._GetDeviceDescriptor((self.devName), c_int(length), pBuf)
        else:
            #func = windll.LoadLibrary("CyUsbApi.dll").GetDeviceDescriptor
            self._GetDeviceDescriptor(c_int(self.devNum), c_int(length), pBuf)


    def ReadPortA (self):
        buf = create_string_buffer(2, 2) 
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xa9), c_int(0), \
            c_int(0), c_int(0), c_int(0), c_int(1), \
            c_int(2), buf)
        else:
            self.func(c_buffer(self.devName), c_int(0xa9), c_int(0), \
            c_int(0), c_int(0), c_int(0), c_int(1), \
            c_int(2), buf)
        return "0x%02x%02x" %(ord(buf[1]), ord(buf[0]))
    
    def WritePortA (self, value):
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xa9), c_int(0), \
                c_int(value), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)
        else:
            self.func(c_buffer(self.devName), c_int(0xa9), c_int(0), \
                c_int(value), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)
    
    def ReadPortB (self):
        buf = create_string_buffer(2, 2)        
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xa9), c_int(1), \
                c_int(0), c_int(0), c_int(0), c_int(1), \
                c_int(2), buf)
        else:
            self.func(c_buffer(self.devName), c_int(0xa9), c_int(1), \
                c_int(0), c_int(0), c_int(0), c_int(1), \
                c_int(2), buf)
        return "0x%02x%02x" %(ord(buf[1]), ord(buf[0]))
    
    def WritePortB (self, value):
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xa9), c_int(1), \
                c_int(value), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)
        else:
            self.func(c_buffer(self.devName), c_int(0xa9), c_int(1), \
                c_int(value), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)
    
    def ReadPortC (self):
        buf = create_string_buffer(2, 2)        
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xa9), c_int(2), \
                c_int(0), c_int(0), c_int(0), c_int(1), \
                c_int(2), buf)
        else:
            self.func(c_buffer(self.devName), c_int(0xa9), c_int(2), \
                c_int(0), c_int(0), c_int(0), c_int(1), \
                c_int(2), buf)
        return "0x%02x%02x" %(ord(buf[1]), ord(buf[0]))
    
    def WritePortC (self, value):
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xa9), c_int(2), \
                c_int(value), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)
        else:
            self.func(c_buffer(self.devName), c_int(0xa9), c_int(2), \
                c_int(value), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)

    def ReadPortD (self):
        buf = create_string_buffer(2, 2)        
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xa9), c_int(3), \
                c_int(0), c_int(0), c_int(0), c_int(1), \
                c_int(2), buf)
        else:
            self.func(c_buffer(self.devName), c_int(0xa9), c_int(3), \
                c_int(0), c_int(0), c_int(0), c_int(1), \
                c_int(2), buf)
        return "0x%02x%02x" %(ord(buf[1]), ord(buf[0]))
    
    def WritePortD (self, value):
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xa9), c_int(3), \
                c_int(value), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)
        else:
            self.func(c_buffer(self.devName), c_int(0xa9), c_int(3), \
                c_int(value), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)
    
    def ReadPortE (self):
        buf = create_string_buffer(2, 2)        
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xa9), c_int(4), \
                c_int(0), c_int(0), c_int(0), c_int(1), \
                c_int(2), buf)
        else:
            self.func(c_buffer(self.devName), c_int(0xa9), c_int(4), \
                c_int(0), c_int(0), c_int(0), c_int(1), \
                c_int(2), buf)
        return "0x%02x%02x" %(ord(buf[1]), ord(buf[0]))
    
    def WritePortE (self, value):
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xa9), c_int(4), \
                c_int(value), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)
        else:
            self.func(c_buffer(self.devName), c_int(0xa9), c_int(4), \
                c_int(value), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)

    def SetStartCondition (self):
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xa3), c_int(self.START_CONDITION), \
                c_int(0), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)
        else:
            self.func(c_buffer(self.devName), c_int(0xa3), c_int(self.START_CONDITION), \
                c_int(0), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)

    def SetStopCondition (self):
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xa3), c_int(self.STOP_CONDITION), \
                c_int(0), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)
        else:
            self.func(c_buffer(self.devName), c_int(0xa3), c_int(self.STOP_CONDITION), \
                c_int(0), c_int(0), c_int(0), c_int(0), \
                c_int(0), 0)

    def WriteBytes (self, length, pbuf):
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xa3), c_int(self.WRITE_BYTES), \
                c_int(0), c_int(0), c_int(0), c_int(0), \
                c_int(length), pbuf)
        else:
            self.func(c_buffer(self.devName), c_int(0xa3), c_int(self.WRITE_BYTES), \
                c_int(0), c_int(0), c_int(0), c_int(0), \
                c_int(length), pbuf)

    def ReadBytes (self, length, pbuf):
        if self.devNum >= 0:
            buf = create_string_buffer(1, 1)        
            self.func(c_int(self.devNum), c_int(0xa3), c_int(self.READ_BYTES), \
                c_int(0), c_int(0), c_int(0), c_int(1), \
                c_int(length), pbuf)
        else:
            buf = create_string_buffer(1, 1)        
            self.func(c_buffer(self.devName), c_int(0xa3), c_int(self.READ_BYTES), \
                c_int(0), c_int(0), c_int(0), c_int(1), \
                c_int(length), pbuf)
        return "0x%02x" %(ord(pbuf[0]))

    def WaitForEEPRomWrite (self):
        buf = create_string_buffer(1, 1)        
        if self.devNum >= 0:
            self.func(c_int(self.devNum), c_int(0xa3), c_int(self.WAIT_EEPROM), \
             c_int(self.SlaveAddr), c_int(0), c_int(0), c_int(1), \
             c_int(1), buf)
        else:
            self.func(c_buffer(self.devName), c_int(0xa3), c_int(self.WAIT_EEPROM), \
             c_int(self.SlaveAddr), c_int(0), c_int(0), c_int(1), \
             c_int(1), buf)
        return ord(buf[0])

    def __is_64bit_python(self):
        if platform.architecture()[0] == "64bit": return True
        else: return False

