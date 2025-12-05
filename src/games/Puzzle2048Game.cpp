#include "../include/games/Puzzle2048Game.hpp"
#include <random>
#include <sstream>
#include <iomanip>
#include <cmath>

Puzzle2048Game::Puzzle2048Game(Subject* subj)
    : board(4, 4, 0), gameOver(false), won(false), subject(subj), score(0) {}

std::string Puzzle2048Game::getName() const {
    return "2048 Puzzle";
}

void Puzzle2048Game::init() {
    board.reset(0);
    gameOver = false;
    won = false;
    score = 0;
    gameOverTimer = 0.f;
    celebrationTimer = 0.f;
    
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }
    
    // Enable smooth font rendering
    const_cast<sf::Texture&>(font.getTexture(40)).setSmooth(true);
    
    spawnTile();
    spawnTile();
}

void Puzzle2048Game::spawnTile() {
    std::vector<std::pair<size_t, size_t>> emptyCells;
    
    for (size_t r = 0; r < 4; ++r) {
        for (size_t c = 0; c < 4; ++c) {
            if (board.at(r, c) == 0) {
                emptyCells.push_back({r, c});
            }
        }
    }
    
    if (!emptyCells.empty()) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> posDis(0, emptyCells.size() - 1);
        std::uniform_int_distribution<> valDis(1, 10);
        
        auto [r, c] = emptyCells[posDis(gen)];
        board.at(r, c) = (valDis(gen) == 10) ? 4 : 2;
    }
}

bool Puzzle2048Game::moveLeft() {
    bool moved = false;
    
    for (size_t r = 0; r < 4; ++r) {
        // Compress
        int writePos = 0;
        for (size_t c = 0; c < 4; ++c) {
            if (board.at(r, c) != 0) {
                if (writePos != c) {
                    board.at(r, writePos) = board.at(r, c);
                    board.at(r, c) = 0;
                    moved = true;
                }
                writePos++;
            }
        }
        
        // Merge
        for (size_t c = 0; c < 3; ++c) {
            if (board.at(r, c) != 0 && board.at(r, c) == board.at(r, c + 1)) {
                board.at(r, c) *= 2;
                score += board.at(r, c);
                board.at(r, c + 1) = 0;
                moved = true;
                
                if (board.at(r, c) == 2048) {
                    won = true;
                }
            }
        }
        
        // Compress again
        writePos = 0;
        for (size_t c = 0; c < 4; ++c) {
            if (board.at(r, c) != 0) {
                if (writePos != c) {
                    board.at(r, writePos) = board.at(r, c);
                    board.at(r, c) = 0;
                }
                writePos++;
            }
        }
    }
    
    return moved;
}

bool Puzzle2048Game::moveRight() {
    bool moved = false;
    
    for (size_t r = 0; r < 4; ++r) {
        // Compress
        int writePos = 3;
        for (int c = 3; c >= 0; --c) {
            if (board.at(r, c) != 0) {
                if (writePos != c) {
                    board.at(r, writePos) = board.at(r, c);
                    board.at(r, c) = 0;
                    moved = true;
                }
                writePos--;
            }
        }
        
        // Merge
        for (int c = 3; c > 0; --c) {
            if (board.at(r, c) != 0 && board.at(r, c) == board.at(r, c - 1)) {
                board.at(r, c) *= 2;
                score += board.at(r, c);
                board.at(r, c - 1) = 0;
                moved = true;
                
                if (board.at(r, c) == 2048) {
                    won = true;
                }
            }
        }
        
        // Compress again
        writePos = 3;
        for (int c = 3; c >= 0; --c) {
            if (board.at(r, c) != 0) {
                if (writePos != c) {
                    board.at(r, writePos) = board.at(r, c);
                    board.at(r, c) = 0;
                }
                writePos--;
            }
        }
    }
    
    return moved;
}

bool Puzzle2048Game::moveUp() {
    bool moved = false;
    
    for (size_t c = 0; c < 4; ++c) {
        // Compress
        int writePos = 0;
        for (size_t r = 0; r < 4; ++r) {
            if (board.at(r, c) != 0) {
                if (writePos != r) {
                    board.at(writePos, c) = board.at(r, c);
                    board.at(r, c) = 0;
                    moved = true;
                }
                writePos++;
            }
        }
        
        // Merge
        for (size_t r = 0; r < 3; ++r) {
            if (board.at(r, c) != 0 && board.at(r, c) == board.at(r + 1, c)) {
                board.at(r, c) *= 2;
                score += board.at(r, c);
                board.at(r + 1, c) = 0;
                moved = true;
                
                if (board.at(r, c) == 2048) {
                    won = true;
                }
            }
        }
        
        // Compress again
        writePos = 0;
        for (size_t r = 0; r < 4; ++r) {
            if (board.at(r, c) != 0) {
                if (writePos != r) {
                    board.at(writePos, c) = board.at(r, c);
                    board.at(r, c) = 0;
                }
                writePos++;
            }
        }
    }
    
    return moved;
}

bool Puzzle2048Game::moveDown() {
    bool moved = false;
    
    for (size_t c = 0; c < 4; ++c) {
        // Compress
        int writePos = 3;
        for (int r = 3; r >= 0; --r) {
            if (board.at(r, c) != 0) {
                if (writePos != r) {
                    board.at(writePos, c) = board.at(r, c);
                    board.at(r, c) = 0;
                    moved = true;
                }
                writePos--;
            }
        }
        
        // Merge
        for (int r = 3; r > 0; --r) {
            if (board.at(r, c) != 0 && board.at(r, c) == board.at(r - 1, c)) {
                board.at(r, c) *= 2;
                score += board.at(r, c);
                board.at(r - 1, c) = 0;
                moved = true;
                
                if (board.at(r, c) == 2048) {
                    won = true;
                }
            }
        }
        
        // Compress again
        writePos = 3;
        for (int r = 3; r >= 0; --r) {
            if (board.at(r, c) != 0) {
                if (writePos != r) {
                    board.at(writePos, c) = board.at(r, c);
                    board.at(r, c) = 0;
                }
                writePos--;
            }
        }
    }
    
    return moved;
}

bool Puzzle2048Game::canMove() const {
    // Check for empty cells
    for (size_t r = 0; r < 4; ++r) {
        for (size_t c = 0; c < 4; ++c) {
            if (board.at(r, c) == 0) return true;
        }
    }
    
    // Check for possible merges
    for (size_t r = 0; r < 4; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            if (board.at(r, c) == board.at(r, c + 1)) return true;
        }
    }
    
    for (size_t c = 0; c < 4; ++c) {
        for (size_t r = 0; r < 3; ++r) {
            if (board.at(r, c) == board.at(r + 1, c)) return true;
        }
    }
    
    return false;
}

sf::Color Puzzle2048Game::getTileColor(int val) const {
    switch (val) {
        case 2: return sf::Color(238, 228, 218);
        case 4: return sf::Color(237, 224, 200);
        case 8: return sf::Color(242, 177, 121);
        case 16: return sf::Color(245, 149, 99);
        case 32: return sf::Color(246, 124, 95);
        case 64: return sf::Color(246, 94, 59);
        case 128: return sf::Color(237, 207, 114);
        case 256: return sf::Color(237, 204, 97);
        case 512: return sf::Color(237, 200, 80);
        case 1024: return sf::Color(237, 197, 63);
        case 2048: return sf::Color(237, 194, 46);
        default: return sf::Color(205, 193, 180);
    }
}

void Puzzle2048Game::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (gameOver) return;
    
    handleMouseDrag(event);
    
    if (event.type == sf::Event::KeyPressed) {
        bool moved = false;
        
        switch (event.key.code) {
            case sf::Keyboard::Left:
            case sf::Keyboard::A:
                moved = moveLeft();
                break;
            case sf::Keyboard::Right:
            case sf::Keyboard::D:
                moved = moveRight();
                break;
            case sf::Keyboard::Up:
            case sf::Keyboard::W:
                moved = moveUp();
                break;
            case sf::Keyboard::Down:
            case sf::Keyboard::S:
                moved = moveDown();
                break;
            default:
                break;
        }
        
        if (moved) {
            spawnTile();
            showMoveHint = false;
            if (!canMove()) {
                gameOver = true;
                if (subject) {
                    std::ostringstream oss;
                    oss << "Score: " << score << (won ? " (Won!)" : " (Game Over)");
                    subject->notifyGameOver(getName(), oss.str());
                }
            }
        }
    }
}

void Puzzle2048Game::update(float dt) {
    animationTimer += dt;
    if (gameOver) {
        gameOverTimer += dt;
    }
}

void Puzzle2048Game::render(sf::RenderWindow& window) {
    float cellSize = 120.0f;
    float padding = 12.0f;
    
    // Draw gradient background
    sf::RectangleShape bgGradient1(sf::Vector2f(900, 300));
    bgGradient1.setPosition(0, 0);
    bgGradient1.setFillColor(sf::Color(250, 248, 239));
    window.draw(bgGradient1);
    
    sf::RectangleShape bgGradient2(sf::Vector2f(900, 300));
    bgGradient2.setPosition(0, 300);
    bgGradient2.setFillColor(sf::Color(237, 224, 200));
    window.draw(bgGradient2);
    
    // Draw board background with shadow
    sf::RectangleShape boardShadow(sf::Vector2f(540, 540));
    boardShadow.setPosition(45, 85);
    boardShadow.setFillColor(sf::Color(0, 0, 0, 40));
    window.draw(boardShadow);
    
    sf::RectangleShape bg(sf::Vector2f(536, 536));
    bg.setPosition(40, 80);
    bg.setFillColor(sf::Color(187, 173, 160));
    bg.setOutlineThickness(3);
    bg.setOutlineColor(sf::Color(158, 143, 130));
    window.draw(bg);
    
    // Draw score with modern styling
    sf::RectangleShape scoreBg(sf::Vector2f(200, 55));
    scoreBg.setPosition(35, 15);
    scoreBg.setFillColor(sf::Color(238, 228, 218));
    scoreBg.setOutlineThickness(2);
    scoreBg.setOutlineColor(sf::Color(187, 173, 160));
    window.draw(scoreBg);
    
    sf::Text scoreLabel;
    scoreLabel.setFont(font);
    scoreLabel.setString("SCORE");
    scoreLabel.setCharacterSize(18);
    scoreLabel.setFillColor(sf::Color(119, 110, 101));
    scoreLabel.setStyle(sf::Text::Bold);
    scoreLabel.setPosition(45, 20);
    window.draw(scoreLabel);
    
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(std::to_string(score));
    scoreText.setCharacterSize(26);
    scoreText.setFillColor(sf::Color(119, 110, 101));
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setPosition(45, 42);
    window.draw(scoreText);
    
    // Draw tiles with enhanced effects
    for (size_t r = 0; r < 4; ++r) {
        for (size_t c = 0; c < 4; ++c) {
            float x = 40 + padding + c * (cellSize + padding);
            float y = 80 + padding + r * (cellSize + padding);
            
            // Tile shadow
            sf::RectangleShape tileShadow(sf::Vector2f(cellSize, cellSize));
            tileShadow.setPosition(x + 3, y + 3);
            tileShadow.setFillColor(sf::Color(0, 0, 0, 30));
            window.draw(tileShadow);
            
            sf::RectangleShape tile(sf::Vector2f(cellSize, cellSize));
            tile.setPosition(x, y);
            
            sf::Color tileColor = getTileColor(board.at(r, c));
            
            // Add glow effect for high value tiles
            if (board.at(r, c) >= 512) {
                float glow = 0.85f + 0.15f * std::sin(animationTimer * 3.0f);
                tileColor.r = std::min(255, (int)(tileColor.r * glow));
                tileColor.g = std::min(255, (int)(tileColor.g * glow));
                tileColor.b = std::min(255, (int)(tileColor.b * glow));
            }
            
            tile.setFillColor(tileColor);
            window.draw(tile);
            
            if (board.at(r, c) != 0) {
                sf::Text text;
                text.setFont(font);
                text.setString(std::to_string(board.at(r, c)));
                
                // Adjust font size based on number length
                if (board.at(r, c) < 100) text.setCharacterSize(50);
                else if (board.at(r, c) < 1000) text.setCharacterSize(45);
                else text.setCharacterSize(38);
                
                text.setFillColor(board.at(r, c) <= 4 ? sf::Color(119, 110, 101) : sf::Color::White);
                text.setStyle(sf::Text::Bold);
                
                sf::FloatRect bounds = text.getLocalBounds();
                text.setPosition(
                    x + (cellSize - bounds.width) / 2 - bounds.left,
                    y + (cellSize - bounds.height) / 2 - bounds.top - 3
                );
                window.draw(text);
            }
        }
    }

    // Instructions panel with modern design
    sf::RectangleShape instructionBg(sf::Vector2f(280, 380));
    instructionBg.setPosition(590.f, 80.f);
    instructionBg.setFillColor(sf::Color(238, 228, 218, 240));
    instructionBg.setOutlineThickness(3);
    instructionBg.setOutlineColor(sf::Color(187, 173, 160));
    window.draw(instructionBg);
    
    sf::Text title;
    title.setFont(font);
    title.setString("2048");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color(119, 110, 101));
    title.setStyle(sf::Text::Bold);
    title.setPosition(660.f, 90.f);
    window.draw(title);
    
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setCharacterSize(16);
    instructions.setFillColor(sf::Color(119, 110, 101));
    instructions.setPosition(605.f, 160.f);
    instructions.setString(
        "HOW TO PLAY\n\n"
        "\x95 Arrow Keys / WASD\n"
        "\x95 Swipe with Mouse\n\n"
        "Tiles slide in the\n"
        "direction you choose.\n\n"
        "When two tiles with\n"
        "the same number touch,\n"
        "they merge into one!\n\n"
        "Reach 2048 to WIN!\n\n"
        "ESC - Exit Game"
    );
    window.draw(instructions);
    
    // Show drag hint for first few seconds with pulse effect
    if (showMoveHint && animationTimer < 6.0f) {
        float alpha = 180 + 75 * std::sin(animationTimer * 3.0f);
        sf::RectangleShape hintBg(sf::Vector2f(300, 40));
        hintBg.setPosition(140.f, 515.f);
        hintBg.setFillColor(sf::Color(255, 200, 0, alpha * 0.6f));
        window.draw(hintBg);
        
        sf::Text hintText;
        hintText.setFont(font);
        hintText.setString("Try swiping on the board!");
        hintText.setCharacterSize(18);
        hintText.setFillColor(sf::Color(80, 60, 0, alpha));
        hintText.setStyle(sf::Text::Bold);
        hintText.setPosition(150.f, 522.f);
        window.draw(hintText);
    }
    
    if (gameOver) {
        // Overlay with fade-in
        float overlayAlpha = std::min(180.0f, gameOverTimer * 250.0f);
        sf::RectangleShape overlay(sf::Vector2f(536, 536));
        overlay.setPosition(40, 80);
        overlay.setFillColor(sf::Color(238, 228, 218, overlayAlpha));
        window.draw(overlay);
        
        // Message background
        sf::RectangleShape msgBg(sf::Vector2f(480, 120));
        msgBg.setPosition(68, 258);
        msgBg.setFillColor(won ? sf::Color(237, 194, 46) : sf::Color(119, 110, 101));
        window.draw(msgBg);
        
        // Animated text with glow
        sf::Text glowText;
        glowText.setFont(font);
        glowText.setString(won ? "YOU WON!" : "GAME OVER!");
        glowText.setCharacterSize(won ? 52 : 48);
        float pulse = 0.7f + 0.3f * std::sin(gameOverTimer * 4.0f);
        glowText.setFillColor(sf::Color(255, 255, 255, 150 * pulse));
        glowText.setStyle(sf::Text::Bold);
        glowText.setPosition(won ? 162 : 142, 268);
        window.draw(glowText);
        
        sf::Text text;
        text.setFont(font);
        text.setString(won ? "YOU WON!" : "GAME OVER!");
        text.setCharacterSize(won ? 52 : 48);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setPosition(won ? 160 : 140, 270);
        window.draw(text);
        
        sf::Text subText;
        subText.setFont(font);
        subText.setString(won ? "View leaderboard or scoreboard" : "Press ESC to exit");
        subText.setCharacterSize(20);
        subText.setFillColor(sf::Color(255, 255, 255, 230));
        subText.setPosition(won ? 108 : 160, 325);
        window.draw(subText);
        
        // Celebration particles for win
        if (won) {
            celebrationTimer += 0.016f;
            for (int i = 0; i < 20; ++i) {
                float angle = (i / 20.0f) * 6.28318f + celebrationTimer;
                float radius = 150 + 30 * std::sin(celebrationTimer * 2 + i);
                float x = 308 + radius * std::cos(angle);
                float y = 328 + radius * std::sin(angle);
                
                sf::CircleShape particle(4);
                particle.setPosition(x, y);
                float hue = (i / 20.0f + celebrationTimer * 0.2f);
                particle.setFillColor(sf::Color(255, 215, 0, 200));
                window.draw(particle);
            }
        }
    }
}

void Puzzle2048Game::handleMouseDrag(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        isDragging = true;
        dragStart = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
    } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        if (isDragging) {
            dragEnd = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
            processDragDirection();
            isDragging = false;
        }
    }
}

void Puzzle2048Game::processDragDirection() {
    const int minDragDistance = 30;
    sf::Vector2i delta = dragEnd - dragStart;
    
    if (std::abs(delta.x) < minDragDistance && std::abs(delta.y) < minDragDistance) {
        return; // Not enough movement
    }
    
    bool moved = false;
    if (std::abs(delta.x) > std::abs(delta.y)) {
        // Horizontal drag
        if (delta.x > 0) {
            moved = moveRight();
        } else {
            moved = moveLeft();
        }
    } else {
        // Vertical drag
        if (delta.y > 0) {
            moved = moveDown();
        } else {
            moved = moveUp();
        }
    }
    
    if (moved) {
        spawnTile();
        showMoveHint = false;
        if (!canMove()) {
            gameOver = true;
            if (subject) {
                std::ostringstream oss;
                oss << "Score: " << score << (won ? " (Won!)" : " (Game Over)");
                subject->notifyGameOver(getName(), oss.str());
            }
        }
    }
}

bool Puzzle2048Game::isOver() const {
    return gameOver && gameOverTimer >= 45.0f;
}
