#ifndef GESTIONNAIRE_INTERVENTIONS_HPP
#define GESTIONNAIRE_INTERVENTIONS_HPP

#include "../interventions/Intervention.hpp"
#include "factory/InterventionFactory.hpp"
#include "decorator/SuiviGPSDecorator.hpp"
#include "decorator/PiecesJointesDecorator.hpp"
#include "observer/Observable.hpp"
#include <memory>
#include <vector>

class GestionnaireInterventions: public Observable {
private:
    std::vector<std::unique_ptr<Intervention>> interventions;

public:
    // Crée une intervention de base via une factory
    Intervention* creerIntervention(InterventionFactory* factory) {
        Intervention* intervention = factory->createIntervention();
        interventions.emplace_back(intervention); // stockée pour gestion mémoire
        notifyObservers("Nouvelle intervention créée : " + intervention->getType());
        return intervention;
    }

    // Ajoute un suivi GPS à une intervention
    Intervention* ajouterGPS(Intervention* intervention) {
        Intervention* decorated = new SuiviGPSDecorator(intervention);
        interventions.emplace_back(decorated);
        notifyObservers("Ajout du suivi GPS à l'intervention.");
        return decorated;
    }

    // Ajoute des pièces jointes
    Intervention* ajouterPJ(Intervention* intervention) {
        Intervention* decorated = new PiecesJointesDecorator(intervention);
        interventions.emplace_back(decorated);
        notifyObservers("Ajout de pièces jointes à l'intervention.");
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