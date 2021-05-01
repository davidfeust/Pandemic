//
// Created by david on 22/04/2021.
//

#pragma once

#include "Player.hpp"

namespace pandemic {
    class Dispatcher : public Player {

    public:
        Dispatcher(Board &board, City city);

        std::string role() const override;

        Dispatcher &fly_direct(pandemic::City city) override;

    };
}