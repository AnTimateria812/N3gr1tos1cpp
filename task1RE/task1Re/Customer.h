#pragma once
#include "Product.h"
#include <vector>

class StoreManager; // Forward declaration

class Customer {
private:
    std::string name;
    double balance;
    std::vector<std::pair<Product*, int>> shoppingList;
public:
    Customer(std::string name, double balance);
    void addToShoppingList(Product* product, int quantity);
    void addBalance(double amount);
    void purchaseItems(StoreManager& manager);
};