//
// Created by david on 22/04/2021.
//

#include <iostream>
#include "doctest.h"
#include "Board.hpp"
#include "OperationsExpert.hpp"
#include "FieldDoctor.hpp"
#include "Dispatcher.hpp"
#include "Scientist.hpp"
#include "Researcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"
#include "GeneSplicer.hpp"

using namespace pandemic;
using namespace std;

City random_city(unsigned int seed = 1);

void clear_board(Board &board);

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

//TEST_CASE ("from demo") {
//    cout << boolalpha;
//    Board board;
//
//    OperationsExpert builder{board, City::Atlanta};
//    builder.build();  // Build a research station in Atlanta, to prepare the board for the tests.
//
////    cout << board << endl;
//
//    FieldDoctor player(board, City::Washington);
//    player.take_card(City::Sydney)
//            .take_card(City::HoChiMinhCity)
//            .take_card(City::HongKong)
//            .take_card(City::Bangkok)
//            .take_card(City::Beijing);
//    player.drive(City::Atlanta);
//
//    player.discover_cure(Color::Red);
//
////    cout << board << endl;
//}

TEST_CASE ("board [] operator") {
    Board board;
    for (auto &[k, v] : enum_str) {
        int ran = rand() % 30;
        board[k] = ran;
                CHECK_EQ(board[k], ran);
                CHECK_EQ(board.getCities()[k].get_disease_cubes(), ran);
        board[k]++;
                CHECK_EQ(board[k], ran + 1);
                CHECK_EQ(board.getCities()[k].get_disease_cubes(), ran + 1);
    }
}

TEST_CASE ("is_clean") {
    Board board;
            CHECK_EQ(board.is_clean(), true);
    for (auto &[k, v] : enum_str) {
        board[k] = (rand() % 50) + 1;
    }
            CHECK_EQ(board.is_clean(), false);
    clear_board(board);
            CHECK_EQ(board.is_clean(), true);
}

TEST_CASE ("Drives") {
    Board board;
    City curr_city = random_city();
    array<Player *, 8> roles = {new OperationsExpert{board, curr_city}, new Dispatcher{board, curr_city},
                                new Scientist{board, curr_city, 3}, new Researcher{board, curr_city},
                                new Medic{board, curr_city}, new Virologist{board, curr_city},
                                new GeneSplicer{board, curr_city}, new FieldDoctor{board, curr_city}};

            SUBCASE("drive") {
        for (Player *player: roles) {
            curr_city = random_city();
            player->take_card(curr_city).fly_direct(curr_city);
            for (int i = 0; i < 50; ++i) {
                City rand_city = random_city();
                if (rand_city == curr_city) {
                    break;
                }
                bool isNeighbors = Board::is_neighbors(curr_city, rand_city);
                try {
                    player->drive(rand_city);
                    curr_city = rand_city;
                } catch (const exception &ex) {}
                        CHECK_EQ (curr_city == rand_city, isNeighbors);
            }
        }
    }

            SUBCASE("fly_direct") {
        for (Player *player: roles) {
            for (int i = 0; i < 50; ++i) {
                City rand_city = random_city();
                bool is_success;
                try {
                    player->fly_direct(rand_city);
                    is_success = true;
                } catch (const exception &ex) {
                    is_success = false;
                }
                        CHECK_EQ (is_success, false);
                try {
                    player->take_card(rand_city).fly_direct(rand_city);
                    is_success = true;
                } catch (const exception &ex) {
                    is_success = false;
                }
                        CHECK_EQ (is_success, true);
            }
        }
    }
            SUBCASE("fly_charter") {
        for (Player *player: roles) {
            for (int i = 0; i < 50; ++i) {
                City start_city = random_city();
                City rand_city = random_city();
                if (start_city == rand_city) {
                    break;
                }
                player->take_card(start_city).fly_direct(start_city);
                        CHECK_THROWS(player->fly_charter(rand_city));
                player->take_card(start_city);
                        CHECK_NOTHROW(player->fly_charter(rand_city));
            }
        }
    }
            SUBCASE("fly_shuttle") {
        for (Player *player: roles) {
            for (int i = 0; i < 5; ++i) {
                City start_city = random_city();
                City rand_city = random_city();
                if (start_city == rand_city) {
                    break;
                }
                player->take_card(start_city).fly_direct(start_city); // move to start_city
                if (!board.getCities()[start_city].get_station() || !board.getCities()[rand_city].get_station()) {
                            CHECK_THROWS(player->fly_shuttle(rand_city));
                }
                OperationsExpert ox{board, rand_city};
                ox.build();
                if (board.getCities()[start_city].get_station() && board.getCities()[rand_city].get_station()) {
                            CHECK_NOTHROW(player->fly_shuttle(rand_city));
                }
                ox.take_card(rand_city).fly_direct(rand_city).build();
                if (board.getCities()[start_city].get_station() && board.getCities()[rand_city].get_station()) {
                            CHECK_NOTHROW(player->fly_shuttle(rand_city));
                }
            }
        }
    }
}

//TEST_CASE ("Build") {
//    Board board;
//    City curr_city = random_city();
//    array<Player *, 7> roles = {new Dispatcher{board, curr_city},
//                                new Scientist{board, curr_city, 3}, new Researcher{board, curr_city},
//                                new Medic{board, curr_city}, new Virologist{board, curr_city},
//                                new GeneSplicer{board, curr_city}, new FieldDoctor{board, curr_city}};
////OperationsExpert{board, curr_city}
//    for (Player *player: roles) {
//        clear_board(board);
//        for (int i = 0; i < 20; ++i) {
//            City rand_city ;//= random_city(time(NULL));
//            cout << board << boolalpha << endl;
//            while (!board.getCities()[rand_city].get_station()) {
//                rand_city = random_city(time(nullptr));
//                cout << enum_str[rand_city] << " " << board.getCities()[rand_city].get_station() << endl;
//                if (!board.getCities()[rand_city].get_station()) break;
//            }
//            player->take_card(rand_city).fly_direct(rand_city); // move to rand_city
//                    CHECK_THROWS(player->build());
//                    CHECK_EQ(board.getCities()[rand_city].get_station(), false);
//            player->take_card(rand_city);
//                    CHECK_NOTHROW(player->build());
//                    CHECK_EQ(board.getCities()[rand_city].get_station(), true);
//
//        }
//    }
//}

City random_city(unsigned int seed) {
    srand(seed);
    int ran = rand() % 48;
    int i = 0;
    for (auto &[k, v] : enum_str) {
        if (i == ran) {
            return k;
        }
        i++;
    }
    return City::Chicago;
}

void clear_board(Board &board) {
    for (auto &[k, v] : board.getCities()) {
        board[k] = 0;
        v.get_station() = false;
    }
}


