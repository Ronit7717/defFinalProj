#include <cstdlib>
#include <string>
#include <iostream>
#include "RegisterPayload.cpp"
#include "PublicKeyPayload.cpp"
// #include "Request.cpp"
#include "LittleReq.cpp"
#include <winsock2.h>
#include "boost/asio.hpp"
using  boost::asio::ip::tcp;
using namespace std;
void clear(char message[], int length){
    for (int i = 0; i< length; i++)
        message[i] = '\0';
    }

void printMenu(){
    std::cout << "MessageU client at your service." << "\n"<<
    "1) Register" << "\n"<<
    "2) Request for clients list" << "\n"<<
    "3) Request for public key" << "\n"<<
    "4) Request for waiting messages" << "\n"<<
    "5) Send a text message" << "\n"<<
    "51) Send a request for symmetric key" << "\n"<<
    "52) Send your symmetric key" << "\n"<<
    "0) Exit client" << "\n"<<
    "?" << "\n";
    }


std ::array<uint8_t, sizeof(LittleReq)> createRequest(char req[1024]){

    std ::array<uint8_t, sizeof(LittleReq) > buffer;
    auto* header = reinterpret_cast<LittleReq*>(buffer.data());  
    char a[16] = "y6a4567fghjcvbn";
    header->setClientId(a);
    header->setVersion(2);
    // Payload *p;


    switch((int)req[0]-'0') {
    case 1:
    {
     std::cout << "user is asking to register";           
        header->setCode(100);
        char name[255] = "64f3f63985f04beb81a0e43321880182\0";
        string publicKey = "user";
        RegisterPayload *p = new RegisterPayload(name, publicKey);
        header->setPayloadSize(sizeof(*p));
        // s.send(boost::asio::buffer(buffer));
//     std ::array<uint8_t, sizeof(RegisterPayload) > buffer2;
//     auto* header2 = reinterpret_cast<RegisterPayload*>(buffer2.data());
// header2->setName(name);
// header2->setPublicKey(publicKey);
        // s.send(boost::asio::buffer(buffer2));

        break;
    }
        
    case 2:
    {
        header->setCode(101);
        header->setPayloadSize(1600);
    
        break;
}
    case 3:
    {
        header->setCode(102);
        header->setPayloadSize(1600);
        break;
}

    case 4:
     {
        header->setCode(104);
        header->setPayloadSize(1600);
        break;
}
    case 5:
     {
         header->setCode(103);
        header->setPayloadSize(1600);
        break;
}
    case 51:
     {
        header->setCode(100);
        header->setPayloadSize(1600);
        break;
}
    case 52:
     {
        header->setCode(100);
        header->setPayloadSize(1600);
        break;
}
    case 0:
     {
        header->setCode(100);
        header->setPayloadSize(1600);
        break;
}
    };

    return buffer;
}    

createGeneralHeader(auto* header){
    char a[16] = "y6a4567fghjcvbn";
    header->setClientId(a);
    header->setVersion(2);
}


std ::array<uint8_t, sizeof(LittleReq) > header1(){
    std ::array<uint8_t, sizeof(LittleReq) > buffer;
    auto* header = reinterpret_cast<LittleReq*>(buffer.data());  
    createGeneralHeader(header);
    header->setCode(100);
    header->setPayloadSize(287);
    return buffer;
}

std ::array<uint8_t, sizeof(RegisterPayload) >  payload1(){
    std ::array<uint8_t, sizeof(RegisterPayload) > buffer;
    auto* header = reinterpret_cast<RegisterPayload*>(buffer.data());
    char name[255] = "64f3f63985f04beb81a0e43321880182\0";
    char publicKey[32] = "user";
    header->setName(name);
    header->setPublicKey(publicKey);
    return buffer;
}

std ::array<uint8_t, sizeof(LittleReq) > header2(){
    std ::array<uint8_t, sizeof(LittleReq) > buffer;
    auto* header = reinterpret_cast<LittleReq*>(buffer.data());  
    createGeneralHeader(header);
    header->setCode(101);
    header->setPayloadSize(0);
    return buffer;
}

std ::array<uint8_t, sizeof(LittleReq) > header3(){
    std ::array<uint8_t, sizeof(LittleReq) > buffer;
    auto* header = reinterpret_cast<LittleReq*>(buffer.data());  
    createGeneralHeader(header);
    header->setCode(102);
    header->setPayloadSize(16);
    return buffer;
}

std ::array<uint8_t, sizeof(PublicKeyPayload) >  payload3(){
    std ::array<uint8_t, sizeof(PublicKeyPayload) > buffer;
    auto* header = reinterpret_cast<PublicKeyPayload*>(buffer.data());
    char clientId[16] = "64b81a0e0182\0";
    header->setClientId(clientId);
    return buffer;
}



std ::array<uint8_t, sizeof(LittleReq) > header4(){
    std ::array<uint8_t, sizeof(LittleReq) > buffer;
    auto* header = reinterpret_cast<LittleReq*>(buffer.data());  
    createGeneralHeader(header);
    header->setCode(104);
    header->setPayloadSize(0);
    return buffer;
}


std ::array<uint8_t, sizeof(LittleReq) > header5(){
    std ::array<uint8_t, sizeof(LittleReq) > buffer;
    auto* header = reinterpret_cast<LittleReq*>(buffer.data());  
    createGeneralHeader(header);
    header->setCode(103);
    header->setPayloadSize(0);
    return buffer;
}


std ::array<uint8_t, sizeof(PublicKeyPayload) >  payload5(){
    std ::array<uint8_t, sizeof(PublicKeyPayload) > buffer;
    auto* header = reinterpret_cast<PublicKeyPayload*>(buffer.data());
    char clientId[16] = "64b81a0e0182\0";
    header->setClientId(clientId);
    return buffer;
}





int main(int argc, char* argv[])
{
        char name[255] = "64f3f63985f04beb81a0e43321880182\0";
        string publicKey = "user";
        RegisterPayload *p = new RegisterPayload(name, publicKey);
    const int max_length = 1024;
    try
    {
        if (argc != 3){
            std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
            return 1;
        }
        printMenu();

        boost::asio::io_context io_context;
        tcp::socket s(io_context);
        tcp::resolver resolver(io_context);
        boost::asio::connect(s, resolver.resolve(argv[1], argv[2]));
        
        for( ; ; ){
            std::cout << "Enter message: ";
            char request[max_length];
            clear(request, max_length);
            std::cin.getline(request, max_length);
            // std ::array<uint8_t, sizeof(LittleReq) > rrr =  createRequest(request);
            
           
            if((int)request[0]-'0' == 1){
            std ::array<uint8_t, sizeof(LittleReq) > header = header1();
            std ::array<uint8_t, sizeof(RegisterPayload) > payload = payload1();
            // char name[255] = "64f3f63985f04beb81a0e43321880182\0";
            // char publicKey[32] = "user";

            // std ::array<uint8_t, sizeof(RegisterPayload) > buffer2;
            // auto* header2 = reinterpret_cast<RegisterPayload*>(buffer2.data());
            // header2->setName(name);
            // header2->setPublicKey(publicKey);
            s.send(boost::asio::buffer(header));
            s.send(boost::asio::buffer(payload));
            std ::array<uint8_t, sizeof(LittleReq) > header1;
            s.receive(boost::asio::buffer(header1));
            auto* headerdd = reinterpret_cast<LittleReq*>(header1.data());


              int a = 9;
            }
            else if ((int)request[0]-'0' == 2){
            std ::array<uint8_t, sizeof(LittleReq) > header = header2();
              s.send(boost::asio::buffer(header));
              std ::array<uint8_t, sizeof(LittleReq) > header1;
              s.receive(boost::asio::buffer(header1));
              int a = 9;
              }
            else if ((int)request[0]-'0' == 3){
            std ::array<uint8_t, sizeof(LittleReq) > header = header3();
            std ::array<uint8_t, sizeof(PublicKeyPayload) > payload = payload3();
              s.send(boost::asio::buffer(header));
              s.send(boost::asio::buffer(payload));
               std ::array<uint8_t, sizeof(LittleReq) > header1;
              s.receive(boost::asio::buffer(header1));
              int a = 9;
              }

            else if ((int)request[0]-'0' == 4){
            std ::array<uint8_t, sizeof(LittleReq) > header = header4();
              s.send(boost::asio::buffer(header));
               std ::array<uint8_t, sizeof(LittleReq) > header1;
              s.receive(boost::asio::buffer(header1));
              int a = 9;
              }
            
            else if ((int)request[0]-'0' == 5){
            std ::array<uint8_t, sizeof(LittleReq) > header = header5();
            std ::array<uint8_t, sizeof(PublicKeyPayload) > payload = payload5();
              s.send(boost::asio::buffer(header));
              s.send(boost::asio::buffer(payload));
               std ::array<uint8_t, sizeof(LittleReq) > header1;
              s.receive(boost::asio::buffer(header1));
              int a = 9;
              }

            
            
            char reply[max_length];

        }
    } catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }
} 

