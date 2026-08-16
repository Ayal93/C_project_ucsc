#ifndef TYPE_H
#define TYPE_H

#include "events.h"


typedef enum { 
None,   // to identify colour and property group
  Brown,
  LightBlue,
  Pink,
  Orange,
  Red,
  Yellow,
  Green,
  DarkBlue

} PropertyGroup;



typedef enum  {     // to identify the type
    Start,
    Property, 
    Event,
    Tax,
    Special,
    Utility,
    Railway,
    Insurance,
    Bank
}SquareType ;

typedef struct 
{
         int Mortgage_Status;
    int current_railway_owner;
    double railway_morgadge_price;
    double Purchase_Price;
    int Loan_Locked;

}railway;





typedef struct   {    //property values

        
        PropertyGroup group;
        double Purchase_Price;
        double Mortgage_Value;
        double Base_Rental;
        double House_Construction_Cost;
        double Hotel_Construction_Cost;
        SquareType square_Type;
        
        int Current_Owner;        // 1 for player1 2for  player 2 like on  in playing order
        int Mortgage_Status;
        int Insurance_Status;
        int Number_of_buildings;
        char owner_name[20];
         int Loan_Locked;



        char property_name[40];
        int no_of_House_Construction;
        int no_of_Hotel_Construction;
         double Tax_Amount; 
         int Insurance_Purchase_Round;
        int previous_owner;
     int property_round_number_after_player_buy; 
        double depreciation_percent;                 
        double current_market_value;                 
        
        
        double building_condition;          
        int rounds_since_maintenance;        
        int is_structurally_damaged;         
        double maintenance_cost_multiplier; 

  }property;




  typedef struct 
{
   int Utility_owner;
   int number_of_Utilities;
   double utility_morgadge_price;
    double Purchase_Price;
    int Mortgage_Status;
    int Loan_Locked;
} utilities;



    


  typedef struct { property bank_owned_property[40];
     int bank_property_count;
     double bank_interest_rate;
 } Bank_Details;
extern Bank_Details bank;

typedef enum {
    SQUARE_GO,
    SQUARE_PETTAH,
    SQUARE_COMMUNITY_DEVELOPMENT_FUND,
    SQUARE_MARADANA,
    SQUARE_INCOME_TAX,
    SQUARE_COLOMBO_FORT_RAILWAY_STATION,
    SQUARE_BAMBALAPITIYA,
    SQUARE_NATIONAL_EVENT_CARD_1,
    SQUARE_WELLAWATTE,
    SQUARE_MOUNT_LAVINIA,
    SQUARE_JAIL,
    SQUARE_NUGEGODA,
    SQUARE_CEYLON_ELECTRICITY_BOARD,
    SQUARE_MAHARAGAMA,
    SQUARE_KOTTAWA,
    SQUARE_KANDY_RAILWAY_STATION,
    SQUARE_NEGOMBO,
    SQUARE_SRI_LANKA_INSURANCE,
    SQUARE_KATUNAYAKE,
    SQUARE_JA_ELA,
    SQUARE_FREE_PARKING,
    SQUARE_KANDY_CITY,
    SQUARE_NATIONAL_EVENT_CARD_2,
    SQUARE_PERADENIYA,
    SQUARE_KATUGASTOTA,
    SQUARE_GALLE_RAILWAY_STATION,
    SQUARE_GALLE_FORT,
    SQUARE_UNAWATUNA,
    SQUARE_NATIONAL_WATER_SUPPLY_BOARD,
    SQUARE_HIKKADUWA,
    SQUARE_GO_TO_JAIL,
    SQUARE_JAFFNA_TOWN,
    SQUARE_NALLUR,
    SQUARE_CEYLINCO_INSURANCE,
    SQUARE_TRINCOMALEE,
    SQUARE_JAFFNA_RAILWAY_STATION,
    SQUARE_NATIONAL_EVENT_CARD_3,
    SQUARE_NUWARA_ELIYA,
    SQUARE_BANK_OF_CEYLON,
    SQUARE_GALLE_FACE,
    SQUARE_COUNT
} enumSquareName;


typedef struct  {     // declaring a square
    
    SquareType square_type;
    property property;
    railway railway;
    utilities utility;
    char square_name[30];
    enumSquareName enumName;
   
    } Square;




typedef struct {
    Square squares[40];
     EventDeck event_deck;
     Regional_Card_Deck regional_deck;
} Board;

typedef struct {
    PropertyGroup boom_property_group;
    int boom_expiration_round;
    
    PropertyGroup decline_property_group;
    int decline_expiration_round;
    
    char regional_development_name[50];
    int regional_development_percentage;
    int regional_development_expiration_round;
    
    int inflation_percentage;
    Bank_Details loan_interest_percentage;
} MarketConditionsState;



extern Bank_Details bank;



#endif