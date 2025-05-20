#pragma once
#include <vector>
#include "Product.hpp"

class Receipt {
    std::vector<std::pair<Product *, int>> products;
    std::string paymentMethod;
    double total = 0.0;
    double deposit = 0.0;

public:
    void AddProduct(Product *product, int count);
    void Close(const std::string &method, double amount, double cashInRegister);
    void Print();
    double GetTotal();
};