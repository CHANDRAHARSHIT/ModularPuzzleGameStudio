#include "../include/util/ScoreBoard.hpp"
#include "../include/util/FileManager.hpp"
#include <sstream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <algorithm>

namespace {
std::string trim(const std::string& text) {
    const auto first = text.find_first_not_of(" \t");
    if (first == std::string::npos) return "";
    const auto last = text.find_last_not_of(" \t");
    return text.substr(first, last - first + 1);
}
}

ScoreBoard::ScoreBoard(const std::string& file) : filename(file) {
    if (!FileManager::fileExists(filename)) {
        std::ofstream createFile(filename);
    }
}

std::vector<ScoreBoard::ScoreEntry> ScoreBoard::getEntries() const {
    std::vector<ScoreEntry> entries;
    auto lines = FileManager::readAllLines(filename);
    entries.reserve(lines.size());
    for (const auto& line : lines) {
        if (line.empty()) continue;
        ScoreEntry entry;
        std::vector<std::string> parts;
        std::stringstream ss(line);
        std::string segment;
        while (std::getline(ss, segment, '|')) {
            parts.push_back(trim(segment));
        }
        if (!parts.empty()) entry.timestamp = parts[0];
        if (parts.size() >= 2) entry.gameName = parts[1];
        if (parts.size() >= 4) {
            entry.playerName = parts[2];
            entry.result = parts[3];
        } else if (parts.size() == 3) {
            entry.playerName = "Unknown";
            entry.result = parts[2];
        } else {
            entry.playerName = "Unknown";
            entry.result = line;
        }
        entries.push_back(entry);
    }
    return entries;
}

void ScoreBoard::addEntry(const ScoreEntry& entry) {
    std::ostringstream oss;
    oss << entry.timestamp << " | "
        << entry.gameName << " | "
        << entry.playerName << " | "
        << entry.result;
    FileManager::appendLine(filename, oss.str());
}

void ScoreBoard::onGameOver(const std::string& playerName,
                            const std::string& gameName,
                            const std::string& result) {
    // Get current timestamp
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    
    ScoreEntry entry;
    std::ostringstream timestampStream;
    timestampStream << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    entry.timestamp = timestampStream.str();
    entry.gameName = gameName;
    entry.playerName = playerName.empty() ? "Player" : playerName;
    entry.result = result;
    
    addEntry(entry);
}

std::pair<int, std::string> ScoreBoard::getPlayerStats(const std::string& playerName) const {
    auto entries = getEntries();
    int count = 0;
    int wins = 0;
    
    for (const auto& entry : entries) {
        if (entry.playerName == playerName) {
            count++;
            if (entry.result.find("Winner") != std::string::npos || 
                entry.result.find("Solved") != std::string::npos ||
                entry.result.find("Score:") != std::string::npos) {
                wins++;
            }
        }
    }
    
    std::string achievement;
    if (count >= 50) achievement = "Legendary Master";
    else if (count >= 20) achievement = "Seasoned Player";
    else if (count >= 10) achievement = "Regular Champion";
    else if (count >= 5) achievement = "Rising Star";
    else achievement = "Newcomer";
    
    return {count, achievement};
}

int ScoreBoard::getTotalGamesPlayed() const {
    return getEntries().size();
}
