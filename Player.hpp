//
// Created by Yuri Grigorian on 05/05/2021.
//

#ifndef PANDEMIC_A_BASEPLAYER_HPP
#define PANDEMIC_A_BASEPLAYER_HPP

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"

namespace pandemic{
    class Player{

        protected:
            Board &board;
            const City city;

        public:
            Player(Board &b, City c): board(b), city(c){};

            virtual void build(){};
            Player& drive(City c){return *this; };
            Player& take_card(City c){ return *this;};
            virtual Player& fly_direct(City c){return *this;};
            Player& fly_charter(City c){return *this;};
            Player& fly_shuttle(City c){return *this;};
            virtual Player& treat(City c){ return *this;};
            virtual Player& discover_cure(Color c){ return *this;};
            virtual std::string role(){throw std::runtime_error("Not impl.");}

            City get_location(){return city;}
            bool has_card(City c){return false;}
    };
}

#endif //PANDEMIC_A_BASEPLAYER_HPP
