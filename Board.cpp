//
// Created by david on 22/04/2021.
//

#include "Board.hpp"


using namespace pandemic;
using namespace std;

Board::Board() : cure_black(false), cure_blue(false), cure_red(false), cure_yellow(false) {
    init_cities();
}

int &Board::operator[](pandemic::City city) {
    return cities[city].get_disease_cubes();
}

std::ostream &pandemic::operator<<(std::ostream &os, pandemic::Board &board) {
    os << "Cities (Only with disease cubes or research station):" << endl;
    for (auto[k, v]: board.cities) {
        if ((v.get_station()) || v.get_disease_cubes() > 0) {
            os << "\t" << enum_str[k] << ": " << v.get_disease_cubes();
            if (v.get_station()) {
                os << "\t" << "A research station was discovered!";
            }
            os << endl;
        }
    }
    os << "The cures discovered:" << endl;
    if (board.cure_black) { os << "Black" << endl; }
    if (board.cure_blue) { os << "Blue" << endl; }
    if (board.cure_yellow) { os << "Yellow" << endl; }
    if (board.cure_red) { os << "Red" << endl; }
    return os;
}

bool Board::is_clean() {
    for (auto[k, v] : cities) {
        if (v.get_disease_cubes() != 0) {
            return false;
        }
    }
    return true;
}

bool Board::is_neighbors(City city1, City city2) {
    for (City &i : graph.at(city1)) {
        if (i == city2) {
            return true;
        }
    }
    return false;
}

void Board::init_cities() {
    cities = {
            {City::Algiers,       CityData{City::Algiers, Color::Black}},
            {City::Atlanta,       CityData{City::Atlanta, Color::Blue}},
            {City::Baghdad,       CityData{City::Baghdad, Color::Black}},
            {City::Bangkok,       CityData{City::Bangkok, Color::Red}},
            {City::Beijing,       CityData{City::Beijing, Color::Red}},
            {City::Bogota,        CityData{City::Bogota, Color::Yellow}},
            {City::BuenosAires,   CityData{City::BuenosAires, Color::Yellow}},
            {City::Cairo,         CityData{City::Cairo, Color::Black}},
            {City::Chennai,       CityData{City::Chennai, Color::Black}},
            {City::Chicago,       CityData{City::Chicago, Color::Blue}},
            {City::Delhi,         CityData{City::Delhi, Color::Black}},
            {City::Essen,         CityData{City::Essen, Color::Blue}},
            {City::HoChiMinhCity, CityData{City::HoChiMinhCity, Color::Red}},
            {City::HongKong,      CityData{City::HongKong, Color::Red}},
            {City::Istanbul,      CityData{City::Istanbul, Color::Black}},
            {City::Jakarta,       CityData{City::Jakarta, Color::Red}},
            {City::Johannesburg,  CityData{City::Johannesburg, Color::Yellow}},
            {City::Karachi,       CityData{City::Karachi, Color::Black}},
            {City::Khartoum,      CityData{City::Khartoum, Color::Yellow}},
            {City::Kinshasa,      CityData{City::Kinshasa, Color::Yellow}},
            {City::Kolkata,       CityData{City::Kolkata, Color::Black}},
            {City::Lagos,         CityData{City::Lagos, Color::Yellow}},
            {City::Lima,          CityData{City::Lima, Color::Yellow}},
            {City::London,        CityData{City::London, Color::Blue}},
            {City::LosAngeles,    CityData{City::LosAngeles, Color::Yellow}},
            {City::Madrid,        CityData{City::Madrid, Color::Blue}},
            {City::Manila,        CityData{City::Manila, Color::Red}},
            {City::MexicoCity,    CityData{City::MexicoCity, Color::Yellow}},
            {City::Miami,         CityData{City::Miami, Color::Yellow}},
            {City::Milan,         CityData{City::Milan, Color::Blue}},
            {City::Montreal,      CityData{City::Montreal, Color::Blue}},
            {City::Moscow,        CityData{City::Moscow, Color::Black}},
            {City::Mumbai,        CityData{City::Mumbai, Color::Black}},
            {City::NewYork,       CityData{City::NewYork, Color::Blue}},
            {City::Osaka,         CityData{City::Osaka, Color::Red}},
            {City::Paris,         CityData{City::Paris, Color::Blue}},
            {City::Riyadh,        CityData{City::Riyadh, Color::Black}},
            {City::SanFrancisco,  CityData{City::SanFrancisco, Color::Blue}},
            {City::Santiago,      CityData{City::Santiago, Color::Yellow}},
            {City::SaoPaulo,      CityData{City::SaoPaulo, Color::Yellow}},
            {City::Seoul,         CityData{City::Seoul, Color::Red}},
            {City::Shanghai,      CityData{City::Shanghai, Color::Red}},
            {City::StPetersburg,  CityData{City::StPetersburg, Color::Blue}},
            {City::Sydney,        CityData{City::Sydney, Color::Red}},
            {City::Taipei,        CityData{City::Taipei, Color::Red}},
            {City::Tehran,        CityData{City::Tehran, Color::Black}},
            {City::Tokyo,         CityData{City::Tokyo, Color::Red}},
            {City::Washington,    CityData{City::Washington, Color::Blue}},
    };

}

Color &Board::get_color(City city) {
    return cities[city].get_color();
}

bool &Board::is_cure(Color color) {
    switch (color) {
        case Color::Yellow:
            return cure_yellow;
        case Color::Red:
            return cure_red;
        case Color::Blue:
            return cure_blue;
        case Color::Black:
            return cure_black;
    }
    return cure_black;
}

map<City, CityData> &Board::getCities() {
    return cities;
}

std::map<City, std::vector<City>> Board::graph = {
        {City::Algiers,       {City::Madrid,       City::Paris,        City::Istanbul,      City::Cairo}},
        {City::Atlanta,       {City::Chicago,      City::Miami,        City::Washington}},
        {City::Baghdad,       {City::Tehran,       City::Istanbul,     City::Cairo,         City::Riyadh,        City::Karachi}},
        {City::Bangkok,       {City::Kolkata,      City::Chennai,      City::Jakarta,       City::HoChiMinhCity, City::HongKong}},
        {City::Beijing,       {City::Shanghai,     City::Seoul}},
        {City::Bogota,        {City::MexicoCity,   City::Lima,         City::Miami,         City::SaoPaulo,      City::BuenosAires}},
        {City::BuenosAires,   {City::Bogota,       City::SaoPaulo}},
        {City::Cairo,         {City::Algiers,      City::Istanbul,     City::Baghdad,       City::Khartoum,      City::Riyadh}},
        {City::Chennai,       {City::Mumbai,       City::Delhi,        City::Kolkata,       City::Bangkok,       City::Jakarta}},
        {City::Chicago,       {City::SanFrancisco, City::LosAngeles,   City::MexicoCity,    City::Atlanta,       City::Montreal}},
        {City::Delhi,         {City::Tehran,       City::Karachi,      City::Mumbai,        City::Chennai,       City::Kolkata}},
        {City::Essen,         {City::London,       City::Paris,        City::Milan,         City::StPetersburg}},
        {City::HoChiMinhCity, {City::Jakarta,      City::Bangkok,      City::HongKong,      City::Manila}},
        {City::HongKong,      {City::Bangkok,      City::Kolkata,      City::HoChiMinhCity, City::Shanghai,      City::Manila,  City::Taipei}},
        {City::Istanbul,      {City::Milan,        City::Algiers,      City::StPetersburg,  City::Cairo,         City::Baghdad, City::Moscow}},
        {City::Jakarta,       {City::Chennai,      City::Bangkok,      City::HoChiMinhCity, City::Sydney}},
        {City::Johannesburg,  {City::Kinshasa,     City::Khartoum}},
        {City::Karachi,       {City::Tehran,       City::Baghdad,      City::Riyadh,        City::Mumbai,        City::Delhi}},
        {City::Khartoum,      {City::Cairo,        City::Lagos,        City::Kinshasa,      City::Johannesburg}},
        {City::Kinshasa,      {City::Lagos,        City::Khartoum,     City::Johannesburg}},
        {City::Kolkata,       {City::Delhi,        City::Chennai,      City::Bangkok,       City::HongKong}},
        {City::Lagos,         {City::SaoPaulo,     City::Khartoum,     City::Kinshasa}},
        {City::Lima,          {City::MexicoCity,   City::Bogota,       City::Santiago}},
        {City::London,        {City::NewYork,      City::Madrid,       City::Essen,         City::Paris}},
        {City::LosAngeles,    {City::SanFrancisco, City::Chicago,      City::MexicoCity,    City::Sydney}},
        {City::Madrid,        {City::London,       City::NewYork,      City::Paris,         City::SaoPaulo,      City::Algiers}},
        {City::Manila,        {City::Taipei,       City::SanFrancisco, City::HoChiMinhCity, City::Sydney}},
        {City::MexicoCity,    {City::LosAngeles,   City::Chicago,      City::Miami,         City::Lima,          City::Bogota}},
        {City::Miami,         {City::Atlanta,      City::MexicoCity,   City::Washington,    City::Bogota}},
        {City::Milan,         {City::Essen,        City::Paris,        City::Istanbul}},
        {City::Montreal,      {City::Chicago,      City::Washington,   City::NewYork}},
        {City::Moscow,        {City::StPetersburg, City::Istanbul,     City::Tehran}},
        {City::Mumbai,        {City::Karachi,      City::Delhi,        City::Chennai}},
        {City::NewYork,       {City::Montreal,     City::Washington,   City::London,        City::Madrid}},
        {City::Osaka,         {City::Taipei,       City::Tokyo}},
        {City::Paris,         {City::Algiers,      City::Essen,        City::Madrid,        City::Milan,         City::London}},
        {City::Riyadh,        {City::Baghdad,      City::Cairo,        City::Karachi}},
        {City::SanFrancisco,  {City::LosAngeles,   City::Chicago,      City::Tokyo,         City::Manila}},
        {City::Santiago,      {City::Lima}},
        {City::SaoPaulo,      {City::Bogota,       City::BuenosAires,  City::Lagos,         City::Madrid}},
        {City::Seoul,         {City::Beijing,      City::Shanghai,     City::Tokyo}},
        {City::Shanghai,      {City::Beijing,      City::HongKong,     City::Taipei,        City::Seoul,         City::Tokyo}},
        {City::StPetersburg,  {City::Essen,        City::Istanbul,     City::Moscow}},
        {City::Sydney,        {City::Jakarta,      City::Manila,       City::LosAngeles}},
        {City::Taipei,        {City::Shanghai,     City::HongKong,     City::Osaka,         City::Manila}},
        {City::Tehran,        {City::Baghdad,      City::Moscow,       City::Karachi,       City::Delhi}},
        {City::Tokyo,         {City::Seoul,        City::Shanghai,     City::Osaka,         City::SanFrancisco}},
        {City::Washington,    {City::Atlanta,      City::NewYork,      City::Montreal,      City::Miami}}
};

void Board::remove_cures() {
    cure_black = false;
    cure_blue = false;
    cure_yellow = false;
    cure_red = false;
}

void Board::remove_stations() {
    for (auto &[k,v] : cities) {
        v.get_station() = false;
    }
}
