com_key = []
com_line = []

fp = open('cmp_com.txt')
lines = fp.readlines()
fp.close()

com_cnt = len(lines)
for i in range(com_cnt):
    l = lines[i].strip()
    p = l.find(' ')
    com_key.append(l[:p])

    p = l.find(':',p)
    com_line.append(int(l[p+1:]))

chl_key = []
chl_line = []

fp = open('cmp_chl.txt')
lines = fp.readlines()
fp.close()

chl_cnt = len(lines)
for i in range(chl_cnt):
    l = lines[i].strip()
    p = l.find(' ')
    chl_key.append(l[:p])

    p = l.find(':',p)
    chl_line.append(int(l[p+1:]))

fp = open('freq_param.txt')
freq_param_lines = fp.readlines()
fp.close()

fp_set = open('freq_set.txt', 'wt')
for l in freq_param_lines:
    seg = l.strip().split(' ')
    link_rate = int(seg[0])

    fn_com = 'freq_set/g_'+str(link_rate)+'/DP_TX_HBR3_40BIT_gthe3_common_wrapper.v'
    fn_chl = 'freq_set/g_'+str(link_rate)+'/DP_TX_HBR3_40BIT_gthe3_channel_wrapper.v'

    fp_com = open(fn_com)
    com_lines = fp_com.readlines()
    fp_com.close()

    fp_chl = open(fn_chl)
    chl_lines = fp_chl.readlines()
    fp_chl.close()

    fp_set.writelines('g_'+str(link_rate)+'_start\n')
    fp_set.writelines('\t'+l)
    fp_set.writelines('\tchl_start\n')
    for i in chl_line:
        fp_set.writelines('\t\t'+chl_lines[i])
    fp_set.writelines('\tchl_end\n')
    fp_set.writelines('\tcom_start\n')
    for i in com_line:
        fp_set.writelines('\t\t'+com_lines[i])
    fp_set.writelines('\tcom_end\n')

    
    fp_set.writelines('g_'+str(link_rate)+'_end\n')
fp_set.close()

