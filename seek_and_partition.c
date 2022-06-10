#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ler()
{
  FILE *file = fopen("example.txt", "r");
  char string[30];
  int i = 0;
  int bits = 0;
  int end = 40;
  int start = 30;
  char aux;
  // inicializando o vetor string
  memset(string, 0, 30);

  if (file != NULL)
  {
    // ira ler a partir do indice start
    fseek(file, start, SEEK_CUR);
    printf("\tDados lidos do arquivo:\n");
    /*enquanto a qntde limite de bits de cada mapper
    nao eh atingida*/
    while (bits < (end - start))
    {
      fscanf(file, "%c", &aux);
      // se aux for uma letra, sera inserida no vetor string
      if (aux != 32 && aux != 44 && aux != 46 && aux != 59 && aux != 58 && aux != 10)
      {
        string[i] = aux;
        i++;
        /*se for o ultimo bit a ser pego
        printa mesmo nao terminando a palavra*/
        if ((end - start) - bits == 1)
        {
          printf("%s.\n", string);
        }
      }
      else
      {
        // aux eh uma pontuacao indicando o fim de uma palavra
        if (i != 0)
        {
          string[i] = '\0';
          // substituir o printf pela chamada da funcao
          printf("%s.\n", string);
        }
        memset(string, 0, 30);
        i = 0;
      }
      bits++;
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
