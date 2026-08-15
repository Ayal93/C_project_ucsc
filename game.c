

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "type.h"
#include "players.h"
#include "board.h"
#include "Auctions.h"
#include "Insuarance.h"
#include "finance.h"
#include "events.h"

double insurance_premium_multiplier = 1.0;

void setup_game(void)
{
    srand(time(NULL));

    initialize_board();
initialize_event_deck(&gameBoard.event_deck);
    before_begin_game_quote();
    players_order();
    player_rolling_order();
    player_playing_order();
}      
// --------------making the playing order-----------------------------



 

void before_begin_game_quote(){

printf("MONOPOLY-LK Simulation\n\n");
    
    printf("Player 1 : Aggressive Investor\n");
    printf("Player 2 : Conservative Banker\n");
    printf("Player 3 : Risk Taker\n");
    printf("Player 4 : Opportunistic Trader\n\n");
    
    printf("Each player begins with LKR 30,000.\n");
};



double railway_cost(int number_of_railway_stations)
{
    double railway_rent;

    switch (number_of_railway_stations)
    {
        case 1:
            railway_rent = 250.00;
            break;

        case 2:
            railway_rent = 500.00;
            break;

        case 3:
            railway_rent = 1000.00;
            break;

        case 4:
            railway_rent = 2000.00;
            break;

        default:
            railway_rent = 0.00;
            break;
    }

    return railway_rent;
}





//poitions

int board_position =0;


Square *current_landed_square(Player *player){
    return &gameBoard.squares[player->player_current_position];
};


void player_passe_go(Player *player)
{
    if (player->player_current_position >= 40)
    {
        player->player_current_position -= 40;
        player->player_round_number++;

        //  every time GO is passed or landed on
        player->player_cash_in_hand += 2000.00;
        printf("%s passed GO. Collected LKR 2,000. Total cash: LKR %.0f\n",
               player->player_name, player->player_cash_in_hand);
    }
}

void display_round_summary(int round_number, const Player players[], int num_players) {
    printf("=======================================\n");
    printf("Round %d Summary\n", round_number);
    printf("=======================================\n\n");

    for (int i = 0; i < num_players; i++) {
        if (players[i].status_bankrupt) {
            printf("%s — BANKRUPT (out of the game)\n", players[i].player_name);
            if (i < num_players - 1) {
                printf("---------------------------------------\n\n");
            }
            continue;
        }

        printf("%s\n\n", players[i].player_name);
        printf("Cash : LKR %.0f\n\n", players[i].player_cash_in_hand);
     printf("Net Worth : LKR %.0f\n\n", calculate_net_worth((Player *)&players[i]));
         printf("Properties : %d\n\n", players[i].number_of_properties);
        printf("Hotels : %d\n\n", players[i].no_hotels);
         printf("Houses : %d\n\n", players[i].no_houses);
 
        if (players[i].number_of_loans > 0) {
            printf("Outstanding Loan : LKR %.0f\n\n", players[i].loan_amount);
        } else {
            printf("Outstanding Loan : None\n\n");
        }

        if (i < num_players - 1) {
            printf("---------------------------------------\n\n");
        }
    }
}


void resolve_landing_action(Player *player, Square *square, int player_index)
{   
    switch (square->square_type)
    {
        case Tax:
            handle_income_tax(player, square, player_index);
            break;

        case Bank:
            bank_of_ceylon_action(player, player->player_current_position, square);
            break;

        case Insurance:
            insurance_action(player, player_index);
            break;

       case Event:
{
    printf("\n%s landed on %s (Event Square).\n", player->player_name, square->square_name);
    EventCard card = pick_event_card(&gameBoard.event_deck);
    apply_event_effect(player, &card);
    break;
}

        case Special:
            if (player->player_current_position == 30)
            {
                const int JAIL_SQUARE_INDEX = 10;

                player->player_current_position = JAIL_SQUARE_INDEX;
                player->is_in_jail = 1;
                player->jail_turns_spent = 0;

                printf("%s landed on Go To Jail and has been sent to Jail (Square %d).\n",
                       player->player_name, JAIL_SQUARE_INDEX);
            }
            break;

        default:
            break;
    }
}



int k = 0;

void start_game()
{
    setup_game();
    int previous_min_round = 0;

    do
    {
        for (int j = 0; j < 4; j++)
        {
               
               
            if (players[j].status_bankrupt)
            {
                continue;
            }

            if (handle_jail_turn(&players[j]))
            {
                continue;
            }
 printf("\n--------------------$$$-------------------\n");
            
            players[j].player_previous_position = players[j].player_current_position;
            players[j].player_current_position += roll_dice();
            printf("%s rolled %d. \n",players[j].player_name,players[j].die_value);
            check_bankrupt(&players[j], j);


            player_passe_go(&players[j]);
            printf("%s moves from Square %d to %d\n", players[j].player_name,
                   players[j].player_previous_position, players[j].player_current_position);
            printf("%d is player %s's current round number\n\n",
                   players[j].player_round_number, players[j].player_name);

            Square *square = current_landed_square(&players[j]);

            if (square->square_type == Property && square->property.Current_Owner == -1)
            {
                player_buying_property(&players[j], square, j);

                if (square->property.Current_Owner == -1)
                {
                    run_auction(square, players, 4);
                }
            }
            else
            {
                player_buying_property(&players[j], square, j);
            }

            pay_rent_when_land_on_others(&players[j], current_landed_square(&players[j]), j);

            construction_buildings(&players[j], j);
            execute_property_turn(&players[j], square, j);

            resolve_landing_action(&players[j], square, j);
             printf("\n\n-----------------------$$$-------------------\n\n");
        }

        int min_round = -1;
        int active_players = 0;
        int winner_index = -1;

        for (int i = 0; i < 4; i++)
        {   
            if (!players[i].status_bankrupt)
            {
                active_players++;
                winner_index = i;
                if (min_round == -1 || players[i].player_round_number < min_round)
                {
                    min_round = players[i].player_round_number;
                }
            }
        }

        if (active_players == 0)
        {
            printf("All players are bankrupt. Game over.\n");
            break;
        }

        if (active_players == 1)
        {
            printf("=======================================\n");
            printf("%s is the last player and WINS the game!\n", players[winner_index].player_name);
            printf("Final Cash : LKR %.0f\n", players[winner_index].player_cash_in_hand);
            printf("=======================================\n");
            break;
        }

        if (min_round > previous_min_round)
        { printf("************************************\n\n");
            apply_loan_interest_and_check_default();
            apply_inflation(min_round);
            review_property_market(min_round);
            run_maintenance_cycle(players, 4);
            check_insurance_expiry(min_round);
            
            
            if (min_round % 10 == 0)
            {
                trigger_disaster(min_round);
            }

            display_round_summary(min_round, players, 4);
 printf("************************************\n\n");
            k = min_round;
            previous_min_round = min_round;
            
        }

    } while (k < 500);
}

