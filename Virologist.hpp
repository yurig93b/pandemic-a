//
// Created by Yuri Grigorian on 05/05/2021.
//

#ifndef PANDEMIC_A_VIROLOGIST_HPP
#define PANDEMIC_A_VIROLOGIST_HPP


#include "Player.hpp"


namespace pandemic {
    class Virologist : public Player {
        public:
            using Player::Player;
            Player & treat(City c) override{ return *this;};
            std::string role() override{ return "Virologist"; }

    };
}



#endif //PANDEMIC_A_VIROLOGIST_HPP
