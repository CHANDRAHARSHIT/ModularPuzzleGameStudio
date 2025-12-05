#include "../include/games/TicTacToeGame.hpp"
#include "../include/ai/TicTacToeRandomAI.hpp"
#include <sstream>
#include <cmath>

TicTacToeGame::TicTacToeGame(Subject* subj)
    : board(3, 3, ' '), currentPlayer('X'), gameOver(false), subject(subj) {}

std::string TicTacToeGame::getName() const {
    return "Tic-Tac-Toe";
}

void TicTacToeGame::init() {
    board.reset(' ');
    currentPlayer = 'X';
    gameOver = false;
    gameOverTimer = 0.f;
    winLineTimer = 0.f;
    hasWinLine = false;
    winner = std::nullopt;
    // initialize AI strategy if not present
    if (!aiStrategy) {
        aiStrategy = std::make_unique<TicTacToeRandomAI>();
    }
    
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        // Try alternative font paths
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }
    
    // Enable smooth font rendering for better scaling
    const_cast<sf::Texture&>(font.getTexture(100)).setSmooth(true);
}

void TicTacToeGame::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && !gameOver) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            handleClick(sf::Mouse::getPosition(window), window);
        }
    } else if (event.type == sf::Event::MouseMoved && !gameOver) {
        updateHover(sf::Mouse::getPosition(window));
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            // exit handled by framework
        }
        if (event.key.code == sf::Keyboard::R) {
            // restart game
            init();
        }
        if (event.key.code == sf::Keyboard::A) {
            // toggle AI mode
            vsAI = !vsAI;
            // if it's AI's turn right now, let it move
            if (!gameOver && vsAI && currentPlayer == aiSymbol) {
                performAIMove();
            }
        }
    }
}

void TicTacToeGame::handleClick(sf::Vector2i pos, sf::RenderWindow& window) {
    float cellSize = 200.0f;
    int row = pos.y / cellSize;
    int col = pos.x / cellSize;
    
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        if (board.at(row, col) == ' ') {
            board.at(row, col) = currentPlayer;
            checkWinner();
            if (!gameOver) {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                // if AI is enabled and it's AI's turn, let the AI play immediately
                if (vsAI && currentPlayer == aiSymbol) {
                    performAIMove();
                }
            }
        }
    }
}

void TicTacToeGame::checkWinner() {
    // Check rows
    for (size_t r = 0; r < 3; ++r) {
        if (board.at(r, 0) != ' ' && 
            board.at(r, 0) == board.at(r, 1) && 
            board.at(r, 1) == board.at(r, 2)) {
            winner = board.at(r, 0);
            gameOver = true;
            hasWinLine = true;
            winLineStartRow = r; winLineStartCol = 0;
            winLineEndRow = r; winLineEndCol = 2;
            if (subject) {
                subject->notifyGameOver(getName(), std::string("Winner: ") + winner.value());
            }
            return;
        }
    }
    
    // Check columns
    for (size_t c = 0; c < 3; ++c) {
        if (board.at(0, c) != ' ' && 
            board.at(0, c) == board.at(1, c) && 
            board.at(1, c) == board.at(2, c)) {
            winner = board.at(0, c);
            gameOver = true;
            hasWinLine = true;
            winLineStartRow = 0; winLineStartCol = c;
            winLineEndRow = 2; winLineEndCol = c;
            if (subject) {
                subject->notifyGameOver(getName(), std::string("Winner: ") + winner.value());
            }
            return;
        }
    }
    
    // Check diagonals
    if (board.at(0, 0) != ' ' && 
        board.at(0, 0) == board.at(1, 1) && 
        board.at(1, 1) == board.at(2, 2)) {
        winner = board.at(0, 0);
        gameOver = true;
        hasWinLine = true;
        winLineStartRow = 0; winLineStartCol = 0;
        winLineEndRow = 2; winLineEndCol = 2;
        if (subject) {
            subject->notifyGameOver(getName(), std::string("Winner: ") + winner.value());
        }
        return;
    }
    
    if (board.at(0, 2) != ' ' && 
        board.at(0, 2) == board.at(1, 1) && 
        board.at(1, 1) == board.at(2, 0)) {
        winner = board.at(0, 2);
        gameOver = true;
        hasWinLine = true;
        winLineStartRow = 0; winLineStartCol = 2;
        winLineEndRow = 2; winLineEndCol = 0;
        if (subject) {
            subject->notifyGameOver(getName(), std::string("Winner: ") + winner.value());
        }
        return;
    }
    
    // Check for draw
    bool full = true;
    for (size_t r = 0; r < 3; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            if (board.at(r, c) == ' ') {
                full = false;
                break;
            }
        }
    }
    
    if (full) {
        gameOver = true;
        if (subject) {
            subject->notifyGameOver(getName(), "Draw");
        }
    }
}

void TicTacToeGame::update(float dt) {
    pulseTimer += dt;
    if (gameOver) {
        gameOverTimer += dt;
        winLineTimer += dt;
    }
}

void TicTacToeGame::render(sf::RenderWindow& window) {
    float cellSize = 200.0f;
    
    // Draw gradient background
    sf::RectangleShape bgTop(sf::Vector2f(600, 300));
    bgTop.setPosition(0, 0);
    bgTop.setFillColor(sf::Color(240, 248, 255));
    window.draw(bgTop);
    
    sf::RectangleShape bgBottom(sf::Vector2f(600, 300));
    bgBottom.setPosition(0, 300);
    bgBottom.setFillColor(sf::Color(230, 240, 250));
    window.draw(bgBottom);
    
    // Draw cells with hover effects and shadows
    for (size_t r = 0; r < 3; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            // Shadow effect
            sf::RectangleShape shadow(sf::Vector2f(cellSize - 8, cellSize - 8));
            shadow.setPosition(c * cellSize + 8, r * cellSize + 8);
            shadow.setFillColor(sf::Color(0, 0, 0, 30));
            window.draw(shadow);
            
            sf::RectangleShape cell(sf::Vector2f(cellSize - 10, cellSize - 10));
            cell.setPosition(c * cellSize + 5, r * cellSize + 5);
            
            if (r == hoverRow && c == hoverCol && board.at(r, c) == ' ' && !gameOver) {
                float glow = 0.5f + 0.3f * std::sin(pulseTimer * 5.0f);
                cell.setFillColor(sf::Color(100, 200, 255, 80 + 120 * glow));
            } else {
                cell.setFillColor(sf::Color(255, 255, 255, 250));
            }
            cell.setOutlineThickness(3);
            cell.setOutlineColor(sf::Color(70, 130, 180, 200));
            window.draw(cell);
        }
    }
    
    // Draw grid lines with gradient effect
    for (int i = 1; i < 3; ++i) {
        sf::RectangleShape line(sf::Vector2f(600, 6));
        line.setPosition(0, i * cellSize - 3);
        line.setFillColor(sf::Color(50, 100, 150, 180));
        window.draw(line);
        
        line.setSize(sf::Vector2f(6, 600));
        line.setPosition(i * cellSize - 3, 0);
        window.draw(line);
    }
    
    // Draw X's and O's with enhanced effects and glow
    for (size_t r = 0; r < 3; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            if (board.at(r, c) != ' ') {
                // Glow effect
                sf::Text glow;
                glow.setFont(font);
                glow.setString(std::string(1, board.at(r, c)));
                glow.setCharacterSize(110);
                sf::Color glowColor = board.at(r, c) == 'X' ? sf::Color(0, 100, 255, 100) : sf::Color(255, 50, 50, 100);
                glow.setFillColor(glowColor);
                glow.setPosition(c * cellSize + 45, r * cellSize + 25);
                glow.setStyle(sf::Text::Bold);
                window.draw(glow);
                
                // Main symbol
                sf::Text text;
                text.setFont(font);
                text.setString(std::string(1, board.at(r, c)));
                text.setCharacterSize(100);
                text.setFillColor(board.at(r, c) == 'X' ? sf::Color(0, 120, 255) : sf::Color(255, 60, 60));
                text.setPosition(c * cellSize + 50, r * cellSize + 30);
                text.setStyle(sf::Text::Bold);
                window.draw(text);
            } else if (r == hoverRow && c == hoverCol && !gameOver) {
                // Show preview of next move
                sf::Text preview;
                preview.setFont(font);
                preview.setString(std::string(1, currentPlayer));
                preview.setCharacterSize(90);
                sf::Color previewColor = currentPlayer == 'X' ? sf::Color(0, 120, 255) : sf::Color(255, 60, 60);
                float alpha = 60 + 40 * std::sin(pulseTimer * 4.0f);
                previewColor.a = alpha;
                preview.setFillColor(previewColor);
                preview.setPosition(c * cellSize + 55, r * cellSize + 40);
                window.draw(preview);
            }
        }
    }
    
    // Draw winning line animation
    if (gameOver && winner.has_value() && hasWinLine) {
        float progress = std::min(1.0f, winLineTimer * 2.0f);
        float startX = winLineStartCol * cellSize + cellSize / 2;
        float startY = winLineStartRow * cellSize + cellSize / 2;
        float endX = winLineEndCol * cellSize + cellSize / 2;
        float endY = winLineEndRow * cellSize + cellSize / 2;
        
        float currentEndX = startX + (endX - startX) * progress;
        float currentEndY = startY + (endY - startY) * progress;
        
        // Glow for line
        sf::Vertex glowLine[] = {
            sf::Vertex(sf::Vector2f(startX, startY), sf::Color(255, 215, 0, 150)),
            sf::Vertex(sf::Vector2f(currentEndX, currentEndY), sf::Color(255, 215, 0, 150))
        };
        for (int i = 0; i < 8; ++i) {
            window.draw(glowLine, 2, sf::Lines);
        }
        
        // Main line
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(startX, startY), sf::Color(255, 215, 0)),
            sf::Vertex(sf::Vector2f(currentEndX, currentEndY), sf::Color(255, 215, 0))
        };
        window.draw(line, 2, sf::Lines);
    }
    
    // Show control instructions with modern styling
    sf::RectangleShape instructionBg(sf::Vector2f(250, 280));
    instructionBg.setPosition(610.f, 100.f);
    instructionBg.setFillColor(sf::Color(255, 255, 255, 230));
    instructionBg.setOutlineThickness(2);
    instructionBg.setOutlineColor(sf::Color(70, 130, 180));
    window.draw(instructionBg);
    
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setCharacterSize(18);
    instructions.setFillColor(sf::Color(30, 30, 30));
    instructions.setPosition(620.f, 110.f);
    instructions.setString(
        "How to Play\n\n"
        "\x95 Click empty cell\n"
        "\x95 Hover to preview\n"
        "\x95 Get 3 in a row\n"
        "\x95 X vs O (AI)\n\n"
        "Controls:\n"
        "\x95 'A' - Toggle AI\n"
        "\x95 'R' - Restart\n"
        "\x95 ESC - Exit"
    );
    window.draw(instructions);

    // Current player indicator with glow
    if (!gameOver) {
        sf::RectangleShape turnBg(sf::Vector2f(200, 60));
        turnBg.setPosition(635.f, 400.f);
        turnBg.setFillColor(currentPlayer == 'X' ? sf::Color(0, 120, 255, 200) : sf::Color(255, 60, 60, 200));
        window.draw(turnBg);
        
        sf::Text playerTurn;
        playerTurn.setFont(font);
        playerTurn.setString(std::string("Turn: ") + currentPlayer);
        playerTurn.setCharacterSize(28);
        playerTurn.setFillColor(sf::Color::White);
        playerTurn.setStyle(sf::Text::Bold);
        playerTurn.setPosition(660.f, 415.f);
        window.draw(playerTurn);
    }

    // Draw animated game over message
    if (gameOver) {
        // Background overlay with fade
        float alpha = std::min(200.0f, gameOverTimer * 300.0f);
        sf::RectangleShape overlay(sf::Vector2f(800, 150));
        overlay.setPosition(50, 500);
        overlay.setFillColor(sf::Color(0, 0, 0, alpha * 0.8f));
        window.draw(overlay);
        
        // Glow effect
        sf::Text glowText;
        glowText.setFont(font);
        if (winner.has_value()) {
            glowText.setString("You won! View leaderboard or scoreboard");
        } else {
            glowText.setString("Draw! Press ESC");
        }
        glowText.setCharacterSize(32);
        float pulse = 0.7f + 0.3f * std::sin(gameOverTimer * 3.0f);
        glowText.setFillColor(sf::Color(255, 255, 0, alpha * pulse));
        glowText.setPosition(78, 548);
        window.draw(glowText);
        
        // Main text
        sf::Text text;
        text.setFont(font);
        if (winner.has_value()) {
            text.setString("You won! View leaderboard or scoreboard");
        } else {
            text.setString("Draw! Press ESC");
        }
        text.setCharacterSize(32);
        text.setFillColor(winner.has_value() ? sf::Color(50, 255, 50) : sf::Color(255, 255, 100));
        text.setStyle(sf::Text::Bold);
        text.setPosition(80, 550);
        window.draw(text);
    }
}

bool TicTacToeGame::isOver() const {
    return gameOver && gameOverTimer >= 45.0f;
}

void TicTacToeGame::updateHover(sf::Vector2i mousePos) {
    float cellSize = 200.0f;
    int row = mousePos.y / cellSize;
    int col = mousePos.x / cellSize;
    
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        hoverRow = row;
        hoverCol = col;
    } else {
        hoverRow = -1;
        hoverCol = -1;
    }
}

void TicTacToeGame::performAIMove() {
    if (!vsAI || gameOver || currentPlayer != aiSymbol || !aiStrategy) return;
    aiStrategy->makeMove(board, aiSymbol);
    checkWinner();
    if (!gameOver) {
        currentPlayer = 'X';
    }
}
