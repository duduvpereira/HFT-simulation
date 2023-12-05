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
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

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