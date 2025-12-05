#ifndef TIC_TAC_TOE_RANDOM_AI_HPP
#define TIC_TAC_TOE_RANDOM_AI_HPP

#include "MoveStrategy.hpp"
#include "../core/Grid.hpp"

/**
 * Random AI strategy for Tic-Tac-Toe
 * Makes random valid moves
 */
class TicTacToeRandomAI : public MoveStrategy<Grid<char>> {
public:
    /**
     * Make a random valid move
     * @param board Reference to game board
     * @param symbol Player symbol (X or O)
     */
    void makeMove(Grid<char>& board, char symbol) override;
};

#endif // TIC_TAC_TOE_RANDOM_AI_HPP
