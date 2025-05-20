#pragma once
#include "Receipt.hpp"
#include <map>

class Shift {
    std::string cashier;
    double cash;
    std::map<std::string, double> shiftStats;

public:
    Shift(std::string &name, double initCash);
    void AddReceipt(const std::string &paymentMethod, double total);
    void Close() const;
    double GetCash();
};