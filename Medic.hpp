//
// Created by Yuri Grigorian on 05/05/2021.
//

#ifndef PANDEMIC_A_MEDIC_HPP
#define PANDEMIC_A_MEDIC_HPP

#include "Player.hpp"

namespace pandemic{
    class Medic: public Player{
        public:
            using Player::Player;
            Player & treat(City c) override{return *this;};
            std::string role() override{ return "Medic"; }

    };
}
#endif //PANDEMIC_A_MEDIC_HPP
