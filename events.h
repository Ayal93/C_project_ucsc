#ifndef EVENTS_H
#define EVENTS_H


#define TOTAL_EVENT_CARDS 20


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
    EventCard cards[TOTAL_EVENT_CARDS];

    int top_index;

} EventDeck;




void initialize_event_deck(EventDeck *deck);

EventCard pick_event_card(EventDeck *deck);

#endif