//
// Created by david on 22/04/2021.
//

#include <iostream>
#include "doctest.h"
#include "Board.hpp"
#include "OperationsExpert.hpp"
#include "FieldDoctor.hpp"

using namespace pandemic;
using namespace std;

TEST_CASE ("test") {
    for (int i = 0; i < 25; ++i) {
                CHECK(1 == 1);
    }
}

TEST_CASE ("Discover Cure") {
    Board b;
    OperationsExpert player{b, City::London};

    player.build();

    player.take_card(City::Paris).
            take_card(City::Milan).
            take_card(City::Madrid).
            take_card(City::NewYork).
            take_card(City::Washington);

            CHECK_EQ(b.is_cure(Color::Blue), false);
    player.discover_cure(Color::Blue);
            CHECK_EQ(b.is_cure(Color::Blue), true);

}

TEST_CASE ("from demo") {
    cout << boolalpha;
    Board board;

    OperationsExpert builder{board, City::Atlanta};
    builder.build();  // Build a research station in Atlanta, to prepare the board for the tests.

    cout << board << endl;

    FieldDoctor player(board, City::Washington);
    player.take_card(City::Sydney)
            .take_card(City::HoChiMinhCity)
            .take_card(City::HongKong)
            .take_card(City::Bangkok)
            .take_card(City::Beijing);
    player.drive(City::Atlanta);

    player.discover_cure(Color::Red);

    cout << board << endl;
}