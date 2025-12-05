#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <string>

/**
 * Abstract Observer interface
 * Part of the Observer design pattern
 */
class Observer {
public:
    virtual ~Observer() = default;
    
    /**
     * Called when a game is over
     * @param gameName Name of the game
     * @param result Result of the game (winner, score, etc.)
     */
    virtual void onGameOver(const std::string& playerName,
                            const std::string& gameName,
                            const std::string& result) = 0;
};

#endif // OBSERVER_HPP
