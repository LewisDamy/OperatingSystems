#include <stdio.h>
#include <stdlib.h>

// FOUND IN STACKOVERFLOW:
// https://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings

char *buffer = NULL;
int string_size, read_size;

char* ReadFile(char *filename)
{
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       // Seek the last byte of the file
       fseek(handler, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(handler);
       printf("string_size: %i\n", string_size);
       // go back to the start of the file
       rewind(handler);

       // Allocate a string that can hold it all
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
}

int main()
{
    char *string = ReadFile("text.txt");

    // test of buffer print
    // for(int i = 0; i < 10; i++) {
    //     printf("buffer: %c\n", buffer[i]);
    // }

    return 0;
}
