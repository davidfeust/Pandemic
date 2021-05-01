//
// Created by david on 22/04/2021.
//

#pragma once

#include "Player.hpp"

namespace pandemic {

    class Medic : public Player {

    public:
        Medic(Board &board, City city);

        std::string role() const override;

        Medic &treat(pandemic::City city) override;

        Medic &drive(pandemic::City city) override;

        Medic &fly_direct(pandemic::City city) override;

        Medic &fly_charter(pandemic::City city) override;

        void fly_shuttle(pandemic::City city) override;


    private:
        void arrival();
    };
}