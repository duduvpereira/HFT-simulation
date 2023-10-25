#include <netinet/in.h> //structure for storing address information 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h> //for socket APIs 
#include <sys/types.h> 
#include <arpa/inet.h> 


unsigned char strData[2][92];

void receive_packet()
{
    int sockD; 
    int i, len;

    struct sockaddr_in servAddr; 
    //printf("1.\n");
    if((sockD = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        printf("Fail.\n");
        //return 0;
    }
    //printf("2.\n");
    //memset(&servAddr, 0, sizeof(servAddr));
  
    servAddr.sin_family = AF_INET; 
    servAddr.sin_port = htons(9001); // use some unused port number 
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //printf("3.\n");
    if (bind(sockD, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
    {
        printf("bind() failed\n");
        return;
    }
    //printf("4.\n");
    //int connectStatus = connect(sockD, (struct sockaddr*)&servAddr, sizeof(servAddr)); 
  
    //if (connectStatus == -1) { 
    //   printf("Error...\n"); 
    //} 
  
    //else { 
    //    
    //    uint32_t templateId;

    //    for(i=0; i<2; i++)
    //    {
    //        recv(sockD, strData[i], sizeof(strData), 0);
    //    }

    //    for(i=0; i<2; i++)
    //    {
    //        templateId =  strData[i][22];
    //        printf("Template ID recebido: %d\n", templateId);
    //    }
    //}
    uint32_t templateId;
    for(i=0; i<2; i++)
    {
        //len = recvfrom(sockD, strData[i], sizeof(strData), 0, NULL, 0);
        len = recv(sockD, strData[i], sizeof(strData), MSG_WAITALL);
        printf("len = %d\n", len);
    }
    for(i=0; i<2; i++)
    {
        templateId =  strData[i][22];
        printf("Template ID recebido: %d\n", templateId);
    }
    close(sockD);
}


void send_packet()
{
    int i;

    /*Envia o pacote recebido*/
    int servSockD = socket(AF_INET, SOCK_STREAM, 0);
    
    // define server address 
    struct sockaddr_in servAddr2; 
  
    servAddr2.sin_family = AF_INET; 
    servAddr2.sin_port = htons(8001); 
    servAddr2.sin_addr.s_addr = INADDR_ANY; 
  
    // bind socket to the specified IP and port 
    bind(servSockD, (struct sockaddr*)&servAddr2, 
         sizeof(servAddr2)); 
  
    // listen for connections 
    listen(servSockD, 1); 
  
    // integer to hold client socket. 
    int clientSocket = accept(servSockD, NULL, NULL); 
  
    // send's messages to client socket
    //printf("\n\n\n\nmsg: %x\n\n\n", arrays[0]);
    for(i=0; i<2; i++)
    {
        send(clientSocket, strData[i], sizeof(strData[i]), 0);
    }

}


int main(int argc, char const* argv[]) 
{ 
    receive_packet();

    //send_packet();    
  
    return 0; 
}
