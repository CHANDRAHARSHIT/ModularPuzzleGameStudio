#include "../include/games/SudokuGame.hpp"
#include <random>
#include <cmath>

SudokuGame::SudokuGame(Subject* subj)
    : board(9, 9, 0), fixedCells(9, 9, false), gameOver(false), 
      subject(subj), selectedRow(-1), selectedCol(-1) {}

std::string SudokuGame::getName() const {
    return "Sudoku";
}

void SudokuGame::init() {
    board.reset(0);
    fixedCells.reset(false);
    gameOver = false;
    gameOverTimer = 0.f;
    celebrationTimer = 0.f;
    selectedRow = -1;
    selectedCol = -1;
    
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }
    
    // Enable smooth font rendering
    const_cast<sf::Texture&>(font.getTexture(30)).setSmooth(true);
    
    loadPuzzle();
}

void SudokuGame::loadPuzzle() {
    // Simple puzzle for demonstration
    int puzzle[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            board.at(r, c) = puzzle[r][c];
            fixedCells.at(r, c) = (puzzle[r][c] != 0);
        }
    }
}

bool SudokuGame::isValidMove(int r, int c, int val) const {
    // Check row
    for (int i = 0; i < 9; ++i) {
        if (i != c && board.at(r, i) == val) return false;
    }
    
    // Check column
    for (int i = 0; i < 9; ++i) {
        if (i != r && board.at(i, c) == val) return false;
    }
    
    // Check 3x3 box
    int boxR = (r / 3) * 3;
    int boxC = (c / 3) * 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int row = boxR + i;
            int col = boxC + j;
            if ((row != r || col != c) && board.at(row, col) == val) {
                return false;
            }
        }
    }
    
    return true;
}

bool SudokuGame::isSolved() const {
    for (size_t r = 0; r < 9; ++r) {
        for (size_t c = 0; c < 9; ++c) {
            if (board.at(r, c) == 0) return false;
            if (!isValidMove(r, c, board.at(r, c))) return false;
        }
    }
    return true;
}

void SudokuGame::handleClick(sf::Vector2i pos, sf::RenderWindow& window) {
    float cellSize = 60.0f;
    int row = pos.y / cellSize;
    int col = pos.x / cellSize;
    
    if (row >= 0 && row < 9 && col >= 0 && col < 9) {
        if (!fixedCells.at(row, col)) {
            selectedRow = row;
            selectedCol = col;
        }
    }
}

void SudokuGame::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (gameOver) return;
    
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            handleClick(sf::Mouse::getPosition(window), window);
        }
    } else if (event.type == sf::Event::MouseMoved) {
        updateHover(sf::Mouse::getPosition(window));
    } else if (event.type == sf::Event::KeyPressed) {
        if (selectedRow >= 0 && selectedCol >= 0) {
            if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9) {
                int num = event.key.code - sf::Keyboard::Num0;
                if (isValidMove(selectedRow, selectedCol, num)) {
                    board.at(selectedRow, selectedCol) = num;
                    if (isSolved()) {
                        gameOver = true;
                        if (subject) {
                            subject->notifyGameOver(getName(), "Solved!");
                        }
                    }
                }
            } else if (event.key.code == sf::Keyboard::Delete || 
                       event.key.code == sf::Keyboard::BackSpace) {
                board.at(selectedRow, selectedCol) = 0;
            }
        }
    }
}

void SudokuGame::update(float dt) {
    highlightTimer += dt;
    if (gameOver) {
        gameOverTimer += dt;
    }
}

void SudokuGame::render(sf::RenderWindow& window) {
    float cellSize = 60.0f;
    
    // Draw gradient background
    sf::RectangleShape bgTop(sf::Vector2f(900, 270));
    bgTop.setPosition(0, 0);
    bgTop.setFillColor(sf::Color(245, 245, 250));
    window.draw(bgTop);
    
    sf::RectangleShape bgBottom(sf::Vector2f(900, 330));
    bgBottom.setPosition(0, 270);
    bgBottom.setFillColor(sf::Color(235, 235, 245));
    window.draw(bgBottom);
    
    // Draw board shadow
    sf::RectangleShape boardShadow(sf::Vector2f(545, 545));
    boardShadow.setPosition(3, 3);
    boardShadow.setFillColor(sf::Color(0, 0, 0, 30));
    window.draw(boardShadow);
    
    // Draw cells with enhanced effects
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            sf::RectangleShape cell(sf::Vector2f(cellSize - 2, cellSize - 2));
            cell.setPosition(c * cellSize + 1, r * cellSize + 1);
            
            // Check for conflicts
            bool hasConflict = false;
            if (board.at(r, c) != 0 && !fixedCells.at(r, c)) {
                for (int i = 0; i < 9; ++i) {
                    if ((i != c && board.at(r, i) == board.at(r, c)) ||
                        (i != r && board.at(i, c) == board.at(r, c))) {
                        hasConflict = true;
                        break;
                    }
                }
                // Check 3x3 box
                if (!hasConflict) {
                    int boxR = (r / 3) * 3;
                    int boxC = (c / 3) * 3;
                    for (int i = 0; i < 3 && !hasConflict; ++i) {
                        for (int j = 0; j < 3; ++j) {
                            int row = boxR + i;
                            int col = boxC + j;
                            if ((row != r || col != c) && board.at(row, col) == board.at(r, c)) {
                                hasConflict = true;
                                break;
                            }
                        }
                    }
                }
            }
            
            if (hasConflict) {
                float pulse = 0.6f + 0.4f * std::sin(highlightTimer * 4.0f);
                cell.setFillColor(sf::Color(255, 100, 100, 200 * pulse));
            } else if (r == selectedRow && c == selectedCol) {
                float pulse = 0.85f + 0.15f * std::sin(highlightTimer * 3.0f);
                cell.setFillColor(sf::Color(100, 150, 255, 220 * pulse));
            } else if (r == hoverRow && c == hoverCol && !fixedCells.at(r, c)) {
                cell.setFillColor(sf::Color(180, 220, 255, 180));
            } else if (selectedRow >= 0 && (r == selectedRow || c == selectedCol)) {
                cell.setFillColor(sf::Color(220, 230, 255, 150));
            } else if (selectedRow >= 0 && board.at(r, c) != 0 && board.at(r, c) == board.at(selectedRow, selectedCol)) {
                cell.setFillColor(sf::Color(200, 220, 255, 180));
            } else if (fixedCells.at(r, c)) {
                cell.setFillColor(sf::Color(235, 235, 245));
            } else {
                cell.setFillColor(sf::Color(255, 255, 255));
            }
            
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color(200, 200, 210));
            window.draw(cell);
            
            // Draw number with shadow
            if (board.at(r, c) != 0) {
                // Shadow
                sf::Text shadow;
                shadow.setFont(font);
                shadow.setString(std::to_string(board.at(r, c)));
                shadow.setCharacterSize(32);
                shadow.setFillColor(sf::Color(0, 0, 0, 30));
                shadow.setPosition(c * cellSize + 19, r * cellSize + 9);
                window.draw(shadow);
                
                // Main number
                sf::Text text;
                text.setFont(font);
                text.setString(std::to_string(board.at(r, c)));
                text.setCharacterSize(32);
                text.setStyle(sf::Text::Bold);
                
                if (hasConflict) {
                    text.setFillColor(sf::Color(200, 0, 0));
                } else if (fixedCells.at(r, c)) {
                    text.setFillColor(sf::Color(40, 40, 50));
                } else {
                    text.setFillColor(sf::Color(0, 100, 200));
                }
                
                text.setPosition(c * cellSize + 18, r * cellSize + 8);
                window.draw(text);
            }
        }
    }
    
    // Draw thick grid lines for 3x3 boxes
    for (int i = 0; i <= 9; i += 3) {
        sf::RectangleShape line(sf::Vector2f(540, i == 0 || i == 9 ? 4 : 4));
        line.setPosition(0, i * cellSize - 2);
        line.setFillColor(sf::Color(70, 70, 90));
        window.draw(line);
        
        line.setSize(sf::Vector2f(i == 0 || i == 9 ? 4 : 4, 540));
        line.setPosition(i * cellSize - 2, 0);
        window.draw(line);
    }

    // Instructions panel with modern design
    sf::RectangleShape instructionBg(sf::Vector2f(310, 480));
    instructionBg.setPosition(560.f, 60.f);
    instructionBg.setFillColor(sf::Color(255, 255, 255, 240));
    instructionBg.setOutlineThickness(3);
    instructionBg.setOutlineColor(sf::Color(100, 150, 200));
    window.draw(instructionBg);
    
    sf::Text title;
    title.setFont(font);
    title.setString("SUDOKU");
    title.setCharacterSize(42);
    title.setFillColor(sf::Color(50, 50, 80));
    title.setStyle(sf::Text::Bold);
    title.setPosition(620.f, 75.f);
    window.draw(title);
    
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setCharacterSize(16);
    instructions.setFillColor(sf::Color(60, 60, 70));
    instructions.setPosition(575.f, 140.f);
    instructions.setString(
        "HOW TO PLAY\n\n"
        "\x95 Click to select cell\n"
        "\x95 Type 1-9 to fill\n"
        "\x95 Delete to clear\n\n"
        "RULES\n\n"
        "Each row, column, and\n"
        "3x3 box must contain\n"
        "digits 1-9 without\n"
        "repetition.\n\n"
        "COLORS\n\n"
        "\x95 Black - Fixed\n"
        "\x95 Blue - Your input\n"
        "\x95 Red - Conflict!\n\n"
        "ESC - Exit Game"
    );
    window.draw(instructions);
    
    // Show selected cell info with modern styling
    if (selectedRow >= 0 && selectedCol >= 0) {
        sf::RectangleShape infoBg(sf::Vector2f(200, 35));
        infoBg.setPosition(615.f, 495.f);
        infoBg.setFillColor(sf::Color(100, 150, 255, 200));
        window.draw(infoBg);
        
        sf::Text cellInfo;
        cellInfo.setFont(font);
        cellInfo.setString("Cell: (" + std::to_string(selectedRow + 1) + ", " + std::to_string(selectedCol + 1) + ")");
        cellInfo.setCharacterSize(18);
        cellInfo.setFillColor(sf::Color::White);
        cellInfo.setStyle(sf::Text::Bold);
        cellInfo.setPosition(640.f, 502.f);
        window.draw(cellInfo);
    }
    
    if (gameOver) {
        // Celebration overlay
        float overlayAlpha = std::min(180.0f, gameOverTimer * 250.0f);
        sf::RectangleShape overlay(sf::Vector2f(540, 540));
        overlay.setPosition(0, 0);
        overlay.setFillColor(sf::Color(255, 255, 255, overlayAlpha * 0.9f));
        window.draw(overlay);
        
        // Success message background
        sf::RectangleShape msgBg(sf::Vector2f(480, 140));
        msgBg.setPosition(30, 200);
        msgBg.setFillColor(sf::Color(50, 200, 100));
        window.draw(msgBg);
        
        // Animated glow
        sf::Text glowText;
        glowText.setFont(font);
        glowText.setString("PUZZLE SOLVED!");
        glowText.setCharacterSize(48);
        float pulse = 0.7f + 0.3f * std::sin(gameOverTimer * 4.0f);
        glowText.setFillColor(sf::Color(255, 255, 255, 200 * pulse));
        glowText.setStyle(sf::Text::Bold);
        glowText.setPosition(72, 218);
        window.draw(glowText);
        
        sf::Text text;
        text.setFont(font);
        text.setString("PUZZLE SOLVED!");
        text.setCharacterSize(48);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setPosition(70, 220);
        window.draw(text);
        
        sf::Text subText;
        subText.setFont(font);
        subText.setString("View leaderboard or scoreboard");
        subText.setCharacterSize(20);
        subText.setFillColor(sf::Color(255, 255, 255, 240));
        subText.setPosition(85, 280);
        window.draw(subText);
        
        // Celebration particles
        celebrationTimer += 0.016f;
        for (int i = 0; i < 30; ++i) {
            float angle = (i / 30.0f) * 6.28318f + celebrationTimer * 1.5f;
            float radius = 120 + 40 * std::sin(celebrationTimer * 3 + i * 0.5f);
            float x = 270 + radius * std::cos(angle);
            float y = 270 + radius * std::sin(angle);
            
            sf::CircleShape particle(3 + 2 * std::sin(celebrationTimer * 2 + i));
            particle.setPosition(x, y);
            int colorPhase = (i * 3) % 360;
            if (colorPhase < 120) particle.setFillColor(sf::Color(50, 200, 100, 220));
            else if (colorPhase < 240) particle.setFillColor(sf::Color(100, 150, 255, 220));
            else particle.setFillColor(sf::Color(255, 200, 50, 220));
            window.draw(particle);
        }
    }
}

bool SudokuGame::isOver() const {
    return gameOver && gameOverTimer >= 45.0f;
}

void SudokuGame::updateHover(sf::Vector2i mousePos) {
    float cellSize = 60.0f;
    int row = mousePos.y / cellSize;
    int col = mousePos.x / cellSize;
    
    if (row >= 0 && row < 9 && col >= 0 && col < 9) {
        hoverRow = row;
        hoverCol = col;
    } else {
        hoverRow = -1;
        hoverCol = -1;
    }
}
