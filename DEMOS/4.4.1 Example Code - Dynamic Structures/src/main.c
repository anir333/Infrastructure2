#include <avr/io.h>
#include <stdlib.h>
#include <usart.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h> // Include for printf

typedef struct
{
    int value;
    char* suit; // Pointer to dynamically allocated suit string
} CARD;

void fullDeck(CARD* deck)
{
    char suits[4][10] = { "hearts", "diamonds", "spades", "clubs" };
    int index;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            index = (i * 13) + j;
            deck[index].value = j + 1;
            deck[index].suit = (char*)malloc(strlen(suits[i]) + 1); // Allocate memory for suit
            strcpy(deck[index].suit, suits[i]); // Copy the suit string
        }
    }
}

// Display the card details
void showCard(CARD* theCard)
{
    switch (theCard->value)
    {
        case 1:
            printf("ace of %s", theCard->suit);
            break;
        case 11:
            printf("jack of %s", theCard->suit);
            break;
        case 12:
            printf("queen of %s", theCard->suit);
            break;
        case 13:
            printf("king of %s", theCard->suit);
            break;
        default:
            printf("%d of %s", theCard->value, theCard->suit);
    }
}

// Return the address of a random card from the deck
CARD* drawCard(CARD deck[])
{
    int randm = rand() % 52;
    return &deck[randm];
}

int main()
{
    initUSART();
    CARD* deck = (CARD*)calloc(52, sizeof(CARD)); // Allocate memory for the deck

    fullDeck(deck);

    for (int i = 0; i < 10; i++)
    {
        CARD* card = drawCard(deck);
        showCard(card);
        printf("\n");
    }

    // Free all allocated memory
    for (int i = 0; i < 52; i++)
    {
        free(deck[i].suit);
    }
    free(deck);

    return 0;
}
