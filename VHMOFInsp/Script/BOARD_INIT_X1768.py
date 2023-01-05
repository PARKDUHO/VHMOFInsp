from time import *
from usbfunc import *
from subfunc import *
from ctypes import *
##from thread import *
##from INST_CTRL import *
##from operator import *


current_tap = 0x2b  ##link rate = 54M * current_tap, the same as value in dp501_start_new_Hibis.py

def set_freq():
    LC_TEST_SELECT='DISABLE'
    ##LC_TEST_SELECT='ENABLE'

    TS_OP_SELECT='HSCKP'

    LC_BIST_SELECT='DISABLE'
    ##LC_BIST_SELECT='ENABLE'

    linkrate_tmp = 54 * current_tap
                      
    agile_en = 'enable'           ##'enable' or 'disable'


    ####DP570 TXPLL DP mode initialization
    ####PHY setting

    WriteReg(0x46,0x1e,0x80)
    WriteReg(0x46,0x20,0x16)
    WriteReg(0x46,0x21,0x00)

    WriteReg(0x46,0x31,0x01)  ##dual mode selection
    WriteReg(0x46,0x1b,0x04)  ##TXPLL off

    if(linkrate_tmp >= 1026 and linkrate_tmp <= 1350):
        WriteReg(0x46,0x1a,0x0c)
        WriteReg(0x46,0x15,0x87)
        WriteReg(0x46,0x16,0x06)
        WriteReg(0x46,0x13,(current_tap << 1) & 0xff)
    elif(linkrate_tmp >= 1377 and linkrate_tmp <= 1647):
        WriteReg(0x46,0x1a,0x0c)
        WriteReg(0x46,0x15,0x80)
        WriteReg(0x46,0x16,0x02)
        WriteReg(0x46,0x13,(current_tap << 1) & 0xff)
    elif(linkrate_tmp >= 2025 and linkrate_tmp <= 2700):
        WriteReg(0x46,0x1a,0x0b)
        WriteReg(0x46,0x15,0x87)
        WriteReg(0x46,0x16,0x06)
        WriteReg(0x46,0x13,(current_tap << 1) & 0xff)
    elif(linkrate_tmp >= 2754 and linkrate_tmp <= 3294):
        WriteReg(0x46,0x1a,0x09)
        WriteReg(0x46,0x15,0x80)
        WriteReg(0x46,0x16,0x02)
        WriteReg(0x46,0x13,current_tap & 0xff)
##    elif(linkrate_tmp >= 4050 and linkrate_tmp <= 5400):
    elif(linkrate_tmp >= 4050 and linkrate_tmp <= 4320):    ##2016/4/15 adj range
        WriteReg(0x46,0x1a,0x08)
        WriteReg(0x46,0x15,0x87)
        WriteReg(0x46,0x16,0x06)
        WriteReg(0x46,0x13,current_tap & 0xff)
##    elif(linkrate_tmp >= 5454 and linkrate_tmp <= 6318):
    elif(linkrate_tmp >= 4374 and linkrate_tmp <= 6318):    ##2016/4/15 adj range
        WriteReg(0x46,0x1a,0x08)
        WriteReg(0x46,0x15,0x80)
        WriteReg(0x46,0x16,0x00)
        WriteReg(0x46,0x13,current_tap & 0xff)
    else:
        print 'Agile tap is out of range'
        return

    if(agile_en == 'enable'):
        WriteReg(0x46,0x14,0x10)
    elif(agile_en == 'disable'):
        WriteReg(0x46,0x14,0x00)

    ##WriteReg(0x46,0x1a,0x0c)  ##config DP mode 5.4Gbps without SS enable
    ##WriteReg(0x46,0x1a,0x18)  ##config DP mode 5.4Gbps with SS enable
                              ##[HDMI_SEL,COLOR_DEPTH<1:0>,DP_SS_EN,DP_SEL,DP_RATE_SEL<2:0>]

    WriteReg(0x46,0x00,0x23)  ##
    WriteReg(0x46,0x01,0x6f)  ##
    WriteReg(0x46,0x02,0x13)  ##
    WriteReg(0x46,0x03,0x31)  ##
    WriteReg(0x46,0x04,0x6f)  ##
    WriteReg(0x46,0x05,0x3b)  ##
    WriteReg(0x46,0x06,0x22)  ##
    WriteReg(0x46,0x07,0x73)  ##
    WriteReg(0x46,0x08,0x2b)  ##
    WriteReg(0x46,0x09,0x22)  ##
    WriteReg(0x46,0x0a,0x33)  ##
    WriteReg(0x46,0x0b,0xdb)  ##
    WriteReg(0x46,0x0c,0x82)  ##
    WriteReg(0x46,0x0d,0x44)  ##
    WriteReg(0x46,0x0e,0xe7)  ##
    WriteReg(0x46,0x0f,0x52)  ##
    WriteReg(0x46,0x10,0x44)  ##
    WriteReg(0x46,0x11,0x03)  ##

    ####output test pattern setting
    ##WriteReg(0x46,0x40,0x10)  ##test pattern output enable
    ##WriteReg(0x46,0x41,0x55)  ##test pattern for lane0 DATAIN_C<7:0>
    ##WriteReg(0x46,0x42,0x55)  ##test pattern for lane0 DATAIN_C<15:8>
    ##WriteReg(0x46,0x43,0x55)  ##test pattern for lane1 DATAIN_C<3:0>, lane0 DATAIN_C<19:16>
    ##WriteReg(0x46,0x44,0x55)  ##test pattern for lane1 DATAIN_C<11:4>
    ##WriteReg(0x46,0x45,0x55)  ##test pattern for lane1 DATAIN_C<19:12>
    ##WriteReg(0x46,0x46,0x55)  ##test pattern for lane2 DATAIN_C<7:0>
    ##WriteReg(0x46,0x47,0x55)  ##test pattern for lane2 DATAIN_C<15:8>
    ##WriteReg(0x46,0x48,0x55)  ##test pattern for lane3 DATAIN_C<3:0>, lane2 DATAIN_C<19:16>
    ##WriteReg(0x46,0x49,0x55)  ##test pattern for lane1 DATAIN_C<11:4>
    ##WriteReg(0x46,0x4a,0x55)  ##test pattern for lane1 DATAIN_C<19:12>

    WriteReg(0x46,0x41,0x54)  ##test pattern for lane0 DATAIN_C<7:0>
    WriteReg(0x46,0x42,0xe2)  ##test pattern for lane0 DATAIN_C<15:8>
    WriteReg(0x46,0x43,0xee)  ##test pattern for lane1 DATAIN_C<3:0>, lane0 DATAIN_C<19:16>
    WriteReg(0x46,0x44,0x54)  ##test pattern for lane1 DATAIN_C<11:4>
    WriteReg(0x46,0x45,0xe2)  ##test pattern for lane1 DATAIN_C<19:12>
    WriteReg(0x46,0x46,0xee)  ##test pattern for lane2 DATAIN_C<7:0>
    WriteReg(0x46,0x47,0x54)  ##test pattern for lane2 DATAIN_C<15:8>
    WriteReg(0x46,0x48,0x22)  ##test pattern for lane3 DATAIN_C<3:0>, lane2 DATAIN_C<19:16>
    WriteReg(0x46,0x49,0xee)  ##test pattern for lane1 DATAIN_C<11:4>
    WriteReg(0x46,0x4a,0x54)  ##test pattern for lane1 DATAIN_C<19:12>

    ####output PRBS7 from FPGA
##    WriteReg(0x46,0x15,0x80)  ##enable TXPLL TESTCK(FB_CK) output
    ##WriteReg(0x46,0x30,0x20)  ##select TXPLL TESTCK(FB_CK) output from VD_CK pin
    WriteReg(0x46,0x30,0x10)  ##select Link clk output from VD_CK pin

    ##PIO setting
    WriteReg(0x46,0x4c,0xff)  ##turn on EDVO
    WriteReg(0x46,0x4d,0xff)  ##turn on EDVO
    WriteReg(0x46,0x4f,0x08)  ##DLL always bypass
    WriteReg(0x46,0x54,0x93)  ##sel_PIO and set EDVO_CK_POL=1

    WriteReg(0x46,0x1b,0x00)  ##TXPLL on

    ##------TXPLL LC bist---------------------------------
    if(LC_BIST_SELECT=='ENABLE'):
        WriteReg(0x46,0x20,0x16)  ##set LC bist low frequency band boundary
        WriteReg(0x46,0x1b,0x40)  ##enable LC bist
        sleep (0.1)
        vala1=ReadReg(0x46,0xc1)
        BIST_DONE   =(vala1&0x20) >> 5  
        BIST_FAIL   =(vala1&0x40) >> 6 
        print ''
        print 'TXPLL LC BIST DONE = 0x%02X' %BIST_DONE
        print 'TXPLL LC BIST FAIL = 0x%02X' %BIST_FAIL
        print ''
    if(LC_BIST_SELECT=='DISABLE'):
        print ''

    ##------TXPLL LC frequency test---------------------------------
    if(LC_TEST_SELECT=='ENABLE'):
        WriteReg(0x46,0x54,0x11)  ##power down PIO,disable input HDCK
        WriteReg(0x46,0x1a,0x80)  ##set HDMI mode with 8-bit color-depth
        WriteReg(0x46,0x1c,0x80)  ##enable register setting for DIV and BAND
        WriteReg(0x46,0x1d,0x00)  ##register setting for post divider    
        WriteReg(0x46,0x1e,0x00)  ##register setting for LC BAND
        WriteReg(0x46,0x1b,0x20)  ##force SET_VCO_LO=1

        print ''
    if(LC_TEST_SELECT=='DISABLE'):
        print ''

        
    #---------Loop back to TS_OP----------------------------------

    if(TS_OP_SELECT=='HSCKP'):
        WriteReg(0x46,0x2c,0x03)    ##
        print 'TXPLL HSCKP is loop back to TS_OP.'


    ##LOOP3=0
    ##while (LOOP3<1):
    ##    vala4=ReadReg(0x18,0xa4)
    ##    CDR_TUDN    =(vala4&0x0f) 
    ##
    ##    valb3=ReadReg(0x18,0xb3)
    ##    CDR_RFD_LOSS=(valb3&0xf0) >> 4
    ##
    ##    valb1=ReadReg(0x18,0xb1)
    ##    CDR_FLOCK   =(valb1&0xf0) >> 4  
    ##    CDR_PHASE_LOCK   =(valb1&0x0f)  
    ##    print ''
    ##    print 'CDR_TUNE_DONE after PHY_ON is 0x%02X' %CDR_TUDN
    ##    print 'CDR RFD  LOSS after PHY_ON is 0x%02X' %CDR_RFD_LOSS
    ##    print 'CDR FREQ  LOCK after PHY_ON is 0x%02X' %CDR_FLOCK
    ##    print 'CDR PHASE LOCK after PHY_ON is 0x%02X' %CDR_PHASE_LOCK 
    ##    print ''
    ##    LOOP3=LOOP3+1

    sleep (0.1)

    valc0=ReadReg(0x46,0xc0)
    valc1=ReadReg(0x46,0xc1)
    valc3=ReadReg(0x46,0xc3)

    print 'P4.c0 (TXPLL status) is 0x%02X' %valc0
    print 'p4.c0[7:0]=[CALIB OK][CALIB FAIL][CALIB DONE][DIVIDER<4:0>]'
    print 'P4.c1 (TXPLL status) is 0x%02X' %valc1
    print 'p4.c1[7:0]=[close loop enable][BIST FAIL][BIST DONE][LC BAND<4:0>]'
    print 'P4.c3 (TXPLL status) is 0x%02X' %valc3
    print 'p4.c3[0]=[TXPLL lock]'

def board_init():
    UsbFuncInit()

    SelectDP825SourceFPGA()
    WriteReg(0x14,0x21,0x07)  ##Reset DP570_2 and DP570_3
    sleep(0.01)
    WriteReg(0x14,0x21,0x04)  ##Unreset
    sleep(0.01)

    SelectDP825SourceDP570_0()
    print 'DP570_0\n'
    set_freq()

    SelectDP825SourceDP570_1()
    print 'DP570_1\n'
    set_freq()

    SelectDP825SourceFPGA()
    WriteReg(0x14,0x21,0x00)   ##WCK Unreset
    WriteReg(0x14,0x21,0x08)   ##LCLK OUT_EN
