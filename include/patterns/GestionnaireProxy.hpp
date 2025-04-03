#ifndef GESTIONNAIRE_PROXY_HPP
#define GESTIONNAIRE_PROXY_HPP

#include "GestionnaireInterventions.hpp"
#include "utilisateur/Utilisateur.hpp"

class GestionnaireProxy {
private:
    GestionnaireInterventions& gestionnaire;
    Utilisateur& utilisateur;

public:
    GestionnaireProxy(GestionnaireInterventions& gest, Utilisateur& user)
        : gestionnaire(gest), utilisateur(user) {}

    Intervention* createIntervention(InterventionFactory* factory) {
        if (utilisateur.getRole() == Role::ECRITURE) {
            return gestionnaire.createIntervention(factory);
        } else {
            std::cout << "⛔ Denied access " << utilisateur.getNom()
                      << " : reader only" << std::endl;
            return nullptr;
        }
    }

    void afficherInterventions() const {
        if (utilisateur.getRole() == Role::LECTURE || utilisateur.getRole() == Role::ECRITURE) {
            gestionnaire.afficherInterventions();
        } else {
            std::cout << "⛔ Denied access" << std::endl;
        }
    }
};

#endif