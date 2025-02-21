#pragma once
#include "Product.h"
#include <map>
#include <string>
#include <utility>

class Store {
private:
    std::string name;
    std::map<Product*, std::pair<double, int>> products;
public:
    Store(std::string name);
    std::string getName() const;
    void addProduct(Product* product, double price, int quantity);
    bool hasProduct(Product* product);
    double getProductPrice(Product* product);
    int getProductQuantity(Product* product);
    void sellProduct(Product* product, int quantity);
};