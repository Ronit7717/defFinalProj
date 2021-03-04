import sqlite3


class Message:
    conn = sqlite3.connect('server.db')
    c=conn.cursor()
    def __init__(self,cid):
        self.cid = cid

    def getAllMessages(self):
        try:
            sqlList=self.c.execute('''SELECT * FROM messages WHERE ToClient=?''',(self.cid,))
            res=sqlList.fetchall()
            messagesList = [item for item in res]
            return (1004,messagesList)
        except Exception:
            return (9000,'could not get messages list')

    def sendMessage(self,clientId,type,content):
        try:
            self.c.execute('''INSERT INTO messages (ToClient, FromClient, Type ,Content) values (?,?,?,?)''',(clientId,self.cid,type,content,))
            self.c.commit()
            messageId=self.c.lastrowid
            return (1003,clientId,messageId)
        except Exception:
            return (9000,'the message was not saved')

    def getSimetricKey(self):
        pass

    def sendSymetricKey(self):
        pass

