/*
  Solución Tarea 2.1.3
  Tema 2.1 Construcción de software modular
  2º Ingeniería Informática
  CUNEF Universidad
 */

#include "Robot/ExtraterrestrialRobot.hpp"
#include "Robot/Exploration.hpp"
#include "Robot/Mining.hpp"
#include "Robot/Zone.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Seed for generating random numbers
    std::srand(std::time(nullptr));

    const int PLANET_SIZE = 5; // Size of the planet grid (e.g., 5x5)
    const int NUM_ROBOTS = 3; // Total number of robots

    // Creation of robots and planet zones
    /* Robots is an array of pointers to ExtraterrestrialRobot. The reason for using pointers
       here is to allow for polymorphism.
       a) Polymorphism: By using pointers to the base class (ExtraterrestrialRobot), you can
       store objects of derived classes (Exploration and Mining) in the same array. This is
       possible because pointers of the base class can point to objects of derived classes,
       and polymorphism allows you to use these pointers to access overridden methods in the derived classes.
       b) Dynamic Memory Allocation: The new keyword is used to dynamically allocate memory for
       objects of the derived classes on the heap. When you create objects using new, they return
       a pointer to the allocated memory. Storing these pointers in an array allows for flexible memory management.
    */
    ExtraterrestrialRobot* robots[NUM_ROBOTS];
    Zone planet[PLANET_SIZE][PLANET_SIZE];

    robots[0] = new Exploration();
    robots[1] = new Mining();
    robots[2] = new Mining();

    // Initialization of planet zones
    for (int i = 0; i < PLANET_SIZE; ++i) {
        for (int j = 0; j < PLANET_SIZE; ++j) {
            planet[i][j].hasMinerals = std::rand() % 2 == 1; // 50% probability of having minerals
            planet[i][j].visitedBy = nullptr; // Initially, no robot has visited the zone
            planet[i][j].mineralVolume = std::rand() % 1000; // Random mineral volume between 0 and 999
        }
    }

    // Each robot visits a random zone on the planet
    for (int i = 0; i < NUM_ROBOTS; ++i) {
        int x = std::rand() % PLANET_SIZE;
        int y = std::rand() % PLANET_SIZE;

        planet[x][y].visitedBy = robots[i];
        std::cout << "Robot " << i << " is ";
        robots[i]->doMission(); // It is used when you're dealing with pointers
        std::cout << "in zone (" << x << ", " << y << ")" << std::endl;
    }

    // Report on planet zones, robots that visited them, and their mineral value
    std::cout << "Planet report:" << std::endl;
    for (int i = 0; i < PLANET_SIZE; ++i) {
        for (int j = 0; j < PLANET_SIZE; ++j) {
            std::cout << "Zone (" << i << ", " << j << "): ";
            if (planet[i][j].visitedBy == nullptr) {
                std::cout << "No robot has visited this zone." << std::endl;
            }
            else {
                std::cout << "Visited by a robot. ";
                std::cout << "Mineral volume: " << planet[i][j].mineralVolume << std::endl;
            }
        }
    }

    // Memory cleanup
    for (int i = 0; i < NUM_ROBOTS; ++i) {
        delete robots[i];
    }

    return 0;
}
