//
// Created by david on 22/04/2021.
//

#pragma once

#include "Player.hpp"

namespace pandemic {

    class FieldDoctor : public Player {

    public:
        FieldDoctor(Board &board, City city);

        std::string role() const override;

        Player &treat(pandemic::City city) override;
    };
}
