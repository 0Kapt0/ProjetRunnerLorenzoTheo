#include "game_over_state.h"

GameOverState::GameOverState(sf::RenderWindow& window)
    : State(window)
{
    if (!font.openFromFile("src/fonts/font.ttf")) {
        std::cerr << "Erreur chargement font GameOverState\n";
    }

    sf::Vector2f viewCenter = view.getView().getCenter();
    sf::Vector2f viewSize = view.getView().getSize();

    overlay.setSize(viewSize);
    overlay.setOrigin(viewSize / 2.f);
    overlay.setPosition(viewCenter);
    overlay.setFillColor(sf::Color(0, 0, 0, 180));

    titleText.emplace(font, "GAME OVER", 120);
    sf::FloatRect titleBounds = titleText->getLocalBounds();
    titleText->setOrigin({ titleBounds.size.x / 2.f, titleBounds.size.y / 2.f });
    titleText->setPosition({ viewCenter.x, viewCenter.y - 200.f });
    titleText->setFillColor(sf::Color::White);

    const std::vector<std::string> labels = { "Restart", "Quit to Menu" };
    float startY = viewCenter.y + 50.f;

    for (int i = 0; i < labels.size(); ++i) {
        sf::Text text(font);
        text.setCharacterSize(70);
        text.setString(labels[i]);

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
        text.setPosition({ viewCenter.x, startY + i * 100.f });

        text.setPosition({ viewCenter.x, startY + i * 100.f });
        text.setFillColor(sf::Color::White);
        options.push_back(text);
    }
}

void GameOverState::handleInput()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos, view.getView());

    selectedItem = -1;

    for (auto& option : options)
        option.setFillColor(sf::Color::White);

    for (int i = 0; i < options.size(); ++i) {
        if (options[i].getGlobalBounds().contains(worldMousePos)) {
            options[i].setFillColor(sf::Color::Red);
            selectedItem = i;
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
    window.setView(view.getView());
    window.draw(overlay);
    if (titleText)
        window.draw(*titleText);
    for (auto& opt : options)
        window.draw(opt);
}
