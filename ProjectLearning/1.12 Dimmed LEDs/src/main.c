// // // to allow variables as parameter for the _delay-functions (must be placed before the include of delay.h)
#define __DELAY_BACKWARD_COMPATIBLE__  
#include <util/delay.h>
#include <avr/io.h>
#include <LEDs.h>
#include <usart.h>
// #include <stdio.h>
// #include <time.h>

int main() {
  initUSART();
  enableAllLeds();
  // lightUpAllLeds();
  // lightUpOneLed(1);

  dimLed(2, 99, 5);

// only dim workf not fade

  // dimLed(3, 99, 5);
  // dimLed(1, 99, 2);
  // fadeInLed(3, 5);
  // fadeOutLed(4, 50);


  return 0;
}


// #include <stdio.h>
// #include <time.h>

// int main() {
//     time_t start_time, end_time;
//     double duration;

//     start_time = time(NULL);
//     printf("Current time: %ld\n", start_time);

//     // Your code to perform some operation or wait for a duration
//     for (int i = 0; i < 10000000; i++) {
//         // Simulating a time-consuming operation
//         printf("%d\n", i);
//     }

//     end_time = time(NULL);
//     printf("Finished counting at: %ld\n", end_time);

//     // Calculate duration
//     duration = difftime(end_time, start_time);
//     printf("Duration: %.2f seconds\n", duration);

//     return 0;
// }



// this makes the alarm go offif you hcange the ports and data directiosn to D:

// #include <avr/io.h>
// #include <util/delay.h>

// #define __DELAY_BACKWARD_COMPATIBLE__
// #include <util/delay.h>

// void dimLed(int lednumber, int percentage, int duration) {
//     int onTime = (percentage * duration) / 100;
//     int offTime = duration - onTime;
    
//     for (;;) {
//       printf("hello");
//         // Turn on LED
//         PORTB |= (1 << lednumber);
//         _delay_ms(onTime);
        
//         // Turn off LED
//         PORTB &= ~(1 << lednumber);
//         _delay_ms(offTime);
//     }
// }

// void fadeInLed(int led, int duration) {
//     for (int i = 0; i <= 100; i++) {
//         dimLed(led, i, duration / 100);
//         _delay_ms(200);
//     }
// }

// void fadeOutLed(int led, int duration) {
//     for (int i = 100; i >= 0; i--) {
//         dimLed(led, i, duration / 100);
//         _delay_ms(200);
//     }
// }

// int main() {
//   initUSART();
//     // Setup LED pin as output
//     DDRB |= (1 << 3); // Assuming LED is connected to PD0
    
//     // Test dimming
//     dimLed(3, 50, 10); // Dim LED on PD0 to 50% brightness for 1 second
    
//     // Test fading in
//     fadeInLed(3, 5000); // Fade in LED on PD0 over 5 seconds
    
//     // Test fading out
//     fadeOutLed(3, 5000); // Fade out LED on PD0 over 5 seconds
    
//     return 0;
// }
