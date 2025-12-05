#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include "Screen.hpp"
#include <memory>

/**
 * Manages screen transitions and current active screen
 */
class ScreenManager {
private:
    std::unique_ptr<Screen> currentScreen;

public:
    ScreenManager() = default;
    
    /**
     * Set the current screen
     * @param screen Unique pointer to screen instance
     */
    void setScreen(std::unique_ptr<Screen> screen);
    
    /**
     * Handle events for current screen
     * @param event SFML event
     * @param window Reference to render window
     */
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    
    /**
     * Update current screen
     * @param dt Delta time in seconds
     */
    void update(float dt);
    
    /**
     * Render current screen
     * @param window Reference to render window
     */
    void render(sf::RenderWindow& window);
    
    /**
     * Check if a screen is currently set
     * @return true if screen exists
     */
    bool hasScreen() const { return currentScreen != nullptr; }
};

#endif // SCREEN_MANAGER_HPP
