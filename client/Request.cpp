#include "Payload2.cpp"
using namespace std;
class Request
{
private:
    struct Header
    {
        uint8_t uid[16];
        uint8_t version;
        uint8_t code;
        uint32_t pSize;
        uint8_t payload[0];
    };

    int clientId;
    int version;
    int code;
    int payloadSize;
    Payload2 *p = new Payload2("dd", 99);

public:
    Request(int clientId, int version, int code, int payloadSize)
    {
        this->clientId = clientId;
        this->version = version;
    }
    Request(int clientId, int version, int code, int payloadSize, Payload2 *p)
    {
        this->clientId = clientId;
        this->version = version;
        this->code = code;
        this->payloadSize = payloadSize;
        this->p = p;
    }
    Request()
    {
    }
    /*this is for trials only*/
    Request(int code)
    {
        this->code = code;
    }

    ~Request();
};
