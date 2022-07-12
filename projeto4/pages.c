#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define dataSize 10     // quantidade de dados que serao armazenados ao total
#define memorySize 4    // tamanho da memoria fisica
#define swapSize 6      // tamanho da memoria de swap
#define amountPages 10  // qntde de paginas
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
int data[dataSize] = {12, 52, 33, 84, 65, 36, 97, 18, 59, 310}; // para testar

void initPaging(page *nodeAux, int pos, int status)
{
  nodeAux->index = pos;
  memset(nodeAux->reference, 0, bitsReference);
  nodeAux->modified = 0;
  if (status == 0) // se ela esta na memoria
  {
    nodeAux->adress = pos; // pagina de indice 0 correspondera ao quadro 0
    nodeAux->inMemory = status;
  }
  else
  {
    nodeAux->adress = status;
    nodeAux->inMemory = status;
  }
}

int main()
{
  int i, j, l, k = 0; // variaveis auxiliares
  page *nodeAux;
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
  for (int z = 0; z < amountPages; z++)
  {
    printf("index da pag: %d - adress %d - modified %d - inMemory %d\n", pages[z].index, pages[z].adress, pages[z].modified, pages[z].inMemory);
    if (pages[z].adress != -1)
      printf("conteudo %d\n", data[pages[z].adress]);
    else
      printf("sem link\n");
  }
  return 0;
}