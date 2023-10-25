#include <netinet/in.h> //structure for storing address information 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h> //for socket APIs 
#include <sys/types.h> 


unsigned char strData[2][92];

void receive_packet()
{
    int i;
    int sockD = socket(AF_INET, SOCK_STREAM, 0); 

    struct sockaddr_in servAddr; 
  
    servAddr.sin_family = AF_INET; 
    servAddr.sin_port 
        = htons(8001); // use some unused port number 
    servAddr.sin_addr.s_addr = INADDR_ANY; 
  
    int connectStatus = connect(sockD, (struct sockaddr*)&servAddr, sizeof(servAddr)); 
  
    if (connectStatus == -1) { 
        printf("Error...\n"); 
    } 
  
    else { 
        uint32_t templateId;

        for(i=0; i<2; i++)
        {
            recv(sockD, strData[i], sizeof(strData), 0);
        }

        for(i=0; i<2; i++)
        {
            templateId =  strData[i][22];
            printf("Template ID recebido: %d\n", templateId);
        }
    }
}




int main(int argc, char const* argv[]) 
{ 
    receive_packet(); 
    return 0; 
}
