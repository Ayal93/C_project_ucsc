#ifndef AUC_H
#define AUC_H



#include "type.h"
#include "game.h"
#include <time.h>
#include "board.h"
#include"finance.h"

#include "events.h"

void run_auction(Square *square, Player players[], int num_players);
void auction_liquidated_assets(Player *bankrupt_player, Board *board, Player players[], int num_players);
int live_auctioning(Player *player);

#endif