#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>
#include <limits>

using namespace std;

class Product {
private:
    string name;
public:
    Product(string name) : name(name) {}
    string getName() const { return name; }
};

class Store {
private:
    string name;
    map<Product*, pair<double, int>> products;
public:
    Store(string name) : name(name) {}

    string getName() const { return name; }

    void addProduct(Product* product, double price, int quantity) {
        products[product] = make_pair(price, quantity);
    }

    bool hasProduct(Product* product) {
        return products.find(product) != products.end();
    }

    double getProductPrice(Product* product) {
        if (!hasProduct(product)) {
            throw runtime_error("Product not found in store");
        }
        return products[product].first;
    }

    int getProductQuantity(Product* product) {
        if (!hasProduct(product)) {
            throw runtime_error("Product not found in store");
        }
        return products[product].second;
    }

    void sellProduct(Product* product, int quantity) {
        if (!hasProduct(product)) {
            throw runtime_error("Product not found");
        }
        if (products[product].second < quantity) {
            throw runtime_error("Not enough quantity");
        }
        products[product].second -= quantity;
    }
};

class StoreManager;

class Customer {
private:
    string name;
    double balance;
    vector<pair<Product*, int>> shoppingList;
public:
    Customer(string name, double balance) : name(name), balance(balance) {}

    void addToShoppingList(Product* product, int quantity) {
        shoppingList.push_back(make_pair(product, quantity));
    }

    void addBalance(double amount) {
        balance += amount;
    }

    void purchaseItems(StoreManager& manager);
};

class StoreManager {
private:
    vector<Store*> stores;
public:
    void addStore(Store* store) {
        stores.push_back(store);
    }

    Store* findStoreWithLowestPrice(Product* product) {
        Store* lowestStore = nullptr;
        double lowestPrice = numeric_limits<double>::max();
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

    friend class Customer;
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

int main() {
    Product apple("Apple");
    Product bread("Bread");

    Store store1("Grocery World");
    Store store2("Fresh Market");

    store1.addProduct(&apple, 1.5, 10);
    store1.addProduct(&bread, 2.0, 5);
    store2.addProduct(&apple, 1.2, 8);
    store2.addProduct(&bread, 2.5, 7);

    StoreManager manager;
    manager.addStore(&store1);
    manager.addStore(&store2);

    Customer customer("Alice", 20.0);
    customer.addToShoppingList(&apple, 3);
    customer.addToShoppingList(&bread, 2);

    customer.purchaseItems(manager);

    cout << "\nRemaining quantities after initial purchase:" << endl;
    cout << "Apple in " << store1.getName() << ": " << store1.getProductQuantity(&apple) << endl;
    cout << "Apple in " << store2.getName() << ": " << store2.getProductQuantity(&apple) << endl;
    cout << "Bread in " << store1.getName() << ": " << store1.getProductQuantity(&bread) << endl;
    cout << "Bread in " << store2.getName() << ": " << store2.getProductQuantity(&bread) << endl;

    customer.addBalance(10.0);
    customer.addToShoppingList(&bread, 5);
    cout << "\nAttempting to purchase 5 Bread with added balance..." << endl;
    customer.purchaseItems(manager);

    return 0;
}
