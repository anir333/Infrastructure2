#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <LEDs.h>

int main() {
  ledChaos();

  return 0;
}





// // // testing random number generator

// #include <stdio.h>
// #include <stdlib.h>

// int main () {

//     int randomNumber = rand() % 901 + 100;

//     int numbers[10000];


//     for (int i = 0; i<10000; i++) {
//       // int randomLedGenerated = rand() % 4 + 1;
//       // printf("%d\n", randomLedGenerated);
//       int randomDurationInMiliseconds = rand() % 901 + 100;
//       numbers[i] = randomDurationInMiliseconds;
//       // printf("%d\n", randomDurationInMiliseconds);
//     }

    
//     int largest = numbers[0];
//     int smallest = numbers[0];

//     // Iterate through the array to find the largest and smallest numbers
//     for (int i = 1; i < 10000; i++) {
//         if (numbers[i] > largest) {
//             largest = numbers[i];
//         }
//         if (numbers[i] < smallest) {
//             smallest = numbers[i];
//         }
//     }
//     printf("Largest number: %d\n", largest);
//     printf("Smallest number: %d\n", smallest);
// }  