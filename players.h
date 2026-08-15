#ifndef PLAYER_H
#define PLAYER_H

#include "type.h"
#include <time.h>
#include "board.h"

typedef enum {
Aggressive_Investor,
Conservative_Banker,
Risk_Taker,
Opportunistic_Trader
} players_name_enum;

typedef struct {
    char player_name[20];
    int player_order;
    int die_value;

    int player_current_position;
    int player_previous_position;
    int player_round_number;

    players_name_enum name_by_enum;

    int no_houses;
    int no_hotels;
    int number_of_railway_staions;
    double player_cash_in_hand;

    int number_of_railways;
    int number_of_properties;

    double rental_income;

    int status_bankrupt;
    int number_of_loans;
    double loan_amount;
    int loan_duration_rounds; 
    int remaining_loan_rounds;
    int is_bankrupt;

    int is_in_jail;        
    int jail_turns_spent; 
    int is_in_auction;
    int has_suffered_loss;

    property player_owned_properties[20];
    int number_of_Utilities;
    utilities player_owned_utilities[2]; 
    railway player_owned_railway[4];

} Player;

extern Player players[4];

void player_buying_property(Player *player, Square *square, int player_index);
void pay_rent_when_land_on_others(Player *player, Square *Square_current, int player_index);
double get_development_rent_multiplier(int houses, int hotels);

int has_monopoly(int player_index, PropertyGroup group);
void utility_own_and_pay_rent(Player *player, Square *square);
void append_utility(Player *player, utilities utility);
void construction_buildings(Player *player, int player_index);

double railway_cost(int number_of_railway_stations);
void check_bankrupt(Player *player, int player_index);
void print_game_over(Player *winner);
int handle_jail_turn(Player *player);

#include "finance.h" 
Square *current_landed_square(Player *player);
void player_passe_go(Player *player);
void display_round_summary(int round_number, const Player players[], int num_players);
void resolve_landing_action(Player *player, Square *square, int player_index);
void apply_event_effect(Player *player, const EventCard *card);

#endif