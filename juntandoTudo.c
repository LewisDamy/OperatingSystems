#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

typedef struct threadArgs {
    int start;
    int end;
} threadArgs;

struct thread_t {
    pthread_t t;
    threadArgs bits;
};

typedef struct thread_t thread_t;


#define MAP 2
thread_t mapArrThread[MAP];
sem_t mutex_mapper; // mutex para mappers


void init(void) {
    sem_init(&mutex_mapper, 0, 1);
}

void create_threads(thread_t *mapArrThread, int n,  void *(*func)(void*), int sizeFile){
    // pegar os valores 
    int start = 0, end;
    
	for (int i = 0; i < n; i++) {
		mapArrThread[i].bits.start = start;
        end = sizeFile/MAP - 1 + start;
        mapArrThread[i].bits.end = end;
		if(pthread_create(&mapArrThread[i].t, NULL, func, &mapArrThread[i].bits) == 0) {
            printf("Created thread %i!\n", i);
        }
        start = end + 1;
	}
}

void *mapper(void *args) {

    int start, end;
    threadArgs bits = *(threadArgs *)args;

    start = bits.start;
    end = bits.end;

    FILE *file = fopen("text.txt", "r");
  char string[30];
  int i = 0;
  int controle = 0;
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
    while (controle < (end - start))
    {
      fscanf(file, "%c", &aux);
      // se aux for uma letra, sera inserida no vetor string
      if (aux != 32 && aux != 44 && aux != 46 && aux != 59 && aux != 58 && aux != 10)
      {
        string[i] = aux;
        i++;
        /*se for o ultimo bit a ser pego
        printa mesmo nao terminando a palavra*/
        if ((end - start) - controle == 1)
        {
        //   printf("%s.\n", string);
          //   CHAMA AQUI
          int teste = 0;
            while(teste < 2) {
            	// item = ler(args);
            	sem_wait(&mutex_mapper);
                printf("Print %s de thread %i - %i\n", string, start, end);
                fflush(stdout);
            	// insert_item(id, item); // insereTH funcao para inserir valor na hash table
            	sem_post(&mutex_mapper);
            	// sleep(1);
                teste++;
            }
        }
      }
      else
      {
        // aux eh uma pontuacao indicando o fim de uma palavra
        if (i != 0)
        {
          string[i] = '\0';
          // substituir o printf pela chamada da funcao
        //   printf("%s.\n", string);
          //   CHAMA AQUI
          int teste2 = 0;
          	while(teste2 < 2) {
            	// item = ler(args);
            	sem_wait(&mutex_mapper);
                printf("Print %s de thread %i - %i\n", string, start, end);
                fflush(stdout);
            	// insert_item(id, item); // insereTH funcao para inserir valor na hash table
            	sem_post(&mutex_mapper);
            	// sleep(1);
                teste2++;
            }
        }
        memset(string, 0, 30);
        i = 0;
      }
      controle++;
    }
    fclose(file);
  }
//   else
    // printf("\nERRO ao abrir arquivo!\n");
    


    // printf("Mapper read bits from %i to %i\n", start, end);
    // fflush(stdout);
    
}

int sizeText(char *fileSize) {
    // get the name of file
    char *file = fileSize;
    // define the variable to hold the size
    int sizeFile;
    // allocates memory for stat structure
    struct stat *buff = malloc(sizeof(struct stat));
    // always set errno to zero first, in case there's some error
    errno = 0;

    // run the function stat, passing the file to read, and the buffer to save the value
    if(stat(file, buff) == 0) { // int stat(const char *restrict pathname, struct stat *restrict statbuf);
        // save the value of the file
        sizeFile = buff->st_size;
        printf("Size of '%s' is %i bytes.\n", file, sizeFile);
        // printf("size: %i\n", sizeFile);
    } else {
        perror(file); // if something went wrong
    }
    free(buff);

    return sizeFile;
}

void join_threads(thread_t *mapArrThread, int n) {
    for (int i = 0; i < n; i++) {
		pthread_join(mapArrThread[i].t, NULL);
	}
}

int main(void) {
    init();
    
    char *file = "text.txt";  // name of the file

    int sizeFile = sizeText(file); // call the function and save the amount of bits 

    printf("Size file: %i\n", sizeFile);

    // int sizeFile = 1000;

    create_threads(mapArrThread, MAP, mapper, sizeFile);
    join_threads(mapArrThread, MAP);
}