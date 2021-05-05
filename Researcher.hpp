//
// Created by Yuri Grigorian on 05/05/2021.
//

#ifndef PANDEMIC_A_RESEARCHER_HPP
#define PANDEMIC_A_RESEARCHER_HPP

#include "Player.hpp"

namespace pandemic{
    class Researcher: public Player{
        public:
            using Player::Player;

            Player & discover_cure(Color c) override{return *this;};
            std::string role() override{ return "Researcher"; }

    };
}

#endif //PANDEMIC_A_RESEARCHER_HPP
