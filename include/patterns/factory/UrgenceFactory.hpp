#ifndef URGENCE_FACTORY_HPP
#define URGENCE_FACTORY_HPP

#include "InterventionFactory.hpp"
#include "interventions/Urgence.hpp"

class UrgenceFactory : public InterventionFactory {
public:
    Intervention* createIntervention() const override {
        return new Urgence();
    }
};

#endif