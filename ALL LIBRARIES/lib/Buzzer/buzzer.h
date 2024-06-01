#include <avr/io.h>
#include <usart.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

// initializes the buzzer for output
void enableBuzzer();

// calculates the period of the frequency to microseconds, calculates the duration in microseconds of the note to be played, turns on and off the buzzer at a half of the period calculated for the frequency during the duration specified in milliseconds
void playTone( float frequency, uint32_t duration );

// disables the buzzer
void disableBuzzer();

void enableBuzzerOnPORTC();

void disableBuzzerOnPORTC();

void playToneForBuzzerOnPORTC( float frequency, uint32_t duration );