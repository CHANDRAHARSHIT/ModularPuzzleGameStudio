#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>

/**
 * Utility class for file I/O operations
 */
class FileManager {
public:
    /**
     * Append a line to a file
     * @param filename Path to file
     * @param line Line to append
     */
    static void appendLine(const std::string& filename, const std::string& line);
    
    /**
     * Read all lines from a file
     * @param filename Path to file
     * @return Vector of lines
     */
    static std::vector<std::string> readAllLines(const std::string& filename);
    
    /**
     * Check if file exists
     * @param filename Path to file
     * @return true if file exists
     */
    static bool fileExists(const std::string& filename);
};

#endif // FILE_MANAGER_HPP
