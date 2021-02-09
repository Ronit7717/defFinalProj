#include <cstdlib>
#include <cstring>
#include <iostream>
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
        boost::asio::io_context io_context;
        tcp::socket s(io_context);
        tcp::resolver resolver(io_context);
        boost::asio::connect(s, resolver.resolve(argv[1], argv[2]));
        printMenu();
        for (;;)
        {
            std::cout << "Enter your request: ";
            char request[max_length];
            clear(request, max_length);
            std::cin.getline(request, max_length);
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
