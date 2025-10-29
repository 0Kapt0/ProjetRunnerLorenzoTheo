#include "game_over_state.h"

GameOverState::GameOverState(sf::RenderWindow& window)
    : State(window)
{
    if (!font.openFromFile("src/fonts/font.ttf")) {
        std::cerr << "Erreur chargement font GameOverState\n";
    }

    overlay.setSize(sf::Vector2f(window.getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));

    titleText.emplace(font, "GAME OVER", 120);
    titleText->setFillColor(sf::Color::White);

    sf::FloatRect titleBounds = titleText->getLocalBounds();
    titleText->setOrigin({ titleBounds.size.x / 2.f, titleBounds.size.y / 2.f });
    titleText->setPosition({
        static_cast<float>(window.getSize().x) / 2.f,
        static_cast<float>(window.getSize().y) / 3.f
        });

    std::vector<std::string> labels = { "Restart", "Quit to Menu" };

    for (std::size_t i = 0; i < labels.size(); ++i) {
        sf::Text text(font, labels[i], 70);
        sf::FloatRect b = text.getLocalBounds();
        text.setOrigin({ b.size.x / 2.f, b.size.y / 2.f });
        text.setPosition({
            static_cast<float>(window.getSize().x) / 2.f,
            static_cast<float>(window.getSize().y) / 2.f + static_cast<float>(i) * 100.f
            });
        text.setFillColor(sf::Color::White);
        options.push_back(text);
    }
}

void GameOverState::handleInput()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

    selectedItem = -1;

    for (auto& option : options) {
        option.setFillColor(sf::Color::White);
    }

    for (std::size_t i = 0; i < options.size(); ++i) {
        if (options[i].getGlobalBounds().contains(worldMousePos)) {
            options[i].setFillColor(sf::Color::Red);
            selectedItem = static_cast<int>(i);
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && selectedItem != -1) {
        const std::string text = options[selectedItem].getString();
        if (text == "Restart") restartGame = true;
        else if (text == "Quit to Menu") quitToMenu = true;
    }
}

void GameOverState::update(float) {}

void GameOverState::draw()
{
    window.setView(window.getDefaultView());
    window.draw(overlay);
    if (titleText)
        window.draw(*titleText);
    for (const auto& o : options)
        window.draw(o);
}
