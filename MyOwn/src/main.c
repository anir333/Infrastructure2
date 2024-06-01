#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <LCD.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <button.h>
#include <display.h>
#include <LEDs.h>
#include <registersLib.h>
#include <string.h>
#include <usart.h>

int seconds = 0;

int main() {
    // Initialize the LCD
    // initUSART();
    initLCD();
    // initUSART();
    initDisplay();
    enableAllLeds();
    turnDisplayOFF();
    initTimer();
    // startTimer();
    enableAllButtons();
    enableAllButtonInterrupts();

    while (1) {
        lightUpAllLeds();
        writeNumber(seconds);
        // updateLCDScreen(1, "Heelloo", NONE, "!11");
    }
    
    return 0;
}
void startTimer() {    
    TCCR2B |= _BV(CS22) | _BV(CS21);
}

void stopTimer() {
    TCCR2B &= ~(_BV(CS22) | _BV(CS21) | _BV(CS20));
}

void initTimer() {    
    // Set Timer/Counter Control Register A (TCCR2A) to CTC mode
    TCCR2A |= _BV( WGM21 );  // Set WGM21 to 1, enabling CTC mode
    
    // Enable the Output Compare Match A interrupt for Timer 2
    TIMSK2 |= (1 << OCIE2A); // Set OCIE2A to 1
    
    OCR2A = 249;

    // Enable global interrupts
    sei();    
}


ISR ( PCINT1_vect ) {
    if(buttonPushed(1)) {
        stopTimer();
    }
    if (buttonPushed(2)) {
        startTimer();
    }
}

char str[5];

#define MULTIPLE 250
int counter = 0;
// This ISR runs every 4 ms
ISR(TIMER2_COMPA_vect) {
    // Increment the counter with 1
    counter++;
    // If the counter + 1 is divisible by MULTIPLE, then count 1 sec
    if (((counter + 1) % MULTIPLE) == 0) { 

        // printf("\nDisplay LCD initilaise renew!\n");
        printString("USART Initialized\n");
        // _delay_ms(10);     
        seconds++;
        
        sprintf(str, "%d", seconds);
        updateLCDScreen(1, "Heelloo", NONE, str);
    }

}






























// #include <avr/io.h>   //Library containing the arduino register definitions
// #include <util/delay.h> //Library containing the delay (~sleep) function
// #include <usart.h>
// #include <button.h>
// #include <LEDs.h>
// #include <LCD.h>
// #include <display.h>






// ISR(PCINT1_vect) {

//     if (buttonPushed(1)) {
//         _delay_us(500);
//         lightUpAllLeds();
//         updateLCDScreen(2, "PUSHED", NONE, "!");
//     }
// }


// int timer = 0;
// int main() {
//     // initUSART();
//     initDisplay();
//     // turnDisplayOFF();

//     enableAllButtons();
//     enableAllButtonInterrupts();
//     initLCD();
//     // lcd_write_instruction_4f(lcd_Clear);
//     // updateLCDScreen(1, "Button 1 is", NONE, ":");
    

//     enableAllLeds();
    
//     while ( 1 )
//     {
//         // writeNumberToSegmentAnir( FIRST_DIGIT, TWO );
//         // _delay_ms ( 1 );
//         // writeNumberToSegmentAnir( SECOND_DIGIT, ZERO );
//         // _delay_ms ( 1 );
//         // writeNumberToSegmentAnir( THIRD_DIGIT, ZERO );
//         // _delay_ms ( 1 );
//         // writeNumberToSegmentAnir( FOURTH_DIGIT, FOUR );
//         // writeNumberAndWait(timer, 1000);


//         // writeNumberToSegmentAnir( FIRST_DIGIT, THREE );
//         _delay_ms ( 1 );
//         // if ( buttonPushed(1) ) {
//         //     printf("\nButton 1 Pushed !!!\n");
//         // } else {
//             // printf("\n NOT PUSHED!");
//             // lightDownAllLeds();
//             updateLCDScreen(1, "- - - -_ _--_-", NONE, "");
//             updateLCDScreen(2, "____  --_--_-", NONE, "");
//         // }
//         // pauseSeconds(1);
//         // printf("timer: %d\n", timer);
//         // timer++;
//         // _delay_ms(100);
//     }
// } 















// int main(void) {
//     initDisplay(); // Initialize the display
//     displayFlashingP(); // Call the function to display the flashing sequence
//     return 0; // This will never be reached because of the infinite loop
// }



// void displayFlashingP() {
//     while (1) { // Infinite loop to keep the display repeating
//         // Display "1P21"
//         writeNumberToSegment(0, 1); // Display '1' on the first digit
//         writeCharToSegment(1, 'P'); // Display 'P' on the second digit
//         writeNumberToSegment(2, 2); // Display '2' on the third digit
//         writeNumberToSegment(3, 1); // Display '1' on the fourth digit
        
//         _delay_ms(500); // Wait for 500 milliseconds (half a second)
        
//         // Turn off the second digit to make 'P' flash
//         writeNumberToSegment(0, 1); // Display '1' on the first digit
//         writeNumberToSegment(1, 0xFF); // Turn off the second digit
//         writeNumberToSegment(2, 2); // Display '2' on the third digit
//         writeNumberToSegment(3, 1); // Display '1' on the fourth digit
        
//         _delay_ms(500); // Wait for 500 milliseconds (half a second)
//     }
// }
































// #include <stdlib.h>
// #include <string.h>
// #include <stdio.h>
// #include <LCD.h> // Include the header file correctly
// #include <LEDs.h>

// int main() {
//     // Initialize the LCD
    
//     initLCD();
//     lcd_write_string_4f("0123");
//     pauseSeconds(1);
//     lcd_write_instruction_4f(lcd_Clear);
//     // enableAllLeds();
//     // updateLCDScreen(1, "-", NONE, ":");
    
//     // char timeString[50];
//     // int time = 0;
//     // while (1) {
//     //     sprintf(timeString, "%d", time);
//     //     updateLCDScreen(2, timeString, NONE, " !!");
//     //     time++;
//     //     _delay_ms(1000);
//     // }

//     // while ( 1 ) {
        
//     // }
//     // {
//         /* code */
//     // }
    

//     // Write something to the first row of the LCD
//     // updateLCDScreen(1, "HOLA", NONE, "MAJDU!!!");

//     // Wait for a while before updating again
//     // _delay_ms(1000);

//     return 0;
// }
