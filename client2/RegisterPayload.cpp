#include "Payload.cpp"

#include <iostream>

using namespace std;
class RegisterPayload: public Payload
{
private:
    string name[8];
    string publicKey;
public:
    RegisterPayload(string name[8], string publicKey){
        for (int i = 0; i < 8; i++)
        {
            this->name[i] = name[i];
        }
        
        this->publicKey = publicKey;
    }

 RegisterPayload(string name[8]){
      
    }

    
    ~RegisterPayload();
};


