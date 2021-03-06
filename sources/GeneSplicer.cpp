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

Player &GeneSplicer::discover_cure(pandemic::Color color) {
    if (curr_board.is_cure(color)) {
        return *this;
    }
    if (!curr_board.getCities()[curr_city].get_station()) {
        throw std::runtime_error{"There is no research station in the current city. Can not discover_cure."};
    }
    uint n = cards.size();
    const int cards_to_cure = 5;
    if (n < cards_to_cure) {
        throw std::runtime_error{"There are not enough cards of the required color. Can not discover_cure."};
    }
    int i = 0;
    for (auto it = cards.begin(); it != cards.end();) {
        i++;
        cards.erase(it++);
        if (i == cards_to_cure) {
            break;
        }
    }
    curr_board.is_cure(color) = true;
    return *this;
}
