#ifndef CONSOLE_NOTIFIER_HPP
#define CONSOLE_NOTIFIER_HPP

#include "IObserver.hpp"
#include <iostream>

class ConsoleNotifier : public IObserver {
public:
    void update(const std::string& message) override {
        std::cout << "Notification: " << message << std::endl;
    }
};

#endif