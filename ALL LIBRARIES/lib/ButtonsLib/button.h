#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define LOW 0
#define HIGH 1
#define BUTTON_DDR DDRC
#define BUTTON_PORT PORTC
#define BUTTON_PIN PINC
#define FIRST_PIN PC0
#define INTERRUPT_BUTTONS PCICR
#define CONTROL_REGISTER_BUTTONS PCIE1
#define MASK_BUTTONS PCMSK1
#define activateInterruptSystemGlobally sei();
#define BUTTON_ONE   1
#define BUTTON_TWO   2
#define BUTTON_THREE 3

/* Writes specified 8 bit mask to specified register (using its memory address and RAM location) */
void writeMask( volatile uint8_t* registr, uint8_t bitmask );

// Function to write value (LOW or HIGH) to a specific digital pin on a specific register (useful to activate the pull-up resistance)
void writePin(volatile uint8_t *regist, uint8_t pin, uint8_t value);

/* Sets data directiong register of button (to 0) for input and activates the pull-up resistor */
void enableButton( int button );

/* enableButton() for buttons 1, 2 & 3 */
void enableAllButtons();

/* Checks if bit is clear on specified button */
int buttonPushed( int button );

/* Checks if buttons is not pushed */
int buttonReleased( int button );

/* It activates the interrupt for PCICR for the Buttons Port (PCIE1), then it it indicates the pin of the specified button in PORTC to activate the ISR, and finally it enables the interrupts and activates the interrupt system globally. */ 
int enableButtonInterrupt( int button );

/* enableButtonInterrupt() for buttons 1, 2 & 3 */
void enableAllButtonInterrupts();