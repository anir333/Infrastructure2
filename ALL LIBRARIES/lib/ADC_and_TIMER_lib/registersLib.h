/* Returns the length (size) of the passed array of type int */
#define getSizeOfArray(array) (sizeof(array) / sizeof(array[0]))

// initializes the ADC for input...
void initADC();

// Standard timer 0 initialisation
void initTimer0();

// Initialise TIMER 0 (TCCR0A register) with Fast Pulse With Modulation (PWM) -> the counter (TCNT0) counts form 0 to 255 and then it resets to 0 and continues counting. Then it determines the speed of the timer by setting a prescaler (Clock speed of Atmega238p microcontroller is 16 MHz which is too high). It sets the CS02 and CS00 prescaler of TCCROB control register for timer 0 to 1, in order to set the prescaler factor to 1024
void initTIMER0();

// It enables the timer interrupts so that the microcontroller can execute specific code when certain timer conditions are met, it first enables the overflow interrupt for Interrupt Mask Register for Timer 0, then it enables the output compare match A interrupt, and finally it set the global interrput flag
void enableTimer0Interrput();