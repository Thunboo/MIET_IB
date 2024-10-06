#ifndef READERCLASS_H
#define READERCLASS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <CarClass.h>
#include <json.hpp>

class AbstractFileEditor {
public:
    virtual void changePath(std::string path) = 0;
    virtual bool isOpen() = 0;
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
};

class AbstractReader {
public:
    virtual std::string readLine() = 0;
    virtual std::tuple<std::vector<Car>, std::vector<int>> readAll() = 0;
protected:
    std::ifstream fin; // Обьект потокового ввода
};

class AbstractWriter {
public:
    virtual std::string writeLine(const Car& car) = 0;
    virtual bool writeAll(const std::vector<Car> &Cars) = 0;
protected:
    std::ofstream fout; // Обьект потокового вывода
};

class CSVReader : public AbstractReader, AbstractFileEditor {
public:
    CSVReader() { std::cout << "Reader was constructed w/o filepath" << std::endl; }
    CSVReader(std::string path) { fin = std::ifstream(path); };
    ~CSVReader() { fin.close(); }// { std::cout << "destructed" << std::endl; };

    void changePath(std::string path) override { fin = std::ifstream(path); }
    bool isOpen() override { return fin.is_open(); }
    std::string readLine() override;
    std::tuple<std::vector<Car>, std::vector<int>> readAll() override;
};

class CSVWriter : public AbstractWriter, AbstractFileEditor {
public:
    CSVWriter() { std::cout << "Writer was constructed w/o filepath" << std::endl; }
    CSVWriter(std::string path) { fout = std::ofstream(path); };
    ~CSVWriter();

    void changePath(std::string path) override { fout = std::ofstream(path); }
    bool isOpen() override { return fout.is_open(); }
    std::string writeLine(const Car& car) override;
    bool writeAll(const std::vector<Car> &Cars) override;
};

class JSONReader : public AbstractReader, AbstractFileEditor {
public:
    JSONReader() { std::cout << "Reader was constructed w/o filepath" << std::endl; }
    JSONReader(std::string path) { fin = std::ifstream(path); };
    ~JSONReader() { fin.close(); };

    void changePath(std::string path) override { fin = std::ifstream(path); }
    bool isOpen() override { return fin.is_open(); }
    std::string readLine() override { return ""; };
    std::tuple<std::vector<Car>, std::vector<int>> readAll() override;
};

class JSONWriter : public AbstractWriter, AbstractFileEditor {
public:
    JSONWriter() { std::cout << "Writer was constructed w/o filepath" << std::endl; }
    JSONWriter(std::string path) { fout = std::ofstream(path); };
    ~JSONWriter();

    void changePath(std::string path) override { fout = std::ofstream(path); }
    bool isOpen() override { return fout.is_open(); }
    std::string writeLine(const Car& car) override { return {}; };
    bool writeAll(const std::vector<Car> &Cars) override;
};

class CorruptedLineException : public std::exception {
public:
    CorruptedLineException(const std::string &message) : message(message) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};

#endif // READERCLASS_H
