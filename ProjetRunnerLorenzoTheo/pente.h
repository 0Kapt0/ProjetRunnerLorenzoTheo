#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Pente
{
private:
	std::vector<sf::Vector2f> points;
	sf::VertexArray ground;

	unsigned int precision;
	int length;
	int endHeight;
	int positionX;

public:

	Pente(unsigned int lengthVal, float amplitudeVal, unsigned int precisionVal, sf::Angle angleDepart, sf::Angle angleArrivee, int startHeight, int endHeight, int positionXVal);

	int getSurfaceHeight(int x);
	int getLength();
	int getEndHeight();
	sf::Vector2f getEndPosition();
	sf::Angle getOrientation(int x);

	void draw(sf::RenderWindow& window);
};

