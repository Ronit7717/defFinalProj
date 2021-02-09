
#include <iostream>

using namespace std;
class Payload2
{
private:
    string name;
    int publicKey;
public:
    Payload2(string name, int publicKey){
        this->name = name;
        this->publicKey = publicKey;
    }
    ~Payload2();
};


