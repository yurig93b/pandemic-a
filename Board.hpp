//
// Created by Yuri Grigorian on 05/05/2021.
//

#ifndef PANDEMIC_A_BOARD_HPP
#define PANDEMIC_A_BOARD_HPP

#include "City.hpp"
#include <iostream>

namespace pandemic {

    class Board {
        public:
            int a;

            int& operator[](City c) {
                //dummy var
                return a;
            }

            bool is_clean(){
                return true;
            }

            void remove_cures(){};
            friend std::ostream& operator<<(std::ostream& os, const Board& b);


    };
}


#endif //PANDEMIC_A_BOARD_HPP
