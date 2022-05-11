#include <iostream>
#include "Player.hpp"
#include "Ambassador.hpp"

using namespace std;

namespace coup
{

    void Ambassador::check_valid_transfer(Player &from_player, Player &to_player)
    {
        if (this->current_game.turn() != this->get_players_name())
        {
            throw invalid_argument("This is not your turn to play !");
        }

        if ((!from_player.get_player_status()) || (!to_player.get_player_status()) ||
            this->current_game.get_player(from_player.get_players_name()) == NULL || this->current_game.get_player(to_player.get_players_name()) == NULL)
        {
            throw invalid_argument("Both of the players need to be active !");
        }

        if (from_player.coins() == 0)
        {
            throw invalid_argument("Cant transfer from 0 coins !");
        }
    }

    void Ambassador::transfer(Player &from_player, Player &to_player)
    {
        check_valid_transfer(from_player, to_player);

        if (this->current_game.get_game_status())
        {
            from_player.coins_quantity(-1);
            to_player.coins_quantity(+1);
            this->last_action.clear();
            this->last_action.push_back("Transfer");
            this->last_action.push_back(from_player.get_players_name());
            this->current_game.update_turn_counter();
        }
        else
        {
            throw invalid_argument("The game is unplayable");
        }
    }

    void Ambassador::check_valid_block(Player &player) const
    {
        if (player.role() != "Captain")
        {
            throw invalid_argument("Cant block another player who is not a Captain !");
        }
        if (!player.get_player_status() || current_game.get_player(player.get_players_name()) == NULL)
        {
            throw invalid_argument("Cant block an inactive player !");
        }
    }

    void Ambassador::block(Player &player)
    {
        check_valid_block(player);

        if (this->current_game.get_game_status())
        {
            if (player.get_last_action()[0] == "Steal" && player.coins() >= 2)
            {
                current_game.get_player(player.get_last_action()[1])->coins_quantity(2);
                player.coins_quantity(-2);
                this->last_action.clear();
                this->last_action.push_back("Block");
                this->last_action.push_back(player.get_players_name());
            }
            else
            {
                throw invalid_argument("Cant block this player !");
            }
        }
        else
        {
            throw invalid_argument("The game is unplayable !");
        }
    }
}