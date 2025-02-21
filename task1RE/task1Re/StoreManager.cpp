#include "include/StoreManager.h"
#include "include/Store.h"
#include <limits>

void StoreManager::addStore(Store* store) {
    stores.push_back(store);
}

Store* StoreManager::findStoreWithLowestPrice(Product* product) {
    Store* lowestStore = nullptr;
    double lowestPrice = std::numeric_limits<double>::max();
    for (auto store : stores) {
        if (store->hasProduct(product)) {
            double price = store->getProductPrice(product);
            if (price < lowestPrice) {
                lowestPrice = price;
                lowestStore = store;
            }
        }
    }
    return lowestStore;
}