#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Pente
{
private:
	std::vector<sf::Vector2f> points;
	sf::VertexArray ground;

	unsigned int precision;

public:

	Pente(unsigned int lengthVal, float amplitudeVal, unsigned int precisionVal, sf::Angle angleDepart, sf::Angle angleArrivee, int startHeight, int endHeight, int positionX);

	int getSurfaceHeight(int x);
	sf::Angle getOrientation(int x);

	void draw(sf::RenderWindow& window);
};

