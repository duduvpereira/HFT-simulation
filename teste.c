#include<stdio.h>


int main()
{
    unsigned char *buff;
    unsigned char temp[4] = {0,1,2,3};
    int i;
    for(i=0;i<4;i++)
    {
        buff[i] = temp[i];
    }
    printf("aqui\n");
    for(i=0;i<4;i++)
    {
        printf("buff: %d\n", buff[i]);
    }
}