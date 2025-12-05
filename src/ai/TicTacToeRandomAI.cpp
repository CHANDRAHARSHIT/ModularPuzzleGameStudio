#include "../include/ai/TicTacToeRandomAI.hpp"
#include <random>
#include <vector>

void TicTacToeRandomAI::makeMove(Grid<char>& board, char symbol) {
    std::vector<std::pair<size_t, size_t>> emptyCells;
    
    // Find all empty cells
    for (size_t r = 0; r < board.getRows(); ++r) {
        for (size_t c = 0; c < board.getCols(); ++c) {
            if (board.at(r, c) == ' ') {
                emptyCells.push_back({r, c});
            }
        }
    }
    
    // Make random move if possible
    if (!emptyCells.empty()) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, emptyCells.size() - 1);
        
        auto [row, col] = emptyCells[dis(gen)];
        board.at(row, col) = symbol;
    }
}
