#include "include/Product.h"
#include "include/Store.h"
#include "include/Customer.h"
#include "include/StoreManager.h"
#include <iostream>

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