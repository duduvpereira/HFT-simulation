#include <netinet/in.h> //structure for storing address information 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h> //for socket APIs 
#include <sys/types.h> 
#include <inttypes.h>

#define TEMPLATE_HEADER 12
#define SIZE_HEADER 22
#define SIZE_T_ID_53 56
#define SIZE_T_ID_15 44
#define SIZE_T_ID_24 32
#define SIZE_T_ID_25 32
#define SIZE_T_ID_51 44
#define SIZE_T_ID_55 64
#define SIZE_UDP_HEADER 46
#define HEADER_SBE 28


struct pkt55
{
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
} __attribute__((packet, aligned(4)));


struct pkt53
{
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
} __attribute__((packet, aligned(4)));

unsigned char strData[500];
int sockfd;
uint8_t retransmit = 0;



void decodePkt(unsigned char *temp, int tam)
{
    int i, j, count=0;

    printf("tam: %d\n", tam);
    //pacote com um template
    
    //Tira o header UDP
    for(i=0; i<tam; i++)
    {
        temp[i] = strData[i+SIZE_UDP_HEADER];
    }

    printf("[TEMPLATE ID]: %d\n", temp[SIZE_HEADER]);

    
    if(55 == temp[SIZE_HEADER])
    {
        printf("caiu55\n");
        unsigned char temID55[SIZE_T_ID_55];
        for(i=HEADER_SBE; i<(SIZE_T_ID_55+HEADER_SBE) ; i++)
        {
            temID55[i-HEADER_SBE] = temp[i];
        }
        //struct pkt55 *msg55 = (struct pkt55 *)temID55;
        retransmit = 1;
        createOrder(temID55);
    }

    if(56 == temp[SIZE_HEADER])
    {
        unsigned char temID53[SIZE_T_ID_53];
        for(i=HEADER_SBE; i<(SIZE_T_ID_53+HEADER_SBE) ; i++)
        {
            temID53[i-HEADER_SBE] = temp[i];
        }
        //struct ppkt56 *msg53 = (struct pkt53 *)temID53;
    }
    
    for(j=0; j<tam; j++)
    {
        //printf("%x\n", msg1[j]);
    }
}


void createOrder(unsigned char *msg)
{
    //struct pkt55 *msg55 = (struct pkt55 *) malloc(sizeof(struct pkt55));
    struct pkt55 *msg55 = (struct pkt55 *)msg;
    printf("secID: %llx\n",             (msg55->securityID));
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


    unsigned char tempSender[138] = {0};
}

/*
void packet_1Template(int tam, unsigned char *temp)
{
    int i, j, count=0;
    //unsigned char *msg1 = (unsigned char *)calloc(tam, sizeof(unsigned char));

    printf("tam: %d\n", tam);
    //pacote com um template
    if(138 == tam)
    {
        //memcpy(msg1, strData[SIZE_UDP_HEADER], tam);
        for(i=0; i<tam; i++)
        {
            //printf("aqui\n");
            temp[i] = strData[i+SIZE_UDP_HEADER];
            //printf("%d\n", i-46);
            //printf("aqui2\n");
        }
        printf("[TEMPLATE ID]: %d\n", temp[SIZE_HEADER]);
        
        for(j=0; j<tam; j++)
        {
            //printf("%x\n", msg1[j]);
        }
    }

    //printf("tam: %d\n", tam);
    count = 0;
    //pacote com um template
    if(126 == tam)
    {
        for(i=SIZE_UDP_HEADER; i<tam; i++)
        {
            temp[i-SIZE_UDP_HEADER] = strData[i];
            //printf("%d\n", i-46);
        }
        printf("[TEMPLATE ID]: %d\n", temp[SIZE_HEADER]);
    }
    //free(msg1);
}

void packet_5Template(int tam, unsigned char *temp)
{
    int i, j, count=0;
    printf("tam: %d\n", tam);
    count = 0;
    //unsigned char *msg2 = (unsigned char *)calloc(tam, sizeof(unsigned char));
    if(330 == tam)
    {
        unsigned char temID53[TEMPLATE_HEADER+SIZE_T_ID_53];
        unsigned char temID15[TEMPLATE_HEADER+SIZE_T_ID_15];
        unsigned char temID24[TEMPLATE_HEADER+SIZE_T_ID_25];
        unsigned char temID25[TEMPLATE_HEADER+SIZE_T_ID_24];
        unsigned char temID51[TEMPLATE_HEADER+SIZE_T_ID_51];
        //printf("SIZE: %d\n", sizeof(msg2));
        for(i=SIZE_UDP_HEADER;i<sizeof(strData); i++)
        {
            temp[i-SIZE_UDP_HEADER] = strData[i];
        }

        //printf("[COUNT]: %d [i]: %d\n", count,i);
        printf("[TEMPLATE ID]: %d\n", temp[SIZE_HEADER]);
        printf("\n");
        if(53 == temp[count+SIZE_HEADER])
        {
            for(i=0; i<sizeof(temID53); i++)
            {
                temID53[i] = temp[i];
                //printf("%d\n", i-46);
                count++;
            }
            for(j=0; j<sizeof(temID53); j++)
            {
                //printf("%x\n", temID53[j]);
            }
        }
        //arrumar daqui pra baixo
        //printf("[COUNT]: %d [i]: %d\n", count,i);
        printf("[TEMPLATE ID]: %d\n", temp[count+SIZE_HEADER]);
        printf("\n");
        if(15 == temp[count+SIZE_HEADER])
        {
            int flag = count;
            for(i; i<sizeof(temID15)+flag; i++)
            {
                temID15[i-flag] = temp[i];
                //printf("%x\n", temp[i]);
                count++;
            }
            for(j=0; i<sizeof(temID15); i++)
            {
                //printf("%x\n", temID15[i]);
            }
        }

        //printf("[COUNT]: %d [i]: %d\n", count,i);
        printf("[TEMPLATE ID]: %d\n", temp[count+SIZE_HEADER]);
        printf("\n");
        if(24 == temp[count+SIZE_HEADER])
        {
            int flag = count;
            //printf("i: %d, flag: %d, count: %d, temId24+flag: %d\n", i, flag, count, sizeof(temID24)+flag);
            for(i; i<sizeof(temID24)+flag; i++)
            {
                temID24[i-flag] = temp[i];
                //printf("%x\n", temp[i]);
                count++;
            }
            for(j=0; j<sizeof(temID24); j++)
            {
                //printf("%x\n", temID24[j]);
            }
        }

        //printf("[COUNT]: %d [i]: %d\n", count,i);
        printf("[TEMPLATE ID]: %d\n", temp[count+SIZE_HEADER]);
        printf("\n");
        if(25 == temp[count+SIZE_HEADER])
        {
            int flag = count;
            for(i; i<sizeof(temID25)+flag; i++)
            {
                temID25[i-flag] = temp[i];
                //printf("%d\n", count);
                count++;
            }
            for(j=0; j<sizeof(temID25); j++)
            {
                //printf("%x\n", temID25[j]);
            }
        }
        
        //printf("[COUNT]: %d [i]: %d\n", count,i);
        printf("[TEMPLATE ID]: %d\n", temp[count+SIZE_HEADER]);
        printf("\n");
        if(51 == temp[count+SIZE_HEADER])
        {
            int flag = count;
            for(i; i<sizeof(temID51)+flag; i++)
            {
                temID51[i-flag] = temp[i];
                //printf("%d\n", i-46);
                count++;
            }
            for(j=0; j<sizeof(temID51); j++)
            {
                //printf("%x\n", temID51[j]);
            }
        }
    }
    //free(temp);
    
}

void packet_3Template(int tam, unsigned char *temp)
{
    int i, j, count=0;
    printf("tam: %d\n", tam);
    count = 0;
    //unsigned char *temp = (unsigned char *)calloc(tam, sizeof(unsigned char));
    if(230 == tam)
    {
        unsigned char temID53[TEMPLATE_HEADER+SIZE_T_ID_53];
        unsigned char temID24[TEMPLATE_HEADER+SIZE_T_ID_25];
        unsigned char temID51[TEMPLATE_HEADER+SIZE_T_ID_51];

        for(i=SIZE_UDP_HEADER;i<tam; i++)
        {
            temp[i-SIZE_UDP_HEADER] = strData[i];
        }

        printf("[TEMPLATE ID]: %d\n", temp[SIZE_HEADER]);
        printf("\n");
        if(53 == temp[count+SIZE_HEADER])
        {
            for(i=0; i<sizeof(temID53); i++)
            {
                temID53[i] = temp[i];
                count++;
            }
            for(j=0; j<sizeof(temID53); j++)
            {
                //printf("%x\n", temID53[j]);
            }
        }

        printf("[TEMPLATE ID]: %d\n", temp[count+SIZE_HEADER]);
        printf("\n");
        if(24 == temp[count+SIZE_HEADER])
        {
            int flag = count;
            //printf("i: %d, flag: %d, count: %d, temId24+flag: %d\n", i, flag, count, sizeof(temID24)+flag);
            for(i; i<sizeof(temID24)+flag; i++)
            {
                temID24[i-flag] = temp[i];
                //printf("%x\n", msg2[i]);
                count++;
            }
            for(j=0; j<sizeof(temID24); j++)
            {
                //printf("%x\n", temID24[j]);
            }
        }

        printf("[TEMPLATE ID]: %d\n", temp[count+SIZE_HEADER]);
        printf("\n");
        if(51 == temp[count+SIZE_HEADER])
        {
            int flag = count;
            for(i; i<sizeof(temID51)+flag; i++)
            {
                temID51[i-flag] = temp[i];
                //printf("%d\n", i-46);
                count++;
            }
            for(j=0; j<sizeof(temID51); j++)
            {
                //printf("%x\n", temID51[j]);
            }
        }
    }
    //free(temp);
}

void packet_2Template(int tam, unsigned char *temp)
{
    int i, j, count=0;
    printf("tam: %d\n", tam);
    count = 0;
    //unsigned char *temp = (unsigned char *)calloc(tam, sizeof(unsigned char));

    if(186 == tam)
    {
        unsigned char temID53[TEMPLATE_HEADER+SIZE_T_ID_53];
        unsigned char temID51[TEMPLATE_HEADER+SIZE_T_ID_51];

        for(i=SIZE_UDP_HEADER;i<tam; i++)
        {
            temp[i-SIZE_UDP_HEADER] = strData[i];
        }

        printf("[TEMPLATE ID]: %d\n", temp[SIZE_HEADER]);
        printf("\n");
        if(53 == temp[count+SIZE_HEADER])
        {
            for(i=0; i<sizeof(temID53); i++)
            {
                temID53[i] = temp[i];
                count++;
            }
            for(j=0; j<sizeof(temID53); j++)
            {
                //printf("%x\n", temID53[j]);
            }
        }

        printf("[TEMPLATE ID]: %d\n", temp[count+SIZE_HEADER]);
        printf("\n");
        if(51 == temp[count+SIZE_HEADER])
        {
            int flag = count;
            for(i; i<sizeof(temID51)+flag; i++)
            {
                temID51[i-flag] = temp[i];
                //printf("%d\n", i-46);
                count++;
            }
            retransmit = 1;
            for(j=0; j<sizeof(temID51); j++)
            {
                //printf("%x\n", temID51[j]);
            }
        }
    }
    //free(temp);
}
*/
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
    serv_addr.sin_port = htons(8002);
    
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
        unsigned char temp[500] = {0};
        printf("TAM1: %d\n", tam);
        decodePkt(temp, tam);
        /*
        if(tam <= 138)
        {
            packet_1Template(tam, temp);
        }
        if(tam == 330)
        {
            packet_5Template(tam, temp);
        }
        if(tam == 230)
        {
            packet_3Template(tam, temp);
        }
        if(tam == 186)
        {
            packet_2Template(tam, temp);
        }*/
        //free(temp);
        //templateId =  strData[22];
        //if(55==templateId)
        //{
        //    retransmit = 1;
        //}
        //printf("Template ID recebido: %d\n", templateId);
    //}
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

void send_packet()
{
    int i;
    printf("Client: \t");
	//scanf("%s", &buffer[0]);
    //for(i=0; i<2; i++)
    //{
    printf("Tem ID: %d\n", strData[SIZE_UDP_HEADER + SIZE_HEADER]);
	send(clientSocket, strData, sizeof(strData), 0);
    retransmit = 0;
	//if(strcmp(buffer, ":exit") == 0){
    //}
    //send(clientSocket, ":exit", sizeof(":exit"), 0);
	close(clientSocket);
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

    send_packet();    
  
    return 0; 
}