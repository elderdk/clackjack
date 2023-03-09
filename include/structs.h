#ifndef STRUCTS_H_
#define STRUCTS_H_


typedef struct {
    char suit;
    char value;
    int score;
} Card;

typedef struct {
    Card cards[52];
} Deck;

typedef struct {
    char * name;
    Card cards[52];
    int score;
    int fund;
    int bet;
    int cardsHeld;
} Player;

typedef enum {
    initiated = 0,
    playerStay = 1,
    playerWin = 2,
    dealerFinish = 3,
    dealerWin = 4,
    push = 5
} gameState;

#endif // STRUCTS_H_