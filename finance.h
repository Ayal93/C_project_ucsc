#ifndef FIN_H
#define FIN_H

#include "type.h"
#include "players.h"



extern double current_loan_interest_rate;

void bank_of_ceylon_action(Player *player, int player_index, Square *square);
void apply_loan_interest_and_check_default(void);
void handle_loan_default(Player *player, int player_index);
void handle_income_tax(Player *player, Square *square, int player_index);
void apply_inflation(int current_round);
void execute_property_turn(Player *player, Square *square, int player_index);
void attempt_debt_recovery(Player *player, int player_index);
void review_property_market(int current_round);
const char* get_province_name(PropertyGroup group);
void run_maintenance_cycle(Player players_list[], int num_players);
double get_condition_rent_multiplier(Square *square);
double calculate_net_worth(Player *player);
#endif