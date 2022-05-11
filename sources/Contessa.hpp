#include <iostream>
#include "Player.hpp"
using namespace std;

namespace coup
{

    class Contessa : public Player
    {
    public:
        Contessa(Game &current_game, string contessas_name) : Player(current_game, contessas_name, "Contessa"){};

        void check_valid_block(Player &player) const;

        void block(Player &player);
    };
}