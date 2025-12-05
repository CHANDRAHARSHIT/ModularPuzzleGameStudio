#ifndef SCOREBOARD_SCREEN_HPP
#define SCOREBOARD_SCREEN_HPP

#include "../core/Screen.hpp"
#include "../util/ScoreBoard.hpp"
#include "../core/ScreenManager.hpp"

/**
 * ScoreBoard display screen
 */
class ScoreBoardScreen : public Screen {
private:
    ScoreBoard& scoreBoard;
    ScreenManager& screenManager;
    sf::Font font;
    float animationTime = 0.f;

public:
    /**
     * Constructor
     * @param sb ScoreBoard reference
     * @param sm Screen manager
     */
    ScoreBoardScreen(ScoreBoard& sb, ScreenManager& sm);
    
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};

#endif // SCOREBOARD_SCREEN_HPP
