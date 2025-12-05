#ifndef NAME_ENTRY_SCREEN_HPP
#define NAME_ENTRY_SCREEN_HPP

#include "../core/Screen.hpp"
#include "../core/GameFactory.hpp"
#include "../core/GameManager.hpp"
#include "../core/ScreenManager.hpp"
#include "../util/ScoreBoard.hpp"
#include "../observer/Subject.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class NameEntryScreen : public Screen {
private:
    GameFactory& factory;
    GameManager& gameManager;
    ScoreBoard& scoreBoard;
    ScreenManager& screenManager;
    Subject& subject;
    std::string gameName;
    sf::Font font;
    std::string playerName;
    float caretTimer = 0.f;
    bool caretVisible = true;

public:
    NameEntryScreen(GameFactory& f,
                    GameManager& gm,
                    ScoreBoard& sb,
                    ScreenManager& sm,
                    Subject& subj,
                    std::string targetGame);

    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    void launchGameAndReturn();
};

#endif // NAME_ENTRY_SCREEN_HPP
