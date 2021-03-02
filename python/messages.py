import sqlite3


class Message:
    conn = sqlite3.connect('server.db')
    def __init__(self,cid):
        self.cid = cid

    def getAllMessages(self):
        pass

    def sendMessage(self):
        pass

    def getSimetricKey(self):
        pass

    def sendSymetricKey(self):
        pass

