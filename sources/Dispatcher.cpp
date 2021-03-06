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
    if (curr_city == city) {
        throw std::runtime_error{
                "Can not drive from city to it self. Can not fly_direct."};
    }
    if (curr_board.getCities()[curr_city].get_station()) {
        curr_city = city;
    } else if (cards.contains(city)) {
        cards.erase(city);
        curr_city = city;
    } else {
        throw std::runtime_error{"The player does not have " + enum_str[city] + " card. Can not fly_direct."};
    }
    return *this;
}
