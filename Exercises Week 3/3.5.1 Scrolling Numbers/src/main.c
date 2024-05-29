#include <display.h>
#include <util/delay.h>
#include <LEDs.h>

int main() {
    initDisplay();
    

    while (1) {
        writeNumberAndWait( 1234, 1000 );
        writeNumberAndWait( 2345, 1000 );
        writeNumberAndWait( 3456, 1000 );
        writeNumberAndWait( 4567, 1000 );
        writeNumberAndWait( 5678, 1000 );
        writeNumberAndWait( 6789, 1000 );
        writeNumberAndWait( 7890, 1000 );
        writeNumberAndWait( 8901, 1000 );
        writeNumberAndWait( 9012, 1000 );
        writeNumberAndWait( 0123, 1000 );
    
        pauseSeconds(1);    
    }

    return 0;
}
