#include <button.h>
#include <stdio.h>
#include <avr/io.h>
#include <LEDs.h>


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
    initUSART();
    if (button < 1 || button > 3) return;
    
    BUTTON_DDR &= ~_BV(FIRST_PIN + button);
    BUTTON_PORT |= _BV(FIRST_PIN + button);

    printf("\n\nButton %d enabled and pull-up resistor activated\n", button);
}

int buttonPushed(int button) {
    initUSART();
    if (button < 1 || button > 3) return 0;
    
    if (bit_is_clear(BUTTON_PIN, (FIRST_PIN + button))) {
        printf("\nBUTTON %d PUSHED\n", button);
    } return bit_is_clear(BUTTON_PIN, (FIRST_PIN + button));
}

int buttonReleased(int button) {
    if (button < 1 || button > 3) return 0;

    if ( !buttonPushed(button) ) {
        printf("\nBUTTON RELEASED!\n");
    } return !buttonPushed(button);
}

int activateInterrumptForButton( int button ) {
    printf("\n\nActivating PCICR for PCIE1: ");
    INTERRUPT_BUTTONS |= _BV( CONTROL_REGISTER_BUTTONS );
    printBinaryByte(INTERRUPT_BUTTONS);

    printf("\nActivating pin of button %d to activate the ISR: ", button);
    MASK_BUTTONS |= _BV( FIRST_PIN + button );
    printBinaryByte(MASK_BUTTONS);

    printf("\nActivating interrumpt system globally...");
    activateInterruptSystemGlobally;
    printf("\n -> sie activated globally");
}
