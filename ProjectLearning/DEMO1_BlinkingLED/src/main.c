#include <avr/io.h>   //Library containing the arduino register definitions
#include <util/delay.h> //Library containing the delay (~sleep) function

int main(){ 
//  DDRB = 0b00010000;  //The 3rd led is connected to PB4, numbered from right to left (start counting from 0)
 while (1){          //A while 1 loop to blink "forever"  
   PORTB = 0b00000000;//we don't apply voltage to PB4, so there is a voltage difference, by consequence the led lights up
   _delay_ms(1000);
   PORTB = 0b00010000;//we apply voltage to PB4, so the voltage difference becomes 0, by consequence the led goes dark
   _delay_ms(1000);
   }
// return 0;
}












// // 1.9 Demo 1 - Blinking LED

// //Use the #include lines to import the C libraries to your code
// //We'll write our own libraries as much as possible, but a number of existing libraries are indispensable.
// #include <util/delay.h> //This library includes the function named _delay_ms(..) which pauses the execution of the program.
// #include <avr/io.h> //Use this library to name the various registers of the ATmega328P microcontroller, like eg DDRB
 
// int main() //Start of the program
// {
//     DDRB = 0b00100000; //Write a binary number to the Data Direction Register B. Pin 5 of port B is enabled for writing with this setting.
//     //DDRB |= 0b00100000; //We could also do a bitwise OR, so that we don't erase ones on other positions of DDRB
//     //DDRB |= (1 << 5); //We could also use the << bitshift operator.
//     //DDRB |= (1 << (PB2 + 3)); //Here we use the port names from io.h to make the code more readable.

//     while (1)
//     {
//         PORTB = (0 << (PB2 + 3)); //We write a 0 to PB2+3 to let the connected LED light up.
//         _delay_ms(1000); //We use the _delay_ms(..) function from delay.h to pause the execution during 1000 milliseconds (1 sec).
//         PORTB = (1 << (PB2 + 3)); //We write a 1 to PB2+3 to let the connected LED go dark.
//         _delay_ms(1000);
//     }
//     return 0;
// }



// 1.10 Demo 2 - Flashing LEDs
// #include <util/delay.h>
// #include <avr/io.h>

// #define NUMBER_OF_LEDS 4 // Define is a "preprocessor directive". It ensures that every NUMBER_OF_LEDS will be replaced by 4 in the following code

// void enableLed ( int lednumber ) //C has no classes; functions can be included directly in the .c file.
// {
//     if ( lednumber < 0 || lednumber > NUMBER_OF_LEDS-1 ) return;
//     DDRB |= ( 1 << ( PB2 + lednumber ));    //Check the tutorial "Writing to a Pin". We know from the documentation on
//                                             //the multifunctional shield that the LEDs start at PB2
// }

// void lightUpLed ( int lednumber )    //Note: enabled LEDs light up immediately ( 0 = on )
// {
//     if ( lednumber < 0 || lednumber > NUMBER_OF_LEDS-1 ) return;
//     PORTB &= ~( 1 << ( PB2 + lednumber ));  //Check the tutorial on "Bit Operations" to know what happens in this line.
// }

// void lightDownLed ( int lednumber )
// {
//     if ( lednumber < 0 || lednumber > 3 ) return;
//     PORTB |= ( 1 << ( PB2 + lednumber ));   //Make sure you understand this line as well!
// }

// int main()
// {
//     for ( int i = 0; i < 4; i++ )
//     {
//         enableLed(i);
//     }
//     while (1)
//     {
//         for ( int i = 0; i < 4; i++ )
//         {
//             lightUpLed(i);
//             _delay_ms( 100 );
//         }
//         for ( int i = 0; i < 4; i++ )
//         {
//             lightDownLed(i);
//             _delay_ms( 100 );
//         }
//     }
//     return 0;
// }



/*
#include <util/delay.h>
#include <avr/io.h>

#define NUMBER_OF_LEDS 4 // Define is a "preprocessor directive". It ensures that every NUMBER_OF_LEDS will be replaced by 4 in the following code

void enableLed ( int lednumber ) //C has no classes; functions can be included directly in the .c file.
{
    if ( lednumber < 0 || lednumber > NUMBER_OF_LEDS-1 ) return;
    DDRB |= ( 1 << ( PB2 + lednumber ));    //Check the tutorial "Writing to a Pin". We know from the documentation on
                                            //the multifunctional shield that the LEDs start at PB2
}

void lightUpLed ( int lednumber )    //Note: enabled LEDs light up immediately ( 0 = on )
{
    if ( lednumber < 0 || lednumber > NUMBER_OF_LEDS-1 ) return;
    PORTB &= ~( 1 << ( PB2 + lednumber ));  //Check the tutorial on "Bit Operations" to know what happens in this line.
}

void lightDownLed ( int lednumber )
{
    if ( lednumber < 0 || lednumber > 3 ) return;
    PORTB |= ( 1 << ( PB2 + lednumber ));   //Make sure you understand this line as well!
}

int main()
{
    for ( int i = 0; i < 4; i++ )
    {
        enableLed(i);
    }
    while (1)
    {
        for ( int i = 0; i < 4; i++ )
        {
            lightUpLed(i);
            _delay_ms( 100 );
            lightDownLed(i);
            _delay_ms( 100 );
        } _delay_ms( 1000 );
    }
    return 0;
}

*/


// others: 




// #include <util/delay.h>
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #define LED_PORT PORTB
// #define BUTTON_PORT PORTC
// #define BUTTON_PIN PINC
// #define LED_DDR DDRB
// #define BUTTON_DDR DDRC
// #define BUTTON1 PC1
// #define LED1 PB2
// #define LED2 PB3

// /* First, review the code in the main function!
//  * This ISR is called when Pin Change Interrupt 1 is triggered (PCINT1_vect)
//  * This is the interrupt for PORTC, where the switches/buttons are connected... */
// ISR( PCINT1_vect )
// {
//     // button 1 is pressed (bit is set to 0)?
//     if ( bit_is_clear( BUTTON_PIN, BUTTON1 ))
//     {
//         //We wait 1000 microseconds and check again (debounce!)
//         _delay_us( 1000 );
//         // button 0 is pressed (bit is set to 0)?
//         if ( bit_is_clear( BUTTON_PIN, BUTTON1 ))
//         {
//             if ( bit_is_set( LED_PORT, LED2 ))  // if led2 is off (bit is set to 1)
//             {
//                 LED_PORT &= ~_BV( LED2 );       // turn led2 on (set bit to 0)
//             }
//             else                                // else
//             {
//                 LED_PORT |= _BV( LED2 );        // turn led2 off (set bit to 1)
//             }
//         }
//     }
// }

// int main()
// {
//     LED_DDR |= _BV( LED1 ) | _BV( LED2 );   // we'll use led1 and led2
//     LED_PORT |= _BV( LED1 ) | _BV( LED2 );  // turn 2 leds off
//     BUTTON_DDR &= ~_BV( BUTTON1 );          // we'll use button1
//     BUTTON_PORT |= _BV( BUTTON1 );          // enable pull-up
//     PCICR |= _BV( PCIE1 );  /* in Pin Change Interrupt Control Register: indicate
//                              * which interrupt(s) you want to activate (PCIE0: port B,
//                              * PCIE1: port C, PCIE2: port D) */
//     PCMSK1 |= _BV( BUTTON1 );   /* In the corresponding Pin Change Mask Register: indicate
//                                  * which pin(s) of that port activate the ISR. */
//     sei();  // Set Enable Interrupts --> activate the interrupt system globally.
//     while ( 1 )
//     {
//         LED_PORT &= ~_BV( LED1 );   // turn led1 on
//         _delay_ms( 1000 );
//         LED_PORT |= _BV( LED1 );    // turn led1 off
//         _delay_ms( 1000 );
//     }
//     return 0;
// }
















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
 













// // #include <avr/io.h>
// // #include <stdio.h>
// // #include <stdint.h>
// // #include <util/delay.h>

// int main() {
//   int last = 0b00100000; // last
//   int second = 0b00001000; // second
//   int first = 0b00000100; // first
//   int third = 0b00001000; // third
//   // PORTB  = 0b00000000;
//   // DDRB = 0b00000000;
//   DDRB = 0b00001000;
//   PORTB = 0b00001000;

//   while (1) {
//     DDRB = 1 << 2;
//     _delay_ms(1000);
//     // PORTB = 1 << 2;

//     DDRB = 1 << 3;
//     _delay_ms(1000);
//     // PORTB = 1 << 3;
    
//     DDRB = 1 << 4;
//     _delay_ms(1000);
//     // PORTB = 1 << 4;

//     DDRB = 1 << 5;
//     _delay_ms(1000);
//     // PORTB = 1 << 5;

//     // DDRB = 0b00111100;
//     // _delay_ms(1000);
//     // DDRB = 0b00000000;
//     // _delay_ms(1000);
//   }
//   // int count = 0;
//   // while (count < 10000000000000000000000) {
//   //     if (DDRB == first) {
//   //       DDRB = second;
//   //     } else if (DDRB == second) {
//   //       DDRB = third;
//   //     } else if (DDRB == third) {
//   //       DDRB = last;
//   //     } else if (DDRB == last) {
//   //       DDRB = first;
//   //     }

//   //     _delay_ms(1000);
//   //     count++;
//   // }
//   return 0;
// }




// #include <avr/io.h>
// #include <util/delay.h>

// int main() {
//     // Configure pins 2, 3, 4, and 5 of PORTB as outputs
//     DDRB = 0b00111100;

//     while (1) {  // Infinite loop
//         // Turn on LED connected to pin 2, turn off others
//         PORTB = (1 << PB2);
//         _delay_ms(1000);

//         // Turn on LED connected to pin 3, turn off others
//         PORTB = (1 << PB3);
//         _delay_ms(1000);

//         // Turn on LED connected to pin 4, turn off others
//         PORTB = (1 << PB4);
//         _delay_ms(1000);

//         // Turn on LED connected to pin 5, turn off others
//         PORTB = (1 << PB5);
//         _delay_ms(1000);
//     }

//     return 0;
// }





// #include <avr/io.h>
// #include <util/delay.h>

// int main() {
//     // Configure pins 2, 3, 4, and 5 of PORTB as outputs
//     DDRB = (1 << 2) ^ (1 << 3) ^ (1 << 4) ^ (1 << 5);

//     while (1) {  // Infinite loop
//         // Turn on LED connected to pin 2, turn off others
//         PORTB = (1 << PB2);
//         _delay_ms(1000);

//         // Turn on LED connected to pin 3, turn off others
//         PORTB = (1 << PB3);
//         _delay_ms(1000);

//         // Turn on LED connected to pin 4, turn off others
//         PORTB = (1 << PB4);
//         _delay_ms(1000);

//         // Turn on LED connected to pin 5, turn off others
//         PORTB = (1 << PB5);
//         _delay_ms(1000);
//     }

//     return 0;
// }
