#include <avr/io.h>
#include <usart.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

// DURATION IS IN MILLISECONDS
#define SHORT_DURATION 100
#define LONG_DURATION 300
#define REST_DURATION 50

// FREQUENCIES OF THE NOTES
#define C5 523.250
#define D5 587.330
#define E5 659.250
#define F5 698.460
#define G5 783.990
#define A5 880.00
#define B5 987.770
#define C6 1046.500

void enableBuzzer()
{
    DDRD |= (1 << PD3); // Buzzer is connected to PD3
}

void playTone(float frequency, uint32_t duration)
{
    uint32_t periodInMicro = (uint32_t)(1000000 / frequency); // Calculate the period in microsecs from the freq
    uint32_t durationInMicro = duration * 1000; // We express duration in microsecs
    for (uint32_t time = 0; time < durationInMicro; time += periodInMicro)
    {
        PORTD &= ~(1 << PD3); // Turn the buzzer on
        _delay_us(periodInMicro / 2); // Wait for half of the period
        PORTD |= (1 << PD3); // Turn the buzzer off
        _delay_us(periodInMicro / 2); // Wait again for half of the period
    }
}

void playRest(uint32_t duration)
{
    _delay_ms(duration);
}

void playCoolSong()
{
    // A rap-inspired beat with a mix of short and long notes
    float melody[] = { C5, D5, E5, G5, E5, D5, C5, G5, C6, A5, G5, E5, F5, D5, C5, G5 };
    uint32_t durations[] = { SHORT_DURATION, SHORT_DURATION, LONG_DURATION, SHORT_DURATION, SHORT_DURATION, LONG_DURATION, SHORT_DURATION, SHORT_DURATION,
                             SHORT_DURATION, LONG_DURATION, SHORT_DURATION, SHORT_DURATION, LONG_DURATION, SHORT_DURATION, SHORT_DURATION, LONG_DURATION };

    for (int note = 0; note < sizeof(melody) / sizeof(melody[0]); note++)
    {
        playTone(melody[note], durations[note]);
        playRest(REST_DURATION); // Adding a rest between notes
        printf("Playing frequency: %d\n", (int)melody[note]);
    }
}

int main()
{
    initUSART();
    enableBuzzer();
    playCoolSong(); // Play the cool song
    return 0;
}



// #include <avr/io.h>
// #include <usart.h>
// #define __DELAY_BACKWARD_COMPATIBLE__
// #include <util/delay.h>

// // DURATION IS IN MILLISECONDS
// #define DURATION 200
// #define REST_DURATION 100
// #define ALARM_REPEAT 5

// // FREQUENCIES OF THE NOTES
// #define C5 523.250
// #define G4 392.00

// void enableBuzzer()
// {
//     DDRD |= (1 << PD3); // Buzzer is connected to PD3
// }

// void playTone(float frequency, uint32_t duration)
// {
//     uint32_t periodInMicro = (uint32_t)(1000000 / frequency); // Calculate the period in microsecs from the freq
//     uint32_t durationInMicro = duration * 1000; // We express duration in microsecs
//     for (uint32_t time = 0; time < durationInMicro; time += periodInMicro)
//     {
//         PORTD &= ~(1 << PD3); // Turn the buzzer on
//         _delay_us(periodInMicro / 2); // Wait for half of the period
//         PORTD |= (1 << PD3); // Turn the buzzer off
//         _delay_us(periodInMicro / 2); // Wait again for half of the period
//     }
// }

// void playRest(uint32_t duration)
// {
//     _delay_ms(duration);
// }

// void playAlarm()
// {
//     // Simple alarm sound using C5 and G4
//     float alarmMelody[] = { C5, G4 };
//     uint32_t alarmDurations[] = { DURATION, DURATION };

//     for (int repeat = 0; repeat < ALARM_REPEAT; repeat++)
//     {
//         for (int note = 0; note < sizeof(alarmMelody) / sizeof(alarmMelody[0]); note++)
//         {
//             playTone(alarmMelody[note], alarmDurations[note]);
//             playRest(REST_DURATION); // Adding a rest between notes
//             printf("Playing frequency: %d\n", (int)alarmMelody[note]);
//         }
//         playRest(500); // Adding a longer rest between repeats
//     }
// }

// int main()
// {
//     initUSART();
//     enableBuzzer();
//     playAlarm(); // Play the alarm sound
//     return 0;
// }


// #include <avr/io.h>
// #include <usart.h>
// #define __DELAY_BACKWARD_COMPATIBLE__
// #include <util/delay.h>

// // DURATION IS IN MILLISECONDS
// #define DURATION 150
// #define REST_DURATION 50

// // FREQUENCIES OF THE NOTES
// #define C5 523.250
// #define D5 587.330
// #define E5 659.250
// #define F5 698.460
// #define G5 783.990
// #define A5 880.00
// #define B5 987.770
// #define C6 1046.500

// void enableBuzzer()
// {
//     DDRD |= (1 << PD3); // Buzzer is connected to PD3
// }

// void playTone(float frequency, uint32_t duration)
// {
//     uint32_t periodInMicro = (uint32_t)(1000000 / frequency); // Calculate the period in microsecs from the freq
//     uint32_t durationInMicro = duration * 1000; // We express duration in microsecs
//     for (uint32_t time = 0; time < durationInMicro; time += periodInMicro)
//     {
//         PORTD &= ~(1 << PD3); // Turn the buzzer on
//         _delay_us(periodInMicro / 2); // Wait for half of the period
//         PORTD |= (1 << PD3); // Turn the buzzer off
//         _delay_us(periodInMicro / 2); // Wait again for half of the period
//     }
// }

// void playRest(uint32_t duration)
// {
//     _delay_ms(duration);
// }

// int main()
// {
//     initUSART();
//     enableBuzzer();

//     // A simple melody: "Ode to Joy" (first few notes)
//     float melody[] = { E5, E5, F5, G5, G5, F5, E5, D5, C5, C5, D5, E5, E5, D5, D5 };
//     uint32_t durations[] = { DURATION, DURATION, DURATION, DURATION, DURATION, DURATION, DURATION, DURATION, DURATION, DURATION, DURATION, DURATION, DURATION, DURATION, DURATION };

//     for (int note = 0; note < sizeof(melody)/sizeof(melody[0]); note++)
//     {
//         playTone(melody[note], durations[note]);
//         playRest(REST_DURATION); // Adding a rest between notes
//         printf("Playing frequency: %d\n", (int)melody[note]);
//     }

//     return 0;
// }


// #include <avr/io.h>
// #include <usart.h>
// #define __DELAY_BACKWARD_COMPATIBLE__
// #include <util/delay.h>

// //DURATION IS IN MILLISECONDS
// #define DURATION 150

// //FREQUENCIES OF THE NOTES
// #define C5 523.250
// #define D5 587.330
// #define E5 659.250
// #define F5 698.460
// #define G5 783.990
// #define A5 880.00
// #define B5 987.770
// #define C6 1046.500

// void enableBuzzer()
// {
//    DDRD |= ( 1 << PD3 ); //Buzzer is connected to PD3
// }

// void playTone( float frequency, uint32_t duration )
// {
//    uint32_t periodInMicro = ( uint32_t ) ( 1000000 / frequency ); //Calculate the period in microsecs from the freq
//    uint32_t durationInMicro = duration * 1000; //We express duration in microsecs
//    for ( uint32_t time = 0; time < durationInMicro; time += periodInMicro ) //See tutorial on Music for more info!
//     {
//     PORTD &= ~( 1 << PD3 ); //turn the buzzer on
//     _delay_us( periodInMicro / 2 ); //Wait for the half of the period
//     PORTD |= ( 1 << PD3 ); //Turn the buzzer off
//     _delay_us( periodInMicro / 2 ); //Wait again for half of the period
//     }
// }

// int main()
// {
// initUSART();
// float frequencies[] = { C5, D5, E5, F5, G5, A5, B5, C6 }; //do-re-mi...
// enableBuzzer();
// for ( int note = 0; note < 8; note++ )
//  {
//   playTone( frequencies[note], DURATION );
//   printf( "Period: %d\n", (int) frequencies[ note ] );
//   _delay_ms( DURATION ); 
//  }
// return 0;
// }