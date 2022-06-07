#include <stdio.h>
 #include <string.h>
 #include <stdlib.h>

 char *buffer = NULL;
 int string_size, read_size;

 // struct of data with key values
 typedef struct {
     char *value;
     int key;
 } data;

 int readFile(char *filename)
 {
   // FOUND IN STACKOVERFLOW:
   // https://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings
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
     buffer = (char *)malloc(sizeof(char) * (string_size + 1));

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

   return 0;
 }

 data *createData(char *value, int key) {
     data *newData;
     // printf("Value before: %s\n", value);
     // newData->value = malloc(strlen(value + 1));
     newData->value = value;
     // printf("Value as newData: %s\n", newData->value);
     newData->key = key;

     return newData;
 }

 // Create function to find the next word in the initBuffer
 int findWordBuffer() {
     int sizeWord = 0;
     int nextWord = 0;

     // iterate through the initBuffer
     for(int i = 0; i < 30; i++) {
         // check if it's a letter A-Z or a-z
         if((buffer[i] >= 65 && buffer[i] <= 90) || (buffer[i] >= 97 && buffer[i] <= 122)) {
             printf("%c", buffer[i]); 
             sizeWord++;
         }
         // check if is "space" or "," or "." or "\n"
         if (buffer[i] == 32 || buffer[i] == 44 || buffer[i] == 46 || buffer[i] == 59 || buffer[i] == 58 || buffer[i] == 10) {
             printf("\nsizeWord: %i\n", sizeWord);
             printf("\nfound: %c, in i = %i\n", buffer[i], i);
             sizeWord = 0;
         }
     }
     // TODO
     // funcao deve particionar " " ou "," ou "." retornando o indice
     // partindo de uma iteracao no initBuffer

     return 0;
 }

 void map() {
     // TODO
         // Call function to find next word in buffer
         // Call function to createData

         // Continue as producer funct in prod_cons.c file

 }

 int main(int argc, char **argv) {
     data p;

    if (readFile("text.txt") != 0)
     {
     printf("erro de leitura");
     // tratar erro
     }
     // sample of how text will be accessed in initBuffer
     // char text[] = "Text fsad";
     // for (int i = 0; i < strlen(text); i++) {
     //     printf("%c ", text[i]);
     // }
     // printf("\n");

     findWordBuffer();


     // sample of how to create an data type
     // char* value = "text";
     // p = *createData(value, 1);
     // printf("value: %s, key: %i\n", p.value, p.key);

 }