/* Returns the length (size) of the passed array of type int */
#define getSizeOfArray(array) (sizeof(array) / sizeof(array[0]))

// initializes the ADC for input...
void initADC();