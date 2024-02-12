//
// Created by maylis on 11.02.24.
//
#include <strings.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define BACKLOG 10
#define MAXLINE 4096

void err_quit(char *str){
    printf("error: %s\n", str);
    exit(-1);
}

int
main(int argc, char **argv)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) err_quit("Unable to open socket");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(7);	/* daytime server */

    if(bind(listenfd, (const struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) err_quit("Unable to bind port");

    listen(listenfd, BACKLOG);

    for ( ; ; ) {
        connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));

        close(connfd);
    }
}