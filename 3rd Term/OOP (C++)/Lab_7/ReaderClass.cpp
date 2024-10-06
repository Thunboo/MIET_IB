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

std::tuple<std::vector<Car>, std::vector<int>> CSVReader::readAll() {
    std::vector<Car> Cars = {};
    std::string line = this->readLine();
    int corruptedLineNumber = 1;
    std::vector<int> corruptedLinesNumbers = {};

    while (line != ""){
        try
        {
            std::vector<std::string> data = this->split_line(line, ";");
            if (data.size() < 4) throw CorruptedLineException("Corrupted line in CSV File: not enough fields");

            Car temp;

            temp.id = stoi(data[0]);
            std::cout << "Read ID : " << temp.id << std::endl;
            temp.brand_model = data[1];
            temp.engine = engineTypeMap[data[2]];
            temp.horsepower = stoi(data[3]);

            Cars.push_back(temp);
            line = this->readLine();

        }
        catch (const CorruptedLineException &e)
        {
            corruptedLinesNumbers.push_back(corruptedLineNumber);
        }
        catch (std::invalid_argument e)
        {
            line = this->readLine();
            corruptedLinesNumbers.push_back(corruptedLineNumber);
            std::cout << "Caught an invalid argument exception: " << e.what() << std::endl;
            //            std::cerr << "Caught an invalid argument exception: " << e.what() << std::endl;
        }
        corruptedLineNumber++;
    }
    return std::make_tuple(Cars, corruptedLinesNumbers);
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

std::tuple<std::vector<Car>, std::vector<int>> JSONReader::readAll() {
    if (!(this->isOpen())) return {};

    std::vector<Car> Cars;
    std::vector<int> corruptedLinesNumbers = {};

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
    return std::make_tuple(Cars, corruptedLinesNumbers);
}

bool JSONWriter::writeAll(const std::vector<Car> &Cars){
    if (fout.is_open())
    {
        json jsonArray = Cars;
        fout << std::setw(4) << jsonArray << std::endl;
    }
    return false;
}
