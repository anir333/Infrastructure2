#include <button.h>
#include <LEDs.h>
#include <stdio.h>
#include <usart.h>


int counterButtonOne = 0;
int counterButtonTwo = 0;
int counterButtonThree = 0;

ISR( PCINT1_vect ) {

  if ( buttonPushed(1) ) {
    counterButtonOne++;
    printf("\n\nBUTTON 1 CLICKED %d TIMES\n\n", counterButtonOne);
    _delay_us( 500 );

    if (counterButtonOne % 2 == 0) {
      printf("\n\nOFF LED\n\n");
      lightDownOneLed(1);
    } else {
      enableButtonInterrupt(1);
      while (1) {

        checkOtherLEDsFlashing();

        if (counterButtonOne % 2 == 0) break;
      }
    }
  }

  if ( buttonPushed(2) ) {
    counterButtonTwo++;
    printf("\n\nBUTTON 2 CLICKED %d TIMES\n\n", counterButtonTwo);
    _delay_us( 500 );

    if (counterButtonTwo % 2 == 0) {
      printf("\n\nOFF LED\n\n");
      lightDownOneLed(2);
    } else {
      enableButtonInterrupt(2);
      while (1) {

        checkOtherLEDsFlashing();

        if (counterButtonTwo % 2 == 0) break;
      }
    }
  }

  if ( buttonPushed(3) ) {
    counterButtonThree++;
    printf("\n\nBUTTON 3 CLICKED %d TIMES\n\n", counterButtonThree);
    _delay_us( 500 );

    if (counterButtonThree % 2 == 0) {
      printf("\n\nOFF LED\n\n");
      lightDownOneLed(3);
    } else {
      enableButtonInterrupt(3);
      while (1) {
        checkOtherLEDsFlashing();

        if (counterButtonThree % 2 == 0) break;
      }
    }
  }

} // ISR 


void checkOtherLEDsFlashing() {
  if (!(counterButtonOne % 2 == 0) && !(counterButtonTwo % 2 == 0) && !(counterButtonThree % 2 == 0)) {
    printf("\n\n FLASHING LEDs 1, 2 & 3 TOGETHER\n\n");
    lightUpMultipleLeds(0b00100000);
    _delay_ms(500);
    lightDownMultipleLeds(0b00111100);
    _delay_ms(500);
  } else if (!(counterButtonOne % 2 == 0) && !(counterButtonTwo % 2 == 0)) {
    printf("\n\n FLASHING LEDs 1 & 2 TOGETHER\n\n");
    lightUpMultipleLeds(0b00110000);
    _delay_ms(500);
    lightDownMultipleLeds(0b00111100);
    _delay_ms(500);
  } else if (!(counterButtonOne % 2 == 0) && !(counterButtonThree % 2 == 0)) {
    printf("\n\n FLASHING LEDs 1 & 3 TOGETHER\n\n");
    lightUpMultipleLeds(0b00101000);
    _delay_ms(500);
    lightDownMultipleLeds(0b00111100);
    _delay_ms(500);
  } else if (!(counterButtonTwo % 2 == 0) && !(counterButtonThree % 2 == 0)) {
    printf("\n\n FLASHING LEDs 2 & 3 TOGETHER\n\n");
    lightUpMultipleLeds(0b00100100);
    _delay_ms(500);
    lightDownMultipleLeds(0b00111100);
    _delay_ms(500);
  } else if (!(counterButtonOne % 2 == 0)) {
    printf("\n\nFLASHING LED 1 ALONE\n\n");
    lightUpMultipleLeds(0b00111000);
    _delay_ms(500);
    lightDownMultipleLeds(0b00111100);
    _delay_ms(500);
  } else if (!(counterButtonTwo % 2 == 0)) {
    printf("\n\nFLASHING LED 2 ALONE\n\n");
    lightUpMultipleLeds(0b00110100);
    _delay_ms(500);
    lightDownMultipleLeds(0b00111100);
    _delay_ms(500);
  } else if (!(counterButtonThree % 2 == 0)) {
    printf("\n\nFLASHING LED 3 ALONE\n\n");
    lightUpMultipleLeds(0b00101100);
    _delay_ms(500);
    lightDownMultipleLeds(0b00111100);
    _delay_ms(500);
  }
}

int main() {
  initUSART();
  enableAllLeds();

  enableAllButtonInterrupts();

  printf( "\n\n\n DONE \n\n\n");

  while (1);

  return 0;
}






    // other:
 /*    bool ledOneOn = false;

ISR(PCINT1_vect) {
    if (buttonPushed(1)) {
        printf("\n\n\n BUTTON 1 CLICKED\n\n\n");
        _delay_us(1000);

        while (buttonPushed(1)) {
            if (ledOneOn) {
                printf("\n\nOFF LED\n\n");
                lightDownOneLed(1);
                ledOneOn = false;
            } else {
                printf("\n\n Flashing LED\n\n");
                lightUpOneLed(1);
                ledOneOn = true;
            }
            _delay_ms(500); // Delay to avoid rapid toggling due to button bouncing
        }
    }
} */