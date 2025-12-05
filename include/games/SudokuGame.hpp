#ifndef SUDOKU_GAME_HPP
#define SUDOKU_GAME_HPP

#include "../core/Game.hpp"
#include "../core/Grid.hpp"
#include "../observer/Subject.hpp"

/**
 * Sudoku puzzle game implementation
 */
class SudokuGame : public Game {
private:
    Grid<int> board;
    Grid<bool> fixedCells;
    bool gameOver;
    sf::Font font;
    Subject* subject;
    int selectedRow;
    int selectedCol;
    int hoverRow = -1;
    int hoverCol = -1;
    float highlightTimer = 0.f;
    float gameOverTimer = 0.f;  // Timer to keep win message visible
    float celebrationTimer = 0.f;  // Timer for solve celebration
    
    /**
     * Load a puzzle
     */
    void loadPuzzle();
    
    /**
     * Check if a move is valid
     * @param r Row
     * @param c Column
     * @param val Value to place
     * @return true if valid
     */
    bool isValidMove(int r, int c, int val) const;
    
    /**
     * Check if puzzle is solved
     * @return true if solved
     */
    bool isSolved() const;
    
    /**
     * Handle mouse click
     * @param pos Mouse position
     * @param window Reference to window
     */
    void handleClick(sf::Vector2i pos, sf::RenderWindow& window);
    
    /**
     * Update hover cell based on mouse position
     */
    void updateHover(sf::Vector2i mousePos);

public:
    /**
     * Constructor
     * @param subj Pointer to subject for notifications
     */
    explicit SudokuGame(Subject* subj = nullptr);
    
    std::string getName() const override;
    void init() override;
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    bool isOver() const override;
};

#endif // SUDOKU_GAME_HPP
