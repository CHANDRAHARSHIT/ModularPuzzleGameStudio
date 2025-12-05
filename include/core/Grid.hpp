#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <stdexcept>

/**
 * Generic 2D grid template class
 * Provides a convenient interface for 2D board games
 */
template<typename T>
class Grid {
private:
    size_t rows;
    size_t cols;
    std::vector<T> data;

public:
    /**
     * Constructor
     * @param r Number of rows
     * @param c Number of columns
     * @param v Initial value for all cells
     */
    Grid(size_t r = 0, size_t c = 0, const T& v = T())
        : rows(r), cols(c), data(r * c, v) {}
    
    /**
     * Access element at position (r, c)
     * @param r Row index
     * @param c Column index
     * @return Reference to element (or proxy for vector<bool>)
     */
    auto at(size_t r, size_t c) -> decltype(data[0]) {
        if (r >= rows || c >= cols) {
            throw std::out_of_range("Grid index out of range");
        }
        return data[r * cols + c];
    }
    
    /**
     * Access element at position (r, c) - const version
     * @param r Row index
     * @param c Column index
     * @return Const reference to element
     */
    const T& at(size_t r, size_t c) const {
        if (r >= rows || c >= cols) {
            throw std::out_of_range("Grid index out of range");
        }
        return data[r * cols + c];
    }
    
    /**
     * Get number of rows
     * @return Number of rows
     */
    size_t getRows() const { return rows; }
    
    /**
     * Get number of columns
     * @return Number of columns
     */
    size_t getCols() const { return cols; }
    
    /**
     * Reset all cells to a value
     * @param v Value to set
     */
    void reset(const T& v = T()) {
        std::fill(data.begin(), data.end(), v);
    }
};

#endif // GRID_HPP
