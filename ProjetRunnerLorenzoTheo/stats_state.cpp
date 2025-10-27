#include "stats_state.h"


StatsState::StatsState(sf::RenderWindow& window): state(window), back(font)
{

	if (!font.openFromFile("src/fonts/font.ttf")) {
		std::cerr << "Erreur de chargement de la police\n";
	}

	back.setCharacterSize(50);
	back.setString("Back");
	back.setPosition({ 200.f, 600.f });
}

void StatsState::handleInput()
{
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (back.getGlobalBounds().contains(mousePos)) {
            backToMenu = true;
        }
    }
}
void StatsState::update(float dt) {}

void StatsState::draw()
{
    window.setView(window.getDefaultView());
    window.draw(back);
}