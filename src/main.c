#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "deck.h"
#include "board.h"
#include "players.h"
#include "tools.h"


int main(void)
{

    srand(time(NULL));

    Player dealer = {"Dealer", .cardsHeld = 0};
    Player you = {"You", .cardsHeld = 0};

    loadScoreIfSaveExists(&dealer, &you);

    while (you.fund > 0)
    {

        Deck deck = deck_createDeck();

        gameState gameState = initiated;

        initializeGame(&dealer, &you, &deck);

        showBoard(&dealer, &you, false);

        // player turn

        while (gameState == initiated)
        {
            gameState = playerTurn(&you, &deck, 0);
            showBoard(&dealer, &you, false);
        }

        switch (gameState)
        {
        case playerWin:
            handlePlayerWin(&dealer, &you);
            continue;
            break;
        case dealerWin:
            handleDealerWin(&dealer, &you);
            continue;
            break;
        default:
            break;
        }

        // dealer turn
        while (gameState == playerStay)
        {
            gameState = dealerTurn(&dealer, &you, &deck);
            sleep(0.75);
            showBoard(&dealer, &you, true);
        }

        switch (gameState)
        {
        case playerWin:
            handlePlayerWin(&dealer, &you);
            continue;
            break;
        case dealerWin:
            handleDealerWin(&dealer, &you);
            continue;
            break;
        case push:
            handlePush(&dealer, &you);
            continue;
            break;
        default:
            break;
        }

    }

    if(you.fund <= 0 || dealer.fund <= 0){
        printf("Game over!\n");
    }
}
