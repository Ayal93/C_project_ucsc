#ifndef GAME_H
#define GAME_H
#include "type.h"
#include "players.h"
#include "events.h"

void setup_game(void);
void before_begin_game_quote(void);

double railway_cost(int number_of_railway_stations);

Square *current_landed_square(Player *player);
void player_passe_go(Player *player);

void display_round_summary(int round_number, const Player players[], int num_players);
void resolve_landing_action(Player *player, Square *square, int player_index);

void start_game(void);

#endif