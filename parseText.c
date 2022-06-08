#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int vetor[50];
  struct TLista *prox;
} TLista;

typedef struct {
  char string[50];
}params_t;

TLista *Listas[5];

void *insere(void* args) {

  params_t a = *(params_t *)args; 
  TLista *aux = (TLista*)malloc(sizeof(TLista));  
  aux->prox = NULL;
  strcpy(aux->vetor,a.string);
}

int main(void) {
    // define size of string
    char string[50];
    // define size text to read
    char stringMat[50][50];
    int i = 0;

    // scan part of the text
    scanf("%[^\n]", string);

    // take the first token of the string
    char *pt = strtok(string, " ");

    // iterate through the 5 strings 
    for (i = 0; i < 5; i++) {
        Listas[i] = NULL; //TODO list aka the HashTable
    }

    int amoutWords = 0;

    // iterate until the end of the string with the pointer
    while(pt != NULL) {
        // copy the value of the word into pt
        strcpy(stringMat[i],pt);
        // move the point to the next word
        pt = strtok(NULL, " ");
        // increment one to the amount of words
        amoutWords++;
    }

    // print the string parsed
    for(i = 0; i < 5; i++) {
        printf("%s\n", stringMat[i]);
    }
}