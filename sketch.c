#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// struct of data with key values
typedef struct {
    char *value;
    int key;
} data;

data *createData(char *value, int key) {
    data *newData;
    // printf("Value before: %s\n", value);
    // newData->value = malloc(strlen(value + 1));
    newData->value = value;
    // printf("Value as newData: %s\n", newData->value);
    newData->key = key;

    return newData;
}

// Create function to find the next word in the initBuffer
int findWordBuffer() {
    // TODO
    // funcao deve particionar " " ou "," ou "." retornando o indice
    // partindo de uma iteracao no initBuffer
    return 0;
}

void map() {
    // TODO
        // Call function to find next word in buffer
        // Call function to createData

        // Continue as producer funct in prod_cons.c file

}

int main(int argc, char **argv) {
    data p;

    // sample of how text will be accessed in initBuffer
    char text[] = "Text fsad";
    for (int i = 0; i < strlen(text); i++) {
        printf("%c ", text[i]);
    }
    printf("\n");


    // sample of how to create an data type
    char* value = "text";
    p = *createData(value, 1);
    printf("value: %s, key: %i\n", p.value, p.key);

}