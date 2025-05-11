#include "Pet.h"
#include <iostream>
#include <algorithm>

Pet::Pet(const std::string& name)
	: name(name), hunger(50), happiness(50), cleanliness(50), energy(50), health(100) {}

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

	// Health drops if any stat is too low
	if (hunger >= 90 || cleanliness <= 10 || energy <= 10 || happiness <= 10) {
		health -= 5;
	}

	ClampStats();
}

void Pet::ShowStats() const {
	std::cout << "\n== " << name << "'s Stats ==\n";
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