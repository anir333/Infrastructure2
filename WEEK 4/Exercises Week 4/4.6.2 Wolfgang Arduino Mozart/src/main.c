#include <avr/io.h>
#include <stdlib.h>
#include <usart.h>
#include <button.h>
#include <display.h>
#include <buzzer.h>
#include <string.h>
#include <stdio.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

typedef struct {
    float frequency;
    uint16_t duration;
} NOTE;

typedef struct {
    char* name;
    NOTE** notes; // List of NOTE*
    uint16_t length;
} SONG;

// Function prototypes
void playSong(SONG* song);
SONG* generateSong(char* name, uint16_t length);
void playNote (NOTE* note);
void delay_ms(uint16_t ms);

int main() {
    initUSART();
    enableAllButtons();
    enableAllButtonInterrupts();
    enableBuzzer();
    
    // Seed the random number generator
    srand(ADC);

    // Wait until button 1 is pressed
    while (!buttonPushed(1)) {
        // Do nothing, just wait
    }

    // Generate a random song
    SONG* song = generateSong("Random Tune", 10);

    // Play the song 4 times
    for (int i = 0; i < 4; i++) {
        playSong(song);
    }

    // Free allocated memory
    for (uint16_t i = 0; i < song->length; i++) {
        free(song->notes[i]);
    }
    free(song->notes);
    free(song->name);
    free(song);

    return 0;
}

void playSong(SONG* song) {
    for (uint16_t i = 0; i < song->length; i++) {
        playNote(song->notes[i]);
    }
}

SONG* generateSong(char* name, uint16_t length) {
    SONG* song = malloc(sizeof(SONG));
    song->length = length;
    song->name = malloc(strlen(name) + 1);
    strcpy(song->name, name);
    song->notes = malloc(length * sizeof(NOTE*));

    float frequencies[] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88}; // C4, D4, E4, F4, G4, A4, B4
    uint16_t durations[] = {1000, 500, 250};

    for (uint16_t i = 0; i < length; i++) {
        song->notes[i] = (NOTE*)malloc(sizeof(NOTE));
        song->notes[i]->frequency = frequencies[rand() % 7];
        song->notes[i]->duration = durations[rand() % 3];
    }

    return song;
}

void playNote (NOTE* note) {
    if (note->frequency == 0) {
        delay_ms(note->duration);
    } else {
        playTone(note->frequency, note->duration);
    }
}

void delay_ms(uint16_t ms) {
    while (ms--) {
        _delay_ms(1);
    }
}



// #include <stdio.h> // contians types utin16_t...
// #include <buzzer.h>
// #include <string.h>

// typedef struct {
//   float frequency;
//   uint16_t duration;  
// } NOTE;

// typedef struct {
//   char* name;
//   NOTE** note;
//   uint16_t length;
// } SONG;

// int main() {

//     return 0;
// }

// void playNote(NOTE* note) {
//   enableBuzzer();
//   playTone(note->frequency, (*note).duration);
//   disableBuzzer();
// }

// SONG* generateSong(char* name, uint16_t length) {
//   SONG* song = malloc(sizeof(SONG));
//   song -> length = rand() % 350 + 100;
//   song -> name = malloc(sizeof("NewSong")+1);
//   strcpy(song->name, "NewSong");

// }