#include <stdio.h>
#include "events.h"
#include "players.h"

void initialize_event_deck(EventDeck *deck)
{
    deck->cards[0] =
        (EventCard){TOURISM_HYPE, "Tourism Hype"};

    deck->cards[1] =
        (EventCard){FUEL_SHORTAGE, "Fuel Shortage"};

    deck->cards[2] =
        (EventCard){HEAVY_FLOODS, "Heavy Floods"};

    deck->cards[3] =
        (EventCard){POLITICAL_RALLY, "Political Rally"};

    deck->cards[4] =
        (EventCard){STOCK_MARKET_RISE, "Stock Market Rise"};

    deck->cards[5] =
        (EventCard){ECONOMIC_DOWNTURN, "Economic Downturn"};

    deck->cards[6] =
        (EventCard){HOUSING_SUBSIDY, "Housing Subsidy"};

    deck->cards[7] =
        (EventCard){INTEREST_RATE_CUT, "Interest Rate Cut"};

    deck->cards[8] =
        (EventCard){INTEREST_RATE_INCREASE, "Interest Rate Increase"};

    deck->cards[9] =
        (EventCard){TAX_AMNESTY, "Tax Amnesty"};

    deck->cards[10] =
        (EventCard){POWER_FAILURE, "Power Failure"};

    deck->cards[11] =
        (EventCard){FOREIGN_FUNDING, "Foreign Funding"};

    deck->cards[12] =
        (EventCard){PORT_EXPANSION, "Port Expansion"};

    deck->cards[13] =
        (EventCard){FESTIVAL_SEASON, "Festival Season"};

    deck->cards[14] =
        (EventCard){LABOUR_STRIKE, "Labour Strike"};

    deck->cards[15] =
        (EventCard){INSURANCE_DISCOUNT, "Insurance Discount"};

    deck->cards[16] =
        (EventCard){PROPERTY_REVALUATION, "Property Revaluation"};

    deck->cards[17] =
        (EventCard){CURRENCY_DEPRECIATION, "Currency Depreciation"};

    deck->cards[18] =
        (EventCard){GOVERNMENT_GRANT, "Government Grant"};

    deck->cards[19] =
        (EventCard){NATIONAL_DISASTER, "National Disaster"};


    deck->top_index = 0;
}



void apply_event_effect(Player *player, const EventCard *card)
{
    switch (card->type)
    {
        case TOURISM_HYPE:
            player->player_cash_in_hand += 500.00;
            printf("%s benefits from Tourism Hype! +LKR 500.\n", player->player_name);
            break;

        case FUEL_SHORTAGE:
            player->player_cash_in_hand -= 200.00;
            printf("%s pays LKR 200 due to Fuel Shortage.\n", player->player_name);
            break;

        case HEAVY_FLOODS:
            player->player_cash_in_hand -= 400.00;
            printf("%s pays LKR 400 in flood damage.\n", player->player_name);
            break;

        case POLITICAL_RALLY:
            printf("%s is delayed by a Political Rally. No effect this turn.\n", player->player_name);
            break;

        case STOCK_MARKET_RISE:
            player->player_cash_in_hand += 300.00;
            printf("%s gains LKR 300 from a Stock Market Rise.\n", player->player_name);
            break;

        case ECONOMIC_DOWNTURN:
            player->player_cash_in_hand -= 300.00;
            printf("%s loses LKR 300 due to an Economic Downturn.\n", player->player_name);
            break;

        case HOUSING_SUBSIDY:
            player->player_cash_in_hand += 250.00;
            printf("%s receives a Housing Subsidy of LKR 250.\n", player->player_name);
            break;

        case INTEREST_RATE_CUT:
            printf("%s benefits from lower loan interest this round.\n", player->player_name);
            break;

        case INTEREST_RATE_INCREASE:
            printf("%s faces higher loan interest this round.\n", player->player_name);
            break;

        case TAX_AMNESTY:
            player->player_cash_in_hand += 150.00;
            printf("%s saves LKR 150 thanks to a Tax Amnesty.\n", player->player_name);
            break;

        case POWER_FAILURE:
            player->player_cash_in_hand -= 100.00;
            printf("%s pays LKR 100 for Power Failure repairs.\n", player->player_name);
            break;

        case FOREIGN_FUNDING:
            player->player_cash_in_hand += 600.00;
            printf("%s receives LKR 600 in Foreign Funding.\n", player->player_name);
            break;

        case PORT_EXPANSION:
            printf("%s hears news of Port Expansion. Railway values may rise.\n", player->player_name);
            break;

        case FESTIVAL_SEASON:
            player->player_cash_in_hand += 200.00;
            printf("%s earns LKR 200 during Festival Season.\n", player->player_name);
            break;

        case LABOUR_STRIKE:
            player->player_cash_in_hand -= 250.00;
            printf("%s loses LKR 250 due to a Labour Strike.\n", player->player_name);
            break;

        case INSURANCE_DISCOUNT:
            printf("%s gets a discount on their next insurance purchase.\n", player->player_name);
            break;

        case PROPERTY_REVALUATION:
            printf("%s's properties are being revalued.\n", player->player_name);
            break;

        case CURRENCY_DEPRECIATION:
            player->player_cash_in_hand -= 350.00;
            printf("%s loses LKR 350 due to Currency Depreciation.\n", player->player_name);
            break;

        case GOVERNMENT_GRANT:
            player->player_cash_in_hand += 700.00;
            printf("%s receives a Government Grant of LKR 700.\n", player->player_name);
            break;

        case NATIONAL_DISASTER:
            player->player_cash_in_hand -= 500.00;
            printf("%s suffers LKR 500 in losses from a National Disaster.\n", player->player_name);
            break;

        default:
            break;
    }
}


EventCard pick_event_card(EventDeck *deck)
{
    EventCard picked_card;

    picked_card = deck->cards[deck->top_index];

    printf("\n");
    printf("========================================\n");
    printf("       NATIONAL EVENT CARD\n");
    printf("========================================\n");
    printf("Card: %s\n", picked_card.name);
    printf("========================================\n");


    deck->top_index++;

    if (deck->top_index >= TOTAL_EVENT_CARDS)
    {
        deck->top_index = 0;
    }


    return picked_card;
}