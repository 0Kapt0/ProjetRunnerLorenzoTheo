#pragma once
#include "SFML/Graphics.hpp"

class View
{
private:
	sf::View view;
	sf::Vector2f cameraTarget;
	float cameraSmoothness;
	sf::Vector2f cameraOffset;

public:
	View();

	void updateCamera(float dt, sf::Vector2f playerPos);
	sf::View& getView() { return view; }
	void setView(sf::RenderWindow& window);
	void reset(sf::Vector2f playerPos);
};