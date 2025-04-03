#include <iostream>

// Factory
#include "patterns/factory/MaintenanceFactory.hpp"
#include "patterns/factory/UrgenceFactory.hpp"

// Decorators
#include "patterns/decorator/SuiviGPSDecorator.hpp"
#include "patterns/decorator/PiecesJointesDecorator.hpp"

// Façade
#include "patterns/GestionnaireInterventions.hpp"

//Observeur
#include "patterns/observer/ConsoleNotifier.hpp"

//Proxy
#include "utilisateur/Utilisateur.hpp"
#include "patterns/GestionnaireProxy.hpp"

int main() {
    std::cout << "=== Bienvenue dans le système de planification d'interventions ===\n" << std::endl;

    MaintenanceFactory maintenanceFactory;
    UrgenceFactory urgenceFactory;

    GestionnaireInterventions gestionnaire;
    ConsoleNotifier console;
    gestionnaire.addObserver(&console);

        Utilisateur admin("Jory", Role::ECRITURE);
    Utilisateur lecteur("Michel", Role::LECTURE);

    GestionnaireProxy proxyAdmin(gestionnaire, admin);
    GestionnaireProxy proxyLecteur(gestionnaire, lecteur);

    proxyAdmin.createIntervention(&maintenanceFactory);
    proxyAdmin.createIntervention(&urgenceFactory);

    proxyLecteur.createIntervention(&maintenanceFactory); // doit afficher accès refusé

    proxyAdmin.afficherInterventions();
    proxyLecteur.afficherInterventions(); // OK

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