#ifndef EXTRATERRESTRIALROBOT_HPP
#define EXTRATERRESTRIALROBOT_HPP

// Definition of the base class ExtraterrestrialRobot
class ExtraterrestrialRobot {
public:
    virtual ~ExtraterrestrialRobot() {} // Virtual destructor
    virtual void doMission() {} // Pure virtual method
};

#endif