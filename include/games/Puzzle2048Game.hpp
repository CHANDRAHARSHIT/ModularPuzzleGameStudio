#ifndef PUZZLE_2048_GAME_HPP
#define PUZZLE_2048_GAME_HPP

#include "../core/Game.hpp"
#include "../core/Grid.hpp"
#include "../observer/Subject.hpp"

/**
 * 2048 puzzle game implementation
 */
class Puzzle2048Game : public Game {
private:
    Grid<int> board;
    bool gameOver;
    bool won;
    sf::Font font;
    Subject* subject;
    int score;
    bool isDragging = false;
    sf::Vector2i dragStart;
    sf::Vector2i dragEnd;
    float animationTimer = 0.f;
    float gameOverTimer = 0.f;  // Timer to keep win message visible
    float celebrationTimer = 0.f;  // Timer for win celebration effects
    bool showMoveHint = true;
    
    /**
     * Spawn a new tile (2 or 4)
     */
    void spawnTile();
    
    /**
     * Move tiles left
     * @return true if any tile moved
     */
    bool moveLeft();
    
    /**
     * Move tiles right
     * @return true if any tile moved
     */
    bool moveRight();
    
    /**
     * Move tiles up
     * @return true if any tile moved
     */
    bool moveUp();
    
    /**
     * Move tiles down
     * @return true if any tile moved
     */
    bool moveDown();
    
    /**
     * Check if any move is possible
     * @return true if can move
     */
    bool canMove() const;
    
    /**
     * Get color for tile value
     * @param val Tile value
     * @return SFML Color
     */
    sf::Color getTileColor(int val) const;

    /**
     * Handle mouse drag for swipe gestures
     */
    void handleMouseDrag(const sf::Event& event);
    
    /**
     * Process drag direction and make move
     */
    void processDragDirection();

public:
    /**
     * Constructor
     * @param subj Pointer to subject for notifications
     */
    explicit Puzzle2048Game(Subject* subj = nullptr);
    
    std::string getName() const override;
    void init() override;
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    bool isOver() const override;
};

#endif // PUZZLE_2048_GAME_HPP
