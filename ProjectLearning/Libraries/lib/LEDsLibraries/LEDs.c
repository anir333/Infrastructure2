#include <avr/io.h>
#include <LEDs.h>
#include <util/delay.h>

void pauseSeconds(int seconds) {
    _delay_ms(seconds * 1000);
}

void disableAllLEDs(void) {
    DDRB = 0b00000000;
}

void enableOneLed(int LEDnumber) {
    DDRB |= (1 << LEDnumber+1);
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
    PORTB &= ~(1 << LED+1);
}

void lightUpOneLedONLY(int LED) {
    PORTB = ~(1 << LED+1);
}

void lightUpMultipleLeds(uint8_t byte) {
    PORTB = byte;
}

void lightUpAllLeds() {
    PORTB = 0b00000000;
}

void lightDownOneLed(int LED) {
    PORTB |= (1 << LED+1);
}

void lightDownMultipleLeds(uint8_t byte) {
    PORTB = byte;
}

void lightDownAllLeds() {
    PORTB = 0b00111100;
}

void lightToggleOneLed(int LED) {
    PORTB |= (1 << LED+1);
}