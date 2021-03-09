
import os
import sqlite3
import random
import time
import uuid 
from datetime import datetime
from messages import Message
import random, string


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
            # id = str(uuid.uuid4())
            id=''.join(random.choices(string.ascii_letters + string.digits, k=15))
            try:
                self.c.execute('''INSERT INTO clients (ID, UNAME, publicKey,LastSeen) values (?,?,?,?)''',(id,n,pKey,str(now)))  
                self.conn.commit()
                time.sleep(3)
                return (1000,(id.encode(),))
            except Exception:
                return (9000,'create user FAILED reason '+str(Exception))
                
        else:
            return (9000,"100 req - the user is already exist")

        

    def getUsersList(self):
        correctCid=self.isCidCorrect()
        if correctCid==False:
            return (9000,'no client id')
        print("in getUsersList")
        allUsersList=[]
        allUsers = self.c.execute('''SELECT ID,UNAME FROM clients''')
        print("our cid ",self.cid)
        for user in allUsers:
            if user[0]!=self.cid:
                fixing = [x.encode('utf-8') for x in user]
                fixTuple = tuple(fixing)
                allUsersList.append(fixTuple)
        return (1001,(allUsersList,))

    def getPublicKey(self, cid):
        correctCid=self.isCidCorrect()
        if correctCid==False:
            return (9000,'no client id')
        try:
            publicKeyValue = self.c.execute('''SELECT publicKey FROM clients WHERE ID=?''',(cid,))
            res = publicKeyValue.fetchall()
            if len(res)!=1:
                return (9000,"ERROR getting the user by client id")
            else:
                publicKey = [val for val in publicKeyValue]
                return (1002,(publicKey[0].encode(), cid.encode()))
        except Exception:
            print(Exception)
            return (9000,"could not ask for user's public key")

    def sendMessage(self, cid, messageType, contentSize, content):
        correctCid=self.isCidCorrect()
        if correctCid==False:
            return (9000,'no client id')
        try:
            type = int(messageType)
        except Exception:
            return(9000,'wrong type of message')
    
        m = Message(self.cid)
        res = m.sendMessage(cid,messageType,content)


        return res

    def getMessages(self):
        correctCid=self.isCidCorrect()
        if correctCid==False:
            return (9000,'no client id')
        m=Message(self.cid)
        messsgesList = m.getAllMessages()
        return messsgesList  

    def isCidCorrect(self):
        print(self.cid)
        cidd=self.cid
        isUserExist = self.c.execute('''SELECT * FROM clients WHERE ID=?''', (self.cid,) )
        res = isUserExist.fetchall()
        if len(res)!=1:
            return False
        return True


    




















#         c.execute(f"select password from users where id={id}")
