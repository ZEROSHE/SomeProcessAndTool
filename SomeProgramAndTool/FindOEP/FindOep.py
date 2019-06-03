for seg in Segments():
    if idc.SegName(seg)=='.text':
        ea = idc.SegStart(seg)
        eaend = idc.SegEnd(seg)
        print('%x,%x' %(ea,eaend))
        while(ea < eaend):
            ea=idc.FindBinary(ea, SEARCH_NEXT|SEARCH_DOWN, '0xE8', radix=16)   
            finde9 = ea+5
            if idc.Byte(finde9) == 0xE9:
                print('E9 = %x' %ea)
        print('over')
        break