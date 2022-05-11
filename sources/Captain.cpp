#include <iostream>
#include "Captain.hpp"
#include "Player.hpp"

using namespace std;

namespace coup
{
    void Captain::check_valid_block(Player &player) const
    {
        if (player.role() != "Captain")
        {
            throw invalid_argument("Cant block a player that is not a Captain !");
        }
        if (!player.get_player_status() || this->current_game.get_player(player.get_players_name()) == NULL)
        {
            throw invalid_argument("Cant block an inactive player !");
        }
    }

    void Captain::block(Player &player)
    {
        check_valid_block(player);

        if (this->current_game.get_game_status())
        {
            if (player.get_last_action()[0] == "Steal")
            {
                this->current_game.get_player(player.get_last_action()[1])->coins_quantity(2);
                player.coins_quantity(-2);
                this->last_action.clear();
                this->last_action.push_back("Block");
                this->last_action.push_back(player.get_players_name());
            }
        }
        else
        {
            throw invalid_argument("The game is unplayable !");
        }
    }

    void Captain::check_valid_steal(Player &player)
    {
        if (this->current_game.turn() != this->get_players_name())
        {
            throw invalid_argument("This is not your turn to play !");
        }
        if (!player.get_player_status() || this->current_game.get_player(player.get_players_name()) == NULL)
        {
            throw invalid_argument("Cant steal from an inactive player !");
        }
    }

    void Captain::steal(Player &player)
    {
        check_valid_steal(player);

        if (this->current_game.get_game_status())
        {
            if (player.coins() >= 2)
            {
                player.coins_quantity(-2);
                this->coins_quantity(2);
                this->last_action.clear();
                this->last_action.push_back("Steal");
                this->last_action.push_back(player.get_players_name());
                this->current_game.update_turn_counter();
            }

            else if (player.coins() == 1)
            {
                player.coins_quantity(-1);
                this->coins_quantity(1);
                this->last_action.clear();
                this->last_action.push_back("Steal");
                this->last_action.push_back(player.get_players_name());
                this->current_game.update_turn_counter();
            }
            else
            {
                throw invalid_argument("You cant steal out of 0 coins !");
            }
        }
        else
        {
            throw invalid_argument("The game is unplayable !");
        }
    }
}