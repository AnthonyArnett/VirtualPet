#include "Pet.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>  // rand()
#include <ctime>    // time()

Pet::Pet(const std::string& name)
	: name(name), hunger(50), happiness(50), cleanliness(50), energy(50), health(100) {
	std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed RNG once

	int roll = std::rand() % 5;
	switch (roll) {
	case 0: personality = Personality::Lazy; break;
	case 1: personality = Personality::Hyper; break;
	case 2: personality = Personality::Neat; break;
	case 3: personality = Personality::Picky; break;
	case 4: personality = Personality::Resilient; break;
	}
}

void Pet::Feed() {
	hunger = std::max(0, hunger - 20);
	cleanliness = std::max(0, cleanliness - 5);
	std::cout << name << " enjoyed the meal!\n";
}

void Pet::Play() {
	happiness = std::min(100, happiness + 15);
	energy = std::max(0, energy - 10);
	hunger = std::min(100, hunger + 10);
	std::cout << name << " had fun playing!\n";
}

void Pet::Clean() {
	cleanliness = 100;
	std::cout << name << " is squeaky clean!\n";
}

void Pet::Sleep() {
	energy = std::min(100, energy + 30);
	hunger = std::min(100, hunger + 10);
	std::cout << name << " had a nice nap.\n";
}

void Pet::Tick() {
	hunger = std::min(100, hunger + 2);
	cleanliness = std::max(0, cleanliness - 2);
	happiness = std::max(0, happiness - 1);
	energy = std::max(0, energy - 1);

	// Trait Effects
	if (personality == Personality::Lazy) {
		energy = std::max(0, energy - 1); // Gets tired faster
	}
	if (personality == Personality::Hyper) {
		hunger = std::min(100, hunger + 1); // More hunger
	}
	if (personality == Personality::Neat && cleanliness < 30) {
		happiness = std::max(0, happiness - 2); // Gets upset when dirty
	}

	// Health drops if any stat is too low
	if (hunger >= 90 || cleanliness <= 10 || energy <= 10 || happiness <= 10) {
		health -= 5;
	}

	ClampStats();
}

void Pet::ShowStats() const {
	std::cout << "\n== " << name << "'s Stats ==\n";
	std::cout << "Mood:        " << GetMood() << "\n";
	std::cout << "Personality: " << GetPersonalityName() << "\n";
	std::cout << "Coins:       " << coins << " 🪙\n";
	std::cout << "Hunger:      " << hunger << "\n";
	std::cout << "Happiness:   " << happiness << "\n";
	std::cout << "Cleanliness: " << cleanliness << "\n";
	std::cout << "Energy:      " << energy << "\n";
	std::cout << "Health:      " << health << "\n";
}

bool Pet::IsAlive() const {
	return health > 0;
}

void Pet::ClampStats() {
	hunger = std::clamp(hunger, 0, 100);
	happiness = std::clamp(happiness, 0, 100);
	cleanliness = std::clamp(cleanliness, 0, 100);
	energy = std::clamp(energy, 0, 100);
	health = std::clamp(health, 0, 100);
}

void Pet::SaveToFile(const std::string& filename) const {
	std::ofstream out(filename);
	if (out) {
		out << name << "\n"
			<< hunger << "\n"
			<< happiness << "\n"
			<< cleanliness << "\n"
			<< energy << "\n"
			<< health << "\n"
			<< coins << "\n";
		out.close();
		std::cout << "Game saved successfully.\n";
	}
	else {
		std::cerr << "Failed to save game.\n";
	}
}

bool Pet::LoadFromFile(const std::string& filename) {
	std::ifstream in(filename);
	if (in) {
		std::getline(in, name);
		in >> hunger >> happiness >> cleanliness >> energy >> health >> coins;
		in.close();
		std::cout << "Game loaded successfully.\n";
		ClampStats();
		return true;
	}
	else {
		std::cerr << "No saved game found.\n";
		return false;
	}
}

std::string Pet::GetMood() const {
	int avg = (hunger + happiness + cleanliness + energy) / 4;

	if (health <= 20) return "💀 Critical";
	if (avg >= 75)     return "😀 Happy";
	if (avg >= 50)     return "😐 Okay";
	if (avg >= 25)     return "😢 Sad";
	return "⚠️ Miserable";
}

void Pet::TriggerRandomEvent() {
	int roll = std::rand() % 100;

	if (roll < 10) {
		std::cout << "⚡ " << name << " got scared by thunder! -5 happiness\n";
		happiness = std::max(0, happiness - 5);
	}
	else if (roll < 20) {
		std::cout << "🎁 " << name << " found an old sock and is thrilled! +5 happiness\n";
		happiness = std::min(100, happiness + 5);
	}
	else if (roll < 25) {
		std::cout << "💩 " << name << " made a mess. -5 cleanliness\n";
		cleanliness = std::max(0, cleanliness - 5);
	}
	else if (roll < 28) {
		std::cout << "💤 " << name << " took a power nap. +10 energy\n";
		energy = std::min(100, energy + 10);
	}
	else if (roll < 30) {
		std::cout << "🍪 " << name << " snuck a snack. +5 hunger\n";
		hunger = std::min(100, hunger + 5);
	}
	else if (roll < 35) {
		Item snack = { "Mystery Snack", ItemType::Food, "A weird but tasty treat. Reduces hunger.", 10 };
		AddItem(snack);
	}
	else if (roll < 38) {
		Item squeaky = { "Squeaky Toy", ItemType::Toy, "A noisy toy that brings joy.", 15 };
		AddItem(squeaky);
	}
	else if (roll < 40) {
		Item pill = { "Vitamin Pill", ItemType::Medicine, "Heals a little bit of health.", 20 };
		AddItem(pill);
	}
	else if (roll < 45) {
		int amount = (std::rand() % 5 + 1) * 10;
		AddCoins(amount);
	}
	// ~70% chance of no event
}

std::string Pet::GetPersonalityName() const {
	switch (personality) {
	case Personality::Lazy: return "Lazy";
	case Personality::Hyper: return "Hyper";
	case Personality::Neat: return "Neat";
	case Personality::Picky: return "Picky";
	case Personality::Resilient: return "Resilient";
	default: return "Unknown";
	}
}

void Pet::AddItem(const Item& item) {
	inventory.push_back(item);
	std::cout << "You received a(n) " << item.name << "!\n";
}

void Pet::ShowInventory() const {
	if (inventory.empty()) {
		std::cout << "Your inventory is empty.\n";
		return;
	}

	std::cout << "\n-- Inventory --\n";
	for (size_t i = 0; i < inventory.size(); ++i) {
		std::cout << i + 1 << ". " << inventory[i].name << " - " << inventory[i].description << "\n";
	}
}

void Pet::UseItem(int index) {
	if (index < 0 || index >= static_cast<int>(inventory.size())) {
		std::cout << "Invalid item.\n";
		return;
	}

	Item item = inventory[index];
	switch (item.type) {
	case ItemType::Food:
		hunger = std::max(0, hunger - item.power);
		std::cout << name << " ate the " << item.name << "!\n";
		break;
	case ItemType::Toy:
		happiness = std::min(100, happiness + item.power);
		std::cout << name << " played with the " << item.name << "!\n";
		break;
	case ItemType::Medicine:
		health = std::min(100, health + item.power);
		std::cout << name << " took the " << item.name << " and feels better!\n";
		break;
	}

	inventory.erase(inventory.begin() + index); // item used up
	ClampStats();
}

int Pet::GetCoins() const {
	return coins;
}

void Pet::AddCoins(int amount) {
	coins += amount;
	std::cout << name << " earned " << amount << " coins! 🪙\n";
}

bool Pet::SpendCoins(int amount) {
	if (coins >= amount) {
		coins -= amount;
		return true;
	}
	else {
		std::cout << "Not enough coins.\n";
		return false;
	}
}