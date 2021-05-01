//
// Created by david on 22/04/2021.
//

#include "GeneSplicer.hpp"

using namespace pandemic;

GeneSplicer::GeneSplicer(Board &board, City city) : Player(board, city) {

}

std::string GeneSplicer::role() const {
    return "GeneSplicer";
}

void GeneSplicer::discover_cure(pandemic::Color color) {
    if (curr_board.is_cure(color)) {
        return;
    }
    if (!curr_board.getCities()[curr_city].get_stations()) {
        throw std::runtime_error{"There is no research station in the current city. Can not discover_cure."};
    }
    int n = 0;
    for (auto[k, v] : cards) {
        if (v) {
            n++;
        }
    }
    if (n < 5) {
        throw std::runtime_error{"There are not enough cards of the required color. Can not discover_cure."};
    }
    int i = 0;
    for (auto[k, v] : cards) {
        if (v) {
            i++;
            cards[k] = false;
        }
        if (i == 5) {
            break;
        }
    }
    curr_board.is_cure(color) = true;
}
