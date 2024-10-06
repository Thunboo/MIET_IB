#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <iomanip>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
/*
enum engineType  {
   UNDEFINED, 
   PETROL, 
   DIESEL, 
   HYBRID, 
   ELECTRIC
};

struct Car  {
    int id;
    string brand_model;
    engineType engine;
    int horsepower;
};

vector<string> split_line(const string& str, string sep) {

    vector<string> tokens;

    if (!str.empty()) {
        size_t start = 0, end;
        do {
            tokens.push_back(str.substr(start, (str.find(sep, start) - start)));
            end = str.find(sep, start);
            start = end + sep.size();
        } while (end != string::npos);
    }

    return tokens;
}

engineType readTypeToEnum(string type) { //?
    if      (type == "P") return PETROL;
    else if (type == "D") return DIESEL;
    else if (type == "H") return HYBRID;
    else if (type == "E") return ELECTRIC;
}

string engineTypeToStr(engineType engine) {
    switch (engine) {
        case PETROL:    return "Petrol";
        case DIESEL:    return "Diesel";
        case HYBRID:    return "Hybrid";
        case ELECTRIC:  return "Electro";
        default:        return "Undefined";
    }
}

bool compare(Car a, Car b) {
    return a.horsepower > b.horsepower;
}

bool condition(Car car) {
    if (   car.horsepower > 249
        && car.engine == PETROL) {
        return true;
    }
    return false;
}

int main_1() {
    int numOfCars, id;
//    cout << "Please, write the number of cars in the list: ";
//    cin >> numOfCars;
//    cout << endl;

    string line;
    std::ifstream file("DB.csv");
    std::getline(file, line);

    string ts;
    ts = split_line(line, ";")[1];
    cout << ts << endl;
    numOfCars = stoi(ts);
    cout << numOfCars << endl;

    vector <Car> DB(numOfCars);

    vector<int> formating = { 2, 13, 11, 3 };
    vector<string> colNames = { "ID", "Brand & Model", "Engine Type", "HP" };

    if (file.is_open()){
        while (!file.eof()) {
            std::getline(file, line);
            vector <string> temp = split_line(line, ";");

            if (temp[1].size() > formating[1]) {
                formating[1] = (int)temp[1].size();
            }

            id = stoi(temp[0]);
//            if (id == numOfCars) break;
            DB[id - 1].id = id;
            DB[id - 1].brand_model = temp[1];
            DB[id - 1].engine = readTypeToEnum(temp[2]);
            DB[id - 1].horsepower = stoi(temp[3]);
            cout << std::setw(formating[0]) << DB[id - 1].id << " | "
                 << std::setw(formating[1]) << DB[id - 1].brand_model << " | "
                 << std::setw(formating[2]) << engineTypeToStr(DB[id - 1].engine) << " | "
                 << std::setw(formating[3]) << DB[id - 1].horsepower << " | \n";
        }

        file.close();
    }
    else {
        cout << "Failed to open file" << endl;
    }

    std::sort(DB.begin(), DB.end(), compare);

    // FIRST ROW
    for (int i = 0; i < colNames.size(); i++) {
        cout << std::setw(formating[i]) << colNames[i] << " | ";
    }
    cout << std::endl;

    for (int i = 0; i < numOfCars; i++) {
        if (DB[i].id == 0) continue;
//        if (!condition(DB[i])) continue;
        cout << std::setw(formating[0]) << DB[i].id << " | " 
             << std::setw(formating[1]) << DB[i].brand_model << " | "
             << std::setw(formating[2]) << engineTypeToStr(DB[i].engine) << " | "
             << std::setw(formating[3]) << DB[i].horsepower << " | \n";
    }


    std::ofstream outfile("DB_sorted.csv");

    if (outfile.is_open()) {
        outfile << "Size" << ";" << DB.size() << endl;
        for (int i = 0; i < DB.size(); i++) {
            if (DB[i].id != 0) {
                outfile << DB[i].id << ";" << DB[i].brand_model << ";" << engineTypeToStr(DB[i].engine)[0] << ";" << DB[i].horsepower << "\n";
            }
        }
    }
    else std::cout << "\nCouldn't create the file" << std::endl;
    std::cout << "\nFile was written" << std::endl;

    return 0;
}

int main_2() {
    static vector<int> nums = { 1,2,3,4,5,6,7,8 };
    for (const auto& N : nums) {
        cout << N << " ";
    }

    cout << endl;

    nums.push_back(10);
    nums[2] = 2;
    nums[0] = 0;
    for (const auto& N : nums) {
        cout << N << " ";
    }
    return 0;
}
*/

class Reader {
public:
    Reader() { cout << "created" << endl; };
    Reader(const int x) { this->Sid = x;  }
    ~Reader() { cout << "destructed" << endl; };
    void set_Sid(const int x) { this->Sid = x; }
    int get_Sid() { return Sid; }
private:
    int Sid;
};

int main() {
    Reader MR(3);
    MR.set_Sid(3);
    cout << MR.get_Sid() << endl;

}