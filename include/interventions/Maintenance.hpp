#ifndef MAINTENANCE_HPP
#define MAINTENANCE_HPP

#include "Intervention.hpp"

class Maintenance : public Intervention {
public:
    std::string getType() const override { return "Maintenance"; }
    std::string getDetails() const override { return "Device Maintenance"; }
};

#endif