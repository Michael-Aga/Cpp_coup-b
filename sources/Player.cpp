#include <iostream>
#include "Player.hpp"
#include "Game.hpp"
#include <map>

using namespace std;

int const MAX_PLAYERS_IN_GAME = 6;
int const MAX_COINS = 10;
int const COINS_FOR_COUP = 7;

namespace coup
{
    Player::Player(Game &current_game, string const &players_name, string players_role) : current_game(current_game)
    {
        if (current_game.amount_of_total_players() >= MAX_PLAYERS_IN_GAME || current_game.get_game_status())
        {
            throw invalid_argument("Pleaes check the number of players and that the game didnt start already");
        }
        this->current_game.add_player(this);
        this->is_active = true;
        this->players_name = players_name;
        this->players_coins = 0;
        this->players_role = move(players_role);
    }

    void Player::check_valid_player() const
    {
        if (this->current_game.players().size() == 1)
        {
            throw invalid_argument("You need more players to play the game !");
        }
        if (this->current_game.turn() != this->players_name)
        {
            throw invalid_argument("Please wait for your turn to play !");
        }
        if (this->coins() >= MAX_COINS)
        {
            throw invalid_argument("You got max coins, now you need to coup someone !");
        }
        if (!this->current_game.get_game_status())
        {
            this->current_game.set_game_status();
        }
    }

    void Player::check_valid_coup(Player &player) const
    {
        if (!player.get_player_status())
        {
            throw invalid_argument("Cant coup the player because he is inactive !");
        }
        if (this->current_game.turn() != this->players_name)
        {
            throw invalid_argument("Please wait for your turn !");
        }
        if (this->coins() < COINS_FOR_COUP)
        {
            throw invalid_argument("You need 7 coins to coup !");
        }
    }

    void Player::income()
    {
        check_valid_player();
        this->players_coins++;
        this->last_action.clear();
        this->last_action.push_back("income");
        this->last_action.push_back("null");
        this->current_game.update_turn_counter();
    }

    void Player::foreign_aid()
    {
        check_valid_player();
        this->players_coins += 2;
        this->last_action.clear();
        this->last_action.push_back("foreign_aid");
        this->last_action.push_back("null");
        this->current_game.update_turn_counter();
    }

    void Player::coup(Player &player)
    {
        check_valid_coup(player);
        this->coins_quantity(-COINS_FOR_COUP);
        player.set_player_status(false);
        this->last_action.clear();
        this->last_action.push_back("coup");
        this->last_action.push_back(player.get_players_name());
        this->current_game.update_turn_counter();
    }

    string Player::role()
    {
        return this->players_role;
    }

    int Player::coins() const
    {
        return this->players_coins;
    }

    bool Player::get_player_status() const
    {
        return this->is_active;
    }

    void Player::set_player_status(bool status)
    {
        this->is_active = status;
    }

    void Player::coins_quantity(int num)
    {
        this->players_coins += num;
    }

    string Player::get_players_name()
    {
        return this->players_name;
    }

    vector<string> Player::get_last_action()
    {
        return this->last_action;
    }
}