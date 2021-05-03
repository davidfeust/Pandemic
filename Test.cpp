//
// Created by david on 22/04/2021.
//

#include <iostream>

#include "Board.hpp"
#include "Dispatcher.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "Medic.hpp"
#include "OperationsExpert.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "Virologist.hpp"
#include "doctest.h"

using namespace pandemic;
using namespace std;

City random_city(unsigned int seed = 1);

void clear_board(Board &board);

Color random_color(unsigned int seed = 1);

void put_disease_cubes(Board &board);

void take_n_cards(Player *player, Board &board, Color color, int n = 5);


TEST_CASE("Discover Cure") {
    Board b;
    OperationsExpert player{b, City::London};

    player.build();

    player.take_card(City::Paris)
        .take_card(City::Milan)
        .take_card(City::Madrid)
        .take_card(City::NewYork)
        .take_card(City::Washington);

    CHECK_EQ(b.is_cure(Color::Blue), false);
    player.discover_cure(Color::Blue);
    CHECK_EQ(b.is_cure(Color::Blue), true);
}

TEST_CASE("board [] operator") {
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

TEST_CASE("is_clean") {
    Board board;
    CHECK_EQ(board.is_clean(), true);
    for (auto &[k, v] : enum_str) {
        board[k] = (rand() % 50) + 1;
    }
    CHECK_EQ(board.is_clean(), false);
    clear_board(board);
    CHECK_EQ(board.is_clean(), true);
}

TEST_CASE("Drives") {
    Board board;
    City curr_city = random_city();
    array<Player *, 8> roles = {new OperationsExpert{board, curr_city},
                                new Dispatcher{board, curr_city},
                                new Scientist{board, curr_city, 3},
                                new Researcher{board, curr_city},
                                new Medic{board, curr_city},
                                new Virologist{board, curr_city},
                                new GeneSplicer{board, curr_city},
                                new FieldDoctor{board, curr_city}};

    SUBCASE("drive") {
        for (Player *player : roles) {
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
                } catch (const exception &ex) {
                }
                CHECK_EQ(curr_city == rand_city, isNeighbors);
            }
        }
    }

    SUBCASE("fly_direct") {
        for (Player *player : roles) {
            for (int i = 0; i < 50; ++i) {
                City rand_city = random_city();
                bool is_success;
                try {
                    player->fly_direct(rand_city);
                    is_success = true;
                } catch (const exception &ex) {
                    is_success = false;
                }
                CHECK_EQ(is_success, false);
                try {
                    player->take_card(rand_city).fly_direct(rand_city);
                    is_success = true;
                } catch (const exception &ex) {
                    is_success = false;
                }
                CHECK_EQ(is_success, true);
            }
        }
    }
    SUBCASE("fly_charter") {
        for (Player *player : roles) {
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
        for (Player *player : roles) {
            for (int i = 0; i < 5; ++i) {
                City start_city = random_city();
                City rand_city = random_city();
                if (start_city == rand_city) {
                    break;
                }
                player->take_card(start_city)
                    .fly_direct(start_city);  // move to start_city
                if (!board.getCities()[start_city].get_station() ||
                    !board.getCities()[rand_city].get_station()) {
                    CHECK_THROWS(player->fly_shuttle(rand_city));
                }
                OperationsExpert ox{board, rand_city};
                ox.build();
                if (board.getCities()[start_city].get_station() &&
                    board.getCities()[rand_city].get_station()) {
                    CHECK_NOTHROW(player->fly_shuttle(rand_city));
                }
                ox.take_card(rand_city).fly_direct(rand_city).build();
                if (board.getCities()[start_city].get_station() &&
                    board.getCities()[rand_city].get_station()) {
                    CHECK_NOTHROW(player->fly_shuttle(rand_city));
                }
            }
        }
    }
}

TEST_CASE("Build") {
    Board board;
    City curr_city = random_city();
    array<Player *, 7> roles = {
        new Dispatcher{board, curr_city}, new Scientist{board, curr_city, 3},
        new Researcher{board, curr_city}, new Medic{board, curr_city},
        new Virologist{board, curr_city}, new GeneSplicer{board, curr_city},
        new FieldDoctor{board, curr_city}};
    for (Player *player : roles) {
        clear_board(board);
        board.remove_stations();
        for (int i = 0; i < 20; ++i) {
            City rand_city = random_city(time(nullptr));
            if (board.getCities()[rand_city].get_station()) {
                continue;
            }
            player->take_card(rand_city).fly_direct(
                rand_city);  // move to rand_city
            CHECK_THROWS(player->build());
            CHECK_EQ(board.getCities()[rand_city].get_station(), false);
            player->take_card(rand_city);
            CHECK_NOTHROW(player->build());
            CHECK_EQ(board.getCities()[rand_city].get_station(), true);
        }
    }
}

TEST_CASE("discover_cure") {
    Board board;
    City start_city = random_city();
    array<Player *, 8> roles = {new OperationsExpert{board, start_city},
                                new Dispatcher{board, start_city},
                                new Scientist{board, start_city, 3},
                                new Researcher{board, start_city},
                                new Medic{board, start_city},
                                new Virologist{board, start_city},
                                new GeneSplicer{board, start_city},
                                new FieldDoctor{board, start_city}};
    for (Player *player : roles) {
        board.remove_stations();
        board.remove_cures();
        for (int i = 0; i < 8; ++i) {
            player->remove_cards();
            Color color = random_color();
            if (board.is_cure(color)) {
                continue;
            }
            City rand_city = random_city();
            player->take_card(rand_city).fly_direct(rand_city);
            if (board.getCities()[rand_city].get_station()) {
                CHECK_THROWS(player->discover_cure(color));
                take_n_cards(player, board, color);
                CHECK_NOTHROW(player->discover_cure(color));
                CHECK_EQ(board.getCities()[rand_city].get_station(), true);
            } else {
                CHECK_THROWS(player->discover_cure(color));
                OperationsExpert ox{board, rand_city};
                ox.build();
                CHECK_THROWS(player->discover_cure(color));
                take_n_cards(player, board, color);
                CHECK_NOTHROW(player->discover_cure(color));
                CHECK_EQ(board.getCities()[rand_city].get_station(), true);
            }
        }
    }
}

TEST_CASE("treat") {
    Board board;
    City start_city = random_city();
    array<Player *, 8> roles = {new OperationsExpert{board, start_city},
                                new Dispatcher{board, start_city},
                                new Scientist{board, start_city, 3},
                                new Researcher{board, start_city},
                                new Medic{board, start_city},
                                new Virologist{board, start_city},
                                new GeneSplicer{board, start_city},
                                new FieldDoctor{board, start_city}};
    for (Player *player : roles) {
        board.remove_stations();
        board.remove_cures();
        player->remove_cards();
        put_disease_cubes(board);

        for (int i = 0; i < 10; ++i) {
            City rand_city = random_city();
            player->take_card(rand_city).fly_direct(rand_city);
            if (board[rand_city] == 0) {
                CHECK_THROWS(player->treat(rand_city));
            } else {
                int t = board[rand_city];
                if (!board.is_cure(board.get_color(rand_city))) {
                    CHECK_NOTHROW(player->treat(rand_city));
                    if (player->role() == "Medic") {
                        CHECK_EQ(board[rand_city], 0);
                    } else {
                        CHECK_EQ(board[rand_city], t - 1);
                    }
                } else {
                    CHECK_NOTHROW(player->treat(rand_city));
                    CHECK_EQ(board[rand_city], 0);
                }
            }
        }
    }
}

TEST_CASE("OperationsExpert") {
    Board board;
    City city = random_city();
    OperationsExpert player{board, city};
    for (int i = 0; i < 10; ++i) {
        City rand_city = random_city();
        player.take_card(rand_city).fly_direct(rand_city);
        CHECK_NOTHROW(player.build());
        CHECK_EQ(board.getCities()[rand_city].get_station(), true);
    }
}

TEST_CASE("Dispatcher") {
    Board board;
    City city = random_city();
    Dispatcher player{board, city};
    for (int i = 0; i < 10; ++i) {
        City rand_city = random_city();
        player.take_card(rand_city).fly_direct(rand_city);
        City rand_new_city = random_city();
        if (board.getCities()[rand_city].get_station()) {
            CHECK_NOTHROW(player.fly_direct(rand_new_city));
        } else {
            CHECK_THROWS(player.fly_direct(rand_new_city));
        }
    }
}

TEST_CASE("Scientist") {
    Board board;
    City city = random_city();
    int n = 3;
    Scientist player{board, city, n};
    board.remove_stations();
    for (int i = 0; i < 8; ++i) {
        player.remove_cards();
        City rand_city = random_city();
        Color &color = board.get_color(rand_city);
        if (board.is_cure(color) ||
            board.getCities()[rand_city].get_station()) {
            continue;
        }
        player.take_card(rand_city).fly_direct(rand_city);
        CHECK_THROWS(player.discover_cure(color));
        CHECK_EQ(board.is_cure(color), false);
        take_n_cards(&player, board, color, n - 1);
        CHECK_THROWS(player.discover_cure(color));
        CHECK_EQ(board.is_cure(color), false);
        take_n_cards(&player, board, color, n);
        CHECK_THROWS(player.discover_cure(color));
        CHECK_EQ(board.is_cure(color), false);
        OperationsExpert ox{board, rand_city};
        ox.build();
        CHECK_NOTHROW(player.discover_cure(color));
        CHECK_EQ(board.is_cure(color), true);
    }
}

TEST_CASE("Researcher") {
    Board board;
    City city = random_city();
    Researcher player{board, city};
    for (int i = 0; i < 10; ++i) {
        City rand_city = random_city();
        Color &color = board.get_color(rand_city);
        player.take_card(rand_city).fly_direct(rand_city);
        if (board.is_cure(color)) {
            continue;
        }
        CHECK_THROWS(player.discover_cure(color));
        take_n_cards(&player, board, color, 5);
        CHECK_NOTHROW(player.discover_cure(color));
    }
}

TEST_CASE("Virologist") {
    Board board;
    City city = random_city();
    Virologist player{board, city};
    put_disease_cubes(board);
    for (int i = 0; i < 10; ++i) {
        City rand_city = random_city();
        Color &color = board.get_color(rand_city);
        if (board[rand_city] == 0) {
            CHECK_THROWS(player.treat(rand_city));
        } else {
            int t = board[rand_city];
            if (city != rand_city) {
                CHECK_THROWS(player.treat(rand_city));
            } else {
                CHECK_NOTHROW(player.treat(rand_city));
                CHECK_EQ(board[rand_city], t - 1);
            }
            t = board[rand_city];
            player.take_card(rand_city);
            CHECK_NOTHROW(player.treat(rand_city));
            CHECK_EQ(board[rand_city], t - 1);
        }
    }
}

TEST_CASE("GeneSplicer") {
    Board board;
    City city = random_city();
    GeneSplicer player{board, city};
    for (int i = 0; i < 10; ++i) {
        City rand_city = random_city();
        Color &color = board.get_color(rand_city);
        player.take_card(rand_city).fly_direct(rand_city);
        if (board.is_cure(color)) {
            continue;
        }

        CHECK_THROWS(player.discover_cure(color));
        CHECK_EQ(board.is_cure(color), false);
        take_n_cards(&player, board, Color::Red, 1);
        take_n_cards(&player, board, Color::Blue, 1);
        take_n_cards(&player, board, Color::Black, 1);
        take_n_cards(&player, board, Color::Yellow, 2);
        CHECK_THROWS(player.discover_cure(color));
        CHECK_EQ(board.is_cure(color), false);
        OperationsExpert ox{board, rand_city};
        ox.build();
        CHECK_NOTHROW(player.discover_cure(color));
        CHECK_EQ(board.is_cure(color), true);
    }
}

TEST_CASE("FieldDoctor") {
    Board board;
    City city = random_city();
    FieldDoctor player{board, city};
    put_disease_cubes(board);
    for (int i = 0; i < 10; ++i) {
        City rand_city = random_city();
        Color &color = board.get_color(rand_city);
        player.take_card(rand_city).fly_direct(rand_city);

        if (board[rand_city] == 0) {
            CHECK_THROWS(player.treat(rand_city));
        } else {
            int t = board[rand_city];
            if (city != rand_city && !Board::is_neighbors(city, rand_city)) {
                CHECK_THROWS(player.treat(rand_city));
            } else {
                CHECK_NOTHROW(player.treat(rand_city));
                CHECK_EQ(board[rand_city], t - 1);
            }
            t = board[rand_city];
            player.take_card(rand_city);
            CHECK_NOTHROW(player.treat(rand_city));
            CHECK_EQ(board[rand_city], t - 1);
        }
    }
}

TEST_CASE("Medic") {
    Board board;
    City city = random_city();
    Medic player{board, city};
    put_disease_cubes(board);
    for (int i = 0; i < 10; ++i) {
        City rand_city = random_city();
        Color &color = board.get_color(rand_city);
        player.take_card(rand_city).fly_direct(rand_city);

        if (board[rand_city] == 0) {
            CHECK_THROWS(player.treat(rand_city));
        } else {
            if (city != rand_city && !Board::is_neighbors(city, rand_city)) {
                CHECK_THROWS(player.treat(rand_city));
            } else {
                CHECK_NOTHROW(player.treat(rand_city));
                CHECK_EQ(board[rand_city], 0);
            }
        }
    }

    for (int i = 0; i < 20; ++i) {
        City rand_city = random_city();
        Color &color = board.get_color(rand_city);
        player.take_card(rand_city).fly_direct(rand_city);
        if (board[rand_city] == 0) {
            continue;
        }
        if (board.is_cure(color)) {
            CHECK_EQ(board[rand_city], 0);
        } else {
            board.is_cure(color) = true;
            player.take_card(rand_city).fly_direct(rand_city);
            CHECK_EQ(board[rand_city], 0);
        }
    }
}

void put_disease_cubes(Board &board) {
    for (auto &[k, v] : board.getCities()) {
        int d = rand() % 5;
        board[k] = d;
    }
}

void take_n_cards(Player *player, Board &board, Color color, int n) {
    int i = 0;
    for (auto &[k, v] : board.getCities()) {
        if (board.get_color(k) == color) {
            player->take_card(k);
            ++i;
        }
        if (i == n) {
            return;
        }
    }
}

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

Color random_color(unsigned int seed) {
    srand(seed);
    int ran = rand() % 4;
    switch (ran) {
        case 0:
            return Color::Blue;
        case 1:
            return Color::Black;
        case 2:
            return Color::Red;
        default:
            return Color::Yellow;
    }
}