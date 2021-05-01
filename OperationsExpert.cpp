//
// Created by david on 22/04/2021.
//

#include "OperationsExpert.hpp"

using namespace pandemic;

OperationsExpert::OperationsExpert(Board &board, City city) : Player(board, city) {}

void OperationsExpert::build() {
    Player::curr_board.getCities()[Player::curr_city].get_stations() = true;
}

std::string OperationsExpert::role() const {
    return "OperationsExpert";
}
