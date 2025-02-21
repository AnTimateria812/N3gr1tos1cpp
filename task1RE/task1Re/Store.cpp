#include "include/Store.h"
#include <stdexcept>

Store::Store(std::string name) : name(name) {}

std::string Store::getName() const { return name; }

void Store::addProduct(Product* product, double price, int quantity) {
    products[product] = std::make_pair(price, quantity);
}

bool Store::hasProduct(Product* product) {
    return products.find(product) != products.end();
}

double Store::getProductPrice(Product* product) {
    if (!hasProduct(product)) throw std::runtime_error("Product not found in store");
    return products[product].first;
}

int Store::getProductQuantity(Product* product) {
    if (!hasProduct(product)) throw std::runtime_error("Product not found in store");
    return products[product].second;
}

void Store::sellProduct(Product* product, int quantity) {
    if (!hasProduct(product)) throw std::runtime_error("Product not found");
    if (products[product].second < quantity) throw std::runtime_error("Not enough quantity");
    products[product].second -= quantity;
}