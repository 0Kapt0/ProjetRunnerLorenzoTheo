#include "speedometer.h"

Speedometer::Speedometer(const sf::Font& font): speedText(font, "", 56)
{
    speedText.setFillColor(sf::Color::Black);
}

void Speedometer::setSpeedText(float s) {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(0) << s/10;
	speedText.setString(ss.str());
}

void Speedometer::draw(sf::RenderTarget& target, const sf::View& view, const sf::Vector2f& playerPos)
{
    sf::View oldView = target.getView();
    target.setView(view);



    sf::Vector2f topRight = view.getCenter() + view.getSize() / 2.f;

    speedText.setPosition({ view.getCenter().x - view.getSize().x / 2.f, view.getCenter().y + view.getSize().y / 2.f - 70});

    sf::Vector2f barSize = { 200.f, 15.f };
    sf::Vector2f barPos = topRight - sf::Vector2f(barSize.x + 30.f, view.getSize().y - 30.f);

    target.draw(speedText);

    target.setView(oldView);
}