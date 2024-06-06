#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <display.h>

#include <avr/interrupt.h>

void initTimer0()
{
    // STEP 1: choose the WAVE FORM and by consequence the Mode of Operation
    // We choose FAST PWM; TCNT0 counts to 255
    TCCR0A |= _BV(WGM00) | _BV(WGM01); // WGM00 = 1 and WGM01 = 1 --> Fast PWM Mode

    // STEP 2: *always* set a PRESCALER, otherwise the timer won't count
    // The counting speed is determined by the CPU clock (16 Mhz) divided by this factor
    TCCR0B |= _BV(CS01) | _BV(CS00); // CS00 and CS01 = 1 --> prescaler, factor is now 64
    // STEP 3: enable INTERRUPTS
    // Enable interrupts for overflow: TCNT0 == TOP
    TIMSK0 |= _BV(TOIE0); // enable overflow interrupt
}

// This ISR runs every time TCNT0 equals the TOP value (255)
ISR(TIMER0_OVF_vect)
{
    writeNumber(2023);
    blankSegment(3); // Otherwise the last segment is much brighter than the rest
}

int main()
{
    initUSART();
    initDisplay();
    initTimer0(); // initialize Timer 0
    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            writeNumberToSegment(i, 8);
            _delay_ms(1000);
        }
        /* Use the writeNumber function if
         * you want to display a 4 digit number. */
        writeNumber(1974);
        _delay_ms(1000);
        /* Problem: this function shows the digits 1 by 1 and then
         * adds a delay. So, only the last digit is displayed.
         * New Solution: use a timer/interrupt */

        sei(); // enable interrupts globally
        _delay_ms(2000);
        cli(); // disable interrupts globally

        /* Or you could use a function from the library.
         * Then you can also specify the display duration. */
        writeNumberAndWait(1974, 2000);
    }
    return 0;
}


// #include <avr/interrupt.h>
// #include <avr/io.h>
// #include <util/delay.h>
// #include <usart.h>

// uint32_t counter = 0;

// void initTimer0()
// {
//     // STEP 1: choose the WAVE FORM and by consequence the Mode of Operation
//     // We choose FAST PWM; TCNT0 counts to 255
//     TCCR0A |= _BV( WGM00 ) | _BV( WGM01 );  // WGM00 = 1 and WGM01 = 1 --> Fast PWM Mode

//     // STEP 2: *always* set a PRESCALER, otherwise the timer won't count
//     // The counting speed is determined by the CPU clock (16 Mhz) divided by this factor
//     TCCR0B |= _BV( CS02 ) | _BV( CS00 );    // CS02 = 1 and CS00 = 1 --> prescaler factor is now 1024 (= every 64 us)

//     // STEP 3: enable INTERRUPTS
//     // Enable interrupts for 2 cases: TCNT0 == TOP and TCNT0 == OCR0A
//     TIMSK0 |= _BV( TOIE0 ); // enable overflow interrupt
//     TIMSK0 |= _BV( OCIE0A );    // enable OCRA interrupt

//     sei();  // enable interrupts globally
// }

// // This ISR runs every time TCNT0 equals the value in the OCRA register
// ISR( TIMER0_COMPA_vect )
// {
//     counter++;
//     PORTB &= ~( _BV( PB2 ) | _BV( PB3 ) | _BV( PB4 ) | _BV( PB5 ));
// }

// // This ISR runs every time TCNT0 equals the TOP value (255)
// ISR( TIMER0_OVF_vect )
// {
//     counter++;
//     PORTB |= _BV( PB2 ) | _BV( PB3 ) | _BV( PB4 ) | _BV( PB5 );
// }

// int main()
// {
//     initUSART();
//     initTimer0();   //initialize Timer 0
//     DDRB |= _BV( PB2 ) | _BV( PB3 ) | _BV( PB4 ) | _BV( PB5 );  //Place the LEDs in output mode

//     while (1)
//     {
//         printf( "**********************************************************************************\n" );
//         printf( "*********************************** Tick Tock Demo *******************************\n" );
//         printf( "**********************************************************************************\n" );

//         printf( "Timer 0 is set to increment its TCNT0 register every 64 us up to a maximum of 255.\n" );
//         printf( "Observe the LEDs...\n" );

//         printf( "Enter the OCR0A value in 3 digit format (000-255): " );

//         OCR0A = getNumber(); // OCR0A can always be chosen freely between 0 and 255

//         printf( "Timer 0 generates *in the background* continuously two interrupts:\n" );
//         printf( "\t*) when the ORC0A (%d) is reached.\n", OCR0A );
//         printf( "\t*) when TOP (%d) is reached.\n\n", 255 );

//         printf( "Meanwhile we are at a total of %d interrupts.\n\n", counter );
//     }

//     return 0;
// }