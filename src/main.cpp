#include <iostream>

// Factory
#include "../include/patterns/MaintenanceFactory.hpp"
#include "../include/patterns/UrgenceFactory.hpp"

// Decorators
#include "../include/patterns/SuiviGPSDecorator.hpp"
#include "../include/patterns/PiecesJointesDecorator.hpp"

// Façade
#include "../include/patterns/GestionnaireInterventions.hpp"

int main() {
    std::cout << "=== Bienvenue dans le système de planification d'interventions ===\n" << std::endl;

    MaintenanceFactory maintenanceFactory;
    UrgenceFactory urgenceFactory;

    Intervention* intervention1 = maintenanceFactory.createIntervention();
    Intervention* intervention2 = urgenceFactory.createIntervention();

    std::cout << "[Factory] Intervention 1 : " << intervention1->getType() 
              << " - " << intervention1->getDetails() << std::endl;

    std::cout << "[Factory] Intervention 2 : " << intervention2->getType() 
              << " - " << intervention2->getDetails() << std::endl;

    Intervention* intervention3 = new SuiviGPSDecorator(new Maintenance());
    Intervention* intervention4 = new PiecesJointesDecorator(new Urgence());
    Intervention* intervention5 = new PiecesJointesDecorator(new SuiviGPSDecorator(new Maintenance()));

    std::cout << "\n[Decorator] Intervention 3 : " << intervention3->getType() 
              << " - " << intervention3->getDetails() << std::endl;

    std::cout << "[Decorator] Intervention 4 : " << intervention4->getType() 
              << " - " << intervention4->getDetails() << std::endl;

    std::cout << "[Decorator] Intervention 5 : " << intervention5->getType() 
              << " - " << intervention5->getDetails() << std::endl;

    // Nettoyage mémoire
    delete intervention1;
    delete intervention2;
    delete intervention3;
    delete intervention4;
    delete intervention5;

    return 0;
}