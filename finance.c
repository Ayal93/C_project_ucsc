#include <stdlib.h> 
#include <time.h>   
#include "game.h"
#include "type.h"
#include <stdio.h>
#include "players.h"
#include <time.h>
#include "board.h"
#include "Auctions.h"
#include "Insuarance.h"


extern Board gameBoard;
double railway_rent = 0;

#define INITIAL_LOAN_DURATION 20

MarketConditionsState current_market_state = {.inflation_percentage=0.0, .loan_interest_percentage=0.0};

// in property depreciation

void initialize_property_finance_state(property *prop)
{
    prop->property_round_number_after_player_buy = 0;
    prop->depreciation_percent = 0.0;
    prop->current_market_value = prop->Purchase_Price;
 
    prop->building_condition = 100.0;
    prop->rounds_since_maintenance = 0;
    prop->is_structurally_damaged = 0;
    prop->maintenance_cost_multiplier = 1.0;
}
 
 
// rent a building actually collects
double get_building_rent_multiplier(double condition)
{
    if (condition >= 90) return 1.00;
    if (condition >= 75) return 0.90;
    if (condition >= 50) return 0.75;
    if (condition >= 25) return 0.50;
    return 0.0;   // below 25% = building closed
}
 
 
// rent actually owed
double calculate_effective_rent(Square *square)
{
    property *p = &square->property;
    double rent = p->Base_Rental;
 
    if (p->no_of_House_Construction > 0 || p->no_of_Hotel_Construction > 0)
    {
        rent = rent * get_building_rent_multiplier(p->building_condition);
 
        if (p->is_structurally_damaged)
            rent = rent * 0.75;   
    }
 
    return rent;
}
 
 
// called once per completed round
void advance_all_properties_round(void)
{
    for (int i = 0; i < 40; i++)
    {
        property *p = &gameBoard.squares[i].property;
 
        if (gameBoard.squares[i].square_type != Property) continue;
        if (p->Current_Owner == -1) continue;
 
        
        p->property_round_number_after_player_buy++;
 
       
        if (p->property_round_number_after_player_buy > 50)
        {
            int rounds_over = p->property_round_number_after_player_buy - 50;
            double depreciation = (rounds_over / 5) * 1.0;
 
            if (depreciation > 30) depreciation = 30;
 
            p->depreciation_percent = depreciation;
            p->current_market_value = p->Purchase_Price * (1.0 - depreciation / 100.0);
        }
 
        //  buildings lose 2% condition every round
        if (p->no_of_House_Construction > 0 || p->no_of_Hotel_Construction > 0)
        {
            p->building_condition -= 2.0;
            if (p->building_condition < 0) p->building_condition = 0;
 
            p->rounds_since_maintenance++;
 
            //  20 rounds  structural damage 
            if (p->rounds_since_maintenance > 20 && !p->is_structurally_damaged)
            {
                p->is_structurally_damaged = 1;
                p->current_market_value = p->current_market_value * 0.85;      // -15% value
                p->maintenance_cost_multiplier = p->maintenance_cost_multiplier * 1.5; // +50% maintenance cost
 
                
            }
        }
    }
}
 
 
//  owner renovates own property
void renovate_property(Player *player, Square *square, int player_index)
{
    property *p = &square->property;
 
    if (square->square_type != Property || p->Current_Owner != player_index)
    {
       
        return;
    }
 
    double cost = p->current_market_value * 0.10;
 
    if (player->player_cash_in_hand < cost)
    {
       
        return;
    }
 
    player->player_cash_in_hand -= cost;
 
    p->depreciation_percent = 0.0;
    p->current_market_value = p->Purchase_Price;
    p->property_round_number_after_player_buy = 0;
    p->Base_Rental = p->Base_Rental * 1.10;   
 
    
}
 
 
//  maintenance, only at start 
void perform_maintenance(Player *player, Square *square, int player_index)
{
    property *p = &square->property;
 
    if (square->square_type != Property || p->Current_Owner != player_index) return;
    if (p->no_of_House_Construction == 0 && p->no_of_Hotel_Construction == 0) return;
 
    double cost;
    if (p->no_of_Hotel_Construction > 0)
        cost = p->Hotel_Construction_Cost * 0.08;
    else
        cost = p->House_Construction_Cost * 0.05 * p->no_of_House_Construction;
 
    cost = cost * p->maintenance_cost_multiplier;
 
    if (player->player_cash_in_hand < cost)
    {
        
        return;
    }
 
    player->player_cash_in_hand -= cost;
    p->building_condition = 100.0;
    p->rounds_since_maintenance = 0;
 
    
}
 
 
//  renovation after structural damage
void renovate_damaged_building(Player *player, Square *square, int player_index)
{
    property *p = &square->property;
 
    if (square->square_type != Property || p->Current_Owner != player_index) return;
    if (!p->is_structurally_damaged)
    {
       
        return;
    }
 
    double replacement_value = (p->no_of_Hotel_Construction > 0) ? p->Hotel_Construction_Cost : p->House_Construction_Cost;
    double cost = replacement_value * 0.25;
 
    if (player->player_cash_in_hand < cost)
    {
        
        return;
    }
 
    player->player_cash_in_hand -= cost;
 
    p->current_market_value = p->Purchase_Price;
    p->depreciation_percent = 0.0;
    p->building_condition = 100.0;
    p->rounds_since_maintenance = 0;
    p->is_structurally_damaged = 0;
    p->maintenance_cost_multiplier = 1.0;
 
    
}


void execute_property_turn(Player *player, Square *square, int player_index)
{
    
    initialize_property_finance_state(&square->property);

    
    advance_all_properties_round();

    
    perform_maintenance(player, square, player_index);

    
    renovate_damaged_building(player, square, player_index);

   
    renovate_property(player, square, player_index);

   
    double final_rent = calculate_effective_rent(square);
}


void display_property_depreciation(const Square *square)
{
    if (!square || square->square_type != Property) return;

    const property *p = &square->property;

    printf("• Property Depreciation\n\n");
    printf("Property\n\n");
    printf("%s\n\n", p->property_name); 
    printf("has depreciated by %.0f%%.\n\n", p->depreciation_percent);
    printf("Current Value\n\n");
    printf("LKR %.0f.\n\n", p->current_market_value);
}




double maximum_loan(Player *player)
{
    double total = 0;

    // Check properties
    for (int i = 0; i < player->number_of_properties; i++)
    {
        if (player->player_owned_properties[i].Mortgage_Status == 0)
        {
            total += player->player_owned_properties[i].Mortgage_Value;
        }
    }

    // Check railways
    for (int i = 0; i < player->number_of_railways; i++)
    {
        if (player->player_owned_railway[i].Mortgage_Status == 0)
        {
            total += player->player_owned_railway[i].railway_morgadge_price;
        }
    }

    // Check utilities
    for (int i = 0; i < player->number_of_Utilities; i++)
    {
        if (player->player_owned_utilities[i].Mortgage_Status == 0)
        {
            total += player->player_owned_utilities[i].utility_morgadge_price;
        }
    }

    return total * 0.75;
}

int can_afford_to_pay_loan(Player *player, int player_index, double loan)
{
    for (int i = 0; i < 40; i++)
    {
        Square *sq = &gameBoard.squares[i];

        if (sq->square_type == Property &&
            sq->property.Current_Owner == player_index &&
            has_monopoly(player_index, sq->property.group) &&
            sq->property.no_of_Hotel_Construction == 0)
        {
            double cost;

            // construction on house count
            if (sq->property.no_of_House_Construction < 4)
            {
                cost = sq->property.House_Construction_Cost;
            }
            else
            {
                cost = sq->property.Hotel_Construction_Cost;
            }

            // Check if loan affordable
            if (player->player_cash_in_hand < cost &&
                (player->player_cash_in_hand + loan) >= cost)
            {
                return 1;
            }
        }
    }
    return 0;
}

void print_collateral(Player *player)
{
    printf("Collateral :\n");

    for (int i = 0; i < player->number_of_properties; i++)
    {
        if (player->player_owned_properties[i].Mortgage_Status == 0)
        {
            printf("%s\n", player->player_owned_properties[i].owner_name);
        }
    }

    for (int i = 0; i < player->number_of_railways; i++)
    {
        if (player->player_owned_railway[i].Mortgage_Status == 0)
        {
            printf("Railway Asset\n");
        }
    }

    for (int i = 0; i < player->number_of_Utilities; i++)
    {
        if (player->player_owned_utilities[i].Mortgage_Status == 0)
        {
            printf("Utility Asset\n");
        }
    }
}

// lock all currently-unmortgaged collateral when a loan is taken
void lock_collateral(Player *player)
{
    for (int i = 0; i < player->number_of_properties; i++)
        if (player->player_owned_properties[i].Mortgage_Status == 0)
            player->player_owned_properties[i].Loan_Locked = 1;

    for (int i = 0; i < player->number_of_railways; i++)
        if (player->player_owned_railway[i].Mortgage_Status == 0)
            player->player_owned_railway[i].Loan_Locked = 1;

    for (int i = 0; i < player->number_of_Utilities; i++)
        if (player->player_owned_utilities[i].Mortgage_Status == 0)
            player->player_owned_utilities[i].Loan_Locked = 1;
}

//  unlock all collateral once the loan is fully repaid
void unlock_collateral(Player *player)
{
    for (int i = 0; i < player->number_of_properties; i++)
        player->player_owned_properties[i].Loan_Locked = 0;

    for (int i = 0; i < player->number_of_railways; i++)
        player->player_owned_railway[i].Loan_Locked = 0;

    for (int i = 0; i < player->number_of_Utilities; i++)
        player->player_owned_utilities[i].Loan_Locked = 0;
}

void bank_of_ceylon_action(Player *player, int player_index, Square *square)
{       

           int check_auctioning = live_auctioning(player);
            
           if (check_auctioning>0)
           {
              printf("PLayer is at an auction he cann't purchase loans how");
              return;
           }
           


    double BANK_INTEREST_RATE = 0.00;

    if (square->square_type != Bank)
    {
        return;
    }

    // Calculate maximum loan
    double max_loan = maximum_loan(player);

    // Obtaining a New Loan
    if (player->number_of_loans == 0)
    {
        if (max_loan <= 0)
        {
            printf("%s landed on %s but has no unmortgaged assets to obtain a loan.\n",
                   player->player_name, square->square_name);
            return;
        }

        int should_borrow = 0;

        switch (player->name_by_enum)
        {
        case Aggressive_Investor:
            should_borrow = can_afford_to_pay_loan(player, player_index, max_loan);
            break;

        case Conservative_Banker:
            should_borrow = (player->player_cash_in_hand <= 0);
            break;

        case Risk_Taker:
            should_borrow = 1;
            break;

        case Opportunistic_Trader:
            should_borrow = (player->rental_income > (max_loan * BANK_INTEREST_RATE));
            break;
        }

        if (should_borrow)
        {
            player->player_cash_in_hand += max_loan;
            player->loan_amount = max_loan;
            player->number_of_loans = 1;
            player->loan_duration_rounds = INITIAL_LOAN_DURATION;
            player->remaining_loan_rounds = INITIAL_LOAN_DURATION;

            //  lock pledged collateral
            lock_collateral(player);

            printf("   Obtaining a Loan at %s\n\n", square->square_name);
            printf("%s obtained a secured loan.\n\n", player->player_name);
            printf("Loan Amount : LKR %.0f.\n\n", max_loan);

            print_collateral(player);

            printf("\nInterest Rate : %.0f%%\n", BANK_INTEREST_RATE * 100);
            printf("Duration : %d Rounds\n\n", INITIAL_LOAN_DURATION);
        }
        else
        {
            printf("%s landed on %s but chose not to take a loan.\n",
                   player->player_name, square->square_name);
        }
    }
    //  Managing an Existing Loan
    else
    {
        double current_loan = player->loan_amount;
        double repayment_amount = 0.0;
        int is_full_repayment = 0;

        switch (player->name_by_enum)
        {
        case Conservative_Banker:
            if (player->player_cash_in_hand >= current_loan)
            {
                repayment_amount = current_loan;
                is_full_repayment = 1;
            }
            else if (player->remaining_loan_rounds <= 3)
            {
                player->remaining_loan_rounds += INITIAL_LOAN_DURATION;
                printf("%s extended their loan period by %d rounds at %s.\n",
                       player->player_name, INITIAL_LOAN_DURATION, square->square_name);
            }
            break;

        case Aggressive_Investor:
            if (player->player_cash_in_hand > 2 * current_loan)
            {
                repayment_amount = current_loan;
                is_full_repayment = 1;
            }
            else if (player->player_cash_in_hand >= (current_loan * 0.5))
            {
                repayment_amount = current_loan * 0.5;
            }
            break;

        case Opportunistic_Trader:
            if (player->rental_income <= (current_loan * BANK_INTEREST_RATE) &&
                player->player_cash_in_hand >= current_loan)
            {
                repayment_amount = current_loan;
                is_full_repayment = 1;
            }
            else if (player->player_cash_in_hand >= (current_loan * 0.25))
            {
                repayment_amount = current_loan * 0.25;
            }
            break;

        case Risk_Taker:
            if (max_loan > current_loan)
            {
                double additional_loan = max_loan - current_loan;
                player->player_cash_in_hand += additional_loan;
                player->loan_amount = max_loan;

                // re-lock in case new collateral was added
                lock_collateral(player);

                printf("%s refinanced their loan by LKR %.0f at %s. Total loan: LKR %.0f.\n",
                       player->player_name, additional_loan, square->square_name, max_loan);
            }
            else if (player->remaining_loan_rounds <= 3)
            {
                player->remaining_loan_rounds += INITIAL_LOAN_DURATION;
                printf("%s extended their loan period by %d rounds at %s.\n",
                       player->player_name, INITIAL_LOAN_DURATION, square->square_name);
            }
            break;
        }

        if (repayment_amount > 0)
        {
            player->player_cash_in_hand -= repayment_amount;
            player->loan_amount -= repayment_amount;

            if (is_full_repayment || player->loan_amount <= 0)
            {
                player->loan_amount = 0;
                player->number_of_loans = 0;
                player->remaining_loan_rounds = 0;

                // unlock collateral now that debt is cleared
                unlock_collateral(player);
            }

            printf("  • Loan Repayment at %s\n\n", square->square_name);
            printf("%s repaid LKR %.0f.\n\n", player->player_name, repayment_amount);
            printf("Outstanding Balance :\nLKR %.0f.\n\n", player->loan_amount);
        }
    }
}





void handle_loan_default(Player *player, int player_index)
{
    printf("  Loan Default\n\n");
    printf("%s has defaulted.\n\n", player->player_name);
    printf("Collateral has been foreclosed.\n\n");
    printf("Outstanding debt cleared.\n\n");

    // Auction/foreclose only pledged board properties
    auction_liquidated_assets(player, player_index, &gameBoard, players, 4);

    // Foreclose pledged railways/utilities on the board
    for (int k = 0; k < 40; k++)
    {
        if (gameBoard.squares[k].square_type == Railway &&
            gameBoard.squares[k].railway.current_railway_owner == player_index &&
            gameBoard.squares[k].railway.Loan_Locked == 1)
        {
            gameBoard.squares[k].railway.current_railway_owner = -1;
            gameBoard.squares[k].railway.Loan_Locked = 0;
            gameBoard.squares[k].railway.Mortgage_Status = 0;
        }
        else if (gameBoard.squares[k].square_type == Utility &&
                 gameBoard.squares[k].utility.Utility_owner == player_index &&
                 gameBoard.squares[k].utility.Loan_Locked == 1)
        {
            gameBoard.squares[k].utility.Utility_owner = -1;
            gameBoard.squares[k].utility.Loan_Locked = 0;
            gameBoard.squares[k].utility.Mortgage_Status = 0;
        }
    }

    // player's local copies for only the pledged assets
    for (int i = 0; i < player->number_of_properties; i++)
    {
        property *p = &player->player_owned_properties[i];
        if (p->Loan_Locked)
        {
            p->no_of_House_Construction = 0;
            p->no_of_Hotel_Construction = 0;
            p->Number_of_buildings = 0;
            p->Insurance_Status = 0;
            p->Loan_Locked = 0;
            p->Mortgage_Status = 0;
            p->Current_Owner = -1;
            p->owner_name[0] = '\0';
        }
    }

    for (int i = 0; i < player->number_of_railways; i++)
    {
        if (player->player_owned_railway[i].Loan_Locked)
        {
            player->player_owned_railway[i].Loan_Locked = 0;
            player->player_owned_railway[i].Mortgage_Status = 0;
            player->player_owned_railway[i].current_railway_owner = -1;
        }
    }

    for (int i = 0; i < player->number_of_Utilities; i++)
    {
        if (player->player_owned_utilities[i].Loan_Locked)
        {
            player->player_owned_utilities[i].Loan_Locked = 0;
            player->player_owned_utilities[i].Mortgage_Status = 0;
            player->player_owned_utilities[i].Utility_owner = -1;
        }
    }

    player->loan_amount = 0;
    player->number_of_loans = 0;
    player->remaining_loan_rounds = 0;

    if (player->player_cash_in_hand <= 0)
    {
        player->is_bankrupt = 1;
        player->status_bankrupt = 1;    
        printf("%s has no remaining assets and is declared BANKRUPT.\n", player->player_name);
    }
    else
    {
        printf("%s continues the game with remaining assets.\n", player->player_name);
    }
}


void print_bank_assets(void)
{
    printf("=== Bank-Owned Assets ===\n\n");

    printf("Properties:\n");
    for (int i = 0; i < 40; i++)
    {
        Square *sq = &gameBoard.squares[i];
        if (sq->square_type == Property && sq->property.Current_Owner == 0)
        {
            printf("  %s\n", sq->square_name);
        }
    }

    printf("\nRailways:\n");
    for (int i = 0; i < 40; i++)
    {
        Square *sq = &gameBoard.squares[i];
        if (sq->square_type == Railway && sq->railway.current_railway_owner == 0)
        {
            printf("  %s\n", sq->square_name);
        }
    }

    printf("\nUtilities:\n");
    for (int i = 0; i < 40; i++)
    {
        Square *sq = &gameBoard.squares[i];
        if (sq->square_type == Utility && sq->utility.Utility_owner == 0)
        {
            printf("  %s\n", sq->square_name);
        }
    }
}



void apply_loan_interest_and_check_default(void)
{
    for (int m = 0; m < 4; m++)
    {
        if (players[m].number_of_loans > 0)
        {
            players[m].loan_amount += (players[m].loan_amount *players[m].current_loan_interest_rate);
            players[m].remaining_loan_rounds--;

            if (players[m].remaining_loan_rounds <= 0)
            {
                handle_loan_default(&players[m], m);
            }
        }
    }
}

void apply_inflation(int current_round) {

    if (current_round % 10 != 0) {
        return; 
    }

    int possible_rates[6] = { -3, 0, 2, 5, 8, 12 };
    int chosen_rate = possible_rates[rand() % 6];
    
    

    double inflation_factor = 1.0 + ((double)chosen_rate / 100.0);

    printf("\nInflation Update\n\n");
    printf("Round : %d\n\n", current_round);
    printf("Inflation Rate : %d%%\n", chosen_rate);
    chosen_rate = current_market_state.inflation_percentage;

    for (int i = 0; i < 40; i++) {
        Square *sq = &gameBoard.squares[i];

        if (sq->square_type == Property) {
            sq->property.Purchase_Price          *= inflation_factor;
            sq->property.House_Construction_Cost *= inflation_factor;
            sq->property.Hotel_Construction_Cost *= inflation_factor;
            sq->property.Base_Rental             *= inflation_factor;
        }
    }
}


void handle_income_tax(Player *player, Square *square, int player_index)
{
    if (square->square_type != Tax) return;

    double tax_due = square->property.Tax_Amount;

    printf("\n--- Income Tax ---\n");
    printf("%s landed on %s.\n", player->player_name, square->square_name);
    printf("Tax Due: LKR %.0f | Current Cash: LKR %.0f\n", tax_due, player->player_cash_in_hand);

    if (player->player_cash_in_hand >= tax_due)
    {
        player->player_cash_in_hand -= tax_due;
        printf("%s paid LKR %.0f in Income Tax.\n", player->player_name, tax_due);
        printf("Remaining Cash: LKR %.0f\n", player->player_cash_in_hand);
        return;
    }

    printf("%s cannot afford the tax! Initiating debt recovery process...\n", player->player_name);

    for (int i = 0; i < player->number_of_properties; i++)
    {
        property *prop = &player->player_owned_properties[i];

        if (prop->Mortgage_Status == 0 && prop->Loan_Locked == 0)
        {
            prop->Mortgage_Status = 1;
            player->player_cash_in_hand += prop->Mortgage_Value;
            printf("%s mortgaged %s for LKR %.0f.\n", 
                   player->player_name, prop->property_name, prop->Mortgage_Value);

            if (player->player_cash_in_hand >= tax_due)
            {
                break;
            }
        }
    }

    if (player->player_cash_in_hand >= tax_due)
    {
        player->player_cash_in_hand -= tax_due;
        printf("%s successfully cleared tax debt after mortgaging assets.\n", player->player_name);
        printf("Remaining Cash: LKR %.0f\n", player->player_cash_in_hand);
    }
    else
    {
        printf("%s failed to pay Income Tax debt! Declaring bankruptcy...\n", player->player_name);
        handle_loan_default(player, player_index);
    }
}


void attempt_debt_recovery(Player *player, int player_index)
{
    if (player->player_cash_in_hand >= 0) return;

    printf("%s's cash is negative (LKR %.0f). Attempting to raise funds...\n",
           player->player_name, player->player_cash_in_hand);

    for (int i = 0; i < player->number_of_properties && player->player_cash_in_hand < 0; i++)
    {
        property *prop = &player->player_owned_properties[i];

        if (prop->Mortgage_Status == 0 && prop->Loan_Locked == 0)
        {
            prop->Mortgage_Status = 1;
            player->player_cash_in_hand += prop->Mortgage_Value;
            printf("%s mortgaged %s for LKR %.0f.\n",
                   player->player_name, prop->property_name, prop->Mortgage_Value);
        }
    }

    if (player->player_cash_in_hand < 0)
    {
        printf("%s could not raise enough funds. Declaring bankruptcy...\n", player->player_name);
        handle_loan_default(player, player_index);
    }
}


const char* get_province_name(PropertyGroup group)
{
    switch (group)
    {
        case Brown:     
        case LightBlue: 
        case Pink:      
        case Orange:    
            return "Western Province";

        case Red:       
            return "Central Province";

        case Yellow:    
            return "Southern Province";

        case Green:     
            return "Northern & Eastern Province";

        case DarkBlue:  
            return "Central & Western Province";

        case None:
        default:        
            return "Unknown Province";
    }
}


void review_property_market(int current_round)
{
    if (current_round % 10 != 0) return;

    srand((int)time(NULL) + current_round);
    PropertyGroup boom_group = (PropertyGroup)(1 + rand() % 8);

    PropertyGroup decline_group;
    do
    {
        srand((int)time(NULL) + current_round + rand());
        decline_group = (PropertyGroup)(1 + rand() % 8);
    } while (decline_group == boom_group);

    printf("Tourism Boom\n\n");
    printf("%s properties increase in value by 15%%.\n\n", get_province_name(boom_group));

    for (int i = 0; i < 40; i++)
    {
        Square *sq = &gameBoard.squares[i];
        if (sq->square_type == Property && sq->property.group == boom_group)
        {
            sq->property.Purchase_Price          *= 1.15;
            sq->property.Mortgage_Value          *= 1.15;
            sq->property.Base_Rental             *= 1.25;
            sq->property.House_Construction_Cost *= 1.10;
            sq->property.Hotel_Construction_Cost *= 1.10;
            sq->property.current_market_value    *= 1.20;
        }
    }

    printf("Market Decline\n\n");
    printf("%s properties decrease in value.\n\n", get_province_name(decline_group));

    for (int i = 0; i < 40; i++)
    {
        Square *sq = &gameBoard.squares[i];
        if (sq->square_type == Property && sq->property.group == decline_group)
        {
            sq->property.current_market_value    *= 0.85;
            sq->property.Base_Rental             *= 0.80;
            sq->property.Mortgage_Value          *= 0.90;
        }
    }
}


void decay_building_condition(Square *square)
{
    if (square->square_type != Property) return;
    if (square->property.no_of_House_Construction == 0 && square->property.no_of_Hotel_Construction == 0) return;

    square->property.rounds_since_maintenance++;
    square->property.building_condition -= 2.0;
    if (square->property.building_condition < 0.0) square->property.building_condition = 0.0;
}


double get_condition_rent_multiplier(Square *square)
{
    double condition = square->property.building_condition;
    if (condition >= 90.0) return 1.00;
    if (condition >= 75.0) return 0.90;
    if (condition >= 50.0) return 0.75;
    if (condition >= 25.0) return 0.50;
    return 0.00;
}


void destroy_buildings_on_property(Board *board, int square_index)
{
    property *board_prop = &board->squares[square_index].property;

    if (board_prop->no_of_House_Construction == 0 &&
        board_prop->no_of_Hotel_Construction == 0)
        return;

    int owner_index = board_prop->Current_Owner;

    printf("%s's buildings on %s were destroyed!\n",
           (owner_index >= 0) ? players[owner_index].player_name : "Bank",
           board_prop->property_name);

    int houses_lost = board_prop->no_of_House_Construction;
    int hotel_lost  = board_prop->no_of_Hotel_Construction;

    board_prop->no_of_House_Construction = 0;
    board_prop->no_of_Hotel_Construction = 0;
    board_prop->Number_of_buildings = 0;
    board_prop->building_condition = 100.0;
    board_prop->rounds_since_maintenance = 0;
    board_prop->is_structurally_damaged = 0;
    board_prop->maintenance_cost_multiplier = 1.0;

    if (owner_index >= 0)
    {
        Player *owner = &players[owner_index];

        for (int k = 0; k < owner->number_of_properties; k++)
        {
            if (owner->player_owned_properties[k].Purchase_Price == board_prop->Purchase_Price &&
                (owner->player_owned_properties[k].no_of_House_Construction == houses_lost ||
                 owner->player_owned_properties[k].no_of_Hotel_Construction == hotel_lost))
            {
                owner->player_owned_properties[k].no_of_House_Construction = 0;
                owner->player_owned_properties[k].no_of_Hotel_Construction = 0;
                break;
            }
        }

        owner->no_houses -= houses_lost;
        if (owner->no_houses < 0) owner->no_houses = 0;

        if (hotel_lost > 0)
        {
            owner->no_hotels -= hotel_lost;
            if (owner->no_hotels < 0) owner->no_hotels = 0;
        }
    }
}


void perform_maintenance_buliding(Player *player, Square *square)
{
    double maintenance_cost = 0.0;
    int building_type = 0;

    if (square->square_type != Property) return;

    if (square->property.no_of_Hotel_Construction == 1) building_type = 2;
    else if (square->property.no_of_House_Construction > 0) building_type = 1;

    switch (building_type)
    {
        case 1:
            maintenance_cost = 0.05 * square->property.House_Construction_Cost
                                * square->property.no_of_House_Construction
                                * square->property.maintenance_cost_multiplier;
            break;
        case 2:
            maintenance_cost = 0.08 * square->property.Hotel_Construction_Cost
                                * square->property.maintenance_cost_multiplier;
            break;
        default:
            printf("%s has no buildings that require maintenance.\n", square->square_name);
            return;
    }

    if (player->player_cash_in_hand >= maintenance_cost)
    {
        player->player_cash_in_hand -= maintenance_cost;
        square->property.building_condition = 100.0;
        square->property.rounds_since_maintenance = 0;
        printf("%s performed maintenance on %s for LKR %.0f. Condition restored to 100%%.\n",
               player->player_name, square->square_name, maintenance_cost);
    }
    else
    {
        printf("%s cannot afford maintenance on %s (needs LKR %.0f).\n",
               player->player_name, square->square_name, maintenance_cost);
    }
}


void check_structural_damage(Square *square)
{
    if (square->square_type != Property) return;
    if (square->property.is_structurally_damaged == 1) return;

    if (square->property.rounds_since_maintenance > 20)
    {
        square->property.current_market_value *= 0.85;
        square->property.Base_Rental *= 0.75;
        square->property.maintenance_cost_multiplier *= 1.50;
        square->property.is_structurally_damaged = 1;

        printf("%s has suffered structural damage from neglected maintenance!\n", square->square_name);
        printf("Property value -15%%, rent -25%%, future maintenance cost +50%%.\n");
    }
}


void renovate_building(Player *player, Square *square)
{
    double renovation_cost = 0.0;

    if (square->square_type != Property) return;

    if (square->property.is_structurally_damaged == 0)
    {
        printf("%s is not damaged and does not need renovation.\n", square->square_name);
        return;
    }

    if (square->property.no_of_Hotel_Construction == 1)
        renovation_cost = 0.25 * square->property.Hotel_Construction_Cost;
    else
        renovation_cost = 0.25 * square->property.House_Construction_Cost * square->property.no_of_House_Construction;

    if (player->player_cash_in_hand >= renovation_cost)
    {
        player->player_cash_in_hand -= renovation_cost;
        square->property.current_market_value = square->property.Purchase_Price;
        square->property.Base_Rental = square->property.Base_Rental / 0.75;
        square->property.building_condition = 100.0;
        square->property.rounds_since_maintenance = 0;
        square->property.is_structurally_damaged = 0;
        square->property.maintenance_cost_multiplier = 1.0;

        printf("%s renovated %s for LKR %.0f. Property value, rent, and condition restored.\n",
               player->player_name, square->square_name, renovation_cost);
    }
    else
    {
        printf("%s cannot afford renovation on %s (needs LKR %.0f).\n",
               player->player_name, square->square_name, renovation_cost);
    }
}


void repair_disaster_damaged_property(Player *player, Square *square, int player_index)
{
    property *p = &square->property;

    if (square->square_type != Property || p->Current_Owner != player_index)
        return;

    if (p->no_of_House_Construction > 0 || p->no_of_Hotel_Construction > 0)
        return;

    if (!has_monopoly(player_index, p->group))
        return;

    double rebuild_cost = p->House_Construction_Cost * 0.25;

    if (player->player_cash_in_hand < rebuild_cost)
        return;

    player->player_cash_in_hand -= rebuild_cost;
    p->no_of_House_Construction = 1;
    p->building_condition = 100.0;
    p->rounds_since_maintenance = 0;
    p->is_structurally_damaged = 0;
    p->maintenance_cost_multiplier = 1.0;
    player->no_houses++;

    printf("%s repaired %s and rebuilt one house for LKR %.0f.\n",
           player->player_name, p->property_name, rebuild_cost);
}


void repair_disaster_damage(Player *player, int player_index)
{
    for (int i = 0; i < 40; i++)
    {
        repair_disaster_damaged_property(player, &gameBoard.squares[i], player_index);
    }
}


void process_round_end_maintenance(void)
{
    for (int i = 0; i < 40; i++)
    {
        decay_building_condition(&gameBoard.squares[i]);
        check_structural_damage(&gameBoard.squares[i]);
    }
}


void run_maintenance_cycle(Player players_list[], int num_players)
{
    for (int p = 0; p < num_players; p++)
    {
        if (players_list[p].is_bankrupt == 1) continue;

        Player *owner = &players_list[p];

        for (int s = 0; s < 40; s++)
        {
            Square *square = &gameBoard.squares[s];

            if (square->square_type != Property) continue;
            if (square->property.Current_Owner != p) continue;

            if (square->property.is_structurally_damaged == 1)
                renovate_building(owner, square);
            else if (square->property.building_condition < 100.0)
                perform_maintenance_buliding(owner, square);
        }
    }

    process_round_end_maintenance();
}





double calculate_net_worth(Player *player)
{
    double cash = player->player_cash_in_hand;

    double property_value = 0.0;
    double building_value = 0.0;
    double insurance_claims_receivable = 0.0;

    for (int i = 0; i < player->number_of_properties; i++)
    {
        property *p = &player->player_owned_properties[i];

        property_value += p->current_market_value;

        if (p->no_of_Hotel_Construction > 0)
        {
            building_value += p->Hotel_Construction_Cost * p->no_of_Hotel_Construction;
        }
        else if (p->no_of_House_Construction > 0)
        {
            building_value += p->House_Construction_Cost * p->no_of_House_Construction;
        }

        // insurance claim owed but not yet paid out
        if (p->Insurance_Status != NO_INSURANCE && p->is_structurally_damaged)
        {
            double repair_cost = p->Purchase_Price * 0.20;
            double compensation_pct = (p->Insurance_Status == COMPREHENSIVE_INSURANCE) ? 1.00 : 0.80;
            insurance_claims_receivable += repair_cost * compensation_pct;
        }
    }

    double railway_value = 0.0;
    for (int i = 0; i < player->number_of_railways; i++)
    {
        railway_value += player->player_owned_railway[i].Purchase_Price;
    }

    double utility_value = 0.0;
    for (int i = 0; i < player->number_of_Utilities; i++)
    {
        utility_value += player->player_owned_utilities[i].Purchase_Price;
    }

    double outstanding_loans = player->loan_amount;

    // Accrued interest is compounded directly into loan_amount each round
    
    double accrued_interest = 0.0;

   
    // net worth is computed between turns.
    double taxes_due = 0.0;

    double net_worth = cash
                      + property_value
                      + building_value
                      + railway_value
                      + utility_value
                      + insurance_claims_receivable
                      - outstanding_loans
                      - accrued_interest
                      - taxes_due;

    return net_worth;
}



