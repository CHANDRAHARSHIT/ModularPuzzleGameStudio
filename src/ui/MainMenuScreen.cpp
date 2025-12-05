#include "../include/ui/MainMenuScreen.hpp"
#include "../include/ui/ScoreBoardScreen.hpp"
#include "../include/ui/SettingsScreen.hpp"
#include "../include/ui/NameEntryScreen.hpp"
#include <memory>
#include <random>
#include <cmath>

MainMenuScreen::MainMenuScreen(GameFactory& f,
                               GameManager& gm,
                               ScoreBoard& sb,
                               ScreenManager& sm,
                               Subject& subj)
    : factory(f), gameManager(gm), scoreBoard(sb), screenManager(sm), subject(subj), selectedIndex(0) {
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }
    
    // Enable smooth font rendering
    const_cast<sf::Texture&>(font.getTexture(30)).setSmooth(true);
    
    menuItems = factory.getGameNames();
    menuItems.push_back("View Scores");
    menuItems.push_back("Settings");
    menuItems.push_back("Exit");
    
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> posX(0.f, 800.f);
    std::uniform_real_distribution<float> posY(0.f, 600.f);
    std::uniform_real_distribution<float> radius(2.f, 6.f);
    std::uniform_real_distribution<float> velocity(-25.f, 25.f);
    std::uniform_int_distribution<int> colorComp(100, 255);
    
    particles.reserve(40);
    for (int i = 0; i < 40; ++i) {
        Particle p;
        float r = radius(rng);
        p.shape.setRadius(r);
        p.shape.setFillColor(sf::Color(colorComp(rng), colorComp(rng), 255));
        p.shape.setPosition(posX(rng), posY(rng));
        sf::Vector2f vel{velocity(rng), velocity(rng)};
        if (std::abs(vel.x) < 5.f) vel.x = (vel.x < 0 ? -1.f : 1.f) * 5.f;
        if (std::abs(vel.y) < 5.f) vel.y = (vel.y < 0 ? -1.f : 1.f) * 5.f;
        p.velocity = vel;
        particles.push_back(p);
    }
}

void MainMenuScreen::selectCurrentItem(sf::RenderWindow& window) {
    if (selectedIndex < static_cast<int>(factory.getGameNames().size())) {
        const std::string gameToLaunch = menuItems[selectedIndex];
        screenManager.setScreen(std::make_unique<NameEntryScreen>(
            factory, gameManager, scoreBoard, screenManager, subject, gameToLaunch));
    } else if (menuItems[selectedIndex] == "View Scores") {
        screenManager.setScreen(std::make_unique<ScoreBoardScreen>(scoreBoard, screenManager));
    } else if (menuItems[selectedIndex] == "Settings") {
        screenManager.setScreen(std::make_unique<SettingsScreen>(screenManager));
    } else if (menuItems[selectedIndex] == "Exit") {
        window.close();
    }
}

void MainMenuScreen::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedIndex = (selectedIndex - 1 + menuItems.size()) % menuItems.size();
        } else if (event.key.code == sf::Keyboard::Down) {
            selectedIndex = (selectedIndex + 1) % menuItems.size();
        } else if (event.key.code == sf::Keyboard::Return) {
            selectCurrentItem(window);
        }
    } else if (event.type == sf::Event::MouseMoved ||
               (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
        // Use mapped coordinates to respect current view scaling
        sf::Vector2i mousePixels = sf::Mouse::getPosition(window);
        sf::Vector2f mouse = window.mapPixelToCoords(mousePixels);

        float yPos = 160.f;
        int hovered = -1;
        for (size_t i = 0; i < menuItems.size(); ++i) {
            sf::FloatRect bounds(220.f, yPos, 380.f, 55.f);
            // Expand hitbox slightly for easier interaction
            bounds.left -= 8.f; bounds.top -= 6.f; bounds.width += 16.f; bounds.height += 12.f;
            if (bounds.contains(mouse)) {
                hovered = static_cast<int>(i);
                break;
            }
            yPos += 55.f;
        }

        if (hovered != -1) {
            selectedIndex = hovered;
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && hovered != -1) {
            selectCurrentItem(window);
        }
    }
}

void MainMenuScreen::update(float dt) {
    glowTimer += dt;
    for (auto& particle : particles) {
        auto pos = particle.shape.getPosition();
        pos += particle.velocity * dt;
        if (pos.x < -10.f) pos.x = 810.f;
        if (pos.x > 810.f) pos.x = -10.f;
        if (pos.y < -10.f) pos.y = 610.f;
        if (pos.y > 610.f) pos.y = -10.f;
        particle.shape.setPosition(pos);
    }
}

void MainMenuScreen::render(sf::RenderWindow& window) {
    // Draw gradient background
    sf::RectangleShape bgTop(sf::Vector2f(900, 300));
    bgTop.setPosition(0, 0);
    bgTop.setFillColor(sf::Color(15, 15, 45));
    window.draw(bgTop);
    
    sf::RectangleShape bgBottom(sf::Vector2f(900, 300));
    bgBottom.setPosition(0, 300);
    bgBottom.setFillColor(sf::Color(25, 15, 55));
    window.draw(bgBottom);
    
    // Draw animated particles
    for (const auto& particle : particles) {
        window.draw(particle.shape);
    }
    
    // Title with enhanced glow effect
    const float pulse = (std::sin(glowTimer * 2.f) + 1.f) * 0.5f;
    
    // Outer glow
    sf::Text titleGlow;
    titleGlow.setFont(font);
    titleGlow.setString("Modular Puzzle Game Studio");
    titleGlow.setCharacterSize(44);
    titleGlow.setFillColor(sf::Color(150, 100, 255, 100 * pulse));
    titleGlow.setPosition(68, 38);
    titleGlow.setStyle(sf::Text::Bold);
    window.draw(titleGlow);
    
    // Main title
    sf::Text title;
    title.setFont(font);
    title.setString("Modular Puzzle Game Studio");
    title.setCharacterSize(44);
    title.setFillColor(sf::Color(200, static_cast<sf::Uint8>(120 + 135 * pulse), 255));
    title.setPosition(70, 40);
    title.setStyle(sf::Text::Bold);
    window.draw(title);
    
    sf::Text subtitle;
    subtitle.setFont(font);
    subtitle.setString("Press Enter on a game, then type your legend name to record scores!");
    subtitle.setCharacterSize(18);
    subtitle.setFillColor(sf::Color(220, 220, 240));
    subtitle.setPosition(70, 95);
    window.draw(subtitle);
    
    // Show total games played with background
    sf::RectangleShape statsBg(sf::Vector2f(240, 40));
    statsBg.setPosition(610.f, 35.f);
    statsBg.setFillColor(sf::Color(80, 60, 120, 150));
    window.draw(statsBg);
    
    sf::Text statsText;
    statsText.setFont(font);
    statsText.setString("Games Played: " + std::to_string(scoreBoard.getTotalGamesPlayed()));
    statsText.setCharacterSize(18);
    statsText.setFillColor(sf::Color(200, 200, 255));
    statsText.setStyle(sf::Text::Bold);
    statsText.setPosition(620.f, 43.f);
    window.draw(statsText);
    
    float yPos = 160.f;
    for (size_t i = 0; i < menuItems.size(); ++i) {
        bool isSelected = i == static_cast<size_t>(selectedIndex);
        
        // Draw menu item background
        sf::RectangleShape itemBg(sf::Vector2f(380, 48));
        itemBg.setPosition(215, yPos - 4);
        
        if (isSelected) {
            float selectPulse = 0.7f + 0.3f * std::sin(glowTimer * 5.f);
            itemBg.setFillColor(sf::Color(100, 80, 180, 180 * selectPulse));
            itemBg.setOutlineThickness(2);
            itemBg.setOutlineColor(sf::Color(150, 120, 255, 200));
        } else {
            itemBg.setFillColor(sf::Color(40, 35, 70, 100));
            itemBg.setOutlineThickness(1);
            itemBg.setOutlineColor(sf::Color(80, 70, 120, 150));
        }
        window.draw(itemBg);
        
        // Draw shadow
        sf::Text itemShadow;
        itemShadow.setFont(font);
        itemShadow.setString(menuItems[i]);
        itemShadow.setCharacterSize(32);
        itemShadow.setFillColor(sf::Color(0, 0, 0, 80));
        itemShadow.setPosition(222, yPos + 2);
        if (isSelected) itemShadow.setStyle(sf::Text::Bold);
        window.draw(itemShadow);
        
        // Draw menu item text
        sf::Text item;
        item.setFont(font);
        item.setString(menuItems[i]);
        item.setCharacterSize(32);
        item.setFillColor(isSelected ? sf::Color(255, 230, 100) : sf::Color(220, 220, 240));
        item.setPosition(220, yPos);
        item.setStyle(isSelected ? sf::Text::Bold : sf::Text::Regular);
        window.draw(item);
        
        // Selection indicator
        if (isSelected) {
            sf::RectangleShape indicator(sf::Vector2f(8, 40));
            indicator.setPosition(200, yPos);
            indicator.setFillColor(sf::Color(255, 230, 100));
            window.draw(indicator);
        }
        
        yPos += 55.f;
    }
    
    // Instructions with background
    sf::RectangleShape instrBg(sf::Vector2f(850, 35));
    instrBg.setPosition(25, 545);
    instrBg.setFillColor(sf::Color(30, 25, 50, 180));
    window.draw(instrBg);
    
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Use Arrow Keys to navigate | Enter to select | ESC returns here from anywhere | Hover & Click supported in games!");
    instructions.setCharacterSize(16);
    instructions.setFillColor(sf::Color(200, 200, 240));
    instructions.setPosition(50, 552);
    window.draw(instructions);
}
