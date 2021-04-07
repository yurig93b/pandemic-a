/**
 * Demo program for Pandemic exercise - Researcher role
 * 
 * Author: Erel Segal-Halevi
 * Since : 2021-04
 */

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

#include "Researcher.hpp"

using namespace pandemic;

#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
	Board board;  // Initialize an empty board
	board.set_infection_level(City::Kinshasa, 2);      // put 2 yellow disease cubes in Kinshasa
	board.set_infection_level(City::MexicoCity, 3);    // put 3 yellow disease cubes in MexicoCity
	board.set_infection_level(City::HoChiMinhCity, 1); // put 1 red disease cube in HoChiMinhCity
	board.set_infection_level(City::Chicago, 1);       // put 1 blue disease cube in Chicago

	Researcher r {board, City::Atlanta};  // initialize a "researcher" player on the given board, in Atlanta.
	r.take_card(City::Atlanta);
	r.take_card(City::Johannesburg);
	r.take_card(City::Khartoum);
	r.take_card(City::SaoPaulo);
	r.take_card(City::BuenosAires);
	r.take_card(City::LosAngeles);
	r.take_card(City::HoChiMinhCity);


	/* build action */

	r.build();  // legal action: you discard the Atlanta card and build a research station in Atlanta.


	/* drive action */

	r.drive(City::Washington);  // legal action: you drive from Atlanta to a connected city.
	try {
		r.drive(City::Madrid);  // illegal action: Madrid is not connected to Washington.
	} catch (const exception& ex) {
	 	cout << "   caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}


	/* fly_direct action */

	r.fly_direct(City::Johannesburg);  // legal action: you discard the Johannesburg card and fly to Johannesburg.
	try {
		r.fly_direct(City::Taipei);  // illegal action: you do not have the card of Taipei.
	} catch (const exception& ex) {
	 	cout << "   caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}


	/* treat action */

	r.drive(City::Kinshasa);    // legal action: you move from Johannesburg to a connected city.
	r.treat(City::Kinshasa);    // legal action: you remove 1 disease cube from current city (1 cube remains).
	r.treat(City::Kinshasa);    // legal action: you remove 1 disease cube from current city (0 cubes remain).
	try {
		r.treat(City::Kinshasa);  // illegal action: no more cubes remain in Kinshasa.
	} catch (const exception& ex) {
	 	cout << "   caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}
	try {
		r.treat(City::Washington);  // illegal action: you are not in Washington.
	} catch (const exception& ex) {
	 	cout << "   caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}


	/* fly_charter action */

	r.drive(City::Khartoum);
	r.fly_charter(City::Sydney);  // legal action: you discard the Khartoum card and fly to Sydney.

	try {
		r.fly_charter(City::Seoul);  // illegal action: you do not have the Sydney card (the card of the city you are in).
	} catch (const exception& ex) {
	 	cout << "   caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}


	/* build action */

	try {
		r.build();  // illegal action: you do not have the Sydney card (the card of the city you are in).
	} catch (const exception& ex) {
	 	cout << "   caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}
	r.drive(City::LosAngeles);  // legal action: note that LosAngeles is connected to Sydney.
	r.build();     // legal action: discard the LosAngeles card to build a research station in LosAngeles.


	/* fly_shuttle action */

	r.fly_shuttle(City::Atlanta); // legal action: you fly from one research station to another.
	r.fly_shuttle(City::LosAngeles); // legal action: you fly from one research station to another.
	try {
		r.fly_shuttle(City::Chicago); // illegal action: there is no research station in Chicago.
	} catch (const exception& ex) {
	 	cout << "   caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}


	/* discover_cure action */

	try {
		r.discover_cure(Color::Yellow); // illegal action: you only have 2 yellow cards remaining.
	} catch (const exception& ex) {
	 	cout << "   caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}

	r.take_card(City::Miami);
	r.take_card(City::Bogota);
	r.take_card(City::Lima);
	r.drive(City::MexicoCity)
	r.discover_cure(Color::Yellow); // legal action: you discard 5 yellow cards and discover a yellow cure.
		// NOTE: there is no research station in MexicoCity, so for other roles this action would throw an exception.
		//       But for the researcher it is legal, since she may discover a cure in any city.
	try {
		r.fly_direct(City::Miami); // illegal action: you discarded the Miami card to discover a cure, so you cannot use this card.
	} catch (const exception& ex) {
	 	cout << "   caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}

	/* treat action after discovering a cure */

	r.treat(City::MexicoCity);   // you now remove ALL disease cubes from MexicoCity, since there is a cure.


	/* clean the board */

	cout << board << endl;  // print the board in any reasonable format.
	cout << board.is_clean() << endl;  // print "0" - the board is not clean.

	r.drive(City::Chicago);
	r.treat(City::Chicago)
	
	r.fly_direct(City::HoChiMinhCity);
	r.treat(City::HoChiMinhCity);

	cout << board << endl;  // print the board in any reasonable format.
	cout << board.is_clean() << endl;  // print "1" - the board is clean - congratulations!!! You cured all diseases!!!
}

