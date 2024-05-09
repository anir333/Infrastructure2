#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#include <LEDs.h>
#include <time.h>
#include <usart.h>
#include <registersLib.h>
#include <stdbool.h>

void pauseSeconds(int seconds) {
    _delay_ms(seconds * 1000);
}

bool isLEDon( int LEDnumber ) {
    if ( LEDnumber < 0 || LEDnumber > NUMBER_OF_LEDS ) return false;
    uint8_t previousLED_PORT = LED_PORT; 

    lightDownOneLed(LEDnumber);

    if (previousLED_PORT == LED_PORT) {
        return false;
    } else return true;
}

void enableOneLed(int LEDnumber) {
    if ( LEDnumber < 0 || LEDnumber > NUMBER_OF_LEDS - 1 ) return;
    LED_DDR |= (1 << (PB1 + LEDnumber));
    lightDownAllLeds();
}

void enableMultipleLeds(uint8_t byte) {
    LED_DDR |= byte;
    lightDownAllLeds();
}

void enableAllLeds() {
    LED_DDR |= 0b00111100;
    lightDownAllLeds();
}

void lightUpOneLed(int LEDnumber) {
    if ( LEDnumber < 0 || LEDnumber > NUMBER_OF_LEDS ) return;
    LED_PORT &= ~(1 << (PB1 + LEDnumber));
}

void lightUpMultipleLeds(uint8_t byte) {
    uint8_t mask = 0b00111100;

    LED_PORT &= ~mask;

    LED_PORT |= (byte & mask);
}

void lightUpAllLeds() {
    LED_PORT &= 0b11000011;
}

void lightDownOneLed(int LEDnumber) {
    if ( LEDnumber < 0 || LEDnumber > NUMBER_OF_LEDS ) return;
    LED_PORT |= (1 << (PB1 + LEDnumber));
}

void lightDownMultipleLeds(uint8_t byte) {
    uint8_t mask = 0b00111100;

    LED_PORT &= ~mask;

    LED_PORT |= (byte & mask);
}

void lightDownAllLeds() { // correct version (it doesn't mess up with other pins, it makes sure onyl the LEDs are set to 1)
    LED_PORT &= 0b11000011;
    LED_PORT |= 0b00111100;
}

void lightToggleOneLed(int LEDnumber) {
    if ( LEDnumber < 0 || LEDnumber > NUMBER_OF_LEDS ) return;
    uint8_t previousLED_PORT = LED_PORT; 

    lightDownOneLed(LEDnumber);

    if (previousLED_PORT == LED_PORT) {
        lightUpOneLed(LEDnumber);
    }
}

void dimLed(int LEDnumber, int percentage, long duration) {
    if ( LEDnumber < 0 || LEDnumber > NUMBER_OF_LEDS ) return;
    int lightOffDuration = percentage / 10;

    int lightOnDuration = 10-lightOffDuration;
    for (int i = 0; i<(duration*500); i++) {
        lightUpOneLed(LEDnumber);
        _delay_ms(lightOnDuration);
        lightDownOneLed(LEDnumber);
        _delay_ms(lightOffDuration);
    }
}



void fadeInLed(int LEDnumber, long duration) {
    if ( LEDnumber < 0 || LEDnumber > NUMBER_OF_LEDS ) return;
    for (long i = 0; i <= duration * 500; i++) {
        int percentage = (i * 100) / (duration * 500);
        dimLed(LEDnumber, percentage, 1);
    }
}


void fadeOutLed(int LEDnumber, long duration) {
    if ( LEDnumber < 0 || LEDnumber > NUMBER_OF_LEDS ) return;
    for (long i = duration * 500; i >= 0; i--) {
        int percentage = (i * 100) / (duration * 500);
        dimLed(LEDnumber, percentage, 1);
    }
}


void ledChaos() {
    enableAllLeds();
    do {
        int randomLedGenerated = rand() % 4 + 1;
        int randomDurationInMiliseconds = rand() % 901 + 100;

        lightUpOneLed(randomLedGenerated);
        _delay_ms(randomDurationInMiliseconds);


        lightDownOneLed(randomLedGenerated);

    } while (1);
}

void consecutiveLightUp() {
    printf("\nStarting Consecutive Light Up (inifinite loop)!\n");

    initUSART();
    enableAllLeds();
    while (1) {
        for (int i = 1; i<=4; i++) {
            lightUpOneLed(i);
            _delay_ms(100);
        }
        for (int i = 1; i<=4; i++) {
            lightDownOneLed(i);
            _delay_ms(100);
        }
    }
}

void lightUpOneLedNTimes(int LEDnumber, int numberOfFlashes) {
    if ( LEDnumber < 0 || LEDnumber > NUMBER_OF_LEDS ) return;
    initUSART();
    enableOneLed(LEDnumber);
    for (int i = 0; i<numberOfFlashes; i++) {
        lightUpAndDownLED(LEDnumber, 1000);
    }

    printf("\nlightUpOneLedNTimes() Done!\n");
}

void makeLedBurnLonger(int LEDnumber) {
    if ( LEDnumber < 0 || LEDnumber > NUMBER_OF_LEDS ) return;
    initUSART();
    enableOneLed(LEDnumber);
    int i = 0;
    int burningTime = 10;
    while (i<=20) { // 100/50 = 20 iterations
        lightUpAndDownLED(LEDnumber, burningTime);

        // printf("buring time: %d and iteration: %d\n", burningTime, i);
        burningTime += (i == 0) ? 40 : 50;

        i++;
    }

    printf("\nmakeLedBurnLonger() Done!\n");
}

void walkThroughArrayLightLed() {
    initUSART();
    enableAllLeds();
    int digits[10] = {};

    for (int e = 0; e<getSizeOfArray(digits); e++) {
        int randomLedGenerated = rand() % 4 + 1;
        digits[e] = randomLedGenerated;
    }

    for (int i = 0; i<getSizeOfArray(digits); i++) {
        lightUpAndDownLED(digits[i], 500);
    }

    printf("\nwalkThroughArrayLightLed() Done!\n");
}

void randomDurationForRandomLed() {
    initUSART();
    enableAllLeds();
    int randomDurations[10] = {};


    for (int i = 0; i<getSizeOfArray(randomDurations); i++) {
        int randomMultiplier = rand() % 20 + 1;
        randomDurations[i] = randomMultiplier * 50;
    }

    for (int e = 0; e<getSizeOfArray(randomDurations); e++) {
        int randomLED = rand() % 4 + 1;
        // printf("lighting up LED: %d during: %d ms\n", randomLED, randomDurations[e]);
        lightUpAndDownLED(randomLED, randomDurations[e]);
    }

    printf("\nrandomDurationForRandomLed() Done!\n");
}

void lightUpLedsBasedOnString(const char *letters) {
    initUSART();

    int size = 0;
    while (letters[size] != '\0') {
        size++;
    }

    enableAllLeds();
    for (int i = 0; i<size; i++) {
        if (letters[i] == 'a') {
          lightUpAndDownLED(1, 100);
        } else if (letters[i] == 'b') {
          lightUpAndDownLED(2, 100);
        } else if (letters[i] == 'c') {
          lightUpAndDownLED(3, 100);
        } else if (letters[i] == 'd') {
          lightUpAndDownLED(4, 100);
        }
    }

    printf("\nlightUpLedsBasedOnString() Done!\n");
}

void lightUpLedsBasedOnArrayOfChars(char chars[], int size) {
    initUSART();

    enableAllLeds();
    for (int i = 0; i<size; i++) {
        if (chars[i] == 'a') {
          lightUpAndDownLED(1, 100);
        } else if (chars[i] == 'b') {
          lightUpAndDownLED(2, 100);
        } else if (chars[i] == 'c') {
          lightUpAndDownLED(3, 100);
        } else if (chars[i] == 'd') {
          lightUpAndDownLED(4, 100);
        }
    }

    printf("\nlightUpLedsBasedOnArrayOfChars() Done!\n");
}

void lightUpAllLedsBasedOnRandomStringXAmountOfTimes() {
    initUSART();
    enableAllLeds();
    char possibleCharactersToLightUpLeds[] = {'a', 'b', 'c', 'd'};
    
    int randLengthOfString = rand() % 10 + 1;
    char str[randLengthOfString];

    for (int i = 0; i < randLengthOfString; i++) {
        int randomCharacterSelectedToAdd = rand() % 4;
        str[i] = possibleCharactersToLightUpLeds[randomCharacterSelectedToAdd];
    }

    for (int e  = 0; e<randLengthOfString; e++) {
        pauseSeconds(1);
        if (str[e] == 'a') {
            lightUpAndDownAllLEDs( 100 );
        } else if (str[e] == 'b') {
            for (int i = 0; i < 2; i++) {
                lightUpAndDownAllLEDs( 100 );
            }
        } else if (str[e] == 'c') {
            for (int i = 0; i < 3; i++) {
                lightUpAndDownAllLEDs( 100 );
            }
        } else if (str[e] == 'd') { // for loop
            for (int i = 0; i < 4; i++) {
                lightUpAndDownAllLEDs( 100 );
            }    
        } 
    }
    
    printf("\nlightUpAllLedsBasedOnRandomStringXAmountOfTimes() Done!\n");
}

void lightUpAndDownLED( int LEDnumber, int durationMS ) {
    lightToggleOneLed( LEDnumber );
    _delay_ms( durationMS );
    lightToggleOneLed( LEDnumber );
    _delay_ms( durationMS );
}

void lightUpAndDownAllLEDs( int durationMS ) {
    lightUpAllLeds();
    _delay_ms( durationMS );
    lightDownAllLeds();
    _delay_ms( durationMS );
}

void flashLight( int LEDnumber, int durationMS ) {
    while (1) {
        lightUpAndDownLED( LEDnumber, durationMS);
    }
}