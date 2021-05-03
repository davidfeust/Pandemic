//
// Created by david on 22/04/2021.
//

#pragma once
#include "Player.hpp"

namespace pandemic {

    class Researcher : public Player {

    public:
        Researcher(Board &board, City city);

        std::string role() const override;

        Player & discover_cure(pandemic::Color color) override;
    };
}