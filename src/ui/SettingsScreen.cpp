#include "../include/ui/SettingsScreen.hpp"
#include <cmath>

SettingsScreen::SettingsScreen(ScreenManager& sm)
    : screenManager(sm) {
    
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }
}

void SettingsScreen::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::BackSpace) {
            // Return to main menu
            window.close();
        }
    }
}

void SettingsScreen::update(float dt) {
    // No update needed
}

void SettingsScreen::render(sf::RenderWindow& window) {
    window.clear(sf::Color(15, 25, 45));
    
    // Animated background
    static float bgTimer = 0;
    bgTimer += 0.01f;
    for (int i = 0; i < 20; ++i) {
        sf::CircleShape star(2 + std::sin(bgTimer + i) * 1);
        star.setFillColor(sf::Color(255, 255, 255, 100 + 50 * std::sin(bgTimer * 2 + i)));
        star.setPosition(50 + i * 35, 100 + 50 * std::sin(bgTimer + i * 0.5f));
        window.draw(star);
    }
    
    // Title
    sf::Text title;
    title.setFont(font);
    title.setString("Game Studio Settings");
    title.setCharacterSize(42);
    title.setFillColor(sf::Color(100, 200, 255));
    title.setPosition(150, 50);
    window.draw(title);
    
    // Features showcase
    sf::Text features;
    features.setFont(font);
    features.setString("Enhanced Gaming Experience\n\n"
                      "- Mouse & Touchpad Support: Click & drag in all games\n"
                      "- Visual Effects: Hover highlights & animations\n" 
                      "- Session Timer: Track your playing time\n"
                      "- Hall of Legends: Compete for top rankings\n"
                      "- Player Statistics: View your achievements\n"
                      "- Smart UI: Responsive design & feedback\n"
                      "- Multiple Controls: Keyboard, mouse, gestures\n\n"
                      "More features coming soon:\n"
                      "  * Sound Effects & Music\n"
                      "  * Difficulty Levels\n" 
                      "  * Custom Themes\n"
                      "  * Online Leaderboards");
    features.setCharacterSize(18);
    features.setFillColor(sf::Color::White);
    features.setPosition(80, 140);
    window.draw(features);
    
    // Instructions
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("All games now support both keyboard AND mouse controls!\n"
                          "Press ESC or Backspace to return to main menu");
    instructions.setCharacterSize(20);
    instructions.setFillColor(sf::Color(255, 215, 0));
    instructions.setPosition(120, 500);
    window.draw(instructions);
}
