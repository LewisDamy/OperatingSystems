#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bin(unsigned n) {
    unsigned i;
    for (i = 1 << 8; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");

    printf("\n");
}

#define generatedPages 5
#define amountPages 50

int randNum(void) {
    int i;
    time_t t;

    // srand((unsigned) time(&t)); // initializes random number generator

    // for(i = 0; i < generatedPages; i++) {
    //     printf("%d\n", rand() % amountPages);
    // }

    srand(time(NULL));
    int random_number = rand();
    printf("%d\n", random_number);

}

void printRandoms(int lower, int upper, int count) {
    for(int i = 0; i < count; i++) {
        int num = (rand() % (upper - lower + 1)) + lower;
        printf("%d\n", num);
    }
}

int main(void) {

    int a = 12;
    
    printf("a: %d ", a);
    bin(a);
    printf("a<<1 = %d ", a<<1);
    bin(a<<1);
    printf("a>>1 = %d ", a>>1);
    bin(a>>1);

    // randNum();  

    int lower = 0, upper = 52, count = 5;
    srand(time(0));
    printRandoms(lower, upper, count);

    return 0;
}