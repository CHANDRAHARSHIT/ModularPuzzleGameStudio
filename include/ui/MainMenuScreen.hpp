#ifndef MAIN_MENU_SCREEN_HPP
#define MAIN_MENU_SCREEN_HPP

#include "../core/Screen.hpp"
#include "../core/GameFactory.hpp"
#include "../core/GameManager.hpp"
#include "../util/ScoreBoard.hpp"
#include "../core/ScreenManager.hpp"
#include "../observer/Subject.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * Main menu screen
 */
class MainMenuScreen : public Screen {
private:
    GameFactory& factory;
    GameManager& gameManager;
    ScoreBoard& scoreBoard;
    ScreenManager& screenManager;
    Subject& subject;
    sf::Font font;
    std::vector<std::string> menuItems;
    int selectedIndex;
    struct Particle {
        sf::CircleShape shape;
        sf::Vector2f velocity;
    };
    std::vector<Particle> particles;
    float glowTimer = 0.f;

public:
    /**
     * Constructor
     * @param f Game factory
     * @param gm Game manager
     * @param sb ScoreBoard
     * @param sm Screen manager
     */
    MainMenuScreen(GameFactory& f,
                   GameManager& gm,
                   ScoreBoard& sb,
                   ScreenManager& sm,
                   Subject& subj);
    
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    void selectCurrentItem(sf::RenderWindow& window);
};

#endif // MAIN_MENU_SCREEN_HPP
