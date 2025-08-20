#ifndef ZONE_HPP
#define ZONE_HPP

#include "ExtraterrestrialRobot.hpp"

// Definition of the Zone structure representing a zone on the planet
struct Zone {
    bool hasMinerals;
    ExtraterrestrialRobot* visitedBy; // Pointer to the robot that has visited the zone
    int mineralVolume; // Amount of minerals in the zone
};

#endif
