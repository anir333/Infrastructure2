#include <LEDs.h>
#include <button.h>
#include <stdio.h> 
#include <stdlib.h>  // For rand()

int iteration = 0;
int answer = 0;

typedef struct {
    char character;
    int LEDsPattern[6]; // longest pattern for morse code is 5, plus 0 byte at the end
} MORSECODE;

// I asked ChatGPT to complete this for me to save some time:
const MORSECODE morseCodeArray[37] = {
    { 'a', { 1, 2 } },
    { 'b', { 2, 1, 1, 1 } },
    { 'c', { 2, 1, 2, 1 } },
    { 'd', { 2, 1, 1 } },
    { 'e', { 1 } },
    { 'f', { 1, 1, 2, 1 } },
    { 'g', { 2, 2, 1 } },
    { 'h', { 1, 1, 1, 1 } },
    { 'i', { 1, 1 } },
    { 'j', { 1, 2, 2, 2 } },
    { 'k', { 2, 1, 2 } },
    { 'l', { 1, 2, 1, 1 } },
    { 'm', { 2, 2 } },
    { 'n', { 2, 1 } },
    { 'o', { 2, 2, 2 } },
    { 'p', { 1, 2, 2, 1 } },
    { 'q', { 2, 2, 1, 2 } },
    { 'r', { 1, 2, 1 } },
    { 's', { 1, 1, 1 } },
    { 't', { 2 } },
    { 'u', { 1, 1, 2 } },
    { 'v', { 1, 1, 1, 2 } },
    { 'w', { 1, 2, 2 } },
    { 'x', { 2, 1, 1, 2 } },
    { 'y', { 2, 1, 2, 2 } },
    { 'z', { 2, 2, 1, 1 } },
    { '0', { 2, 2, 2, 2, 2 } },
    { '1', { 1, 2, 2, 2, 2 } },
    { '2', { 1, 1, 2, 2, 2 } },
    { '3', { 1, 1, 1, 2, 2 } },
    { '4', { 1, 1, 1, 1, 2 } },
    { '5', { 1, 1, 1, 1, 1 } },
    { '6', { 2, 1, 1, 1, 1 } },
    { '7', { 2, 2, 1, 1, 1 } },
    { '8', { 2, 2, 2, 1, 1 } },
    { '9', { 2, 2, 2, 2, 1 } }
};

ISR ( PCINT1_vect ) {
    if ( buttonPushed(1) ) {
            _delay_us (500);
            printf("\n\nButton 1 pushed!\n\n");

        pauseSeconds(1);
        main();
        // something happens

    } else {
         printf("\n\nButton 1 NOT pushed!\n\n");
    }
    // if ( buttonPushed(3) ) {
    //     // something happens
    // }
    // if ( buttonPushed(3) ) {
    //     // something happens
    // }
}

int main() {
    initUSART();

    // countDownLEDs();

    enableAllButtons();
    enableAllButtonInterrupts();

    printf("\n\nSize of MORSECODE: %d\n\n", sizeof(morseCodeArray));


    programChecker();
    
    // do { iteration ++;
    //     printf("\n\n\n MAIN LOOP iteration: %d \n\n\n", iteration);
    //     randomMorseCodeLEDsGenerator();

    // } while ( iteration <= 5 );

    return 0;
}

void programChecker() {
    if (iteration < 6) {
        iteration++;

        printf("\n\n\n MAIN LOOP iteration: %d \n\n\n", iteration);
        randomMorseCodeLEDsGenerator();

    } else {
        printf("\n finishing program\n");
        ledChaos();
    }
}


void randomMorseCodeLEDsGenerator() {
    srand(time(NULL)); // to avoid patterns on the random number generator and improve uniqueness of each position number generated
    int randomCharacterPosition = rand() % 37;

    makeLEDsShowMorseCode( morseCodeArray[randomCharacterPosition] );

    printOptions( morseCodeArray[randomCharacterPosition] );

    // while (!buttonPushed(1)) {
    //     printf("\n button 1 not pushed yet \n\n");
    //     pauseSeconds(1);
    // }

    // printf("\n\n button 1 pushed finishing program!\n\n");
    // while (1); // to wait for button input
    // while (1) {
    //     if (buttonPushed(1)) {
    //         _delay_us (500);
    //         printf("\n\nButton 1 pushed!\n\n");
    //     } else {
    //         printf("\n\nButton 1 NOT pushed!\n\n");
    //     }

    //     pauseSeconds(1);
    // }
}

void makeLEDsShowMorseCode( MORSECODE character ) {
    
}

void printOptions( MORSECODE correctAnswer ) {

}