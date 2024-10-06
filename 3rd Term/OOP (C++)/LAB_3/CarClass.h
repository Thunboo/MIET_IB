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
extern std::map<engineType, std::string> engineTypeToStrMap;
extern std::vector<std::string> split_line(const std::string& str, std::string sep);

class CSVReader {
public:
    CSVReader() { std::cout << "constructed" << std::endl; };
    CSVReader(std::string path);
    ~CSVReader();// { std::cout << "destructed" << std::endl; };
    void changePath(std::string path) { fin = std::ifstream(path); }
    bool isOpen() const { return fin.is_open(); }
    std::string readLine();
    std::ifstream fin; // Обьект потокового ввода
};

class CSVWriter
{
public:
    CSVWriter() { std::cout << "constructed" << std::endl; };
    CSVWriter(std::string path);
    ~CSVWriter();// { std::cout << "destructed" << std::endl; };
    void changePath(std::string path) { fout = std::ofstream(path); }
    bool isOpen() const { return fout.is_open(); }
    void writeAll(const std::vector<Car>& Cars);
    std::ofstream fout; // Обьект потокового вывода
};

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
    bool add_from_file(CSVReader& Reader);
    bool save_to_file(CSVWriter& Writer);
    bool check_ID(int id);
};

#endif // CARCLASS_H
