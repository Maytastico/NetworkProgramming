//
// Created by maylis on 29.01.24.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void ){
    int i;
    int pid;
    int status;

    if ((pid = fork())<0){
        //failed
        printf("Error forking\n");
        return(-1);
    }else if (pid == 0){
        //child
        for (i = 0; i<5;i++){
            printf("Child loop i=%d\n", i);
            sleep(2);
        }
    }else{
        // parent
        for (i = 0; i<5;i++){
            printf("Parent loop i=%d\n", i);
            sleep(1);
        }
        if((pid = waitpid(pid, &status, 0))<0){
            printf("Error Waiting  for child\n");
            return(-1);
        }
        printf("End of Parent");
        return 0;

    }
}