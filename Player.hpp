//
// Created by david on 22/04/2021.
//

#pragma once

#include <list>
#include <string>
#include <set>
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"

namespace pandemic {

    class Player {
    protected:
        std::map<City, bool> cards;
//        std::set<City> cards;
        City curr_city;
        Board &curr_board;

    public:
        Player(pandemic::Board &board, pandemic::City city);

        /**
        * Move the player from the current city to the giving city, only if city is connected city.
        * @throw exception if the giving city is not connected to the current city.
        * @param city
        * @return this player reference
        */
        virtual Player &drive(pandemic::City city);

        /**
        * Move from the current city to the giving city, only if the player have card of this city,
        * and the player discard this card by flying there.
        * @throw exception if the player doesn't have the appropriate card.
        * @param city
        * @return this player reference
        */
        virtual Player &fly_direct(pandemic::City city);

        /**
        * Move from the current city to the giving city, only if the player have the card of the current city,
        * and the player discard this card by flying there.
        * @throw exception if the player doesn't have the card of the current city.
        * @param city
        * @return this player reference
        */
        virtual Player &fly_charter(pandemic::City city);

        /**
        * Move from the current city to the giving city,
        * only if in the current city there is a research station and also in the given city.
        * @throw exception if in the current city or in the giving city there is no research station.
        * @param city
        */
        virtual Player &fly_shuttle(pandemic::City city);

        /**
         * Build a research station in the current city.
         * To do this, discard the appropriate card to the city you are in.
         * Each city can have at most one research station.
         * @throw exception if the player doesn't have the card of the current city,
         * or if there is already a research station in the city.
         */
        virtual Player &build();

        /**
        * Discovering a cure for a disease of a certain color.
        * To do this, you must be in a city that has a research station,
        * and discard 5 colored cards of the disease.
        * @throw exception if the player doesn't have enough cards of the required color.
        */
        virtual Player &discover_cure(pandemic::Color color);

        /**
        * Reduction of one disease cube from the current city.
        * If a cure for the disease has already been discovered in the city's color,
        * then the "treat" action removes all the disease cubes from the current city.
        * If there is no pollution at all in the city, then the action will throw an exception.
        * @throw exception if there is no pollution at all in the city.
        * @param city
        * @return this player reference
        */
        virtual Player &treat(pandemic::City city);

        /**
         * Returns the role of the player.
         */
        virtual std::string role() const = 0;

        /**
         * Taking some city card.
         * There is only one card of each city,
         * so if you take a take_card operation on a card already in the player's possession,
         * there will be no change in the player's position.
         * @param city
         * @return this player reference
         */
        Player &take_card(pandemic::City city);
    };
}