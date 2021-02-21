from users import Users
class Requests:

#     def __init__(self, req):
#         self.req = req
    def __init__(self, cid, vrsn,code,payloadSize,payload):
        self.clientId = cid
        self.version = vrsn
        self.code = code
        self.pSize = payloadSize
        self.payload = payload



    # def __str__(self):
    #      return self.req

    def reqAction(self):
        print("in reqAction")
        u = Users(self.clientId)
        print(self.code)
        print(self.code.strip()=='100')
        if self.code == '100':
            print('the code is 100')
            newUser = u.createUser(self.payload['name'],self.payload['pKey'])
            if newUser!='the user is already exist':
                print('the new user is' ,self.payload['name'],self.payload['pKey'],newUser[0] )
            return newUser
        
        elif self.code == '101':
            print(u.cid)
            print("in get all users")
            listOfUsers = u.getUsersList()
            if(listOfUsers=="no users are exist"):
                return
            for user in listOfUsers:
                print("in list:",user)
                
        elif self.code == '102':
            u.getPublicKey(self.clientId)

        elif self.code=='103':
            pass

        elif self.code=='104':
            pass


            
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
        
