#include "ProductBase.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

void ProductBase::loadFromCSV(const std::string &filename) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        throw std::runtime_error("Can't find DataBase file");
    }
    std::string line;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, barcode, priceString;
        std::getline(ss, name, ',');
        std::getline(ss, barcode, ',');
        std::getline(ss, priceString, ',');
        try {
            double price = std::stod(priceString);
            products.emplace_back(name, barcode, price);
            barcodeMap[barcode] = &products.back();
            nameMap[name] = &products.back();
        }catch(...){
            throw std::runtime_error("Parsing error of: " + line);
        }
    }
}

Product* ProductBase::findProduct(const std::string &import) {
    auto it1 = barcodeMap.find(import);
    if(it1 != barcodeMap.end())
        return it1->second;
    auto it2 = nameMap.find(import);
    if(it2 != nameMap.end())
        return it2->second;
    return nullptr;
}