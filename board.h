#ifndef BOARD_H
#define BOARD_H




extern Board gameBoard;
void initialize_board();
int roll_dice();
int compareRoll(const void *a, const void *b);
void players_order();
void player_rolling_order();

void player_playing_order(void);






#endif