#include <iostream>
#include "Player.hpp"

using namespace std;

namespace coup
{

    class Ambassador : public Player
    {
    public:
        Ambassador(Game &current_game, string ambassador_name) : Player(current_game, ambassador_name, "Ambassador"){};

        void check_valid_transfer(Player &from_player, Player &to_player);

        void transfer(Player &from_player, Player &to_player);

        void check_valid_block(Player &player) const;

        void block(Player &player);
    };
}