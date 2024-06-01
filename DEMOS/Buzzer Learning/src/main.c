#include <avr/io.h>
#include <usart.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <buzzer.h>

//DURATION IS IN MILLISECONDS
#define DURATION 150

//FREQUENCIES OF THE NOTES
#define C5 523.250
#define D5 587.330
#define E5 659.250
#define F5 698.460
#define G5 783.990
#define A5 880.00
#define B5 987.770
#define C6 1046.500

int main()
{
  initUSART();
  float frequencies[] = { C5, D5, E5, F5, G5, A5, B5, C6 }; //do-re-mi...
  // // float frequencies[] = { 16.35, 118.35, 2220.60, 106.35, 2000.60, 221.83, 24.5, 201.83 };
  // enableBuzzer();
  enableBuzzerOnPORTC();
  // while (1) {
    for ( int note = 0; note < 8; note++ )
    {
      playToneForBuzzerOnPORTC( frequencies[note], DURATION );
      printf( "Period: %d\n", (int) frequencies[ note ] );
      _delay_ms( DURATION ); 
    }
  // }
  return 0;
}


// #include <avr/io.h>
// #include <util/delay.h>

// int main() {
//   DDRD |= ( 1 << PD3 );


//   for (uint32_t time = 0; time < 5000000; time += 1912) { 
//     //5 seconds is 5000000 microseconds
//     PORTD &= ~(1 << PD3);
//     _delay_us(956);//wait for half the period
//     PORTD |= (1 << PD3);//turn the buzzer off
//     _delay_us(956);//wait for the other half of the period
// }


//     return 0;
// }