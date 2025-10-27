#include "pause_state.h"
#include <iostream>

PauseState::PauseState(sf::RenderWindow& window, const sf::Vector2f& playerPos)
    : state(window)
{
    if (!font.openFromFile("src/fonts/font.ttf")) {
        std::cerr << "Font non charge\n";
    }

    sf::Vector2f viewCenter = window.getView().getCenter();
    sf::Vector2f viewSize = window.getView().getSize();

    overlay.setSize(viewSize);
    overlay.setOrigin(viewSize / 2.f);
    overlay.setPosition(viewCenter);
    overlay.setFillColor(sf::Color(0, 0, 0, 180));

    const std::vector<std::string> labels = { "Resume", "Restart", "Quit to Menu" };
    float spacing = 100.f;
    float startY = viewCenter.y - (spacing * (labels.size() - 1) / 2.f);

    for (int i = 0; i < labels.size(); ++i) {
        sf::Text text(font);
        text.setCharacterSize(70);
        text.setString(labels[i]);

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });

        text.setPosition({ playerPos.x, startY + i * spacing });
        text.setFillColor(sf::Color::White);
        options.push_back(text);
    }
}

void PauseState::handleInput()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

    selectedItem = -1;

    for (int i = 0; i < options.size(); ++i) {
        if (options[i].getGlobalBounds().contains(worldMousePos)) {
            options[i].setFillColor(sf::Color::Red);
            selectedItem = i;
        }
        else {
            options[i].setFillColor(sf::Color::White);
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && selectedItem != -1) {
        auto text = options[selectedItem].getString();
        if (text == "Resume") resumeGame = true;
        else if (text == "Restart") restartGame = true;
        else if (text == "Quit to Menu") quitToMenu = true;
    }
}

void PauseState::update(float)
{
}

void PauseState::draw()
{
    window.draw(overlay);
    for (auto& opt : options)
        window.draw(opt);
}
