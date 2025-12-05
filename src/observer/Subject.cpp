#include "../include/observer/Subject.hpp"
#include <algorithm>

void Subject::addObserver(Observer* obs) {
    if (obs) {
        observers.push_back(obs);
    }
}

void Subject::removeObserver(Observer* obs) {
    observers.erase(
        std::remove(observers.begin(), observers.end(), obs),
        observers.end()
    );
}

void Subject::notifyGameOver(const std::string& gameName, const std::string& result) {
    for (Observer* obs : observers) {
        obs->onGameOver(activePlayerName, gameName, result);
    }
}

void Subject::setActivePlayerName(const std::string& name) {
    if (name.empty()) {
        activePlayerName = "Player";
    } else {
        activePlayerName = name;
    }
}
