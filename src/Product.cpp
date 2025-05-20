#include "Product.hpp"

Product::Product(const std::string &name, const std::string &barcode, const double price) {
    this->name = name;
    this->barcode = barcode;
    this->price = price;
}