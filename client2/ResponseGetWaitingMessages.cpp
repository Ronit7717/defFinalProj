class ResponseGetWaitingMessages
{
private:
    char clientId[16];
    int messageId;
    char messageType;
    int messageSize;
    char content[255];
public:
 char* getClientId(){
        return this->clientId;
    }
     int getMessageId(){
        return this->messageId;
    }
     char getMessageType(){
        return this->messageType;
    }

     int getMessageSize(){
        return this->messageSize;
    }

    char* getContent(){
        return this->content;
    }




    ResponseGetWaitingMessages(/* args */);
    ~ResponseGetWaitingMessages();
};


