
#ifndef TOOLS_H_
#define TOOLS_H_

#include "structs.h"


void initializeGame(Player *dealer, Player *you, Deck *deck);
void handlePlayerWin(Player *dealer, Player *you);
void handleDealerWin(Player *dealer, Player *you);
void handlePush(Player *dealer, Player *you);
void saveScores(Player *dealer, Player *you);
void loadScoreIfSaveExists(Player *dealer, Player *you);

#endif // TOOLS_H_