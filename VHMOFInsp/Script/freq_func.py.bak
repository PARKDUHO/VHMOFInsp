##log
## 20200401: fix typo line201: reg_frac.append(((val<<2) & 0xfc) | (Reg_Setting[0x25] & 0x3))

import os
import math

EEPROM_ADDR = 0x40

qpll = 1
div = 4
fb_div = 80

com_key = []
com_line = []
com_val = []
com_cnt = 0
chl_key = []
chl_line = []
chl_val = []
chl_cnt = 0

com_bitset = []
com_addr = []
chl_bitset = []
chl_addr = []

##link_rate = 1080+54*140     ##1080+54*N valid
def Get_Parameter(link_rate):    
    global qpll
    global div
    global fb_div

    global com_key
    global com_line
    global com_val
    global com_cnt
    
    global chl_key
    global chl_line
    global chl_val
    global chl_cnt

    global com_bitset
    global com_addr
    global chl_bitset
    global chl_addr
   
    fp_set = open('freq_set.txt')
    set_lines = fp_set.readlines()
    fp_set.close()

    length = len(set_lines);

    find = False
    for i in range(length):
        if set_lines[i].startswith('g_'+str(link_rate)+'_start'):
            find = True
            break
    if(not find):
        print 'Freq not find.'
        return

    seg = set_lines[i+1].strip().split(' ')
    qpll = int(seg[1])
    div = int(seg[2])
    fb_div = int(seg[3])

    chl_line = []
    chl_key = []
    chl_val = []
    com_line = []
    com_key = []
    com_val = []

    for j in range(i+3,length):
        if set_lines[j].find('chl_end') != -1:
            break
        chl_line.append(set_lines[j])

    for k in range(j+2,length):
        if set_lines[k].find('com_end') != -1:
            break
        com_line.append(set_lines[k])

##    print com_line
##    print chl_line
    com_cnt = len(com_line)
    for i in range(com_cnt):
        l = com_line[i].strip()[1:]
        p = l.find(' ')
        com_key.append(l[:p])

        p = l.find('(')
        p2 = l.find(')',p)
        val_s = l[p+1:p2].strip()
        p = val_s.find('\'b')
        if p != -1: val = int(val_s[p+2:],2)
        else:
            p = val_s.find('\'h')
            if p != -1: val = int(val_s[p+2:],16)
            else: val = int(val_s)
        com_val.append(val)

    chl_cnt = len(chl_line)
    for i in range(chl_cnt):
        l = chl_line[i].strip()[1:]
        p = l.find(' ')
        chl_key.append(l[:p])

        p = l.find('(')
        p2 = l.find(')',p)
        val_s = l[p+1:p2].strip()
        p = val_s.find('\'b')
        if p != -1: val = int(val_s[p+2:],2)
        else:
            p = val_s.find('\'h')
            if p != -1: val = int(val_s[p+2:],16)
            else: val = val = int(val_s)
        chl_val.append(val)

    fp = open('DRP.txt')
    lines = fp.readlines()
    fp.close()

    com_bitset = [[] for i in range(com_cnt)]
    com_addr = [0 for i in range(com_cnt)]
    chl_bitset = [[] for i in range(chl_cnt)]
    chl_addr = [0 for i in range(chl_cnt)]
    for l in lines:
        l = l.strip()
        if l.startswith('#') or l.startswith('//'):
            continue

        p = l.find('h ')
        addr = int(l[:p],16)
        p = l.find('[',p)
        p2 = l.find(']',p)
        bitset = l[p+1:p2].split(':')
        if len(bitset) == 1:
            bitset = [int(bitset[0]), int(bitset[0])]
        else:
            bitset = [int(bitset[0]), int(bitset[1])]

        for j in range(com_cnt):
            p = com_key[j].find('_',6)
            seg = l.split(' ')
            if com_key[j][p+1:] in seg:
                com_addr[j] = addr
                com_bitset[j] = bitset

        for j in range(chl_cnt):
            p = chl_key[j].find('_',6)
            seg = l.split(' ')
            if chl_key[j][p+1:] in seg:
                chl_addr[j] = addr
                chl_bitset[j] = bitset

#########################################################################################
from subfunc import  *

#UsbFuncInit(1)

#SelectDP855SourceFPGA()
##SelectDP855SourceFPGA()

####VCO 2.7G, CLK 135M
Reg_Setting = [
0x61, 0xF3, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFD, 0xC0, 0x00, 0xB6, 0xB4, 0x92,
0xE0, 0xCC, 0x81, 0x80, 0x00, 0x03, 0x8C, 0x06, 0x40, 0x00, 0x00, 0x00, 0x9F, 0xFF, 0xE8, 0x80,
0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xA0, 0x00,
0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x01, 0x40, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
0x63, 0x01, 0x23, 0x01, 0xBB, 0x00, 0xBB, 0x00, 0xFC, 0xE4]

def Init_Chip():
    cnt = len(Reg_Setting)
    ##Enable SCL1 and SCL2 Output
    WriteReg(EEPROM_ADDR,0x03,0x3)
    
    ##Initial CHIP
    BurstWrite(0xd4,0x00,cnt,Reg_Setting)

    ##Forces VCO band calibration manually. Needs to be toggled from 0 to 1 to activate the VCO calibration. 
    WriteReg(0xd4,0x1c,Reg_Setting[0x1c] & 0x7f)
    WriteReg(0xd4,0x1c,Reg_Setting[0x1c] | 0x80)

def Set_OD1(chip,f):
    global Reg_Setting
    if chip == 0x1: WriteReg(EEPROM_ADDR,0x03,0x2)
    else: WriteReg(EEPROM_ADDR,0x03,0x1)

    VCO = 2700.0               ##2.7G
    div = VCO/2/f
    val = int(div)>>4
    reg_int = [val]
    val = Reg_Setting[0x2e] & 0x0f | ((int(div)<<4) & 0xf0)
    reg_int.append(val)
    BurstWrite(0xd4,0x2d,2,reg_int)
    val = int(2**24 * (div - int(div)))
    reg_frac = [val>>22]
    reg_frac.append((val>>14) & 0xff)
    reg_frac.append((val>>6) & 0xff)
    reg_frac.append(((val<<2) & 0xfc) | (Reg_Setting[0x25] & 0x3))
    BurstWrite(0xd4,0x22,4,reg_frac)
##    print reg_int,reg_frac

def GTH_TX_Reset(link):
    ##TX Reset
    if link == 0:
        WriteReg(EEPROM_ADDR,0x01,0x01)
    elif link == 1:
        WriteReg(EEPROM_ADDR,0x01,0x02)
    else:
        WriteReg(EEPROM_ADDR,0x01,0x03)
    WriteReg(EEPROM_ADDR,0x01,0x00)

def DRP_READ(link, addr, com=0):
    link &= 1
    com &= 1

    wr_data = [0 for i in range(5)]
    wr_data[0] = addr & 0xff
    wr_data[1] = (addr>>8) & 0xff
    if com == 1:
        if(link == 0):
            wr_data[4] = 0x1
        else:
            wr_data[4] = 0x2
    else:
        if(link == 0):
            wr_data[2] = 0x1
        else:
            wr_data[3] = 0x1
    BurstWrite(EEPROM_ADDR,0x72,5,wr_data)
    rd_data = BurstRead(EEPROM_ADDR,0x77+com*4+link*2,2)
    val = rd_data[0] + rd_data[1]*256
    
    return val

def DRP_WRITE(link, addr,data, com=0):
    link &= 1
    com &= 1

    wr_data = [0 for i in range(7)]
    wr_data[0] = data & 0xff
    wr_data[1] = (data>>8) & 0xff
    wr_data[2] = addr & 0xff
    wr_data[3] = (addr>>8) & 0xff
    if com == 1:
        if(link == 0):
            wr_data[6] = 0x5
        else:
            wr_data[6] = 0xa
    else:
        if(link == 0):
            wr_data[4] = 0xff
        else:
            wr_data[5] = 0xff
    BurstWrite(EEPROM_ADDR,0x70,7,wr_data)

def TX_DRP(link):
    link &= 1
    if(qpll == 0):
        txpllclksel = 0x3
    else:
        txpllclksel = 0x2
    if(link == 0):
        WriteReg(EEPROM_ADDR,0x4a,txpllclksel)
    else:
        WriteReg(EEPROM_ADDR,0x5a,txpllclksel)

    for i in range(com_cnt):
        val = DRP_READ(link,com_addr[i],1)
##        print val
        mask = (0xffff>>(15-com_bitset[i][0]+com_bitset[i][1])) << com_bitset[i][1]
        if com_key[i].endswith('_FBDIV'):
            wr_val = com_val[i] - 2
##            print com_val[i],wr_val,'FBDIV'
        else:
            wr_val = com_val[i]
        val = val & (~mask) | (wr_val<<com_bitset[i][1])
        DRP_WRITE(link,com_addr[i],val,1)

    for i in range(chl_cnt):
        val = DRP_READ(link,chl_addr[i],0)
##        print val
        mask = (0xffff>>(15-chl_bitset[i][0]+chl_bitset[i][1])) << chl_bitset[i][1]
        if chl_key[i].endswith('TXOUT_DIV'):
##            wr_val = int(math.log(chl_val[i],2))
            wr_val = int(math.log(div,2))      ##Manual
##            print chl_val[i],wr_val,'TXOUT_DIV Log'
        else:
            wr_val = chl_val[i]
        val = val & (~mask) | (wr_val<<chl_bitset[i][1])
        DRP_WRITE(link,chl_addr[i],val,0)

    ####10.0  20.0  40.0  80.0
    TX_PROGDIV = [57760,57762,57766,57743]
    TX_PROGDIV_CFG_ADDR = 0x003e
    DRP_WRITE(link,TX_PROGDIV_CFG_ADDR,TX_PROGDIV[int(math.log(div,2))],0)

def Link_Setup(link, link_rate):
    link &= 1
    Get_Parameter(link_rate)
    refclk = float(link_rate)*div/fb_div
##    Set_OD1(link, refclk)
##    TX_DRP(link)
##    GTH_TX_Reset(link)
    ## 2020/5/27 add QPLL reset to enhance QPLL stability
    WriteReg(EEPROM_ADDR,0x01,0x01<<(link+4))    ##QPLL RESET
    Set_OD1(link, refclk)
    TX_DRP(link)
    WriteReg(EEPROM_ADDR,0x01,0x0)    ##UNRESET
    WriteReg(EEPROM_ADDR,0x01,0x01<<(link+2))    ##TXDATAPATH RESET
    WriteReg(EEPROM_ADDR,0x01,0x0)    ##UNRESET


##Init_Chip()
##
##link = 0
##link_rate = 5400
##Link_Setup(link, link_rate)
##print 'link%d, qpll%d, link_rate = %dMHz, lclk = %fMHz'%(link,qpll,link_rate,link_rate/40.0)
