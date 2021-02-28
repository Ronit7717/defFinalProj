import pyodbc
import os
import sqlite3
import random
import time
import uuid 
from datetime import datetime


class Users:
    conn = sqlite3.connect('server.db') 
    c = conn.cursor()
    def __init__(self,cid):
        self.cid=cid

    def getUser(self):
        pass

    def createUser(self,n,pKey):
        now = datetime.now()
        isUserExist = self.c.execute("SELECT * FROM clients WHERE UNAME=?", (n,))
        print(isUserExist)
        res=isUserExist.fetchall()
        if len(res)==0:
            id = uuid.uuid4()
            try:
                self.c.execute('''INSERT INTO clients (ID, UNAME, publicKey,LastSeen) values (?,?,?)''',(str(id),n,pKey,str(now)))  
                self.conn.commit()
                time.sleep(3)
                return id,1000
            except Exception:
                return 'create user FAILED reason '+str(Exception)
                
        else:
            return "the user is already exist"

        

    def getUsersList(self):
        print("in getUsersList")
        allUsersList=[]
        allUsers = self.c.execute('''SELECT ID,UNAME FROM clients''')
        print("our cid ",self.cid)
        for user in allUsers:
            print(user[0])
            if user[0]!=self.cid:
                allUsersList.append(user)
        return allUsersList

    def getPublicKey(self, cid):
        try:
            publicKeyValue = self.c.execute('''SELECT publicKey FROM clients WHERE ID=?''',(cid,))
            res = publicKeyValue.fetchall()
            if len(res)==0:
                print("sorry, there is no user with this id")
                return
            elif len(res)>1:
                raise "ERROR. there is more than one user with this id"
            else:
                publicKey = [val for val in publicKeyValue]
                return publicKey
        except Exception:
            print(Exception)




















#         c.execute(f"select password from users where id={id}")
