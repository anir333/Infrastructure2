#include <display.h>
#include <util/delay.h>
#include <LEDs.h>
#include <usart.h>

int main() {
    initUSART();
    initDisplay();
    turnDisplayOFF();
    
    int num;
    while (1) {
        num = 1234;
        printf("\nDisplaying number: %d", num);
        writeNumberAndWait( num, 1000 );
        num = 2345;
        printf("\nDisplaying number: %d", num);
        writeNumberAndWait( num, 1000 );
        num = 3456;
        printf("\nDisplaying number: %d", num);
        writeNumberAndWait( num, 1000 );
        num = 4567;
        printf("\nDisplaying number: %d", num);
        writeNumberAndWait( num, 1000 );
        num = 5678;
        printf("\nDisplaying number: %d", num);
        writeNumberAndWait( num, 1000 );
        num = 6789;
        printf("\nDisplaying number: %d", num);
        writeNumberAndWait( num, 1000 );
        num = 7890;
        printf("\nDisplaying number: %d", num);
        writeNumberAndWait( num, 1000 );
        num = 8901;
        printf("\nDisplaying number: %d", num);
        writeNumberAndWait( num, 1000 );
        num = 9012;
        printf("\nDisplaying number: %d", num);
        writeNumberAndWait( num, 1000 );
        num = 123;
        printf("\nDisplaying number: %d", num);
        writeNumberAndWait( num, 1000 );
        // break;
    }
// turnDisplayOFF();    

    return 0;
}
