#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "display.h"
#include "usart.h"
#include <button.h>

volatile int counter = 0;
volatile int meters = 9999;
volatile int speed = 100;
volatile int fuel = 1500;

#define MULTIPLE 250


ISR ( PCINT1_vect ) {
    if(buttonPushed(1)) {
        speed = 50;    
    }
}

int main() {
    initDisplay();
    turnDisplayOFF();
    enableAllButtons();
    enableAllButtonInterrupts();
    initUSART();

    while (1) {
        writeNumberAndWait( meters, 1000 );
        meters -= speed;
        if ((meters <= 100) && (speed = 100)) {
            printf("\n\n\nThe Lunar Lander Crashed!\n\n\n");
            break;
        } else if ((meters <= 100) && (speed = 50)) {
            printf("\n\n\nThe Lunar Lander Landed Safely!\n\n\n");
            break;
        }
        if (buttonPushed(1)) speed = 50; else speed = 100;
    };

    return 0;
}