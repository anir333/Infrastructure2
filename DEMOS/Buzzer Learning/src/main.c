#include <avr/io.h>
#include <usart.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <buzzer.h>

// FREQUENCIES OF THE NOTES
#define C4 261.63
#define D4 293.66
#define E4 329.63
#define F4 349.23
#define G4 392.00
#define A4 440.00
#define B4 493.88
#define C5 523.250
#define D5 587.330
#define E5 659.250
#define F5 698.460
#define G5 783.990
#define A5 880.00
#define B5 987.770
#define C6 1046.500


// Melody (50 notes)

float melody[50] = {
    C5, D5, E5, F5, G5, A5, B5, C6, C5, D5,
    E5, F5, G5, A5, B5, C6, C5, D5, E5, F5,
    G5, A5, B5, C6, C5, D5, E5, F5, G5, A5,
    B5, C6, C5, D5, E5, F5, G5, A5, B5, C6,
    C5, D5, E5, F5, G5, A5, B5, C6, C5, D5
};

float melody[50] = {
    C5, E5, G5, C6, B5, A5, G5, F5, E5, D5,
    C5, G5, E5, C5, G5, A5, B5, C6, D5, E5,
    F5, E5, D5, C5, B4, A4, G4, F4, E4, D4,
    C4, E4, G4, A4, G4, F4, E4, D4, C4, B4,
    C5, E5, G5, C6, B5, A5, G5, F5, E5, D5
};

float melody[50] = {
    C5, E5, G5, C6, B5, A5, G5, F5, E5, D5,
    C5, G5, E5, C5, G5, A5, B5, C6, D5, E5,
    F5, E5, D5, C5, B4, A4, G4, F4, E4, D4,
    C4, E4, G4, A4, G4, F4, E4, D4, C4, B4,
    C5, E5, G5, C6, B5, A5, G5, F5, E5, D5
};

float melody[50] = {
    E5, D5, C5, D5, E5, E5, E5, D5, D5, D5,
    E5, G5, G5, E5, D5, C5, D5, E5, E5, E5,
    D5, D5, E5, D5, C5, D5, D5, D5, D5, E5,
    D5, C5, B4, C5, D5, E5, D5, C5, D5, E5,
    E5, E5, D5, D5, D5, E5, G5, G5, E5, D5
};

float melody[50] = {
    G4, A4, B4, C5, D5, E5, F5, G5, F5, E5,
    D5, C5, B4, A4, G4, F4, E4, D4, C4, B4,
    A4, G4, F4, E4, D4, C4, B4, A4, G4, F4,
    E4, D4, C4, B4, A4, G4, F4, E4, D4, C4,
    B4, A4, G4, F4, E4, D4, C4, B4, C5, D5
};






// Duration for each note
#define NOTE_DURATION 150

int main()
{
    initUSART();
    enableBuzzerOnPORTC();

    for (int note = 0; note < 50; note++)
    {
        playToneForBuzzerOnPORTC(melody[note], NOTE_DURATION);
        printf("Note: %.2f\n", melody[note]);
        _delay_ms(NOTE_DURATION);
    }
    
    return 0;
}
