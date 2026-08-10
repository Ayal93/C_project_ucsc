
#include "type.h"
#include "game.h"
#include <time.h>
#include "board.h"
#include"finance.h"

#include "events.h"

void trigger_disaster(int current_round);
void trigger_disaster(int current_round);
void check_insurance_expiry(int current_round);
void insurance_action(Player *player, int player_index);
void decide_insurance_purchase(Player *player, Square *square, int player_index);
void insurance_action(Player *player, int player_index);