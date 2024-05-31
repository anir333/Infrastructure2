#include <avr/io.h>

#define LOW 0
#define HIGH 1
/* Define shift register pins used for seven segment display */
#define LATCH_DIO PD4
#define CLK_DIO PD7
#define DATA_DIO PB0

#define LSBFIRST 0
#define MSBFIRST 1
#define NUMBER_OF_SEGMENTS 8

#define sbi(register, bit) (register |= _BV(bit))
#define cbi(register, bit) (register &= ~_BV(bit))

void initDisplay();
void writeNumberToSegment(uint8_t segment, uint8_t value);
void writeNumber(int number);
void writeNumberAndWait(int number, int delay);
void writeNumberToSegmentAnir(uint8_t segment, uint8_t value);
void writeIntToSegmentAnir(uint8_t segment, uint8_t value);
void turnDisplayOFF();

/* My own: */
#define FIRST_DIGIT   0xF1
#define SECOND_DIGIT  0xF2
#define THIRD_DIGIT   0xF4
#define FOURTH_DIGIT  0xF8

#define ZERO   0xC0
#define ONE    0xF9
#define TWO    0xA4
#define THREE  0xB0
#define FOUR   0x99
#define FIVE   0x92 
#define SIX    0x82
#define SEVEN  0xF8
#define EIGHT  0x80
#define NINE   0x90

// int numbersAnir[11] = { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE };

#define A   0b10001000
#define B   0B10000011
#define C   0xC6
#define D   0xA1
#define E   0x86
#define F   0x8E
#define G   0xC2
#define H   0x89
#define I   0b11111001
#define J   0b11100001
#define K   0b10001111
#define L   0b11000111
#define M   0xA1
#define N   0b10001001
#define O   0xC8
#define P   0xC8
#define Q   0x92
#define R   0b10001000
#define S   0xC0
#define T   0xA4
#define U   0xC1
#define V   0xA1
#define W   0x8E
#define X   0xC6
#define Y   0x92
#define Z   0x89

void writeCharToSegment(uint8_t segment, char character);
void writeString(char* str);
void writeStringAndWait(char* str, int delay);

void blankSegment(uint8_t segment);

// const uint8_t NUMBERS[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE }; 
// const uint8_t LETTERS[] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};