#include "Receipt.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cctype>

void Receipt::AddProduct(Product *product, int count) {
    products.emplace_back(product, count);
    total += product->price * count;
}

void Receipt::Close(const std::string &method, double amount, double cashInRegister) {
    paymentMethod = method;
    if (method == "cash" && amount < total)
        throw std::runtime_error("insufficient funds for payment");
    deposit = amount - total;
    if (cashInRegister < deposit)
        throw std::runtime_error("Not enough money in the cash register for change");
    Receipt::Print();
}

void Receipt::Print() {
    std::cout << "\n-----RECEIPT-----" << std::endl;
    std::cout << "NAME-----PRICE-----COUNT-----TOTAL" << std::endl;
    for(auto& i: products) {
        double itotal = i.first->price * i.second;
        std::cout << i.first->name 
        << "     " 
        << i.first->price << "     *     " << i.second
        << "     " 
        << itotal 
        << std::endl;
    }
    std::cout << "---------------------" << std::endl;
    std::cout << "Result: " << total << " units" << std::endl;
    std::cout << "Payment method: " << paymentMethod << std::endl;
    std::cout << "Deposit amount : " << deposit << " units" << std::endl;
    std::cout << "----------------------" << std::endl;
}

double Receipt::GetTotal() {
    return total;
}