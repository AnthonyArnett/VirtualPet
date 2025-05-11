

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>
#include <vector>
#include "Pet.h"
#include "Item.h"

std::vector<Item> GetShopItems() {
    return {
        { "Yummy Snack", ItemType::Food, "Reduces hunger by 20.", 20 },
        { "Rubber Ball", ItemType::Toy, "Boosts happiness by 20.", 20 },
        { "Health Potion", ItemType::Medicine, "Restores 30 health.", 30 }
    };
}

void OpenShop(Pet& pet) {
    std::vector<Item> shopItems = GetShopItems();
    std::cout << "\n-- 🛒 Pet Shop --\n";
    for (size_t i = 0; i < shopItems.size(); ++i) {
        int price = shopItems[i].power * 2; // Example price formula
        std::cout << i + 1 << ". " << shopItems[i].name
            << " (" << price << " coins) - " << shopItems[i].description << "\n";
    }
    std::cout << "0. Leave Shop\n";
    std::cout << "Choose an item to buy: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice > 0 && choice <= static_cast<int>(shopItems.size())) {
        Item item = shopItems[choice - 1];
        int price = item.power * 2;

        if (pet.SpendCoins(price)) {
            pet.AddItem(item);
            std::cout << "You bought " << item.name << "!\n";
        }
        else {
            std::cout << "You can't afford that.\n";
        }
    }
    else if (choice != 0) {
        std::cout << "Invalid choice.\n";
    }
}

void ShowMenu() {
    std::cout << "\nWhat would you like to do?\n";
    std::cout << "1. Feed\n";
    std::cout << "2. Play\n";
    std::cout << "3. Clean\n";
    std::cout << "4. Sleep\n";
    std::cout << "5. Use Item\n";
    std::cout << "6. Open Shop\n";
	std::cout << "7. Quit\n";
    std::cout << "Choose an option: ";
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
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
            myPet.ShowInventory();
            std::cout << "Choose item to use (or 0 to cancel): ";
            int itemChoice;
            std::cin >> itemChoice;
            std::cin.ignore();
            if (itemChoice > 0)
                myPet.UseItem(itemChoice - 1);
            break;
        case 6:
            OpenShop(myPet);
            break;
        case 7:
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
