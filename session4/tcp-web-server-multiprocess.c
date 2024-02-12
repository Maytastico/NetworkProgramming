//
// Created by maylis on 11.02.24.
//
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
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
    char line[100];
    time_t ticks;
    pid_t pid;
    FILE *fptr;

    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) err_quit("Unable to open socket");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(80);	/* daytime server */

    // Open the file in read mode
    fptr = fopen("index.html", "r");

    // Check if the file was opened successfully
    if (fptr == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }
    fseek(fptr, 0, SEEK_END);
    long fsize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);  /* same as rewind(fptr); */

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, fptr);
    fclose(fptr);


    if(bind(listenfd, (const struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) err_quit("Unable to bind port");

    listen(listenfd, BACKLOG);


    for ( ; ; ) {
        connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);

        if((pid=fork())<0){
            printf("error handling new conenction");
        }
        if(pid == 0){


            printf("%s", string);

            char* http = "HTTP/1.0 200 OK\nContent-Type: text/html\n\n";
            write(connfd,http, strlen(http));
            write(connfd,string, strlen(string));


        }

        close(connfd);

    }
}