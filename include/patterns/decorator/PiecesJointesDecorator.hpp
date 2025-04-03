#ifndef PIECESJOINTES_DECORATOR_HPP
#define PIECESJOINTES_DECORATOR_HPP

#include "InterventionDecorator.hpp"

class PiecesJointesDecorator : public InterventionDecorator {
public:
    PiecesJointesDecorator(Intervention* base) : InterventionDecorator(base) {}

    std::string getType() const override {
        return intervention->getType() + " + PJ";
    }

    std::string getDetails() const override {
        return intervention->getDetails() + " | Pièces jointes ajoutées.";
    }
};

#endif