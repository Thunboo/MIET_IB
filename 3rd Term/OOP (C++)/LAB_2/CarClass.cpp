#include "CarClass.h"
#include "mainwindow.h"

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


std::map<engineType, std::string> engineTypeToStrMap = {
    {PETROL, "petrol"},
    {DIESEL, "diesel"},
    {HYBRID, "hybrid"},
    {ELECTRIC, "electric"},
    {UNDEFINED, "undefined"}
};

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

void CarsCollection::add_car(const Car &c) {
    this->Cars.push_back(c);
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

bool CarsCollection::add_from_file(std::string path) {
    std::ifstream file(path);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::vector<std::string> data = split_line(line, ";");

            Car temp;

            temp.id = stoi(data[0]);
            temp.brand_model = data[1];
            temp.engine = engineTypeMap[data[2]];
            temp.horsepower = stoi(data[3]);

            this->Cars.push_back(temp);
        }
        file.close();
        return true;
    }
    else return false;
}

bool CarsCollection::save_to_file(std::string path) {
    std::ofstream outfile(path);
    if (outfile.is_open()){
        for (const auto &v: this->Cars)
            outfile << v.id << ";"
                    << v.brand_model << ";"
                    << engineTypeToStrMap[v.engine] << ";"
                    << v.horsepower << std::endl;
        outfile.close();
        return true;
    }
    else
        return false;
}

bool CarsCollection::check_ID(int ID){
    for (const auto &v: this->Cars){
        if (v.id == ID)
            return true;
    }
    return false;
}
