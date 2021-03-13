class ResponseMessageSent
{
private:
    char clientId[16];
    int messageId;
public:

char* getClientId(){
        return this->clientId;
    }
    int getMessageId(){
        return this->messageId;
    }


    ResponseMessageSent(/* args */);
    ~ResponseMessageSent();
};


