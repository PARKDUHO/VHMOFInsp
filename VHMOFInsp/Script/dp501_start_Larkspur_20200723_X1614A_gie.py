import math
from time import *
from usbfunc import *
from subfunc import *
from ctypes import *

import freq_func
import Mux_Setting

UsbFuncInit()

SelectDP855SourceFPGA()

page0 = 0x10
page2 = 0x14
page5 = 0x1a


current_tap = 0x2e    ##lclk = current_tap * 54MHz, should be config via GUI

lane_num = 4          ##lane number, should be config via GUI
TPS_type = 'tps2'     ##training pattern select, should be config via GUI

Color_format = 'RGB'  ##'RGB' or 'YCbCr422' or 'YCbCr444'
Bit_depth = '8bit'    ##'6bit' or '8bit' or '10bit' , should be config via GUI

##mode = '2048x2732_719'    ##see list below
##mode = '2388x1668_x1047'    ##see list below
##mode = '1920x1080_vesa'    ##see list below
##mode = '2048x1536'    ##see list below , should be config via GUI
##mode = '2732x2048_x1608'
##mode = '2732x2048_x1614'
mode = '2732x2048_x1614A'

Hibiscus_fr_pattern_sel = 1  ##select the same freerun as hibiscus , should be config via GUI
Display_from_mem_en = 0      ##display pattern from external memory , should be config via GUI
FR_SOURCE = 'new'     ##'new' or 'old'
RGB_0_1 = 'RGB0'      ##'RGB0' or 'RGB1'  only valid when FR_SOURCE is 'new'
Pattern_type = 0x0c   ##0 ~ 0xf , should be config via GUI

pol_en = 0          ##polarity enable , should be config via GUI
pol_start = 0x0000  ##polarity change in which lines, should be config via GUI
pol_cycle = 0x3f    ##polarity change interval in frames, should be config via GUI

training_type = 0 # 0: full training   1 fast training    2 no training
TPS1_time = 0.1 ##second
TPS2_time = 0.1 ##second



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
    WriteReg(page0,0x2f,0x8a)
    WriteReg(page0,0x98,0x80)


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
##        value = value & 0xdf      ##typo err caused scrambler disable
        value = value & 0xbf
    elif en == 'disable':
##        value = value | 0x20
        value = value | 0x40
    WriteReg(page0,0x60,value)


def SetLinkRate():
    value = int(current_tap * 54 / 270)
##    print "linkrate index is %d" % (value)
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
    WriteReg(page0,0x74,0x0a)
    sleep(0.05)
    value = ReadReg(page0,0x5f) | 0x40
    WriteReg(page0,0x5f,value)    
    if(training_type == 0):
        value = ReadReg(page0,0x5f)
        value = value & 0xfc | 0x01
        WriteReg(page0,0x5f,value)
        sleep(0.001)
        WriteReg(page0, 0x74, 0x00)
    elif(training_type == 1):
        AUX_SingleWrite(0x102, 0x01)
        WriteReg(page0, 0x74, 0x80)
        sleep(TPS1_time)
        if(TPS_type == 'tps2'):
            AUX_SingleWrite(0x102, 0x02)
        elif(TPS_type == 'tps3'):
            AUX_SingleWrite(0x102, 0x03)
        WriteReg(page0, 0x74, 0x90)
        sleep(TPS2_time)
        AUX_SingleWrite(0x102, 0x00)
        WriteReg(page0, 0x74, 0xc0)
    elif(training_type == 2):
        WriteReg(page0, 0x74, 0xc0)

def SelVideoTiming():
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
    ##write pattern16~31
    value1 = ReadReg(page5,0x5a)
    value1 = (value1 & 0x7f) | ((tps_type & 0x10)<<3)
    WriteReg(page5,0x5a,value1)

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
    if(training_type == 0):
        lane0_1_result = ReadReg(page0,0x63)
        lane2_3_result = ReadReg(page0,0x64)
        lane4_5_result = ReadReg(page0,0xc3)
        lane6_7_result = ReadReg(page0,0xc4)
        lane_result = lane0_1_result | (lane2_3_result<<8) | (lane4_5_result<<16) | (lane6_7_result<<24)
        train_result = True
        for i in range(lane_num):
            if((lane_result & 0x07) != 0x07):
                train_result = False
                break
            lane_result>>4 
        if(train_result):
            print 'DP501 full Train OK'
        else:
            print 'DP501 full Train Fail'
    elif(training_type == 1):
        print 'DP501 fast Train done'
    elif(training_type == 2):
        print 'DP501 no Train'


def Set_VCLK(vclk, frac_mode=2):
    if frac_mode == 1: frac_en = 1   ##enable
    elif frac_mode == 2:    ##auto
        WriteReg(0x18,0xff,0x00)
        val = BurstRead(0x18,0xfd,2)
        version = (val[0]<<8) | val[1]
        if version >= 0x2020: frac_en = 1
        else: frac_en = 0
    else:
        frac_en = 0       ##disable

    pixel_width = 4               ##quad pixel mode
    vclk = float(vclk)
    vclk /= pixel_width
    Fvco_max = 1440
    Fvco_min = 600
    Fin = 27.0
    if(frac_en):
        loop_min = int(math.ceil(8.0*Fvco_min/Fin))
        loop_max = int(8.0*Fvco_max/Fin)
        ##MUL [2,64]*8
        if loop_min < 16: loop_min = 16
        if loop_max > 512: loop_max = 512
##        print loop_min, loop_max
        ratio = vclk / Fin
        pll_mul = loop_min
        pll_div = 16
        for m in range(loop_min,loop_max+1):
            ##DIVIDE [2,128]*8
            ##for n in range(8,128*8+1):
            for n in range(16,128*8+1):
                if abs(float(m)/n-ratio) < abs(float(pll_mul)/pll_div-ratio):
                    pll_mul = m
                    pll_div = n
    else:
        loop_min = int(math.ceil(Fvco_min/Fin))
        loop_max = int(Fvco_max/Fin)
        ##MUL [2,64]
        if loop_min < 2: loop_min = 2
        if loop_max > 64: loop_max = 64
##        print loop_min, loop_max
        ratio = vclk / Fin
        pll_mul = loop_min
        pll_div = 1
        for m in range(loop_min,loop_max+1):
            ##DIVIDE [1,128]
            for n in range(1,128+1):
                if abs(float(m)/n-ratio) < abs(float(pll_mul)/pll_div-ratio):
                    pll_mul = m
                    pll_div = n
        
    vclk = Fin*pll_mul/pll_div*pixel_width
    print "vclk = %.2fMHz"%vclk,"PLL_MUL = %d "%pll_mul,"PLL_DIV = %d "%pll_div

    if(frac_en):
        frac = (pll_mul&0x7) | ((pll_div&0x7)<<3) | (0x1<<6)
        pll_mul >>= 3
        pll_div >>= 3
    else:
        frac = 0
    WriteReg(0x14,0x23,frac)
    WriteReg(0x14,0x17,pll_mul)
    WriteReg(0x14,0x18,pll_div)
    WriteReg(0x14,0x18,(pll_div | 0x80))
    

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



def Ini_Pat_21_22_24_25_27():
    vheight31 = int(vheight/3)
    WriteReg(page5, 0x52, vheight31&0xff)
    WriteReg(page5, 0x53, (vheight31>>8)&0xff)
    hwidth31 = int(hwidth/12)  ## 4 pixel per pixel clock
    WriteReg(page5, 0x50, hwidth31&0xff)
    WriteReg(page5, 0x51, (hwidth31>>8)&0xff)

def Ini_Pat_23():
    color_step = int(vheight/14)
    WriteReg(page5, 0x55, color_step&0xff)
    gray_step = int(color_step*2/3)
    WriteReg(page5, 0x54, gray_step&0xff)
    
def Ini_Pat_26():
    ##write start h position default 1/4 HWIDTH
    hwidth41 = int(hwidth/16)  ## 4 pixel per pixel clock
    WriteReg(page5, 0x59, hwidth41&0xff)
    WriteReg(page5, 0x5c, (hwidth41>>8)&0xff)
    ##color step
    color_step = int(hwidth/4/2/13) - 1
    WriteReg(page5, 0x58, color_step&0xff)
    ##gray step
    gray_step = int(color_step*2/3) - 1
    WriteReg(page5, 0xef, gray_step&0xff)

def Ini_Pat_28_29():
    bpc = (ReadReg(page0,0x20)>>5) & 0x7
    value = ReadReg(page5,0x6f)
    if(bpc == 0 or bpc == 1):
        value = value | 0x2
        WriteReg(page5, 0x6f, value&0xff)
    else:
        value = value & 0xfd
        WriteReg(page5, 0x6f, value&0xff)

def Ini_Pat_30():
    WriteReg(page5, 0x70, 8)
    WriteReg(page5, 0x71, 0x7f)  ##height equals width

def Set_TUsize(value):
    WriteReg(page0,0x36,value&0xff)

def Set_BSdelay(value):
    WriteReg(page0,0x39,value&0xff)

def En_Internal_Reg(retry_num):
    WriteReg(page0, 0x75, 0x78)          ##AUX Reset
    WriteReg(page0, 0x75, 0x00)
    for i in range(retry_num):
        AUX_SingleWrite(0x00490, 0x00)  ##reset sequence
        AUX_SingleWrite(0x00490, 0x50)
        AUX_SingleWrite(0x00490, 0x41)
        AUX_SingleWrite(0x00490, 0x52)
        AUX_SingleWrite(0x00490, 0x41)
        AUX_SingleWrite(0x00490, 0x41)
        AUX_SingleWrite(0x00490, 0x55)
        AUX_SingleWrite(0x00490, 0x58)
        AUX_SingleWrite(0x00490, 0x02)
        AUX_SingleWrite(0x00490, 0x52)
        AUX_SingleWrite(0x00490, 0x45)
        AUX_SingleWrite(0x00490, 0x47)     
        ucValue = AUX_SingleRead(0x00490)
        if(ucValue != 0):
            break
    if(ucValue == 0):
        return False
    else:
        return True


def Write_DPCD454(value):
    if(not En_Internal_Reg(10)):
        print "Error: enable writing internal register failed"
        return False
    print "Write DPCD454"
    AUX_SingleWrite(0x00491, 0x01)
    AUX_SingleWrite(0x00492, 0x14)
    AUX_SingleWrite(0x00493, value&0xff)


def Write_DPCD453(value):
    AUX_SingleWrite(0x00453, value&0xff)


def Set_Recalc():
    value_471 = AUX_SingleRead(0x00471)
    if(lane_num>4):
        AUX_SingleWrite(0x00101, 0x84)  ##write lane_num
        AUX_SingleWrite(0x0035f, lane_num-4)
        AUX_SingleWrite(0x00471, value_471|0x02)
    else:
        AUX_SingleWrite(0x00101, 0x80+lane_num)
        AUX_SingleWrite(0x00471, value_471&0xfd)
    
    value_100 = AUX_SingleRead(0x00100)
    sink_linkrate = value_100 * 270  ##MHz
    value_450 = AUX_SingleRead(0x00450)
    value_451 = AUX_SingleRead(0x00451)
    sink_current_tap = AUX_SingleRead(0x00454)
    sink_base_tap = AUX_SingleRead(0x00455)
    target_link_rate = current_tap * 54
    link_rate_num = 1.0 * target_link_rate /270
    if((not(value_451 & 0x01)) and (target_link_rate != sink_linkrate)):
        print "traditional"
        for i in range(21):
            if(link_rate_num == i):
                if(link_rate_num > 14):   ## need re-calibration only when linkrate greater than 4Gbps
                    print "Need re-calibration"
                    AUX_SingleWrite(0x00100, i)
                    AUX_SingleWrite(0x00451, (value_451|0x80))
                    sleep(0.1)
                return
        if(value_450 & 0x01):
            if(current_tap >74):
                AUX_SingleWrite(0x00451, (value_451|0x03))
            else:
                AUX_SingleWrite(0x00451, (value_451|0x01))
            if(current_tap != sink_base_tap):
                AUX_SingleWrite(0x00455, current_tap)
      ##      if(current_tap != sink_current_tap):
      ##          Write_DPCD454(current_tap)
            AUX_SingleWrite(0x00453, 0)
            if(current_tap >74):
                AUX_SingleWrite(0x00451, (value_451|0x83))
            else:
                AUX_SingleWrite(0x00451, (value_451|0x81))
            sleep(0.01)
        else:
            print "Agile not support, and can not support this linkrate %dMbps" % (target_link_rate)    
    elif((value_451 & 0x01) and (current_tap != sink_base_tap)):
        print "Need re-calibration"
        if((sink_base_tap<=50 and current_tap>50) or (sink_base_tap>50 and current_tap<=50)):
            print "Error: cross 2.7G boundary, won't change sink base tap"
        else:
            if(current_tap >74):
                AUX_SingleWrite(0x00451, (value_451|0x03))
            else:
                AUX_SingleWrite(0x00451, (value_451|0x01))
            AUX_SingleWrite(0x00455, current_tap)
       ##     if(current_tap != sink_current_tap):
       ##         Write_DPCD454(current_tap)
            AUX_SingleWrite(0x00453, 0)
            if(current_tap >74):
                AUX_SingleWrite(0x00451, (value_451|0x83))
            else:
                AUX_SingleWrite(0x00451, (value_451|0x81))
            sleep(0.01)



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

elif mode == "2732x2048_x1060":
    vclk = 750
    htotal = 2772
    hstart = 12
    hwidth = 2732
    vtotal = 2256
    vstart = 146
    vheight = 2048
    hsp    = 0
    hsw    = 8
    vsp    = 0
    vsw    = 2

elif mode == "2732x2048_x1608":
    vclk = 750
    htotal = 2772
    hstart = 12
    hwidth = 2732
    vtotal = 2256
    vstart = 146
    vheight = 2048
    hsp    = 0
    hsw    = 8
    vsp    = 0
    vsw    = 2

elif mode == "2732x2048_x1614A":
    vclk = 313.04
    htotal = 2426
    hstart = 12
    hwidth = 2268
    vtotal = 2151
    vstart = 129
    vheight = 1488
    hsp    = 0
    hsw    = 8
    vsp    = 0
    vsw    = 2

elif mode == "2224x1668_x1047":
    vclk = 500
    htotal = 2256
    hstart = 12
    hwidth = 2224
    vtotal = 1848
    vstart = 118
    vheight = 1668
    hsp    = 0
    hsw    = 8
    vsp    = 0
    vsw    = 2

elif mode == "2388x1668_x1047":
    vclk = 536
    htotal = 2418
    hstart = 12
    hwidth = 2388
    vtotal = 1848
    vstart = 118
    vheight = 1668
    hsp    = 0
    hsw    = 8
    vsp    = 0
    vsw    = 2


elif mode == "1668x2224":
    vclk = 500
    htotal = 1698
    hstart = 12
    hwidth = 1668
    vtotal = 2454
    vstart = 168
    vheight = 2224
    hsp    = 0
    hsw    = 8
    vsp    = 0
    vsw    = 2

elif mode == "2048x2732_754":
    vclk = 754
    htotal = 2088
    hstart = 20
    hwidth = 2048
    vtotal = 3010
    vstart = 200
    vheight = 2732
    hsp    = 0
    hsw    = 8
    vsp    = 0
    vsw    = 2

elif mode == "2048x2732_719":
    vclk = 719
    htotal = 2088
    hstart = 20
    hwidth = 2048
    vtotal = 2874
    vstart = 100
    vheight = 2732
    hsp    = 0
    hsw    = 8
    vsp    = 0
    vsw    = 2

elif mode == "2048x2732_400":
    vclk = 400
    htotal = 2202
    hstart = 76
    hwidth = 2048
    vtotal = 3026
    vstart = 200
    vheight = 2732
    hsp    = 0
    hsw    = 8
    vsp    = 0
    vsw    = 2

elif mode == "1668x2224_120":
    vclk = 500.1
    htotal = 1700
    hstart = 16
    hwidth = 1668
    vtotal = 2454
    vstart = 30
    vheight = 2224
    hsp    = 0
    hsw    = 8
    vsp    = 0
    vsw    = 2

elif mode == "1668x2224_60":
    vclk = 500.1
    htotal = 1700
    hstart = 16
    hwidth = 1668
    vtotal = 4908
    vstart = 30
    vheight = 2224
    hsp    = 0
    hsw    = 8
    vsp    = 0
    vsw    = 2

elif mode == "1668x2224_24":
    vclk = 500.1
    htotal = 1700
    hstart = 16
    hwidth = 1668
    vtotal = 12270
    vstart = 30
    vheight = 2224
    hsp    = 0
    hsw    = 8
    vsp    = 0
    vsw    = 2

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

elif mode == "2048x1536":
    vclk = 207.99
##    vclk = 110
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
    vclk   = 138.8
##    vclk   = 75
    
    htotal = 2080
    hstart = 112
    hwidth = 1920
    vtotal = 1112
    vstart = 29
    vheight = 1080
    hsp    = 0
    hsw    = 32
    vsp    = 0
    vsw    = 6

elif mode == "1920x1080_vesa":
    vclk   = 148.5
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
    vclk = 100
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

elif mode == "640x480_60Hz":
    vclk = 25.2
    htotal = 800
    hstart = 32
    hwidth = 640
    vtotal = 525
    vstart = 16
    vheight = 480
    hsp    = 0
    hsw    = 16
    vsp    = 0
    vsw    = 4




dual_bus = 1          ##



def DP501_START_INIT():
    Set_VCLK(vclk, 2)    ##0: Int Divide, 1: Frac Divide, 2: Atuo, base on version
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
    SetPOL_start(vstart + vheight)
    Ini_Pat_21_22_24_25_27()
    Ini_Pat_23()
    Ini_Pat_26()
    Ini_Pat_28_29()
    Ini_Pat_30()
    Set_TUsize(0x0f)
    Set_BSdelay(0x0f)
##    Set_Recalc()
    Write_DPCD453(current_tap)
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
    ##WriteReg(0x14,0x21, 0x20);   ##[4] 1: AUX_1  jumper testin[2] on

    LCLK_SEL = (ReadReg(EEPROM_ADDR,0x02)>>4) & 0x01
    freq_func.Init_Chip()
    freq_func.Link_Setup(LCLK_SEL,current_tap*54)
    Mux_Setting.Port_Switch(0,LCLK_SEL)   
    swing = 0xFF
    postcursor = 0x17
    Set_SWING(2,swing)
    Set_POSTCURSOR(2,postcursor)


##Clock and MUX Initial

Initial()

DP501_START_INIT()
