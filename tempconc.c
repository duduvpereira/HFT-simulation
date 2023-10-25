#include<stdio.h>

int main()
{
    unsigned char x[3] = 
    {0x00, 0x09, 0x01};

    //int y = ((x[2] | 0x00) << 2) + ((x[1] | 0x00) << 0);

    int y = x[1] | (x[2]<<8);

    printf("aaa: %d\n", y);
}