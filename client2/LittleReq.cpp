
#include <iostream>

using namespace std;
class LittleReq
{
private:
    char name[16];
    char version;
    char code;
    int payloadSize;
public:
  

 LittleReq(){
      
    }
    void setName(char name[16]){
        for (int i = 0; i < 16; i++)
        {
             this->name[i] = name[i];
        }
    
    }
    void setVersion(char version){
        this->version = version;    
    }

    void setCode(char code){
        this->code = code;    
    }

     void setPayloadSize(int payloadSize){
        this->payloadSize = payloadSize;    
    }
    
    
    ~LittleReq();
};


