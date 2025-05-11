#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "Pet.h"

void ShowMenu() {
    std::cout << "\nWhat would you like to do?\n";
    std::cout << "1. Feed\n";
    std::cout << "2. Play\n";
    std::cout << "3. Clean\n";
    std::cout << "4. Sleep\n";
    std::cout << "5. Quit\n";
    std::cout << "Choose an option: ";
}

int main() {
    std::string name;
    std::cout << "Welcome to Virtual Pet Simulator!\n";
    std::cout << "Enter your pet's name: ";
    std::getline(std::cin, name);

    Pet myPet(name);
    bool running = true;

    while (running && myPet.IsAlive()) {
        myPet.ShowStats();
        ShowMenu();

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // clear newline from input buffer

        switch (choice) {
        case 1: myPet.Feed(); break;
        case 2: myPet.Play(); break;
        case 3: myPet.Clean(); break;
        case 4: myPet.Sleep(); break;
        case 5: running = false; break;
        default: std::cout << "Invalid choice.\n"; break;
        }

        // Simulate time passing after each action
        myPet.Tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Slow it down a bit
    }

    if (!myPet.IsAlive()) {
        std::cout << "\nOh no! " << name << " has passed away...\n";
    }
    else {
        std::cout << "\nThanks for playing!\n";
    }

    return 0;
}