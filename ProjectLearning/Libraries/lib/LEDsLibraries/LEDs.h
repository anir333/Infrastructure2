/* Pauses the program running for specified number of seconds */
void pauseSeconds(int seconds);

/* Disables all 4 LEDs => (for input => it overwrites current DDRB value and diables all LEDs) */
void disableAllLEDs(void);

/* 
Enables specified LED (does not overwrite => uses OR |) 
    DISCLAIMER: it doesn't let it light up once it is enabled, it makes sure it only enables it and that the LED's doesn't light up just because it was enabled, you should use the lightUpLeds functions to do so  */
void enableOneLed(int);

/* 
Enables LEDs specified in the binary byte provided (does not overwrite => uses OR |) 
    DISCLAIMER: it doesn't let them light up once they are enabled, it makes sure it only enables them and that the LED's don't light up just because they were enabled, you should use the lightUpLeds functions to do so */
void enableMultipleLeds(uint8_t); 

/* 
Enables all 4 LEDs => (for output => it overwrites current DDRB value and enables all LEDs) 
   DISCLAIMER: it doesn't let them light up once they are enabled, it makes sure it only enables them   and that the LED's don't light up just because they were enabled, you should use the lightUpLeds functions to do so */
void enableAllLeds();

/* Lights up specififed LED, (does not overwrite, so if other LEDs were lit up previously they will remain lit up) */
void lightUpOneLed(int);

/* Lights up specified LED => it overwrites previous PORTB so if any other LEDs were lit up they will be turned off and only the one specified will be lit up */
void lightUpOneLedONLY(int);

/* It lights up speccified LEDs (it overwrites previous PORTB) */
void lightUpMultipleLeds(uint8_t);

/* It overwrites previous PORTB and lights up all the LEDs */
void lightUpAllLeds(void); 

/* It lights down the specified LED (it doesn't overwrite, so if other LEDs were lit up they will stay on) */
void lightDownOneLed(int); 

/* Lights down specified LEDs */
void lightDownMultipleLeds (uint8_t);

/* It overwrites previous PORTB and lights down all the LEDs */
void lightDownAllLeds(void); 

/* It switches the current state of the specified LED (from OFF to ON and vivecersa) => It first saves the current state of PORTB, then it lights down he specified LED, then it checks if the current state of PORTB is the equal to the previous state of PORTB, (which means that the state of the specified LED hasn't been changed), if it is then it lights up the specidifed LED, if it's not then that means that the state of the LED has changed correctly so the LED has been toggled */
void lightToggleOneLed(int);

/* Dims the LED specified, the specified percentage, during the specified amount of time (lednumber, dimming percentage, duration in milliseconds) */
void dimLed(int, int, int);

/*  it's supposed to fade in the led but i haven't figured it out yet */
void fadeInLed(int, int);

/*  it's supposed out fade in the led but i haven't figured it out yet */
void fadeOutLed(int, int);

/* Function that makes the LEDs flash in a random pattern: randomly selected LEDs are switched on and off for arbitrarily long periods (between 100 and 1000 milliseconds */
void ledChaos(void);

/* It consecutevly lights up the LEDs */
void consecutiveLightUp(void);

/* Lights up the specified LED N number of times specified */
void lightUpOneLedNTimes(int led, int numberOfFlashes);

/* Makes the specified LED burn longer and longer starting at 10ms and incrementing by 50ms after every iteration untl reaching 100 ms */
void makeLedBurnLonger(int led);

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
void lightUpLedsBasedOnArrayOfChars(char string[], int size);

/* It creates a randomly generated string (with a random length from 1 to 10), containing the letters a, b, c or d;
    First it adds a ranodmly generated amount of times a random letter => (a, b, c, or d), then:
       - It iterates throught that string and lights up the LEDs X amount of times correspondingly (with a 1 second Pause for each iteration):  {
    'a' : ALL 4 LEDs light up ONCE;
    'b' : ALL 4 LEDs light up TWICE;
    'c' : ALL 4 LEDs light up THRICE;
    'd' : ALL 4 LEDs light up FOUR TIMES;
} */
void lightUpAllLedsBasedOnRandomStringXAmountOfTimes();