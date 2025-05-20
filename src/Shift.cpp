#include "Shift.hpp"
#include <iostream>

Shift::Shift(std::string &name, double initCash) {
    cashier = name;
    cash = initCash;
}

void Shift::AddReceipt(const std::string &paymentMethod, double total) {
    shiftStats[paymentMethod] += total;
    if(paymentMethod == "cash")
        cash += total;
}

void Shift::Close() const {
    std::cout << "\n----------SHIFT STATISTICS----------" << std::endl;
    std::cout << "Cashier: " + cashier << std::endl;
    std::cout << "Amount of cash in the cash register: " << cash << std::endl;
    std::cout << "-------EARNINGS BY PAYMENT METHODS-------" << std::endl;
    for( auto &i: shiftStats) {
        std::cout << i.first + ": " << i.second << " units" << std::endl;
    }
    std::cout << "----------------------" << std::endl;
}

double Shift::GetCash() {
    return cash;
}