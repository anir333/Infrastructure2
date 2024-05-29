#include <button.h>
#include <usart.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main() {
    initUSART();
    enableButton(1);

    char phrase[] = "I am not allowed to speak in class.";

    while (1) {
      if (buttonPushed(1)) {
        _delay_ms(100);
        for (int i = 0; i<=100; i++) {
          printf("\n%d: %s", i, phrase);
          writeLinesOnHeap(phrase);
          i++;
          if (i >=101) {
            break;
          }
        }
        break;
      }
    }
    printf("\n finished\n");

    return 0;
}

void writeLinesOnHeap(char sentence[]) {
  int* phrase = malloc(strlen(sentence)+1);
  if (!phrase || phrase == NULL) {
    printf("\nMemory allocation failed!!");
    return 1;
  }
  strcpy(phrase, sentence);
  printf("\n\"%s\" is on heap", phrase);
  free(phrase);
}