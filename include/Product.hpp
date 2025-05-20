#pragma once
#include <string>

class Product{
    public:
        std::string name;
        std::string barcode;
        double price;
        Product(const std::string &name, const std::string &barcode, const double price);
};