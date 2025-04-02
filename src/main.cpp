#include <iostream>
#include "../include/patterns/MaintenanceFactory.hpp"
#include "../include/patterns/UrgenceFactory.hpp"

int main() {
    std::cout << "--- Planification d'interventions ---" << std::endl;

    MaintenanceFactory maintenanceFactory;
    UrgenceFactory urgenceFactory;

    Intervention* intervention1 = maintenanceFactory.createIntervention();
    Intervention* intervention2 = urgenceFactory.createIntervention();

    std::cout << "Intervention 1: " << intervention1->getType() << " - " << intervention1->getDetails() << std::endl;
    std::cout << "Intervention 2: " << intervention2->getType() << " - " << intervention2->getDetails() << std::endl;

    delete intervention1;
    delete intervention2;

    return 0;
}