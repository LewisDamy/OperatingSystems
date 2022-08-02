#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define dataSize 52     // quantidade de dados que serao armazenados ao total
#define memorySize 20   // tamanho da memoria fisica
#define swapSize 20     // tamanho da memoria de swap
#define amountPages 52  // qntde de paginas
#define bitsReference 8 // qntde de bits de referencia da pagina
#define generatedPages 4
#define referencesQnty 20
#define totalIterations 10 // qntde total de iterações para o algoritmo rodar
#define qtMaxReferencias 255
// qntde de paginas = area de swap + RAM

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
int memoryArea[memorySize];
char data[dataSize];
int stringOfReference[referencesQnty];
int amountAging = 0;

void reader(int events)
{
    for (int i = 0; i < events; i++)
    {
        // ler a palavra até enter (gerada randomicamente)
        // colocar em cada indice do vetor input (var global) a letra em int
    }
}

void initData(char *dataAux)
{
    int i, letter = 122; // 122 corresponde a 'z'
    for (i = 0; i < dataSize; i++)
    {
        if (letter > 96)
        { // preenchendo de z ate a
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
    nodeAux->reference = 0;
    nodeAux->modified = 0;

    if (status == 0)
    {                               // se ela esta na memoria
        nodeAux->adress = pos;      // pagina de indice 0 correspondera ao quadro 0
        nodeAux->inMemory = status; // informa se esta na memoria
    }
    else
    {
        nodeAux->adress = status; // adress recebe -1 por nao estar na memoria
        nodeAux->inMemory = status;
    }
}

void initMemory(page *nodeAux)
{
    int i, j, l, k = 0;

    for (i = 0; i < memorySize; i++)
    {                            // preenchendo a memoria RAM com os primeiros indices
        memoryArea[i] = data[i]; // do vetor data
    }
    for (j = i; j < dataSize; j++)
    { // preenchendo a swap com o restante do vetor data
        swapArea[k] = data[j];
        k++;
    }
    for (l = 0; l < amountPages; l++)
    { // preenchendo a memoria virtual
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
}

void referencesCreator()
{
    srand(time(NULL));
    printf("Generated Numbers: ");
    for (int i = 0; i < referencesQnty; i++)
    {
        stringOfReference[i] = (rand() % (amountPages + 1));
        printf("%d ", stringOfReference[i]);
    }
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

int whichIsSmallest(void)
{                     // procura o menor valor dentre os da memoria principal
    int temp = 99999; // numero muito alto para ser substituido
    for (int i = 0; i < memorySize; i++)
    { // faz interacao na memoria principal
        if (pages[i].reference < temp)
        {
            temp = pages[i].reference;
        }
    }
    return temp;
}

void isPageAvailable(int i)
{
    // percorrer o tamanho da memoria virtual e buscar pelo index
     if(pages[n].index == stringOfReference){ //se a pagina referenciada ja estiver na memoria
        for(n = 0; n < amountPages; n++){
         // quando encontrado a struct page retorna ela
            if(pages[n]->inMemory == 0)
                return 0;    
            else if(pages[n]->inMemory == -1)
                return -1;   
        }
     }
}

int swapMemoryLocations(int index)
{ // TODO                 ----- TROCAR AS PAGINAS VITIMAS -----
    // limpa os bits referenciados
    // troca a var modified, inMemory = -1
    return 0;
    // tras a pagina da memoria swap para a principal modificar os endressos de cada uma
    // percorrer o tamanho da memoria virtual e buscar pelo index
    // modificar o inMemory para 0
    // copia o endereco novo na memoria principal

    // chama pushNonReferedBits
    // soma + 128 para ja ser referenciada
}

void pushNonReferedBits(void)
{ // TODO
    // Faz interacao em todas as paginas na memoria principal
    // empurra todos os bits nao referenciados das paginas na
}

void printBits(int index)
{
    // printf("Bits: ");
    bin(pages[index].reference);
}

///*
int agingAlgorithm(int randNum)
{
    for (int i = 0; i < amountPages; i++)
    {
        if (randNum == pages[i].index && pages[i].inMemory == 0)
        { // se a pagina for referenciada e se estiver na memoria
            if (pages[i].reference < qtMaxReferencias)
            { // checar se não estrapolou a qt max de referencias
                // "EMPURRA" os bits de referencia, chamando funcao pushNonReferedBits
                pages[i].reference += 128; // adiciona 1 no bit + significativo
                printf("\nAFTER:\n");
                printf("\nrandNum: %i | pages[%i].reference: ", randNum, i);
                printBits(i);
                printf("\n");
            }
        }
        else if (pages[i].inMemory == -1)
        {                                        // se nao tiver na memoria principal
            int toBeRemoved = whichIsSmallest(); // chama funcao whichIsSmallerst para saber a pagina com menos referencia
            // chama funcao swapMemoryLocations que limpa os bits antes de ir para a memoria principal
            // incrementa 1 na quantidade de amountAging
        }
        else
        {
            // ???
            continue;
        }
    }
}
//*/

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

    int i, j, l, k = 0; // variaveis auxiliares
    int lower = 0;
    page *nodeAux; //
    char *dataAux; // pointeiro para data
    dataAux = data;

    initData(dataAux);
    initMemory(nodeAux);
    referencesCreator(); // cria a string de referencia à memoria

    // for(int i = 0; i < referencesQnty; i++) {
    //     pageIterationPrint(stringOfReference[i], i);
    // }

    // for(int i = 0; i < totalIterations; i++) {
    //     agingAlgorithm(stringOfReference[i]);
    // }

    // for(int i = 0; i < referencesQnty; i++) {
    //     pageIterationPrint(stringOfReference[i], i);
    // }

    return 0;
}
