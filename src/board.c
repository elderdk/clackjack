#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"

void displayBanner()
{

    printf("\033[0;0H"); // move the cursor to row 4, column 0

    printf("+-+-+-+-+-+ +-+-+-+-+ +-+-+-+ +-+-+-+-+-+\n"
           "|b|r|i|n|g| |d|o|w|n| |t|h|e| |h|o|u|s|e|\n"
           "+-+-+-+-+-+ +-+-+-+-+ +-+-+-+ +-+-+-+-+-+\n");
}

int countAces(Player *player)
{
    int aceCount = 0;
    for (int i = 0; i < player->cardsHeld; i++)
    {
        if (player->cards[i].score == 1)
        {
            aceCount++;
        }
    }
    return aceCount;
}

void calculateScores(Player *player)
{

    int sum = 0;
    int aceCount = 0;

    for (int i = 0; i < player->cardsHeld; i++)
    {
        sum += player->cards[i].score;
    }

    // recalculate ace score
    aceCount = countAces(player);
    if (aceCount > 0)
    {
        while (aceCount > 0)
        {
            if (sum + 10 > 21)
            {
                aceCount--;
                continue;
            }
            else
            {
                sum += 10;
            }
            aceCount--;
        }
    }

    player->score = sum;
}

void cleanInputBuffer()
{
    char c;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

bool askDoubleDown()
{
    cleanInputBuffer();
    char doubleDownAnswer;
    printf("(d)ouble down / (p)ass: ");
    scanf("%c", &doubleDownAnswer);

    if (doubleDownAnswer == 'd')
    {
        cleanInputBuffer();
        return true;
    }
    else
    {
        cleanInputBuffer();
        return false;
    }
}

char *showFace(Card *card)
{
    static char face[3];
    sprintf(face, "%c%c", card->suit, card->value);
    return face;
}

void clearScreen()
{
    printf("\033[2J"); // clear the screen
    fflush(stdout);    // flush the output buffer
}

void makeBet(Player *you)
{
    bool isValidBet = false;

    while(!isValidBet) {
        int betAmount = 0;
        
        printf("Make bet (current: %d): ", you->fund);
        scanf("%d", &betAmount);

        if (betAmount == 0)
        {
            you->bet = (int)you->fund / 10;
            you->fund -= you->bet;
            isValidBet = true;
        }
        else if (betAmount > 0 && betAmount <= you->fund)
        {
            you->bet = betAmount;
            you->fund -= you->bet;
            isValidBet = true;
        } else {
            printf("You can only bet between 1 and up to your current fund.\n");
            isValidBet = false;
        }
    }
}

void showScoreBoard()
{
    printf("\033[4;0H"); // move the cursor to row 4, column 0
    printf("\n*******************");
    printf("\n%-7s: ", "Dealer");
    printf(": ");
    printf("\n%-7s: ", "You");
    printf(": ");
    printf("\n*******************");
}

void showBoard(Player *dealer, Player *you, bool isDealerTurn)
{

    clearScreen();
    displayBanner();
    showScoreBoard();

    calculateScores(dealer);
    calculateScores(you);

    // dealer cards
    printf("\033[6;10H"); // move the cursor to row 4, column 0
    printf("                                                   ");
    printf("\033[6;10H"); // move the cursor to row 4, column 0
    for (int i = 0; i < dealer->cardsHeld; i++)
    {
        if (i == 1 && !isDealerTurn)
        {
            printf("** ");
        }
        else
        {
            printf("%s ", showFace(&dealer->cards[i]));
        }
    }
    if (isDealerTurn)
    {
        printf("  %i", dealer->score);
    }

    // player cards
    printf("\033[7;10H"); // move the cursor to row 4, column 0
    printf("                                                   ");
    printf("\033[7;10H"); // move the cursor to row 4, column 0
    for (int i = 0; i < you->cardsHeld; i++)
    {
        printf("%s ", showFace(&you->cards[i]));
    }
    printf("  %i\n", you->score);

    printf("\033[10;0H"); // move the cursor to row 4, column 0
    printf("                                                   ");
    printf("\033[10;0H"); // move the cursor to row 4, column 0
    printf("Bet: %i\n", you->bet);

    printf("\n");
}