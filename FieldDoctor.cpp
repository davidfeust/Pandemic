//
// Created by david on 22/04/2021.
//

#include "FieldDoctor.hpp"

using namespace pandemic;

FieldDoctor::FieldDoctor(Board &board, City city) : Player(board, city) {

}

std::string FieldDoctor::role() const {
    return "FieldDoctor";
}

Player &FieldDoctor::treat(pandemic::City city) {
    if (city != curr_city && !Board::is_neighbors(curr_city, city)) {
        throw std::runtime_error{
                "The current city is " + enum_str[curr_city] + " not " + enum_str[city] + ". Can not treat."};
    }
    if (curr_board[city] == 0) {
        throw std::runtime_error{
                "There is no pollution in the current city. Can not treat."};
    }
    if (curr_board.is_cure(curr_board.getCities()[city].get_color())) {
        curr_board[city] = 0;
    } else {
        curr_board[curr_city]--;
    }
    return *this;
}
