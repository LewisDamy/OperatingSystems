#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct threadArgs {
    int start;
    int end;
} threadArgs;

struct thread_t {
    pthread_t t;
    threadArgs bits;
};
typedef struct thread_t thread_t;


#define MAP 4
thread_t mapArrThread[MAP];
sem_t mutex_mapper; // mutex para mappers


void init(void) {
    sem_init(&mutex_mapper, 0, 1);
}

void create_threads(thread_t *mapArrThread, int n,  void *(*func)(void*), int amoutBits, int sizeFile){
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
    // pegar:
        // posicao inicial bits para ler
        // quantos bits vai ler
    int start, end;
    threadArgs bits = *(threadArgs *)args;

    start = bits.start;
    end = bits.end;

    // FOPEN, FSEEK, FREAD ...
    printf("Mapper read bits from %i to %i\n", start, end);
    fflush(stdout);
	// while(1) {
	// 	// item = produce_item();
	// 	sem_wait(&mutex_mapper);
	// 	// insert_item(id, item);
	// 	sem_post(&mutex_mapper);
	// 	sleep(1);
	// }
}

void join_threads(thread_t *mapArrThread, int n) {
    for (int i = 0; i < n; i++) {
		pthread_join(mapArrThread[i].t, NULL);
	}
}

int main(void) {
    init();
    int amountBits = 50;
    int sizeFile = 1000;
    create_threads(mapArrThread, MAP, mapper, amountBits, sizeFile);
    join_threads(mapArrThread, MAP);
}