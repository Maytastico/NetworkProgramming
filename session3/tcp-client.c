#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <memory.h>

#define MAXLINE 4096
#define PORT "13"

void err_quit(char *str);
void err_quit(char *str){
    printf("error: %s\n", str);
    exit(-1);
}

int resolve_address(char* i_hostname, struct sockaddr_in* po_serveradress){
    struct addrinfo hints, *result, *p;
    char ip4[INET_ADDRSTRLEN];
    // Initialize hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;  // AF_UNSPEC allows for both IPv4 and IPv6
    hints.ai_socktype = SOCK_STREAM;

    // Get address information
    int status = getaddrinfo(i_hostname, PORT, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return -1;
    }

    struct sockaddr_in *ipv4 = (struct sockaddr_in *)result->ai_addr;
    void* addr = &ipv4->sin_addr;

    inet_ntop(AF_INET, addr, ip4, INET_ADDRSTRLEN);
    // Free the memory allocated by getaddrinfo
    memcpy(po_serveradress, ipv4, INET_ADDRSTRLEN);
    freeaddrinfo(result);

    return 1;
}

int main(int argc, char **argv)
{
    int fd;
    int n;
    struct sockaddr_in serveradress;
    char buff[MAXLINE];


    if(resolve_address("ai.tillh.de", &serveradress) < 0) err_quit("Failed resolving adress");

    if (argc != 2) err_quit("usage: %s <host-ip>\n");

    if((fd = socket(AF_INET, SOCK_STREAM, 0))<=0) err_quit("Error creating socket");

    bzero(&serveradress, sizeof(serveradress));
    serveradress.sin_family = AF_INET;
    serveradress.sin_port = htons(13);

    /*if(inet_pton(AF_INET, argv[1], &serveradress.sin_addr)< 0){
        printf("Address seems to be a domainname...\n");
        printf("Resolving...");
        resolve_address(argv[1], &serveradress);
    }*/
    char ip4[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(serveradress.sin_addr), ip4, INET_ADDRSTRLEN);

    if(connect(fd, (struct sockaddr *) &serveradress, sizeof(serveradress))<0)
        err_quit("unable to connect to %s\n");

    while ((n = read(fd, buff, MAXLINE))>0){
        buff[n] = 0;
        printf("%s\n", buff);
    }
    close(fd);
}