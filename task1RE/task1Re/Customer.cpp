#include "include/Customer.h"
#include "include/StoreManager.h"
#include <iostream>

Customer::Customer(std::string name, double balance) : name(name), balance(balance) {}

void Customer::addToShoppingList(Product* product, int quantity) {
    shoppingList.push_back(std::make_pair(product, quantity));
}

void Customer::addBalance(double amount) {
    balance += amount;
}

void purchaseItems(StoreManager& manager);
};
void Customer::purchaseItems(StoreManager& manager) {
    for (auto& item : shoppingList) {
        Product* product = item.first;
        int desiredQuantity = item.second;
        Store* store = manager.findStoreWithLowestPrice(product);
        if (store == nullptr) {
            cout << "Product " << product->getName() << " not found in any store." << endl;
            continue;
        }
        try {
            double price = store->getProductPrice(product);
            int availableQuantity = store->getProductQuantity(product);
            if (availableQuantity < desiredQuantity) {
                cout << "Not enough quantity for " << product->getName() << " in " << store->getName() << ". Available: " << availableQuantity << endl;
                continue;
            }
            double totalCost = price * desiredQuantity;
            if (balance < totalCost) {
                cout << "Insufficient funds for " << product->getName() << ". Required: $" << totalCost << ", balance: $" << balance << endl;
                continue;
            }
            store->sellProduct(product, desiredQuantity);
            balance -= totalCost;
            cout << name << " purchased " << desiredQuantity << " of " << product->getName() << " at " << store->getName() << " for $" << totalCost << endl;
        }
        catch (const exception& e) {
            cout << "Error purchasing " << product->getName() << ": " << e.what() << endl;
        }
    }
}