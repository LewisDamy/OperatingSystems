#include <stdio.h>
#include <stdlib.h>
#include <string.h>             

typedef struct Node // Define struct do tipo nó
{   
    int qtWord; // numero para calcular quantidade de palavras
    char chave [25]; // string chave do nó 
    struct Node *prox; // ponteiro do proximo nó
} Node;
typedef Node *NodeTypeHash; // ponteiro para a struct Node


 
typedef struct HashTable // Define struct para a tabela hash 
{
    NodeTypeHash primeiro, ultimo;  // Define dois nós para o primeiro e ultimo elemento da "lista" hash
} HashTable;

typedef HashTable *typeHash; // ponteiro para a struct HashTable



int insereElemLista (typeHash listaAux, char *value, int valor){ // Função de inserção 
    NodeTypeHash novo = malloc(sizeof(Node)); // Alocando memoria para o nó 'novo' do tipo NodeTypeHash 
    
    if (novo == NULL){ // condição para a inserção 
        return 0; // se não inseriu, retorna 0 pois algo deu errado
    }

    strcpy(novo->chave, value); // string chave da struct Node recebe char value como sua nova string
    novo->qtWord = valor;

    // printf(" %s\n", novo->chave);
    // printf("Valor da qt da palavra: %d \n", novo->qtWord);

    if (listaAux->primeiro == NULL){ //verificando o primeiro elemento da listaAux
        listaAux->primeiro = novo; //salva o primeiro elemento como 'novo'
        listaAux->ultimo = novo; //salva o último elemento como 'novo'
    } 
    
    else { //condição para primeiro não nulo
        listaAux->ultimo->prox = novo;//salva o proximo elemento depois do ultimo como 'novo'
        listaAux->ultimo = novo;
        listaAux->ultimo->prox = NULL;
    }

    return 1; //retorna 1 se der tudo certo
}
 


NodeTypeHash buscaElemento (typeHash listaAux, char *value){ //função para procurar a string chave 
    NodeTypeHash pAux; //nó auxiliar tipo NodeTypeHash
    
    for (pAux = listaAux->primeiro; pAux != NULL; pAux = pAux->prox){ //faz um loop até encontrar a chave ou chegar no final da lista
        // if (pAux->chave == value){ //se encontrou a chave, retorna o ponteiro
        if(pAux->chave == value) {
            printf("FOUND!\n");
            return pAux;
        }
    }
    return NULL; //do contrário, retorna nulo
}
 


int removeElementoLE(typeHash listaAux, char *value)
{                                                              // função de remoção da string chave
  NodeTypeHash pAnt, remover = buscaElemento(listaAux, value); // cria um nó pAnt do tipo NodetypeHash e outro que aponta a string para remover

  if (listaAux->primeiro == NULL || remover == NULL)
  {           // checa se há elementos a serem removidos
    return 0; // se não há o que ser removido, retorna 0
  }

  if (strcmp(remover->chave, listaAux->primeiro->chave) == 0)
  {
    // printf("PRIMEIRO ELEMENTO listaAux->primeiro: %s\n", listaAux->primeiro->chave);
                                                    // checa se o elemento a ser removido é igual ao primeiro item da lista
    listaAux->primeiro = listaAux->primeiro->prox; // se for, 'primeiro' aponta para a proxima string
  }

  else
  {
    for (pAnt = listaAux->primeiro; pAnt != NULL; pAnt = pAnt->prox)
    { // iteração para percorrer a listaAux do primeiro até o fim da lista
      // if (pAnt->prox == remover)
      if(strcmp(pAnt->prox->chave, remover->chave) == 0)
      { // condição do nó a ser removido ser encontrado
        // printf("\n\n"); 
        // printf("pAnt->chave: %s\n", pAnt->chave);
        // printf("pAnt->prox->chave: %s | remover->prox: %s\n", pAnt->prox->chave, remover->chave);
        // printf("\n\n");
        pAnt->prox = remover->prox;

        // if (remover == listaAux->ultimo) //se remover for o ultimo valor 
        if (strcmp(remover->chave, listaAux->ultimo->chave) == 0){
        //   printf("ultimo valor para remover\n");
          listaAux->ultimo = pAnt;
        }
        break;
      }
    }
  }

  free(remover);
  return 1;
}
 

void imprimeElementosLE (typeHash listaAux){ // print function for the chaned ones 
    NodeTypeHash pAux = listaAux->primeiro;


    // if(listaAux != NULL) {
        
    //     do{
    //         printf("%d %s | ", pAux->qtWord, pAux->chave); 
    //         if(pAux->prox != NULL){
    //             pAux = pAux->prox;
    //             printf("%d %s", pAux->qtWord, pAux->chave); 
    //         }
    //     } while(pAux->prox != NULL);
    // }

    while(pAux != NULL) {
        printf("%d %s ", pAux->qtWord, pAux->chave); 
        pAux = pAux->prox;
    }
}
 

void inicializaTH(typeHash Taux, int tamHash){ // inicializa a tabela hash
    int i;

    for (i = 0; i < tamHash; i++){ // cria a lista para a hash com cada elemento apontando para Null
        Taux[i].primeiro = NULL;
        Taux[i].ultimo = NULL;
    }
}
 

int insereTH(typeHash Taux, int tamHash, char *value, int index, int num){ // insert main function 
    // int i, h;
    // calculate the key
    // h = chave % tamHash;
    // printf("value: %i\n", value);
    // call the function to insert the element on the right key-location
    // printf("Inserindo em [%i]: \n", index);
    return insereElemLista(&(Taux[index]), value, num);
}
 
// search main fuction 
int buscaTH(typeHash Taux, int tamHash, char *value, int index){
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
int removeTH(typeHash Taux, int tamHash, char *value, int index){
    // calculate the key
    // int h = chave % tamHash;
    // cal the function to remove the element on the specific key location
    return removeElementoLE(&(Taux[index]), value);
}
 

void imprimeTH(typeHash Taux, int tamHash){ // print the hash table
    for(int i = 0; i < tamHash; i++){
        printf("[%d] ", i);   // print the value to be found  
    
        imprimeElementosLE(&Taux[i]);  // call the function to print the other chained elements
        printf("\n");
    }
}
 
int main(void){

    int i, tamHash = 0, qtdEntradas = 0, index, amountWords = 0, dummy = 0;
    char value[50];
    printf("tamanho tabela hash: ");
    scanf("%d", &tamHash);  // tamanho da tabela hash
   
    HashTable TH[tamHash];  //create an hashtable

    inicializaTH(TH, tamHash); // initialize the function
    
    for(int i = 0; i < tamHash; i++) { // keep looping while the number is greater or equals to 0
        printf("index: %i, recebera quantas palavras: ", i);
        scanf("%i", &amountWords);  
        
        for(int j = 0; j < amountWords; j++) {
            scanf("%s", value); // insert it on the hash table
            insereTH(TH, tamHash, value, i, dummy); 
            dummy++;
        }
    }

    // printf("Tabela antes de remocao:\n");
    imprimeTH(TH, tamHash);
    
    // printf("Digite numero para buscar: ");
    // scanf("%d", &temp1);
    // printf("Digite indice para fazer a busca: ");
    // scanf("%d", &index);

    // if (buscaTH(TH, tamHash, temp1, index)){  //search the value
    //     printf("Found word!\n");
        
    //     removeTH(TH, tamHash, temp1, index); // remove the value
    // }
    
    // else
    //     printf("Valor não encontrado\n"); // if we haven't found, print 


    // printf("Tabela apos remocao:\n");
    // imprimeTH(TH, tamHash);

    return 0;
}