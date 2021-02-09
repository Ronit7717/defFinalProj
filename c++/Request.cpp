#include "Payload.cpp"

class Request
{
private:
    int clientId;
    int version;
    int code;
    int payloadSize;
    Payload payload;

public:
    Request(int clientId, int version, int code, int payloadSize, Payload payload){
    this->clientId = clientId;
    this->version = version;
    }
    ~Request();
};

