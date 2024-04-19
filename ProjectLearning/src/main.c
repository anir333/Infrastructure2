#include <avr/io.h>
#include <stdio.h>
#include <usart.h>

int main() {
  DDRB = 0b11111111;
  PORTB  = 0b11110000;

  initUSART();
  printf("\n");
  printf("hey\n");
  return 0;
}