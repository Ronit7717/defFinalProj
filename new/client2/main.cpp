#include <cstdlib>
#include <string>
#include <iostream>
#include "RegisterPayload.cpp"
#include "PublicKeyPayload.cpp"
#include "LittleReq.cpp"
#include "boost/asio.hpp"
#include <iostream>
#include <fstream>
#include "ResponseUsersList.cpp"
#include "ResponsePublicKey.cpp"
#include "ResponseGetWaitingMessages.cpp"
#include "MessagePayload.cpp"
#include "ResponseHeader.cpp"

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

void getClientId(){
    string myText;
int i =0;
 ofstream myfile ("me.txt");
  if (myfile.is_open())
  {
    ifstream MyReadFile("me.txt");
    while (getline (MyReadFile, myText)) {
  // Output the text from the file
  std::cout << myText << "\n";
  i++;
  MyReadFile.close();
}

// Close the file


}
 int f = i;
}



void createGeneralHeader(auto* header){
    char a[16] = "wWqm1XlbrVvt1SP";
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
    char name[255] = "try1f63985f24ddb81a0e43321880182\0";
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
    char clientId[16] = "Qxn20JhYJ1AWttx";
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


std ::array<uint8_t, sizeof(LittleReq) > header5(int textSize){
    std ::array<uint8_t, sizeof(LittleReq) > buffer;
    auto* header = reinterpret_cast<LittleReq*>(buffer.data());  
    createGeneralHeader(header);
    header->setCode(103);
    header->setPayloadSize(textSize);
    return buffer;
}


std ::array<uint8_t, sizeof(MessagePayload) >  payload5(){
    std ::array<uint8_t, sizeof(MessagePayload) > buffer;
    auto* header = reinterpret_cast<MessagePayload*>(buffer.data());
    char clientId[16];
    clear(clientId, 16);
    std::cout << "Enter a client name." << "\n";
    std::cin.getline(clientId, 16);
    // char clientId[16] = "64b81a0e0182\0";
    header->setClientId(clientId);
    char yehudit[255];
    clear(yehudit, 255);
    std::cout << "Enter a text message." << "\n";
    std::cin.getline(yehudit, 255);
    header->setTextMessage(yehudit);
    header->setPayloadSize();
    header->setMessageType(3);
    return buffer;
}


void printMessage(char* content, char messageType)
{

}

int main(int argc, char* argv[])
{

    getClientId();
        char name[255] = "rrf3f63985f04bedd1a0e43321880182\0";
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
            s.send(boost::asio::buffer(header));
            s.send(boost::asio::buffer(payload));
            
            std ::array<uint8_t, sizeof(ResponseHeader) > resHeader;
            s.receive(boost::asio::buffer(resHeader));
            auto* respHeader = reinterpret_cast<ResponseHeader*>(resHeader.data());
            if (respHeader->getCode()== 9000)
            {
                std::cout << "Server responded with an error "<< "\n";
            }
            else {
              //save in me.info name and id
            }
            
            }

            else if ((int)request[0]-'0' == 2){
            std ::array<uint8_t, sizeof(LittleReq) > header = header2();
            s.send(boost::asio::buffer(header));
            std ::array<uint8_t, sizeof(ResponseHeader) > header1;
            s.receive(boost::asio::buffer(header1));
            auto* res = reinterpret_cast<ResponseHeader*>(header1.data());
            int numOfUsers = res->getPayloadSize()/271;
            for (int i = 0; i < numOfUsers; i++){
                std ::array<uint8_t, sizeof(ResponseUsersList) > header1;
                s.receive(boost::asio::buffer(header1)); 
                auto* resPayload = reinterpret_cast<ResponseUsersList*>(header1.data());
                std::cout << resPayload->getClientName() << "\n";
               }
            }

            else if ((int)request[0]-'0' == 3){
            std ::array<uint8_t, sizeof(LittleReq) > header = header3();
            std ::array<uint8_t, sizeof(PublicKeyPayload) > payload = payload3();
            s.send(boost::asio::buffer(header));
            s.send(boost::asio::buffer(payload));
            
            std ::array<uint8_t, sizeof(ResponseHeader) > header1;
            s.receive(boost::asio::buffer(header1));
            auto* resHeader = reinterpret_cast<ResponseHeader*>(header1.data());

            std ::array<uint8_t, sizeof(ResponsePublicKey) > payloadRes;
            s.receive(boost::asio::buffer(payloadRes)); 
            auto* resPayload = reinterpret_cast<ResponsePublicKey*>(payloadRes.data());
            std::cout << resPayload->getPublicKey() << "\n";
            }

            else if ((int)request[0]-'0' == 4){// ask for waiting messages. 104
            std ::array<uint8_t, sizeof(LittleReq) > header = header4();
              s.send(boost::asio::buffer(header));

              std ::array<uint8_t, sizeof(ResponseHeader) > payloadHeader;
              s.receive(boost::asio::buffer(payloadHeader));
              auto* res = reinterpret_cast<ResponseHeader*>(payloadHeader.data());
              int sizeOfAllMessages = res->getPayloadSize();
              while (sizeOfAllMessages){
              std ::array<uint8_t, sizeof(ResponseGetWaitingMessages) > message;
              s.receive(boost::asio::buffer(message));
              auto* res = reinterpret_cast<ResponseGetWaitingMessages*>(message.data());
              int messageSize = res->getMessageSize();
              char*  yehudit = res->getContent();
              sizeOfAllMessages -= messageSize;
               std::cout << res->getContent()<< "\n";
            //   std ::array<uint8_t, sizeof(char) > content;
            //   s.receive(boost::asio::buffer(content));
            //   auto* resContent = reinterpret_cast<char*>(content.data());
              //printMessage(resContent,  res->getMessageType());
            }
           }
           
            else if ((int)request[0]-'0'    == 5){
            std ::array<uint8_t, sizeof(MessagePayload) > payload = payload5();
            auto* payloadData = reinterpret_cast<MessagePayload*>(payload.data());
            int textSize = payloadData->getPayloadSize();
            std ::array<uint8_t, sizeof(LittleReq) > header = header5(textSize);
            s.send(boost::asio::buffer(header));
            s.send(boost::asio::buffer(payload));
            std ::array<uint8_t, sizeof(LittleReq) > header1;
            s.receive(boost::asio::buffer(header1));
            }
        }
    } catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }
} 

