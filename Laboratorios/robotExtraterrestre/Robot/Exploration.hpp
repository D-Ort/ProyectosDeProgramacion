#ifndef EXPLORATION_HPP
#define EXPLORATION_HPP

#include "ExtraterrestrialRobot.hpp"

// Definition of the Exploration class, which inherits from ExtraterrestrialRobot
class Exploration : public ExtraterrestrialRobot {
public:
    // It is not needed to use override but it is a good practice
    void doMission() override;
};

#endif