#include "include/Product.h"

Product::Product(std::string name) : name(name) {}
std::string Product::getName() const {
	return name;
}