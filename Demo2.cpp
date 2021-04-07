/**
 * Demo program for Pandemic exercise - Scientist role
 * 
 * Author: Erel Segal-Halevi
 * Since : 2021-04
 */

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

#include "Scientist.hpp"

using namespace pandemic;

#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
	Board board;  // Initialize an empty board

	Scientist s {board, City::Atlanta, 4};  // initialize a "scientist" player that can find a cure using only 4 cards of its color.
	s.take_card(City::Sydney);
	s.take_card(City::HoChiMinhCity);
	s.take_card(City::HongKong);
	s.take_card(City::Bangkok);
	s.take_card(City::Atlanta);

	try {
		s.discover_cure(Color::Red); // Illegal action: you have 4 cards, but you are not in a research station.
	} catch (const exception& ex) {
	 	cout << "   caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}

	s.build();  // legal action: build a station in Atlanta.
	s.discover_cure(Color::Red); // Legal action.
		// NOTE: you only have 4 cards, so for other roles this action would throw an exception.
		//       But for the scientist it is legal.

	cout << board << endl;  // print the board in any reasonable format.
}

