#include <avr/io.h>   //Library containing the arduino register definitions
#include <util/delay.h> //Library containing the delay (~sleep) function
#include <usart.h>
#include <button.h>
#include <LEDs.h>
#include <LCD.h>
#include <display.h>






ISR(PCINT1_vect) {

    if (buttonPushed(1)) {
        _delay_us(500);
        lightUpAllLeds();
        updateLCDScreen(2, "PUSHED", NONE, "!");
    }
}


int timer = 0;
int main() {
    // initUSART();
    initDisplay();
    // turnDisplayOFF();

    enableAllButtons();
    enableAllButtonInterrupts();
    initLCD();
    // lcd_write_instruction_4f(lcd_Clear);
    updateLCDScreen(1, "Button 1 is", NONE, ":");
    

    enableAllLeds();
    
    while ( 1 )
    {
        // writeNumberToSegmentAnir( FIRST_DIGIT, TWO );
        // _delay_ms ( 1 );
        // writeNumberToSegmentAnir( SECOND_DIGIT, ZERO );
        // _delay_ms ( 1 );
        // writeNumberToSegmentAnir( THIRD_DIGIT, ZERO );
        // _delay_ms ( 1 );
        // writeNumberToSegmentAnir( FOURTH_DIGIT, FOUR );
        // writeNumberAndWait(timer, 1000);
        writeNumberToSegmentAnir( FIRST_DIGIT, THREE );
        _delay_ms ( 1 );
        if ( buttonPushed(1) ) {
            printf("\nButton 1 Pushed !!!\n");
        } else {
            printf("\n NOT PUSHED!");
            lightDownAllLeds();
            updateLCDScreen(2, "NOT PUSHED", NONE, "!");
        }
        // pauseSeconds(1);
        printf("timer: %d\n", timer);
        timer++;
        // _delay_ms(100);
    }
} 















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
