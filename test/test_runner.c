#ifdef TESTING
#define printf(...) ((void)0)
#endif

#include<stdio.h>
#include "../include/structs.h"
#include "../include/players.h"
#include "../include/deck.h"
#include "../include/tools.h"
#include "../include/board.h"


extern int PLAYERTURNLEFT;

int test_playerStays()
{
    Player you = {"You", .fund = 1000, .cardsHeld = 0};
    Deck deck = deck_createDeck();

    you.cards[0] = deck.cards[0];
    you.cards[1] = deck.cards[1];
    you.cardsHeld = 2;

    calculateScores(&you);

    int state = playerTurn(&you, &deck, 83); // pressed s

    if (state == playerStay)
    {
        printf("test_playerStays... Success\n");
        return 0;
    }
    else
    {
        printf("test_playerStays... Fail\n");
        return 1;
    }
}

int test_playerHits()
{
    Player you = {"You", .fund = 1000, .cardsHeld = 0};
    Deck deck = deck_createDeck();

    you.cards[0] = deck.cards[0];
    you.cards[1] = deck.cards[1];
    you.cardsHeld = 2;

    calculateScores(&you);

    int state = playerTurn(&you, &deck, 104); // pressed h

    if (state == initiated)
    {
        printf("test_playerHits... Success\n");
        return 0;
    }
    else
    {
        printf("test_playerHits... Fail\n");
        return 1;
    }
}

int test_playerDoubles()
{
    Player you = {"You", .fund = 1000, .cardsHeld = 0};
    Deck deck = deck_createDeck();

    you.cards[0] = deck.cards[0];
    you.cards[1] = deck.cards[1];
    you.cardsHeld = 2;

    calculateScores(&you);
    PLAYERTURNLEFT = 10;
    int state = playerTurn(&you, &deck, 100); // pressed d

    if (state == initiated && PLAYERTURNLEFT == 0)
    {
        printf("test_playerDoubles... Success\n");
        return 0;
    }
    else
    {
        printf("test_playerDoubles... Fail\n");
        printf("Expected state == 0 && PLAYERTURNLEFT == 0, but got state == %d && PLAYERTURNLEFT == %d\n", state, PLAYERTURNLEFT);
        return 1;
    }
}

int test_playerBusts()
{
    Player you = {"You", .fund = 1000, .cardsHeld = 0};
    Deck deck = deck_createDeck();

    you.cards[0] = deck.cards[0];
    you.cards[1] = deck.cards[1];
    you.cardsHeld = 2;

    calculateScores(&you);
    you.score = 22;

    int state = playerTurn(&you, &deck, 104); // pressed h

    if (state == dealerWin)
    {
        printf("test_playerBusts... Success\n");
        return 0;
    }
    else
    {
        printf("test_playerBusts... Fail\n");
        return 1;
    }
}


// dealer wins if score is higher than the player
// dealer loses if score is lower than the player
// dealer bust

int test_dealerTurn_dealerWins()
{
    Player dealer = {"Dealer", .fund = 1000, .cardsHeld = 0};
    Player you = {"You", .fund = 1000, .cardsHeld = 0};
    Deck deck = deck_createDeck();

    dealer.cards[0] = deck.cards[0];
    dealer.cards[1] = deck.cards[1];
    dealer.cardsHeld = 2;

    you.cards[0] = deck.cards[2];
    you.cards[1] = deck.cards[3];
    you.cardsHeld = 2;

    dealer.score = 20;
    you.score = 19;

    int state = dealerTurn(&dealer, &you, &deck);

    if (state == dealerWin)
    {
        printf("test_dealerTurn_dealerWins... Success\n");
        return 0;
    }
    else
    {
        printf("test_dealerTurn_dealerWins... Fail\n");
        return 1;
    }
}

int test_dealerTurn_push()
{
    Player dealer = {"Dealer", .fund = 1000, .cardsHeld = 0};
    Player you = {"You", .fund = 1000, .cardsHeld = 0};
    Deck deck = deck_createDeck();

    dealer.cards[0] = deck.cards[0];
    dealer.cards[1] = deck.cards[1];
    dealer.cardsHeld = 2;

    you.cards[0] = deck.cards[2];
    you.cards[1] = deck.cards[3];
    you.cardsHeld = 2;

    dealer.score = 20;
    you.score = 20;

    int state = dealerTurn(&dealer, &you, &deck);

    if (state == push)
    {
        printf("test_dealerTurn_push... Success\n");
        return 0;
    }
    else
    {
        printf("test_dealerTurn_push... Fail\n");
        return 1;
    }
}

int test_dealerTurn_playerWins()
{
    Player dealer = {"Dealer", .fund = 1000, .cardsHeld = 0};
    Player you = {"You", .fund = 1000, .cardsHeld = 0};
    Deck deck = deck_createDeck();

    dealer.cards[0] = deck.cards[0];
    dealer.cards[1] = deck.cards[1];
    dealer.cardsHeld = 2;

    you.cards[0] = deck.cards[2];
    you.cards[1] = deck.cards[3];
    you.cardsHeld = 2;

    dealer.score = 19;
    you.score = 20;

    int state = dealerTurn(&dealer, &you, &deck);

    if (state == playerWin)
    {
        printf("test_dealerTurn_playerWins... Success\n");
        return 0;
    }
    else
    {
        printf("test_dealerTurn_playerWins... Fail\n");
        return 1;
    }
}

int test_initializeGame(){
    Player dealer = {"Dealer", .fund = 10000000, .cardsHeld = 0};
    Player you = {"You", .fund = 1000, .cardsHeld = 0};
    Deck deck = deck_createDeck();

    // redirect input
    freopen("100", "r", stdin);


    initializeGame(&dealer, &you, &deck);

    freopen("stdin", "r", stdin);  // restore stdin to the console

    if(you.cardsHeld == 2 && dealer.cardsHeld == 2 && you.bet == 100){
        printf("\rtest_initializeGame... Success\n");
        return 0;
    }
    printf("\rtest_initializeGame... Fail\n");
    return 1;
}

int test_handlePlayerWin(){
    Player dealer = {"Dealer", .fund = 10000000, .cardsHeld = 0};
    Player you = {"You", .fund = 1000, .cardsHeld = 0};

    you.bet = 100;
    you.fund -= 100;

    handlePlayerWin(&dealer, &you);

    if(
        you.fund == 1100 && 
        you.bet == 0 && 
        dealer.fund == 10000000-100 &&
        PLAYERTURNLEFT == 10
        ){
        printf("\rtest_handlePlayerWin... Success\n");
        return 0;
    }
    printf("\rtest_handlePlayerWin... Fail... fund: %d, bet: %d, dealer fund: %d, playerturn: %d\n", you.fund, you.bet, dealer.fund, PLAYERTURNLEFT);
    return 1;
}

int test_handlePlayerWinBlackJack(){
    Player dealer = {"Dealer", .fund = 10000000, .cardsHeld = 0};
    Player you = {"You", .fund = 1000, .cardsHeld = 0};

    you.bet = 100;
    you.fund -= 100;
    you.score = 21;
    PLAYERTURNLEFT = 10;

    handlePlayerWin(&dealer, &you);

    if(
        you.fund == 1150 && 
        you.bet == 0 && 
        dealer.fund == 10000000-150
        ){
        printf("\rtest_handlePlayerWinBlackJack... Success\n");
        return 0;
    }
    printf("\rtest_handlePlayerWinBlackJack... Fail... fund: %d, bet: %d, dealer fund: %d, playerturn: %d\n", you.fund, you.bet, dealer.fund, PLAYERTURNLEFT);
    return 1;
}

int test_handleDealerWin(){
    Player dealer = {"Dealer", .fund = 10000000, .cardsHeld = 0};
    Player you = {"You", .fund = 1000, .cardsHeld = 0};

    you.bet = 100;
    you.fund -= 100;

    handleDealerWin(&dealer, &you);

    if(
        you.fund == 900 && 
        you.bet == 0 && 
        dealer.fund == 10000000+100 &&
        PLAYERTURNLEFT == 10
        ){
        printf("\rtest_handleDealerWin... Success\n");
        return 0;
    }
    printf("\rtest_handleDealerWin... Fail\n");
    return 1;
}

int test_handlePush(){
    Player dealer = {"Dealer", .fund = 10000000, .cardsHeld = 0};
    Player you = {"You", .fund = 1000, .cardsHeld = 0};

    you.bet = 100;
    you.fund -= 100;

    handlePush(&dealer, &you);

    if(
        you.fund == 1000 && 
        you.bet == 0 && 
        dealer.fund == 10000000 &&
        PLAYERTURNLEFT == 10
        ){
        printf("\rtest_handlePush... Success\n");
        return 0;
    }
    printf("\rtest_handlePush... Fail\n");
    return 1;
}

int test_countAces(){
    Card cards[5] = {
        {.suit = 'H', .value = '1', .score = 1},
        {.suit = 'H', .value = '2', .score = 2},
        {.suit = 'H', .value = '3', .score = 3},
        {.suit = 'H', .value = '4', .score = 4},
        {.suit = 'H', .value = '1', .score = 1}
    };

    Player player = {"Player", .fund = 1000, .cardsHeld = 0};

    // Give the player the cards
    for(int i = 0; i < 5; i++){
        player.cards[i] = cards[i];
    }

    player.cardsHeld = 5;

    int count = countAces(&player);

    if(count == 2){
        printf("test_countAces... Success\n");
        return 0;
    }
    printf("test_countAces... Fail\n");
    return 1;
}

int test_calculateScore_soft17(){
    Card cards[2] = {
        {.suit = 'H', .value = '1', .score = 1},
        {.suit = 'H', .value = '6', .score = 6}
    };

    Player player = {"Player", .fund = 1000, .cardsHeld = 0};

    // Give the player the cards
    for(int i = 0; i < 2; i++){
        player.cards[i] = cards[i];
    }

    player.cardsHeld = 2;

    calculateScores(&player);

    if(player.score == 17){
        printf("test_calculateScore_soft17... Success\n");
        return 0;
    }
    printf("test_calculateScore_soft17... Fail\n");
    return 1;
}

int test_calculateScore_doubleAce(){
    Card cards[2] = {
        {.suit = 'H', .value = '1', .score = 1},
        {.suit = 'S', .value = '1', .score = 1}
    };

    Player player = {"Player", .fund = 1000, .cardsHeld = 0};

    // Give the player the cards
    for(int i = 0; i < 2; i++){
        player.cards[i] = cards[i];
    }

    player.cardsHeld = 2;

    calculateScores(&player);

    if(player.score == 12){
        printf("test_calculateScore_doubleAce... Success\n");
        return 0;
    }
    printf("test_calculateScore_doubleAce... Fail\n");
    return 1;
}

int test_deck_createDeck(){

    Deck deck = deck_createDeck();
    int deckSize = sizeof(deck.cards) / sizeof(Card);

    if(deckSize == 52){
        printf("test_deck_createDeck... Success\n");
        return 0;
    }
    printf("test_deck_createDeck... Fail\n");
    return 1;
}


int main (void) {

    // players.c
    test_playerStays();
    test_playerHits();
    test_playerDoubles();
    test_playerBusts();
    test_dealerTurn_dealerWins();
    test_dealerTurn_push();
    test_dealerTurn_playerWins();

    // tools.c
    test_initializeGame();
    test_handlePlayerWin();
    test_handlePlayerWinBlackJack();
    test_handleDealerWin();
    test_handlePush();

    // board.c
    test_countAces();
    test_calculateScore_soft17();
    test_calculateScore_doubleAce();

    // deck.c
    test_deck_createDeck();
}