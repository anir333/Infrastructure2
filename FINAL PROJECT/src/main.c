/* START of Libraries included */
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <usart.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <LCD.h> // LCD library
#include <LEDs.h> // LED library
#include <button.h> // Button library
#include <buzzer.h> // Buzzer library
#include <registersLib.h> // Contains functions for Timers and ADC (Potentiometer)
#include <display.h> // Display library
/* END of libraries included */

/* START of Definitions/Macros */

    // making my own booleans to improve code readability
#define true  1
#define false 0

    // Comment the next line if you want to test the game so that the game doesn't end
#define ALLOW_END_GAME true

    // Comment the next line to play the game without the buzzer making sound
#define MAKE_SOUND true

    // Comment this line if you want to see the game information at the end with JavaFX instead of the terminal
#define WITH_JAVAFX true

    // For digits that need to be turned OFF on the 8 segment display
#define EMPTY_DIGIT 0xFF

    // The speed of the game is chosen by the user by turning the potentiometer, there are 5 possible speeds, 1-slow | 5-fast 
#define SPEED1 204.6  // 1 -> Speed of tiles -> 2 seconds
#define SPEED2 409.2  // 2 -> Speed of tiles -> 1.5 seconds
#define SPEED3 613.8  // 3 -> Speed of tiles -> 1 seconds
#define SPEED4 818.4  // 4 -> Speed of tiles -> 0.75 seconds
#define SPEED5 1023   // 5 -> Speed of tiles -> 0.5 seconds

  // Defines the maximum capacity of characters for one row of the LCD screen
#define MAX_ROW_LENGTH 16

// TILES
#define TILE1 '-'
#define TILE2 '`'
#define TILE3 '_'
#define EMPTY_TILE ' '

// FREQUENCIES OF THE NOTES to be used for different melodies (sharp frequencies)
#define C4 261
#define D4 293
#define E4 329
#define F4 349
#define G4 392
#define A4 440
#define B4 493
#define C5 523
#define D5 587
#define E5 659
#define F5 698
#define G5 783
#define A5 880
#define B5 987
#define C6 1046

/* END of Definitions/Macros */


// Structure that will contain a randomly chosen song for each game
typedef struct {
  int* song;
} MELODY;

// Type definition struct that will contain rows with tiles for the LCD display, and the melody to play during the game
typedef struct {
  char* rowOne; // ==> pointer to an array
  char* rowTwo; // ==> pointer to an array
  MELODY melody;// ==> randomly chosen song
} GAME;

// I used the help of ChatGPT to generate these melodies
const int song1[50] = {C5, D5, E5, F5, G5, A5, B5, C6, C5, D5, E5, F5, G5, A5, B5, C6, C5, D5, E5, F5, G5, A5, B5, C6, C5, D5, E5, F5, G5, A5, B5, C6, C5, D5, E5, F5, G5, A5, B5, C6, C5, D5, E5, F5, G5, A5, B5, C6, C5, D5};
const int song2[50] = {C5, E5, G5, C6, B5, A5, G5, F5, E5, D5, C5, G5, E5, C5, G5, A5, B5, C6, D5, E5, F5, E5, D5, C5, B4, A4, G4, F4, E4, D4, C4, E4, G4, A4, G4, F4, E4, D4, C4, B4, C5, E5, G5, C6, B5, A5, G5, F5, E5, D5};
const int song3[50] = {C5, E5, G5, C6, B5, A5, G5, F5, E5, D5, C5, G5, E5, C5, G5, A5, B5, C6, D5, E5, F5, E5, D5, C5, B4, A4, G4, F4, E4, D4, C4, E4, G4, A4, G4, F4, E4, D4, C4, B4, C5, E5, G5, C6, B5, A5, G5, F5, E5, D5};
const int song4[50] = {E5, D5, C5, D5, E5, E5, E5, D5, D5, D5, E5, G5, G5, E5, D5, C5, D5, E5, E5, E5, D5, D5, E5, D5, C5, D5, D5, D5, D5, E5, D5, C5, B4, C5, D5, E5, D5, C5, D5, E5, E5, E5, D5, D5, D5, E5, G5, G5, E5, D5};
const int song5[50] = {G4, A4, B4, C5, D5, E5, F5, G5, F5, E5, D5, C5, B4, A4, G4, F4, E4, D4, C4, B4, A4, G4, F4, E4, D4, C4, B4, A4, G4, F4, E4, D4, C4, B4, A4, G4, F4, E4, D4, C4, B4, A4, G4, F4, E4, D4, C4, B4, C5, D5};


/* Global Variables */
uint8_t gameStarted = false;
uint8_t speedChosen = false;
uint16_t speedMultiple = 250; // default 1 second speed but can change up to 500 or as low as 125
uint16_t secondsMultiple = 250; // used with for the time counter
uint8_t continueGame = true; // becomes 0 (false) when game is lost (score <= 0) or time is up
volatile int numberOfTilesEaten = 0;
volatile int numberOfButtonClick = 0;
volatile uint16_t seconds = 60; // this is the duration of the game in seconds, default 60
volatile uint16_t score = 90; // this is the default starting score = 90
volatile uint8_t note = 0;  // used to now whats the next note to be played
volatile uint8_t buttonClicked = false;
volatile uint8_t lastButtonClicked = 0;
volatile uint8_t followingButtonToClick = 0;
volatile uint8_t generateTileNow = true; // set to false to make game start with a bit of delay (around 1-2 seconds), the purpose of it is to let the program now if it's time to geberate a new tile or not
volatile unsigned long counter = 0;
/* END of global variables */


/* Button Interrputs */
ISR( PCINT1_vect ) {
  if ( buttonPushed( BUTTON_ONE ) ) {
    _delay_ms( 100 ); // to debounce
    if ( gameStarted && speedChosen ) {
      buttonClicked = true; // this makes the game call a function that checks if the button clicked was correct or not and handles the button click...
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
    _delay_ms( 100 ); // to debounce
    if ( gameStarted && speedChosen ) {
      buttonClicked = true;
      lastButtonClicked = BUTTON_TWO;
    }
  }
  if ( buttonPushed( BUTTON_THREE ) ) {
    _delay_ms( 100 ); // to debounce
    if ( gameStarted && speedChosen ) {
      buttonClicked = true;
      lastButtonClicked = BUTTON_THREE;
    }
  }
}


// This ISR runs every 4 ms
ISR( TIMER2_COMPA_vect ) { // I use the comparing ISR
    counter++; // to check time
  
    if ( ( (counter + 1) % secondsMultiple ) == 0 ) seconds--; // keeps track of seconds passed

    // if you don't want the game to ever end comment the ALLOW_END_GAME macro 
    #if !defined(ALLOW_END_GAME) 
      if ( seconds < 1 ) seconds = 99; 
      if ( score < 1 ) score = 90;    
    #endif

    // Generates a new tile at the speed decided previously
    if ( ( (counter + 1) % speedMultiple ) == 0 ) { 
      generateTileNow = true;
      lightDownAllLeds(); // when you click a button it lights them uo, so they need to be lit down once every tile is generated
    }
}


// main function
int main() {
    /* Initialisation of elements used during the game */
    initLCD(); // Initialize the LCD
    initDisplay(); // Initialize the 4-digit 8 segment display
    turnDisplayOFF(); // Turn 8 segment display off until its used 
    initADC(); // Initialize ADC to read input (potentiometer)
    enableAllLeds(); // enable all LEDs for ouput
    enableAllButtons(); // enable all buttons for input
    enableAllButtonInterrupts(); // enable the interrupts for all the buttons
    // Initialisation to the serial monitor is done at the end of the game since it messes up with the LCD display during the game

    // now this functions will wait for the game to start
    waitForStartOfGame();
    
    return 0;
}


// this function waits for the Button S1 to be clicked in order to set the gameStarted to true and displays the start game text on the LCD and the PLAY string on the 8 segment display
void waitForStartOfGame() {
  lightUpOneLed(4);
  pauseSeconds(1);

  //LCD display/screen
  updateLCDScreen(1, "Play Piano Tiles", NONE, "");
  updateLCDScreen(2, "Click S1 > Start", NONE, "");
  
  while (!gameStarted) {
    // 8 segment display 
    writeStringAndWait( "PLAY", 1 );
  }

  lightDownOneLed(4);

  startGame();
}


// this function first calls the choose speed function which allows the user to turn the potentiometer to choose the speed for the games at which the tiles are generated, then once the speed is chosen, it starts the game by calling the play game function, finally, when the game ends it calls the endGame function
void startGame() {
  int* gameSpeed = calloc(1, sizeof(uint8_t));

  if (!gameSpeed || gameSpeed == NULL) {
    endGameByMemoryAllocationFail();
    return;
  }
  
  chooseSpeed(gameSpeed);
  playGame(gameSpeed);
  
  free(gameSpeed);

  endGame(&score);
}


/// @brief Allows the user to turn the potentiomter in order to choose a level of speed for the game and displays it on the LCD and on the 8 segment display
/// @param gameSpeedPointer a pointer to the game speed chosen
void chooseSpeed( int* gameSpeedPointer ) {
  while ( !speedChosen ) {
    writeSpeedToDisplay();
    showSpeedOnLCD();
    *gameSpeedPointer = currentSpeedValue();
  }
}

// the most important function of the whole game:
//  ==> It plays the whole game. Once the speed has been chosen by the player, and the button S1 is clicked, the game starts:
void playGame(int* gameSpeedChosen) {
  // first I set the speedMultiple which is used by the timer to generate tiles at the speed chosen
  speedMultiple =  (*gameSpeedChosen == 1) ? 500 : 
                  ((*gameSpeedChosen == 2) ? 400 : 
                  ((*gameSpeedChosen == 3) ? 250 : 
                  ((*gameSpeedChosen == 4) ? 188 : 
                  ((*gameSpeedChosen == 5) ? 125 : 250 ))));
  
  // initialise the Timer
  initTimer(speedMultiple);

  // start the timer
  startTimer();

  // seed the random generator with the ADC value chosen (value read by potentiometer) to generate random tiles in every game
  srand(ADC);

  // I allocate memory for the random song to be chosen and for the gameSong Melody
  uint8_t* songChosen = calloc(1, sizeof(uint8_t));
  MELODY* gameSong = malloc( sizeof( MELODY ) );

  if ((!songChosen || songChosen == NULL) || (!gameSong || gameSong == NULL)) {
    endGameByMemoryAllocationFail();
    return;
  }

  // chooses a song from 1 to 5
  *songChosen = rand() % 5 + 1;

  // sets the song to the MELODY corresponding to the random value generated
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

  // I set the secondsMultiple which is used by the timer to decrease the seconds during the game, since each speed of the game alters the speed of the seconds, I have to set a different value for each speed
  secondsMultiple = speedMultiple == 250 ? speedMultiple : (speedMultiple == 125 ? 500 : (speedMultiple == 188 ? 350 : (speedMultiple == 400 ? 415 : 250))); 

  // allocate memory for the game
  GAME* game = malloc(sizeof(GAME));
  game->rowOne = malloc(MAX_ROW_LENGTH + 1);
  game->rowTwo = malloc(MAX_ROW_LENGTH + 1);
  game->melody = *gameSong;

  if ((!game || game == NULL) || (!game->rowOne || game->rowOne == NULL) || (!game->rowTwo || game->rowTwo == NULL)) {
    endGameByMemoryAllocationFail();
    return;
  }

  // With the memset() function I initialise all values of the rows of the GAME to EMPTY_TILE == ' ' in order to NOT have garbage data in those values, and then I make sure the array is finished with a \0 byte since with dynamic allocation this is not done automatically
  memset(game->rowOne, EMPTY_TILE, MAX_ROW_LENGTH);
  memset(game->rowTwo, EMPTY_TILE, MAX_ROW_LENGTH);
  game->rowOne[MAX_ROW_LENGTH] = '\0';
  game->rowTwo[MAX_ROW_LENGTH] = '\0';

  // since the songChosen was only needed to set the gameSong, and the gameSong pointer has been copied tot he GAME, we can free those memory allocations now
  free(songChosen);
  free(gameSong);

  // This is the loop that runs the game
  while ( continueGame ) {

    // each time at the speed chosen previously, the timer will set generateTileNow to true which will make the generateTile function be called 
    if ( generateTileNow ) {
      generateTile( game );
    }

    // this function sets the next button that has to be clicked depending on the lowest tile visible on the LCD
    checkNextTile( game );

    // every time a button is clicked it sets the buttonClicked to true
    if ( buttonClicked ) {
      numberOfButtonClick++;
      
      // if the button clicked corresponds to the correct button that needed to be clicked at that instance depending on the lowest tile displayed on the LCD, then it lights up all the LEDs for the duration of a tile being generated, it removes the tile correctly clicked, and makes the following sound of the melody for the game
      if ( lastButtonClicked == followingButtonToClick ) {
        lightUpAllLeds();
        removeTile( game );
        numberOfTilesEaten++;

        #ifdef MAKE_SOUND
          playSound( game );
        #endif
      } else { // if the button clicked isn't the one that corresponds to the lowest tile, the score decreases by 10 points and an error sound is played
        score -= 10;

        #ifdef MAKE_SOUND
          playErrorSound();
        #endif
      }

      buttonClicked = false;
    }
 
    // shows the time left for the game on the first two digits of the 8 segment display, and separated by a dot it shows the current score at that moment in time for the game
    displaySecondsLeftAndScore();
    
    // checks if the score <= 0  or if the time left = 0 in order to end the game if ALLOW_END_GAME is not commented, and if the game has ended then it sets the continueGame variable to false so that the while loop that runs the game ends
    #ifdef ALLOW_END_GAME
      checkGameEnd();
    #endif
  }

  // we stop the timer
  stopTimer();

  // Once the game loop finishes, it means that the game has ended, we cna now free the memory used for the game
  free(game->rowOne);
  free(game->rowTwo);
  free(game);

  // after this function has finished its job of playing the game, the function that handles the ended game will be called

} // play game function end

// to initialise timer 2
void initTimer( uint16_t speedMultiple ) {    
    // Set Timer/Counter Control Register A (TCCR2A) to CTC mode
    TCCR2A |= _BV( WGM21 );  // Set WGM21 to 1, enabling CTC mode
    
    // Enable the Output Compare Match A interrupt for Timer 2
    TIMSK2 |= _BV( OCIE2A ); // Set OCIE2A to 1
    
    OCR2A = speedMultiple - 1;

    // Enable global interrupts
    sei();    
}

// starting the timer 2 by setting the prescaler to 256
void startTimer() {    
    TCCR2B |= _BV( CS22 ) | _BV( CS21 );
}

// stopping the timer by setting the prescaler to 0
void stopTimer() {
    TCCR2B &= ~(_BV(CS22) | _BV(CS21) | _BV(CS20));
}

// This function shows the speed in the fourth digit of the 8 segment display
void writeSpeedToDisplay() {
  writeNumberToSegmentAnir( FIRST_DIGIT, EMPTY_DIGIT ); // Making sure the digits not used are OFF
  writeNumberToSegmentAnir( SECOND_DIGIT, EMPTY_DIGIT ); // Making sure the digits not used are OFF
  writeNumberToSegmentAnir( THIRD_DIGIT, EMPTY_DIGIT ); // Making sure the digits not used are OFF
  writeIntToSegmentAnir( FOURTH_DIGIT, currentSpeedValue() ); // Displaying the current speed level on the fourth digit of the 8 segment display
}

// Returns the current speed value depending on the number read on the ADC, changes by turning the potentiometer (speeds from 1 to 5)
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

  // should never get here, but just in case I return level 1 of speed to avoid any errors
  return 1;
}

// Shows the speed as the potentiometer turns on the LCD display and a 'progress bar' the moves as the speed is changed (turning the potentiometer)
void showSpeedOnLCD() {
  char firstRow[16] = "";
  sprintf( firstRow, "Choose Speed: %d", currentSpeedValue() ); 

  int numOfSpeedToDisplay = ADC / 64; // value between 0 and 16
  char secondRow[17] = "";

  for ( int i = 0 ; i<numOfSpeedToDisplay ; i++ ) {
    secondRow[i] = TILE1;
  }
  
  updateLCDScreen( 1, firstRow,  NONE, "" );
  updateLCDScreen( 2, secondRow, NONE, "" );
}

// checks if the core <= 0 or if the time for the game is up
void checkGameEnd() {
  if ( ( score <= 0 ) || ( seconds < 1 ) ) {
    continueGame = false;
  }
}

// plays the next sound of the melody and loops the melody as necessary so that it doesn't run out of notes
void playSound( GAME* game ) {
  note++;
  if (note > 49) note = 0;

  enableBuzzerOnPORTC();
  playToneForBuzzerOnPORTC( game->melody.song[note], 150 );
}

// if wrong button clicked an error sound is played
void playErrorSound() {
  enableBuzzerOnPORTC();
  playToneForBuzzerOnPORTC( 200, 50 );
  _delay_ms(50);
  playToneForBuzzerOnPORTC( 200, 50 );  
  _delay_ms(50);
  playToneForBuzzerOnPORTC( 200, 50 );  
}

// used to show the seconds and the score on the 8 segment display during the game
void displaySecondsLeftAndScore() {
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

/// @brief used to remove a tile when the button clicked is correct
/// @param game a pointer to the game that contains the rows and the melody
void removeTile( GAME* game ) {
  for ( int i = 16 ; i>=0 ; i-- ) {
    if ( (game->rowOne[i] == TILE1) || (game->rowTwo[i] == TILE2) || (game->rowTwo[i] == TILE3) ) {
      game->rowOne[i] = EMPTY_TILE;
      game->rowTwo[i] = EMPTY_TILE;
      return;
      break;
    }
  }
}

/// @brief sets the next button to be clicked depending on the lowest tile in displayed in the LCD
/// @param game a pointer to the game that contains the rows and the melody
void checkNextTile( GAME* game ) {
  for ( int i = 0 ; i<16 ; i++ ) {
    if ( (game->rowOne[i] == EMPTY_TILE) && (game->rowTwo[i] == TILE3) ) {
      followingButtonToClick = 1;
    } else if ( (game->rowOne[i] == EMPTY_TILE) && (game->rowTwo[i] == TILE2) ) {
      followingButtonToClick = 2;
    } else if ( (game->rowOne[i] == TILE1) && (game->rowTwo[i] == EMPTY_TILE) ) {
      followingButtonToClick = 3;
    }
  }
}

/// @brief generates a new tile at randomly, (function called at the speed chosen before)
/// @param game a pointer to the game that contains the rows and the melody
void generateTile( GAME* game ) {
  int* randomTileNumber = calloc( 1, sizeof(uint8_t) );
  
  if ((!randomTileNumber || randomTileNumber == NULL)) {
    endGameByMemoryAllocationFail();
    return;
  }

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

/// @brief moves/shifts the tiles forwards (towards the bottom of the LCD display)
/// @param tile the number of the tile to add which is randomly chosen 
/// @param game a pointer to the game that contains the rows and the melody
void shiftAndAddTiles( int tile, GAME* game ) {
  // if the tile has reached the bottom of the LCD and the player hasn't had time to click on it, then 5 points are reduced from the score
  if ( ((game->rowOne[15] == TILE1) && (game->rowTwo[15] == EMPTY_TILE)) || 
       ((game->rowOne[15] == EMPTY_TILE) && (game->rowTwo[15] == TILE2)) ||
       ((game->rowOne[15] == EMPTY_TILE) && (game->rowTwo[15] == TILE3)) ) {
    score -= 5;
  }

  /* First I create a copy of the current state of the tiles in the game */
  char* rowOneCopy = malloc( MAX_ROW_LENGTH + 1 );
  char* rowTwoCopy = malloc( MAX_ROW_LENGTH + 1 );

  if ((!rowOneCopy || rowOneCopy == NULL) || (!rowTwoCopy || rowTwoCopy == NULL)) {
    endGameByMemoryAllocationFail();
    return;
  }

  rowOneCopy[MAX_ROW_LENGTH] = '\0';
  rowTwoCopy[MAX_ROW_LENGTH] = '\0';

  /* I copy the current tiles to the copy arrays so I can modify the original array of tiles without loosing the current state */
  for ( int i = 0 ; i<16 ; i++ ) {
    rowOneCopy[i] = *(game->rowOne + i);
    rowTwoCopy[i] = *(game->rowTwo + i);
  }

  /* Now I modify the original array of tiles in the game to add the new generated tile at the very beginning (position 0) of the array */
    if ( tile == 1 ) {
      game->rowOne[0] = TILE1;
      game->rowTwo[0] = EMPTY_TILE;
    } else if ( tile == 2 ) {
      game->rowOne[0] = EMPTY_TILE;
      game->rowTwo[0] = TILE2;
    } else {
      game->rowOne[0] = EMPTY_TILE;
      game->rowTwo[0] = TILE3;
    }

  /* Now shift the values, this means to copy the previous values of the copy array back into the original array but one position forward */
  for ( int i = 1 ; i<16 ; i++ ) {
    game->rowOne[i] = rowOneCopy[i-1];
    game->rowTwo[i] = rowTwoCopy[i-1];
  }

  /* Freeing the space of the copies I made */
  free( rowOneCopy );
  free( rowTwoCopy );
}



/// @brief function called once the game ends 
/// @param score ==> the memory address of score to check the value score to see if player won or lost
void endGame(int* score) {
  if ( *score <= 0 ) { // show LOST info on the LCD
    updateLCDScreen(1, "YOU LOST!", NONE, ":(");
    updateLCDScreen(2, "Don't give up!", NONE, "");
  } else { // show WON info on the LCD
    char scoreS[10] = "";
    sprintf(scoreS, "Score: %d ", *score); // to make the score int a char[] to show it on the LCD
    updateLCDScreen(1, "YOU WON!", NONE, ";)");
    updateLCDScreen(2, scoreS, NONE, "");
  }

  // We now initalise the serial monitor to show the information about the game once it has ended
  initUSART();

  #if !defined(WITH_JAVAFX)
    printf("\n\n\n\n");
    printf("\n**********************************************************");
    printf("\n*************** PIANO TILES GAME ENDED *******************\n");
    if ( *score <= 0 ) {
      printf("\n*********************** YOU LOST! ************************\n");
    } else {
      printf("\n*********************** YOU WON! *************************\n");
    }

    printf("\n********************** YOUR SCORE: %d ********************\n", *score);
    printf("\n************** Number of times clicked: %d ***************\n", numberOfButtonClick);
    printf("\n************* Total number of tiles eaten: %d ************\n\n", numberOfTilesEaten);
    printf("*********************************************************\n\n\n\n");
  #endif
  
  #ifdef WITH_JAVAFX
    printf("SEPARATOR%dSEPARATOR%dSEPARATOR%dSEPARATOR%dSEPARATOR***...", *score <= 0 ? 0 : 1, *score, numberOfButtonClick, numberOfTilesEaten );
  #endif

  // used to display a value in the 8 segment display (0 if you lost, 1 if you won)
  writeNumberToSegmentAnir( FOURTH_DIGIT, *score <= 0 ? 0b11000000 : 0b11111001 );

  // Finally show a SMILEY face on the 8 segment display if the player WON and a SAD face if the player LOST
   while (1) {
        // Light up each LED one by one
        for (int i = 1; i <= 4; i++) {
            lightUpOneLed(i);
            _delay_ms(100);
        }

        // Light down each LED one by one
        for (int i = 1; i <= 4; i++) {
            lightDownOneLed(i);
            _delay_ms(100);
        }

    }
}

// stops the game because of an error when allocating memory
void endGameByMemoryAllocationFail() {
    initUSART();
    printf("\n\n MEMORY ALLOCATION FAILED ;(\n\n");

    while (1);    
}