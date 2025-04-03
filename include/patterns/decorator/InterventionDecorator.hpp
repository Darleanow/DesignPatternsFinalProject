#ifndef INTERVENTION_DECORATOR_HPP
#define INTERVENTION_DECORATOR_HPP

#include "../interventions/Intervention.hpp"

class InterventionDecorator : public Intervention {
protected:
    Intervention* intervention;

public:
    InterventionDecorator(Intervention* base) : intervention(base) {}
    virtual ~InterventionDecorator() { delete intervention; }
};

#endif