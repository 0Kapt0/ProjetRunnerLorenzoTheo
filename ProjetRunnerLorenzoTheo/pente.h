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
	Pente(unsigned int lengthVal, float amplitudeVal = 1.f, unsigned int precisionVal = 10u, std::string slopeType = "flat");

	int getSurfaceHeight(int x);
	sf::Angle getOrientation(int x);

	void draw(sf::RenderWindow& window);
};

