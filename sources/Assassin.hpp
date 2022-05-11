#include <iostream>
#include "Player.hpp"

using namespace std;

namespace coup
{

    class Assassin : public Player
    {
    public:
        Assassin(Game &current_game, string assassin_name) : Player(current_game, assassin_name, "Assassin"){};

        void check_valid_coup(Player &player);

        void coup(Player &player);
    };
}