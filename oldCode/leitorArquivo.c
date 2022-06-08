#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ler()
{
  FILE *file = fopen("text.txt", "r");
  char string[30];

  if (file != NULL)
  {
    printf("\tDados lidos do arquivo:\n");
    while (fscanf(file, "%s", string) != -1)
    {
      for (int i = 0; i < sizeof(string); i++)
      {
        if (string[i] == 32 || string[i] == 44 || string[i] == 46 || string[i] == 59 || string[i] == 58 || string[i] == 10)
        {
          string[i] = '\0';
        }
      }
      // aqui chama a funcao para inserir
      printf("%s \n", string);
    }
    fclose(file);
  }
  else
    printf("\nERRO ao abrir arquivo!\n");
}

int main()
{
  ler();
  return 0;
}