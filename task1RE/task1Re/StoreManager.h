#pragma once
#include <vector>

class Store;
class Product;

class StoreManager {
private:
    std::vector<Store*> stores;
public:
    void addStore(Store* store);
    Store* findStoreWithLowestPrice(Product* product);
    friend class Customer;
};