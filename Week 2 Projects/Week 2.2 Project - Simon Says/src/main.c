#include <button.h>
#include <LEDs.h>
#include <stdbool.h>
#include <usart.h>
#include <stdlib.h>  // for rand() method

#define MAX_LEVEL 10

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
        _delay_us (1000);
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
        _delay_us (1000);
        lightUpOneLed(2);
        if (puzzle[numOfButtonClicks] == 2) {
            printf("\nYou pressed button 2, correct!\n"); 
        } else printf("\nYou pressed button 2, wrong!\n");
        
        buttonsClickedPattern[numOfButtonClicks] = 2;
        numOfButtonClicks++;
        lightDownOneLed(2);
    }
    if ( gameStarted && buttonPushed(3) ) {
        _delay_us (1000);
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
    printf("\n\t -> Once you guess the pattern correctly on all 10 levels, you will become the Simon Master!");


    while ( !gameStarted ) {
        lightUpAndDownLED( 4, 100 );
        ledCounter++;
        // printf("\nIteration\n");
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
        // printf("\nSize of puzzle: %d\n", sizeof(MAX_LEVEL));
        printf("\n\t-> SHOWING LED PATTERN, WAIT UNTIL FINISHED...\n");
        lightUpLEDsPatternPuzzle( puzzle, 650 ); // light up the LEDs according to the puzzle randomly created, and on top of that I can make it faster for each level to increase level difficulty by changing 650 to (3000/level)
        printf("\t\t-> LED PATTERN FINISHED! YOU CAN START CLICKING THE BUTTONS!\n");    
    
        level += checkerButtonEngine();
        if ( level > MAX_LEVEL ) break;
        // printf("next level: %d", level);
    }

    printf("\n\n ALL 10 LEVEL COMPLETED! You're now the SIMON MASTER!\n");
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
    // printf("\nchecker engine started, num of button clicks is: %d\n", numOfButtonClicks);
    enableAllButtonInterrupts();
    while (numOfButtonClicks < level) {
        // printf("\nnumber of buttons clicekd: %d", numOfButtonClicks);
        _delay_ms(500);
    }



    int i = 0;
        // printf("\n\n INCREASING LEVEL? : \n");
        // printf("\nCHECK BUTTONS CLICKED VS PUZZLE: ");
    while ( puzzle[i] != 0 ) {
        // printf("BUTTON: %d || PUZZLE: %d\n", buttonsClickedPattern[i], puzzle[i]);
        
        if (puzzle[i] != buttonsClickedPattern[i]) {
            // printf("\n\n SHOULD RETURN 0: %d", false);
            return false;
            break;
            // printf("\nSHOULDNT HAVE GOTTEN HERE 1\n");
        }

        i++;
    }

    // printf("\nSHOULDNT HAVE GOTTEN HERE 2 unless correct clicks\n");

    return true;
}

void lightUpLEDsPatternPuzzle( int puzzle[], int duration ) {
    for (int i = 0; i < level; i++) {
        // lightUpAndDownLED( puzzle[i], duration );
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