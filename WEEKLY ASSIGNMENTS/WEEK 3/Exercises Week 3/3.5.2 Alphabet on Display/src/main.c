#include <display.h>
#include <LEDs.h>
#include <usart.h>

int main() {
  // initUSART();
  initDisplay();
  turnDisplayOFF();

  // while (1) {
      /* first part of exercise: */
      // char ch = 'z';
      // writeCharToSegment( FIRST_DIGIT, ch );

    /* second part of exercise */
      char str[] = "easy";
      writeStringAndWait(&str, 1000);
      turnDisplayOFF();
  // }
    return 0;
}