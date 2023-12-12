#include <netinet/in.h> //structure for storing address information 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h> //for socket APIs 
#include <sys/types.h> 

#define TEMPLATE_HEADER 12
#define SIZE_HEADER 22
#define SIZE_T_ID_53 56
#define SIZE_T_ID_15 44
#define SIZE_T_ID_24 32
#define SIZE_T_ID_25 32
#define SIZE_T_ID_51 44
#define SIZE_UDP_HEADER 46

unsigned char strData[500];
int sockfd;
uint8_t retransmit = 0;

void packet_1Template(int tam)
{
    int i, j, count=0;
    

    printf("tam: %d\n", tam);
    //pacote com um template
    if(138 == tam)
    {
        unsigned char *msg1;
        //memcpy(msg1, strData[SIZE_UDP_HEADER], tam);
        for(i=0; i<tam; i++)
        {
            printf("aqui\n");
            msg1[i] = strData[i+SIZE_UDP_HEADER];
            //printf("%d\n", i-46);
            printf("aqui2\n");
        }
        printf("[TEMPLATE ID]: %d\n", msg1[SIZE_HEADER]);
        if(55==msg1[SIZE_HEADER])
        {
            retransmit = 1;
        }
        for(j=0; j<tam; j++)
        {
            //printf("%x\n", msg1[j]);
        }
    }

    printf("tam: %d\n", tam);
    count = 0;
    //pacote com um template
    if(126 == tam)
    {
        unsigned char *msg3;
        for(i=SIZE_UDP_HEADER; i<tam; i++)
        {
            msg3[i-SIZE_UDP_HEADER] = strData[i];
            //printf("%d\n", i-46);
        }
        printf("[TEMPLATE ID]: %d\n", msg3[SIZE_HEADER]);
    }
}

void packet_5Template(int tam)
{
    int i, j, count=0;
    printf("tam: %d\n", tam);
    count = 0;
    if(330 == tam)
    {
        unsigned char *msg2;
        unsigned char temID53[TEMPLATE_HEADER+SIZE_T_ID_53];
        unsigned char temID15[TEMPLATE_HEADER+SIZE_T_ID_15];
        unsigned char temID24[TEMPLATE_HEADER+SIZE_T_ID_25];
        unsigned char temID25[TEMPLATE_HEADER+SIZE_T_ID_24];
        unsigned char temID51[TEMPLATE_HEADER+SIZE_T_ID_51];
        //printf("SIZE: %d\n", sizeof(msg2));
        for(i=SIZE_UDP_HEADER;i<sizeof(strData); i++)
        {
            msg2[i-SIZE_UDP_HEADER] = strData[i];
        }

        //printf("[COUNT]: %d [i]: %d\n", count,i);
        printf("[TEMPLATE ID]: %d\n", msg2[SIZE_HEADER]);
        printf("\n");
        if(53 == msg2[count+SIZE_HEADER])
        {
            for(i=0; i<sizeof(temID53); i++)
            {
                temID53[i] = msg2[i];
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
        printf("[TEMPLATE ID]: %d\n", msg2[count+SIZE_HEADER]);
        printf("\n");
        if(15 == msg2[count+SIZE_HEADER])
        {
            int flag = count;
            for(i; i<sizeof(temID15)+flag; i++)
            {
                temID15[i-flag] = msg2[i];
                //printf("%x\n", msg2[i]);
                count++;
            }
            for(j=0; i<sizeof(temID15); i++)
            {
                //printf("%x\n", temID15[i]);
            }
        }

        //printf("[COUNT]: %d [i]: %d\n", count,i);
        printf("[TEMPLATE ID]: %d\n", msg2[count+SIZE_HEADER]);
        printf("\n");
        if(24 == msg2[count+SIZE_HEADER])
        {
            int flag = count;
            //printf("i: %d, flag: %d, count: %d, temId24+flag: %d\n", i, flag, count, sizeof(temID24)+flag);
            for(i; i<sizeof(temID24)+flag; i++)
            {
                temID24[i-flag] = msg2[i];
                //printf("%x\n", msg2[i]);
                count++;
            }
            for(j=0; j<sizeof(temID24); j++)
            {
                //printf("%x\n", temID24[j]);
            }
        }

        //printf("[COUNT]: %d [i]: %d\n", count,i);
        printf("[TEMPLATE ID]: %d\n", msg2[count+SIZE_HEADER]);
        printf("\n");
        if(25 == msg2[count+SIZE_HEADER])
        {
            int flag = count;
            for(i; i<sizeof(temID25)+flag; i++)
            {
                temID25[i-flag] = msg2[i];
                //printf("%d\n", count);
                count++;
            }
            for(j=0; j<sizeof(temID25); j++)
            {
                //printf("%x\n", temID25[j]);
            }
        }
        
        //printf("[COUNT]: %d [i]: %d\n", count,i);
        printf("[TEMPLATE ID]: %d\n", msg2[count+SIZE_HEADER]);
        printf("\n");
        if(51 == msg2[count+SIZE_HEADER])
        {
            int flag = count;
            for(i; i<sizeof(temID51)+flag; i++)
            {
                temID51[i-flag] = msg2[i];
                //printf("%d\n", i-46);
                count++;
            }
            for(j=0; j<sizeof(temID51); j++)
            {
                //printf("%x\n", temID51[j]);
            }
        }
    }
    
}

void packet_3Template(int tam)
{
    int i, j, count=0;
    printf("tam: %d\n", tam);
    count = 0;

    if(230 == tam)
    {
        unsigned char *msg4;
        unsigned char temID53[TEMPLATE_HEADER+SIZE_T_ID_53];
        unsigned char temID24[TEMPLATE_HEADER+SIZE_T_ID_25];
        unsigned char temID51[TEMPLATE_HEADER+SIZE_T_ID_51];

        for(i=SIZE_UDP_HEADER;i<tam; i++)
        {
            msg4[i-SIZE_UDP_HEADER] = strData[i];
        }

        printf("[TEMPLATE ID]: %d\n", msg4[SIZE_HEADER]);
        printf("\n");
        if(53 == msg4[count+SIZE_HEADER])
        {
            for(i=0; i<sizeof(temID53); i++)
            {
                temID53[i] = msg4[i];
                count++;
            }
            for(j=0; j<sizeof(temID53); j++)
            {
                //printf("%x\n", temID53[j]);
            }
        }

        printf("[TEMPLATE ID]: %d\n", msg4[count+SIZE_HEADER]);
        printf("\n");
        if(24 == msg4[count+SIZE_HEADER])
        {
            int flag = count;
            //printf("i: %d, flag: %d, count: %d, temId24+flag: %d\n", i, flag, count, sizeof(temID24)+flag);
            for(i; i<sizeof(temID24)+flag; i++)
            {
                temID24[i-flag] = msg4[i];
                //printf("%x\n", msg2[i]);
                count++;
            }
            for(j=0; j<sizeof(temID24); j++)
            {
                //printf("%x\n", temID24[j]);
            }
        }

        printf("[TEMPLATE ID]: %d\n", msg4[count+SIZE_HEADER]);
        printf("\n");
        if(51 == msg4[count+SIZE_HEADER])
        {
            int flag = count;
            for(i; i<sizeof(temID51)+flag; i++)
            {
                temID51[i-flag] = msg4[i];
                //printf("%d\n", i-46);
                count++;
            }
            for(j=0; j<sizeof(temID51); j++)
            {
                //printf("%x\n", temID51[j]);
            }
        }
    }
}

void packet_2Template(int tam)
{
    int i, j, count=0;
    printf("tam: %d\n", tam);
    count = 0;

    if(186 == tam)
    {
        unsigned char *msg5;
        unsigned char temID53[TEMPLATE_HEADER+SIZE_T_ID_53];
        unsigned char temID51[TEMPLATE_HEADER+SIZE_T_ID_51];

        for(i=SIZE_UDP_HEADER;i<tam; i++)
        {
            msg5[i-SIZE_UDP_HEADER] = strData[i];
        }

        printf("[TEMPLATE ID]: %d\n", msg5[SIZE_HEADER]);
        printf("\n");
        if(53 == msg5[count+SIZE_HEADER])
        {
            for(i=0; i<sizeof(temID53); i++)
            {
                temID53[i] = msg5[i];
                count++;
            }
            for(j=0; j<sizeof(temID53); j++)
            {
                //printf("%x\n", temID53[j]);
            }
        }

        printf("[TEMPLATE ID]: %d\n", msg5[count+SIZE_HEADER]);
        printf("\n");
        if(51 == msg5[count+SIZE_HEADER])
        {
            int flag = count;
            for(i; i<sizeof(temID51)+flag; i++)
            {
                temID51[i-flag] = msg5[i];
                //printf("%d\n", i-46);
                count++;
            }
            for(j=0; j<sizeof(temID51); j++)
            {
                //printf("%x\n", temID51[j]);
            }
        }
    }
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
        printf("TAM: %d\n", tam);
        if(tam == 138)
        {
            packet_1Template(tam);
        }
        if(tam == 138)
        {
            packet_5Template(tam);
        }
        if(tam == 138)
        {
            packet_3Template(0);
        }
        if(tam == 138)
        {
            packet_2Template(0);
        }
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
    int i;
    printf("Client: \t");
	//scanf("%s", &buffer[0]);
    //for(i=0; i<2; i++)
    //{
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