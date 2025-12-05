#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

/**
 * Manages the current game instance and main game loop
 */
class GameManager {
private:
    std::unique_ptr<Game> currentGame;
    sf::Font hudFont;
    bool hudFontLoaded = false;

public:
    GameManager() = default;
    
    /**
     * Set the current game
     * @param game Unique pointer to game instance
     */
    void setGame(std::unique_ptr<Game> game);
    
    /**
     * Run the main game loop
     */
    void run();
    
    /**
     * Get pointer to current game
     * @return Raw pointer to current game (nullptr if none)
     */
    Game* getCurrentGame() const { return currentGame.get(); }

private:
    void ensureHudFontLoaded();
    void drawTimerHud(sf::RenderWindow& window, float elapsedSeconds);
};

#endif // GAME_MANAGER_HPP
