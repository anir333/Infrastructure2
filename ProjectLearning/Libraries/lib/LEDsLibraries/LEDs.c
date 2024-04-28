#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#include <LEDs.h>
#include <time.h>
#include <usart.h>
#include <myOwnlib.h>

void pauseSeconds(int seconds) {
    _delay_ms(seconds * 1000);
}

void disableAllLEDs(void) {
    DDRB = 0b00000000;
}

void enableOneLed(int LEDnumber) {
    DDRB |= (1 << (LEDnumber+1));
    lightDownAllLeds();
}

void enableMultipleLeds(uint8_t byte) {
    DDRB |= byte;
    lightDownAllLeds();
}

void enableAllLeds(void) {
    DDRB = 0b00111100;
    lightDownAllLeds();
}

void lightUpOneLed(int LED) {
    PORTB &= ~(1 << (LED+1));
}

void lightUpOneLedONLY(int LED) {
    PORTB = ~(1 << (LED+1));
}

void lightUpMultipleLeds(uint8_t byte) {
    PORTB = byte;
}

void lightUpAllLeds(void) {
    PORTB = 0b00000000;
}

void lightDownOneLed(int LED) {
    PORTB |= (1 << (LED+1));
}

void lightDownMultipleLeds(uint8_t byte) {
    PORTB = byte;
}

void lightDownAllLeds(void) {
    PORTB = 0b00111100;
}

void lightToggleOneLed(int LED) {
    uint8_t previousPORTB = PORTB; 

    lightDownOneLed(LED);

    if (previousPORTB == PORTB) {
        lightUpOneLed(LED);
    }
}

void dimLed(int lednumber, int percentage, int duration) {
    int lightOffDuration = percentage / 10;
    
    // long startTime = millis();
    // while (1) { //(millis() - startTime <= duration) {
    //     // printf("startTime: %d\n", startTime);
    //     lightUpOneLed(lednumber);
    //     _delay_ms(10-lightOffDuration);
    //     lightDownOneLed(lednumber);
    //     _delay_ms(lightOffDuration);
        
    // } 

    int lightOnDuration = 10-lightOffDuration;
    for (int i = 0; i<(duration*70); i++) {
        // printf("%d\n", i);
                  lightUpOneLed(lednumber);
                for (int j = 0; j < (10 - lightOffDuration); j++) {
            _delay_ms(1); // Delay for 1 millisecond
        }
                lightDownOneLed(lednumber);
                 for (int j = 0; j < lightOffDuration; j++) {
            _delay_ms(1); // Delay for 1 millisecond
        }
    }
    // printf("finished counting");
}

void fadeInLed(int led, int duration) {
    for (int i = 0; i <= 100; i++) {
        dimLed(led, i, duration);
        _delay_ms(2000);
    }
}


void fadeOutLed(int led, int duration) {
    for (int i = 100; i >= 0; i--) {
        dimLed(led, 99, duration);
        _delay_ms(200);
    }
}

void ledChaos(void) {
    enableAllLeds();
    do {
        int randomLedGenerated = rand() % 4 + 1;
        int randomDurationInMiliseconds = rand() % 901 + 100;

        lightUpOneLed(randomLedGenerated);
        _delay_ms(randomDurationInMiliseconds);


        lightDownOneLed(randomLedGenerated);

    } while (1);
}

void consecutiveLightUp(void) {
    printf("\nStarting Consecutive Light Up (inifinite loop)!\n");

    initUSART();
    enableAllLeds();
    while (1) {
        lightUpOneLed(1);
        _delay_ms(100);
        lightUpOneLed(2);
        _delay_ms(100);
        lightUpOneLed(3);
        _delay_ms(100);
        lightUpOneLed(4);
        _delay_ms(100);
        lightDownOneLed(1);
        _delay_ms(100);
        lightDownOneLed(2);
        _delay_ms(100);
        lightDownOneLed(3);
        _delay_ms(100);
        lightDownOneLed(4);
        _delay_ms(100);
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

void randomDurationForRandomLed(void) {
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
        lightToggleOneLed(1);
        _delay_ms(100);
        lightDownOneLed(1);
        _delay_ms(100);
        } else if (letters[i] == 'b') {
        lightToggleOneLed(2);
        _delay_ms(100);
        lightDownOneLed(2);
        _delay_ms(100);
        } else if (letters[i] == 'c') {
        lightToggleOneLed(3);
        _delay_ms(100);
        lightDownOneLed(3);
        _delay_ms(100);
        } else if (letters[i] == 'd') {
        lightToggleOneLed(4);
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
            lightUpAllLeds();
            _delay_ms(100);
            lightDownAllLeds();
            _delay_ms(100);
            lightUpAllLeds();
            _delay_ms(100);
            lightDownAllLeds();
            _delay_ms(100);
        } else if (str[e] == 'c') {
            lightUpAllLeds();
            _delay_ms(100);
            lightDownAllLeds();
            _delay_ms(100);
            lightUpAllLeds();
            _delay_ms(100);
            lightDownAllLeds();
            _delay_ms(100);
            lightUpAllLeds();
            _delay_ms(100);
            lightDownAllLeds();
            _delay_ms(100);
        } else if (str[e] == 'd') {
            lightUpAllLeds();
            _delay_ms(100);
            lightDownAllLeds();
            _delay_ms(100);
            lightUpAllLeds();
            _delay_ms(100);
            lightDownAllLeds();
            _delay_ms(100);
            lightUpAllLeds();
            _delay_ms(100);
            lightDownAllLeds();
            _delay_ms(100);
            lightUpAllLeds();
            _delay_ms(100);
            lightDownAllLeds();
            _delay_ms(100);
        } 
    }
    
    printf("\nlightUpAllLedsBasedOnRandomStringXAmountOfTimes() Done!\n");
}