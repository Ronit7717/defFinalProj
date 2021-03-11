import socket
from CreateTables import CreateTables
from requests import Requests
import os.path
from os import path
import sqlite3
import time
import json
import struct

file_path='server.db'
if os.stat(file_path).st_size == 0:
    print("file empty server.db")
    CreateTables()

HOST = ''
with open('port.info') as port_reader:
    PORT = int(port_reader.read())
    print(type(PORT))
port_reader.close()


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        while True:
            data = struct.unpack('16sbbi',bytes(conn.recv(struct.calcsize('16sbbi'))))
            payload=''
            message_type=data[2]
            if message_type==100:
                payload=struct.unpack('255s32s', bytes(conn.recv(struct.calcsize('255s160s')))) 
            elif(message_type == 101):
                print("message is 101. No payload is needed")
            elif(message_type == 102):
                print("message is 102.")
                payload = struct.unpack('16s', bytes(conn.recv(struct.calcsize('16s'))))

            elif(message_type == 103):
                print("message is 102.")
                payload = struct.unpack('16s1si255s', bytes(conn.recv(struct.calcsize('16s1si255s'))))

            elif(message_type == 104): # user asks all witing messages
                print("message is 104.")
                


            req = Requests(data,payload)
            action=req.reqAction()
            print('the action ',action)
            conn.sendall(action[0])
            if(len(action)>1):
                if action[2]==0:
                    conn.sendall(action[1])
                elif action[2]==1:
                    for i in action[1]:
                        conn.sendall(i)
    conn.close()




            # data2 = conn.recv(1024)
            # text = data2.decode("utf-8")
            # reqBody = {'Client id':'123456789','Version':2, 'Code':'100','Payload Size':2,'payload':{'Name':'ronit in ascii','Public Key':'121212121'}}
            # #the next line is trial...
            # # pld = {'name':"rrr",'pKey':"1234567890"}
            # # r = Requests('no',2,'101',2,pld)
            # reaction = 'a'
            # # print("Enter message ")
            # if reaction:
            #     reply = reaction[0]
            # else:
            #     reply = 'no reply'
            # replydata = bytearray(reply, "utf-8")
            # newdata = bytearray(1024)
            # for i in range(min(len(replydata), len(newdata))):
            #     newdata[i] = replydata[i]
            # conn.sendall(newdata)
