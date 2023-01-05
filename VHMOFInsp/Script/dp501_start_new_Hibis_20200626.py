from time import *
from usbfunc import *
from subfunc import *
from ctypes import *

import freq_func
import Mux_Setting


UsbFuncInit()

##SelectDP825SourceFPGA()
##SelectDebugTool()
SelectDP855SourceFPGA()

page0 = 0x10
page2 = 0x14


##current_tap = 0x1e    ##lclk = current_tap * 54MHz, should be config via GUI
##current_tap = 0x32
##current_tap = 0x64
##current_tap = 0x96    ##for X1712
##current_tap = 0x6a
##current_tap = 0x91
##current_tap = 0x73    ##for X1719
current_tap = 0x2b      ##for X1768/X1769

##extend_lane_en = 0    ##extend lane(6 or 8 lane) support, should be config via GUI

lane_num = 4         ##lane number, should be config via GUI
TPS_type = 'tps3'     ##training pattern select, should be config via GUI

Color_format = 'RGB'  ##'RGB' or 'YCbCr422' or 'YCbCr444'
Bit_depth = '8bit'    ##'6bit' or '8bit' or '10bit' , should be config via GUI

##mode = '4480x2520'
##mode = '3840x2160'
##mode = '1920x1080_vesa'
##mode = '1920x1080'
##mode = '2048x1536'    ##see list below , should be config via GUI
##mode = '3456x2234_X1712'    
##mode = '3024x1964_X1719'
##mode = '2560x1600_X1768/1769'
##mode = '2266x1488'

Hibiscus_fr_pattern_sel = 0  ##select the same freerun as hibiscus , should be config via GUI
Display_from_mem_en = 0      ##display pattern from external memory , should be config via GUI
FR_SOURCE = 'new'     ##'new' or 'old'
RGB_0_1 = 'RGB0'      ##'RGB0' or 'RGB1'  only valid when FR_SOURCE is 'new'
Pattern_type = 0x0a   ##0 ~ 0xf , should be config via GUI

pol_en = 0          ##polarity enable , should be config via GUI
pol_start = 0x0000  ##polarity change in which lines, should be config via GUI
pol_cycle = 0x3f    ##polarity change interval in frames, should be config via GUI




def WriteHTOTAL(value):
    WriteReg(page0,0x10,value&0xff)
    WriteReg(page0,0x11,value>>8)

def WriteHSTART(value):
    WriteReg(page0,0x12,value&0xff)
    WriteReg(page0,0x13,value>>8)

def WriteHWIDTH(value):
    WriteReg(page0,0x14,value&0xff)
    WriteReg(page0,0x15,value>>8)

def WriteVTOTAL(value):
    WriteReg(page0,0x16,value&0xff)
    WriteReg(page0,0x17,value>>8)

def WriteVSTART(value):
    WriteReg(page0,0x18,value&0xff)
    WriteReg(page0,0x19,value>>8)

def WriteVHEIGHT(value):
    WriteReg(page0,0x1a,value&0xff)
    WriteReg(page0,0x1b,value>>8)

def WriteHSPHSW(hsp, hsw):
    value = (hsp << 15) + hsw
    WriteReg(page0,0x1c,value&0xff)
    WriteReg(page0,0x1d,value>>8)

def WriteVSPVSW(vsp, vsw):
    value = (vsp << 15) + vsw
    WriteReg(page0,0x1e,value&0xff)
    WriteReg(page0,0x1f,value>>8)

def WriteMISC(color_format, bit_depth):
    value = ReadReg(page0,0x20)
    if color_format == 'RGB':
        value = value & 0xf9 | 0x00
    elif color_format == 'YCbCr422':
        value = value & 0xf9 | 0x02
    elif color_format == 'YCbCr444':
        value = value & 0xf9 | 0x04

    if bit_depth == '6bit':
        value = value & 0x1f | 0x00
    elif bit_depth == '8bit':
        value = value & 0x1f | 0x20
    elif bit_depth == '10bit':
        value = value & 0x1f | 0x40
    elif bit_depth == '12bit':
        value = value & 0x1f | 0x60
    WriteReg(page0,0x20,value)
    WriteReg(page0,0x2f,0x82)


def SetReadDPCD(en):
    value = ReadReg(page0,0x72)
    if en == 'enable':
        value = value | 0x80
    elif en == 'disable':
        value = value & 0x7f
    WriteReg(page0,0x72,value)

def SetScramble(en):
    value = ReadReg(page0,0x60)
    if en == 'enable':
        value = value & 0xdf
    elif en == 'disable':
        value = value | 0x20
    WriteReg(page0,0x60,value)

def SetLinkRate():
    value = int(current_tap * 54 / 270)
    WriteReg(page0,0x5d,value)

def SetLaneCnt(lanenum):
    extend_lane_en = AUX_SingleRead(0x00471) & 0x01
##    print "extend_lane_en = %d"%extend_lane_en
    if(extend_lane_en == 1):
        if lanenum == 1:
            value = 0xc1
        elif lanenum == 2:
            value = 0xc2
        elif lanenum == 4:
            value = 0xc4
        elif lanenum == 6:
            value = 0xc6
        elif lanenum == 8:
            value = 0xc8
        elif lanenum > 8:
            print 'Only support up to 8 lanes'
    else:
        if lanenum == 1:
            value = 0x81
        elif lanenum == 2:
            value = 0x82
        elif lanenum == 4:
            value = 0x84
        elif lanenum > 4:
            print 'Only support up to 4 lanes'
    WriteReg(page0,0x5e,value)

def SetEnhanceframe(type):
    value = ReadReg(page0,0x5e)
    if type == 'enhance':
        value = value | 0x80
    elif type == 'nenhance':
        value = value & 0x7f
    WriteReg(page0,0x5e,value)

def SetTPSType(type):
    value = ReadReg(page0,0x5f)
    if type == 'tps2':
        value = value & 0xdf
    elif type == 'tps3':
        value = value | 0x20
    WriteReg(page0,0x5f,value)

def StartLinktraining():
    value = ReadReg(page0,0x5f)
    value = value & 0xfc | 0x01
    WriteReg(page0,0x5f,value)

def SelVideoTiming():
    ##WR_FIFO_EN_MASK
    if dual_bus == 1:
        WriteReg(page0,0xa5,0xe9 + (Hibiscus_fr_pattern_sel<<2) + (Display_from_mem_en<<4)) 
    elif dual_bus == 0:
        WriteReg(page0,0xa5,0xe8 + (Hibiscus_fr_pattern_sel<<2) + (Display_from_mem_en<<4))
    WriteReg(page0,0x27,0x00)
    WriteReg(page0,0x25,0x00)


def Selectfreepattern(source, rgb0_1, tps_type):
    WriteReg(page0,0x22,0x67)
    value = ReadReg(page0,0x23)
    if source == 'old':
        value = value & 0xf7 | 0x00
    elif source == 'new':
        if rgb0_1 == 'RGB0':
            value = value & 0x77 | 0x08
        elif rgb0_1 == 'RGB1':
            value = value & 0x77 | 0x88
    WriteReg(page0,0x23,value)
    value = ReadReg(page0,0xa6)
    value = value & 0xf0 | (tps_type & 0x0f)
    WriteReg(page0,0xa6,value)

def SetPOL_en(en):
    WriteReg(page0,0x22,0x80)
    if en == 1:
        WriteReg(page0,0x23,0x01)
    elif en == 0:
        WriteReg(page0,0x23,0x00)

def SetPOL_cycle(value):
    WriteReg(page0,0x22,0x81)
    WriteReg(page0,0x23,value & 0xff)

def SetPOL_start(value):
    WriteReg(page0,0x22,0x82)
    WriteReg(page0,0x23,value & 0xff)
    WriteReg(page0,0x22,0x83)
    WriteReg(page0,0x23,(value>>8) & 0xff)


def Trainresult():
    train_result = ReadReg(page0,0x63)
    if(( train_result&0x07) == 0x07):
##        print 'DP501 Train OK'
        print 'DP501 Train OK.',hex(train_result),hex(ReadReg(page0,0x64))
    else:
        print 'DP501 Train Fail',hex(train_result)
##        raw_input('Wait')


def Calc_MMCM_M_D(vclk):
    global PLL_MUL
    global PLL_DIV
    vclk = vclk / 4.0               ##quad pixel mode
    Fvco_max = 1600
    Fvco_min = 600
    Fin = 27.0
    for m in range(5,65):           ##[5,64]
        if(Fin*m)<Fvco_min or (Fin*m)>Fvco_max : continue
        for n in range(1,129):      ##[1,128]            
            if abs((Fin*m/n)-vclk) < abs((Fin*PLL_MUL/PLL_DIV)-vclk):
                PLL_MUL = m
                PLL_DIV = n
    vclk = Fin*PLL_MUL/PLL_DIV*4
    print "vclk = %.2fMHz"%vclk,"PLL_MUL = %d "%PLL_MUL,"PLL_DIV = %d "%PLL_DIV

def SetVCLK(MUL, DIV):                      ##vclk = 27M * MUL / VID
    WriteReg(page2,0x17,MUL)
    WriteReg(page2,0x18,DIV)
    WriteReg(page2,0x18,(DIV | 0x80))
    sleep(0.1)

def AUX_SingleWrite(addr, data):
    WriteReg(0x10,0x7f,0x80+(addr>>16))
    WriteReg(0x10,0x7e,(addr>>8)&0xff)
    WriteReg(0x10,0x7d,addr&0xff)
    WriteReg(0x10,0x80,0x00)
    WriteReg(0x10,0x81,data&0xff)
    WriteReg(0x10,0x83,0x01)

def AUX_SingleRead(addr):
    WriteReg(0x10,0x80,0x00)
    WriteReg(0x10,0x7f,0x90+(addr>>16))
    WriteReg(0x10,0x7e,(addr>>8)&0xff)
    WriteReg(0x10,0x7d,addr&0xff)
    WriteReg(0x10,0x83,0x01)
    value = ReadReg(0x10,0x82)
    return value



################ Config Video mode parameter ########
if mode == "2732x2048_400":
    vclk = 400
    htotal = 2786
    hstart = 32
    hwidth = 2732
    vtotal = 2393
    vstart = 16
    vheight = 2048
    hsp    = 0
    hsw    = 16
    vsp    = 0
    vsw    = 4

elif mode == "1536x2048":
    vclk = 240
    htotal = 1740
    hstart = 32
    hwidth = 1536
    vtotal = 2299
    vstart = 16
    vheight = 2048
    hsp    = 0
    hsw    = 16
    vsp    = 0
    vsw    = 4

elif mode == "3456x2234_X1712":
    vclk = 1042.13
    htotal = 3536
    hstart = 72
    hwidth = 3456
    vtotal = 2456
    vstart = 104
    vheight = 2234
    hsp    = 0
    hsw    = 32
    vsp    = 0
    vsw    = 8

elif mode == "3024x1964_X1719":
    vclk = 804.56
    htotal = 3104
    hstart = 72
    hwidth = 3024
    vtotal = 2160
    vstart = 94
    vheight = 1964
    hsp    = 0
    hsw    = 32
    vsp    = 0
    vsw    = 8

    
elif mode == "2560x1600_X1768/1769":
    vclk = 266.67
    htotal = 2642
    hstart = 74
    hwidth = 2560
    vtotal = 1682
    vstart = 50
    vheight = 1600
    hsp    = 0
    hsw    = 32
    vsp    = 0
    vsw    = 8

elif mode == "2560x1600_X1768":
    vclk = 266.67
    htotal = 2642
    hstart = 74
    hwidth = 2560
    vtotal = 1682
    vstart = 50
    vheight = 1600
    hsp    = 0
    hsw    = 32
    vsp    = 0
    vsw    = 8


elif mode == "2266x1488":
    vclk = 240
    htotal = 2426
    hstart = 12
    hwidth = 2266
    vtotal = 1649
    vstart = 129
    vheight = 1488
    hsp    = 0
    hsw    = 8
    vsp    = 0
    vsw    = 2
##elif mode == "2048x1536":
####    vclk = 207.99
##    vclk = 110
##    htotal = 2208
####    htotal = 2064
##    hstart = 112
####    hstart = 8
##    hwidth = 2048
####    vtotal = 1570
##    vtotal = 2500
##    vstart = 31
##    vheight = 1536
##    hsp    = 0
##    hsw    = 32
####    hsw    = 4
##    vsp    = 0
##    vsw    = 5

elif mode == "2048x1536":
    vclk = 207.99
##    vclk = 148.5 / 4 * lane_num
 ##   vclk = 24.9
##    vclk = 38.9
    htotal = 2208
##    htotal = 2064
    hstart = 112
##    hstart = 8
    hwidth = 2048
    vtotal = 1570
##    vtotal = 2500
    vstart = 31
    vheight = 1536
    hsp    = 0
    hsw    = 32
##    hsw    = 4
    vsp    = 0
    vsw    = 5

elif mode == "2048x1536_2354":
    vclk = 96
    htotal = 2354
    hstart = 24
    hwidth = 2048
    vtotal = 1560
    vstart = 2
    vheight = 1536
    hsp    = 0
    hsw    = 16
    vsp    = 0
    vsw    = 3

elif mode == "2560x1600":
    vclk = 328
    htotal = 2720
    hstart = 32
    hwidth = 2560
    vtotal = 1646
    vstart = 16
    vheight = 1600
    hsp    = 0
    hsw    = 16
    vsp    = 0
    vsw    = 4

elif mode == "2880x1800":
    vclk = 337.7
    htotal = 3040
    hstart = 32
    hwidth = 2880
    vtotal = 1852
    vstart = 16
    vheight = 1800
    hsp    = 0
    hsw    = 16
    vsp    = 0
    vsw    = 4

elif mode == "2732x2048_342":
    vclk = 342.9
    htotal = 2797
    hstart = 32
    hwidth = 2732
    vtotal = 2074
    vstart = 16
    vheight = 2048
    hsp    = 0
    hsw    = 16
    vsp    = 0
    vsw    = 4

elif mode == "1024x768":
    vclk = 56.1
    htotal = 1184
    hstart = 32
    hwidth = 1024
    vtotal = 790
    vstart = 16
    vheight = 768
    hsp    = 0
    hsw    = 16
    vsp    = 0
    vsw    = 4
    
elif mode == "1920x1080":
    vclk   = 838.66
##    vclk   = 75
    
    htotal = 2080
    hstart = 112
    hwidth = 1920
    vtotal = 1120
    vstart = 30
    vheight = 1080
    hsp    = 0
    hsw    = 48
    vsp    = 0
    vsw    = 10

elif mode == "1920x1080_vesa":
    vclk   = 148.5
##    vclk   = 100
    htotal = 2200
    hstart = 192
    hwidth = 1920
    vtotal = 1125
    vstart = 41
    vheight = 1080
    hsp    = 0
    hsw    = 44
    vsp    = 0
    vsw    = 5

elif mode == "2880x2160":
    vclk = 200
    htotal = 3040
    hstart = 32
    hwidth = 2880
    vtotal = 2194
    vstart = 16
    vheight = 2160
    hsp    = 0
    hsw    = 16
    vsp    = 0
    vsw    = 4
elif mode == "3840x2160":
##    vclk = 527.5
    vclk = 263.75
    htotal = 3960
    hstart = 32
    hwidth = 3840
    vtotal = 2220
    vstart = 16
    vheight = 2160
    hsp    = 0
    hsw    = 16
    vsp    = 0
    vsw    = 4
elif mode == "4480x2520":
    vclk = 730
    htotal = 4580
    hstart = 20
    hwidth = 4480
    vtotal = 2620
    vstart = 20
    vheight = 2520
    hsp    = 0
    hsw    = 8
    vsp    = 0
    vsw    = 2


dual_bus = 1          ##

PLL_MUL = 37          ##vclk = 27M * PLL_MUL / PLL_DIV
PLL_DIV = 5           ##200MHz frequency of vclk for FPGA actually is half of the vclk



def DP501_START_INIT():
    Calc_MMCM_M_D(vclk)
    SetVCLK(PLL_MUL, PLL_DIV)
    WriteHTOTAL(htotal)
    WriteHSTART(hstart)
    WriteHWIDTH(hwidth)
    WriteVTOTAL(vtotal)
    WriteVSTART(vstart)
    WriteVHEIGHT(vheight)
    WriteHSPHSW(hsp, hsw)
    WriteVSPVSW(vsp, vsw)
    WriteMISC(Color_format, Bit_depth)
    SetReadDPCD('enable')
    SetScramble('enable')
    SetLinkRate()
    SetLaneCnt(lane_num)
    SetEnhanceframe('enhance')
    SetTPSType(TPS_type)
    Selectfreepattern(FR_SOURCE, RGB_0_1, Pattern_type)
    SelVideoTiming()
    SetPOL_en(pol_en)
    SetPOL_cycle(pol_cycle)
    SetPOL_start(pol_start)
    StartLinktraining()
    sleep(0.1)
    Trainresult()

EEPROM_ADDR = 0x40
def Set_SWING(chl,swing):
    wr_data = [swing,swing]
    if chl == 0:
        BurstWrite(EEPROM_ADDR,0x40,2,wr_data)
    elif chl == 1:
        BurstWrite(EEPROM_ADDR,0x50,2,wr_data)
    else:
        BurstWrite(EEPROM_ADDR,0x40,2,wr_data)
        BurstWrite(EEPROM_ADDR,0x50,2,wr_data)

def Set_POSTCURSOR(chl,postcursor):
    wr_data = [postcursor,postcursor,postcursor,postcursor]
    if chl == 0:
        BurstWrite(EEPROM_ADDR,0x46,4,wr_data)
    elif chl == 1:
        BurstWrite(EEPROM_ADDR,0x56,4,wr_data)
    else:
        BurstWrite(EEPROM_ADDR,0x46,4,wr_data)
        BurstWrite(EEPROM_ADDR,0x56,4,wr_data)

def Initial():
    WriteReg(0x14,0x21, 0x00);   ##[4] 0: AUX_0

    LCLK_SEL = (ReadReg(EEPROM_ADDR,0x02)>>4) & 0x01
    freq_func.Init_Chip()
    freq_func.Link_Setup(LCLK_SEL,current_tap*54)
    Mux_Setting.MUX_Init(0)
    Mux_Setting.Port_Switch(0,LCLK_SEL)
    
    swing = 0x22
    postcursor = 0x5
    Set_SWING(2,swing)
    Set_POSTCURSOR(2,postcursor)


##Clock and MUX Initial
Initial()

DP501_START_INIT()

