#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define dataSize 52     // quantidade de dados que serao armazenados ao total
#define memorySize 32   // tamanho da memoria fisica
#define swapSize 20     // tamanho da memoria de swap
#define amountPages 52  // qntde de paginas
#define bitsReference 8 // qntde de bits de referencia da pagina
#define generatedPages 4
#define generatedNumbers 10 
#define totalIterations 10 // qntde total de iterações para o algoritmo rodar
// qntde de paginas = area de swap + RAM certo????

typedef struct pageNode {
    int index;                    // numero da pagina
    int reference;
    int adress;                   // endereco fisico nos quadros de pagina
    int modified;                 // checar se foi modificada
    int inMemory;                 // checar se esta na memoria
    //ADICIONAR CAMPO DATA
} page;

page pages[amountPages];
int swapArea[swapSize];        
int memoryArea[memorySize];   
char data[dataSize];            
int randNumArr[generatedNumbers];
int amountAging = 0;

void bin(unsigned n) {
    unsigned i;
    for (i = 1 << 8; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");

    printf("\n");
}

void initData(char *dataAux) {
    int i, letter = 122; // 122 corresponde a 'z'
    for (i = 0; i < dataSize; i++) {
    if (letter > 96) { // preenchendo de z ate a
        *(dataAux + i) = letter;
        letter--;
    } else {
        *(dataAux + i) = letter - 6; // o decimal correspondente a
        letter--;                    // Z comeca em 90 por isso a subtracao
    }
    }
}

void initPaging(page *nodeAux, int pos, int status) {
    nodeAux->index = pos;
    nodeAux->reference = 0;
    nodeAux->modified = 0;

    if (status == 0) {  // se ela esta na memoria
        nodeAux->adress = pos;      // pagina de indice 0 correspondera ao quadro 0
        nodeAux->inMemory = status; // informa se esta na memoria
    } else {
        nodeAux->adress = status;   // adress recebe -1 por nao estar na memoria
        nodeAux->inMemory = status;
    }
}

void initMemory(page *nodeAux) {
    int i, j, l, k = 0;

    for (i = 0; i < memorySize; i++) {  // preenchendo a memoria RAM com os primeiros indices
        memoryArea[i] = data[i];    // do vetor data
    } 
    for (j = i; j < dataSize; j++) {  // preenchendo a swap com o restante do vetor data
        swapArea[k] = data[j];
        k++;
    }
    for (l = 0; l < amountPages; l++) {   // preenchendo a memoria virtual
        nodeAux = &pages[l];
        if (l < memorySize) {
            initPaging(nodeAux, l, 0); // preenchendo com dados em memoria RAM
        } else {
            initPaging(nodeAux, l, -1); // preenchendo com dados em SWAP area
        }
    }
}

int printRandoms(int lower, int upper, int count) {
    printf("Generated Numbers: ");
    for(int i = 0; i < count; i++) {
        int num = (rand() % (upper - lower + 1)) + lower;
        randNumArr[i] = num;
        printf("%d ", num);
    }
    printf("\n");
}

int agingAlgo(int randNum) {
    for (int i = 0; i < generatedPages; i++) {
        if(randNum == pages[i].index) {
            pages[i].reference++;
        } else if {
            // TODO
        }
    }
}

void pageIterationPrint(int randInt, int z) {
        printf("RAND INT: %d\n", randInt);
    //   for (int z = 0; z < amountPages; z++) {
        printf("\n---------BEFORE---------\n");
        printf("PAGE: index %d | mod %d | inMemory %d\n", pages[z].index, pages[z].modified, pages[z].inMemory);
        bin(pages[z].reference);
        printf("Decimal: %d ", pages[z].reference);
        printf("\n---------AFTER---------\n");
        // pages[z].reference = ;
        printf("PAGE: index %d | mod %d | inMemory %d\n", pages[z].index, pages[z].modified + 1, pages[z].inMemory);
        bin(pages[z].reference);
        printf("Decimal: %d\n", pages[z].reference);
    // }
}

int main(void) {

    int i, j, l, k = 0; // variaveis auxiliares
    page *nodeAux;  //  
    char *dataAux;  // pointeiro para data
    dataAux = data;

    initData(dataAux);

    initMemory(nodeAux);

    int value;
  /* ------------------- prints de teste ----------------------- */

  // print da struct pageNode


    // Chama funcao para gerar numeros aleatorios e salvar no vetor randnum
    int lower = 0, upper = amountPages, count = generatedNumbers;
    srand(time(0));
    printRandoms(lower, upper, count);


    // for(int i = 0; i < generatedNumbers; i++) {
    //     pageIterationPrint(randNumArr[i], i);
    // }

    for(int i = 0; i < totalIterations; i++) {
        agingAlgo(RandNumArr[i]);
    }


    return 0;
}   