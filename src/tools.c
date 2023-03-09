#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structs.h"
#include "deck.h"
#include "board.h"

extern int PLAYERTURNLEFT; // Declare the global variable


void waitForPrompt(){
    fflush(stdout);
    cleanInputBuffer();
    getchar();
}

void saveScores(Player *dealer, Player *you){
    FILE *fp;
    fp = fopen("scores.txt", "w");

    fprintf(fp, "%d %d", dealer->fund, you->fund);

    fclose(fp);
}

void loadScoreIfSaveExists(Player *dealer, Player *you){
    FILE *fp;
    fp = fopen("scores.txt", "r");

    if(fp != NULL){
        fscanf(fp, "%d %d", &dealer->fund, &you->fund);
    } else {
        dealer->fund = 1000000;
        you->fund = 1000;
    }

    fclose(fp);
}

void initializeGame(Player *dealer, Player *you, Deck *deck)
{

    makeBet(you);


    dealer->cardsHeld = 0;
    you->cardsHeld = 0;

    for (int i = 0; i < 2; i++)
    {
        dealer->cards[i] = deck_drawNextCard(deck);
        dealer->cardsHeld++;

        you->cards[i] = deck_drawNextCard(deck);
        you->cardsHeld++;
    }

    calculateScores(dealer);
    calculateScores(you);
}

void handlePlayerWin(Player *dealer, Player *you)
{
    printf("Player win");

    // in case of win by blackjack
    if(you->score == 21 && PLAYERTURNLEFT==10){
        you->fund += you->bet * 2.5;
        dealer->fund -= you->bet * 1.5;
    } else {
        you->fund += you->bet * 2;
        dealer->fund -= you->bet;
    }

    you->bet = 0;
    PLAYERTURNLEFT = 10;

    saveScores(dealer, you);

    waitForPrompt();
}

void handleDealerWin(Player *dealer, Player *you)
{
    if (you->score > 21)
    {
        printf("Bust! Dealer win");
    }
    else
    {
        printf("Dealer win");
    }
    dealer->fund += you->bet;
    you->bet = 0;
    PLAYERTURNLEFT = 10;

    saveScores(dealer, you);

    waitForPrompt();
}

void handlePush(Player *dealer, Player *you)
{
    printf("Push");
    you->fund += you->bet;
    you->bet = 0;
    PLAYERTURNLEFT = 10;

    saveScores(dealer, you);

    waitForPrompt();
}
