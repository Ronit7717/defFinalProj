class ResponseHeader
{
private:
    char version;
    short code;
    int payloadSize;
public:

    char getVersion(){
        return this->version;
    }

    short getCode(){
        return this->code;
    }


    int getPayloadSize(){
        return this->payloadSize;
    }




    ResponseHeader(/* args */);
    ~ResponseHeader();
};
