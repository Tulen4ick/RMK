#include "App.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>

App::App() {
    try {
        dataBase.loadFromCSV(INPUT_FILE_PATH);
    }
    catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

void App::Run() {
    std::string command;
    while(true) {
        std::cout << "Enter the command: ";
        getline(std::cin, command);
        std::transform(command.begin(), command.end(), command.begin(), [](unsigned char c){ return std::tolower(c); });
        Command(command);
    }
}

void App::Command(const std::string &command) {
    try {
        if(command == "open shift") {
            if(currentShift)
                throw std::runtime_error("Shift is already opened");
            std::string cashierName;
            std::cout << "Enter the cashier: ";
            getline(std::cin, cashierName);
            if(cashierName.empty())
                throw std::runtime_error("Cahier name cannot be empty");
            int initCash;
            std::cout << "Enter the initial cash amount: ";
            if(!(std::cin >> initCash) || (initCash <= 0)) {
                std::cin.clear();
                std::cin.ignore();
                throw std::runtime_error("Incorrect cash value");
            }
            std::cin.ignore();
            currentShift = new Shift(cashierName, initCash);
            std::cout << "Shift was opened by cashier " + cashierName << "; Initial cash is " << initCash << " units" << std::endl;
        }
        else if(command == "create receipt") {
            if(!currentShift)
                throw std::runtime_error("First, open the shift");
            if(currentReceipt)
                throw std::runtime_error("Receipt has already been created");
            currentReceipt = new Receipt();
            std::cout << "Receipt was created successfully" << std::endl;
        }
        else if(command == "add product") {
            if(!currentShift)
                throw std::runtime_error("First, open the shift; then create a receipt");
            if(!currentReceipt)
                throw std::runtime_error("First, create a receipt");
            std::string nameOrBarcode;
            int count;
            std::cout << "Enter the product name or its barcode: ";
            getline(std::cin, nameOrBarcode);
            Product *product = dataBase.findProduct(nameOrBarcode);
            if (!product)
                throw std::runtime_error("Product not found");
            std::cout << "Enter the quantity of the product: ";
            if(!(std::cin >> count) || (count <= 0)) {
                std::cin.clear();
                std::cin.ignore();
                throw std::runtime_error("Incorrect quantity of product");
            }
            std::cin.ignore();
            currentReceipt->AddProduct(product, count);
            std::cout << count << " * " + product->name + " was successfully added to the receipt" << std::endl;
        }
        else if(command == "close receipt") {
            if(!currentShift)
                throw std::runtime_error("First, open the shift; then create a receipt");
            if(!currentReceipt)
                throw std::runtime_error("First, create a receipt");
            std::string paymentMethod;
            double amount = 0.0;
            std::cout << "Enter the payment method: ";
            std::getline(std::cin, paymentMethod);
            std::transform(paymentMethod.begin(), paymentMethod.end(), paymentMethod.begin(),
            [](unsigned char c)
            { return std::tolower(c); });
            if(paymentMethod != "card" && paymentMethod != "cash")
                throw std::runtime_error("A non-existent payment method has been selected");
            if(paymentMethod == "cash") {
                std::cout << "Amount deposited for the payment (to be paid " << currentReceipt->GetTotal() << " units): ";
                if(!(std::cin >> amount)) {
                    std::cin.clear();
                    std::cin.ignore();
                    throw std::runtime_error("Incorrect amount");
                }
                std::cin.ignore();
            }
            else
                amount = currentReceipt->GetTotal();
            currentReceipt->Close(paymentMethod, amount, currentShift->GetCash());
            currentShift->AddReceipt(paymentMethod, currentReceipt->GetTotal());
            delete currentReceipt;
            currentReceipt = nullptr;
            std::cout << "Receipt was closed" << std::endl;
        }
        else if(command == "close shift") {
            if(!currentShift)
                throw std::runtime_error("First, open the shift;");
            if(currentReceipt)
                throw std::runtime_error("Close the receipt first");
            currentShift->Close();
            delete currentShift;
            currentShift = nullptr;
            std::cout << "Shift was closed" << std::endl;
        }
        else if(command == "exit") {
            if(currentShift) {
                std::string answer;
                std::cout << "Shift is opened, you should firstly close it;" << std::endl;
                std::cout << "Do you want to end the app anyway? Print <yes> if you want to: ";
                std::getline(std::cin, answer);
                std::transform(answer.begin(), answer.end(), answer.begin(),
                    [](unsigned char c)
                    { return std::tolower(c); });
                if (answer == "yes")
                    exit(0);
            }
            exit(0);
        }
        else {
            std::cerr << "Incorrect command: " << command << std::endl;
        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}