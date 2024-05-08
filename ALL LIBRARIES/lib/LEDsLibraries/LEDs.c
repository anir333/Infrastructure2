#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#include <LEDs.h>
#include <time.h>
#include <usart.h>
#include <registersLib.h>

/* fix the lightDownMultipleLeds and also the up one, and the light up one led and others to make them ONLY CHANGE THE LEDs not the other four bits (first two and last two) */

void pauseSeconds(int seconds) {
    _delay_ms(seconds * 1000);
}

void enableOneLed(int LEDnumber) {
    if ( LEDnumber < 0 || LEDnumber > NUMBER_OF_LEDS - 1 ) return;
    DDRB |= (1 << (PB1 + LEDnumber));
    lightDownAllLeds();
}

void enableMultipleLeds(uint8_t byte) {
    DDRB |= byte;
    lightDownAllLeds();
}

void enableAllLeds() {
    DDRB |= 0b00111100;
    lightDownAllLeds();
}

void lightUpOneLed(int LEDnumber) {
    if ( LEDnumber < 0 || LEDnumber > NUMBER_OF_LEDS ) return;
    PORTB &= ~(1 << (PB1 + LEDnumber));
}

void lightUpMultipleLeds(uint8_t byte) {
    uint8_t mask = 0b00111100;

    PORTB &= ~mask;

    PORTB |= (byte & mask);
}

void lightUpAllLeds() {
    PORTB &= 0b11000011;
}

void lightDownOneLed(int LEDnumber) {
    if ( LEDnumber < 0 || LEDnumber > NUMBER_OF_LEDS ) return;
    PORTB |= (1 << (PB1 + LEDnumber));
}

void lightDownMultipleLeds(uint8_t byte) {
    uint8_t mask = 0b00111100;

    PORTB &= ~(byte & mask);
}

void lightDownAllLeds() { // correct version (it doesn't mess up with other pins, it makes sure onyl the LEDs are set to 1)
    PORTB &= 0b11000011;
    PORTB |= 0b00111100;
}

void lightToggleOneLed(int LEDnumber) {
    if ( LEDnumber < 0 || LEDnumber > NUMBER_OF_LEDS ) return;
    uint8_t previousPORTB = PORTB; 

    lightDownOneLed(LEDnumber);

    if (previousPORTB == PORTB) {
        lightUpOneLed(LEDnumber);
    }
}

void dimLed(int lednumber, int percentage, long duration) {
    int lightOffDuration = percentage / 10;

    int lightOnDuration = 10-lightOffDuration;
    for (int i = 0; i<(duration*500); i++) {
            lightUpOneLed(lednumber);
            _delay_ms(lightOnDuration);
            lightDownOneLed(lednumber);
            _delay_ms(lightOffDuration);
    }
}



void fadeInLed(int ledNumber, long duration) {
    for (long i = 0; i <= duration * 500; i++) {
        int percentage = (i * 100) / (duration * 500);
        dimLed(ledNumber, percentage, 1);
    }
}


void fadeOutLed(int ledNumber, long duration) {
    for (long i = duration * 500; i >= 0; i--) {
        int percentage = (i * 100) / (duration * 500);
        dimLed(ledNumber, percentage, 1);
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

void lightUpOneLedNTimes(int led, int numberOfFlashes) {
    initUSART();
    enableOneLed(led);
    for (int i = 0; i<numberOfFlashes; i++) {
        lightUpOneLed(led);
        _delay_ms(1000);
        lightDownOneLed(led);
        _delay_ms(1000);
    }

    printf("\nlightUpOneLedNTimes() Done!\n");
}

void makeLedBurnLonger(int led) {
    initUSART();
    enableOneLed(led);
    int i = 0;
    int burningTime = 10;
    while (i<=20) { // 100/50 = 20 iterations
        lightUpOneLed(led);
        _delay_ms(burningTime);
        lightDownOneLed(led);
        _delay_ms(burningTime);

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
        lightUpOneLed(digits[i]);
        _delay_ms(500);
        lightDownOneLed(digits[i]);
        _delay_ms(500);
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
        lightToggleOneLed(randomLED);
        _delay_ms(randomDurations[e]);
        lightToggleOneLed(randomLED);
        _delay_ms(randomDurations[e]);
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
        lightUpOneLed(1);
        _delay_ms(100);
        lightDownOneLed(1);
        _delay_ms(100);
        } else if (letters[i] == 'b') {
        lightUpOneLed(2);
        _delay_ms(100);
        lightDownOneLed(2);
        _delay_ms(100);
        } else if (letters[i] == 'c') {
        lightUpOneLed(3);
        _delay_ms(100);
        lightDownOneLed(3);
        _delay_ms(100);
        } else if (letters[i] == 'd') {
        lightUpOneLed(4);
        _delay_ms(100);
        lightDownOneLed(4);
        _delay_ms(100);
        }
    }

    printf("\nlightUpLedsBasedOnString() Done!\n");
}

void lightUpLedsBasedOnArrayOfChars(char chars[], int size) {
    initUSART();

    enableAllLeds();
    for (int i = 0; i<size; i++) {
        if (chars[i] == 'a') {
        lightToggleOneLed(1);
        _delay_ms(100);
        lightDownOneLed(1);
        _delay_ms(100);
        } else if (chars[i] == 'b') {
        lightToggleOneLed(2);
        _delay_ms(100);
        lightDownOneLed(2);
        _delay_ms(100);
        } else if (chars[i] == 'c') {
        lightToggleOneLed(3);
        _delay_ms(100);
        lightDownOneLed(3);
        _delay_ms(100);
        } else if (chars[i] == 'd') {
        lightToggleOneLed(4);
        _delay_ms(100);
        lightDownOneLed(4);
        _delay_ms(100);
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
            lightUpAllLeds();
            _delay_ms(100);
            lightDownAllLeds();
            _delay_ms(100);
        } else if (str[e] == 'b') {
            for (int i = 0; i < 2; i++) {
                lightUpAllLeds();
                _delay_ms(100);
                lightDownAllLeds();
                _delay_ms(100);
            }
        } else if (str[e] == 'c') {
            for (int i = 0; i < 3; i++) {
                lightUpAllLeds();
                _delay_ms(100);
                lightDownAllLeds();
                _delay_ms(100);
            }
        } else if (str[e] == 'd') { // for loop
            for (int i = 0; i < 4; i++) {
                lightUpAllLeds();
                _delay_ms(100);
                lightDownAllLeds();
                _delay_ms(100);
            }    
        } 
    }
    
    printf("\nlightUpAllLedsBasedOnRandomStringXAmountOfTimes() Done!\n");
}