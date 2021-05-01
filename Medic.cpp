//
// Created by david on 22/04/2021.
//

#include "Medic.hpp"

using namespace pandemic;

Medic::Medic(Board &board, City city) : Player(board, city) {

}

std::string Medic::role() const {
    return "Medic";
}

Medic &Medic::treat(pandemic::City city) {
    if (city != curr_city) {
        throw std::runtime_error{
                "The current city is " + enum_str[curr_city] + " not " + enum_str[city] + ". Can not treat."};
    }
    if (curr_board[city] == 0) {
        throw std::runtime_error{
                "There is no pollution in the current city. Can not treat."};
    }
    curr_board[city] = 0;
    return *this;
}

void Medic::arrival() {
    if (curr_board.is_cure(curr_board.getCities()[curr_city].get_color())) {
        curr_board[curr_city] = 0;
    }
}

Medic &Medic::fly_direct(pandemic::City city) {
    arrival();
    Player::fly_direct(city);
    return *this;
}

Medic &Medic::fly_charter(pandemic::City city) {
    arrival();
    Player::fly_charter(city);
    return *this;
}

void Medic::fly_shuttle(pandemic::City city) {
    arrival();
    Player::fly_shuttle(city);
}

Medic &Medic::drive(pandemic::City city) {
    arrival();
    Player::drive(city);
    return *this;
}
