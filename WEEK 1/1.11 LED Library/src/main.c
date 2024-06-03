#include <avr/io.h>   //Library containing the arduino register definitions
#include <util/delay.h> //Library containing the delay (~sleep) function
#include <usart.h>
#include <LEDs.h>


int main() {
    
    enableOneLed(2);
    enableMultipleLeds(0b00111100); 
pauseSeconds(1);
    enableAllLeds ();
pauseSeconds(1);
    lightUpOneLed(2); 
pauseSeconds(1);
    lightUpMultipleLeds (0b00101000);
pauseSeconds(1);
    lightUpAllLeds (); 
pauseSeconds(1);
    lightDownOneLed(1); 
pauseSeconds(1);
    lightDownMultipleLeds (0b00101100);
pauseSeconds(1);
    lightDownAllLeds (); 
pauseSeconds(1);
    lightUpAllLeds();
pauseSeconds(1);
    lightToggleOneLed(3);
 
  return 0;
}



// Testing usart library :


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