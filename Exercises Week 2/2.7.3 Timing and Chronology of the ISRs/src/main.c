#include <button.h>

ISR( PCINT1_vect ) {
    if (buttonPushed(1)) {
        while (1) {
            lightUpOneLed(2);
            lightUpOneLed(3);
            pauseSeconds(5);
            lightDownOneLed(2);
            lightDownOneLed(3);
            pauseSeconds(5);
        }
    } 
    if (buttonPushed(2)) {
        while (1) {
            lightUpOneLed(2);
            _delay_ms(500);
            lightDownOneLed(2);
            _delay_ms(500);
        }
    }
}

int main() {
    initUSART();
    enableAllLeds();

    enableButton(1);
    activateInterrumptForButton(1, false);
    enableButton(2);
    activateInterrumptForButton(2, false);

    while (1) {
        lightUpOneLed(1);
        lightUpOneLed(2);
        pauseSeconds(2);
        lightDownOneLed(1);
        lightDownOneLed(2);
        pauseSeconds(2);
    }
}

/* 
Part 1 - Questions:
    - Does LED D1 continue to flash when the ISR has started?
        No, LED D1 does not continue to flash when the ISR has started.

    - Does LED D1 and D2 continue to flash after the ISR has been handled (ie is it over)?
        They don't continue to flash together, yes their while loop is over.

    - If LED D1 and D2 were on before starting the ISR, are they still on after running the ISR?
        - Yes.

    - If LED D1 and D2 were off before starting the ISR, are they still off after running the ISR?
        - Only one since we turn on LED 2 to start the second cycle.

    - If LEDs D1 and D2 were on for only 0.5 seconds before starting the ISR, will they keep their status for 1.5 seconds after performing the ISR?
        - LED one will keep its status forever on.

Part 2- Questions:
    - Activate the functionality associated with button S2 after starting the program.
    - How does this affect the execution of the program?
        When button 2 clicked, it activates the functionality of ISR associated with the button, but it it won't let other buttons associations work.

    - Activate the functionality associated with button S2 during the execution of the ISR associated with pressing button S1. How does this affect the execution of the program / the ISR?
        The functionality associated with button 2 doesn't execute if the button 1 was clicked first.
 */