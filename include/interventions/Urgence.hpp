#ifndef URGENCE_HPP
#define URGENCE_HPP

#include "Intervention.hpp"

class Urgence : public Intervention {
public:
    std::string getType() const override { return "Emergency"; }
    std::string getDetails() const override { return "Emergency repair"; }
};

#endif