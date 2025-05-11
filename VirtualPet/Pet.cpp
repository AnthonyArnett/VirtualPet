#include "Pet.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>  // rand()
#include <ctime>    // time()

Pet::Pet(const std::string& name)
	: name(name), hunger(50), happiness(50), cleanliness(50), energy(50), health(100) {
	std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed RNG once
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

	// Health drops if any stat is too low
	if (hunger >= 90 || cleanliness <= 10 || energy <= 10 || happiness <= 10) {
		health -= 5;
	}

	ClampStats();
}

void Pet::ShowStats() const {
	std::cout << "\n== " << name << "'s Stats ==\n";
	std::cout << "Mood:        " << GetMood() << "\n";
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
			<< health << "\n";
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
		in >> hunger >> happiness >> cleanliness >> energy >> health;
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
	// ~70% chance of no event
}