import socket
from requests import Requests
import os.path
from os import path
import sqlite3
import time

if path.isfile('server.db'):
    os.remove("server.db")
    print ("File exist")
else:
    print ("File not exist")
    time.sleep(1)
    # CreateTables()


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
            pld = {'name':"hhhh",'pKey':"mypkey"}
            r = Requests(123,2,'100',2,pld)
            r.reqAction()
            print("Enter message ")
            reply = input()
            replydata = bytearray(reply, "utf-8")
            newdata = bytearray(1024)
            for i in range(min(len(replydata), len(newdata))):
                newdata[i] = replydata[i]
            conn.sendall(newdata)
    conn.close()
