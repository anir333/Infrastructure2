#include <registersLib.h>
#include <avr/io.h>
#include <stdlib.h>
#include <LEDs.h>
#include <usart.h>
#include <display.h>
#include <button.h>
#include <stdbool.h>

#define START_NUMBER     21
#define MAX_NUMBER       3
#define HUMAN_PLAYER    'P'
#define COMPUTER_PLAYER 'C'

typedef struct {
  char character;
  int* matchesRemoved;
} PLAYER;


bool gameStarted = false; 
int currentMatches = START_NUMBER;
int matchesToRemove = MAX_NUMBER;
char currentPlayer;
uint16_t randSeed = 0;
int computerButtonTwoTimesPressed = 0;
bool gameAction = false;

ISR ( PCINT1_vect ) {
  if ( buttonPushed(1) ) {
    
    if (gameStarted && (currentPlayer == HUMAN_PLAYER) && (matchesToRemove > 1)) matchesToRemove -=1;

    if (!gameStarted) gameStarted = true;
    
  }
  if ( buttonPushed(2) ) {
    if (gameStarted) {
      gameAction = true;
    }
  }
  if ( buttonPushed(3) ) {
    if (gameStarted && (currentPlayer == HUMAN_PLAYER) && (matchesToRemove < 3)) matchesToRemove +=1;
  }
  
}

int main() {
  initUSART();
  initDisplay();
  initADC();
  turnDisplayOFF();
  enableAllButtons();
  enableAllButtonInterrupts();

  const PLAYER human = { HUMAN_PLAYER, calloc(1, sizeof(int)) };
  const PLAYER computer = { COMPUTER_PLAYER, calloc(1, sizeof(int)) };

  waitForStart(human.matchesRemoved, computer.matchesRemoved);

  return 0;
}

void waitForStart(int *humanMatchesRemoved, int *computerMatchesRemoved) {
    while (!gameStarted) {
      randSeed = ADC * 9.775;

      writeNumberAndWait( randSeed, 100 );
    }
    turnDisplayOFF();
    startGame(humanMatchesRemoved, computerMatchesRemoved);
}

void startGame(int* humanMatchesRemoved, int* computerMatchesRemoved) {
  srand(randSeed);

  int startingPlayerChosen = rand() % 2; // generates a random number 0-1 which I use to randomly select a player to start a game
  if (startingPlayerChosen == 0) {
    currentPlayer = COMPUTER_PLAYER;
  } else {
    currentPlayer = HUMAN_PLAYER;
  }

  do {
    displayValues();

    if (gameAction) {
      handleGameAction(humanMatchesRemoved, computerMatchesRemoved);
    }

  } while (gameNotEnded());

  printf("\nWinner is: %s!!!\n", currentPlayer == HUMAN_PLAYER ? "HUMAN" : "COMPUTER");
  printf("\nHuman removed %d matches.", *humanMatchesRemoved);
  printf("\nComputer removed %d matches.", *computerMatchesRemoved);

  free(humanMatchesRemoved);
  free(computerMatchesRemoved);

  displayWinner();
}

void handleGameAction(int *humanMatchesRemoved, int *computerMatchesRemoved) {
  if (currentPlayer == COMPUTER_PLAYER) {
    computerButtonTwoTimesPressed++;

    if (computerButtonTwoTimesPressed == 1) {
      int computerMatchesToRemove = (currentMatches - 1) %  (MAX_NUMBER + 1);
      if (computerMatchesToRemove == 0) matchesToRemove = rand() % 3 + 1; else matchesToRemove = computerMatchesToRemove;
    } else if (computerButtonTwoTimesPressed == 2) {
      currentMatches -= matchesToRemove;
      *computerMatchesRemoved += matchesToRemove;
    

      computerButtonTwoTimesPressed = 0;
      gameAction = false;
      switchPlayers();
      return;
    }
    
  } else if (currentPlayer = HUMAN_PLAYER) {
    currentMatches -= matchesToRemove;
    *humanMatchesRemoved += matchesToRemove;

    switchPlayers();
  }
  
  gameAction = false;
}

void switchPlayers() {
  if (currentPlayer == HUMAN_PLAYER) currentPlayer = COMPUTER_PLAYER; else currentPlayer = HUMAN_PLAYER;
}

int gameNotEnded() {
  if (currentMatches <= 1) {
    return false;
  }

  return true;
}

void displayValues() {
  for (int i = 0; i<5000; i++) {
    writeCharToSegment( SECOND_DIGIT, currentPlayer );
    writeNumberToSegment( 0, matchesToRemove );
    writeNumberToSegment( 2, currentMatches / 10 );
    writeNumberToSegment( 3, currentMatches % 10 );
  }
  for (int i = 0; i<5000; i++) {
    writeNumberToSegmentAnir( SECOND_DIGIT, 0xFF );
    writeNumberToSegment( 0, matchesToRemove );
    writeNumberToSegment( 2, currentMatches / 10 );
    writeNumberToSegment( 3, currentMatches % 10 );
  }
}

void displayWinner() {
  turnDisplayOFF(); // the reason i turn the display off before changing the values is because sometimes it lags and it tries to 'merge' the previous value and the new value I want to show
 if (currentPlayer == HUMAN_PLAYER) {
  while (1) {
    writeNumberToSegmentAnir( FIRST_DIGIT, 0b10001001 );
    writeNumberToSegmentAnir( SECOND_DIGIT, 0b01111001 );
    writeNumberToSegmentAnir( THIRD_DIGIT, 0b01111001 );
    writeNumberToSegmentAnir( FOURTH_DIGIT, 0b01111001 );
  }
 } else {
  while (1) {
    writeNumberToSegmentAnir( FIRST_DIGIT, 0b11000110 );
    writeNumberToSegmentAnir( SECOND_DIGIT, 0b01111001 );
    writeNumberToSegmentAnir( THIRD_DIGIT, 0b01111001 );
    writeNumberToSegmentAnir( FOURTH_DIGIT, 0b01111001 );
  }
 }
}