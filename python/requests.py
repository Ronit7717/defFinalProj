from users import Users
class Requests:

#     def __init__(self, req):
#         self.req = req
    def __init__(self, cId, vrsn,code,payloadSize,payload):
        self.clientId = cId
        self.version = vrsn
        self.code = code
        self.pSize = payloadSize
        self.payload = payload



    # def __str__(self):
    #      return self.req

    def reqAction(self):
        if self.code == '100':
            # u = Users()
            # newUser = u.createUser(self.payload['name'],self.payload['pKey'])
            # print('the new user is' ,self.payload['name'],self.payload['pKey'],newUser )
            pass
            
        else:
            print('hey')
            # here there must be self.clientId
            

        # other codes should give exist uName for every request




# 1) Register
# 2) Request for clients list
# 3) Request for public key
# 4) Request for waiting messages     
# 5) Send a text message
# 51) Send a request for symmetric key
# 52) Send your symmetric key
# 0) Exit client
        
