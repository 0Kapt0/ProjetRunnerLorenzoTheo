#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Speedometer
{
private:
	sf::Vector2f uiPos;
	sf::Text speedText;
	
public:
	Speedometer(const sf::Font& font);
	void setSpeedText(float s);
	void draw(sf::RenderTarget& target, const sf::View& view, const sf::Vector2f& playerPos);
};

