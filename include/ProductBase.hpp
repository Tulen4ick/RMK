#pragma once
#include <deque>
#include "Product.hpp"
#include <map>


class ProductBase{
    std::deque<Product> products;
    std::map<std::string, Product*> barcodeMap;
    std::map<std::string, Product*> nameMap;

public:
    void loadFromCSV(const std::string &filename);
    Product *findProduct(const std::string &import);
};