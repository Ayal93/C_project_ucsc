
#ifndef PLAYER_H
#define PLAYER_H


typedef struct {

    int noOf_railway_stations;

}Player_Assets;


typedef struct{

 char player_name[20];
 int player_order;
 int die_value;
 int player_current_position;
 int player_round_number;
 Player_Assets assets;
 int players_square_type;

}Player;


extern Player players[4];





#endif

