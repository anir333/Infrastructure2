#include <button.h>
#include <LEDs.h>
#include <stdbool.h>
#include <usart.h>
#include <stdlib.h>  // for rand() method

#define MAX_LEVEL 10

int ledCounter = 0;
bool gameStarted = false;
int level = 1;

ISR ( PCINT1_vect ) {
    if ( buttonPushed(1) ) {
        _delay_us (500);
        if ( !gameStarted ) {
            gameStarted = true;
            printf("\nStarting game...\n\n\n");
            
            startGame();
        }
    }
}

int main() {
    initUSART();

    enableAllLeds();
    enableAllButtons();
    enableAllButtonInterrupts();

    while ( !gameStarted ) {
        lightUpAndDownLED( 4, 100 );
        ledCounter++;
        printf("\nitertion\n");
        lightDownAllLeds();

    }


    return 0;
}

void startGame() {
    lightDownAllLeds();
    pauseSeconds(1);

    srand(ledCounter); // seeding the rand with the number of times the LED flashed before starting the game to improve randomness 

    while (level <= MAX_LEVEL) {
        printf("\n\n\n LEVEL %d\n", level);
        // generate new puzzle of the length of the level (so that each level becomes harder)
        int puzzle[] = {0};
        generatePuzzle( &puzzle[0], level );
        printf("Puzzle generated: ");
        for (int i = 0; i<level; i++) {
            printf("%d ", puzzle[i]);
        }

        lightUpLEDsPatternPuzzle( puzzle, 650 ); // light up the LEDs according to the puzzle randomly created, and on top of that I can make it faster for each level to increase level difficulty by changing 650 to (3000/level)
        
    
        level = checkerButtonEngine();
    }
}

int buttonsClickedPattern[level] = {};

int checkerButtonEngine() {

}

void lightUpLEDsPatternPuzzle( int puzzle[], int duration ) {
    for (int i = 0; i < level+1; i++) {
        lightUpAndDownLED( puzzle[i], duration );
    }
}

void generatePuzzle( int* puzzle, int length ) {
    for (int i = 0; i<length; i++) {
        puzzle[i] = rand() % 3 + 1; // from 1 to 3
    }
}