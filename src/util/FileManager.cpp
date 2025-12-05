#include "../include/util/FileManager.hpp"
#include <fstream>
#include <iostream>

void FileManager::appendLine(const std::string& filename, const std::string& line) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << line << std::endl;
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

std::vector<std::string> FileManager::readAllLines(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    
    return lines;
}

bool FileManager::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}
