#include <button.h>
#include <stdio.h>
#include <avr/io.h>

void writeMask(volatile uint8_t *registr, uint8_t value) {
    *registr = value;
}

void writePin(volatile uint8_t *regist, uint8_t pin, uint8_t value) {
    if (value == LOW) {
        *regist &= ~(1 << pin); // Clear the bit corresponding to the pin
    } else if (value == HIGH) {
        *regist |= (1 << pin); // Set the bit corresponding to the pin
    }
}

void enableButton(int button) {
       if (button < 1 || button > 3) return;

    BUTTON_DDR &= ~_BV(FIRST_PIN + button);

    BUTTON_PORT |= _BV(FIRST_PIN + button);
}

void enableAllButtons() {
    enableButton(1);
    enableButton(2);
    enableButton(3);
}

int buttonPushed(int button) {
       if (button < 1 || button > 3) return;
    
    if (bit_is_clear(BUTTON_PIN, (FIRST_PIN + button))) {
        _delay_us(500); // debouncing
    } return bit_is_clear(BUTTON_PIN, (FIRST_PIN + button));
}

int buttonReleased(int button) {
        if (button < 1 || button > 3) return 0;

    if ( !buttonPushed(button) ) {
        printf("\nBUTTON RELEASED!\n");
    } return !buttonPushed(button);
}


int enableButtonInterrupt( int button ) {
       if (button < 1 || button > 3) return 0;

    enableButton(button);

    INTERRUPT_BUTTONS |= _BV( CONTROL_REGISTER_BUTTONS );

    MASK_BUTTONS |= _BV( FIRST_PIN + button );

    activateInterruptSystemGlobally;
}

void enableAllButtonInterrupts() {
    enableButtonInterrupt(1);
    enableButtonInterrupt(2);
    enableButtonInterrupt(3);
}