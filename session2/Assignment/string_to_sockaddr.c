//
// Created by maylis on 04.02.24.
//
#include <arpa/inet.h>
#include <stdio.h>
#include <limits.h>

void itob_(unsigned  long x, char *buf);

int main(void){
    struct sockaddr_in sa;

    inet_pton(AF_INET, "127.0.0.1", &(sa.sin_addr));

    char ip4[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);

    printf("Your IP-Address is: %s\n", ip4);
    printf("Your IP-Address in Dezimal: %d\n", sa.sin_addr);
}



void itob_(unsigned  long x, char *buf)
{
    unsigned char *ptr = (unsigned char *)&x;
    int pos = 0;
    for (int i = sizeof(int) - 1; i >= 0; i--)
        for (int j = CHAR_BIT - 1; j >= 0; j--)
            buf[pos++] = '0' + !!(ptr[i] & 1U << j);
    buf[pos] = '\0';
}