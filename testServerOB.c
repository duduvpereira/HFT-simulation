#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h> 
#include <time.h>

#define PORT 4444


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
    serv_addr.sin_port = htons(8009);
    
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

send_packet(int port, int p)
{
    int i, bytes;

    struct sockaddr_in cli_addr;
    
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_addr.s_addr = INADDR_ANY;
    cli_addr.sin_port = htons(port);
    //for(i=0; i<2; i++)
    //{
    //if(50 == p)
    //{
        bytes = sendto(sockfd, "ok", 2, 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
        if(bytes <= 0)
        {
            printf("ERRO SEND\n");
        }
}

int main(){

	int sockfd, ret;
	struct sockaddr_in serverAddr;
	struct timespec spec;
	long            ms; // Milliseconds
    time_t          s;  // Seconds
	uint32_t templateId, k;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	unsigned char strData[138];
	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in binding.\n");
	}


	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0){
			printf("out\n");
			exit(1);
		}
		recv(newSocket, strData, sizeof(strData), 0);
		printf("data: %s\n", strData);
		if(strcmp(strData, "12345678") == 0)
		{
			send(newSocket, "1", 1, 0);
			printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
			create_socket();
		}
		else
		{
			send(newSocket, "0", 1, 0);
			printf("Wrong key, Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
			close(newSocket);
			break;
		}


		if((childpid = fork()) == 0){
			close(sockfd);

			while(1){
				//start_t = clock();
				recv(newSocket, strData, sizeof(strData), 0);
				clock_gettime(CLOCK_REALTIME, &spec);
				s  = spec.tv_sec;
    			ms = round(spec.tv_nsec); // Convert nanoseconds to milliseconds
    			//if (ms > 999) {
    			//    s++;
    			//    ms = 0;
    			//}
				templateId =  strData[68];
				printf("Template ID recebido: %d\n", templateId);
				//for(k=0; k<92; k++)
				//{
				//	printf("packet: %d\n", buffer[k]);
				//}
				printf("Current time: %03ld sec %03ld ms\n", s, ms);
				if(templateId==55)
				{
					send_packet(8001, 0);
					printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					break;
				}
				//if(strcmp(buffer, ":exit") == 0){
				//	printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
				//	break;
				//}
				//}else{
					//printf("Client: %s\n", buffer);
					//send(newSocket, buffer, strlen(buffer), 0);
				//	bzero(buffer, sizeof(buffer));
				//}
			}
		}

	}

	close(newSocket);


	return 0;
}