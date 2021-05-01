//
// Created by david on 22/04/2021.
//

#pragma once

#include "Player.hpp"

namespace pandemic {
    class OperationsExpert : public Player {

    public:
        OperationsExpert(Board &board, City city);

        std::string role() const override;

        void build() override;
    };
}