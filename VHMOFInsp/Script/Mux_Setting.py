from subfunc import  *

#UsbFuncInit()

#SelectDP855SourceFPGA()

def Read_Mux_Reg(chip):
    if(chip == 0): Mux_Slave_Addr = 0x6          ##chip 0:0x6  1:0xe
    else: Mux_Slave_Addr = 0xe
    val = []
    for i in range(0x13):
        val.append(ReadReg(Mux_Slave_Addr,i))
    PrtListHex(val,16)

def Port_Switch(chip,port):
    if(chip == 0): Mux_Slave_Addr = 0x6
    else: Mux_Slave_Addr = 0xe
    if port == 0:    ##A
        WriteReg(Mux_Slave_Addr,0x01,0x0)
    elif port == 1:  ##B
        WriteReg(Mux_Slave_Addr,0x01,0xf)
    else:
        val = ReadReg(Mux_Slave_Addr,0x01)
        WriteReg(Mux_Slave_Addr,0x01,val^0xf)

####Invert on Input side
def Port_Invert(chip,port, mode):
    if(chip == 0): Mux_Slave_Addr = 0x6
    else: Mux_Slave_Addr = 0xe
    if port == 0:    ##A
        val = ReadReg(Mux_Slave_Addr,0x10)
        if mode == 1: val |= 0xf
        else: val &= 0xf0
        WriteReg(Mux_Slave_Addr,0x10,val)
    elif port == 1:  ##B
        val = ReadReg(Mux_Slave_Addr,0x10)
        if mode == 1: val |= 0xf0
        else: val &= 0x0f
        WriteReg(Mux_Slave_Addr,0x10,val)
    else:            ##C
        val = ReadReg(Mux_Slave_Addr,0x11)
        if mode == 1: val |= 0xf0
        else: val &= 0x0f
        WriteReg(Mux_Slave_Addr,0x11,val)

##AGC Input, VOD output
def Port_AGC_VOD(chip,port, agc, vod):
    if(chip == 0): Mux_Slave_Addr = 0x6
    else: Mux_Slave_Addr = 0xe
    val = agc & 0x01               ##0:0.5      1:1
    val |= ((~vod) & 0x1) << 4     ##0:600mV    1:1200mV
    if port != 0 and port != 1: port = 2
    WriteReg(Mux_Slave_Addr,0x04+port*4, val)
    
##EQ   0~7: 1.3dB   8: 2dB   9: 3.6dB   a: 5dB   b: 6.5dB   c: 8.3dB   d: 10dB   e: 11.9dB   f: 13.9dB
def Port_EQ(chip,port, eq):
    if(chip == 0): Mux_Slave_Addr = 0x6
    else: Mux_Slave_Addr = 0xe
    val = ReadReg(Mux_Slave_Addr,0x03+port*4)
    val = (val & 0xf0) | eq
    WriteReg(Mux_Slave_Addr,0x03+port*4, val)

def MUX_Init(chip):
    Port_Invert(chip,0,1)
    Port_Invert(chip,1,1)
    Port_AGC_VOD(chip,0, 1, 1)
    Port_AGC_VOD(chip,1, 1, 1)

#MUX_Init(0)
#MUX_Init(1)

##Read_Mux_Reg(0)
##Port_Switch(0,1)
