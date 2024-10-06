#include "ReaderClass.h"
#include "mainwindow.h"

std::string CSVReader::readLine() {
    if (not fin.is_open()) return "";
    std::string line;

    if (fin.is_open()) {
        if (not fin.eof()){
            std::getline(fin, line);
            return line;
        }
    }
    return "";
}

std::vector<Car> CSVReader::readAll() {
    std::vector<Car> Cars;
    std::string line = this->readLine();

    while (line != ""){
        std::vector<std::string> data = this->split_line(line, ";");
//        std::vector<std::string> data = split_line(line, ";");

        Car temp;

        temp.id = stoi(data[0]);
        std::cout << "Read ID : " << temp.id << std::endl;
        temp.brand_model = data[1];
        temp.engine = engineTypeMap[data[2]];
        temp.horsepower = stoi(data[3]);

        Cars.push_back(temp);
        line = this->readLine();
    }
    return Cars;
}

std::string CSVWriter::writeLine(const Car& car) {
    std::string newLine = "";

    newLine = std::to_string(car.id)         + ";"
            + car.brand_model                + ";"
            + engineTypeToStrMap[car.engine] + ";"
            + std::to_string(car.horsepower) + "\n";

    return newLine;
}

bool CSVWriter::writeAll(const std::vector<Car> &Cars){
    if (fout.is_open()) {
        for (const auto& car: Cars) {
            std::cout << "Writing Car № " << car.id << std::endl;
            fout << this->writeLine(car);
        }
        return true;
    }
    return false;
}

/////////////////////////////////////////

using json = nlohmann::json;
void to_json(json& j, const Car& car){
    j = json{
        {"id",          car.id},
        {"brand_model", car.brand_model},
        {"engine",      engineTypeToStrMap[car.engine]},
        {"hp",          car.horsepower}
    };
}
//void from_json(const json& j, Car& car) {
//    j.at("id").get_to(car.id);
//    j.at("brand_model").get_to(car.brand_model);
//    j.at("engine").get_to(car.engine);
//    j.at("hp").get_to(car.horsepower);
//}


std::vector<Car> JSONReader::readAll() {
    if (!(this->isOpen())) return {};

    std::vector<Car> Cars;

    nlohmann::json json;
    fin >> json;

    for (const auto &j: json)
    {
        Car car;
        car.id          = j["id"];
        car.brand_model = j["brand_model"];
        car.engine      = engineTypeMap[j["engine"]];
        car.horsepower  = j["hp"];

        Cars.push_back(car);
    }
    return Cars;
}

bool JSONWriter::writeAll(const std::vector<Car> &Cars){
    if (fout.is_open())
    {
/*
        nlohmann::json j;
        fout << "[\n";
        bool first = true;
        for (const auto& car: Cars)
        {
            if (first) first = false;
            else fout << ",";
            j = nlohmann::json{
                {"id",          car.id},
                {"brand_model", car.brand_model},
                {"engine",      engineTypeToStrMap[car.engine]},
                {"hp",          car.horsepower}
            };
            fout << std::setw(4) << j << std::endl;
        }
        fout << "\n]";
*/

        json jsonArray = Cars;
        fout << std::setw(4) << jsonArray << std::endl;

/*
        bool first_obj = true;
        fout << "[" << std::endl;
        for (const auto &car: Cars)
        {
            if (first_obj)  first_obj = false;
            else    fout << ",\n";

            fout << "{\n\"id\": "           << car.id           << ",\n"
                 << "\"brand_model\": \""   << car.brand_model  << "\",\n"
                 << "\"engine\": \""        << engineTypeToStrMap[car.engine] << "\",\n"
                 << "\"hp\": "              << car.horsepower   << "\n}";
        }
        fout << "]" << std::endl;
        return true;
*/
    }
    return false;
}
