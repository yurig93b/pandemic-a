//
// Created by Yuri Grigorian on 05/05/2021.
//

#ifndef PANDEMIC_A_GENESPLICER_HPP
#define PANDEMIC_A_GENESPLICER_HPP


#include "Player.hpp"

namespace pandemic {
    class GeneSplicer : public Player {
        public:
            using Player::Player;
            Player & discover_cure(Color c) override{return *this;};
            std::string role() override{ return "GeneSplicer"; }

    };
}



#endif //PANDEMIC_A_GENESPLICER_HPP
