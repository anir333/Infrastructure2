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
void lightUpAllLeds(); 

/* It lights down the specified LED (it doesn't overwrite, so if other LEDs were lit up they will stay on) */
void lightDownOneLed(int); 

/* Lights down specified LEDs */
void lightDownMultipleLeds (uint8_t);

/* It overwrites previous PORTB and lights down all the LEDs */
void lightDownAllLeds (); 

/* It switches the current state of the specified LED (from OFF to ON and vivecersa) */
void lightToggleOneLed(int);