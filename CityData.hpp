//
// Created by david on 27/04/2021.
//

#pragma once

#include "City.hpp"
#include "Color.hpp"

namespace pandemic {
    class CityData {
    private:
        City enum_city;
        std::string name;
        int disease_cubes;
        bool station;
        Color color;

    public:
        CityData(City city, Color color) : enum_city(city), color(color), name(enum_str[city]), disease_cubes(0),
                                           station(false) {}

        CityData() {}

        int &get_disease_cubes() { return disease_cubes; }

        bool &get_station() { return station; }

        Color &get_color() { return color; }
    };

}