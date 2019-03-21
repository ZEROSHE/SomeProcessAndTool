
#!/usr/bin/python
#coding:utf-8

import sys
import json
import time
import requests
# url = 'http://api.db-ip.com/v2/free/218.30.116.7'
# r = requests.get(url)
# dada = r.json()
# print(dada)


url = 'http://api.db-ip.com/v2/free/'
def checkIP(ip):
    r = requests.get(url+ip)
    json_data = r.json()
    if json_data[u"city"] != 0:
        # print("continentCode:" + json_data["continentCode"])
        # print("continentName:" + json_data["continentName"])
        # print("countryCode:" + json_data["countryCode"])
        # print("countryName:" + json_data["countryName"])
        # print("stateProv:" + json_data["stateProv"])
        # print("city:" + json_data["city"])
        return ("%s: %s-%s-%s-%s"%(ip,json_data["continentName"],json_data["countryName"],json_data["stateProv"],json_data["city"]))
    else:
        return ("%s+err"%ip)


if __name__ == "__main__":
    File = sys.argv[3]
    if File == "":
        File = 'ip.txt'
    FSrcHandle = open(File)
    ips = FSrcHandle.readlines()
    FSrcHandle.close()

    fDecHandle = open('ip-City.txt', 'w')
    for ip in ips:
        line = checkIP(ip.strip())
        if line:
            #print(line)
            fDecHandle.write(line+'\n')
        else:
            #print(line)
            fDecHandle.write(line+'\n')
            fDecHandle.close()
    print("OVER!")

