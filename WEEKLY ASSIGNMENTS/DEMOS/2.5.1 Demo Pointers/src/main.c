// #include <util/delay.h>
// #include <avr/io.h>
// #include <usart.h>
#include <stdio.h>

void increment_byref( int* a)
{
    printf( "Incrementing a (%d)\n", *a);
    (*a)++;
}

void increment_byval( int a )
{
    printf( "Incrementing a (%d)\n", a );
    a++;
}

void array_as_parameter( int* p )
{
    //how large is the array in bytes?
    printf( "sizeof array as parameter: %d\n" , sizeof( p ));
}

int main()
{
    // initUSART();
    int a = 10;
    int* b = &a;
    int c[] = { 1,2,3 };
    int d[] = { 1,2,3,4,5,6 };

    // print the value of a
    printf( "Value of a: %d\n", a );
    // how many bytes does an int take up?
    printf( "sizeof a: %d\n", sizeof( a ));
    // In what memory address is a stored (in hex)?
    // (you could use %d if you wanted to see the address in decimal, but ignore the warning then...)
    printf( "Value of &a: %p\n", &a );
    // b has the address of a
    printf( "Value of b: %p\n", b );
    //how large is b (how large is an int pointer)?
    printf( "sizeof b: %d\n", sizeof( b ));
    // And what is the address of b itself?
    printf( "Value of &b: %p\n", &b );
    // An array is actually a pointer to the first element...
    printf( "Value of c: %p\n", c );
    // So, an array is the address of the first element...
    printf( "Value of &c[0]: %p\n", &c[0] );
    // What's the size of the array in bytes?
    printf( "sizeof c: %d\n", sizeof( c ));
    // Pass the array as a parameter
    array_as_parameter( c );
    printf( "Value of d: %p\n", d );
    printf( "sizeof d: %d\n", sizeof( d ));
    increment_byval( a );
    printf( "Value of a after by val increment: %d\n", a );
    increment_byref( &a );
    printf( "Value of a after by ref increment: %d\n", a );

    return 0;
}