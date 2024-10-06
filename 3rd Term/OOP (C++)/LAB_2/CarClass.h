#ifndef CARCLASS_H
#define CARCLASS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

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
/*
std::map<std::string, engineType> engineTypeMap = {
    {"petrol", PETROL},
    {"diesel", DIESEL},
    {"hybrid", HYBRID},
    {"electric", ELECTRIC},
    {"P", PETROL},
    {"D", DIESEL},
    {"H", HYBRID},
    {"E", ELECTRIC},
    {"undefined", UNDEFINED}
};
*/
extern std::map<engineType, std::string> engineTypeToStrMap;
/*
std::map<engineType, std::string> engineTypeToStrMap = {
    {PETROL, "petrol"},
    {DIESEL, "diesel"},
    {HYBRID, "hybrid"},
    {ELECTRIC, "electric"},
    {UNDEFINED, "undefined"}
};
*/

extern std::vector<std::string> split_line(const std::string& str, std::string sep);
/*
std::vector<std::string> split_line(const std::string& str, std::string sep) {

    std::vector<std::string> tokens;

    if (!str.empty()) {
        size_t start = 0, end;
        do {
            tokens.push_back(str.substr(start, (str.find(sep, start) - start)));
            end = str.find(sep, start);
            start = end + sep.size();
        } while (end != std::string::npos);
    }

    return tokens;
}
*/

class CarsCollection {
private:
    static bool compare_HP(const Car &a, const Car &b);
    static bool compare_ID(const Car &a, const Car &b);
    static bool compare_model(const Car &a, const Car &b);
public:
    std::vector<Car> Cars;
    void add_car(const Car &v);
    void remove_car(int id);
    void sort_alphabetically(bool Descending);
    void sort_by_ID(bool Descending);
    void sort_by_HP(bool Descending);
    bool add_from_file(std::string path);
    bool save_to_file(std::string path);
    bool check_ID(int id);
};

#endif // CARCLASS_H
