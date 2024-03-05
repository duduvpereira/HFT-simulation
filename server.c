#include<stdio.h>
#include<stdlib.h>
#include<string.h>    
#include<netinet/ip_icmp.h>   
#include<netinet/udp.h>   
#include<netinet/tcp.h>   
#include<netinet/ip.h>    
#include<sys/socket.h>
#include<arpa/inet.h>
#include <math.h> 
#include <time.h>

/* Frame (138 bytes) */
static const unsigned char pkt[138] = {
0x01, 0x00, 0x5e, 0x72, 0x65, 0xcc, 0xa0, 0x36, /* ..^re..6 */
0x9f, 0xc7, 0x1d, 0x44, 0x81, 0x00, 0x07, 0x55, /* ...D...U */
0x08, 0x00, 0x45, 0x00, 0x00, 0x78, 0xb1, 0x65, /* ..E..x.e */
0x40, 0x00, 0x64, 0x11, 0xc3, 0x1b, 0x0a, 0x67, /* @.d....g */
0x42, 0x4e, 0xef, 0x72, 0x65, 0xcc, 0xa6, 0x24, /* BN.re..$ */
0xd9, 0x03, 0x00, 0x64, 0x2f, 0xc0, 0x32, 0x00, /* ...d/.2. */
0xbf, 0x07, 0xfb, 0xd9, 0x00, 0x00, 0x85, 0xd3, /* ........ */
0xdc, 0x1d, 0xac, 0x33, 0x6d, 0x17, 0x4c, 0x00, /* ...3m.L. */
0x50, 0xeb, 0x40, 0x00, 0x37, 0x00, 0x02, 0x00, /* P.@.7... */
0x07, 0x00, 0x4a, 0x58, 0x77, 0x48, 0x17, 0x00, /* ..JXwH.. */
0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x0d, /* ........ */
0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc7, 0xf9, /* ......^t */
0xb2, 0x1d, 0xac, 0x33, 0x6d, 0x17, 0x40, 0x00, /* w..3m.9. */
0x00, 0x00, 0x01, 0xe1, 0x51, 0x1f, 0xac, 0x33, /* .......3 */
0x6d, 0x17                                      /* m. */
};

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

unsigned char arrays[2][500];
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
    serv_addr.sin_port = htons(8001);
    
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

send_packet_first(int port, int p)
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
        bytes = sendto(sockfd, pkt, sizeof(pkt), 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
        if(bytes <= 0)
        {
            printf("ERRO SEND\n");
        }
        printf("Sending Template: 55 Execution Summary\n", bytes);
}

send_packet(int port, int p, unsigned char *snd)
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
        bytes = sendto(sockfd, snd, 1000, 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
        if(bytes <= 0)
        {
            printf("ERRO SEND\n");
        }
        printf("Sending template id: 53 Trade\n");
}

unsigned char strData[1000];

void receive_packet()
{
    int i;
    uint32_t templateId;
    int tam;
    printf("receving packet....\n");
    
    tam = recv(sockfd, strData, 1000, 0);
    struct pkt53 *rcv = (struct pkt53 *)strData; 
    //printf("tam: %d\n", tam);
    //for(i=0;i<30;i++)
    //{
        printf("%d\n", rcv->templateId);
        send_packet(8003, 0, rcv);
        send_packet(8002, 0, rcv);
    //}
    
}



int main (void)
{
    //printf("teste\n");
    //printf("tam: %d\n", sizeof(pkt));
    int i;
    

    int p;
    create_socket();
    //printf("pacote: ");
    //scanf("%d", &p);
    send_packet_first(8003, 0);
    send_packet_first(8002, 0);

    receive_packet();
    //int port;
    //scanf("%d", &port);
    //send_packet(port);     
  
    return 0; 
}