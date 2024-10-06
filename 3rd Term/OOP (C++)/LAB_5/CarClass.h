#ifndef CARCLASS_H
#define CARCLASS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

enum fileType {
    CSV = -1,
    JSON = -2
};

enum engineType {
   UNDEFINED,
   PETROL,
   DIESEL,
   HYBRID,
   ELECTRIC
};

struct Car {
    int id;
    std::string brand_model;
    engineType engine;
    int horsepower;
};

extern std::map<std::string, engineType> engineTypeMap;
extern std::map<engineType, std::string> engineTypeToStrMap;

class CarsCollection {
private:
    static bool compare_HP(const Car &a, const Car &b);
    static bool compare_ID(const Car &a, const Car &b);
    static bool compare_model(const Car &a, const Car &b);
public:
    std::vector<Car> Cars;
    void add_car(const Car &c);
    void add_cars(const std::vector<Car> &cs);
    void remove_car(int id);
    void sort_alphabetically(bool Descending);
    void sort_by_ID(bool Descending);
    void sort_by_HP(bool Descending);
    bool add_from_file(std::string path, fileType type); // тут был врайтер
    bool save_to_file(std::string path, fileType type);
    bool check_ID(int id);
};

#endif // CARCLASS_H
