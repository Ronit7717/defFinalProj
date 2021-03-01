#include<io.h>
#include<stdio.h>
#include<winsock2.h>
    #include <stdio.h> 
    #include <stdlib.h> 
    #include <errno.h> 
    #include <string.h> 
    #include <sys/types.h> 
    #include <unistd.h>
  #include <strings.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library


int main(int argc , char *argv[])
{

    WSADATA wsa;
    SOCKET s , new_socket;
    struct sockaddr_in server , client;
    int c;
    char *message;


//create a socket
if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons( 8888 );

      //   their_addr.sin_addr = *((struct in_addr *)he->h_addr);
        memset(&(client.sin_zero),'0',7);



if (connect(s, (struct sockaddr *)&client, \
                                              sizeof(struct sockaddr)) == -1) {
            perror("connect");
            exit(1);
        }
}