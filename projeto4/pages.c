#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define dataSize 52     // quantidade de dados que serao armazenados ao total
#define memorySize 32   // tamanho da memoria fisica
#define swapSize 20     // tamanho da memoria de swap
#define amountPages 52  // qntde de paginas
#define bitsReference 8 // qntde de bits de referencia da pagina
// qntde de paginas = area de swap + RAM certo????

typedef struct pageNode
{
  int index;                    // numero da pagina
  int reference[bitsReference]; // referencias ao longo de 8 ciclos de clock
  int adress;                   // endereco fisico nos quadros de pagina
  int modified;                 // checar se foi modificada
  int inMemory;                 // checar se esta na memoria
} page;

page pages[amountPages];
int swapArea[swapSize];
int memoryArea[memorySize];
char data[dataSize];

void initData(char *dataAux)
{
  int i, letter = 122; // 122 corresponde a 'z'
  for (i = 0; i < dataSize; i++)
  {
    if (letter > 96) // preenchendo de z ate a
    {
      *(dataAux + i) = letter;
      letter--;
    }
    else
    {
      *(dataAux + i) = letter - 6; // o decimal correspondente a
      letter--;                    // Z comeca em 90 por isso a subtracao
    }
  }
}

void initPaging(page *nodeAux, int pos, int status)
{
  nodeAux->index = pos;
  memset(nodeAux->reference, 0, bitsReference);
  nodeAux->modified = 0;
  if (status == 0) // se ela esta na memoria
  {
    nodeAux->adress = pos;      // pagina de indice 0 correspondera ao quadro 0
    nodeAux->inMemory = status; // informa se esta na memoria
  }
  else
  {
    nodeAux->adress = status; // adress recebe -1 por nao estar na memoria
    nodeAux->inMemory = status;
  }
}

int main()
{
  int i, j, l, k = 0; // variaveis auxiliares
  page *nodeAux;
  char *dataAux;
  dataAux = data;
  initData(dataAux);

  for (i = 0; i < memorySize; i++) // preenchendo a memoria RAM com os primeiros indices
  {                                // do vetor data
    memoryArea[i] = data[i];
  }
  for (j = i; j < dataSize; j++) // preenchendo a swap com o restante do vetor data
  {
    swapArea[k] = data[j];
    k++;
  }
  for (l = 0; l < amountPages; l++) // preenchendo a memoria virtual
  {
    nodeAux = &pages[l];
    if (l < memorySize)
    {
      initPaging(nodeAux, l, 0); // preenchendo com dados em memoria RAM
    }
    else
    {
      initPaging(nodeAux, l, -1); // preenchendo com dados em SWAP area
    }
  }

  /* ------------------- prints de teste ----------------------- */
  // print do vetor data
  for (int m = 0; m < dataSize; m++)
  {
    printf("%c ", *(dataAux + m));
  }
  printf("\n");

  // print da struct pageNode
  for (int z = 0; z < amountPages; z++)
  {
    printf("index da pag: %d - adress %d - modified %d - inMemory %d\n", pages[z].index, pages[z].adress, pages[z].modified, pages[z].inMemory);
    if (pages[z].adress != -1)
      printf("conteudo %d\n", data[pages[z].adress]);
    else
      printf("sem link\n");
    for (int w = 0; w < bitsReference; w++)
    {
      printf("%d ", pages[z].reference[w]);
    }
    printf("\n");
  }
  return 0;
}
