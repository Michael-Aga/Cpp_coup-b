#include <iostream>
#include <stdexcept>
#include "Player.hpp"

using namespace std;

namespace coup
{

    class Captain : public Player
    {
    public:
        Captain(Game &current_game, string captains_name) : Player(current_game, captains_name, "Captain"){};

        void check_valid_block(Player &player) const;

        void block(Player &player);

        void check_valid_steal(Player &player);

        void steal(Player &player);
    };
}