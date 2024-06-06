#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <display.h>
#include <display.c>

int main()
{
    initUSART();
    initDisplay();


    // while ( 1 ) {
    //     writeNumberToSegmentAnir( FIRST_DIGIT, TWO );
    //     _delay_ms( 1 );
    //     writeNumberToSegmentAnir( SECOND_DIGIT, ZERO );
    //     _delay_ms( 1 );
    //     writeNumberToSegmentAnir( THIRD_DIGIT, ZERO );
    //     _delay_ms( 1 );
    //     writeNumberToSegmentAnir( FOURTH_DIGIT, FOUR );
    //     _delay_ms( 1 );
    //     writeNumberToSegmentAnir( FIRST_DIGIT, ZERO );
    //     _delay_ms( 1 ); 
    //     for (int i = 0; i< 400; i++) {
    //         writeNumberToSegmentAnir ( FOURTH_DIGIT, ZERO );
    //         _delay_ms( 1 );
    //     } printf("done");
    //     turnDisplayOFF();
    // }
    

    while ( 1 )
    {
        for ( int i = 0; i < 4; i++ )
        {
            writeNumberToSegment( i, 8 );
            _delay_ms( 1000 );
        }
        /* Use the writeNumber function if
         * you want to display a 4 digit number. */
        writeNumber( 1974 );
        _delay_ms( 1000 );
        /* Problem: this function shows the digits 1 by 1 and then
         * adds a delay. So, only the last digit is displayed. 
         * Solution: to display the complete number, repeat this in a loop. */
        for ( int i = 0; i < 10000; i ++ )
        {
            writeNumber( 1974 );
        }
        /* Or you could use a function from the library.
         * Then you can also specify the display duration. */
        writeNumberAndWait( 1974, 1000 );
        break;
    }
    turnDisplayOFF();
    return 0;
}

// #include <usart.h>

// int main() {
//     initUSART();

//     int number = 4;
//     int nums[5] = { 0, 1, 2, 3 };
//     printf("Size of an int in C: %d\n", sizeof(number));
//     printf("Size of an int array[] in C: %d\n", sizeof(nums));
//     printf("Size of an int type in C: %d\n", sizeof(int));

//     int four = 4000000000;
//     printf("\nSize of four: %d and four: %d\n", sizeof(four), four);

//     return 0;
// }