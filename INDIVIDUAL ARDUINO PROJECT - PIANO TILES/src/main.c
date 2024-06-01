/* Libraries included */
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <usart.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <LCD.h> // LCD library
#include <LEDs.h> // LED library
#include <button.h> // Button library
#include <buzzer.h> // Buzzer library
#include <registersLib.h> // Contains functions for Timers and ADC (Potentiometer)
#include <display.h> // Display library
/* END of libraries */

/*  Definitions */
    // making my own booleans to improve code readability
#define true  1
#define false 0

  // For digits that need to be turned OFF on the 7 segment display
#define EMPTY_DIGIT 0xFF

    // The speed of the game is chosen by the user by turning the potentiometer, there are 5 possible speeds, 1-slow | 5-fast 
#define SPEED1 204.6  // Speed of tiles -> 2 seconds
#define SPEED2 409.2  // Speed of tiles -> 1.5 seconds
#define SPEED3 613.8  // Speed of tiles -> 1 seconds
#define SPEED4 818.4  // Speed of tiles -> 0.75 seconds
#define SPEED5 1023   // Speed of tiles -> 0.5 seconds

  // Defines the maximum capacity of characters for one row of the LCD screen
#define MAX_ROW_LENGTH 16
/* END of Definitions */


/* Global Variables */
uint8_t gameStarted = false;
uint8_t speedChosen = false;
uint16_t speedMultiple = 250; // default 1 second speed but can change up to 500
uint8_t continueGame = true;
uint8_t generateTileNow = false;
volatile unsigned long counter = 0;
/* END of global variables */


/* Button Interrputs */
ISR( PCINT1_vect ) {
  if ( buttonPushed( BUTTON_ONE ) ) {
    if (gameStarted && !speedChosen) {
      speedChosen = true;
    }
    if (!gameStarted) {
      gameStarted = true;
    }
  }
}





int main() {
    /* Initialisation of elements used during the game */
    initLCD(); // Initialize the LCD
    initDisplay(); // Initialize the 4-digit 7 segment display
    turnDisplayOFF(); // Turn 7 segment display off until its used 
    initADC(); // Initialize ADC to read input (potentiometer)
    enableAllLeds(); // enable all LEDs for ouput
    enableAllButtons(); // enable all buttons for input
    enableAllButtonInterrupts(); // enable the interrupts for all the buttons


    waitForStartOfGame();
    
    return 0;
}



void waitForStartOfGame() {
  while (!gameStarted) {
    updateLCDScreen(1, "Play Piano Tiles", NONE, "");
    updateLCDScreen(2, "Click S1 > Start", NONE, "");
  }

  startGame();
}

void startGame() {
  int* gameSpeed = calloc(1, sizeof(uint8_t));
  
  chooseSpeed(gameSpeed);
  playGame(gameSpeed);
  
  free(gameSpeed);
  // endGame();
}

typedef struct {
  char* rowOne;
  char* rowTwo;
} ROWS;


void playGame(int* gameSpeedChosen) {
  speedMultiple = (*gameSpeedChosen == 1) ? 500 : ((*gameSpeedChosen == 2) ? 375 : ((*gameSpeedChosen == 3) ? 250 : ((*gameSpeedChosen == 4) ? 188 : ((*gameSpeedChosen == 5) ? 125 : 250 ))));
  initTimer(speedMultiple);
  startTimer();

  srand(ACD); // seed the random generator with the speed level chosen (value read by potentiometer) to genuenly generate random tiles in every game

  ROWS* game = malloc( sizeof(ROWS) );
  game->rowOne = malloc( MAX_ROW_LENGTH + 1 );
  (*game).rowTwo = malloc( MAX_ROW_LENGTH + 1 );
  
  while (continueGame) {
    if (generateTileNow) generateTile(game);
  }

  // endGame(game); -> init usart and print things and turn LCD off but use display!
  free(game);
}

void generateTile(ROWS* game) {
  int* randomTileNumber = calloc(1, sizeof(uint8_t));
  *randomTileNumber = rand() % 3 + 1; // generates a random number between 1 and 3 inclusive
    

  free(randomTileNumber);
  generateTileNow = false;
}





void startTimer() {    
    TCCR2B |= _BV(CS22) | _BV(CS21);
}

void initTimer(uint16_t speedMultiple) {    
    // Set Timer/Counter Control Register A (TCCR2A) to CTC mode
    TCCR2A |= _BV( WGM21 );  // Set WGM21 to 1, enabling CTC mode
    
    // Enable the Output Compare Match A interrupt for Timer 2
    TIMSK2 |= (1 << OCIE2A); // Set OCIE2A to 1
    
    OCR2A = speedMultiple-1;

    // Enable global interrupts
    sei();    
}

int seconds = 0;

// This ISR runs every 4 ms
ISR(TIMER2_COMPA_vect) {
    counter++; // to check time
  
    // Generates a new tile at the speed decided previously
    if (((counter + 1) % speedMultiple) == 0) { 
      generateTileNow = true;
      seconds++;



      // sprintf(speedvalue, "%d", seconds);

      // updateLCDScreen(1, "Value of speed:", NONE, "");
      // updateLCDScreen(2, speedvalue, NONE, "");
    }

}



void chooseSpeed(int* gameSpeedPointer) {
  while (!speedChosen) {
    writeSpeedToDisplay();
    showSpeedOnLCD();
    *gameSpeedPointer = currentSpeedValue();
  }
}



/* Returns the current speed value depending on the number read on the ADC, changes by turning the potentiometer */
int currentSpeedValue() {
  if ( ( ADC >= 0 ) && ( ADC < SPEED1 ) ) {
    return 1;
  } else if ( ( ADC >= SPEED1 ) && ( ADC < SPEED2 ) ) {
    return 2;
  } else if ( ( ADC >= SPEED2 ) && ( ADC < SPEED3 ) ) {
    return 3;
  } else if ( ( ADC >= SPEED3 ) && ( ADC < SPEED4 ) ) {
    return 4;
  } else if ( ( ADC >= SPEED4 ) && ( ADC <= SPEED5 ) ) {
    return 5;
  }

  // should never get here, but just in case I return level 1 of speed
  return 1;
}


void writeSpeedToDisplay() {
  writeNumberToSegmentAnir( FIRST_DIGIT, EMPTY_DIGIT ); // Making sure the digits not used are OFF
  writeNumberToSegmentAnir( SECOND_DIGIT, EMPTY_DIGIT ); // Making sure the digits not used are OFF
  writeNumberToSegmentAnir( THIRD_DIGIT, EMPTY_DIGIT ); // Making sure the digits not used are OFF
  writeIntToSegmentAnir( FOURTH_DIGIT, currentSpeedValue() ); // Displaying the current speed level on the 7 segment display
}



void showSpeedOnLCD() {
  char firstRow[16] = "";
  sprintf(firstRow, "Choose Speed: %d", currentSpeedValue()); 

  int numOfSpeedToDisplay = ADC / 64; // value between 0 and 16
  char secondRow[17] = "";

  for (int i = 0; i<numOfSpeedToDisplay; i++) {
    secondRow[i] = '*';
  }
  
  updateLCDScreen(1, firstRow, NONE, "");
  updateLCDScreen(2, secondRow, NONE, "");
}

























// // Libraries included
// // #define __DELAY_BACKWARD_COMPATIBLE__
// #include <util/delay.h>
// // #include <usart.h>
// // #include <stdlib.h>
// // #include <stdio.h>
// // #include <avr/io.h>
// // #include <avr/interrupt.h>
// #include <LCD.h>
// #include <LEDs.h>
// // #include <button.h>
// // #include <buzzer.h>
// // #include <registersLib.h>
// // #include <button.h>
// // #include <display.h>
// // END of libraries included

// // Program definitions

// // END of program deinitions

// int main() {
//   // initUSART();
//   // initLCD;
//   // lcd_write_instruction_4f(lcd_DisplayOff);
  
//   enableAllLeds();    

//   while (1) {
//     updateLCDScreen(1, "Play Piano Tiles", NONE, "");
//     // updateLCDScreen(1, "Heelloo", NONE, "str");
//     // lcd_write_instruction_4f(lcd_DisplayOff);
//     // _delay_ms(1000);
//     // updateLCDScreen(2, "Click S1 to ", NONE, "start");
//     lightUpAllLeds();
//     _delay_ms(1000);
//     lightDownAllLeds();
//     _delay_ms(1000);
//   }
  
//   return 0;
// }