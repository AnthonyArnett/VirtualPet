#pragma once
#include <string>
#include <vector>
#include "Item.h"

enum class Personality {
	Lazy,
	Hyper,
	Neat,
	Picky,
	Resilient
};

class Pet {
public:
	Pet(const std::string& name);

	void Feed();
	void Play();
	void Clean();
	void Sleep();

	void Tick(); // Called every turn to simulate time passing
	void ShowStats() const;
	bool IsAlive() const;

	void SaveToFile(const std::string& filename) const;
	bool LoadFromFile(const std::string& filename);

	std::string GetName() const { return name; }

	std::string GetMood() const;

	void TriggerRandomEvent();

	std::string GetPersonalityName() const;

	void AddItem(const Item& item);
	void ShowInventory() const;
	void UseItem(int index);

	int GetCoins() const;
	void AddCoins(int amount);
	bool SpendCoins(int amount);

private:
	std::string name;
	int hunger;
	int happiness;
	int cleanliness;
	int energy;
	int health;

	Personality personality;

	void ClampStats();

	std::vector<Item> inventory;

	int coins = 0;
};
