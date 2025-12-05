#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <string>

/**
 * Abstract base class for all games
 * Defines the interface that all game implementations must follow
 */
class Game {
public:
    virtual ~Game() = default;
    
    /**
     * Get the name of the game
     * @return Game name as string
     */
    virtual std::string getName() const = 0;
    
    /**
     * Initialize the game state
     */
    virtual void init() = 0;
    
    /**
     * Handle user input events
     * @param event SFML event
     * @param window Reference to render window
     */
    virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
    
    /**
     * Update game logic
     * @param dt Delta time in seconds
     */
    virtual void update(float dt) = 0;
    
    /**
     * Render the game
     * @param window Reference to render window
     */
    virtual void render(sf::RenderWindow& window) = 0;
    
    /**
     * Check if game is over
     * @return true if game is finished
     */
    virtual bool isOver() const = 0;
};

#endif // GAME_HPP
