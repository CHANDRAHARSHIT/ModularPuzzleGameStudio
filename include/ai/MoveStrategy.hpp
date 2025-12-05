#ifndef MOVE_STRATEGY_HPP
#define MOVE_STRATEGY_HPP

/**
 * Abstract strategy interface for AI moves
 * Implements the Strategy design pattern
 */
template<typename BoardType>
class MoveStrategy {
public:
    virtual ~MoveStrategy() = default;
    
    /**
     * Make a move on the board
     * @param board Reference to game board
     * @param symbol Player symbol/identifier
     */
    virtual void makeMove(BoardType& board, char symbol) = 0;
};

#endif // MOVE_STRATEGY_HPP
