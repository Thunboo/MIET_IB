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

//CSVReader::CSVReader(std::string path) {
//    CSVReader::fin = std::ifstream(path);
//}

//CSVReader::~CSVReader() {
//    CSVReader::fin.close();
//}

//std::string CSVReader::readLine(){
//    if (not fin.is_open()) return "";
//    std::string line;

//    if (fin.is_open()) {
//        if (not fin.eof()){
//            std::getline(fin, line);
//            return line;
//        }
//    }
//    return "";
//}

//CSVWriter::CSVWriter(std::string path) {
//    CSVWriter::fout = std::ofstream(path);
//}

//CSVWriter::~CSVWriter() {
//    CSVWriter::fout.close();
//}

//void CSVWriter::writeAll(const std::vector<Car>& Cars){
//    if (fout.is_open()) {
//        for (const auto& car: Cars) {
//            std::cout << "Writing Car № " << car.id << std::endl;
//            fout << car.id << ";"
//                 << car.brand_model << ";"
//                 << engineTypeToStrMap[car.engine] << ";"
//                 << car.horsepower << "\n";
//        }
//    }
//}

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
   return a.horsepower < b.horsepower;
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
