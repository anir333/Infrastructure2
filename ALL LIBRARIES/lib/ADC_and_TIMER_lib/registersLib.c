#include <avr/io.h>
#include <button.h>

void initADC()
{
    ADMUX |= (1 << REFS0); // Set up the reference voltage. We choose 5V as the reference.
    ADMUX &= ~(1 << MUX3  ) & ~(1 << MUX2  ) & ~(1 << MUX1 ) & ~(1 << MUX0 );
     //Set MUX0-3 to zero to read analog input from PC0
     //Default is 0000 so this setting is not really necessary     
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Determine the sample rate by setting the division factor to 128.
    ADCSRA |= (1 << ADEN);                                // Enable the ADC
    ADCSRA |= (1 << ADATE);                               // Enable ADC Auto Triggering
    ADCSRB = 0;                                                // Set ADC Auto Trigger Source to Free Running Mode (default)
    ADCSRA |= (1 << ADSC);                                // Start the analog-to-digital conversion
}

void initTimer0()
{
    // STEP 1: choose the WAVE FORM and by consequence the Mode of Operation
    // We choose FAST PWM; TCNT0 counts to 255
    TCCR0A |= _BV( WGM00 ) | _BV( WGM01 );  // WGM00 = 1 and WGM01 = 1 --> Fast PWM Mode

    // STEP 2: *always* set a PRESCALER, otherwise the timer won't count
    // The counting speed is determined by the CPU clock (16 Mhz) divided by this factor
    TCCR0B |= _BV( CS02 ) | _BV( CS00 );    // CS02 = 1 and CS00 = 1 --> prescaler factor is now 1024 (= every 64 us)

    // STEP 3: enable INTERRUPTS
    // Enable interrupts for 2 cases: TCNT0 == TOP and TCNT0 == OCR0A
    TIMSK0 |= _BV( TOIE0 ); // enable overflow interrupt
    TIMSK0 |= _BV( OCIE0A );    // enable OCRA interrupt

    sei();  // enable interrupts globally
}


void initTIMER0() {
    TCCR0A |= _BV(WGM00) | _BV(WGM01); // WGM00 = 1 and WGM01 = 1 --> Fast PWM Mode
    TCCR0B |= _BV(CS02) | _BV(CS00); // CS02 = 1 and CS00 = 1 --> prescaler factor is now 1024
}

void enableTimer0Interrput() {
    TIMSK0 |= _BV(TOIE0);   // enable overflow interrupt
    TIMSK0 |= _BV(OCIE0A);  // enable OCRA interrupt

    activateInterruptSystemGlobally;  // enable interrupts globally -> sei();
}