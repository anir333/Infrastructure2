#include <stdlib.h>
#include <usart.h>
#include <string.h>

#define MAX 5
#define COUNT 7

void printNames( char** names, int count )
{
    printString( "\nNames: \n");
    for ( int i = 0; i < count; i++ )
    {
        printf( "The #%d name is: ", i );
        int j = 0;
        while ( names[i][j] != '\0' )
        {
            printf( "%c", names[i][j] );
            j++;
        }
        printString( "\n" );
    }
}

int main()
{
    initUSART();
    int* tabc;
    tabc = calloc( MAX, sizeof( int ));
    printString( "\nThe contents of array tabc: " );
    for ( int i = 0; i < MAX; i++ ) //Walking through the array using the [] notation
    {
        printf( " %d ", tabc[i] );  //initial value
    }
    int* tabm;
    tabm = malloc( MAX * sizeof( int ));
    printString( "\nThe contents of array tabm: " );
    for ( int i = 0; i < MAX; i++ ) //Walking through the array using pointer notation
    {
        printf( " %d ", *(tabm + i ));  //initial value
    }
    int* p;
    p = tabm;
    for ( int i = 0; i < MAX; i++ ) //Walking through the array using a variable pointer
    {
        *p = i * i;
        p++;
    }
    free( tabc );
    free( tabm );
    printf("\nFreed memory\n");
    char names[COUNT][10] = { "Curly","Larry","Moe","Huey","Dewey","Louie","Donald" };
    char* pnames[COUNT];    //An array of pointers to a char
    for ( int i = 0; i < COUNT; i++ )
    {
        pnames[i] = malloc( strlen(names[i] ) + 1 );
        strcpy( pnames[i], names[i] );
    }
    printNames( pnames, COUNT );
    for ( int i = 0; i < COUNT; i ++ )
    {
        free( pnames[i] );
    }
    char** ppnames = calloc( COUNT, sizeof( char* ));   //A pointer to a pointer to a char
    for ( int i = 0; i < COUNT; i++ )
    {
        *( ppnames + i ) = malloc( strlen( names[i] ) + 1 );
        strcpy( *(ppnames + i ), names[i] );
    }
    printNames( ppnames, COUNT );
    for ( int i = 0; i < COUNT; i++ )
    {
        free( *( ppnames + i ));
    }
    free( ppnames);
    return 0;
}