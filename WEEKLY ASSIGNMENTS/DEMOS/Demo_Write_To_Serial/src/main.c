#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>

int main()
{
    initUSART();
    DDRC &= ~( 1 << PC1 );  /* Button 1 is connected to C1.
                             * We set the corresponding bit in the Data Direction Register to 0. */
    printf( "\nDDRC: " );
    printBinaryByte( DDRC );
    PORTC |= ( 1 << PC1 );  /* Activate the Pull-up of C1: PINC will be set to high */
    printf( "\nPORTC: " );
    printBinaryByte( PORTC );
    while ( 1 )
    {
        printf( "\nPINC: " );
        printBinaryByte( PINC );
        if (( PINC & ( 1 << PC1 )) == 0 )   /* This way we can test whether the PC1 bit
                                             * of PINC is set to 0 (button is pressed) */
        {
            printf( " - Button 0 pressed!\n" );
        }
        else
        {
            printf( " - Button 0 NOT pressed!!\n" );
        }
        _delay_ms( 1000 );
    }
    return 0;
}


// #include <util/delay.h>
// #include <avr/io.h>
// #include <LEDs.h>
// #include <usart.h>  /* This preprocessor directive makes sure that all the function declarations
//                      * of the usart library are loaded.
//                      * Check the tutorial of week 1: "1.8 Using your own library in VS Code" */

// int main()
// {
//     DDRB |= ( 1 << PB2 );
//     initUSART();    /* We call a function from usart.h.
//                      * This function initializes the communication with the serial port. */
//     int counter = 0;
//     while (1)
//     {
//         PORTB = ( 1 << PB2 );
//         _delay_ms( 100 );
//         PORTB = ( 0 << PB2 );
//         _delay_ms( 100 );
//         printString( " Debugging!! " );  /* We call a function from usart.h.
//                                          * If everything is ok, then this text
//                                          * should appear at the bottom of the screen,
//                                          * in the Serial Monitor. */
//         printf( "Counter: %d\n", counter ); /* We call the printf function, from the standard C library.
//                                              * This function is very similar to System.out.printf in Java. */
//         counter++;
//     }
//     return 0;
// }