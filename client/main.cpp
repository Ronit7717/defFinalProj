#include <cstdlib>
#include <cstring>
#include <iostream>
#include "Request.cpp"
#include <vector>

#include <boost/serialization/vector.hpp>

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

void clear(char message[], int length)
{
    for (int i = 0; i < length; i++)
        message[i] = '\0';
}

void printMenu()
{
    std::cout << "MessageU client at your service."
              << "\n"
              << "1) Register"
              << "\n"
              << "2) Request for clients list"
              << "\n"
              << "3) Request for public key"
              << "\n"
              << "4) Request for waiting messages"
              << "\n"
              << "5) Send a text message"
              << "\n"
              << "51) Send a request for symmetric key"
              << "\n"
              << "52) Send your symmetric key"
              << "\n"
              << "0) Exit client"
              << "\n"
              << "?"
              << "\n";
}

Request *createRequest(char req[1024])
{

    Payload2 *p = new Payload2("yehudit", 999);
    struct Header head;
    head.cid = 111;
    head.version = 2;
    head.code = 100;
    head.pSize = 2;
    int clientId = 111;
    int version = 222;
    int code = 0;
    int payloadSize = 100;
    Request *request = new Request();
    int a = 8;
    switch ((int)req[0] - '0')
    {
    case 1:
        std::cout << "user is asking to register";
        request = new Request(clientId, version, 100, payloadSize, p);
        break;
    case 2:
        std::cout << "user is asking for users list";
        request = new Request(clientId, version, 101, payloadSize);
        break;
    default:
        // code block
        int aa = 8;
    };

    std::cout << req;
    return request;
}

int main(int argc, char *argv[])
{
    const int max_length = 1024;
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
            return 1;
        }
        printMenu();
        std::vector<Request *> stocks_;
        Request *re = new Request(100);
        stocks_.push_back(re);

        boost::asio::io_context io_context;
        tcp::socket s(io_context);
        tcp::resolver resolver(io_context);
        boost::asio::connect(s, resolver.resolve(argv[1], argv[2]));
        s.send(boost::asio::buffer(&stocks_, sizeof(stocks_)));

        for (;;)
        {
            std::cout << "Enter message: ";
            char request[max_length];
            clear(request, max_length);
            std::cin.getline(request, max_length);
            createRequest(request);
            boost::asio::const_buffer b1 = boost::asio::buffer(request, max_length);
            boost::asio::write(s, boost::asio::buffer(request, max_length));
            char reply[max_length];
            size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply, max_length));
            std::cout << "Reply is: " << reply << "\n";
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}
