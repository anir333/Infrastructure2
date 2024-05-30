#include "display.h"
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define SPACE 0xFF

/* Segment byte maps for numbers 0 to 9 */
const uint8_t SEGMENT_MAP[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99,
                               0x92, 0x82, 0xF8, 0X80, 0X90};

/* Byte maps to select digit 1 to 4 */
const uint8_t SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};

const uint8_t ALPHABET_MAP[] = {0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 0xC2,
                                0x89, 0xCF, 0xE1, 0x8A, 0xC7, 0xEA, 0xC8,
                                0xC0, 0x8C, 0x4A, 0xCC, 0x92, 0x87, 0xC1,
                                0xC1, 0xD5, 0x89, 0x91, 0xA4};


void initDisplay() {
  sbi(DDRD, LATCH_DIO);
  sbi(DDRD, CLK_DIO);
  sbi(DDRB, DATA_DIO);
}

// loop through seven segments of LED display and shift the correct bits in the
// data register
void shift(uint8_t val, uint8_t bitorder) {
  uint8_t bit;

  for (uint8_t i = 0; i < NUMBER_OF_SEGMENTS; i++) {
    if (bitorder == LSBFIRST) {
      bit = !!(val & (1 << i));
    } else {
      bit = !!(val & (1 << (7 - i)));
    }
    // write bit to register
    if (bit == HIGH)
      sbi(PORTB, DATA_DIO);
    else
      cbi(PORTB, DATA_DIO);

    // Trigger the clock pin so the display updates
    sbi(PORTD, CLK_DIO);
    cbi(PORTD, CLK_DIO);
  }
}

//Writes a digit to a certain segment. Segment 0 is the leftmost.
void writeNumberToSegment(uint8_t segment, uint8_t value) {
  cbi(PORTD, LATCH_DIO);
  shift(SEGMENT_MAP[value], MSBFIRST);
  shift(SEGMENT_SELECT[segment], MSBFIRST);
  sbi(PORTD, LATCH_DIO);
}

//Writes a nuber between 0 and 9999 to the display. To be used in a loop...
void writeNumber(int number) {
  if (number < 0 || number > 9999) return;
  writeNumberToSegment(0, number / 1000);
  writeNumberToSegment(1, (number / 100) % 10);
  writeNumberToSegment(2, (number / 10) % 10);
  writeNumberToSegment(3, number % 10);
}

//Writes a number between 0 and 9999 to the display and makes sure that it stays there a certain number of millisecs.
//Note: the timing is approximate; the amount of time writeNumberToSegment takes is not accounted for...
void writeNumberAndWait(int number, int delay) {
  if (number < 0 || number > 9999) return;
  for (int i = 0; i < delay / 20; i++) {
    writeNumberToSegment(0, number / 1000);
    _delay_ms(5);
    writeNumberToSegment(1, (number / 100) % 10);
    _delay_ms(5);
    writeNumberToSegment(2, (number / 10) % 10);
    _delay_ms(5);
    writeNumberToSegment(3, number % 10);
    _delay_ms(5);
  }
}


void writeNumberToSegmentAnir(uint8_t segment, uint8_t value) {
  cbi(PORTD, LATCH_DIO);
  shift(value, MSBFIRST);
  shift(segment, MSBFIRST);
  sbi(PORTD, LATCH_DIO);
}

void turnDisplayOFF() {
    writeNumberToSegmentAnir( FIRST_DIGIT, SPACE );
    _delay_ms(1);
    writeNumberToSegmentAnir( SECOND_DIGIT, SPACE );
    _delay_ms(1);
    writeNumberToSegmentAnir( THIRD_DIGIT, SPACE );
    _delay_ms(1);
    writeNumberToSegmentAnir( FOURTH_DIGIT, SPACE );
    _delay_ms(1);
}

void writeCharToSegment(uint8_t segment, char character) {
  if ( character >= 'a' && character <= 'z' ) {
    character -= 32;
  }
  
  if ( character >= 'A' && character <= 'Z' ) {
    writeNumberToSegmentAnir( segment, ALPHABET_MAP[character-65]);
  } else {
      writeNumberToSegment( segment, SPACE );
  } 
}

void writeString(char* str) {
  for (int i = 0; i < 4; i++) {
      int segment = i == 0 ? FIRST_DIGIT : ( i == 1 ? SECOND_DIGIT : (i == 2 ? THIRD_DIGIT : (i == 3 ? FOURTH_DIGIT : 0)) );
      writeCharToSegment( segment, *str);
      str++;
  }
}

void writeStringAndWait(char* str, int delay) {
  int time = delay * 3;
  for (int i = 0; i < time; i++) {
    writeString(str);
  }
}

// Blanks a certain segment. Segment 0 is the leftmost.
void blankSegment(uint8_t segment)
{
  cbi(PORTD, LATCH_DIO);
  shift(0xFF, MSBFIRST);
  shift(SEGMENT_SELECT[segment], MSBFIRST);
  sbi(PORTD, LATCH_DIO);
}