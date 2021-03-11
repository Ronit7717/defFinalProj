class ResponsePublicKey
{
private:
    char clientId[16];
    char publicKey[160];
public:

char* getClientId(){
        return this->clientId;
    }

    char* getPublicKey(){
        return this->publicKey;
    }

    ResponsePublicKey(/* args */);
    ~ResponsePublicKey();
};


