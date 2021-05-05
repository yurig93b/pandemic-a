//
// Created by Yuri Grigorian on 05/05/2021.
//

#ifndef PANDEMIC_A_DISPATCHER_HPP
#define PANDEMIC_A_DISPATCHER_HPP

#include "Player.hpp"

namespace pandemic{
    class Dispatcher: public Player{
        public:
            using Player::Player;

            Player & fly_direct(City c) override{return *this;};
            std::string role() override{ return "Disptacher"; }
    };
}
#endif //PANDEMIC_A_DISPATCHER_HPP
