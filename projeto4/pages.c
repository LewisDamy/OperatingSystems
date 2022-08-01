#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define dataSize 52     // quantidade de dados que serao armazenados ao total
#define memorySize 32   // tamanho da memoria fisica
#define swapSize 20     // tamanho da memoria de swap
#define amountPages 52  // qntde de paginas
#define bitsReference 8 // qntde de bits de referencia da pagina

typedef struct pageNode
{
  int index;    // numero da pagina
  int dataInfo; // informacao sobre o dado requisitado
  int bitsRef;  // referencias ao longo de 8 ciclos de clock
  int adress;   // endereco fisico nos quadros de pagina
  int modified; // checar se foi modificada
  int inMemory; // checar se esta na memoria
} page;

page pages[amountPages];    // memoria virtual
int swapArea[swapSize];     // SWAP
int memoryArea[memorySize]; // RAM
char data[dataSize];        // vetor de dados utilizados na aplicacao
int input[50];              // palavras de no maximo 50 caracteres

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

void initPaging(int pos, int status, int aux)
{
  pages[pos].index = pos;
  pages[pos].bitsRef = 0;
  pages[pos].modified = 0;
  if (status == 0) // se ela esta na memoria
  {
    pages[pos].adress = pos;      // pagina de indice 0 correspondera ao quadro 0
    pages[pos].inMemory = status; // informa se esta na memoria
    pages[pos].dataInfo = (int)memoryArea[aux];
  }
  else
  {
    pages[pos].adress = status; // adress recebe -1 por nao estar na memoria
    pages[pos].inMemory = status;
    pages[pos].dataInfo = (int)swapArea[aux];
  }
}

void initMemory()
{
  int i, l;
  int j;
  int k = 0;
  int aux = 0;
  int aux2 = 0;
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
    if (l < memorySize)
    {
      initPaging(l, 0, aux); // preenchendo com dados em memoria RAM
      aux++;
    }
    else
    {
      initPaging(l, -1, aux2); // preenchendo com dados em SWAP area
      aux2++;
    }
  }
}

void reader(int events)
{
  for (int i = 0; i < events; i++)
  {
    // ler a palavra até enter (gerada randomicamente)
    // colocar em cada indice do vetor input (var global) a letra em int
  }
}

void pagesMenaging()
{
  // for do tamanho do vetor input
  // se letra usada na palavra tiver na memoria bitsRef = 1
  // se nao tiver sido usada na palavra e tiver na memoria bitsRef = 0
  // se tiver na palavra e nao tiver na memoria -> aging
}

void aging()
{
}

int main()
{
  int i, p, m, n; // variaveis auxiliares
  char *dataAux;
  int events;
  dataAux = data;
  initData(dataAux);
  initMemory();
  // loop while 1
  printf("Insira a quantidade de palavras (eventos)\n");
  scanf("%d", &events);
  // reader(events);
  // pagesMenaging;

  /* ------------------- prints de teste ----------------------- */
  // print do vetor data
  printf("-------- data ---------\n");
  for (m = 0; m < dataSize; m++)
  {
    printf("%c ", *(dataAux + m));
  }

  // print da struct pageNode
  printf("\n-------- pages ---------\n");
  for (int z = 0; z < amountPages; z++)
  {
    printf("index da pag: %d - adress %d - modified %d - inMemory %d\n", pages[z].index, pages[z].adress, pages[z].modified, pages[z].inMemory);
    printf("conteudo %d\n", pages[z].dataInfo);
    if (pages[z].adress == -1)
      printf("sem link\n");
    printf("%d ", pages[z].bitsRef);
    printf("\n");
  }

  // print da SWAP
  printf("\n-------- SWAP ---------\n");
  for (n = 0; n < swapSize; n++)
  {
    printf("%c ", swapArea[n]);
  }

  // print da memoria RAM
  printf("\n-------- RAM ---------\n");
  for (p = 0; p < memorySize; p++)
  {
    printf("%c ", memoryArea[p]);
  }
  return 0;
}
