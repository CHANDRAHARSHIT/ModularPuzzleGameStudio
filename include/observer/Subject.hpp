#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include "Observer.hpp"
#include <vector>
#include <string>

/**
 * Subject class for Observer pattern
 * Manages observers and notifies them of events
 */
class Subject {
private:
    std::vector<Observer*> observers;
    std::string activePlayerName = "Player";

public:
    /**
     * Add an observer
     * @param obs Pointer to observer
     */
    void addObserver(Observer* obs);
    
    /**
     * Remove an observer
     * @param obs Pointer to observer
     */
    void removeObserver(Observer* obs);
    
    /**
     * Notify all observers that a game is over
     * @param gameName Name of the game
     * @param result Result of the game
     */
    void notifyGameOver(const std::string& gameName, const std::string& result);

    /**
     * Set the active player's name for upcoming score notifications
     */
    void setActivePlayerName(const std::string& name);

    /**
     * Get the currently active player's name
     */
    const std::string& getActivePlayerName() const { return activePlayerName; }
};

#endif // SUBJECT_HPP
