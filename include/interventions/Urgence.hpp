#ifndef URGENCE_HPP
#define URGENCE_HPP

#include "Intervention.hpp"

class Urgence : public Intervention {
public:
    std::string getType() const override { return "Urgence"; }
    std::string getDetails() const override { return "Intervention d'urgence"; }
};

#endif