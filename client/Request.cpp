#include "Payload2.cpp"
using namespace std;
class Request
{
private:
    int clientId;
    int version;
    int code;
    int payloadSize;
    Payload2 *p = new Payload2("dd", 99);
public:
    Request(int clientId, int version, int code, int payloadSize){
    this->clientId = clientId;
    this->version = version;
    }
    Request(int clientId, int version, int code, int payloadSize,Payload2 *p ){
    this->clientId = clientId;
    this->version = version;
    this->code = code;
    this->payloadSize = payloadSize;
    this->p= p;

    }
    Request(){

    }
    ~Request();
};

