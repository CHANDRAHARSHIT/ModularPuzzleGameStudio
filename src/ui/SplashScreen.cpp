#include "../include/ui/SplashScreen.hpp"
#include "../include/ui/MainMenuScreen.hpp"
#include <memory>
#include <cmath>

SplashScreen::SplashScreen(ScreenManager& sm, 
                          GameFactory& f, 
                          GameManager& gm, 
                          ScoreBoard& sb, 
                          Subject& subj)
    : screenManager(sm), factory(f), gameManager(gm), scoreBoard(sb), subject(subj) {
    
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }
    
    // Try to load the Mindix logo
    if (logoTexture.loadFromFile("Mindix.png")) {
        logoLoaded = true;
        logoSprite.setTexture(logoTexture);
        
        // Center the logo
        sf::Vector2u logoSize = logoTexture.getSize();
        logoSprite.setPosition(
            (800.f - logoSize.x) * 0.5f,
            (600.f - logoSize.y) * 0.5f - 80.f
        );
        
        // Scale if too large
        if (logoSize.x > 400 || logoSize.y > 300) {
            float scaleX = 400.f / logoSize.x;
            float scaleY = 300.f / logoSize.y;
            float scale = std::min(scaleX, scaleY);
            logoSprite.setScale(scale, scale);
            
            // Recenter after scaling
            sf::FloatRect bounds = logoSprite.getLocalBounds();
            logoSprite.setPosition(
                (800.f - bounds.width * scale) * 0.5f,
                (600.f - bounds.height * scale) * 0.5f - 80.f
            );
        }
    }
}

void SplashScreen::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    // Skip splash on any key/mouse press
    if (event.type == sf::Event::KeyPressed || 
        event.type == sf::Event::MouseButtonPressed) {
        screenManager.setScreen(std::make_unique<MainMenuScreen>(
            factory, gameManager, scoreBoard, screenManager, subject));
    }
}

void SplashScreen::update(float dt) {
    timer += dt;
    
    // Fade in effect
    if (timer < 1.5f) {
        fadeAlpha = (timer / 1.5f) * 255.f;
    } else if (timer < 3.5f) {
        fadeAlpha = 255.f;
    } else if (timer < 5.0f) {
        fadeAlpha = (1.0f - (timer - 3.5f) / 1.5f) * 255.f;
    } else {
        // Auto-transition to main menu after 5 seconds
        screenManager.setScreen(std::make_unique<MainMenuScreen>(
            factory, gameManager, scoreBoard, screenManager, subject));
        return;
    }
    
    fadeAlpha = std::max(0.f, std::min(255.f, fadeAlpha));
}

void SplashScreen::render(sf::RenderWindow& window) {
    // Dark gradient background
    sf::VertexArray gradient(sf::Quads, 4);
    gradient[0].position = {0.f, 0.f};
    gradient[1].position = {800.f, 0.f};
    gradient[2].position = {800.f, 600.f};
    gradient[3].position = {0.f, 600.f};
    sf::Color topColor(10, 15, 30, 255);
    sf::Color bottomColor(25, 35, 60, 255);
    gradient[0].color = topColor;
    gradient[1].color = topColor;
    gradient[2].color = bottomColor;
    gradient[3].color = bottomColor;
    window.draw(gradient);
    
    // Draw logo if loaded
    if (logoLoaded) {
        sf::Color logoColor = sf::Color::White;
        logoColor.a = static_cast<sf::Uint8>(fadeAlpha);
        logoSprite.setColor(logoColor);
        window.draw(logoSprite);
    }
    
    // "Developed by" text
    sf::Text developedBy;
    developedBy.setFont(font);
    developedBy.setString("Developed by");
    developedBy.setCharacterSize(28);
    sf::Color devColor(180, 180, 200);
    devColor.a = static_cast<sf::Uint8>(fadeAlpha);
    developedBy.setFillColor(devColor);
    developedBy.setPosition(300.f, logoLoaded ? 420.f : 250.f);
    window.draw(developedBy);
    
    // "MINDIX" text with glow effect
    sf::Text mindix;
    mindix.setFont(font);
    mindix.setString("MINDIX");
    mindix.setCharacterSize(48);
    mindix.setStyle(sf::Text::Bold);
    
    float glow = 0.3f + 0.7f * (std::sin(timer * 2.0f) + 1.0f) * 0.5f;
    sf::Color mindixColor(100 + 155 * glow, 150 + 105 * glow, 255);
    mindixColor.a = static_cast<sf::Uint8>(fadeAlpha);
    mindix.setFillColor(mindixColor);
    mindix.setPosition(320.f, logoLoaded ? 460.f : 290.f);
    window.draw(mindix);
    
    // Puzzle Game Studio subtitle
    sf::Text subtitle;
    subtitle.setFont(font);
    subtitle.setString("Puzzle Game Studio");
    subtitle.setCharacterSize(20);
    sf::Color subColor(150, 150, 180);
    subColor.a = static_cast<sf::Uint8>(fadeAlpha * 0.8f);
    subtitle.setFillColor(subColor);
    subtitle.setPosition(315.f, logoLoaded ? 520.f : 350.f);
    window.draw(subtitle);
    
    // Skip instruction (fade in after 2 seconds)
    if (timer > 2.0f) {
        sf::Text skipText;
        skipText.setFont(font);
        skipText.setString("Press any key to continue...");
        skipText.setCharacterSize(16);
        sf::Color skipColor(120, 120, 140);
        skipColor.a = static_cast<sf::Uint8>((fadeAlpha * 0.6f) * std::sin((timer - 2.0f) * 3.0f));
        skipText.setFillColor(skipColor);
        skipText.setPosition(310.f, 560.f);
        window.draw(skipText);
    }
}