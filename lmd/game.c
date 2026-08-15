

#include <stdio.h>
#include "game.h"
#include "type.h"
#include <stdlib.h>
#include "players.h"
#include <time.h>
#include "board.h"



int roll_dice(void){   //roll 2 dies

    srand(time(NULL));
    int num1 = (rand() % 6) + 1;
    int num2 = (rand() % 6) + 1;

    return num1 + num2;
}



        
// --------------making the playing order-----------------------------


int compareRoll(const void *a, const void *b)
{
    Player *p1 = (Player *)a;
    Player *p2 = (Player *)b;

    return p2->die_value - p1->die_value; // compare func
}


 
  
 void players_order(){
    for (int i = 0; i < 4; i++) {
    players[i].die_value = rand() % 6 + 1;  
                                                //each player a random value get
}




qsort(players, 4, sizeof(Player), compareRoll);

   for(int i = 0; i < 4; i++)
    {
        players[i].player_order = i + 1;      //initialize to player struc
    }

};



void player_rolling_order()   //print player order
{
   for (int i = 0; i < 4; i++)
   {
        printf("%s rolls  %d\n",players[i].player_name,players[i].die_value);
   }
   

};


//--------end of the playing order selecting----------------




//poitions

int board_position =0;


void landed_square(Player *player){     // to solve the problem of identifing the type of square player landed on

    Square *currentSquare = &squares[player->player_current_position];

    switch (currentSquare-> square_type )
    {
    case Start:
            player->players_square_type = Start;
            printf("%s landed on %s\n",
                   player->player_name,
                   currentSquare->square_name);
            break;


        case Property:
            player->players_square_type = Property;
            printf("%s landed on property %s\n",
                   player->player_name,
                   currentSquare->square_name);
            break;


        case Railway:
            player->players_square_type = Railway;
            printf("%s landed on railway %s\n",
                   player->player_name,
                   currentSquare->square_name);
            break;


        case Utility:
            player->players_square_type = Utility;
            printf("%s landed on utility %s\n",
                   player->player_name,
                   currentSquare->square_name);
            break;


        case Event:
            player->players_square_type = Event;
            printf("%s landed on event square %s\n",
                   player->player_name,
                   currentSquare->square_name);
            break;


        case Tax:
            player->players_square_type = Tax;
            printf("%s landed on tax square %s\n",
                   player->player_name,
                   currentSquare->square_name);
            break;


        case Insurance:
            player->players_square_type = Insurance;
            printf("%s landed on insurance square %s\n",
                   player->player_name,
                   currentSquare->square_name);
            break;


        case Bank:
            player->players_square_type = Bank;
            printf("%s landed on bank square %s\n",
                   player->player_name,
                   currentSquare->square_name);
            break;


        case Special:
            player->players_square_type = Special;
            printf("%s landed on special square %s\n",
                   player->player_name,
                   currentSquare->square_name);
            break;

    
    }

};










// connect end of array to start 



void start_game(){

    int round_number=0;

    do               // do-while to run game 500 rounds
    {
        for (int j = 0; j < 4; j++)           // for each player 1 round to play

   {

            players[j]. player_current_position +=players[j].die_value;

                                if(players[j].player_current_position >= 40) // condition to prevent current position increase 40 
                    {
                                 players[j].player_current_position -= 40;
                                 players[j].player_round_number++;
                                 printf("%s passed GO\n" , players[j].player_name);

                                 if (players[j].player_round_number>500){  //one player can play less than or equal to 500 round
                                    return;
                                 }
                                
                                 

                    };

            

                      // a one player's movment inside here


                    //finding landed square by a player[j]

                    landed_square(&players[j]);

                    // players[j].player_round_number

                        // inside finance.c implement railway cost thats where it calculate money


        
   };

            

    } while (1);
    
   
   


}