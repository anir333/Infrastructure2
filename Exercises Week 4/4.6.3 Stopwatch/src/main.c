#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "display.h"
#include "usart.h"

// Global variables
int counter = 0;
long seconds = 0;
// Enter here your global variables

void initTimer() {    
    // Set Timer/Counter Control Register A (TCCR2A) to CTC mode
    TCCR2A |= _BV( WGM21 );  // Set WGM21 to 1, enabling CTC mode
    
    // Enable the Output Compare Match A interrupt for Timer 2
    TIMSK2 |= (1 << OCIE2A); // Set OCIE2A to 1
    
    // Enable global interrupts
    sei();    
}

void startTimer() {    
    // enter your code
}

void stopTimer() {    
    // enter your code
}

void tick() {    
    // enter your code
}

void writeTimeAndWait(uint8_t minuten, uint8_t seconden, int delay) {    
    // enter your code
}

#define MULTIPLE 250

// This ISR runs every 4 ms
ISR(TIMER2_COMPA_vect) {
    // Increment the counter with 1
    counter++;
    // If the counter + 1 is divisible by MULTIPLE, then count 1 sec
    if ((counter + 1) % MULTIPLE) seconds++;
}

int main() {    
    initUSART();    
    initDisplay();
    printf("Start the stopwatch by pressing button S1, stop by pressing button S2, and reset with S3\n");    
    while (1) {        
        // Don't forget to initialize and start your timer
        // Also, don't forget sei()    
    }
    return 0;
}


//  initTimer();
    
//     // Set the value of the Output Compare Register A (OCR2A)
//     OCR2A = 249; // Example value, modify as needed
    
//     // Start the timer with a prescaler (example: prescaler 64)
//     TCCR2B |= (1 << CS22); // Set CS22 to 1, starting the timer with prescaler 64
    
//     while (1) {
//         // Main loop
//     }
// }