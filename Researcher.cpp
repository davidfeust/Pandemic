//
// Created by david on 22/04/2021.
//

#include "Researcher.hpp"

using namespace pandemic;

Researcher::Researcher(Board &board, City city) : Player(board, city) {

}

std::string Researcher::role() const {
    return "Researcher";
}

Player &Researcher::discover_cure(pandemic::Color color) {
    if (curr_board.is_cure(color)) {
        return *this;
    }
    int n = 0;
    for (const auto &v : cards) {
        if (curr_board.get_color(v) == color) {
            n++;
        }
    }
    const int cards_to_cure = 5;
    if (n < cards_to_cure) {
        throw std::runtime_error{"There are not enough cards of the required color. Can not discover_cure."};
    }
    int i = 0;
    for (auto it = cards.begin(); it != cards.end();) {
        if (curr_board.get_color(*it) == color) {
            i++;
            cards.erase(it++);
        } else {
            ++it;
        }
        if (i == cards_to_cure) {
            break;
        }
    }
    curr_board.is_cure(color) = true;
    return *this;
}
