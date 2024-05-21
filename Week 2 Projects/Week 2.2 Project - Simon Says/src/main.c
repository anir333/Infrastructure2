#include <button.h>
#include <LEDs.h>
#include <stdbool.h>
#include <usart.h>
#include <stdlib.h>  // for rand() method

#define MAX_LEVEL 10 // CURRENTLY BY DEFAULT THERE ARE 10 LEVELS, CHANGE THE NUMBER OF LEVELS HERE TO TEST THE GAME WITH LESS LEVELS

/* UNCOMMENT THE FOLLOWING LINE TO SEE THE PATTERN GENERATED (ONLY FOR TESTING PURPOSES) */
#define PRINT_PUZZLE_GENERATED

int ledCounter = 0;
bool gameStarted = false;
int level = 1;
int puzzle[MAX_LEVEL+1] = {0};
int buttonsClickedPattern[MAX_LEVEL+1] = {0};
int numOfButtonClicks = 0;

ISR ( PCINT1_vect ) {
    if ( buttonPushed(1) ) {
        _delay_us (100);
        if ( !gameStarted ) {
            gameStarted = true;
            
            startGame();
        } else {
            lightUpOneLed(1);
            if (puzzle[numOfButtonClicks] == 1) {
                printf("\nYou pressed button 1, correct!\n"); 
            } else printf("\nYou pressed button 1, wrong!\n");
            
            buttonsClickedPattern[numOfButtonClicks] = 1;
            numOfButtonClicks++;
            lightDownOneLed(1);
        }
    }
    if ( gameStarted && buttonPushed(2) ) {
        _delay_us (100);
        lightUpOneLed(2);
        if (puzzle[numOfButtonClicks] == 2) {
            printf("\nYou pressed button 2, correct!\n"); 
        } else printf("\nYou pressed button 2, wrong!\n");
        
        buttonsClickedPattern[numOfButtonClicks] = 2;
        numOfButtonClicks++;
        lightDownOneLed(2);
    }
    if ( gameStarted && buttonPushed(3) ) {
        _delay_us (100);
        lightUpOneLed(3);
        if (puzzle[numOfButtonClicks] == 3) {
            printf("\nYou pressed button 3, correct!\n"); 
        } else printf("\n\nYou pressed button 3, wrong!\n\n");
        
        buttonsClickedPattern[numOfButtonClicks] = 3;
        numOfButtonClicks++;
        lightDownOneLed(3);
    }
}

int main() {
    initUSART();

    enableAllLeds();
    enableAllButtons();
    enableAllButtonInterrupts();

    printf("\n\n\n\t -> Click Button 1 to start the game!\n");
    printf("\n\t -> RULES: Every time you start a new level, a pattern of lights will show.\n\t The length of this pattern will increase on each level!\n");
    printf("\n\t-> After the pattern of lights Simon shows, all 4 LEDs will make a consecutive light up and down to let you know that you can start clicking the buttons to figure out the pattern previously shown by the LEDs!\n");
    printf("\n\t -> Once you guess the pattern correctly on all %d levels, you will become the Simon Master!", MAX_LEVEL);
    printf("\nClick the buttons fast to not have problems with debouncing!");


    while ( !gameStarted ) {
        lightUpAndDownLED( 4, 100 );
        ledCounter++;
        lightDownAllLeds();
    }


    return 0;
}

void startGame() {
    lightUpOneLed(1);
    _delay_ms( 100 );
    lightUpOneLed(2);
    _delay_ms( 100 );
    lightUpOneLed(3);
    _delay_ms( 100 );
    lightUpOneLed(4);
    _delay_ms( 100 );
    lightDownOneLed(1);
    _delay_ms( 100 );
    lightDownOneLed(2);
    _delay_ms( 100 );
    lightDownOneLed(3);
    _delay_ms( 100 );
    lightDownOneLed(4);

    printf("\n\n\nStarting game...\n\n\n");
    lightDownAllLeds();
    pauseSeconds(1);

    srand(ledCounter); // seeding the rand with the number of times the LED flashed before starting the game to improve randomness 


    enableAllButtonInterrupts();
    while ( level <= MAX_LEVEL ) {
        printf("------------------------------------------------");
        printf("\n\n\n\t -> LEVEL %d\n\n", level);
        // generate new puzzle of the length of the level (so that each level becomes harder)
        generatePuzzle( &puzzle[0], level );
        
        #ifdef PRINT_PUZZLE_GENERATED
        printf("Puzzle generated: ");
        for (int i = 0; i<level; i++) {
            printf("%d ", puzzle[i]);
        }
        #endif

        printf("\n\t-> Showing LED pattern, wait until finished...\n");
        lightUpLEDsPatternPuzzle( puzzle, 650 ); // light up the LEDs according to the puzzle randomly created, and on top of that I can make it faster for each level to increase level difficulty by changing 650 to (3000/level)
        printf("\t\t-> LED PATTERN FINISHED! You can start clicking the buttons!\n");    
    
        level += checkerButtonEngine();
        if ( level > MAX_LEVEL ) break;
    }

    printf("\n\n ALL %d LEVELS COMPLETED! You're now the SIMON MASTER!\n", MAX_LEVEL);
    exit(0);
}


int checkerButtonEngine() {
    lightUpOneLed(1);
    _delay_ms( 50 );
    lightUpOneLed(2);
    _delay_ms( 50 );
    lightUpOneLed(3);
    _delay_ms( 50 );
    lightUpOneLed(4);
    _delay_ms( 50 );
    lightDownOneLed(1);
    _delay_ms( 50 );
    lightDownOneLed(2);
    _delay_ms( 50 );
    lightDownOneLed(3);
    _delay_ms( 50 );
    lightDownOneLed(4);

    numOfButtonClicks=0;
    enableAllButtonInterrupts();
    while (numOfButtonClicks < level) {
        _delay_ms(500);
    }



    int i = 0;
    while ( puzzle[i] != 0 ) {
        if (puzzle[i] != buttonsClickedPattern[i]) {
            for (int wrong = 0; wrong<4; wrong++) {
                lightUpAndDownAllLEDs( 300 );
            }        
            printf("\n\n WRONG! THE PATTERN WAS [");
            for (int i = 0; i<level; i++) {
                if (i == level-1) printf("%d", puzzle[i]); else printf("%d, ", puzzle[i]);
            } printf("]\n\n");
            return false;
            break;
        }

        i++;
    }

    for (int correct = 0; correct<8; correct++) {
        lightUpAndDownLED( 4, 100 );
    }
    if (level < MAX_LEVEL) printf("\n\n -> CORRECT WE GO TO LEVEL %d\n\n", level+1);
    return true;
}

void lightUpLEDsPatternPuzzle( int puzzle[], int duration ) {
    for (int i = 0; i < level; i++) {
        lightUpOneLed( puzzle[i] );
        _delay_ms ( duration );
        lightDownOneLed( puzzle[i] );
        _delay_ms ( duration / 2 );
        
    }
}

void generatePuzzle( int* puzzle, int length ) {
    for (int i = 0; i<length; i++) {
        puzzle[i] = rand() % 3 + 1; // from 1 to 3
    }
}