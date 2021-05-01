//
// Created by david on 22/04/2021.
//
#include <iostream>
#include "Player.hpp"
#include "Dispatcher.hpp"
#include "Board.hpp"
#include "City.hpp"

using namespace pandemic;
using namespace std;

int main() {
    Board b;
//    Player p{b, City::Atlanta};
    Dispatcher d{b, City::Atlanta};
//    cout << p.role() << endl;
    cout << d.role() << endl;
    return 0;
}