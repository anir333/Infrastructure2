#define F_CPU 16000000UL // Define the CPU frequency as 16 MHz

#include <avr/io.h>
#include <avr/interrupt.h>

// Initialize Timer1
void initTimer1() {
    // Set the Timer Mode to CTC (Clear Timer on Compare Match)
    TCCR1B |= (1 << WGM12);

    // Set the prescaler to 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    // Set the compare value for 1 second interval
    OCR1A = 15624; // 16,000,000 / 1024 = 15625

    // Enable the Timer Compare Interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Enable global interrupts
    sei();
}

// ISR (Interrupt Service Routine) for Timer1 Compare Match
ISR(TIMER1_COMPA_vect) {
    // Code to execute every second
    PORTB ^= (1 << PORTB5); // Toggle the LED on pin 13 (PORTB5)
}

int main() {
    // Set pin 13 (PORTB5) as output
    DDRB |= (1 << DDB5);

    // Initialize Timer1
    initTimer1();

    // Main loop
    while (1) {
        // Main code
    }
}
