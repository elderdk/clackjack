
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"


int CARDCOUNT = 52;

// Functions
Card popCard(Deck *deck, int retval)
{

    Card poppedCard = deck->cards[retval];

    // start from retval, move all i+1 to i, "popping" the card drawn
    for (int i = retval; i < CARDCOUNT - 1; i++)
    {
        deck->cards[i] = deck->cards[i + 1];
    }

    CARDCOUNT--;

    return poppedCard;
}

Card deck_drawRandomCard(Deck *deck)
{

    if (CARDCOUNT == 0)
    {
        printf("There's no more card.\n");
        exit(0);
    }

    int retval;
    int divisor = RAND_MAX / (CARDCOUNT);

    do
    {
        retval = rand() / divisor;
    } while (retval > CARDCOUNT - 1);

    Card poppedCard = popCard(deck, retval);

    return poppedCard;
}

Card deck_drawNextCard(Deck *deck)
{

    if (CARDCOUNT == 0)
    {
        printf("There's no more card.\n");
        exit(0);
    }

    Card poppedCard = popCard(deck, 0);

    return poppedCard;
}

Deck getShuffledDeck(Deck *deck)
{
    Deck tempDeck;

    for (int i = 0; i < CARDCOUNT; i++)
    {
        tempDeck.cards[i] = deck_drawRandomCard(deck);
    }

    return tempDeck;
}

Deck deck_createDeck()
{
    Deck deck;
    Deck shuffledDeck;

    char *suit_options = "HSCD";
    char *value_options = "A234567890JQK";

    int a = 0;

    for (int i = 0; i < 4; i++)
    {

        char suit = suit_options[i];

        for (int x = 1; x < 14; x++)
        {

            int card_score;
            if (x >= 10)
            {
                card_score = 10;
            }
            else
            {
                card_score = x;
            }

            Card card = {suit, value_options[x - 1], card_score};
            deck.cards[a] = card;

            a++;
        }
    }
    CARDCOUNT = 52;

    shuffledDeck = getShuffledDeck(&deck);
    return shuffledDeck;
}