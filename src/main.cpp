#include "core/GameFactory.hpp"
#include "core/GameManager.hpp"
#include "core/ScreenManager.hpp"
#include "games/TicTacToeGame.hpp"
#include "games/SudokuGame.hpp"
#include "games/Puzzle2048Game.hpp"
#include "util/ScoreBoard.hpp"
#include "observer/Subject.hpp"
#include "ui/SplashScreen.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * Main entry point for the Modular Puzzle Game Studio
 * Demonstrates Factory, Strategy, Observer, and other OOP design patterns
 */
int main() {
    try {
        // Create subject for observer pattern
        Subject gameSubject;
        
        // Create scoreboard and register as observer
        ScoreBoard scoreBoard("scores.txt");
        gameSubject.addObserver(&scoreBoard);
        
        // Create game factory and register games
        GameFactory factory;
        factory.registerGame("Tic-Tac-Toe", [&gameSubject]() {
            return std::make_unique<TicTacToeGame>(&gameSubject);
        });
        factory.registerGame("Sudoku", [&gameSubject]() {
            return std::make_unique<SudokuGame>(&gameSubject);
        });
        factory.registerGame("2048", [&gameSubject]() {
            return std::make_unique<Puzzle2048Game>(&gameSubject);
        });
        
        // Create managers
        GameManager gameManager;
        ScreenManager screenManager;
        
        // Create and set splash screen instead of main menu
        screenManager.setScreen(
            std::make_unique<SplashScreen>(screenManager, factory, gameManager, scoreBoard, gameSubject)
        );
        
        // Main application window with proper scaling
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8; // High quality anti-aliasing
        sf::RenderWindow window(sf::VideoMode(800, 600), "Modular Puzzle Game Studio", sf::Style::Default, settings);
        
        // Center the window on screen
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        window.setPosition(sf::Vector2i((desktop.width - 800) / 2, (desktop.height - 600) / 2));
        
        window.setFramerateLimit(60);
        sf::Clock clock;
        
        // Main loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::Resized) {
                    // Update view to match new window size
                    sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                    window.setView(sf::View(visibleArea));

                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    // Return to splash screen on ESC (which will auto-advance to main menu)
                    screenManager.setScreen(
                        std::make_unique<SplashScreen>(screenManager, factory, gameManager, scoreBoard, gameSubject)
                    );
                } else {
                    screenManager.handleEvent(event, window);
                }
            }
            
            float dt = clock.restart().asSeconds();
            screenManager.update(dt);
            
            window.clear(sf::Color::Black);
            screenManager.render(window);
            window.display();
        }
        
        std::cout << "Thank you for playing!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
