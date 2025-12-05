#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>

/**
 * Abstract base class for all screens/UI states
 */
class Screen {
public:
    virtual ~Screen() = default;
    
    /**
     * Handle user input events
     * @param event SFML event
     * @param window Reference to render window
     */
    virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
    
    /**
     * Update screen logic
     * @param dt Delta time in seconds
     */
    virtual void update(float dt) = 0;
    
    /**
     * Render the screen
     * @param window Reference to render window
     */
    virtual void render(sf::RenderWindow& window) = 0;
};

#endif // SCREEN_HPP
