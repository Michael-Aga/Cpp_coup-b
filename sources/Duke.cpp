#include <iostream>
#include "Duke.hpp"
#include "Player.hpp"

using namespace std;

int const MAX_COINS = 10;

namespace coup
{
        void Duke::block(Player &player)
        {
                if (!player.get_player_status() || current_game.get_player(player.get_players_name()) == NULL)
                {
                        throw invalid_argument("This player is not playing right now !");
                }

                if (this->current_game.get_game_status())
                {
                        if (player.get_last_action()[0] == "foreign_aid" && player.coins() >= 2)
                        {
                                player.coins_quantity(-2);
                                this->last_action.clear();
                                this->last_action.push_back("Block");
                                this->last_action.push_back(player.get_players_name());
                        }
                        else
                        {
                                throw invalid_argument("You cant use block !");
                        }
                }
                else
                {
                        throw invalid_argument("The game is unplayable !");
                }
        }

        void Duke::check_valid_tax()
        {
                if (this->role() != "Duke")
                {
                        throw invalid_argument("You need to be a Duke to use tax !");
                }

                if (this->current_game.turn() != this->get_players_name())
                {
                        throw invalid_argument("Please wait for your turn !");
                }

                if (this->coins() >= MAX_COINS)
                {
                        throw invalid_argument("You got max coins, now you need to coup someone !");
                }
        }

        void Duke::tax()
        {
                check_valid_tax();
                this->coins_quantity(3);
                this->last_action.clear();
                this->last_action.push_back("tax");
                this->last_action.push_back("null");
                this->current_game.update_turn_counter();
        }
}