#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *buffer = NULL;
int string_size, read_size;

// struct of data with key values
typedef struct
{
  char *value;
  int key;
  struct data *next;
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

int createData(char *value, int key)
{
  printf("oi");
  printf("%c\n", *value);
  /*data *newData;
  // printf("Value before: %s\n", value);
  // newData->value = malloc(strlen(value + 1));
  newData->value = value;
  // printf("Value as newData: %s\n", newData->value);
  newData->key = key;*/

  return 0;
}

// Create function to find the next word in the initBuffer
int parseBuffer()
// depois de um ". " ou ", " ele ta repetindo a primeira letra da prox palavra
{
  int i = 0, j;
  int nextWord;
  char string[50];
  char start, end; // string's indexes
  string[i] = buffer[0];
  for (j = 1; j < 90; j++)
  {
    if (buffer[j] == 32 | buffer[j] == 44 | buffer[j] == 46 | buffer[j] == 59 | buffer[j] == 58 | buffer[j] == 10)
    // index == ' ' ou ',' ou '.' ou ';' ou ':' ou quebra de linha
    {
      string[j] = '\0';
      printf("index da palavra eh %d \n", i);
      printf("%c\n", buffer[i]);
      // createData(&string[i], 1);
      nextWord = j;
      while (buffer[nextWord] == 32 | buffer[nextWord] == 44 | buffer[nextWord] == 46 | buffer[nextWord] == 59 | buffer[nextWord] == 58 | buffer[nextWord] == 10)
      {
        nextWord++;
      }
      i = nextWord;
    }
    else
    {
      string[j] = buffer[j];
    }
  }

  // TODO
  // funcao deve particionar " " ou "," ou "." retornando o indice
  // partindo de uma iteracao no initBuffer
  return 0;
}

void map()
{
  // TODO
  // Call function to find next word in buffer
  // Call function to createData

  // Continue as producer funct in prod_cons.c file
}

int main(int argc, char **argv)
{
  // p has to be a list with struct indexes
  data p;
  int i;
  if (readFile("text.txt") != 0)
  {
    printf("erro de leitura");
    // tratar erro
  }
  parseBuffer();
  // tratar erro

  // sample of how text will be accessed in initBuffer
  /*char text[] = "Text fsad";
  for (int i = 0; i < strlen(text); i++) {
      printf("%c ", text[i]);
  }
  printf("\n");
  */

  // sample of how to create an data type
  /*char *value = "text";
  p = *createData(value, 1);
  printf("value: %s, key: %i\n", p.value, p.key);*/
}