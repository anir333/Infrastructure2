#include <button.h>
#include <stdio.h>

void writeMask( volatile uint8_t* registr, uint8_t value  ) {
    *registr = value;
}

void writePin(volatile uint8_t *regist, uint8_t pin, uint8_t value) {
    if (value == LOW) {
        *regist &= ~(1 << pin); // Clear the bit corresponding to the pin
    } else {
        *regist |= (1 << pin);  // Set the bit corresponding to the pin
    }
}