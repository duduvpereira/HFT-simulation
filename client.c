#include <netinet/in.h> //structure for storing address information 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h> //for socket APIs 
#include <sys/types.h> 


unsigned char strData[2][92];

void receive_packet()
{
    int i;

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    //bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(9001);

    // connect to server with server address which is set above (serv_addr)
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("ERROR while connecting");
        return;
    }
    
    // send's messages to client socket
    //printf("\n\n\n\nmsg: %x\n\n\n", arrays[0]);
    uint32_t templateId;
    for(i=0; i<2; i++)
    {
        recv(sockfd, strData[i], sizeof(strData[i]), 0);
        //send(clientSocket, strData[i], sizeof(strData[i]), 0);
    }
    close(sockfd);
    for(i=0; i<2; i++)
    {
        templateId =  strData[i][22];
        printf("Template ID recebido: %d\n", templateId);
    }
}


void send_packet()
{
}


int main(int argc, char const* argv[]) 
{ 
    receive_packet();

    //send_packet();    
  
    return 0; 
}