//
// Created by david on 22/04/2021.
//

#include "Dispatcher.hpp"

using namespace pandemic;

Dispatcher::Dispatcher(Board &board, City city) : Player(board, city) {

}

std::string Dispatcher::role() const {
    return "Dispatcher";
}

Dispatcher &Dispatcher::fly_direct(pandemic::City city) {
    if (curr_board.getCities()[curr_city].get_stations()) {
        curr_city = city;
    }
    return *this;
//    return Player::fly_direct(city);
}
