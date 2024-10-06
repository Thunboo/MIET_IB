#include "CarClass.h"
#include "mainwindow.h"

std::map<std::string, engineType> engineTypeMap = {
    {"petrol", PETROL},
    {"diesel", DIESEL},
    {"hybrid", HYBRID},
    {"electric", ELECTRIC},
    {"electro", ELECTRIC},
    {"P", PETROL},
    {"D", DIESEL},
    {"H", HYBRID},
    {"E", ELECTRIC},
    {"undefined", UNDEFINED}
};

std::map<engineType, std::string> engineTypeToStrMap = {
    {PETROL, "petrol"},
    {DIESEL, "diesel"},
    {HYBRID, "hybrid"},
    {ELECTRIC, "electric"},
    {UNDEFINED, "undefined"}
};

void CarsCollection::add_car(const Car &c) {
    this->Cars.push_back(c);
}

void CarsCollection::add_cars(const std::vector<Car> &cs) {
    for (const auto& car: cs){
        this->Cars.push_back(car);
    }
}

void CarsCollection::remove_car(int ID) {
    for (auto to_remove = this->Cars.begin(); to_remove != this->Cars.end(); ++to_remove)
        if (to_remove->id == ID){
            this->Cars.erase(to_remove);
            break;
   }
}

bool CarsCollection::compare_model(const Car &a, const Car &b) {
   return a.brand_model < b.brand_model;
}

void CarsCollection::sort_alphabetically(bool Descending) {
    if (not Descending){
        std::sort(this->Cars.begin(), this->Cars.end(), compare_model);
    }
    else {
        std::sort(this->Cars.begin(), this->Cars.end(), [](auto a, auto b){return not compare_model(a,b); });
    }
}

bool CarsCollection::compare_HP(const Car &a, const Car &b) {
//   return a.horsepower < b.horsepower;
    return a < b;
}

void CarsCollection::sort_by_HP(bool Descending){
    if (not Descending){
        std::sort(this->Cars.begin(), this->Cars.end(), compare_HP);
    }
    else {
        std::sort(this->Cars.begin(), this->Cars.end(), [](auto a, auto b){return not compare_HP(a, b);});
    }

}

bool CarsCollection::compare_ID(const Car &a, const Car &b) {
   return a.id < b.id;
}

void CarsCollection::sort_by_ID(bool Descending){
    if (not Descending){
        std::sort(this->Cars.begin(), this->Cars.end(), compare_ID);
    }
    else {
        std::sort(this->Cars.begin(), this->Cars.end(), [](auto a, auto b){return not compare_ID(a, b);});
    }

}

bool CarsCollection::check_ID(int ID){
    for (const auto &v: this->Cars){
        if (v.id == ID)
            return true;
    }
    return false;
}
