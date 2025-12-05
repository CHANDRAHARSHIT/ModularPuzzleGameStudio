#ifndef TIC_TAC_TOE_GAME_HPP
#define TIC_TAC_TOE_GAME_HPP

#include "../core/Game.hpp"
#include "../core/Grid.hpp"
#include "../observer/Subject.hpp"
#include <optional>
#include "../ai/MoveStrategy.hpp"
#include <memory>

/**
 * Tic-Tac-Toe game implementation
 */
class TicTacToeGame : public Game {
private:
    Grid<char> board;
    char currentPlayer;
    bool gameOver;
    std::optional<char> winner;
    sf::Font font;
    Subject* subject;
    int hoverRow = -1;
    int hoverCol = -1;
    float pulseTimer = 0.f;
    float gameOverTimer = 0.f;  // Timer to keep win message visible
    float winLineTimer = 0.f;  // Animation timer for winning line
    bool hasWinLine = false;
    int winLineStartRow = -1, winLineStartCol = -1;
    int winLineEndRow = -1, winLineEndCol = -1;
    bool vsAI = true;        // single-player vs AI by default
    char aiSymbol = 'O';     // AI plays as 'O' by default
    std::unique_ptr<MoveStrategy<Grid<char>>> aiStrategy; // AI move strategy
    
    /**
     * Handle mouse click
     * @param pos Mouse position
     * @param window Reference to window
     */
    void handleClick(sf::Vector2i pos, sf::RenderWindow& window);
    
    /**
     * Check for winner
     */
    void checkWinner();
    
    /**
     * Update hover cell based on mouse position
     */
    void updateHover(sf::Vector2i mousePos);

    /**
     * Perform AI move when it's AI's turn
     */
    void performAIMove();

public:
    /**
     * Constructor
     * @param subj Pointer to subject for notifications
     */
    explicit TicTacToeGame(Subject* subj = nullptr);
    
    std::string getName() const override;
    void init() override;
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    bool isOver() const override;
};

#endif // TIC_TAC_TOE_GAME_HPP
