#include <cstdlib>
#include <cstring>
#include <iostream>
#include "Request.cpp"
#include "LittleReq.cpp"
#include <winsock2.h>
#include "boost/asio.hpp"
using  boost::asio::ip::tcp;
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
            header->setName(a);
            header->setVersion(2);
    switch((int)req[0]-'0') {
    case 1:
     std::cout << "user is asking to register";


           
            header->setCode(100);
            header->setPayloadSize(1600);


        break;
    case 2:
      std::cout << "user is asking for users list";
        break;

        // code block
       
    };

    return buffer;
}    

int main(int argc, char* argv[])
{

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
            std ::array<uint8_t, sizeof(LittleReq) > rrr =  createRequest(request);

           
      

         

         

            s.send(boost::asio::buffer(rrr));
            
            
            
            char reply[max_length];

        }
    } catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }
} 

