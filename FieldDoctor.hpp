//
// Created by Yuri Grigorian on 05/05/2021.
//

#ifndef PANDEMIC_A_FIELDDOCTOR_HPP
#define PANDEMIC_A_FIELDDOCTOR_HPP


#include "Player.hpp"

namespace pandemic {
    class FieldDoctor : public Player {
        public:
            using Player::Player;
            Player & treat(City c) override{ return *this;};
            std::string role() override{ return "FieldDoctor"; }

    };
}



#endif //PANDEMIC_A_FIELDDOCTOR_HPP
