#include <stdio.h>

#define LOW 0
#define HIGH 1

/* Writes specified 8 bit mask to specified register (using its memory address and RAM location) */
void writeMask( volatile uint8_t* registr, uint8_t bitmask );

// Function to write value (LOW or HIGH) to a specific digital pin on a specific register (useful to activate the pull-up resistance)
void writePin(volatile uint8_t *regist, uint8_t pin, uint8_t value);