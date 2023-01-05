from time import *
from usbfunc import *
from subfunc import *
from ctypes import *
import sys

########################################################
##
##  IMPORTANT:
##  This script MUST work with FPGA image version v1028 and later
##  Training OK is needed before run this script
##
########################################################


##UsbFuncInit()
##raw_input("")
##DP501 initial and train
##DP501_Initial()
##SelectGRP_E()
##SelectTC2510SourceFPGA()
##SelectDP825SourceFPGA()

page0 = 0x10
page2 = 0x14
page4 = 0x18
page5 = 0x1a


##actual VTOTAL is REG_VTOTAL(page0, offset 0x16 and 0x17) plus apt_rr_line
##24 bits
##should be config via GUI
apt_rr_line = 1000


##frame rate
##120Hz, 80Hz, 60Hz, 48Hz, 40Hz, 35Hz, 30Hz, 24Hz, 1Hz
##should be config via GUI
##apt_framerate = 60


##if this bit is 1, "apt_rr_line" use the direct value(script or GUI)
##else "apt_rr_line" use the value calculate by "apt_framerate"
##should be config via GUI
apt_manual_en = 0
display_old_from = 0


#################################configurate bist for dp501#####################

error_set = 0   ##indicate if setting is correct or not (1 not correct 0 correct)

def APT_Enable():
    WriteReg(page5, 0x09, 0x01)
    print "APT enable\n\n\n"

def APT_Disable():
    WriteReg(page5, 0x09, 0x00)
    print "APT done and disable"


def CalVclkFreq():
    M = ReadReg(page2, 0x17)
    N = ReadReg(page2, 0x18) & 0x7f
    vclk = 108.0 * M / N
##    print "vclk frequency is %.2fMhz" % (vclk)
    return vclk

def CalFrameRate(vclk):
    htotal = (ReadReg(page0, 0x11)<<8) + ReadReg(page0, 0x10)
    vtotal = (ReadReg(page0, 0x17)<<8) + ReadReg(page0, 0x16)
    frame_rate = vclk*1000000/htotal/vtotal
    print "Initial frame rate is %d" %(frame_rate)
    return frame_rate


    
def CalAPT_RR_Line(target_framerate, current_framerate):
    global error_set
    vtotal = (ReadReg(page0, 0x17)<<8) + ReadReg(page0, 0x16)
    vheight = (ReadReg(page0, 0x1b)<<8) + ReadReg(page0, 0x1a)
    vstart = (ReadReg(page0, 0x19)<<8) + ReadReg(page0, 0x18)
    target_vtotal = (current_framerate / target_framerate) * vtotal
    if(target_vtotal < vheight + vstart):
        error_set = 1
        print "Error,target VTOTAL is less than VHEIGHT plus VSTART"
    else:
        error_set = 0
        rr_line = int(target_vtotal - vtotal)
##        print "APT line is %d" %(rr_line)
        return rr_line



def WriteAPT_RR_Line(target_rr_line):
    value = ReadReg(page0, 0xa5) & 0xbf
    WriteReg(page0, 0xa5, value)
    WriteReg(page5, 0x05, target_rr_line&0xff)
    WriteReg(page5, 0x06, (target_rr_line>>8)&0xff)
    WriteReg(page5, 0x07, (target_rr_line>>16)&0xff)
    value = value | 0x40
    WriteReg(page0, 0xa5, value)


def APT_INIT(target_rr_line, target_framerate):
    if(apt_manual_en == 0):
        vclk = CalVclkFreq()
        current_framerate = CalFrameRate(vclk)
        rr_line = CalAPT_RR_Line(target_framerate, current_framerate)
        if(error_set == 0):
            WriteAPT_RR_Line(rr_line)
            print "Target frame rate is %d" %(target_framerate)
            print "APT line is %d" %(rr_line)
    else:
        vtotal = (ReadReg(page0, 0x17)<<8) + ReadReg(page0, 0x16)
        vclk = CalVclkFreq()
        current_framerate = CalFrameRate(vclk)
        target_framerate_calc = 1.0 * current_framerate * vtotal /(vtotal + target_rr_line)
        print "Target frame rate is %d" %(target_framerate_calc)
        WriteAPT_RR_Line(target_rr_line)

def Read_Image_Num():
    WriteReg(page4,0xff,1)     #sub page 1
    value = ReadReg(page4, 0x0)
    return value


def Display_Image(n):
    WriteReg(0x18,0xff,0)     #sub page 0
    WriteReg(0x18,0x20,0x00)  #Not IMG_LDDONE, Busy

    WriteReg(0x18,0xff,1)     #sub page 1
    
    WriteReg(0x18, 0x30, n)   ##Index

    if(n == 0):
        addr_7_0 = 0
        addr_15_8 = 0
        addr_23_16 = 0
        addr_31_24 = 0
    else:
        addr_7_0 = ReadReg(0x18, 0x40)   ##Read Image Address
        addr_15_8 = ReadReg(0x18, 0x41)
        addr_23_16 = ReadReg(0x18, 0x42)
        addr_31_24 = ReadReg(0x18, 0x43)

    WriteReg(0x18, 0x30, 0)   ##Index 0

    WriteReg(0x18, 0x40, addr_7_0)   ##Write Image Address
    WriteReg(0x18, 0x41, addr_15_8)
    WriteReg(0x18, 0x42, addr_23_16)
    WriteReg(0x18, 0x43, addr_31_24)

    WriteReg(0x18, 0x0, 0)    ##Current Display Count

    WriteReg(0x18,0xff,0)     #sub page 0
    WriteReg(0x18,0x20,0x80)  #IMG_LDDONE
    


##"pattern_index" indicate which pattern, for freerun, 0~31  and for MEM  0~13
##"display_from_ddr_en"  = 1, choose pattern from external memory, images should be downloaded into memory
## before start this script, images stored in SD and auto copy to memory after power-up/reset is recommended.
##"display_from_ddr_en"  = 0, choose pattern from freerun

def SelectPattern(pattern_index, display_from_ddr_en):
    if(display_from_ddr_en):
        if(pattern_index > 13):
            print "Please input a correct index which is 0~13"
            sys.exit(1)
        else:
            Display_Image(pattern_index)
            value = ReadReg(page0, 0xa5) | 0x10
            WriteReg(page0, 0xa5, value)
        print "Display from external memory\n\n\n"
    else:
        if(pattern_index > 31):
            print "Please input a correct index which is 0~31"
            sys.exit(1)
        else:
            value = (ReadReg(page0, 0xa5) & 0xef) | 0x04
            WriteReg(page0, 0xa5, value)
            value = ReadReg(page0,0xa6)
            value = value & 0xf0 | (pattern_index & 0x0f)
            WriteReg(page0,0xa6,value)
            ##pattern16~31 for freerun same as hibiscus
            value1 = ReadReg(page5,0x5a)
            value1 = (value1 & 0x7f) | ((pattern_index & 0x10)<<3)
	    print "Value=%d " % (value1)
            WriteReg(page5,0x5a,value1)
        print "Display from internal Freerun\n\n\n"

#def Pattern_Change(display_from, pattern_index, framerate):
#	UsbFuncInit()
#	SelectDP825SourceFPGA()
def Pattern_Change(display_from, pattern_index, framerate, BoardNo):
    	UsbFuncInit(BoardNo)
    	SelectDP855SourceFPGA()

	APT_Disable()        ##disable APT

	apt_manual_en = 0       ## manual/auto control FR
	apt_framerate = framerate      ## FR value in auto control FR
	apt_rr_line = 1000      ## rr_line value in manual control FR
	APT_INIT(apt_rr_line, apt_framerate)  

        global display_old_from
        if(display_old_from != display_from):
            SelectPattern(1, 0)
        display_old_from = display_from

	SelectPattern(pattern_index, display_from)    ## pattern select

	APT_Enable()        ##enable APT


##Pattern_Change(1, 0x08, 120)	## ddr Pattern
Pattern_Change(0, 0x00, 60, 0)	## logical Pattern
