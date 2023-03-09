
#ifndef BOARD_H_
#define BOARD_H_

#include<stdbool.h>
#include "structs.h"

void showBoard(Player *dealer, Player *you, bool isDealerTurn);
void cleanInputBuffer();
void makeBet(Player *you);
void calculateScores(Player *player);
int countAces(Player *player);


#endif // BOARD_H_