#pragma once
#include "pente.h"

class BlocNiveau
{
private:
	int length;
	sf::Vector2f positionStart;
	int presetId;

	std::vector<Pente> penteList;
public:

	BlocNiveau(sf::Vector2f posVal, int presetId);

	int getLength();
	sf::Vector2f getEndPosition();
	void draw(sf::RenderWindow& window);
};

