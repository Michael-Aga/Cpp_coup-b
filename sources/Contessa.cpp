#include <iostream>
#include <string>
#include "Player.hpp"
#include "Contessa.hpp"

using namespace std;

namespace coup
{
    void Contessa::check_valid_block(Player &player) const
    {
        if (player.role() != "Assassin" || player.get_last_action()[0] == "coup")
        {
            throw invalid_argument("Cant block a regular coup");
        }
        if (!player.get_player_status() || current_game.get_player(player.get_players_name()) == NULL)
        {
            throw invalid_argument("This player is inactive !");
        }
    }

    void Contessa::block(Player &player)
    {
        check_valid_block(player);

        if (this->current_game.get_game_status())
        {
            if (player.get_last_action()[0] == "Assassination")
            {
                current_game.get_player(player.get_last_action()[1])->set_player_status(true);
                this->last_action.clear();
                this->last_action.push_back("Block");
                this->last_action.push_back(player.get_players_name());
            }
            else
            {
                throw invalid_argument("Cant block !");
            }
        }
        else
        {
            throw invalid_argument("The game is unplayable !");
        }
    }
}