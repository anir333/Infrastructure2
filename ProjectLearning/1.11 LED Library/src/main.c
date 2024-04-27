#include <avr/io.h>   //Library containing the arduino register definitions
#include <util/delay.h> //Library containing the delay (~sleep) function
#include <usart.h>

int main(){ 
//   initUSART();
//  DDRB = 0b00001000;  //The 3rd led is connected to PB4, numbered from right to left (start counting from 0)
//  PORTB = 0b00000000; // we don't apply voltage so there is a voltage difference so the led at pin 3 lights up
//  while (1){          //A while 1 loop to blink "forever"  
//    PORTB = 0b00000000;//we don't apply voltage to PB4, so there is a voltage difference, by consequence the led lights up
//    _delay_ms(1000);
//    PORTB = 0b00011100;//we apply voltage to PB4, so the voltage difference becomes 0, by consequence the led goes dark
//    _delay_ms(1000);
//    }
return 0;
}






// Testin library usart :


// #include <util/delay.h>
// #include <avr/io.h>
// #include <usart.h>

// int main() {
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
// }