#include <stdio.h>
#define MAX 5
#define SEVENFOLD(num) (num * 7)

void printArray(int array[]);
void makeArray(int array[]);

int main() {
    int array[MAX] = {0}; 

    printArray(array);
    makeArray(array);
    printArray(array);

    return 0;
}

void printArray(int array[]) {
    printf("\nContent of array:\n");
    for (int i = 0; i < MAX; i++) {
        printf("    Address: %p has value %d\n", &array[i], array[i]);
    }
}

void makeArray(int array[]) {
    for (int i = 0; i < MAX; i++) {
        array[i] = SEVENFOLD(i);
    }
}
