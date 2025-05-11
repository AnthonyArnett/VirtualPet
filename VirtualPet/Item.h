#pragma once
#include <string>

enum class ItemType {
	Food,
	Toy,
	Medicine
};

struct Item {
	std::string name;
	ItemType type;
	std::string description;
	int power; // How strong it is (like +10 happiness)
};
