#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "display.h"
#include "usart.h"

volatile int counter = 0;
volatile int secondsPassed = 0;
#define MULTIPLE 250

int main() {
    initTimer();
    initDisplay();
    turnDisplayOFF();
    startTimer();
    initUSART();

    while (1) {
        // Your main loop code
        // _delay_ms(1000);  // Avoid using delay in a timing-critical loop
    }

    return 0;
}

void initTimer() {
    // Set Timer/Counter Control Register A (TCCR2A) to CTC mode
    TCCR2A |= _BV(WGM21);  // Set WGM21 to 1, enabling CTC mode
    
    // Enable the Output Compare Match A interrupt for Timer 2
    TIMSK2 |= (1 << OCIE2A); // Set OCIE2A to 1
    
    OCR2A = 249;  // Compare match value for 4ms interval (assuming 16MHz clock and prescaler 64)
    
    // Enable global interrupts
    sei();    
}

// This ISR runs every 4 ms
ISR(TIMER2_COMPA_vect) {
    // Increment the counter with 1
    counter++;
    
    // Write the number to the display
    if (counter % 2 == 0) {
      writeNumber(secondsPassed);
      turnDisplayOFF();
    }
    // If the counter is divisible by MULTIPLE, then count 1 sec
    if ((counter % MULTIPLE) == 0) { 
        secondsPassed++;
        printf("\nseconds: %d\n", secondsPassed);
    }
}

void startTimer() {
    // Set the prescaler to 64 and start the timer
    TCCR2B |= _BV(CS22) | _BV(CS21);
}

void stopTimer() {
    // Clear the prescaler bits to stop the timer
    TCCR2B &= ~(_BV(CS22) | _BV(CS21) | _BV(CS20));
}
