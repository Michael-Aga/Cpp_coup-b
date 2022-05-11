#include <iostream>
#include <vector>
#include "Player.hpp"
#include "Game.hpp"

using namespace std;

namespace coup
{
    Game::Game()
    {
        this->turn_counter = 0;
        this->did_the_game_start = false;
    }

    string Game::turn()
    {
        return this->total_players[turn_counter]->get_players_name();
    }

    vector<string> Game::players()
    {
        vector<string> active_players;

        for (Player *current_player : this->total_players)
        {
            if (current_player->get_player_status())
            {
                active_players.push_back(current_player->get_players_name());
            }
        }
        return active_players;
    }

    string Game::winner()
    {
        if (!this->get_game_status() || this->amount_of_active_players() > 1)
        {
            throw invalid_argument("No one won for now !");
        }

        string game_winner;

        for (Player *candidate : this->total_players)
        {
            if (candidate->get_player_status())
            {
                game_winner = candidate->get_players_name();
            }
        }

        return game_winner;
    }

    void Game::update_turn_counter()
    {
        this->turn_counter++;
        this->turn_counter = this->turn_counter % this->total_players.size();
        while (!this->total_players[this->turn_counter]->get_player_status())
        {
            this->turn_counter++;
            this->turn_counter = this->turn_counter % this->total_players.size();
        }
    }

    Player *Game::get_player(string const &wanted_player_name)
    {
        for (Player *player : this->total_players)
        {
            if (player->get_players_name() == wanted_player_name)
            {
                return player;
            }
        }
        return NULL;
    }

    int Game::get_players_location(Player *player)
    {
        int player_location = 0;
        for (size_t i = 0; i < total_players.size(); i++)
        {
            if (total_players[i]->get_players_name() == player->get_players_name())
            {
                player_location = i;
            }
        }
        return player_location;
    }

    void Game::add_player(Player *player)
    {
        this->total_players.push_back(player);
    }

    bool Game::get_game_status() const
    {
        return did_the_game_start;
    }

    void Game::set_game_status()
    {
        did_the_game_start = true;
    }

    size_t Game::amount_of_total_players()
    {
        return this->total_players.size();
    }

    int Game::amount_of_active_players()
    {
        int amount = 0;

        for (Player *player : total_players)
        {
            if (player->get_player_status())
            {
                amount++;
            }
        }

        return amount;
    }
}