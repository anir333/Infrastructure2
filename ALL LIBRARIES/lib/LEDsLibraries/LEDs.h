#include <stdbool.h>
#define LED_DDR DDRB
#define LED_PORT PORTB
#define NUMBER_OF_LEDS 4


/* Pauses the program running for specified number of seconds */
void pauseSeconds(int seconds);

/* Returns true if LED specified is ON or false if it's OFF */
bool isLEDon( int LEDnumber );

/* 
Enables specified LED (does not overwrite => uses OR |) 
    DISCLAIMER: the LED won't light up after enabling them, use the lightup methods to do so  */
void enableOneLed(int);

/* 
Enables LEDs specified in the binary byte provided (does not overwrite => uses OR |) 
   DISCLAIMER: the LEDs won't light up after enabling them, use the lightup methods to do so */
void enableMultipleLeds(uint8_t); 

/* 
Enables all 4 LEDs => (for output) 
   DISCLAIMER: the LEDs won't light up after enabling them, use the lightup methods to do so*/
void enableAllLeds();

/* Lights up specififed LED, (does not overwrite, so if other LEDs were lit up previously they will remain lit up) */
void lightUpOneLed(int);

// Turn on the specified LEDs by setting their corresponding bits to 0 if they were off, otherwise leave them unchanged
void lightUpMultipleLeds(uint8_t);

/* Lights up all the LEDs (without changing other pins state) */
void lightUpAllLeds(void); 

/* It lights down the specified LED (it doesn't overwrite, so if other LEDs were lit up they will stay on) */
void lightDownOneLed(int); 

/* Lights down specified LEDs */
// Turn off the specified LEDs by setting their corresponding bits to 1 if they were on, otherwise leave them unchanged
void lightDownMultipleLeds(uint8_t);

/* It lights down all the LEDs without changing the state of the other pins (it make ssure only the LEDs pins are set to 1) */
void lightDownAllLeds(void); 

/* It switches the current state of the specified LED (from OFF to ON and viceversa) => It first saves the current state of PORTB, then it lights down the specified LED, then it checks if the current state of PORTB is the equal to the previous state of PORTB, (which means that the state of the specified LED hasn't changed), if it is then it lights up the specidifed LED instead, thus changing the state of the LED, but if the current state of PORTB is not equal to the previous one, then that means that the state of the LED has changed correctly so the LED has been toggled */
void lightToggleOneLed(int);

/* Dims the LED specified, the specified percentage, during the specified amount of time (lednumber, dimming percentage, duration in milliseconds) */
void dimLed(int, int, long);

/*  Fades in led */
void fadeInLed(int, long);

/*  Fades out led */
void fadeOutLed(int, long);

/* Function that makes the LEDs flash in a random pattern: randomly selected LEDs are switched on and off for arbitrarily long periods (between 100 and 1000 milliseconds */
void ledChaos(void);

/* It consecutevly lights up the LEDs */
void consecutiveLightUp(void);

/* Lights up the specified LED N number of times specified */
void lightUpOneLedNTimes(int, int);

/* Makes the specified LED burn longer and longer starting at 10ms and incrementing by 50ms after every iteration untl reaching 100 ms */
void makeLedBurnLonger(int);

/* It walks through an array of randomly generated integers (from 1 to 4 corresponding to the LEDs) and lights up the corresponding LED for 500 ms */
void walkThroughArrayLightLed();

/* It creates an empty array and then fills it with random numbers from 10 to 1000 with a step value of 50 ms. Then it uses this array to light up a randomly selected led */
void randomDurationForRandomLed(void);

/*  It iterates through the string passed in and lights the corresponding LED (only) based on each letter: {
    'a' : (only) LED 1 lights up;
    'b' : (only) LED 2 lights up;
    'c' : (only) LED 3 lights up;
    'd' : (only) LED 4 lights up;
} */
void lightUpLedsBasedOnString(const char *letters);


/*  It iterates through the array of characters passed in and lights the corresponding LED (only) based on each letter: {
    'a' : (only) LED 1 lights up;
    'b' : (only) LED 2 lights up;
    'c' : (only) LED 3 lights up;
    'd' : (only) LED 4 lights up;
} */
void lightUpLedsBasedOnArrayOfChars(char string[], int);

/* It creates a randomly generated string (with a random length from 1 to 10), containing the letters a, b, c or d;
    First it adds a ranodmly generated amount of times a random letter => (a, b, c, or d), then:
       - It iterates throught that string and lights up the LEDs X amount of times correspondingly (with a 1 second Pause for each iteration):  {
    'a' : ALL 4 LEDs light up ONCE;
    'b' : ALL 4 LEDs light up TWICE;
    'c' : ALL 4 LEDs light up THRICE;
    'd' : ALL 4 LEDs light up FOUR TIMES;
} */
void lightUpAllLedsBasedOnRandomStringXAmountOfTimes();

/* Toggles up and down the led specified and waits for the duration specified (used to improve code readability in some of my methods) */
void lightUpAndDownLED(int, int);

/* Lights Up and Down all led's for specified duration of time (used to improve readability in my methods) */
void lightUpAndDownAllLEDs( int durationMS );

/* Lights up and down the specified LED with the specified duration on an infinite while loop */
void flashLight( int LEDnumber, int durationMS );