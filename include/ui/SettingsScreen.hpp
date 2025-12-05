#ifndef SETTINGS_SCREEN_HPP
#define SETTINGS_SCREEN_HPP

#include "../core/Screen.hpp"
#include "../core/ScreenManager.hpp"

/**
 * Settings screen
 */
class SettingsScreen : public Screen {
private:
    ScreenManager& screenManager;
    sf::Font font;

public:
    /**
     * Constructor
     * @param sm Screen manager
     */
    explicit SettingsScreen(ScreenManager& sm);
    
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};

#endif // SETTINGS_SCREEN_HPP
