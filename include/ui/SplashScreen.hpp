#ifndef SPLASH_SCREEN_HPP
#define SPLASH_SCREEN_HPP

#include "../core/Screen.hpp"
#include "../core/ScreenManager.hpp"
#include "../core/GameFactory.hpp"
#include "../core/GameManager.hpp"
#include "../util/ScoreBoard.hpp"
#include "../observer/Subject.hpp"
#include <SFML/Graphics.hpp>

class SplashScreen : public Screen {
private:
    ScreenManager& screenManager;
    GameFactory& factory;
    GameManager& gameManager;
    ScoreBoard& scoreBoard;
    Subject& subject;
    sf::Font font;
    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    float timer = 0.f;
    float fadeAlpha = 0.f;
    bool logoLoaded = false;

public:
    SplashScreen(ScreenManager& sm, 
                GameFactory& f, 
                GameManager& gm, 
                ScoreBoard& sb, 
                Subject& subj);
    
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};

#endif // SPLASH_SCREEN_HPP