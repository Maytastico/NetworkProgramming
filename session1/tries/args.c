#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int i;
    printf("PID %d\n", getpid());

    for (int j = 0; j < argc; ++j) {
        printf("argv[%d]=%s\n", j, argv[j]);
    }
}