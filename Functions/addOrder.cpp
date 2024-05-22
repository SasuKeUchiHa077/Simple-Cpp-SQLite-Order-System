#include "../headerFiles/addOrder.h"
#include <cctype>
#include <cstddef>
#include <filesystem>
#include <ios>
#include <iostream>
#include <limits>
#include <sqlite3.h>
#include <string>

void CreateDataBase() {
    sqlite3* dataBase;
    int returnCode = sqlite3_open("orderData.db", &dataBase);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Can't create DataBase : " << sqlite3_errmsg(dataBase) << '\n';
        sqlite3_close(dataBase);
        return;
    }

    std::string createTable = "CREATE TABLE IF NOT EXISTS orderTable (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, item TEXT NOT NULL, quantity INTEGER NOT NULL)";
    returnCode = sqlite3_exec(dataBase, createTable.c_str(), nullptr, nullptr, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Can't create table : " << sqlite3_errmsg(dataBase) << '\n';
        sqlite3_close(dataBase);
        return;
    }
    sqlite3_close(dataBase);;
}

void InsertData(const std::string customerName, const std::string customerItem, const int itemQuantity) {
    sqlite3* dataBase;
    int returnCode = sqlite3_open("orderData.db", &dataBase);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Cant open DataBase : " << sqlite3_errmsg(dataBase) << '\n';
        sqlite3_close(dataBase);
        return;
    }

    std::string insertData = "INSERT INTO orderTable (name, item, quantity) VALUES ('" + customerName + "', '" + customerItem + "', " + std::to_string(itemQuantity)+ ");";
    returnCode = sqlite3_exec(dataBase, insertData.c_str(), nullptr, nullptr, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Cant Insert DataBase : " << sqlite3_errmsg(dataBase) << '\n';
        sqlite3_close(dataBase);
        return;
    }
    sqlite3_close(dataBase);
}

void AddOrder(std::string &customerName, std::string &customerItem, int &itemQuantity) {
    std::filesystem::path dataPath = "orderData.db";
    if (!std::filesystem::exists(dataPath)) {
        CreateDataBase();
    }

    std::cout << "\n[Enter Order details:]\n";

    std::cout << "Enter Customer Name : ";
    std::getline(std::cin, customerName);

    std::cout << "Enter Customer Item : ";
    std::getline(std::cin, customerItem);

    do {
        std::cout << "Enter Item Quantity : ";
        std::cin >> itemQuantity;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::cin.fail() || itemQuantity <= 0) {
            std::cerr << "Inavlid Input. Try again.\n";
            continue;
        } else {
            break;
        }
    } while(true);
    InsertData(customerName, customerItem, itemQuantity);
}

