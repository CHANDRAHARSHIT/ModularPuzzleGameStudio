#include "../include/ui/NameEntryScreen.hpp"
#include "../include/ui/MainMenuScreen.hpp"
#include <memory>
#include <utility>

NameEntryScreen::NameEntryScreen(GameFactory& f,
                                 GameManager& gm,
                                 ScoreBoard& sb,
                                 ScreenManager& sm,
                                 Subject& subj,
                                 std::string targetGame)
    : factory(f), gameManager(gm), scoreBoard(sb), screenManager(sm), subject(subj), gameName(std::move(targetGame)) {
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }
}

void NameEntryScreen::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::TextEntered) {
        const auto code = event.text.unicode;
        if (code >= 32 && code < 127 && playerName.size() < 16) {
            playerName += static_cast<char>(code);
        }
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            launchGameAndReturn();
        } else if (event.key.code == sf::Keyboard::BackSpace && !playerName.empty()) {
            playerName.pop_back();
        }
    }
}

void NameEntryScreen::update(float dt) {
    caretTimer += dt;
    if (caretTimer >= 0.5f) {
        caretVisible = !caretVisible;
        caretTimer = 0.f;
    }
}

void NameEntryScreen::render(sf::RenderWindow& window) {
    window.clear(sf::Color(10, 10, 25));

    sf::RectangleShape panel({600.f, 250.f});
    panel.setFillColor(sf::Color(25, 25, 55, 240));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(120, 120, 255));
    panel.setPosition(100.f, 170.f);
    window.draw(panel);

    sf::Text title;
    title.setFont(font);
    title.setString("Enter your legend name for " + gameName);
    title.setCharacterSize(28);
    title.setFillColor(sf::Color(220, 220, 255));
    title.setPosition(120.f, 190.f);
    window.draw(title);

    sf::Text inputLabel;
    inputLabel.setFont(font);
    inputLabel.setString("Name:");
    inputLabel.setCharacterSize(24);
    inputLabel.setFillColor(sf::Color(180, 180, 220));
    inputLabel.setPosition(130.f, 260.f);
    window.draw(inputLabel);

    sf::RectangleShape inputBox({420.f, 50.f});
    inputBox.setFillColor(sf::Color(5, 5, 15));
    inputBox.setOutlineThickness(2.f);
    inputBox.setOutlineColor(sf::Color(150, 150, 255));
    inputBox.setPosition(210.f, 250.f);
    window.draw(inputBox);

    sf::Text nameText;
    nameText.setFont(font);
    nameText.setString(playerName.empty() ? "Player" : playerName);
    nameText.setCharacterSize(26);
    nameText.setFillColor(sf::Color::White);
    nameText.setPosition(225.f, 260.f);
    window.draw(nameText);

    if (caretVisible) {
        sf::RectangleShape caret({2.f, 32.f});
        float caretX = 225.f + nameText.getLocalBounds().width + 4.f;
        caret.setPosition(caretX, 262.f);
        caret.setFillColor(sf::Color(255, 215, 0));
        window.draw(caret);
    }

    sf::Text hint;
    hint.setFont(font);
    hint.setString("Tip: Keep it short (max 16 chars). Press Enter to begin!\nYour wins/losses will be tagged with this name on the scoreboard.");
    hint.setCharacterSize(18);
    hint.setFillColor(sf::Color(200, 200, 200));
    hint.setPosition(130.f, 330.f);
    window.draw(hint);
}

void NameEntryScreen::launchGameAndReturn() {
    std::string finalName = playerName;
    if (finalName.size() > 16) {
        finalName = finalName.substr(0, 16);
    }
    subject.setActivePlayerName(finalName);

    auto game = factory.create(gameName);
    if (game) {
        gameManager.setGame(std::move(game));
        gameManager.run();
    }

    screenManager.setScreen(std::make_unique<MainMenuScreen>(
        factory, gameManager, scoreBoard, screenManager, subject));
}
