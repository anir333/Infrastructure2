#include <LEDs.h>
#include <button.h>
#include <stdio.h> 
#include <stdlib.h>  // For rand()
#include <stdbool.h>
#include <usart.h>

int iteration = 0;
int answer = 0;
int score = 0;
bool continueLoop = true;
int optionA = -1;
int optionB = -1;
int optionC = -1;

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
        iteration++;
        _delay_us (500); // debounce
    
        showScoreAndSolution(1);

        continueLoop = (iteration < 5);
        randomMorseCodeLEDsGenerator();

    }
    if ( buttonPushed(2) ) {
        iteration++;
        _delay_us (500); // debounce
    
        showScoreAndSolution(2);

        continueLoop = (iteration < 5);
        randomMorseCodeLEDsGenerator();
    }
    if ( buttonPushed(3) ) {
        iteration++;
        _delay_us (500); // debounce
    
        showScoreAndSolution(3);

        continueLoop = (iteration < 5);
        randomMorseCodeLEDsGenerator();
    }
}

int main() {
    initUSART();

    enableAllLeds();

    countDownLEDs();

    enableAllButtons();
    enableAllButtonInterrupts();
    
    randomMorseCodeLEDsGenerator();

    return 0;
}

void randomMorseCodeLEDsGenerator() {
    if (continueLoop) {
        int randomCharacterPosition = rand() % 37;

        makeLEDsShowMorseCode( morseCodeArray[randomCharacterPosition] );
        printf("\n------------------------------------------------------\n");
        printf("\n\n\n-> Question %d:", iteration+1);
        printOptions( morseCodeArray[randomCharacterPosition], randomCharacterPosition );

        enableAllButtonInterrupts();
        while(continueLoop);
    } else {
        printf("\n------------------------------------------------------\n");
        printf("\n\n\nFinishing program with an LED dance!\n");
        ledChaos(); // infiniter while loop
        // exit(0);
    }
}

void makeLEDsShowMorseCode( MORSECODE character ) {
    int i = 0;
    int ledDurationLength = character.LEDsPattern[i];

    while ( ledDurationLength != 0 ) { // to printf the pattern first
        i++;
        ledDurationLength = character.LEDsPattern[i];
    }

    i = 0;
    ledDurationLength = character.LEDsPattern[i];
    while ( ledDurationLength != 0 ) {
        if ( ledDurationLength == 1 ) {
            lightUpAllLeds();
            _delay_ms ( 250 );
            lightDownAllLeds();
            _delay_ms ( 100 );
        } else if ( ledDurationLength == 2 ) {
            lightUpAllLeds();
            pauseSeconds(1.5);
            lightDownAllLeds();
            _delay_ms ( 100 );
        }
        
        i++;
        ledDurationLength = character.LEDsPattern[i];
    } 
}

void printOptions(MORSECODE correctAnswer, int indexOfCorrectAnswer) {
    printf("\nThinking...\n");
    int randomOptionForCorrectAnswer = rand() % 3 + 1;
    optionA = -1;
    optionB = -1;
    optionC = -1;

    if (randomOptionForCorrectAnswer == 1) {
        answer = 1;
        optionA = indexOfCorrectAnswer;
    } else if (randomOptionForCorrectAnswer == 2) {
        answer = 2;
        optionB = indexOfCorrectAnswer;
    } else if (randomOptionForCorrectAnswer == 3) {
        answer = 3;
        optionC = indexOfCorrectAnswer;
    }

    while (1) {
        if ( randomOptionForCorrectAnswer == 1 ) {
            optionB = rand() % 37;
            optionC = rand() % 37;    
        } else if ( randomOptionForCorrectAnswer == 2 ) {
            optionA = rand() % 37;
            optionC = rand() % 37;
        } else if ( randomOptionForCorrectAnswer == 3 ) {
            optionA = rand() % 37;
            optionB = rand() % 37;
        }

        // printf("\n\n OPTION A: %d, OPTION B: %d, OPTION C: %d", optionA, optionB, optionC);

        if ((optionA != optionB) && (optionA != optionC) && (optionB != optionC))
            break;
    }

    printf("\n-> GIVEN THE LED PATTERN THAT WAS SHOWN \n");
    printf("    CLICK A BUTTON TO CHOOSE AN ANSWER: \n");
    printf("{ Button 1 == A; Button 2 == B; Button 3 == C }\n");
    printf("\n A) %c\n", morseCodeArray[optionA].character);
    printf("\n B) %c\n", morseCodeArray[optionB].character);
    printf("\n C) %c\n\n\n", morseCodeArray[optionC].character);
}

void showScoreAndSolution(int selectedAnswer) {
    bool answeredCorrectly = (answer == selectedAnswer);

    printf("\n\nYOU CHOSE ANSWER: %c) %c\n", (selectedAnswer == 1 ? 'A' : (selectedAnswer == 2 ? 'B' : 'C')), morseCodeArray[(selectedAnswer == 1 ? optionA : (selectedAnswer == 2 ? optionB : optionC))].character);
    printf("YOUR ANSWER IS %s\n", (answeredCorrectly ? "CORRECT!" : "INCORRECT!"));

    if (!answeredCorrectly) {
        printf("-> THE CORRECT ANSWER IS: %c) %c\n", (answer == 1 ? 'A' : (answer == 2 ? 'B' : 'C')), morseCodeArray[(answer == 1 ? optionA : (answer == 2 ? optionB : optionC))].character);
    }
    if (answeredCorrectly) {
        score += 50;
    }

    printf("YOUR CURRENT SCORE IS: %d\n", score);
}