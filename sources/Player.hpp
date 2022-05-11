#include <iostream>
#include "Game.hpp"
#include <map>
#pragma once

using namespace std;

namespace coup
{

    class Game;

    class Player
    {
    protected:
        Game &current_game;
        string players_role;
        string players_name;
        int players_coins;
        bool is_active;
        vector<string> last_action;

    public:
        Player(Game &current_game, string const &players_name, string players_role);

        void check_valid_player() const;
        void check_valid_coup(Player &player) const;

        void income();
        void foreign_aid();
        void coup(Player &player);
        string role();
        int coins() const;

        bool get_player_status() const;
        void set_player_status(bool status);
        void coins_quantity(int num);
        string get_players_name();
        vector<string> get_last_action();
    };
}