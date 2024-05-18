#include <stdio.h>
#include <string.h>
#include <usart.h>

typedef struct { // like defining a class in java
  int year;
  char model[10]; //remember 9 elements and a place reserved for the \0 zero byte at the end
  char type[10];
} CAR; // name of the type 

CAR car1; // car takes 22 bytes of memory, (chars take 1 byte each, ints take 2 bytes each)
CAR car3 = { 2005, "Toyota", "C4" };

int main() {
    initUSART();

    printf("CAR 3 TYPE: %s\n", car3.type);

    car1.year = 1998;
    printf("car year: %d\n", car1.year);
    car1.year = 1789;
    printf("car year: %d\n", car1.year);

    CAR newCar = { 1965, "Ford", "R4" };
    printf("NEW CAR: MODEL: %s,  YEAR: %d,  TYPE: %s", newCar.model, newCar.year, newCar.type);
    
    // copying a string to a variable (it takes each byte of the passed i n string and sets it to the variables)
    strcpy(newCar.model, "Scenic");
    printf("\nNew car model after copy: %s", newCar.model);


    /* 
    In Java, if you have, let's say, a class CAR and you make a variable:
      -> CAR car1 = new CAR();
      -> CAR car2 = car1;

    Then car2 and car1 reference the same object, so you have two references to the same object because they point to the same information in memory.

    But in C, it's not the same...
    When you have a struct CAR and you do:
      CAR car1;
      CAR car2 = car1;

    car2 is a copy of car1, so you have two separate objects. Changes to car1 do not affect car2 and vice versa.
    */


    return 0;
}