
import os
import sqlite3
import random
import time
import uuid 
from datetime import datetime
from messages import Message


class Users:
    conn = sqlite3.connect('server.db') 
    c = conn.cursor()
    def __init__(self,cid):
        self.cid=cid


    def createUser(self,n,pKey):
        now = datetime.now()
        isUserExist = self.c.execute("SELECT * FROM clients WHERE UNAME=?", (n,))
        print(isUserExist)
        res=isUserExist.fetchall()
        if len(res)==0:
            id = str(uuid.uuid4())
            try:
                self.c.execute('''INSERT INTO clients (ID, UNAME, publicKey,LastSeen) values (?,?,?,?)''',(id,n,pKey,str(now)))  
                self.conn.commit()
                time.sleep(3)
                return (1000,id)
            except Exception:
                return (9000,'create user FAILED reason '+str(Exception))
                
        else:
            return (9000,"100 req - the user is already exist")

        

    def getUsersList(self):
        if self.cid == None:
            return (9000,'no client id')
        print("in getUsersList")
        allUsersList=[]
        allUsers = self.c.execute('''SELECT ID,UNAME FROM clients''')
        print("our cid ",self.cid)
        for user in allUsers:
            if user[0]!=self.cid:
                allUsersList.append(user)
        return (1001,allUsersList)

    def getPublicKey(self, cid):
        try:
            publicKeyValue = self.c.execute('''SELECT publicKey FROM clients WHERE ID=?''',(cid,))
            res = publicKeyValue.fetchall()
            if len(res)!=1:
                return (9000,"ERROR getting the user by client id")
            else:
                publicKey = [val for val in publicKeyValue]
                return (1002,publicKey[0], cid)
        except Exception:
            print(Exception)
            return (9000,"could not ask for user's public key")

    def sendMessage(self, cid, messageType, contentSize, content):
        try:
            type = int(messageType)
        except Exception:
            return(9000,'wrong type of message')
    
        m = Message(self.cid)
        if messageType == 1:
            res = m.getSimetricKey(cid)
        
        elif messageType == 2:
            res = m.sendSymetricKey(cid)

        elif messageType == 3:
            res = m.sendMessage(cid)

        else:
            return (9000, 'message has wrong type')

        return (1003,res)

    def getMessages(self):
        m=Message(self.cid)
        messsgesList = m.getAllMessages()
        return messsgesList    


    




















#         c.execute(f"select password from users where id={id}")
