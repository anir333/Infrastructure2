#include <stdio.h>
#include <avr/io.h>
#include <LEDs.h>
#include <util/delay.h>
#include <time.h>

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

void lightUpAllLeds() {
    PORTB = 0b00000000;
}

void lightDownOneLed(int LED) {
    PORTB |= (1 << (LED+1));
}

void lightDownMultipleLeds(uint8_t byte) {
    PORTB = byte;
}

void lightDownAllLeds() {
    PORTB = 0b00111100;
}

void lightToggleOneLed(int LED) {
    PORTB |= (1 << (LED+1));
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
        printf(i);
        dimLed(led, i, duration);
        printf(i);
        _delay_ms(2000);
    }
}


// void fadeOutLed(int led, int duration) {
//     for (int i = 100; i >= 0; i--) {
//         dimLed(led, 99, duration);
//         _delay_ms(200);
//     }
// }