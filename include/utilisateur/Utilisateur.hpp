#ifndef UTILISATEUR_HPP
#define UTILISATEUR_HPP

#include "roles/Role.hpp"
#include <string>

class Utilisateur {
private:
    std::string nom;
    Role role;

public:
    Utilisateur(const std::string& nom, Role role);

    std::string getNom() const;{
        return nom;
    }
    Role getRole() const {
        return role;
    }
};

#endif