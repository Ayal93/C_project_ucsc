

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

int roll_dice(int *is_double){   

    int num1 = (rand() % 6) + 1;
    int num2 = (rand() % 6) + 1;

    if (num1 == num2)
    {
        *is_double = 1;
    }
    else
    {
        *is_double = 0;
    }

    return num1 + num2;
}

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


int compareRoll(const void *a, const void *b)
{
    Player *p1 = (Player *)a;
    Player *p2 = (Player *)b;

    return p1->die_value - p2->die_value; // compare func
}

 void players_order(){
    int is_double; 

    for (int i = 0; i < 4; i++) {
    players[i].die_value = roll_dice(&is_double);   
    
                                                //each player a random value get
}





        qsort(players, 4, sizeof(Player), compareRoll);

        int k=0;
       //if 2 players has same die value take them and roll die again 
     int tieFound;
    do
    {
        tieFound = 0;

        for (int i = 0; i < 3; i++)
        {
            if (players[i].die_value == players[i + 1].die_value)
            {
                tieFound = 1;

                // Find all players in this tie
                int start = i;
                int end = i;

                while (end < 3 &&
                       players[end].die_value == players[end + 1].die_value)
                {
                    end++;
                }

                 for (int j = start; j <= end; j++)
                {
                    players[j].die_value = roll_dice(&is_double);   
                }

                // Sort again
                qsort(players, 4, sizeof(Player), compareRoll);

                break;      
            }
        }

    } while (tieFound);
    




   for(int i = 0; i < 4; i++)
    {
        players[i].player_order = i + 1;      //initialize to player structuer 
    }

};
     

void before_begin_game_quote(){

printf("MONOPOLY-LK Simulation\n\n");
    
    printf("Player 1 : Aggressive Investor\n");
    printf("Player 2 : Conservative Banker\n");
    printf("Player 3 : Risk Taker\n");
    printf("Player 4 : Opportunistic Trader\n\n");
    
    printf("Each player begins with LKR 30,000.\n");
};


void player_rolling_order() 
{
    // Sort players in descending order by die_value
    for (int i = 0; i < 4 - 1; i++) 
    {
        for (int j = 0; j < 4 - i - 1; j++) 
        {
            if (players[j].die_value < players[j + 1].die_value) 
            {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    // Assign play position
    for (int i = 0; i < 4; i++) 
    {
        players[i].player_order = i + 1;
    }

    
    printf("\n\n");
    for (int i = 0; i < 4; i++) 
    {
        printf("%s rolls %d\n", players[i].player_name, players[i].die_value);
    }

    printf("\n\n");

    
    for (int i = 0; i < 4; i++) 
    {
        if (players[i].player_order == 1) 
        {
            printf("%s will begin the game.\n", players[i].player_name);
            break;
        }
    }
}

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



void player_playing_order(){
printf("\n\n");
    


printf("Turn Order:\n");
printf("%s\n",players[0].player_name);
printf("%s\n",players[1].player_name);
printf("%s\n",players[2].player_name);
printf("%s\n",players[3].player_name);
printf("\n");

};


//--------end of the playing order selecting----------------


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

        // Passing  GO awards LKR 2,000
        if (player->player_round_number > 1)
        {
            player->player_cash_in_hand += 2000.00;
            printf("%s passed GO. Collected LKR 2,000. Total cash: LKR %.2f\n", 
                   player->player_name, player->player_cash_in_hand);
        }
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
        printf("Cash : LKR %.2f\n\n", players[i].player_cash_in_hand);
        printf("Net Worth : LKR %.2f\n\n", players[i].player_cash_in_hand);
        printf("Properties : %d\n\n", players[i].number_of_properties);
        printf("Hotels : %d\n\n", players[i].no_hotels);
        printf("Houses : %d\n\n", players[i].no_houses);

        if (players[i].number_of_loans > 0) {
            printf("Outstanding Loan : LKR %.2f\n\n", players[i].loan_amount);
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
            handle_income_tax(player, square);
            break;

        case Bank:
            bank_of_ceylon_action(player, player->player_current_position, square);
            break;

        case Insurance:
            insurance_action(player, player_index);
            break;
          case Event:
{
    EventCard card = pick_event_card(&gameBoard.event_deck);
    apply_event_effect(player, &card);
    break;
}

            case Special:
            if (player->player_current_position == 30) // Go To Jail
            {
                const int JAIL_SQUARE_INDEX = 10; // "Jail 

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
{    setup_game();
    int previous_min_round = 0; 

    do 
    {
        for (int j = 0; j < 4; j++) // for each player 1 turn to play
        {
            check_bankrupt(&players[j]);
            if (players[j].status_bankrupt)
            {
                
                continue;
            }

            if (!handle_jail_turn(&players[j]))
            {
                
                continue;
            }
             int is_double;
            players[j].player_previous_position = players[j].player_current_position;
            players[j].player_current_position += roll_dice(&is_double);

            player_passe_go(&players[j]); 
            printf("%s moves from Square %d to %d\n", players[j].player_name,
                   players[j].player_previous_position, players[j].player_current_position);
            printf("%d is player %s's current round number\n\n",
                   players[j].player_round_number, players[j].player_name);

            printf("Collected LKR 2000. total is %f\n", players[j].player_cash_in_hand);




            
            
                Square *square = current_landed_square(&players[j]);
                
            // buy property
            player_buying_property(&players[j], &gameBoard.squares[players[j].player_current_position], j);

                 // pay others when landed on their properties
            pay_rent_when_land_on_others(&players[j], current_landed_square(&players[j]), j);

            construction_buildings(&players[j], j);
            execute_property_turn(&players[j], square, j);

           

           resolve_landing_action(&players[j], square, j);

            // Unowned Property & Auction handling
            if (square->square_type == Property && square->property.Current_Owner == -1)
            {
                // Returns 1 if bought, else 0
                player_buying_property(&players[j], square, j);

                  

                    run_auction(square, players, 4);
            
            }


                





           
            

            // chect gefault if the player
           for (int m = 0; m < 4; m++) 
             {
    apply_loan_interest_and_check_default();
      }

           
        }
        

        // to a full round has completed
        int min_round = players[0].player_round_number;
        for (int i = 1; i < 4; i++)
        {
            if (players[i].player_round_number < min_round)
            {
                min_round = players[i].player_round_number;
            }
        }

        
    if (min_round > previous_min_round)
{
    apply_inflation(min_round);  
    review_property_market(min_round); 
    display_round_summary(min_round, players, 4); 
   
    k = min_round; 
    previous_min_round = min_round;
}
    } while (k < 0); 
}



