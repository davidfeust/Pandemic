//
// Created by david on 22/04/2021.
//

#pragma once

#include "Player.hpp"

namespace pandemic {

    class Virologist : public Player {

    public:
        Virologist(Board &board, City city);

        std::string role() const override;

        Virologist &treat(pandemic::City city) override;
    };
}