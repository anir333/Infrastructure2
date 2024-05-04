// // // to allow variables as parameter for the _delay-functions (must be placed before the include of delay.h)
#define __DELAY_BACKWARD_COMPATIBLE__  
#include <util/delay.h>
#include <avr/io.h>
#include <LEDs.h>
#include <usart.h>

int main() {
  enableAllLeds();
  lightUpOneLed(1);
pauseSeconds(1);
  dimLed(2, 99, 10);
pauseSeconds(1);
  fadeInLed(3, 5);
pauseSeconds(1);
  fadeOutLed(4, 1);


  return 0;
}