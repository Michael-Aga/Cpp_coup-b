#include <iostream>
#include <vector>
#pragma once

using namespace std;

namespace coup
{

    class Player;

    class Game
    {
    private:
        vector<Player *> total_players;
        size_t turn_counter;
        bool did_the_game_start;

    public:
        Game();
        string turn();
        vector<string> players();
        string winner();

        void update_turn_counter();
        Player *get_player(string const &name);
        int get_players_location(Player *player);
        void add_player(Player *player);
        bool get_game_status() const;
        void set_game_status();
        size_t amount_of_total_players();
        int amount_of_active_players();
    };
}