#include <stdio.h>
#include "events.h"
#include "players.h"
# include "board.h"


const char *CARD_NAMES[12] = {
    "Southern Tourism Boom",
    "Port City Expansion",
    "IT Industry Growth",
    "Northern Development Programme",
    "Tea Export Boom",
    "Airport Expansion",
    "University City Growth",
    "Beach Pollution",
    "Flood Damage",
    "Transport Strike",
    "Electricity Tariff Increase",
    "Water Shortage"
};

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






// regional card part --------------

void init_deck() {
    Regional_Card_Deck *deck;
    for (int i = 0; i < 12; i++) {
        deck->cards[i] = (reginalCard)i;
    }
    deck->top_index = 0;
}


reginalCard draw_from_top_areginal_card() {
    Regional_Card_Deck *deck;
    reginalCard drawn = deck->cards[deck->top_index];
    deck->top_index = (deck->top_index + 1) % 12; 
    return drawn;
}


void reginal_case(){
    Board *board;
    reginalCard card =draw_from_top_areginal_card();

for (int i = 0; i < SQUARE_COUNT; i++) {
        enumSquareName name = board->squares[i].enumName;

        switch (card) {
            case SOUTHERN_TOURISM_BOOM:
                if (name == SQUARE_GALLE_FORT || 
                    name == SQUARE_UNAWATUNA || 
                    name == SQUARE_HIKKADUWA) {
                    board->squares[i].property.Base_Rental *= 1.40;
                }
                break;

            case PORT_CITY_EXPANSION:
                if (name == SQUARE_PETTAH || name == SQUARE_MARADANA) {
                    board->squares[i].property.Purchase_Price *= 1.25;
                } else if (name == SQUARE_COLOMBO_FORT_RAILWAY_STATION) {
                    board->squares[i].railway.Purchase_Price *= 1.25;
                }
                break;

            case IT_INDUSTRY_GROWTH:
                if (name == SQUARE_MAHARAGAMA || 
                    name == SQUARE_NUGEGODA || 
                    name == SQUARE_KOTTAWA) {
                    board->squares[i].property.Purchase_Price *= 1.20;
                }
                break;

            case NORTHERN_DEVELOPMENT_PROGRAMME:
                if (name == SQUARE_JAFFNA_TOWN || 
                    name == SQUARE_NALLUR || 
                    name == SQUARE_TRINCOMALEE) {
                    board->squares[i].property.Purchase_Price *= 1.30;
                }
                break;

            case TEA_EXPORT_BOOM:
                if (name == SQUARE_NUWARA_ELIYA) {
                    board->squares[i].property.Purchase_Price *= 1.35;
                }
                break;

            case AIRPORT_EXPANSION:
                if (name == SQUARE_NEGOMBO || 
                    name == SQUARE_KATUNAYAKE || 
                    name == SQUARE_JA_ELA) {
                    board->squares[i].property.Base_Rental *= 1.30;
                }
                break;

            case UNIVERSITY_CITY_GROWTH:
                if (name == SQUARE_PERADENIYA || name == SQUARE_KANDY_CITY) {
                    board->squares[i].property.Purchase_Price *= 1.20;
                }
                break;

            case BEACH_POLLUTION:
                if (name == SQUARE_GALLE_FORT || 
                    name == SQUARE_UNAWATUNA || 
                    name == SQUARE_HIKKADUWA || 
                    name == SQUARE_MOUNT_LAVINIA) {
                    board->squares[i].property.Base_Rental *= 0.70;
                }
                break;

            case FLOOD_DAMAGE:
                if (name == SQUARE_PETTAH || 
                    name == SQUARE_WELLAWATTE || 
                    name == SQUARE_BAMBALAPITIYA) {
                    board->squares[i].property.Purchase_Price *= 0.80;
                }
                break;

            case TRANSPORT_STRIKE:
                if (board->squares[i].square_type == Railway) {
                    board->squares[i].railway.Purchase_Price *= 0.60;
                }
                break;

            case ELECTRICITY_TARIFF_INCREASE:
                if (board->squares[i].square_type == Utility) {
                    board->squares[i].utility.Purchase_Price *= 1.25;
                }
                break;

            case WATER_SHORTAGE:
                if (name == SQUARE_NATIONAL_WATER_SUPPLY_BOARD) {
                    board->squares[i].utility.Purchase_Price *= 1.20;
                } else if (board->squares[i].square_type == Property) {
                    board->squares[i].property.Purchase_Price *= 0.90;
                }
                break;

            default:
                break;
        }
    }

}














