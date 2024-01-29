/* fork3.c
   create child process
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[]) {
	int i;
	pid_t pid;
	int status;
	int maxprocs = 5;
	int procs;

    srand((unsigned int) time(NULL));

	for(procs=0; procs < maxprocs; procs++) {
        int rnd = rand()%10+1;
		if ((pid = fork()) < 0) {
			printf("error forking\n");
			return 0;
		}
		if (pid == 0) {
			// Child
            printf("Process %d started with sleeptime %d\n", procs, rnd);
			for(i=0;i<5;i++) {
				printf("Child in loop number %d\n",i);
                sleep(rnd);
			}
			printf("End of child procs %d\n", procs);
			return(0);
		}
	}
	while(waitpid(-1,&status,0) > 0) ;
	printf("Parent completed\n");
	return 0;
}
