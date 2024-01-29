/* cat2.c
   simple version of cat: concatenate files
   cat1 copy one file to stdout
   if filename not given on the command line, then use stdin as input
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1000

int open_file(char *file_path){
    int fd;
    fd = open(file_path,O_RDONLY);
    if (fd < 0) {
        printf("error opening %s\n",file_path[1]);
        return -1;
    }
    return fd;
}

int write_buffer_to_file(int file_handler, char *buffer){
    int n;
    while ((n=read(file_handler,buffer, BUFSIZE)) > 0) {
        if (write(STDOUT_FILENO,buffer,n) != n) {
            printf("%s", &buffer[1]);
        }
    }
    close(file_handler);
}

int main(int argc, char*argv[]) {
	int fd; // file handler
	char *buf[BUFSIZE]; // Buffer mit einem Byte
	int n;
	if (argc > 1) {
        int i = 1;
        while (argv[i] != 0){
		    fd = open_file(argv[i]);
            if(fd == -1) return -1;
            write_buffer_to_file(fd, buf);
            i++;
        }
	}
	else
		fd = STDIN_FILENO;
        write_buffer_to_file(fd, buf);
	return 0;
}


