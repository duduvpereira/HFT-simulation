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

struct pkt102
{
    uint64_t UDP1;
    uint64_t UDP2;
    uint64_t UDP3;
    uint64_t UDP4;
    uint64_t UDP5;
    uint32_t UDP6;
    uint16_t UDP7;
    //cabeçalho
    uint8_t chNumber;
    uint8_t reserved;
    uint16_t seqVersion;
    uint32_t seqNumber;
    uint64_t sendingTime;
    uint16_t msgLength;
    uint16_t encondingType;
    uint16_t blockLength;
    uint16_t templateId;
    uint16_t schemaId;
    uint16_t version;
    //body
    uint64_t ClOrdID;
    uint32_t EnteringFirm;
    uint64_t EnteringTrader;
    uint16_t EnteringTrader2;
    uint8_t SenderLocation;
    uint8_t OrdTagID;
    uint8_t MarketSegmented;
    uint8_t side;
    uint64_t TransactTime;
    uint64_t OrderQty;
    uint64_t securityID;
    uint8_t TimeInForce;
    uint8_t OrdType;
} __attribute__((packed));

struct pkt55
{
    uint64_t UDP1;
    uint64_t UDP2;
    uint64_t UDP3;
    uint64_t UDP4;
    uint64_t UDP5;
    uint32_t UDP6;
    uint16_t UDP7;
    uint8_t chNumber;
    uint8_t reserved;
    uint16_t seqVersion;
    uint32_t seqNumber;
    uint64_t sendingTime;
    uint16_t msgLength;
    uint16_t encondingType;
    uint16_t blockLength;
    uint16_t templateId;
    uint16_t schemaId;
    uint16_t version;
    uint64_t securityID;
    uint16_t padding;
    uint8_t agressorSide;
    uint8_t padding2;
    uint64_t lastPx;
    uint64_t fillqtx;
    uint64_t tradeHiddenQty;
    uint64_t cxlQty;
    uint64_t agressorTime;
    uint32_t rptSeq;
    uint64_t mdEntryTimeStamp;
} __attribute__((packed));


struct pkt53
{
    uint64_t UDP1;
    uint64_t UDP2;
    uint64_t UDP3;
    uint64_t UDP4;
    uint64_t UDP5;
    uint32_t UDP6;
    uint16_t UDP7;
    //cabeçalho
    uint8_t chNumber;
    uint8_t reserved;
    uint16_t seqVersion;
    uint32_t seqNumber;
    uint64_t sendingTime;
    uint16_t msgLength;
    uint16_t encondingType;
    uint16_t blockLength;
    uint16_t templateId;
    uint16_t schemaId;
    uint16_t version;
    //body
    uint64_t securityID;
    uint8_t matchEventIndicator;
    uint8_t tradingSessionID;
    uint16_t tradeCondition;
    uint64_t mDEntryPx;
    uint64_t mDEntrySize;
    uint32_t tradeID;
    uint32_t mDEntryBuyer;
    uint32_t mDEntrySeller;
    uint16_t tradeDate;
    uint8_t trdSubType;
    uint8_t padding;
    uint64_t mdEntryTimeStamp;
    uint32_t rptSeq;
} __attribute__((packed));

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

send_packet(int port, int p, unsigned char *pkt)
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
        bytes = sendto(sockfd, pkt, 1000, 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
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

	unsigned char strData[1000];
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
	unsigned char login[8];

	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0){
			printf("out\n");
			exit(1);
		}
		recv(newSocket, login, 8, 0);
		printf("data: %s\n", login);
		if(strcmp(login, "12345678") == 0)
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
				recv(newSocket, strData, 1000, 0);
				clock_gettime(CLOCK_REALTIME, &spec);
				s  = spec.tv_sec;
    			ms = round(spec.tv_nsec); // Convert nanoseconds to milliseconds

				struct pkt102 *rcv = (struct pkt102 *)strData; 
				struct pkt53 *snd;

				snd->templateId = 53;
				snd->securityID = rcv->securityID;
				snd->matchEventIndicator = 0x00;
				snd->tradingSessionID = 0x01;
				snd->tradeCondition = 0x2001;
				snd->mDEntryPx = 0x400d030000000000;
				snd->mDEntrySize = 0x05;
				snd->tradeID = 0x0a;
				snd->mDEntryBuyer = rcv->EnteringFirm;
				snd->mDEntrySeller = 0x00;
				snd->tradeDate = 0x4c51;
				snd->trdSubType = 0x01;
				snd->padding = 0x00;
				snd->mdEntryTimeStamp = s;
				snd->rptSeq = 0x01;

				printf("\ntempo pkt: %03ld\n", snd->mdEntryTimeStamp);


    			//if (ms > 999) {
    			//    s++;
    			//    ms = 0;
    			//}
				
				printf("Template ID recebido: %d\n", rcv->templateId);
				//for(k=0; k<500; k++)
				//{
				//	printf("packet[%d]: %llx\n",k, strData[k]);
				//}
				//printf("Current time: %03ld sec %03ld ms\n", s, ms);
				if(rcv->templateId==102)
				{
					send_packet(8001, 0, snd);
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