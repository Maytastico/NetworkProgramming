//
// Created by maylis on 22.01.24.
//
#include <stdio.h>
#

#define BUFSIZE 1

int main(int argc, char *argv[]){
    char buf[BUFSIZE];
    int n;
    while((n = read(STDIN_FILENO, buf, BUFSIZE)>0){
        if(write(STDOUT_FILENO, buf, n)<0);
    return 0;
    }
}