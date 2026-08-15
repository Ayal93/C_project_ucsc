#include <stdio.h>
#include "game.h"
#include "type.h"
#include <stdlib.h>
#include "players.h"
#include <time.h>
#include "board.h"
#include "Auctions.h"
#include "finance.h"
#include "events.h"
Board gameBoard;
Bank_Details bank = {0};

void initialize_board() {
  Square squares[40] = {

    {.square_type = Start,
     .property = {.property_name = "GO", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "GO",
     .enumName = SQUARE_GO},

    {.square_type = Property,
     .property = {.property_name = "Pettah", .group = Brown, .Purchase_Price = 1500, .Mortgage_Value = 750, .Base_Rental = 100, .House_Construction_Cost = 500, .Hotel_Construction_Cost = 2000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Pettah",
     .enumName = SQUARE_PETTAH},

    {.square_type = Event,
     .property = {.property_name = "Community Development Fund", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Community Development Fund",
     .enumName = SQUARE_COMMUNITY_DEVELOPMENT_FUND},

    {.square_type = Property,
     .property = {.property_name = "Maradana", .group = Brown, .Purchase_Price = 1800, .Mortgage_Value = 900, .Base_Rental = 120, .House_Construction_Cost = 500, .Hotel_Construction_Cost = 2000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Maradana",
     .enumName = SQUARE_MARADANA},

    {.square_type = Tax,
     .property = {.property_name = "Income Tax", .Current_Owner = -1, .Tax_Amount = 2000.00},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Income Tax",
     .enumName = SQUARE_INCOME_TAX},

    {.square_type = Railway,
     .property = {.property_name = "Colombo Fort Railway Station", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Purchase_Price = 8000, .railway_morgadge_price = 4000, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Colombo Fort Railway Station",
     .enumName = SQUARE_COLOMBO_FORT_RAILWAY_STATION},

    {.square_type = Property,
     .property = {.property_name = "Bambalapitiya", .group = LightBlue, .Purchase_Price = 2500, .Mortgage_Value = 1250, .Base_Rental = 180, .House_Construction_Cost = 750, .Hotel_Construction_Cost = 3000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Bambalapitiya",
     .enumName = SQUARE_BAMBALAPITIYA},

    {.square_type = Event,
     .property = {.property_name = "National Event Card", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "National Event Card",
     .enumName = SQUARE_NATIONAL_EVENT_CARD_1},

    {.square_type = Property,
     .property = {.property_name = "Wellawatte", .group = LightBlue, .Purchase_Price = 2700, .Mortgage_Value = 1350, .Base_Rental = 200, .House_Construction_Cost = 750, .Hotel_Construction_Cost = 3000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Wellawatte",
     .enumName = SQUARE_WELLAWATTE},

    {.square_type = Property,
     .property = {.property_name = "Mount Lavinia", .group = LightBlue, .Purchase_Price = 3000, .Mortgage_Value = 1500, .Base_Rental = 220, .House_Construction_Cost = 750, .Hotel_Construction_Cost = 3000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Mount Lavinia",
     .enumName = SQUARE_MOUNT_LAVINIA},

    {.square_type = Special,
     .property = {.property_name = "Jail / Just Visiting", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Jail / Just Visiting",
     .enumName = SQUARE_JAIL},

    {.square_type = Property,
     .property = {.property_name = "Nugegoda", .group = Pink, .Purchase_Price = 3500, .Mortgage_Value = 1750, .Base_Rental = 260, .House_Construction_Cost = 1000, .Hotel_Construction_Cost = 4000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Nugegoda",
     .enumName = SQUARE_NUGEGODA},

    {.square_type = Utility,
     .property = {.property_name = "Ceylon Electricity Board", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Purchase_Price = 1500, .utility_morgadge_price = 750, .Mortgage_Status = 0},
     .square_name = "Ceylon Electricity Board",
     .enumName = SQUARE_CEYLON_ELECTRICITY_BOARD},

    {.square_type = Property,
     .property = {.property_name = "Maharagama", .group = Pink, .Purchase_Price = 3800, .Mortgage_Value = 1900, .Base_Rental = 280, .House_Construction_Cost = 1000, .Hotel_Construction_Cost = 4000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Maharagama",
     .enumName = SQUARE_MAHARAGAMA},

    {.square_type = Property,
     .property = {.property_name = "Kottawa", .group = Pink, .Purchase_Price = 4000, .Mortgage_Value = 2000, .Base_Rental = 300, .House_Construction_Cost = 1000, .Hotel_Construction_Cost = 4000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Kottawa",
     .enumName = SQUARE_KOTTAWA},

    {.square_type = Railway,
     .property = {.property_name = "Kandy Railway Station", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Purchase_Price = 8000, .railway_morgadge_price = 4000, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Kandy Railway Station",
     .enumName = SQUARE_KANDY_RAILWAY_STATION},

    {.square_type = Property,
     .property = {.property_name = "Negombo", .group = Orange, .Purchase_Price = 4500, .Mortgage_Value = 2250, .Base_Rental = 350, .House_Construction_Cost = 1250, .Hotel_Construction_Cost = 5000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Negombo",
     .enumName = SQUARE_NEGOMBO},

    {.square_type = Insurance,
     .property = {.property_name = "Sri Lanka Insurance", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Sri Lanka Insurance",
     .enumName = SQUARE_SRI_LANKA_INSURANCE},

    {.square_type = Property,
     .property = {.property_name = "Katunayake", .group = Orange, .Purchase_Price = 4700, .Mortgage_Value = 2350, .Base_Rental = 370, .House_Construction_Cost = 1250, .Hotel_Construction_Cost = 5000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Katunayake",
     .enumName = SQUARE_KATUNAYAKE},

    {.square_type = Property,
     .property = {.property_name = "Ja-Ela", .group = Orange, .Purchase_Price = 5000, .Mortgage_Value = 2500, .Base_Rental = 400, .House_Construction_Cost = 1250, .Hotel_Construction_Cost = 5000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Ja-Ela",
     .enumName = SQUARE_JA_ELA},

    {.square_type = Special,
     .property = {.property_name = "Free Parking", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Free Parking",
     .enumName = SQUARE_FREE_PARKING},

    {.square_type = Property,
     .property = {.property_name = "Kandy City", .group = Red, .Purchase_Price = 5500, .Mortgage_Value = 2750, .Base_Rental = 450, .House_Construction_Cost = 1500, .Hotel_Construction_Cost = 6000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Kandy City",
     .enumName = SQUARE_KANDY_CITY},

    {.square_type = Event,
     .property = {.property_name = "National Event Card", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "National Event Card",
     .enumName = SQUARE_NATIONAL_EVENT_CARD_2},

    {.square_type = Property,
     .property = {.property_name = "Peradeniya", .group = Red, .Purchase_Price = 5800, .Mortgage_Value = 2900, .Base_Rental = 480, .House_Construction_Cost = 1500, .Hotel_Construction_Cost = 6000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Peradeniya",
     .enumName = SQUARE_PERADENIYA},

    {.square_type = Property,
     .property = {.property_name = "Katugastota", .group = Red, .Purchase_Price = 6000, .Mortgage_Value = 3000, .Base_Rental = 500, .House_Construction_Cost = 1500, .Hotel_Construction_Cost = 6000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Katugastota",
     .enumName = SQUARE_KATUGASTOTA},

    {.square_type = Railway,
     .property = {.property_name = "Galle Railway Station", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Purchase_Price = 8000, .railway_morgadge_price = 4000, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Galle Railway Station",
     .enumName = SQUARE_GALLE_RAILWAY_STATION},

    {.square_type = Property,
     .property = {.property_name = "Galle Fort", .group = Yellow, .Purchase_Price = 6500, .Mortgage_Value = 3250, .Base_Rental = 600, .House_Construction_Cost = 2000, .Hotel_Construction_Cost = 8000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Galle Fort",
     .enumName = SQUARE_GALLE_FORT},

    {.square_type = Property,
     .property = {.property_name = "Unawatuna", .group = Yellow, .Purchase_Price = 6800, .Mortgage_Value = 3400, .Base_Rental = 620, .House_Construction_Cost = 2000, .Hotel_Construction_Cost = 8000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Unawatuna",
     .enumName = SQUARE_UNAWATUNA},

    {.square_type = Utility,
     .property = {.property_name = "National Water Supply Board", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Purchase_Price = 1500, .utility_morgadge_price = 750, .Mortgage_Status = 0},
     .square_name = "National Water Supply Board",
     .enumName = SQUARE_NATIONAL_WATER_SUPPLY_BOARD},

    {.square_type = Property,
     .property = {.property_name = "Hikkaduwa", .group = Yellow, .Purchase_Price = 7000, .Mortgage_Value = 3500, .Base_Rental = 650, .House_Construction_Cost = 2000, .Hotel_Construction_Cost = 8000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Hikkaduwa",
     .enumName = SQUARE_HIKKADUWA},

    {.square_type = Special,
     .property = {.property_name = "Go To Jail", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Go To Jail",
     .enumName = SQUARE_GO_TO_JAIL},

    {.square_type = Property,
     .property = {.property_name = "Jaffna Town", .group = Green, .Purchase_Price = 8000, .Mortgage_Value = 4000, .Base_Rental = 750, .House_Construction_Cost = 2500, .Hotel_Construction_Cost = 10000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Jaffna Town",
     .enumName = SQUARE_JAFFNA_TOWN},

    {.square_type = Property,
     .property = {.property_name = "Nallur", .group = Green, .Purchase_Price = 8300, .Mortgage_Value = 4150, .Base_Rental = 780, .House_Construction_Cost = 2500, .Hotel_Construction_Cost = 10000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Nallur",
     .enumName = SQUARE_NALLUR},

    {.square_type = Insurance,
     .property = {.property_name = "Ceylinco Insurance", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Ceylinco Insurance",
     .enumName = SQUARE_CEYLINCO_INSURANCE},

    {.square_type = Property,
     .property = {.property_name = "Trincomalee", .group = Green, .Purchase_Price = 8500, .Mortgage_Value = 4250, .Base_Rental = 800, .House_Construction_Cost = 2500, .Hotel_Construction_Cost = 10000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Trincomalee",
     .enumName = SQUARE_TRINCOMALEE},

    {.square_type = Railway,
     .property = {.property_name = "Jaffna Railway Station", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Purchase_Price = 8000, .railway_morgadge_price = 4000, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Jaffna Railway Station",
     .enumName = SQUARE_JAFFNA_RAILWAY_STATION},

    {.square_type = Event,
     .property = {.property_name = "National Event Card", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "National Event Card",
     .enumName = SQUARE_NATIONAL_EVENT_CARD_3},

    {.square_type = Property,
     .property = {.property_name = "Nuwara Eliya", .group = DarkBlue, .Purchase_Price = 10000, .Mortgage_Value = 5000, .Base_Rental = 1000, .House_Construction_Cost = 3000, .Hotel_Construction_Cost = 12000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Nuwara Eliya",
     .enumName = SQUARE_NUWARA_ELIYA},

    {.square_type = Bank,
     .property = {.property_name = "Bank of Ceylon", .Current_Owner = -1},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Bank of Ceylon",
     .enumName = SQUARE_BANK_OF_CEYLON},

    {.square_type = Property,
     .property = {.property_name = "Galle Face", .group = DarkBlue, .Purchase_Price = 12000, .Mortgage_Value = 6000, .Base_Rental = 1200, .House_Construction_Cost = 3000, .Hotel_Construction_Cost = 12000, .Current_Owner = -1, .no_of_House_Construction = 0, .no_of_Hotel_Construction = 0, .Mortgage_Status = 0},
     .railway  = {.current_railway_owner = -1, .Mortgage_Status = 0},
     .utility  = {.Utility_owner = -1, .number_of_Utilities = 0, .Mortgage_Status = 0},
     .square_name = "Galle Face",
     .enumName = SQUARE_GALLE_FACE}
};

  for (int i = 0; i < 40; i++) {
    gameBoard.squares[i] = squares[i];
  }
     initialize_event_deck(&gameBoard.event_deck);
}

int roll_dice(int *is_double){   
    int num1 = (rand() % 6) + 1;
    int num2 = (rand() % 6) + 1;

      if (num1 == num2)
    {
        *is_double = 1;
    }
    else
    {
        *is_double = 0;
    }

    return num1 + num2;
}
int compareRoll(const void *a, const void *b)
{
    Player *p1 = (Player *)a;
    Player *p2 = (Player *)b;
    return p2->die_value - p1->die_value; // compare func
}



void players_order(){
    int is_double; 

    for (int i = 0; i < 4; i++) {
     players[i].die_value = roll_dice(&is_double); 
    
                                                //each player a random value get
}





        qsort(players, 4, sizeof(Player), compareRoll);

        int k=0;
       //if 2 players has same die value take them and roll die again 
     int tieFound;
    do
    {
        tieFound = 0;

        for (int i = 0; i < 3; i++)
        {
            if (players[i].die_value == players[i + 1].die_value)
            {
                tieFound = 1;

                // Find all players in this tie
                int start = i;
                int end = i;

                while (end < 3 &&
                       players[end].die_value == players[end + 1].die_value)
                {
                    end++;
                }

                 for (int j = start; j <= end; j++)
                {
                    players[j].die_value = roll_dice(&is_double);   
                }

                // Sort again
                qsort(players, 4, sizeof(Player), compareRoll);

                break;      
            }
        }

    } while (tieFound);
    




   for(int i = 0; i < 4; i++)
    {
        players[i].player_order = i + 1;      //initialize to player structuer 
    }

};
   
void player_rolling_order() 
{
    printf("\n\n");
    for (int i = 0; i < 4; i++) 
    {
        printf("%s rolls %d\n", players[i].player_name, players[i].die_value);
    }

    printf("\n\n");

    for (int i = 0; i < 4; i++) 
    {
        if (players[i].player_order == 1) 
        {
            printf("%s will begin the game.\n", players[i].player_name);
            break;
        }
    }
}

void player_playing_order(){
    printf("\n\n");
    printf("Turn Order:\n");
    printf("%s\n",players[0].player_name);
    printf("%s\n",players[1].player_name);
    printf("%s\n",players[2].player_name);
    printf("%s\n",players[3].player_name);
    printf("\n");
}

//--------end of the playing order selecting----------------


