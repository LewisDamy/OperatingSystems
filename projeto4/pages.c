#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define memoryRAMsize 3 // tamanho da memoria fisica
#define swapSize 2      // tamanho da memoria de swap
#define amountPages 5   // qntde de paginas
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
int pushedOrNot = false;


// Kaquete para fazer os prints
int breaker1 = 0;
int breaker2 = 0;
int hasSwapped = 0;


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

// funcao para iniciar a memoria
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

// funcao auxiliar para imprimir os bits de referencia
void bin(unsigned n) { 
    unsigned i;
    for (i = 1 << 7; i > 0; i = i / 2)
    {
        (n & i) ? printf("1") : printf("0");
    }
}

void printBits(int index)
{
    printf("Bits: ");
    bin(pages[index].reference);
    printf("\n");
}

// funcao para saber qual valor e o menor dentre os da RAM
int whichIsSmallest(void) { 
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

// funcao para empurrar a referencia de bits
void pushNonReferedBits() 
{ 
    int temp = 0;
    // Faz interacao em todas as paginas na memoria principal
    for(int i = 0; i < memoryRAMsize; i++) { 
        // empurra todos os bits nao referenciados das paginas na memoria principal
        temp = pages[i].reference;
        pages[i].reference = temp>>1;
    }
    
}

// funcao para saber se a pagina esta na RAM e incrementar 1 bit na referencia
int isPageAvailable(int i)
{
    int n;
    int requestedPage = stringOfReference[i];
    for (n = 0; n < amountPages; n++)
    {
        if (pages[n].index == requestedPage)
        {
            if (pages[n].inMemory == 0) {
                pages[requestedPage].reference += 128;
            }
            return 0;
        }
    }
    return -1;
}

// funcao que tira a pagina da memoria RAM menos acessada pela requisitada na swapMemory
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

// busca pagina que nao esta na RAM
int pageFault(int index) 
{
    int requestedPage = stringOfReference[index];
    int pageVictim = whichIsSmallest();
    swapping(pageVictim, requestedPage);
    return 0;
}

// funcao para imprimir as paginas
void pagePrint(int interation, int pageToSearch) {

    printf("---------ITERATION: %i | Searching for page index: %i ---------\n\n", interation, pageToSearch);

    for(int i = 0; i < amountPages; i++) {
        if(pages[i].inMemory == 0) {
            if(breaker1 == 0) {
                printf("---------RAM Memory---------\n\n");
                breaker1 = -1;
            }
            printf("index: %i | address: %i | mod: %i | inMemory: %i \nBits: ", pages[i].index, pages[i].adress, pages[i].modified, pages[i].inMemory);
            bin(pages[i].reference);
            printf(" | Decimal: %i\n\n  ", pages[i].reference);
        }
        else if (hasSwapped == 1){ // se fez swap vamo imprimir o que aconteceu la dentro
            // TODO 
        } else {
            if(breaker2 == 0) {
                printf("---------SWAP Memory---------\n\n");
                breaker2 = -1;
            }
            printf("index: %i | address: %i | mod: %i | inMemory: %i \nBits: ", pages[i].index, pages[i].adress, pages[i].modified, pages[i].inMemory);
            bin(pages[i].reference);
            printf(" | Decimal: %i\n\n", pages[i].reference);
        }
    }
    breaker1 = 0;
    breaker2 = 0;
}


// funcao que cria um vetor de numeros aleatorios salvando em stringOfReference e imprime eles
void referencesCreator(int lower, int upper, int count) {
    printf("RandArr: ");
    for(int i = 0; i < count; i++) {
        int num = (rand() % (upper - lower + 1)) + lower;
        stringOfReference[i] = num;
        printf("%d ", num);
    }
    printf("\n");
}


int main(void)
{
    int i, j, k, ref;

    initMemory();
    // printf("Insira a qntde de referências à memória: ");
    // scanf("%i", &count);

    // valores minimo e maximo para gerar numeros
    int lower = 0, upper = amountPages, count = 4; // CHUMBEI AQUI O VALOR DA QT DE NUMEROS GERADOS!!!
    srand(time(0));
    referencesCreator(lower, upper, count); // funcao que gera numeros

    for (i = 0; i < count; i++) 
    {
        if (isPageAvailable(i) == 0) // aqui ja atualiza bits de referencia
        {
            // printf("ta em memoria\n");
        }
        else 
        {
            // printf("nao ta em memoria\n");
            hasSwapped = 1; // vai acontecer swap vira 1
            pageFault(i);
        }
        pagePrint(i, stringOfReference[i]); // mandar imprimir bits das referencias aqui 
        if(hasSwapped == 1) { // se houve swap
            hasSwapped == 0; // volta para 0
        }
        if(stringOfReference[i + 1] != -1) {
            pushNonReferedBits();    
        }
    }
    printf("------------------------------------------------------------ AFTER FINISH !\n\n");
    // //--------PRINTS TESTE----------
    // printf("memoria RAM: ");
    // for (i = 0; i < memoryRAMsize; i++)
    // {
    //     printf("%d ", memoryRAMarea[i]);
    // }
    // printf("\n");
    // printf("memoria SWAP: ");
    // for (int j = 0; j < swapSize; j++)
    // {
    //     printf("%d ", swapArea[j]);
    // }
    // printf("\n");
    // printf("paginas virtuais: ");
    // for (k = 0; k < amountPages; k++)
    // {
    //     printf("%d ", pages[k].index);
    // }
    // printf("\n");

    pagePrint(-1, -1);

    return 0;
}