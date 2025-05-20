#include "ProductBase.hpp"
#include "Shift.hpp"

class App {
    ProductBase dataBase;
    Shift *currentShift = nullptr;
    Receipt *currentReceipt = nullptr;

public:
    App();
    void Run();
    void Command(const std::string &command);
};