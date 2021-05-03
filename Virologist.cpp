//
// Created by david on 22/04/2021.
//

#include "Virologist.hpp"

using namespace pandemic;

Virologist::Virologist(Board &board, City city) : Player(board, city) {

}

std::string Virologist::role() const {
    return "Virologist";
}

Virologist &Virologist::treat(pandemic::City city) {
    if (curr_board[city] == 0) {
        throw std::runtime_error{
                "There is no pollution in the current city. Can not treat."};
    }
    if (city != curr_city && !cards.contains(city)) {
        throw std::runtime_error{
                "The Virologist have not " + enum_str[city] + " card. Can not treat."};
    }
    if (curr_board.is_cure(city)) {
        curr_board[city] = 0;
    } else {
        curr_board[curr_city]--;
    }
    if (city != curr_city) {
        cards.erase(city);
    }
    return *this;
}
