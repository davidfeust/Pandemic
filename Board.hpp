//
// Created by david on 22/04/2021.
//

#pragma once

#include <ostream>
#include <map>
#include <vector>
#include "City.hpp"
#include "CityData.hpp"

namespace pandemic {
    class Board {
    private:
        std::map<City, CityData> cities;
//        std::map<Color, bool> cures;
        static std::map<City, std::vector<City>> graph;

        bool cure_blue, cure_yellow, cure_black, cure_red;

//        void init_graph();

        void init_cities();

    public:

        Board();

        int &operator[](City city);

        friend std::ostream &operator<<(std::ostream &os, Board &board);

        bool is_clean();

        bool is_neighbors(City city1, City city2);

        std::map<City, CityData> &getCities();

//        bool& get_station(City city);

        Color &get_color(City city);

        bool &is_cure(Color color);

        void cure(Color color);
    };
}