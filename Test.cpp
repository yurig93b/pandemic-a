//
// Created by Yuri Grigorian on 05/05/2021.
//


#include <cmath>
#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include "doctest.h"


#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "Medic.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "Virologist.hpp"

using namespace pandemic;

// a func to get a random positive int
u_int getrandom(u_int min, u_int max) {
    // just to be sure
    if (min > max) {
        u_int temp = min;
        min = max;
        max = temp;
    }

    u_int i = rand() % 10;
    i %= 5;
    u_int k = pow(10, i);
    u_int r = (u_int) rand() % k;
    return r;
}

// a func to get a random string
std::string randString() {
    u_int len = (u_int)(rand() % 20);
    std::string s = "";
    for (size_t i = 0; i < len; i++) {
        s += (char) (65 + (rand() % 57));
    }
    return s;

}

TEST_CASE ("Test Board functionality") {
    Board b{};

    // Check initial clean state
    CHECK(b.is_clean());

    // Check clean state
    b[City::Tokyo] = 0;
    CHECK(b.is_clean());

    // Check dirty state
    b[City::Tokyo] = 2;
    CHECK_FALSE(b.is_clean());

    // Check return to clean state
    b[City::Tokyo] = 0;
    CHECK(b.is_clean());

    // Check multiple cities
    b[City::Tokyo] = 1;
    b[City::Beijing] = 1;
    CHECK_FALSE(b.is_clean());
    b[City::Tokyo] = 0;
    CHECK_FALSE(b.is_clean());
    b[City::Beijing] = 0;
    CHECK(b.is_clean());
}


TEST_CASE ("Test Player good functionality") {
    Board b{};

    Player p{b, City::Tokyo};
    CHECK(p.get_location() == City::Tokyo);

    //// Check drive
    p.drive(City::Seoul); // Player at Seoul with no cards.
    CHECK(p.get_location() == City::Seoul);

    p.drive(City::Beijing); // Player at Beijing with no cards.
    CHECK(p.get_location() == City::Beijing);

    // Check builder syntax
    p.drive(City::Seoul).drive(City::Beijing); // Player at Beijing with no cards.
    CHECK(p.get_location() == City::Beijing);

    //// Check fly_direct
    p.take_card(City::Moscow);
    CHECK(p.has_card(City::Moscow));
    CHECK(p.get_location() == City::Beijing);
    p.fly_direct(City::Moscow);
    CHECK_FALSE(p.has_card(City::Moscow));
    CHECK(p.get_location() == City::Moscow);

    p.take_card(City::Moscow);
    p.take_card(City::Algiers);
    p.fly_direct(City::Algiers);
    CHECK_FALSE(p.has_card(City::Algiers));
    CHECK(p.get_location() == City::Algiers); // Player at Algiers with Moscow card.

    //// Check fly_charter
    CHECK(p.has_card(City::Moscow));
    p.take_card(City::Algiers);
    p.fly_charter(City::Moscow); // Player at Moscow with Moscow card.
    CHECK_FALSE(p.has_card(City::Algiers));

    ///// Check build
    p.build();
    p.take_card(City::Tokyo);
    p.fly_direct(City::Tokyo);
    p.take_card(City::Tokyo);
    p.build();
    p.build(); // Second build no exception
    CHECK_FALSE(p.has_card(City::Tokyo));

    //// Check fly_shuttle
    CHECK(p.get_location() != City::Moscow);
    p.fly_shuttle(City::Moscow);
    CHECK(p.get_location() == City::Moscow);
    // Check no card needed
    p.take_card(City::Tokyo);
    p.fly_shuttle(City::Tokyo);
    CHECK(p.has_card(City::Tokyo));

    //// Check discover_cure
    p.take_card(City::Tokyo);
    p.fly_direct(City::Tokyo);
    p.take_card(City::Tokyo);
    p.build();

    p.take_card(City::Tokyo);
    p.take_card(City::Seoul);
    p.take_card(City::Osaka);
    p.take_card(City::Bangkok);
    p.take_card(City::Jakarta);
    p.discover_cure(Color::Red);
    p.take_card(City::Tokyo);
    p.take_card(City::Seoul);
    p.take_card(City::Osaka);
    p.take_card(City::Bangkok);
    p.take_card(City::Jakarta);
    p.discover_cure(Color::Red);
    CHECK(p.has_card(City::Tokyo));
    CHECK(p.has_card(City::Seoul));
    CHECK(p.has_card(City::Osaka));
    CHECK(p.has_card(City::Bangkok));
    CHECK(p.has_card(City::Jakarta));

    //// Check treat
    b[City::Tokyo] = 2;
    CHECK(b[City::Tokyo] == 2);
    p.treat(City::Tokyo);
    CHECK(b[City::Tokyo] == 0);

    b[City::Moscow] = 1;
    p.take_card(City::Moscow);
    p.fly_direct(City::Moscow);
    p.treat(City::Moscow);
    CHECK(b[City::Moscow] == 0);
}


TEST_CASE ("Test Player bad functionality") {
    Board b{};

    Player p{b, City::Tokyo};
    CHECK(p.get_location() == City::Tokyo);

    //// Check drive
    CHECK_THROWS(p.drive(City::Moscow)); // No card
    CHECK(p.get_location() == City::Tokyo);

    //// Check fly_direct
    CHECK_THROWS(p.fly_direct(City::Moscow)); // No target card

    //// Check fly_charter
    CHECK_FALSE(p.has_card(City::Tokyo));
    CHECK_THROWS(p.fly_charter(City::Moscow)); // No source card

    ///// Check build
    CHECK_FALSE(p.has_card(City::Tokyo));
    CHECK_THROWS(p.build());

    //// Check fly_shuttle
    CHECK_THROWS(p.fly_shuttle(City::Bangkok));

    //// Check discover_cure
    p.take_card(City::Baghdad);
    p.fly_direct(City::Baghdad);
    CHECK_THROWS(p.discover_cure(Color::Red)); // No enough cards + no research station

    p.take_card(City::Tokyo);
    p.take_card(City::Seoul);
    p.take_card(City::Osaka);
    p.take_card(City::Bangkok);
    p.take_card(City::Jakarta);
    CHECK_THROWS(p.discover_cure(Color::Red)); // No research station

    //// Check treat
    p.take_card(City::Moscow);
    p.fly_direct(City::Moscow);
    b[City::Tokyo] = 2;
    CHECK_THROWS(p.treat(City::Tokyo)); // Not in right location.

    b[City::Moscow] = 0;
    CHECK_THROWS(p.treat(City::Tokyo)); // Nothing to treat.

}


TEST_CASE ("OperationsExpert customs") {
    Board b{};

    OperationsExpert oe{b, City::Tokyo};
    oe.take_card(City::Tokyo);
    oe.build();
    CHECK(oe.has_card(City::Tokyo));
}

TEST_CASE ("Dispatcher customs") {
    Board b{};

    OperationsExpert oe{b, City::Tokyo};
    oe.build();

    Dispatcher d{b, City::Tokyo};
    d.take_card(City::Moscow);
    d.fly_direct(City::Moscow);
    CHECK(d.has_card(City::Moscow));
}


TEST_CASE ("Scientist customs") {
    Board b{};

    Scientist s{b, City::Tokyo, 2};
    s.take_card(City::Tokyo);
    s.take_card(City::Seoul);
    s.discover_cure(Color::Red);
    b[City::Tokyo] = 23;
    s.treat(City::Tokyo);
    CHECK(b[City::Tokyo] == 0); // Has cure.
}


TEST_CASE ("Researcher customs") {
    Board b{};

    OperationsExpert oe{b, City::Tokyo};
    oe.build();
    Researcher r{b, City::Tokyo};
    r.discover_cure(Color::Red);
    b[City::Tokyo] = 23;
    r.treat(City::Tokyo);
    CHECK(b[City::Tokyo] == 0); // Has cure.
}

TEST_CASE ("Medic customs") {
    Board b{};

    Medic m{b, City::Tokyo};
    b[City::Tokyo] = 23;
    m.treat(City::Tokyo);
    CHECK(b[City::Tokyo] == 0); // I'm a medic.
}


TEST_CASE ("Virologist customs") {
    Board b{};

    Virologist v{b, City::Moscow};
    b[City::Tokyo] = 23;
    v.treat(City::Tokyo);
    CHECK(b[City::Tokyo] == 0);
}


TEST_CASE ("GeneSplicer customs") {
    Board b{};

    GeneSplicer g{b, City::Tokyo};

    g.take_card(City::LosAngeles); // Take yellow cards
    g.take_card(City::Lagos); // Take yellow cards
    g.take_card(City::Lima); // Take yellow cards
    g.take_card(City::Santiago); // Take yellow cards
    g.take_card(City::Miami); // Take yellow cards

    b[City::Tokyo] = 23;
    g.discover_cure(Color::Red);
    g.treat(City::Tokyo);
    CHECK(b[City::Tokyo] == 0);

    CHECK_FALSE(g.has_card(City::LosAngeles));
    CHECK_FALSE(g.has_card(City::Lagos));
    CHECK_FALSE(g.has_card(City::Lima));
    CHECK_FALSE(g.has_card(City::Santiago));
    CHECK_FALSE(g.has_card(City::Miami));
}



TEST_CASE ("FieldDoctor customs") {
    Board b{};

    FieldDoctor f{b, City::Tokyo};
    b[City::Seoul] = 1;
    b[City::Osaka] = 1;

    f.treat(City::Seoul);
    f.treat(City::Osaka);

    CHECK(b[City::Seoul] ==0);
    CHECK(b[City::Osaka] ==0);
    CHECK_THROWS(f.treat(City::Moscow));
}