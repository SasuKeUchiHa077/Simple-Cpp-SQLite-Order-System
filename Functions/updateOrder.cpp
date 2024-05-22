#include "../headerFiles/updateOrder.h"
#include <ios>
#include <iostream>
#include <limits>
#include <sqlite3.h>
#include <string>

void UpdateOrder() {
    sqlite3* dataBase;

    if (sqlite3_open("orderData.db", &dataBase) != SQLITE_OK) {
        std::cerr << "Can't open database : " << sqlite3_errmsg(dataBase) << '\n';
        sqlite3_close(dataBase);
        return;
    }

    std::string updateTable = "UPDATE orderTable SET name = ?, item = ?, quantity = ? WHERE id = ?;";
    sqlite3_stmt *statement;

    if (sqlite3_prepare_v2(dataBase, updateTable.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error : " << sqlite3_errmsg(dataBase);
        sqlite3_close(dataBase);
        return;
    }

    int customerId = 0;

    do {
        std::cout << "Enter Customer ID to Update : ";
        std::cin >> customerId;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::cin.fail()) {
            std::cerr << "Invalid Input. Try again.\n";
            continue;
        } else {
            break;
        }
    } while(true);

    std::string customerName, customerItem;
    int itemQuantity = 0;

    std::cout << "[Updating order]- ID : " << customerId << '\n';

    std::cout << "Enter Name : ";
    std::getline(std::cin, customerName);

    std::cout << "Enter Item : ";
    std::getline(std::cin, customerItem);

    do {
        std::cout << "Enter Item Quantity : ";
        std::cin >> itemQuantity;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::cin.fail() || itemQuantity <= 0) {
            std::cerr << "Invalid Input. Try again.\n";
            continue;
        } else {
            break;
        } 
    } while(true);

    sqlite3_bind_text(statement, 1, customerName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 2, customerItem.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(statement, 3, itemQuantity);
    sqlite3_bind_int(statement, 4, customerId);

    if (sqlite3_step(statement) != SQLITE_DONE) {
        std::cerr << "Error updating order : " << sqlite3_errmsg(dataBase) << '\n';
        sqlite3_finalize(statement);
        sqlite3_close(dataBase);
        return;
    }

    std::cout << "Order Data updated Successfully.\n\n";

    sqlite3_finalize(statement);
    sqlite3_close(dataBase);
}
