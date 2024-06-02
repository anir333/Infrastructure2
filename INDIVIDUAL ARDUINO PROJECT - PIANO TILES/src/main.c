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

  // Comment the next line if you want to test the game so that the game doesn't end
#define ALLOW_END_GAME true

  // Comment the next line to play the game without the buzzer making sound
#define MAKE_SOUND true

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


// FREQUENCIES OF THE NOTES
#define C4 261.63
#define D4 293.66
#define E4 329.63
#define F4 349.23
#define G4 392.00
#define A4 440.00
#define B4 493.88
#define C5 523.250
#define D5 587.330
#define E5 659.250
#define F5 698.460
#define G5 783.990
#define A5 880.00
#define B5 987.770
#define C6 1046.500

/* END of Definitions */



typedef struct {
  int* song;
} MELODY;

// type definition that contains tiles rows for the LCD display, and the melody to play
typedef struct {
  char* rowOne;
  char* rowTwo;
  MELODY melody;
} ROWS;

// I used the help of ChatGPT to generate these melodies
  // I had to make them integers to simplify the program...
const int song1[50] = {C5, D5, E5, F5, G5, A5, B5, C6, C5, D5, E5, F5, G5, A5, B5, C6, C5, D5, E5, F5, G5, A5, B5, C6, C5, D5, E5, F5, G5, A5, B5, C6, C5, D5, E5, F5, G5, A5, B5, C6, C5, D5, E5, F5, G5, A5, B5, C6, C5, D5};
const int song2[50] = {C5, E5, G5, C6, B5, A5, G5, F5, E5, D5, C5, G5, E5, C5, G5, A5, B5, C6, D5, E5, F5, E5, D5, C5, B4, A4, G4, F4, E4, D4, C4, E4, G4, A4, G4, F4, E4, D4, C4, B4, C5, E5, G5, C6, B5, A5, G5, F5, E5, D5};
const int song3[50] = {C5, E5, G5, C6, B5, A5, G5, F5, E5, D5, C5, G5, E5, C5, G5, A5, B5, C6, D5, E5, F5, E5, D5, C5, B4, A4, G4, F4, E4, D4, C4, E4, G4, A4, G4, F4, E4, D4, C4, B4, C5, E5, G5, C6, B5, A5, G5, F5, E5, D5};
const int song4[50] = {E5, D5, C5, D5, E5, E5, E5, D5, D5, D5, E5, G5, G5, E5, D5, C5, D5, E5, E5, E5, D5, D5, E5, D5, C5, D5, D5, D5, D5, E5, D5, C5, B4, C5, D5, E5, D5, C5, D5, E5, E5, E5, D5, D5, D5, E5, G5, G5, E5, D5};
const int song5[50] = {G4, A4, B4, C5, D5, E5, F5, G5, F5, E5, D5, C5, B4, A4, G4, F4, E4, D4, C4, B4, A4, G4, F4, E4, D4, C4, B4, A4, G4, F4, E4, D4, C4, B4, A4, G4, F4, E4, D4, C4, B4, A4, G4, F4, E4, D4, C4, B4, C5, D5};

/* 

REMEMBER TO CHECK FOR ALL MEMROY ALLOCATIONS IF !MEM OR  MEM == NULL

AND ALSO REMEMBER TO FREE ALL ALLOCATIONS

 */

/* Global Variables */
uint8_t gameStarted = false;
uint8_t speedChosen = false;
uint16_t speedMultiple = 250; // default 1 second speed but can change up to 500 or as low as 125
uint16_t secondsMultiple = 250;
uint8_t continueGame = true;
volatile uint16_t seconds = 60;
volatile uint16_t score = 90;
volatile uint8_t note = 0;
volatile uint8_t buttonClicked = false;
volatile uint8_t lastButtonClicked = 0;
volatile uint8_t followingButtonToClick = 0;
volatile uint8_t generateTileNow = true; // set to false to make game start with a bit of delay (around 1-2 seconds)
volatile unsigned long counter = 0;
/* END of global variables */


/* Button Interrputs */
ISR( PCINT1_vect ) {
  if ( buttonPushed( BUTTON_ONE ) ) {
    _delay_ms( 100 ); // to debounce
    if ( gameStarted && speedChosen ) {
      buttonClicked = true;
      lastButtonClicked = BUTTON_ONE;
    }
    if ( gameStarted && !speedChosen ) {
      speedChosen = true;
    }
    if ( !gameStarted ) {
      gameStarted = true;
    }
  }
  if ( buttonPushed( BUTTON_TWO ) ) {
    _delay_ms( 100 );
    if ( gameStarted && speedChosen ) {
      buttonClicked = true;
      lastButtonClicked = BUTTON_TWO;
    }
  }
  if ( buttonPushed( BUTTON_THREE ) ) {
    _delay_ms( 100 );
    if ( gameStarted && speedChosen ) {
      buttonClicked = true;
      lastButtonClicked = BUTTON_THREE;
    }
  }
}


// This ISR runs every 4 ms
ISR( TIMER2_COMPA_vect ) {
    counter++; // to check time
  
    if ( ( (counter + 1) % secondsMultiple ) == 0 ) seconds--;

    #if !defined(ALLOW_END_GAME)
      if ( seconds < 1 ) seconds = 99; 
      if ( score < 1 ) score = 90;    
    #endif

    // Generates a new tile at the speed decided previously
    if ( ( (counter + 1) % speedMultiple ) == 0 ) { 
      generateTileNow = true;
      lightDownAllLeds();
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
    // Initialisation to the serial monitor is done at the end of the game since it messes up with the LCD display during the game

    waitForStartOfGame();
    
    return 0;
}



void waitForStartOfGame() {
  lightUpOneLed(4);
  pauseSeconds(1);
  while (!gameStarted) {
    //LCD display/screen
    updateLCDScreen(1, "Play Piano Tiles", NONE, "");
    updateLCDScreen(2, "Click S1 > Start", NONE, "");

    // 7 segment display
    writeString("PLAY"); // displayed on the 7 segment display
    turnDisplayOFF(); // it turns it off for a tiny bit of a milisecond to give a better visual
  }
  lightDownOneLed(4);

  startGame();
}



void startGame() {
  int* gameSpeed = calloc(1, sizeof(uint8_t));
  
  chooseSpeed(gameSpeed);
  playGame(gameSpeed);
  
  free(gameSpeed);

  endGame(&score);
}


void endGame(int* score) {
  if ( *score <= 0 ) {
    updateLCDScreen(1, "YOU LOST!", NONE, ":(");
    updateLCDScreen(2, "Don't give up!", NONE, "");
  } else {
    char scoreS[10] = "";
    sprintf(scoreS, "Score: %d ", *score);
    updateLCDScreen(1, "YOU WON!", NONE, ";)");
    updateLCDScreen(2, scoreS, NONE, "");
  }




  initUSART();

  printf("\n\n\n\n");
  printf("\n**********************************************************");
  printf("\n*************** PIANO TILES GAME ENDED *******************\n");
  if ( *score <= 0 ) {
    printf("\n*********************** YOU LOST! ************************\n");
  } else {
    printf("\n*********************** YOU WON! *************************\n");
  }

  printf("\n********************** YOUR SCORE: %d ********************\n\n", *score);
  printf("**********************************************************\n\n\n\n");

  while (1) {
    if ( *score <= 0 ) {
      writeNumberToSegmentAnir( FIRST_DIGIT, 0xFF );
      writeNumberToSegmentAnir( SECOND_DIGIT, 0xFF );
      writeNumberToSegmentAnir( THIRD_DIGIT, 0b11110000 );
      writeNumberToSegmentAnir( FOURTH_DIGIT, 0b10000000 );
    } else {
      writeNumberToSegmentAnir( FIRST_DIGIT, 0xFF );
      writeNumberToSegmentAnir( SECOND_DIGIT, 0xFF );
      writeNumberToSegmentAnir( THIRD_DIGIT, 0b11000110 );
      writeNumberToSegmentAnir( FOURTH_DIGIT, 0b10000000 );
    }
  }
}


void playGame(int* gameSpeedChosen) {
  speedMultiple =  (*gameSpeedChosen == 1) ? 500 : 
                  ((*gameSpeedChosen == 2) ? 400 : 
                  ((*gameSpeedChosen == 3) ? 250 : 
                  ((*gameSpeedChosen == 4) ? 188 : 
                  ((*gameSpeedChosen == 5) ? 125 : 250 ))));
  initTimer(speedMultiple);
  startTimer();

  srand(ADC); // seed the random generator with the speed level chosen (value read by potentiometer) to genuenly generate random tiles in every game

  uint8_t* songChosen = calloc(1, sizeof(uint8_t));
  MELODY* gameSong = malloc( sizeof( MELODY ) );
  // CHEKC FOR MEMORY ALLOCATION DONE CORRECLTY OR NOT
  *songChosen = rand() % 5 + 1; // chooses a song from 1 to 5

  if (*songChosen == 1) {
    gameSong->song = song1;
  } else if (*songChosen == 2) {
    gameSong->song = song2;
  } else if (*songChosen == 3) {
    gameSong->song = song3;
  } else if (*songChosen == 4) {
    gameSong->song = song4;
  } else {
    gameSong->song = song5;
  }


  secondsMultiple = speedMultiple == 250 ? speedMultiple : (speedMultiple == 125 ? 500 : (speedMultiple == 188 ? 350 : (speedMultiple == 400 ? 415 : 250))); 


  ROWS* game = malloc(sizeof(ROWS));
  game->rowOne = malloc(MAX_ROW_LENGTH + 1);
  game->rowTwo = malloc(MAX_ROW_LENGTH + 1);
  game->melody = *gameSong;

  // With some online research I learned how to initialise all the values of an array of a pointer where memory has been dynamically allocated, with the memset() function I initialise all values of game rows to ' ' in order to NOT have garbage data in those values, and then I make sure the array is finished with a \0 byte since with dynamic allocation this is not done automatically
  memset(game->rowOne, ' ', MAX_ROW_LENGTH);
  memset(game->rowTwo, ' ', MAX_ROW_LENGTH);
  game->rowOne[MAX_ROW_LENGTH] = '\0';
  game->rowTwo[MAX_ROW_LENGTH] = '\0';

  free(songChosen);
  free(gameSong);

  while ( continueGame ) {

    if ( generateTileNow ) {
      generateTile( game );
    }

    checkNextTile( game );

    if ( buttonClicked ) {
      if ( lastButtonClicked == followingButtonToClick ) {
        lightUpAllLeds();
        removeTile( game );

        #ifdef MAKE_SOUND
          playSound( game );
        #endif
      } else {
        score -= 10;

        #ifdef MAKE_SOUND
          playErrorSound();
        #endif
      }

      buttonClicked = false;
    }

    displaySecondsLeft();
    
    #ifdef ALLOW_END_GAME
      checkGameEnd();
    #endif
  }
  
  // // endGame(game); -> init usart and print things and turn LCD off but use display!
  free(game->rowOne);
  free(game->rowTwo);
  free(game);
} // play game function

void checkGameEnd() {
  if ( ( score <= 0 ) || ( seconds < 1 ) ) {
    continueGame = false;
  }
}

void playSound( ROWS* game ) {
  note++;
  if (note > 49) note = 0;

  enableBuzzerOnPORTC();
  playToneForBuzzerOnPORTC( game->melody.song[note], 150 );
}

void playErrorSound() {
  enableBuzzerOnPORTC();
  playToneForBuzzerOnPORTC( 200, 50 ); // 1080 | 150
  _delay_ms(50);
  playToneForBuzzerOnPORTC( 200, 50 );  
}

void displaySecondsLeft() {
  if (seconds >= 1) { 
    writeIntToSegmentAnir( FIRST_DIGIT , seconds / 10 );
    writeIntToSegmentWithDotAnir( SECOND_DIGIT , seconds % 10 );
  } else {
    writeNumberToSegmentAnir( FIRST_DIGIT, EMPTY_DIGIT );
    writeNumberToSegmentAnir( SECOND_DIGIT, EMPTY_DIGIT );
  }
  writeIntToSegmentAnir( THIRD_DIGIT  , score / 10 );
  writeIntToSegmentAnir( FOURTH_DIGIT , score % 10 );
}


void removeTile( ROWS* game ) {
  for ( int i = 16 ; i>=0 ; i-- ) {
    if ( (game->rowOne[i] == '-') || (game->rowTwo[i] == '`') || (game->rowTwo[i] == '_') ) {
      game->rowOne[i] = ' ';
      game->rowTwo[i] = ' ';
      return;
      break;
    }
  }
}

void checkNextTile( ROWS* game ) {
  for ( int i = 0 ; i<16 ; i++ ) {
    if ( (game->rowOne[i] == ' ') && (game->rowTwo[i] == '_') ) {
      followingButtonToClick = 1;
    } else if ( (game->rowOne[i] == ' ') && (game->rowTwo[i] == '`') ) {
      followingButtonToClick = 2;
    } else if ( (game->rowOne[i] == '-') && (game->rowTwo[i] == ' ') ) {
      followingButtonToClick = 3;
    }
  }
}

void generateTile( ROWS* game ) {
  int* randomTileNumber = calloc( 1, sizeof(uint8_t) );
  *randomTileNumber = rand() % 3 + 1; // generates a random number between 1 and 3 inclusive

    if ( *randomTileNumber == 1 ) {
      shiftAndAddTiles( 1, game );
    } else if ( *randomTileNumber == 2 ) {
      shiftAndAddTiles( 2, game );
    } else {
      shiftAndAddTiles( 3, game );
    }

  updateLCDScreen( 1, game->rowOne, NONE, "" );
  updateLCDScreen( 2, game->rowTwo, NONE, "" );
    

  free( randomTileNumber );
  generateTileNow = false;
}

void shiftAndAddTiles( int tile, ROWS* game ) {
  if ( ((game->rowOne[15] == '-') && (game->rowTwo[15] == ' ')) || 
       ((game->rowOne[15] == ' ') && (game->rowTwo[15] == '`')) ||
       ((game->rowOne[15] == ' ') && (game->rowTwo[15] == '_')) ) {
    score -= 5;
  }

  /* First I create a copy of the current state of the tiles in the game */
  char* rowOneCopy = malloc( MAX_ROW_LENGTH + 1 );
  char* rowTwoCopy = malloc( MAX_ROW_LENGTH + 1 );
  rowOneCopy[MAX_ROW_LENGTH] = '\0';
  rowTwoCopy[MAX_ROW_LENGTH] = '\0';

  /* I copy the current tiles to the copy arrays so I can modify the original array of tiles without loosing the current state */
  for ( int i = 0 ; i<16 ; i++ ) {
    rowOneCopy[i] = *(game->rowOne + i);
    rowTwoCopy[i] = *(game->rowTwo + i);
  }

  /* Now I modify the original array of tiles in the game to add the new generated tile at the very beginning (position 0) of the array */
  // if (seconds <= 17) {
  //   game->rowOne[0] = ' ';
  //   game->rowTwo[0] = ' ';
  // } else {
    if ( tile == 1 ) {
      game->rowOne[0] = '-';
      game->rowTwo[0] = ' ';
    } else if ( tile == 2 ) {
      game->rowOne[0] = ' ';
      game->rowTwo[0] = '`';
    } else {
      game->rowOne[0] = ' ';
      game->rowTwo[0] = '_';
    }
  // }

  /* Now shift the values, this means to copy the previous values of the original array back into the original array but one position forward */
  for ( int i = 1 ; i<16 ; i++ ) {
    game->rowOne[i] = rowOneCopy[i-1];
    game->rowTwo[i] = rowTwoCopy[i-1];
  }

  /* Freeing the space of the copies I made */
  free( rowOneCopy );
  free( rowTwoCopy );
}


void startTimer() {    
    TCCR2B |= _BV( CS22 ) | _BV( CS21 );
}

void stopTimer() {
    TCCR2B &= ~(_BV(CS22) | _BV(CS21) | _BV(CS20));
}

void initTimer( uint16_t speedMultiple ) {    
    // Set Timer/Counter Control Register A (TCCR2A) to CTC mode
    TCCR2A |= _BV( WGM21 );  // Set WGM21 to 1, enabling CTC mode
    
    // Enable the Output Compare Match A interrupt for Timer 2
    TIMSK2 |= _BV( OCIE2A ); // Set OCIE2A to 1
    
    OCR2A = speedMultiple - 1;

    // Enable global interrupts
    sei();    
}




void chooseSpeed( int* gameSpeedPointer ) {
  while ( !speedChosen ) {
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
  sprintf( firstRow, "Choose Speed: %d", currentSpeedValue() ); 

  int numOfSpeedToDisplay = ADC / 64; // value between 0 and 16
  char secondRow[17] = "";

  for ( int i = 0 ; i<numOfSpeedToDisplay ; i++ ) {
    secondRow[i] = '-';
  }
  
  updateLCDScreen( 1, firstRow,  NONE, "" );
  updateLCDScreen( 2, secondRow, NONE, "" );
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