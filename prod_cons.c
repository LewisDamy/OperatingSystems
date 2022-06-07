#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 10
int buffer[N];
int w, r;
sem_t mutex_prod; // mutex para RC entre produtores
sem_t mutex_cons; // mutex para RC entre consumidores
sem_t full; // indica qtd posicoes cheias no buffer
sem_t empty; // indica qtd de posicoes vazias no buffer

void init(void) {
	w = 0;
	r = 0;
	sem_init(&mutex_prod, 0, 1);
	sem_init(&mutex_cons, 0, 1);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, N);
	srand(time(NULL));
}

int produce_item(void) {
	int item;
	item = rand()%(N*10);
	return (item);
}

void insert_item(int id, int item) {
	buffer[w] = item;
	printf("Prod %d buffer[%d] = %d \n", id, w, item);
	fflush(stdout);
	w = (w+1)%N;
}

void *producer(void *args) {
	int id = *(int *)args;
	int item;
	while(1) {
		item = produce_item();
		sem_wait(&empty);
		sem_wait(&mutex_prod);
		insert_item(id, item);
		sem_post(&mutex_prod);
		sem_post(&full);
		sleep(1);
	}
}

int remove_item(int id) {
	int item;
	item = buffer[r];
	printf("Cons %d buffer[%d] = %d \n", id, r, item);
	r = (r+1)%N;
}

void *consumer(void *args) {
	int id = *(int *)args;
	int item;
	while(1) {
		sem_wait(&full);
		sem_wait(&mutex_cons);
		item = remove_item(id);
		sem_post(&mutex_cons);
		sem_post(&empty);
		sleep(5);
	}
}

#define NP 3
#define NC 2

struct thread_t {
	pthread_t t;
	int id;
};

typedef struct thread_t thread_t;

void create_threads(thread_t *th, int n, void *(*func)(void*)){
	int i;
	for (i=0; i<n; i++) {
		th[i].id = i;
		pthread_create(&th[i].t, NULL, func, &th[i].id);
	}
}

void join_threads(thread_t *th, int n) {
	int i;
        for (i=0; i<n; i++) {
		pthread_join(th[i].t, NULL);
	}
}

int main(int argc, char **argv) {
	thread_t tp[NP], tc[NC];
	init();
	create_threads(tp, NP, producer);
	create_threads(tc, NC, consumer);
	join_threads(tp, NP);
	join_threads(tc, NC);
	return 0;
}