#ifndef EVENTS_H
#define EVENTS_H


#define TOTAL_EVENT_CARDS 20
#define MAX_ACTIVE_EVENTS 10

typedef enum
{
    TOURISM_HYPE,
    FUEL_SHORTAGE,
    HEAVY_FLOODS,
    POLITICAL_RALLY,
    STOCK_MARKET_RISE,
    ECONOMIC_DOWNTURN,
    HOUSING_SUBSIDY,
    INTEREST_RATE_CUT,
    INTEREST_RATE_INCREASE,
    TAX_AMNESTY,
    POWER_FAILURE,
    FOREIGN_FUNDING,
    PORT_EXPANSION,
    FESTIVAL_SEASON,
    LABOUR_STRIKE,
    INSURANCE_DISCOUNT,
    PROPERTY_REVALUATION,
    CURRENCY_DEPRECIATION,
    GOVERNMENT_GRANT,
    NATIONAL_DISASTER

} EventCardType;


typedef struct
{
    EventCardType type;
    char name[50];

} EventCard;


typedef struct
{
    EventCard cards[20];

    int top_index;

} EventDeck;

typedef struct
{
    EventCardType type;
    int player_index;     
    int expiration_round;
    int in_use;
} ActiveNationalEvent;




extern ActiveNationalEvent active_national_events[MAX_ACTIVE_EVENTS];  

void initialize_event_deck(EventDeck *deck);

EventCard pick_event_card(EventDeck *deck);



#endif