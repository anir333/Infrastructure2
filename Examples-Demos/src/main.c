#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>

void increment_byref( int* a)
{
    printf( "Incrementing a (%d)\n", *a);
    (*a)++;
}

void increment_byval( int a )
{
    printf( "Incrementing a (%d)\n", a );
    a++;
}

void array_as_parameter( int* p )
{
    //how large is the array in bytes?
    printf( "sizeof array as parameter: %d\n" , sizeof( p ));
}

int main()
{
    initUSART();
    int a = 10;
    int* b = &a;
    int c[] = { 1,2,3 };
    int d[] = { 1,2,3,4,5,6 };

    // print the value of a
    printf( "Value of a: %d\n", a );
    // how many bytes does an int take up?
    printf( "sizeof a: %d\n", sizeof( a ));
    // In what memory address is a stored (in hex)?
    // (you could use %d if you wanted to see the address in decimal, but ignore the warning then...)
    printf( "Value of &a: %p %d\n", &a, &a );
    // b has the address of a
    printf( "Value of b: %p\n", b );
    //how large is b (how large is an int pointer)?
    printf( "sizeof b: %d\n", sizeof( b ));
    // And what is the address of b itself?
    printf( "Value of &b: %p\n", &b );
    // An array is actually a pointer to the first element...
    printf( "Value of c: %p\n", c );
    // So, an array is the address of the first element...
    printf( "Value of &c[0]: %p\n", &c[0] );
    // What's the size of the array in bytes?
    printf( "sizeof c: %d\n", sizeof( c ));
    // Pass the array as a parameter
    array_as_parameter( c );
    printf( "Value of d: %p\n", d );
    printf( "sizeof d: %d\n", sizeof( d ));
    increment_byval( a );
    printf( "Value of a after by val increment: %d\n", a );
    increment_byref( &a );
    printf( "Value of a after by ref increment: %d\n", a );

    return 0;
}
// #include <util/delay.h>
// #include <avr/io.h>
// #include <usart.h>

// /* In this code we'll use some predefined macros, like _BV and bit_is_clear
//  * These macros make the code more readable.
//  * They are defined in avr/sfr_defs.h and are included in avr/io.h. */

//  //#define DEBUG             //if this line is uncommented, debug info will be printed

// int main()
// {
//     initUSART();
//     DDRC &= ~_BV( PC1 );    /* Set up DDR, instead of using ( 1 << PC1 ) we use the
    
//                              * macro _BV( bit ). (BV stands for "Bit Value") */
//     #ifdef DEBUG            // The following code is only printed when DEBUG is defined
//     printf( "DDRC: " );
//     printBinaryByte( DDRC );
//     #endif

//     PORTC |= _BV( PC1 );    /* Activate pull-up of C1.
//                              * We use the macro _BV( bit ) instead of ( 1 << PC 1 ) */
//     #ifdef DEBUG
//     printf( "\nPORTC: " );
//     printBinaryByte( PORTC );
//     #endif

//     while ( 1 )
//     {
//         printf( "\nPINC: " );
//         printBinaryByte( PINC );
//         if ( bit_is_clear( PINC, PC1 )) /* instead of (!(PINC & ( 1 << PC1 ))) we use the macro bit_is_clear */
//         {
//             printf( " - Button 1 pressed!\n" );
//         }
//         else
//         {
//             #ifdef DEBUG
//             printf( " - Button 1 NOT pressed!!\n" );
//             #endif
//         }
//         _delay_ms( 1000 );
//     }
//     return 0;
// }





// #include <util/delay.h>
// #include <avr/io.h>
// #include <usart.h>

// int main()
// {
//     initUSART();
//     DDRC &= ~( 1 << PC1 );  /* Button 1 is connected to C1.
//                              * We set the corresponding bit in the Data Direction Register to 0. */
//     printf( "DDRC: " );
//     printBinaryByte( DDRC );
//     PORTC |= ( 1 << PC1 );  /* Activate the Pull-up of C1: PINC will be set to high */
//     printf( "\nPORTC: " );
//     printBinaryByte( PORTC );
//     while ( 1 )
//     {
//         printf( "\nPINC: " );
//         printBinaryByte( PINC );
//         if (( PINC & ( 1 << PC1 )) == 0 )   /* This way we can test whether the PC1 bit
//                                              * of PINC is set to 0 (button is pressed) */
//         {
//             printf( " - Button 0 pressed!\n" );
//         }
//         else
//         {
//             printf( " - Button 0 NOT pressed!!\n" );
//         }
//         _delay_ms( 1000 );
//     }
//     return 0;
// }