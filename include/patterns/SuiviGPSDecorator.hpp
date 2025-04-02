#ifndef SUIVIGPS_DECORATOR_HPP
#define SUIVIGPS_DECORATOR_HPP

#include "InterventionDecorator.hpp"

class SuiviGPSDecorator : public InterventionDecorator {
public:
    SuiviGPSDecorator(Intervention* base) : InterventionDecorator(base) {}

    std::string getType() const override {
        return intervention->getType() + " + GPS";
    }

    std::string getDetails() const override {
        return intervention->getDetails() + " | Suivi GPS activé.";
    }
};

#endif