#include "../headerFiles/viewOrder.h"
#include <filesystem>
#include <sqlite3.h>
#include <iostream>

void ViewOrder() {
    std::filesystem::path dataPath = "orderData.db";
    if (!(std::filesystem::exists(dataPath))) {
        std::cerr << "DataBase isn't created yet.\n";
        return;
    }

    sqlite3* dataBase;
    int returnCode = sqlite3_open("orderData.db", &dataBase);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Can't open dataBase : " << sqlite3_errmsg(dataBase) << '\n';
        sqlite3_close(dataBase);
        return;
    }

    sqlite3_stmt* statement;

    std::string selectData = "SELECT * FROM orderTable WHERE id = ?;";
    returnCode = sqlite3_prepare_v2(dataBase, selectData.c_str(), -1, &statement, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Can't select dataBase : " << sqlite3_errmsg(dataBase) << '\n';
        sqlite3_close(dataBase);
        return;
    }

    int customerID = 0;

    std::cout << "Enter Customer ID to inspect order : ";
    std::cin >> customerID;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    sqlite3_bind_int(statement, 1, customerID);
    
    if (sqlite3_step(statement) == SQLITE_ROW) {
        std::cout << "ID : " << sqlite3_column_int(statement, 0) << "\n";
        std::cout << "Name : " << sqlite3_column_text(statement, 1) << "\n";
        std::cout << "Item : " << sqlite3_column_text(statement, 2) << '\n';
        std::cout << "Item Quantity : " << sqlite3_column_int(statement, 3) << "\n\n";
    } else {
        std::cerr << "Order not found.\n\n";
    }

    sqlite3_finalize(statement);
    sqlite3_close(dataBase);
}


