#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <LEDs.h>
#include <usart.h>
#include <avr/io.h>
#include <stdio.h>
// #include <myOwnlib.h>
// #include <'My Own Libraries'/myOwnlib.h>


#define getSizeOfArray(array) (sizeof(array) / sizeof(array[0]))

int main() {

  lightUpOneLedNTimes(3, 2);

  _delay_ms(1000);

  makeLedBurnLonger(4);

  _delay_ms(1000);
  
  walkThroughArrayLightLed();

  _delay_ms(1000);

  randomDurationForRandomLed();

  _delay_ms(1000);
 
  lightUpLedsBasedOnString("abcdabdcdacbdabdcdbadcdaaabcdc");

  _delay_ms(1000);

  char characters[14] = {'a', 'b', 'c', 'd', 'a', 'c', 'd', 'b', 'a', 'b', 'd', 'c', 'a', 'd'};
  lightUpLedsBasedOnArrayOfChars(characters, 14);

  _delay_ms(1000);

  lightUpAllLedsBasedOnRandomStringXAmountOfTimes();

  _delay_ms(1000);

  consecutiveLightUp(); // when this is executed, it will not execute anything after it since its an infinite while loop to light up the lights consecutively

  return 0;
}
