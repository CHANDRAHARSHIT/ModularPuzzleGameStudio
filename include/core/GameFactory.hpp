#ifndef GAME_FACTORY_HPP
#define GAME_FACTORY_HPP

#include "Game.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

/**
 * Factory class for creating game instances
 * Implements the Factory design pattern
 */
class GameFactory {
public:
    using Creator = std::function<std::unique_ptr<Game>()>;

private:
    std::unordered_map<std::string, Creator> registry;

public:
    /**
     * Register a game creator function
     * @param name Game name
     * @param creator Function that creates game instance
     */
    void registerGame(const std::string& name, Creator creator);
    
    /**
     * Create a game instance by name
     * @param name Game name
     * @return Unique pointer to game instance
     */
    std::unique_ptr<Game> create(const std::string& name) const;
    
    /**
     * Get list of all registered game names
     * @return Vector of game names
     */
    std::vector<std::string> getGameNames() const;
};

#endif // GAME_FACTORY_HPP
