#include <stdio.h>
#include "Auctions.h"
#include "type.h"
#include "players.h"
#include "board.h"

void run_auction(Square *square, Player players[], int num_players)
{
    printf("Auction Started.\n\n");
    printf("Property :\n%s\n\n", square->square_name);

    double current_bid = square->property.Purchase_Price * 0.50;
    printf("Opening Bid :\nLKR %.0f.\n\n", current_bid);

    int active_in_auction[4] = {0, 0, 0, 0};
    int active_bidders_count = 0;

    for (int i = 0; i < num_players; i++)
    {
        if (!players[i].status_bankrupt)
        {
            active_in_auction[i] = 1;
            active_bidders_count++;
        }
    }

    int highest_bidder_index = -1;
    int current_turn = 0;

    while (active_bidders_count > (highest_bidder_index != -1 ? 1 : 0))
    {
        if (active_in_auction[current_turn] == 0)
        {
            current_turn = (current_turn + 1) % num_players;
            continue;
        }

        Player *p = &players[current_turn];

        double next_min_bid;
        if (highest_bidder_index == -1)
        {
            next_min_bid = current_bid;
        }
        else
        {
            next_min_bid = current_bid + 250.0;
        }

        if (p->player_cash_in_hand < next_min_bid)
        {
            printf("%s withdraws.\n\n", p->player_name);
            active_in_auction[current_turn] = 0;
            active_bidders_count--;
        }
        else
        {
            int wants_to_bid = 0;

            switch (p->name_by_enum)
            {
                case Aggressive_Investor:
                    if (next_min_bid <= square->property.Purchase_Price * 1.20)
                        wants_to_bid = 1;
                    break;
                case Conservative_Banker:
                    if (next_min_bid < square->property.Purchase_Price)
                        wants_to_bid = 1;
                    break;
                case Risk_Taker:
                    if (p->player_cash_in_hand >= next_min_bid)
                        wants_to_bid = 1;
                    break;
                case Opportunistic_Trader:
                    if (next_min_bid <= square->property.Purchase_Price * 0.90)
                        wants_to_bid = 1;
                    break;
                default:
                    if (p->player_cash_in_hand >= next_min_bid)
                        wants_to_bid = 1;
                    break;
            }

            if (wants_to_bid == 1)
            {
                current_bid = next_min_bid;
                highest_bidder_index = current_turn;
                printf("%s bids LKR %.0f.\n\n", p->player_name, current_bid);
            }
            else
            {
                printf("%s withdraws.\n\n", p->player_name);
                active_in_auction[current_turn] = 0;
                active_bidders_count--;
            }
        }

        current_turn = (current_turn + 1) % num_players;

        if (highest_bidder_index != -1 && active_bidders_count == 1)
        {
            break;
        }
    }

    if (highest_bidder_index != -1)
    {
        Player *winner = &players[highest_bidder_index];
        winner->player_cash_in_hand -= current_bid;

        square->property.Current_Owner = highest_bidder_index;
        square->property.Mortgage_Status = 0;

        winner->player_owned_properties[winner->number_of_properties] = square->property;
        winner->number_of_properties++;

        printf("%s wins the auction.\n", winner->player_name);
    }
    else
    {
        printf("Ownership remains with the Bank.\n");
        square->property.Current_Owner = -1;
    }
}

int live_auctioning(Player *player)
{
    return player->is_in_auction;
}

void auction_liquidated_assets(Player *bankrupt_player, int player_index, Board *board, Player players[], int num_players)
{
    for (int k = 0; k < 40; k++)
    {
        if (board->squares[k].square_type == Property &&
            board->squares[k].property.Current_Owner == player_index &&
            board->squares[k].property.Loan_Locked == 1)
        {
            board->squares[k].property.Current_Owner = -1;
            board->squares[k].property.no_of_House_Construction = 0;
            board->squares[k].property.no_of_Hotel_Construction = 0;
            board->squares[k].property.Mortgage_Status = 0;
            board->squares[k].property.Loan_Locked = 0;

            run_auction(&board->squares[k], players, num_players);
        }
    }
}