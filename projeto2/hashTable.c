#include <stdio.h>
#include <stdlib.h>
 
// Define struct of type node
typedef struct Node
{
    //int for the key
    int chave;
    // pointer to the next node
    struct Node *prox;
} Node;
 
// Define an node as being an struct for the hash table
typedef Node *NodeTypeHash;
 
// Define struct for hash table
typedef struct HashTable
{
    //define two nodes for first and last element of the "array" hashtable
    NodeTypeHash primeiro, ultimo;
} HashTable;
 
// Define the Hashtable is an typeHash
typedef HashTable *typeHash;

// Insert function
int insereElemLista (typeHash listaAux, int value)
{
    // Allocate enough memory for the new node
    NodeTypeHash novo = malloc(sizeof(Node));
    //Check if the insertion went well
    if (novo == NULL)
    {
        // if not, something went wrong
        return 0;
    }

    //save the info of the key to the new node
    novo->chave = value;
 
    // check if we found the first element 
    if (listaAux->primeiro == NULL)
    {
        // if so, set the prox to point at null
        novo->prox = NULL;
        // save the first element to be the new one
        listaAux->primeiro = novo;
        // save the last element to be the new one
        listaAux->ultimo = novo;
    } 
    else
    {
        // set the prox to point at null
        novo->prox = NULL;
        // set the next element of the last one, aka the new one to be the new one
        listaAux->ultimo->prox = novo;
        // set the last element to be the new one
        listaAux->ultimo = novo;
    }
    // if everything went well return 1
    return 1; 
}
 
// function to search an element (it will return an type node)
NodeTypeHash buscaElemento (typeHash listaAux, int value)
{
    // create an auxiliar node
    NodeTypeHash pAux;
    // loop until either we found the chave or we reach the end of the table
    for (pAux = listaAux->primeiro; pAux != NULL; pAux = pAux->prox)
    {
        if (pAux->chave == value)
        {
            // if we found the key, return the pointer 
            return pAux;
        }
    }
    // else return null
    return NULL;
}
 
// remove element function
int removeElementoLE(typeHash listaAux, int value)
{
    // create pAnt type node, and another one pointing at the element to remove
    NodeTypeHash pAnt, remover = buscaElemento(listaAux, value);  

    // check if we reach the first element aka the last one, or there's no element to be removed
    if (listaAux->primeiro == NULL || remover == NULL) 
    {
        // return 0, cannot be removed
        return 0; 
    }
    // check if the remover is equal the first item in the list
    if (remover == listaAux->primeiro)
    {
        // if so, point to the next one
        listaAux->primeiro = listaAux->primeiro->prox;
    }
    else
    {
        // iterate to walk inside of the items chaned
        for (pAnt = listaAux->primeiro; pAnt != NULL; pAnt = pAnt->prox)
        {
            // if we found the node to be removed
            if (pAnt->prox == remover)
            {
                // point the aux pointer to be the next one of the remotion
                pAnt->prox = remover->prox;
            if (remover == listaAux->ultimo)
                listaAux->ultimo = pAnt;
            break;
            }
        }
    }
    free(remover);
    return 1; 
}
 
// print function for the chaned ones 
void imprimeElementosLE (typeHash listaAux)
{
    NodeTypeHash pAux;
    // iterate though the chaned items and print then out
    for (pAux = listaAux->primeiro; pAux != NULL; pAux = pAux->prox)
    {
        printf("%d ", pAux->chave);
    }
}
 
// inicialize the hash table
void inicializaTH(typeHash Taux, int tamHash)
{
    int i;
    // create the array for the hash table pointing each element to null
    for (i = 0; i < tamHash; i++)
    {
        Taux[i].primeiro = NULL;
        Taux[i].ultimo = NULL;
    }
}
 
// insert main function 
int insereTH(typeHash Taux, int tamHash, int value, int index)
{
    // int i, h;
    // calculate the key
    // h = chave % tamHash;
    // printf("value: %i\n", value);
    // call the function to insert the element on the right key-location
    return insereElemLista(&(Taux[index]), value);
}
 
// search main fuction 
int buscaTH(typeHash Taux, int tamHash, int value, int index)
{
    // calculate the key
    // int h = chave % tamHash;
    // search the element and save as an node by calling the function buscaElemento
    NodeTypeHash busca = buscaElemento(&(Taux[index]), value);
    // if we found, return 1, else return 0
    if (busca != NULL)
        return 1;
    else
        return 0;
}

// remove main function
int removeTH(typeHash Taux, int tamHash, int value, int index)
{
    // calculate the key
    // int h = chave % tamHash;
    // cal the function to remove the element on the specific key location
    return removeElementoLE(&(Taux[index]), value);
}
 
// print the hash table
void imprimeTH(typeHash Taux, int tamHash)
{
    for(int i = 0; i < tamHash; i++) {
    // print the value to be found
    printf("[%d] ", i);
    
    // call the function to print the other chained elements
    imprimeElementosLE(&Taux[i]);
    printf("\n");
    }
}
 
int main(void)
{
    int i, tamHash = 0, qtdEntradas = 0, temp1 = -1, value = 0, index;
    printf("tamanho tabela hash: ");
    // tamanho da tabela hash
    scanf("%d", &tamHash); 

    //create an hashtable
    HashTable TH[tamHash];

    // initialize the function
    inicializaTH(TH, tamHash); 
    
    // keep looping while the number is greater or equals to 0
    for(int i = 0; i < tamHash; i++) {
        printf("index: %i, recebera quantos numeros: ", i);
        scanf("%d", &temp1);
        for(int j = 0; j < temp1; j++) {
            // insert it on the hash table
            scanf("%d", &value);
            insereTH(TH, tamHash, value, i); 
        }
    }
    printf("Tabela antes de remocao:\n");
    imprimeTH(TH, tamHash);
    
    printf("Digite numero para buscar: ");
    scanf("%d", &temp1);
    printf("Digite indice para fazer a busca: ");
    scanf("%d", &index);

    //search the value
    if (buscaTH(TH, tamHash, temp1, index))
    {
        printf("Found number!");
        // remove the value
        removeTH(TH, tamHash, temp1, index);
    }
    // if we haven't found, print 
    else
        printf("Valor não encontrado\n");


    printf("Tabela apos remocao:\n");
    imprimeTH(TH, tamHash);

    return 0;
}