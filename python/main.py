import socket
from CreateTables import CreateTables
from requests import Requests
import os.path
from os import path
import sqlite3
import time

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
            data = conn.recv(1024)
            text = data.decode("utf-8")
            pld = {'name':"momy",'pKey':"15151515"}
            r = Requests('no',2,'100',2,pld)
            cid = r.reqAction()
            print("the cid from main ",cid)
            r2 = Requests(cid[0],2,'101',2,pld)
            r2.reqAction()
            print("Enter message ")
            reply = input()
            replydata = bytearray(reply, "utf-8")
            newdata = bytearray(1024)
            for i in range(min(len(replydata), len(newdata))):
                newdata[i] = replydata[i]
            conn.sendall(newdata)
    conn.close()
