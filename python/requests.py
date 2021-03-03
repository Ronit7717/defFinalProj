from users import Users
import sqlite3

class Requests:

#     def __init__(self, req):
#         self.req = req
    def __init__(self, req,payload):
        self.clientId = req[0]
        # in case of req 100 no cid nedded
        self.version = req[1]
        self.code = req[2]
        self.pSize = req[3]
        self.payload=payload




    # def __str__(self):
    #      return self.req

    def reqAction(self):
        print("in reqAction")
        u = Users(self.clientId)
        print(self.code)
        print(self.code.strip()=='100')
        if self.code == 100 :
            print('the code is 100')
            name=self.payload[0].rstrip().decode("utf-8")
            pKey=self.payload[1].rstrip().decode("utf-8")
            newUser = u.createUser(name,pKey)
            if newUser[0]!=9000:
                print('the new user is',name,pKey,newUser[1] )
                return newUser
        
        elif self.code == 101:
            if self.pSize == 0:
                print("request - get all users")
                listOfUsers = u.getUsersList()
                return listOfUsers
            else:
                return (9000, 'psize should be 0')
                
        elif self.code == 102:
            print('request - get public key')
            cid=self.payload[0].rstrip().decode("utf-8")
            publicKey = u.getPublicKey(cid)
            #buildReturnObject()
            return publicKey


        elif self.code==103:
            print('req - send message')
            sendMessage = u.sendMessage(self.payload['cid'],self.payload['messageType'],self.payload['contentSize'],self.payload['content'])
            return sendMessage

        elif self.code==104:
            pass


            
            # here there must be self.clientId
            

        # other codes should give exist uName for every request

    def buildReturnObject(self,obj):
        pass
        # build the object to return to the client maybe use struct.pack
        #answer header: version, code, payload size, payload




# 1) Register
# 2) Request for clients list
# 3) Request for public key
# 4) Request for waiting messages     
# 5) Send a text message
# 51) Send a request for symmetric key
# 52) Send your symmetric key
# 0) Exit client
        
