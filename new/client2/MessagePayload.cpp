using namespace std;
#include <iostream>

class MessagePayload
{
private:
    char clientId[16];
    int messageType;
    int contentSize;
    char message[255];
public:
    
       void setClientId(char clientId[16]){
        for (int i = 0; i < 16; i++)
        {
             this->clientId[i] = clientId[i];
        }
        }



    void setTextMessage(char text[255]){
        int i = 0;
         for (i; i < 255; i++)
        {
             this->message[i] = text[i];
        }
         this->message[i] = '\0';
    }

    int getPayloadSize (){
        return 255;
        }
    void setPayloadSize (){
         this->contentSize= 255;
        }
    void setMessageType (int messageType){
         this->messageType= messageType;
        }


    MessagePayload(/* args */);
    ~MessagePayload();
};

