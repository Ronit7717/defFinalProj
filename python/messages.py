import sqlite3


class Message:
    conn = sqlite3.connect('server.db')
    c=conn.cursor()
    def __init__(self,cid):
        self.cid = cid

    def getAllMessages(self):
        try:
            messagesList = []
            sqlList=self.c.execute('''SELECT fromClient, ID, type,280 , content FROM messages WHERE ToClient=?''',(self.cid,))
            res=sqlList.fetchall()
            for message in res:
                fixing = []
                fixing.append(message[0].encode())
                fixing.append(message[1])
                fixing.append(message[2].encode())
                fixing.append(message[3])
                fixing.append(message[4].encode())
                fixTuple = tuple(fixing)
                messagesList.append(fixTuple)
            return (1004,(messagesList,))
        except Exception:
            return (9000,'could not get messages list')

    def sendMessage(self,name,type,content):
        if type<1 or type>4:
            return (9000,'wrong type')
        if type==1:
            content='Request for symmetric key'
        try:
            toClient = self.c.execute('''SELECT ID FROM clients where  uname=?''',(name,))
            self.c.execute('''INSERT INTO messages (ToClient, FromClient, Type ,Content) values (?,?,?,?)''',(clientId,self.cid,type,content,))
            self.c.commit()
            messageId=self.c.lastrowid
            return (1003,(clientId,messageId))
        except Exception:
            return (9000,'the message was not saved')

        

