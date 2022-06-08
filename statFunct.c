#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

int sizeText(char *fileSize);

int main(void) {
    
    char *file = "example.txt";  // name of the file
    
    int result = sizeText(file); // call the function and save the amount of bits 

    printf("Size file: %i\n", result);
}

int sizeText(char *fileSize) {
    // get the name of file
    char *file = fileSize;
    // define the variable to hold the size
    int sizeFile;
    // allocates memory for stat structure
    struct stat *buff = malloc(sizeof(struct stat));
    // always set errno to zero first, in case there's some error
    errno = 0;

    // run the function stat, passing the file to read, and the buffer to save the value
    if(stat(file, buff) == 0) { // int stat(const char *restrict pathname, struct stat *restrict statbuf);
        // save the value of the file
        sizeFile = buff->st_size;
        printf("Size of '%s' is %i bytes.\n", file, sizeFile);
        // printf("size: %i\n", sizeFile);
    } else {
        perror(file); // if something went wrong
    }
    free(buff);

    return sizeFile;
}