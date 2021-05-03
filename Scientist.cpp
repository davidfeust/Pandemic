//
// Created by david on 22/04/2021.
//

#include "Scientist.hpp"

using namespace pandemic;


Scientist::Scientist(Board &board, City city, int n) : Player((board), city), num(n) {}

std::string Scientist::role() const {
    return "Scientist";
}

Player &Scientist::discover_cure(pandemic::Color color) {
    if (curr_board.is_cure(color)) {
        return *this;
    }
    if (!curr_board.getCities()[curr_city].get_station()) {
        throw std::runtime_error{"There is no research station in the current city. Can not discover_cure."};
    }
    int n = 0;
    for (const auto &v : cards) {
        if (curr_board.get_color(v) == color) {
            n++;
        }
    }
    if (n < num) {
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
        if (i == num) {
            break;
        }
    }
    curr_board.is_cure(color) = true;
    return *this;
}
