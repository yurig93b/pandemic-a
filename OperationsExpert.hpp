//
// Created by Yuri Grigorian on 05/05/2021.
//

#ifndef PANDEMIC_A_OPERATIONSEXPERT_HPP
#define PANDEMIC_A_OPERATIONSEXPERT_HPP

#include "Player.hpp"

namespace pandemic{
    class OperationsExpert: public Player{
        public:
            using Player::Player;

            void build() override{};

            std::string role() override{ return "OperationsExpert"; }

    };
}

#endif //PANDEMIC_A_OPERATIONSEXPERT_HPP
