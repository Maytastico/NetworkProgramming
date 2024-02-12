//
// Created by maylis on 11.02.24.
//
#include <stdlib.h>
#include <stdio.h>

int main(void){
    FILE *filePointer;
    char line[100]; // Assuming each line in the file is no longer than 100 characters

    // Open the file in read mode
    filePointer = fopen("session4/index.html", "r");

    fseek(filePointer, 0, SEEK_END);
    long fsize = ftell(filePointer);
    fseek(filePointer, 0, SEEK_SET);  /* same as rewind(filePointer); */

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, filePointer);

    printf("%s", string);
    fclose(filePointer);

    return 0;
}