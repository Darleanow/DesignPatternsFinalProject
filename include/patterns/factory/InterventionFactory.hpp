#ifndef INTERVENTION_FACTORY_HPP
#define INTERVENTION_FACTORY_HPP

#include "interventions/Intervention.hpp"

class InterventionFactory {
public:
    virtual ~InterventionFactory() = default;
    virtual Intervention* createIntervention() const = 0;
};

#endif