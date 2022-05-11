#include <iostream>
#include "Assassin.hpp"
#include "Player.hpp"

using namespace std;

int const COINS_FOR_COUP = 7;
int const ASSASSINATION = 3;

namespace coup
{
    void Assassin::check_valid_coup(Player &player)
    {
        if (this->current_game.turn() != this->get_players_name())
        {
            throw invalid_argument("This is not your turn to play !");
        }
        if (!player.get_player_status() || current_game.get_player(player.get_players_name()) == NULL)
        {
            throw invalid_argument("Cant coup an inactive player !");
        }
    }

    void Assassin::coup(Player &player)
    {
        check_valid_coup(player);

        if (this->coins() >= COINS_FOR_COUP)
        {
            Player::coup(player);
            return;
        }

        if (this->coins() < ASSASSINATION)
        {
            throw invalid_argument("You dont have enough coins to assassinate");
        }

        if (this->current_game.get_game_status())
        {
            player.set_player_status(false);
            this->coins_quantity(-3);
            this->last_action.clear();
            this->last_action.push_back("Assassination");
            this->last_action.push_back(player.get_players_name());
            this->current_game.update_turn_counter();
        }
        else
        {
            throw invalid_argument("The game is unplayable !");
        }
    }
}