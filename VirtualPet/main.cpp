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
    Pet myPet("Unnamed");

    // Try to load saved pet
    bool hasSave = myPet.LoadFromFile("save.dat");

    if (!hasSave) {
        std::cout << "Welcome to Virtual Pet Simulator!\n";
        std::cout << "Enter your pet's name: ";
        std::getline(std::cin, name);
        myPet = Pet(name);
    }

    bool running = true;

    while (running && myPet.IsAlive()) {
        myPet.ShowStats();
        ShowMenu();

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: myPet.Feed(); break;
        case 2: myPet.Play(); break;
        case 3: myPet.Clean(); break;
        case 4: myPet.Sleep(); break;
        case 5:
            running = false;
            myPet.SaveToFile("save.dat");
            break;
        default: std::cout << "Invalid choice.\n"; break;
        }

        myPet.Tick();
        myPet.TriggerRandomEvent();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    if (!myPet.IsAlive()) {
        std::cout << "\nOh no! " << myPet.GetName() << " has passed away... \n";
        std::remove("save.dat"); // Delete save on death
    }
    else {
        std::cout << "\nThanks for playing!\n";
    }

    return 0;
}
