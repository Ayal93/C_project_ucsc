#ifndef INSURANCE_H
#define INSURANCE_H

#include "type.h"
#include "game.h"
#include <time.h>
#include "board.h"
#include "finance.h"
#include "events.h"


typedef enum {
    DISASTER_FIRE,
    DISASTER_FLOOD,
    DISASTER_RIOT,
    DISASTER_VANDALISM,
    DISASTER_ELECTRICAL_FAILURE
} DisasterType;
 



typedef enum {
    NO_INSURANCE,
    BASIC_INSURANCE,
    COMPREHENSIVE_INSURANCE,
    BUSINESS_INTERRUPTION_INSURANCE
} InsuranceType;






void trigger_disaster(int current_round);
void check_insurance_expiry(int current_round);
void insurance_action(Player *player, int player_index);
void decide_insurance_purchase(Player *player, Square *square, int player_index);
void mark_loss(Player *player);
void process_insurance_claim(Player *owner, property *hit, DisasterType disaster);

#endif