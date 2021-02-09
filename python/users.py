import pyodbc
import os
import sqlite3
import random
import time
import uuid 

class Users:
    conn = sqlite3.connect('server.db') 
    c = conn.cursor()
    def __init__(self):
        pass
        # בדיקת תקינות על קלט שם המשתמש שהוא באסקי

    def getUser(self):
        pass

    def createUser(self,n,pKey):
        isUserExist = self.c.execute("SELECT * FROM tasks WHERE UNAME=?", (n,))
        res=isUserExist.fetchall()
        if len(res)==0:
            id = uuid.uuid1()
            try:
                self.c.execute('''INSERT INTO clients ( ID, UNAME, publicKey) values (id,n,pKey)''')  
                time.sleep(3)
                var = self.c.execute('''SELECT * FROM clients''')  
                for row in var:
                    print(row)
                return id
            except Exception:
                return 'create user FAILED reason '+str(Exception)
                
        else:
            return "the user is already exist"

        

    def getUsersList(self):
        pass






















#         c.execute(f"select password from users where id={id}")
