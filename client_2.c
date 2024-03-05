#include <netinet/in.h> //structure for storing address information 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h> //for socket APIs 
#include <sys/types.h> 
#include <inttypes.h>

#include <stddef.h>

#define TEMPLATE_HEADER 12
#define SIZE_HEADER 22
#define SIZE_T_ID_53 56
#define SIZE_T_ID_15 44
#define SIZE_T_ID_24 32
#define SIZE_T_ID_25 32
#define SIZE_T_ID_51 44
#define SIZE_T_ID_55 (64 + 28)
#define SIZE_UDP_HEADER 46
#define HEADER_SBE 28


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

unsigned char strData[1000];
int sockfd;
uint8_t retransmit = 0;



void decodePkt(unsigned char *temp, int tam)
{
    int i, j, count=0;

    //printf("tam: %d\n", tam);
    //pacote com um template
    
    //Tira o header UDP
    for(i=0; i<tam; i++)
    {
        temp[i] = strData[i];
    }

    printf("[TEMPLATE ID]: %d\n", temp[SIZE_HEADER+SIZE_UDP_HEADER]);

    
    if(55 == temp[SIZE_HEADER+SIZE_UDP_HEADER])
    {
        //printf("caiu55\n");
        //unsigned char temID55[SIZE_T_ID_55];
        //for(i=HEADER_SBE; i<(SIZE_T_ID_55+HEADER_SBE) ; i++)
        //{
        //    temID55[i-HEADER_SBE] = temp[i];
        //}
        struct pkt55 *msg55 = (struct pkt55 *)temp;
        //printf("\n%llx\n", msg55->securityID);
        retransmit = 1;
        createOrder(temp);
    }

    if(53 == temp[SIZE_HEADER+SIZE_UDP_HEADER])
    {
        //unsigned char temID53[SIZE_T_ID_53];
        //for(i=HEADER_SBE; i<(SIZE_T_ID_53+HEADER_SBE) ; i++)
        //{
        //    temID53[i-HEADER_SBE] = temp[i];
        //}
        struct pkt53 *msg53 = (struct pkt53 *)temp;
        printf("securityID: %llx\n",            (msg53->securityID));
        printf("matchEventIndicator: %llx\n",   (msg53->matchEventIndicator));
        printf("tradingSessionID: %llx\n",      (msg53->tradingSessionID));
        printf("tradeCondition: %llx\n",        (msg53->tradeCondition));
        printf("mDEntryPx: %llx\n",             (msg53->mDEntryPx));
        printf("mDEntrySize: %llx\n",           (msg53->mDEntrySize));
        printf("tradeID: %llx\n",               (msg53->tradeID));
        printf("mDEntryBuyer: %llx\n",          (msg53->mDEntryBuyer));
        printf("mDEntrySeller: %llx\n",         (msg53->mDEntrySeller));
        printf("tradeDate: %llx\n",             (msg53->tradeDate));
        printf("trdSubType: %llx\n",            (msg53->trdSubType));
        printf("padding: %llx\n",               (msg53->padding));
        printf("mdEntryTimeStamp: %03ld\n",      (msg53->mdEntryTimeStamp));
        printf("rptSeq: %llx\n",                (msg53->rptSeq));
    }
    
    //for(j=0; j<tam; j++)
    //{
        //printf("%x\n", msg1[j]);
    //}
}


void createOrder(unsigned char *msg)
{
    //struct pkt55 *msg55 = (struct pkt55 *) malloc(sizeof(struct pkt55));
    struct pkt55 *msg55 = (struct pkt55 *)msg;
    printf("securityID: %llx\n",             (msg55->securityID));
    printf("padding: %llx\n",           (msg55->padding));
    printf("agressorSide: %llx\n",      (msg55->agressorSide));
    printf("padding2: %llx\n",          (msg55->padding2));
    printf("lastPx: %llx\n",            (msg55->lastPx));
    printf("fillqtx: %llx\n",           (msg55->fillqtx));
    printf("tradeHiddenQty: %llx\n",    (msg55->tradeHiddenQty));
    printf("cxlQty: %llx\n",            (msg55->cxlQty));
    printf("agressorTime: %llx\n",      (msg55->agressorTime));
    printf("rptSeq: %llx\n",            (msg55->rptSeq));
    printf("mdEntryTimeStamp: %llx\n",  (msg55->mdEntryTimeStamp));

    //printf("\naqui2\n");
    struct pkt102 *msg102 = (struct pkt102 *) malloc(sizeof(struct pkt102));
    //printf("\naqui3\n");
    msg102->templateId = 0x66;
    //printf("\naqui4\n");
    msg102->ClOrdID = 0x01;
    msg102->EnteringFirm = 0x00505543;
    msg102->EnteringTrader = 0xF5BA50;
    msg102->SenderLocation = 0X00;
    msg102->OrdTagID = 0X01;
    msg102->MarketSegmented = 0XAF;
    msg102->side = 0X01;
    msg102->TransactTime = 0X65DCF0B6;
    msg102->OrderQty = 0X05;
    msg102->securityID = msg55->securityID;
    msg102->TimeInForce = 0x00;
    msg102->OrdType = 0x02;

    //printf("\naqui5\n");

    send_packet(msg102);
    
}


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
    int tam;
    printf("receving packet....\n");
    //for(i=0; i<2; i++)
    //{
        tam = recv(sockfd, strData, sizeof(strData), 0);
        //send(clientSocket, strData[i], sizeof(strData[i]), 0);
    //}
    //for(i=0; i<2; i++)
    //{
        //unsigned char *temp = calloc(tam, sizeof(unsigned char));
        unsigned char temp[1000] = {0};
        printf("TAM1: %d\n", tam);
        decodePkt(temp, tam);
}

int clientSocket;
//unsigned char arrays[2][92];
void connectOB()
{
    int ret;
	struct sockaddr_in serverAddr;

	char buffer[1024];

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
    send(clientSocket, "12345678", 8, 0);
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("buff: %s\n", buffer);
    if(strcmp(buffer, "1") == 0)
    {
        printf("[+]Connected to Server.\n");
    }
    else
    {
        printf("[+]Not connected to Order Book, wrong key.\n");
        return 0;
    }
	
}

void send_packet(unsigned char *temp)
{
    int i;
    printf("Client: \t");
	//scanf("%s", &buffer[0]);
    //for(i=0; i<2; i++)
    //{
    printf("Tem ID: %d\n", temp[SIZE_UDP_HEADER + SIZE_HEADER]);
    //for(i=0;i<500;i++)
    //{
    //    printf("[%d]: %llx\n", i, temp[i]);
    //}
	send(clientSocket, temp, 1000, 0);
    retransmit = 0;
	//if(strcmp(buffer, ":exit") == 0){
    //}
    //send(clientSocket, ":exit", sizeof(":exit"), 0);
	close(clientSocket);
    receive_packet();
	printf("[-]Disconnected from server.\n");
	exit(1);
}


int main(int argc, char const* argv[]) 
{ 
    connectOB();
    create_socket();
    while(retransmit == 0)
    {
        receive_packet();
    }

    //send_packet();    
  
    return 0; 
}