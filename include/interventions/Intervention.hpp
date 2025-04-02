#ifndef INTERVENTION_HPP
#define INTERVENTION_HPP

#include <string>

class Intervention {
    public:
        virtual ~Intervention() = default;
        virtual std::string getType() const = 0;
        virtual std::string getDetails() const = 0;
};

#endif