#include <stdio.h>
#include <stdbool.h>
#include "deck.h"
#include "structs.h"
#include "tools.h"
#include "board.h"
#include "structs.h"

int PLAYERTURNLEFT = 10;


int chooseHit(Player *you, Deck *deck)
{
    you->cards[you->cardsHeld] = deck_drawNextCard(deck);
    you->cardsHeld++;

    calculateScores(you);
    if (you->score > 21)
    {
        return dealerWin;
    }
    return initiated;
}

int playerTurn(Player *you, Deck *deck, char decision)
{

    gameState state;



    // player doubled down. Can only hit one more time.
    if (PLAYERTURNLEFT == 0)
    {
        state = chooseHit(you, deck);

        if (state == dealerWin)
        {
            return dealerWin;
        }
        else
        {
            return playerStay;
        }
    }

    // check for blackjack
    if (you->score == 21 && PLAYERTURNLEFT == 10)
    {
        return playerWin;
    }

    if(decision == 0){
        cleanInputBuffer();
        printf("Your move? ([h]it, ");
        if(PLAYERTURNLEFT == 10) {
            printf("(d)ouble, ");
        }
        printf("[s]tay): ");

        decision = getchar();
    }

    PLAYERTURNLEFT--;

    switch (decision)
    {
    case 72:
    case 104: // (h)it
        return chooseHit(you, deck);
        break;

    case 68:
    case 100: //(d)ouble
        if(PLAYERTURNLEFT != 9){ // user pressed 'd' and it's not the first round
            return playerStay;
        }
        if (you->fund >= you->bet)
        {
            you->fund -= you->bet;
            you->bet = you->bet * 2;
            PLAYERTURNLEFT = 0;
        }
        return initiated;
        break;

    case 83:
    case 115: // (s)tay
        return playerStay;
        break;
    default:
        return playerStay; // ask for input again if bad input
        break;
    }

    if (you->score > 21)
    {
        return dealerWin;
    }
}


int dealerTurn(Player *dealer, Player *you, Deck *deck)
{

    if (dealer->score >= 17 && dealer->score < 22)
    {
        // settle score
        if (dealer->score > you->score)
        {
            return dealerWin;
        }
        else if (dealer->score == you->score)
        {
            return push;
        }
        else
        {
            return playerWin;
        }
    }
    else if (dealer->score > 21)
    {
        return playerWin; // dealer bust
    }

    dealer->cards[dealer->cardsHeld] = deck_drawNextCard(deck);
    dealer->cardsHeld++;

    return playerStay;
}