#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <LEDs.h>
#include <usart.h>
#include <avr/io.h>
#include <stdio.h>


#define getSizeOfArray(array) (sizeof(array) / sizeof(array[0]))

int main() {
  enableAllLeds();
  lightUpAllLeds();
pauseSeconds(1);

  lightUpOneLedNTimes(3, 2);
pauseSeconds(1);

  makeLedBurnLonger(4);
pauseSeconds(1);

  walkThroughArrayLightLed();
pauseSeconds(1);

  randomDurationForRandomLed();
pauseSeconds(1);

  lightUpLedsBasedOnString("abcdabdcdacbdabdcdbadcdaaabcdc");
pauseSeconds(1);

  char characters[14] = {'a', 'b', 'c', 'd', 'a', 'c', 'd', 'b', 'a', 'b', 'd', 'c', 'a', 'd'};
  lightUpLedsBasedOnArrayOfChars(characters, 14);
pauseSeconds(1);

  lightUpAllLedsBasedOnRandomStringXAmountOfTimes();
pauseSeconds(1);

  consecutiveLightUp(); // when this is executed, it will not execute anything after it since its an infinite while loop to light up the lights consecutively

  return 0;
}
