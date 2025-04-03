#ifndef MAINTENANCE_FACTORY_HPP
#define MAINTENANCE_FACTORY_HPP

#include "InterventionFactory.hpp"
#include "interventions/Maintenance.hpp"

class MaintenanceFactory : public InterventionFactory {
public:
    Intervention* createIntervention() const override {
        return new Maintenance();
    }
};

#endif