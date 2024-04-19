#include <avr/io.h>

int main() {
  DDRB = 0b00010000;
  PORTB  = 0b00000000;

  return 0;
}