//
// Created by david on 22/04/2021.
//

#pragma once
#include "Player.hpp"

namespace pandemic {
    class Scientist : public Player {
    private:
        int num;
    public:

        Scientist(Board &board, City city, int n);

        std::string role() const override;

        Player & discover_cure(pandemic::Color color) override;
    };
}