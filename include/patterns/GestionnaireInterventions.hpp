#ifndef GESTIONNAIRE_INTERVENTIONS_HPP
#define GESTIONNAIRE_INTERVENTIONS_HPP

#include "../interventions/Intervention.hpp"
#include "InterventionFactory.hpp"
#include "SuiviGPSDecorator.hpp"
#include "PiecesJointesDecorator.hpp"
#include <memory>
#include <vector>

class GestionnaireInterventions {
private:
    std::vector<std::unique_ptr<Intervention>> interventions;

public:
    // Crée une intervention de base via une factory
    Intervention* creerIntervention(InterventionFactory* factory) {
        Intervention* intervention = factory->createIntervention();
        interventions.emplace_back(intervention); // stockée pour gestion mémoire
        return intervention;
    }

    // Ajoute un suivi GPS à une intervention
    Intervention* ajouterGPS(Intervention* intervention) {
        Intervention* decorated = new SuiviGPSDecorator(intervention);
        interventions.emplace_back(decorated);
        return decorated;
    }

    // Ajoute des pièces jointes
    Intervention* ajouterPJ(Intervention* intervention) {
        Intervention* decorated = new PiecesJointesDecorator(intervention);
        interventions.emplace_back(decorated);
        return decorated;
    }

    // Affiche toutes les interventions
    void afficherInterventions() const {
        std::cout << "\n=== Liste des interventions ===" << std::endl;
        for (const auto& i : interventions) {
            std::cout << "- " << i->getType() << " | " << i->getDetails() << std::endl;
        }
    }
};

#endif