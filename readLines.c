#include <stdio.h>
#include <stdlib.h>

// FOUND IN STACKOVERFLOW:
// https://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings
#define N 256

char buffer[N];
int string_size, read_size;

char* ReadFile(char *filename, int SEEK)
{
   FILE *file = fopen(filename, "r");

    while (fgets(buffer, sizeof(buffer), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        printf("%s", buffer); 
        break;
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);

    return buffer;
}

int main()
{
    char *string = ReadFile("example.txt", SEEK_SET);

    for(int i = 0; i < 30; i++) {
        printf("buffer: %c\n", buffer[i]);
    }

    return 0;
}
