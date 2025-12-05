#include "../include/core/GameManager.hpp"
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>

void GameManager::setGame(std::unique_ptr<Game> game) {
    currentGame = std::move(game);
    if (currentGame) {
        currentGame->init();
    }
}

void GameManager::run() {
    if (!currentGame) {
        return;
    }
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1000, 750), currentGame->getName(), sf::Style::Default, settings);
    window.setFramerateLimit(60);
    sf::Clock clock;
    float elapsedSeconds = 0.f;
    ensureHudFontLoaded();
    
    while (window.isOpen() && !currentGame->isOver()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                // Update view to match window size
                sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));
            }
            currentGame->handleEvent(event, window);
        }
        
        float dt = clock.restart().asSeconds();
        elapsedSeconds += dt;
        currentGame->update(dt);
        
        window.clear(sf::Color::White);
        currentGame->render(window);
        drawTimerHud(window, elapsedSeconds);
        window.display();
    }
}

void GameManager::ensureHudFontLoaded() {
    if (hudFontLoaded) {
        return;
    }
    if (hudFont.loadFromFile("assets/fonts/arial.ttf")) {
        hudFontLoaded = true;
        return;
    }
    if (hudFont.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        hudFontLoaded = true;
    }
}

void GameManager::drawTimerHud(sf::RenderWindow& window, float elapsedSeconds) {
    if (!hudFontLoaded) {
        return;
    }

    int totalSeconds = static_cast<int>(elapsedSeconds);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes << ":" << std::setw(2) << seconds;

    const float panelWidth = 180.f;
    const float panelHeight = 50.f;
    sf::View view = window.getView();
    sf::Vector2f viewSize = view.getSize();
    
    sf::RectangleShape panel({panelWidth, panelHeight});
    panel.setPosition(10.f, viewSize.y - panelHeight - 10.f);
    panel.setFillColor(sf::Color(0, 0, 0, 130));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(255, 215, 0));
    window.draw(panel);

    sf::Text label;
    label.setFont(hudFont);
    label.setString("Timer");
    label.setCharacterSize(14);
    label.setFillColor(sf::Color(220, 220, 220));
    label.setPosition(panel.getPosition().x + 8.f, panel.getPosition().y + 4.f);
    window.draw(label);

    sf::Text timerValue;
    timerValue.setFont(hudFont);
    timerValue.setString(oss.str());
    timerValue.setCharacterSize(24);
    timerValue.setFillColor(sf::Color(255, 215, 0));
    timerValue.setPosition(panel.getPosition().x + 35.f, panel.getPosition().y + 20.f);
    window.draw(timerValue);
}
