#include <netinet/in.h> //structure for storing address information 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h> //for socket APIs 
#include <sys/types.h> 


unsigned char strData[92];
int sockfd;

create_socket()
{
    int32_t reuse = 1;

    struct sockaddr_in serv_addr;
    
    // define server address 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0)
    {
        printf("ERRO SOCKET\n");
    }

    memset((char*) &serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
    serv_addr.sin_port = htons(8003);
    
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse)) != 0)
    {
        printf("ERRO SETSOCKOPT\n");
    }

    // bind socket to the specified IP and port 
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        printf("ERROR on binding\n");
        return;
    }
}

void receive_packet()
{
    int i;
    uint32_t templateId;
    printf("receving packet....\n");
    //for(i=0; i<2; i++)
    //{
        recv(sockfd, strData, sizeof(strData), 0);
        //send(clientSocket, strData[i], sizeof(strData[i]), 0);
    //}
    //for(i=0; i<2; i++)
    //{
        templateId =  strData[22];
        printf("Template ID recebido: %d\n", templateId);
    //}
}

int clientSocket;
//unsigned char arrays[2][92];
void connectOB()
{
    int ret;
	struct sockaddr_in serverAddr;
	//char buffer[1024];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(4444);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");
}

void send_packet()
{
    printf("Client: \t");
	//scanf("%s", &buffer[0]);
	send(clientSocket, strData, sizeof(strData), 0);
	//if(strcmp(buffer, ":exit") == 0){
		close(clientSocket);
		printf("[-]Disconnected from server.\n");
		exit(1);
	//}
}


int main(int argc, char const* argv[]) 
{ 
    connectOB();
    create_socket();
    receive_packet();

    send_packet();    
  
    return 0; 
}