#include "../include/core/GameFactory.hpp"
#include <stdexcept>

void GameFactory::registerGame(const std::string& name, Creator creator) {
    registry[name] = creator;
}

std::unique_ptr<Game> GameFactory::create(const std::string& name) const {
    auto it = registry.find(name);
    if (it == registry.end()) {
        throw std::runtime_error("Game not found: " + name);
    }
    return it->second();
}

std::vector<std::string> GameFactory::getGameNames() const {
    std::vector<std::string> names;
    for (const auto& pair : registry) {
        names.push_back(pair.first);
    }
    return names;
}
