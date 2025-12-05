#include "../include/core/ScreenManager.hpp"

void ScreenManager::setScreen(std::unique_ptr<Screen> screen) {
    currentScreen = std::move(screen);
}

void ScreenManager::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (currentScreen) {
        currentScreen->handleEvent(event, window);
    }
}

void ScreenManager::update(float dt) {
    if (currentScreen) {
        currentScreen->update(dt);
    }
}

void ScreenManager::render(sf::RenderWindow& window) {
    if (currentScreen) {
        currentScreen->render(window);
    }
}
