from usbfunc import *
from time import *
#from win32api import *

def dec2bin(decdata):
    retval=[1,1,1,1,1,1,1,1]
    temp=decdata
    for i in range(1,8):
        q = temp//(2**(8-i))
        temp = temp%(2**(8-i))
        retval[8-i]=q
        retval[0]=temp
    return retval

def bin2dec(bindata):
    retval = 0
    for i in range(1,9):
        retval = retval + bindata[i-1]*(2**(i-1))        
    return retval

def KeyInt(comt=''): 
    k = raw_input('%s Hit any key to continue...'%comt)

def SelectPS8617():
    SelectChipByNameStr('ps8617@PS8617 Demo Board') 

def SelectPS175():
    SelectChipByNameStr('ps175@PS175 Demo Board')

def SelectDebugTool():
    SelectChipByNameStr('debug tool@Parade I2C Debug Tool')

def SelectDP855SourceFPGA():
    SelectChipByNameStr('fpga_core@DP855 Source Board')

        



    

