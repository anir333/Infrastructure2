#include <stdio.h>
#include <string.h>

#define MAX 7
#define MAX_LENGTH 10

void printFirstLetters(char names[MAX][MAX_LENGTH]);
void printLastLetters(char names[MAX][MAX_LENGTH]);
void searchShortestName(char names[MAX][MAX_LENGTH]);

int main() {
    char names[MAX][MAX_LENGTH] = {"Aline", "Daria", "Hasham", "Anna", "Eva", "Vesela", "Rufina"};
    printFirstLetters(names);
    printLastLetters(names);
    searchShortestName(names);

    return 0;
}

void printFirstLetters(char names[MAX][MAX_LENGTH]) {
    printf("\nFirst letters: ");
    for (int i = 0; i < MAX; i++) {
        printf("%c", names[i][0]);
    }
}

void printLastLetters(char names[MAX][MAX_LENGTH]) {
    printf("\nLast letters: ");
    for (int i = 0; i < MAX; i++) {
        int length = strlen(names[i]);
        printf("%c", names[i][length - 1]);
    }
}

void searchShortestName(char names[MAX][MAX_LENGTH]) {
    int shortestNameIndex = 0;
    int shortestNameLength = MAX;
    for (int nameIndex = 0; nameIndex < MAX; nameIndex++) {
        int currentNameLength = 0;
        for (int nameLength = 0; nameLength < MAX_LENGTH; nameLength++) {
            if (names[nameIndex][nameLength] != 0) {
                currentNameLength++;
            }
        }
        if (currentNameLength < shortestNameLength) {
            shortestNameLength = currentNameLength;
            shortestNameIndex = nameIndex;
        }
        // printf("\nname: %s, nameIndex: %d, length: %d\n", names[nameIndex], shortestNameIndex, shortestNameLength);
    }
    printf("\nShortest = %s with length: %d", names[shortestNameIndex], shortestNameLength);
}