//
// Created by david on 22/04/2021.
//

#include "Player.hpp"

using namespace pandemic;

Player::Player(Board &board, City city) : curr_board(board), curr_city(city) {}

Player &Player::take_card(pandemic::City city) {
    cards.insert(city);
    return *this;
}

Player &Player::build() {
    if (curr_board.getCities()[curr_city].get_station()) {
        return *this;
    }
    if (cards.contains(curr_city)) {
        cards.erase(curr_city);
        curr_board.getCities()[curr_city].get_station() = true;
    } else {
        throw std::runtime_error{
                "The player does not have " + enum_str[curr_city] + " card (current city). Can not build."};
    }
    return *this;
}

Player &Player::drive(City city) {
    if (!Board::is_neighbors(curr_city, city)) {
        throw std::runtime_error{
                enum_str[city] + " and " + enum_str[curr_city] + " are not neighboring cities. Can not drive."};
    }
    curr_city = city;
    return *this;
}

Player &Player::fly_direct(City city) {
    if (cards.contains(city)) {
        cards.erase(city);
        curr_city = city;
    } else {
        throw std::runtime_error{"The player does not have " + enum_str[city] + " card. Can not fly_direct."};
    }
    return *this;
}

Player &Player::treat(City city) {
    if (city != curr_city) {
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

Player &Player::fly_charter(City city) {
    if (cards.contains(curr_city)) {
        cards.erase(curr_city);
        curr_city = city;
    } else {
        throw std::runtime_error{
                "The player does not have " + enum_str[city] + " card (current city). Can not fly_charter."};
    }
    return *this;
}

Player &Player::fly_shuttle(City city) {
    bool &station_curr = curr_board.getCities()[curr_city].get_station();
    bool &station_oth = curr_board.getCities()[city].get_station();
    if (!station_curr && !station_oth) {
        throw std::runtime_error{
                "There is no research station in the current city (" + enum_str[curr_city] + ") and in " +
                enum_str[city] + ". Can not fly_shuttle."};
    }
    if (!station_curr) {
        throw std::runtime_error{
                "There is no research station in the current city(" + enum_str[curr_city] + "). Can not fly_shuttle."};
    }
    if (!station_oth) {
        throw std::runtime_error{
                "There is no research station in " + enum_str[curr_city] + ". Can not fly_shuttle."};
    }
    curr_city = city;
    return *this;
}

Player &Player::discover_cure(pandemic::Color color) {
    if (curr_board.is_cure(color)) {
        return *this;
    }
    if (!curr_board.getCities()[curr_city].get_station()) {
        throw std::runtime_error{"There is no research station in the current city. Can not discover_cure."};
    }
    int n = 0;
    for (const auto &i : cards) {
        if (curr_board.get_color(i) == color) {
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

void Player::remove_cards() {
    cards.clear();
}

