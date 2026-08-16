#include <stdio.h>
#include "game.h"
#include "type.h"
#include <stdlib.h>
#include "players.h"
#include "board.h"
#include"finance.h"


 
Player players[4] = 
{
    {.player_name="Aggressive Investor",
        .die_value= 0,
        .player_current_position= 0,
        .player_order= 0,
    .player_cash_in_hand=30000.00,
.player_previous_position=0,
.name_by_enum =Aggressive_Investor,
.no_hotels=0,
.no_houses=0,
.rental_income=0.00,
 .number_of_loans=0,
 .loan_amount=0.0,
 .loan_duration_rounds=0, 
    .remaining_loan_rounds=0,
    .current_loan_interest_rate=0.00
},


    {.player_name = "Conservative Banker",
        .die_value = 0,
        .player_current_position = 0,
        .player_order = 0,
        .player_cash_in_hand=30000.00,
        .player_previous_position=0,
        .name_by_enum =Conservative_Banker,
        .no_hotels=0,
.no_houses=0,
.rental_income=0.00,
 .number_of_loans=0,
.loan_amount=0.0,
 .loan_duration_rounds=0, 
    .remaining_loan_rounds=0,
    .current_loan_interest_rate=0.00

    },


  {
        .player_name = "Risk Taker",
        .die_value = 0,
        .player_current_position = 0,
        .player_order = 0,
        .player_cash_in_hand=30000.00,
        .player_previous_position=0,
         .name_by_enum =Risk_Taker,
         .no_hotels=0,
.no_houses=0,
.rental_income=0.00,
 .number_of_loans=0,
.loan_amount=0.0,
 .loan_duration_rounds=0, 
    .remaining_loan_rounds=0,
    .current_loan_interest_rate=0.00
    },

    
    {
        .player_name = "Opportunistic Trader",
        .die_value = 0,
        .player_current_position = 0,
        .player_order = 0,
        .player_cash_in_hand=30000.00,
        .player_previous_position=0,
         .name_by_enum =Opportunistic_Trader,
         .no_hotels=0,
.no_houses=0,
.rental_income=0.00,
 .number_of_loans=0,
 .loan_amount=0.0,
 .loan_duration_rounds=0, 
    .remaining_loan_rounds=0,
    .current_loan_interest_rate=0.00
    }
};
void append_property(Player *player, property property)
{
   

    player->player_owned_properties[player->number_of_properties] = property;
    player->number_of_properties++;
}

  void append_utility(Player *player, utilities utility)
{
    player->player_owned_utilities[player->number_of_Utilities] = utility;
    player->number_of_Utilities++;
}

void append_railway(Player *player, railway railway)

{
    player->player_owned_railway[player->number_of_railways] = railway;
    player->number_of_railways++;
}


void pay_utility_rent(Player *player){
    double u_rent=0;
    if (player->number_of_Utilities==1)
        {
            player->player_cash_in_hand=player->player_cash_in_hand - (player->die_value*4);
            u_rent=(player->die_value*4);

            printf("\nPlayer paid utility rent %f \n",u_rent);
        }
        else  if (player->number_of_Utilities==2)
        {
            player->player_cash_in_hand=player->player_cash_in_hand - (player->die_value*10);

            u_rent=(player->die_value*4);
             printf("\nPlayer paid utility rent %f \n",u_rent);
        }
}


void check_bankrupt(Player *player, int player_index)
{
    if (player->is_bankrupt)
    {
        printf("Player %s is bankrupt out of game.\n", player->player_name);
        return;
    }

    double net_worth = calculate_net_worth(player);

    if (net_worth <= 0)
    {
        printf("%s's net worth has fallen to LKR %.0f. Attempting to raise funds...\n",
               player->player_name, net_worth);

        // give the player a chance to recover cash before declaring bankrupt
        if (player->player_cash_in_hand < 0)
        {
            attempt_debt_recovery(player, player_index);
        }

        // check net worth after any mortgaging,foreclosure attempts
        net_worth = calculate_net_worth(player);

        if (net_worth <= 0)
        {
            player->is_bankrupt = 1;
            player->status_bankrupt = 1;
            printf("%s has been declared BANKRUPT (Net Worth : LKR %.0f).\n",
                   player->player_name, net_worth);
        }
    }
    else if (player->player_cash_in_hand < 0)
    {
        // cash is negative but net worth is still positive  recover  mortgaging 
        attempt_debt_recovery(player, player_index);
    }
}


double get_development_rent_multiplier(int houses, int hotels)
{
    if (hotels > 0) return 10.0;

    switch (houses)
    {
        case 0: return 1.0;
        case 1: return 2.0;
        case 2: return 3.0;
        case 3: return 5.0;
        case 4: return 7.0;
        default: return 1.0;
    }
}

void pay_rent_when_land_on_others(Player *player, Square *Square_current, int player_index)
{
    if (Square_current->square_type == Property &&
        Square_current->property.Current_Owner != -1 &&
        Square_current->property.Current_Owner != player_index)
    {
        int owner_index = Square_current->property.Current_Owner;

        if (Square_current->property.Mortgage_Status != 0)
        {
            printf("\n%s landed on %s, but it is mortgaged. No rent charged.\n",
                   player->player_name, Square_current->square_name);
            attempt_debt_recovery(player, player_index);
            return;
        }

        double dev_multiplier = get_development_rent_multiplier(
            Square_current->property.no_of_House_Construction,
            Square_current->property.no_of_Hotel_Construction);

        double condition_multiplier = 1.0;
        if (Square_current->property.no_of_House_Construction > 0 ||
            Square_current->property.no_of_Hotel_Construction > 0)
        {
            condition_multiplier = get_condition_rent_multiplier(Square_current);
        }

        double rent = Square_current->property.Base_Rental * dev_multiplier * condition_multiplier;

        if (rent > 0)
        {
            printf("\n%s landed on %s\n", player->player_name, Square_current->square_name);
            printf("Rent paid: LKR %.0f\n", rent);
            printf("Owner: %s", players[owner_index].player_name);

            player->player_cash_in_hand -= rent;
            players[owner_index].player_cash_in_hand += rent;
            players[owner_index].rental_income += rent;
        }
    }
    else if (Square_current->square_type == Utility &&
             Square_current->utility.Utility_owner != -1 &&
             Square_current->utility.Utility_owner != player_index)
    {
        int owner_index = Square_current->utility.Utility_owner;
        double u_rent = 0;

        if (player->number_of_Utilities == 1)
        {
            u_rent = player->die_value * 4;
        }
        else if (player->number_of_Utilities == 2)
        {
            u_rent = player->die_value * 10;
        }

        player->player_cash_in_hand -= u_rent;
        players[owner_index].player_cash_in_hand += u_rent;
        players[owner_index].rental_income += u_rent;

        printf("\nPlayer paid utility rent %0.f \n", u_rent);
        printf("\n%s landed on %s (Utility)\n", player->player_name, Square_current->square_name);
        printf("Owner: %s\n", players[owner_index].player_name);
    }
    else if (Square_current->square_type == Railway &&
             Square_current->railway.current_railway_owner != -1 &&
             Square_current->railway.current_railway_owner != player_index)
    {
        int owner_index = Square_current->railway.current_railway_owner;

        if (Square_current->railway.Mortgage_Status != 0)
        {
            printf("\n%s landed on %s, but it is mortgaged. No rent charged.\n",
                   player->player_name, Square_current->square_name);
            attempt_debt_recovery(player, player_index);
            return;
        }

        double rent = railway_cost(players[owner_index].number_of_railway_staions);

        player->player_cash_in_hand -= rent;
        players[owner_index].player_cash_in_hand += rent;
        players[owner_index].rental_income += rent;

        printf("\n%s landed on %s (Railway)\n", player->player_name, Square_current->square_name);
        printf("Rent paid: LKR %.0f\n", rent);
        printf("Owner: %s\n", players[owner_index].player_name);
    }

    attempt_debt_recovery(player, player_index);
}



    
   int has_monopoly(int player_index, PropertyGroup group) {
    if (group == None) return 0;  
     
    int owned = 0, total = 0;
    for (int i = 0; i < 40; i++) {
        Square *sq = &gameBoard.squares[i];
        if (sq->square_type == Property && sq->property.group == group) {
            total++;
            if (sq->property.Current_Owner == player_index) {
                owned++;
            }
        }
    }
   
    return (total > 0 && owned == total);
}



     // func to buy properties,utility, railways 
  int if_not_player_buy(Player *player_buy){
    return 1;
    
  }
     

void player_buying_property(Player *player, Square *square, int player_index){
if (square->square_type == Property)
        {
            if (square->property.Current_Owner != -1) {
        printf("%s is already owned by Player %d.\n", 
               square->square_name, square->property.Current_Owner + 1);
               
        return;
    }

    double price = square->property.Purchase_Price;


     {

        
        switch (player->name_by_enum)
    {
    case Aggressive_Investor:
                if (player->player_cash_in_hand >= square->property.Base_Rental)
                {
                    player->player_cash_in_hand = player->player_cash_in_hand-square->property.Purchase_Price;

        // Assign ownership acording to player playing order
        square->property.Current_Owner = player_index;
        append_property(player, square->property);
        
        

        printf("%s purchasaed %s for LKR  %.0f. \n",player->player_name,square->square_name,square->property.Purchase_Price);
                }
                
                
            

        
        break;




            case Conservative_Banker:

                if (player->player_cash_in_hand - square->property.Purchase_Price >= 0.5 * player->player_cash_in_hand)
                {
                   

                         player->player_cash_in_hand = player->player_cash_in_hand-square->property.Purchase_Price;

        // Assign ownership acording to player playing order
        square->property.Current_Owner = player_index;
                    append_property(player, square->property);

        printf("%s purchasaed %s for LKR  %f. \n",player->player_name,square->square_name,square->property.Purchase_Price);



                }
                 
                

        
        break;




        
            case Risk_Taker:

                 player->player_cash_in_hand = player->player_cash_in_hand-square->property.Purchase_Price;

        // Assign ownership acording to player playing order
        square->property.Current_Owner = player_index;
        append_property(player, square->property);


        printf("%s purchasaed %s for LKR  %f. \n",player->player_name,square->square_name,square->property.Purchase_Price);

          
        
        break;






            case Opportunistic_Trader:
                         
                if (player->player_cash_in_hand>square->property.House_Construction_Cost || player->player_cash_in_hand>square->property.Hotel_Construction_Cost)
                {
                     player->player_cash_in_hand = player->player_cash_in_hand-square->property.Purchase_Price;

        // Assign ownership acording to player playing order
        square->property.Current_Owner = player_index;
        append_property(player, square->property);


        printf("%s purchasaed %s for LKR  %f. \n",player->player_name,square->square_name,square->property.Purchase_Price);
                }
                  else{
                    if_not_player_buy(player);
                }
                

        
        break;

        
    
    
    }
        
        

        
}
        }
   
else if (square->square_type == Utility)       //buying a utility
{
    if (square->utility.Utility_owner != -1) {
        printf("%s is already owned by Player %d.\n",
               square->square_name, square->utility.Utility_owner + 1);

        return;
    }

    else {

        switch (player->name_by_enum)
        {
        case Aggressive_Investor:

            if (player->player_cash_in_hand > 0)
            {
                // Assign ownership acording to player playing order
                square->utility.Utility_owner = player_index;
                append_utility(player, square->utility);

                printf("%s purchasaed %s . \n", player->player_name, square->square_name);
            }

            break;


        case Conservative_Banker:

            if (player->player_cash_in_hand - square->property.Purchase_Price >= 0.5 * player->player_cash_in_hand)
            {
              
                square->utility.Utility_owner = player_index;
                append_utility(player, square->utility);

                printf("%s purchasaed %s . \n", player->player_name, square->square_name);
            }

            break;


        case Risk_Taker:

            
            square->utility.Utility_owner = player_index;
            append_utility(player, square->utility);

            printf("%s purchasaed %s . \n", player->player_name, square->square_name);

            break;


        case Opportunistic_Trader:

            
            square->utility.Utility_owner = player_index;
            append_utility(player, square->utility);

            printf("%s purchasaed %s . \n", player->player_name, square->square_name);

            break;
        }
    }
}


    
else if (square->square_type == Railway)       //buying a railway
{
    if (square->railway.current_railway_owner != -1) {
        printf("%s is already owned by Player %d.\n",
               square->square_name, square->railway.current_railway_owner + 1);

        return;
    }

    else {

        double price = railway_cost(player->number_of_railway_staions);

        switch (player->name_by_enum)
        {
        case Aggressive_Investor:

            if (player->player_cash_in_hand >= price)
            {
                player->player_cash_in_hand -= price;

                // Assign ownership acording to player playing order
                square->railway.current_railway_owner = player_index;
                player->number_of_railway_staions++;
                append_railway(player, square->railway);

                printf("%s purchasaed %s for LKR %.0f. \n", player->player_name, square->square_name, price);
            }

            break;


        case Conservative_Banker:

            if (player->player_cash_in_hand - price >= 0.5 * player->player_cash_in_hand)
            {
                player->player_cash_in_hand -= price;

                // Assign ownership acording to player playing order
                square->railway.current_railway_owner = player_index;
                player->number_of_railway_staions++;
                append_railway(player, square->railway);

                printf("%s purchasaed %s for LKR %f. \n", player->player_name, square->square_name, price);
            }

            break;


        case Risk_Taker:

            player->player_cash_in_hand -= price;

            // Assign ownership acording to player playing order
            square->railway.current_railway_owner = player_index;
            player->number_of_railway_staions++;
            append_railway(player, square->railway);

            printf("%s purchasaed %s for LKR %f. \n", player->player_name, square->square_name, price);

            break;


        case Opportunistic_Trader:

            if (player->player_cash_in_hand >= price)
            {
                player->player_cash_in_hand -= price;

                // Assign ownership acording to player playing order
                square->railway.current_railway_owner = player_index;
                player->number_of_railway_staions++;
                append_railway(player, square->railway);

                printf("%s purchasaed %s for LKR %f. \n", player->player_name, square->square_name, price);
            }

            break;
        }
    }
    
}
       

}





int min_houses_in_group(PropertyGroup group) {
    int min_houses = 4;
    for (int i = 0; i < 40; i++) {
        Square *sq = &gameBoard.squares[i];
        if (sq->square_type == Property && sq->property.group == group) {
            if (sq->property.no_of_House_Construction <= min_houses) {
                min_houses = sq->property.no_of_House_Construction;
            }
        }
    }
    return min_houses;
}



void construction(Player *player, Square *square, int player_index)
{
    if (square->square_type != Property)
        return;

    if (square->property.Current_Owner != player_index)
        return;

    if (!has_monopoly(player_index, square->property.group))
        return;

    switch (player->name_by_enum)
    {
        case Aggressive_Investor:

            while (player->player_cash_in_hand >= square->property.House_Construction_Cost)
            {
                if (square->property.no_of_Hotel_Construction == 1)
                    break;

                if (square->property.no_of_House_Construction < 4 &&
                    square->property.no_of_House_Construction <= min_houses_in_group(square->property.group))
                {
                    square->property.no_of_House_Construction++;
                    player->player_cash_in_hand -= square->property.House_Construction_Cost;
                    player->no_houses++;

                    printf("%s built a house on %s\n", player->player_name, square->square_name);
                }
                else if (square->property.no_of_House_Construction == 4 &&
                         player->player_cash_in_hand >= square->property.Hotel_Construction_Cost)
                {
                    square->property.no_of_House_Construction = 0;
                    square->property.no_of_Hotel_Construction = 1;
                    player->player_cash_in_hand -= square->property.Hotel_Construction_Cost;
                    player->no_houses -= 4;
                    player->no_hotels++;

                    printf("%s built a HOTEL on %s\n", player->player_name, square->square_name);
                    break;
                }
                else
                {
                    break;
                }
            }
            break;


        case Conservative_Banker:

            if (player->number_of_loans == 0)
            {
                if (square->property.no_of_House_Construction < 4 &&
                    square->property.no_of_Hotel_Construction == 0 &&
                    square->property.no_of_House_Construction <= min_houses_in_group(square->property.group) &&
                    (player->player_cash_in_hand -
                     square->property.House_Construction_Cost) >=
                    (0.5 * player->player_cash_in_hand))
                {
                    square->property.no_of_House_Construction++;
                    player->player_cash_in_hand -= square->property.House_Construction_Cost;
                    player->no_houses++;
                    printf("%s built a house on %s\n", player->player_name, square->square_name);
                }
                else if (square->property.no_of_House_Construction == 4 &&
                         square->property.no_of_Hotel_Construction == 0 &&
                         player->player_cash_in_hand >=
                         square->property.Hotel_Construction_Cost)
                {
                    square->property.no_of_House_Construction = 0;
                    square->property.no_of_Hotel_Construction = 1;
                    player->player_cash_in_hand -= square->property.Hotel_Construction_Cost;
                    player->no_houses -= 4;
                    player->no_hotels++;
                    printf("%s built a HOTEL on %s\n", player->player_name, square->square_name);
                }
            }
            break;


        case Risk_Taker:

            if (square->property.no_of_House_Construction < 4 &&
                square->property.no_of_Hotel_Construction == 0 &&
                square->property.no_of_House_Construction <= min_houses_in_group(square->property.group) &&
                player->player_cash_in_hand >=
                square->property.House_Construction_Cost)
            {
                square->property.no_of_House_Construction++;
                player->player_cash_in_hand -= square->property.House_Construction_Cost;
                player->no_houses++;
                printf("%s built a house on %s\n", player->player_name, square->square_name);
            }
            else if (square->property.no_of_House_Construction == 4 &&
                     square->property.no_of_Hotel_Construction == 0 &&
                     player->player_cash_in_hand >=
                     square->property.Hotel_Construction_Cost)
            {
                square->property.no_of_House_Construction = 0;
                square->property.no_of_Hotel_Construction = 1;
                player->player_cash_in_hand -= square->property.Hotel_Construction_Cost;
                player->no_houses -= 4;
                player->no_hotels++;
                printf("%s built a HOTEL on %s\n", player->player_name, square->square_name);
            }
            break;


        case Opportunistic_Trader:

            if (player->player_cash_in_hand >
                square->property.Hotel_Construction_Cost)
            {
                if (square->property.no_of_House_Construction < 4 &&
                    square->property.no_of_Hotel_Construction == 0 &&
                    square->property.no_of_House_Construction <= min_houses_in_group(square->property.group))
                {
                    square->property.no_of_House_Construction++;
                    player->player_cash_in_hand -= square->property.House_Construction_Cost;
                    player->no_houses++;
                    printf("%s built a house on %s\n", player->player_name, square->square_name);
                }
                else if (square->property.no_of_House_Construction == 4 &&
                         square->property.no_of_Hotel_Construction == 0)
                {
                    square->property.no_of_House_Construction = 0;
                    square->property.no_of_Hotel_Construction = 1;
                    player->player_cash_in_hand -= square->property.Hotel_Construction_Cost;
                    player->no_houses -= 4;
                    player->no_hotels++;
                    printf("%s built a HOTEL on %s\n", player->player_name, square->square_name);
                }
            }
            break;
    }
}

void construction_buildings(Player *player, int player_index)
{
    for (int i = 0; i < 40; i++)
    {
        construction(player, &gameBoard.squares[i], player_index);
    }
}



int handle_jail_turn(Player *player)
{
    if (!player->is_in_jail) return 1;

    const double BAIL_AMOUNT = 300.00;

    if (player->player_cash_in_hand >= BAIL_AMOUNT)
    {
        player->player_cash_in_hand -= BAIL_AMOUNT;
        player->is_in_jail = 0;
        player->jail_turns_spent = 0;
        printf("%s paid bail of LKR %.2f and is released from Jail.\n",
               player->player_name, BAIL_AMOUNT);
        return 1;
    }

    int is_double;
    int roll = roll_dice(&is_double);   // uses the same roll_dice
    player->die_value = roll;

    if (is_double)
    {
        player->is_in_jail = 0;
        player->jail_turns_spent = 0;
        printf("%s rolled doubles (%d) and is released from Jail!\n",
               player->player_name, roll);
        return 1;
    }

    player->jail_turns_spent++;
    printf("%s remains in Jail (%d/3 turns served).\n",
           player->player_name, player->jail_turns_spent);

    if (player->jail_turns_spent >= 3)
    {
        player->is_in_jail = 0;
        player->jail_turns_spent = 0;
        printf("%s has served 3 turns and is released from Jail.\n", player->player_name);
        return 1;
    }

    return 0;
}

int get_active_player_count(Player players[], int num_players, int *winner_index)
{
    int active_count = 0;
    for (int i = 0; i < num_players; i++)
    {
        if (!players[i].is_bankrupt)
        {
            active_count++;
            if (winner_index) *winner_index = i;
        }
    }
    return active_count;
}


void print_game_over(Player *winner)
{
    double total_property_value = 0.0;

for (int i = 0; i < winner->number_of_properties; i++)
{
    total_property_value += winner->player_owned_properties[i].Purchase_Price;
}
for (int i = 0; i < winner->number_of_railways; i++)
{
    total_property_value += winner->player_owned_railway[i].Purchase_Price;
}
for (int i = 0; i < winner->number_of_Utilities; i++)
{
    total_property_value += winner->player_owned_utilities[i].Purchase_Price;
}

double net_worth = calculate_net_worth(winner);

    printf("=======================================\n");
    printf("End of Game\n");
    printf("=======================================\n\n");

    printf("GAME OVER\n\n");
    printf("Winner\n");
    printf("%s\n\n", winner->player_name);

    printf("Total Cash\n");
    printf("LKR %.0f\n\n", winner->player_cash_in_hand);

    printf("Total Property Value\n");
    printf("LKR %.0f\n\n", total_property_value);

    printf("Outstanding Loans\n");
    if (winner->number_of_loans > 0)
    {
        printf("LKR %.0f\n\n", winner->loan_amount);
    }
    else
    {
        printf("None\n\n");
    }

    printf("Net Worth\n");
    printf("LKR %.0f\n\n", net_worth);
}


