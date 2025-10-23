#pragma once
#include "SFML/Graphics.hpp"
class Bonus
{
protected:
	sf::Vector2f position;

public:
	sf::Vector2f getPosition();

	virtual void draw(sf::RenderWindow& window);
};

