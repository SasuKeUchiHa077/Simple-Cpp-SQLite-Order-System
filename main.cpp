#include "headerFiles/addOrder.h"
#include "headerFiles/viewOrder.h"
#include "headerFiles/updateOrder.h"
#include <cctype>
#include <cstddef>
#include <ios>
#include <iostream>
#include <limits>
#include <sqlite3.h>
#include <string>

int main(int argc, char *argv[]) {
    char userChoice = 'n';
    bool running = true;

    std::string customerName, customerItem;
    int itemQuantity = 0;

    do {
        std::cout << "[A]dd Order\n[V]iew Order\n[U]pdate Order\n[E]xit\nEnter : ";
        std::cin >> userChoice;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        userChoice = std::toupper(userChoice);

        switch (userChoice) {
            case 'A':
                AddOrder(customerName, customerItem, itemQuantity);
                break;

            case 'V':
                ViewOrder();
                break;

            case 'U':
                UpdateOrder();
                break;

            case 'E':
                running = false;
                break;

            default:
               std::cout << "Invalid Choice.\n";
                break;
        }
    } while (running);
    return 0;
}
