#include "../include/ui/ScoreBoardScreen.hpp"
#include <cmath>
#include <unordered_map>
#include <algorithm>

ScoreBoardScreen::ScoreBoardScreen(ScoreBoard& sb, ScreenManager& sm)
    : scoreBoard(sb), screenManager(sm) {
    
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }
}

void ScoreBoardScreen::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    // Main loop already listens for ESC to return to menu, no extra handling required here
}

void ScoreBoardScreen::update(float dt) {
    animationTime += dt;
}

void ScoreBoardScreen::render(sf::RenderWindow& window) {
    const float wave = std::sin(animationTime * 0.5f) * 30.f;
    sf::VertexArray gradient(sf::Quads, 4);
    gradient[0].position = {0.f, 0.f};
    gradient[1].position = {800.f, 0.f};
    gradient[2].position = {800.f, 600.f};
    gradient[3].position = {0.f, 600.f};
    sf::Color topColor(30, 30, 80 + static_cast<int>(wave));
    sf::Color bottomColor(10, 10, 30);
    gradient[0].color = topColor;
    gradient[1].color = topColor;
    gradient[2].color = bottomColor;
    gradient[3].color = bottomColor;
    window.draw(gradient);
    
    // Title
    sf::Text title;
    title.setFont(font);
    title.setString("Legendary Scores");
    title.setCharacterSize(42);
    title.setFillColor(sf::Color(255, 215, 0));
    title.setPosition(200, 25);
    window.draw(title);
    
    auto entries = scoreBoard.getEntries();
    std::unordered_map<std::string, int> playerCounts;
    for (const auto& entry : entries) {
        if (!entry.playerName.empty()) {
            ++playerCounts[entry.playerName];
        }
    }
    std::vector<std::pair<std::string, int>> legends(playerCounts.begin(), playerCounts.end());
    std::sort(legends.begin(), legends.end(), [](const auto& a, const auto& b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second > b.second;
    });
    if (legends.size() > 3) {
        legends.resize(3);
    }
    if (entries.empty()) {
        sf::Text noScores;
        noScores.setFont(font);
        noScores.setString("No champions recorded yet. Play a game!");
        noScores.setCharacterSize(22);
        noScores.setFillColor(sf::Color(200, 200, 200));
        noScores.setPosition(120, 290);
        window.draw(noScores);
    } else {
        float yBase = 120.f;
        int displayed = 0;
        for (auto it = entries.rbegin(); it != entries.rend() && displayed < 10; ++it, ++displayed) {
            float offset = std::sin(animationTime * 2.f + displayed * 0.5f) * 5.f;
            sf::RectangleShape card({500.f, 60.f});
            card.setPosition(40.f, yBase + displayed * 70.f + offset);
            card.setFillColor(sf::Color(40, 40, 80, 220));
            card.setOutlineThickness(2.f);
            card.setOutlineColor(sf::Color(80 + displayed * 10, 120, 220));
            window.draw(card);
            
            sf::Text playerLine;
            playerLine.setFont(font);
            playerLine.setCharacterSize(22);
            playerLine.setFillColor(sf::Color::White);
            playerLine.setString(it->playerName + " conquered " + it->gameName);
            playerLine.setPosition(card.getPosition().x + 15.f, card.getPosition().y + 8.f);
            window.draw(playerLine);
            
            sf::Text detailLine;
            detailLine.setFont(font);
            detailLine.setCharacterSize(16);
            detailLine.setFillColor(sf::Color(200, 200, 200));
            detailLine.setString(it->result + "  |  " + it->timestamp);
            detailLine.setPosition(card.getPosition().x + 15.f, card.getPosition().y + 34.f);
            window.draw(detailLine);
        }
    }
    sf::RectangleShape hallPanel({210.f, 360.f});
    hallPanel.setFillColor(sf::Color(20, 20, 60, 230));
    hallPanel.setOutlineThickness(2.f);
    hallPanel.setOutlineColor(sf::Color(255, 105, 180));
    hallPanel.setPosition(560.f, 140.f);
    window.draw(hallPanel);

    sf::Text hallTitle;
    hallTitle.setFont(font);
    hallTitle.setString("Hall of Legends");
    hallTitle.setCharacterSize(20);
    hallTitle.setFillColor(sf::Color(255, 215, 0));
    hallTitle.setPosition(hallPanel.getPosition().x + 12.f, hallPanel.getPosition().y + 10.f);
    window.draw(hallTitle);

    if (legends.empty()) {
        sf::Text prompt;
        prompt.setFont(font);
        prompt.setString("No heroes yet.\nPlay and claim the board!");
        prompt.setCharacterSize(16);
        prompt.setFillColor(sf::Color(220, 220, 220));
        prompt.setPosition(hallPanel.getPosition().x + 12.f, hallPanel.getPosition().y + 50.f);
        window.draw(prompt);
    } else {
        float legendY = hallPanel.getPosition().y + 55.f;
        int rank = 1;
        for (const auto& legend : legends) {
            sf::Text legendText;
            legendText.setFont(font);
            legendText.setCharacterSize(18);
            legendText.setFillColor(sf::Color::White);
            legendText.setString(std::to_string(rank) + ". " + legend.first);
            legendText.setPosition(hallPanel.getPosition().x + 12.f, legendY);
            window.draw(legendText);

            sf::Text countText;
            countText.setFont(font);
            countText.setCharacterSize(16);
            countText.setFillColor(sf::Color(180, 200, 255));
            countText.setString(std::to_string(legend.second) + " recorded feats");
            countText.setPosition(hallPanel.getPosition().x + 12.f, legendY + 24.f);
            window.draw(countText);

            legendY += 70.f;
            ++rank;
        }
    }
    
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Tip: Timer runs during games. Enter your name and rack up feats to reach the Hall of Legends. Press ESC to return.");
    instructions.setCharacterSize(18);
    instructions.setFillColor(sf::Color(220, 220, 220));
    instructions.setPosition(40.f, 540.f);
    window.draw(instructions);
}
