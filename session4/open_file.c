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

    // Check if the file was opened successfully
    if (filePointer == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Read and print each line of the file
    while (fgets(line, sizeof(line), filePointer)) {
        printf("%s", line);
    }

    // Close the file
    fclose(filePointer);

    return 0;
}