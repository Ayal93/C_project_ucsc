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


typedef struct{
     char regional_development_name[50];
int regional_development_percentage;
    int regional_development_expiration_round;
}
Regional;

typedef enum 
{
    SOUTHERN_TOURISM_BOOM,
    PORT_CITY_EXPANSION,
    IT_INDUSTRY_GROWTH,
    NORTHERN_DEVELOPMENT_PROGRAMME,
    TEA_EXPORT_BOOM,
    AIRPORT_EXPANSION,
    UNIVERSITY_CITY_GROWTH,
    BEACH_POLLUTION,
    FLOOD_DAMAGE,
    TRANSPORT_STRIKE,
    ELECTRICITY_TARIFF_INCREASE,
    WATER_SHORTAGE
}reginalCard;





typedef struct {
    reginalCard cards[12];
    int top_index;
} Regional_Card_Deck;



extern ActiveNationalEvent active_national_events[MAX_ACTIVE_EVENTS];  

void initialize_event_deck(EventDeck *deck);

EventCard pick_event_card(EventDeck *deck);
reginalCard draw_from_top_areginal_card();

void init_deck(Regional_Card_Deck *deck);
reginalCard draw_from_top_areginal_card(Regional_Card_Deck *deck);
void reginal_case(void);

#endif