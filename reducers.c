#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

typedef struct threadArgs
{
  int start;
  int end;
} threadArgs;

struct thread_t
{
  pthread_t t;
  threadArgs bits;
  int i;
};

typedef struct thread_t thread_t;

typedef struct Node // Define struct do tipo nó
{
  int qtWord;        // numero para calcular quantidade de palavras
  char chave[25];    // string chave do nó
  struct Node *prox; // ponteiro do proximo nó
} Node;
typedef Node *NodeTypeHash; // ponteiro para a struct Node

typedef struct HashTable // Define struct para a tabela hash
{
  NodeTypeHash primeiro, ultimo; // Define dois nós para o primeiro e ultimo
                                 // elemento da "lista" hash
} HashTable;

typedef HashTable *typeHash; // ponteiro para a struct HashTable

#define MAP 2
#define REDUCE 5
HashTable TH[5];
thread_t mapArrThread[MAP];
thread_t mapReduceThread[REDUCE];
sem_t mutex_mapper; // mutex para mappers

void init(void);
void create_threads(thread_t *mapArrThread, int n, void *(*func)(void *), int sizeFile);
void join_threads(thread_t *mapArrThread, int n);
void *mapper(void *args);
NodeTypeHash buscaElemento(typeHash listaAux, char *value);
void *reducer(void *args);
int removeElementoLE(typeHash listaAux, NodeTypeHash remover);
int sizeText(char *fileSize);
int insereElemLista(typeHash listaAux, char *value, int valor);
void imprimeElementosLE(typeHash listaAux);
void inicializaTH(typeHash Taux, int tamHash);
int insereTH(typeHash Taux, int tamHash, char *value, int index, int num);
void imprimeTH(typeHash Taux, int tamHash);
void create_reducer_threads(thread_t *mapReduceThread, int n, void *(*func)(void *));
int writeNewFile(void);

void init(void)
{
  sem_init(&mutex_mapper, 0, 1);
  inicializaTH(TH, 5);
}

void create_threads(thread_t *mapArrThread, int n, void *(*func)(void *), int sizeFile)
{
  // pegar os valores
  int start = 0, end;

  for (int i = 0; i < n; i++)
  {
    mapArrThread[i].bits.start = start;
    end = sizeFile / MAP - 1 + start;
    mapArrThread[i].bits.end = end;
    if (pthread_create(&mapArrThread[i].t, NULL, func, &mapArrThread[i].bits) == 0)
    {
      //   printf("Created thread %i!\n", i);
    }
    start = end + 1;
  }
}

void join_threads(thread_t *mapArrThread, int n)
{
  for (int i = 0; i < n; i++)
  {
    pthread_join(mapArrThread[i].t, NULL);
  }
}

void *mapper(void *args)
{

  int start, end;
  threadArgs bits = *(threadArgs *)args;

  start = bits.start;
  end = bits.end;

  int calculatedIndex = 0;
  FILE *file = fopen("example.txt", "r");
  char string[30];
  int i = 0;
  int bitsControle = 0;
  char aux;
  // inicializando o vetor string
  memset(string, 0, 30);

  if (file != NULL)
  {
    // ira ler a partir do indice start
    fseek(file, start, SEEK_CUR);
    // printf("\tDados lidos do arquivo:\n");
    /*enquanto a qntde limite de bits de cada mapper
    nao eh atingida*/
    while (bitsControle < (end - start))
    {
      fscanf(file, "%c", &aux);
      // se aux for uma letra, sera inserida no vetor string
      if (aux != 32 && aux != 44 && aux != 46 && aux != 59 && aux != 58 &&
          aux != 10)
      {
        string[i] = aux;
        i++;
        /*se for o ultimo bit a ser pego
        printa mesmo nao terminando a palavra*/
        if ((end - start) - bitsControle == 1)
        {
          // calculando o indice na hashTable
          calculatedIndex = string[0] % 5;
          sem_wait(&mutex_mapper);
          //   printf("Print %s de thread %i - %i\n", string, start, end);
          insereTH(TH, 5, &string, calculatedIndex, 1);
          fflush(stdout);
          sem_post(&mutex_mapper);
        }
      }
      else
      {
        if (i != 0)
        {
          string[i] = '\0';
          // calculando o indice na hashTable
          calculatedIndex = string[0] % 5;
          sem_wait(&mutex_mapper);
          insereTH(TH, 5, &string, calculatedIndex, 1);
          //   printf("Print %s de thread %i - %i\n", string, start, end);
          fflush(stdout);
          sem_post(&mutex_mapper);
        }
        memset(string, 0, 30);
        i = 0;
      }
      bitsControle++;
    }
    fclose(file);
  }
  //   else
  // printf("\nERRO ao abrir arquivo!\n");

  // printf("Mapper read bits from %i to %i\n", start, end);
  // fflush(stdout);
}

NodeTypeHash buscaElemento(typeHash listaAux, char *value)
{
  NodeTypeHash pAux; // nó auxiliar tipo NodeTypeHash
  char *ocorrencia;  // guardar as outras ocorrencias das chaves e seus enderecos
  for (pAux = listaAux->primeiro; pAux != NULL; pAux = pAux->prox)
  {
    // faz um loop até encontrar a chave ou chegar no
    // final da lista
    ocorrencia = pAux->chave;
    if (strcmp(ocorrencia, value) == 0)
    { // se as strings sao iguais
      if (ocorrencia != value)
      {
        /*comparando os enderecos para checar se as chaves
         estao em indexes diferentes*/
        // printf("string recebida do reducer: %s\n", value);
        // printf("retornando %s, end %d que deve ser diferente de %d\n", pAux->chave, ocorrencia, value);
        return pAux;
      }
    }
  }
  // printf("nao foram encontradas correspondencias\n");
  return NULL; // do contrário, retorna nulo
}

void *reducer(void *args)
{
  int i = *(int *)args;                             // cast de tipo de variavel
  NodeTypeHash primeiraOcorrencia = TH[i].primeiro; // primeira chave a ser comparada
  NodeTypeHash outrasOcorrencias;                   // segunda chave a ser comparada e deletada
  NodeTypeHash pAux;
  char *chaveComparada = TH[i].primeiro->chave;
  // ponteiro char para passar como parametro a primeira chave a ser comparada
  for (pAux = TH[i].primeiro; pAux != NULL; pAux = pAux->prox)
  {
    primeiraOcorrencia = pAux;
    chaveComparada = primeiraOcorrencia->chave;
    outrasOcorrencias = buscaElemento(&(TH[i]), chaveComparada);

    while (outrasOcorrencias != NULL) // se houver outras ocorrencias
    {
      primeiraOcorrencia->qtWord++;                  // somar a qntde de palavras da primeira ocorrencia
      removeElementoLE(&(TH[i]), outrasOcorrencias); // excluindo as outras ocorrencias
      outrasOcorrencias = buscaElemento(&(TH[i]), chaveComparada);
    }
  }
}

int removeElementoLE(typeHash listaAux, NodeTypeHash remover)
{
  // funcao para remover as demais ocorrencias
  NodeTypeHash pAnt;                            // no anterior ao que sera excluido
  NodeTypeHash primeiraChave, ultChave, pAtual; // no atual
  primeiraChave = listaAux->primeiro;
  ultChave = listaAux->ultimo;

  if (listaAux->primeiro == NULL ||
      remover == NULL)
  {           // checa se há elementos a serem removidos
    return 0; // se não há o que ser removido, retorna 0
  }

  if (primeiraChave == remover)
  {
    // checa se o elemento a ser removido é o
    // primeiro item da lista
    listaAux->primeiro =
        listaAux->primeiro->prox; // se for, 'primeiro' aponta para a proxima string
  }
  else
  {
    for (pAnt = listaAux->primeiro; pAnt != NULL; pAnt = pAnt->prox)
    {
      pAtual = pAnt->prox;
      // iteração para percorrer a listaAux do primeiro
      // até o fim da lista
      if (pAtual == remover)
      { // condição do nó a ser removido ser encontrado
        pAnt->prox = remover->prox;
        // se remover for o ultimo valor
        if (ultChave == remover)
        {
          listaAux->ultimo = pAnt;
        }
        break;
      }
    }
  }
  free(remover);
  return 1;
}

int sizeText(char *fileSize)
{
  // get the name of file
  char *file = fileSize;
  // define the variable to hold the size
  int sizeFile;
  // allocates memory for stat structure
  struct stat *buff = malloc(sizeof(struct stat));
  // always set errno to zero first, in case there's some error
  errno = 0;

  // run the function stat, passing the file to read, and the buffer to save the
  // value
  if (stat(file, buff) == 0)
  { // int stat(const char *restrict pathname, struct
    // stat *restrict statbuf);
    // save the value of the file
    sizeFile = buff->st_size;
    printf("Size of '%s' is %i bytes.\n", file, sizeFile);
  }
  else
  {
    perror(file); // if something went wrong
  }
  free(buff);

  return sizeFile;
}

int insereElemLista(typeHash listaAux, char *value, int valor)
{ // Função de inserção
  NodeTypeHash novo = malloc(
      sizeof(Node)); // Alocando memoria para o nó 'novo' do tipo NodeTypeHash

  if (novo == NULL)
  {           // condição para a inserção
    return 0; // se não inseriu, retorna 0 pois algo deu errado
  }

  strcpy(novo->chave, value); // string chave da struct Node recebe char value
                              // como sua nova string
  novo->qtWord = valor;

  if (listaAux->primeiro ==
      NULL)
  {                            // verificando o primeiro elemento da listaAux
    listaAux->primeiro = novo; // salva o primeiro elemento como 'novo'
    listaAux->ultimo = novo;   // salva o último elemento como 'novo'
  }

  else
  { // condição para primeiro não nulo
    listaAux->ultimo->prox =
        novo; // salva o proximo elemento depois do ultimo como 'novo'
    listaAux->ultimo = novo;
    listaAux->ultimo->prox = NULL;
  }

  return 1; // retorna 1 se der tudo certo
}

void imprimeElementosLE(typeHash listaAux)
{ // função para imprimir as strings  // e a quantidade de palavras
  NodeTypeHash pAux = listaAux->primeiro;

  while (pAux != NULL)
  {
    printf("%d %s ", pAux->qtWord, pAux->chave);
    pAux = pAux->prox;
  }
}

void inicializaTH(typeHash Taux, int tamHash)
{ // inicializa a tabela hash
  int i;
  for (i = 0; i < tamHash;
       i++)
  { // cria a lista para a hash com cada elemento apontando para Null
    Taux[i].primeiro = NULL;
    Taux[i].ultimo = NULL;
  }
}

int insereTH(typeHash Taux, int tamHash, char *value, int index, int num)
{ // insere elemento na tabela hash
  return insereElemLista(&(Taux[index]), value, num);
}

void imprimeTH(typeHash Taux, int tamHash)
{ // imprime a tabela hash
  for (int i = 0; i < tamHash; i++)
  {
    printf("[%d] ", i);           // imprime o valor a ser achado
    imprimeElementosLE(&Taux[i]); // chama a função para imprimir os outros
                                  // elementos encadeados
    printf("\n");
  }
}

void create_reducer_threads(thread_t *mapReduceThread, int n, void *(*func)(void *))
{
  int index = 0;
  for (int i = 0; i < n; i++)
  {
    mapReduceThread[i].i = i;
    if (pthread_create(&mapReduceThread[i].t, NULL, func, &mapReduceThread[i].i) == 0)
    {
      fflush(stdout);
      index++;
    }
  }
}

int writeNewFile(void)
{
  char *fileName = "saida.txt";

  FILE *fp = fopen(fileName, "w");
  NodeTypeHash pAux;
  ;

  if (fp == NULL)
  {
    printf("Error opening the file %s \n", fileName);
    return -1;
  }
  for (int i = 0; i < 5; i++)
  {
    for (pAux = TH[i].primeiro; pAux != NULL; pAux = pAux->prox)
    {
      fprintf(fp, "%i %s,\n", pAux->qtWord, pAux->chave);
    }
  }
  return 0;
}

int main(void)
{
  init();

  char *file = "example.txt"; // nome do arquivo  de origem

  int sizeFile = sizeText(file); // obtendo a quantidade de bits

  // MAPPERS
  create_threads(mapArrThread, MAP, mapper, sizeFile);
  join_threads(mapArrThread, MAP);

  printf("---Hash Table---\n");
  imprimeTH(TH, 5);

  // REDUCERS
  create_reducer_threads(mapReduceThread, REDUCE, reducer);
  join_threads(mapReduceThread, REDUCE);

  printf("\n---Hash Table após reducers---\n");
  imprimeTH(TH, 5);

  if (writeNewFile() != 0)
  {
    printf("Erro ao escrever no arquivo.\n");
  }
}
