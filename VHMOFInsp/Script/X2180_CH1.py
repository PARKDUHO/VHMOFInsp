from time import *
from usbfunc import *
from subfunc import *
from ctypes import *

import freq_func
import Mux_Setting

#UsbFuncInit()

#SelectDP855SourceFPGA()

page0 = 0x10
page2 = 0x14
page5 = 0x1a


current_tap = 0x28    ##lclk = current_tap * 54MHz, should be config via GUI

lane_num = 4          ##lane number, should be config via GUI
####TPS_type = 'tps3'     ##training pattern select, should be config via GUI
TPS_type = 'tps2'

Color_format = 'RGB'  ##'RGB' or 'YCbCr422' or 'YCbCr444'
Bit_depth = '8bit'    ##'6bit' or '8bit' or '10bit' , should be config via GUI

mode = '2560x1665_X2180'

Hibiscus_fr_pattern_sel = 1  ##select the same freerun as hibiscus , should be config via GUI
Display_from_mem_en = 0      ##display pattern from external memory , should be config via GUI
FR_SOURCE = 'new'     ##'new' or 'old'
RGB_0_1 = 'RGB0'      ##'RGB0' or 'RGB1'  only valid when FR_SOURCE is 'new'
Pattern_type = 0x01   ##0 ~ 0xf , should be config via GUI

pol_en = 1          ##polarity enable , should be config via GUI
pol_start = 0x0000  ##polarity change in which lines, should be config via GUI
pol_cycle = 0x3f    ##polarity change interval in frames, should be config via GUI

training_type = 0 # 0: full training   1 fast training    2 no training
TPS1_time = 0.1 ##second
TPS2_time = 0.1 ##second


## use X1060 EE Arch as an example
N1_VB = 0x1F    ##in lines, should be config via GUI
## N1_VB start point is AUX preamble, that is different from spec, value write into reg should be value user input + AUXPRE_INLINE
N4_VB = 0x00    ##in lines, should be config via GUI
N5B_VB = 0x0A  ##in lines, should be config via GUI
N5A_VB = 0x00   ##in lines, should be config via GUI
N7_VB = 0x00  ##in lines, should be config via GUI

N1_IFP = 0x00   ##in lines, should be config via GUI
N4_IFP = 0x00   ##in lines, should be config via GUI
N5B_IFP = 0x00  ##in lines, should be config via GUI
##N5A_IFP = 0x01  ##in lines, should be config via GUI
##N6_IFP = 0x01   ##in lines, should be config via GUI
##N7_IFP = 0x01   ##in lines, should be config via GUI

N2_VB = 0x02  ##in symbols, should be config via GUI
N2_IFP = 0x0000  ##in symbols, should be config via GUI
N2VB_PRE = 0x01      ## set tps1 sending time(0~15us) before aux command stop

## N2_VB and N2_IFP are all 10us for TPS1 pattern
## N2_VB = int(10000.0/(1000.0/(current_tap*54))/20)
N2_IFP = N2_VB

VB_ALPM_EN = 'disable'   ## enable or disable ALPM in vertical blank, should be config via GUI
IFP_ALPM_EN = 'disable'  ## enable or disable ALPM in IFP blank, should be config via GUI
##SLEEP_STDBY_SEL = 'stdby'    ## sleep or stdby
SLEEP_STDBY_SEL = 'sleep'    ## sleep or stdby, should be config via GUI
FCHANGE_EN = 0  ##linkrate change enable during ALPM, should be config via GUI


N1_THRESH = 49.9

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
if mode == "2560x1665_X2180":
    vclk = 277.042
    htotal = 2640
    hstart = 72
    hwidth = 2560
    vtotal = 1749
    vstart = 52
    vheight = 1665
    hsp    = 0
    hsw    = 32
    vsp    = 0
    vsw    = 8


    
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
##    Selectfreepattern(FR_SOURCE, RGB_0_1, Pattern_type)
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

##Clock and MUX Initial

def DP501_N1_TRANS():
    global AUXPRE_INLINE
    htotall = ReadReg(page0, 0x10)
    htotalh = ReadReg(page0, 0x11)
    htotal = (htotalh << 8) + htotall
    line_time = 1/vclk * htotal     ##time in us per line
    T3a_reg = ReadReg(page0, 0x68)
    T3a = 20 + (T3a_reg&0x0f)     ## T3a = 15us + T3a_reg[3:0] + 4us + 1us
    AUXPRE_INLINE = int(round(T3a/line_time))  ## AUX preamble + AUX Fchang/wake = 22us
        

def DP501_N1_VB(value):
    
    WriteReg(page0, 0x22, 0x01)
    WriteReg(page0, 0x23, value)

def DP501_N4_VB(value):
    WriteReg(page0, 0x22, 0x00)
    WriteReg(page0, 0x23, value)

def DP501_N5B_VB(value):
    WriteReg(page0, 0x22, 0x02)
    WriteReg(page0, 0x23, value)

def DP501_N5A_VB(value):
    WriteReg(page0, 0x22, 0x43)
    WriteReg(page0, 0x23, value)

def DP501_N7_VB(value):
    WriteReg(page0, 0x22, 0x44)
    WriteReg(page0, 0x23, value)

def DP501_N2_VB(value):
    WriteReg(page0, 0x22, 0x05)
    WriteReg(page0, 0x23, value&0xff)
    WriteReg(page0, 0x22, 0x06)
    WriteReg(page0, 0x23, value>>8)

def DP501_N2VB_PRE(value):
    WriteReg(page0, 0x22, 0x92)
    WriteReg(page0, 0x23, value&0xff)

def DP501_N3_VB(value):
    WriteReg(page0, 0x22, 0x07)
    WriteReg(page0, 0x23, value)


def DP501_N1_IFP(value):
    WriteReg(page0, 0x22, 0x0a)
    WriteReg(page0, 0x23, value)

def DP501_N4_IFP(value):
    WriteReg(page0, 0x22, 0x09)
    WriteReg(page0, 0x23, value)

def DP501_N5B_IFP(value):
    WriteReg(page0, 0x22, 0x0b)
    WriteReg(page0, 0x23, value)

##def DP501_N5A_IFP(value):
##    WriteReg(page0, 0x22, 0x45)
##    WriteReg(page0, 0x23, value)
##
##def DP501_N6_IFP(value):
##    WriteReg(page0, 0x22, 0x46)
##    WriteReg(page0, 0x23, value)
##
##def DP501_N7_IFP(value):
##    WriteReg(page0, 0x22, 0x47)
##    WriteReg(page0, 0x23, value)

def DP501_N2_IFP(value):
    WriteReg(page0, 0x22, 0x0c)
    WriteReg(page0, 0x23, value&0xff)
    WriteReg(page0, 0x22, 0x0d)
    WriteReg(page0, 0x23, value>>8)

def DP501_N3_IFP(value):
    WriteReg(page0, 0x22, 0x0e)
    WriteReg(page0, 0x23, value)

def DP501_ALPM_CTRL(VB_ALPM_EN, IFP_ALPM_EN, HW_SW_SEL, SLEEP_STDBY_SEL, LOCK_TYPE, FCH_SEL, COMBINE_SEL, SCR_EN, ML_SDEN): 
    ##ALPM control register set
    ##ALPM_EN: enable or disable
    ##HW_SW_SEL: hardware or software
    ##SLEEP_STDBY_SEL: sleep or stdby
    ##LOCK_TYPE: sr_blank    SR insert in the first blank after wake end
    ##           idle_sr     IDLE patter with SR after TPS2 pattern
    ##           ilde_nsr    IDLE patter without SR after TPS2 pattern
    ##           one_blank   One more VBlank line insert between wake end and active
    ##FCH_SEL: AUX_PHY_WAKE or AUX_WAKE_F_CHANGE select  fch or nfch
    ##COMBINE_SEL: wake or combined wake select  combine or ncombine

    if COMBINE_SEL == 'combine':
        value1 = 0x01
    elif COMBINE_SEL == 'ncombine':
        value1 = 0x00

    if FCH_SEL == 1:
        value2 = 0x01
    else:
        value2 = 0x00
    value = (value2<<1) + value1
    WriteReg(page0, 0x7c, value)

    if VB_ALPM_EN == 'enable':
        value1 = 0x01
    elif VB_ALPM_EN == 'disable':
        value1 = 0x00

    if HW_SW_SEL == 'hardware':
        value2 = 0x01
    elif HW_SW_SEL == 'software':
        value2 = 0x00

    if SLEEP_STDBY_SEL == 'sleep':
        value3 = 0x01
    elif SLEEP_STDBY_SEL == 'stdby':
        value3 = 0x00

    if LOCK_TYPE == 'sr_blank':
        value4 = 0x00
    elif LOCK_TYPE == 'idle_sr':
        value4 = 0x01
    elif LOCK_TYPE == 'idle_nsr':
        value4 = 0x02
    elif LOCK_TYPE == 'one_blank':
        value4 = 0x03

    if SCR_EN == 'scr_enable':
        value5 = 0x00
    elif SCR_EN == 'scr_disable':
        value5 = 0x01

    if ML_SDEN == 'sd_enable':
        value6 = 0x01
    elif ML_SDEN == 'sd_disable':
        value6 = 0x00

    if IFP_ALPM_EN == 'enable':
        value7 = 0x01
    elif IFP_ALPM_EN == 'disable':
        value7 = 0x00

    value = (value7<<7) + (value6<<6) + (value5<<5) + (value4<<3) + (value3<<2) + (value2<<1) + value1
    WriteReg(page0, 0x22, 0x03)
    WriteReg(page0, 0x23, value)

def SetMLSDDelay(value):
    WriteReg(page0,0x22,0x08)
    WriteReg(page0,0x23,value)

def SetTPSType(type):
    value = ReadReg(page0,0x5f)
    if type == 'tps2':
        value = value & 0xdf
    elif type == 'tps3':
        value = value | 0x20
    WriteReg(0x10,0x5f,value)

def CalVclkFreq():
    global vclk
    M = ReadReg(page2, 0x17)
    N = ReadReg(page2, 0x18) & 0x7f
    Frac = ReadReg(page2,0x23)      ## if frac is enabled
    if(Frac & 0x40):
        M = (M<<3) | (Frac&0x7)
        N = (N<<3) | ((Frac>>3)&0x7)
##        print M,N        
    vclk = 108.0 * M / N
    print "vclk frequency is %.2fMhz" % (vclk)

def DP501_ALPM_SW(SW_ALPM, WAKE_WAY, SW_WAKE): ##ALPM software control
    WriteReg(page0, 0x22, 0x03)
    value = ReadReg(page0, 0x23) ##read REG_ALPM_CTL
    value = value & 0xfd         ##set HW_SW_SEL = 1'b0 i.e. software control
    WriteReg(page0, 0x23, value)

    if SW_ALPM == 'enable':
        value1 = 0x01
    elif SW_ALPM == 'disable':
        value1 = 0x00

    if WAKE_WAY == 'auto':
        value2 = 0x01
    elif WAKE_WAY == 'manual':
        value2 = 0x00

    if SW_WAKE == 'enable':
        value3 = 0x01
    elif SW_WAKE == 'disable':
        value3 = 0x00

    value = (value3<<2) + (value2<<1) + value1
    WriteReg(page0, 0x22, 0x04)
    WriteReg(page0, 0x23, value)

def DP501_ALPM_INIT(): 
##    check N5 
    vtotall = ReadReg(page0, 0x16)
    vtotalh = ReadReg(page0, 0x17)
    vtotal = (vtotalh << 8) + vtotall
    vheightl = ReadReg(page0, 0x1a)
    vheighth = ReadReg(page0, 0x1b)
    vheight = (vheighth << 8) + vheightl
    vblank = vtotal - vheight
    if(vblank < (N1_VB + N5B_VB)):
        print "N1 plus N5 exceed VBLANK line number"
    else:
        CalVclkFreq()
        DP501_N1_TRANS()
    ##    check N1
        htotall = ReadReg(page0, 0x10)
        htotalh = ReadReg(page0, 0x11)
        htotal = (htotalh << 8) + htotall
        n1 = (1.0 * htotal / vclk) * (N1_VB - N4_VB - N7_VB)
        print "n1 is %.2f" % (n1)
        if(n1 < N1_THRESH):
            N1_time_temp = int(N1_THRESH * vclk / htotal) + N4_VB + N7_VB + 1
            print "N1 is too small for RX to lock, minimun N1 is %x" % (N1_time_temp)
        else:
            DP501_N1_VB(N1_VB + AUXPRE_INLINE)
            DP501_N4_VB(N4_VB)
            DP501_N5A_VB(N5A_VB)
            DP501_N5B_VB(N5B_VB)
            DP501_N7_VB(N7_VB)
            DP501_N2_VB(N2_VB)
            DP501_N2VB_PRE(N2VB_PRE)
##            DP501_N2_VB(0x0800)
            DP501_N3_VB(0x0a)
            DP501_N1_IFP(N1_IFP + AUXPRE_INLINE)
            DP501_N4_IFP(N4_IFP)
##            DP501_N5A_IFP(N5A_IFP)
            DP501_N5B_IFP(N5B_IFP)
##            DP501_N6_IFP(N6_IFP)
##            DP501_N7_IFP(N7_IFP)
            DP501_N2_IFP(N2_IFP)
##            DP501_N2_IFP(0x0000)
            DP501_N3_IFP(0x0a)
            SetTPSType('tps3')
            SetMLSDDelay(0x1f)
            DP501_ALPM_CTRL(VB_ALPM_EN, IFP_ALPM_EN, 'hardware', SLEEP_STDBY_SEL, 'sr_blank', FCHANGE_EN, 'ncombine', 'scr_disable', 'sd_enable')


def Initial():
    WriteReg(0x14,0x21, 0x00);   ##[4] 0: AUX_0
    ##WriteReg(0x14,0x21, 0x20);   ##[4] 1: AUX_1  jumper testin[2] on

    LCLK_SEL = (ReadReg(EEPROM_ADDR,0x02)>>4) & 0x01
    freq_func.Init_Chip()
    freq_func.Link_Setup(LCLK_SEL,current_tap*54)
    Mux_Setting.Port_Switch(0,LCLK_SEL)   
    swing = 0x77
    postcursor = 0x0
    Set_SWING(2,swing)
    Set_POSTCURSOR(2,postcursor)


def DP501_START_INIT_Board(BoardNo):
    UsbFuncInit(BoardNo)
    SelectDP855SourceFPGA()
    Mux_Setting.MUX_Init(0)
    Mux_Setting.MUX_Init(1)
    Initial()
    DP501_START_INIT()

##Clock and MUX Initial

#Initial()

#DP501_START_INIT()

#DP501_START_INIT_Board(0)   ## select board 0-3
#sleep(1)
DP501_START_INIT_Board(0)   ## select board 0-3
