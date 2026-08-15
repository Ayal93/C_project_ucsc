#include <stdio.h>
#include "type.h"
#include "game.h"
#include <time.h>
#include "board.h"
#include "finance.h"
#include "players.h"
#include <stdlib.h>
#include "Insuarance.h"

// Used by Risk_Taker, who only buys insurance after a loss.
void mark_loss(Player *player) {
    player->has_suffered_loss = 1;
}
 
void decide_insurance_purchase(Player *player, Square *square, int player_index) {
 
    if (square->square_type != Property) {
        return;
    }
    if (square->property.Current_Owner != player_index) {
        return;
    }
 
    int is_hotel   = (square->property.no_of_Hotel_Construction > 0);
    int is_house   = (square->property.no_of_House_Construction > 0);
    int high_value = (square->property.Purchase_Price >= 6000);
 
    InsuranceType choice = NO_INSURANCE;
 
    switch (player->name_by_enum) {
 
        case Aggressive_Investor:
            // Basic insurance for houses, Comprehensive for hotels
            if (is_hotel) {
                choice = COMPREHENSIVE_INSURANCE;
            } else if (is_house) {
                choice = BASIC_INSURANCE;
            } else {
                choice = NO_INSURANCE;
            }
            break;
 
        case Conservative_Banker:
            
            if (is_house || is_hotel) {
                choice = COMPREHENSIVE_INSURANCE;
            } else {
                choice = NO_INSURANCE;
            }
            break;
 
        case Risk_Taker:
            // Only buys insurance after already suffering a financial loss
            if (player->has_suffered_loss) {
                if (is_house || is_hotel) {
                    choice = BASIC_INSURANCE;
                } else {
                    choice = NO_INSURANCE;
                }
            } else {
                choice = NO_INSURANCE;
            }
            break;
 
        case Opportunistic_Trader:
           // only for high-value developments
            if (is_house || is_hotel) {
                if (high_value) {
                    choice = COMPREHENSIVE_INSURANCE;
                } else {
                    choice = NO_INSURANCE;
                }
            } else {
                choice = NO_INSURANCE;
            }
            break;
 
        default:
            choice = NO_INSURANCE;
            break;
    }
 
    if (choice == NO_INSURANCE) {
        return;
    }
 
    // Already insured no rebuy
    if (square->property.Insurance_Status != NO_INSURANCE) {
        return;
    }
 
    double premium = 0;
    char *type_name = "";
 
    //  premiums are a   Purchase_Price
    if (choice == COMPREHENSIVE_INSURANCE) {
        premium = square->property.Purchase_Price * 0.10;
        type_name = "Comprehensive";
    } else if (choice == BASIC_INSURANCE) {
        premium = square->property.Purchase_Price * 0.05;
        type_name = "Basic";
    } else if (choice == BUSINESS_INTERRUPTION_INSURANCE) {
        // Business Interruption is hotel only 
        if (!is_hotel) {
            return;
        }
        premium = square->property.Purchase_Price * 0.15;
        type_name = "Business Interruption";
    }
 
    if (player->player_cash_in_hand < premium) {
        return; 
    }
 
    player->player_cash_in_hand -= premium;
    square->property.Insurance_Status = choice;
    square->property.Insurance_Purchase_Round = player->player_round_number;
 
    printf("\nPurchasing Insurance\n\n");
    printf("%s Insurance purchased.\n\n", type_name);
    printf("Property : %s\n\n", square->property.property_name);
    printf("Premium : LKR %.0f.\n", premium);
}
 
 

// 20 rounds have passed since purchase.
void check_insurance_expiry(int current_round) {
    for (int i = 0; i < 40; i++) {
        property *prop = &gameBoard.squares[i].property;
 
        if (prop->Insurance_Status == NO_INSURANCE) {
            continue;
        }
 
        int rounds_active = current_round - prop->Insurance_Purchase_Round;
 
        if (rounds_active == 17) {
            printf("\nInsurance Renewal Reminder\n\n");
            printf("Property : %s\n\n", prop->property_name);
            printf("Expires In : 3 rounds.\n");
        }
 
        if (rounds_active >= 20) {
            prop->Insurance_Status = NO_INSURANCE;
            printf("\nInsurance Expired\n\n");
            printf("Property : %s\n", prop->property_name);
        }
    }
}
 
 
void insurance_action(Player *player, int player_index) {
    for (int s = 0; s < 40; s++) {
        Square *sq = &gameBoard.squares[s];
        if (sq->square_type == Property && sq->property.Current_Owner == player_index) {
            decide_insurance_purchase(player, sq, player_index);
        }
    }
}

// Returns 1 if the given policy covers the given disaster type
int policy_covers_disaster(InsuranceType policy, DisasterType disaster) {



    
    if (policy == BASIC_INSURANCE) {
        if (disaster == DISASTER_FIRE ||disaster == DISASTER_FLOOD || disaster == DISASTER_FLOOD) {
            return 1;
        }
        return 0;
    }

    if (policy == COMPREHENSIVE_INSURANCE) {
        if (disaster == DISASTER_FIRE || disaster == DISASTER_FLOOD  ||
            disaster == DISASTER_RIOT || disaster == DISASTER_VANDALISM) {
            return 1;
        }
        return 0;
    }

    if (policy== BUSINESS_INTERRUPTION_INSURANCE)
    {
         
        return 1;
    
    }
    

    return 0;
}

void process_insurance_claim(Player *owner, property *hit, DisasterType disaster) {

    double repair_cost = hit->Purchase_Price * 0.20;

    printf("\nDisaster Occurred\n\n");
    printf("Property : %s\n\n", hit->property_name);

    if (hit->Insurance_Status != NO_INSURANCE &&
        policy_covers_disaster((InsuranceType)hit->Insurance_Status, disaster)) {

        double compensation_pct = 0;
        double other;
        if (hit->Insurance_Status == BASIC_INSURANCE) {
            compensation_pct = 0.80;
            other=0.00;
        } 
        
        else if (hit->Insurance_Status == COMPREHENSIVE_INSURANCE) {
            compensation_pct = 1.00;
            other=0.00;
        }
        else if (hit->Insurance_Status == BUSINESS_INTERRUPTION_INSURANCE)
        {
            compensation_pct = 0.00;
            other=hit->no_of_Hotel_Construction*hit->Base_Rental*10;
        }
        

        double compensation = (repair_cost * compensation_pct )+other;
        owner->player_cash_in_hand += compensation;

        printf("Insurance Claim Approved.\n\n");
        printf("Compensation Paid : LKR %.0f.\n", compensation);

    } else {

        if (owner->player_cash_in_hand >= repair_cost) {
            owner->player_cash_in_hand -= repair_cost;
            printf("Repair Cost Paid : LKR %.0f.\n", repair_cost);
        } else {
            printf("Repair Cost Pending : LKR %.0f.\n", repair_cost);
        }
        mark_loss(owner);
    }
}


// Selects a random developed property and disaster type

void trigger_disaster(int current_round) {

    int developed[40];
    int count = 0;

    for (int i = 0; i < 40; i++) {
        property *prop = &gameBoard.squares[i].property;
        if (gameBoard.squares[i].square_type == Property &&
            (prop->no_of_House_Construction > 0 || prop->no_of_Hotel_Construction > 0)) {
            developed[count] = i;
            count++;
        }
    }

    if (count == 0) {
        return;
    }

    int square_index = developed[rand() % count];
    Square *hit_square = &gameBoard.squares[square_index];
    property *hit = &hit_square->property;

    //DisasterType disaster = (DisasterType)(rand() % 5);  // reomve this random disatsre part brotherrrrrrrrrrr

        reginalCard disaster;
    int owner_index = hit->Current_Owner;
    if (owner_index < 0) {
        return; // unowned property nothing to do
    }

    Player *owner = &players[owner_index];

    process_insurance_claim(owner, hit, disaster);
}




