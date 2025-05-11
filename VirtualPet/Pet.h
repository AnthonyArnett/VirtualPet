#pragma once
#include <string>

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

private:
	std::string name;
	int hunger;
	int happiness;
	int cleanliness;
	int energy;
	int health;

	void ClampStats();
};
