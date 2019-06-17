import os
import re
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

def Writeattachment(tablehandle, filedata, i,j):
	strname = ""
	strhash = ""
	strsize = ""
	strextension = ""
	## name
	  ## 是否存在filename key,只要存在就可有遍历
	if Is_Exist(filedata[0],"filename") != "":
		for dicts in filedata:
			for key1, val1 in dicts.items():
				##print(key1)
				if key1 == "filename" and val1 != "part-000":
					strname = strname + (dicts)["filename"] + " "
					strhash = strhash + dicts["hash"]["md5"]+" "
					strsize = strsize + str(dicts["size"])+" "
					#strextension = strextension + dicts["extension"]+" "
	tablehandle.write(i,j,strname)
	j = j + 1
	tablehandle.write(i,j,strhash)
	j = j + 1
	tablehandle.write(i,j,strsize)
	j = j + 1
	#tablehandle.write(i,j,strextension)
	
		
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
datafilename = "F:\\github_bak\\MyWork\\2019-06-14\\data.xls"
datafile=Workbook(encoding='utf-8')
table=datafile.add_sheet('data', cell_overwrite_ok=True)

#遍历文件
path = "F:\\github_bak\\MyWork\\2019-06-14\\eml"
files = os.listdir(path)

table.write(0,0,"filename")
table.write(0,1,"attachment_name")
table.write(0,2,"attachment_hash")
table.write(0,3,"attachment_size")

table.write(0,4,"header_subject")
#table.write(0,5,"header_from")
table.write(0,5,"header_to")
table.write(0,6,"header_data")

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
		table.write(raw,0,file)
		#print(s1)
		#WriteData(table, file, raw,col,1)
		col = col + 1
		#普通邮件,有附件
		#特殊邮件
		#非邮件
		if(Is_Exist(s1, "attachment")):
			Writeattachment(table, ((s1["attachment"])),raw,col)
			col = col + 3
			WriteData(table, (s1["header"]), raw,col, "subject")
			col = col + 1
			WriteData(table, (s1["header"]["header"]), raw,col, "to")
			col = col + 1
			WriteData(table, (s1["header"]), raw,col,"date")
			raw = raw+1
			col = 0
		# 非邮件 特殊邮件
		elif(Is_Exist((s1["header"]["header"]), "to") == "" and Is_Exist((s1["header"]),"subject")):
			#按行读取邮件
			f = open(file, "r", encoding='UTF-8',errors='ignore')
			filename = ""
			filesize = ""
			line = f.readline()
			while line:
				# 截取需要的内容
				if(line[:3] == "To:"):
					
					#print(raw,col)
					table.write(raw,5,line[3:])
					col = col + 1
				if(line[:5] == "Date:"):
					table.write(raw , 6, line[5:])
					col = col + 1
					#print('data='+line[7:])
				if(line[:7] == "Subject"):
					table.write(raw , 4, line[8:])
					col = col + 1	
					#print('sub='+line[8:])					
				#附件的内容特殊
				if(line[:19]=="Content-Disposition"):
					##直接读取3行,在分割获取
					line = line + f.readline() + f.readline()
					strall = line.replace("\n","").split(";")
					num = len(strall)
					print(num)
					print(strall)
					p1 = re.compile(r'["](.*?)["]', re.S)
					if num >= 2:
						#print(re.findall(p1,strall[1]))
						if(re.findall(p1,strall[1]) != []):
							filename = filename + (re.findall(p1,strall[1]))[0] + " "
						else:
							filename = filename + (strall[1])[(strall[1].find("="))+1:] + " "
						#print(filename)
					if num >= 3:
						if(re.findall(p1,strall[2]) != []):
							filesize = filesize + (re.findall(p1,strall[2]))[0] + " "
						else:
							filesize = filesize + (strall[2])[(strall[2].find("="))+1: 7] + " "
						#print(filesize)
				line = f.readline()
			##完毕之后写入多个附件信息
			print(raw, col, filename)
			table.write(raw , 1, filename)
			col = col + 1
			print(raw,col,filesize)
			table.write(raw , 3, filesize)
			table.write(raw , 7, "****")
			raw = raw+1
			col = 0			
		
		else:
			pass
			
datafile.save(datafilename)
print(datafilename)



