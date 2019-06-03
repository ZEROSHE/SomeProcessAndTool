import os
import datetime
import json
import eml_parser
from xlwt import *

def Is_Exist(s1, key):
	a = key in s1
	if(a==0):
		return ""
	else:
		return key
		
def WriteData(tablehandle,filedata, i,j, key):
	if(Is_Exist(filedata,key)):
		tablehandle.write(i,j,filedata[key])
	else:
		tablehandle.write(i,j," ")


def json_serial(obj):
    if isinstance(obj, datetime.datetime):
        serial = obj.isoformat()
        return serial
#创建文件
datafilename = "F:\\github_bak\\MyWork\\2019-6-3\\data.xls"
datafile=Workbook(encoding='utf-8')
table=datafile.add_sheet('data')

#遍历文件
path = "F:\\github_bak\\MyWork\\2019-6-3\\123\\5269748959346688"
files = os.listdir(path)

table.write(0,0,"filename")
table.write(0,1,"attachment_hash")
table.write(0,2,"attachment_name")
table.write(0,3,"attachment_size")
table.write(0,4,"attachment_extension")
table.write(0,5,"header_subject")
table.write(0,6,"header_from")
table.write(0,7,"header_to")
table.write(0,8,"header_delivered_to")
table.write(0,9,"header_data")
table.write(0,10,"header_recv_email")
table.write(0,11,"header_recv_domain")
table.write(0,12,"header_recv_ip")
table.write(0,13,"header_recv_foremail")
raw = 1
col = 0

for file in files:
	if not os.path.isdir(file):
		print(file)
		with open(file, 'rb') as fhdl:
			raw_email = fhdl.read()
		parsed_eml = eml_parser.eml_parser.decode_email_b(raw_email)
		s = json.dumps(parsed_eml, default=json_serial)
		s1=json.loads(s)
		#将制定数据写入
		table.write(raw,col,file)
		#WriteData(table, file, raw,col,1)
		col = col + 1	
		if(Is_Exist(s1, "attachment")):
			WriteData(table, (((s1["attachment"])[0])["hash"]), raw,col, "md5")
			col = col + 1
			WriteData(table, ((s1["attachment"])[0]), raw,col,"filename")
			col = col + 1
			WriteData(table, ((s1["attachment"])[0]), raw,col,"size")
			col = col + 1
			WriteData(table, ((s1["attachment"])[0]), raw,col,"extension")
			col = col + 1
		else:
			col = col + 4
		if(Is_Exist(s1, "header") == 0):
			raw = raw+1
			col = 0
			continue
		WriteData(table, (s1["header"]), raw,col, "subject")
		col = col + 1
		WriteData(table, (s1["header"]), raw,col, "from")
		col = col + 1
		WriteData(table, (s1["header"]), raw,col, "to")
		col = col + 1
		# WriteData(table, (s1["header"])["delivered_to"], raw,col)
		# col = col + 1
		WriteData(table, (s1["header"]), raw,col,"date")
		col = col + 1
		# WriteData(table, (s1["header"])["received_email"], raw,col)
		# col = col + 1
		WriteData(table, (s1["header"]), raw,col,"received_domain")
		col = col + 1
		WriteData(table, (s1["header"]), raw,col,"received_ip")
		col = col + 1
		#WriteData(table, (s1["header"])["received_foremail"], raw,col)
		#print((((s1["attachment"])[0])["hash"])["md5"])
		raw = raw+1
		col = 0
datafile.save(datafilename)
print(datafilename)



