//
// Created by maylis on 11.02.24.
//
#include <strings.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

#define MAXLINE 4096

void err_quit(char *str){
    printf("error: %s\n", str);
    exit(-1);
}


int
main(int argc, char **argv){
    int fd;
    int n;
    char buff[MAXLINE];

    struct addrinfo hints, *res;
    int status;

    if(argc != 2) err_quit("argument error");

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) err_quit("invalid name / address");
    struct sockaddr_in *serveraddr = (struct sockaddr_in *)res->ai_addr;

    serveraddr->sin_port = htons(13);

    if((fd = socket(AF_INET, SOCK_STREAM, 0))<=0) err_quit("error creating socket");

    if((connect(fd, (struct sockaddr * ) serveraddr, sizeof (*serveraddr)) < 0 )) err_quit("unnable to connect");

    while((n = read(fd, buff, MAXLINE)) >0 ){
        buff[n] = 0;
        printf("%s\n", buff);
    }

    close(fd);
}