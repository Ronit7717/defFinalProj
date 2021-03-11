from users import Users
import sqlite3
import sys
import struct

class Requests:

#     def __init__(self, req):
#         self.req = req
    def __init__(self, req,payload):
        self.clientId = req[0].decode()
        self.clientId = self.clientId.rstrip('\x00')
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
        if self.code == 100 :
            print('the code is 100')
            name=self.payload[0].decode()
            name=name.rstrip('\x00')
            pKey=self.payload[1].decode()
            pKey=pKey.rstrip('\x00')
            print(name,pKey)
            newUser = u.createUser(name,pKey)
            if newUser[0]!=9000:
                print('the new user is',name,pKey,newUser[1] )
                packpayload=self.buildReturnPayload(newUser[1],'16s', 16)
                packheader = self.buildReturnHeader(newUser[0],packpayload[0])
                return (packheader,packpayload[1],0)# 0 is the code when the payload don't contain array
            else:
                packheader = self.buildReturnHeader(newUser[0],0)
                return (packheader,)
        
        elif self.code == 101:
            print(self.pSize)
            if self.pSize == 0:
                print("request - get all users")
                listOfUsers = u.getUsersList()
                if listOfUsers[0]!=9000:
                    pldContent=listOfUsers[1]
                    packpayload=self.buildReturnPayloadArr(pldContent[0],'16s255s')
                    print('pldContent ',pldContent)
                    packheader = self.buildReturnHeader(listOfUsers[0],packpayload[0])
                    return (packheader,packpayload[1],1)
                else:
                    packheader = self.buildReturnHeader(listOfUsers[0],0)
                    return (packheader,)

            else:
                packheader=self.buildReturnHeader(9000,0)
                return (packheader,)
                # return (9000, 'psize should be 0')
           
                
        elif self.code == 102:
            print('request - get public key')
            cid = self.payload[0].decode()
            cid = cid.rstrip('\x00')
            publicKey = u.getPublicKey(cid)
            # returnValue = buildReturnObject(publicKey,'16s160s')
            if publicKey[0]!=9000:
                packpayload=self.buildReturnPayload(publicKey[1],'16s160s', 176)
                packheader = self.buildReturnHeader(publicKey[0],packpayload[0])
                return (packheader,packpayload[1],0)
            else:
                packheader = self.buildReturnHeader(publicKey[0],0)
                return (packheader,)



        elif self.code==103:
            print('req - send message')
            cid=self.payload[0].decode()
            cid=cid.rstrip('\x00')
            messageType=self.payload[1].decode()
            messageType=messageType.rstrip('\x00')
            size=self.payload[2].decode()
            size=size.rstrip('\x00')
            content=self.payload[3].decode()
            content=content.rstrip('\x00')
            sendMessage = u.sendMessage(cid,messageType,size,content)
            if sendMessage[0]!=9000:
                packpayload=self.buildReturnPayload(sendMessage[1],'16s160s', 176)#replace format
                packheader = self.buildReturnHeader(sendMessage[0],packpayload[0])
                return (packheader,packpayload)
            else:
                packheader = self.buildReturnHeader(sendMessage[0],0)
                return (packheader,)

        elif self.code==104:
            getMessages = u.getMessages()
            if getMessages[0]!=9000:
                packpayload=self.buildReturnPayload(getMessages[1][0][0],'16si1si255s', 280)#replace format
                packheader = self.buildReturnHeader(getMessages[0],packpayload[0])
                return (packheader,packpayload[1], 0)
            else:
                packheader = self.buildReturnHeader(getMessages[0],0)
                return (packheader,)


            
            # here there must be self.clientId
            

        # other codes should give exist uName for every request

    def buildReturnHeader(self,resCode,size=0):
        code=int(resCode)
        version=int(2)
        payloadSize=int(size)
        header=(version,code,payloadSize)
        # packedHeader = struct.Struct('bbi').pack(*header)
        packedHeader = struct.pack('BHI',version,code,payloadSize)

        
        return packedHeader

    def buildReturnPayload(self,pld,formt, payloadSize):
        #getsizeof payload or getsizeof packed payload
        packedPayload = struct.Struct(formt).pack(*pld)
        # payloadSize=sys.getsizeof(packedPayload)
        return (payloadSize,packedPayload)

    def buildReturnPayloadArr(self,pld,formt):
        ansArr=[]
        for i in pld:
            packedPayload = struct.Struct(formt).pack(*i)
            ansArr.append(packedPayload)
        payloadSize=pld.__len__()*271 #getsizeof payload or getsizeof packed payload
        return (payloadSize,ansArr)
            
        # build the object to return to the client maybe use struct.pack
        #answer header: version, code, payload size, payload




