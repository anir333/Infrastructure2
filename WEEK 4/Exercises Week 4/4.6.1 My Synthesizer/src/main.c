#include <LEDs.h>
#include <registersLib.h>
#include <usart.h>
#include <button.h>
#include <avr/io.h>
#include <display.h>
#include <buzzer.h>

#define TRUE 1
#define FALSE 0

volatile int playing = FALSE;

ISR(PCINT1_vect) {
    if (buttonPushed(1) || buttonPushed(2) || buttonPushed(3)) {
        if (!playing) {
            playing = TRUE;
            enableBuzzer();
        } else {
            playing = FALSE;
            disableBuzzer();
        }
    }
}

int main() {
    initUSART();
    enableAllLeds();
    enableAllButtons();
    enableAllButtonInterrupts();
    initADC();
    initDisplay();
    turnDisplayOFF();

    // int counter = 0;
    // uint16_t frequency = ADC;

    while (TRUE) {
        // counter++;
        // printf("it: %d\n", counter);
        
        if (playing) {
            playTone(ADC, 150);
        }
        
        writeNumber(ADC);
    }

    return 0;
}
