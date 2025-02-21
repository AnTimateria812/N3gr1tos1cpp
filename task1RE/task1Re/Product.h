#pragma once
#include <string>

class Product {
private:
	std::string name;
public:
	Product(std::string name);
	std::string getName() const;
};