using namespace std;
#include <iostream>

class MessagePayload
{
private:
    char clientId[16];
    int messageType;
    char contentSize[16];
    string message;
public:
    MessagePayload(/* args */);
    ~MessagePayload();
};

