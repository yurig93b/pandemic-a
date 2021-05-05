//
// Created by Yuri Grigorian on 05/05/2021.
//

#ifndef PANDEMIC_A_SCIENTIST_HPP
#define PANDEMIC_A_SCIENTIST_HPP


#include "Player.hpp"

namespace pandemic {
    class Scientist : public Player {

            unsigned int cards_needed;
        public:
            Scientist(Board &b, City c, unsigned int card_needed) : Player(b, c), cards_needed(card_needed) {};

            Player &discover_cure(Color c) override { return *this; };

            std::string role() override{ return "Scientist"; }

    };
}


#endif //PANDEMIC_A_SCIENTIST_HPP
