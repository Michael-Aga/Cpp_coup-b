#include <iostream>
#include <stdexcept>
#include "Player.hpp"

using namespace std;

namespace coup
{
    class Duke : public Player
    {
    public:
        Duke(Game &current_game, string dukes_name) : Player(current_game, dukes_name, "Duke"){};

        void block(Player &player);

        void check_valid_tax();

        void tax();
    };
}