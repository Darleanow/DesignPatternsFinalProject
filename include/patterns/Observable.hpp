#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include "IObserver.hpp"
#include <vector>

class Observable {
protected:
std::vector<IObserver*> observers;

public:
void addObserver(IObserver* observer) {
    observers.push_back(observer);
}

void notifyObservers(const std::string& message) {
    for (IObserver* observer : observers) {
        observer->update(message);
    }
}
};

#endif