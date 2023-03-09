#ifndef PLAYERS_H_
#define PLAYERS_H_

#include "structs.h"


int playerTurn(Player *you, Deck *deck, char decision);
int dealerTurn(Player *dealer, Player *you, Deck *deck);



#endif /* PLAYERS_H_ */