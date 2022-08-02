#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define memoryRAMsize 32 // tamanho da memoria fisica
#define swapSize 20      // tamanho da memoria de swap
#define amountPages 52   // qntde de paginas
#define TAM_MAX 1000

typedef struct pageNode
{
    int index;     // numero da pagina
    int reference; // quantidades de referencias
    int adress;    // endereco fisico nos quadros de pagina
    int modified;  // checar se foi modificada
    int inMemory;  // checar se esta na memoria  -> 0 = RAM | -1 = swapMemory
} page;

page pages[amountPages];
int swapArea[swapSize];
int memoryRAMarea[memoryRAMsize];
int stringOfReference[TAM_MAX];

void initPaging(int pos, int status)
{
    pages[pos].index = pos;
    pages[pos].reference = 0;
    pages[pos].modified = 0;
    if (status == 0) // se ela esta na memoria
    {
        pages[pos].adress = pos;      // pagina de indice 0 correspondera ao quadro 0
        pages[pos].inMemory = status; // informa se esta na memoria
    }
    else
    {
        pages[pos].adress = status; // adress recebe -1 por nao estar na memoria
        pages[pos].inMemory = status;
    }
}

void initMemory()
{
    int i, j, l, k = 0;

    for (i = 0; i < memoryRAMsize; i++)
    {
        memoryRAMarea[i] = i;
    }
    k = i++;
    for (j = 0; j < swapSize; j++)
    {
        swapArea[j] = k;
        k++;
    }
    for (l = 0; l < amountPages; l++)
    { // preenchendo a memoria virtual
        if (l < memoryRAMsize)
        {
            initPaging(l, 0); // preenchendo com dados em memoria RAM
        }
        else
        {
            initPaging(l, -1); // preenchendo com dados em SWAP area
        }
    }
}

void referencesCreator(int ref)
{
    int i;
    srand(time(NULL));
    printf("String de referências: ");
    for (i = 0; i < ref; i++)
    {
        stringOfReference[i] = (rand() % (amountPages + 1));
    }
    stringOfReference[i] = -1;
    for (int j = 1; j < ref; j++)
    {
        printf("%d ", stringOfReference[j]);
    }
    // printf("%d ", stringOfReference[i]);
    printf("%d \n");
}

void bin(unsigned n)
{ // funcao para imprimir os bits de referencia
    unsigned i;
    for (i = 1 << 8; i > 0; i = i / 2)
    {
        (n & i) ? printf("1") : printf("0");
    }
}

int whichIsSmallest()
{
    int i, aux = 0;
    for (i = 1; i < amountPages; i++)
    {
        if (pages[i].reference < pages[aux].reference)
        {
            aux = i;
        }
    }
    return pages[aux].index;
}

int isPageAvailable(int i)
{
    int n;
    int requestedPage = stringOfReference[i];
    for (n = 0; n < amountPages; n++)
    {
        if (pages[n].index == requestedPage)
        {
            if (pages[n].inMemory == 0)
                pages[requestedPage].reference += 128;
            return 0;
        }
    }
    return -1;
}

void swapping(int pageVictim, int requestedPage)
{
    int i, j;
    for (j = 0; j < swapSize; j++)
    {
        if (requestedPage == swapArea[j])
        {
            swapArea[j] = pageVictim;
            pages[pageVictim].adress = -1;
            pages[pageVictim].inMemory = -1;
            pages[pageVictim].reference = 0;
            break;
        }
    }
    for (i = 0; i < memoryRAMsize; i++)
    {
        if (pageVictim == memoryRAMarea[i])
        {
            memoryRAMarea[i] = requestedPage;
            pages[requestedPage].adress = i;
            pages[requestedPage].inMemory = 0;
            pages[requestedPage].reference = 128;
            break;
        }
    }
}

void pushNonReferedBits()
{ // TODO
  // Faz interacao em todas as paginas na memoria principal
  // empurra todos os bits nao referenciados das paginas na
}

void printBits(int index)
{
    // printf("Bits: ");
    bin(pages[index].reference);
}

int pageFault(int i)
{
    int requestedPage = stringOfReference[i];
    int pageVictim = whichIsSmallest();
    swapping(pageVictim, requestedPage);
}

void pageIterationPrint(int randInt, int z)
{
    printf("RAND INT: %d\n", randInt);
    //   for (int z = 0; z < amountPages; z++) {
    printf("\n---------PAGE %d---------", pages[z].index);
    printf("\nBEFORE: ");
    printf("mod %d | inMemory %d\n", pages[z].modified, pages[z].inMemory);
    printf("Bits: ");
    bin(pages[z].reference);
    printf(" | Decimal: %d\n", pages[z].reference);
    printf("\nAFTER: ");
    // pages[z].reference = ;
    printf("mod %d | inMemory %d\n", pages[z].modified + 1, pages[z].inMemory);
    printf("Bits: ");
    bin(pages[z].reference);
    printf(" | Decimal: %d\n", pages[z].reference);
    // }
}

int main(void)
{
    int i, j, k, ref;

    initMemory();
    printf("Insira a qntde de referências à memória: ");
    scanf("%d", &ref);
    referencesCreator(ref); // cria a string de referencia à memoria
    printf("memoria RAM: ");
    for (i = 0; i < memoryRAMsize; i++)
    {
        printf("%d ", memoryRAMarea[i]);
    }
    printf("\n");
    printf("memoria SWAP: ");
    for (int j = 0; j < swapSize; j++)
    {
        printf("%d ", swapArea[j]);
    }
    printf("\n");
    printf("paginas virtuais: ");
    for (k = 0; k < amountPages; k++)
    {
        printf("%d ", pages[k].index);
    }
    printf("\n");

    /*for (i = 0; i < TAM_MAX; i++)
    {
        if (isPageAvailable(i) == 0) // aqui ja atualiza bits de referencia
        {
            printf("ta em memoria");
        }
        else
        {
            printf("nao ta em memoria");
            pageFault(i);
        }
        pushNonReferedBits();
    }*/
    return 0;
}
