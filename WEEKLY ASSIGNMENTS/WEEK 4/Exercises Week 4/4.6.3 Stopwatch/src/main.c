#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "display.h"
#include "usart.h"
#include <button.h>

// Global variables
int counter = 0;
int totalSeconds = 0;
int seconds = 0;
int minutes = 0;
// Enter here your global variables

void initTimer() {    
    // Set Timer/Counter Control Register A (TCCR2A) to CTC mode
    TCCR2A |= _BV( WGM21 );  // Set WGM21 to 1, enabling CTC mode
    
    // Enable the Output Compare Match A interrupt for Timer 2
    TIMSK2 |= (1 << OCIE2A); // Set OCIE2A to 1
    
    OCR2A = 249;

    // Enable global interrupts
    sei();    
}

void startTimer() {    
    TCCR2B |= _BV(CS22) | _BV(CS21);
}

void stopTimer() {    
    TCCR2B &= ~(_BV(CS22) | _BV(CS21) | _BV(CS20));
}

void tick() {    
    minutes = totalSeconds / 60;
    seconds = totalSeconds % 60;
}


#define MULTIPLE 250

// This ISR runs every 4 ms
ISR(TIMER2_COMPA_vect) {
    // Increment the counter with 1
    counter++;
    // If the counter + 1 is divisible by MULTIPLE, then count 1 sec
    if (((counter + 1) % MULTIPLE) == 0) { 
        totalSeconds++;
        tick();
        printf("\n\nMinutes: %d Seconds: %d", minutes, seconds);
    }

}

ISR( PCINT1_vect ) {
    if ( buttonPushed(1) ) {
        startTimer();
    }
    if ( buttonPushed(2) ) {
        stopTimer();
    }
    if ( buttonPushed(3) ) {
        totalSeconds = 0;
    }
}

int main() {    
    initUSART();    
    initDisplay();
    turnDisplayOFF();
    initTimer();
    // init_timer1();
    enableAllButtons();
    enableAllButtonInterrupts();

    printf("\n\nStart the stopwatch by pressing button S1, stop by pressing button S2, and reset with S3\n");    
    
    while (1) {        
        writeTimeAndWait();
    }
    return 0;
}

void writeTimeAndWait() {
    writeNumberToSegment(0, minutes / 10);
    writeIntToSegmentWithDotAnir(SECOND_DIGIT, minutes % 10);
    writeNumberToSegment(2, seconds / 10);
    writeIntToSegmentAnir( FOURTH_DIGIT, seconds % 10 );
}

// void init_timer1() {
//     // Set Timer/Counter Control Register A (TCCR1A) to Normal mode
//     TCCR1A = 0;

//     // Set prescaler to 64
//     TCCR1B |= (1 << CS11) | (1 << CS10);  // CS11 = 1 and CS10 = 1 (prescaler 64)

//     // Enable Timer 1 overflow interrupt
//     TIMSK1 |= (1 << TOIE1);  // Enable overflow interrupt

//     // Initialize the counter value to achieve 10 ms interval
//     TCNT1 = 65536 - 2500;  // 2500 counts for 10 ms with prescaler of 64 and 16 MHz clock

//     sei();
// }

// ISR(TIMER1_OVF_vect) {
//     // Reload the timer count to get 10 ms intervals
//     TCNT1 = 65536 - 2500;

//     // Execute your method
//     // writeTimeAndWait();
//     // turnDisplayOFF();
// }