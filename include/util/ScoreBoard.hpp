#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include "../observer/Observer.hpp"
#include <string>
#include <vector>

/**
 * ScoreBoard class that observes game events
 * Stores and manages game scores
 */
class ScoreBoard : public Observer {
public:
    struct ScoreEntry {
        std::string timestamp;
        std::string playerName;
        std::string gameName;
        std::string result;
    };

private:
    std::string filename;

public:
    /**
     * Constructor
     * @param file Path to score file
     */
    explicit ScoreBoard(const std::string& file);
    
    /**
     * Get all scores
     * @return Vector of score entries
     */
    std::vector<ScoreEntry> getEntries() const;
    
    /**
     * Get player statistics
     */
    std::pair<int, std::string> getPlayerStats(const std::string& playerName) const;
    
    /**
     * Get total games played
     */
    int getTotalGamesPlayed() const;
    
    /**
     * Add a structured score entry
     */
    void addEntry(const ScoreEntry& entry);
    
    /**
     * Observer callback for game over event
     * @param gameName Name of the game
     * @param result Result of the game
     */
    void onGameOver(const std::string& playerName,
                    const std::string& gameName,
                    const std::string& result) override;
};

#endif // SCOREBOARD_HPP
