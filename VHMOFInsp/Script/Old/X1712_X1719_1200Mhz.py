# X1712 X1719 CDIC BERT Example Python Code
# 2020/05/26 v0

# In the example, TCON SPI Slave reg read/write functions are as below:
#
# self.rd(page,offset)
# self.wr(page,offset,data)
#
# where (page<<8+offset) => Larkspur TCON reg 2byte offset value

#===== CDIC BERT Function
def cdicBert(self, sleepDur = 30):
    ''' sleepDur is the test time '''
    result = {}

    # 1) Enable CDI VBERT
    self.wr(0x03, 0xf5, 0x0e) # Enable VBERT Pattern

    # 2) Set CDI read back parameters
    self.wr(0x19, 0x68, 0xa3) ## RGREAD_BIT_T[7:0]
    self.wr(0x19, 0x69, 0x02) ## RGREAD_BIT_T[15:8]
    self.wr(0x19, 0x6a, 0x51) ## RGREAD_SAMPLE[7:0]
    self.wr(0x19, 0x6b, 0x01) ## RGREAD_SAMPLE[15:8]

    # 3) Disable MBC monitoring
    self.wr(0x19, 0x6d, 0x45) ## Disable MBC monitoring

    # 4) clear errors
    self.wr(0x1a, 0x0b, 0xe3)
    self.wr(0x1a, 0x0b, 0x03) # Clears error

    # 5) Wait 
    self.sleep(sleepDur) 

    # 6) Read back data
    addr = 0x00
    length = 0x02

    self.wr(0x03, 0x90, 0x00) ####[7:2]0x00,read;0x01,readandclear;0x02,write, [1:0] RBS_ADDR[9:8]
    self.wr(0x03, 0x91, addr) ###[7:0] RBS_ADDR[7:0]
    self.wr(0x03, 0x92, length) ####[7:0] RBS_LEN

    for i in range(0, self.cdicCount): ## cdicCount = 8 for X1712, 7 for X1719
        cdicNameString = 'cdic' + str(i)
        self.wr(0x03, 0x93, 0x80 + i) ####[7] command valid [6] RBS data valid [3:0] CD_SEL
        self.sleep_ms(100)
        regValue = self.rd(0x03, 0x93)

        if ((self.rd(0x03, 0x93) & 0x40) == 0x40): ## Check RBS data valid
            lsb = self.rd(0x03, 0x98) # LSB
            msb = self.rd(0x03, 0x99) # MSB

            result.update({cdicNameString : msb << 8 | lsb})
        else :
            result.update({cdicNameString : -1})
            self.log("RBS data is not valid")

    # 7) Disable VBERT
    self.wr(0x03, 0xf5,0x00) # Disable VBERT Pattern

    self.log(result)

    return result

#===== Set TCON CDI Frequency
def cdicSetFrequency(self, Frequency) :
    '''Frequency: 1053 MHz - 1200 MHz'''
    self.wr(0x03, 0x61, 0x00) # Disable CDI Agile clocking
    self.wr(0x05, 0xb3, 0x04) # REG_ALPM_CMDSEL
    self.wr(0x0e, 0x3a, 0xb0) #
    self.wr(0x0e, 0x40, 0x02) # REG_CDPLL_START_SEL
    N = (float(Frequency) * 2) / 27 * 1024
    N_div = int(N)

    CDPLL_DIV_N_7_0 = N_div & 0xFF
    CDPLL_DIV_N_15_8 = (N_div & 0x0ff00) >> 8
    CDPLL_DIV_N_17_16 = (N_div & 0x030000) >> 16
    CDPLL_DIV_TAG_N = ((CDPLL_DIV_N_17_16 & 0x0f) << 4) | ((CDPLL_DIV_N_17_16) & 0x0f)

    Mask1 = self.rd(0x0e, 0x67, 1) & 0xfc
    # REG_PLL_CTRL6
    self.wr(0x0e, 0x48, CDPLL_DIV_N_7_0) # Cal0
    self.wr(0x0e, 0x49, CDPLL_DIV_N_15_8) # CALI0_VAL
    self.wr(0x0e, 0x58, CDPLL_DIV_TAG_N) #REG_PLL_CTRL10 REG_CDI_CALI0 & 1
    self.wr(0x0e, 0x65, CDPLL_DIV_N_7_0) # CDI PLL DIV
    self.wr(0x0e, 0x66, CDPLL_DIV_N_15_8)
    self.wr(0x0e, 0x67, Mask1 | CDPLL_DIV_N_17_16 | 0x80)
    self.wr(0x0f, 0x1a, 0x10) # CDIPLL cal enable
    self.wr(0x0f, 0x1b, 0x40)
    self.wr(0x0e, 0x40, 0x1b) # SW CDIPLL start
    self.sleep_ms(100)
    self.wr(0x0e, 0x40, 0x1f)

    return 0

#===== TCON Reg Masked Write Function
def wrMask(self, page, offset, value, mask):
    '''Write to register but keep masked bits intact. mask 0 to write bit, 1 to protect bit'''
    readValue = self.rd(page, offset, 1)
    maskedValue = ~mask & value
    readValue &= mask
    writeValue = maskedValue | readValue
    self.wr(page, offset, writeValue)
#===== Set TCON CDI Tx Jitter Frequency
def _cdicSetJitterFrequencyDiv_(self, div):
    '''div: 1,2'''
    self.wrMask(0x0f, 0x16, div << 4, 0x8f) # REG_RPIO [6:4] REG_NOS_CK_SEL
    return 0
#===== Set TCON CDI Tx Jitter Amplitude
def _cdicSetJitterAmplitude_(self, ampl):
    '''ampl : 1,2,3,4,5,6,7'''
    self.wrMask(0x0f, 0x16, ampl, 0xf8) # REG_RPIO [3:0] injection noise level
    return 0
#===== Enable CDI TCON Tx Jitter
def _cdicEnableJitterInjection_(self, enable):
    '''enable : 1: enable; 0: disable'''
    self.wrMask(0x0f, 0x16, enable << 3, 0xf7) # REG_RPIO[3] enable Vlpll noise injection
    return 0
#===== Combined TCON CDI Tx Jitter Function
def cdicJitterInjection(self, enable = 0, div = 1, ampl = 1):
    status = self._cdicSetJitterFrequencyDiv_(div) | self._cdicSetJitterAmplitude_(ampl) | self._cdicEnableJitterInjection_(enable) # Vlpll noise injection
    self.log("CDIC Jitter Injection Register: " + hex(self.rd(0x0f, 0x16)))
    return status


#===== Set CDIC EQ Band
def cdicSetEQ(self, band):
    '''
    eRVDS: band 0 (EQ off), 1 (-1dB); 2 (-2dB); 3 (-3dB); 4 (-4dB); 5 (-5dB); 6 (-6dB); 7 (-7dB)
        EQ[2][2:0]: Reg0x1A02[7:5]; EQ[1][2:0]: Reg0x1A02[4:2]; EQ[0][2:0]: Reg0x1A02[1:0] Reg0x1A01[7]
    '''
    if band in range(8):
        eq0 = band & 1
        eq1 = (band>>1) & 1
        eq2 = (band>>2) & 1
        ## 2nd bit inversion for PLL CDR
        eq0_2nd_bit_inv = eq0<<2 |(1-eq0)<<1 | eq0
        eq1_2nd_bit_inv = eq1<<2 |(1-eq1)<<1 | eq1
        eq2_2nd_bit_inv = eq2<<2 |(1-eq2)<<1 | eq2
        p1 = (self.rd(0x1a,0x01,1) & 0x7f) | ((eq0_2nd_bit_inv & 1)<<7) ## Reg0x1A01[7] is EQ[0]
        p2 = eq2_2nd_bit_inv<<5 | eq1_2nd_bit_inv<<2 | eq0_2nd_bit_inv>>1
        self.wr(0x1a,0x01,p1)
        self.wr(0x1a,0x02,p2)
    else:
        raise ValueError("invalid EQ band for eRVDS")
    return 0

#===== Set CDI Driver Current Level
def cdicSetCurrentDriver(self, current_driver):
    '''
    current_driver:
    3 : 5.2mA,
    2 : 3.9mA,
    1 : 2.6mA,
    0 : 1.3mA
    '''
    self.wrMask(0x0f, 0x00, current_driver << 5, 0x9f) # REG_RPIO[6:5] CDI current level
    self.log ("Set Current Driver: " + hex(self.rd(0x0f, 0x00)))
    return 0

#===== Set CDI Current Bias
def cdicSetBiasCurrent(self, bias_current):
    ''''bias_current 53, 56, 60, 63, 69, 72, 75, 50, 47, 44, 41, 38, 34, 31, 28'''
    if bias_current == 50:
        currentReg = 0x00

    elif bias_current == 47:
        currentReg = 0x11

    elif bias_current == 44:
        currentReg = 0x22

    elif bias_current == 41:
        currentReg = 0x33

    elif bias_current == 38:
        currentReg = 0x44

    elif bias_current == 34:
        currentReg = 0x55

    elif bias_current == 31:
        currentReg = 0x66

    elif bias_current == 28:
        currentReg = 0x77

    elif bias_current == 75:
        currentReg = 0x88

    elif bias_current == 72:
        currentReg = 0x99

    elif bias_current == 69:
        currentReg = 0xaa

    elif bias_current == 66:
        currentReg = 0xbb

    elif bias_current == 63:
        currentReg = 0xcc

    elif bias_current == 60:
        currentReg = 0xdd

    elif bias_current == 56:
        currentReg = 0xee

    elif bias_current == 53:
        currentReg = 0xff

    else :
        raise ValueError("Not acceptable bias current value")

    self.wr(0x0f, 0x02, currentReg) # CDI port0&1 bias current control
    self.wr(0x0f, 0x03, currentReg) # CDI port2&3 bias current control
    self.wr(0x0f, 0x04, currentReg) # CDI port4&5 bias current control
    self.wr(0x0f, 0x05, currentReg) # CDI port6&7 bias current control

    self.log ("Set Bias Current")
    self.log (hex(self.rd(0x0f, 0x02)))
    self.log (hex(self.rd(0x0f, 0x03)))
    self.log (hex(self.rd(0x0f, 0x04)))
    self.log (hex(self.rd(0x0f, 0x05)))

    return 0
    
cdicSetFrequency(1200)